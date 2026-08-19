#!/usr/bin/env python3
"""Inventory and validate public EPModel type documentation.

This intentionally checks structure, not truth. API and behavior claims still
require comparison with Model, implementations, tests, translators, and the
EnergyPlus IDD.
"""

from __future__ import annotations

import argparse
import re
import sys
from dataclasses import dataclass
from pathlib import Path


ROOT = Path(__file__).resolve().parents[2]
EPMODEL = ROOT / "src" / "epmodel"

CLASS_RE = re.compile(r"\b(?:class|struct)\s+EPMODEL_API\s+([A-Za-z_]\w*)\b")
DOCUMENTED_CLASS_RE = re.compile(
    r"(?P<doc>/\*\*.*?\*/)[ \t\r\n]*"
    r"(?:class|struct)\s+EPMODEL_API\s+(?P<name>[A-Za-z_]\w*)\b",
    re.DOTALL,
)

REQUIRED_MARKERS = (
    r"\brief",
    r"\par EnergyPlus object",
    r"\par OpenStudio Model API",
    r"\par Known limitations",
)

FORBIDDEN_PUBLIC_TERMS = (
    "Schema Alignment Notes",
    "Canonical Counterpart",
    "Implemented Parity",
    "Remaining Parity Work",
    "Partial Parity",
    "Near Parity",
    "Scalar Parity",
    "Scaffolded",
    "transient or value wrapper used by the corresponding parent or topology type",
)


@dataclass(frozen=True)
class ClassDoc:
    path: Path
    name: str
    line: int
    doc: str | None
    source: str

    @property
    def relative_path(self) -> Path:
        return self.path.relative_to(ROOT)


def eligible(path: Path) -> bool:
    relative = path.relative_to(EPMODEL)
    return (
        path.suffix == ".hpp"
        and not path.name.endswith("_Impl.hpp")
        and "scaffolds" not in relative.parts
        and "test" not in relative.parts
    )


def expand_paths(values: list[str]) -> list[Path]:
    if not values:
        return sorted(path for path in EPMODEL.rglob("*.hpp") if eligible(path))

    result: set[Path] = set()
    for value in values:
        path = Path(value)
        if not path.is_absolute():
            path = ROOT / path
        path = path.resolve()
        if path.is_dir():
            result.update(
                candidate for candidate in path.rglob("*.hpp") if candidate.is_relative_to(EPMODEL) and eligible(candidate)
            )
        elif path.is_file() and path.is_relative_to(EPMODEL) and eligible(path):
            result.add(path)
        else:
            raise ValueError(f"Not an eligible EPModel public header: {value}")
    return sorted(result)


def scan(path: Path) -> list[ClassDoc]:
    text = path.read_text(encoding="utf-8")
    attached = {match.start("name"): match.group("doc") for match in DOCUMENTED_CLASS_RE.finditer(text)}
    result = []
    for match in CLASS_RE.finditer(text):
        result.append(
            ClassDoc(
                path=path,
                name=match.group(1),
                line=text.count("\n", 0, match.start()) + 1,
                doc=attached.get(match.start(1)),
                source=text,
            )
        )
    return result


def problems(item: ClassDoc) -> list[str]:
    if item.doc is None:
        return ["missing an immediately preceding type-level Doxygen comment"]

    result = []
    if "Schema Alignment Notes" in item.source:
        result.append("still contains a legacy Schema Alignment Notes block")
    for marker in REQUIRED_MARKERS:
        if marker not in item.doc:
            result.append(f"missing '{marker}'")
    for term in FORBIDDEN_PUBLIC_TERMS:
        if term.lower() in item.doc.lower():
            result.append(f"contains internal campaign term '{term}'")
    if "IddObjectType::" in item.doc:
        result.append("repeats an IddObjectType enum in user-facing documentation")
    return result


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "paths", nargs="*", help="EPModel public headers or directories; defaults to all public headers"
    )
    parser.add_argument(
        "--inventory", action="store_true", help="print one tab-separated row per public type"
    )
    parser.add_argument("--strict", action="store_true", help="return a failing exit code when documentation is incomplete")
    args = parser.parse_args()

    try:
        paths = expand_paths(args.paths)
    except ValueError as error:
        parser.error(str(error))

    classes = [item for path in paths for item in scan(path)]
    invalid = [(item, problems(item)) for item in classes]
    invalid = [(item, issues) for item, issues in invalid if issues]

    if args.inventory:
        invalid_names = {(item.path, item.name) for item, _ in invalid}
        for item in classes:
            state = "needs-review" if (item.path, item.name) in invalid_names else "formatted"
            print(f"{state}\t{item.relative_path}\t{item.line}\t{item.name}")
    else:
        for item, issues in invalid:
            for issue in issues:
                print(f"{item.relative_path}:{item.line}: {item.name}: {issue}")

    formatted = len(classes) - len(invalid)
    print(
        f"EPModel documentation: {formatted}/{len(classes)} public types use the agreed structure; "
        f"{len(invalid)} need review.",
        file=sys.stderr,
    )
    return 1 if args.strict and invalid else 0


if __name__ == "__main__":
    raise SystemExit(main())
