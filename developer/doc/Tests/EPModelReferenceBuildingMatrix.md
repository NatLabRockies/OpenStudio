# EPModel reference building test results

## Scope

This test pass used the 16 DOE `New2004_Chicago` reference buildings bundled with EnergyPlus 26.1.0. Each workflow loaded the reference IDF, removed its HVAC, added one of the packaged EPModel example systems, configured a July 21–27 weather run, and ran EnergyPlus.

The repeatable runner is `developer/python/epmodel_reference_building_matrix.py`. Results are classified as failures when the workflow fails, times out, or EnergyPlus reports any severe errors.

## HVAC removal performance

The OutPatient building exposed a removal performance problem before EnergyPlus was started. Its first large air loop originally took more than four minutes to remove, and the complete workflow exceeded a ten-minute timeout.

Profiling showed that removal repeatedly scanned the whole model to rediscover component owners and prove that demand-side branches did not belong to other loops. After replacing those scans with reverse-reference and cached-topology lookups, the same workflow measured:

| Operation | Time |
| --- | ---: |
| Load the reference IDF | 4.7 s |
| Remove the 41-zone air loop | 50.4 s |
| Remove the 45-zone air loop | 14.4 s |
| Remove remaining zone and plant HVAC | less than 0.2 s |
| Complete ideal-load workflow | 132.6 s |

Removal is therefore still material for this large building, but it no longer prevents the example from running. The committed profiler can time load, owner discovery, zone discovery, and removal independently.

## Ideal-load results

The initial full matrix completed 11 of 16 buildings without severe errors. A typed repair for refrigeration cases made FullServiceRestaurant pass, bringing the current result to 12 of 16.

| Result | Reference buildings |
| --- | --- |
| Pass | FullServiceRestaurant, MediumOffice, MidriseApartment, OutPatient, PrimarySchool, QuickServiceRestaurant, SmallHotel, SmallOffice, Stand-aloneRetail, StripMall, SuperMarket, Warehouse |
| Removal rejected | Hospital, LargeHotel, LargeOffice, SecondarySchool |

The four rejected buildings contain multiple specialized chillers on `CoolSys1` together with legacy condenser-loop objects that are not yet represented as typed EPModel loops. Plant-loop removal correctly remains atomic instead of deleting only part of this ownership graph. Supporting these files needs a deliberate condenser-loop and multi-chiller ownership implementation; the example measure should not bypass that boundary with raw object deletion.

## Other system results

The first pass ran packaged unitary, multizone VAV, packaged terminal heat pump, and four-pipe fan coil workflows against the 12 buildings that passed the plant-removal boundary. This was 48 additional simulations.

That pass found two general ownership defects:

- Unit heaters left their owned fans and coils behind. This caused six severe errors in MidriseApartment and two each in Stand-aloneRetail and Warehouse for every replacement family. EPModel now matches canonical Model ownership, and focused reruns of the fan-coil workflow pass all three buildings with zero severe errors.
- PTACs and PTHPs also left their owned fans and coils behind. SmallHotel consequently produced 102 severe errors with fan coils and VAV. EPModel now removes those children with their parent. The SmallHotel fan-coil and VAV reruns both pass with zero severe errors.

Additional current findings:

- The SmallHotel PTHP workflow has a separate EnergyPlus sizing failure for a zero-load zone: EnergyPlus cannot determine the fan airflow for PTHP 13.
- OutPatient VAV and PTHP reported one and two warmup-convergence severe errors respectively and still need focused diagnosis.
- The packaged-unitary measure initially autosized the outdoor-air controller minimum flow instead of using canonical Model's zero minimum. That fixed minimum fought the mechanical-ventilation request and produced tens of thousands of recurring warnings. Restoring the canonical value reduced FullServiceRestaurant from 51,503 warnings to 11, MediumOffice from 325,596 warnings and two severe errors to 35 warnings and zero severe errors, and PrimarySchool from 411,942 warnings to 54.
- PrimarySchool packaged unitary now exposes six warmup-convergence severe errors after the outdoor-air correction. OutPatient still exceeds ten minutes because EnergyPlus spends several minutes sizing and warming up its many single-zone systems, rather than because it is printing the former warning storm.

## Other defects found and fixed

- Removing HVAC from FullServiceRestaurant left refrigerated cases configured to return under-case air to a removed HVAC node. The removal measure now uses typed refrigeration APIs to set that return fraction to zero.
- Pump power was omitted from the VAV and four-pipe fan-coil examples. Their variable-speed pumps now autosize rated power consumption.
- Imported duplicate `PlantEquipmentList` rows are canonicalized on load. Resolved rows have their type and name repaired before duplicates are removed, so the first malformed row cannot displace a later coherent row.
- The matrix runner now labels a completed workflow with EnergyPlus severe errors as `Severe` instead of printing the misleading `Success` status from the OSW alone.

## Reproduction

Run all ideal-load cases from the repository root:

```sh
python3 developer/python/epmodel_reference_building_matrix.py \
  --energyplus-dir build/EnergyPlus-26.1.0-6f2e40d102-Linux-Ubuntu24.04-x86_64 \
  --measures-dir build/resources/Examples/epmodel/measures \
  --systems ideal_loads \
  --output-dir build/epmodel-reference-matrix-ideal \
  --jobs 4 --timeout 600
```

Use `--buildings SmallHotel,OutPatient` or a narrower `--systems` list for focused reruns. Each output directory retains the OSW, console log, EnergyPlus files, elapsed time, warning count, and severe-error count. Generated matrix artifacts remain under `build/` and are not committed.
