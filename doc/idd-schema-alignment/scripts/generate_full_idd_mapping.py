#!/usr/bin/env python3
"""Generate the OpenStudio -> EnergyPlus IDD mapping inventory.

Output:
- doc/idd-schema-alignment/idd_mapping.generated.md

Mapping evidence is derived from:
- `src/model` `iddObjectType()` definitions
- `ForwardTranslator.cpp` switch dispatch
- ForwardTranslator function bodies and source files
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
MODEL_DIR = ROOT / "src/model"
OUT_PATH = ROOT / "doc/idd-schema-alignment/idd_mapping.generated.md"

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

    Output map: fn_name -> {"body": str, "signature": str, "path": str}
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
            out[fn] = {
                "body": text[open_idx + 1 : close_idx],
                "signature": signature,
                "path": str(path.relative_to(ROOT)),
            }

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


def parse_model_idd_mappings(files: Iterable[Path]) -> dict[str, dict[str, str]]:
    """Return OS enum -> canonical model metadata from src/model sources."""
    out: dict[str, dict[str, str]] = {}
    fn_re = re.compile(r"IddObjectType\s+([A-Za-z0-9_]+)::iddObjectType\s*\(\s*\)\s*\{")

    for path in files:
        text = path.read_text(errors="ignore")
        for m in fn_re.finditer(text):
            model_class = m.group(1)
            block_start = text.find("{", m.end() - 1)
            if block_start == -1:
                continue
            block_end = find_matching_brace(text, block_start)
            if block_end == -1:
                continue
            body = text[block_start + 1 : block_end]
            m_ret = re.search(r"(?:openstudio::)?IddObjectType::(OS_[A-Za-z0-9_]+)", body)
            if not m_ret:
                continue
            out[m_ret.group(1)] = {"model_class": model_class}

    return out


def parse_model_direct_bases(files: Iterable[Path]) -> dict[str, str]:
    """Return canonical model class -> direct public base class from src/model headers."""
    out: dict[str, str] = {}
    class_re = re.compile(
        r"class\s+(?:MODEL_API\s+)?([A-Za-z_][A-Za-z0-9_]*)\s*:\s*public\s+([A-Za-z_][A-Za-z0-9_:<>]*)",
        re.MULTILINE,
    )

    for path in files:
        if path.name.endswith("_Impl.hpp"):
            continue
        text = path.read_text(errors="ignore")
        for model_class, base_class in class_re.findall(text):
            if model_class not in out:
                out[model_class] = base_class.split("::")[-1]

    return out


def normalize_name_for_alignment(name: str) -> str:
    return re.sub(r"[^A-Za-z0-9]", "", name).lower()


def main() -> None:
    os_idd_names = [n for n in parse_idd_object_names(OS_IDD_PATH.read_text(errors="ignore")) if n.startswith("OS:")]
    ep_idd_names = [n for n in parse_idd_object_names(EP_IDD_PATH.read_text(errors="ignore")) if not n.startswith("OS:")]

    os_enum_to_names: dict[str, list[str]] = defaultdict(list)
    for n in os_idd_names:
        os_enum_to_names[os_idd_name_to_enum(n)].append(n)

    ep_enum_to_names: dict[str, list[str]] = defaultdict(list)
    for n in ep_idd_names:
        ep_enum_to_names[n.replace(":", "_")].append(n)
    normalized_ep_names: dict[str, list[str]] = defaultdict(list)
    for n in ep_idd_names:
        normalized_ep_names[normalize_name_for_alignment(n)].append(n)

    ft_switch = parse_ft_switch(FT_CPP.read_text(errors="ignore"))

    ft_files = [FT_CPP] + sorted(FT_DIR.glob("*.cpp"))
    ft_functions = parse_ft_functions(ft_files, "ForwardTranslator")
    model_mappings = parse_model_idd_mappings(sorted(MODEL_DIR.rglob("*.cpp")))
    model_direct_bases = parse_model_direct_bases(sorted(MODEL_DIR.rglob("*.hpp")))

    # OS enum -> EP enums from forward translator
    os_to_ep: dict[str, list[str]] = {}
    os_to_model: dict[str, str | None] = {}
    os_to_direct_base: dict[str, str | None] = {}
    os_to_ft_files: dict[str, set[str]] = defaultdict(set)

    for os_enum_list in os_enum_to_names.values():
        # one row per actual OS IDD object name; each maps back to a single enum token.
        os_enum = os_idd_name_to_enum(os_enum_list[0])
        entry = ft_switch.get(os_enum, {"model_class": None, "translate_fn": None, "mode": "missing-switch"})
        translate_fn = entry.get("translate_fn")
        mode = (entry.get("mode") or "missing-switch")

        ep_types: list[str] = []
        if isinstance(translate_fn, str):
            fn_meta = ft_functions.get(translate_fn)
            if fn_meta:
                ep_types = ep_types_created_in_function(fn_meta["body"])
                os_to_ft_files[os_enum].add(fn_meta["path"])

        os_to_ep[os_enum] = ep_types
        model_info = model_mappings.get(os_enum)
        model_class = model_info["model_class"] if model_info else None
        os_to_model[os_enum] = model_class
        os_to_direct_base[os_enum] = model_direct_bases.get(model_class) if model_class else None

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
            os_to_ft_files[os_enum].add(meta["path"])
    # Build rows for OS objects
    os_rows: list[dict[str, str]] = []
    for os_name in sorted(os_idd_names):
        os_enum = os_idd_name_to_enum(os_name)
        model_class = os_to_model.get(os_enum) or ""
        direct_base = os_to_direct_base.get(os_enum) or ""
        ft_files = ", ".join(f"`{path}`" for path in sorted(os_to_ft_files.get(os_enum, set())))
        ep_list = os_to_ep.get(os_enum, [])

        # retain only EP objects that exist in ProposedEnergy+.idd
        ep_list = [e for e in ep_list if e in ep_enum_to_names]

        ep_display: list[str] = []
        for ep_enum in sorted(ep_list):
            names = ep_enum_to_names.get(ep_enum, [])
            if len(names) == 1:
                ep_display.append(f"`{names[0]}`")
            elif len(names) > 1:
                ep_display.append(f"`{ep_enum}` (ambiguous: {', '.join(f'`{n}`' for n in names)})")
            else:
                ep_display.append(f"`{ep_enum}`")

        os_rows.append(
            {
                "os": os_name,
                "model": model_class,
                "direct_base": direct_base,
                "ep": ", ".join(ep_display) if ep_display else "",
                "ep_names": ", ".join(f"`{n}`" for ep_enum in sorted(ep_list) for n in ep_enum_to_names.get(ep_enum, [ep_enum])),
                "ft_files": ft_files,
            }
        )

    os_rows_no_ep_output = [r for r in os_rows if not r["ep"]]
    os_rows_no_name_alignment = [
        r
        for r in os_rows
        if r["model"] and r["ep_names"] and normalize_name_for_alignment(r["model"]) not in normalized_ep_names
    ]

    lines: list[str] = []
    lines.append("# IDD Mapping (Generated)")
    lines.append("")
    lines.append("This file is machine-generated from IDDs and translator source.")
    lines.append("")
    lines.append("## Method")
    lines.append("")
    lines.append("1. Parse object names from both IDDs.")
    lines.append("2. Parse `src/model` `iddObjectType()` definitions to link `OS_*` -> canonical model class.")
    lines.append("3. Parse `ForwardTranslator.cpp` switch to link `OS_*` -> direct `translateX` function.")
    lines.append("4. Parse ForwardTranslator function bodies and source files for created EP `IddObjectType` IDF objects.")
    lines.append("5. Include indirect model-level translator functions (not switch-dispatched) by matching model parameter class.")
    lines.append("")
    lines.append("## OS -> EP (Full)")
    lines.append("")
    lines.append("| OS IddObjectType | Model class | Direct OS base class | EP IddObjectType(s) produced | FT source file(s) |")
    lines.append("| --- | --- | --- | --- | --- |")
    for r in os_rows:
        lines.append(f"| `{r['os']}` | `{r['model']}` | `{r['direct_base']}` | {r['ep'] or ''} | {r['ft_files']} |")

    lines.append("")
    lines.append("## OS Types With No EP Output Evidence")
    lines.append("")
    lines.append("| OS IddObjectType | Model class | Direct OS base class | FT source file(s) |")
    lines.append("| --- | --- | --- | --- |")
    for r in os_rows_no_ep_output:
        lines.append(f"| `{r['os']}` | `{r['model']}` | `{r['direct_base']}` | {r['ft_files']} |")

    lines.append("")
    lines.append("## OS ModelObject Types Without E+ Name Alignment")
    lines.append("")
    lines.append(
        "Name alignment here is based on the canonical `openstudio::model` class name and the EnergyPlus IDD type name after normalizing away punctuation and case differences."
    )
    lines.append("")
    lines.append("| OS IddObjectType | ModelObject Name | E+ IDD Type Name |")
    lines.append("| --- | --- | --- |")
    for r in os_rows_no_name_alignment:
        lines.append(f"| `{r['os']}` | `{r['model']}` | {r['ep_names']} |")

    OUT_PATH.write_text("\n".join(lines) + "\n")


if __name__ == "__main__":
    main()
