#!/usr/bin/env python3
"""Generate a Doxygen class index that mirrors the EPModel source tree."""

from __future__ import annotations

import argparse
import re
from collections import defaultdict
from pathlib import Path

from check_epmodel_docs import EPMODEL, expand_paths, scan


TOP_LEVEL = "Top level"


def family_for(path: Path) -> str:
    relative = path.relative_to(EPMODEL)
    return relative.parts[0] if len(relative.parts) > 1 else TOP_LEVEL


def anchor_for(family: str) -> str:
    return "epmodel_family_" + re.sub(r"[^a-z0-9]+", "_", family.lower()).strip("_")


def type_reference(name: str) -> str:
    return rf'\ref openstudio::epmodel::{name} "{name}"'


def render(output: Path) -> None:
    families: dict[str, list[str]] = defaultdict(list)
    for path in expand_paths([]):
        for item in scan(path):
            families[family_for(path)].append(item.name)

    ordered_families = sorted(families, key=lambda value: (value != TOP_LEVEL, value.casefold()))
    lines = [
        "/** \\page epmodel_class_families EPModel Classes",
        " *",
        " * The classes below follow the existing EPModel source-tree organization.",
        " * Directory names usually identify a shared base class or an established API",
        " * family. This is a browsing aid, not a separate type hierarchy; each class",
        " * declaration is authoritative about its C++ inheritance.",
        " *",
        " * **Jump to:** "
        + " &middot; ".join(rf'\ref {anchor_for(family)} "{family}"' for family in ordered_families),
        " *",
    ]

    for family in ordered_families:
        lines.extend(
            [
                rf" * \section {anchor_for(family)} {family}",
                " *",
                ' * <table class="table table-condensed table-striped">',
            ]
        )
        names = sorted(families[family], key=lambda name: (name != family, name.casefold()))
        for index in range(0, len(names), 2):
            left = type_reference(names[index])
            right = type_reference(names[index + 1]) if index + 1 < len(names) else ""
            lines.append(rf" * <tr><td>{left}</td><td>{right}</td></tr>")
        lines.extend([" * </table>", " *"])

    lines.append(" */")
    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_text("\n".join(lines) + "\n", encoding="utf-8")


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--output", type=Path, required=True, help="generated Doxygen header")
    args = parser.parse_args()
    render(args.output.resolve())
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
