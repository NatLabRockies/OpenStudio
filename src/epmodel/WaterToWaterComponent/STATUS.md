# WaterToWaterComponent Status

This note summarizes the current state of the
`src/epmodel/WaterToWaterComponent` ModelObject types.

## Current Picture

Broadly speaking, the work now falls into three buckets:

- components that are in good shape and can reasonably be treated as complete
- components that are usable but still have clearly documented gaps
- components that need another engineering pass before they should be considered
  settled

## Components In Good Shape

The following components are in good shape.

### Heat Pumps

- `HeatPumpWaterToWaterEquationFitCooling`
- `HeatPumpWaterToWaterEquationFitHeating`
- `HeatPumpPlantLoopEIRCooling`

These now have aligned load/source loop semantics, companion heat-pump handling,
curve relationships, scalar coverage, and focused translator coverage for the
implemented EnergyPlus fields. The remaining `autosized*()` limitations are
documented where they still depend on broader SQL-backed result support.

### Chillers

- `ChillerAbsorptionIndirect`
- `ChillerElectric`
- `ChillerElectricEIR`
- `ChillerElectricReformulatedEIR`
- `ChillerElectricASHRAE205`

These components have their scalar fields, schedule and curve relationships,
loop conveniences, heat-recovery behavior, and translator coverage in good
shape. `ChillerElectric` remains an epmodel type for the direct EnergyPlus
`Chiller:Electric` object rather than a one-to-one canonical model type.
`ChillerElectricASHRAE205` still omits representation-file linkage because
epmodel does not yet expose `ExternalFile`.

### Storage, Water Heating, and Systems

- `ThermalStorageChilledWaterStratified`
- `WaterHeaterMixed`
- `CentralHeatPumpSystem`

These components are in good shape for their current epmodel surface.
`ThermalStorageChilledWaterStratified` still documents the ambient schedule
type difference caused by missing `ScheduleRuleset` support. `WaterHeaterMixed`
now has the outdoor-air-node fallback translation path covered. `CentralHeatPumpSystem`
has aligned three-loop routing and loop convenience behavior; module-list
support remains unavailable because the related epmodel object families do not
exist yet.

## Components Usable But Still Have Gaps

The components below are usable, but still have clearly documented gaps.

- `ChillerAbsorption`
  The component itself is close to canonical behavior, including generator-loop
  routing and SQL-backed autosized helper support. The campaign review still
  found a cross-platform test cleanup issue around temporary SQLite file
  lifetime, and fresh runtime verification was limited by the workspace build
  state.
- `HeatPumpPlantLoopEIRHeating`
  The component behavior appears aligned with the canonical heating-side
  plant-loop heat pump surface. The campaign did not identify a local component
  defect, but signoff was blocked because the available epmodel test binary was
  stale and the EnergyPlus test binary failed at startup in this workspace.

## Components Needing Another Engineering Pass

The components below still need another engineering pass before they should be
considered settled.

- `HeatExchangerFluidToFluid`
  Field-level behavior and translator mapping are in good shape, but the
  advertised secondary-loop classification and fuel delegation cannot fully work
  until shared epmodel loop support reports real component types and fuel types.
  The header note should not claim closure for that delegated path until the
  shared loop layer supports it.
- `WaterHeaterStratified`
  WaterHeaterSizing reattachment improved, but cross-model `clone(Model)` still
  does not match canonical deep-clone behavior for referenced schedules and
  related objects. The header note currently reads more complete than the
  campaign review supports.

## Cross-Cutting Themes

Several issues show up repeatedly.

- The shared `WaterToWaterComponent` topology layer is central to this family.
  Most components depend on it for two-loop and three-loop attachment,
  removal, and loop convenience behavior.
- SQL-backed autosized results are now available for some water-to-water
  surfaces, but support is still uneven. Components that only expose stubbed
  `autosized*()` helpers should continue to document that limit directly.
- Some remaining limitations are not local component bugs. Missing epmodel
  support for `ExternalFile`, `ScheduleRuleset`, `CentralHeatPumpSystemModule`,
  `ModelObjectList`, and shared loop fuel/type aggregation prevents full
  parity for a few components.
- Several campaign reviews were limited by workspace build and test-binary
  state. Those limitations affect verification confidence, not necessarily the
  component implementation itself.
