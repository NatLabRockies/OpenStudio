#!/usr/bin/env python3

"""Run the packaged EPModel HVAC measures against the DOE reference buildings."""

from __future__ import annotations

import argparse
import concurrent.futures
import datetime as dt
import json
import re
import subprocess
import time
from dataclasses import asdict, dataclass
from pathlib import Path


SYSTEM_MEASURES = {
    "ideal_loads": "EpModelAddIdealLoads",
    "packaged_unitary": "EpModelAddPackagedUnitarySystems",
    "multizone_vav": "EpModelAddMultizoneVAVSystem",
    "packaged_terminal_heat_pumps": "EpModelAddPackagedTerminalHeatPumps",
    "four_pipe_fan_coils": "EpModelAddFourPipeFanCoils",
}

REFERENCE_PATTERN = re.compile(r"^RefBldg(.+)New2004_Chicago\.idf$")
ERROR_SUMMARY_PATTERN = re.compile(r"Completed Successfully--\s*(\d+) Warning;\s*(\d+) Severe Errors")


@dataclass
class Result:
    building: str
    system: str
    status: str
    elapsed_seconds: float
    warnings: int | None = None
    severe_errors: int | None = None
    detail: str = ""
    output_directory: str = ""


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--openstudio", type=Path, default=Path("build/Products/openstudio"))
    parser.add_argument("--energyplus-dir", type=Path)
    parser.add_argument("--measures-dir", type=Path, default=Path("resources/Examples/epmodel/measures"))
    parser.add_argument("--output-dir", type=Path, default=Path("build/epmodel-reference-matrix"))
    parser.add_argument("--systems", default=",".join(SYSTEM_MEASURES), help="Comma-separated system keys")
    parser.add_argument("--buildings", default="", help="Comma-separated building names or substrings")
    parser.add_argument("--jobs", type=int, default=4)
    parser.add_argument("--timeout", type=int, default=600, help="Per-workflow timeout in seconds")
    return parser.parse_args()


def find_energyplus_dir(build_dir: Path) -> Path:
    candidates = sorted(build_dir.glob("EnergyPlus-*/ExampleFiles/RefBldgSmallOfficeNew2004_Chicago.idf"))
    if len(candidates) != 1:
        raise RuntimeError(f"Expected one configured EnergyPlus distribution under {build_dir}, found {len(candidates)}")
    return candidates[0].parent.parent


def selected_reference_buildings(example_files: Path, selectors: list[str]) -> list[tuple[str, Path]]:
    buildings = []
    for path in sorted(example_files.glob("RefBldg*New2004_Chicago.idf")):
        match = REFERENCE_PATTERN.match(path.name)
        if not match:
            continue
        name = match.group(1)
        if selectors and not any(selector.casefold() in name.casefold() for selector in selectors):
            continue
        buildings.append((name, path.resolve()))
    return buildings


def run_workflow(
    openstudio: Path,
    measures_dir: Path,
    weather_file: Path,
    output_root: Path,
    timeout: int,
    building: str,
    seed_file: Path,
    system: str,
) -> Result:
    task_dir = output_root / building / system
    task_dir.mkdir(parents=True, exist_ok=True)
    workflow_path = task_dir / "workflow.osw"
    workflow = {
        "weather_file": str(weather_file),
        "seed_file": str(seed_file),
        "steps": [
            {"measure_dir_name": "EpModelRemoveAllHVACSystems", "arguments": {}},
            {"measure_dir_name": SYSTEM_MEASURES[system], "arguments": {}},
            {"measure_dir_name": "EpModelConfigureShortWeatherRun", "arguments": {}},
        ],
        "measure_paths": [str(measures_dir)],
    }
    workflow_path.write_text(json.dumps(workflow, indent=2) + "\n", encoding="utf-8")

    started = time.monotonic()
    try:
        process = subprocess.run(
            [str(openstudio), "run", "-w", str(workflow_path)],
            cwd=task_dir,
            text=True,
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
            timeout=timeout,
            check=False,
        )
    except subprocess.TimeoutExpired as error:
        elapsed = time.monotonic() - started
        output = error.stdout or ""
        if isinstance(output, bytes):
            output = output.decode(errors="replace")
        (task_dir / "console.log").write_text(output, encoding="utf-8")
        return Result(building, system, "Timeout", elapsed, detail=f"Exceeded {timeout} seconds", output_directory=str(task_dir))

    elapsed = time.monotonic() - started
    (task_dir / "console.log").write_text(process.stdout, encoding="utf-8")
    out_osw_path = task_dir / "out.osw"
    if not out_osw_path.exists():
        return Result(building, system, "Fail", elapsed, detail=f"CLI exit code {process.returncode}; no out.osw", output_directory=str(task_dir))

    out_osw = json.loads(out_osw_path.read_text(encoding="utf-8"))
    status = out_osw.get("completed_status", "Unknown")
    eplus_error = out_osw.get("eplusout_err", "")
    summary = ERROR_SUMMARY_PATTERN.search(eplus_error)
    warnings = int(summary.group(1)) if summary else None
    severe_errors = int(summary.group(2)) if summary else None
    detail = "" if process.returncode == 0 else f"CLI exit code {process.returncode}"
    if status == "Success" and severe_errors not in (None, 0):
        status = "Severe"
        detail = f"EnergyPlus reported {severe_errors} severe errors"
    return Result(building, system, status, elapsed, warnings, severe_errors, detail, str(task_dir))


def main() -> int:
    args = parse_args()
    repo = Path.cwd().resolve()
    openstudio = (repo / args.openstudio).resolve() if not args.openstudio.is_absolute() else args.openstudio.resolve()
    measures_dir = (repo / args.measures_dir).resolve() if not args.measures_dir.is_absolute() else args.measures_dir.resolve()
    output_root = (repo / args.output_dir).resolve() if not args.output_dir.is_absolute() else args.output_dir.resolve()
    energyplus_dir = args.energyplus_dir.resolve() if args.energyplus_dir else find_energyplus_dir(openstudio.parent.parent)
    weather_file = (energyplus_dir / "WeatherData/USA_IL_Chicago-OHare.Intl.AP.725300_TMY3.epw").resolve()

    systems = [value.strip() for value in args.systems.split(",") if value.strip()]
    unknown_systems = sorted(set(systems) - set(SYSTEM_MEASURES))
    if unknown_systems:
        raise RuntimeError(f"Unknown systems: {', '.join(unknown_systems)}")
    selectors = [value.strip() for value in args.buildings.split(",") if value.strip()]
    buildings = selected_reference_buildings(energyplus_dir / "ExampleFiles", selectors)
    if not buildings:
        raise RuntimeError("No reference buildings matched")

    output_root.mkdir(parents=True, exist_ok=True)
    tasks = [(building, seed, system) for building, seed in buildings for system in systems]
    results: list[Result] = []
    with concurrent.futures.ThreadPoolExecutor(max_workers=args.jobs) as executor:
        futures = {
            executor.submit(
                run_workflow,
                openstudio,
                measures_dir,
                weather_file,
                output_root,
                args.timeout,
                building,
                seed,
                system,
            ): (building, system)
            for building, seed, system in tasks
        }
        for future in concurrent.futures.as_completed(futures):
            result = future.result()
            results.append(result)
            print(
                f"{result.status:8} {result.building:24} {result.system:34} "
                f"{result.elapsed_seconds:7.1f}s warnings={result.warnings} severe={result.severe_errors}",
                flush=True,
            )

    results.sort(key=lambda item: (item.building, item.system))
    report = {
        "generated_at": dt.datetime.now(dt.timezone.utc).isoformat(),
        "openstudio": str(openstudio),
        "energyplus_dir": str(energyplus_dir),
        "results": [asdict(result) for result in results],
    }
    (output_root / "summary.json").write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    failures = [result for result in results if result.status != "Success" or result.severe_errors not in (None, 0)]
    print(f"Completed {len(results)} workflows with {len(failures)} failures. Summary: {output_root / 'summary.json'}")
    return 1 if failures else 0


if __name__ == "__main__":
    raise SystemExit(main())
