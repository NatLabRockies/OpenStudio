# WaterToAirComponent Status

This note summarizes the current state of the
`src/epmodel/WaterToAirComponent` ModelObject types.

## Current Picture

Broadly speaking, the work now falls into three buckets:

- components that are in good shape and can reasonably be treated as complete
- components that are usable but still have clearly documented gaps
- components that need another engineering pass before they should be considered
  settled

## Components In Good Shape

The following components are in good shape.

### Water Coils

- `CoilHeatingWater`

### Variable-Speed Water-To-Air Heat Pump Coils

- `CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit`
- `CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit`

### Air-To-Water Water Heating Coils

- `CoilWaterHeatingAirToWaterHeatPump`
- `CoilWaterHeatingAirToWaterHeatPumpVariableSpeed`

## Components Usable But Still Have Gaps

The components below are usable, but still have clearly documented gaps.

### Water Coils and User-Defined Coils

- `CoilCoolingWater`
  The main wrapper parity is much better, but controller ownership is still
  inferred from node topology rather than a canonical direct back-reference.
- `CoilUserDefined`
  The public and impl surfaces are closer now, but the remaining child
  resolution and removal story still needs a cleaner final verification pass.

### Equation-Fit Water-To-Air Heat Pump Coils

- `CoilCoolingWaterToAirHeatPumpEquationFit`
  The wrapper itself is in decent shape, but its AFN-equivalent-duct story is
  still best treated as part of a shared family pattern rather than as a fully
  closed local type.
- `CoilHeatingWaterToAirHeatPumpEquationFit`
  The bounded parity slice is stronger now, but canonical `componentType` and
  fuel-type surface is still not exposed on the epmodel type.

## Components Needing Another Engineering Pass

No components currently stand out as clearly needing another engineering pass.
The remaining work is mostly final judgment, shared-support follow-up, or
verification depth rather than obviously broken local type behavior.

## Cross-Cutting Themes

Several issues show up repeatedly.

- Shared `AirflowNetworkDistributionComponentCoil` support matters for the
  equation-fit and variable-speed water-to-air heat pump families.
- Variable-speed families depend on transient speed-data child ownership and
  cleanup behaving correctly across `children()`, `remove()`, and
  `removeAllSpeeds()`.
- SQL-backed autosized results are still not generally available in epmodel, so
  some `autosized*()` accessors remain intentionally partial.
- A number of wrap-up turns were limited by unrelated build or test-environment
  problems, especially SWIG generation failures, stale epmodel test binaries,
  and broader test-target rebuild cost.
