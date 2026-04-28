#!/usr/bin/env python3
"""Generate HVAC OS IDD object relationship documentation.

This parses OpenStudio.idd for object-list relationships and writes
`doc/idd-schema-alignment/os_idd_object_relationships.md`.
"""

from __future__ import annotations

import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
IDD_PATH = ROOT / "resources/model/OpenStudio.idd"
HVAC_MAPPING_PATH = ROOT / "doc/idd-schema-alignment/idd_mapping.generated.md"
OUT_PATH = ROOT / "doc/idd-schema-alignment/os_idd_object_relationships.md"

SUPPRESS_LISTS = {"AllObjects"}
MAX_TARGETS = 25
HARDCODED_REFERENCE_LISTS = {
    "ConnectionNames": "Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD",
}


FIELD_RE = re.compile(r"^\s*([AN]\d+)[,;]\s*(.*)$")
OBJ_RE = re.compile(r"^\s*([A-Za-z0-9:_]+),\s*$")


def parse_hvac_objects(text: str) -> list[str]:
    os_tokens = re.findall(r"`(OS:[A-Za-z0-9:]+|OS_[A-Za-z0-9_]+)`", text)
    seen: set[str] = set()
    hvac_os: list[str] = []
    for token in os_tokens:
        if token.startswith("OS_"):
            token = "OS:" + token[3:].replace("_", ":")
        if token not in seen:
            seen.add(token)
            hvac_os.append(token)
    return hvac_os


def parse_attrs(line: str, field: dict) -> None:
    for attr in ("field", "type", "object-list", "reference"):
        for match in re.finditer(rf"\\{attr}\s+([^\\]+)", line):
            value = match.group(1).strip()
            if attr == "field":
                field["label"] = value
            elif attr == "type":
                field["type"] = value
            elif attr == "object-list":
                field.setdefault("object_lists", []).append(value)
            elif attr == "reference":
                field.setdefault("references", []).append(value)


def parse_idd(text: str) -> dict[str, dict]:
    objects: dict[str, dict] = {}
    current_obj: str | None = None
    current_field: dict | None = None

    def finish_field() -> None:
        nonlocal current_field
        if current_field is None:
            return
        objects[current_obj]["fields"].append(current_field)
        current_field = None

    def finish_object() -> None:
        nonlocal current_obj, current_field
        if current_obj is None:
            return
        finish_field()
        current_obj = None

    for raw in text.splitlines():
        line = raw.rstrip("\n")
        if not line or line.lstrip().startswith("!"):
            continue

        m_obj = OBJ_RE.match(line)
        if m_obj:
            name = m_obj.group(1)
            if not re.match(r"^[AN]\d+$", name):
                finish_object()
                current_obj = name
                objects[current_obj] = {"fields": []}
                continue

        if current_obj is None:
            continue

        m_field = FIELD_RE.match(line)
        if m_field:
            finish_field()
            current_field = {
                "index": m_field.group(1),
                "label": None,
                "type": None,
                "object_lists": [],
                "references": [],
            }
            parse_attrs(m_field.group(2), current_field)
        else:
            if current_field is None:
                continue
            parse_attrs(line, current_field)

        if line.rstrip().endswith(";"):
            finish_object()

    return objects


def main() -> None:
    hvac_idd = parse_hvac_objects(HVAC_MAPPING_PATH.read_text())
    objects = parse_idd(IDD_PATH.read_text())

    reference_providers: dict[str, set[str]] = {}
    for obj_name, data in objects.items():
        for field in data["fields"]:
            for ref in field.get("references", []):
                reference_providers.setdefault(ref, set()).add(obj_name)

    relations: dict[str, list[dict]] = {}
    no_refs: list[str] = []
    missing: list[str] = []
    for obj_name in hvac_idd:
        data = objects.get(obj_name)
        if not data:
            missing.append(obj_name)
            continue
        out: list[dict] = []
        for field in data["fields"]:
            obj_lists = sorted(set(field.get("object_lists", [])))
            if not obj_lists:
                continue
            for obj_list in obj_lists:
                out.append(
                    {
                        "field_index": field["index"],
                        "field_label": field.get("label") or field["index"],
                        "object_list": obj_list,
                        "targets": sorted(reference_providers.get(obj_list, [])),
                    }
                )
        if out:
            relations[obj_name] = out
        else:
            no_refs.append(obj_name)

    lines: list[str] = []
    lines.append("# OS IDD Object Relationships (HVAC)")
    lines.append("")
    lines.append(
        "This document lists **object-list based relationships** between HVAC-related OpenStudio IDD object types."
    )
    lines.append("")
    lines.append("## How this was derived")
    lines.append("")
    lines.append("- Source of truth: `resources/model/OpenStudio.idd`.")
    lines.append("- mapping object set: `doc/idd-schema-alignment/idd_mapping.generated.md` (all `OS:*` rows).")
    lines.append("- For each object, fields with `\\object-list` are treated as outgoing references.")
    lines.append(
        "- Target objects are inferred by matching `\\object-list <ListName>` to objects whose fields declare `\\reference <ListName>`."
    )
    lines.append("- Relationships are **schema-based only** (no implicit C++ translator relationships).")
    lines.append("")
    lines.append("## Update / Reproduce")
    lines.append("")
    lines.append("- Parse `resources/model/OpenStudio.idd` into object blocks and fields.")
    lines.append(
        "- Collect HVAC object types from `doc/idd-schema-alignment/idd_mapping.generated.md` (`OS:*` rows)."
    )
    lines.append("- For each HVAC object, list each field that declares `\\object-list`; emit one row per field/object-list pair.")
    lines.append(
        "- Resolve targets by linking `\\object-list <ListName>` to objects that declare `\\reference <ListName>`.")
    lines.append(
        "- If a target list is very large (more than 25 entries) or is `AllObjects`, suppress the expanded list and report the count instead."
    )
    lines.append("- Record HVAC objects missing from `OpenStudio.idd` and those with no `\\object-list` fields.")
    lines.append("")

    if missing:
        lines.append("Note: The following HVAC objects from `idd_mapping.generated.md` were not found in `OpenStudio.idd`:")
        lines.append("")
        lines.append(", ".join(f"`{obj}`" for obj in missing))
        lines.append("")

    lines.append("## Relationships")
    lines.append("")

    for obj_name in sorted(relations):
        lines.append(f"### `{obj_name}`")
        lines.append("")
        lines.append("| Field | Object List | Target OS IddObjectTypes |")
        lines.append("| --- | --- | --- |")
        for entry in relations[obj_name]:
            field_label = f"`{entry['field_index']}` {entry['field_label']}"
            obj_list = entry["object_list"]
            targets = entry["targets"]
            if obj_list in HARDCODED_REFERENCE_LISTS:
                target_text = HARDCODED_REFERENCE_LISTS[obj_list]
            elif obj_list in SUPPRESS_LISTS or len(targets) > MAX_TARGETS:
                target_text = f"{len(targets)} targets (suppressed; list is `{obj_list}`)"
            elif not targets:
                target_text = "No `\\reference` matches found"
            else:
                target_text = ", ".join(f"`{target}`" for target in targets)
            lines.append(f"| {field_label} | `{obj_list}` | {target_text} |")
        lines.append("")

    if no_refs:
        lines.append("## HVAC Objects Without Object-List References")
        lines.append("")
        lines.append(", ".join(f"`{obj}`" for obj in sorted(no_refs)))
        lines.append("")

    OUT_PATH.write_text("\n".join(lines) + "\n")


if __name__ == "__main__":
    main()
