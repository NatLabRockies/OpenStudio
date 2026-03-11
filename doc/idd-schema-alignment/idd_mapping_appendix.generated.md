# IDD Mapping Appendix (Generated)

This appendix is machine-generated from IDDs and translator source.

## Method

1. Parse object names from both IDDs.
2. Parse `ForwardTranslator.cpp` switch to link `OS_*` -> model class -> `translateX` function.
3. Parse all ForwardTranslator function bodies for created `IddObjectType` IDF objects.
4. Include indirect model-level translator functions (not switch-dispatched) by matching model parameter class.
5. Invert mapping for EP-side coverage and annotate with `ReverseTranslator.cpp` switch function names.

## OS -> EP (Full)

| OS IddObjectType | Model class (FT switch/indirect) | EP IddObjectType(s) produced | Status | FT function |
| --- | --- | --- | --- | --- |
| `OS:AdditionalProperties` | `` |  | OS-only / no EP output | `` |
| `OS:AirConditioner:VariableRefrigerantFlow` | `AirConditionerVariableRefrigerantFlow` | `AirConditioner:VariableRefrigerantFlow`, `ZoneTerminalUnitList` | Mapped | `translateAirConditionerVariableRefrigerantFlow` |
| `OS:AirConditioner:VariableRefrigerantFlow:FluidTemperatureControl` | `AirConditionerVariableRefrigerantFlowFluidTemperatureControl` | `AirConditioner:VariableRefrigerantFlow:FluidTemperatureControl`, `ZoneTerminalUnitList` | Mapped | `translateAirConditionerVariableRefrigerantFlowFluidTemperatureControl` |
| `OS:AirConditioner:VariableRefrigerantFlow:FluidTemperatureControl:HR` | `AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR` | `AirConditioner:VariableRefrigerantFlow:FluidTemperatureControl:HR`, `ZoneTerminalUnitList` | Mapped | `translateAirConditionerVariableRefrigerantFlowFluidTemperatureControlHR` |
| `OS:AirConditioner:VariableRefrigerantFlow:FluidTemperatureControl:LoadingIndex` | `` |  | OS-only / no EP output | `` |
| `OS:AirLoopHVAC` | `AirLoopHVAC` | `AirLoopHVAC`, `AirLoopHVAC:ControllerList`, `AvailabilityManagerAssignmentList`, `AvailabilityManager:Scheduled`, `Branch`, `BranchList`, `ConnectorList`, `Connector:Splitter`, `NodeList` | Mapped | `translateAirLoopHVAC` |
| `OS:AirLoopHVAC:DedicatedOutdoorAirSystem` | `AirLoopHVACDedicatedOutdoorAirSystem` | `AirLoopHVAC:DedicatedOutdoorAirSystem`, `AirLoopHVAC:Mixer`, `AirLoopHVAC:Splitter` | Mapped | `translateAirLoopHVACDedicatedOutdoorAirSystem` |
| `OS:AirLoopHVAC:OutdoorAirSystem` | `AirLoopHVACOutdoorAirSystem` | `AirLoopHVAC:ControllerList`, `AirLoopHVAC:OutdoorAirSystem`, `AirLoopHVAC:OutdoorAirSystem:EquipmentList`, `OutdoorAir:Mixer`, `OutdoorAir:NodeList` | Mapped | `translateAirLoopHVACOutdoorAirSystem` |
| `OS:AirLoopHVAC:ReturnPlenum` | `AirLoopHVACReturnPlenum` | `AirLoopHVAC:ReturnPlenum`, `NodeList` | Mapped | `translateAirLoopHVACReturnPlenum` |
| `OS:AirLoopHVAC:SupplyPlenum` | `AirLoopHVACSupplyPlenum` | `AirLoopHVAC:SupplyPlenum` | Mapped | `translateAirLoopHVACSupplyPlenum` |
| `OS:AirLoopHVAC:UnitaryCoolOnly` | `` |  | OS-only / no EP output | `` |
| `OS:AirLoopHVAC:UnitaryHeatCool:VAVChangeoverBypass` | `AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass` | `AirLoopHVAC:UnitaryHeatCool:VAVChangeoverBypass`, `OutdoorAir:Mixer`, `OutdoorAir:NodeList` | Mapped | `translateAirLoopHVACUnitaryHeatCoolVAVChangeoverBypass` |
| `OS:AirLoopHVAC:UnitaryHeatPump:AirToAir` | `AirLoopHVACUnitaryHeatPumpAirToAir` | `AirLoopHVAC:UnitaryHeatPump:AirToAir` | Mapped | `translateAirLoopHVACUnitaryHeatPumpAirToAir` |
| `OS:AirLoopHVAC:UnitaryHeatPump:AirToAir:MultiSpeed` | `AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed` | `AirLoopHVAC:UnitaryHeatPump:AirToAir:MultiSpeed` | Mapped | `translateAirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed` |
| `OS:AirLoopHVAC:UnitarySystem` | `AirLoopHVACUnitarySystem` | `AirLoopHVAC:UnitarySystem`, `UnitarySystemPerformance:Multispeed` | Mapped | `translateAirLoopHVACUnitarySystem` |
| `OS:AirLoopHVAC:ZoneMixer` | `AirLoopHVACZoneMixer` | `AirLoopHVAC:ZoneMixer` | Mapped | `translateAirLoopHVACZoneMixer` |
| `OS:AirLoopHVAC:ZoneSplitter` | `AirLoopHVACZoneSplitter` | `AirLoopHVAC:ZoneSplitter` | Mapped | `translateAirLoopHVACZoneSplitter` |
| `OS:AirTerminal:DualDuct:ConstantVolume` | `AirTerminalDualDuctConstantVolume` | `AirTerminal:DualDuct:ConstantVolume`, `ZoneHVAC:AirDistributionUnit` | Mapped | `translateAirTerminalDualDuctConstantVolume` |
| `OS:AirTerminal:DualDuct:VAV` | `AirTerminalDualDuctVAV` | `AirTerminal:DualDuct:VAV`, `ZoneHVAC:AirDistributionUnit` | Mapped | `translateAirTerminalDualDuctVAV` |
| `OS:AirTerminal:DualDuct:VAV:OutdoorAir` | `AirTerminalDualDuctVAVOutdoorAir` | `AirTerminal:DualDuct:VAV:OutdoorAir`, `ZoneHVAC:AirDistributionUnit` | Mapped | `translateAirTerminalDualDuctVAVOutdoorAir` |
| `OS:AirTerminal:SingleDuct:ConstantVolume:CooledBeam` | `AirTerminalSingleDuctConstantVolumeCooledBeam` | `AirTerminal:SingleDuct:ConstantVolume:CooledBeam`, `ZoneHVAC:AirDistributionUnit` | Mapped | `translateAirTerminalSingleDuctConstantVolumeCooledBeam` |
| `OS:AirTerminal:SingleDuct:ConstantVolume:FourPipeBeam` | `AirTerminalSingleDuctConstantVolumeFourPipeBeam` | `AirTerminal:SingleDuct:ConstantVolume:FourPipeBeam`, `ZoneHVAC:AirDistributionUnit` | Mapped | `translateAirTerminalSingleDuctConstantVolumeFourPipeBeam` |
| `OS:AirTerminal:SingleDuct:ConstantVolume:FourPipeInduction` | `AirTerminalSingleDuctConstantVolumeFourPipeInduction` | `AirLoopHVAC:ZoneMixer`, `AirTerminal:SingleDuct:ConstantVolume:FourPipeInduction`, `ZoneHVAC:AirDistributionUnit` | Mapped | `translateAirTerminalSingleDuctConstantVolumeFourPipeInduction` |
| `OS:AirTerminal:SingleDuct:ConstantVolume:NoReheat` | `AirTerminalSingleDuctConstantVolumeNoReheat` | `AirTerminal:SingleDuct:ConstantVolume:NoReheat`, `ZoneHVAC:AirDistributionUnit` | Mapped | `translateAirTerminalSingleDuctConstantVolumeNoReheat` |
| `OS:AirTerminal:SingleDuct:ConstantVolume:Reheat` | `AirTerminalSingleDuctConstantVolumeReheat` | `AirTerminal:SingleDuct:ConstantVolume:Reheat`, `ZoneHVAC:AirDistributionUnit` | Mapped | `translateAirTerminalSingleDuctConstantVolumeReheat` |
| `OS:AirTerminal:SingleDuct:InletSideMixer` | `AirTerminalSingleDuctInletSideMixer` | `AirTerminal:SingleDuct:Mixer`, `ZoneHVAC:AirDistributionUnit` | Mapped | `translateAirTerminalSingleDuctInletSideMixer` |
| `OS:AirTerminal:SingleDuct:ParallelPIU:Reheat` | `AirTerminalSingleDuctParallelPIUReheat` | `AirLoopHVAC:ZoneMixer`, `AirTerminal:SingleDuct:ParallelPIU:Reheat`, `ZoneHVAC:AirDistributionUnit` | Mapped | `translateAirTerminalSingleDuctParallelPIUReheat` |
| `OS:AirTerminal:SingleDuct:SeriesPIU:Reheat` | `AirTerminalSingleDuctSeriesPIUReheat` | `AirLoopHVAC:ZoneMixer`, `AirTerminal:SingleDuct:SeriesPIU:Reheat`, `ZoneHVAC:AirDistributionUnit` | Mapped | `translateAirTerminalSingleDuctSeriesPIUReheat` |
| `OS:AirTerminal:SingleDuct:VAV:HeatAndCool:NoReheat` | `AirTerminalSingleDuctVAVHeatAndCoolNoReheat` | `AirTerminal:SingleDuct:VAV:HeatAndCool:NoReheat`, `ZoneHVAC:AirDistributionUnit` | Mapped | `translateAirTerminalSingleDuctVAVHeatAndCoolNoReheat` |
| `OS:AirTerminal:SingleDuct:VAV:HeatAndCool:Reheat` | `AirTerminalSingleDuctVAVHeatAndCoolReheat` | `AirTerminal:SingleDuct:VAV:HeatAndCool:Reheat`, `ZoneHVAC:AirDistributionUnit` | Mapped | `translateAirTerminalSingleDuctVAVHeatAndCoolReheat` |
| `OS:AirTerminal:SingleDuct:VAV:NoReheat` | `AirTerminalSingleDuctVAVNoReheat` | `AirTerminal:SingleDuct:VAV:NoReheat`, `ZoneHVAC:AirDistributionUnit` | Mapped | `translateAirTerminalSingleDuctVAVNoReheat` |
| `OS:AirTerminal:SingleDuct:VAV:Reheat` | `AirTerminalSingleDuctVAVReheat` | `AirTerminal:SingleDuct:VAV:Reheat`, `ZoneHVAC:AirDistributionUnit` | Mapped | `translateAirTerminalSingleDuctVAVReheat` |
| `OS:AirflowNetworkConstantPressureDrop` | `AirflowNetworkConstantPressureDrop` | `AirflowNetwork:Distribution:Component:ConstantPressureDrop` | Mapped | `` |
| `OS:AirflowNetworkCrack` | `AirflowNetworkCrack` | `AirflowNetwork:MultiZone:Surface:Crack` | Mapped | `` |
| `OS:AirflowNetworkDetailedOpening` | `AirflowNetworkDetailedOpening` | `AirflowNetwork:MultiZone:Component:DetailedOpening` | Mapped | `` |
| `OS:AirflowNetworkDistributionLinkage` | `AirflowNetworkDistributionLinkage` | `AirflowNetwork:Distribution:Linkage` | Mapped | `` |
| `OS:AirflowNetworkDistributionNode` | `AirflowNetworkDistributionNode` | `AirflowNetwork:Distribution:Node` | Mapped | `` |
| `OS:AirflowNetworkDuct` | `AirflowNetworkDuct` | `AirflowNetwork:Distribution:Component:Duct` | Mapped | `` |
| `OS:AirflowNetworkDuctViewFactors` | `AirflowNetworkDuctViewFactors` | `AirflowNetwork:Distribution:DuctViewFactors` | Mapped | `` |
| `OS:AirflowNetworkEffectiveLeakageArea` | `AirflowNetworkEffectiveLeakageArea` | `AirflowNetwork:MultiZone:Surface:EffectiveLeakageArea` | Mapped | `` |
| `OS:AirflowNetworkEquivalentDuct` | `AirflowNetworkEquivalentDuct` | `AirflowNetwork:Distribution:Component:Coil`, `AirflowNetwork:Distribution:Component:HeatExchanger`, `AirflowNetwork:Distribution:Component:TerminalUnit` | Mapped | `` |
| `OS:AirflowNetworkExternalNode` | `AirflowNetworkExternalNode` | `AirflowNetwork:MultiZone:ExternalNode` | Mapped | `` |
| `OS:AirflowNetworkFan` | `AirflowNetworkFan` | `AirflowNetwork:Distribution:Component:Fan` | Mapped | `` |
| `OS:AirflowNetworkHorizontalOpening` | `AirflowNetworkHorizontalOpening` | `AirflowNetwork:MultiZone:Component:HorizontalOpening` | Mapped | `` |
| `OS:AirflowNetworkLeak` | `` |  | OS-only / no EP output | `` |
| `OS:AirflowNetworkLeakageRatio` | `AirflowNetworkLeakageRatio` | `AirflowNetwork:Distribution:Component:LeakageRatio` | Mapped | `` |
| `OS:AirflowNetworkOccupantVentilationControl` | `AirflowNetworkOccupantVentilationControl` | `AirflowNetwork:OccupantVentilationControl` | Mapped | `` |
| `OS:AirflowNetworkOutdoorAirflow` | `AirflowNetworkOutdoorAirflow` | `AirflowNetwork:Distribution:Component:OutdoorAirFlow` | Mapped | `` |
| `OS:AirflowNetworkPressureController` | `` |  | OS-only / no EP output | `` |
| `OS:AirflowNetworkReferenceCrackConditions` | `AirflowNetworkReferenceCrackConditions` | `AirflowNetwork:MultiZone:ReferenceCrackConditions` | Mapped | `` |
| `OS:AirflowNetworkReliefAirFlow` | `` |  | OS-only / no EP output | `` |
| `OS:AirflowNetworkSimpleOpening` | `AirflowNetworkSimpleOpening` | `AirflowNetwork:MultiZone:Component:SimpleOpening` | Mapped | `` |
| `OS:AirflowNetworkSimulationControl` | `AirflowNetworkSimulationControl` | `AirflowNetwork:SimulationControl` | Mapped | `` |
| `OS:AirflowNetworkSpecifiedFlowRate` | `AirflowNetworkSpecifiedFlowRate` | `AirflowNetwork:MultiZone:SpecifiedFlowRate` | Mapped | `` |
| `OS:AirflowNetworkSurface` | `AirflowNetworkSurface` | `AirflowNetwork:MultiZone:Surface` | Mapped | `` |
| `OS:AirflowNetworkZone` | `AirflowNetworkZone` | `AirflowNetwork:MultiZone:Zone` | Mapped | `` |
| `OS:AirflowNetworkZoneExhaustFan` | `AirflowNetworkZoneExhaustFan` | `AirflowNetwork:MultiZone:Component:ZoneExhaustFan` | Mapped | `` |
| `OS:AvailabilityManager:DifferentialThermostat` | `AvailabilityManagerDifferentialThermostat` | `AvailabilityManager:DifferentialThermostat` | Mapped | `translateAvailabilityManagerDifferentialThermostat` |
| `OS:AvailabilityManager:HighTemperatureTurnOff` | `AvailabilityManagerHighTemperatureTurnOff` | `AvailabilityManager:HighTemperatureTurnOff` | Mapped | `translateAvailabilityManagerHighTemperatureTurnOff` |
| `OS:AvailabilityManager:HighTemperatureTurnOn` | `AvailabilityManagerHighTemperatureTurnOn` | `AvailabilityManager:HighTemperatureTurnOn` | Mapped | `translateAvailabilityManagerHighTemperatureTurnOn` |
| `OS:AvailabilityManager:HybridVentilation` | `AvailabilityManagerHybridVentilation` | `AvailabilityManager:HybridVentilation` | Mapped | `translateAvailabilityManagerHybridVentilation` |
| `OS:AvailabilityManager:LowTemperatureTurnOff` | `AvailabilityManagerLowTemperatureTurnOff` | `AvailabilityManager:LowTemperatureTurnOff` | Mapped | `translateAvailabilityManagerLowTemperatureTurnOff` |
| `OS:AvailabilityManager:LowTemperatureTurnOn` | `AvailabilityManagerLowTemperatureTurnOn` | `AvailabilityManager:LowTemperatureTurnOn` | Mapped | `translateAvailabilityManagerLowTemperatureTurnOn` |
| `OS:AvailabilityManager:NightCycle` | `AvailabilityManagerNightCycle` | `AvailabilityManager:NightCycle`, `ZoneList` | Mapped | `translateAvailabilityManagerNightCycle` |
| `OS:AvailabilityManager:NightVentilation` | `AvailabilityManagerNightVentilation` | `AvailabilityManager:NightVentilation` | Mapped | `translateAvailabilityManagerNightVentilation` |
| `OS:AvailabilityManager:OptimumStart` | `AvailabilityManagerOptimumStart` | `AvailabilityManager:OptimumStart`, `ZoneList` | Mapped | `translateAvailabilityManagerOptimumStart` |
| `OS:AvailabilityManager:Scheduled` | `AvailabilityManagerScheduled` | `AvailabilityManager:Scheduled` | Mapped | `translateAvailabilityManagerScheduled` |
| `OS:AvailabilityManager:ScheduledOff` | `AvailabilityManagerScheduledOff` | `AvailabilityManager:ScheduledOff` | Mapped | `translateAvailabilityManagerScheduledOff` |
| `OS:AvailabilityManager:ScheduledOn` | `AvailabilityManagerScheduledOn` | `AvailabilityManager:ScheduledOn` | Mapped | `translateAvailabilityManagerScheduledOn` |
| `OS:AvailabilityManagerAssignmentList` | `AvailabilityManagerAssignmentList` | `AvailabilityManagerAssignmentList` | Mapped | `translateAvailabilityManagerAssignmentList` |
| `OS:Boiler:HotWater` | `BoilerHotWater` | `Boiler:HotWater` | Mapped | `translateBoilerHotWater` |
| `OS:Boiler:Steam` | `BoilerSteam` | `Boiler:Steam` | Mapped | `translateBoilerSteam` |
| `OS:Building` | `Building` | `Building` | Mapped | `translateBuilding` |
| `OS:BuildingStory` | `` |  | OS-only / no EP output | `` |
| `OS:BuildingUnit` | `` |  | OS-only / no EP output | `` |
| `OS:CentralHeatPumpSystem` | `CentralHeatPumpSystem` | `CentralHeatPumpSystem` | Mapped | `translateCentralHeatPumpSystem` |
| `OS:CentralHeatPumpSystem:Module` | `` |  | OS-only / no EP output | `` |
| `OS:Chiller:Absorption` | `ChillerAbsorption` | `Chiller:Absorption` | Mapped | `translateChillerAbsorption` |
| `OS:Chiller:Absorption:Indirect` | `ChillerAbsorptionIndirect` | `Chiller:Absorption:Indirect` | Mapped | `translateChillerAbsorptionIndirect` |
| `OS:Chiller:Electric:ASHRAE205` | `ChillerElectricASHRAE205` | `Chiller:Electric:ASHRAE205`, `OutdoorAir:NodeList` | Mapped | `translateChillerElectricASHRAE205` |
| `OS:Chiller:Electric:EIR` | `ChillerElectricEIR` | `Chiller:Electric:EIR`, `OutdoorAir:NodeList` | Mapped | `translateChillerElectricEIR` |
| `OS:Chiller:Electric:ReformulatedEIR` | `ChillerElectricReformulatedEIR` | `Chiller:Electric:ReformulatedEIR` | Mapped | `translateChillerElectricReformulatedEIR` |
| `OS:ChillerHeaterPerformance:Electric:EIR` | `ChillerHeaterPerformanceElectricEIR` | `ChillerHeaterPerformance:Electric:EIR` | Mapped | `translateChillerHeaterPerformanceElectricEIR` |
| `OS:ClimateZones` | `` |  | OS-only / no EP output | `` |
| `OS:Coil:Cooling:CooledBeam` | `` |  | OS-only / no EP output | `` |
| `OS:Coil:Cooling:DX` | `CoilCoolingDX` | `CoilSystem:Cooling:DX`, `Coil:Cooling:DX`, `OutdoorAir:NodeList` | Mapped | `translateCoilCoolingDXWithoutUnitary` |
| `OS:Coil:Cooling:DX:CurveFit:OperatingMode` | `CoilCoolingDXCurveFitOperatingMode` | `Coil:Cooling:DX:CurveFit:OperatingMode` | Mapped | `translateCoilCoolingDXCurveFitOperatingMode` |
| `OS:Coil:Cooling:DX:CurveFit:Performance` | `CoilCoolingDXCurveFitPerformance` | `Coil:Cooling:DX:CurveFit:Performance` | Mapped | `translateCoilCoolingDXCurveFitPerformance` |
| `OS:Coil:Cooling:DX:CurveFit:Speed` | `CoilCoolingDXCurveFitSpeed` | `Coil:Cooling:DX:CurveFit:Speed` | Mapped | `translateCoilCoolingDXCurveFitSpeed` |
| `OS:Coil:Cooling:DX:MultiSpeed` | `CoilCoolingDXMultiSpeed` | `Coil:Cooling:DX:MultiSpeed` | Mapped | `translateCoilCoolingDXMultiSpeed` |
| `OS:Coil:Cooling:DX:MultiSpeed:StageData` | `` |  | OS-only / no EP output | `` |
| `OS:Coil:Cooling:DX:SingleSpeed` | `CoilCoolingDXSingleSpeed` | `CoilSystem:Cooling:DX`, `Coil:Cooling:DX:SingleSpeed` | Mapped | `translateCoilCoolingDXSingleSpeedWithoutUnitary` |
| `OS:Coil:Cooling:DX:SingleSpeed:ThermalStorage` | `CoilCoolingDXSingleSpeedThermalStorage` | `CoilSystem:Cooling:DX`, `Coil:Cooling:DX:SingleSpeed:ThermalStorage`, `OutdoorAir:NodeList` | Mapped | `translateCoilCoolingDXSingleSpeedThermalStorageWithoutUnitary` |
| `OS:Coil:Cooling:DX:TwoSpeed` | `CoilCoolingDXTwoSpeed` | `CoilSystem:Cooling:DX`, `Coil:Cooling:DX:TwoSpeed` | Mapped | `translateCoilCoolingDXTwoSpeedWithoutUnitary` |
| `OS:Coil:Cooling:DX:TwoStageWithHumidityControlMode` | `CoilCoolingDXTwoStageWithHumidityControlMode` | `CoilSystem:Cooling:DX`, `Coil:Cooling:DX:TwoStageWithHumidityControlMode` | Mapped | `translateCoilCoolingDXTwoStageWithHumidityControlModeWithoutUnitary` |
| `OS:Coil:Cooling:DX:VariableRefrigerantFlow` | `CoilCoolingDXVariableRefrigerantFlow` | `Coil:Cooling:DX:VariableRefrigerantFlow` | Mapped | `translateCoilCoolingDXVariableRefrigerantFlow` |
| `OS:Coil:Cooling:DX:VariableRefrigerantFlow:FluidTemperatureControl` | `CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl` | `Coil:Cooling:DX:VariableRefrigerantFlow:FluidTemperatureControl` | Mapped | `translateCoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl` |
| `OS:Coil:Cooling:DX:VariableSpeed` | `CoilCoolingDXVariableSpeed` | `CoilSystem:Cooling:DX`, `Coil:Cooling:DX:VariableSpeed` | Mapped | `translateCoilCoolingDXVariableSpeedWithoutUnitary` |
| `OS:Coil:Cooling:DX:VariableSpeed:SpeedData` | `` |  | OS-only / no EP output | `` |
| `OS:Coil:Cooling:FourPipeBeam` | `` |  | OS-only / no EP output | `` |
| `OS:Coil:Cooling:LowTemperatureRadiant:ConstantFlow` | `` |  | OS-only / no EP output | `` |
| `OS:Coil:Cooling:LowTemperatureRadiant:VariableFlow` | `` |  | OS-only / no EP output | `` |
| `OS:Coil:Cooling:Water` | `CoilCoolingWater` | `Coil:Cooling:Water` | Mapped | `translateCoilCoolingWater` |
| `OS:Coil:Cooling:Water:Panel:Radiant` | `` |  | OS-only / no EP output | `` |
| `OS:Coil:Cooling:WaterToAirHeatPump:EquationFit` | `CoilCoolingWaterToAirHeatPumpEquationFit` | `Coil:Cooling:WaterToAirHeatPump:EquationFit` | Mapped | `translateCoilCoolingWaterToAirHeatPumpEquationFit` |
| `OS:Coil:Cooling:WaterToAirHeatPump:VariableSpeedEquationFit` | `CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit` | `Coil:Cooling:WaterToAirHeatPump:VariableSpeedEquationFit` | Mapped | `translateCoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit` |
| `OS:Coil:Cooling:WaterToAirHeatPump:VariableSpeedEquationFit:SpeedData` | `` |  | OS-only / no EP output | `` |
| `OS:Coil:Heating:DX:MultiSpeed` | `CoilHeatingDXMultiSpeed` | `Coil:Heating:DX:MultiSpeed` | Mapped | `translateCoilHeatingDXMultiSpeed` |
| `OS:Coil:Heating:DX:MultiSpeed:StageData` | `` |  | OS-only / no EP output | `` |
| `OS:Coil:Heating:DX:SingleSpeed` | `CoilHeatingDXSingleSpeed` | `CoilSystem:Heating:DX`, `Coil:Heating:DX:SingleSpeed` | Mapped | `translateCoilHeatingDXSingleSpeedWithoutUnitary` |
| `OS:Coil:Heating:DX:VariableRefrigerantFlow` | `CoilHeatingDXVariableRefrigerantFlow` | `Coil:Heating:DX:VariableRefrigerantFlow` | Mapped | `translateCoilHeatingDXVariableRefrigerantFlow` |
| `OS:Coil:Heating:DX:VariableRefrigerantFlow:FluidTemperatureControl` | `CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl` | `Coil:Heating:DX:VariableRefrigerantFlow:FluidTemperatureControl` | Mapped | `translateCoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl` |
| `OS:Coil:Heating:DX:VariableSpeed` | `CoilHeatingDXVariableSpeed` | `CoilSystem:Heating:DX`, `Coil:Heating:DX:VariableSpeed` | Mapped | `translateCoilHeatingDXVariableSpeedWithoutUnitary` |
| `OS:Coil:Heating:DX:VariableSpeed:SpeedData` | `` |  | OS-only / no EP output | `` |
| `OS:Coil:Heating:Desuperheater` | `CoilHeatingDesuperheater` | `Coil:Heating:Desuperheater` | Mapped | `translateCoilHeatingDesuperheater` |
| `OS:Coil:Heating:Electric` | `CoilHeatingElectric` | `Coil:Heating:Electric` | Mapped | `translateCoilHeatingElectric` |
| `OS:Coil:Heating:Electric:MultiStage` | `CoilHeatingElectricMultiStage` | `Coil:Heating:Electric:MultiStage` | Mapped | `translateCoilHeatingElectricMultiStage` |
| `OS:Coil:Heating:Electric:MultiStage:StageData` | `` |  | OS-only / no EP output | `` |
| `OS:Coil:Heating:FourPipeBeam` | `` |  | OS-only / no EP output | `` |
| `OS:Coil:Heating:Gas` | `CoilHeatingGas` | `Coil:Heating:Fuel` | Mapped | `translateCoilHeatingGas` |
| `OS:Coil:Heating:Gas:MultiStage` | `CoilHeatingGasMultiStage` | `Coil:Heating:Gas:MultiStage` | Mapped | `translateCoilHeatingGasMultiStage` |
| `OS:Coil:Heating:Gas:MultiStage:StageData` | `` |  | OS-only / no EP output | `` |
| `OS:Coil:Heating:LowTemperatureRadiant:ConstantFlow` | `` |  | OS-only / no EP output | `` |
| `OS:Coil:Heating:LowTemperatureRadiant:VariableFlow` | `` |  | OS-only / no EP output | `` |
| `OS:Coil:Heating:Water` | `CoilHeatingWater` | `Coil:Heating:Water` | Mapped | `translateCoilHeatingWater` |
| `OS:Coil:Heating:Water:Baseboard` | `` |  | OS-only / no EP output | `` |
| `OS:Coil:Heating:Water:Baseboard:Radiant` | `` |  | OS-only / no EP output | `` |
| `OS:Coil:Heating:WaterToAirHeatPump:EquationFit` | `CoilHeatingWaterToAirHeatPumpEquationFit` | `Coil:Heating:WaterToAirHeatPump:EquationFit` | Mapped | `translateCoilHeatingWaterToAirHeatPumpEquationFit` |
| `OS:Coil:Heating:WaterToAirHeatPump:VariableSpeedEquationFit` | `CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit` | `Coil:Heating:WaterToAirHeatPump:VariableSpeedEquationFit` | Mapped | `translateCoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit` |
| `OS:Coil:Heating:WaterToAirHeatPump:VariableSpeedEquationFit:SpeedData` | `` |  | OS-only / no EP output | `` |
| `OS:Coil:UserDefined` | `CoilUserDefined` | `Coil:UserDefined` | Mapped | `translateCoilUserDefined` |
| `OS:Coil:WaterHeating:AirToWaterHeatPump` | `CoilWaterHeatingAirToWaterHeatPump` | `Coil:WaterHeating:AirToWaterHeatPump:Pumped` | Mapped | `translateCoilWaterHeatingAirToWaterHeatPump` |
| `OS:Coil:WaterHeating:AirToWaterHeatPump:VariableSpeed` | `CoilWaterHeatingAirToWaterHeatPumpVariableSpeed` | `Coil:WaterHeating:AirToWaterHeatPump:VariableSpeed` | Mapped | `translateCoilWaterHeatingAirToWaterHeatPumpVariableSpeed` |
| `OS:Coil:WaterHeating:AirToWaterHeatPump:VariableSpeed:SpeedData` | `` |  | OS-only / no EP output | `` |
| `OS:Coil:WaterHeating:AirToWaterHeatPump:Wrapped` | `CoilWaterHeatingAirToWaterHeatPumpWrapped` | `Coil:WaterHeating:AirToWaterHeatPump:Wrapped` | Mapped | `translateCoilWaterHeatingAirToWaterHeatPumpWrapped` |
| `OS:Coil:WaterHeating:Desuperheater` | `CoilWaterHeatingDesuperheater` | `Coil:WaterHeating:Desuperheater` | Mapped | `translateCoilWaterHeatingDesuperheater` |
| `OS:CoilPerformance:DX:Cooling` | `CoilPerformanceDXCooling` | `CoilPerformance:DX:Cooling` | Mapped | `translateCoilPerformanceDXCooling` |
| `OS:CoilSystem:Cooling:DX:HeatExchangerAssisted` | `CoilSystemCoolingDXHeatExchangerAssisted` | `CoilSystem:Cooling:DX:HeatExchangerAssisted` | Mapped | `translateCoilSystemCoolingDXHeatExchangerAssisted` |
| `OS:CoilSystem:Cooling:Water` | `CoilSystemCoolingWater` | `CoilSystem:Cooling:Water` | Mapped | `translateCoilSystemCoolingWater` |
| `OS:CoilSystem:Cooling:Water:HeatExchangerAssisted` | `CoilSystemCoolingWaterHeatExchangerAssisted` | `CoilSystem:Cooling:Water:HeatExchangerAssisted`, `SetpointManager:MixedAir` | Mapped | `translateCoilSystemCoolingWaterHeatExchangerAssisted` |
| `OS:CoilSystem:IntegratedHeatPump:AirSource` | `CoilSystemIntegratedHeatPumpAirSource` | `CoilSystem:IntegratedHeatPump:AirSource` | Mapped | `translateCoilSystemIntegratedHeatPumpAirSource` |
| `OS:ComponentCost:Adjustments` | `` |  | OS-only / no EP output | `` |
| `OS:ComponentData` | `` |  | OS-only / no EP output | `` |
| `OS:Connection` | `` |  | OS-only / no EP output | `` |
| `OS:Connector:Mixer` | `` |  | OS-only / no EP output | `` |
| `OS:Connector:Splitter` | `` |  | OS-only / no EP output | `` |
| `OS:Construction` | `Construction` | `Construction` | Mapped | `translateConstruction` |
| `OS:Construction:AirBoundary` | `ConstructionAirBoundary` | `Construction:AirBoundary` | Mapped | `translateConstructionAirBoundary` |
| `OS:Construction:CfactorUndergroundWall` | `CFactorUndergroundWallConstruction` | `Construction:CfactorUndergroundWall` | Mapped | `translateCFactorUndergroundWallConstruction` |
| `OS:Construction:FfactorGroundFloor` | `FFactorGroundFloorConstruction` | `Construction:FfactorGroundFloor` | Mapped | `translateFFactorGroundFloorConstruction` |
| `OS:Construction:InternalSource` | `ConstructionWithInternalSource` | `Construction`, `ConstructionProperty:InternalHeatSource` | Mapped | `translateConstructionWithInternalSource` |
| `OS:Construction:WindowDataFile` | `` |  | OS-only / no EP output | `` |
| `OS:Controller:MechanicalVentilation` | `ControllerMechanicalVentilation` | `Controller:MechanicalVentilation` | Mapped | `translateControllerMechanicalVentilation` |
| `OS:Controller:OutdoorAir` | `ControllerOutdoorAir` | `Controller:OutdoorAir` | Mapped | `translateControllerOutdoorAir` |
| `OS:Controller:WaterCoil` | `ControllerWaterCoil` | `Controller:WaterCoil` | Mapped | `translateControllerWaterCoil` |
| `OS:ConvergenceLimits` | `ConvergenceLimits` | `ConvergenceLimits` | Mapped | `translateConvergenceLimits` |
| `OS:CoolingTower:SingleSpeed` | `CoolingTowerSingleSpeed` | `CoolingTower:SingleSpeed` | Mapped | `translateCoolingTowerSingleSpeed` |
| `OS:CoolingTower:TwoSpeed` | `CoolingTowerTwoSpeed` | `CoolingTower:TwoSpeed` | Mapped | `translateCoolingTowerTwoSpeed` |
| `OS:CoolingTower:VariableSpeed` | `CoolingTowerVariableSpeed` | `CoolingTower:VariableSpeed` | Mapped | `translateCoolingTowerVariableSpeed` |
| `OS:CoolingTowerPerformance:CoolTools` | `CoolingTowerPerformanceCoolTools` | `CoolingTowerPerformance:CoolTools` | Mapped | `translateCoolingTowerPerformanceCoolTools` |
| `OS:CoolingTowerPerformance:YorkCalc` | `CoolingTowerPerformanceYorkCalc` | `CoolingTowerPerformance:YorkCalc` | Mapped | `translateCoolingTowerPerformanceYorkCalc` |
| `OS:CurrencyType` | `CurrencyType` | `CurrencyType` | Mapped | `translateCurrencyType` |
| `OS:Curve:Bicubic` | `CurveBicubic` | `Curve:Bicubic` | Mapped | `translateCurveBicubic` |
| `OS:Curve:Biquadratic` | `CurveBiquadratic` | `Curve:Biquadratic` | Mapped | `translateCurveBiquadratic` |
| `OS:Curve:Cubic` | `CurveCubic` | `Curve:Cubic` | Mapped | `translateCurveCubic` |
| `OS:Curve:DoubleExponentialDecay` | `CurveDoubleExponentialDecay` | `Curve:DoubleExponentialDecay` | Mapped | `translateCurveDoubleExponentialDecay` |
| `OS:Curve:Exponent` | `CurveExponent` | `Curve:Exponent` | Mapped | `translateCurveExponent` |
| `OS:Curve:ExponentialDecay` | `CurveExponentialDecay` | `Curve:ExponentialDecay` | Mapped | `translateCurveExponentialDecay` |
| `OS:Curve:ExponentialSkewNormal` | `CurveExponentialSkewNormal` | `Curve:ExponentialSkewNormal` | Mapped | `translateCurveExponentialSkewNormal` |
| `OS:Curve:FanPressureRise` | `CurveFanPressureRise` | `Curve:FanPressureRise` | Mapped | `translateCurveFanPressureRise` |
| `OS:Curve:Functional:PressureDrop` | `CurveFunctionalPressureDrop` | `Curve:Functional:PressureDrop` | Mapped | `translateCurveFunctionalPressureDrop` |
| `OS:Curve:Linear` | `CurveLinear` | `Curve:Linear` | Mapped | `translateCurveLinear` |
| `OS:Curve:QuadLinear` | `CurveQuadLinear` | `Curve:QuadLinear` | Mapped | `translateCurveQuadLinear` |
| `OS:Curve:Quadratic` | `CurveQuadratic` | `Curve:Quadratic` | Mapped | `translateCurveQuadratic` |
| `OS:Curve:QuadraticLinear` | `CurveQuadraticLinear` | `Curve:QuadraticLinear` | Mapped | `translateCurveQuadraticLinear` |
| `OS:Curve:Quartic` | `CurveQuartic` | `Curve:Quartic` | Mapped | `translateCurveQuartic` |
| `OS:Curve:QuintLinear` | `CurveQuintLinear` | `Curve:QuintLinear` | Mapped | `translateCurveQuintLinear` |
| `OS:Curve:RectangularHyperbola1` | `CurveRectangularHyperbola1` | `Curve:RectangularHyperbola1` | Mapped | `translateCurveRectangularHyperbola1` |
| `OS:Curve:RectangularHyperbola2` | `CurveRectangularHyperbola2` | `Curve:RectangularHyperbola2` | Mapped | `translateCurveRectangularHyperbola2` |
| `OS:Curve:Sigmoid` | `CurveSigmoid` | `Curve:Sigmoid` | Mapped | `translateCurveSigmoid` |
| `OS:Curve:Triquadratic` | `CurveTriquadratic` | `Curve:Triquadratic` | Mapped | `translateCurveTriquadratic` |
| `OS:Daylighting:Control` | `DaylightingControl` |  | OS-only / no EP output | `translateDaylightingControl` |
| `OS:DaylightingDevice:LightWell` | `DaylightingDeviceLightWell` | `DaylightingDevice:LightWell` | Mapped | `translateDaylightingDeviceLightWell` |
| `OS:DaylightingDevice:Shelf` | `DaylightingDeviceShelf` | `DaylightingDevice:Shelf` | Mapped | `translateDaylightingDeviceShelf` |
| `OS:DaylightingDevice:Tubular` | `DaylightingDeviceTubular` | `DaylightingDevice:Tubular` | Mapped | `translateDaylightingDeviceTubular` |
| `OS:DefaultConstructionSet` | `` |  | OS-only / no EP output | `` |
| `OS:DefaultScheduleSet` | `` |  | OS-only / no EP output | `` |
| `OS:DefaultSubSurfaceConstructions` | `` |  | OS-only / no EP output | `` |
| `OS:DefaultSurfaceConstructions` | `` |  | OS-only / no EP output | `` |
| `OS:DesignSpecification:OutdoorAir` | `` |  | OS-only / no EP output | `` |
| `OS:DesignSpecification:ZoneAirDistribution` | `` |  | OS-only / no EP output | `` |
| `OS:DistrictCooling` | `DistrictCooling` | `DistrictCooling` | Mapped | `translateDistrictCooling` |
| `OS:DistrictHeating:Steam` | `DistrictHeatingSteam` | `DistrictHeating:Steam` | Mapped | `translateDistrictHeatingSteam` |
| `OS:DistrictHeating:Water` | `DistrictHeatingWater` | `DistrictHeating:Water` | Mapped | `translateDistrictHeatingWater` |
| `OS:Duct` | `Duct` | `Duct` | Mapped | `translateDuct` |
| `OS:ElectricEquipment` | `ElectricEquipment` | `ElectricEquipment` | Mapped | `translateElectricEquipment` |
| `OS:ElectricEquipment:Definition` | `` |  | OS-only / no EP output | `` |
| `OS:ElectricEquipment:ITE:AirCooled` | `ElectricEquipmentITEAirCooled` | `ElectricEquipment:ITE:AirCooled` | Mapped | `translateElectricEquipmentITEAirCooled` |
| `OS:ElectricEquipment:ITE:AirCooled:Definition` | `` |  | OS-only / no EP output | `` |
| `OS:ElectricLoadCenter:Distribution` | `ElectricLoadCenterDistribution` | `ElectricLoadCenter:Distribution`, `ElectricLoadCenter:Generators` | Mapped | `translateElectricLoadCenterDistribution` |
| `OS:ElectricLoadCenter:Inverter:LookUpTable` | `ElectricLoadCenterInverterLookUpTable` | `ElectricLoadCenter:Inverter:LookUpTable` | Mapped | `translateElectricLoadCenterInverterLookUpTable` |
| `OS:ElectricLoadCenter:Inverter:PVWatts` | `ElectricLoadCenterInverterPVWatts` | `ElectricLoadCenter:Inverter:PVWatts` | Mapped | `translateElectricLoadCenterInverterPVWatts` |
| `OS:ElectricLoadCenter:Inverter:Simple` | `ElectricLoadCenterInverterSimple` | `ElectricLoadCenter:Inverter:Simple` | Mapped | `translateElectricLoadCenterInverterSimple` |
| `OS:ElectricLoadCenter:Storage:Converter` | `ElectricLoadCenterStorageConverter` | `ElectricLoadCenter:Storage:Converter` | Mapped | `translateElectricLoadCenterStorageConverter` |
| `OS:ElectricLoadCenter:Storage:LiIonNMCBattery` | `ElectricLoadCenterStorageLiIonNMCBattery` | `ElectricLoadCenter:Storage:LiIonNMCBattery` | Mapped | `translateElectricLoadCenterStorageLiIonNMCBattery` |
| `OS:ElectricLoadCenter:Storage:Simple` | `ElectricLoadCenterStorageSimple` | `ElectricLoadCenter:Storage:Simple` | Mapped | `translateElectricLoadCenterStorageSimple` |
| `OS:ElectricLoadCenter:Transformer` | `ElectricLoadCenterTransformer` | `ElectricLoadCenter:Transformer` | Mapped | `translateElectricLoadCenterTransformer` |
| `OS:EnergyManagementSystem:Actuator` | `EnergyManagementSystemActuator` | `EnergyManagementSystem:Actuator` | Mapped | `translateEnergyManagementSystemActuator` |
| `OS:EnergyManagementSystem:ConstructionIndexVariable` | `EnergyManagementSystemConstructionIndexVariable` | `EnergyManagementSystem:ConstructionIndexVariable` | Mapped | `translateEnergyManagementSystemConstructionIndexVariable` |
| `OS:EnergyManagementSystem:CurveOrTableIndexVariable` | `EnergyManagementSystemCurveOrTableIndexVariable` | `EnergyManagementSystem:CurveOrTableIndexVariable` | Mapped | `translateEnergyManagementSystemCurveOrTableIndexVariable` |
| `OS:EnergyManagementSystem:GlobalVariable` | `EnergyManagementSystemGlobalVariable` | `EnergyManagementSystem:GlobalVariable` | Mapped | `translateEnergyManagementSystemGlobalVariable` |
| `OS:EnergyManagementSystem:InternalVariable` | `EnergyManagementSystemInternalVariable` | `EnergyManagementSystem:InternalVariable` | Mapped | `translateEnergyManagementSystemInternalVariable` |
| `OS:EnergyManagementSystem:MeteredOutputVariable` | `EnergyManagementSystemMeteredOutputVariable` | `EnergyManagementSystem:MeteredOutputVariable` | Mapped | `translateEnergyManagementSystemMeteredOutputVariable` |
| `OS:EnergyManagementSystem:OutputVariable` | `EnergyManagementSystemOutputVariable` | `EnergyManagementSystem:OutputVariable` | Mapped | `translateEnergyManagementSystemOutputVariable` |
| `OS:EnergyManagementSystem:Program` | `EnergyManagementSystemProgram` | `EnergyManagementSystem:Program` | Mapped | `translateEnergyManagementSystemProgram` |
| `OS:EnergyManagementSystem:ProgramCallingManager` | `EnergyManagementSystemProgramCallingManager` | `EnergyManagementSystem:ProgramCallingManager` | Mapped | `translateEnergyManagementSystemProgramCallingManager` |
| `OS:EnergyManagementSystem:Sensor` | `EnergyManagementSystemSensor` | `EnergyManagementSystem:Sensor` | Mapped | `translateEnergyManagementSystemSensor` |
| `OS:EnergyManagementSystem:Subroutine` | `EnergyManagementSystemSubroutine` | `EnergyManagementSystem:Subroutine` | Mapped | `translateEnergyManagementSystemSubroutine` |
| `OS:EnergyManagementSystem:TrendVariable` | `EnergyManagementSystemTrendVariable` | `EnergyManagementSystem:TrendVariable` | Mapped | `translateEnergyManagementSystemTrendVariable` |
| `OS:EnvironmentalImpactFactors` | `EnvironmentalImpactFactors` | `EnvironmentalImpactFactors` | Mapped | `translateEnvironmentalImpactFactors` |
| `OS:EvaporativeCooler:Direct:ResearchSpecial` | `EvaporativeCoolerDirectResearchSpecial` | `EvaporativeCooler:Direct:ResearchSpecial` | Mapped | `translateEvaporativeCoolerDirectResearchSpecial` |
| `OS:EvaporativeCooler:Indirect:ResearchSpecial` | `EvaporativeCoolerIndirectResearchSpecial` | `EvaporativeCooler:Indirect:ResearchSpecial`, `OutdoorAir:NodeList` | Mapped | `translateEvaporativeCoolerIndirectResearchSpecial` |
| `OS:EvaporativeFluidCooler:SingleSpeed` | `EvaporativeFluidCoolerSingleSpeed` | `EvaporativeFluidCooler:SingleSpeed` | Mapped | `translateEvaporativeFluidCoolerSingleSpeed` |
| `OS:EvaporativeFluidCooler:TwoSpeed` | `EvaporativeFluidCoolerTwoSpeed` | `EvaporativeFluidCooler:TwoSpeed` | Mapped | `translateEvaporativeFluidCoolerTwoSpeed` |
| `OS:Exterior:FuelEquipment` | `ExteriorFuelEquipment` | `Exterior:FuelEquipment` | Mapped | `translateExteriorFuelEquipment` |
| `OS:Exterior:FuelEquipment:Definition` | `` |  | OS-only / no EP output | `` |
| `OS:Exterior:Lights` | `ExteriorLights` | `Exterior:Lights` | Mapped | `translateExteriorLights` |
| `OS:Exterior:Lights:Definition` | `` |  | OS-only / no EP output | `` |
| `OS:Exterior:WaterEquipment` | `ExteriorWaterEquipment` | `Exterior:WaterEquipment` | Mapped | `translateExteriorWaterEquipment` |
| `OS:Exterior:WaterEquipment:Definition` | `` |  | OS-only / no EP output | `` |
| `OS:External:File` | `` |  | OS-only / no EP output | `` |
| `OS:ExternalInterface` | `ExternalInterface` | `ExternalInterface` | Mapped | `translateExternalInterface` |
| `OS:ExternalInterface:Actuator` | `ExternalInterfaceActuator` | `ExternalInterface:Actuator` | Mapped | `translateExternalInterfaceActuator` |
| `OS:ExternalInterface:FunctionalMockupUnitExport:From:Variable` | `ExternalInterfaceFunctionalMockupUnitExportFromVariable` | `ExternalInterface:FunctionalMockupUnitExport:From:Variable` | Mapped | `translateExternalInterfaceFunctionalMockupUnitExportFromVariable` |
| `OS:ExternalInterface:FunctionalMockupUnitExport:To:Actuator` | `ExternalInterfaceFunctionalMockupUnitExportToActuator` | `ExternalInterface:FunctionalMockupUnitExport:To:Actuator` | Mapped | `translateExternalInterfaceFunctionalMockupUnitExportToActuator` |
| `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule` | `ExternalInterfaceFunctionalMockupUnitExportToSchedule` | `ExternalInterface:FunctionalMockupUnitExport:To:Schedule` | Mapped | `translateExternalInterfaceFunctionalMockupUnitExportToSchedule` |
| `OS:ExternalInterface:FunctionalMockupUnitExport:To:Variable` | `ExternalInterfaceFunctionalMockupUnitExportToVariable` | `ExternalInterface:FunctionalMockupUnitExport:To:Variable` | Mapped | `translateExternalInterfaceFunctionalMockupUnitExportToVariable` |
| `OS:ExternalInterface:FunctionalMockupUnitImport` | `ExternalInterfaceFunctionalMockupUnitImport` | `ExternalInterface:FunctionalMockupUnitImport` | Mapped | `translateExternalInterfaceFunctionalMockupUnitImport` |
| `OS:ExternalInterface:FunctionalMockupUnitImport:From:Variable` | `ExternalInterfaceFunctionalMockupUnitImportFromVariable` | `ExternalInterface:FunctionalMockupUnitImport:From:Variable` | Mapped | `translateExternalInterfaceFunctionalMockupUnitImportFromVariable` |
| `OS:ExternalInterface:FunctionalMockupUnitImport:To:Actuator` | `ExternalInterfaceFunctionalMockupUnitImportToActuator` | `ExternalInterface:FunctionalMockupUnitImport:To:Actuator` | Mapped | `translateExternalInterfaceFunctionalMockupUnitImportToActuator` |
| `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule` | `ExternalInterfaceFunctionalMockupUnitImportToSchedule` | `ExternalInterface:FunctionalMockupUnitImport:To:Schedule` | Mapped | `translateExternalInterfaceFunctionalMockupUnitImportToSchedule` |
| `OS:ExternalInterface:FunctionalMockupUnitImport:To:Variable` | `ExternalInterfaceFunctionalMockupUnitImportToVariable` | `ExternalInterface:FunctionalMockupUnitImport:To:Variable` | Mapped | `translateExternalInterfaceFunctionalMockupUnitImportToVariable` |
| `OS:ExternalInterface:Schedule` | `ExternalInterfaceSchedule` | `ExternalInterface:Schedule` | Mapped | `translateExternalInterfaceSchedule` |
| `OS:ExternalInterface:Variable` | `ExternalInterfaceVariable` | `ExternalInterface:Variable` | Mapped | `translateExternalInterfaceVariable` |
| `OS:Facility` | `` |  | OS-only / no EP output | `` |
| `OS:Fan:ComponentModel` | `FanComponentModel` | `Fan:ComponentModel` | Mapped | `translateFanComponentModel` |
| `OS:Fan:ConstantVolume` | `FanConstantVolume` | `Fan:ConstantVolume` | Mapped | `translateFanConstantVolume` |
| `OS:Fan:OnOff` | `FanOnOff` | `Fan:OnOff` | Mapped | `translateFanOnOff` |
| `OS:Fan:SystemModel` | `FanSystemModel` | `Fan:SystemModel` | Mapped | `translateFanSystemModel` |
| `OS:Fan:VariableVolume` | `FanVariableVolume` | `Fan:VariableVolume` | Mapped | `translateFanVariableVolume` |
| `OS:Fan:ZoneExhaust` | `FanZoneExhaust` | `Fan:ZoneExhaust` | Mapped | `translateFanZoneExhaust` |
| `OS:FluidCooler:SingleSpeed` | `FluidCoolerSingleSpeed` | `FluidCooler:SingleSpeed` | Mapped | `translateFluidCoolerSingleSpeed` |
| `OS:FluidCooler:TwoSpeed` | `FluidCoolerTwoSpeed` | `FluidCooler:TwoSpeed` | Mapped | `translateFluidCoolerTwoSpeed` |
| `OS:Foundation:Kiva` | `FoundationKiva` | `Foundation:Kiva` | Mapped | `translateFoundationKiva` |
| `OS:Foundation:Kiva:Settings` | `FoundationKivaSettings` | `Foundation:Kiva:Settings` | Mapped | `translateFoundationKivaSettings` |
| `OS:FuelFactors` | `FuelFactors` | `FuelFactors` | Mapped | `translateFuelFactors` |
| `OS:GasEquipment` | `GasEquipment` | `GasEquipment` | Mapped | `translateGasEquipment` |
| `OS:GasEquipment:Definition` | `` |  | OS-only / no EP output | `` |
| `OS:Generator:FuelCell` | `GeneratorFuelCell` | `Generator:FuelCell` | Mapped | `translateGeneratorFuelCell` |
| `OS:Generator:FuelCell:AirSupply` | `GeneratorFuelCellAirSupply` | `Generator:FuelCell:AirSupply`, `OutdoorAir:NodeList` | Mapped | `translateGeneratorFuelCellAirSupply` |
| `OS:Generator:FuelCell:AuxiliaryHeater` | `GeneratorFuelCellAuxiliaryHeater` | `Generator:FuelCell:AuxiliaryHeater` | Mapped | `translateGeneratorFuelCellAuxiliaryHeater` |
| `OS:Generator:FuelCell:ElectricalStorage` | `GeneratorFuelCellElectricalStorage` | `Generator:FuelCell:ElectricalStorage` | Mapped | `translateGeneratorFuelCellElectricalStorage` |
| `OS:Generator:FuelCell:ExhaustGasToWaterHeatExchanger` | `GeneratorFuelCellExhaustGasToWaterHeatExchanger` | `Generator:FuelCell:ExhaustGasToWaterHeatExchanger` | Mapped | `translateGeneratorFuelCellExhaustGasToWaterHeatExchanger` |
| `OS:Generator:FuelCell:Inverter` | `GeneratorFuelCellInverter` | `Generator:FuelCell:Inverter` | Mapped | `translateGeneratorFuelCellInverter` |
| `OS:Generator:FuelCell:PowerModule` | `GeneratorFuelCellPowerModule` | `Generator:FuelCell:PowerModule`, `OutdoorAir:NodeList` | Mapped | `translateGeneratorFuelCellPowerModule` |
| `OS:Generator:FuelCell:StackCooler` | `GeneratorFuelCellStackCooler` | `Generator:FuelCell:StackCooler` | Mapped | `translateGeneratorFuelCellStackCooler` |
| `OS:Generator:FuelCell:WaterSupply` | `GeneratorFuelCellWaterSupply` | `Generator:FuelCell:WaterSupply` | Mapped | `translateGeneratorFuelCellWaterSupply` |
| `OS:Generator:FuelSupply` | `GeneratorFuelSupply` | `Generator:FuelSupply` | Mapped | `translateGeneratorFuelSupply` |
| `OS:Generator:MicroTurbine` | `GeneratorMicroTurbine` | `Generator:MicroTurbine` | Mapped | `translateGeneratorMicroTurbine` |
| `OS:Generator:MicroTurbine:HeatRecovery` | `` |  | OS-only / no EP output | `` |
| `OS:Generator:PVWatts` | `GeneratorPVWatts` | `Generator:PVWatts` | Mapped | `translateGeneratorPVWatts` |
| `OS:Generator:Photovoltaic` | `GeneratorPhotovoltaic` | `Generator:Photovoltaic` | Mapped | `translateGeneratorPhotovoltaic` |
| `OS:Generator:WindTurbine` | `GeneratorWindTurbine` | `Generator:WindTurbine` | Mapped | `translateGeneratorWindTurbine` |
| `OS:Glare:Sensor` | `` |  | OS-only / no EP output | `` |
| `OS:GroundHeatExchanger:HorizontalTrench` | `GroundHeatExchangerHorizontalTrench` | `GroundHeatExchanger:HorizontalTrench` | Mapped | `translateGroundHeatExchangerHorizontalTrench` |
| `OS:GroundHeatExchanger:Vertical` | `GroundHeatExchangerVertical` | `GroundHeatExchanger:ResponseFactors`, `GroundHeatExchanger:System`, `GroundHeatExchanger:Vertical:Properties` | Mapped | `translateGroundHeatExchangerVertical` |
| `OS:HVACComponentList` | `` |  | OS-only / no EP output | `` |
| `OS:HeaderedPumps:ConstantSpeed` | `HeaderedPumpsConstantSpeed` | `HeaderedPumps:ConstantSpeed` | Mapped | `translateHeaderedPumpsConstantSpeed` |
| `OS:HeaderedPumps:VariableSpeed` | `HeaderedPumpsVariableSpeed` | `HeaderedPumps:VariableSpeed` | Mapped | `translateHeaderedPumpsVariableSpeed` |
| `OS:HeatBalanceAlgorithm` | `HeatBalanceAlgorithm` | `HeatBalanceAlgorithm` | Mapped | `translateHeatBalanceAlgorithm` |
| `OS:HeatExchanger:AirToAir:SensibleAndLatent` | `HeatExchangerAirToAirSensibleAndLatent` | `HeatExchanger:AirToAir:SensibleAndLatent` | Mapped | `translateHeatExchangerAirToAirSensibleAndLatent` |
| `OS:HeatExchanger:Desiccant:BalancedFlow` | `HeatExchangerDesiccantBalancedFlow` | `HeatExchanger:Desiccant:BalancedFlow` | Mapped | `translateHeatExchangerDesiccantBalancedFlow` |
| `OS:HeatExchanger:Desiccant:BalancedFlow:PerformanceDataType1` | `HeatExchangerDesiccantBalancedFlowPerformanceDataType1` | `HeatExchanger:Desiccant:BalancedFlow:PerformanceDataType1` | Mapped | `translateHeatExchangerDesiccantBalancedFlowPerformanceDataType1` |
| `OS:HeatExchanger:FluidToFluid` | `HeatExchangerFluidToFluid` | `HeatExchanger:FluidToFluid` | Mapped | `translateHeatExchangerFluidToFluid` |
| `OS:HeatPump:AirToWater` | `HeatPumpAirToWater` | `HeatPump:AirToWater`, `OutdoorAir:NodeList` | Mapped | `translateHeatPumpAirToWater` |
| `OS:HeatPump:AirToWater:Cooling` | `` |  | OS-only / no EP output | `` |
| `OS:HeatPump:AirToWater:Cooling:SpeedData` | `` |  | OS-only / no EP output | `` |
| `OS:HeatPump:AirToWater:FuelFired:Cooling` | `HeatPumpAirToWaterFuelFiredCooling` | `HeatPump:AirToWater:FuelFired:Cooling`, `OutdoorAir:Node` | Mapped | `translateHeatPumpAirToWaterFuelFiredCooling` |
| `OS:HeatPump:AirToWater:FuelFired:Heating` | `HeatPumpAirToWaterFuelFiredHeating` | `HeatPump:AirToWater:FuelFired:Heating`, `OutdoorAir:Node` | Mapped | `translateHeatPumpAirToWaterFuelFiredHeating` |
| `OS:HeatPump:AirToWater:Heating` | `` |  | OS-only / no EP output | `` |
| `OS:HeatPump:AirToWater:Heating:SpeedData` | `` |  | OS-only / no EP output | `` |
| `OS:HeatPump:PlantLoop:EIR:Cooling` | `HeatPumpPlantLoopEIRCooling` | `HeatPump:PlantLoop:EIR:Cooling`, `OutdoorAir:NodeList` | Mapped | `translateHeatPumpPlantLoopEIRCooling` |
| `OS:HeatPump:PlantLoop:EIR:Heating` | `HeatPumpPlantLoopEIRHeating` | `HeatPump:PlantLoop:EIR:Heating`, `OutdoorAir:NodeList` | Mapped | `translateHeatPumpPlantLoopEIRHeating` |
| `OS:HeatPump:WaterToWater:EquationFit:Cooling` | `HeatPumpWaterToWaterEquationFitCooling` | `HeatPump:WaterToWater:EquationFit:Cooling` | Mapped | `translateHeatPumpWaterToWaterEquationFitCooling` |
| `OS:HeatPump:WaterToWater:EquationFit:Heating` | `HeatPumpWaterToWaterEquationFitHeating` | `HeatPump:WaterToWater:EquationFit:Heating` | Mapped | `translateHeatPumpWaterToWaterEquationFitHeating` |
| `OS:HotWaterEquipment` | `HotWaterEquipment` | `HotWaterEquipment` | Mapped | `translateHotWaterEquipment` |
| `OS:HotWaterEquipment:Definition` | `` |  | OS-only / no EP output | `` |
| `OS:Humidifier:Steam:Electric` | `HumidifierSteamElectric` | `Humidifier:Steam:Electric` | Mapped | `translateHumidifierSteamElectric` |
| `OS:Humidifier:Steam:Gas` | `HumidifierSteamGas` | `Humidifier:Steam:Gas` | Mapped | `translateHumidifierSteamGas` |
| `OS:IlluminanceMap` | `IlluminanceMap` |  | OS-only / no EP output | `translateIlluminanceMap` |
| `OS:InteriorPartitionSurface` | `InteriorPartitionSurface` | `InternalMass` | Mapped | `translateInteriorPartitionSurface` |
| `OS:InteriorPartitionSurfaceGroup` | `InteriorPartitionSurfaceGroup` |  | OS-only / no EP output | `translateInteriorPartitionSurfaceGroup` |
| `OS:InternalMass` | `InternalMass` | `InternalMass` | Mapped | `translateInternalMass` |
| `OS:InternalMass:Definition` | `` |  | OS-only / no EP output | `` |
| `OS:LifeCycleCost` | `LifeCycleCost` | `LifeCycleCost:NonrecurringCost`, `LifeCycleCost:RecurringCosts` | Mapped | `translateLifeCycleCost` |
| `OS:LifeCycleCost:Parameters` | `LifeCycleCostParameters` | `LifeCycleCost:Parameters` | Mapped | `translateLifeCycleCostParameters` |
| `OS:LifeCycleCost:UsePriceEscalation` | `` |  | OS-only / no EP output | `` |
| `OS:LightingDesignDay` | `` |  | OS-only / no EP output | `` |
| `OS:LightingSimulationControl` | `` |  | OS-only / no EP output | `` |
| `OS:LightingSimulationZone` | `` |  | OS-only / no EP output | `` |
| `OS:Lights` | `Lights` | `Lights` | Mapped | `translateLights` |
| `OS:Lights:Definition` | `` |  | OS-only / no EP output | `` |
| `OS:LoadProfile:Plant` | `LoadProfilePlant` | `LoadProfile:Plant` | Mapped | `translateLoadProfilePlant` |
| `OS:Luminaire` | `Luminaire` | `Lights` | Mapped | `translateLuminaire` |
| `OS:Luminaire:Definition` | `` |  | OS-only / no EP output | `` |
| `OS:Material` | `StandardOpaqueMaterial` | `Material` | Mapped | `translateStandardOpaqueMaterial` |
| `OS:Material:AirGap` | `AirGap` | `Material:AirGap` | Mapped | `translateAirGap` |
| `OS:Material:InfraredTransparent` | `InfraredTransparentMaterial` | `Material:InfraredTransparent` | Mapped | `translateInfraredTransparentMaterial` |
| `OS:Material:NoMass` | `MasslessOpaqueMaterial` | `Material:NoMass` | Mapped | `translateMasslessOpaqueMaterial` |
| `OS:Material:RoofVegetation` | `RoofVegetation` | `Material:RoofVegetation` | Mapped | `translateRoofVegetation` |
| `OS:MaterialProperty:GlazingSpectralData` | `MaterialPropertyGlazingSpectralData` | `MaterialProperty:GlazingSpectralData` | Mapped | `translateMaterialPropertyGlazingSpectralData` |
| `OS:MaterialProperty:MoisturePenetrationDepth:Settings` | `MaterialPropertyMoisturePenetrationDepthSettings` | `MaterialProperty:MoisturePenetrationDepth:Settings` | Mapped | `translateMaterialPropertyMoisturePenetrationDepthSettings` |
| `OS:MaterialProperty:PhaseChange` | `MaterialPropertyPhaseChange` | `MaterialProperty:PhaseChange` | Mapped | `translateMaterialPropertyPhaseChange` |
| `OS:MaterialProperty:PhaseChangeHysteresis` | `MaterialPropertyPhaseChangeHysteresis` | `MaterialProperty:PhaseChangeHysteresis` | Mapped | `translateMaterialPropertyPhaseChangeHysteresis` |
| `OS:Meter:Custom` | `MeterCustom` | `Meter:Custom` | Mapped | `translateMeterCustom` |
| `OS:Meter:CustomDecrement` | `MeterCustomDecrement` | `Meter:CustomDecrement` | Mapped | `translateMeterCustomDecrement` |
| `OS:ModelObjectList` | `` |  | OS-only / no EP output | `` |
| `OS:Node` | `Node` |  | OS-only / no EP output | `translateNode` |
| `OS:OtherEquipment` | `OtherEquipment` | `OtherEquipment` | Mapped | `translateOtherEquipment` |
| `OS:OtherEquipment:Definition` | `` |  | OS-only / no EP output | `` |
| `OS:Output:Constructions` | `OutputConstructions` | `Output:Constructions` | Mapped | `translateOutputConstructions` |
| `OS:Output:DebuggingData` | `OutputDebuggingData` | `Output:DebuggingData` | Mapped | `translateOutputDebuggingData` |
| `OS:Output:Diagnostics` | `OutputDiagnostics` | `Output:Diagnostics` | Mapped | `translateOutputDiagnostics` |
| `OS:Output:EnergyManagementSystem` | `OutputEnergyManagementSystem` | `Output:EnergyManagementSystem` | Mapped | `translateOutputEnergyManagementSystem` |
| `OS:Output:EnvironmentalImpactFactors` | `OutputEnvironmentalImpactFactors` | `Output:EnvironmentalImpactFactors` | Mapped | `translateOutputEnvironmentalImpactFactors` |
| `OS:Output:JSON` | `OutputJSON` | `Output:JSON` | Mapped | `translateOutputJSON` |
| `OS:Output:Meter` | `OutputMeter` |  | OS-only / no EP output | `translateOutputMeter` |
| `OS:Output:SQLite` | `OutputSQLite` | `Output:SQLite` | Mapped | `translateOutputSQLite` |
| `OS:Output:Schedules` | `OutputSchedules` | `Output:Schedules` | Mapped | `translateOutputSchedules` |
| `OS:Output:Table:Annual` | `OutputTableAnnual` | `Output:Table:Annual` | Mapped | `translateOutputTableAnnual` |
| `OS:Output:Table:Monthly` | `OutputTableMonthly` | `Output:Table:Monthly` | Mapped | `translateOutputTableMonthly` |
| `OS:Output:Table:SummaryReports` | `OutputTableSummaryReports` | `Output:Table:SummaryReports` | Mapped | `translateOutputTableSummaryReports` |
| `OS:Output:Variable` | `OutputVariable` | `Output:Variable` | Mapped | `translateOutputVariable` |
| `OS:OutputControl:Files` | `OutputControlFiles` | `OutputControl:Files` | Mapped | `translateOutputControlFiles` |
| `OS:OutputControl:ReportingTolerances` | `OutputControlReportingTolerances` | `OutputControl:ReportingTolerances` | Mapped | `translateOutputControlReportingTolerances` |
| `OS:OutputControl:ResilienceSummaries` | `OutputControlResilienceSummaries` | `OutputControl:ResilienceSummaries` | Mapped | `translateOutputControlResilienceSummaries` |
| `OS:OutputControl:Table:Style` | `OutputControlTableStyle` | `OutputControl:Table:Style` | Mapped | `translateOutputControlTableStyle` |
| `OS:OutputControl:Timestamp` | `OutputControlTimestamp` | `OutputControl:Timestamp` | Mapped | `translateOutputControlTimestamp` |
| `OS:People` | `People` | `People` | Mapped | `translatePeople` |
| `OS:People:Definition` | `` |  | OS-only / no EP output | `` |
| `OS:PerformancePrecisionTradeoffs` | `PerformancePrecisionTradeoffs` | `PerformancePrecisionTradeoffs` | Mapped | `translatePerformancePrecisionTradeoffs` |
| `OS:PhotovoltaicPerformance:Sandia` | `PhotovoltaicPerformanceSandia` | `PhotovoltaicPerformance:Sandia` | Mapped | `translatePhotovoltaicPerformanceSandia` |
| `OS:PhotovoltaicPerformance:Simple` | `PhotovoltaicPerformanceSimple` | `PhotovoltaicPerformance:Simple` | Mapped | `translatePhotovoltaicPerformanceSimple` |
| `OS:Pipe:Adiabatic` | `PipeAdiabatic` | `Pipe:Adiabatic` | Mapped | `translatePipeAdiabatic` |
| `OS:Pipe:Indoor` | `PipeIndoor` | `Pipe:Indoor` | Mapped | `translatePipeIndoor` |
| `OS:Pipe:Outdoor` | `PipeOutdoor` | `OutdoorAir:NodeList`, `Pipe:Outdoor` | Mapped | `translatePipeOutdoor` |
| `OS:PlantComponent:TemperatureSource` | `PlantComponentTemperatureSource` | `PlantComponent:TemperatureSource` | Mapped | `translatePlantComponentTemperatureSource` |
| `OS:PlantComponent:UserDefined` | `PlantComponentUserDefined` | `PlantComponent:UserDefined` | Mapped | `translatePlantComponentUserDefined` |
| `OS:PlantEquipmentOperation:CoolingLoad` | `PlantEquipmentOperationCoolingLoad` | `PlantEquipmentList`, `PlantEquipmentOperation:CoolingLoad` | Mapped | `translatePlantEquipmentOperationCoolingLoad` |
| `OS:PlantEquipmentOperation:HeatingLoad` | `PlantEquipmentOperationHeatingLoad` | `PlantEquipmentList`, `PlantEquipmentOperation:HeatingLoad` | Mapped | `translatePlantEquipmentOperationHeatingLoad` |
| `OS:PlantEquipmentOperation:OutdoorDewpoint` | `PlantEquipmentOperationOutdoorDewpoint` | `PlantEquipmentList`, `PlantEquipmentOperation:OutdoorDewpoint` | Mapped | `translatePlantEquipmentOperationOutdoorDewpoint` |
| `OS:PlantEquipmentOperation:OutdoorDewpointDifference` | `PlantEquipmentOperationOutdoorDewpointDifference` | `PlantEquipmentList`, `PlantEquipmentOperation:OutdoorDewpointDifference` | Mapped | `translatePlantEquipmentOperationOutdoorDewpointDifference` |
| `OS:PlantEquipmentOperation:OutdoorDryBulb` | `PlantEquipmentOperationOutdoorDryBulb` | `PlantEquipmentList`, `PlantEquipmentOperation:OutdoorDryBulb` | Mapped | `translatePlantEquipmentOperationOutdoorDryBulb` |
| `OS:PlantEquipmentOperation:OutdoorDryBulbDifference` | `PlantEquipmentOperationOutdoorDryBulbDifference` | `PlantEquipmentList`, `PlantEquipmentOperation:OutdoorDryBulbDifference` | Mapped | `translatePlantEquipmentOperationOutdoorDryBulbDifference` |
| `OS:PlantEquipmentOperation:OutdoorRelativeHumidity` | `PlantEquipmentOperationOutdoorRelativeHumidity` | `PlantEquipmentList`, `PlantEquipmentOperation:OutdoorRelativeHumidity` | Mapped | `translatePlantEquipmentOperationOutdoorRelativeHumidity` |
| `OS:PlantEquipmentOperation:OutdoorWetBulb` | `PlantEquipmentOperationOutdoorWetBulb` | `PlantEquipmentList`, `PlantEquipmentOperation:OutdoorWetBulb` | Mapped | `translatePlantEquipmentOperationOutdoorWetBulb` |
| `OS:PlantEquipmentOperation:OutdoorWetBulbDifference` | `PlantEquipmentOperationOutdoorWetBulbDifference` | `PlantEquipmentList`, `PlantEquipmentOperation:OutdoorWetBulbDifference` | Mapped | `translatePlantEquipmentOperationOutdoorWetBulbDifference` |
| `OS:PlantLoop` | `PlantLoop` | `Branch`, `BranchList`, `ConnectorList`, `Connector:Mixer`, `Connector:Splitter`, `Pipe:Adiabatic`, `PlantEquipmentList`, `PlantEquipmentOperationSchemes`, `PlantEquipmentOperation:ComponentSetpoint`, `PlantEquipmentOperation:CoolingLoad`, `PlantEquipmentOperation:HeatingLoad`, `PlantEquipmentOperation:Uncontrolled`, `PlantLoop` | Mapped | `translatePlantLoop` |
| `OS:PortList` | `PortList` | `NodeList` | Mapped | `translatePortList` |
| `OS:ProgramControl` | `` |  | OS-only / no EP output | `` |
| `OS:Pump:ConstantSpeed` | `PumpConstantSpeed` | `Pump:ConstantSpeed` | Mapped | `translatePumpConstantSpeed` |
| `OS:Pump:VariableSpeed` | `PumpVariableSpeed` | `Pump:VariableSpeed` | Mapped | `translatePumpVariableSpeed` |
| `OS:PythonPlugin:Instance` | `PythonPluginInstance` | `PythonPlugin:Instance`, `PythonPlugin:SearchPaths` | Mapped | `translatePythonPluginInstance` |
| `OS:PythonPlugin:OutputVariable` | `PythonPluginOutputVariable` | `PythonPlugin:OutputVariable` | Mapped | `translatePythonPluginOutputVariable` |
| `OS:PythonPlugin:SearchPaths` | `PythonPluginSearchPaths` | `PythonPlugin:SearchPaths` | Mapped | `translatePythonPluginSearchPaths` |
| `OS:PythonPlugin:TrendVariable` | `PythonPluginTrendVariable` | `PythonPlugin:TrendVariable` | Mapped | `translatePythonPluginTrendVariable` |
| `OS:PythonPlugin:Variable` | `PythonPluginVariable` | `PythonPlugin:Variables` | Mapped | `translatePythonPluginVariable` |
| `OS:RadianceParameters` | `` |  | OS-only / no EP output | `` |
| `OS:Refrigeration:AirChiller` | `RefrigerationAirChiller` | `Refrigeration:AirChiller` | Mapped | `translateRefrigerationAirChiller` |
| `OS:Refrigeration:Case` | `RefrigerationCase` | `Refrigeration:Case` | Mapped | `translateRefrigerationCase` |
| `OS:Refrigeration:Compressor` | `RefrigerationCompressor` | `Refrigeration:Compressor` | Mapped | `translateRefrigerationCompressor` |
| `OS:Refrigeration:CompressorRack` | `RefrigerationCompressorRack` | `Refrigeration:CaseAndWalkInList`, `Refrigeration:CompressorRack` | Mapped | `translateRefrigerationCompressorRack` |
| `OS:Refrigeration:Condenser:AirCooled` | `RefrigerationCondenserAirCooled` | `Refrigeration:Condenser:AirCooled` | Mapped | `translateRefrigerationCondenserAirCooled` |
| `OS:Refrigeration:Condenser:Cascade` | `RefrigerationCondenserCascade` | `Refrigeration:Condenser:Cascade` | Mapped | `translateRefrigerationCondenserCascade` |
| `OS:Refrigeration:Condenser:EvaporativeCooled` | `RefrigerationCondenserEvaporativeCooled` | `Refrigeration:Condenser:EvaporativeCooled` | Mapped | `translateRefrigerationCondenserEvaporativeCooled` |
| `OS:Refrigeration:Condenser:WaterCooled` | `RefrigerationCondenserWaterCooled` | `Refrigeration:Condenser:WaterCooled` | Mapped | `translateRefrigerationCondenserWaterCooled` |
| `OS:Refrigeration:DefrostCycleParameters` | `` |  | OS-only / no EP output | `` |
| `OS:Refrigeration:GasCooler:AirCooled` | `RefrigerationGasCoolerAirCooled` | `Refrigeration:GasCooler:AirCooled` | Mapped | `translateRefrigerationGasCoolerAirCooled` |
| `OS:Refrigeration:SecondarySystem` | `RefrigerationSecondarySystem` | `Refrigeration:CaseAndWalkInList`, `Refrigeration:SecondarySystem` | Mapped | `translateRefrigerationSecondarySystem` |
| `OS:Refrigeration:Subcooler:LiquidSuction` | `RefrigerationSubcoolerLiquidSuction` | `Refrigeration:Subcooler` | Mapped | `translateRefrigerationSubcoolerLiquidSuction` |
| `OS:Refrigeration:Subcooler:Mechanical` | `RefrigerationSubcoolerMechanical` | `Refrigeration:Subcooler` | Mapped | `translateRefrigerationSubcoolerMechanical` |
| `OS:Refrigeration:System` | `RefrigerationSystem` | `Refrigeration:CaseAndWalkInList`, `Refrigeration:CompressorList`, `Refrigeration:System`, `Refrigeration:TransferLoadList` | Mapped | `translateRefrigerationSystem` |
| `OS:Refrigeration:TranscriticalSystem` | `RefrigerationTranscriticalSystem` | `Refrigeration:CaseAndWalkInList`, `Refrigeration:CompressorList`, `Refrigeration:TranscriticalSystem` | Mapped | `translateRefrigerationTranscriticalSystem` |
| `OS:Refrigeration:WalkIn` | `RefrigerationWalkIn` | `Refrigeration:WalkIn` | Mapped | `translateRefrigerationWalkIn` |
| `OS:Refrigeration:WalkIn:ZoneBoundary` | `` |  | OS-only / no EP output | `` |
| `OS:Rendering:Color` | `` |  | OS-only / no EP output | `` |
| `OS:RunPeriod` | `RunPeriod` | `RunPeriod` | Mapped | `translateRunPeriod` |
| `OS:RunPeriodControl:DaylightSavingTime` | `RunPeriodControlDaylightSavingTime` | `RunPeriodControl:DaylightSavingTime` | Mapped | `translateRunPeriodControlDaylightSavingTime` |
| `OS:RunPeriodControl:SpecialDays` | `RunPeriodControlSpecialDays` | `RunPeriodControl:SpecialDays` | Mapped | `translateRunPeriodControlSpecialDays` |
| `OS:Schedule:Compact` | `ScheduleCompact` | `Schedule:Compact` | Mapped | `translateScheduleCompact` |
| `OS:Schedule:Constant` | `ScheduleConstant` | `Schedule:Constant` | Mapped | `translateScheduleConstant` |
| `OS:Schedule:Day` | `ScheduleDay` | `Schedule:Day:Interval` | Mapped | `translateScheduleDay` |
| `OS:Schedule:File` | `ScheduleFile` | `Schedule:File` | Mapped | `translateScheduleFile` |
| `OS:Schedule:FixedInterval` | `ScheduleFixedInterval` | `Schedule:Compact` | Mapped | `translateScheduleFixedInterval` |
| `OS:Schedule:Rule` | `` |  | OS-only / no EP output | `` |
| `OS:Schedule:Ruleset` | `ScheduleRuleset` | `Schedule:Year` | Mapped | `translateScheduleRuleset` |
| `OS:Schedule:VariableInterval` | `ScheduleVariableInterval` | `Schedule:Compact` | Mapped | `translateScheduleVariableInterval` |
| `OS:Schedule:Week` | `ScheduleWeek` | `Schedule:Week:Daily` | Mapped | `translateScheduleWeek` |
| `OS:Schedule:Year` | `ScheduleYear` | `Schedule:Year` | Mapped | `translateScheduleYear` |
| `OS:ScheduleTypeLimits` | `ScheduleTypeLimits` | `ScheduleTypeLimits` | Mapped | `translateScheduleTypeLimits` |
| `OS:SetpointManager:Coldest` | `SetpointManagerColdest` | `SetpointManager:Coldest` | Mapped | `translateSetpointManagerColdest` |
| `OS:SetpointManager:FollowGroundTemperature` | `SetpointManagerFollowGroundTemperature` | `SetpointManager:FollowGroundTemperature` | Mapped | `translateSetpointManagerFollowGroundTemperature` |
| `OS:SetpointManager:FollowOutdoorAirTemperature` | `SetpointManagerFollowOutdoorAirTemperature` | `SetpointManager:FollowOutdoorAirTemperature` | Mapped | `translateSetpointManagerFollowOutdoorAirTemperature` |
| `OS:SetpointManager:FollowSystemNodeTemperature` | `SetpointManagerFollowSystemNodeTemperature` | `SetpointManager:FollowSystemNodeTemperature` | Mapped | `translateSetpointManagerFollowSystemNodeTemperature` |
| `OS:SetpointManager:MixedAir` | `SetpointManagerMixedAir` | `SetpointManager:MixedAir` | Mapped | `translateSetpointManagerMixedAir` |
| `OS:SetpointManager:MultiZone:Cooling:Average` | `SetpointManagerMultiZoneCoolingAverage` | `SetpointManager:MultiZone:Cooling:Average` | Mapped | `translateSetpointManagerMultiZoneCoolingAverage` |
| `OS:SetpointManager:MultiZone:Heating:Average` | `SetpointManagerMultiZoneHeatingAverage` | `SetpointManager:MultiZone:Heating:Average` | Mapped | `translateSetpointManagerMultiZoneHeatingAverage` |
| `OS:SetpointManager:MultiZone:Humidity:Maximum` | `SetpointManagerMultiZoneHumidityMaximum` | `SetpointManager:MultiZone:Humidity:Maximum` | Mapped | `translateSetpointManagerMultiZoneHumidityMaximum` |
| `OS:SetpointManager:MultiZone:Humidity:Minimum` | `SetpointManagerMultiZoneHumidityMinimum` | `SetpointManager:MultiZone:Humidity:Minimum` | Mapped | `translateSetpointManagerMultiZoneHumidityMinimum` |
| `OS:SetpointManager:MultiZone:MaximumHumidity:Average` | `SetpointManagerMultiZoneMaximumHumidityAverage` | `SetpointManager:MultiZone:MaximumHumidity:Average` | Mapped | `translateSetpointManagerMultiZoneMaximumHumidityAverage` |
| `OS:SetpointManager:MultiZone:MinimumHumidity:Average` | `SetpointManagerMultiZoneMinimumHumidityAverage` | `SetpointManager:MultiZone:MinimumHumidity:Average` | Mapped | `translateSetpointManagerMultiZoneMinimumHumidityAverage` |
| `OS:SetpointManager:OutdoorAirPretreat` | `SetpointManagerOutdoorAirPretreat` | `SetpointManager:OutdoorAirPretreat` | Mapped | `translateSetpointManagerOutdoorAirPretreat` |
| `OS:SetpointManager:OutdoorAirReset` | `SetpointManagerOutdoorAirReset` | `SetpointManager:OutdoorAirReset` | Mapped | `translateSetpointManagerOutdoorAirReset` |
| `OS:SetpointManager:Scheduled` | `SetpointManagerScheduled` | `SetpointManager:Scheduled` | Mapped | `translateSetpointManagerScheduled` |
| `OS:SetpointManager:Scheduled:DualSetpoint` | `SetpointManagerScheduledDualSetpoint` | `SetpointManager:Scheduled:DualSetpoint` | Mapped | `translateSetpointManagerScheduledDualSetpoint` |
| `OS:SetpointManager:SingleZone:Cooling` | `SetpointManagerSingleZoneCooling` | `SetpointManager:SingleZone:Cooling` | Mapped | `translateSetpointManagerSingleZoneCooling` |
| `OS:SetpointManager:SingleZone:Heating` | `SetpointManagerSingleZoneHeating` | `SetpointManager:SingleZone:Heating` | Mapped | `translateSetpointManagerSingleZoneHeating` |
| `OS:SetpointManager:SingleZone:Humidity:Maximum` | `SetpointManagerSingleZoneHumidityMaximum` | `SetpointManager:SingleZone:Humidity:Maximum` | Mapped | `translateSetpointManagerSingleZoneHumidityMaximum` |
| `OS:SetpointManager:SingleZone:Humidity:Minimum` | `SetpointManagerSingleZoneHumidityMinimum` | `SetpointManager:SingleZone:Humidity:Minimum` | Mapped | `translateSetpointManagerSingleZoneHumidityMinimum` |
| `OS:SetpointManager:SingleZone:OneStageCooling` | `SetpointManagerSingleZoneOneStageCooling` | `SetpointManager:SingleZone:OneStageCooling` | Mapped | `translateSetpointManagerSingleZoneOneStageCooling` |
| `OS:SetpointManager:SingleZone:OneStageHeating` | `SetpointManagerSingleZoneOneStageHeating` | `SetpointManager:SingleZone:OneStageHeating` | Mapped | `translateSetpointManagerSingleZoneOneStageHeating` |
| `OS:SetpointManager:SingleZone:Reheat` | `SetpointManagerSingleZoneReheat` | `SetpointManager:SingleZone:Reheat` | Mapped | `translateSetpointManagerSingleZoneReheat` |
| `OS:SetpointManager:SystemNodeReset:Humidity` | `SetpointManagerSystemNodeResetHumidity` | `SetpointManager:SystemNodeReset:Humidity` | Mapped | `translateSetpointManagerSystemNodeResetHumidity` |
| `OS:SetpointManager:SystemNodeReset:Temperature` | `SetpointManagerSystemNodeResetTemperature` | `SetpointManager:SystemNodeReset:Temperature` | Mapped | `translateSetpointManagerSystemNodeResetTemperature` |
| `OS:SetpointManager:Warmest` | `SetpointManagerWarmest` | `SetpointManager:Warmest` | Mapped | `translateSetpointManagerWarmest` |
| `OS:SetpointManager:WarmestTemperatureFlow` | `SetpointManagerWarmestTemperatureFlow` | `SetpointManager:WarmestTemperatureFlow` | Mapped | `translateSetpointManagerWarmestTemperatureFlow` |
| `OS:ShadingControl` | `ShadingControl` | `WindowShadingControl` | Mapped | `translateShadingControl` |
| `OS:ShadingSurface` | `ShadingSurface` |  | OS-only / no EP output | `translateShadingSurface` |
| `OS:ShadingSurfaceGroup` | `ShadingSurfaceGroup` |  | OS-only / no EP output | `translateShadingSurfaceGroup` |
| `OS:ShadowCalculation` | `ShadowCalculation` | `ShadowCalculation`, `ZoneList` | Mapped | `translateShadowCalculation` |
| `OS:SimulationControl` | `SimulationControl` | `SimulationControl` | Mapped | `translateSimulationControl` |
| `OS:Site` | `Site` | `Site:Location` | Mapped | `translateSite` |
| `OS:Site:GroundReflectance` | `SiteGroundReflectance` | `Site:GroundReflectance` | Mapped | `translateSiteGroundReflectance` |
| `OS:Site:GroundTemperature:BuildingSurface` | `SiteGroundTemperatureBuildingSurface` | `Site:GroundTemperature:BuildingSurface` | Mapped | `translateSiteGroundTemperatureBuildingSurface` |
| `OS:Site:GroundTemperature:Deep` | `SiteGroundTemperatureDeep` | `Site:GroundTemperature:Deep` | Mapped | `translateSiteGroundTemperatureDeep` |
| `OS:Site:GroundTemperature:FCfactorMethod` | `SiteGroundTemperatureFCfactorMethod` | `Site:GroundTemperature:FCfactorMethod` | Mapped | `translateSiteGroundTemperatureFCfactorMethod` |
| `OS:Site:GroundTemperature:Shallow` | `SiteGroundTemperatureShallow` | `Site:GroundTemperature:Shallow` | Mapped | `translateSiteGroundTemperatureShallow` |
| `OS:Site:GroundTemperature:Undisturbed:KusudaAchenbach` | `SiteGroundTemperatureUndisturbedKusudaAchenbach` | `Site:GroundTemperature:Undisturbed:KusudaAchenbach` | Mapped | `translateSiteGroundTemperatureUndisturbedKusudaAchenbach` |
| `OS:Site:GroundTemperature:Undisturbed:Xing` | `SiteGroundTemperatureUndisturbedXing` | `Site:GroundTemperature:Undisturbed:Xing` | Mapped | `translateSiteGroundTemperatureUndisturbedXing` |
| `OS:Site:WaterMainsTemperature` | `SiteWaterMainsTemperature` | `Site:WaterMainsTemperature` | Mapped | `translateSiteWaterMainsTemperature` |
| `OS:Sizing:Parameters` | `SizingParameters` | `Sizing:Parameters` | Mapped | `translateSizingParameters` |
| `OS:Sizing:Plant` | `SizingPlant` | `Sizing:Plant` | Mapped | `translateSizingPlant` |
| `OS:Sizing:System` | `SizingSystem` | `Sizing:System` | Mapped | `translateSizingSystem` |
| `OS:Sizing:Zone` | `SizingZone` | `DesignSpecification:ZoneAirDistribution`, `Sizing:Zone` | Mapped | `translateSizingZone` |
| `OS:SizingPeriod:DesignDay` | `DesignDay` | `SizingPeriod:DesignDay` | Mapped | `translateDesignDay` |
| `OS:SizingPeriod:WeatherFileConditionType` | `` |  | OS-only / no EP output | `` |
| `OS:SizingPeriod:WeatherFileDays` | `` |  | OS-only / no EP output | `` |
| `OS:SolarCollector:FlatPlate:PhotovoltaicThermal` | `SolarCollectorFlatPlatePhotovoltaicThermal` | `SolarCollector:FlatPlate:PhotovoltaicThermal` | Mapped | `translateSolarCollectorFlatPlatePhotovoltaicThermal` |
| `OS:SolarCollector:FlatPlate:Water` | `SolarCollectorFlatPlateWater` | `SolarCollector:FlatPlate:Water` | Mapped | `translateSolarCollectorFlatPlateWater` |
| `OS:SolarCollector:IntegralCollectorStorage` | `SolarCollectorIntegralCollectorStorage` | `SolarCollector:IntegralCollectorStorage` | Mapped | `translateSolarCollectorIntegralCollectorStorage` |
| `OS:SolarCollectorPerformance:FlatPlate` | `SolarCollectorPerformanceFlatPlate` | `SolarCollectorPerformance:FlatPlate` | Mapped | `translateSolarCollectorPerformanceFlatPlate` |
| `OS:SolarCollectorPerformance:IntegralCollectorStorage` | `SolarCollectorPerformanceIntegralCollectorStorage` | `SolarCollectorPerformance:IntegralCollectorStorage` | Mapped | `translateSolarCollectorPerformanceIntegralCollectorStorage` |
| `OS:SolarCollectorPerformance:PhotovoltaicThermal:BIPVT` | `SolarCollectorPerformancePhotovoltaicThermalBIPVT` | `SolarCollectorPerformance:PhotovoltaicThermal:BIPVT` | Mapped | `translateSolarCollectorPerformancePhotovoltaicThermalBIPVT` |
| `OS:SolarCollectorPerformance:PhotovoltaicThermal:Simple` | `SolarCollectorPerformancePhotovoltaicThermalSimple` | `SolarCollectorPerformance:PhotovoltaicThermal:Simple` | Mapped | `translateSolarCollectorPerformancePhotovoltaicThermalSimple` |
| `OS:Space` | `Space` | `Space` | Mapped | `translateSpace` |
| `OS:SpaceInfiltration:DesignFlowRate` | `SpaceInfiltrationDesignFlowRate` | `ZoneInfiltration:DesignFlowRate` | Mapped | `translateSpaceInfiltrationDesignFlowRate` |
| `OS:SpaceInfiltration:EffectiveLeakageArea` | `SpaceInfiltrationEffectiveLeakageArea` | `ZoneInfiltration:EffectiveLeakageArea` | Mapped | `translateSpaceInfiltrationEffectiveLeakageArea` |
| `OS:SpaceInfiltration:FlowCoefficient` | `SpaceInfiltrationFlowCoefficient` | `ZoneInfiltration:FlowCoefficient` | Mapped | `translateSpaceInfiltrationFlowCoefficient` |
| `OS:SpaceType` | `SpaceType` | `SpaceList`, `ZoneList` | Mapped | `translateSpaceType` |
| `OS:Splitter` | `` |  | OS-only / no EP output | `` |
| `OS:StandardsInformation:Construction` | `` |  | OS-only / no EP output | `` |
| `OS:StandardsInformation:Material` | `` |  | OS-only / no EP output | `` |
| `OS:SteamEquipment` | `SteamEquipment` | `SteamEquipment` | Mapped | `translateSteamEquipment` |
| `OS:SteamEquipment:Definition` | `` |  | OS-only / no EP output | `` |
| `OS:SubSurface` | `SubSurface` | `FenestrationSurface:Detailed` | Mapped | `translateSubSurface` |
| `OS:Surface` | `Surface` | `BuildingSurface:Detailed` | Mapped | `translateSurface` |
| `OS:SurfaceControl:MovableInsulation` | `SurfaceControlMovableInsulation` | `SurfaceControl:MovableInsulation` | Mapped | `translateSurfaceControlMovableInsulation` |
| `OS:SurfaceConvectionAlgorithm:Inside` | `InsideSurfaceConvectionAlgorithm` | `SurfaceConvectionAlgorithm:Inside` | Mapped | `translateInsideSurfaceConvectionAlgorithm` |
| `OS:SurfaceConvectionAlgorithm:Outside` | `OutsideSurfaceConvectionAlgorithm` | `SurfaceConvectionAlgorithm:Outside` | Mapped | `translateOutsideSurfaceConvectionAlgorithm` |
| `OS:SurfaceProperty:ConvectionCoefficients` | `SurfacePropertyConvectionCoefficients` | `SurfaceProperty:ConvectionCoefficients` | Mapped | `translateSurfacePropertyConvectionCoefficients` |
| `OS:SurfaceProperty:ConvectionCoefficients:MultipleSurface` | `SurfacePropertyConvectionCoefficientsMultipleSurface` | `SurfaceProperty:ConvectionCoefficients:MultipleSurface` | Mapped | `translateSurfacePropertyConvectionCoefficientsMultipleSurface` |
| `OS:SurfaceProperty:ExposedFoundationPerimeter` | `SurfacePropertyExposedFoundationPerimeter` | `SurfaceProperty:ExposedFoundationPerimeter` | Mapped | `translateSurfacePropertyExposedFoundationPerimeter` |
| `OS:SurfaceProperty:GroundSurfaces` | `SurfacePropertyGroundSurfaces` | `SurfaceProperty:GroundSurfaces` | Mapped | `translateSurfacePropertyGroundSurfaces` |
| `OS:SurfaceProperty:IncidentSolarMultiplier` | `SurfacePropertyIncidentSolarMultiplier` | `SurfaceProperty:IncidentSolarMultiplier` | Mapped | `translateSurfacePropertyIncidentSolarMultiplier` |
| `OS:SurfaceProperty:LocalEnvironment` | `SurfacePropertyLocalEnvironment` | `SurfaceProperty:LocalEnvironment` | Mapped | `translateSurfacePropertyLocalEnvironment` |
| `OS:SurfaceProperty:OtherSideCoefficients` | `SurfacePropertyOtherSideCoefficients` | `SurfaceProperty:OtherSideCoefficients` | Mapped | `translateSurfacePropertyOtherSideCoefficients` |
| `OS:SurfaceProperty:OtherSideConditionsModel` | `SurfacePropertyOtherSideConditionsModel` | `SurfaceProperty:OtherSideConditionsModel` | Mapped | `translateSurfacePropertyOtherSideConditionsModel` |
| `OS:SurfaceProperty:SurroundingSurfaces` | `SurfacePropertySurroundingSurfaces` | `SurfaceProperty:SurroundingSurfaces` | Mapped | `translateSurfacePropertySurroundingSurfaces` |
| `OS:SwimmingPool:Indoor` | `SwimmingPoolIndoor` | `SwimmingPool:Indoor` | Mapped | `translateSwimmingPoolIndoor` |
| `OS:Table:IndependentVariable` | `TableIndependentVariable` | `Table:IndependentVariable` | Mapped | `translateTableIndependentVariable` |
| `OS:Table:Lookup` | `TableLookup` | `Table:IndependentVariableList`, `Table:Lookup` | Mapped | `translateTableLookup` |
| `OS:Table:MultiVariableLookup` | `TableMultiVariableLookup` | `Table:IndependentVariable`, `Table:IndependentVariableList`, `Table:Lookup` | Mapped | `translateTableMultiVariableLookup` |
| `OS:TemperingValve` | `TemperingValve` | `TemperingValve` | Mapped | `translateTemperingValve` |
| `OS:ThermalStorage:ChilledWater:Stratified` | `ThermalStorageChilledWaterStratified` | `OutdoorAir:NodeList`, `ThermalStorage:ChilledWater:Stratified` | Mapped | `translateThermalStorageChilledWaterStratified` |
| `OS:ThermalStorage:Ice:Detailed` | `ThermalStorageIceDetailed` | `ThermalStorage:Ice:Detailed` | Mapped | `translateThermalStorageIceDetailed` |
| `OS:ThermalZone` | `ThermalZone` | `Daylighting:Controls`, `Daylighting:ReferencePoint`, `DesignSpecification:OutdoorAir`, `HVACTemplate:Zone:IdealLoadsAirSystem`, `Output:IlluminanceMap`, `ScheduleTypeLimits`, `Schedule:Compact`, `Zone`, `ZoneControl:Thermostat`, `ZoneHVAC:EquipmentConnections`, `ZoneVentilation:DesignFlowRate` | Mapped | `translateThermalZone` |
| `OS:ThermostatSetpoint:DualSetpoint` | `ThermostatSetpointDualSetpoint` | `ThermostatSetpoint:DualSetpoint`, `ThermostatSetpoint:SingleCooling`, `ThermostatSetpoint:SingleHeating` | Mapped | `translateThermostatSetpointDualSetpoint` |
| `OS:Timestep` | `Timestep` | `Timestep` | Mapped | `translateTimestep` |
| `OS:UnitarySystemPerformance:Multispeed` | `UnitarySystemPerformanceMultispeed` | `UnitarySystemPerformance:Multispeed` | Mapped | `translateUnitarySystemPerformanceMultispeed` |
| `OS:UtilityBill` | `` |  | OS-only / no EP output | `` |
| `OS:UtilityCost:Charge:Block` | `` |  | OS-only / no EP output | `` |
| `OS:UtilityCost:Charge:Simple` | `` |  | OS-only / no EP output | `` |
| `OS:UtilityCost:Computation` | `` |  | OS-only / no EP output | `` |
| `OS:UtilityCost:Qualify` | `` |  | OS-only / no EP output | `` |
| `OS:UtilityCost:Ratchet` | `` |  | OS-only / no EP output | `` |
| `OS:UtilityCost:Tariff` | `` |  | OS-only / no EP output | `` |
| `OS:UtilityCost:Variable` | `` |  | OS-only / no EP output | `` |
| `OS:Version` | `Version` | `Version` | Mapped | `translateVersion` |
| `OS:WaterHeater:HeatPump` | `WaterHeaterHeatPump` | `WaterHeater:HeatPump:PumpedCondenser` | Mapped | `translateWaterHeaterHeatPump` |
| `OS:WaterHeater:HeatPump:WrappedCondenser` | `WaterHeaterHeatPumpWrappedCondenser` | `WaterHeater:HeatPump:WrappedCondenser` | Mapped | `translateWaterHeaterHeatPumpWrappedCondenser` |
| `OS:WaterHeater:Mixed` | `WaterHeaterMixed` | `OutdoorAir:NodeList`, `WaterHeater:Mixed` | Mapped | `translateWaterHeaterMixed` |
| `OS:WaterHeater:Sizing` | `WaterHeaterSizing` | `WaterHeater:Sizing` | Mapped | `translateWaterHeaterSizing` |
| `OS:WaterHeater:Stratified` | `WaterHeaterStratified` | `WaterHeater:Stratified` | Mapped | `translateWaterHeaterStratified` |
| `OS:WaterUse:Connections` | `WaterUseConnections` | `WaterUse:Connections` | Mapped | `translateWaterUseConnections` |
| `OS:WaterUse:Equipment` | `WaterUseEquipment` | `WaterUse:Equipment` | Mapped | `translateWaterUseEquipment` |
| `OS:WaterUse:Equipment:Definition` | `` |  | OS-only / no EP output | `` |
| `OS:WeatherFile` | `` |  | OS-only / no EP output | `` |
| `OS:WeatherProperty:SkyTemperature` | `SkyTemperature` | `WeatherProperty:SkyTemperature` | Mapped | `translateSkyTemperature` |
| `OS:WindowMaterial:Blind` | `Blind` | `WindowMaterial:Blind` | Mapped | `translateBlind` |
| `OS:WindowMaterial:DaylightRedirectionDevice` | `DaylightRedirectionDevice` |  | OS-only / no EP output | `translateDaylightRedirectionDevice` |
| `OS:WindowMaterial:Gas` | `Gas` | `WindowMaterial:Gas` | Mapped | `translateGas` |
| `OS:WindowMaterial:GasMixture` | `GasMixture` | `WindowMaterial:GasMixture` | Mapped | `translateGasMixture` |
| `OS:WindowMaterial:Glazing` | `StandardGlazing` | `WindowMaterial:Glazing` | Mapped | `translateStandardGlazing` |
| `OS:WindowMaterial:Glazing:RefractionExtinctionMethod` | `RefractionExtinctionGlazing` | `WindowMaterial:Glazing:RefractionExtinctionMethod` | Mapped | `translateRefractionExtinctionGlazing` |
| `OS:WindowMaterial:GlazingGroup:Thermochromic` | `ThermochromicGlazing` | `WindowMaterial:GlazingGroup:Thermochromic` | Mapped | `translateThermochromicGlazing` |
| `OS:WindowMaterial:Screen` | `Screen` | `WindowMaterial:Screen` | Mapped | `translateScreen` |
| `OS:WindowMaterial:Shade` | `Shade` | `WindowMaterial:Shade` | Mapped | `translateShade` |
| `OS:WindowMaterial:SimpleGlazingSystem` | `SimpleGlazing` | `WindowMaterial:SimpleGlazingSystem` | Mapped | `translateSimpleGlazing` |
| `OS:WindowProperty:FrameAndDivider` | `WindowPropertyFrameAndDivider` | `WindowProperty:FrameAndDivider` | Mapped | `translateWindowPropertyFrameAndDivider` |
| `OS:YearDescription` | `` |  | OS-only / no EP output | `` |
| `OS:ZoneAirContaminantBalance` | `ZoneAirContaminantBalance` | `ZoneAirContaminantBalance` | Mapped | `translateZoneAirContaminantBalance` |
| `OS:ZoneAirHeatBalanceAlgorithm` | `ZoneAirHeatBalanceAlgorithm` | `ZoneAirHeatBalanceAlgorithm` | Mapped | `translateZoneAirHeatBalanceAlgorithm` |
| `OS:ZoneAirMassFlowConservation` | `ZoneAirMassFlowConservation` | `ZoneAirMassFlowConservation` | Mapped | `translateZoneAirMassFlowConservation` |
| `OS:ZoneCapacitanceMultiplier:ResearchSpecial` | `ZoneCapacitanceMultiplierResearchSpecial` | `ZoneCapacitanceMultiplier:ResearchSpecial` | Mapped | `translateZoneCapacitanceMultiplierResearchSpecial` |
| `OS:ZoneControl:ContaminantController` | `ZoneControlContaminantController` | `ZoneControl:ContaminantController` | Mapped | `translateZoneControlContaminantController` |
| `OS:ZoneControl:Humidistat` | `ZoneControlHumidistat` | `ZoneControl:Humidistat` | Mapped | `translateZoneControlHumidistat` |
| `OS:ZoneControl:Thermostat:StagedDualSetpoint` | `ZoneControlThermostatStagedDualSetpoint` | `ScheduleTypeLimits`, `Schedule:Compact`, `ThermostatSetpoint:DualSetpoint`, `ZoneControl:Thermostat`, `ZoneControl:Thermostat:StagedDualSetpoint` | Mapped | `translateZoneControlThermostatStagedDualSetpoint` |
| `OS:ZoneHVAC:Baseboard:Convective:Electric` | `ZoneHVACBaseboardConvectiveElectric` | `ZoneHVAC:Baseboard:Convective:Electric` | Mapped | `translateZoneHVACBaseboardConvectiveElectric` |
| `OS:ZoneHVAC:Baseboard:Convective:Water` | `ZoneHVACBaseboardConvectiveWater` | `ZoneHVAC:Baseboard:Convective:Water` | Mapped | `translateZoneHVACBaseboardConvectiveWater` |
| `OS:ZoneHVAC:Baseboard:RadiantConvective:Electric` | `ZoneHVACBaseboardRadiantConvectiveElectric` | `ZoneHVAC:Baseboard:RadiantConvective:Electric` | Mapped | `translateZoneHVACBaseboardRadiantConvectiveElectric` |
| `OS:ZoneHVAC:Baseboard:RadiantConvective:Water` | `ZoneHVACBaseboardRadiantConvectiveWater` | `ZoneHVAC:Baseboard:RadiantConvective:Water`, `ZoneHVAC:Baseboard:RadiantConvective:Water:Design` | Mapped | `translateZoneHVACBaseboardRadiantConvectiveWater` |
| `OS:ZoneHVAC:CoolingPanel:RadiantConvective:Water` | `ZoneHVACCoolingPanelRadiantConvectiveWater` | `ZoneHVAC:CoolingPanel:RadiantConvective:Water` | Mapped | `translateZoneHVACCoolingPanelRadiantConvectiveWater` |
| `OS:ZoneHVAC:Dehumidifier:DX` | `ZoneHVACDehumidifierDX` | `ZoneHVAC:Dehumidifier:DX` | Mapped | `translateZoneHVACDehumidifierDX` |
| `OS:ZoneHVAC:EnergyRecoveryVentilator` | `ZoneHVACEnergyRecoveryVentilator` | `OutdoorAir:NodeList`, `ZoneHVAC:EnergyRecoveryVentilator` | Mapped | `translateZoneHVACEnergyRecoveryVentilator` |
| `OS:ZoneHVAC:EnergyRecoveryVentilator:Controller` | `ZoneHVACEnergyRecoveryVentilatorController` | `ZoneHVAC:EnergyRecoveryVentilator:Controller` | Mapped | `translateZoneHVACEnergyRecoveryVentilatorController` |
| `OS:ZoneHVAC:EquipmentList` | `ZoneHVACEquipmentList` | `ZoneHVAC:EquipmentList`, `ZoneHVAC:RefrigerationChillerSet` | Mapped | `translateZoneHVACEquipmentList` |
| `OS:ZoneHVAC:EvaporativeCoolerUnit` | `ZoneHVACEvaporativeCoolerUnit` | `OutdoorAir:NodeList`, `ZoneHVAC:EvaporativeCoolerUnit` | Mapped | `translateZoneHVACEvaporativeCoolerUnit` |
| `OS:ZoneHVAC:FourPipeFanCoil` | `ZoneHVACFourPipeFanCoil` | `OutdoorAir:Mixer`, `OutdoorAir:NodeList`, `ZoneHVAC:FourPipeFanCoil` | Mapped | `translateZoneHVACFourPipeFanCoil` |
| `OS:ZoneHVAC:HighTemperatureRadiant` | `ZoneHVACHighTemperatureRadiant` | `ZoneHVAC:HighTemperatureRadiant` | Mapped | `translateZoneHVACHighTemperatureRadiant` |
| `OS:ZoneHVAC:IdealLoadsAirSystem` | `ZoneHVACIdealLoadsAirSystem` | `ZoneHVAC:IdealLoadsAirSystem` | Mapped | `translateZoneHVACIdealLoadsAirSystem` |
| `OS:ZoneHVAC:LowTemperatureRadiant:ConstantFlow` | `ZoneHVACLowTempRadiantConstFlow` | `ZoneHVAC:LowTemperatureRadiant:ConstantFlow`, `ZoneHVAC:LowTemperatureRadiant:ConstantFlow:Design`, `ZoneHVAC:LowTemperatureRadiant:SurfaceGroup` | Mapped | `translateZoneHVACLowTempRadiantConstFlow` |
| `OS:ZoneHVAC:LowTemperatureRadiant:Electric` | `ZoneHVACLowTemperatureRadiantElectric` | `ZoneHVAC:LowTemperatureRadiant:Electric`, `ZoneHVAC:LowTemperatureRadiant:SurfaceGroup` | Mapped | `translateZoneHVACLowTemperatureRadiantElectric` |
| `OS:ZoneHVAC:LowTemperatureRadiant:VariableFlow` | `ZoneHVACLowTempRadiantVarFlow` | `ZoneHVAC:LowTemperatureRadiant:SurfaceGroup`, `ZoneHVAC:LowTemperatureRadiant:VariableFlow`, `ZoneHVAC:LowTemperatureRadiant:VariableFlow:Design` | Mapped | `translateZoneHVACLowTempRadiantVarFlow` |
| `OS:ZoneHVAC:PackagedTerminalAirConditioner` | `ZoneHVACPackagedTerminalAirConditioner` | `OutdoorAir:Mixer`, `OutdoorAir:NodeList`, `ZoneHVAC:PackagedTerminalAirConditioner` | Mapped | `translateZoneHVACPackagedTerminalAirConditioner` |
| `OS:ZoneHVAC:PackagedTerminalHeatPump` | `ZoneHVACPackagedTerminalHeatPump` | `OutdoorAir:Mixer`, `OutdoorAir:NodeList`, `ZoneHVAC:PackagedTerminalHeatPump` | Mapped | `translateZoneHVACPackagedTerminalHeatPump` |
| `OS:ZoneHVAC:TerminalUnit:VariableRefrigerantFlow` | `ZoneHVACTerminalUnitVariableRefrigerantFlow` | `OutdoorAir:Mixer`, `OutdoorAir:NodeList`, `ZoneHVAC:TerminalUnit:VariableRefrigerantFlow` | Mapped | `translateZoneHVACTerminalUnitVariableRefrigerantFlow` |
| `OS:ZoneHVAC:UnitHeater` | `ZoneHVACUnitHeater` | `ZoneHVAC:UnitHeater` | Mapped | `translateZoneHVACUnitHeater` |
| `OS:ZoneHVAC:UnitVentilator` | `ZoneHVACUnitVentilator` | `OutdoorAir:NodeList`, `ZoneHVAC:UnitVentilator` | Mapped | `translateZoneHVACUnitVentilator` |
| `OS:ZoneHVAC:WaterToAirHeatPump` | `ZoneHVACWaterToAirHeatPump` | `OutdoorAir:Mixer`, `OutdoorAir:NodeList`, `ZoneHVAC:WaterToAirHeatPump` | Mapped | `translateZoneHVACWaterToAirHeatPump` |
| `OS:ZoneMixing` | `ZoneMixing` | `ZoneMixing` | Mapped | `translateZoneMixing` |
| `OS:ZoneProperty:UserViewFactors:BySurfaceName` | `ZonePropertyUserViewFactorsBySurfaceName` | `ZoneProperty:UserViewFactors:BySurfaceName` | Mapped | `translateZonePropertyUserViewFactorsBySurfaceName` |
| `OS:ZoneVentilation:DesignFlowRate` | `ZoneVentilationDesignFlowRate` | `ZoneVentilation:DesignFlowRate` | Mapped | `translateZoneVentilationDesignFlowRate` |
| `OS:ZoneVentilation:WindandStackOpenArea` | `ZoneVentilationWindandStackOpenArea` | `ZoneVentilation:WindandStackOpenArea` | Mapped | `translateZoneVentilationWindandStackOpenArea` |

## EP -> OS (Full)

| EP IddObjectType | Source OS IddObjectType(s) (from FT) | Status | RT function (if in switch) |
| --- | --- | --- | --- |
| `AirConditioner:VariableRefrigerantFlow` | `OS:AirConditioner:VariableRefrigerantFlow` | Generated by translator (has direct OS IDD peer) | `` |
| `AirConditioner:VariableRefrigerantFlow:FluidTemperatureControl` | `OS:AirConditioner:VariableRefrigerantFlow:FluidTemperatureControl` | Generated by translator (has direct OS IDD peer) | `` |
| `AirConditioner:VariableRefrigerantFlow:FluidTemperatureControl:HR` | `OS:AirConditioner:VariableRefrigerantFlow:FluidTemperatureControl:HR` | Generated by translator (has direct OS IDD peer) | `` |
| `AirLoopHVAC` | `OS:AirLoopHVAC` | Generated by translator (has direct OS IDD peer) | `translateAirLoopHVAC` |
| `AirLoopHVAC:ControllerList` | `OS:AirLoopHVAC`, `OS:AirLoopHVAC:OutdoorAirSystem` | Generated by translator (no direct OS IDD peer) | `` |
| `AirLoopHVAC:DedicatedOutdoorAirSystem` | `OS:AirLoopHVAC:DedicatedOutdoorAirSystem` | Generated by translator (has direct OS IDD peer) | `translateAirLoopHVACDedicatedOutdoorAirSystem` |
| `AirLoopHVAC:ExhaustSystem` |  | EP-only (no OS forward source found) | `` |
| `AirLoopHVAC:Mixer` | `OS:AirLoopHVAC:DedicatedOutdoorAirSystem` | Generated by translator (no direct OS IDD peer) | `` |
| `AirLoopHVAC:OutdoorAirSystem` | `OS:AirLoopHVAC:OutdoorAirSystem` | Generated by translator (has direct OS IDD peer) | `translateAirLoopHVACOutdoorAirSystem` |
| `AirLoopHVAC:OutdoorAirSystem:EquipmentList` | `OS:AirLoopHVAC:OutdoorAirSystem` | Generated by translator (no direct OS IDD peer) | `` |
| `AirLoopHVAC:ReturnPath` |  | EP-only (no OS forward source found) | `` |
| `AirLoopHVAC:ReturnPlenum` | `OS:AirLoopHVAC:ReturnPlenum` | Generated by translator (has direct OS IDD peer) | `` |
| `AirLoopHVAC:Splitter` | `OS:AirLoopHVAC:DedicatedOutdoorAirSystem` | Generated by translator (no direct OS IDD peer) | `` |
| `AirLoopHVAC:SupplyPath` |  | EP-only (no OS forward source found) | `` |
| `AirLoopHVAC:SupplyPlenum` | `OS:AirLoopHVAC:SupplyPlenum` | Generated by translator (has direct OS IDD peer) | `` |
| `AirLoopHVAC:Unitary:Furnace:HeatCool` |  | EP-only (no OS forward source found) | `` |
| `AirLoopHVAC:Unitary:Furnace:HeatOnly` |  | EP-only (no OS forward source found) | `` |
| `AirLoopHVAC:UnitaryHeatCool` |  | EP-only (no OS forward source found) | `` |
| `AirLoopHVAC:UnitaryHeatCool:VAVChangeoverBypass` | `OS:AirLoopHVAC:UnitaryHeatCool:VAVChangeoverBypass` | Generated by translator (has direct OS IDD peer) | `` |
| `AirLoopHVAC:UnitaryHeatOnly` |  | EP-only (no OS forward source found) | `` |
| `AirLoopHVAC:UnitaryHeatPump:AirToAir` | `OS:AirLoopHVAC:UnitaryHeatPump:AirToAir` | Generated by translator (has direct OS IDD peer) | `` |
| `AirLoopHVAC:UnitaryHeatPump:AirToAir:MultiSpeed` | `OS:AirLoopHVAC:UnitaryHeatPump:AirToAir:MultiSpeed` | Generated by translator (has direct OS IDD peer) | `` |
| `AirLoopHVAC:UnitaryHeatPump:WaterToAir` |  | EP-only (no OS forward source found) | `` |
| `AirLoopHVAC:UnitarySystem` | `OS:AirLoopHVAC:UnitarySystem` | Generated by translator (has direct OS IDD peer) | `` |
| `AirLoopHVAC:ZoneMixer` | `OS:AirLoopHVAC:ZoneMixer`, `OS:AirTerminal:SingleDuct:ConstantVolume:FourPipeInduction`, `OS:AirTerminal:SingleDuct:ParallelPIU:Reheat`, `OS:AirTerminal:SingleDuct:SeriesPIU:Reheat` | Generated by translator (has direct OS IDD peer) | `` |
| `AirLoopHVAC:ZoneSplitter` | `OS:AirLoopHVAC:ZoneSplitter` | Generated by translator (has direct OS IDD peer) | `` |
| `AirTerminal:DualDuct:ConstantVolume` | `OS:AirTerminal:DualDuct:ConstantVolume` | Generated by translator (has direct OS IDD peer) | `` |
| `AirTerminal:DualDuct:VAV` | `OS:AirTerminal:DualDuct:VAV` | Generated by translator (has direct OS IDD peer) | `` |
| `AirTerminal:DualDuct:VAV:OutdoorAir` | `OS:AirTerminal:DualDuct:VAV:OutdoorAir` | Generated by translator (has direct OS IDD peer) | `` |
| `AirTerminal:SingleDuct:ConstantVolume:CooledBeam` | `OS:AirTerminal:SingleDuct:ConstantVolume:CooledBeam` | Generated by translator (has direct OS IDD peer) | `` |
| `AirTerminal:SingleDuct:ConstantVolume:FourPipeBeam` | `OS:AirTerminal:SingleDuct:ConstantVolume:FourPipeBeam` | Generated by translator (has direct OS IDD peer) | `` |
| `AirTerminal:SingleDuct:ConstantVolume:FourPipeInduction` | `OS:AirTerminal:SingleDuct:ConstantVolume:FourPipeInduction` | Generated by translator (has direct OS IDD peer) | `` |
| `AirTerminal:SingleDuct:ConstantVolume:NoReheat` | `OS:AirTerminal:SingleDuct:ConstantVolume:NoReheat` | Generated by translator (has direct OS IDD peer) | `translateAirTerminalSingleDuctConstantVolumeNoReheat` |
| `AirTerminal:SingleDuct:ConstantVolume:Reheat` | `OS:AirTerminal:SingleDuct:ConstantVolume:Reheat` | Generated by translator (has direct OS IDD peer) | `translateAirTerminalSingleDuctConstantVolumeReheat` |
| `AirTerminal:SingleDuct:Mixer` | `OS:AirTerminal:SingleDuct:InletSideMixer` | Generated by translator (no direct OS IDD peer) | `` |
| `AirTerminal:SingleDuct:ParallelPIU:Reheat` | `OS:AirTerminal:SingleDuct:ParallelPIU:Reheat` | Generated by translator (has direct OS IDD peer) | `` |
| `AirTerminal:SingleDuct:SeriesPIU:Reheat` | `OS:AirTerminal:SingleDuct:SeriesPIU:Reheat` | Generated by translator (has direct OS IDD peer) | `` |
| `AirTerminal:SingleDuct:UserDefined` |  | EP-only (no OS forward source found) | `` |
| `AirTerminal:SingleDuct:VAV:HeatAndCool:NoReheat` | `OS:AirTerminal:SingleDuct:VAV:HeatAndCool:NoReheat` | Generated by translator (has direct OS IDD peer) | `` |
| `AirTerminal:SingleDuct:VAV:HeatAndCool:Reheat` | `OS:AirTerminal:SingleDuct:VAV:HeatAndCool:Reheat` | Generated by translator (has direct OS IDD peer) | `` |
| `AirTerminal:SingleDuct:VAV:NoReheat` | `OS:AirTerminal:SingleDuct:VAV:NoReheat` | Generated by translator (has direct OS IDD peer) | `translateAirTerminalSingleDuctVAVNoReheat` |
| `AirTerminal:SingleDuct:VAV:Reheat` | `OS:AirTerminal:SingleDuct:VAV:Reheat` | Generated by translator (has direct OS IDD peer) | `translateAirTerminalSingleDuctVAVReheat` |
| `AirTerminal:SingleDuct:VAV:Reheat:VariableSpeedFan` |  | EP-only (no OS forward source found) | `` |
| `AirflowNetwork:Distribution:Component:Coil` |  | EP-only (no OS forward source found) | `` |
| `AirflowNetwork:Distribution:Component:ConstantPressureDrop` |  | EP-only (no OS forward source found) | `` |
| `AirflowNetwork:Distribution:Component:Duct` |  | EP-only (no OS forward source found) | `` |
| `AirflowNetwork:Distribution:Component:Fan` |  | EP-only (no OS forward source found) | `` |
| `AirflowNetwork:Distribution:Component:HeatExchanger` |  | EP-only (no OS forward source found) | `` |
| `AirflowNetwork:Distribution:Component:Leak` |  | EP-only (no OS forward source found) | `` |
| `AirflowNetwork:Distribution:Component:LeakageRatio` |  | EP-only (no OS forward source found) | `` |
| `AirflowNetwork:Distribution:Component:OutdoorAirFlow` |  | EP-only (no OS forward source found) | `` |
| `AirflowNetwork:Distribution:Component:ReliefAirFlow` |  | EP-only (no OS forward source found) | `` |
| `AirflowNetwork:Distribution:Component:TerminalUnit` |  | EP-only (no OS forward source found) | `` |
| `AirflowNetwork:Distribution:DuctSizing` |  | EP-only (no OS forward source found) | `` |
| `AirflowNetwork:Distribution:DuctViewFactors` |  | EP-only (no OS forward source found) | `` |
| `AirflowNetwork:Distribution:Linkage` |  | EP-only (no OS forward source found) | `` |
| `AirflowNetwork:Distribution:Node` |  | EP-only (no OS forward source found) | `` |
| `AirflowNetwork:IntraZone:Linkage` |  | EP-only (no OS forward source found) | `` |
| `AirflowNetwork:IntraZone:Node` |  | EP-only (no OS forward source found) | `` |
| `AirflowNetwork:MultiZone:Component:DetailedOpening` |  | EP-only (no OS forward source found) | `` |
| `AirflowNetwork:MultiZone:Component:HorizontalOpening` |  | EP-only (no OS forward source found) | `` |
| `AirflowNetwork:MultiZone:Component:SimpleOpening` |  | EP-only (no OS forward source found) | `` |
| `AirflowNetwork:MultiZone:Component:ZoneExhaustFan` |  | EP-only (no OS forward source found) | `` |
| `AirflowNetwork:MultiZone:ExternalNode` |  | EP-only (no OS forward source found) | `` |
| `AirflowNetwork:MultiZone:ReferenceCrackConditions` |  | EP-only (no OS forward source found) | `` |
| `AirflowNetwork:MultiZone:SpecifiedFlowRate` |  | EP-only (no OS forward source found) | `` |
| `AirflowNetwork:MultiZone:Surface` |  | EP-only (no OS forward source found) | `` |
| `AirflowNetwork:MultiZone:Surface:Crack` |  | EP-only (no OS forward source found) | `` |
| `AirflowNetwork:MultiZone:Surface:EffectiveLeakageArea` |  | EP-only (no OS forward source found) | `` |
| `AirflowNetwork:MultiZone:WindPressureCoefficientArray` |  | EP-only (no OS forward source found) | `` |
| `AirflowNetwork:MultiZone:WindPressureCoefficientValues` |  | EP-only (no OS forward source found) | `` |
| `AirflowNetwork:MultiZone:Zone` |  | EP-only (no OS forward source found) | `` |
| `AirflowNetwork:OccupantVentilationControl` |  | EP-only (no OS forward source found) | `` |
| `AirflowNetwork:SimulationControl` |  | EP-only (no OS forward source found) | `` |
| `AirflowNetwork:ZoneControl:PressureController` |  | EP-only (no OS forward source found) | `` |
| `AvailabilityManager:DifferentialThermostat` | `OS:AvailabilityManager:DifferentialThermostat` | Generated by translator (has direct OS IDD peer) | `` |
| `AvailabilityManager:HighTemperatureTurnOff` | `OS:AvailabilityManager:HighTemperatureTurnOff` | Generated by translator (has direct OS IDD peer) | `` |
| `AvailabilityManager:HighTemperatureTurnOn` | `OS:AvailabilityManager:HighTemperatureTurnOn` | Generated by translator (has direct OS IDD peer) | `` |
| `AvailabilityManager:HybridVentilation` | `OS:AvailabilityManager:HybridVentilation` | Generated by translator (has direct OS IDD peer) | `` |
| `AvailabilityManager:LowTemperatureTurnOff` | `OS:AvailabilityManager:LowTemperatureTurnOff` | Generated by translator (has direct OS IDD peer) | `` |
| `AvailabilityManager:LowTemperatureTurnOn` | `OS:AvailabilityManager:LowTemperatureTurnOn` | Generated by translator (has direct OS IDD peer) | `` |
| `AvailabilityManager:NightCycle` | `OS:AvailabilityManager:NightCycle` | Generated by translator (has direct OS IDD peer) | `` |
| `AvailabilityManager:NightVentilation` | `OS:AvailabilityManager:NightVentilation` | Generated by translator (has direct OS IDD peer) | `` |
| `AvailabilityManager:OptimumStart` | `OS:AvailabilityManager:OptimumStart` | Generated by translator (has direct OS IDD peer) | `` |
| `AvailabilityManager:Scheduled` | `OS:AirLoopHVAC`, `OS:AvailabilityManager:Scheduled` | Generated by translator (has direct OS IDD peer) | `` |
| `AvailabilityManager:ScheduledOff` | `OS:AvailabilityManager:ScheduledOff` | Generated by translator (has direct OS IDD peer) | `` |
| `AvailabilityManager:ScheduledOn` | `OS:AvailabilityManager:ScheduledOn` | Generated by translator (has direct OS IDD peer) | `` |
| `AvailabilityManagerAssignmentList` | `OS:AirLoopHVAC`, `OS:AvailabilityManagerAssignmentList` | Generated by translator (has direct OS IDD peer) | `` |
| `Boiler:HotWater` | `OS:Boiler:HotWater` | Generated by translator (has direct OS IDD peer) | `` |
| `Boiler:Steam` | `OS:Boiler:Steam` | Generated by translator (has direct OS IDD peer) | `` |
| `Branch` | `OS:AirLoopHVAC`, `OS:PlantLoop` | Generated by translator (no direct OS IDD peer) | `` |
| `BranchList` | `OS:AirLoopHVAC`, `OS:PlantLoop` | Generated by translator (no direct OS IDD peer) | `` |
| `Building` | `OS:Building` | Generated by translator (has direct OS IDD peer) | `translateBuilding` |
| `BuildingSurface:Detailed` | `OS:Surface` | Generated by translator (no direct OS IDD peer) | `translateBuildingSurfaceDetailed` |
| `Ceiling:Adiabatic` |  | EP-only (no OS forward source found) | `` |
| `Ceiling:Interzone` |  | EP-only (no OS forward source found) | `` |
| `CentralHeatPumpSystem` | `OS:CentralHeatPumpSystem` | Generated by translator (has direct OS IDD peer) | `` |
| `Chiller:Absorption` | `OS:Chiller:Absorption` | Generated by translator (has direct OS IDD peer) | `` |
| `Chiller:Absorption:Indirect` | `OS:Chiller:Absorption:Indirect` | Generated by translator (has direct OS IDD peer) | `` |
| `Chiller:CombustionTurbine` |  | EP-only (no OS forward source found) | `` |
| `Chiller:ConstantCOP` |  | EP-only (no OS forward source found) | `` |
| `Chiller:Electric` |  | EP-only (no OS forward source found) | `` |
| `Chiller:Electric:ASHRAE205` | `OS:Chiller:Electric:ASHRAE205` | Generated by translator (has direct OS IDD peer) | `translateChillerElectricASHRAE205` |
| `Chiller:Electric:EIR` | `OS:Chiller:Electric:EIR` | Generated by translator (has direct OS IDD peer) | `` |
| `Chiller:Electric:ReformulatedEIR` | `OS:Chiller:Electric:ReformulatedEIR` | Generated by translator (has direct OS IDD peer) | `` |
| `Chiller:EngineDriven` |  | EP-only (no OS forward source found) | `` |
| `ChillerHeater:Absorption:DirectFired` |  | EP-only (no OS forward source found) | `` |
| `ChillerHeater:Absorption:DoubleEffect` |  | EP-only (no OS forward source found) | `` |
| `ChillerHeaterPerformance:Electric:EIR` | `OS:ChillerHeaterPerformance:Electric:EIR` | Generated by translator (has direct OS IDD peer) | `` |
| `Coil:Cooling:DX` | `OS:Coil:Cooling:DX` | Generated by translator (has direct OS IDD peer) | `translateCoilCoolingDX` |
| `Coil:Cooling:DX:CurveFit:OperatingMode` | `OS:Coil:Cooling:DX:CurveFit:OperatingMode` | Generated by translator (has direct OS IDD peer) | `translateCoilCoolingDXCurveFitOperatingMode` |
| `Coil:Cooling:DX:CurveFit:Performance` | `OS:Coil:Cooling:DX:CurveFit:Performance` | Generated by translator (has direct OS IDD peer) | `translateCoilCoolingDXCurveFitPerformance` |
| `Coil:Cooling:DX:CurveFit:Speed` | `OS:Coil:Cooling:DX:CurveFit:Speed` | Generated by translator (has direct OS IDD peer) | `translateCoilCoolingDXCurveFitSpeed` |
| `Coil:Cooling:DX:MultiSpeed` | `OS:Coil:Cooling:DX:MultiSpeed` | Generated by translator (has direct OS IDD peer) | `` |
| `Coil:Cooling:DX:SingleSpeed` | `OS:Coil:Cooling:DX:SingleSpeed` | Generated by translator (has direct OS IDD peer) | `translateCoilCoolingDXSingleSpeed` |
| `Coil:Cooling:DX:SingleSpeed:ThermalStorage` | `OS:Coil:Cooling:DX:SingleSpeed:ThermalStorage` | Generated by translator (has direct OS IDD peer) | `` |
| `Coil:Cooling:DX:TwoSpeed` | `OS:Coil:Cooling:DX:TwoSpeed` | Generated by translator (has direct OS IDD peer) | `` |
| `Coil:Cooling:DX:TwoStageWithHumidityControlMode` | `OS:Coil:Cooling:DX:TwoStageWithHumidityControlMode` | Generated by translator (has direct OS IDD peer) | `` |
| `Coil:Cooling:DX:VariableRefrigerantFlow` | `OS:Coil:Cooling:DX:VariableRefrigerantFlow` | Generated by translator (has direct OS IDD peer) | `` |
| `Coil:Cooling:DX:VariableRefrigerantFlow:FluidTemperatureControl` | `OS:Coil:Cooling:DX:VariableRefrigerantFlow:FluidTemperatureControl` | Generated by translator (has direct OS IDD peer) | `` |
| `Coil:Cooling:DX:VariableSpeed` | `OS:Coil:Cooling:DX:VariableSpeed` | Generated by translator (has direct OS IDD peer) | `` |
| `Coil:Cooling:Water` | `OS:Coil:Cooling:Water` | Generated by translator (has direct OS IDD peer) | `` |
| `Coil:Cooling:Water:DetailedGeometry` |  | EP-only (no OS forward source found) | `` |
| `Coil:Cooling:WaterToAirHeatPump:EquationFit` | `OS:Coil:Cooling:WaterToAirHeatPump:EquationFit` | Generated by translator (has direct OS IDD peer) | `` |
| `Coil:Cooling:WaterToAirHeatPump:ParameterEstimation` |  | EP-only (no OS forward source found) | `` |
| `Coil:Cooling:WaterToAirHeatPump:VariableSpeedEquationFit` | `OS:Coil:Cooling:WaterToAirHeatPump:VariableSpeedEquationFit` | Generated by translator (has direct OS IDD peer) | `` |
| `Coil:DX:ASHRAE205:Performance` |  | EP-only (no OS forward source found) | `` |
| `Coil:Heating:DX:MultiSpeed` | `OS:Coil:Heating:DX:MultiSpeed` | Generated by translator (has direct OS IDD peer) | `` |
| `Coil:Heating:DX:SingleSpeed` | `OS:Coil:Heating:DX:SingleSpeed` | Generated by translator (has direct OS IDD peer) | `` |
| `Coil:Heating:DX:VariableRefrigerantFlow` | `OS:Coil:Heating:DX:VariableRefrigerantFlow` | Generated by translator (has direct OS IDD peer) | `` |
| `Coil:Heating:DX:VariableRefrigerantFlow:FluidTemperatureControl` | `OS:Coil:Heating:DX:VariableRefrigerantFlow:FluidTemperatureControl` | Generated by translator (has direct OS IDD peer) | `` |
| `Coil:Heating:DX:VariableSpeed` | `OS:Coil:Heating:DX:VariableSpeed` | Generated by translator (has direct OS IDD peer) | `` |
| `Coil:Heating:Desuperheater` | `OS:Coil:Heating:Desuperheater` | Generated by translator (has direct OS IDD peer) | `` |
| `Coil:Heating:Electric` | `OS:Coil:Heating:Electric` | Generated by translator (has direct OS IDD peer) | `` |
| `Coil:Heating:Electric:MultiStage` | `OS:Coil:Heating:Electric:MultiStage` | Generated by translator (has direct OS IDD peer) | `` |
| `Coil:Heating:Fuel` | `OS:Coil:Heating:Gas` | Generated by translator (no direct OS IDD peer) | `translateCoilHeatingGas` |
| `Coil:Heating:Gas:MultiStage` | `OS:Coil:Heating:Gas:MultiStage` | Generated by translator (has direct OS IDD peer) | `` |
| `Coil:Heating:Steam` |  | EP-only (no OS forward source found) | `` |
| `Coil:Heating:Water` | `OS:Coil:Heating:Water` | Generated by translator (has direct OS IDD peer) | `` |
| `Coil:Heating:WaterToAirHeatPump:EquationFit` | `OS:Coil:Heating:WaterToAirHeatPump:EquationFit` | Generated by translator (has direct OS IDD peer) | `` |
| `Coil:Heating:WaterToAirHeatPump:ParameterEstimation` |  | EP-only (no OS forward source found) | `` |
| `Coil:Heating:WaterToAirHeatPump:VariableSpeedEquationFit` | `OS:Coil:Heating:WaterToAirHeatPump:VariableSpeedEquationFit` | Generated by translator (has direct OS IDD peer) | `` |
| `Coil:UserDefined` | `OS:Coil:UserDefined` | Generated by translator (has direct OS IDD peer) | `` |
| `Coil:WaterHeating:AirToWaterHeatPump:Pumped` | `OS:Coil:WaterHeating:AirToWaterHeatPump` | Generated by translator (no direct OS IDD peer) | `` |
| `Coil:WaterHeating:AirToWaterHeatPump:VariableSpeed` | `OS:Coil:WaterHeating:AirToWaterHeatPump:VariableSpeed` | Generated by translator (has direct OS IDD peer) | `` |
| `Coil:WaterHeating:AirToWaterHeatPump:Wrapped` | `OS:Coil:WaterHeating:AirToWaterHeatPump:Wrapped` | Generated by translator (has direct OS IDD peer) | `` |
| `Coil:WaterHeating:Desuperheater` | `OS:Coil:WaterHeating:Desuperheater` | Generated by translator (has direct OS IDD peer) | `` |
| `CoilPerformance:DX:Cooling` | `OS:CoilPerformance:DX:Cooling` | Generated by translator (has direct OS IDD peer) | `` |
| `CoilSystem:Cooling:DX` |  | EP-only (no OS forward source found) | `translateCoilSystemCoolingDX` |
| `CoilSystem:Cooling:DX:HeatExchangerAssisted` | `OS:CoilSystem:Cooling:DX:HeatExchangerAssisted` | Generated by translator (has direct OS IDD peer) | `` |
| `CoilSystem:Cooling:Water` | `OS:CoilSystem:Cooling:Water` | Generated by translator (has direct OS IDD peer) | `` |
| `CoilSystem:Cooling:Water:HeatExchangerAssisted` | `OS:CoilSystem:Cooling:Water:HeatExchangerAssisted` | Generated by translator (has direct OS IDD peer) | `` |
| `CoilSystem:Heating:DX` |  | EP-only (no OS forward source found) | `` |
| `CoilSystem:IntegratedHeatPump:AirSource` | `OS:CoilSystem:IntegratedHeatPump:AirSource` | Generated by translator (has direct OS IDD peer) | `` |
| `ComfortViewFactorAngles` |  | EP-only (no OS forward source found) | `` |
| `ComplexFenestrationProperty:SolarAbsorbedLayers` |  | EP-only (no OS forward source found) | `` |
| `Compliance:Building` |  | EP-only (no OS forward source found) | `` |
| `ComponentCost:Adjustments` |  | EP-only (no OS forward source found) | `` |
| `ComponentCost:LineItem` |  | EP-only (no OS forward source found) | `` |
| `ComponentCost:Reference` |  | EP-only (no OS forward source found) | `` |
| `CondenserEquipmentList` |  | EP-only (no OS forward source found) | `` |
| `CondenserEquipmentOperationSchemes` |  | EP-only (no OS forward source found) | `` |
| `CondenserLoop` |  | EP-only (no OS forward source found) | `` |
| `Connector:Mixer` | `OS:PlantLoop` | Generated by translator (has direct OS IDD peer) | `` |
| `Connector:Splitter` | `OS:AirLoopHVAC`, `OS:PlantLoop` | Generated by translator (has direct OS IDD peer) | `` |
| `ConnectorList` | `OS:AirLoopHVAC`, `OS:PlantLoop` | Generated by translator (no direct OS IDD peer) | `` |
| `Construction` | `OS:Construction`, `OS:Construction:InternalSource` | Generated by translator (has direct OS IDD peer) | `translateConstruction` |
| `Construction:AirBoundary` | `OS:Construction:AirBoundary` | Generated by translator (has direct OS IDD peer) | `translateConstructionAirBoundary` |
| `Construction:CfactorUndergroundWall` | `OS:Construction:CfactorUndergroundWall` | Generated by translator (has direct OS IDD peer) | `` |
| `Construction:ComplexFenestrationState` |  | EP-only (no OS forward source found) | `` |
| `Construction:FfactorGroundFloor` | `OS:Construction:FfactorGroundFloor` | Generated by translator (has direct OS IDD peer) | `` |
| `Construction:WindowDataFile` |  | EP-only (no OS forward source found) | `` |
| `Construction:WindowEquivalentLayer` |  | EP-only (no OS forward source found) | `` |
| `ConstructionProperty:InternalHeatSource` | `OS:Construction:InternalSource` | Generated by translator (no direct OS IDD peer) | `translateConstructionWithInternalSource` |
| `Controller:MechanicalVentilation` | `OS:Controller:MechanicalVentilation` | Generated by translator (has direct OS IDD peer) | `` |
| `Controller:OutdoorAir` | `OS:Controller:OutdoorAir` | Generated by translator (has direct OS IDD peer) | `translateControllerOutdoorAir` |
| `Controller:WaterCoil` | `OS:Controller:WaterCoil` | Generated by translator (has direct OS IDD peer) | `` |
| `ConvergenceLimits` | `OS:ConvergenceLimits` | Generated by translator (has direct OS IDD peer) | `translateConvergenceLimits` |
| `CoolingTower:SingleSpeed` | `OS:CoolingTower:SingleSpeed` | Generated by translator (has direct OS IDD peer) | `` |
| `CoolingTower:TwoSpeed` | `OS:CoolingTower:TwoSpeed` | Generated by translator (has direct OS IDD peer) | `` |
| `CoolingTower:VariableSpeed` | `OS:CoolingTower:VariableSpeed` | Generated by translator (has direct OS IDD peer) | `` |
| `CoolingTower:VariableSpeed:Merkel` |  | EP-only (no OS forward source found) | `` |
| `CoolingTowerPerformance:CoolTools` | `OS:CoolingTowerPerformance:CoolTools` | Generated by translator (has direct OS IDD peer) | `` |
| `CoolingTowerPerformance:YorkCalc` | `OS:CoolingTowerPerformance:YorkCalc` | Generated by translator (has direct OS IDD peer) | `` |
| `CurrencyType` | `OS:CurrencyType` | Generated by translator (has direct OS IDD peer) | `` |
| `Curve:Bicubic` | `OS:Curve:Bicubic` | Generated by translator (has direct OS IDD peer) | `translateCurveBicubic` |
| `Curve:Biquadratic` | `OS:Curve:Biquadratic` | Generated by translator (has direct OS IDD peer) | `translateCurveBiquadratic` |
| `Curve:ChillerPartLoadWithLift` |  | EP-only (no OS forward source found) | `` |
| `Curve:Cubic` | `OS:Curve:Cubic` | Generated by translator (has direct OS IDD peer) | `translateCurveCubic` |
| `Curve:CubicLinear` |  | EP-only (no OS forward source found) | `` |
| `Curve:DoubleExponentialDecay` | `OS:Curve:DoubleExponentialDecay` | Generated by translator (has direct OS IDD peer) | `translateCurveDoubleExponentialDecay` |
| `Curve:Exponent` | `OS:Curve:Exponent` | Generated by translator (has direct OS IDD peer) | `` |
| `Curve:ExponentialDecay` | `OS:Curve:ExponentialDecay` | Generated by translator (has direct OS IDD peer) | `translateCurveExponentialDecay` |
| `Curve:ExponentialSkewNormal` | `OS:Curve:ExponentialSkewNormal` | Generated by translator (has direct OS IDD peer) | `translateCurveExponentialSkewNormal` |
| `Curve:FanPressureRise` | `OS:Curve:FanPressureRise` | Generated by translator (has direct OS IDD peer) | `translateCurveFanPressureRise` |
| `Curve:Functional:PressureDrop` | `OS:Curve:Functional:PressureDrop` | Generated by translator (has direct OS IDD peer) | `translateCurveFunctionalPressureDrop` |
| `Curve:Linear` | `OS:Curve:Linear` | Generated by translator (has direct OS IDD peer) | `translateCurveLinear` |
| `Curve:QuadLinear` | `OS:Curve:QuadLinear` | Generated by translator (has direct OS IDD peer) | `translateCurveQuadLinear` |
| `Curve:Quadratic` | `OS:Curve:Quadratic` | Generated by translator (has direct OS IDD peer) | `translateCurveQuadratic` |
| `Curve:QuadraticLinear` | `OS:Curve:QuadraticLinear` | Generated by translator (has direct OS IDD peer) | `translateCurveQuadraticLinear` |
| `Curve:Quartic` | `OS:Curve:Quartic` | Generated by translator (has direct OS IDD peer) | `translateCurveQuartic` |
| `Curve:QuintLinear` | `OS:Curve:QuintLinear` | Generated by translator (has direct OS IDD peer) | `translateCurveQuintLinear` |
| `Curve:RectangularHyperbola1` | `OS:Curve:RectangularHyperbola1` | Generated by translator (has direct OS IDD peer) | `translateCurveRectangularHyperbola1` |
| `Curve:RectangularHyperbola2` | `OS:Curve:RectangularHyperbola2` | Generated by translator (has direct OS IDD peer) | `translateCurveRectangularHyperbola2` |
| `Curve:Sigmoid` | `OS:Curve:Sigmoid` | Generated by translator (has direct OS IDD peer) | `translateCurveSigmoid` |
| `Curve:Triquadratic` | `OS:Curve:Triquadratic` | Generated by translator (has direct OS IDD peer) | `translateCurveTriquadratic` |
| `Daylighting:Controls` | `OS:ThermalZone` | Generated by translator (no direct OS IDD peer) | `translateDaylightingControls` |
| `Daylighting:DELight:ComplexFenestration` |  | EP-only (no OS forward source found) | `` |
| `Daylighting:ReferencePoint` | `OS:ThermalZone` | Generated by translator (no direct OS IDD peer) | `` |
| `DaylightingDevice:LightWell` | `OS:DaylightingDevice:LightWell` | Generated by translator (has direct OS IDD peer) | `` |
| `DaylightingDevice:Shelf` | `OS:DaylightingDevice:Shelf` | Generated by translator (has direct OS IDD peer) | `` |
| `DaylightingDevice:Tubular` | `OS:DaylightingDevice:Tubular` | Generated by translator (has direct OS IDD peer) | `` |
| `Dehumidifier:Desiccant:NoFans` |  | EP-only (no OS forward source found) | `` |
| `Dehumidifier:Desiccant:System` |  | EP-only (no OS forward source found) | `` |
| `DemandManager:ElectricEquipment` |  | EP-only (no OS forward source found) | `` |
| `DemandManager:ExteriorLights` |  | EP-only (no OS forward source found) | `` |
| `DemandManager:Lights` |  | EP-only (no OS forward source found) | `` |
| `DemandManager:Thermostats` |  | EP-only (no OS forward source found) | `` |
| `DemandManager:Ventilation` |  | EP-only (no OS forward source found) | `` |
| `DemandManagerAssignmentList` |  | EP-only (no OS forward source found) | `` |
| `DesignSpecification:AirTerminal:Sizing` |  | EP-only (no OS forward source found) | `` |
| `DesignSpecification:OutdoorAir` | `OS:ThermalZone` | Generated by translator (has direct OS IDD peer) | `translateDesignSpecificationOutdoorAir` |
| `DesignSpecification:OutdoorAir:SpaceList` |  | EP-only (no OS forward source found) | `` |
| `DesignSpecification:ZoneAirDistribution` | `OS:Sizing:Zone` | Generated by translator (has direct OS IDD peer) | `` |
| `DesignSpecification:ZoneHVAC:Sizing` |  | EP-only (no OS forward source found) | `` |
| `DistrictCooling` | `OS:DistrictCooling` | Generated by translator (has direct OS IDD peer) | `` |
| `DistrictHeating:Steam` | `OS:DistrictHeating:Steam` | Generated by translator (has direct OS IDD peer) | `` |
| `DistrictHeating:Water` | `OS:DistrictHeating:Water` | Generated by translator (has direct OS IDD peer) | `` |
| `Door` |  | EP-only (no OS forward source found) | `` |
| `Door:Interzone` |  | EP-only (no OS forward source found) | `` |
| `Duct` | `OS:Duct` | Generated by translator (has direct OS IDD peer) | `` |
| `Duct:Loss:Conduction` |  | EP-only (no OS forward source found) | `` |
| `Duct:Loss:Leakage` |  | EP-only (no OS forward source found) | `` |
| `Duct:Loss:MakeupAir` |  | EP-only (no OS forward source found) | `` |
| `ElectricEquipment` | `OS:ElectricEquipment` | Generated by translator (has direct OS IDD peer) | `translateElectricEquipment` |
| `ElectricEquipment:ITE:AirCooled` | `OS:ElectricEquipment:ITE:AirCooled` | Generated by translator (has direct OS IDD peer) | `` |
| `ElectricLoadCenter:Distribution` | `OS:ElectricLoadCenter:Distribution` | Generated by translator (has direct OS IDD peer) | `` |
| `ElectricLoadCenter:Generators` | `OS:ElectricLoadCenter:Distribution` | Generated by translator (no direct OS IDD peer) | `` |
| `ElectricLoadCenter:Inverter:FunctionOfPower` |  | EP-only (no OS forward source found) | `` |
| `ElectricLoadCenter:Inverter:LookUpTable` | `OS:ElectricLoadCenter:Inverter:LookUpTable` | Generated by translator (has direct OS IDD peer) | `` |
| `ElectricLoadCenter:Inverter:PVWatts` | `OS:ElectricLoadCenter:Inverter:PVWatts` | Generated by translator (has direct OS IDD peer) | `` |
| `ElectricLoadCenter:Inverter:Simple` | `OS:ElectricLoadCenter:Inverter:Simple` | Generated by translator (has direct OS IDD peer) | `` |
| `ElectricLoadCenter:Storage:Battery` |  | EP-only (no OS forward source found) | `` |
| `ElectricLoadCenter:Storage:Converter` | `OS:ElectricLoadCenter:Storage:Converter` | Generated by translator (has direct OS IDD peer) | `translateElectricLoadCenterStorageConverter` |
| `ElectricLoadCenter:Storage:LiIonNMCBattery` | `OS:ElectricLoadCenter:Storage:LiIonNMCBattery` | Generated by translator (has direct OS IDD peer) | `translateElectricLoadCenterStorageLiIonNMCBattery` |
| `ElectricLoadCenter:Storage:Simple` | `OS:ElectricLoadCenter:Storage:Simple` | Generated by translator (has direct OS IDD peer) | `translateElectricLoadCenterStorageSimple` |
| `ElectricLoadCenter:Transformer` | `OS:ElectricLoadCenter:Transformer` | Generated by translator (has direct OS IDD peer) | `` |
| `EnergyManagementSystem:Actuator` | `OS:EnergyManagementSystem:Actuator` | Generated by translator (has direct OS IDD peer) | `translateEnergyManagementSystemActuator` |
| `EnergyManagementSystem:ConstructionIndexVariable` | `OS:EnergyManagementSystem:ConstructionIndexVariable` | Generated by translator (has direct OS IDD peer) | `translateEnergyManagementSystemConstructionIndexVariable` |
| `EnergyManagementSystem:CurveOrTableIndexVariable` | `OS:EnergyManagementSystem:CurveOrTableIndexVariable` | Generated by translator (has direct OS IDD peer) | `translateEnergyManagementSystemCurveOrTableIndexVariable` |
| `EnergyManagementSystem:GlobalVariable` | `OS:EnergyManagementSystem:GlobalVariable` | Generated by translator (has direct OS IDD peer) | `translateEnergyManagementSystemGlobalVariable` |
| `EnergyManagementSystem:InternalVariable` | `OS:EnergyManagementSystem:InternalVariable` | Generated by translator (has direct OS IDD peer) | `translateEnergyManagementSystemInternalVariable` |
| `EnergyManagementSystem:MeteredOutputVariable` | `OS:EnergyManagementSystem:MeteredOutputVariable` | Generated by translator (has direct OS IDD peer) | `translateEnergyManagementSystemMeteredOutputVariable` |
| `EnergyManagementSystem:OutputVariable` | `OS:EnergyManagementSystem:OutputVariable` | Generated by translator (has direct OS IDD peer) | `translateEnergyManagementSystemOutputVariable` |
| `EnergyManagementSystem:Program` | `OS:EnergyManagementSystem:Program` | Generated by translator (has direct OS IDD peer) | `translateEnergyManagementSystemProgram` |
| `EnergyManagementSystem:ProgramCallingManager` | `OS:EnergyManagementSystem:ProgramCallingManager` | Generated by translator (has direct OS IDD peer) | `translateEnergyManagementSystemProgramCallingManager` |
| `EnergyManagementSystem:Sensor` | `OS:EnergyManagementSystem:Sensor` | Generated by translator (has direct OS IDD peer) | `translateEnergyManagementSystemSensor` |
| `EnergyManagementSystem:Subroutine` | `OS:EnergyManagementSystem:Subroutine` | Generated by translator (has direct OS IDD peer) | `translateEnergyManagementSystemSubroutine` |
| `EnergyManagementSystem:TrendVariable` | `OS:EnergyManagementSystem:TrendVariable` | Generated by translator (has direct OS IDD peer) | `translateEnergyManagementSystemTrendVariable` |
| `EnvironmentalImpactFactors` | `OS:EnvironmentalImpactFactors` | Generated by translator (has direct OS IDD peer) | `translateEnvironmentalImpactFactors` |
| `EvaporativeCooler:Direct:CelDekPad` |  | EP-only (no OS forward source found) | `` |
| `EvaporativeCooler:Direct:ResearchSpecial` | `OS:EvaporativeCooler:Direct:ResearchSpecial` | Generated by translator (has direct OS IDD peer) | `translateEvaporativeCoolerDirectResearchSpecial` |
| `EvaporativeCooler:Indirect:CelDekPad` |  | EP-only (no OS forward source found) | `` |
| `EvaporativeCooler:Indirect:ResearchSpecial` | `OS:EvaporativeCooler:Indirect:ResearchSpecial` | Generated by translator (has direct OS IDD peer) | `` |
| `EvaporativeCooler:Indirect:WetCoil` |  | EP-only (no OS forward source found) | `` |
| `EvaporativeFluidCooler:SingleSpeed` | `OS:EvaporativeFluidCooler:SingleSpeed` | Generated by translator (has direct OS IDD peer) | `translateEvaporativeFluidCoolerSingleSpeed` |
| `EvaporativeFluidCooler:TwoSpeed` | `OS:EvaporativeFluidCooler:TwoSpeed` | Generated by translator (has direct OS IDD peer) | `` |
| `Exterior:FuelEquipment` | `OS:Exterior:FuelEquipment` | Generated by translator (has direct OS IDD peer) | `translateExteriorFuelEquipment` |
| `Exterior:Lights` | `OS:Exterior:Lights` | Generated by translator (has direct OS IDD peer) | `translateExteriorLights` |
| `Exterior:WaterEquipment` | `OS:Exterior:WaterEquipment` | Generated by translator (has direct OS IDD peer) | `translateExteriorWaterEquipment` |
| `ExternalInterface` | `OS:ExternalInterface` | Generated by translator (has direct OS IDD peer) | `` |
| `ExternalInterface:Actuator` | `OS:ExternalInterface:Actuator` | Generated by translator (has direct OS IDD peer) | `` |
| `ExternalInterface:FunctionalMockupUnitExport:From:Variable` | `OS:ExternalInterface:FunctionalMockupUnitExport:From:Variable` | Generated by translator (has direct OS IDD peer) | `` |
| `ExternalInterface:FunctionalMockupUnitExport:To:Actuator` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Actuator` | Generated by translator (has direct OS IDD peer) | `` |
| `ExternalInterface:FunctionalMockupUnitExport:To:Schedule` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule` | Generated by translator (has direct OS IDD peer) | `` |
| `ExternalInterface:FunctionalMockupUnitExport:To:Variable` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Variable` | Generated by translator (has direct OS IDD peer) | `` |
| `ExternalInterface:FunctionalMockupUnitImport` | `OS:ExternalInterface:FunctionalMockupUnitImport` | Generated by translator (has direct OS IDD peer) | `` |
| `ExternalInterface:FunctionalMockupUnitImport:From:Variable` | `OS:ExternalInterface:FunctionalMockupUnitImport:From:Variable` | Generated by translator (has direct OS IDD peer) | `` |
| `ExternalInterface:FunctionalMockupUnitImport:To:Actuator` | `OS:ExternalInterface:FunctionalMockupUnitImport:To:Actuator` | Generated by translator (has direct OS IDD peer) | `` |
| `ExternalInterface:FunctionalMockupUnitImport:To:Schedule` | `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule` | Generated by translator (has direct OS IDD peer) | `` |
| `ExternalInterface:FunctionalMockupUnitImport:To:Variable` | `OS:ExternalInterface:FunctionalMockupUnitImport:To:Variable` | Generated by translator (has direct OS IDD peer) | `` |
| `ExternalInterface:Schedule` | `OS:ExternalInterface:Schedule` | Generated by translator (has direct OS IDD peer) | `` |
| `ExternalInterface:Variable` | `OS:ExternalInterface:Variable` | Generated by translator (has direct OS IDD peer) | `` |
| `Fan:ComponentModel` | `OS:Fan:ComponentModel` | Generated by translator (has direct OS IDD peer) | `translateFanComponentModel` |
| `Fan:ConstantVolume` | `OS:Fan:ConstantVolume` | Generated by translator (has direct OS IDD peer) | `translateFanConstantVolume` |
| `Fan:OnOff` | `OS:Fan:OnOff` | Generated by translator (has direct OS IDD peer) | `` |
| `Fan:SystemModel` | `OS:Fan:SystemModel` | Generated by translator (has direct OS IDD peer) | `translateFanSystemModel` |
| `Fan:VariableVolume` | `OS:Fan:VariableVolume` | Generated by translator (has direct OS IDD peer) | `` |
| `Fan:ZoneExhaust` | `OS:Fan:ZoneExhaust` | Generated by translator (has direct OS IDD peer) | `` |
| `FanPerformance:NightVentilation` |  | EP-only (no OS forward source found) | `` |
| `FaultModel:EnthalpySensorOffset:OutdoorAir` |  | EP-only (no OS forward source found) | `` |
| `FaultModel:EnthalpySensorOffset:ReturnAir` |  | EP-only (no OS forward source found) | `` |
| `FaultModel:Fouling:AirFilter` |  | EP-only (no OS forward source found) | `` |
| `FaultModel:Fouling:Boiler` |  | EP-only (no OS forward source found) | `` |
| `FaultModel:Fouling:Chiller` |  | EP-only (no OS forward source found) | `` |
| `FaultModel:Fouling:Coil` |  | EP-only (no OS forward source found) | `` |
| `FaultModel:Fouling:CoolingTower` |  | EP-only (no OS forward source found) | `` |
| `FaultModel:Fouling:EvaporativeCooler` |  | EP-only (no OS forward source found) | `` |
| `FaultModel:HumidistatOffset` |  | EP-only (no OS forward source found) | `` |
| `FaultModel:HumiditySensorOffset:OutdoorAir` |  | EP-only (no OS forward source found) | `` |
| `FaultModel:TemperatureSensorOffset:ChillerSupplyWater` |  | EP-only (no OS forward source found) | `` |
| `FaultModel:TemperatureSensorOffset:CoilSupplyAir` |  | EP-only (no OS forward source found) | `` |
| `FaultModel:TemperatureSensorOffset:CondenserSupplyWater` |  | EP-only (no OS forward source found) | `` |
| `FaultModel:TemperatureSensorOffset:OutdoorAir` |  | EP-only (no OS forward source found) | `` |
| `FaultModel:TemperatureSensorOffset:ReturnAir` |  | EP-only (no OS forward source found) | `` |
| `FaultModel:ThermostatOffset` |  | EP-only (no OS forward source found) | `` |
| `FenestrationSurface:Detailed` | `OS:SubSurface` | Generated by translator (no direct OS IDD peer) | `translateFenestrationSurfaceDetailed` |
| `Floor:Adiabatic` |  | EP-only (no OS forward source found) | `` |
| `Floor:Detailed` |  | EP-only (no OS forward source found) | `` |
| `Floor:GroundContact` |  | EP-only (no OS forward source found) | `` |
| `Floor:Interzone` |  | EP-only (no OS forward source found) | `` |
| `FluidCooler:SingleSpeed` | `OS:FluidCooler:SingleSpeed` | Generated by translator (has direct OS IDD peer) | `` |
| `FluidCooler:TwoSpeed` | `OS:FluidCooler:TwoSpeed` | Generated by translator (has direct OS IDD peer) | `` |
| `FluidProperties:Concentration` |  | EP-only (no OS forward source found) | `` |
| `FluidProperties:GlycolConcentration` |  | EP-only (no OS forward source found) | `` |
| `FluidProperties:Name` |  | EP-only (no OS forward source found) | `` |
| `FluidProperties:Saturated` |  | EP-only (no OS forward source found) | `` |
| `FluidProperties:Superheated` |  | EP-only (no OS forward source found) | `` |
| `FluidProperties:Temperatures` |  | EP-only (no OS forward source found) | `` |
| `Foundation:Kiva` | `OS:Foundation:Kiva` | Generated by translator (has direct OS IDD peer) | `translateFoundationKiva` |
| `Foundation:Kiva:Settings` | `OS:Foundation:Kiva:Settings` | Generated by translator (has direct OS IDD peer) | `translateFoundationKivaSettings` |
| `FuelFactors` | `OS:FuelFactors` | Generated by translator (has direct OS IDD peer) | `translateFuelFactors` |
| `GasEquipment` | `OS:GasEquipment` | Generated by translator (has direct OS IDD peer) | `translateGasEquipment` |
| `Generator:CombustionTurbine` |  | EP-only (no OS forward source found) | `` |
| `Generator:FuelCell` | `OS:Generator:FuelCell` | Generated by translator (has direct OS IDD peer) | `` |
| `Generator:FuelCell:AirSupply` | `OS:Generator:FuelCell:AirSupply` | Generated by translator (has direct OS IDD peer) | `` |
| `Generator:FuelCell:AuxiliaryHeater` | `OS:Generator:FuelCell:AuxiliaryHeater` | Generated by translator (has direct OS IDD peer) | `` |
| `Generator:FuelCell:ElectricalStorage` | `OS:Generator:FuelCell:ElectricalStorage` | Generated by translator (has direct OS IDD peer) | `` |
| `Generator:FuelCell:ExhaustGasToWaterHeatExchanger` | `OS:Generator:FuelCell:ExhaustGasToWaterHeatExchanger` | Generated by translator (has direct OS IDD peer) | `` |
| `Generator:FuelCell:Inverter` | `OS:Generator:FuelCell:Inverter` | Generated by translator (has direct OS IDD peer) | `` |
| `Generator:FuelCell:PowerModule` | `OS:Generator:FuelCell:PowerModule` | Generated by translator (has direct OS IDD peer) | `` |
| `Generator:FuelCell:StackCooler` | `OS:Generator:FuelCell:StackCooler` | Generated by translator (has direct OS IDD peer) | `` |
| `Generator:FuelCell:WaterSupply` | `OS:Generator:FuelCell:WaterSupply` | Generated by translator (has direct OS IDD peer) | `` |
| `Generator:FuelSupply` | `OS:Generator:FuelSupply` | Generated by translator (has direct OS IDD peer) | `` |
| `Generator:InternalCombustionEngine` |  | EP-only (no OS forward source found) | `` |
| `Generator:MicroCHP` |  | EP-only (no OS forward source found) | `` |
| `Generator:MicroCHP:NonNormalizedParameters` |  | EP-only (no OS forward source found) | `` |
| `Generator:MicroTurbine` | `OS:Generator:MicroTurbine` | Generated by translator (has direct OS IDD peer) | `translateGeneratorMicroTurbine` |
| `Generator:PVWatts` | `OS:Generator:PVWatts` | Generated by translator (has direct OS IDD peer) | `` |
| `Generator:Photovoltaic` | `OS:Generator:Photovoltaic` | Generated by translator (has direct OS IDD peer) | `` |
| `Generator:WindTurbine` | `OS:Generator:WindTurbine` | Generated by translator (has direct OS IDD peer) | `translateGeneratorWindTurbine` |
| `GeometryTransform` |  | EP-only (no OS forward source found) | `` |
| `GlazedDoor` |  | EP-only (no OS forward source found) | `` |
| `GlazedDoor:Interzone` |  | EP-only (no OS forward source found) | `` |
| `GlobalGeometryRules` |  | EP-only (no OS forward source found) | `` |
| `GroundHeatExchanger:HorizontalTrench` | `OS:GroundHeatExchanger:HorizontalTrench` | Generated by translator (has direct OS IDD peer) | `` |
| `GroundHeatExchanger:Pond` |  | EP-only (no OS forward source found) | `` |
| `GroundHeatExchanger:ResponseFactors` | `OS:GroundHeatExchanger:Vertical` | Generated by translator (no direct OS IDD peer) | `` |
| `GroundHeatExchanger:Slinky` |  | EP-only (no OS forward source found) | `` |
| `GroundHeatExchanger:Surface` |  | EP-only (no OS forward source found) | `` |
| `GroundHeatExchanger:System` | `OS:GroundHeatExchanger:Vertical` | Generated by translator (no direct OS IDD peer) | `translateGroundHeatExchangerVertical` |
| `GroundHeatExchanger:Vertical:Array` |  | EP-only (no OS forward source found) | `` |
| `GroundHeatExchanger:Vertical:Properties` | `OS:GroundHeatExchanger:Vertical` | Generated by translator (no direct OS IDD peer) | `` |
| `GroundHeatExchanger:Vertical:Single` |  | EP-only (no OS forward source found) | `` |
| `GroundHeatExchanger:Vertical:Sizing:Rectangle` |  | EP-only (no OS forward source found) | `` |
| `GroundHeatTransfer:Basement:AutoGrid` |  | EP-only (no OS forward source found) | `` |
| `GroundHeatTransfer:Basement:BldgData` |  | EP-only (no OS forward source found) | `` |
| `GroundHeatTransfer:Basement:ComBldg` |  | EP-only (no OS forward source found) | `` |
| `GroundHeatTransfer:Basement:EquivAutoGrid` |  | EP-only (no OS forward source found) | `` |
| `GroundHeatTransfer:Basement:Insulation` |  | EP-only (no OS forward source found) | `` |
| `GroundHeatTransfer:Basement:Interior` |  | EP-only (no OS forward source found) | `` |
| `GroundHeatTransfer:Basement:ManualGrid` |  | EP-only (no OS forward source found) | `` |
| `GroundHeatTransfer:Basement:MatlProps` |  | EP-only (no OS forward source found) | `` |
| `GroundHeatTransfer:Basement:SimParameters` |  | EP-only (no OS forward source found) | `` |
| `GroundHeatTransfer:Basement:SurfaceProps` |  | EP-only (no OS forward source found) | `` |
| `GroundHeatTransfer:Basement:XFACE` |  | EP-only (no OS forward source found) | `` |
| `GroundHeatTransfer:Basement:YFACE` |  | EP-only (no OS forward source found) | `` |
| `GroundHeatTransfer:Basement:ZFACE` |  | EP-only (no OS forward source found) | `` |
| `GroundHeatTransfer:Control` |  | EP-only (no OS forward source found) | `` |
| `GroundHeatTransfer:Slab:AutoGrid` |  | EP-only (no OS forward source found) | `` |
| `GroundHeatTransfer:Slab:BldgProps` |  | EP-only (no OS forward source found) | `` |
| `GroundHeatTransfer:Slab:BoundConds` |  | EP-only (no OS forward source found) | `` |
| `GroundHeatTransfer:Slab:EquivalentSlab` |  | EP-only (no OS forward source found) | `` |
| `GroundHeatTransfer:Slab:Insulation` |  | EP-only (no OS forward source found) | `` |
| `GroundHeatTransfer:Slab:ManualGrid` |  | EP-only (no OS forward source found) | `` |
| `GroundHeatTransfer:Slab:Materials` |  | EP-only (no OS forward source found) | `` |
| `GroundHeatTransfer:Slab:MatlProps` |  | EP-only (no OS forward source found) | `` |
| `GroundHeatTransfer:Slab:XFACE` |  | EP-only (no OS forward source found) | `` |
| `GroundHeatTransfer:Slab:YFACE` |  | EP-only (no OS forward source found) | `` |
| `GroundHeatTransfer:Slab:ZFACE` |  | EP-only (no OS forward source found) | `` |
| `HVACSystemRootFindingAlgorithm` |  | EP-only (no OS forward source found) | `` |
| `HVACTemplate:Plant:Boiler` |  | EP-only (no OS forward source found) | `` |
| `HVACTemplate:Plant:Boiler:ObjectReference` |  | EP-only (no OS forward source found) | `` |
| `HVACTemplate:Plant:ChilledWaterLoop` |  | EP-only (no OS forward source found) | `` |
| `HVACTemplate:Plant:Chiller` |  | EP-only (no OS forward source found) | `` |
| `HVACTemplate:Plant:Chiller:ObjectReference` |  | EP-only (no OS forward source found) | `` |
| `HVACTemplate:Plant:HotWaterLoop` |  | EP-only (no OS forward source found) | `` |
| `HVACTemplate:Plant:MixedWaterLoop` |  | EP-only (no OS forward source found) | `` |
| `HVACTemplate:Plant:Tower` |  | EP-only (no OS forward source found) | `` |
| `HVACTemplate:Plant:Tower:ObjectReference` |  | EP-only (no OS forward source found) | `` |
| `HVACTemplate:System:ConstantVolume` |  | EP-only (no OS forward source found) | `` |
| `HVACTemplate:System:DedicatedOutdoorAir` |  | EP-only (no OS forward source found) | `` |
| `HVACTemplate:System:DualDuct` |  | EP-only (no OS forward source found) | `` |
| `HVACTemplate:System:PackagedVAV` |  | EP-only (no OS forward source found) | `` |
| `HVACTemplate:System:Unitary` |  | EP-only (no OS forward source found) | `` |
| `HVACTemplate:System:UnitaryHeatPump:AirToAir` |  | EP-only (no OS forward source found) | `` |
| `HVACTemplate:System:UnitarySystem` |  | EP-only (no OS forward source found) | `` |
| `HVACTemplate:System:VAV` |  | EP-only (no OS forward source found) | `` |
| `HVACTemplate:System:VRF` |  | EP-only (no OS forward source found) | `` |
| `HVACTemplate:Thermostat` |  | EP-only (no OS forward source found) | `` |
| `HVACTemplate:Zone:BaseboardHeat` |  | EP-only (no OS forward source found) | `` |
| `HVACTemplate:Zone:ConstantVolume` |  | EP-only (no OS forward source found) | `` |
| `HVACTemplate:Zone:DualDuct` |  | EP-only (no OS forward source found) | `` |
| `HVACTemplate:Zone:FanCoil` |  | EP-only (no OS forward source found) | `` |
| `HVACTemplate:Zone:IdealLoadsAirSystem` | `OS:ThermalZone` | Generated by translator (no direct OS IDD peer) | `` |
| `HVACTemplate:Zone:PTAC` |  | EP-only (no OS forward source found) | `` |
| `HVACTemplate:Zone:PTHP` |  | EP-only (no OS forward source found) | `` |
| `HVACTemplate:Zone:Unitary` |  | EP-only (no OS forward source found) | `` |
| `HVACTemplate:Zone:VAV` |  | EP-only (no OS forward source found) | `` |
| `HVACTemplate:Zone:VAV:FanPowered` |  | EP-only (no OS forward source found) | `` |
| `HVACTemplate:Zone:VAV:HeatAndCool` |  | EP-only (no OS forward source found) | `` |
| `HVACTemplate:Zone:VRF` |  | EP-only (no OS forward source found) | `` |
| `HVACTemplate:Zone:WaterToAirHeatPump` |  | EP-only (no OS forward source found) | `` |
| `HeaderedPumps:ConstantSpeed` | `OS:HeaderedPumps:ConstantSpeed` | Generated by translator (has direct OS IDD peer) | `` |
| `HeaderedPumps:VariableSpeed` | `OS:HeaderedPumps:VariableSpeed` | Generated by translator (has direct OS IDD peer) | `` |
| `HeatBalanceAlgorithm` | `OS:HeatBalanceAlgorithm` | Generated by translator (has direct OS IDD peer) | `translateHeatBalanceAlgorithm` |
| `HeatBalanceSettings:ConductionFiniteDifference` |  | EP-only (no OS forward source found) | `` |
| `HeatExchanger:AirToAir:FlatPlate` |  | EP-only (no OS forward source found) | `` |
| `HeatExchanger:AirToAir:SensibleAndLatent` | `OS:HeatExchanger:AirToAir:SensibleAndLatent` | Generated by translator (has direct OS IDD peer) | `` |
| `HeatExchanger:Desiccant:BalancedFlow` | `OS:HeatExchanger:Desiccant:BalancedFlow` | Generated by translator (has direct OS IDD peer) | `` |
| `HeatExchanger:Desiccant:BalancedFlow:PerformanceDataType1` | `OS:HeatExchanger:Desiccant:BalancedFlow:PerformanceDataType1` | Generated by translator (has direct OS IDD peer) | `` |
| `HeatExchanger:FluidToFluid` | `OS:HeatExchanger:FluidToFluid` | Generated by translator (has direct OS IDD peer) | `` |
| `HeatPump:AirToWater` | `OS:HeatPump:AirToWater` | Generated by translator (has direct OS IDD peer) | `translateHeatPumpAirToWater` |
| `HeatPump:AirToWater:FuelFired:Cooling` | `OS:HeatPump:AirToWater:FuelFired:Cooling` | Generated by translator (has direct OS IDD peer) | `` |
| `HeatPump:AirToWater:FuelFired:Heating` | `OS:HeatPump:AirToWater:FuelFired:Heating` | Generated by translator (has direct OS IDD peer) | `` |
| `HeatPump:PlantLoop:EIR:Cooling` | `OS:HeatPump:PlantLoop:EIR:Cooling` | Generated by translator (has direct OS IDD peer) | `` |
| `HeatPump:PlantLoop:EIR:Heating` | `OS:HeatPump:PlantLoop:EIR:Heating` | Generated by translator (has direct OS IDD peer) | `` |
| `HeatPump:WaterToWater:EquationFit:Cooling` | `OS:HeatPump:WaterToWater:EquationFit:Cooling` | Generated by translator (has direct OS IDD peer) | `` |
| `HeatPump:WaterToWater:EquationFit:Heating` | `OS:HeatPump:WaterToWater:EquationFit:Heating` | Generated by translator (has direct OS IDD peer) | `` |
| `HeatPump:WaterToWater:ParameterEstimation:Cooling` |  | EP-only (no OS forward source found) | `` |
| `HeatPump:WaterToWater:ParameterEstimation:Heating` |  | EP-only (no OS forward source found) | `` |
| `HotWaterEquipment` | `OS:HotWaterEquipment` | Generated by translator (has direct OS IDD peer) | `translateHotWaterEquipment` |
| `Humidifier:Steam:Electric` | `OS:Humidifier:Steam:Electric` | Generated by translator (has direct OS IDD peer) | `` |
| `Humidifier:Steam:Gas` | `OS:Humidifier:Steam:Gas` | Generated by translator (has direct OS IDD peer) | `` |
| `HybridModel:Zone` |  | EP-only (no OS forward source found) | `` |
| `IndoorLivingWall` |  | EP-only (no OS forward source found) | `` |
| `InternalMass` | `OS:InteriorPartitionSurface`, `OS:InternalMass` | Generated by translator (has direct OS IDD peer) | `translateInternalMass` |
| `LifeCycleCost:NonrecurringCost` | `OS:LifeCycleCost` | Generated by translator (no direct OS IDD peer) | `` |
| `LifeCycleCost:Parameters` | `OS:LifeCycleCost:Parameters` | Generated by translator (has direct OS IDD peer) | `` |
| `LifeCycleCost:RecurringCosts` | `OS:LifeCycleCost` | Generated by translator (no direct OS IDD peer) | `` |
| `LifeCycleCost:UseAdjustment` |  | EP-only (no OS forward source found) | `` |
| `LifeCycleCost:UsePriceEscalation` |  | EP-only (no OS forward source found) | `` |
| `Lights` | `OS:Lights`, `OS:Luminaire` | Generated by translator (has direct OS IDD peer) | `translateLights` |
| `LoadProfile:Plant` | `OS:LoadProfile:Plant` | Generated by translator (has direct OS IDD peer) | `` |
| `Material` | `OS:Material` | Generated by translator (has direct OS IDD peer) | `translateMaterial` |
| `Material:AirGap` | `OS:Material:AirGap` | Generated by translator (has direct OS IDD peer) | `translateMaterialAirGap` |
| `Material:InfraredTransparent` | `OS:Material:InfraredTransparent` | Generated by translator (has direct OS IDD peer) | `` |
| `Material:NoMass` | `OS:Material:NoMass` | Generated by translator (has direct OS IDD peer) | `translateMaterialNoMass` |
| `Material:RoofVegetation` | `OS:Material:RoofVegetation` | Generated by translator (has direct OS IDD peer) | `` |
| `MaterialProperty:GlazingSpectralData` | `OS:MaterialProperty:GlazingSpectralData` | Generated by translator (has direct OS IDD peer) | `translateMaterialPropertyGlazingSpectralData` |
| `MaterialProperty:HeatAndMoistureTransfer:Diffusion` |  | EP-only (no OS forward source found) | `` |
| `MaterialProperty:HeatAndMoistureTransfer:Redistribution` |  | EP-only (no OS forward source found) | `` |
| `MaterialProperty:HeatAndMoistureTransfer:Settings` |  | EP-only (no OS forward source found) | `` |
| `MaterialProperty:HeatAndMoistureTransfer:SorptionIsotherm` |  | EP-only (no OS forward source found) | `` |
| `MaterialProperty:HeatAndMoistureTransfer:Suction` |  | EP-only (no OS forward source found) | `` |
| `MaterialProperty:HeatAndMoistureTransfer:ThermalConductivity` |  | EP-only (no OS forward source found) | `` |
| `MaterialProperty:MoisturePenetrationDepth:Settings` | `OS:MaterialProperty:MoisturePenetrationDepth:Settings` | Generated by translator (has direct OS IDD peer) | `` |
| `MaterialProperty:PhaseChange` | `OS:MaterialProperty:PhaseChange` | Generated by translator (has direct OS IDD peer) | `` |
| `MaterialProperty:PhaseChangeHysteresis` | `OS:MaterialProperty:PhaseChangeHysteresis` | Generated by translator (has direct OS IDD peer) | `` |
| `MaterialProperty:VariableAbsorptance` |  | EP-only (no OS forward source found) | `` |
| `MaterialProperty:VariableThermalConductivity` |  | EP-only (no OS forward source found) | `` |
| `Matrix:TwoDimension` |  | EP-only (no OS forward source found) | `` |
| `Meter:Custom` | `OS:Meter:Custom` | Generated by translator (has direct OS IDD peer) | `translateMeterCustom` |
| `Meter:CustomDecrement` | `OS:Meter:CustomDecrement` | Generated by translator (has direct OS IDD peer) | `translateMeterCustomDecrement` |
| `Node` |  | EP-only (no OS forward source found) | `` |
| `NodeList` | `OS:AirLoopHVAC`, `OS:AirLoopHVAC:ReturnPlenum`, `OS:PortList` | Generated by translator (no direct OS IDD peer) | `` |
| `OtherEquipment` | `OS:OtherEquipment` | Generated by translator (has direct OS IDD peer) | `translateOtherEquipment` |
| `OutdoorAir:Mixer` | `OS:AirLoopHVAC:OutdoorAirSystem`, `OS:AirLoopHVAC:UnitaryHeatCool:VAVChangeoverBypass`, `OS:ZoneHVAC:FourPipeFanCoil`, `OS:ZoneHVAC:PackagedTerminalAirConditioner`, `OS:ZoneHVAC:PackagedTerminalHeatPump`, `OS:ZoneHVAC:TerminalUnit:VariableRefrigerantFlow`, `OS:ZoneHVAC:WaterToAirHeatPump` | Generated by translator (no direct OS IDD peer) | `` |
| `OutdoorAir:Node` | `OS:HeatPump:AirToWater:FuelFired:Cooling`, `OS:HeatPump:AirToWater:FuelFired:Heating` | Generated by translator (no direct OS IDD peer) | `` |
| `OutdoorAir:NodeList` | `OS:AirLoopHVAC:OutdoorAirSystem`, `OS:AirLoopHVAC:UnitaryHeatCool:VAVChangeoverBypass`, `OS:Chiller:Electric:ASHRAE205`, `OS:Chiller:Electric:EIR`, `OS:Coil:Cooling:DX`, `OS:Coil:Cooling:DX:SingleSpeed:ThermalStorage`, `OS:EvaporativeCooler:Indirect:ResearchSpecial`, `OS:Generator:FuelCell:AirSupply`, `OS:Generator:FuelCell:PowerModule`, `OS:HeatPump:AirToWater`, `OS:HeatPump:PlantLoop:EIR:Cooling`, `OS:HeatPump:PlantLoop:EIR:Heating`, `OS:Pipe:Outdoor`, `OS:ThermalStorage:ChilledWater:Stratified`, `OS:WaterHeater:Mixed`, `OS:ZoneHVAC:EnergyRecoveryVentilator`, `OS:ZoneHVAC:EvaporativeCoolerUnit`, `OS:ZoneHVAC:FourPipeFanCoil`, `OS:ZoneHVAC:PackagedTerminalAirConditioner`, `OS:ZoneHVAC:PackagedTerminalHeatPump`, `OS:ZoneHVAC:TerminalUnit:VariableRefrigerantFlow`, `OS:ZoneHVAC:UnitVentilator`, `OS:ZoneHVAC:WaterToAirHeatPump` | Generated by translator (no direct OS IDD peer) | `` |
| `Output:Constructions` | `OS:Output:Constructions` | Generated by translator (has direct OS IDD peer) | `translateOutputConstructions` |
| `Output:DaylightFactors` |  | EP-only (no OS forward source found) | `` |
| `Output:DebuggingData` | `OS:Output:DebuggingData` | Generated by translator (has direct OS IDD peer) | `translateOutputDebuggingData` |
| `Output:Diagnostics` | `OS:Output:Diagnostics` | Generated by translator (has direct OS IDD peer) | `translateOutputDiagnostics` |
| `Output:EnergyManagementSystem` | `OS:Output:EnergyManagementSystem` | Generated by translator (has direct OS IDD peer) | `translateOutputEnergyManagementSystem` |
| `Output:EnvironmentalImpactFactors` | `OS:Output:EnvironmentalImpactFactors` | Generated by translator (has direct OS IDD peer) | `translateOutputEnvironmentalImpactFactors` |
| `Output:IlluminanceMap` | `OS:ThermalZone` | Generated by translator (no direct OS IDD peer) | `translateOutputIlluminanceMap` |
| `Output:JSON` | `OS:Output:JSON` | Generated by translator (has direct OS IDD peer) | `translateOutputJSON` |
| `Output:Meter` |  | EP-only (no OS forward source found) | `translateOutputMeter` |
| `Output:Meter:Cumulative` |  | EP-only (no OS forward source found) | `translateOutputMeterCumulative` |
| `Output:Meter:Cumulative:MeterFileOnly` |  | EP-only (no OS forward source found) | `translateOutputMeterCumulativeMeterFileOnly` |
| `Output:Meter:MeterFileOnly` |  | EP-only (no OS forward source found) | `translateOutputMeterMeterFileOnly` |
| `Output:PreprocessorMessage` |  | EP-only (no OS forward source found) | `` |
| `Output:SQLite` | `OS:Output:SQLite` | Generated by translator (has direct OS IDD peer) | `translateOutputSQLite` |
| `Output:Schedules` | `OS:Output:Schedules` | Generated by translator (has direct OS IDD peer) | `translateOutputSchedules` |
| `Output:Surfaces:Drawing` |  | EP-only (no OS forward source found) | `` |
| `Output:Surfaces:List` |  | EP-only (no OS forward source found) | `` |
| `Output:Table:Annual` | `OS:Output:Table:Annual` | Generated by translator (has direct OS IDD peer) | `translateOutputTableAnnual` |
| `Output:Table:Monthly` | `OS:Output:Table:Monthly` | Generated by translator (has direct OS IDD peer) | `translateOutputTableMonthly` |
| `Output:Table:ReportPeriod` |  | EP-only (no OS forward source found) | `` |
| `Output:Table:SummaryReports` | `OS:Output:Table:SummaryReports` | Generated by translator (has direct OS IDD peer) | `translateOutputTableSummaryReports` |
| `Output:Table:TimeBins` |  | EP-only (no OS forward source found) | `` |
| `Output:Variable` | `OS:Output:Variable` | Generated by translator (has direct OS IDD peer) | `translateOutputVariable` |
| `Output:VariableDictionary` |  | EP-only (no OS forward source found) | `` |
| `OutputControl:Files` | `OS:OutputControl:Files` | Generated by translator (has direct OS IDD peer) | `translateOutputControlFiles` |
| `OutputControl:IlluminanceMap:Style` |  | EP-only (no OS forward source found) | `` |
| `OutputControl:ReportingTolerances` | `OS:OutputControl:ReportingTolerances` | Generated by translator (has direct OS IDD peer) | `translateOutputControlReportingTolerances` |
| `OutputControl:ResilienceSummaries` | `OS:OutputControl:ResilienceSummaries` | Generated by translator (has direct OS IDD peer) | `translateOutputControlResilienceSummaries` |
| `OutputControl:Sizing:Style` |  | EP-only (no OS forward source found) | `` |
| `OutputControl:SurfaceColorScheme` |  | EP-only (no OS forward source found) | `` |
| `OutputControl:Table:Style` | `OS:OutputControl:Table:Style` | Generated by translator (has direct OS IDD peer) | `translateOutputControlTableStyle` |
| `OutputControl:Timestamp` | `OS:OutputControl:Timestamp` | Generated by translator (has direct OS IDD peer) | `translateOutputControlTimestamp` |
| `Parametric:FileNameSuffix` |  | EP-only (no OS forward source found) | `` |
| `Parametric:Logic` |  | EP-only (no OS forward source found) | `` |
| `Parametric:RunControl` |  | EP-only (no OS forward source found) | `` |
| `Parametric:SetValueForRun` |  | EP-only (no OS forward source found) | `` |
| `People` | `OS:People` | Generated by translator (has direct OS IDD peer) | `translatePeople` |
| `PerformancePrecisionTradeoffs` | `OS:PerformancePrecisionTradeoffs` | Generated by translator (has direct OS IDD peer) | `translatePerformancePrecisionTradeoffs` |
| `PhotovoltaicPerformance:Sandia` | `OS:PhotovoltaicPerformance:Sandia` | Generated by translator (has direct OS IDD peer) | `translatePhotovoltaicPerformanceSandia` |
| `PhotovoltaicPerformance:Simple` | `OS:PhotovoltaicPerformance:Simple` | Generated by translator (has direct OS IDD peer) | `` |
| `Pipe:Adiabatic` | `OS:Pipe:Adiabatic`, `OS:PlantLoop` | Generated by translator (has direct OS IDD peer) | `` |
| `Pipe:Adiabatic:Steam` |  | EP-only (no OS forward source found) | `` |
| `Pipe:Indoor` | `OS:Pipe:Indoor` | Generated by translator (has direct OS IDD peer) | `` |
| `Pipe:Outdoor` | `OS:Pipe:Outdoor` | Generated by translator (has direct OS IDD peer) | `` |
| `Pipe:Underground` |  | EP-only (no OS forward source found) | `` |
| `PipingSystem:Underground:Domain` |  | EP-only (no OS forward source found) | `` |
| `PipingSystem:Underground:PipeCircuit` |  | EP-only (no OS forward source found) | `` |
| `PipingSystem:Underground:PipeSegment` |  | EP-only (no OS forward source found) | `` |
| `PlantComponent:TemperatureSource` | `OS:PlantComponent:TemperatureSource` | Generated by translator (has direct OS IDD peer) | `` |
| `PlantComponent:UserDefined` | `OS:PlantComponent:UserDefined` | Generated by translator (has direct OS IDD peer) | `` |
| `PlantEquipmentList` | `OS:PlantEquipmentOperation:CoolingLoad`, `OS:PlantEquipmentOperation:HeatingLoad`, `OS:PlantEquipmentOperation:OutdoorDewpoint`, `OS:PlantEquipmentOperation:OutdoorDewpointDifference`, `OS:PlantEquipmentOperation:OutdoorDryBulb`, `OS:PlantEquipmentOperation:OutdoorDryBulbDifference`, `OS:PlantEquipmentOperation:OutdoorRelativeHumidity`, `OS:PlantEquipmentOperation:OutdoorWetBulb`, `OS:PlantEquipmentOperation:OutdoorWetBulbDifference` | Generated by translator (no direct OS IDD peer) | `` |
| `PlantEquipmentOperation:ChillerHeaterChangeover` |  | EP-only (no OS forward source found) | `` |
| `PlantEquipmentOperation:ComponentSetpoint` |  | EP-only (no OS forward source found) | `` |
| `PlantEquipmentOperation:CoolingLoad` | `OS:PlantEquipmentOperation:CoolingLoad` | Generated by translator (has direct OS IDD peer) | `` |
| `PlantEquipmentOperation:HeatingLoad` | `OS:PlantEquipmentOperation:HeatingLoad` | Generated by translator (has direct OS IDD peer) | `` |
| `PlantEquipmentOperation:OutdoorDewpoint` | `OS:PlantEquipmentOperation:OutdoorDewpoint` | Generated by translator (has direct OS IDD peer) | `` |
| `PlantEquipmentOperation:OutdoorDewpointDifference` | `OS:PlantEquipmentOperation:OutdoorDewpointDifference` | Generated by translator (has direct OS IDD peer) | `` |
| `PlantEquipmentOperation:OutdoorDryBulb` | `OS:PlantEquipmentOperation:OutdoorDryBulb` | Generated by translator (has direct OS IDD peer) | `` |
| `PlantEquipmentOperation:OutdoorDryBulbDifference` | `OS:PlantEquipmentOperation:OutdoorDryBulbDifference` | Generated by translator (has direct OS IDD peer) | `` |
| `PlantEquipmentOperation:OutdoorRelativeHumidity` | `OS:PlantEquipmentOperation:OutdoorRelativeHumidity` | Generated by translator (has direct OS IDD peer) | `` |
| `PlantEquipmentOperation:OutdoorWetBulb` | `OS:PlantEquipmentOperation:OutdoorWetBulb` | Generated by translator (has direct OS IDD peer) | `` |
| `PlantEquipmentOperation:OutdoorWetBulbDifference` | `OS:PlantEquipmentOperation:OutdoorWetBulbDifference` | Generated by translator (has direct OS IDD peer) | `` |
| `PlantEquipmentOperation:ThermalEnergyStorage` |  | EP-only (no OS forward source found) | `` |
| `PlantEquipmentOperation:Uncontrolled` |  | EP-only (no OS forward source found) | `` |
| `PlantEquipmentOperation:UserDefined` |  | EP-only (no OS forward source found) | `` |
| `PlantEquipmentOperationSchemes` |  | EP-only (no OS forward source found) | `` |
| `PlantLoop` | `OS:PlantLoop` | Generated by translator (has direct OS IDD peer) | `` |
| `Pump:ConstantSpeed` | `OS:Pump:ConstantSpeed` | Generated by translator (has direct OS IDD peer) | `` |
| `Pump:VariableSpeed` | `OS:Pump:VariableSpeed` | Generated by translator (has direct OS IDD peer) | `` |
| `Pump:VariableSpeed:Condensate` |  | EP-only (no OS forward source found) | `` |
| `PythonPlugin:Instance` | `OS:PythonPlugin:Instance` | Generated by translator (has direct OS IDD peer) | `` |
| `PythonPlugin:OutputVariable` | `OS:PythonPlugin:OutputVariable` | Generated by translator (has direct OS IDD peer) | `` |
| `PythonPlugin:SearchPaths` | `OS:PythonPlugin:Instance`, `OS:PythonPlugin:SearchPaths` | Generated by translator (has direct OS IDD peer) | `` |
| `PythonPlugin:TrendVariable` | `OS:PythonPlugin:TrendVariable` | Generated by translator (has direct OS IDD peer) | `` |
| `PythonPlugin:Variables` | `OS:PythonPlugin:Variable` | Generated by translator (no direct OS IDD peer) | `` |
| `Refrigeration:AirChiller` | `OS:Refrigeration:AirChiller` | Generated by translator (has direct OS IDD peer) | `` |
| `Refrigeration:Case` | `OS:Refrigeration:Case` | Generated by translator (has direct OS IDD peer) | `translateRefrigerationCase` |
| `Refrigeration:CaseAndWalkInList` | `OS:Refrigeration:CompressorRack`, `OS:Refrigeration:SecondarySystem`, `OS:Refrigeration:System`, `OS:Refrigeration:TranscriticalSystem` | Generated by translator (no direct OS IDD peer) | `` |
| `Refrigeration:Compressor` | `OS:Refrigeration:Compressor` | Generated by translator (has direct OS IDD peer) | `translateRefrigerationCompressor` |
| `Refrigeration:CompressorList` | `OS:Refrigeration:System`, `OS:Refrigeration:TranscriticalSystem` | Generated by translator (no direct OS IDD peer) | `` |
| `Refrigeration:CompressorRack` | `OS:Refrigeration:CompressorRack` | Generated by translator (has direct OS IDD peer) | `` |
| `Refrigeration:Condenser:AirCooled` | `OS:Refrigeration:Condenser:AirCooled` | Generated by translator (has direct OS IDD peer) | `` |
| `Refrigeration:Condenser:Cascade` | `OS:Refrigeration:Condenser:Cascade` | Generated by translator (has direct OS IDD peer) | `` |
| `Refrigeration:Condenser:EvaporativeCooled` | `OS:Refrigeration:Condenser:EvaporativeCooled` | Generated by translator (has direct OS IDD peer) | `` |
| `Refrigeration:Condenser:WaterCooled` | `OS:Refrigeration:Condenser:WaterCooled` | Generated by translator (has direct OS IDD peer) | `` |
| `Refrigeration:GasCooler:AirCooled` | `OS:Refrigeration:GasCooler:AirCooled` | Generated by translator (has direct OS IDD peer) | `` |
| `Refrigeration:SecondarySystem` | `OS:Refrigeration:SecondarySystem` | Generated by translator (has direct OS IDD peer) | `` |
| `Refrigeration:Subcooler` | `OS:Refrigeration:Subcooler:LiquidSuction`, `OS:Refrigeration:Subcooler:Mechanical` | Generated by translator (no direct OS IDD peer) | `` |
| `Refrigeration:System` | `OS:Refrigeration:System` | Generated by translator (has direct OS IDD peer) | `` |
| `Refrigeration:TranscriticalSystem` | `OS:Refrigeration:TranscriticalSystem` | Generated by translator (has direct OS IDD peer) | `` |
| `Refrigeration:TransferLoadList` | `OS:Refrigeration:System` | Generated by translator (no direct OS IDD peer) | `` |
| `Refrigeration:WalkIn` | `OS:Refrigeration:WalkIn` | Generated by translator (has direct OS IDD peer) | `` |
| `Roof` |  | EP-only (no OS forward source found) | `` |
| `RoofCeiling:Detailed` |  | EP-only (no OS forward source found) | `` |
| `RoofIrrigation` |  | EP-only (no OS forward source found) | `` |
| `RoomAir:Node` |  | EP-only (no OS forward source found) | `` |
| `RoomAir:Node:AirflowNetwork` |  | EP-only (no OS forward source found) | `` |
| `RoomAir:Node:AirflowNetwork:AdjacentSurfaceList` |  | EP-only (no OS forward source found) | `` |
| `RoomAir:Node:AirflowNetwork:HVACEquipment` |  | EP-only (no OS forward source found) | `` |
| `RoomAir:Node:AirflowNetwork:InternalGains` |  | EP-only (no OS forward source found) | `` |
| `RoomAir:TemperaturePattern:ConstantGradient` |  | EP-only (no OS forward source found) | `` |
| `RoomAir:TemperaturePattern:NondimensionalHeight` |  | EP-only (no OS forward source found) | `` |
| `RoomAir:TemperaturePattern:SurfaceMapping` |  | EP-only (no OS forward source found) | `` |
| `RoomAir:TemperaturePattern:TwoGradient` |  | EP-only (no OS forward source found) | `` |
| `RoomAir:TemperaturePattern:UserDefined` |  | EP-only (no OS forward source found) | `` |
| `RoomAirModelType` |  | EP-only (no OS forward source found) | `` |
| `RoomAirSettings:AirflowNetwork` |  | EP-only (no OS forward source found) | `` |
| `RoomAirSettings:CrossVentilation` |  | EP-only (no OS forward source found) | `` |
| `RoomAirSettings:OneNodeDisplacementVentilation` |  | EP-only (no OS forward source found) | `` |
| `RoomAirSettings:ThreeNodeDisplacementVentilation` |  | EP-only (no OS forward source found) | `` |
| `RoomAirSettings:UnderFloorAirDistributionExterior` |  | EP-only (no OS forward source found) | `` |
| `RoomAirSettings:UnderFloorAirDistributionInterior` |  | EP-only (no OS forward source found) | `` |
| `RunPeriod` | `OS:RunPeriod` | Generated by translator (has direct OS IDD peer) | `translateRunPeriod` |
| `RunPeriodControl:DaylightSavingTime` | `OS:RunPeriodControl:DaylightSavingTime` | Generated by translator (has direct OS IDD peer) | `translateRunPeriodControlDaylightSavingTime` |
| `RunPeriodControl:SpecialDays` | `OS:RunPeriodControl:SpecialDays` | Generated by translator (has direct OS IDD peer) | `translateRunPeriodControlSpecialDays` |
| `Schedule:Compact` | `OS:Schedule:Compact`, `OS:Schedule:FixedInterval`, `OS:Schedule:VariableInterval`, `OS:ThermalZone`, `OS:ZoneControl:Thermostat:StagedDualSetpoint` | Generated by translator (has direct OS IDD peer) | `translateScheduleCompact` |
| `Schedule:Constant` | `OS:Schedule:Constant` | Generated by translator (has direct OS IDD peer) | `translateScheduleConstant` |
| `Schedule:Day:Hourly` |  | EP-only (no OS forward source found) | `translateScheduleDayHourly` |
| `Schedule:Day:Interval` | `OS:Schedule:Day` | Generated by translator (no direct OS IDD peer) | `translateScheduleDayInterval` |
| `Schedule:Day:List` |  | EP-only (no OS forward source found) | `` |
| `Schedule:File` | `OS:Schedule:File` | Generated by translator (has direct OS IDD peer) | `translateScheduleFile` |
| `Schedule:File:Shading` |  | EP-only (no OS forward source found) | `` |
| `Schedule:Week:Compact` |  | EP-only (no OS forward source found) | `` |
| `Schedule:Week:Daily` | `OS:Schedule:Week` | Generated by translator (no direct OS IDD peer) | `translateScheduleWeekDaily` |
| `Schedule:Year` | `OS:Schedule:Ruleset`, `OS:Schedule:Year` | Generated by translator (has direct OS IDD peer) | `translateScheduleYear` |
| `ScheduleTypeLimits` | `OS:ScheduleTypeLimits`, `OS:ThermalZone`, `OS:ZoneControl:Thermostat:StagedDualSetpoint` | Generated by translator (has direct OS IDD peer) | `translateScheduleTypeLimits` |
| `SetpointManager:Coldest` | `OS:SetpointManager:Coldest` | Generated by translator (has direct OS IDD peer) | `` |
| `SetpointManager:CondenserEnteringReset` |  | EP-only (no OS forward source found) | `` |
| `SetpointManager:CondenserEnteringReset:Ideal` |  | EP-only (no OS forward source found) | `` |
| `SetpointManager:FollowGroundTemperature` | `OS:SetpointManager:FollowGroundTemperature` | Generated by translator (has direct OS IDD peer) | `` |
| `SetpointManager:FollowOutdoorAirTemperature` | `OS:SetpointManager:FollowOutdoorAirTemperature` | Generated by translator (has direct OS IDD peer) | `` |
| `SetpointManager:FollowSystemNodeTemperature` | `OS:SetpointManager:FollowSystemNodeTemperature` | Generated by translator (has direct OS IDD peer) | `` |
| `SetpointManager:MixedAir` | `OS:CoilSystem:Cooling:Water:HeatExchangerAssisted`, `OS:SetpointManager:MixedAir` | Generated by translator (has direct OS IDD peer) | `translateSetpointManagerMixedAir` |
| `SetpointManager:MultiZone:Cooling:Average` | `OS:SetpointManager:MultiZone:Cooling:Average` | Generated by translator (has direct OS IDD peer) | `` |
| `SetpointManager:MultiZone:Heating:Average` | `OS:SetpointManager:MultiZone:Heating:Average` | Generated by translator (has direct OS IDD peer) | `` |
| `SetpointManager:MultiZone:Humidity:Maximum` | `OS:SetpointManager:MultiZone:Humidity:Maximum` | Generated by translator (has direct OS IDD peer) | `` |
| `SetpointManager:MultiZone:Humidity:Minimum` | `OS:SetpointManager:MultiZone:Humidity:Minimum` | Generated by translator (has direct OS IDD peer) | `` |
| `SetpointManager:MultiZone:MaximumHumidity:Average` | `OS:SetpointManager:MultiZone:MaximumHumidity:Average` | Generated by translator (has direct OS IDD peer) | `` |
| `SetpointManager:MultiZone:MinimumHumidity:Average` | `OS:SetpointManager:MultiZone:MinimumHumidity:Average` | Generated by translator (has direct OS IDD peer) | `` |
| `SetpointManager:OutdoorAirPretreat` | `OS:SetpointManager:OutdoorAirPretreat` | Generated by translator (has direct OS IDD peer) | `` |
| `SetpointManager:OutdoorAirReset` | `OS:SetpointManager:OutdoorAirReset` | Generated by translator (has direct OS IDD peer) | `` |
| `SetpointManager:ReturnAirBypassFlow` |  | EP-only (no OS forward source found) | `` |
| `SetpointManager:ReturnTemperature:ChilledWater` |  | EP-only (no OS forward source found) | `` |
| `SetpointManager:ReturnTemperature:HotWater` |  | EP-only (no OS forward source found) | `` |
| `SetpointManager:Scheduled` | `OS:SetpointManager:Scheduled` | Generated by translator (has direct OS IDD peer) | `translateSetpointManagerScheduled` |
| `SetpointManager:Scheduled:DualSetpoint` | `OS:SetpointManager:Scheduled:DualSetpoint` | Generated by translator (has direct OS IDD peer) | `` |
| `SetpointManager:SingleZone:Cooling` | `OS:SetpointManager:SingleZone:Cooling` | Generated by translator (has direct OS IDD peer) | `` |
| `SetpointManager:SingleZone:Heating` | `OS:SetpointManager:SingleZone:Heating` | Generated by translator (has direct OS IDD peer) | `` |
| `SetpointManager:SingleZone:Humidity:Maximum` | `OS:SetpointManager:SingleZone:Humidity:Maximum` | Generated by translator (has direct OS IDD peer) | `` |
| `SetpointManager:SingleZone:Humidity:Minimum` | `OS:SetpointManager:SingleZone:Humidity:Minimum` | Generated by translator (has direct OS IDD peer) | `` |
| `SetpointManager:SingleZone:OneStageCooling` | `OS:SetpointManager:SingleZone:OneStageCooling` | Generated by translator (has direct OS IDD peer) | `` |
| `SetpointManager:SingleZone:OneStageHeating` | `OS:SetpointManager:SingleZone:OneStageHeating` | Generated by translator (has direct OS IDD peer) | `` |
| `SetpointManager:SingleZone:Reheat` | `OS:SetpointManager:SingleZone:Reheat` | Generated by translator (has direct OS IDD peer) | `translateSetpointManagerSingleZoneReheat` |
| `SetpointManager:SystemNodeReset:Humidity` | `OS:SetpointManager:SystemNodeReset:Humidity` | Generated by translator (has direct OS IDD peer) | `translateSetpointManagerSystemNodeResetHumidity` |
| `SetpointManager:SystemNodeReset:Temperature` | `OS:SetpointManager:SystemNodeReset:Temperature` | Generated by translator (has direct OS IDD peer) | `translateSetpointManagerSystemNodeResetTemperature` |
| `SetpointManager:Warmest` | `OS:SetpointManager:Warmest` | Generated by translator (has direct OS IDD peer) | `` |
| `SetpointManager:WarmestTemperatureFlow` | `OS:SetpointManager:WarmestTemperatureFlow` | Generated by translator (has direct OS IDD peer) | `` |
| `Shading:Building` |  | EP-only (no OS forward source found) | `` |
| `Shading:Building:Detailed` |  | EP-only (no OS forward source found) | `translateShadingBuildingDetailed` |
| `Shading:Fin` |  | EP-only (no OS forward source found) | `` |
| `Shading:Fin:Projection` |  | EP-only (no OS forward source found) | `` |
| `Shading:Overhang` |  | EP-only (no OS forward source found) | `` |
| `Shading:Overhang:Projection` |  | EP-only (no OS forward source found) | `` |
| `Shading:Site` |  | EP-only (no OS forward source found) | `` |
| `Shading:Site:Detailed` |  | EP-only (no OS forward source found) | `translateShadingSiteDetailed` |
| `Shading:Zone:Detailed` |  | EP-only (no OS forward source found) | `translateShadingZoneDetailed` |
| `ShadingProperty:Reflectance` |  | EP-only (no OS forward source found) | `` |
| `ShadowCalculation` | `OS:ShadowCalculation` | Generated by translator (has direct OS IDD peer) | `translateShadowCalculation` |
| `SimulationControl` | `OS:SimulationControl` | Generated by translator (has direct OS IDD peer) | `translateSimulationControl` |
| `Site:GroundDomain:Basement` |  | EP-only (no OS forward source found) | `` |
| `Site:GroundDomain:Slab` |  | EP-only (no OS forward source found) | `` |
| `Site:GroundReflectance` | `OS:Site:GroundReflectance` | Generated by translator (has direct OS IDD peer) | `translateSiteGroundReflectance` |
| `Site:GroundReflectance:SnowModifier` |  | EP-only (no OS forward source found) | `` |
| `Site:GroundTemperature:BuildingSurface` | `OS:Site:GroundTemperature:BuildingSurface` | Generated by translator (has direct OS IDD peer) | `translateSiteGroundTemperatureBuildingSurface` |
| `Site:GroundTemperature:Deep` | `OS:Site:GroundTemperature:Deep` | Generated by translator (has direct OS IDD peer) | `` |
| `Site:GroundTemperature:FCfactorMethod` | `OS:Site:GroundTemperature:FCfactorMethod` | Generated by translator (has direct OS IDD peer) | `` |
| `Site:GroundTemperature:Shallow` | `OS:Site:GroundTemperature:Shallow` | Generated by translator (has direct OS IDD peer) | `` |
| `Site:GroundTemperature:Undisturbed:FiniteDifference` |  | EP-only (no OS forward source found) | `` |
| `Site:GroundTemperature:Undisturbed:KusudaAchenbach` | `OS:Site:GroundTemperature:Undisturbed:KusudaAchenbach` | Generated by translator (has direct OS IDD peer) | `` |
| `Site:GroundTemperature:Undisturbed:Xing` | `OS:Site:GroundTemperature:Undisturbed:Xing` | Generated by translator (has direct OS IDD peer) | `` |
| `Site:HeightVariation` |  | EP-only (no OS forward source found) | `` |
| `Site:Location` | `OS:Site` | Generated by translator (no direct OS IDD peer) | `translateSiteLocation` |
| `Site:Precipitation` |  | EP-only (no OS forward source found) | `` |
| `Site:SolarAndVisibleSpectrum` |  | EP-only (no OS forward source found) | `` |
| `Site:SpectrumData` |  | EP-only (no OS forward source found) | `` |
| `Site:VariableLocation` |  | EP-only (no OS forward source found) | `` |
| `Site:WaterMainsTemperature` | `OS:Site:WaterMainsTemperature` | Generated by translator (has direct OS IDD peer) | `translateSiteWaterMainsTemperature` |
| `Site:WeatherStation` |  | EP-only (no OS forward source found) | `` |
| `Sizing:Parameters` | `OS:Sizing:Parameters` | Generated by translator (has direct OS IDD peer) | `translateSizingParameters` |
| `Sizing:Plant` | `OS:Sizing:Plant` | Generated by translator (has direct OS IDD peer) | `` |
| `Sizing:System` | `OS:Sizing:System` | Generated by translator (has direct OS IDD peer) | `translateSizingSystem` |
| `Sizing:Zone` | `OS:Sizing:Zone` | Generated by translator (has direct OS IDD peer) | `translateSizingZone` |
| `SizingPeriod:DesignDay` | `OS:SizingPeriod:DesignDay` | Generated by translator (has direct OS IDD peer) | `translateSizingPeriodDesignDay` |
| `SizingPeriod:WeatherFileConditionType` |  | EP-only (no OS forward source found) | `` |
| `SizingPeriod:WeatherFileDays` |  | EP-only (no OS forward source found) | `` |
| `SolarCollector:FlatPlate:PhotovoltaicThermal` | `OS:SolarCollector:FlatPlate:PhotovoltaicThermal` | Generated by translator (has direct OS IDD peer) | `` |
| `SolarCollector:FlatPlate:Water` | `OS:SolarCollector:FlatPlate:Water` | Generated by translator (has direct OS IDD peer) | `` |
| `SolarCollector:IntegralCollectorStorage` | `OS:SolarCollector:IntegralCollectorStorage` | Generated by translator (has direct OS IDD peer) | `` |
| `SolarCollector:UnglazedTranspired` |  | EP-only (no OS forward source found) | `` |
| `SolarCollector:UnglazedTranspired:Multisystem` |  | EP-only (no OS forward source found) | `` |
| `SolarCollectorPerformance:FlatPlate` | `OS:SolarCollectorPerformance:FlatPlate` | Generated by translator (has direct OS IDD peer) | `` |
| `SolarCollectorPerformance:IntegralCollectorStorage` | `OS:SolarCollectorPerformance:IntegralCollectorStorage` | Generated by translator (has direct OS IDD peer) | `` |
| `SolarCollectorPerformance:PhotovoltaicThermal:BIPVT` | `OS:SolarCollectorPerformance:PhotovoltaicThermal:BIPVT` | Generated by translator (has direct OS IDD peer) | `translateSolarCollectorPerformancePhotovoltaicThermalBIPVT` |
| `SolarCollectorPerformance:PhotovoltaicThermal:Simple` | `OS:SolarCollectorPerformance:PhotovoltaicThermal:Simple` | Generated by translator (has direct OS IDD peer) | `` |
| `Space` | `OS:Space` | Generated by translator (has direct OS IDD peer) | `` |
| `SpaceHVAC:EquipmentConnections` |  | EP-only (no OS forward source found) | `` |
| `SpaceHVAC:ZoneEquipmentMixer` |  | EP-only (no OS forward source found) | `` |
| `SpaceHVAC:ZoneEquipmentSplitter` |  | EP-only (no OS forward source found) | `` |
| `SpaceHVAC:ZoneReturnMixer` |  | EP-only (no OS forward source found) | `` |
| `SpaceList` | `OS:SpaceType` | Generated by translator (no direct OS IDD peer) | `` |
| `SteamEquipment` | `OS:SteamEquipment` | Generated by translator (has direct OS IDD peer) | `translateSteamEquipment` |
| `SurfaceContaminantSourceAndSink:Generic:BoundaryLayerDiffusion` |  | EP-only (no OS forward source found) | `` |
| `SurfaceContaminantSourceAndSink:Generic:DepositionVelocitySink` |  | EP-only (no OS forward source found) | `` |
| `SurfaceContaminantSourceAndSink:Generic:PressureDriven` |  | EP-only (no OS forward source found) | `` |
| `SurfaceControl:MovableInsulation` | `OS:SurfaceControl:MovableInsulation` | Generated by translator (has direct OS IDD peer) | `translateSurfaceControlMovableInsulation` |
| `SurfaceConvectionAlgorithm:Inside` | `OS:SurfaceConvectionAlgorithm:Inside` | Generated by translator (has direct OS IDD peer) | `translateSurfaceConvectionAlgorithmInside` |
| `SurfaceConvectionAlgorithm:Inside:AdaptiveModelSelections` |  | EP-only (no OS forward source found) | `` |
| `SurfaceConvectionAlgorithm:Inside:UserCurve` |  | EP-only (no OS forward source found) | `` |
| `SurfaceConvectionAlgorithm:Outside` | `OS:SurfaceConvectionAlgorithm:Outside` | Generated by translator (has direct OS IDD peer) | `translateSurfaceConvectionAlgorithmOutside` |
| `SurfaceConvectionAlgorithm:Outside:AdaptiveModelSelections` |  | EP-only (no OS forward source found) | `` |
| `SurfaceConvectionAlgorithm:Outside:UserCurve` |  | EP-only (no OS forward source found) | `` |
| `SurfaceProperties:VaporCoefficients` |  | EP-only (no OS forward source found) | `` |
| `SurfaceProperty:ConvectionCoefficients` | `OS:SurfaceProperty:ConvectionCoefficients` | Generated by translator (has direct OS IDD peer) | `` |
| `SurfaceProperty:ConvectionCoefficients:MultipleSurface` | `OS:SurfaceProperty:ConvectionCoefficients:MultipleSurface` | Generated by translator (has direct OS IDD peer) | `` |
| `SurfaceProperty:ExposedFoundationPerimeter` | `OS:SurfaceProperty:ExposedFoundationPerimeter` | Generated by translator (has direct OS IDD peer) | `translateSurfacePropertyExposedFoundationPerimeter` |
| `SurfaceProperty:ExteriorNaturalVentedCavity` |  | EP-only (no OS forward source found) | `` |
| `SurfaceProperty:GroundSurfaces` | `OS:SurfaceProperty:GroundSurfaces` | Generated by translator (has direct OS IDD peer) | `translateSurfacePropertyGroundSurfaces` |
| `SurfaceProperty:HeatBalanceSourceTerm` |  | EP-only (no OS forward source found) | `` |
| `SurfaceProperty:HeatTransferAlgorithm` |  | EP-only (no OS forward source found) | `` |
| `SurfaceProperty:HeatTransferAlgorithm:Construction` |  | EP-only (no OS forward source found) | `` |
| `SurfaceProperty:HeatTransferAlgorithm:MultipleSurface` |  | EP-only (no OS forward source found) | `` |
| `SurfaceProperty:HeatTransferAlgorithm:SurfaceList` |  | EP-only (no OS forward source found) | `` |
| `SurfaceProperty:IncidentSolarMultiplier` | `OS:SurfaceProperty:IncidentSolarMultiplier` | Generated by translator (has direct OS IDD peer) | `translateSurfacePropertyIncidentSolarMultiplier` |
| `SurfaceProperty:LocalEnvironment` | `OS:SurfaceProperty:LocalEnvironment` | Generated by translator (has direct OS IDD peer) | `translateSurfacePropertyLocalEnvironment` |
| `SurfaceProperty:OtherSideCoefficients` | `OS:SurfaceProperty:OtherSideCoefficients` | Generated by translator (has direct OS IDD peer) | `` |
| `SurfaceProperty:OtherSideConditionsModel` | `OS:SurfaceProperty:OtherSideConditionsModel` | Generated by translator (has direct OS IDD peer) | `translateSurfacePropertyOtherSideConditionsModel` |
| `SurfaceProperty:SolarIncidentInside` |  | EP-only (no OS forward source found) | `` |
| `SurfaceProperty:SurroundingSurfaces` | `OS:SurfaceProperty:SurroundingSurfaces` | Generated by translator (has direct OS IDD peer) | `translateSurfacePropertySurroundingSurfaces` |
| `SurfaceProperty:Underwater` |  | EP-only (no OS forward source found) | `` |
| `SwimmingPool:Indoor` | `OS:SwimmingPool:Indoor` | Generated by translator (has direct OS IDD peer) | `translateSwimmingPoolIndoor` |
| `Table:IndependentVariable` | `OS:Table:IndependentVariable`, `OS:Table:MultiVariableLookup` | Generated by translator (has direct OS IDD peer) | `` |
| `Table:IndependentVariableList` | `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` | Generated by translator (no direct OS IDD peer) | `` |
| `Table:Lookup` | `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` | Generated by translator (has direct OS IDD peer) | `translateTableLookup` |
| `TemperingValve` | `OS:TemperingValve` | Generated by translator (has direct OS IDD peer) | `` |
| `ThermalStorage:ChilledWater:Mixed` |  | EP-only (no OS forward source found) | `` |
| `ThermalStorage:ChilledWater:Stratified` | `OS:ThermalStorage:ChilledWater:Stratified` | Generated by translator (has direct OS IDD peer) | `` |
| `ThermalStorage:HotWater:Stratified` |  | EP-only (no OS forward source found) | `` |
| `ThermalStorage:Ice:Detailed` | `OS:ThermalStorage:Ice:Detailed` | Generated by translator (has direct OS IDD peer) | `` |
| `ThermalStorage:Ice:Simple` |  | EP-only (no OS forward source found) | `` |
| `ThermalStorage:PCM` |  | EP-only (no OS forward source found) | `` |
| `ThermalStorage:Sizing` |  | EP-only (no OS forward source found) | `` |
| `ThermostatSetpoint:DualSetpoint` | `OS:ThermostatSetpoint:DualSetpoint`, `OS:ZoneControl:Thermostat:StagedDualSetpoint` | Generated by translator (has direct OS IDD peer) | `translateThermostatSetpointDualSetpoint` |
| `ThermostatSetpoint:SingleCooling` | `OS:ThermostatSetpoint:DualSetpoint` | Generated by translator (no direct OS IDD peer) | `` |
| `ThermostatSetpoint:SingleHeating` | `OS:ThermostatSetpoint:DualSetpoint` | Generated by translator (no direct OS IDD peer) | `` |
| `ThermostatSetpoint:SingleHeatingOrCooling` |  | EP-only (no OS forward source found) | `` |
| `ThermostatSetpoint:ThermalComfort:Fanger:DualSetpoint` |  | EP-only (no OS forward source found) | `` |
| `ThermostatSetpoint:ThermalComfort:Fanger:SingleCooling` |  | EP-only (no OS forward source found) | `` |
| `ThermostatSetpoint:ThermalComfort:Fanger:SingleHeating` |  | EP-only (no OS forward source found) | `` |
| `ThermostatSetpoint:ThermalComfort:Fanger:SingleHeatingOrCooling` |  | EP-only (no OS forward source found) | `` |
| `Timestep` | `OS:Timestep` | Generated by translator (has direct OS IDD peer) | `translateTimestep` |
| `UnitarySystemPerformance:Multispeed` | `OS:AirLoopHVAC:UnitarySystem`, `OS:UnitarySystemPerformance:Multispeed` | Generated by translator (has direct OS IDD peer) | `` |
| `UtilityCost:Charge:Block` |  | EP-only (no OS forward source found) | `` |
| `UtilityCost:Charge:Simple` |  | EP-only (no OS forward source found) | `` |
| `UtilityCost:Computation` |  | EP-only (no OS forward source found) | `` |
| `UtilityCost:Qualify` |  | EP-only (no OS forward source found) | `` |
| `UtilityCost:Ratchet` |  | EP-only (no OS forward source found) | `` |
| `UtilityCost:Tariff` |  | EP-only (no OS forward source found) | `` |
| `UtilityCost:Variable` |  | EP-only (no OS forward source found) | `` |
| `Version` | `OS:Version` | Generated by translator (has direct OS IDD peer) | `translateVersion` |
| `Wall:Adiabatic` |  | EP-only (no OS forward source found) | `` |
| `Wall:Detailed` |  | EP-only (no OS forward source found) | `` |
| `Wall:Exterior` |  | EP-only (no OS forward source found) | `` |
| `Wall:Interzone` |  | EP-only (no OS forward source found) | `` |
| `Wall:Underground` |  | EP-only (no OS forward source found) | `` |
| `WaterHeater:HeatPump:PumpedCondenser` | `OS:WaterHeater:HeatPump` | Generated by translator (no direct OS IDD peer) | `` |
| `WaterHeater:HeatPump:WrappedCondenser` | `OS:WaterHeater:HeatPump:WrappedCondenser` | Generated by translator (has direct OS IDD peer) | `` |
| `WaterHeater:Mixed` | `OS:WaterHeater:Mixed` | Generated by translator (has direct OS IDD peer) | `` |
| `WaterHeater:Sizing` | `OS:WaterHeater:Sizing` | Generated by translator (has direct OS IDD peer) | `` |
| `WaterHeater:Stratified` | `OS:WaterHeater:Stratified` | Generated by translator (has direct OS IDD peer) | `` |
| `WaterUse:Connections` | `OS:WaterUse:Connections` | Generated by translator (has direct OS IDD peer) | `` |
| `WaterUse:Equipment` | `OS:WaterUse:Equipment` | Generated by translator (has direct OS IDD peer) | `` |
| `WaterUse:RainCollector` |  | EP-only (no OS forward source found) | `` |
| `WaterUse:Storage` |  | EP-only (no OS forward source found) | `` |
| `WaterUse:Well` |  | EP-only (no OS forward source found) | `` |
| `WeatherProperty:SkyTemperature` | `OS:WeatherProperty:SkyTemperature` | Generated by translator (has direct OS IDD peer) | `` |
| `Window` |  | EP-only (no OS forward source found) | `` |
| `Window:Interzone` |  | EP-only (no OS forward source found) | `` |
| `WindowGap:DeflectionState` |  | EP-only (no OS forward source found) | `` |
| `WindowGap:SupportPillar` |  | EP-only (no OS forward source found) | `` |
| `WindowMaterial:Blind` | `OS:WindowMaterial:Blind` | Generated by translator (has direct OS IDD peer) | `` |
| `WindowMaterial:Blind:EquivalentLayer` |  | EP-only (no OS forward source found) | `` |
| `WindowMaterial:ComplexShade` |  | EP-only (no OS forward source found) | `` |
| `WindowMaterial:Drape:EquivalentLayer` |  | EP-only (no OS forward source found) | `` |
| `WindowMaterial:Gap` |  | EP-only (no OS forward source found) | `` |
| `WindowMaterial:Gap:EquivalentLayer` |  | EP-only (no OS forward source found) | `` |
| `WindowMaterial:Gas` | `OS:WindowMaterial:Gas` | Generated by translator (has direct OS IDD peer) | `translateWindowMaterialGas` |
| `WindowMaterial:GasMixture` | `OS:WindowMaterial:GasMixture` | Generated by translator (has direct OS IDD peer) | `` |
| `WindowMaterial:Glazing` | `OS:WindowMaterial:Glazing` | Generated by translator (has direct OS IDD peer) | `translateWindowMaterialGlazing` |
| `WindowMaterial:Glazing:EquivalentLayer` |  | EP-only (no OS forward source found) | `` |
| `WindowMaterial:Glazing:RefractionExtinctionMethod` | `OS:WindowMaterial:Glazing:RefractionExtinctionMethod` | Generated by translator (has direct OS IDD peer) | `` |
| `WindowMaterial:GlazingGroup:Thermochromic` | `OS:WindowMaterial:GlazingGroup:Thermochromic` | Generated by translator (has direct OS IDD peer) | `translateWindowMaterialGlazingGroupThermochromic` |
| `WindowMaterial:Screen` | `OS:WindowMaterial:Screen` | Generated by translator (has direct OS IDD peer) | `` |
| `WindowMaterial:Screen:EquivalentLayer` |  | EP-only (no OS forward source found) | `` |
| `WindowMaterial:Shade` | `OS:WindowMaterial:Shade` | Generated by translator (has direct OS IDD peer) | `` |
| `WindowMaterial:Shade:EquivalentLayer` |  | EP-only (no OS forward source found) | `` |
| `WindowMaterial:SimpleGlazingSystem` | `OS:WindowMaterial:SimpleGlazingSystem` | Generated by translator (has direct OS IDD peer) | `translateWindowMaterialSimpleGlazingSystem` |
| `WindowProperty:AirflowControl` |  | EP-only (no OS forward source found) | `` |
| `WindowProperty:FrameAndDivider` | `OS:WindowProperty:FrameAndDivider` | Generated by translator (has direct OS IDD peer) | `translateWindowPropertyFrameAndDivider` |
| `WindowProperty:StormWindow` |  | EP-only (no OS forward source found) | `` |
| `WindowShadingControl` | `OS:ShadingControl` | Generated by translator (no direct OS IDD peer) | `translateWindowShadingControl` |
| `WindowThermalModel:Params` |  | EP-only (no OS forward source found) | `` |
| `WindowsCalculationEngine` |  | EP-only (no OS forward source found) | `` |
| `Zone` | `OS:ThermalZone` | Generated by translator (no direct OS IDD peer) | `translateZone` |
| `ZoneAirBalance:OutdoorAir` |  | EP-only (no OS forward source found) | `` |
| `ZoneAirContaminantBalance` | `OS:ZoneAirContaminantBalance` | Generated by translator (has direct OS IDD peer) | `` |
| `ZoneAirHeatBalanceAlgorithm` | `OS:ZoneAirHeatBalanceAlgorithm` | Generated by translator (has direct OS IDD peer) | `translateZoneAirHeatBalanceAlgorithm` |
| `ZoneAirMassFlowConservation` | `OS:ZoneAirMassFlowConservation` | Generated by translator (has direct OS IDD peer) | `translateZoneAirMassFlowConservation` |
| `ZoneBaseboard:OutdoorTemperatureControlled` |  | EP-only (no OS forward source found) | `` |
| `ZoneCapacitanceMultiplier:ResearchSpecial` | `OS:ZoneCapacitanceMultiplier:ResearchSpecial` | Generated by translator (has direct OS IDD peer) | `` |
| `ZoneContaminantSourceAndSink:CarbonDioxide` |  | EP-only (no OS forward source found) | `` |
| `ZoneContaminantSourceAndSink:Generic:Constant` |  | EP-only (no OS forward source found) | `` |
| `ZoneContaminantSourceAndSink:Generic:CutoffModel` |  | EP-only (no OS forward source found) | `` |
| `ZoneContaminantSourceAndSink:Generic:DecaySource` |  | EP-only (no OS forward source found) | `` |
| `ZoneContaminantSourceAndSink:Generic:DepositionRateSink` |  | EP-only (no OS forward source found) | `` |
| `ZoneControl:ContaminantController` | `OS:ZoneControl:ContaminantController` | Generated by translator (has direct OS IDD peer) | `` |
| `ZoneControl:Humidistat` | `OS:ZoneControl:Humidistat` | Generated by translator (has direct OS IDD peer) | `` |
| `ZoneControl:Thermostat` | `OS:ThermalZone`, `OS:ZoneControl:Thermostat:StagedDualSetpoint` | Generated by translator (no direct OS IDD peer) | `` |
| `ZoneControl:Thermostat:OperativeTemperature` |  | EP-only (no OS forward source found) | `` |
| `ZoneControl:Thermostat:StagedDualSetpoint` | `OS:ZoneControl:Thermostat:StagedDualSetpoint` | Generated by translator (has direct OS IDD peer) | `` |
| `ZoneControl:Thermostat:TemperatureAndHumidity` |  | EP-only (no OS forward source found) | `` |
| `ZoneControl:Thermostat:ThermalComfort` |  | EP-only (no OS forward source found) | `` |
| `ZoneCoolTower:Shower` |  | EP-only (no OS forward source found) | `` |
| `ZoneCrossMixing` |  | EP-only (no OS forward source found) | `translateZoneCrossMixing` |
| `ZoneEarthtube` |  | EP-only (no OS forward source found) | `` |
| `ZoneEarthtube:Parameters` |  | EP-only (no OS forward source found) | `` |
| `ZoneGroup` |  | EP-only (no OS forward source found) | `` |
| `ZoneHVAC:AirDistributionUnit` | `OS:AirTerminal:DualDuct:ConstantVolume`, `OS:AirTerminal:DualDuct:VAV`, `OS:AirTerminal:DualDuct:VAV:OutdoorAir`, `OS:AirTerminal:SingleDuct:ConstantVolume:CooledBeam`, `OS:AirTerminal:SingleDuct:ConstantVolume:FourPipeBeam`, `OS:AirTerminal:SingleDuct:ConstantVolume:FourPipeInduction`, `OS:AirTerminal:SingleDuct:ConstantVolume:NoReheat`, `OS:AirTerminal:SingleDuct:ConstantVolume:Reheat`, `OS:AirTerminal:SingleDuct:InletSideMixer`, `OS:AirTerminal:SingleDuct:ParallelPIU:Reheat`, `OS:AirTerminal:SingleDuct:SeriesPIU:Reheat`, `OS:AirTerminal:SingleDuct:VAV:HeatAndCool:NoReheat`, `OS:AirTerminal:SingleDuct:VAV:HeatAndCool:Reheat`, `OS:AirTerminal:SingleDuct:VAV:NoReheat`, `OS:AirTerminal:SingleDuct:VAV:Reheat` | Generated by translator (no direct OS IDD peer) | `` |
| `ZoneHVAC:Baseboard:Convective:Electric` | `OS:ZoneHVAC:Baseboard:Convective:Electric` | Generated by translator (has direct OS IDD peer) | `` |
| `ZoneHVAC:Baseboard:Convective:Water` | `OS:ZoneHVAC:Baseboard:Convective:Water` | Generated by translator (has direct OS IDD peer) | `` |
| `ZoneHVAC:Baseboard:RadiantConvective:Electric` | `OS:ZoneHVAC:Baseboard:RadiantConvective:Electric` | Generated by translator (has direct OS IDD peer) | `` |
| `ZoneHVAC:Baseboard:RadiantConvective:Steam` |  | EP-only (no OS forward source found) | `` |
| `ZoneHVAC:Baseboard:RadiantConvective:Steam:Design` |  | EP-only (no OS forward source found) | `` |
| `ZoneHVAC:Baseboard:RadiantConvective:Water` | `OS:ZoneHVAC:Baseboard:RadiantConvective:Water` | Generated by translator (has direct OS IDD peer) | `` |
| `ZoneHVAC:Baseboard:RadiantConvective:Water:Design` | `OS:ZoneHVAC:Baseboard:RadiantConvective:Water` | Generated by translator (no direct OS IDD peer) | `` |
| `ZoneHVAC:CoolingPanel:RadiantConvective:Water` | `OS:ZoneHVAC:CoolingPanel:RadiantConvective:Water` | Generated by translator (has direct OS IDD peer) | `` |
| `ZoneHVAC:Dehumidifier:DX` | `OS:ZoneHVAC:Dehumidifier:DX` | Generated by translator (has direct OS IDD peer) | `` |
| `ZoneHVAC:EnergyRecoveryVentilator` | `OS:ZoneHVAC:EnergyRecoveryVentilator` | Generated by translator (has direct OS IDD peer) | `` |
| `ZoneHVAC:EnergyRecoveryVentilator:Controller` | `OS:ZoneHVAC:EnergyRecoveryVentilator:Controller` | Generated by translator (has direct OS IDD peer) | `` |
| `ZoneHVAC:EquipmentConnections` | `OS:ThermalZone` | Generated by translator (no direct OS IDD peer) | `` |
| `ZoneHVAC:EquipmentList` | `OS:ZoneHVAC:EquipmentList` | Generated by translator (has direct OS IDD peer) | `translateZoneHVACEquipmentList` |
| `ZoneHVAC:EvaporativeCoolerUnit` | `OS:ZoneHVAC:EvaporativeCoolerUnit` | Generated by translator (has direct OS IDD peer) | `` |
| `ZoneHVAC:ExhaustControl` |  | EP-only (no OS forward source found) | `` |
| `ZoneHVAC:ForcedAir:UserDefined` |  | EP-only (no OS forward source found) | `` |
| `ZoneHVAC:FourPipeFanCoil` | `OS:ZoneHVAC:FourPipeFanCoil` | Generated by translator (has direct OS IDD peer) | `` |
| `ZoneHVAC:HighTemperatureRadiant` | `OS:ZoneHVAC:HighTemperatureRadiant` | Generated by translator (has direct OS IDD peer) | `` |
| `ZoneHVAC:HybridUnitaryHVAC` |  | EP-only (no OS forward source found) | `` |
| `ZoneHVAC:IdealLoadsAirSystem` | `OS:ZoneHVAC:IdealLoadsAirSystem` | Generated by translator (has direct OS IDD peer) | `translateZoneHVACIdealLoadsAirSystem` |
| `ZoneHVAC:LowTemperatureRadiant:ConstantFlow` | `OS:ZoneHVAC:LowTemperatureRadiant:ConstantFlow` | Generated by translator (has direct OS IDD peer) | `` |
| `ZoneHVAC:LowTemperatureRadiant:ConstantFlow:Design` | `OS:ZoneHVAC:LowTemperatureRadiant:ConstantFlow` | Generated by translator (no direct OS IDD peer) | `` |
| `ZoneHVAC:LowTemperatureRadiant:Electric` | `OS:ZoneHVAC:LowTemperatureRadiant:Electric` | Generated by translator (has direct OS IDD peer) | `` |
| `ZoneHVAC:LowTemperatureRadiant:SurfaceGroup` | `OS:ZoneHVAC:LowTemperatureRadiant:ConstantFlow`, `OS:ZoneHVAC:LowTemperatureRadiant:Electric`, `OS:ZoneHVAC:LowTemperatureRadiant:VariableFlow` | Generated by translator (no direct OS IDD peer) | `` |
| `ZoneHVAC:LowTemperatureRadiant:VariableFlow` | `OS:ZoneHVAC:LowTemperatureRadiant:VariableFlow` | Generated by translator (has direct OS IDD peer) | `` |
| `ZoneHVAC:LowTemperatureRadiant:VariableFlow:Design` | `OS:ZoneHVAC:LowTemperatureRadiant:VariableFlow` | Generated by translator (no direct OS IDD peer) | `` |
| `ZoneHVAC:OutdoorAirUnit` |  | EP-only (no OS forward source found) | `` |
| `ZoneHVAC:OutdoorAirUnit:EquipmentList` |  | EP-only (no OS forward source found) | `` |
| `ZoneHVAC:PackagedTerminalAirConditioner` | `OS:ZoneHVAC:PackagedTerminalAirConditioner` | Generated by translator (has direct OS IDD peer) | `` |
| `ZoneHVAC:PackagedTerminalHeatPump` | `OS:ZoneHVAC:PackagedTerminalHeatPump` | Generated by translator (has direct OS IDD peer) | `` |
| `ZoneHVAC:RefrigerationChillerSet` | `OS:ZoneHVAC:EquipmentList` | Generated by translator (no direct OS IDD peer) | `` |
| `ZoneHVAC:TerminalUnit:VariableRefrigerantFlow` | `OS:ZoneHVAC:TerminalUnit:VariableRefrigerantFlow` | Generated by translator (has direct OS IDD peer) | `` |
| `ZoneHVAC:UnitHeater` | `OS:ZoneHVAC:UnitHeater` | Generated by translator (has direct OS IDD peer) | `` |
| `ZoneHVAC:UnitVentilator` | `OS:ZoneHVAC:UnitVentilator` | Generated by translator (has direct OS IDD peer) | `` |
| `ZoneHVAC:VentilatedSlab` |  | EP-only (no OS forward source found) | `` |
| `ZoneHVAC:VentilatedSlab:SlabGroup` |  | EP-only (no OS forward source found) | `` |
| `ZoneHVAC:WaterToAirHeatPump` | `OS:ZoneHVAC:WaterToAirHeatPump` | Generated by translator (has direct OS IDD peer) | `` |
| `ZoneHVAC:WindowAirConditioner` |  | EP-only (no OS forward source found) | `` |
| `ZoneInfiltration:DesignFlowRate` | `OS:SpaceInfiltration:DesignFlowRate` | Generated by translator (no direct OS IDD peer) | `translateZoneInfiltrationDesignFlowRate` |
| `ZoneInfiltration:EffectiveLeakageArea` | `OS:SpaceInfiltration:EffectiveLeakageArea` | Generated by translator (no direct OS IDD peer) | `translateZoneInfiltrationEffectiveLeakageArea` |
| `ZoneInfiltration:FlowCoefficient` | `OS:SpaceInfiltration:FlowCoefficient` | Generated by translator (no direct OS IDD peer) | `translateZoneInfiltrationFlowCoefficient` |
| `ZoneList` | `OS:AvailabilityManager:NightCycle`, `OS:AvailabilityManager:OptimumStart`, `OS:ShadowCalculation`, `OS:SpaceType` | Generated by translator (no direct OS IDD peer) | `translateZoneList` |
| `ZoneMixing` | `OS:ZoneMixing` | Generated by translator (has direct OS IDD peer) | `translateZoneMixing` |
| `ZoneProperty:LocalEnvironment` |  | EP-only (no OS forward source found) | `` |
| `ZoneProperty:UserViewFactors:BySurfaceName` | `OS:ZoneProperty:UserViewFactors:BySurfaceName` | Generated by translator (has direct OS IDD peer) | `translateZonePropertyUserViewFactorsBySurfaceName` |
| `ZoneRefrigerationDoorMixing` |  | EP-only (no OS forward source found) | `` |
| `ZoneTerminalUnitList` | `OS:AirConditioner:VariableRefrigerantFlow`, `OS:AirConditioner:VariableRefrigerantFlow:FluidTemperatureControl`, `OS:AirConditioner:VariableRefrigerantFlow:FluidTemperatureControl:HR` | Generated by translator (no direct OS IDD peer) | `` |
| `ZoneThermalChimney` |  | EP-only (no OS forward source found) | `` |
| `ZoneVentilation:DesignFlowRate` | `OS:ThermalZone`, `OS:ZoneVentilation:DesignFlowRate` | Generated by translator (has direct OS IDD peer) | `translateZoneVentilationDesignFlowRate` |
| `ZoneVentilation:WindandStackOpenArea` | `OS:ZoneVentilation:WindandStackOpenArea` | Generated by translator (has direct OS IDD peer) | `translateZoneVentilationWindandStackOpenArea` |
