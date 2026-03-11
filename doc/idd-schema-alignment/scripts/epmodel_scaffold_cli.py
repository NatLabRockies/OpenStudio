#!/usr/bin/env python3
"""Temporary queue driver for epmodel scaffold saturation."""

from __future__ import annotations

import argparse
import datetime as dt
import json
import os
import re
import subprocess
import sys
from collections import Counter
from pathlib import Path
from typing import Any, Counter as CounterType, Dict, List, Optional, Set, Tuple

try:  # Optional dependency
    import yaml  # type: ignore
except ImportError:
    yaml = None


RESULT_BEGIN = "EPMODEL_SCAFFOLD_RESULT_BEGIN"
RESULT_END = "EPMODEL_SCAFFOLD_RESULT_END"
DEFAULT_MAX_RETRIES = 3
DEFAULT_MAX_MINUTES_PER_TYPE = 30
VALID_STATUSES = {"pending", "in_progress", "done", "blocked", "deferred"}
APPENDIX_PATH = Path("doc/idd-schema-alignment/idd_mapping_appendix.generated.md")
COMMIT_IGNORE_PATHS = {"EPModelTestFixture.log"}
# Minimum items needed to keep a bucket. Set to 1 to effectively disable size-based climbing.
BUCKET_THRESHOLD = 1


def utc_now() -> str:
    return dt.datetime.now(dt.timezone.utc).replace(microsecond=0).isoformat().replace("+00:00", "Z")


class ScaffoldState:
    def __init__(self, root: Path) -> None:
        self.root = root
        self.doc_root = root / "doc" / "idd-schema-alignment"
        self.scaffold_root = self.doc_root / "scaffold"
        self.contract_path = self.doc_root / "epmodel-scaffold-contract.md"
        self.inventory_path = self.scaffold_root / "inventory.yml"
        self.overrides_path = self.scaffold_root / "overrides.yml"
        self.runs_log_path = self.scaffold_root / "runs.log.yml"

    def ensure_files(self) -> None:
        required = [
            self.contract_path,
            self.inventory_path,
            self.overrides_path,
            self.runs_log_path,
        ]
        missing = [str(p) for p in required if not p.exists()]
        if missing:
            raise SystemExit("Missing required scaffold files:\n- " + "\n- ".join(missing))

    def load_contract_version(self) -> str:
        text = self.contract_path.read_text(encoding="utf-8")
        match = re.search(r"^contract_version:\s*(\S+)\s*$", text, flags=re.MULTILINE)
        if not match:
            raise SystemExit(f"Unable to find contract_version in {self.contract_path}")
        return match.group(1)

    def load_inventory(self) -> List[Dict[str, Any]]:
        data = load_yaml(self.inventory_path)
        if not isinstance(data, list):
            raise SystemExit(f"{self.inventory_path} must contain a top-level list")
        for i, item in enumerate(data):
            if not isinstance(item, dict):
                raise SystemExit(f"inventory record #{i} must be a map")
            status = item.get("status")
            if status not in VALID_STATUSES:
                raise SystemExit(f"inventory record #{i} has invalid status: {status}")
        return data

    def save_inventory(self, inventory: List[Dict[str, Any]]) -> None:
        save_yaml(self.inventory_path, inventory)

    def load_runs_log(self) -> List[Dict[str, Any]]:
        data = load_yaml(self.runs_log_path)
        if data is None:
            return []
        if not isinstance(data, list):
            raise SystemExit(f"{self.runs_log_path} must contain a top-level list")
        return data

    def append_run_log(self, entry: Dict[str, Any]) -> None:
        data = self.load_runs_log()
        data.append(entry)
        save_yaml(self.runs_log_path, data)


def load_yaml(path: Path) -> Any:
    text = path.read_text(encoding="utf-8")
    if yaml is not None:
        return yaml.safe_load(text)
    return json.loads(text)


def save_yaml(path: Path, data: Any) -> None:
    if yaml is not None:
        with path.open("w", encoding="utf-8") as f:
            yaml.safe_dump(data, f, sort_keys=False, default_flow_style=False, allow_unicode=False)
    else:
        path.write_text(json.dumps(data, indent=2) + "\n", encoding="utf-8")


def dump_for_print(data: Any) -> str:
    if yaml is not None:
        return yaml.safe_dump(data, sort_keys=False).strip()
    return json.dumps(data, indent=2)


def first_pending_index(inventory: List[Dict[str, Any]]) -> Optional[int]:
    for i, item in enumerate(inventory):
        if item.get("status") == "pending":
            return i
    return None


def recover_stale_in_progress(state: ScaffoldState) -> List[str]:
    """Reset stale in_progress rows to pending after an interrupted run."""
    inventory = state.load_inventory()
    recovered: List[str] = []
    for item in inventory:
        if item.get("status") == "in_progress":
            item["status"] = "pending"
            recovered.append(str(item.get("idd_type", "")))
    if recovered:
        state.save_inventory(inventory)
    return recovered


def _clean_cell(value: str) -> str:
    value = value.strip()
    if value.startswith("`") and value.endswith("`"):
        value = value[1:-1]
    return value.strip()


def _extract_backticked_values(value: str) -> List[str]:
    return [v.strip() for v in re.findall(r"`([^`]+)`", value) if v.strip()]


def _camel_from_name(name: str) -> str:
    parts = re.split(r"[:\-\s_]+", name)
    return "".join(p[:1].upper() + p[1:] for p in parts if p)


def _class_from_os_type(os_type: str) -> str:
    s = os_type
    if s.startswith("OS:"):
        s = s[3:]
    return _camel_from_name(s)


def _extract_model_classes_and_parent_map(state: ScaffoldState) -> Tuple[Set[str], Dict[str, Optional[str]]]:
    model_root = state.root / "src" / "model"
    model_classes: Set[str] = set()
    parent_map: Dict[str, Optional[str]] = {}
    class_decl = re.compile(
        r"class\s+(?:[A-Za-z_]\w*\s+)*(?P<name>[A-Za-z_]\w*)\s*(?::\s*public\s+(?P<base>[A-Za-z_]\w*))?\s*\{"
    )
    for hpp in sorted(model_root.rglob("*.hpp")):
        text = hpp.read_text(encoding="utf-8", errors="ignore")
        for match in class_decl.finditer(text):
            name = match.group("name")
            base = match.group("base")
            if name == "detail" or name.endswith("_Impl"):
                continue
            model_classes.add(name)
            parent_map[name] = base
    return model_classes, parent_map


def _extract_epmodel_classes(state: ScaffoldState) -> Set[str]:
    epmodel_root = state.root / "src" / "epmodel"
    classes: Set[str] = set()
    class_decl = re.compile(r"class\s+(?:[A-Za-z_]\w*\s+)*(?P<name>[A-Za-z_]\w*)\s*(?::\s*public\s+[A-Za-z_]\w*)?\s*\{")
    for hpp in sorted(epmodel_root.rglob("*.hpp")):
        text = hpp.read_text(encoding="utf-8", errors="ignore")
        for match in class_decl.finditer(text):
            name = match.group("name")
            if name in {"detail"}:
                continue
            classes.add(name)
    classes.add("ModelObject")
    return classes


def _extract_forward_signature_function_map(state: ScaffoldState) -> Dict[str, str]:
    header = state.root / "src" / "energyplus" / "ForwardTranslator.hpp"
    if not header.exists():
        return {}
    text = header.read_text(encoding="utf-8", errors="ignore")
    out: Dict[str, str] = {}
    for match in re.finditer(r"\b(translate[A-Za-z0-9_]+)\s*\(\s*model::([A-Za-z_]\w*)\s*&\s*modelObject", text):
        out[match.group(1)] = match.group(2)
    return out


def _appendix_sections(state: ScaffoldState) -> Dict[str, List[str]]:
    appendix = state.root / APPENDIX_PATH
    text = appendix.read_text(encoding="utf-8", errors="ignore")
    sections: Dict[str, List[str]] = {}
    current = ""
    for line in text.splitlines():
        if line.startswith("## "):
            current = line[3:].strip()
            sections[current] = []
            continue
        if current:
            sections[current].append(line)
    return sections


def _appendix_os_to_model_class_map(state: ScaffoldState) -> Tuple[Dict[str, str], Dict[str, str]]:
    sections = _appendix_sections(state)
    lines = sections.get("OS -> EP (Full)", [])
    os_to_model: Dict[str, str] = {}
    fn_to_model: Dict[str, str] = {}
    for line in lines:
        if not line.startswith("| `OS:"):
            continue
        parts = [p.strip() for p in line.split("|")]
        if len(parts) < 6:
            continue
        os_vals = _extract_backticked_values(parts[1])
        if not os_vals:
            continue
        os_type = os_vals[0]
        model_class = _clean_cell(parts[2])
        if not model_class:
            continue
        os_to_model[os_type] = model_class
        fns = _extract_backticked_values(parts[5])
        if fns:
            fn_to_model[fns[0]] = model_class
    return os_to_model, fn_to_model


def _appendix_ep_rows(state: ScaffoldState) -> Dict[str, Dict[str, Any]]:
    sections = _appendix_sections(state)
    lines = sections.get("EP -> OS (Full)", [])
    rows: Dict[str, Dict[str, Any]] = {}
    for line in lines:
        if not line.startswith("| `"):
            continue
        parts = [p.strip() for p in line.split("|")]
        if len(parts) < 6:
            continue
        ep_vals = _extract_backticked_values(parts[1])
        if not ep_vals:
            continue
        ep = ep_vals[0]
        os_vals = _extract_backticked_values(parts[2])
        status_text = _clean_cell(parts[3]).lower()
        rt_vals = _extract_backticked_values(parts[4])
        rows[ep] = {
            "os_types": os_vals,
            "status_text": status_text,
            "rt_function": rt_vals[0] if rt_vals else "",
        }
    return rows


def _resolve_counterpart_class(
    record: Dict[str, Any],
    ep_row: Dict[str, Any],
    os_to_model_class: Dict[str, str],
    fn_to_model_class: Dict[str, str],
    fn_to_model_from_signature: Dict[str, str],
    model_classes: Set[str],
) -> Tuple[Optional[str], str, str]:
    # Priority 1: direct OS counterpart(s) from appendix EP row.
    os_types = [str(x) for x in ep_row.get("os_types", [])]
    for os_type in os_types:
        cls = os_to_model_class.get(os_type)
        if cls and cls in model_classes:
            return cls, "appendix_os_to_model", "high"

    # Priority 2: RT function name mapped to model class from appendix OS rows.
    rt_fn = str(ep_row.get("rt_function", "") or "")
    if rt_fn:
        cls = fn_to_model_class.get(rt_fn)
        if cls and cls in model_classes:
            return cls, "appendix_rt_function", "medium"
        cls = fn_to_model_from_signature.get(rt_fn)
        if cls and cls in model_classes:
            return cls, "forward_signature", "medium"

    # Priority 3: direct type class if already canonical.
    existing_target = str(record.get("target_class", "") or "").strip()
    if existing_target and existing_target in model_classes:
        return existing_target, "inventory_target_class", "low"

    # Priority 4: best-effort fallback from OS type naming transform.
    for os_type in os_types:
        fallback = _class_from_os_type(os_type)
        if fallback in model_classes:
            return fallback, "os_type_name_transform", "low"

    return None, "", ""


def _intended_base_for_target(target_class: str, parent_map: Dict[str, Optional[str]]) -> str:
    base = parent_map.get(target_class)
    if base:
        return base
    return "ModelObject"


def _choose_bucket(
    intended_base: str, parent_map: Dict[str, Optional[str]], bucket_counts: CounterType[str], threshold: int
) -> str:
    current = intended_base or "ModelObject"
    seen: Set[str] = set()
    while current and current not in seen:
        seen.add(current)
        if bucket_counts.get(current, 0) >= threshold:
            return current
        parent = parent_map.get(current)
        if not parent:
            break
        current = parent
    return "ModelObject"


def resolve_model_classes_preflight(state: ScaffoldState, print_summary: bool = False) -> Dict[str, int]:
    inventory = state.load_inventory()
    model_classes, _parent_map = _extract_model_classes_and_parent_map(state)
    os_to_model, fn_to_model_from_appendix = _appendix_os_to_model_class_map(state)
    ep_rows = _appendix_ep_rows(state)
    fn_to_model_from_signature = _extract_forward_signature_function_map(state)

    resolved_count = 0
    unresolved_count = 0
    updated_count = 0
    blocked_count = 0

    for item in inventory:
        has_counterpart = bool(item.get("has_model_counterpart", False))
        idd_type = str(item.get("idd_type", "") or "")
        prior = (
            str(item.get("resolved_model_class", "") or ""),
            str(item.get("resolver_source", "") or ""),
            str(item.get("resolver_confidence", "") or ""),
            str(item.get("resolver_error", "") or ""),
            str(item.get("target_class", "") or ""),
            str(item.get("status", "") or ""),
            str(item.get("notes", "") or ""),
        )

        if not has_counterpart:
            # Keep non-counterpart rows IDD-derived.
            if not str(item.get("target_class", "") or "").strip():
                item["target_class"] = _camel_from_name(idd_type)
            item.pop("resolved_model_class", None)
            item.pop("resolver_source", None)
            item.pop("resolver_confidence", None)
            item.pop("resolver_error", None)
            after = (
                str(item.get("resolved_model_class", "") or ""),
                str(item.get("resolver_source", "") or ""),
                str(item.get("resolver_confidence", "") or ""),
                str(item.get("resolver_error", "") or ""),
                str(item.get("target_class", "") or ""),
                str(item.get("status", "") or ""),
                str(item.get("notes", "") or ""),
            )
            if prior != after:
                updated_count += 1
            continue

        ep_row = ep_rows.get(idd_type, {"os_types": [], "status_text": "", "rt_function": ""})
        resolved, source, confidence = _resolve_counterpart_class(
            item,
            ep_row,
            os_to_model,
            fn_to_model_from_appendix,
            fn_to_model_from_signature,
            model_classes,
        )
        if resolved:
            resolved_count += 1
            item["resolved_model_class"] = resolved
            item["resolver_source"] = source
            item["resolver_confidence"] = confidence
            item.pop("resolver_error", None)
            item["target_class"] = resolved
        else:
            unresolved_count += 1
            item.pop("resolved_model_class", None)
            item["resolver_source"] = "unresolved"
            item["resolver_confidence"] = "none"
            rt_fn = str(ep_row.get("rt_function", "") or "")
            os_types = ", ".join(str(x) for x in (ep_row.get("os_types", []) or []))
            item["resolver_error"] = (
                f"Unable to resolve canonical openstudio::model class for counterpart row {idd_type}. "
                f"os_types=[{os_types}] rt_function={rt_fn or '<none>'}"
            )
            if item.get("status") != "done":
                item["status"] = "blocked"
                item["notes"] = item["resolver_error"]
                blocked_count += 1

        after = (
            str(item.get("resolved_model_class", "") or ""),
            str(item.get("resolver_source", "") or ""),
            str(item.get("resolver_confidence", "") or ""),
            str(item.get("resolver_error", "") or ""),
            str(item.get("target_class", "") or ""),
            str(item.get("status", "") or ""),
            str(item.get("notes", "") or ""),
        )
        if prior != after:
            updated_count += 1

    if updated_count > 0:
        state.save_inventory(inventory)

    if print_summary:
        print("Resolver preflight summary:")
        print(f"- resolved_counterparts: {resolved_count}")
        print(f"- unresolved_counterparts: {unresolved_count}")
        print(f"- newly_blocked: {blocked_count}")
        print(f"- inventory_records_updated: {updated_count}")

    return {
        "resolved_counterparts": resolved_count,
        "unresolved_counterparts": unresolved_count,
        "newly_blocked": blocked_count,
        "updated": updated_count,
        "total": len(inventory),
    }


def _reclassify_inventory_records(state: ScaffoldState, inventory: List[Dict[str, Any]]) -> Tuple[List[Dict[str, Any]], Dict[str, int]]:
    model_classes, parent_map = _extract_model_classes_and_parent_map(state)
    epmodel_classes = _extract_epmodel_classes(state)

    intended_base_by_type: Dict[str, str] = {}
    for item in inventory:
        idd_type = str(item.get("idd_type", ""))
        target_class = str(item.get("target_class", "") or "").strip()
        has_counterpart = bool(item.get("has_model_counterpart", False))
        if has_counterpart:
            resolved = str(item.get("resolved_model_class", "") or "").strip()
            if resolved:
                target_class = resolved
                item["target_class"] = resolved
        if target_class and target_class not in model_classes and has_counterpart:
            target_class = "ModelObject"
        intended_base_by_type[idd_type] = _intended_base_for_target(target_class, parent_map)

    bucket_counts: CounterType[str] = Counter(intended_base_by_type.values())

    updates = 0
    for item in inventory:
        idd_type = str(item.get("idd_type", ""))
        intended_base = intended_base_by_type.get(idd_type, "ModelObject")
        bucket = _choose_bucket(intended_base, parent_map, bucket_counts, BUCKET_THRESHOLD)
        effective_base = intended_base if intended_base in epmodel_classes else "ModelObject"
        output_dir = f"src/epmodel/{bucket}"

        before = (
            str(item.get("intended_base_class", "")),
            str(item.get("base_class", "")),
            str(item.get("folder_bucket", "")),
            str(item.get("output_dir", "")),
        )
        after = (intended_base, effective_base, bucket, output_dir)
        if before != after:
            updates += 1
            item["intended_base_class"] = intended_base
            item["base_class"] = effective_base
            item["folder_bucket"] = bucket
            item["output_dir"] = output_dir

    return inventory, {"updated": updates, "total": len(inventory)}


def refresh_inventory_classification(state: ScaffoldState, print_summary: bool = False) -> Dict[str, int]:
    resolver_stats = resolve_model_classes_preflight(state, print_summary=print_summary)
    inventory = state.load_inventory()
    inventory, stats = _reclassify_inventory_records(state, inventory)
    if stats["updated"] > 0:
        state.save_inventory(inventory)
    if print_summary:
        print(
            "Resolver preflight: "
            f"{resolver_stats['resolved_counterparts']} resolved, "
            f"{resolver_stats['unresolved_counterparts']} unresolved, "
            f"{resolver_stats['newly_blocked']} newly blocked"
        )
        print(f"Reclassified inventory records: {stats['updated']} updated / {stats['total']} total")
    return {
        "updated": stats["updated"],
        "total": stats["total"],
        "resolved_counterparts": resolver_stats["resolved_counterparts"],
        "unresolved_counterparts": resolver_stats["unresolved_counterparts"],
        "newly_blocked": resolver_stats["newly_blocked"],
    }


def seed_inventory_from_appendix(state: ScaffoldState) -> int:
    appendix = state.root / APPENDIX_PATH
    if not appendix.exists():
        raise SystemExit(f"Cannot seed inventory: missing {appendix}")

    text = appendix.read_text(encoding="utf-8")
    lines = text.splitlines()

    in_ep_section = False
    by_idd: Dict[str, Dict[str, Any]] = {}
    inventory = state.load_inventory()
    for item in inventory:
        it = item.get("idd_type")
        if isinstance(it, str):
            by_idd[it] = item

    added = 0
    for line in lines:
        if line.startswith("## EP -> OS (Full)"):
            in_ep_section = True
            continue
        if in_ep_section and line.startswith("## "):
            break
        if not in_ep_section:
            continue
        if not line.startswith("| `"):
            continue

        parts = [p.strip() for p in line.split("|")]
        if len(parts) < 5:
            continue

        ep_vals = _extract_backticked_values(parts[1])
        ep_type = ep_vals[0] if ep_vals else _clean_cell(parts[1])
        os_vals = _extract_backticked_values(parts[2])
        status_col = _clean_cell(parts[3]).lower()
        if not ep_type:
            continue

        has_model_counterpart = any(v.startswith("OS:") for v in os_vals)
        if has_model_counterpart:
            first_os = next((v for v in os_vals if v.startswith("OS:")), os_vals[0])
            target_class = _class_from_os_type(first_os)
        else:
            target_class = _camel_from_name(ep_type)

        if ep_type in by_idd:
            item = by_idd[ep_type]
            # Preserve workflow state but refresh metadata for consistency.
            item["target_class"] = target_class
            item["has_model_counterpart"] = has_model_counterpart
            continue

        item = {
            "idd_type": ep_type,
            "status": "pending",
            "target_class": target_class,
            "intended_base_class": "ModelObject",
            "base_class": "ModelObject",
            "folder_bucket": "ModelObject",
            "output_dir": "src/epmodel/ModelObject",
            "has_model_counterpart": has_model_counterpart,
            "notes": "auto-seeded from EP inventory appendix",
        }
        inventory.append(item)
        by_idd[ep_type] = item
        added += 1

    state.save_inventory(inventory)
    refresh_inventory_classification(state, print_summary=False)
    return added


def expected_output_dir(record: Dict[str, Any]) -> str:
    output_dir = record.get("output_dir")
    if isinstance(output_dir, str) and output_dir.strip():
        return output_dir.strip()
    bucket = str(record.get("folder_bucket", "ModelObject")).strip() or "ModelObject"
    return f"src/epmodel/{bucket}"


def expected_type_basename(record: Dict[str, Any]) -> str:
    target_class = str(record.get("target_class", "")).strip()
    if target_class:
        return target_class
    return _camel_from_name(str(record.get("idd_type", "")))


def expected_base_migration_files(state: ScaffoldState, record: Dict[str, Any]) -> List[Tuple[Path, Path]]:
    """Return (root_path, target_path) files that must be migrated with subdir introduction.

    If a base class file currently exists in src/epmodel root and output_dir is a subdirectory,
    require the corresponding file in output_dir after a successful run.
    """
    output_dir = expected_output_dir(record)
    if output_dir == "src/epmodel":
        return []

    base = str(record.get("base_class", "") or "").strip()
    if not base:
        return []

    root_dir = state.root / "src" / "epmodel"
    target_dir = state.root / output_dir
    pairs: List[Tuple[Path, Path]] = []
    for suffix in [".hpp", ".cpp", "_Impl.hpp"]:
        src = root_dir / f"{base}{suffix}"
        dst = target_dir / f"{base}{suffix}"
        if src.exists():
            pairs.append((src, dst))
    return pairs


def find_record_index(inventory: List[Dict[str, Any]], idd_type: str) -> Optional[int]:
    for i, item in enumerate(inventory):
        if item.get("idd_type") == idd_type:
            return i
    return None


def move_record_to_end(inventory: List[Dict[str, Any]], idx: int) -> List[Dict[str, Any]]:
    item = inventory.pop(idx)
    inventory.append(item)
    return inventory


def _parse_porcelain_paths(stdout: str) -> List[str]:
    paths: List[str] = []
    for line in stdout.splitlines():
        if not line:
            continue
        # format: XY <path> or XY <old> -> <new>
        item = line[3:] if len(line) > 3 else ""
        if " -> " in item:
            old, new = item.split(" -> ", 1)
            paths.append(old.strip())
            paths.append(new.strip())
        else:
            paths.append(item.strip())
    return [p for p in paths if p]


def _is_ignored_commit_path(path: str) -> bool:
    return path in COMMIT_IGNORE_PATHS


def _git_status_paths(state: ScaffoldState) -> List[str]:
    proc = subprocess.run(
        ["git", "status", "--porcelain"],
        cwd=str(state.root),
        text=True,
        capture_output=True,
        check=False,
    )
    if proc.returncode != 0:
        return []
    return _parse_porcelain_paths(proc.stdout)


def _is_clean_for_autocommit(state: ScaffoldState) -> bool:
    paths = _git_status_paths(state)
    meaningful = [p for p in paths if not _is_ignored_commit_path(p)]
    return len(meaningful) == 0


def _maybe_commit_done_type(state: ScaffoldState, idd_type: str, summary: str = "") -> Tuple[bool, str]:
    add_proc = subprocess.run(["git", "add", "-A"], cwd=str(state.root), text=True, capture_output=True, check=False)
    if add_proc.returncode != 0:
        return False, f"git add failed: {(add_proc.stderr or '').strip()}"

    for ignored in sorted(COMMIT_IGNORE_PATHS):
        subprocess.run(["git", "reset", "-q", "HEAD", "--", ignored], cwd=str(state.root), check=False)

    diff_proc = subprocess.run(["git", "diff", "--cached", "--quiet"], cwd=str(state.root), check=False)
    if diff_proc.returncode == 0:
        return True, "no staged changes to commit"

    msg = f"epmodel scaffold: {idd_type}"
    body = summary.strip()
    if body:
        commit_proc = subprocess.run(["git", "commit", "-m", msg, "-m", body], cwd=str(state.root), text=True, capture_output=True, check=False)
    else:
        commit_proc = subprocess.run(["git", "commit", "-m", msg], cwd=str(state.root), text=True, capture_output=True, check=False)
    if commit_proc.returncode != 0:
        err = (commit_proc.stderr or commit_proc.stdout or "").strip()
        return False, f"git commit failed: {err}"

    sha_proc = subprocess.run(["git", "rev-parse", "--short", "HEAD"], cwd=str(state.root), text=True, capture_output=True, check=False)
    sha = (sha_proc.stdout or "").strip() if sha_proc.returncode == 0 else ""
    return True, f"committed {sha}" if sha else "committed"


def build_prompt(state: ScaffoldState, contract_version: str, record: Dict[str, Any], max_minutes_per_type: int) -> str:
    idd_type = record.get("idd_type")
    target_class = record.get("target_class", "")
    base_class = record.get("base_class", "")
    bucket = record.get("folder_bucket", "")
    counterpart = record.get("has_model_counterpart", False)
    notes = str(record.get("notes", "") or "").strip()
    output_dir = expected_output_dir(record)
    base = expected_type_basename(record)
    expected_paths = [f"{output_dir}/{base}.hpp", f"{output_dir}/{base}.cpp", f"{output_dir}/{base}_Impl.hpp"]
    base_pairs = expected_base_migration_files(state, record)
    base_expectation_lines = [f"- move {src.relative_to(state.root)} -> {dst.relative_to(state.root)}" for src, dst in base_pairs]

    return f"""
You are running one serial scaffold cycle for epmodel.

Selected type:
- idd_type: {idd_type}
- target_class: {target_class}
- base_class: {base_class}
- folder_bucket: {bucket}
- output_dir: {output_dir}
- has_model_counterpart: {str(counterpart).lower()}
{f"- operator_notes: {notes}" if notes else ""}

Expected scaffold file locations:
- {expected_paths[0]}
- {expected_paths[1]}
- {expected_paths[2]}
{("Required base-class migration in this run:\\n" + chr(10).join(base_expectation_lines)) if base_expectation_lines else ""}

Required preflight:
1. Read doc/idd-schema-alignment/epmodel-scaffold-contract.md.
2. Read all files referenced by that contract.
3. Read doc/idd-schema-alignment/scaffold/inventory.yml.
4. Read doc/idd-schema-alignment/scaffold/overrides.yml.
5. Read doc/idd-schema-alignment/scaffold/runs.log.yml.

Hard rules:
- Preserve existing openstudio::model API/class names when counterpart exists.
- Preserve existing accessor names/signatures even if IDD field names drift.
- For no-counterpart types, use IDD-derived names.
- Use ForwardTranslator evidence when naming or field mapping drifts.
- Replicate Ruby model generator method placement conventions:
  - declarations in .hpp / _Impl.hpp
  - method definitions in .cpp
  - do not inline non-template scalar accessor bodies in .hpp
- Replicate Ruby generator field API semantics:
  - optionality logic from required/default/autosize/autocalculate metadata
  - choice handling (boolean vs non-boolean) and values helpers
  - setCanFail behavior and bool-return-with-assert pattern
  - default/autosize/autocalculate and reset method generation rules
  - required getter strictness and naming transform rules
- Generate/update exactly 3 files for this type: .hpp, .cpp, _Impl.hpp.
- Place/update those 3 type files under output_dir, not directly under src/epmodel root.
- If output_dir is a subdirectory and base class files exist in src/epmodel root, move those base files into output_dir in this run.
- For already-existing epmodel classes, migrate existing files into output_dir and update references as needed.
- For already-existing epmodel classes, keep existing non-scalar behavior and add missing scalar accessors incrementally.
- Generate simple scalar accessors only.
- Exclude relationship fields (object-list/reference/node/target-link).
- Do not classify as blocked merely because move/refactor work is needed for existing classes.
- If a true public API signature break appears required, STOP and classify as blocked.
- Add schema-alignment mapping comments per contract.
- Do not edit inventory.yml, overrides.yml, or runs.log.yml.

Execution:
1. Scaffold only this selected type.
2. Add/update targeted tests for compile + scalar accessor roundtrip.
3. Run targeted build/tests (use -j32 where the build/test command supports parallel jobs).
4. Keep iteration bounded to {max_minutes_per_type} minutes total.

Output requirements:
- Provide a human summary.
- Then emit EXACTLY one machine-readable JSON object between markers:
{RESULT_BEGIN}
<json>
{RESULT_END}

JSON schema:
{{
  "contract_version": "{contract_version}",
  "status": "done|blocked|retry",
  "summary": "...",
  "files_changed": ["path", "..."],
  "mapping_decisions": ["..."],
  "excluded_fields": ["..."],
  "ruby_parity_checks": {{
    "optionality_logic_applied": true,
    "choice_handling_applied": true,
    "setter_fail_semantics_applied": true,
    "default_auto_api_applied": true,
    "reset_rules_applied": true,
    "required_getter_strictness_applied": true,
    "naming_transform_applied": true
  }},
  "tests": "...",
  "blocker_reason": "..."
}}
- blocker_reason is required when status=blocked.
""".strip()


def parse_result(output: str) -> Tuple[Optional[Dict[str, Any]], Optional[str]]:
    pattern = re.compile(
        rf"{re.escape(RESULT_BEGIN)}\s*(\{{.*?\}})\s*{re.escape(RESULT_END)}",
        flags=re.DOTALL,
    )
    match = pattern.search(output)
    if not match:
        return None, "missing result block"

    payload = match.group(1)
    try:
        obj = json.loads(payload)
    except json.JSONDecodeError as exc:
        return None, f"invalid result json: {exc}"

    if not isinstance(obj, dict):
        return None, "result payload is not an object"

    status = obj.get("status")
    if status not in {"done", "blocked", "retry"}:
        return None, f"invalid status: {status}"

    if status == "blocked" and not obj.get("blocker_reason"):
        return None, "blocked result missing blocker_reason"

    checks = obj.get("ruby_parity_checks")
    if not isinstance(checks, dict):
        return None, "missing ruby_parity_checks object"

    required_checks = [
        "optionality_logic_applied",
        "choice_handling_applied",
        "setter_fail_semantics_applied",
        "default_auto_api_applied",
        "reset_rules_applied",
        "required_getter_strictness_applied",
        "naming_transform_applied",
    ]
    for key in required_checks:
        if key not in checks:
            return None, f"ruby_parity_checks missing key: {key}"
        if not isinstance(checks[key], bool):
            return None, f"ruby_parity_checks.{key} must be boolean"

    return obj, None


INLINE_METHOD_RE = re.compile(
    r"^\s*(?!class\b)(?!struct\b)(?!enum\b)(?!template\b)[\w:<>,~*&\s]+\([^;{}]*\)\s*(?:const\s*)?(?:noexcept\s*)?\{"
)


def _has_inline_methods_in_header(path: Path) -> bool:
    if not path.exists():
        return False
    for line in path.read_text(encoding="utf-8").splitlines():
        s = line.strip()
        if not s or s.startswith("//") or s.startswith("/*") or s.startswith("*") or s.startswith("#"):
            continue
        if INLINE_METHOD_RE.search(line):
            return True
    return False


def run_codex(
    prompt: str, cwd: Path, codex_model: str = "gpt-5.3-codex", agent: str = "opencode"
) -> subprocess.CompletedProcess[str]:
    selected_agent = (agent or "opencode").strip().lower()
    if selected_agent not in {"codex", "opencode"}:
        selected_agent = "opencode"

    runner_bin = os.environ.get("EPMODEL_AGENT_BIN", selected_agent)
    if selected_agent == "codex":
        cmd = [runner_bin, "exec"]
        if codex_model:
            cmd += ["-m", codex_model]
        cmd.append(prompt)
    else:
        cmd = [runner_bin, "run"]
        if codex_model:
            cmd += ["--model", codex_model]
        cmd.append(prompt)
    try:
        return subprocess.run(
            cmd,
            cwd=str(cwd),
            text=True,
            capture_output=True,
            check=False,
        )
    except FileNotFoundError:
        return subprocess.CompletedProcess(
            args=cmd,
            returncode=127,
            stdout="",
            stderr=f"runner binary not found: {runner_bin}",
        )


def process_one(
    state: ScaffoldState,
    record_idx: int,
    max_retries: int,
    max_minutes_per_type: int,
    codex_model: str,
    agent: str,
) -> Dict[str, Any]:
    inventory = state.load_inventory()
    record = inventory[record_idx]
    idd_type = record["idd_type"]
    contract_version = state.load_contract_version()
    expected_dir = expected_output_dir(record)
    expected_base = expected_type_basename(record)
    expected_files = [
        state.root / expected_dir / f"{expected_base}.hpp",
        state.root / expected_dir / f"{expected_base}.cpp",
        state.root / expected_dir / f"{expected_base}_Impl.hpp",
    ]
    expected_base_moves = expected_base_migration_files(state, record)

    record["status"] = "in_progress"
    inventory[record_idx] = record
    state.save_inventory(inventory)

    last_error = ""
    for attempt in range(1, max_retries + 1):
        prompt = build_prompt(state, contract_version, record, max_minutes_per_type)
        proc = run_codex(prompt, state.root, codex_model=codex_model, agent=agent)

        combined_output = ""
        if proc.stdout:
            combined_output += proc.stdout
        if proc.stderr:
            combined_output += "\n" + proc.stderr

        if proc.returncode != 0:
            stderr_snippet = (proc.stderr or "").strip().splitlines()
            tail = stderr_snippet[-3:] if stderr_snippet else []
            tail_text = " | ".join(tail)
            if tail_text:
                last_error = f"runner exited with code {proc.returncode}: {tail_text}"
            else:
                last_error = f"runner exited with code {proc.returncode}"
            continue

        result_obj, parse_error = parse_result(combined_output)
        if parse_error:
            last_error = parse_error
            continue

        returned_contract = str(result_obj.get("contract_version", ""))
        if returned_contract != contract_version:
            last_error = (
                f"contract_version mismatch: expected {contract_version}, got {returned_contract or '<empty>'}"
            )
            continue

        status = result_obj["status"]
        if status == "done":
            checks = result_obj.get("ruby_parity_checks", {})
            failed_checks = [k for k, v in checks.items() if not bool(v)]
            if failed_checks:
                last_error = f"done result failed ruby parity checks: {', '.join(sorted(failed_checks))}"
                continue

            missing_expected = [str(p.relative_to(state.root)) for p in expected_files if not p.exists()]
            if missing_expected:
                last_error = f"done result missing expected scaffold files in output_dir: {', '.join(missing_expected)}"
                continue

            missing_base_moves = [str(dst.relative_to(state.root)) for _src, dst in expected_base_moves if not dst.exists()]
            if missing_base_moves:
                last_error = (
                    "done result missing required base-class migrated files in output_dir: "
                    + ", ".join(missing_base_moves)
                )
                continue

            header_path = expected_files[0]
            if _has_inline_methods_in_header(header_path):
                last_error = f"done result violated style: inline non-template method bodies found in {header_path.relative_to(state.root)}"
                continue

            inventory = state.load_inventory()
            inventory[record_idx]["status"] = "done"
            state.save_inventory(inventory)

            state.append_run_log(
                {
                    "timestamp": utc_now(),
                    "idd_type": idd_type,
                    "status": "done",
                    "contract_version": contract_version,
                    "attempts": attempt,
                    "files_changed": result_obj.get("files_changed", []),
                    "mapping_decisions": result_obj.get("mapping_decisions", []),
                    "excluded_fields": result_obj.get("excluded_fields", []),
                    "ruby_parity_checks": result_obj.get("ruby_parity_checks", {}),
                    "tests": result_obj.get("tests", ""),
                    "notes": result_obj.get("summary", ""),
                }
            )
            return {
                "idd_type": idd_type,
                "status": "done",
                "attempts": attempt,
                "result": result_obj,
            }

        if status == "blocked":
            inventory = state.load_inventory()
            inventory[record_idx]["status"] = "blocked"
            inventory[record_idx]["notes"] = result_obj.get("blocker_reason", "")
            state.save_inventory(inventory)

            state.append_run_log(
                {
                    "timestamp": utc_now(),
                    "idd_type": idd_type,
                    "status": "blocked",
                    "contract_version": contract_version,
                    "attempts": attempt,
                    "files_changed": result_obj.get("files_changed", []),
                    "mapping_decisions": result_obj.get("mapping_decisions", []),
                    "excluded_fields": result_obj.get("excluded_fields", []),
                    "ruby_parity_checks": result_obj.get("ruby_parity_checks", {}),
                    "tests": result_obj.get("tests", ""),
                    "notes": result_obj.get("summary", ""),
                    "blocker_reason": result_obj.get("blocker_reason", ""),
                }
            )
            return {
                "idd_type": idd_type,
                "status": "blocked",
                "attempts": attempt,
                "result": result_obj,
            }

        # retry status: continue attempts
        last_error = str(result_obj.get("summary", "requested retry"))

    # Retries exhausted: put back to pending, record operational failure.
    inventory = state.load_inventory()
    inventory[record_idx]["status"] = "pending"
    state.save_inventory(inventory)

    state.append_run_log(
        {
            "timestamp": utc_now(),
            "idd_type": idd_type,
            "status": "retry_exhausted",
            "contract_version": contract_version,
            "attempts": max_retries,
            "files_changed": [],
            "mapping_decisions": [],
            "excluded_fields": [],
            "tests": "",
            "notes": last_error,
        }
    )

    return {
        "idd_type": idd_type,
        "status": "retry_exhausted",
        "attempts": max_retries,
        "error": last_error,
    }


def cmd_status(state: ScaffoldState) -> int:
    inventory = state.load_inventory()
    counts: Dict[str, int] = {k: 0 for k in VALID_STATUSES}
    for item in inventory:
        counts[item["status"]] += 1

    print("Queue status:")
    for status in ["pending", "in_progress", "done", "blocked", "deferred"]:
        print(f"- {status}: {counts.get(status, 0)}")

    idx = first_pending_index(inventory)
    if idx is None:
        print("Next pending: none")
    else:
        print(f"Next pending: {inventory[idx]['idd_type']}")
    return 0


def cmd_reclassify(state: ScaffoldState) -> int:
    stats = refresh_inventory_classification(state, print_summary=True)
    if stats["updated"] == 0 and stats["unresolved_counterparts"] == 0:
        print("No classification changes were needed.")
    return 0


def cmd_resolve_model_classes(state: ScaffoldState) -> int:
    stats = refresh_inventory_classification(state, print_summary=True)
    if stats["unresolved_counterparts"] > 0:
        print(f"Resolver preflight blocked {stats['unresolved_counterparts']} counterpart rows.")
        return 2
    return 0


def cmd_show(state: ScaffoldState, idd_type: str) -> int:
    inventory = state.load_inventory()
    idx = find_record_index(inventory, idd_type)
    if idx is None:
        print(f"Type not found in inventory: {idd_type}")
        return 1

    print("Inventory record:")
    print(dump_for_print(inventory[idx]))

    overrides = load_yaml(state.overrides_path) or {}
    if idd_type in overrides:
        print("Overrides:")
        print(dump_for_print(overrides[idd_type]))

    runs = state.load_runs_log()
    latest = None
    for entry in runs:
        if entry.get("idd_type") == idd_type:
            latest = entry
    if latest:
        print("Latest run:")
        print(dump_for_print(latest))
    return 0


def cmd_retry(state: ScaffoldState, idd_type: str) -> int:
    inventory = state.load_inventory()
    idx = find_record_index(inventory, idd_type)
    if idx is None:
        print(f"Type not found in inventory: {idd_type}")
        return 1

    if inventory[idx]["status"] not in {"blocked", "in_progress", "deferred"}:
        print(f"Type {idd_type} is in status {inventory[idx]['status']}, not retry-eligible")
        return 1

    inventory[idx]["status"] = "pending"
    state.save_inventory(inventory)
    print(f"Set {idd_type} to pending")
    return 0


def cmd_block(state: ScaffoldState, idd_type: str, reason: str) -> int:
    inventory = state.load_inventory()
    idx = find_record_index(inventory, idd_type)
    if idx is None:
        print(f"Type not found in inventory: {idd_type}")
        return 1

    inventory[idx]["status"] = "blocked"
    inventory[idx]["notes"] = reason
    state.save_inventory(inventory)

    state.append_run_log(
        {
            "timestamp": utc_now(),
            "idd_type": idd_type,
            "status": "blocked",
            "contract_version": state.load_contract_version(),
            "attempts": 0,
            "files_changed": [],
            "mapping_decisions": [],
            "excluded_fields": [],
            "tests": "",
            "notes": "manually blocked",
            "blocker_reason": reason,
        }
    )

    print(f"Blocked {idd_type}: {reason}")
    return 0


def cmd_unblock(state: ScaffoldState, idd_type: str) -> int:
    inventory = state.load_inventory()
    idx = find_record_index(inventory, idd_type)
    if idx is None:
        print(f"Type not found in inventory: {idd_type}")
        return 1

    if inventory[idx]["status"] not in {"blocked", "deferred"}:
        print(f"Type {idd_type} is in status {inventory[idx]['status']}, cannot unblock")
        return 1

    inventory[idx]["status"] = "pending"
    state.save_inventory(inventory)
    print(f"Unblocked {idd_type} -> pending")
    return 0


def _handle_blocked_interactive(
    state: ScaffoldState,
    idd_type: str,
    blocker_reason: str = "",
    summary: str = "",
    mapping_decisions: Optional[List[str]] = None,
    excluded_fields: Optional[List[str]] = None,
    tests: str = "",
) -> Tuple[str, str]:
    mapping_decisions = mapping_decisions or []
    excluded_fields = excluded_fields or []
    while True:
        print("Blocked item encountered.")
        if blocker_reason:
            print(f"Reason: {blocker_reason}")
        if summary:
            print(f"Summary: {summary}")
        if mapping_decisions:
            print("Mapping decisions:")
            for m in mapping_decisions[:10]:
                print(f"- {m}")
        if excluded_fields:
            print("Excluded fields:")
            for f in excluded_fields[:10]:
                print(f"- {f}")
        if tests:
            print(f"Tests: {tests}")
        print("Suggested next step: provide guidance and retry, or adjust overrides manually.")
        print("Choose action: [g]uidance+retry, [u]nblock-after-manual-fix, [d]efer, [k]eep-blocked, [q]uit")
        choice = input("> ").strip().lower()
        if choice == "g":
            print("Enter short guidance for next retry (stored in inventory notes):")
            guidance = input("> ").strip()
            if guidance:
                return "guidance_retry", guidance
            print("No guidance entered.")
            continue
        if choice == "u":
            print("Apply your edits/overrides now, then press Enter to continue.")
            input()
            inventory = state.load_inventory()
            idx = find_record_index(inventory, idd_type)
            if idx is not None:
                inventory[idx]["status"] = "pending"
                state.save_inventory(inventory)
            return "continue", ""
        if choice == "d":
            inventory = state.load_inventory()
            idx = find_record_index(inventory, idd_type)
            if idx is not None:
                inventory[idx]["status"] = "deferred"
                state.save_inventory(inventory)
            return "continue", ""
        if choice == "k":
            return "continue", ""
        if choice == "q":
            return "quit", ""


def cmd_next(
    state: ScaffoldState,
    max_retries: int,
    max_minutes_per_type: int,
    auto_commit: bool,
    codex_model: str,
    agent: str,
) -> int:
    recovered = recover_stale_in_progress(state)
    if recovered:
        print(f"Recovered stale in_progress -> pending: {', '.join(recovered)}")

    if auto_commit and not _is_clean_for_autocommit(state):
        print("Auto-commit aborted: working tree has pre-existing changes (excluding ignored paths).")
        return 1
    stats = refresh_inventory_classification(state)
    if stats["unresolved_counterparts"] > 0:
        print(
            f"Resolver preflight blocked {stats['unresolved_counterparts']} unresolved counterpart rows; "
            "they are marked blocked in inventory."
        )

    inventory = state.load_inventory()
    idx = first_pending_index(inventory)
    if idx is None:
        print("NO_PENDING_TYPES")
        return 0

    result = process_one(
        state,
        idx,
        max_retries=max_retries,
        max_minutes_per_type=max_minutes_per_type,
        codex_model=codex_model,
        agent=agent,
    )
    if auto_commit and result.get("status") == "done":
        result_obj = result.get("result", {}) if isinstance(result, dict) else {}
        summary = ""
        if isinstance(result_obj, dict):
            summary = str(result_obj.get("summary", "") or "")
        ok, msg = _maybe_commit_done_type(state, str(result.get("idd_type", "")), summary=summary)
        result["commit"] = msg
        if not ok:
            result["status"] = "commit_failed"
            print(dump_for_print(result))
            return 3

    print(dump_for_print(result))
    return 0 if result["status"] == "done" else 2


def cmd_run(
    state: ScaffoldState,
    max_retries: int,
    max_minutes_per_type: int,
    max_items: int = 0,
    auto_commit: bool = True,
    codex_model: str = "gpt-5.3-codex",
    agent: str = "opencode",
) -> int:
    recovered = recover_stale_in_progress(state)
    if recovered:
        print(f"Recovered stale in_progress -> pending: {', '.join(recovered)}")

    if auto_commit and not _is_clean_for_autocommit(state):
        print("Auto-commit aborted: working tree has pre-existing changes (excluding ignored paths).")
        return 1
    stats = refresh_inventory_classification(state)
    if stats["unresolved_counterparts"] > 0:
        print(
            f"Resolver preflight blocked {stats['unresolved_counterparts']} unresolved counterpart rows; "
            "they are marked blocked in inventory."
        )

    processed = 0
    done_count = 0
    blocked_count = 0
    exhausted_count = 0

    while True:
        if max_items > 0 and processed >= max_items:
            print(f"Reached max-items limit: {max_items}")
            break

        inventory = state.load_inventory()
        idx = first_pending_index(inventory)
        if idx is None:
            added = seed_inventory_from_appendix(state)
            if added > 0:
                print(f"Auto-seeded {added} pending types from appendix")
                inventory = state.load_inventory()
                idx = first_pending_index(inventory)
            if idx is None:
                print("NO_PENDING_TYPES")
                break

        result = process_one(
            state,
            idx,
            max_retries=max_retries,
            max_minutes_per_type=max_minutes_per_type,
            codex_model=codex_model,
            agent=agent,
        )
        processed += 1
        status = result["status"]
        idd_type = result["idd_type"]
        print(f"{idd_type}: {status}")

        if status == "done":
            done_count += 1
            if auto_commit:
                result_obj = result.get("result", {}) if isinstance(result, dict) else {}
                summary = ""
                if isinstance(result_obj, dict):
                    summary = str(result_obj.get("summary", "") or "")
                ok, msg = _maybe_commit_done_type(state, idd_type, summary=summary)
                print(f"{idd_type}: {msg}")
                if not ok:
                    print("Stopping run due to commit failure.")
                    break
            continue

        if status == "blocked":
            blocked_count += 1
            result_obj = result.get("result", {}) if isinstance(result, dict) else {}
            blocker_reason = ""
            summary = ""
            mapping_decisions: List[str] = []
            excluded_fields: List[str] = []
            tests = ""
            if isinstance(result_obj, dict):
                blocker_reason = str(result_obj.get("blocker_reason", "") or "")
                summary = str(result_obj.get("summary", "") or "")
                mapping_decisions = [str(x) for x in (result_obj.get("mapping_decisions", []) or [])]
                excluded_fields = [str(x) for x in (result_obj.get("excluded_fields", []) or [])]
                tests = str(result_obj.get("tests", "") or "")
            action, guidance = _handle_blocked_interactive(
                state,
                idd_type,
                blocker_reason=blocker_reason,
                summary=summary,
                mapping_decisions=mapping_decisions,
                excluded_fields=excluded_fields,
                tests=tests,
            )
            if action == "quit":
                break
            if action == "guidance_retry":
                inv = state.load_inventory()
                ridx = find_record_index(inv, idd_type)
                if ridx is not None:
                    prior = str(inv[ridx].get("notes", "") or "").strip()
                    inv[ridx]["notes"] = f"{prior} | operator-guidance: {guidance}" if prior else f"operator-guidance: {guidance}"
                    inv[ridx]["status"] = "pending"
                    state.save_inventory(inv)
            continue

        exhausted_count += 1
        # Skip this item for now by rotating it to the end of queue.
        inv = state.load_inventory()
        eidx = find_record_index(inv, idd_type)
        if eidx is not None:
            inv = move_record_to_end(inv, eidx)
            state.save_inventory(inv)

    print("Run summary:")
    print(f"- processed: {processed}")
    print(f"- done: {done_count}")
    print(f"- blocked: {blocked_count}")
    print(f"- retry_exhausted: {exhausted_count}")
    return 0


def build_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(description="epmodel scaffold queue driver")
    parser.add_argument("--repo-root", default=".", help="Path to repository root")

    sub = parser.add_subparsers(dest="cmd", required=True)

    status_p = sub.add_parser("status", help="Show queue status")
    status_p.set_defaults(func=lambda args, state: cmd_status(state))

    show_p = sub.add_parser("show", help="Show details for one type")
    show_p.add_argument("idd_type")
    show_p.set_defaults(func=lambda args, state: cmd_show(state, args.idd_type))

    retry_p = sub.add_parser("retry", help="Move type to pending")
    retry_p.add_argument("idd_type")
    retry_p.set_defaults(func=lambda args, state: cmd_retry(state, args.idd_type))

    block_p = sub.add_parser("block", help="Manually block a type")
    block_p.add_argument("idd_type")
    block_p.add_argument("--reason", required=True)
    block_p.set_defaults(func=lambda args, state: cmd_block(state, args.idd_type, args.reason))

    unblock_p = sub.add_parser("unblock", help="Unblock/defer back to pending")
    unblock_p.add_argument("idd_type")
    unblock_p.set_defaults(func=lambda args, state: cmd_unblock(state, args.idd_type))

    next_p = sub.add_parser("next", help="Process one pending type")
    next_p.add_argument("--max-retries", type=int, default=DEFAULT_MAX_RETRIES)
    next_p.add_argument("--max-minutes-per-type", type=int, default=DEFAULT_MAX_MINUTES_PER_TYPE)
    next_p.add_argument("--auto-commit", action=argparse.BooleanOptionalAction, default=True)
    next_p.add_argument(
        "--agent",
        choices=["codex", "opencode"],
        default="opencode",
        help="Agent runner to invoke (default: opencode)",
    )
    next_p.add_argument(
        "--model",
        "--codex-model",
        dest="model",
        default="gpt-5.3-codex",
        help="Model identifier to pass to the selected agent (default: gpt-5.3-codex)",
    )
    next_p.set_defaults(
        func=lambda args, state: cmd_next(
            state,
            max_retries=max(1, args.max_retries),
            max_minutes_per_type=max(1, args.max_minutes_per_type),
            auto_commit=bool(args.auto_commit),
            codex_model=str(args.model or ""),
            agent=str(args.agent or "opencode"),
        )
    )

    run_p = sub.add_parser("run", help="Continuously process pending types")
    run_p.add_argument("--max-retries", type=int, default=DEFAULT_MAX_RETRIES)
    run_p.add_argument("--max-minutes-per-type", type=int, default=DEFAULT_MAX_MINUTES_PER_TYPE)
    run_p.add_argument("--max-items", type=int, default=0, help="Process at most N types this run (0 = unlimited)")
    run_p.add_argument("--auto-commit", action=argparse.BooleanOptionalAction, default=True)
    run_p.add_argument(
        "--agent",
        choices=["codex", "opencode"],
        default="opencode",
        help="Agent runner to invoke (default: opencode)",
    )
    run_p.add_argument(
        "--model",
        "--codex-model",
        dest="model",
        default="gpt-5.3-codex",
        help="Model identifier to pass to the selected agent (default: gpt-5.3-codex)",
    )
    run_p.set_defaults(
        func=lambda args, state: cmd_run(
            state,
            max_retries=max(1, args.max_retries),
            max_minutes_per_type=max(1, args.max_minutes_per_type),
            max_items=max(0, args.max_items),
            auto_commit=bool(args.auto_commit),
            codex_model=str(args.model or ""),
            agent=str(args.agent or "opencode"),
        )
    )

    seed_p = sub.add_parser("seed", help="Seed pending types from EP inventory appendix")
    seed_p.set_defaults(
        func=lambda args, state: (
            print(f"Added {seed_inventory_from_appendix(state)} types"),
            0,
        )[1]
    )

    resolve_p = sub.add_parser("resolve-model-classes", help="Resolve canonical openstudio::model class names and reclassify inventory")
    resolve_p.set_defaults(func=lambda args, state: cmd_resolve_model_classes(state))

    reclassify_p = sub.add_parser("reclassify", help="Recompute base/bucket/output_dir metadata for all inventory types")
    reclassify_p.set_defaults(func=lambda args, state: cmd_reclassify(state))

    return parser


def main(argv: Optional[List[str]] = None) -> int:
    parser = build_parser()
    args = parser.parse_args(argv)
    root = Path(args.repo_root).resolve()
    state = ScaffoldState(root)
    state.ensure_files()
    return args.func(args, state)


if __name__ == "__main__":
    sys.exit(main())
