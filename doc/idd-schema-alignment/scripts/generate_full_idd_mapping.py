#!/usr/bin/env python3
"""Generate full OpenStudio <-> EnergyPlus IDD mapping inventory.

Outputs:
- doc/idd-schema-alignment/idd_mapping.md (human summary)
- doc/idd-schema-alignment/idd_mapping_appendix.generated.md (machine appendix)

This supersedes the original HVAC-only inventory with a complete two-way analysis
across all OS and EP IDD object types. Mapping evidence is derived from:
- ForwardTranslator.cpp switch (OS type -> model class -> translate function)
- ForwardTranslator function bodies (translate function -> produced EP IDD types)
- ReverseTranslator.cpp switch (EP type -> reverse translate function)
"""

from __future__ import annotations

import re
from collections import defaultdict
from pathlib import Path
from typing import Iterable

ROOT = Path(__file__).resolve().parents[3]
OS_IDD_PATH = ROOT / "resources/model/OpenStudio.idd"
EP_IDD_PATH = ROOT / "resources/energyplus/ProposedEnergy+.idd"
FT_CPP = ROOT / "src/energyplus/ForwardTranslator.cpp"
FT_DIR = ROOT / "src/energyplus/ForwardTranslator"
RT_CPP = ROOT / "src/energyplus/ReverseTranslator.cpp"
SUMMARY_OUT_PATH = ROOT / "doc/idd-schema-alignment/idd_mapping.md"
APPENDIX_OUT_PATH = ROOT / "doc/idd-schema-alignment/idd_mapping_appendix.generated.md"

OBJ_RE = re.compile(r"^\s*([A-Za-z0-9:_]+),\s*$")
FIELD_RE = re.compile(r"^\s*([AN]\d+)[,;]\s*(.*)$")


# -------- IDD parsing --------
def parse_idd_object_names(text: str) -> list[str]:
    names: list[str] = []
    for raw in text.splitlines():
        line = raw.rstrip("\n")
        if not line or line.lstrip().startswith("!"):
            continue
        m = OBJ_RE.match(line)
        if not m:
            continue
        name = m.group(1)
        if FIELD_RE.match(line):
            continue
        names.append(name)
    # de-duplicate preserving order
    out: list[str] = []
    seen: set[str] = set()
    for n in names:
        if n not in seen:
            seen.add(n)
            out.append(n)
    return out


def os_idd_name_to_enum(name: str) -> str:
    # OS:Foo:Bar -> OS_Foo_Bar
    assert name.startswith("OS:"), name
    return "OS_" + name[3:].replace(":", "_")


def os_enum_to_idd_name(enum_name: str) -> str:
    # OS_Foo_Bar -> OS:Foo:Bar
    assert enum_name.startswith("OS_"), enum_name
    return "OS:" + enum_name[3:].replace("_", ":")


# -------- C++ parsing helpers --------
def find_matching_brace(text: str, open_brace_idx: int) -> int:
    depth = 0
    i = open_brace_idx
    in_str = False
    in_chr = False
    in_line_comment = False
    in_block_comment = False
    escape = False

    while i < len(text):
        ch = text[i]
        nxt = text[i + 1] if i + 1 < len(text) else ""

        if in_line_comment:
            if ch == "\n":
                in_line_comment = False
            i += 1
            continue

        if in_block_comment:
            if ch == "*" and nxt == "/":
                in_block_comment = False
                i += 2
                continue
            i += 1
            continue

        if in_str:
            if escape:
                escape = False
            elif ch == "\\":
                escape = True
            elif ch == '"':
                in_str = False
            i += 1
            continue

        if in_chr:
            if escape:
                escape = False
            elif ch == "\\":
                escape = True
            elif ch == "'":
                in_chr = False
            i += 1
            continue

        if ch == "/" and nxt == "/":
            in_line_comment = True
            i += 2
            continue
        if ch == "/" and nxt == "*":
            in_block_comment = True
            i += 2
            continue
        if ch == '"':
            in_str = True
            i += 1
            continue
        if ch == "'":
            in_chr = True
            i += 1
            continue

        if ch == "{":
            depth += 1
        elif ch == "}":
            depth -= 1
            if depth == 0:
                return i

        i += 1

    return -1


def find_matching_paren(text: str, open_paren_idx: int) -> int:
    depth = 0
    i = open_paren_idx
    in_str = False
    in_chr = False
    in_line_comment = False
    in_block_comment = False
    escape = False

    while i < len(text):
        ch = text[i]
        nxt = text[i + 1] if i + 1 < len(text) else ""

        if in_line_comment:
            if ch == "\n":
                in_line_comment = False
            i += 1
            continue

        if in_block_comment:
            if ch == "*" and nxt == "/":
                in_block_comment = False
                i += 2
                continue
            i += 1
            continue

        if in_str:
            if escape:
                escape = False
            elif ch == "\\":
                escape = True
            elif ch == '"':
                in_str = False
            i += 1
            continue

        if in_chr:
            if escape:
                escape = False
            elif ch == "\\":
                escape = True
            elif ch == "'":
                in_chr = False
            i += 1
            continue

        if ch == "/" and nxt == "/":
            in_line_comment = True
            i += 2
            continue
        if ch == "/" and nxt == "*":
            in_block_comment = True
            i += 2
            continue
        if ch == '"':
            in_str = True
            i += 1
            continue
        if ch == "'":
            in_chr = True
            i += 1
            continue

        if ch == "(":
            depth += 1
        elif ch == ")":
            depth -= 1
            if depth == 0:
                return i

        i += 1

    return -1


def parse_ft_switch(text: str) -> dict[str, dict[str, str | None]]:
    """Parse ForwardTranslator switch cases.

    Returns dict keyed by OS enum type with fields:
    - model_class
    - translate_fn
    - mode: translated / no-op / warn
    """
    out: dict[str, dict[str, str | None]] = {}

    case_re = re.compile(r"case\s+openstudio::IddObjectType::(OS_[A-Za-z0-9_]+)\s*:\s*\{")
    matches = list(case_re.finditer(text))

    for i, m in enumerate(matches):
        os_enum = m.group(1)
        block_start = m.end() - 1  # points to '{'
        block_end = find_matching_brace(text, block_start)
        if block_end == -1:
            continue
        body = text[block_start + 1 : block_end]

        model_class = None
        translate_fn = None
        mode = "no-op"

        m_cast = re.search(r"cast<\s*([A-Za-z0-9_:]+)\s*>", body)
        if m_cast:
            model_class = m_cast.group(1).split("::")[-1]

        m_fn = re.search(r"retVal\s*=\s*(translate[A-Za-z0-9_]+)\s*\(", body)
        if m_fn:
            translate_fn = m_fn.group(1)
            mode = "translated"
        elif "LOG(Warn" in body:
            mode = "warn"

        out[os_enum] = {
            "model_class": model_class,
            "translate_fn": translate_fn,
            "mode": mode,
        }

    return out


def parse_ft_functions(files: Iterable[Path], class_name: str) -> dict[str, dict[str, str]]:
    """Return function metadata for class_name::func definitions.

    Output map: fn_name -> {"body": str, "signature": str}
    """
    out: dict[str, dict[str, str]] = {}
    fn_re = re.compile(rf"\b{re.escape(class_name)}::([A-Za-z0-9_]+)\s*\(")

    for path in files:
        text = path.read_text(errors="ignore")
        for m in fn_re.finditer(text):
            fn = m.group(1)
            sig_open_paren = m.end() - 1
            sig_close_paren = find_matching_paren(text, sig_open_paren)
            if sig_close_paren == -1:
                continue
            i = sig_close_paren + 1
            while i < len(text) and text[i].isspace():
                i += 1
            if i >= len(text) or text[i] != "{":
                # Declaration/prototype or unexpected form.
                continue
            open_idx = i
            close_idx = find_matching_brace(text, open_idx)
            if close_idx == -1:
                continue
            signature = text[m.start() : sig_close_paren + 1]
            out[fn] = {"body": text[open_idx + 1 : close_idx], "signature": signature}

    return out


def parse_first_model_param_class(signature: str) -> str | None:
    m = re.search(r"\(\s*(?:const\s+)?([A-Za-z0-9_:]+)\s*&\s*[A-Za-z_][A-Za-z0-9_]*", signature)
    if not m:
        return None
    return m.group(1).split("::")[-1]


def ep_types_created_in_function(body: str) -> list[str]:
    patterns = [
        r"createAndRegisterIdfObject\s*\(\s*(?:openstudio::)?IddObjectType::([A-Za-z0-9_]+)",
        r"createRegisterAndNameIdfObject\s*\(\s*(?:openstudio::)?IddObjectType::([A-Za-z0-9_]+)",
        r"IdfObject\s+[A-Za-z_][A-Za-z0-9_]*\s*\(\s*(?:openstudio::)?IddObjectType::([A-Za-z0-9_]+)",
        r"emplace_back\s*\(\s*(?:openstudio::)?IddObjectType::([A-Za-z0-9_]+)",
        r"push_back\s*\(\s*IdfObject\s*\(\s*(?:openstudio::)?IddObjectType::([A-Za-z0-9_]+)",
    ]
    out: list[str] = []
    seen: set[str] = set()
    for pat in patterns:
        for t in re.findall(pat, body):
            if t.startswith("OS_"):
                continue
            if t not in seen:
                seen.add(t)
                out.append(t)
    return out


def parse_rt_switch(text: str) -> dict[str, str | None]:
    """Parse ReverseTranslator switch: EP enum -> translate fn name."""
    out: dict[str, str | None] = {}
    case_re = re.compile(r"case\s+openstudio::IddObjectType::([A-Za-z0-9_]+)\s*:\s*\{")
    matches = list(case_re.finditer(text))
    for m in matches:
        ep_enum = m.group(1)
        block_start = m.end() - 1
        block_end = find_matching_brace(text, block_start)
        if block_end == -1:
            continue
        body = text[block_start + 1 : block_end]
        m_fn = re.search(r"modelObject\s*=\s*(translate[A-Za-z0-9_]+)\s*\(", body)
        out[ep_enum] = m_fn.group(1) if m_fn else None
    return out


def main() -> None:
    os_idd_names = [n for n in parse_idd_object_names(OS_IDD_PATH.read_text(errors="ignore")) if n.startswith("OS:")]
    ep_idd_names = [n for n in parse_idd_object_names(EP_IDD_PATH.read_text(errors="ignore")) if not n.startswith("OS:")]

    os_enum_to_names: dict[str, list[str]] = defaultdict(list)
    for n in os_idd_names:
        os_enum_to_names[os_idd_name_to_enum(n)].append(n)

    ep_enum_to_names: dict[str, list[str]] = defaultdict(list)
    for n in ep_idd_names:
        ep_enum_to_names[n.replace(":", "_")].append(n)

    ft_switch = parse_ft_switch(FT_CPP.read_text(errors="ignore"))

    ft_files = [FT_CPP] + sorted(FT_DIR.glob("*.cpp"))
    ft_functions = parse_ft_functions(ft_files, "ForwardTranslator")

    # OS enum -> EP enums from forward translator
    os_to_ep: dict[str, list[str]] = {}
    os_to_model: dict[str, str | None] = {}
    os_to_mode: dict[str, str] = {}
    os_to_fn: dict[str, str | None] = {}

    for os_enum_list in os_enum_to_names.values():
        # one row per actual OS IDD object name; each maps back to a single enum token.
        os_enum = os_idd_name_to_enum(os_enum_list[0])
        entry = ft_switch.get(os_enum, {"model_class": None, "translate_fn": None, "mode": "missing-switch"})
        model_class = entry.get("model_class")
        translate_fn = entry.get("translate_fn")
        mode = (entry.get("mode") or "missing-switch")

        ep_types: list[str] = []
        if isinstance(translate_fn, str):
            fn_meta = ft_functions.get(translate_fn)
            if fn_meta:
                ep_types = ep_types_created_in_function(fn_meta["body"])

        os_to_ep[os_enum] = ep_types
        os_to_model[os_enum] = model_class if isinstance(model_class, str) else None
        os_to_mode[os_enum] = mode
        os_to_fn[os_enum] = translate_fn if isinstance(translate_fn, str) else None

    # Reverse translator coverage (EP->fn)
    rt_switch = parse_rt_switch(RT_CPP.read_text(errors="ignore"))

    # EP -> source OS enums (invert from forward map)
    ep_to_os: dict[str, set[str]] = defaultdict(set)
    for os_enum, ep_list in os_to_ep.items():
        for ep in ep_list:
            ep_to_os[ep].add(os_enum)

    # Second pass: include translator functions that are not switch-dispatched
    # (for example model-level translation flows like AirflowNetwork).
    class_to_os: dict[str, set[str]] = defaultdict(set)
    for os_enum, model_class in os_to_model.items():
        if model_class:
            class_to_os[model_class].add(os_enum)

    norm_to_os: dict[str, list[str]] = defaultdict(list)
    for os_enum in os_enum_to_names:
        norm_to_os[os_enum[3:].replace("_", "").lower()].append(os_enum)

    for fn, meta in ft_functions.items():
        if not fn.startswith("translate"):
            continue
        model_class = parse_first_model_param_class(meta["signature"])
        if not model_class:
            continue
        ep_list = [e for e in ep_types_created_in_function(meta["body"]) if e in ep_enum_to_names]
        if not ep_list:
            continue

        targets: set[str] = set()
        if model_class in class_to_os:
            targets |= class_to_os[model_class]
        else:
            norm = model_class.replace("_", "").lower()
            cands = norm_to_os.get(norm, [])
            if len(cands) == 1:
                targets.add(cands[0])

        for os_enum in targets:
            existing = set(os_to_ep.get(os_enum, []))
            existing |= set(ep_list)
            os_to_ep[os_enum] = sorted(existing)
            if not os_to_model.get(os_enum):
                os_to_model[os_enum] = model_class
            if os_to_mode.get(os_enum) in {"missing-switch", "no-op"}:
                os_to_mode[os_enum] = "translated-indirect"

    # Build rows for OS objects
    os_rows: list[dict[str, str]] = []
    os_only_count = 0
    os_mapped_count = 0

    for os_name in sorted(os_idd_names):
        os_enum = os_idd_name_to_enum(os_name)
        model_class = os_to_model.get(os_enum) or ""
        fn = os_to_fn.get(os_enum) or ""
        mode = os_to_mode.get(os_enum, "missing-switch")
        ep_list = os_to_ep.get(os_enum, [])

        # retain only EP objects that exist in ProposedEnergy+.idd
        ep_list = [e for e in ep_list if e in ep_enum_to_names]

        inferred_name_match = ""
        if not ep_list:
            candidate = os_enum[3:]  # drop OS_
            candidate_names = ep_enum_to_names.get(candidate, [])
            if len(candidate_names) == 1:
                inferred_name_match = candidate_names[0]
            elif len(candidate_names) > 1:
                inferred_name_match = f"ambiguous: {', '.join(candidate_names)}"

        ep_display: list[str] = []
        for ep_enum in sorted(ep_list):
            names = ep_enum_to_names.get(ep_enum, [])
            if len(names) == 1:
                ep_display.append(f"`{names[0]}`")
            elif len(names) > 1:
                ep_display.append(f"`{ep_enum}` (ambiguous: {', '.join(f'`{n}`' for n in names)})")
            else:
                ep_display.append(f"`{ep_enum}`")

        if ep_list:
            status = "Mapped"
            os_mapped_count += 1
        else:
            status = "OS-only / no EP output"
            os_only_count += 1

        os_rows.append(
            {
                "os": os_name,
                "model": model_class,
                "ep": ", ".join(ep_display) if ep_display else "",
                "status": status,
                "mode": mode,
                "fn": fn,
                "name_match": inferred_name_match,
            }
        )

    # Build EP rows
    ep_rows: list[dict[str, str]] = []
    ep_only_count = 0
    ep_generated_count = 0
    ep_generated_with_peer_count = 0
    ep_generated_no_peer_count = 0

    for ep_name in sorted(ep_idd_names):
        ep_enum = ep_name.replace(":", "_")
        os_sources = sorted(ep_to_os.get(ep_enum, set()))
        rt_fn = rt_switch.get(ep_enum)

        os_sources_display: list[str] = []
        for os_enum in os_sources:
            os_names = os_enum_to_names.get(os_enum, [])
            if len(os_names) == 1:
                os_sources_display.append(f"`{os_names[0]}`")
            elif len(os_names) > 1:
                os_sources_display.append(f"`{os_enum}` (ambiguous: {', '.join(f'`{n}`' for n in os_names)})")
            else:
                os_sources_display.append(f"`{os_enum}`")

        direct_os_peer = f"OS:{ep_name}" in os_idd_names

        if os_sources:
            if direct_os_peer:
                status = "Generated by translator (has direct OS IDD peer)"
                ep_generated_with_peer_count += 1
            else:
                status = "Generated by translator (no direct OS IDD peer)"
                ep_generated_no_peer_count += 1
            ep_generated_count += 1
        else:
            status = "EP-only (no OS forward source found)"
            ep_only_count += 1

        ep_rows.append(
            {
                "ep": ep_name,
                "os_sources": ", ".join(os_sources_display),
                "status": status,
                "rt_fn": rt_fn or "",
            }
        )

    os_only_types = sorted([r["os"] for r in os_rows if r["status"].startswith("OS-only")])
    ep_only_types = sorted([r["ep"] for r in ep_rows if r["status"].startswith("EP-only")])

    summary_lines: list[str] = []
    summary_lines.append("# IDD Mapping Summary (OS ↔ E+)")
    summary_lines.append("")
    summary_lines.append("This file summarizes full two-way type coverage between OpenStudio and EnergyPlus IDDs.")
    summary_lines.append("")
    summary_lines.append("Detailed generated tables are in `idd_mapping_appendix.generated.md`.")
    summary_lines.append("")
    summary_lines.append("## Counts")
    summary_lines.append("")
    summary_lines.append(f"- Total OS objects (`OpenStudio.idd`, `OS:*`): {len(os_idd_names)}")
    summary_lines.append(f"- Total EP objects (`ProposedEnergy+.idd`): {len(ep_idd_names)}")
    summary_lines.append(f"- OS objects with explicit EP output via ForwardTranslator: {os_mapped_count}")
    summary_lines.append(f"- OS-only / no EP output evidence: {os_only_count}")
    summary_lines.append(f"- EP objects generated by translator: {ep_generated_count}")
    summary_lines.append(f"- EP generated with direct OS IDD peer: {ep_generated_with_peer_count}")
    summary_lines.append(f"- EP generated with no direct OS IDD peer: {ep_generated_no_peer_count}")
    summary_lines.append(f"- EP-only / no OS forward source found: {ep_only_count}")
    summary_lines.append("")
    summary_lines.append("## OS-only Types")
    summary_lines.append("")
    for t in os_only_types:
        summary_lines.append(f"- `{t}`")
    summary_lines.append("")
    summary_lines.append("## E+-only Types")
    summary_lines.append("")
    for t in ep_only_types:
        summary_lines.append(f"- `{t}`")
    summary_lines.append("")
    summary_lines.append("## Notes")
    summary_lines.append("")
    summary_lines.append("- OS-only here means no EP object creation evidence was found in forward translation paths.")
    summary_lines.append("- E+-only here means no producing OS type was found by forward-translation analysis.")
    summary_lines.append("- ReverseTranslator function evidence is tracked in the appendix for EP-side context.")

    appendix_lines: list[str] = []
    appendix_lines.append("# IDD Mapping Appendix (Generated)")
    appendix_lines.append("")
    appendix_lines.append("This appendix is machine-generated from IDDs and translator source.")
    appendix_lines.append("")
    appendix_lines.append("## Method")
    appendix_lines.append("")
    appendix_lines.append("1. Parse object names from both IDDs.")
    appendix_lines.append("2. Parse `ForwardTranslator.cpp` switch to link `OS_*` -> model class -> `translateX` function.")
    appendix_lines.append("3. Parse all ForwardTranslator function bodies for created `IddObjectType` IDF objects.")
    appendix_lines.append("4. Include indirect model-level translator functions (not switch-dispatched) by matching model parameter class.")
    appendix_lines.append("5. Invert mapping for EP-side coverage and annotate with `ReverseTranslator.cpp` switch function names.")
    appendix_lines.append("")
    appendix_lines.append("## OS -> EP (Full)")
    appendix_lines.append("")
    appendix_lines.append("| OS IddObjectType | Model class (FT switch/indirect) | EP IddObjectType(s) produced | Status | FT function |")
    appendix_lines.append("| --- | --- | --- | --- | --- |")
    for r in os_rows:
        appendix_lines.append(
            f"| `{r['os']}` | `{r['model']}` | {r['ep'] or ''} | {r['status']} | `{r['fn']}` |"
        )

    appendix_lines.append("")
    appendix_lines.append("## EP -> OS (Full)")
    appendix_lines.append("")
    appendix_lines.append("| EP IddObjectType | Source OS IddObjectType(s) (from FT) | Status | RT function (if in switch) |")
    appendix_lines.append("| --- | --- | --- | --- |")
    for r in ep_rows:
        appendix_lines.append(f"| `{r['ep']}` | {r['os_sources']} | {r['status']} | `{r['rt_fn']}` |")

    SUMMARY_OUT_PATH.write_text("\n".join(summary_lines) + "\n")
    APPENDIX_OUT_PATH.write_text("\n".join(appendix_lines) + "\n")


if __name__ == "__main__":
    main()
