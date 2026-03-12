#!/usr/bin/env python3
"""Manifest-driven backend for resumable epmodel campaigns."""

from __future__ import annotations

import argparse
import datetime as dt
import glob as globlib
import hashlib
import json
import os
import re
import subprocess
import sys
from dataclasses import dataclass
from pathlib import Path
from typing import Any, Dict, Iterable, List, Optional, Sequence, Tuple


WORKFLOW_ID = "epmodel_campaign"
STATE_ROOT = ".opencode/epmodel-campaigns"
RESOLUTION_RESULT_BEGIN = "EPMODEL_RESOLUTION_RESULT_BEGIN"
RESOLUTION_RESULT_END = "EPMODEL_RESOLUTION_RESULT_END"


def utc_now() -> str:
    return dt.datetime.now(dt.timezone.utc).replace(microsecond=0).isoformat().replace("+00:00", "Z")


def utc_stamp() -> str:
    return dt.datetime.now(dt.timezone.utc).strftime("%Y%m%dT%H%M%SZ")


def slugify(value: str) -> str:
    lowered = value.strip().lower()
    slug = re.sub(r"[^a-z0-9]+", "-", lowered)
    return re.sub(r"-+", "-", slug).strip("-") or "campaign"


def to_abs(repo_root: Path, value: str) -> Path:
    path = Path(value)
    if path.is_absolute():
        return path
    return (repo_root / path).resolve()


def to_display_path(repo_root: Path, path: Path) -> str:
    try:
        return str(path.relative_to(repo_root))
    except ValueError:
        return str(path)


def file_sha256(path: Path) -> str:
    digest = hashlib.sha256()
    digest.update(path.read_bytes())
    return digest.hexdigest()


def print_data(data: Any) -> None:
    print(json.dumps(data, indent=2, sort_keys=False))


def read_json(path: Path, default: Any) -> Any:
    if not path.exists():
        return default
    try:
        return json.loads(path.read_text(encoding="utf-8"))
    except json.JSONDecodeError as exc:
        raise SystemExit(f"Invalid JSON at {path}: {exc}") from exc


def write_json(path: Path, data: Any) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(data, indent=2, sort_keys=False) + "\n", encoding="utf-8")


def append_event(path: Path, event: Dict[str, Any]) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("a", encoding="utf-8") as handle:
        handle.write(json.dumps(event, sort_keys=False) + "\n")


def load_structured_file(path: Path) -> Any:
    text = path.read_text(encoding="utf-8")
    try:
        return json.loads(text)
    except json.JSONDecodeError:
        pass

    ruby_cmd = [
        "ruby",
        "-rjson",
        "-ryaml",
        "-e",
        "data = YAML.safe_load(File.read(ARGV[0]), permitted_classes: [], aliases: false); puts JSON.generate(data)",
        str(path),
    ]
    try:
        proc = subprocess.run(ruby_cmd, text=True, capture_output=True, check=False)
    except FileNotFoundError as exc:
        raise SystemExit(f"Unable to parse YAML at {path}: ruby not found") from exc
    if proc.returncode != 0:
        detail = (proc.stderr or proc.stdout or "").strip()
        raise SystemExit(f"Unable to parse YAML at {path}: {detail}")
    try:
        return json.loads(proc.stdout)
    except json.JSONDecodeError as exc:
        raise SystemExit(f"Ruby YAML bridge returned invalid JSON for {path}: {exc}") from exc


def run_agent_prompt(prompt: str, cwd: Path, files: Optional[List[Path]] = None) -> subprocess.CompletedProcess[str]:
    runner_bin = os.environ.get("EPMODEL_AGENT_BIN", "opencode")
    model = os.environ.get("EPMODEL_AGENT_MODEL", "")
    cmd = [runner_bin, "run"]
    if model:
        cmd += ["--model", model]
    for path in files or []:
        cmd += ["--file", str(path)]
    cmd.append("--")
    cmd.append(prompt)
    try:
        return subprocess.run(cmd, cwd=str(cwd), text=True, capture_output=True, check=False)
    except FileNotFoundError:
        return subprocess.CompletedProcess(args=cmd, returncode=127, stdout="", stderr=f"runner binary not found: {runner_bin}")


def parse_agent_json_result(output: str) -> Dict[str, Any]:
    pattern = re.compile(
        rf"{re.escape(RESOLUTION_RESULT_BEGIN)}\s*(\{{.*?\}})\s*{re.escape(RESOLUTION_RESULT_END)}",
        flags=re.DOTALL,
    )
    match = pattern.search(output)
    if not match:
        raise SystemExit("LLM subject resolution did not return a result block")
    try:
        obj = json.loads(match.group(1))
    except json.JSONDecodeError as exc:
        raise SystemExit(f"LLM subject resolution returned invalid JSON: {exc}") from exc
    if not isinstance(obj, dict):
        raise SystemExit("LLM subject resolution result must be a JSON object")
    return obj


def normalize_action(action: str) -> str:
    value = re.sub(r"\s+", " ", action.strip().lower())
    if value in {"describe", "plan", "inspect", "show scope", "show plan"}:
        return "describe"
    if value in {"run", "run it end to end", "run end to end", "execute", "end to end", "end-to-end"}:
        return "run"
    if value in {"resume", "continue", "continue run", "resume run"}:
        return "resume"
    raise SystemExit("Unsupported action. Use one of: describe, run it end to end, resume")


def looks_like_path_selector(selector: str) -> bool:
    return any(token in selector for token in ["/", "\\", "*", "?", "["])


@dataclass
class Manifest:
    repo_root: Path
    manifest_path: Path
    campaign_id: str
    workflow: str
    change: str
    include: List[str]
    exclude: List[str]
    each_work_item: str
    after_all_work_items: str
    context_read: List[Path]
    context_references: List[Path]
    context_notes: str


@dataclass
class TypeRecord:
    type_id: str
    class_name: str
    family: str
    header_path: Path
    cpp_path: Optional[Path]
    impl_header_path: Optional[Path]
    source: str

    def to_json(self, repo_root: Path) -> Dict[str, Any]:
        return {
            "type_id": self.type_id,
            "class_name": self.class_name,
            "family": self.family,
            "header_path": to_display_path(repo_root, self.header_path),
            "cpp_path": to_display_path(repo_root, self.cpp_path) if self.cpp_path else None,
            "impl_header_path": to_display_path(repo_root, self.impl_header_path) if self.impl_header_path else None,
            "source": self.source,
        }


@dataclass
class Subject:
    kind: str
    subject_id: str
    display: str
    detail: Dict[str, Any]

    def to_json(self) -> Dict[str, Any]:
        return {
            "kind": self.kind,
            "subject_id": self.subject_id,
            "display": self.display,
            "detail": self.detail,
        }


@dataclass
class SelectorResult:
    selector: str
    kind: str
    explanation: str
    matched_subjects: List[Subject]

    def to_json(self) -> Dict[str, Any]:
        return {
            "selector": self.selector,
            "kind": self.kind,
            "explanation": self.explanation,
            "matched_count": len(self.matched_subjects),
            "subject_kind_counts": subject_kind_counts(self.matched_subjects),
            "sample_subject_ids": [subject.subject_id for subject in self.matched_subjects[:10]],
        }


@dataclass
class Resolution:
    include: List[SelectorResult]
    exclude: List[SelectorResult]
    include_subjects: List[Subject]
    exclude_subjects: List[Subject]


@dataclass
class WorkItem:
    kind: str
    work_item_id: str
    subject_ids: List[str]

    def to_json(self) -> Dict[str, Any]:
        return {
            "kind": self.kind,
            "work_item_id": self.work_item_id,
            "subject_ids": self.subject_ids,
        }


@dataclass
class WorkPlan:
    kind: str
    items: List[WorkItem]


@dataclass
class Plan:
    strategy: str
    summary: str
    work_item_kind: Optional[str]
    apply_capable: bool
    supported: bool
    reason: str

    def to_json(self) -> Dict[str, Any]:
        return {
            "strategy": self.strategy,
            "summary": self.summary,
            "work_item_kind": self.work_item_kind,
            "apply_capable": self.apply_capable,
            "supported": self.supported,
            "reason": self.reason,
        }


@dataclass
class ExecutionPolicy:
    each_work_item: str
    each_mode: str
    after_all_work_items: str
    after_all_mode: str
    final_repair_pass: bool

    def to_json(self) -> Dict[str, Any]:
        return {
            "each_work_item": {
                "instructions": self.each_work_item,
                "mode": self.each_mode,
            },
            "after_all_work_items": {
                "instructions": self.after_all_work_items,
                "mode": self.after_all_mode,
                "final_repair_pass": self.final_repair_pass,
            },
        }


@dataclass
class CodeBlock:
    name: str
    category: Optional[str]
    property_name: str
    start: int
    end: int
    text: str
    ordinal: int


def subject_kind_counts(subjects: Iterable[Subject]) -> Dict[str, int]:
    counts: Dict[str, int] = {}
    for subject in subjects:
        counts[subject.kind] = counts.get(subject.kind, 0) + 1
    return counts


def interpret_execution_policy(each_work_item: str, after_all_work_items: str) -> ExecutionPolicy:
    each = re.sub(r"\s+", " ", each_work_item.strip().lower())
    after = re.sub(r"\s+", " ", after_all_work_items.strip().lower())

    if not each:
        each_mode = "edit_only"
    elif ("no build" in each or "do not run build" in each or "no test" in each or "do not run test" in each):
        each_mode = "edit_only"
    elif "build" in each or "test" in each or "validate" in each:
        each_mode = "validate_each_work_item"
    else:
        each_mode = "custom"

    if not after:
        after_mode = "none"
        final_repair_pass = False
    elif "repair" in after or "iterate" in after or "until green" in after or "fix failures" in after:
        after_mode = "final_validation_with_repair"
        final_repair_pass = True
    elif "build" in after or "test" in after or "ctest" in after:
        after_mode = "final_validation"
        final_repair_pass = False
    else:
        after_mode = "custom"
        final_repair_pass = False

    return ExecutionPolicy(
        each_work_item=each_work_item.strip(),
        each_mode=each_mode,
        after_all_work_items=after_all_work_items.strip(),
        after_all_mode=after_mode,
        final_repair_pass=final_repair_pass,
    )


def load_manifest(repo_root: Path, manifest_path: Path) -> Manifest:
    data = load_structured_file(manifest_path)
    if not isinstance(data, dict):
        raise SystemExit(f"Manifest must be a map: {manifest_path}")

    errors: List[str] = []
    workflow = str(data.get("workflow", "") or "").strip()
    if workflow != WORKFLOW_ID:
        errors.append(f"workflow must equal {WORKFLOW_ID}")

    change = str(data.get("change", "") or "").strip()
    if not change:
        errors.append("change is required")

    targets = data.get("targets")
    if targets is None:
        targets = {}
    if not isinstance(targets, dict):
        errors.append("targets must be a map when present")
        targets = {}

    include = [str(x).strip() for x in (targets.get("include") or []) if str(x).strip()]
    exclude = [str(x).strip() for x in (targets.get("exclude") or []) if str(x).strip()]
    if targets.get("include") is not None and not isinstance(targets.get("include"), list):
        errors.append("targets.include must be a list when present")
    if targets.get("exclude") is not None and not isinstance(targets.get("exclude"), list):
        errors.append("targets.exclude must be a list when present")

    context = data.get("context")
    if context is None:
        context = {}
    if not isinstance(context, dict):
        errors.append("context must be a map when present")
        context = {}

    execution = data.get("execution")
    if execution is None:
        execution = {}
    if not isinstance(execution, dict):
        errors.append("execution must be a map when present")
        execution = {}

    each_work_item = str(execution.get("each_work_item", "") or "").strip()
    after_all_work_items = str(execution.get("after_all_work_items", "") or "").strip()

    def _validate_path_list(key: str) -> List[Path]:
        raw = context.get(key) or []
        if raw and not isinstance(raw, list):
            errors.append(f"context.{key} must be a list when present")
            return []
        paths: List[Path] = []
        for item in raw:
            value = str(item).strip()
            if not value:
                continue
            path = to_abs(repo_root, value)
            if not path.exists():
                errors.append(f"context.{key} path does not exist: {path}")
            else:
                paths.append(path)
        return paths

    context_read = _validate_path_list("read")
    context_references = _validate_path_list("references")
    context_notes = str(context.get("notes", "") or "").strip()

    if errors:
        raise SystemExit("Manifest validation failed:\n- " + "\n- ".join(errors))

    return Manifest(
        repo_root=repo_root,
        manifest_path=manifest_path,
        campaign_id=slugify(manifest_path.stem),
        workflow=workflow,
        change=change,
        include=include,
        exclude=exclude,
        each_work_item=each_work_item,
        after_all_work_items=after_all_work_items,
        context_read=context_read,
        context_references=context_references,
        context_notes=context_notes,
    )


def discover_epmodel_types(repo_root: Path) -> Dict[str, TypeRecord]:
    base = repo_root / "src/epmodel"
    if not base.exists():
        raise SystemExit(f"epmodel source tree not found: {base}")

    records: Dict[str, TypeRecord] = {}
    for header in sorted(base.rglob("*.hpp")):
        if header.name.endswith("_Impl.hpp"):
            continue
        if "test" in header.parts:
            continue
        class_name = header.stem
        if not header_declares_type(header, class_name):
            continue
        cpp = header.with_suffix(".cpp")
        impl = header.with_name(f"{class_name}_Impl.hpp")
        record = TypeRecord(
            type_id=to_display_path(repo_root, header),
            class_name=class_name,
            family=header.parent.name,
            header_path=header,
            cpp_path=cpp if cpp.exists() else None,
            impl_header_path=impl if impl.exists() else None,
            source="codebase",
        )
        records[record.type_id] = record
    return records


def derive_type_from_public_header(repo_root: Path, header: Path) -> TypeRecord:
    class_name = header.stem
    if not header_declares_type(header, class_name):
        raise SystemExit(f"Header does not appear to declare public type {class_name}: {header}")
    cpp = header.with_suffix(".cpp")
    impl = header.with_name(f"{class_name}_Impl.hpp")
    return TypeRecord(
        type_id=to_display_path(repo_root, header),
        class_name=class_name,
        family=header.parent.name,
        header_path=header,
        cpp_path=cpp if cpp.exists() else None,
        impl_header_path=impl if impl.exists() else None,
        source="path_selector",
    )


def _read_text(path: Optional[Path]) -> str:
    if path is None or not path.exists():
        return ""
    return path.read_text(encoding="utf-8", errors="ignore")


def header_declares_type(path: Path, class_name: str) -> bool:
    text = _read_text(path)
    pattern = re.compile(rf"\b(?:class|struct)\s+(?:[A-Za-z_]\w*\s+)*{re.escape(class_name)}\b")
    return bool(pattern.search(text))


def type_subject(repo_root: Path, record: TypeRecord, source_selector: str) -> Subject:
    return Subject(
        kind="type",
        subject_id=record.type_id,
        display=record.class_name,
        detail={
            **record.to_json(repo_root),
            "source_selector": source_selector,
        },
    )


def file_subject(repo_root: Path, path: Path, source_selector: str) -> Subject:
    rel = to_display_path(repo_root, path)
    return Subject(
        kind="file",
        subject_id=rel,
        display=rel,
        detail={
            "path": rel,
            "source_selector": source_selector,
            "suffix": path.suffix,
        },
    )


def method_subject(
    repo_root: Path,
    record: TypeRecord,
    method_name: str,
    source_selector: str,
    category: Optional[str] = None,
    property_name: str = "",
) -> Subject:
    subject_id = f"{record.type_id}::{method_name}"
    detail = {
        **record.to_json(repo_root),
        "method_name": method_name,
        "source_selector": source_selector,
    }
    if category:
        detail["category"] = category
    if property_name:
        detail["property_name"] = property_name
    return Subject(
        kind="method",
        subject_id=subject_id,
        display=f"{record.class_name}::{method_name}",
        detail=detail,
    )


def parse_declared_parents(path: Path, class_name: str) -> List[str]:
    text = _read_text(path)
    match = re.search(rf"\bclass\s+{re.escape(class_name)}\s*:\s*([^{{]+)\{{", text, flags=re.MULTILINE)
    if not match:
        return []
    parents: List[str] = []
    for part in match.group(1).split(","):
        cleaned = re.sub(r"\b(public|protected|private|virtual)\b", " ", part)
        cleaned = re.sub(r"\s+", " ", cleaned).strip()
        if cleaned:
            parents.append(cleaned.split(" ")[-1].split("::")[-1])
    return parents


def build_inheritance_maps(records: Dict[str, TypeRecord]) -> Tuple[Dict[str, List[str]], Dict[str, List[str]]]:
    parents: Dict[str, List[str]] = {}
    children: Dict[str, List[str]] = {}
    for record in records.values():
        record_parents = parse_declared_parents(record.header_path, record.class_name)
        parents[record.class_name] = record_parents
        for parent in record_parents:
            children.setdefault(parent, []).append(record.class_name)
    return parents, children


def class_derives_from(class_name: str, ancestor: str, parents: Dict[str, List[str]]) -> bool:
    seen: set[str] = set()
    pending = list(parents.get(class_name, []))
    while pending:
        current = pending.pop()
        if current in seen:
            continue
        if current == ancestor:
            return True
        seen.add(current)
        pending.extend(parents.get(current, []))
    return False


def all_ancestors(class_name: str, parents: Dict[str, List[str]]) -> List[str]:
    seen: set[str] = set()
    ordered: List[str] = []
    pending = list(parents.get(class_name, []))
    while pending:
        current = pending.pop(0)
        if current in seen:
            continue
        seen.add(current)
        ordered.append(current)
        pending.extend(parents.get(current, []))
    return ordered


def split_identifier_tokens(value: str) -> List[str]:
    raw = re.sub(r"([a-z0-9])([A-Z])", r"\1 \2", value)
    raw = re.sub(r"[^A-Za-z0-9]+", " ", raw)
    tokens = [token.lower() for token in raw.split() if token]
    return tokens


def selector_terms(selector: str) -> List[str]:
    stopwords = {
        "a",
        "an",
        "all",
        "and",
        "are",
        "as",
        "be",
        "by",
        "do",
        "for",
        "from",
        "in",
        "is",
        "it",
        "of",
        "on",
        "or",
        "that",
        "the",
        "their",
        "these",
        "this",
        "to",
        "types",
        "type",
        "with",
    }
    terms = [token for token in split_identifier_tokens(selector) if len(token) >= 3 and token not in stopwords]
    return list(dict.fromkeys(terms))


def header_is_abstract(path: Path) -> bool:
    return bool(re.search(r"=\s*0\s*;", _read_text(path)))


def is_concrete_type(record: TypeRecord, children: Dict[str, List[str]]) -> bool:
    return record.class_name not in children and not header_is_abstract(record.header_path)


def public_method_names(record: TypeRecord) -> List[str]:
    blocks = collect_class_method_blocks(_read_text(record.header_path), record.class_name)
    return [block.name for block in blocks if block.name]


def relevant_source_snippets(repo_root: Path, record: TypeRecord, terms: List[str], limit: int = 6) -> List[Dict[str, Any]]:
    if not terms:
        return []

    patterns = [re.compile(re.escape(term), flags=re.IGNORECASE) for term in terms]
    snippets: List[Dict[str, Any]] = []
    for label, path in [("header", record.header_path), ("cpp", record.cpp_path), ("impl_header", record.impl_header_path)]:
        if path is None or not path.exists():
            continue
        for line_number, line in enumerate(_read_text(path).splitlines(), start=1):
            text = line.strip()
            if not text:
                continue
            matched_terms = [term for term, pattern in zip(terms, patterns) if pattern.search(line)]
            if not matched_terms:
                continue
            snippets.append(
                {
                    "file": to_display_path(repo_root, path),
                    "section": label,
                    "line": line_number,
                    "matched_terms": matched_terms,
                    "text": text[:240],
                }
            )
            if len(snippets) >= limit:
                return snippets
    return snippets


def candidate_relevance_score(record: TypeRecord, parents: Dict[str, List[str]], selector: str, terms: List[str]) -> int:
    haystack_parts = [record.class_name, record.family, record.type_id]
    haystack_parts.extend(parents.get(record.class_name, []))
    haystack_parts.extend(all_ancestors(record.class_name, parents))
    haystack_parts.extend(public_method_names(record)[:25])
    haystack = " ".join(haystack_parts).lower()

    source_text = (_read_text(record.header_path) + "\n" + _read_text(record.cpp_path) + "\n" + _read_text(record.impl_header_path)).lower()
    score = 0
    for term in terms:
        if term in haystack:
            score += 3
        if term in source_text:
            score += 1

    lowered_selector = selector.lower()
    if "concrete" in lowered_selector and record.cpp_path is not None:
        score += 1
    return score


def candidate_type_catalog(repo_root: Path, records: Dict[str, TypeRecord], parents: Dict[str, List[str]], children: Dict[str, List[str]]) -> List[Dict[str, Any]]:
    catalog: List[Dict[str, Any]] = []
    for record in sorted(records.values(), key=lambda item: item.type_id):
        catalog.append(
            {
                "type_id": record.type_id,
                "class_name": record.class_name,
                "family": record.family,
                "parents": parents.get(record.class_name, []),
                "ancestors": all_ancestors(record.class_name, parents),
                "child_count": len(children.get(record.class_name, [])),
                "is_abstract": header_is_abstract(record.header_path),
                "has_cpp": record.cpp_path is not None,
                "has_impl_header": record.impl_header_path is not None,
                "public_methods": public_method_names(record)[:20],
            }
        )
    return catalog


def candidate_type_detail_catalog(
    repo_root: Path,
    records: Dict[str, TypeRecord],
    parents: Dict[str, List[str]],
    children: Dict[str, List[str]],
    selector: str,
    limit: int = 60,
) -> List[Dict[str, Any]]:
    terms = selector_terms(selector)
    ranked: List[Tuple[int, TypeRecord]] = []
    for record in records.values():
        score = candidate_relevance_score(record, parents, selector, terms)
        if score > 0:
            ranked.append((score, record))

    ranked.sort(key=lambda item: (-item[0], item[1].type_id))
    chosen = ranked[:limit] if ranked else [(0, record) for record in sorted(records.values(), key=lambda item: item.type_id)[:limit]]

    details: List[Dict[str, Any]] = []
    for score, record in chosen:
        details.append(
            {
                "type_id": record.type_id,
                "class_name": record.class_name,
                "family": record.family,
                "parents": parents.get(record.class_name, []),
                "ancestors": all_ancestors(record.class_name, parents),
                "child_count": len(children.get(record.class_name, [])),
                "is_abstract": header_is_abstract(record.header_path),
                "public_methods": public_method_names(record)[:30],
                "relevance_score": score,
                "snippets": relevant_source_snippets(repo_root, record, terms),
            }
        )
    return details


def candidate_file_catalog(repo_root: Path, records: Dict[str, TypeRecord]) -> List[Dict[str, Any]]:
    files: Dict[str, Dict[str, Any]] = {}
    for record in records.values():
        for path in [record.header_path, record.cpp_path, record.impl_header_path]:
            if path is None:
                continue
            rel = to_display_path(repo_root, path)
            files[rel] = {
                "path": rel,
                "suffix": path.suffix,
                "type_id": record.type_id,
                "class_name": record.class_name,
                "family": record.family,
            }
    return [files[key] for key in sorted(files)]


def candidate_method_catalog(repo_root: Path, records: Dict[str, TypeRecord]) -> List[Dict[str, Any]]:
    methods: List[Dict[str, Any]] = []
    for record in sorted(records.values(), key=lambda item: item.type_id):
        blocks = collect_class_method_blocks(_read_text(record.header_path), record.class_name)
        for block in blocks:
            if block.category is None:
                continue
            methods.append(
                {
                    "subject_id": f"{record.type_id}::{block.name}",
                    "type_id": record.type_id,
                    "class_name": record.class_name,
                    "family": record.family,
                    "header_path": to_display_path(repo_root, record.header_path),
                    "method_name": block.name,
                    "category": block.category,
                    "property_name": block.property_name,
                }
            )
    return methods


def resolve_selector_with_llm(
    manifest: Manifest,
    selector: str,
    base_types: Dict[str, TypeRecord],
    parents: Dict[str, List[str]],
    children: Dict[str, List[str]],
) -> SelectorResult:
    repo_root = manifest.repo_root
    type_catalog = candidate_type_catalog(repo_root, base_types, parents, children)
    type_detail_catalog = candidate_type_detail_catalog(repo_root, base_types, parents, children, selector)
    file_catalog = candidate_file_catalog(repo_root, base_types)
    method_catalog = candidate_method_catalog(repo_root, base_types)
    prompt = (
        "Resolve one fuzzy epmodel campaign target selector into a concrete set of subjects.\n"
        "Do not modify files. Do not run builds or tests. Use the attached candidate catalogs and attached context files if needed.\n"
        "Use only identifiers that appear in the attached candidate catalogs.\n"
        f"Return strict JSON between {RESOLUTION_RESULT_BEGIN} and {RESOLUTION_RESULT_END}.\n"
        "JSON schema:\n"
        '{"status":"ok|blocked","explanation":"...","confidence":"high|medium|low","matches":[{"kind":"type|file|method","type_id":"...","path":"...","method_subject_id":"...","why":"..."}],"blocker_reason":"..."}\n'
        "Rules:\n"
        "- status=ok when you can identify the set.\n"
        "- status=blocked when the selector is too ambiguous.\n"
        "- Prefer precision over recall; omit uncertain candidates.\n"
        "- candidate_type_details.jsonl contains top-ranked candidates with richer ancestry, method, and snippet facts.\n"
        "- Use candidate_type_details.jsonl first for semantic selectors, then validate against the full catalogs.\n"
        "- For kind=type, emit type_id.\n"
        "- For kind=file, emit path.\n"
        "- For kind=method, emit method_subject_id from candidate_methods.jsonl.\n"
        f"Selector: {selector}\n"
        f"Campaign change: {manifest.change}\n"
        f"Context notes: {manifest.context_notes or '<none>'}\n"
        "Attached files:\n"
        "- candidate_types.jsonl\n"
        "- candidate_type_details.jsonl\n"
        "- candidate_files.jsonl\n"
        "- candidate_methods.jsonl\n"
        "You may also use any attached context.read files.\n"
    )
    temp_dir = repo_root / STATE_ROOT / ".resolution-tmp"
    temp_dir.mkdir(parents=True, exist_ok=True)
    temp_paths: List[Path] = []
    for filename, catalog in [
        ("candidate_types.jsonl", type_catalog),
        ("candidate_type_details.jsonl", type_detail_catalog),
        ("candidate_files.jsonl", file_catalog),
        ("candidate_methods.jsonl", method_catalog),
    ]:
        temp_path = temp_dir / filename
        temp_path.write_text("".join(json.dumps(item, sort_keys=True) + "\n" for item in catalog), encoding="utf-8")
        temp_paths.append(temp_path)
    try:
        proc = run_agent_prompt(prompt, repo_root, files=temp_paths + manifest.context_read)
    finally:
        for temp_path in temp_paths:
            temp_path.unlink(missing_ok=True)
    combined = (proc.stdout or "") + ("\n" + proc.stderr if proc.stderr else "")
    if proc.returncode != 0:
        tail = " | ".join((proc.stderr or "").strip().splitlines()[-3:])
        detail = f": {tail}" if tail else ""
        raise SystemExit(f"LLM subject resolution failed with exit code {proc.returncode}{detail}")

    result = parse_agent_json_result(combined)
    status = str(result.get("status", ""))
    if status == "blocked":
        raise SystemExit(f"LLM subject resolution blocked: {result.get('blocker_reason', 'unspecified blocker')}")
    if status != "ok":
        raise SystemExit("LLM subject resolution returned invalid status")

    matches = result.get("matches")
    if not isinstance(matches, list):
        raise SystemExit("LLM subject resolution missing matches list")

    subjects: List[Subject] = []
    for match in matches:
        if not isinstance(match, dict):
            continue
        kind = str(match.get("kind", "") or "").strip()
        if kind == "type":
            type_id = str(match.get("type_id", "") or "").strip()
            if not type_id or type_id not in base_types:
                raise SystemExit(f"LLM subject resolution returned unknown type_id: {type_id or '<empty>'}")
            subject = type_subject(repo_root, base_types[type_id], selector)
        elif kind == "file":
            rel = str(match.get("path", "") or "").strip()
            abs_path = to_abs(repo_root, rel)
            if not rel or not abs_path.exists():
                raise SystemExit(f"LLM subject resolution returned unknown file path: {rel or '<empty>'}")
            subject = file_subject(repo_root, abs_path, selector)
        elif kind == "method":
            method_subject_id = str(match.get("method_subject_id", "") or "").strip()
            if not method_subject_id or "::" not in method_subject_id:
                raise SystemExit("LLM subject resolution returned invalid method_subject_id")
            type_id, method_name = method_subject_id.rsplit("::", 1)
            if type_id not in base_types:
                raise SystemExit(f"LLM subject resolution returned unknown method type_id: {type_id}")
            blocks = collect_class_method_blocks(_read_text(base_types[type_id].header_path), base_types[type_id].class_name)
            block = next((item for item in blocks if item.name == method_name), None)
            if block is None:
                raise SystemExit(f"LLM subject resolution returned unknown method subject: {method_subject_id}")
            subject = method_subject(
                repo_root,
                base_types[type_id],
                method_name,
                selector,
                category=block.category,
                property_name=block.property_name,
            )
        else:
            raise SystemExit("LLM subject resolution returned unsupported subject kind")
        why = str(match.get("why", "") or "").strip()
        if why:
            subject.detail["llm_why"] = why
        subject.detail["resolution_source"] = "llm"
        subjects.append(subject)

    return SelectorResult(
        selector=selector,
        kind="llm",
        explanation=str(result.get("explanation", "") or "matched with llm assistance"),
        matched_subjects=unique_subjects(subjects),
    )


def match_natural_selector(
    manifest: Manifest,
    selector: str,
    base_types: Dict[str, TypeRecord],
    parents: Dict[str, List[str]],
    children: Dict[str, List[str]],
) -> SelectorResult:
    repo_root = manifest.repo_root
    lowered = re.sub(r"\s+", " ", selector.strip().lower())
    records = list(base_types.values())

    if lowered in {"all types", "all epmodel types", "all classes"}:
        matched = [type_subject(repo_root, record, selector) for record in sorted(records, key=lambda item: item.type_id)]
        return SelectorResult(selector, "natural", "matched all discovered epmodel types", matched)

    if lowered in {"all concrete types", "all concrete classes", "all concrete epmodel types", "all concrete epmodel classes"}:
        matched = [
            type_subject(repo_root, record, selector)
            for record in sorted(records, key=lambda item: item.type_id)
            if is_concrete_type(record, children)
        ]
        return SelectorResult(selector, "natural", "matched discovered concrete epmodel types", matched)

    derives_match = re.search(r"derive(?:s|d)? from ([A-Za-z_]\w*)", selector, flags=re.IGNORECASE)
    if derives_match:
        ancestor = derives_match.group(1)
        matched_records = [record for record in records if class_derives_from(record.class_name, ancestor, parents)]
        explanation = f"matched types whose inheritance chain includes {ancestor}"
        if "base class" in lowered:
            matched_records = [record for record in matched_records if record.class_name in children]
            explanation = f"matched types deriving from {ancestor} that also act as base classes"
        matched = [type_subject(repo_root, record, selector) for record in sorted(matched_records, key=lambda item: item.type_id)]
        return SelectorResult(selector, "natural", explanation, matched)

    family_match = re.match(r"all ([a-z0-9_]+) subclasses", lowered)
    if family_match:
        family = family_match.group(1)
        matched = [
            type_subject(repo_root, record, selector)
            for record in sorted(records, key=lambda item: item.type_id)
            if record.family.lower() == family.lower()
        ]
        return SelectorResult(selector, "natural", f"matched discovered {family} family types", matched)

    matched = [
        type_subject(repo_root, record, selector)
        for record in sorted(records, key=lambda item: item.type_id)
        if record.class_name.lower() == lowered
    ]
    if matched:
        return SelectorResult(selector, "class_name", "matched class name directly", matched)

    return resolve_selector_with_llm(manifest, selector, base_types, parents, children)


def match_path_selector(selector: str, repo_root: Path) -> SelectorResult:
    pattern = selector if Path(selector).is_absolute() else str(repo_root / selector)
    matches = sorted(Path(path).resolve() for path in globlib.glob(pattern, recursive=True))
    if not matches:
        raise SystemExit(f"Target selector matched no files: {selector}")

    derived: Dict[str, Subject] = {}
    for path in matches:
        if path.is_dir():
            for child in sorted(path.rglob("*")):
                if child.is_file() and (child.suffix == ".cpp" or child.suffix == ".hpp"):
                    subject = file_subject(repo_root, child, selector)
                    derived[subject.subject_id] = subject
            continue

        if path.suffix not in {".hpp", ".cpp"}:
            continue

        subject = file_subject(repo_root, path, selector)
        derived[subject.subject_id] = subject

    matched = [derived[key] for key in sorted(derived)]
    if not matched:
        raise SystemExit(f"Target selector matched files but no usable file subjects: {selector}")
    return SelectorResult(selector, "path", "matched files/globs as file subjects", matched)


def unique_subjects(subjects: Iterable[Subject]) -> List[Subject]:
    unique: Dict[str, Subject] = {}
    for subject in subjects:
        unique[subject.subject_id] = subject
    return [unique[key] for key in sorted(unique)]


def resolve_targets(manifest: Manifest) -> Resolution:
    base_types = discover_epmodel_types(manifest.repo_root)
    parents, children = build_inheritance_maps(base_types)
    include_results: List[SelectorResult] = []
    exclude_results: List[SelectorResult] = []
    include_subjects: List[Subject] = []
    exclude_subjects: List[Subject] = []

    if manifest.include:
        for selector in manifest.include:
            result = (
                match_path_selector(selector, manifest.repo_root)
                if looks_like_path_selector(selector)
                else match_natural_selector(manifest, selector, base_types, parents, children)
            )
            include_results.append(result)
            include_subjects.extend(result.matched_subjects)
    else:
        defaults = [type_subject(manifest.repo_root, record, "<default>") for record in sorted(base_types.values(), key=lambda item: item.type_id)]
        include_results.append(SelectorResult("<default>", "default", "used all discovered epmodel types", defaults))
        include_subjects.extend(defaults)

    for selector in manifest.exclude:
        result = (
            match_path_selector(selector, manifest.repo_root)
            if looks_like_path_selector(selector)
            else match_natural_selector(manifest, selector, base_types, parents, children)
        )
        exclude_results.append(result)
        exclude_subjects.extend(result.matched_subjects)

    return Resolution(
        include=include_results,
        exclude=exclude_results,
        include_subjects=unique_subjects(include_subjects),
        exclude_subjects=unique_subjects(exclude_subjects),
    )


def record_from_file_subject(manifest: Manifest, subject: Subject, base_types: Dict[str, TypeRecord]) -> TypeRecord:
    path = to_abs(manifest.repo_root, str(subject.detail["path"]))
    if path.suffix == ".hpp" and not path.name.endswith("_Impl.hpp"):
        type_id = to_display_path(manifest.repo_root, path)
        return base_types.get(type_id) or derive_type_from_public_header(manifest.repo_root, path)

    class_name = path.stem.replace("_Impl", "")
    for record in base_types.values():
        if record.class_name == class_name:
            return record

    header = path.with_name(f"{class_name}.hpp")
    if header.exists():
        return derive_type_from_public_header(manifest.repo_root, header)
    raise SystemExit(f"Could not normalize file subject to a type work item: {subject.subject_id}")


def record_from_method_subject(subject: Subject, base_types: Dict[str, TypeRecord]) -> TypeRecord:
    type_id = str(subject.detail.get("type_id", "") or "").strip()
    if not type_id or type_id not in base_types:
        raise SystemExit(f"Could not normalize method subject to a type work item: {subject.subject_id}")
    return base_types[type_id]


def normalize_work_items(manifest: Manifest, plan: Plan, resolution: Resolution) -> WorkPlan:
    if plan.work_item_kind != "type":
        raise SystemExit("No work-item normalization implemented for this change")

    base_types = discover_epmodel_types(manifest.repo_root)

    def normalize_subject(subject: Subject) -> TypeRecord:
        if subject.kind == "type":
            type_id = str(subject.detail.get("type_id", subject.subject_id))
            record = base_types.get(type_id)
            if record is not None:
                return record
            header_path = subject.detail.get("header_path")
            if isinstance(header_path, str):
                return derive_type_from_public_header(manifest.repo_root, to_abs(manifest.repo_root, header_path))
            raise SystemExit(f"Cannot reload type subject: {subject.subject_id}")
        if subject.kind == "file":
            return record_from_file_subject(manifest, subject, base_types)
        if subject.kind == "method":
            return record_from_method_subject(subject, base_types)
        raise SystemExit(f"Cannot normalize subject kind '{subject.kind}' into work-item kind '{plan.work_item_kind}'")

    included: Dict[str, WorkItem] = {}
    for subject in resolution.include_subjects:
        record = normalize_subject(subject)
        item = included.get(record.type_id)
        if item is None:
            item = WorkItem(
                kind="type",
                work_item_id=record.type_id,
                subject_ids=[subject.subject_id],
            )
            included[record.type_id] = item
        elif subject.subject_id not in item.subject_ids:
            item.subject_ids.append(subject.subject_id)

    excluded_ids = {normalize_subject(subject).type_id for subject in resolution.exclude_subjects}
    items = [included[key] for key in sorted(included) if key not in excluded_ids]
    return WorkPlan(kind="type", items=items)


def classify_work_item_mapping(subjects: List[Subject], work_plan: WorkPlan) -> str:
    if work_plan.kind != "type":
        return "normalized"
    if not subjects and not work_plan.items:
        return "identity"
    if len(subjects) != len(work_plan.items):
        return "normalized"
    for item in work_plan.items:
        if len(item.subject_ids) != 1:
            return "normalized"
        subject_id = item.subject_ids[0]
        if subject_id != item.work_item_id:
            return "normalized"
    if any(subject.kind != "type" for subject in subjects):
        return "normalized"
    return "identity"


def payload_for_work_item(manifest: Manifest, work_item: Dict[str, Any]) -> Dict[str, Any]:
    kind = str(work_item.get("kind", "") or "")
    work_item_id = str(work_item.get("work_item_id", "") or "")
    if kind != "type":
        raise SystemExit(f"Unsupported run work-item kind: {kind or '<empty>'}")
    base_types = discover_epmodel_types(manifest.repo_root)
    record = base_types.get(work_item_id)
    if record is None:
        raise SystemExit(f"Could not load work item payload for {work_item_id}")
    return record.to_json(manifest.repo_root)


def plan_change(change: str) -> Plan:
    lowered = change.lower()
    if (
        any(token in lowered for token in ["getter", "setter", "default", "reset"])
        and any(token in lowered for token in ["group", "together", "reorder", "order"])
    ):
        return Plan(
            strategy="accessor_grouping_apply",
            summary="Group related getter/setter/default/reset methods in declarations and definitions.",
            work_item_kind="type",
            apply_capable=True,
            supported=True,
            reason="matched accessor-grouping change intent",
        )

    return Plan(
        strategy="unplanned",
        summary="No internal strategy matched the requested change.",
            work_item_kind=None,
            apply_capable=False,
            supported=False,
            reason="change intent did not match a built-in campaign strategy",
        )


def state_root_for(manifest: Manifest) -> Path:
    return manifest.repo_root / STATE_ROOT / manifest.campaign_id


def resolution_path(manifest: Manifest) -> Path:
    return state_root_for(manifest) / "resolution.json"


def canonical_subjects_path(manifest: Manifest) -> Path:
    return state_root_for(manifest) / "subjects.json"


def canonical_work_items_path(manifest: Manifest) -> Path:
    return state_root_for(manifest) / "work-items.json"


def latest_pointer_path(manifest: Manifest) -> Path:
    return state_root_for(manifest) / "latest.json"


def _context_entries(repo_root: Path, paths: Iterable[Path]) -> List[Dict[str, Any]]:
    entries: List[Dict[str, Any]] = []
    for path in paths:
        entries.append(
            {
                "path": to_display_path(repo_root, path),
                "sha256": file_sha256(path),
                "size_bytes": path.stat().st_size,
            }
        )
    return entries


def build_resolution_artifacts(
    manifest: Manifest,
    plan: Plan,
    execution_policy: ExecutionPolicy,
    resolution: Resolution,
    work_plan: Optional[WorkPlan],
) -> Tuple[Dict[str, Any], Dict[str, Any], Dict[str, Any]]:
    if work_plan is None:
        work_item_kind = None
        work_item_count = 0
        work_item_mapping = "unplanned"
    else:
        work_item_kind = work_plan.kind
        work_item_count = len(work_plan.items)
        work_item_mapping = classify_work_item_mapping(resolution.include_subjects, work_plan)

    resolution_record = {
        "status": "current",
        "created_at": utc_now(),
        "updated_at": utc_now(),
        "manifest": {
            "path": to_display_path(manifest.repo_root, manifest.manifest_path),
            "sha256": file_sha256(manifest.manifest_path),
            "workflow": manifest.workflow,
            "change": manifest.change,
        },
        "campaign_id": manifest.campaign_id,
        "plan": plan.to_json(),
        "execution": execution_policy.to_json(),
        "selectors": {
            "include": [item.to_json() for item in resolution.include],
            "exclude": [item.to_json() for item in resolution.exclude],
        },
        "subject_summary": {
            "included_count": len(resolution.include_subjects),
            "included_kind_counts": subject_kind_counts(resolution.include_subjects),
            "excluded_count": len(resolution.exclude_subjects),
            "excluded_kind_counts": subject_kind_counts(resolution.exclude_subjects),
        },
        "work_item_summary": {
            "kind": work_item_kind,
            "count": work_item_count,
            "mapping": work_item_mapping,
        },
        "state": {
            "resolution_json": to_display_path(manifest.repo_root, resolution_path(manifest)),
            "subjects_json": to_display_path(manifest.repo_root, canonical_subjects_path(manifest)),
            "work_items_json": to_display_path(manifest.repo_root, canonical_work_items_path(manifest)),
        },
    }

    subjects = {
        "include": [subject.to_json() for subject in resolution.include_subjects],
        "exclude": [subject.to_json() for subject in resolution.exclude_subjects],
    }

    work_items = {
        "kind": work_item_kind,
        "mapping": work_item_mapping,
        "item_count": work_item_count,
        "source": "subjects.json" if work_item_mapping == "identity" else None,
        "items": (
            []
            if work_plan is None or work_item_mapping == "identity"
            else [item.to_json() for item in work_plan.items]
        ),
    }

    return resolution_record, subjects, work_items


def save_resolution_artifacts(manifest: Manifest, resolution_record: Dict[str, Any], subjects: Dict[str, Any], work_items: Dict[str, Any]) -> None:
    root = state_root_for(manifest)
    root.mkdir(parents=True, exist_ok=True)
    resolution_record["updated_at"] = utc_now()
    write_json(resolution_path(manifest), resolution_record)
    write_json(canonical_subjects_path(manifest), subjects)
    write_json(canonical_work_items_path(manifest), work_items)


def load_persisted_resolution(manifest: Manifest) -> Optional[Tuple[Dict[str, Any], Dict[str, Any], Dict[str, Any]]]:
    resolution_record = read_json(resolution_path(manifest), None)
    subjects = read_json(canonical_subjects_path(manifest), None)
    work_items = read_json(canonical_work_items_path(manifest), None)
    if not isinstance(resolution_record, dict) or not isinstance(subjects, dict) or not isinstance(work_items, dict):
        return None
    return resolution_record, subjects, work_items


def load_current_resolution(manifest: Manifest) -> Tuple[Dict[str, Any], Dict[str, Any], Dict[str, Any]]:
    loaded = load_persisted_resolution(manifest)
    if loaded is None:
        raise SystemExit("No persisted resolution found. Run describe first.")

    resolution_record, subjects, work_items = loaded
    manifest_info = resolution_record.get("manifest") or {}
    current_sha = file_sha256(manifest.manifest_path)
    if str(manifest_info.get("sha256", "")) != current_sha:
        resolution_record["status"] = "stale"
        resolution_record["stale_reason"] = "manifest changed since describe"
        save_resolution_artifacts(manifest, resolution_record, subjects, work_items)
        raise SystemExit("Persisted resolution is stale. Run describe again.")

    if resolution_record.get("status") != "current":
        raise SystemExit("Persisted resolution is not current. Run describe again.")

    return resolution_record, subjects, work_items


def build_run_work_items(resolution_work_items: Dict[str, Any], subjects: Dict[str, Any], execution_policy: ExecutionPolicy) -> Dict[str, Any]:
    mapping = str(resolution_work_items.get("mapping", "normalized") or "normalized")
    if mapping == "identity":
        items = [
            {
                "kind": str(subject.get("kind", "") or ""),
                "work_item_id": str(subject.get("subject_id", "") or ""),
                "subject_ids": [str(subject.get("subject_id", "") or "")],
            }
            for subject in subjects.get("include", [])
            if isinstance(subject, dict)
        ]
    else:
        items = list(resolution_work_items.get("items", []))
    return {
        "kind": resolution_work_items.get("kind"),
        "mapping": mapping,
        "items": [
            {
                **item,
                "status": "pending",
                "changed_files": [],
                "detail": "",
                "session_scope": "work_item",
                "validation": {
                    "instructions": execution_policy.each_work_item,
                    "mode": execution_policy.each_mode,
                    "performed": [],
                    "result": "not_run" if execution_policy.each_mode == "edit_only" else "pending",
                },
                "updated_at": None,
            }
            for item in items
        ],
    }


def create_run(
    manifest: Manifest,
    plan: Plan,
    execution_policy: ExecutionPolicy,
    resolution_record: Dict[str, Any],
    subjects: Dict[str, Any],
    resolution_work_items: Dict[str, Any],
) -> Tuple[Path, Dict[str, Any], Dict[str, Any], Dict[str, Any]]:
    run_id = utc_stamp()
    run_dir = state_root_for(manifest) / "runs" / run_id
    run_dir.mkdir(parents=True, exist_ok=True)

    work_items = build_run_work_items(resolution_work_items, subjects, execution_policy)

    run = {
        "run_id": run_id,
        "status": "planned",
        "created_at": utc_now(),
        "updated_at": utc_now(),
        "manifest": {
            "path": to_display_path(manifest.repo_root, manifest.manifest_path),
            "sha256": file_sha256(manifest.manifest_path),
            "workflow": manifest.workflow,
            "change": manifest.change,
        },
        "campaign_id": manifest.campaign_id,
        "plan": plan.to_json(),
        "resolution": {
            "path": to_display_path(manifest.repo_root, resolution_path(manifest)),
            "status": resolution_record.get("status"),
            "manifest_sha256": resolution_record.get("manifest", {}).get("sha256"),
        },
        "execution": {
            "session_model": "per_work_item",
            "work_item_kind": resolution_work_items.get("kind"),
            "policy": execution_policy.to_json(),
            "phases": {
                "work_items": "pending",
                "after_all_work_items": "pending" if execution_policy.after_all_mode != "none" else "not_requested",
            },
        },
        "context": {
            "read": _context_entries(manifest.repo_root, manifest.context_read),
            "references": _context_entries(manifest.repo_root, manifest.context_references),
            "notes": manifest.context_notes,
        },
        "selectors": resolution_record.get("selectors", {}),
        "subject_summary": {
            "included": resolution_record.get("subject_summary", {}).get("included_kind_counts", {}),
            "excluded": resolution_record.get("subject_summary", {}).get("excluded_kind_counts", {}),
        },
        "work_item_summary": {
            "total": len(work_items.get("items", [])),
            "pending": len(work_items.get("items", [])),
            "queued": 0,
            "in_progress": 0,
            "done": 0,
            "skipped": 0,
            "failed": 0,
        },
    }

    write_json(run_dir / "run.json", run)
    write_json(run_dir / "subjects.json", subjects)
    write_json(run_dir / "work-items.json", work_items)
    append_event(run_dir / "events.jsonl", {"time": utc_now(), "event": "run_created", "run_id": run_id})
    write_json(
        latest_pointer_path(manifest),
        {
            "run_id": run_id,
            "path": to_display_path(manifest.repo_root, run_dir),
            "updated_at": utc_now(),
        },
    )
    return run_dir, run, subjects, work_items


def load_latest_resumable_run(manifest: Manifest) -> Optional[Tuple[Path, Dict[str, Any], Dict[str, Any], Dict[str, Any]]]:
    pointer = read_json(latest_pointer_path(manifest), None)
    if not isinstance(pointer, dict):
        return None
    run_path = pointer.get("path")
    if not isinstance(run_path, str) or not run_path:
        return None
    run_dir = to_abs(manifest.repo_root, run_path)
    run = read_json(run_dir / "run.json", None)
    subjects = read_json(run_dir / "subjects.json", None)
    work_items = read_json(run_dir / "work-items.json", None)
    if not isinstance(run, dict) or not isinstance(subjects, dict) or not isinstance(work_items, dict):
        return None
    if run.get("status") in {"completed", "failed", "cancelled"}:
        return None
    manifest_info = run.get("manifest") or {}
    if str(manifest_info.get("sha256", "")) != file_sha256(manifest.manifest_path):
        return None
    return run_dir, run, subjects, work_items


def save_run_state(run_dir: Path, run: Dict[str, Any], subjects: Dict[str, Any], work_items: Dict[str, Any]) -> None:
    run["updated_at"] = utc_now()
    write_json(run_dir / "run.json", run)
    write_json(run_dir / "subjects.json", subjects)
    write_json(run_dir / "work-items.json", work_items)


def refresh_work_item_summary(run: Dict[str, Any], work_items: Dict[str, Any]) -> None:
    summary = {"total": 0, "pending": 0, "queued": 0, "in_progress": 0, "done": 0, "skipped": 0, "failed": 0}
    for item in work_items.get("items", []):
        status = str(item.get("status", "pending"))
        summary["total"] += 1
        if status in summary:
            summary[status] += 1
    run["work_item_summary"] = summary


def _lower_first(value: str) -> str:
    return value[:1].lower() + value[1:] if value else value


def classify_method(name: str) -> Tuple[Optional[str], str]:
    if name.startswith("set") and len(name) > 3:
        return "setter", _lower_first(name[3:])
    if name.startswith("reset") and len(name) > 5:
        return "reset", _lower_first(name[5:])
    if name.startswith("is") and name.endswith("Defaulted") and len(name) > len("isDefaulted"):
        return "default", _lower_first(name[2:-9])
    if name.startswith("is") and name.endswith("Autosized") and len(name) > len("isAutosized"):
        return "default", _lower_first(name[2:-9])
    if name.startswith("is") and name.endswith("Autocalculated") and len(name) > len("isAutocalculated"):
        return "default", _lower_first(name[2:-14])
    if name.startswith("autosize") and len(name) > 8:
        return "default", _lower_first(name[8:])
    if name.startswith("autocalculate") and len(name) > 13:
        return "default", _lower_first(name[13:])
    if name.startswith("set") or name.startswith("reset"):
        return None, ""
    return "getter", _lower_first(name)


def line_offsets(text: str) -> List[int]:
    offsets: List[int] = []
    running = 0
    for line in text.splitlines(keepends=True):
        offsets.append(running)
        running += len(line)
    return offsets or [0]


def extract_method_name(signature: str) -> Optional[str]:
    match = re.search(r"([~A-Za-z_]\w*)\s*\(", signature)
    return match.group(1) if match else None


def collect_class_method_blocks(text: str, class_name: str) -> List[CodeBlock]:
    lines = text.splitlines(keepends=True)
    offsets = line_offsets(text)
    class_decl = re.compile(rf"\bclass\s+(?:[A-Za-z_]\w*\s+)*{re.escape(class_name)}\b")

    in_class = False
    brace_depth = 0
    access = "private"
    buffer: List[str] = []
    start_line: Optional[int] = None
    entries: List[CodeBlock] = []

    for idx, line in enumerate(lines):
        stripped = line.strip()
        if not in_class:
            if class_decl.search(line):
                in_class = True
                brace_depth += line.count("{") - line.count("}")
            continue

        brace_depth += line.count("{") - line.count("}")
        if stripped in {"public:", "private:", "protected:"}:
            access = stripped[:-1]
            if brace_depth <= 0:
                break
            continue

        if access != "public":
            if brace_depth <= 0:
                break
            continue

        if start_line is None:
            if not stripped or stripped.startswith("//") or stripped.startswith("/*") or stripped.startswith("*"):
                if brace_depth <= 0:
                    break
                continue
            if "(" not in stripped:
                if brace_depth <= 0:
                    break
                continue
            start_line = idx

        buffer.append(line)
        if ";" in stripped:
            signature = " ".join(part.strip() for part in buffer)
            method_name = extract_method_name(signature)
            if method_name:
                category, prop = classify_method(method_name)
                if method_name in {class_name, f"~{class_name}"}:
                    category, prop = None, ""
                entries.append(
                    CodeBlock(
                        name=method_name,
                        category=category,
                        property_name=prop,
                        start=offsets[start_line],
                        end=offsets[idx] + len(lines[idx]),
                        text="".join(buffer).rstrip(),
                        ordinal=len(entries),
                    )
                )
            buffer = []
            start_line = None

        if brace_depth <= 0:
            break

    return entries


def collect_cpp_method_blocks(text: str, qualified_class_name: str, constructor_name: str) -> List[CodeBlock]:
    lines = text.splitlines(keepends=True)
    offsets = line_offsets(text)
    entries: List[CodeBlock] = []
    marker = f"{qualified_class_name}::"
    signature_re = re.compile(rf"\b{re.escape(qualified_class_name)}::([~A-Za-z_]\w*)\s*\(")
    i = 0
    while i < len(lines):
        line = lines[i]
        if marker not in line:
            i += 1
            continue

        start_line = i
        block_lines = [line]
        brace_depth = line.count("{") - line.count("}")
        found_open = "{" in line
        j = i
        while not found_open and j + 1 < len(lines):
            j += 1
            block_lines.append(lines[j])
            brace_depth += lines[j].count("{") - lines[j].count("}")
            if "{" in lines[j]:
                found_open = True
        if not found_open:
            i += 1
            continue
        while brace_depth > 0 and j + 1 < len(lines):
            j += 1
            block_lines.append(lines[j])
            brace_depth += lines[j].count("{") - lines[j].count("}")

        signature = " ".join(part.strip() for part in block_lines)
        match = signature_re.search(signature)
        if match:
            method_name = match.group(1)
            category, prop = classify_method(method_name)
            if method_name in {constructor_name, f"~{constructor_name}"}:
                category, prop = None, ""
            entries.append(
                CodeBlock(
                    name=method_name,
                    category=category,
                    property_name=prop,
                    start=offsets[start_line],
                    end=offsets[j] + len(lines[j]),
                    text="".join(block_lines).rstrip(),
                    ordinal=len(entries),
                )
            )
        i = j + 1
    return entries


def apply_grouping_blocks(text: str, blocks: List[CodeBlock]) -> Tuple[str, bool, str]:
    accessors = [block for block in blocks if block.category is not None and block.property_name]
    if not accessors:
        return text, False, ""

    region_start = accessors[0].start
    region_end = accessors[-1].end
    if any(block.category is None and region_start <= block.start and block.end <= region_end for block in blocks):
        return text, False, "non-accessor methods interleaved within accessor region"

    previous_end = region_start
    for block in accessors:
        if text[previous_end:block.start].strip():
            return text, False, "comments or non-whitespace separators found inside accessor region"
        previous_end = block.end

    grouped: Dict[str, List[CodeBlock]] = {}
    property_order: List[str] = []
    for block in accessors:
        prop = block.property_name
        if prop not in grouped:
            grouped[prop] = []
            property_order.append(prop)
        grouped[prop].append(block)

    category_order = {"getter": 0, "setter": 1, "default": 2, "reset": 3}
    desired: List[CodeBlock] = []
    for prop in property_order:
        desired.extend(sorted(grouped[prop], key=lambda item: (category_order.get(str(item.category), 99), item.ordinal)))

    if [block.name for block in accessors] == [block.name for block in desired]:
        return text, False, ""

    replacement = "\n\n".join(block.text for block in desired)
    if text[region_start:region_end].endswith("\n"):
        replacement += "\n"
    return text[:region_start] + replacement + text[region_end:], True, ""


def apply_accessor_grouping(record: TypeRecord) -> Tuple[str, List[str], str]:
    changed_files: List[str] = []
    skipped_reasons: List[str] = []

    file_specs = [
        (record.header_path, lambda text: collect_class_method_blocks(text, record.class_name)),
    ]
    if record.impl_header_path and record.impl_header_path.exists():
        file_specs.append((record.impl_header_path, lambda text: collect_class_method_blocks(text, f"{record.class_name}_Impl")))
    if record.cpp_path and record.cpp_path.exists():
        file_specs.append((record.cpp_path, lambda text: collect_cpp_method_blocks(text, record.class_name, record.class_name)))
        file_specs.append((record.cpp_path, lambda text: collect_cpp_method_blocks(text, f"{record.class_name}_Impl", f"{record.class_name}_Impl")))

    text_cache: Dict[Path, str] = {}
    for path, collector in file_specs:
        current = text_cache.get(path)
        if current is None:
            current = path.read_text(encoding="utf-8", errors="ignore")
        updated, changed, reason = apply_grouping_blocks(current, collector(current))
        if changed:
            text_cache[path] = updated
            display = str(path)
            if display not in changed_files:
                changed_files.append(display)
        else:
            text_cache[path] = current
            if reason:
                skipped_reasons.append(f"{path}: {reason}")

    for path in {Path(item) for item in changed_files}:
        path.write_text(text_cache[path], encoding="utf-8")

    if changed_files:
        return "done", changed_files, f"updated {len(changed_files)} file(s)"
    if skipped_reasons:
        return "skipped", [], "; ".join(skipped_reasons)
    return "done", [], "no accessor regrouping needed"


def run_accessor_grouping(record: TypeRecord, repo_root: Path) -> Tuple[str, List[str], str]:
    status, changed_files, detail = apply_accessor_grouping(record)
    changed_display = [to_display_path(repo_root, Path(path)) for path in changed_files]
    return status, changed_display, detail


def describe(manifest: Manifest, plan: Plan, execution_policy: ExecutionPolicy, resolution: Resolution, work_plan: Optional[WorkPlan]) -> int:
    resolution_record, subjects, work_items = build_resolution_artifacts(manifest, plan, execution_policy, resolution, work_plan)
    save_resolution_artifacts(manifest, resolution_record, subjects, work_items)
    out = {
        "workflow": manifest.workflow,
        "manifest": to_display_path(manifest.repo_root, manifest.manifest_path),
        "campaign_id": manifest.campaign_id,
        "change": manifest.change,
        "plan": resolution_record["plan"],
        "execution": resolution_record["execution"],
        "state_root": to_display_path(manifest.repo_root, state_root_for(manifest)),
        "resolution": resolution_record,
        "context": {
            "read": [to_display_path(manifest.repo_root, path) for path in manifest.context_read],
            "references": [to_display_path(manifest.repo_root, path) for path in manifest.context_references],
            "notes": manifest.context_notes,
        },
        "selectors": resolution_record["selectors"],
        "subjects": {
            **resolution_record["subject_summary"],
            "sample_included": subjects["include"][:10],
            "sample_excluded": subjects["exclude"][:10],
        },
        "work_items": {
            "kind": work_items["kind"],
            "count": len(work_items["items"]),
            "sample": work_items["items"][:10],
        },
    }
    print_data(out)
    return 0


def execute(
    manifest: Manifest,
    plan: Plan,
    execution_policy: ExecutionPolicy,
    resolution_record: Dict[str, Any],
    subjects: Dict[str, Any],
    resolution_work_items: Dict[str, Any],
    action: str,
) -> int:
    if not plan.supported or not plan.apply_capable:
        raise SystemExit(f"This change is not runnable yet: {plan.reason}")

    loaded = load_latest_resumable_run(manifest) if action == "resume" else None
    if loaded is None:
        run_dir, run, subjects, work_items = create_run(
            manifest,
            plan,
            execution_policy,
            resolution_record,
            subjects,
            resolution_work_items,
        )
    else:
        run_dir, run, subjects, work_items = loaded

    run["status"] = "resolved"
    run["execution"]["phases"]["work_items"] = "pending"
    save_run_state(run_dir, run, subjects, work_items)
    append_event(run_dir / "events.jsonl", {"time": utc_now(), "event": "resolved", "subject_count": len(subjects.get("include", [])), "work_item_count": len(work_items.get("items", []))})

    try:
        run["status"] = "running"
        run["execution"]["phases"]["work_items"] = "running"
        save_run_state(run_dir, run, subjects, work_items)
        for item in work_items.get("items", []):
            if item.get("status") in {"done", "skipped"}:
                continue
            item["status"] = "queued"
            item["updated_at"] = utc_now()
            refresh_work_item_summary(run, work_items)
            save_run_state(run_dir, run, subjects, work_items)

            item["status"] = "in_progress"
            item["updated_at"] = utc_now()
            refresh_work_item_summary(run, work_items)
            save_run_state(run_dir, run, subjects, work_items)
            append_event(run_dir / "events.jsonl", {"time": utc_now(), "event": "work_item_started", "work_item_id": item["work_item_id"], "kind": item["kind"]})

            payload = payload_for_work_item(manifest, item)
            record = TypeRecord(
                type_id=payload["type_id"],
                class_name=payload["class_name"],
                family=payload["family"],
                header_path=to_abs(manifest.repo_root, payload["header_path"]),
                cpp_path=to_abs(manifest.repo_root, payload["cpp_path"]) if payload.get("cpp_path") else None,
                impl_header_path=(
                    to_abs(manifest.repo_root, payload["impl_header_path"])
                    if payload.get("impl_header_path")
                    else None
                ),
                source=str(payload.get("source", "state")),
            )

            try:
                status, changed_files, detail = run_accessor_grouping(record, manifest.repo_root)
            except Exception as exc:  # pragma: no cover - per-target guardrail
                status, changed_files, detail = "failed", [], str(exc)
            item["status"] = status
            item["changed_files"] = changed_files
            item["detail"] = detail
            if execution_policy.each_mode == "edit_only":
                item["validation"]["result"] = "not_run"
            elif execution_policy.each_mode == "validate_each_work_item":
                item["validation"]["result"] = "deferred"
            else:
                item["validation"]["result"] = "custom"
            item["updated_at"] = utc_now()
            append_event(
                run_dir / "events.jsonl",
                {
                    "time": utc_now(),
                    "event": "work_item_finished",
                    "work_item_id": item["work_item_id"],
                    "status": status,
                    "changed_files": changed_files,
                    "detail": detail,
                },
            )
            refresh_work_item_summary(run, work_items)
            save_run_state(run_dir, run, subjects, work_items)
    except KeyboardInterrupt:
        run["status"] = "paused"
        run["execution"]["phases"]["work_items"] = "paused"
        save_run_state(run_dir, run, subjects, work_items)
        append_event(run_dir / "events.jsonl", {"time": utc_now(), "event": "paused"})
        raise SystemExit("Run paused. Resume with the same manifest.")
    except Exception as exc:  # pragma: no cover - defensive run-state guard
        run["status"] = "failed"
        run["execution"]["phases"]["work_items"] = "failed"
        save_run_state(run_dir, run, subjects, work_items)
        append_event(run_dir / "events.jsonl", {"time": utc_now(), "event": "failed", "error": str(exc)})
        raise

    run["execution"]["phases"]["work_items"] = "completed"
    refresh_work_item_summary(run, work_items)

    if execution_policy.after_all_mode == "none":
        run["execution"]["phases"]["after_all_work_items"] = "not_requested"
        run["status"] = "completed"
        append_event(run_dir / "events.jsonl", {"time": utc_now(), "event": "after_all_work_items_not_requested"})
    else:
        run["execution"]["phases"]["after_all_work_items"] = "deferred"
        run["status"] = "paused"
        run["pause_reason"] = "after_all_work_items phase requested but not executed by backend"
        append_event(
            run_dir / "events.jsonl",
            {
                "time": utc_now(),
                "event": "after_all_work_items_deferred",
                "mode": execution_policy.after_all_mode,
                "instructions": execution_policy.after_all_work_items,
                "final_repair_pass": execution_policy.final_repair_pass,
            },
        )

    save_run_state(run_dir, run, subjects, work_items)
    append_event(run_dir / "events.jsonl", {"time": utc_now(), "event": run["status"], "summary": run["work_item_summary"]})
    write_json(
        latest_pointer_path(manifest),
        {"run_id": run["run_id"], "path": to_display_path(manifest.repo_root, run_dir), "updated_at": utc_now()},
    )

    out = {
        "campaign_id": manifest.campaign_id,
        "run_id": run["run_id"],
        "status": run["status"],
        "plan": run["plan"],
        "execution": run["execution"],
        "state": {
            "root": to_display_path(manifest.repo_root, state_root_for(manifest)),
            "resolution_json": to_display_path(manifest.repo_root, resolution_path(manifest)),
            "run": to_display_path(manifest.repo_root, run_dir),
            "run_json": to_display_path(manifest.repo_root, run_dir / "run.json"),
            "subjects_json": to_display_path(manifest.repo_root, run_dir / "subjects.json"),
            "work_items_json": to_display_path(manifest.repo_root, run_dir / "work-items.json"),
            "events_jsonl": to_display_path(manifest.repo_root, run_dir / "events.jsonl"),
        },
        "subject_summary": run["subject_summary"],
        "work_item_summary": run["work_item_summary"],
        "changed_work_items": [item["work_item_id"] for item in work_items["items"] if item.get("changed_files")],
    }
    print_data(out)
    return 0


def cmd_use(repo_root: Path, manifest_arg: str, action_arg: str) -> int:
    manifest_path = to_abs(repo_root, manifest_arg)
    if not manifest_path.exists():
        raise SystemExit(f"Manifest not found: {manifest_path}")
    manifest = load_manifest(repo_root, manifest_path)
    plan = plan_change(manifest.change)
    execution_policy = interpret_execution_policy(manifest.each_work_item, manifest.after_all_work_items)
    action = normalize_action(action_arg)
    if action == "describe":
        resolution = resolve_targets(manifest)
        work_plan = normalize_work_items(manifest, plan, resolution) if plan.work_item_kind else None
        return describe(manifest, plan, execution_policy, resolution, work_plan)
    if action == "resume":
        loaded = load_latest_resumable_run(manifest)
        if loaded is None:
            raise SystemExit("No resumable run found. Run describe, then run it end to end.")
        resolution_record, subjects, resolution_work_items = load_current_resolution(manifest)
        return execute(manifest, plan, execution_policy, resolution_record, subjects, resolution_work_items, action)

    resolution_record, subjects, resolution_work_items = load_current_resolution(manifest)
    if plan.work_item_kind is None:
        raise SystemExit(f"This change is not runnable yet: {plan.reason}")
    resolved_plan = resolution_record.get("plan", {})
    if resolved_plan.get("strategy") != plan.strategy or resolved_plan.get("work_item_kind") != plan.work_item_kind:
        raise SystemExit("Persisted resolution does not match the current planner state. Run describe again.")
    return execute(manifest, plan, execution_policy, resolution_record, subjects, resolution_work_items, action)


def build_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(description="epmodel campaign workflow backend")
    parser.add_argument("--repo-root", default=".", help="repository root")
    sub = parser.add_subparsers(dest="cmd", required=True)

    use_p = sub.add_parser("use", help="use a manifest with an action")
    use_p.add_argument("--manifest", required=True, help="manifest path")
    use_p.add_argument("--action", required=True, help="describe, run it end to end, or resume")
    use_p.set_defaults(func=lambda args, root: cmd_use(root, args.manifest, args.action))

    validate_p = sub.add_parser("validate-manifest", help="validate manifest only")
    validate_p.add_argument("--manifest", required=True, help="manifest path")
    validate_p.set_defaults(
        func=lambda args, root: (
            load_manifest(root, to_abs(root, args.manifest)),
            print("Manifest is valid."),
            0,
        )[2]
    )
    return parser


def main(argv: Optional[Sequence[str]] = None) -> int:
    parser = build_parser()
    args = parser.parse_args(argv)
    repo_root = Path(args.repo_root).resolve()
    return int(args.func(args, repo_root))


if __name__ == "__main__":
    sys.exit(main())
