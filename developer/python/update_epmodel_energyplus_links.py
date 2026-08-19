#!/usr/bin/env python3
"""Update EPModel class documentation links from the EnergyPlus object index."""

from __future__ import annotations

import argparse
import html
import re
import urllib.request
from html.parser import HTMLParser
from pathlib import Path

from check_epmodel_docs import ROOT, expand_paths


CMAKE = ROOT / "CMakeLists.txt"
SECTION_RE = re.compile(
    r"(?P<head>\\par EnergyPlus object\s*)(?P<body>.*?)(?=\n\s*\*\s*\\par |\*/)",
    re.DOTALL,
)
EPOBJECT_RE = re.compile(r"\\epobject\{[^,{}]+,(?P<name>[^{}]+)\}")
HTML_CODE_RE = re.compile(r"<code>(?P<name>[^<]+)</code>")
MARKDOWN_CODE_RE = re.compile(r"`(?P<name>[^`\n]+)`")


def energyplus_doc_version() -> str:
    text = CMAKE.read_text(encoding="utf-8")

    def value(name: str) -> str:
        match = re.search(rf"set\({name}\s+(\d+)\)", text)
        if match is None:
            raise RuntimeError(f"Cannot find {name} in {CMAKE}")
        return match.group(1)

    return f"{value('ENERGYPLUS_VERSION_MAJOR')}-{value('ENERGYPLUS_VERSION_MINOR')}"


class ObjectIndexParser(HTMLParser):
    def __init__(self) -> None:
        super().__init__()
        self.current_href: str | None = None
        self.current_text: list[str] = []
        self.links: dict[str, str] = {}

    def handle_starttag(self, tag: str, attrs: list[tuple[str, str | None]]) -> None:
        if tag != "a":
            return
        href = dict(attrs).get("href")
        if href and "/input-output-reference/" in href:
            self.current_href = href
            self.current_text = []

    def handle_data(self, data: str) -> None:
        if self.current_href is not None:
            self.current_text.append(data)

    def handle_endtag(self, tag: str) -> None:
        if tag != "a" or self.current_href is None:
            return
        name = html.unescape("".join(self.current_text)).strip()
        target = self.current_href.split("/input-output-reference/", 1)[1]
        if name and target:
            self.links[name] = target
        self.current_href = None
        self.current_text = []


def load_links(source: str | None, version: str) -> tuple[dict[str, str], str]:
    url = f"https://bigladdersoftware.com/epx/docs/{version}/input-output-reference/object-index.html"
    if source:
        text = Path(source).read_text(encoding="utf-8")
        origin = str(Path(source))
    else:
        with urllib.request.urlopen(url) as response:  # noqa: S310 - fixed HTTPS origin
            text = response.read().decode("utf-8")
        origin = url

    parser = ObjectIndexParser()
    parser.feed(text)
    if not parser.links:
        raise RuntimeError(f"No EnergyPlus object links found in {origin}")
    return parser.links, origin


def epobject(name: str, links: dict[str, str]) -> str | None:
    target = links.get(name)
    return rf"\epobject{{{target},{name}}}" if target else None


def update_section(body: str, links: dict[str, str]) -> tuple[str, int]:
    changes = 0

    def replace_existing(match: re.Match[str]) -> str:
        nonlocal changes
        replacement = epobject(match.group("name"), links)
        if replacement is not None and replacement != match.group(0):
            changes += 1
            return replacement
        return match.group(0)

    def replace_code(match: re.Match[str]) -> str:
        nonlocal changes
        replacement = epobject(match.group("name"), links)
        if replacement is not None:
            changes += 1
            return replacement
        return match.group(0)

    body = EPOBJECT_RE.sub(replace_existing, body)
    body = HTML_CODE_RE.sub(replace_code, body)
    body = MARKDOWN_CODE_RE.sub(replace_code, body)
    return body, changes


def update_file(path: Path, links: dict[str, str]) -> tuple[str, int]:
    text = path.read_text(encoding="utf-8")
    changes = 0

    def replace_section(match: re.Match[str]) -> str:
        nonlocal changes
        body, section_changes = update_section(match.group("body"), links)
        changes += section_changes
        return match.group("head") + body

    return SECTION_RE.sub(replace_section, text), changes


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--object-index", help="use a downloaded EnergyPlus object-index.html")
    parser.add_argument("--write", action="store_true", help="write updated public headers")
    args = parser.parse_args()

    version = energyplus_doc_version()
    links, origin = load_links(args.object_index, version)
    changed_files = 0
    changed_links = 0
    for path in expand_paths([]):
        updated, changes = update_file(path, links)
        if changes:
            changed_files += 1
            changed_links += changes
            if args.write:
                path.write_text(updated, encoding="utf-8")

    action = "Updated" if args.write else "Would update"
    print(f"{action} {changed_links} EnergyPlus links in {changed_files} headers using {origin}.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
