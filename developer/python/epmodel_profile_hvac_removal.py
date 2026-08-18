#!/usr/bin/env python3

"""Measure EPModel load and owner-level HVAC removal time for one EnergyPlus file."""

from __future__ import annotations

import argparse
import json
import time
from dataclasses import asdict, dataclass
from pathlib import Path

import openstudio


@dataclass
class Timing:
    phase: str
    name: str
    seconds: float
    removed_objects: int
    success: bool


def timed_remove(phase: str, owners) -> tuple[list[Timing], bool]:
    timings = []
    for owner in list(owners):
        name = owner.nameString()
        started = time.perf_counter()
        removed = owner.remove()
        elapsed = time.perf_counter() - started
        timing = Timing(phase, name, elapsed, len(removed), bool(removed))
        timings.append(timing)
        print(
            f"{phase:10} {elapsed:9.3f}s removed={len(removed):5} success={bool(removed)!s:5} {name}",
            flush=True,
        )
        if not removed:
            return timings, False
    return timings, True


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("seed", type=Path)
    parser.add_argument("--output", type=Path)
    args = parser.parse_args()

    seed = args.seed.resolve()
    load_started = time.perf_counter()
    optional_model = openstudio.epmodel.Model.load(seed)
    load_seconds = time.perf_counter() - load_started
    if not optional_model:
        print(f"Failed to load {seed}")
        return 1
    model = optional_model.get()
    print(f"load       {load_seconds:9.3f}s objects={model.numObjects():5} {seed.name}", flush=True)

    timings = []
    succeeded = True
    for phase, owners in (
        ("air_loop", model.getAirLoopHVACs()),
        ("zone_hvac", model.getZoneHVACComponents()),
        ("plant_loop", model.getPlantLoops()),
    ):
        phase_timings, succeeded = timed_remove(phase, owners)
        timings.extend(phase_timings)
        if not succeeded:
            break

    report = {
        "seed": str(seed),
        "load_seconds": load_seconds,
        "timings": [asdict(timing) for timing in timings],
        "remaining": {
            "air_loops": len(model.getAirLoopHVACs()),
            "zone_hvac": len(model.getZoneHVACComponents()),
            "plant_loops": len(model.getPlantLoops()),
        },
    }
    if args.output:
        args.output.parent.mkdir(parents=True, exist_ok=True)
        args.output.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    return 0 if succeeded else 1


if __name__ == "__main__":
    raise SystemExit(main())
