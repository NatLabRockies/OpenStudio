#!/usr/bin/env python3
"""Manifest-driven backend for resumable subject campaigns."""

from __future__ import annotations

import argparse
import concurrent.futures
import datetime as dt
import glob as globlib
import hashlib
import json
import os
import re
import socket
import subprocess
import sys
import time
from dataclasses import dataclass
from pathlib import Path
from typing import Any, Dict, Iterable, List, Optional, Sequence, Set, Tuple


WORKFLOW_ID = "epmodel_campaign"
STATE_ROOT = ".opencode/epmodel-campaigns"
RESOLUTION_RESULT_BEGIN = "EPMODEL_RESOLUTION_RESULT_BEGIN"
RESOLUTION_RESULT_END = "EPMODEL_RESOLUTION_RESULT_END"
EXEC_RESULT_BEGIN = "EPMODEL_EXEC_RESULT_BEGIN"
EXEC_RESULT_END = "EPMODEL_EXEC_RESULT_END"
DEFAULT_STATUS_WATCH_SECONDS = 2.0
DEFAULT_SUBJECT_PARALLELISM = 4
PID_POLL_SIGNAL = 0
CONTROLLER_SNAPSHOT_INTERVAL_SECONDS = 60.0


def utc_now() -> str:
    return dt.datetime.now(dt.timezone.utc).replace(microsecond=0).isoformat().replace("+00:00", "Z")


def utc_stamp() -> str:
    return dt.datetime.now(dt.timezone.utc).strftime("%Y%m%dT%H%M%SZ")


def parse_utc(value: Any) -> Optional[dt.datetime]:
    if not isinstance(value, str) or not value.strip():
        return None
    text = value.strip()
    if text.endswith("Z"):
        text = text[:-1] + "+00:00"
    try:
        return dt.datetime.fromisoformat(text)
    except ValueError:
        return None


def format_duration(seconds: float) -> str:
    total = max(0, int(round(seconds)))
    hours, rem = divmod(total, 3600)
    minutes, secs = divmod(rem, 60)
    if hours:
        return f"{hours}h {minutes}m"
    if minutes:
        return f"{minutes}m {secs}s"
    return f"{secs}s"


def elapsed_human(start: Any, end: Optional[Any] = None) -> str:
    start_dt = parse_utc(start)
    if start_dt is None:
        return ""
    end_dt = parse_utc(end) if end is not None else dt.datetime.now(dt.timezone.utc)
    if end_dt is None:
        end_dt = dt.datetime.now(dt.timezone.utc)
    return format_duration(max(0.0, (end_dt - start_dt).total_seconds()))


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


@dataclass
class AgentConfig:
    model: str = ""
    variant: str = ""
    parallelism: int = 1

    def resolved(self, *, fallback_model: str = "", fallback_variant: str = "", fallback_parallelism: Optional[int] = None) -> "AgentConfig":
        parallelism = self.parallelism if self.parallelism > 0 else (fallback_parallelism or 1)
        return AgentConfig(
            model=self.model or fallback_model,
            variant=self.variant or fallback_variant,
            parallelism=max(1, parallelism),
        )

    def to_json(self) -> Dict[str, Any]:
        return {
            "model": self.model or None,
            "variant": self.variant or None,
            "parallelism": self.parallelism,
        }


@dataclass
class ExecutionPolicy:
    each_work_item: str
    after_all_work_items: str
    backend: str
    work_item_grouping: str
    resolution_agent: AgentConfig
    subject_agent: AgentConfig
    after_all_agent: AgentConfig

    @property
    def has_after_all(self) -> bool:
        return bool(self.after_all_work_items.strip())

    def to_json(self) -> Dict[str, Any]:
        return {
            "backend": self.backend,
            "work_item_grouping": self.work_item_grouping,
            "each_work_item": {
                "instructions": self.each_work_item,
                "mode": "agent_per_subject",
            },
            "after_all_work_items": {
                "instructions": self.after_all_work_items,
                "mode": "agent_once" if self.has_after_all else "none",
            },
            "resolution_agent": self.resolution_agent.to_json(),
            "subject_agent": self.subject_agent.to_json(),
            "after_all_agent": self.after_all_agent.to_json(),
        }


@dataclass
class Manifest:
    repo_root: Path
    manifest_path: Path
    campaign_id: str
    workflow: str
    change: str
    include: List[str]
    exclude: List[str]
    context_read: List[Path]
    context_references: List[Path]
    context_notes: str
    execution: ExecutionPolicy

    @property
    def each_work_item(self) -> str:
        return self.execution.each_work_item

    @property
    def after_all_work_items(self) -> str:
        return self.execution.after_all_work_items


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
    selected_subjects: List[Subject]


@dataclass
class StartedServer:
    url: str
    pid: int
    log_path: Path


def normalize_action(action: str) -> str:
    value = re.sub(r"\s+", " ", action.strip().lower())
    if value in {"describe", "plan", "inspect", "show scope", "show plan"}:
        return "describe"
    if value in {"run", "run it end to end", "run end to end", "execute", "end to end", "end-to-end"}:
        return "run"
    if value in {"resume", "continue", "continue run", "resume run"}:
        return "resume"
    if value in {"status", "show status", "progress"}:
        return "status"
    raise SystemExit("Unsupported action. Use one of: describe, run, resume, status")


def looks_like_path_selector(selector: str) -> bool:
    return any(token in selector for token in ["/", "\\", "*", "?", "["])


def tail_text(text: str, line_count: int = 12) -> str:
    lines = [line for line in text.strip().splitlines() if line.strip()]
    return "\n".join(lines[-line_count:])


def subject_kind_counts(subjects: Iterable[Subject]) -> Dict[str, int]:
    counts: Dict[str, int] = {}
    for subject in subjects:
        counts[subject.kind] = counts.get(subject.kind, 0) + 1
    return counts


def list_repo_files(repo_root: Path) -> List[Path]:
    git_cmd = ["git", "ls-files", "--cached", "--others", "--exclude-standard"]
    try:
        proc = subprocess.run(git_cmd, cwd=str(repo_root), text=True, capture_output=True, check=False)
    except FileNotFoundError:
        proc = None

    if proc and proc.returncode == 0:
        files = []
        for raw in proc.stdout.splitlines():
            value = raw.strip()
            if not value:
                continue
            path = (repo_root / value).resolve()
            if path.is_file():
                files.append(path)
        return sorted(set(files))

    ignored_parts = {".git", ".opencode", "build", "dist", "node_modules", "__pycache__"}
    files: List[Path] = []
    for path in repo_root.rglob("*"):
        if any(part in ignored_parts for part in path.parts):
            continue
        if path.is_file():
            files.append(path.resolve())
    return sorted(set(files))


def file_catalog_entry(repo_root: Path, path: Path) -> Dict[str, Any]:
    return {
        "path": to_display_path(repo_root, path),
        "basename": path.name,
        "suffix": path.suffix,
        "parent": to_display_path(repo_root, path.parent),
        "size_bytes": path.stat().st_size,
    }


def selector_terms(selector: str) -> List[str]:
    stop = {
        "all",
        "and",
        "any",
        "campaign",
        "class",
        "classes",
        "concrete",
        "file",
        "files",
        "from",
        "kind",
        "kinds",
        "subject",
        "subjects",
        "target",
        "targets",
        "type",
        "types",
    }
    terms = []
    for token in re.findall(r"[A-Za-z0-9_]+", selector.lower()):
        if len(token) < 3 or token in stop:
            continue
        terms.append(token)
    return sorted(set(terms))


def default_agent_model() -> str:
    return os.environ.get("EPMODEL_AGENT_MODEL", "").strip()


def default_agent_variant() -> str:
    return os.environ.get("EPMODEL_AGENT_VARIANT", "").strip()


def infer_resolution_agent(change: str) -> AgentConfig:
    return AgentConfig(model="openai/gpt-5.4", variant="high", parallelism=1)


def infer_subject_agent(change: str) -> AgentConfig:
    lowered = change.lower()
    formatting_tokens = ["group", "order", "reorder", "format", "organize", "comment"]
    structure_tokens = ["getter", "setter", "default", "reset", "accessor"]
    if any(token in lowered for token in formatting_tokens) and any(token in lowered for token in structure_tokens):
        return AgentConfig(model="openai/gpt-5.1-codex-mini", variant="minimal", parallelism=DEFAULT_SUBJECT_PARALLELISM)
    return AgentConfig(model="openai/gpt-5.1-codex-mini", variant="medium", parallelism=DEFAULT_SUBJECT_PARALLELISM)


def infer_after_all_agent(change: str) -> AgentConfig:
    return AgentConfig(model="openai/gpt-5.2", variant="high", parallelism=1)


def parse_agent_config(raw: Any, errors: List[str], field_name: str, *, allow_parallelism: bool = False) -> AgentConfig:
    if raw is None:
        return AgentConfig()
    if not isinstance(raw, dict):
        errors.append(f"execution.{field_name} must be a map when present")
        return AgentConfig()
    model = str(raw.get("model", "") or "").strip()
    variant = str(raw.get("variant", "") or "").strip()
    parallelism = 1
    if allow_parallelism:
        value = raw.get("parallelism", 1)
        if value is None:
            value = 1
        try:
            parallelism = int(value)
        except (TypeError, ValueError):
            errors.append(f"execution.{field_name}.parallelism must be an integer when present")
            parallelism = 1
        if parallelism < 1:
            errors.append(f"execution.{field_name}.parallelism must be >= 1")
            parallelism = 1
    return AgentConfig(model=model, variant=variant, parallelism=parallelism)


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

    targets = data.get("targets") or {}
    if not isinstance(targets, dict):
        errors.append("targets must be a map when present")
        targets = {}

    include = [str(x).strip() for x in (targets.get("include") or []) if str(x).strip()]
    exclude = [str(x).strip() for x in (targets.get("exclude") or []) if str(x).strip()]
    if targets.get("include") is not None and not isinstance(targets.get("include"), list):
        errors.append("targets.include must be a list when present")
    if targets.get("exclude") is not None and not isinstance(targets.get("exclude"), list):
        errors.append("targets.exclude must be a list when present")

    context = data.get("context") or {}
    if not isinstance(context, dict):
        errors.append("context must be a map when present")
        context = {}

    execution = data.get("execution") or {}
    if not isinstance(execution, dict):
        errors.append("execution must be a map when present")
        execution = {}

    def validate_path_list(key: str) -> List[Path]:
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

    each_work_item = str(execution.get("each_work_item", "") or "").strip()
    after_all_work_items = str(execution.get("after_all_work_items", "") or "").strip()
    backend = str(execution.get("backend", "cli") or "cli").strip().lower()
    if backend not in {"cli", "server"}:
        errors.append("execution.backend must be one of: cli, server")
        backend = "cli"
    work_item_grouping = str(execution.get("work_item_grouping", "identity") or "identity").strip().lower()
    if work_item_grouping not in {"identity", "type_family"}:
        errors.append("execution.work_item_grouping must be one of: identity, type_family")
        work_item_grouping = "identity"

    resolution_agent = parse_agent_config(execution.get("resolution_agent"), errors, "resolution_agent")
    subject_agent = parse_agent_config(execution.get("subject_agent"), errors, "subject_agent", allow_parallelism=True)
    after_all_agent = parse_agent_config(execution.get("after_all_agent"), errors, "after_all_agent")

    resolution_agent = resolution_agent.resolved(
        fallback_model=infer_resolution_agent(change).model,
        fallback_variant=infer_resolution_agent(change).variant,
        fallback_parallelism=1,
    )
    inferred_subject = infer_subject_agent(change)
    subject_agent = subject_agent.resolved(
        fallback_model=inferred_subject.model,
        fallback_variant=inferred_subject.variant,
        fallback_parallelism=inferred_subject.parallelism,
    )
    inferred_after_all = infer_after_all_agent(change)
    after_all_agent = after_all_agent.resolved(
        fallback_model=inferred_after_all.model,
        fallback_variant=inferred_after_all.variant,
        fallback_parallelism=1,
    )

    context_read = validate_path_list("read")
    context_references = validate_path_list("references")
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
        context_read=context_read,
        context_references=context_references,
        context_notes=context_notes,
        execution=ExecutionPolicy(
            each_work_item=each_work_item,
            after_all_work_items=after_all_work_items,
            backend=backend,
            work_item_grouping=work_item_grouping,
            resolution_agent=resolution_agent,
            subject_agent=subject_agent,
            after_all_agent=after_all_agent,
        ),
    )


def parse_marked_json_block(output: str, begin: str, end: str, label: str) -> Dict[str, Any]:
    start = output.find(begin)
    if start < 0:
        raise SystemExit(f"{label} did not return a result block")
    start += len(begin)
    finish = output.find(end, start)
    if finish < 0:
        raise SystemExit(f"{label} did not return a complete result block")
    payload = output[start:finish].strip()
    try:
        obj = json.loads(payload)
    except json.JSONDecodeError as exc:
        raise SystemExit(f"{label} returned invalid JSON: {exc}") from exc
    if not isinstance(obj, dict):
        raise SystemExit(f"{label} result must be a JSON object")
    return obj


def run_agent_prompt(
    prompt: str,
    cwd: Path,
    *,
    files: Optional[List[Path]] = None,
    agent_config: Optional[AgentConfig] = None,
    attach_url: str = "",
) -> subprocess.CompletedProcess[str]:
    runner_bin = os.environ.get("EPMODEL_AGENT_BIN", "opencode")
    model = (agent_config.model if agent_config else "") or default_agent_model()
    variant = (agent_config.variant if agent_config else "") or default_agent_variant()
    cmd = [runner_bin, "run"]
    if attach_url:
        cmd += ["--attach", attach_url]
    if model:
        cmd += ["--model", model]
    if variant:
        cmd += ["--variant", variant]
    for path in files or []:
        cmd += ["--file", str(path)]
    cmd += ["--", prompt]
    try:
        return subprocess.run(cmd, cwd=str(cwd), text=True, capture_output=True, check=False)
    except FileNotFoundError:
        return subprocess.CompletedProcess(args=cmd, returncode=127, stdout="", stderr=f"runner binary not found: {runner_bin}")


def file_subject(repo_root: Path, path: Path, source_selector: str, why: str = "") -> Subject:
    rel = to_display_path(repo_root, path)
    detail = {
        "path": rel,
        "basename": path.name,
        "suffix": path.suffix,
        "parent": to_display_path(repo_root, path.parent),
        "size_bytes": path.stat().st_size,
        "source_selector": source_selector,
    }
    if why:
        detail["llm_why"] = why
    return Subject(kind="file", subject_id=rel, display=rel, detail=detail)


def candidate_file_catalog(repo_root: Path, selector: str = "") -> List[Dict[str, Any]]:
    files = list_repo_files(repo_root)
    terms = selector_terms(selector)
    if terms:
        filtered = [path for path in files if any(term in to_display_path(repo_root, path).lower() for term in terms)]
        if filtered:
            files = filtered
    return [file_catalog_entry(repo_root, path) for path in files]


def resolve_selector_with_llm(manifest: Manifest, selector: str) -> SelectorResult:
    repo_root = manifest.repo_root
    file_catalog = candidate_file_catalog(repo_root, selector)
    base_prompt = (
        "Resolve one campaign target selector into a concrete set of file subjects.\n"
        "Do not edit files. Do not run builds or tests. Use only file paths that appear in the attached catalog.\n"
        "You may inspect the repository as needed to decide which files belong in the subject set.\n"
        "Resolve the selector to the full intended subject universe, not only files that already appear to need edits.\n"
        "Use the campaign change only to understand subject granularity, not to pre-filter by current compliance.\n"
        f"Return strict JSON between {RESOLUTION_RESULT_BEGIN} and {RESOLUTION_RESULT_END}.\n"
        "JSON schema:\n"
        '{"status":"ok|blocked","explanation":"...","confidence":"high|medium|low","matches":[{"path":"repo/relative/path","why":"..."}],"blocker_reason":"..."}\n'
        "Rules:\n"
        "- Prefer precision over recall.\n"
        "- Return only repo-relative file paths from candidate_files.jsonl.\n"
        "- Use status=blocked if the selector remains ambiguous.\n"
        f"Selector: {selector}\n"
        f"Campaign change: {manifest.change}\n"
        f"Context notes: {manifest.context_notes or '<none>'}\n"
        "Attached files:\n"
        "- candidate_files.jsonl\n"
        "You may also use any attached context files.\n"
    )

    temp_dir = repo_root / STATE_ROOT / ".resolution-tmp"
    temp_dir.mkdir(parents=True, exist_ok=True)
    temp_path = temp_dir / "candidate_files.jsonl"
    temp_path.write_text("".join(json.dumps(item, sort_keys=True) + "\n" for item in file_catalog), encoding="utf-8")

    prompt_attempts = [
        base_prompt,
        base_prompt + "Your final response must contain only the marked JSON block, with no prose before or after it.\n",
    ]
    result: Optional[Dict[str, Any]] = None
    last_error = ""

    try:
        for prompt in prompt_attempts:
            proc = run_agent_prompt(
                prompt,
                repo_root,
                files=[temp_path] + manifest.context_read + manifest.context_references,
                agent_config=manifest.execution.resolution_agent,
            )
            combined = (proc.stdout or "") + ("\n" + proc.stderr if proc.stderr else "")
            if proc.returncode != 0:
                last_error = f"exit code {proc.returncode}: {tail_text(combined, 8)}"
                continue
            try:
                result = parse_marked_json_block(combined, RESOLUTION_RESULT_BEGIN, RESOLUTION_RESULT_END, "LLM subject resolution")
                break
            except SystemExit as exc:
                last_error = f"{exc}: {tail_text(combined, 8)}"
                continue
    finally:
        temp_path.unlink(missing_ok=True)

    if result is None:
        raise SystemExit(f"LLM subject resolution failed: {last_error or 'missing result'}")

    status = str(result.get("status", "") or "").strip().lower()
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
        rel = str(match.get("path", "") or "").strip()
        if not rel:
            continue
        abs_path = to_abs(repo_root, rel)
        if not abs_path.exists() or not abs_path.is_file():
            raise SystemExit(f"LLM subject resolution returned unknown file path: {rel}")
        subjects.append(file_subject(repo_root, abs_path, selector, str(match.get("why", "") or "").strip()))

    return SelectorResult(
        selector=selector,
        kind="llm",
        explanation=str(result.get("explanation", "") or "matched with llm assistance"),
        matched_subjects=unique_subjects(subjects),
    )


def match_path_selector(selector: str, repo_root: Path) -> SelectorResult:
    pattern = selector if Path(selector).is_absolute() else str(repo_root / selector)
    matches = sorted(Path(path).resolve() for path in globlib.glob(pattern, recursive=True))
    if not matches:
        raise SystemExit(f"Target selector matched no files: {selector}")

    subjects: Dict[str, Subject] = {}
    for path in matches:
        if path.is_dir():
            for child in sorted(item.resolve() for item in path.rglob("*") if item.is_file()):
                subject = file_subject(repo_root, child, selector)
                subjects[subject.subject_id] = subject
            continue
        if path.is_file():
            subject = file_subject(repo_root, path, selector)
            subjects[subject.subject_id] = subject

    matched = [subjects[key] for key in sorted(subjects)]
    if not matched:
        raise SystemExit(f"Target selector matched files but no usable file subjects: {selector}")
    return SelectorResult(selector, "path", "matched files/globs as file subjects", matched)


def unique_subjects(subjects: Iterable[Subject]) -> List[Subject]:
    unique: Dict[str, Subject] = {}
    for subject in subjects:
        unique[subject.subject_id] = subject
    return [unique[key] for key in sorted(unique)]


def epmodel_public_headers(repo_root: Path) -> List[Path]:
    base = repo_root / "src/epmodel"
    if not base.exists():
        return []
    headers: List[Path] = []
    for path in sorted(base.rglob("*.hpp")):
        if path.name.endswith("_Impl.hpp"):
            continue
        if path.name in {"EPModelAPI.hpp", "mainpage.hpp"}:
            continue
        if "test" in path.parts:
            continue
        headers.append(path.resolve())
    return headers


def header_is_abstract(path: Path) -> bool:
    try:
        text = path.read_text(encoding="utf-8", errors="ignore")
    except OSError:
        return False
    return bool(re.search(r"=\s*0\s*;", text))


def concrete_epmodel_file_subjects(manifest: Manifest, selector: str) -> List[Subject]:
    repo_root = manifest.repo_root
    subjects: List[Subject] = []
    for header in epmodel_public_headers(repo_root):
        cpp = header.with_suffix(".cpp")
        if not cpp.exists():
            continue
        if header_is_abstract(header):
            continue
        impl = header.with_name(f"{header.stem}_Impl.hpp")
        subjects.append(file_subject(repo_root, header, selector, "builtin concrete type family: public header"))
        if impl.exists():
            subjects.append(file_subject(repo_root, impl, selector, "builtin concrete type family: impl header"))
        subjects.append(file_subject(repo_root, cpp, selector, "builtin concrete type family: implementation"))
    return unique_subjects(subjects)


def match_builtin_selector(manifest: Manifest, selector: str) -> Optional[SelectorResult]:
    lowered = re.sub(r"\s+", " ", selector.strip().lower())
    if lowered in {"all concrete epmodel types", "all concrete epmodel classes"}:
        matched = concrete_epmodel_file_subjects(manifest, selector)
        return SelectorResult(
            selector,
            "builtin",
            "matched concrete epmodel file families using public headers with sibling implementations",
            matched,
        )
    return None


def default_subjects(manifest: Manifest) -> List[Subject]:
    return [file_subject(manifest.repo_root, path, "<default>") for path in list_repo_files(manifest.repo_root)]


def resolve_selector(manifest: Manifest, selector: str) -> SelectorResult:
    builtin = match_builtin_selector(manifest, selector)
    if builtin is not None:
        return builtin
    if looks_like_path_selector(selector):
        return match_path_selector(selector, manifest.repo_root)
    return resolve_selector_with_llm(manifest, selector)


def resolve_targets(manifest: Manifest) -> Resolution:
    include_results: List[SelectorResult] = []
    exclude_results: List[SelectorResult] = []
    include_subjects: List[Subject] = []
    exclude_subjects: List[Subject] = []

    if manifest.include:
        for selector in manifest.include:
            result = resolve_selector(manifest, selector)
            include_results.append(result)
            include_subjects.extend(result.matched_subjects)
    else:
        defaults = default_subjects(manifest)
        include_results.append(SelectorResult("<default>", "default", "used all repo files", defaults))
        include_subjects.extend(defaults)

    for selector in manifest.exclude:
        result = resolve_selector(manifest, selector)
        exclude_results.append(result)
        exclude_subjects.extend(result.matched_subjects)

    include_unique = unique_subjects(include_subjects)
    exclude_unique = unique_subjects(exclude_subjects)
    excluded_ids = {subject.subject_id for subject in exclude_unique}
    selected = [subject for subject in include_unique if subject.subject_id not in excluded_ids]

    return Resolution(
        include=include_results,
        exclude=exclude_results,
        include_subjects=include_unique,
        exclude_subjects=exclude_unique,
        selected_subjects=selected,
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
    return state_root_for(manifest) / "latest-run.json"


def run_root_for(manifest: Manifest, run_id: str) -> Path:
    return state_root_for(manifest) / "runs" / run_id


def control_path(run_dir: Path) -> Path:
    return run_dir / "control.json"


def controller_log_path(run_dir: Path) -> Path:
    return run_dir / "controller.log"


def server_log_path(run_dir: Path) -> Path:
    return run_dir / "server.log"


def load_run_bundle(run_dir: Path) -> Tuple[Dict[str, Any], Dict[str, Any], Dict[str, Any]]:
    run = read_json(run_dir / "run.json", None)
    subjects = read_json(run_dir / "subjects.json", None)
    work_items = read_json(run_dir / "work-items.json", None)
    if not isinstance(run, dict) or not isinstance(subjects, dict) or not isinstance(work_items, dict):
        raise SystemExit(f"Invalid run state at {run_dir}")
    return run, subjects, work_items


def engine_plan() -> Dict[str, Any]:
    return {
        "strategy": "agent_per_subject",
        "summary": "Resolve subjects and run an agent on each subject.",
        "work_item_kind": "subject",
        "apply_capable": True,
        "supported": True,
        "reason": "generic manifest executor",
    }


def build_resolution_artifacts(manifest: Manifest, execution_policy: ExecutionPolicy, resolution: Resolution) -> Tuple[Dict[str, Any], Dict[str, Any], Dict[str, Any]]:
    work_item_kind = "type_family" if execution_policy.work_item_grouping == "type_family" else "subject"
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
        "plan": engine_plan(),
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
            "selected_count": len(resolution.selected_subjects),
            "selected_kind_counts": subject_kind_counts(resolution.selected_subjects),
        },
        "work_item_summary": {
            "kind": work_item_kind,
            "count": len(resolution.selected_subjects),
            "mapping": execution_policy.work_item_grouping,
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
        "selected": [subject.to_json() for subject in resolution.selected_subjects],
    }

    work_items = {
        "kind": work_item_kind,
        "mapping": execution_policy.work_item_grouping,
        "item_count": len(resolution.selected_subjects),
        "source": "subjects.json",
        "items": [],
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
    if str((resolution_record.get("manifest") or {}).get("sha256", "")) != file_sha256(manifest.manifest_path):
        resolution_record["status"] = "stale"
        resolution_record["stale_reason"] = "manifest changed since describe"
        save_resolution_artifacts(manifest, resolution_record, subjects, work_items)
        raise SystemExit("Persisted resolution is stale. Run describe again.")

    if resolution_record.get("status") != "current":
        raise SystemExit("Persisted resolution is not current. Run describe again.")
    return resolution_record, subjects, work_items


def paths_from_subject_detail(manifest: Manifest, detail: Dict[str, Any]) -> List[Path]:
    paths: List[Path] = []
    for key, value in detail.items():
        if isinstance(value, str) and value.strip() and (key == "path" or key.endswith("_path")):
            path = to_abs(manifest.repo_root, value)
            if path.exists() and path.is_file():
                paths.append(path)
    unique: List[Path] = []
    seen: Set[Path] = set()
    for path in paths:
        if path not in seen:
            unique.append(path)
            seen.add(path)
    return unique


def type_family_key(subject: Dict[str, Any]) -> str:
    detail = subject.get("detail") or {}
    path = str(detail.get("path", subject.get("subject_id", "")) or "")
    base = Path(path).name
    if base.endswith("_Impl.hpp"):
        return base[:-9]
    return Path(base).stem


def build_run_work_items(resolution_work_items: Dict[str, Any], subjects: Dict[str, Any], execution_policy: ExecutionPolicy, manifest: Manifest) -> Dict[str, Any]:
    source_subjects = subjects.get("selected") or subjects.get("include") or []
    items = []
    if execution_policy.work_item_grouping == "type_family":
        grouped: Dict[str, List[Dict[str, Any]]] = {}
        for subject in source_subjects:
            if not isinstance(subject, dict):
                continue
            grouped.setdefault(type_family_key(subject), []).append(subject)
        for family, members in sorted(grouped.items()):
            editable_paths: List[str] = []
            seen_paths: Set[str] = set()
            for subject in members:
                for path in paths_from_subject_detail(manifest, subject.get("detail") or {}):
                    display = to_display_path(manifest.repo_root, path)
                    if display not in seen_paths:
                        editable_paths.append(display)
                        seen_paths.add(display)
            destination_hint = "ModelObject"
            if family == "DesignSpecificationOutdoorAir":
                destination_hint = "ResourceObject"
            elif family == "SetpointManagerMixedAir":
                destination_hint = "SetpointManager"
            elif family == "Splitter":
                destination_hint = "HVACComponent"
            items.append(
                {
                    "kind": "type_family",
                    "work_item_id": family,
                    "subject_id": family,
                    "subject_ids": [str(subject.get("subject_id", "") or "") for subject in sorted(members, key=lambda x: str(x.get("subject_id", "")))],
                    "status": "pending",
                    "changed_files": [],
                    "detail": "",
                    "session_scope": "work_item",
                    "validation": {
                        "instructions": execution_policy.each_work_item,
                        "mode": "agent_per_subject",
                        "performed": [],
                        "result": "not_run",
                    },
                    "editable_paths": editable_paths,
                    "family_destination_hint": destination_hint,
                    "worker_id": None,
                    "session_id": None,
                    "started_at": None,
                    "finished_at": None,
                    "heartbeat_at": None,
                    "updated_at": None,
                }
            )
        return {
            "kind": "type_family",
            "mapping": "type_family",
            "item_count": len(items),
            "source": "subjects.json",
            "items": items,
        }
    for subject in source_subjects:
        if not isinstance(subject, dict):
            continue
        editable = [to_display_path(manifest.repo_root, path) for path in paths_from_subject_detail(manifest, subject.get("detail") or {})]
        items.append(
            {
                "kind": str(subject.get("kind", "") or "subject"),
                "work_item_id": str(subject.get("subject_id", "") or ""),
                "subject_id": str(subject.get("subject_id", "") or ""),
                "subject_ids": [str(subject.get("subject_id", "") or "")],
                "status": "pending",
                "changed_files": [],
                "detail": "",
                "session_scope": "work_item",
                "validation": {
                    "instructions": execution_policy.each_work_item,
                    "mode": "agent_per_subject",
                    "performed": [],
                    "result": "not_run",
                },
                "editable_paths": editable,
                "worker_id": None,
                "session_id": None,
                "started_at": None,
                "finished_at": None,
                "heartbeat_at": None,
                "updated_at": None,
            }
        )
    return {
        "kind": resolution_work_items.get("kind", "subject"),
        "mapping": "identity",
        "item_count": len(items),
        "source": "subjects.json",
        "items": items,
    }


def execution_runtime(manifest: Manifest) -> Dict[str, Any]:
    return {
        "backend": manifest.execution.backend,
        "launch_mode": "foreground",
        "controller": {
            "pid": None,
            "heartbeat_at": None,
            "started_at": None,
            "updated_at": None,
            "log_path": None,
        },
        "server": None,
        "agent_selection": {
            "resolution_agent": manifest.execution.resolution_agent.to_json(),
            "subject_agent": manifest.execution.subject_agent.to_json(),
            "after_all_agent": manifest.execution.after_all_agent.to_json(),
        },
    }


def create_run(manifest: Manifest, resolution_record: Dict[str, Any], subjects: Dict[str, Any], resolution_work_items: Dict[str, Any], execution_policy: ExecutionPolicy) -> Tuple[Path, Dict[str, Any], Dict[str, Any], Dict[str, Any]]:
    run_id = utc_stamp()
    run_dir = run_root_for(manifest, run_id)
    run_dir.mkdir(parents=True, exist_ok=True)
    work_items = build_run_work_items(resolution_work_items, subjects, execution_policy, manifest)

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
        "plan": resolution_record.get("plan", engine_plan()),
        "resolution": {
            "path": to_display_path(manifest.repo_root, resolution_path(manifest)),
            "status": resolution_record.get("status"),
            "manifest_sha256": (resolution_record.get("manifest") or {}).get("sha256"),
        },
        "execution": {
            "session_model": "per_subject",
            "work_item_kind": work_items.get("kind", "subject"),
            "policy": execution_policy.to_json(),
            "phases": {
                "work_items": "pending",
                "after_all_work_items": "pending" if execution_policy.has_after_all else "not_requested",
            },
            "parallelism": execution_policy.subject_agent.parallelism,
        },
        "context": {
            "read": [{"path": to_display_path(manifest.repo_root, path), "sha256": file_sha256(path), "size_bytes": path.stat().st_size} for path in manifest.context_read],
            "references": [{"path": to_display_path(manifest.repo_root, path), "sha256": file_sha256(path), "size_bytes": path.stat().st_size} for path in manifest.context_references],
            "notes": manifest.context_notes,
        },
        "selectors": resolution_record.get("selectors", {}),
        "subject_summary": {
            "included": resolution_record.get("subject_summary", {}).get("selected_kind_counts", {}),
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
        "runtime": execution_runtime(manifest),
        "after_all_work_items": None,
    }

    write_json(run_dir / "run.json", run)
    write_json(run_dir / "subjects.json", subjects)
    write_json(run_dir / "work-items.json", work_items)
    write_json(control_path(run_dir), {"requested": "continue", "updated_at": utc_now()})
    append_event(run_dir / "events.jsonl", {"time": utc_now(), "event": "run_created", "run_id": run_id})
    write_json(latest_pointer_path(manifest), {"run_id": run_id, "path": to_display_path(manifest.repo_root, run_dir), "updated_at": utc_now()})
    return run_dir, run, subjects, work_items


def load_latest_resumable_run(manifest: Manifest) -> Optional[Tuple[Path, Dict[str, Any], Dict[str, Any], Dict[str, Any]]]:
    pointer = read_json(latest_pointer_path(manifest), None)
    if not isinstance(pointer, dict):
        return None
    run_path = pointer.get("path")
    if not isinstance(run_path, str) or not run_path:
        return None
    run_dir = to_abs(manifest.repo_root, run_path)
    run, subjects, work_items = load_run_bundle(run_dir)
    if run.get("status") in {"completed", "failed", "cancelled"}:
        return None
    if str((run.get("manifest") or {}).get("sha256", "")) != file_sha256(manifest.manifest_path):
        return None
    return run_dir, run, subjects, work_items


def load_run_by_id(manifest: Manifest, run_id: str) -> Tuple[Path, Dict[str, Any], Dict[str, Any], Dict[str, Any]]:
    run_dir = run_root_for(manifest, run_id)
    if not run_dir.exists():
        raise SystemExit(f"Run not found: {run_id}")
    run, subjects, work_items = load_run_bundle(run_dir)
    return run_dir, run, subjects, work_items


def save_run_state(run_dir: Path, run: Dict[str, Any], subjects: Dict[str, Any], work_items: Dict[str, Any]) -> None:
    run["updated_at"] = utc_now()
    write_json(run_dir / "run.json", run)
    write_json(run_dir / "subjects.json", subjects)
    write_json(run_dir / "work-items.json", work_items)


def refresh_work_item_summary(run: Dict[str, Any], work_items: Dict[str, Any]) -> None:
    summary = {"total": 0, "pending": 0, "queued": 0, "in_progress": 0, "done": 0, "skipped": 0, "failed": 0}
    for item in work_items.get("items", []):
        status = str(item.get("status", "pending") or "pending")
        summary["total"] += 1
        if status in summary:
            summary[status] += 1
        else:
            summary["failed"] += 1
    run["work_item_summary"] = summary


def subject_index(subjects: Dict[str, Any]) -> Dict[str, Dict[str, Any]]:
    index: Dict[str, Dict[str, Any]] = {}
    for key in ["selected", "include", "exclude"]:
        for subject in subjects.get(key, []):
            if not isinstance(subject, dict):
                continue
            subject_id = str(subject.get("subject_id", "") or "")
            if subject_id:
                index[subject_id] = subject
    return index


def subject_for_work_item(item: Dict[str, Any], subjects: Dict[str, Any]) -> Dict[str, Any]:
    index = subject_index(subjects)
    for key in ["subject_id", "work_item_id"]:
        subject_id = str(item.get(key, "") or "")
        if subject_id in index:
            return index[subject_id]
    for subject_id in item.get("subject_ids", []):
        if subject_id in index:
            return index[subject_id]
    raise SystemExit(f"Could not resolve subject for work item: {item.get('work_item_id', '<empty>')}")


def subjects_for_work_item(item: Dict[str, Any], subjects: Dict[str, Any]) -> List[Dict[str, Any]]:
    index = subject_index(subjects)
    resolved: List[Dict[str, Any]] = []
    seen: Set[str] = set()
    for subject_id in item.get("subject_ids", []):
        if subject_id in index and subject_id not in seen:
            resolved.append(index[subject_id])
            seen.add(subject_id)
    if resolved:
        return resolved
    return [subject_for_work_item(item, subjects)]


def attached_paths_for_subject(manifest: Manifest, subject: Dict[str, Any]) -> List[Path]:
    paths = paths_from_subject_detail(manifest, subject.get("detail") or {})
    unique: List[Path] = []
    seen: Set[Path] = set()
    for path in paths + manifest.context_read + manifest.context_references:
        if path.exists() and path not in seen:
            unique.append(path)
            seen.add(path)
    return unique


def editable_paths_for_subject(manifest: Manifest, subject: Dict[str, Any]) -> List[Path]:
    return paths_from_subject_detail(manifest, subject.get("detail") or {})


def attached_paths_for_work_item(manifest: Manifest, item: Dict[str, Any], work_subjects: List[Dict[str, Any]]) -> List[Path]:
    unique: List[Path] = []
    seen: Set[Path] = set()
    for subject in work_subjects:
        for path in paths_from_subject_detail(manifest, subject.get("detail") or {}):
            if path.exists() and path not in seen:
                unique.append(path)
                seen.add(path)
    for path in manifest.context_read + manifest.context_references:
        if path.exists() and path not in seen:
            unique.append(path)
            seen.add(path)
    return unique


def editable_paths_for_work_item(manifest: Manifest, item: Dict[str, Any], work_subjects: List[Dict[str, Any]]) -> List[Path]:
    unique: List[Path] = []
    seen: Set[Path] = set()
    for subject in work_subjects:
        for path in paths_from_subject_detail(manifest, subject.get("detail") or {}):
            if path not in seen:
                unique.append(path)
                seen.add(path)
    return unique


def snapshot_paths(paths: Iterable[Path]) -> Dict[str, Optional[str]]:
    snapshot: Dict[str, Optional[str]] = {}
    for path in paths:
        snapshot[str(path)] = file_sha256(path) if path.exists() else None
    return snapshot


def changed_paths_from_snapshots(before: Dict[str, Optional[str]], after: Dict[str, Optional[str]], repo_root: Path) -> List[str]:
    changed: List[str] = []
    for path_str in sorted(set(before) | set(after)):
        if before.get(path_str) != after.get(path_str):
            changed.append(to_display_path(repo_root, Path(path_str)))
    return changed


def normalize_changed_files(repo_root: Path, values: Any) -> List[str]:
    if not isinstance(values, list):
        return []
    normalized: List[str] = []
    seen: Set[str] = set()
    for value in values:
        if not isinstance(value, str) or not value.strip():
            continue
        display = to_display_path(repo_root, to_abs(repo_root, value.strip()))
        if display not in seen:
            normalized.append(display)
            seen.add(display)
    return normalized


def join_detail(summary: str, notes: str) -> str:
    parts = [part.strip() for part in [summary, notes] if part and part.strip()]
    return " | ".join(parts)


def subject_prompt(manifest: Manifest, subject: Dict[str, Any]) -> str:
    display = str(subject.get("display", subject.get("subject_id", "<unknown>")) or "<unknown>")
    detail = json.dumps(subject.get("detail", {}), indent=2, sort_keys=True)
    return (
        "Execute one campaign subject.\n"
        "Make only the changes needed for this subject. Do not edit unrelated subjects.\n"
        "You may inspect the attached files and use repository tools as needed, but avoid shell commands unless absolutely necessary.\n"
        "Do not run builds, tests, loops, broad searches, or long-running shell commands for a single subject.\n"
        "If a shell command would require extra permission, skip it and continue with file-focused reasoning instead.\n"
        "Allowed: read attached files, inspect nearby code, make focused edits to this subject, and reason from the provided context.\n"
        "Forbidden: builds, tests, benchmarking, repository-wide shell exploration, permission-gated shell calls, and any command intended to iterate broadly or run for a long time.\n"
        "If the subject is already compliant, report done with no changed files.\n"
        "If the subject is intentionally not applicable or unsafe to change, report skipped and explain why.\n"
        "Your final output must be exactly one marked JSON block and nothing else.\n"
        "Do not output diffs, patches, commentary, or tool transcripts outside the JSON block.\n"
        f"Return strict JSON between {EXEC_RESULT_BEGIN} and {EXEC_RESULT_END}.\n"
        "JSON schema:\n"
        '{"status":"done|skipped|failed","summary":"...","changed_files":["path"],"notes":"..."}\n'
        f"Campaign change:\n{manifest.change}\n\n"
        f"Per-subject instructions:\n{manifest.each_work_item or '<none>'}\n\n"
        f"Context notes:\n{manifest.context_notes or '<none>'}\n\n"
        f"Subject:\n- display: {display}\n- kind: {subject.get('kind', '<unknown>')}\n- id: {subject.get('subject_id', '<unknown>')}\n"
        f"Subject detail JSON:\n{detail}\n"
    )


def work_item_prompt(manifest: Manifest, item: Dict[str, Any], work_subjects: List[Dict[str, Any]]) -> str:
    if len(work_subjects) == 1 and item.get("kind") != "type_family":
        return subject_prompt(manifest, work_subjects[0])
    members = []
    for subject in work_subjects:
        members.append(
            {
                "subject_id": subject.get("subject_id"),
                "display": subject.get("display"),
                "detail": subject.get("detail"),
            }
        )
    return (
        "Execute one campaign work item spanning a single epmodel type family.\n"
        "Make only the changes needed for this one type family. Do not edit unrelated families.\n"
        "You may inspect the attached files and use repository tools as needed, but avoid shell commands unless absolutely necessary.\n"
        "Do not run builds, tests, loops, broad searches, or long-running shell commands except the explicitly requested validation build for this work item.\n"
        "If a shell command would require extra permission, skip it and continue with file-focused reasoning instead.\n"
        "Allowed: read attached files, inspect nearby code, make focused edits to this family, and run the requested validation build command.\n"
        "Forbidden: repository-wide exploratory shell usage, permission-gated shell calls, broad loops, and unrelated edits outside this family.\n"
        "Your final output must be exactly one marked JSON block and nothing else.\n"
        f"Return strict JSON between {EXEC_RESULT_BEGIN} and {EXEC_RESULT_END}.\n"
        "JSON schema:\n"
        '{"status":"done|skipped|failed","summary":"...","changed_files":["path"],"notes":"..."}\n'
        f"Campaign change:\n{manifest.change}\n\n"
        f"Per-work-item instructions:\n{manifest.each_work_item or '<none>'}\n\n"
        f"Context notes:\n{manifest.context_notes or '<none>'}\n\n"
        f"Work item id: {item.get('work_item_id')}\n"
        f"Destination hint: {item.get('family_destination_hint', '<none>')}\n"
        f"Family members JSON:\n{json.dumps(members, indent=2, sort_keys=True)}\n"
    )


def after_all_prompt(manifest: Manifest, run: Dict[str, Any], work_items: Dict[str, Any]) -> str:
    changed_files = sorted({path for item in work_items.get("items", []) for path in item.get("changed_files", [])})
    return (
        "Execute the final campaign phase after all subjects are processed.\n"
        "Use repository tools as needed.\n"
        f"Return strict JSON between {EXEC_RESULT_BEGIN} and {EXEC_RESULT_END}.\n"
        "JSON schema:\n"
        '{"status":"done|skipped|failed","summary":"...","changed_files":["path"],"notes":"..."}\n'
        f"Campaign change:\n{manifest.change}\n\n"
        f"After-all instructions:\n{manifest.after_all_work_items or '<none>'}\n\n"
        f"Context notes:\n{manifest.context_notes or '<none>'}\n\n"
        f"Completed work item count: {run.get('work_item_summary', {}).get('done', 0)}\n"
        f"Skipped work item count: {run.get('work_item_summary', {}).get('skipped', 0)}\n"
        f"Previously changed files:\n{json.dumps(changed_files, indent=2)}\n"
    )


def started_server_metadata(started: StartedServer, repo_root: Path) -> Dict[str, Any]:
    return {
        "url": started.url,
        "pid": started.pid,
        "log_path": to_display_path(repo_root, started.log_path),
        "started_at": utc_now(),
    }


def choose_free_port() -> int:
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
        sock.bind(("127.0.0.1", 0))
        return int(sock.getsockname()[1])


def process_is_alive(pid: Optional[int]) -> bool:
    if not pid:
        return False
    try:
        os.kill(int(pid), PID_POLL_SIGNAL)
    except OSError:
        return False
    return True


def process_snapshot(pid: Optional[int]) -> Dict[str, Any]:
    if not pid or not process_is_alive(pid):
        return {"alive": False, "pid": pid, "children": []}
    cmd = ["ps", "-o", "pid=,ppid=,pgid=,stat=,etime=,cmd=", "-p", str(pid), "--ppid", str(pid)]
    proc = subprocess.run(cmd, text=True, capture_output=True, check=False)
    lines = [line.rstrip() for line in (proc.stdout or "").splitlines() if line.strip()]
    children: List[Dict[str, Any]] = []
    root: Dict[str, Any] = {"alive": True, "pid": pid, "children": children}
    for idx, line in enumerate(lines):
        parts = line.split(None, 5)
        if len(parts) < 6:
            continue
        entry = {
            "pid": int(parts[0]),
            "ppid": int(parts[1]),
            "pgid": int(parts[2]),
            "stat": parts[3],
            "etime": parts[4],
            "cmd": parts[5],
        }
        if idx == 0 and entry["pid"] == int(pid):
            root.update(entry)
        else:
            children.append(entry)
    root["top_commands"] = [entry["cmd"] for entry in children[:5]]
    return root


def classify_process_tree(snapshot: Dict[str, Any]) -> str:
    commands = "\n".join(snapshot.get("top_commands") or [])
    lowered = commands.lower()
    if "cmake --build" in lowered or "ninja" in lowered or "gmake" in lowered or "make " in lowered:
        return "building"
    if "ctest" in lowered or "openstudio_epmodel_tests" in lowered:
        return "testing"
    if commands.strip():
        return "running_tools"
    if snapshot.get("alive"):
        return "agent_running"
    return "not_running"


def monitored_process_metadata(proc: subprocess.Popen[str], attach_url: str = "") -> Dict[str, Any]:
    return {
        "pid": proc.pid,
        "attach_url": attach_url or None,
        "heartbeat_at": utc_now(),
        "phase_detail": "agent_started",
        "process_tree": process_snapshot(proc.pid),
    }


def controller_is_alive(run: Dict[str, Any]) -> bool:
    runtime = run.get("runtime") or {}
    controller = runtime.get("controller") or {}
    return process_is_alive(controller.get("pid"))


def ensure_server_backend(manifest: Manifest, run_dir: Path, run: Dict[str, Any]) -> Optional[StartedServer]:
    if manifest.execution.backend != "server":
        return None
    runtime = run.setdefault("runtime", {})
    existing = runtime.get("server") or {}
    pid = existing.get("pid")
    url = str(existing.get("url", "") or "")
    if url and process_is_alive(pid):
        return StartedServer(url=url, pid=int(pid), log_path=to_abs(manifest.repo_root, str(existing.get("log_path", "") or server_log_path(run_dir))))

    port = choose_free_port()
    log_path = server_log_path(run_dir)
    runner_bin = os.environ.get("EPMODEL_AGENT_BIN", "opencode")
    with log_path.open("a", encoding="utf-8") as handle:
        proc = subprocess.Popen(
            [runner_bin, "serve", "--hostname", "127.0.0.1", "--port", str(port)],
            cwd=str(manifest.repo_root),
            stdout=handle,
            stderr=handle,
            text=True,
            start_new_session=True,
        )
    url = f"http://127.0.0.1:{port}"
    time.sleep(1.0)
    if proc.poll() is not None:
        detail = tail_text(log_path.read_text(encoding="utf-8", errors="ignore"), 12) if log_path.exists() else ""
        raise SystemExit(f"Unable to start opencode server backend: {detail or 'server exited immediately'}")
    started = StartedServer(url=url, pid=proc.pid, log_path=log_path)
    runtime["server"] = started_server_metadata(started, manifest.repo_root)
    return started


def stop_server_backend(started: Optional[StartedServer], run: Dict[str, Any]) -> None:
    if started is None:
        return
    try:
        os.kill(started.pid, 15)
    except OSError:
        pass
    runtime = run.setdefault("runtime", {})
    server = runtime.get("server") or {}
    server["stopped_at"] = utc_now()
    runtime["server"] = server


def run_subject_agent(manifest: Manifest, subject: Dict[str, Any], *, attach_url: str = "") -> Tuple[str, List[str], str, Dict[str, Any]]:
    repo_root = manifest.repo_root
    attached = attached_paths_for_subject(manifest, subject)
    editable = editable_paths_for_subject(manifest, subject)
    before = snapshot_paths(editable)
    proc = run_agent_prompt(
        subject_prompt(manifest, subject),
        repo_root,
        files=attached,
        agent_config=manifest.execution.subject_agent,
        attach_url=attach_url,
    )
    combined = (proc.stdout or "") + ("\n" + proc.stderr if proc.stderr else "")
    metadata = {
        "model": manifest.execution.subject_agent.model or default_agent_model() or None,
        "variant": manifest.execution.subject_agent.variant or default_agent_variant() or None,
        "backend": manifest.execution.backend,
        "session_id": None,
    }
    if proc.returncode != 0:
        return "failed", [], tail_text(combined, 10) or f"agent exited with code {proc.returncode}", metadata

    try:
        result = parse_marked_json_block(combined, EXEC_RESULT_BEGIN, EXEC_RESULT_END, "Subject executor")
    except SystemExit as exc:
        return "failed", [], f"{exc}: {tail_text(combined, 10)}", metadata

    status = str(result.get("status", "") or "").strip().lower()
    if status not in {"done", "skipped", "failed"}:
        return "failed", [], f"invalid executor status: {status or '<empty>'}", metadata

    after = snapshot_paths(editable)
    detected = changed_paths_from_snapshots(before, after, repo_root)
    reported = normalize_changed_files(repo_root, result.get("changed_files"))
    changed_files = sorted({*detected, *reported})
    detail = join_detail(str(result.get("summary", "") or ""), str(result.get("notes", "") or ""))
    return status, changed_files, detail or "subject processed", metadata


def run_after_all_agent(manifest: Manifest, run_dir: Path, run: Dict[str, Any], subjects: Dict[str, Any], work_items: Dict[str, Any], *, attach_url: str = "") -> Tuple[str, List[str], str, Dict[str, Any]]:
    runner_bin = os.environ.get("EPMODEL_AGENT_BIN", "opencode")
    model = manifest.execution.after_all_agent.model or default_agent_model()
    variant = manifest.execution.after_all_agent.variant or default_agent_variant()
    command = [runner_bin, "run"]
    if attach_url:
        command += ["--attach", attach_url]
    if model:
        command += ["--model", model]
    if variant:
        command += ["--variant", variant]
    for path in manifest.context_read + manifest.context_references:
        command += ["--file", str(path)]
    command += ["--", after_all_prompt(manifest, run, work_items)]
    try:
        proc = subprocess.Popen(command, cwd=str(manifest.repo_root), text=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    except FileNotFoundError:
        return "failed", [], f"runner binary not found: {runner_bin}", {"model": model or None, "variant": variant or None, "backend": manifest.execution.backend, "session_id": None}

    after_all_state = run.setdefault("after_all_work_items", {})
    after_all_state.update(monitored_process_metadata(proc, attach_url=attach_url))
    after_all_state["status"] = "running"
    append_event(run_dir / "events.jsonl", {"time": utc_now(), "event": "after_all_agent_pid", "pid": proc.pid})

    while proc.poll() is None:
        snapshot = process_snapshot(proc.pid)
        after_all_state["heartbeat_at"] = utc_now()
        after_all_state["process_tree"] = snapshot
        after_all_state["phase_detail"] = classify_process_tree(snapshot)
        run["after_all_work_items"] = after_all_state
        save_run_state(run_dir, run, subjects, work_items)
        maybe_emit_controller_snapshot(run_dir, run, work_items)
        time.sleep(2.0)

    stdout, stderr = proc.communicate()
    combined = (stdout or "") + ("\n" + stderr if stderr else "")
    metadata = {
        "model": model or None,
        "variant": variant or None,
        "backend": manifest.execution.backend,
        "session_id": None,
        "pid": proc.pid,
    }
    after_all_state["heartbeat_at"] = utc_now()
    after_all_state["process_tree"] = process_snapshot(proc.pid)
    after_all_state["phase_detail"] = "completed" if proc.returncode == 0 else "failed"
    run["after_all_work_items"] = after_all_state
    if proc.returncode != 0:
        return "failed", [], tail_text(combined, 12) or f"agent exited with code {proc.returncode}", metadata
    try:
        result = parse_marked_json_block(combined, EXEC_RESULT_BEGIN, EXEC_RESULT_END, "After-all executor")
    except SystemExit as exc:
        return "failed", [], f"{exc}: {tail_text(combined, 12)}", metadata

    status = str(result.get("status", "") or "").strip().lower()
    if status not in {"done", "skipped", "failed"}:
        return "failed", [], f"invalid executor status: {status or '<empty>'}", metadata

    changed_files = normalize_changed_files(manifest.repo_root, result.get("changed_files"))
    detail = join_detail(str(result.get("summary", "") or ""), str(result.get("notes", "") or ""))
    return status, changed_files, detail or "after-all phase processed", metadata


def describe(manifest: Manifest, execution_policy: ExecutionPolicy, resolution: Resolution) -> int:
    resolution_record, subjects, work_items = build_resolution_artifacts(manifest, execution_policy, resolution)
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
            "sample_selected": subjects["selected"][:10],
            "sample_excluded": subjects["exclude"][:10],
        },
        "work_items": {
            "kind": work_items["kind"],
            "count": work_items["item_count"],
            "sample": subjects["selected"][:10],
        },
    }
    print_data(out)
    return 0


def run_state_summary(run_dir: Path, run: Dict[str, Any], work_items: Dict[str, Any], repo_root: Path, event_limit: int = 8) -> Dict[str, Any]:
    runtime = run.get("runtime") or {}
    controller = runtime.get("controller") or {}
    server = runtime.get("server") or {}
    active = [
        {
            "work_item_id": item.get("work_item_id"),
            "status": item.get("status"),
            "worker_id": item.get("worker_id"),
            "started_at": item.get("started_at"),
            "heartbeat_at": item.get("heartbeat_at"),
            "editable_paths": item.get("editable_paths", []),
        }
        for item in work_items.get("items", [])
        if item.get("status") in {"queued", "in_progress"}
    ]
    events_path = run_dir / "events.jsonl"
    recent_events: List[Dict[str, Any]] = []
    if events_path.exists():
        lines = events_path.read_text(encoding="utf-8", errors="ignore").splitlines()
        for line in lines[-event_limit:]:
            try:
                event = json.loads(line)
            except json.JSONDecodeError:
                continue
            if isinstance(event, dict):
                recent_events.append(event)
    progress = work_items.get("items", [])
    completed_count = sum(1 for item in progress if item.get("status") in {"done", "failed", "skipped"})
    start_time = parse_utc(run.get("created_at"))
    now_time = dt.datetime.now(dt.timezone.utc)
    eta: Optional[Dict[str, Any]] = None
    if start_time is not None and completed_count > 0:
        elapsed_seconds = max(1.0, (now_time - start_time).total_seconds())
        throughput_per_minute = completed_count / (elapsed_seconds / 60.0)
        remaining_count = sum(1 for item in progress if item.get("status") in {"pending", "queued", "in_progress"})
        remaining_seconds = (remaining_count / completed_count) * elapsed_seconds if completed_count > 0 else 0.0
        eta_at = now_time + dt.timedelta(seconds=remaining_seconds)
        eta = {
            "completed_items": completed_count,
            "remaining_items": remaining_count,
            "elapsed_seconds": int(round(elapsed_seconds)),
            "throughput_per_minute": round(throughput_per_minute, 2),
            "remaining_seconds": int(round(remaining_seconds)),
            "remaining_human": format_duration(remaining_seconds),
            "estimated_completion_at": eta_at.replace(microsecond=0).isoformat().replace("+00:00", "Z"),
        }
    return {
        "campaign_id": run.get("campaign_id"),
        "run_id": run.get("run_id"),
        "status": run.get("status"),
        "execution": run.get("execution"),
        "runtime": run.get("runtime"),
        "controller": {
            **controller,
            "alive": process_is_alive(controller.get("pid")),
            "process_tree": process_snapshot(controller.get("pid")),
        },
        "server": {
            **server,
            "alive": process_is_alive(server.get("pid")),
        } if server else None,
        "work_item_summary": run.get("work_item_summary"),
        "eta": eta,
        "active_work_items": active,
        "after_all_work_items": run.get("after_all_work_items"),
        "recent_events": recent_events,
        "state": {
            "run": to_display_path(repo_root, run_dir),
            "run_json": to_display_path(repo_root, run_dir / "run.json"),
            "subjects_json": to_display_path(repo_root, run_dir / "subjects.json"),
            "work_items_json": to_display_path(repo_root, run_dir / "work-items.json"),
            "events_jsonl": to_display_path(repo_root, run_dir / "events.jsonl"),
            "control_json": to_display_path(repo_root, control_path(run_dir)),
            "controller_log": to_display_path(repo_root, controller_log_path(run_dir)),
        },
    }


def print_status_text(summary: Dict[str, Any]) -> None:
    execution = summary.get("execution") or {}
    runtime = summary.get("runtime") or {}
    controller = summary.get("controller") or {}
    server = summary.get("server") or {}
    work_item_summary = summary.get("work_item_summary") or {}
    active = summary.get("active_work_items") or []
    print(f"run_id: {summary.get('run_id')}")
    print(f"status: {summary.get('status')}")
    print(f"backend: {runtime.get('backend') or execution.get('policy', {}).get('backend') or '<unknown>'}")
    if controller:
        print(f"controller: pid={controller.get('pid')} alive={controller.get('alive')} heartbeat={controller.get('heartbeat_at')}")
    phases = (execution.get("phases") or {})
    print(f"phases: work_items={phases.get('work_items')} after_all_work_items={phases.get('after_all_work_items')}")
    print(
        "work_items: "
        f"total={work_item_summary.get('total', 0)} "
        f"pending={work_item_summary.get('pending', 0)} queued={work_item_summary.get('queued', 0)} "
        f"in_progress={work_item_summary.get('in_progress', 0)} done={work_item_summary.get('done', 0)} "
        f"skipped={work_item_summary.get('skipped', 0)} failed={work_item_summary.get('failed', 0)}"
    )
    eta = summary.get("eta") or {}
    if eta:
        print(
            "eta: "
            f"remaining={eta.get('remaining_human')} "
            f"at={eta.get('estimated_completion_at')} "
            f"rate={eta.get('throughput_per_minute')} items/min"
        )
    if active:
        print("active_work_items:")
        for item in active[:10]:
            age = elapsed_human(item.get("started_at"))
            age_text = f" age={age}" if age else ""
            print(f"- {item.get('work_item_id')} [{item.get('status')}] worker={item.get('worker_id')}{age_text}")
    events = summary.get("recent_events") or []
    if events:
        print("recent_events:")
        for event in events[-5:]:
            print(f"- {event.get('time')} {event.get('event')}")
    after_all = summary.get("after_all_work_items") or {}
    if after_all:
        phase_detail = after_all.get("phase_detail")
        pid = after_all.get("pid")
        heartbeat = after_all.get("heartbeat_at")
        status = after_all.get("status")
        if phase_detail or pid or heartbeat:
            print(f"after_all: status={status} phase={phase_detail or '<unknown>'} pid={pid} heartbeat={heartbeat}")
        process_tree = after_all.get("process_tree") or {}
        top_commands = process_tree.get("top_commands") or []
        if top_commands:
            print("after_all_processes:")
            for command in top_commands[:5]:
                print(f"- {command}")
    state = summary.get("state") or {}
    print(f"run_json: {state.get('run_json')}")
    if server:
        print(f"server: pid={server.get('pid')} alive={server.get('alive')} url={server.get('url')}")


def latest_run_bundle(manifest: Manifest, run_id: str = "") -> Tuple[Path, Dict[str, Any], Dict[str, Any], Dict[str, Any]]:
    if run_id:
        return load_run_by_id(manifest, run_id)
    loaded = load_latest_resumable_run(manifest)
    if loaded is None:
        pointer = read_json(latest_pointer_path(manifest), None)
        if isinstance(pointer, dict) and isinstance(pointer.get("run_id"), str):
            return load_run_by_id(manifest, str(pointer["run_id"]))
        raise SystemExit("No run found for manifest.")
    return loaded


def status_command(manifest: Manifest, run_id: str = "", as_json: bool = False) -> int:
    run_dir, run, subjects, work_items = latest_run_bundle(manifest, run_id)
    del subjects
    summary = run_state_summary(run_dir, run, work_items, manifest.repo_root)
    if as_json:
        print_data(summary)
    else:
        print_status_text(summary)
    return 0


def status_watch_command(manifest: Manifest, run_id: str = "", as_json: bool = False, interval: float = DEFAULT_STATUS_WATCH_SECONDS) -> int:
    last_signature = ""
    while True:
        run_dir, run, subjects, work_items = latest_run_bundle(manifest, run_id)
        del subjects
        summary = run_state_summary(run_dir, run, work_items, manifest.repo_root)
        signature = json.dumps(summary.get("work_item_summary"), sort_keys=True) + str(summary.get("status")) + json.dumps(summary.get("active_work_items"), sort_keys=True)
        if signature != last_signature:
            if as_json:
                print_data(summary)
            else:
                print_status_text(summary)
                print("---")
            last_signature = signature
        if run.get("status") in {"completed", "failed", "cancelled"}:
            return 0
        time.sleep(max(0.2, interval))


def update_control(run_dir: Path, requested: str) -> None:
    write_json(control_path(run_dir), {"requested": requested, "updated_at": utc_now()})


def load_control(run_dir: Path) -> Dict[str, Any]:
    data = read_json(control_path(run_dir), None)
    if not isinstance(data, dict):
        return {"requested": "continue", "updated_at": None}
    return data


def set_control(manifest: Manifest, requested: str, run_id: str = "") -> int:
    run_dir, run, subjects, work_items = latest_run_bundle(manifest, run_id)
    del subjects, work_items
    update_control(run_dir, requested)
    append_event(run_dir / "events.jsonl", {"time": utc_now(), "event": f"control_{requested}"})
    print_data({
        "run_id": run.get("run_id"),
        "status": run.get("status"),
        "control": requested,
        "control_json": to_display_path(manifest.repo_root, control_path(run_dir)),
    })
    return 0


def refresh_controller_heartbeat(run: Dict[str, Any]) -> None:
    runtime = run.setdefault("runtime", {})
    controller = runtime.setdefault("controller", {})
    now = utc_now()
    controller["heartbeat_at"] = now
    controller["updated_at"] = now


def maybe_emit_controller_snapshot(run_dir: Path, run: Dict[str, Any], work_items: Dict[str, Any], *, force: bool = False) -> None:
    runtime = run.setdefault("runtime", {})
    controller = runtime.setdefault("controller", {})
    now_dt = dt.datetime.now(dt.timezone.utc)
    last = parse_utc(controller.get("last_snapshot_at"))
    if not force and last is not None and (now_dt - last).total_seconds() < CONTROLLER_SNAPSHOT_INTERVAL_SECONDS:
        return
    active_items = []
    for item in work_items.get("items", []):
        if item.get("status") in {"queued", "in_progress"}:
            active_items.append(
                {
                    "work_item_id": item.get("work_item_id"),
                    "status": item.get("status"),
                    "worker_id": item.get("worker_id"),
                    "started_at": item.get("started_at"),
                    "age": elapsed_human(item.get("started_at")),
                }
            )
    after_all = run.get("after_all_work_items") or {}
    snapshot = {
        "time": utc_now(),
        "event": "controller_snapshot",
        "run_status": run.get("status"),
        "phases": (run.get("execution") or {}).get("phases"),
        "work_item_summary": run.get("work_item_summary"),
        "active_work_items": active_items[:5],
        "after_all": {
            "status": after_all.get("status"),
            "phase_detail": after_all.get("phase_detail"),
            "pid": after_all.get("pid"),
            "heartbeat_at": after_all.get("heartbeat_at"),
        } if after_all else None,
    }
    append_event(run_dir / "events.jsonl", snapshot)
    controller["last_snapshot_at"] = snapshot["time"]


def item_lock_paths(item: Dict[str, Any]) -> Set[str]:
    editable = item.get("editable_paths") or []
    if not editable:
        editable = [str(item.get("work_item_id", "") or "")]
    return {str(path) for path in editable if str(path).strip()}


def next_runnable_index(items: List[Dict[str, Any]], locked_paths: Set[str]) -> Optional[int]:
    for index, item in enumerate(items):
        if item.get("status") != "pending":
            continue
        paths = item_lock_paths(item)
        if paths & locked_paths:
            continue
        return index
    return None


def item_result_payload(item: Dict[str, Any], status: str, changed_files: List[str], detail: str, metadata: Dict[str, Any]) -> Dict[str, Any]:
    return {
        "work_item_id": item.get("work_item_id"),
        "status": status,
        "changed_files": changed_files,
        "detail": detail,
        "metadata": metadata,
    }


def run_subject_work(manifest: Manifest, item: Dict[str, Any], subjects: Dict[str, Any], attach_url: str) -> Dict[str, Any]:
    work_subjects = subjects_for_work_item(item, subjects)
    repo_root = manifest.repo_root
    attached = attached_paths_for_work_item(manifest, item, work_subjects)
    editable = editable_paths_for_work_item(manifest, item, work_subjects)
    before = snapshot_paths(editable)
    proc = run_agent_prompt(
        work_item_prompt(manifest, item, work_subjects),
        repo_root,
        files=attached,
        agent_config=manifest.execution.subject_agent,
        attach_url=attach_url,
    )
    combined = (proc.stdout or "") + ("\n" + proc.stderr if proc.stderr else "")
    metadata = {
        "model": manifest.execution.subject_agent.model or default_agent_model() or None,
        "variant": manifest.execution.subject_agent.variant or default_agent_variant() or None,
        "backend": manifest.execution.backend,
        "session_id": None,
    }
    if proc.returncode != 0:
        return item_result_payload(item, "failed", [], tail_text(combined, 10) or f"agent exited with code {proc.returncode}", metadata)
    try:
        result = parse_marked_json_block(combined, EXEC_RESULT_BEGIN, EXEC_RESULT_END, "Subject executor")
    except SystemExit as exc:
        return item_result_payload(item, "failed", [], f"{exc}: {tail_text(combined, 10)}", metadata)

    status = str(result.get("status", "") or "").strip().lower()
    if status not in {"done", "skipped", "failed"}:
        return item_result_payload(item, "failed", [], f"invalid executor status: {status or '<empty>'}", metadata)

    after = snapshot_paths(editable)
    detected = changed_paths_from_snapshots(before, after, repo_root)
    reported = normalize_changed_files(repo_root, result.get("changed_files"))
    changed_files = sorted({*detected, *reported})
    detail = join_detail(str(result.get("summary", "") or ""), str(result.get("notes", "") or "")) or "subject processed"
    return item_result_payload(item, status, changed_files, detail, metadata)


def maybe_pause_or_cancel(run_dir: Path, run: Dict[str, Any], subjects: Dict[str, Any], work_items: Dict[str, Any], active_count: int) -> Optional[int]:
    control = load_control(run_dir)
    requested = str(control.get("requested", "continue") or "continue")
    if requested == "cancel" and active_count == 0:
        run["status"] = "cancelled"
        run.setdefault("execution", {}).setdefault("phases", {})["work_items"] = "cancelled"
        save_run_state(run_dir, run, subjects, work_items)
        append_event(run_dir / "events.jsonl", {"time": utc_now(), "event": "cancelled"})
        return 0
    if requested == "pause" and active_count == 0:
        run["status"] = "paused"
        run.setdefault("execution", {}).setdefault("phases", {})["work_items"] = "paused"
        save_run_state(run_dir, run, subjects, work_items)
        append_event(run_dir / "events.jsonl", {"time": utc_now(), "event": "paused"})
        return 0
    return None


def execute_work_items_parallel(manifest: Manifest, run_dir: Path, run: Dict[str, Any], subjects: Dict[str, Any], work_items: Dict[str, Any], attach_url: str) -> bool:
    items = work_items.get("items", [])
    max_workers = max(1, manifest.execution.subject_agent.parallelism)
    active: Dict[concurrent.futures.Future[Dict[str, Any]], Tuple[int, Set[str]]] = {}
    locked_paths: Set[str] = set()
    worker_serial = 0

    with concurrent.futures.ThreadPoolExecutor(max_workers=max_workers) as executor:
        while True:
            refresh_controller_heartbeat(run)
            refresh_work_item_summary(run, work_items)
            maybe_emit_controller_snapshot(run_dir, run, work_items)
            save_run_state(run_dir, run, subjects, work_items)

            control = load_control(run_dir)
            requested = str(control.get("requested", "continue") or "continue")
            if requested == "cancel" and not active:
                break
            if requested == "pause" and not active:
                break

            while len(active) < max_workers and requested == "continue":
                next_index = next_runnable_index(items, locked_paths)
                if next_index is None:
                    break
                item = items[next_index]
                worker_serial += 1
                item["status"] = "in_progress"
                item["worker_id"] = f"worker-{worker_serial}"
                item["started_at"] = item.get("started_at") or utc_now()
                item["heartbeat_at"] = utc_now()
                item["updated_at"] = utc_now()
                refresh_work_item_summary(run, work_items)
                save_run_state(run_dir, run, subjects, work_items)
                append_event(run_dir / "events.jsonl", {"time": utc_now(), "event": "work_item_started", "work_item_id": item.get("work_item_id"), "kind": item.get("kind"), "worker_id": item.get("worker_id")})
                paths = item_lock_paths(item)
                locked_paths |= paths
                future = executor.submit(run_subject_work, manifest, item, subjects, attach_url)
                active[future] = (next_index, paths)
                requested = str(load_control(run_dir).get("requested", "continue") or "continue")

            if not active:
                if all(item.get("status") in {"done", "skipped", "failed"} for item in items):
                    return True
                outcome = maybe_pause_or_cancel(run_dir, run, subjects, work_items, 0)
                if outcome == 0:
                    return False
                if requested != "continue":
                    return False
                break

            done, _ = concurrent.futures.wait(active.keys(), timeout=1.0, return_when=concurrent.futures.FIRST_COMPLETED)
            for future in done:
                index, paths = active.pop(future)
                locked_paths -= paths
                item = items[index]
                try:
                    result = future.result()
                except Exception as exc:
                    result = item_result_payload(item, "failed", [], f"worker exception: {exc}", {"backend": manifest.execution.backend})
                item["status"] = result["status"]
                item["changed_files"] = result["changed_files"]
                item["detail"] = result["detail"]
                item["validation"]["result"] = "not_run"
                item["finished_at"] = utc_now()
                item["heartbeat_at"] = utc_now()
                item["updated_at"] = utc_now()
                item["session_id"] = (result.get("metadata") or {}).get("session_id")
                item["agent"] = result.get("metadata")
                refresh_work_item_summary(run, work_items)
                save_run_state(run_dir, run, subjects, work_items)
                append_event(
                    run_dir / "events.jsonl",
                    {
                        "time": utc_now(),
                        "event": "work_item_finished",
                        "work_item_id": item.get("work_item_id"),
                        "status": item.get("status"),
                        "changed_files": item.get("changed_files"),
                        "detail": item.get("detail"),
                        "worker_id": item.get("worker_id"),
                    },
                )

        outcome = maybe_pause_or_cancel(run_dir, run, subjects, work_items, len(active))
        if outcome == 0:
            return False
    return all(item.get("status") in {"done", "skipped", "failed"} for item in items)


def finalize_run(run_dir: Path, run: Dict[str, Any], subjects: Dict[str, Any], work_items: Dict[str, Any]) -> Dict[str, Any]:
    refresh_work_item_summary(run, work_items)
    save_run_state(run_dir, run, subjects, work_items)
    append_event(run_dir / "events.jsonl", {"time": utc_now(), "event": run["status"], "summary": run["work_item_summary"]})
    return {
        "campaign_id": run.get("campaign_id"),
        "run_id": run.get("run_id"),
        "status": run.get("status"),
        "plan": run.get("plan", engine_plan()),
        "execution": run.get("execution"),
        "runtime": run.get("runtime"),
        "state": {
            "run": str(run_dir),
            "run_json": str(run_dir / "run.json"),
            "subjects_json": str(run_dir / "subjects.json"),
            "work_items_json": str(run_dir / "work-items.json"),
            "events_jsonl": str(run_dir / "events.jsonl"),
        },
        "work_item_summary": run.get("work_item_summary"),
        "after_all_work_items": run.get("after_all_work_items"),
        "changed_work_items": [item.get("work_item_id") for item in work_items.get("items", []) if item.get("changed_files")],
    }


def run_controller(manifest: Manifest, run_dir: Path, run: Dict[str, Any], subjects: Dict[str, Any], work_items: Dict[str, Any]) -> Dict[str, Any]:
    runtime = run.setdefault("runtime", {})
    controller = runtime.setdefault("controller", {})
    controller["pid"] = os.getpid()
    controller["started_at"] = controller.get("started_at") or utc_now()
    controller["updated_at"] = utc_now()
    controller["heartbeat_at"] = utc_now()
    controller["log_path"] = to_display_path(manifest.repo_root, controller_log_path(run_dir))
    controller.setdefault("last_snapshot_at", None)
    started_server: Optional[StartedServer] = None
    save_run_state(run_dir, run, subjects, work_items)
    attach_url = ""
    try:
        started_server = ensure_server_backend(manifest, run_dir, run)
        if started_server is not None:
            attach_url = started_server.url
            save_run_state(run_dir, run, subjects, work_items)
            append_event(run_dir / "events.jsonl", {"time": utc_now(), "event": "server_started", "url": started_server.url, "pid": started_server.pid})

        for item in work_items.get("items", []):
            if item.get("status") in {"queued", "in_progress"}:
                item["status"] = "pending"
                item["worker_id"] = None

        refresh_work_item_summary(run, work_items)
        run["status"] = "running"
        run.setdefault("execution", {}).setdefault("phases", {})
        if run["execution"]["phases"].get("work_items") != "completed":
            run["execution"]["phases"]["work_items"] = "running"
        save_run_state(run_dir, run, subjects, work_items)
        append_event(run_dir / "events.jsonl", {"time": utc_now(), "event": "resolved", "subject_count": len(subjects.get("selected") or subjects.get("include", [])), "work_item_count": len(work_items.get("items", []))})
        maybe_emit_controller_snapshot(run_dir, run, work_items, force=True)

        completed = execute_work_items_parallel(manifest, run_dir, run, subjects, work_items, attach_url)
        refresh_work_item_summary(run, work_items)

        if run.get("status") in {"paused", "cancelled"}:
            return finalize_run(run_dir, run, subjects, work_items)

        if not completed and run.get("status") in {"paused", "cancelled"}:
            return finalize_run(run_dir, run, subjects, work_items)

        run["execution"]["phases"]["work_items"] = "completed"
        if run["work_item_summary"].get("failed", 0) > 0:
            run["status"] = "failed"
            run["execution"]["phases"]["after_all_work_items"] = "not_run"
            save_run_state(run_dir, run, subjects, work_items)
            append_event(run_dir / "events.jsonl", {"time": utc_now(), "event": "failed", "summary": run["work_item_summary"]})
        elif manifest.execution.has_after_all:
            phase = run["execution"]["phases"].get("after_all_work_items")
            if phase != "completed":
                run["execution"]["phases"]["after_all_work_items"] = "running"
                save_run_state(run_dir, run, subjects, work_items)
                append_event(run_dir / "events.jsonl", {"time": utc_now(), "event": "after_all_work_items_started"})
                status, changed_files, detail, metadata = run_after_all_agent(manifest, run_dir, run, subjects, work_items, attach_url=attach_url)
                run["after_all_work_items"] = {
                    "status": status,
                    "changed_files": changed_files,
                    "detail": detail,
                    "updated_at": utc_now(),
                    "agent": metadata,
                }
                run["execution"]["phases"]["after_all_work_items"] = "completed" if status != "failed" else "failed"
                run["status"] = "completed" if status != "failed" else "failed"
                save_run_state(run_dir, run, subjects, work_items)
                append_event(
                    run_dir / "events.jsonl",
                    {
                        "time": utc_now(),
                        "event": "after_all_work_items_finished",
                        "status": status,
                        "changed_files": changed_files,
                        "detail": detail,
                    },
                )
            else:
                existing = run.get("after_all_work_items") or {}
                run["status"] = "completed" if existing.get("status") != "failed" else "failed"
        else:
            run["execution"]["phases"]["after_all_work_items"] = "not_requested"
            run["status"] = "completed"
    except KeyboardInterrupt:
        run["status"] = "paused"
        if run.setdefault("execution", {}).setdefault("phases", {}).get("work_items") == "running":
            run["execution"]["phases"]["work_items"] = "paused"
        save_run_state(run_dir, run, subjects, work_items)
        append_event(run_dir / "events.jsonl", {"time": utc_now(), "event": "paused"})
        raise SystemExit("Run paused. Resume with the same manifest.")
    except Exception as exc:
        run["status"] = "failed"
        save_run_state(run_dir, run, subjects, work_items)
        append_event(run_dir / "events.jsonl", {"time": utc_now(), "event": "failed", "error": str(exc)})
        raise
    finally:
        if started_server is not None:
            stop_server_backend(started_server, run)
            save_run_state(run_dir, run, subjects, work_items)

    return finalize_run(run_dir, run, subjects, work_items)


def spawn_controller(manifest: Manifest, run_id: str) -> int:
    command = [
        sys.executable,
        str(Path(__file__).resolve()),
        "--repo-root",
        str(manifest.repo_root),
        "controller",
        "--manifest",
        to_display_path(manifest.repo_root, manifest.manifest_path),
        "--run-id",
        run_id,
    ]
    run_dir = run_root_for(manifest, run_id)
    log_path = controller_log_path(run_dir)
    with log_path.open("a", encoding="utf-8") as handle:
        proc = subprocess.Popen(command, cwd=str(manifest.repo_root), stdout=handle, stderr=handle, text=True, start_new_session=True)
    run, subjects, work_items = load_run_bundle(run_dir)
    del subjects, work_items
    runtime = run.setdefault("runtime", {})
    controller = runtime.setdefault("controller", {})
    controller["pid"] = proc.pid
    controller["log_path"] = to_display_path(manifest.repo_root, log_path)
    controller["started_at"] = controller.get("started_at") or utc_now()
    controller["updated_at"] = utc_now()
    runtime["launch_mode"] = "detached"
    save_run_state(run_dir, run, read_json(run_dir / "subjects.json", {}), read_json(run_dir / "work-items.json", {}))
    append_event(run_dir / "events.jsonl", {"time": utc_now(), "event": "controller_spawned", "pid": proc.pid})
    print_data(
        {
            "campaign_id": manifest.campaign_id,
            "run_id": run_id,
            "status": "spawned",
            "launch_mode": "detached",
            "backend": manifest.execution.backend,
            "state": {
                "run": to_display_path(manifest.repo_root, run_dir),
                "run_json": to_display_path(manifest.repo_root, run_dir / "run.json"),
                "events_jsonl": to_display_path(manifest.repo_root, run_dir / "events.jsonl"),
                "controller_log": to_display_path(manifest.repo_root, log_path),
            },
            "server_hint": "Use status --watch while the run is active. In server backend mode you can also attach to the printed server_url once it appears in status.",
        }
    )
    return 0


def execute(manifest: Manifest, execution_policy: ExecutionPolicy, resolution_record: Dict[str, Any], subjects: Dict[str, Any], resolution_work_items: Dict[str, Any], action: str, *, foreground: bool = False) -> int:
    loaded = load_latest_resumable_run(manifest) if action == "resume" else None
    if loaded is None:
        run_dir, run, subjects, work_items = create_run(manifest, resolution_record, subjects, resolution_work_items, execution_policy)
    else:
        run_dir, run, subjects, work_items = loaded
        if not work_items.get("items"):
            work_items = build_run_work_items(resolution_work_items, subjects, execution_policy, manifest)
    runtime = run.setdefault("runtime", {})
    runtime["launch_mode"] = "foreground" if foreground else "detached"
    save_run_state(run_dir, run, subjects, work_items)
    write_json(latest_pointer_path(manifest), {"run_id": run["run_id"], "path": to_display_path(manifest.repo_root, run_dir), "updated_at": utc_now()})
    update_control(run_dir, "continue")
    if not foreground:
        if controller_is_alive(run):
            print_data(
                {
                    "campaign_id": manifest.campaign_id,
                    "run_id": run.get("run_id"),
                    "status": run.get("status"),
                    "launch_mode": "detached",
                    "message": "Controller already running for this run.",
                    "state": {
                        "run": to_display_path(manifest.repo_root, run_dir),
                        "run_json": to_display_path(manifest.repo_root, run_dir / "run.json"),
                        "events_jsonl": to_display_path(manifest.repo_root, run_dir / "events.jsonl"),
                        "controller_log": to_display_path(manifest.repo_root, controller_log_path(run_dir)),
                    },
                }
            )
            return 0
        return spawn_controller(manifest, str(run["run_id"]))
    out = run_controller(manifest, run_dir, run, subjects, work_items)
    print_data(out)
    return 0


def cmd_controller(repo_root: Path, manifest_arg: str, run_id: str) -> int:
    manifest = load_manifest(repo_root, to_abs(repo_root, manifest_arg))
    run_dir, run, subjects, work_items = load_run_by_id(manifest, run_id)
    out = run_controller(manifest, run_dir, run, subjects, work_items)
    print_data(out)
    return 0


def cmd_use(repo_root: Path, manifest_arg: str, action_arg: str, *, foreground: bool = False) -> int:
    manifest_path = to_abs(repo_root, manifest_arg)
    if not manifest_path.exists():
        raise SystemExit(f"Manifest not found: {manifest_path}")

    manifest = load_manifest(repo_root, manifest_path)
    execution_policy = manifest.execution
    action = normalize_action(action_arg)

    if action == "describe":
        return describe(manifest, execution_policy, resolve_targets(manifest))
    if action == "status":
        return status_command(manifest)

    if action == "resume" and load_latest_resumable_run(manifest) is None:
        raise SystemExit("No resumable run found. Run describe, then run.")

    resolution_record, subjects, resolution_work_items = load_current_resolution(manifest)
    return execute(manifest, execution_policy, resolution_record, subjects, resolution_work_items, action, foreground=foreground)


def build_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(description="campaign workflow backend")
    parser.add_argument("--repo-root", default=".", help="repository root")
    sub = parser.add_subparsers(dest="cmd", required=True)

    use_p = sub.add_parser("use", help="use a manifest with an action")
    use_p.add_argument("--manifest", required=True, help="manifest path")
    use_p.add_argument("--action", required=True, help="describe, run, resume, or status")
    use_p.add_argument("--foreground", action="store_true", help="run in the foreground instead of detached mode")
    use_p.set_defaults(func=lambda args, root: cmd_use(root, args.manifest, args.action, foreground=bool(args.foreground)))

    status_p = sub.add_parser("status", help="show run status for a manifest")
    status_p.add_argument("--manifest", required=True, help="manifest path")
    status_p.add_argument("--run-id", default="", help="explicit run id")
    status_p.add_argument("--json", action="store_true", help="print structured JSON")
    status_p.add_argument("--watch", action="store_true", help="watch until the run finishes")
    status_p.add_argument("--interval", type=float, default=DEFAULT_STATUS_WATCH_SECONDS, help="watch poll interval in seconds")
    status_p.set_defaults(func=lambda args, root: status_watch_command(load_manifest(root, to_abs(root, args.manifest)), args.run_id, bool(args.json), args.interval) if args.watch else status_command(load_manifest(root, to_abs(root, args.manifest)), args.run_id, bool(args.json)))

    pause_p = sub.add_parser("pause", help="pause the latest run for a manifest")
    pause_p.add_argument("--manifest", required=True, help="manifest path")
    pause_p.add_argument("--run-id", default="", help="explicit run id")
    pause_p.set_defaults(func=lambda args, root: set_control(load_manifest(root, to_abs(root, args.manifest)), "pause", args.run_id))

    cancel_p = sub.add_parser("cancel", help="cancel the latest run for a manifest")
    cancel_p.add_argument("--manifest", required=True, help="manifest path")
    cancel_p.add_argument("--run-id", default="", help="explicit run id")
    cancel_p.set_defaults(func=lambda args, root: set_control(load_manifest(root, to_abs(root, args.manifest)), "cancel", args.run_id))

    resume_p = sub.add_parser("resume", help="resume a paused run for a manifest")
    resume_p.add_argument("--manifest", required=True, help="manifest path")
    resume_p.add_argument("--foreground", action="store_true", help="run in the foreground instead of detached mode")
    resume_p.set_defaults(func=lambda args, root: cmd_use(root, args.manifest, "resume", foreground=bool(args.foreground)))

    controller_p = sub.add_parser("controller", help="internal detached controller")
    controller_p.add_argument("--manifest", required=True, help="manifest path")
    controller_p.add_argument("--run-id", required=True, help="run id")
    controller_p.set_defaults(func=lambda args, root: cmd_controller(root, args.manifest, args.run_id))

    validate_p = sub.add_parser("validate-manifest", help="validate manifest only")
    validate_p.add_argument("--manifest", required=True, help="manifest path")
    validate_p.set_defaults(func=lambda args, root: (load_manifest(root, to_abs(root, args.manifest)), print("Manifest is valid."), 0)[2])
    return parser


def main(argv: Optional[Sequence[str]] = None) -> int:
    parser = build_parser()
    args = parser.parse_args(argv)
    repo_root = to_abs(Path.cwd(), args.repo_root)
    return int(args.func(args, repo_root))


if __name__ == "__main__":
    sys.exit(main())
