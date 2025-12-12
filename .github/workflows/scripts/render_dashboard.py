#!/usr/bin/env python3
"""Render a markdown summary from CTest JUnit XML results."""

from __future__ import annotations

import glob
import sys
from collections import defaultdict
from datetime import datetime
from pathlib import Path
import xml.etree.ElementTree as ET


def collect_results(test_dir: Path) -> tuple[list[Path], dict[str, int], list[dict[str, str]]]:
    xml_files = sorted(test_dir.glob("run*/results.xml"))
    totals = defaultdict(int)
    failures = []

    for xml_path in xml_files:
        if not xml_path.exists():
            continue
        try:
            tree = ET.parse(xml_path)
        except ET.ParseError:
            continue
        root = tree.getroot()
        suites = root.findall("testsuite") if root.tag == "testsuites" else [root]
        for suite in suites:
            totals["tests"] += int(suite.get("tests", 0))
            totals["failures"] += int(suite.get("failures", 0))
            totals["errors"] += int(suite.get("errors", 0))
            totals["skipped"] += int(suite.get("skipped", 0))
            for case in suite.findall("testcase"):
                failure = case.find("failure") or case.find("error")
                if failure is None:
                    continue
                failures.append(
                    {
                        "suite": suite.get("name", "unknown"),
                        "classname": case.get("classname", "unknown"),
                        "name": case.get("name", "unknown"),
                        "message": (failure.get("message", "") or "").strip(),
                        "details": (failure.text or "").strip(),
                        "run": xml_path.parent.name,
                    }
                )
    return xml_files, totals, failures


def write_dashboard(test_dir: Path, xml_files: list[Path], totals: dict[str, int], failures: list[dict[str, str]]):
    dashboard_dir = test_dir / "dashboard"
    dashboard_dir.mkdir(parents=True, exist_ok=True)
    output = dashboard_dir / "test-dashboard.md"

    total_tests = totals.get("tests", 0)
    success_count = total_tests - totals.get("failures", 0) - totals.get("errors", 0)
    success_rate = (success_count / total_tests * 100.0) if total_tests else 0.0

    lines = []
    lines.append("# Test Results Dashboard\n")
    lines.append("| Metric | Value |\n")
    lines.append("|--------|-------|\n")
    lines.append(f"| Total Tests | {total_tests} |\n")
    lines.append(f"| Passed | {success_count} |\n")
    lines.append(f"| Failed | {totals.get('failures', 0)} |\n")
    lines.append(f"| Errors | {totals.get('errors', 0)} |\n")
    lines.append(f"| Skipped | {totals.get('skipped', 0)} |\n")
    lines.append(f"| Success Rate | {success_rate:.1f}% |\n")
    lines.append(f"| Generated | {datetime.utcnow().strftime('%Y-%m-%d %H:%M:%S UTC')} |\n\n")

    if failures:
        lines.append(f"## Failed Tests ({len(failures)})\n\n")
        for failure in failures:
            lines.append("<details>\n")
            lines.append(
                f"<summary><strong>{failure['classname']}.{failure['name']}</strong> ({failure['run']})</summary>\n\n"
            )
            if failure["message"]:
                lines.append("**Message:**\n")
                lines.append("````\n" + failure["message"] + "\n````\n\n")
            if failure["details"]:
                lines.append("**Details:**\n")
                lines.append("````\n" + failure["details"] + "\n````\n\n")
            lines.append("</details>\n\n")
    else:
        lines.append("## All Tests Passed\n\n")

    lines.append("## Test Runs\n\n")
    lines.append("| Run | XML File | Status |\n")
    lines.append("|-----|----------|--------|\n")
    if xml_files:
        for xml_path in xml_files:
            run_name = xml_path.parent.name
            lines.append(f"| {run_name} | `{xml_path.name}` | Present |\n")
    else:
        lines.append("| - | No XML files | Missing |\n")

    output.write_text("".join(lines), encoding="utf-8")


def main(argv: list[str]) -> int:
    test_dir = Path(argv[1]) if len(argv) > 1 else Path("Testing")
    xml_files, totals, failures = collect_results(test_dir)
    write_dashboard(test_dir, xml_files, totals, failures)
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
