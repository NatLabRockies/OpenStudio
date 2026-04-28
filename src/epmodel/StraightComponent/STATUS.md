# StraightComponent Status

This note summarizes the current state of the
`src/epmodel/StraightComponent` ModelObject types.

## Current Picture

Broadly speaking, the work now falls into three buckets:

- components that are in good shape and can reasonably be treated as complete
- components that are usable but still have clearly documented gaps
- components that need another engineering pass before they should be considered
  settled

## Components In Good Shape

The following components are in good shape.

### Unitary, VRF, and Air Terminals

- `AirConditionerVariableRefrigerantFlow`
- `AirLoopHVACUnitaryHeatPumpAirToAir`
- `AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed`
- `AirTerminalSingleDuctConstantVolumeCooledBeam`
- `AirTerminalSingleDuctConstantVolumeFourPipeBeam`
- `AirTerminalSingleDuctConstantVolumeFourPipeInduction`
- `AirTerminalSingleDuctConstantVolumeNoReheat`
- `AirTerminalSingleDuctConstantVolumeReheat`

### Cooling and Heating Coils

- `CoilCoolingDX`
- `CoilCoolingDXMultiSpeed`
- `CoilCoolingDXSingleSpeed`
- `CoilCoolingDXSingleSpeedThermalStorage`
- `CoilCoolingDXTwoSpeed`
- `CoilCoolingDXTwoStageWithHumidityControlMode`
- `CoilCoolingDXVariableRefrigerantFlow`
- `CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl`
- `CoilCoolingDXVariableSpeed`
- `CoilCoolingLowTempRadiantConstFlow`
- `CoilCoolingLowTempRadiantVarFlow`
- `CoilCoolingWaterPanelRadiant`
- `CoilHeatingDXMultiSpeed`
- `CoilHeatingDXSingleSpeed`
- `CoilHeatingDXVariableRefrigerantFlow`
- `CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl`
- `CoilHeatingDXVariableSpeed`
- `CoilHeatingDesuperheater`
- `CoilHeatingElectric`
- `CoilHeatingElectricMultiStage`
- `CoilHeatingGas`
- `CoilHeatingGasMultiStage`
- `CoilHeatingLowTempRadiantConstFlow`
- `CoilHeatingLowTempRadiantVarFlow`
- `CoilHeatingWaterBaseboard`
- `CoilHeatingWaterBaseboardRadiant`
- `CoilSystemCoolingDXHeatExchangerAssisted`
- `CoilSystemCoolingWater`
- `CoilSystemCoolingWaterHeatExchangerAssisted`
- `CoilSystemIntegratedHeatPumpAirSource`
- `CoilWaterHeatingAirToWaterHeatPumpWrapped`
- `CoilWaterHeatingDesuperheater`

### Towers, District Equipment, Pumps, and Related Plant Components

- `CoolingTowerSingleSpeed`
- `CoolingTowerVariableSpeed`
- `DistrictCooling`
- `DistrictHeatingSteam`
- `EvaporativeCoolerIndirectResearchSpecial`
- `EvaporativeFluidCoolerSingleSpeed`
- `EvaporativeFluidCoolerTwoSpeed`
- `FluidCoolerTwoSpeed`
- `GeneratorFuelCellExhaustGasToWaterHeatExchanger`
- `GeneratorFuelCellStackCooler`
- `HeaderedPumpsConstantSpeed`
- `HeaderedPumpsVariableSpeed`
- `HumidifierSteamElectric`
- `HumidifierSteamGas`
- `PumpConstantSpeed`
- `PumpVariableSpeed`
- `RefrigerationCompressorRack`
- `RefrigerationCondenserWaterCooled`
- `ThermalStorageIceDetailed`

### Heat Pumps, Solar, and Other Straight Components

- `BoilerSteam`
- `HeatPumpAirToWaterFuelFiredCooling`
- `HeatPumpAirToWaterFuelFiredHeating`
- `SolarCollectorFlatPlatePhotovoltaicThermal`
- `SolarCollectorIntegralCollectorStorage`

## Components Usable But Still Have Gaps

The components below are usable, but still have clearly documented gaps.

- `AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass`
  The owned fan/cooling/heating chain is in better shape, but the return-side
  `plenumorMixer` story is still limited by the current epmodel return-plenum
  type hierarchy.
- `DistrictHeatingWater`
  The type is much closer now, especially around continuous schedule-type
  enforcement, but it still needs a final judgment on whether the remaining
  deltas are real defects or acceptable documented limits.
- `EvaporativeCoolerDirectResearchSpecial`
  Availability schedule handling improved, but constructor/default parity is
  still partial.
- `FluidCoolerSingleSpeed`
  The type is more honest now, but unresolved autosized-value support and
  the public outdoor-air-node surface still leave it incomplete.
- `GroundHeatExchangerHorizontalTrench`
  A useful parity slice landed, including relationship and placement behavior,
  but this still deserves a final pass before being called finished.
- `GroundHeatExchangerVertical`
  Cleanup and branch-insertion behavior improved substantially, but it still
  carries intentional omissions and should be treated as partial.
- `LoadProfilePlant`
  The type and tests are stronger, but it still reads as partial rather than
  complete.
- `PlantComponentTemperatureSource`
  The type is close, but it still sits in the category of "improved and
  better tested" rather than "fully settled."
- `PlantComponentUserDefined`
  The one-connection contract is now much clearer and better enforced, but the
  type still needs a final pass before being considered complete.
- `SwimmingPoolIndoor`
  Several defaults and topology behaviors were repaired, but default coverage is
  still not complete enough to call this done.
- `TemperingValve`
  The tests are much better, but the type still needs a final engineering
  decision on whether anything substantive remains.
- `WaterUseConnections`
  Demand-side placement and schedule-related coverage improved, but this also
  still sits just short of closure.

## Components Needing Another Engineering Pass

The components below still need another engineering pass before they should be
considered settled.

- `BoilerHotWater`
  This still needs a clean re-triage from the current source state.
- `CoolingTowerTwoSpeed`
  The epmodel type itself improved, but it still needs a clean closure pass
  from the current repo state.
- `HeatPumpAirToWater`
  This is the clearest item that simply needs another engineering pass. The
  remaining issue is local type behavior, especially around curve handling.
- `PipeIndoor`
  Shared plant-loop cleanup work landed, but the type should still get one
  final closure pass.
- `PipeOutdoor`
  This should be judged from the current epmodel type state only, without
  leaning on any translator-side history.
- `SolarCollectorFlatPlateWater`
  This still needs a clean epmodel-focused review from the current repository
  state.
- `AirTerminalSingleDuctInletSideMixer`
  This still needs engineering work before it should be considered settled.
- `AirTerminalSingleDuctParallelPIUReheat`
  This still needs engineering work before it should be considered settled.
- `AirTerminalSingleDuctSeriesPIUReheat`
  This still needs engineering work before it should be considered settled.
- `AirTerminalSingleDuctVAVHeatAndCoolNoReheat`
  This still needs engineering work before it should be considered settled.
- `AirTerminalSingleDuctVAVHeatAndCoolReheat`
  This still needs engineering work before it should be considered settled.
- `AirTerminalSingleDuctVAVNoReheat`
  This still needs engineering work before it should be considered settled.
- `AirTerminalSingleDuctVAVReheat`
  This still needs engineering work before it should be considered settled.

## Cross-Cutting Themes

Several issues show up repeatedly.

- Shared schedule-type compatibility logic in
  `src/epmodel/ModelObject/ModelObject.cpp` is now more important than it used
  to be. Many types depend on that common path for correct schedule
  acceptance and rejection behavior.
- SQL-backed autosized results are still not generally available in epmodel, so
  a number of types remain intentionally partial around `autosized*()`
  accessors.
- Some remaining limitations are not local component bugs. In some cases,
  related epmodel types or object-model support do not exist yet, so the
  component cannot be fully implemented.
- Several components are already good enough that the next step may be a
  classification decision rather than more code. In other words, some of the
  remaining work is deciding whether a component should now be described as
  "parity with documented deltas."
