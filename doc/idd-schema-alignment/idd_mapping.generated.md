# IDD Mapping (Generated)

This file is machine-generated from IDDs and translator source.

## Method

1. Parse object names from both IDDs.
2. Parse `src/model` `iddObjectType()` definitions to link `OS_*` -> canonical model class.
3. Parse `ForwardTranslator.cpp` switch to link `OS_*` -> direct `translateX` function.
4. Parse ForwardTranslator function bodies and source files for created EP `IddObjectType` IDF objects.
5. Include indirect model-level translator functions (not switch-dispatched) by matching model parameter class.

## OS -> EP (Full)

| OS IddObjectType | Model class | Direct OS base class | EP IddObjectType(s) produced | FT source file(s) |
| --- | --- | --- | --- | --- |
| `OS:AdditionalProperties` | `AdditionalProperties` | `ModelObject` |  |  |
| `OS:AirConditioner:VariableRefrigerantFlow` | `AirConditionerVariableRefrigerantFlow` | `StraightComponent` | `AirConditioner:VariableRefrigerantFlow`, `ZoneTerminalUnitList` | `src/energyplus/ForwardTranslator/ForwardTranslateAirConditionerVariableRefrigerantFlow.cpp` |
| `OS:AirConditioner:VariableRefrigerantFlow:FluidTemperatureControl` | `AirConditionerVariableRefrigerantFlowFluidTemperatureControl` | `HVACComponent` | `AirConditioner:VariableRefrigerantFlow:FluidTemperatureControl`, `ZoneTerminalUnitList` | `src/energyplus/ForwardTranslator/ForwardTranslateAirConditionerVariableRefrigerantFlowFluidTemperatureControl.cpp` |
| `OS:AirConditioner:VariableRefrigerantFlow:FluidTemperatureControl:HR` | `AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR` | `HVACComponent` | `AirConditioner:VariableRefrigerantFlow:FluidTemperatureControl:HR`, `ZoneTerminalUnitList` | `src/energyplus/ForwardTranslator/ForwardTranslateAirConditionerVariableRefrigerantFlowFluidTemperatureControlHR.cpp` |
| `OS:AirConditioner:VariableRefrigerantFlow:FluidTemperatureControl:LoadingIndex` | `LoadingIndex` | `ParentObject` |  |  |
| `OS:AirLoopHVAC` | `AirLoopHVAC` | `Loop` | `AirLoopHVAC`, `AirLoopHVAC:ControllerList`, `AvailabilityManagerAssignmentList`, `AvailabilityManager:Scheduled`, `Branch`, `BranchList`, `ConnectorList`, `Connector:Splitter`, `NodeList` | `src/energyplus/ForwardTranslator/ForwardTranslateAirLoopHVAC.cpp` |
| `OS:AirLoopHVAC:DedicatedOutdoorAirSystem` | `AirLoopHVACDedicatedOutdoorAirSystem` | `ModelObject` | `AirLoopHVAC:DedicatedOutdoorAirSystem`, `AirLoopHVAC:Mixer`, `AirLoopHVAC:Splitter` | `src/energyplus/ForwardTranslator/ForwardTranslateAirLoopHVACDedicatedOutdoorAirSystem.cpp` |
| `OS:AirLoopHVAC:OutdoorAirSystem` | `AirLoopHVACOutdoorAirSystem` | `HVACComponent` | `AirLoopHVAC:ControllerList`, `AirLoopHVAC:OutdoorAirSystem`, `AirLoopHVAC:OutdoorAirSystem:EquipmentList`, `OutdoorAir:Mixer`, `OutdoorAir:NodeList` | `src/energyplus/ForwardTranslator/ForwardTranslateAirLoopHVACOutdoorAirSystem.cpp` |
| `OS:AirLoopHVAC:ReturnPlenum` | `AirLoopHVACReturnPlenum` | `Mixer` | `AirLoopHVAC:ReturnPlenum`, `NodeList` | `src/energyplus/ForwardTranslator/ForwardTranslateAirLoopHVACReturnPlenum.cpp` |
| `OS:AirLoopHVAC:SupplyPlenum` | `AirLoopHVACSupplyPlenum` | `Splitter` | `AirLoopHVAC:SupplyPlenum` | `src/energyplus/ForwardTranslator/ForwardTranslateAirLoopHVACSupplyPlenum.cpp` |
| `OS:AirLoopHVAC:UnitaryCoolOnly` | `` | `` |  |  |
| `OS:AirLoopHVAC:UnitaryHeatCool:VAVChangeoverBypass` | `AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass` | `StraightComponent` | `AirLoopHVAC:UnitaryHeatCool:VAVChangeoverBypass`, `OutdoorAir:Mixer`, `OutdoorAir:NodeList` | `src/energyplus/ForwardTranslator/ForwardTranslateAirLoopHVACUnitaryHeatCoolVAVChangeoverBypass.cpp` |
| `OS:AirLoopHVAC:UnitaryHeatPump:AirToAir` | `AirLoopHVACUnitaryHeatPumpAirToAir` | `StraightComponent` | `AirLoopHVAC:UnitaryHeatPump:AirToAir` | `src/energyplus/ForwardTranslator/ForwardTranslateAirLoopHVACUnitaryHeatPumpAirToAir.cpp` |
| `OS:AirLoopHVAC:UnitaryHeatPump:AirToAir:MultiSpeed` | `AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed` | `StraightComponent` | `AirLoopHVAC:UnitaryHeatPump:AirToAir:MultiSpeed` | `src/energyplus/ForwardTranslator/ForwardTranslateAirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed.cpp` |
| `OS:AirLoopHVAC:UnitarySystem` | `AirLoopHVACUnitarySystem` | `ZoneHVACComponent` | `AirLoopHVAC:UnitarySystem`, `UnitarySystemPerformance:Multispeed` | `src/energyplus/ForwardTranslator/ForwardTranslateAirLoopHVACUnitarySystem.cpp` |
| `OS:AirLoopHVAC:ZoneMixer` | `AirLoopHVACZoneMixer` | `Mixer` | `AirLoopHVAC:ZoneMixer` | `src/energyplus/ForwardTranslator/ForwardTranslateAirLoopHVACZoneMixer.cpp` |
| `OS:AirLoopHVAC:ZoneSplitter` | `AirLoopHVACZoneSplitter` | `Splitter` | `AirLoopHVAC:ZoneSplitter` | `src/energyplus/ForwardTranslator/ForwardTranslateAirLoopHVACZoneSplitter.cpp` |
| `OS:AirTerminal:DualDuct:ConstantVolume` | `AirTerminalDualDuctConstantVolume` | `Mixer` | `AirTerminal:DualDuct:ConstantVolume`, `ZoneHVAC:AirDistributionUnit` | `src/energyplus/ForwardTranslator/ForwardTranslateAirTerminalDualDuctConstantVolume.cpp` |
| `OS:AirTerminal:DualDuct:VAV` | `AirTerminalDualDuctVAV` | `Mixer` | `AirTerminal:DualDuct:VAV`, `ZoneHVAC:AirDistributionUnit` | `src/energyplus/ForwardTranslator/ForwardTranslateAirTerminalDualDuctVAV.cpp` |
| `OS:AirTerminal:DualDuct:VAV:OutdoorAir` | `AirTerminalDualDuctVAVOutdoorAir` | `Mixer` | `AirTerminal:DualDuct:VAV:OutdoorAir`, `ZoneHVAC:AirDistributionUnit` | `src/energyplus/ForwardTranslator/ForwardTranslateAirTerminalDualDuctVAVOutdoorAir.cpp` |
| `OS:AirTerminal:SingleDuct:ConstantVolume:CooledBeam` | `AirTerminalSingleDuctConstantVolumeCooledBeam` | `StraightComponent` | `AirTerminal:SingleDuct:ConstantVolume:CooledBeam`, `ZoneHVAC:AirDistributionUnit` | `src/energyplus/ForwardTranslator/ForwardTranslateAirTerminalSingleDuctConstantVolumeCooledBeam.cpp` |
| `OS:AirTerminal:SingleDuct:ConstantVolume:FourPipeBeam` | `AirTerminalSingleDuctConstantVolumeFourPipeBeam` | `StraightComponent` | `AirTerminal:SingleDuct:ConstantVolume:FourPipeBeam`, `ZoneHVAC:AirDistributionUnit` | `src/energyplus/ForwardTranslator/ForwardTranslateAirTerminalSingleDuctConstantVolumeFourPipeBeam.cpp` |
| `OS:AirTerminal:SingleDuct:ConstantVolume:FourPipeInduction` | `AirTerminalSingleDuctConstantVolumeFourPipeInduction` | `StraightComponent` | `AirLoopHVAC:ZoneMixer`, `AirTerminal:SingleDuct:ConstantVolume:FourPipeInduction`, `ZoneHVAC:AirDistributionUnit` | `src/energyplus/ForwardTranslator/ForwardTranslateAirTerminalSingleDuctConstantVolumeFourPipeInduction.cpp` |
| `OS:AirTerminal:SingleDuct:ConstantVolume:NoReheat` | `AirTerminalSingleDuctConstantVolumeNoReheat` | `StraightComponent` | `AirTerminal:SingleDuct:ConstantVolume:NoReheat`, `ZoneHVAC:AirDistributionUnit` | `src/energyplus/ForwardTranslator/ForwardTranslateAirTerminalSingleDuctConstantVolumeNoReheat.cpp` |
| `OS:AirTerminal:SingleDuct:ConstantVolume:Reheat` | `AirTerminalSingleDuctConstantVolumeReheat` | `StraightComponent` | `AirTerminal:SingleDuct:ConstantVolume:Reheat`, `ZoneHVAC:AirDistributionUnit` | `src/energyplus/ForwardTranslator/ForwardTranslateAirTerminalSingleDuctConstantVolumeReheat.cpp` |
| `OS:AirTerminal:SingleDuct:InletSideMixer` | `AirTerminalSingleDuctInletSideMixer` | `StraightComponent` | `AirTerminal:SingleDuct:Mixer`, `ZoneHVAC:AirDistributionUnit` | `src/energyplus/ForwardTranslator/ForwardTranslateAirTerminalSingleDuctInletSideMixer.cpp` |
| `OS:AirTerminal:SingleDuct:ParallelPIU:Reheat` | `AirTerminalSingleDuctParallelPIUReheat` | `StraightComponent` | `AirLoopHVAC:ZoneMixer`, `AirTerminal:SingleDuct:ParallelPIU:Reheat`, `ZoneHVAC:AirDistributionUnit` | `src/energyplus/ForwardTranslator/ForwardTranslateAirTerminalSingleDuctParallelPIUReheat.cpp` |
| `OS:AirTerminal:SingleDuct:SeriesPIU:Reheat` | `AirTerminalSingleDuctSeriesPIUReheat` | `StraightComponent` | `AirLoopHVAC:ZoneMixer`, `AirTerminal:SingleDuct:SeriesPIU:Reheat`, `ZoneHVAC:AirDistributionUnit` | `src/energyplus/ForwardTranslator/ForwardTranslateAirTerminalSingleDuctSeriesPIUReheat.cpp` |
| `OS:AirTerminal:SingleDuct:VAV:HeatAndCool:NoReheat` | `AirTerminalSingleDuctVAVHeatAndCoolNoReheat` | `StraightComponent` | `AirTerminal:SingleDuct:VAV:HeatAndCool:NoReheat`, `ZoneHVAC:AirDistributionUnit` | `src/energyplus/ForwardTranslator/ForwardTranslateAirTerminalSingleDuctVAVHeatAndCoolNoReheat.cpp` |
| `OS:AirTerminal:SingleDuct:VAV:HeatAndCool:Reheat` | `AirTerminalSingleDuctVAVHeatAndCoolReheat` | `StraightComponent` | `AirTerminal:SingleDuct:VAV:HeatAndCool:Reheat`, `ZoneHVAC:AirDistributionUnit` | `src/energyplus/ForwardTranslator/ForwardTranslateAirTerminalSingleDuctVAVHeatAndCoolReheat.cpp` |
| `OS:AirTerminal:SingleDuct:VAV:NoReheat` | `AirTerminalSingleDuctVAVNoReheat` | `StraightComponent` | `AirTerminal:SingleDuct:VAV:NoReheat`, `ZoneHVAC:AirDistributionUnit` | `src/energyplus/ForwardTranslator/ForwardTranslateAirTerminalSingleDuctVAVNoReheat.cpp` |
| `OS:AirTerminal:SingleDuct:VAV:Reheat` | `AirTerminalSingleDuctVAVReheat` | `StraightComponent` | `AirTerminal:SingleDuct:VAV:Reheat`, `ZoneHVAC:AirDistributionUnit` | `src/energyplus/ForwardTranslator/ForwardTranslateAirTerminalSingleDuctVAVReheat.cpp` |
| `OS:AirflowNetworkConstantPressureDrop` | `AirflowNetworkConstantPressureDrop` | `ModelObject` | `AirflowNetwork:Distribution:Component:ConstantPressureDrop` | `src/energyplus/ForwardTranslator/ForwardTranslateAirflowNetwork.cpp` |
| `OS:AirflowNetworkCrack` | `AirflowNetworkCrack` | `AirflowNetworkComponent` | `AirflowNetwork:MultiZone:Surface:Crack` | `src/energyplus/ForwardTranslator/ForwardTranslateAirflowNetwork.cpp` |
| `OS:AirflowNetworkDetailedOpening` | `AirflowNetworkDetailedOpening` | `AirflowNetworkComponent` | `AirflowNetwork:MultiZone:Component:DetailedOpening` | `src/energyplus/ForwardTranslator/ForwardTranslateAirflowNetwork.cpp` |
| `OS:AirflowNetworkDistributionLinkage` | `AirflowNetworkDistributionLinkage` | `AirflowNetworkLinkage` | `AirflowNetwork:Distribution:Linkage` | `src/energyplus/ForwardTranslator/ForwardTranslateAirflowNetwork.cpp` |
| `OS:AirflowNetworkDistributionNode` | `AirflowNetworkDistributionNode` | `AirflowNetworkNode` | `AirflowNetwork:Distribution:Node` | `src/energyplus/ForwardTranslator/ForwardTranslateAirflowNetwork.cpp` |
| `OS:AirflowNetworkDuct` | `AirflowNetworkDuct` | `AirflowNetworkComponent` | `AirflowNetwork:Distribution:Component:Duct` | `src/energyplus/ForwardTranslator/ForwardTranslateAirflowNetwork.cpp` |
| `OS:AirflowNetworkDuctViewFactors` | `AirflowNetworkDuctViewFactors` | `ModelObject` | `AirflowNetwork:Distribution:DuctViewFactors` | `src/energyplus/ForwardTranslator/ForwardTranslateAirflowNetwork.cpp` |
| `OS:AirflowNetworkEffectiveLeakageArea` | `AirflowNetworkEffectiveLeakageArea` | `AirflowNetworkComponent` | `AirflowNetwork:MultiZone:Surface:EffectiveLeakageArea` | `src/energyplus/ForwardTranslator/ForwardTranslateAirflowNetwork.cpp` |
| `OS:AirflowNetworkEquivalentDuct` | `AirflowNetworkEquivalentDuct` | `AirflowNetworkComponent` | `AirflowNetwork:Distribution:Component:Coil`, `AirflowNetwork:Distribution:Component:HeatExchanger`, `AirflowNetwork:Distribution:Component:TerminalUnit` | `src/energyplus/ForwardTranslator/ForwardTranslateAirflowNetwork.cpp` |
| `OS:AirflowNetworkExternalNode` | `AirflowNetworkExternalNode` | `AirflowNetworkNode` | `AirflowNetwork:MultiZone:ExternalNode` | `src/energyplus/ForwardTranslator/ForwardTranslateAirflowNetwork.cpp` |
| `OS:AirflowNetworkFan` | `AirflowNetworkFan` | `AirflowNetworkComponent` | `AirflowNetwork:Distribution:Component:Fan` | `src/energyplus/ForwardTranslator/ForwardTranslateAirflowNetwork.cpp` |
| `OS:AirflowNetworkHorizontalOpening` | `AirflowNetworkHorizontalOpening` | `AirflowNetworkComponent` | `AirflowNetwork:MultiZone:Component:HorizontalOpening` | `src/energyplus/ForwardTranslator/ForwardTranslateAirflowNetwork.cpp` |
| `OS:AirflowNetworkLeak` | `` | `` |  |  |
| `OS:AirflowNetworkLeakageRatio` | `AirflowNetworkLeakageRatio` | `AirflowNetworkComponent` | `AirflowNetwork:Distribution:Component:LeakageRatio` | `src/energyplus/ForwardTranslator/ForwardTranslateAirflowNetwork.cpp` |
| `OS:AirflowNetworkOccupantVentilationControl` | `AirflowNetworkOccupantVentilationControl` | `ModelObject` | `AirflowNetwork:OccupantVentilationControl` | `src/energyplus/ForwardTranslator/ForwardTranslateAirflowNetwork.cpp` |
| `OS:AirflowNetworkOutdoorAirflow` | `AirflowNetworkOutdoorAirflow` | `ModelObject` | `AirflowNetwork:Distribution:Component:OutdoorAirFlow` | `src/energyplus/ForwardTranslator/ForwardTranslateAirflowNetwork.cpp` |
| `OS:AirflowNetworkPressureController` | `` | `` |  |  |
| `OS:AirflowNetworkReferenceCrackConditions` | `AirflowNetworkReferenceCrackConditions` | `ModelObject` | `AirflowNetwork:MultiZone:ReferenceCrackConditions` | `src/energyplus/ForwardTranslator/ForwardTranslateAirflowNetwork.cpp` |
| `OS:AirflowNetworkReliefAirFlow` | `` | `` |  |  |
| `OS:AirflowNetworkSimpleOpening` | `AirflowNetworkSimpleOpening` | `AirflowNetworkComponent` | `AirflowNetwork:MultiZone:Component:SimpleOpening` | `src/energyplus/ForwardTranslator/ForwardTranslateAirflowNetwork.cpp` |
| `OS:AirflowNetworkSimulationControl` | `AirflowNetworkSimulationControl` | `ParentObject` | `AirflowNetwork:SimulationControl` | `src/energyplus/ForwardTranslator/ForwardTranslateAirflowNetwork.cpp` |
| `OS:AirflowNetworkSpecifiedFlowRate` | `AirflowNetworkSpecifiedFlowRate` | `AirflowNetworkComponent` | `AirflowNetwork:MultiZone:SpecifiedFlowRate` | `src/energyplus/ForwardTranslator/ForwardTranslateAirflowNetwork.cpp` |
| `OS:AirflowNetworkSurface` | `AirflowNetworkSurface` | `AirflowNetworkLinkage` | `AirflowNetwork:MultiZone:Surface` | `src/energyplus/ForwardTranslator/ForwardTranslateAirflowNetwork.cpp` |
| `OS:AirflowNetworkZone` | `AirflowNetworkZone` | `AirflowNetworkNode` | `AirflowNetwork:MultiZone:Zone` | `src/energyplus/ForwardTranslator/ForwardTranslateAirflowNetwork.cpp` |
| `OS:AirflowNetworkZoneExhaustFan` | `AirflowNetworkZoneExhaustFan` | `ModelObject` | `AirflowNetwork:MultiZone:Component:ZoneExhaustFan` | `src/energyplus/ForwardTranslator/ForwardTranslateAirflowNetwork.cpp` |
| `OS:AvailabilityManager:DifferentialThermostat` | `AvailabilityManagerDifferentialThermostat` | `AvailabilityManager` | `AvailabilityManager:DifferentialThermostat` | `src/energyplus/ForwardTranslator/ForwardTranslateAvailabilityManagerDifferentialThermostat.cpp` |
| `OS:AvailabilityManager:HighTemperatureTurnOff` | `AvailabilityManagerHighTemperatureTurnOff` | `AvailabilityManager` | `AvailabilityManager:HighTemperatureTurnOff` | `src/energyplus/ForwardTranslator/ForwardTranslateAvailabilityManagerHighTemperatureTurnOff.cpp` |
| `OS:AvailabilityManager:HighTemperatureTurnOn` | `AvailabilityManagerHighTemperatureTurnOn` | `AvailabilityManager` | `AvailabilityManager:HighTemperatureTurnOn` | `src/energyplus/ForwardTranslator/ForwardTranslateAvailabilityManagerHighTemperatureTurnOn.cpp` |
| `OS:AvailabilityManager:HybridVentilation` | `AvailabilityManagerHybridVentilation` | `AvailabilityManager` | `AvailabilityManager:HybridVentilation` | `src/energyplus/ForwardTranslator/ForwardTranslateAvailabilityManagerHybridVentilation.cpp` |
| `OS:AvailabilityManager:LowTemperatureTurnOff` | `AvailabilityManagerLowTemperatureTurnOff` | `AvailabilityManager` | `AvailabilityManager:LowTemperatureTurnOff` | `src/energyplus/ForwardTranslator/ForwardTranslateAvailabilityManagerLowTemperatureTurnOff.cpp` |
| `OS:AvailabilityManager:LowTemperatureTurnOn` | `AvailabilityManagerLowTemperatureTurnOn` | `AvailabilityManager` | `AvailabilityManager:LowTemperatureTurnOn` | `src/energyplus/ForwardTranslator/ForwardTranslateAvailabilityManagerLowTemperatureTurnOn.cpp` |
| `OS:AvailabilityManager:NightCycle` | `AvailabilityManagerNightCycle` | `AvailabilityManager` | `AvailabilityManager:NightCycle`, `ZoneList` | `src/energyplus/ForwardTranslator/ForwardTranslateAvailabilityManagerNightCycle.cpp` |
| `OS:AvailabilityManager:NightVentilation` | `AvailabilityManagerNightVentilation` | `AvailabilityManager` | `AvailabilityManager:NightVentilation` | `src/energyplus/ForwardTranslator/ForwardTranslateAvailabilityManagerNightVentilation.cpp` |
| `OS:AvailabilityManager:OptimumStart` | `AvailabilityManagerOptimumStart` | `AvailabilityManager` | `AvailabilityManager:OptimumStart`, `ZoneList` | `src/energyplus/ForwardTranslator/ForwardTranslateAvailabilityManagerOptimumStart.cpp` |
| `OS:AvailabilityManager:Scheduled` | `AvailabilityManagerScheduled` | `AvailabilityManager` | `AvailabilityManager:Scheduled` | `src/energyplus/ForwardTranslator/ForwardTranslateAvailabilityManagerScheduled.cpp` |
| `OS:AvailabilityManager:ScheduledOff` | `AvailabilityManagerScheduledOff` | `AvailabilityManager` | `AvailabilityManager:ScheduledOff` | `src/energyplus/ForwardTranslator/ForwardTranslateAvailabilityManagerScheduledOff.cpp` |
| `OS:AvailabilityManager:ScheduledOn` | `AvailabilityManagerScheduledOn` | `AvailabilityManager` | `AvailabilityManager:ScheduledOn` | `src/energyplus/ForwardTranslator/ForwardTranslateAvailabilityManagerScheduledOn.cpp` |
| `OS:AvailabilityManagerAssignmentList` | `AvailabilityManagerAssignmentList` | `ModelObject` | `AvailabilityManagerAssignmentList` | `src/energyplus/ForwardTranslator/ForwardTranslateAvailabilityManagerAssignmentList.cpp` |
| `OS:Boiler:HotWater` | `BoilerHotWater` | `StraightComponent` | `Boiler:HotWater` | `src/energyplus/ForwardTranslator/ForwardTranslateBoilerHotWater.cpp` |
| `OS:Boiler:Steam` | `BoilerSteam` | `StraightComponent` | `Boiler:Steam` | `src/energyplus/ForwardTranslator/ForwardTranslateBoilerSteam.cpp` |
| `OS:Building` | `Building` | `ParentObject` | `Building` | `src/energyplus/ForwardTranslator/ForwardTranslateBuilding.cpp` |
| `OS:BuildingStory` | `BuildingStory` | `ModelObject` |  |  |
| `OS:BuildingUnit` | `BuildingUnit` | `ModelObject` |  |  |
| `OS:CentralHeatPumpSystem` | `CentralHeatPumpSystem` | `WaterToWaterComponent` | `CentralHeatPumpSystem` | `src/energyplus/ForwardTranslator/ForwardTranslateCentralHeatPumpSystem.cpp` |
| `OS:CentralHeatPumpSystem:Module` | `CentralHeatPumpSystemModule` | `ParentObject` |  |  |
| `OS:Chiller:Absorption` | `ChillerAbsorption` | `WaterToWaterComponent` | `Chiller:Absorption` | `src/energyplus/ForwardTranslator/ForwardTranslateChillerAbsorption.cpp` |
| `OS:Chiller:Absorption:Indirect` | `ChillerAbsorptionIndirect` | `WaterToWaterComponent` | `Chiller:Absorption:Indirect` | `src/energyplus/ForwardTranslator/ForwardTranslateChillerAbsorptionIndirect.cpp` |
| `OS:Chiller:Electric:ASHRAE205` | `ChillerElectricASHRAE205` | `WaterToWaterComponent` | `Chiller:Electric:ASHRAE205`, `OutdoorAir:NodeList` | `src/energyplus/ForwardTranslator/ForwardTranslateChillerElectricASHRAE205.cpp` |
| `OS:Chiller:Electric:EIR` | `ChillerElectricEIR` | `WaterToWaterComponent` | `Chiller:Electric:EIR`, `OutdoorAir:NodeList` | `src/energyplus/ForwardTranslator/ForwardTranslateChillerElectricEIR.cpp` |
| `OS:Chiller:Electric:ReformulatedEIR` | `ChillerElectricReformulatedEIR` | `WaterToWaterComponent` | `Chiller:Electric:ReformulatedEIR` | `src/energyplus/ForwardTranslator/ForwardTranslateChillerElectricReformulatedEIR.cpp` |
| `OS:ChillerHeaterPerformance:Electric:EIR` | `ChillerHeaterPerformanceElectricEIR` | `ParentObject` | `ChillerHeaterPerformance:Electric:EIR` | `src/energyplus/ForwardTranslator/ForwardTranslateChillerHeaterPerformanceElectricEIR.cpp` |
| `OS:ClimateZones` | `ClimateZones` | `ModelObject` |  |  |
| `OS:Coil:Cooling:CooledBeam` | `CoilCoolingCooledBeam` | `StraightComponent` |  |  |
| `OS:Coil:Cooling:DX` | `CoilCoolingDX` | `StraightComponent` | `CoilSystem:Cooling:DX`, `Coil:Cooling:DX`, `OutdoorAir:NodeList` | `src/energyplus/ForwardTranslator/ForwardTranslateCoilCoolingDX.cpp` |
| `OS:Coil:Cooling:DX:CurveFit:OperatingMode` | `CoilCoolingDXCurveFitOperatingMode` | `ResourceObject` | `Coil:Cooling:DX:CurveFit:OperatingMode` | `src/energyplus/ForwardTranslator/ForwardTranslateCoilCoolingDXCurveFitOperatingMode.cpp` |
| `OS:Coil:Cooling:DX:CurveFit:Performance` | `CoilCoolingDXCurveFitPerformance` | `ResourceObject` | `Coil:Cooling:DX:CurveFit:Performance` | `src/energyplus/ForwardTranslator/ForwardTranslateCoilCoolingDXCurveFitPerformance.cpp` |
| `OS:Coil:Cooling:DX:CurveFit:Speed` | `CoilCoolingDXCurveFitSpeed` | `ResourceObject` | `Coil:Cooling:DX:CurveFit:Speed` | `src/energyplus/ForwardTranslator/ForwardTranslateCoilCoolingDXCurveFitSpeed.cpp` |
| `OS:Coil:Cooling:DX:MultiSpeed` | `CoilCoolingDXMultiSpeed` | `StraightComponent` | `Coil:Cooling:DX:MultiSpeed` | `src/energyplus/ForwardTranslator/ForwardTranslateCoilCoolingDXMultiSpeed.cpp` |
| `OS:Coil:Cooling:DX:MultiSpeed:StageData` | `CoilCoolingDXMultiSpeedStageData` | `ParentObject` |  |  |
| `OS:Coil:Cooling:DX:SingleSpeed` | `CoilCoolingDXSingleSpeed` | `StraightComponent` | `CoilSystem:Cooling:DX`, `Coil:Cooling:DX:SingleSpeed` | `src/energyplus/ForwardTranslator/ForwardTranslateCoilCoolingDXSingleSpeed.cpp` |
| `OS:Coil:Cooling:DX:SingleSpeed:ThermalStorage` | `CoilCoolingDXSingleSpeedThermalStorage` | `StraightComponent` | `CoilSystem:Cooling:DX`, `Coil:Cooling:DX:SingleSpeed:ThermalStorage`, `OutdoorAir:NodeList` | `src/energyplus/ForwardTranslator/ForwardTranslateCoilCoolingDXSingleSpeedThermalStorage.cpp` |
| `OS:Coil:Cooling:DX:TwoSpeed` | `CoilCoolingDXTwoSpeed` | `StraightComponent` | `CoilSystem:Cooling:DX`, `Coil:Cooling:DX:TwoSpeed` | `src/energyplus/ForwardTranslator/ForwardTranslateCoilCoolingDXTwoSpeed.cpp` |
| `OS:Coil:Cooling:DX:TwoStageWithHumidityControlMode` | `CoilCoolingDXTwoStageWithHumidityControlMode` | `StraightComponent` | `CoilSystem:Cooling:DX`, `Coil:Cooling:DX:TwoStageWithHumidityControlMode` | `src/energyplus/ForwardTranslator/ForwardTranslateCoilCoolingDXTwoStageWithHumidityControlMode.cpp` |
| `OS:Coil:Cooling:DX:VariableRefrigerantFlow` | `CoilCoolingDXVariableRefrigerantFlow` | `HVACComponent` | `Coil:Cooling:DX:VariableRefrigerantFlow` | `src/energyplus/ForwardTranslator/ForwardTranslateCoilCoolingDXVariableRefrigerantFlow.cpp` |
| `OS:Coil:Cooling:DX:VariableRefrigerantFlow:FluidTemperatureControl` | `CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl` | `HVACComponent` | `Coil:Cooling:DX:VariableRefrigerantFlow:FluidTemperatureControl` | `src/energyplus/ForwardTranslator/ForwardTranslateCoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl.cpp` |
| `OS:Coil:Cooling:DX:VariableSpeed` | `CoilCoolingDXVariableSpeed` | `StraightComponent` | `CoilSystem:Cooling:DX`, `Coil:Cooling:DX:VariableSpeed` | `src/energyplus/ForwardTranslator/ForwardTranslateCoilCoolingDXVariableSpeed.cpp` |
| `OS:Coil:Cooling:DX:VariableSpeed:SpeedData` | `CoilCoolingDXVariableSpeedSpeedData` | `ParentObject` |  |  |
| `OS:Coil:Cooling:FourPipeBeam` | `CoilCoolingFourPipeBeam` | `StraightComponent` |  |  |
| `OS:Coil:Cooling:LowTemperatureRadiant:ConstantFlow` | `CoilCoolingLowTempRadiantConstFlow` | `StraightComponent` |  |  |
| `OS:Coil:Cooling:LowTemperatureRadiant:VariableFlow` | `CoilCoolingLowTempRadiantVarFlow` | `StraightComponent` |  |  |
| `OS:Coil:Cooling:Water` | `CoilCoolingWater` | `WaterToAirComponent` | `Coil:Cooling:Water` | `src/energyplus/ForwardTranslator/ForwardTranslateCoilCoolingWater.cpp` |
| `OS:Coil:Cooling:Water:Panel:Radiant` | `CoilCoolingWaterPanelRadiant` | `StraightComponent` |  |  |
| `OS:Coil:Cooling:WaterToAirHeatPump:EquationFit` | `CoilCoolingWaterToAirHeatPumpEquationFit` | `WaterToAirComponent` | `Coil:Cooling:WaterToAirHeatPump:EquationFit` | `src/energyplus/ForwardTranslator/ForwardTranslateCoilCoolingWaterToAirHeatPumpEquationFit.cpp` |
| `OS:Coil:Cooling:WaterToAirHeatPump:VariableSpeedEquationFit` | `CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit` | `WaterToAirComponent` | `Coil:Cooling:WaterToAirHeatPump:VariableSpeedEquationFit` | `src/energyplus/ForwardTranslator/ForwardTranslateCoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit.cpp` |
| `OS:Coil:Cooling:WaterToAirHeatPump:VariableSpeedEquationFit:SpeedData` | `CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData` | `ParentObject` |  |  |
| `OS:Coil:Heating:DX:MultiSpeed` | `CoilHeatingDXMultiSpeed` | `StraightComponent` | `Coil:Heating:DX:MultiSpeed` | `src/energyplus/ForwardTranslator/ForwardTranslateCoilHeatingDXMultiSpeed.cpp` |
| `OS:Coil:Heating:DX:MultiSpeed:StageData` | `CoilHeatingDXMultiSpeedStageData` | `ParentObject` |  |  |
| `OS:Coil:Heating:DX:SingleSpeed` | `CoilHeatingDXSingleSpeed` | `StraightComponent` | `CoilSystem:Heating:DX`, `Coil:Heating:DX:SingleSpeed` | `src/energyplus/ForwardTranslator/ForwardTranslateCoilHeatingDXSingleSpeed.cpp` |
| `OS:Coil:Heating:DX:VariableRefrigerantFlow` | `CoilHeatingDXVariableRefrigerantFlow` | `HVACComponent` | `Coil:Heating:DX:VariableRefrigerantFlow` | `src/energyplus/ForwardTranslator/ForwardTranslateCoilHeatingDXVariableRefrigerantFlow.cpp` |
| `OS:Coil:Heating:DX:VariableRefrigerantFlow:FluidTemperatureControl` | `CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl` | `HVACComponent` | `Coil:Heating:DX:VariableRefrigerantFlow:FluidTemperatureControl` | `src/energyplus/ForwardTranslator/ForwardTranslateCoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl.cpp` |
| `OS:Coil:Heating:DX:VariableSpeed` | `CoilHeatingDXVariableSpeed` | `StraightComponent` | `CoilSystem:Heating:DX`, `Coil:Heating:DX:VariableSpeed` | `src/energyplus/ForwardTranslator/ForwardTranslateCoilHeatingDXVariableSpeed.cpp` |
| `OS:Coil:Heating:DX:VariableSpeed:SpeedData` | `CoilHeatingDXVariableSpeedSpeedData` | `ParentObject` |  |  |
| `OS:Coil:Heating:Desuperheater` | `CoilHeatingDesuperheater` | `StraightComponent` | `Coil:Heating:Desuperheater` | `src/energyplus/ForwardTranslator/ForwardTranslateCoilHeatingDesuperheater.cpp` |
| `OS:Coil:Heating:Electric` | `CoilHeatingElectric` | `StraightComponent` | `Coil:Heating:Electric` | `src/energyplus/ForwardTranslator/ForwardTranslateCoilHeatingElectric.cpp` |
| `OS:Coil:Heating:Electric:MultiStage` | `CoilHeatingElectricMultiStage` | `StraightComponent` | `Coil:Heating:Electric:MultiStage` | `src/energyplus/ForwardTranslator/ForwardTranslateCoilHeatingElectricMultiStage.cpp` |
| `OS:Coil:Heating:Electric:MultiStage:StageData` | `CoilHeatingElectricMultiStageStageData` | `ModelObject` |  |  |
| `OS:Coil:Heating:FourPipeBeam` | `CoilHeatingFourPipeBeam` | `StraightComponent` |  |  |
| `OS:Coil:Heating:Gas` | `CoilHeatingGas` | `StraightComponent` | `Coil:Heating:Fuel` | `src/energyplus/ForwardTranslator/ForwardTranslateCoilHeatingGas.cpp` |
| `OS:Coil:Heating:Gas:MultiStage` | `CoilHeatingGasMultiStage` | `StraightComponent` | `Coil:Heating:Gas:MultiStage` | `src/energyplus/ForwardTranslator/ForwardTranslateCoilHeatingGasMultiStage.cpp` |
| `OS:Coil:Heating:Gas:MultiStage:StageData` | `CoilHeatingGasMultiStageStageData` | `ModelObject` |  |  |
| `OS:Coil:Heating:LowTemperatureRadiant:ConstantFlow` | `CoilHeatingLowTempRadiantConstFlow` | `StraightComponent` |  |  |
| `OS:Coil:Heating:LowTemperatureRadiant:VariableFlow` | `CoilHeatingLowTempRadiantVarFlow` | `StraightComponent` |  |  |
| `OS:Coil:Heating:Water` | `CoilHeatingWater` | `WaterToAirComponent` | `Coil:Heating:Water` | `src/energyplus/ForwardTranslator/ForwardTranslateCoilHeatingWater.cpp` |
| `OS:Coil:Heating:Water:Baseboard` | `CoilHeatingWaterBaseboard` | `StraightComponent` |  |  |
| `OS:Coil:Heating:Water:Baseboard:Radiant` | `CoilHeatingWaterBaseboardRadiant` | `StraightComponent` |  |  |
| `OS:Coil:Heating:WaterToAirHeatPump:EquationFit` | `CoilHeatingWaterToAirHeatPumpEquationFit` | `WaterToAirComponent` | `Coil:Heating:WaterToAirHeatPump:EquationFit` | `src/energyplus/ForwardTranslator/ForwardTranslateCoilHeatingWaterToAirHeatPumpEquationFit.cpp` |
| `OS:Coil:Heating:WaterToAirHeatPump:VariableSpeedEquationFit` | `CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit` | `WaterToAirComponent` | `Coil:Heating:WaterToAirHeatPump:VariableSpeedEquationFit` | `src/energyplus/ForwardTranslator/ForwardTranslateCoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit.cpp` |
| `OS:Coil:Heating:WaterToAirHeatPump:VariableSpeedEquationFit:SpeedData` | `CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData` | `ParentObject` |  |  |
| `OS:Coil:UserDefined` | `CoilUserDefined` | `WaterToAirComponent` | `Coil:UserDefined` | `src/energyplus/ForwardTranslator/ForwardTranslateCoilUserDefined.cpp` |
| `OS:Coil:WaterHeating:AirToWaterHeatPump` | `CoilWaterHeatingAirToWaterHeatPump` | `HVACComponent` | `Coil:WaterHeating:AirToWaterHeatPump:Pumped` | `src/energyplus/ForwardTranslator/ForwardTranslateCoilWaterHeatingAirToWaterHeatPump.cpp` |
| `OS:Coil:WaterHeating:AirToWaterHeatPump:VariableSpeed` | `CoilWaterHeatingAirToWaterHeatPumpVariableSpeed` | `HVACComponent` | `Coil:WaterHeating:AirToWaterHeatPump:VariableSpeed` | `src/energyplus/ForwardTranslator/ForwardTranslateCoilWaterHeatingAirToWaterHeatPumpVariableSpeed.cpp` |
| `OS:Coil:WaterHeating:AirToWaterHeatPump:VariableSpeed:SpeedData` | `CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData` | `ParentObject` |  |  |
| `OS:Coil:WaterHeating:AirToWaterHeatPump:Wrapped` | `CoilWaterHeatingAirToWaterHeatPumpWrapped` | `ModelObject` | `Coil:WaterHeating:AirToWaterHeatPump:Wrapped` | `src/energyplus/ForwardTranslator/ForwardTranslateCoilWaterHeatingAirToWaterHeatPumpWrapped.cpp` |
| `OS:Coil:WaterHeating:Desuperheater` | `CoilWaterHeatingDesuperheater` | `StraightComponent` | `Coil:WaterHeating:Desuperheater` | `src/energyplus/ForwardTranslator/ForwardTranslateCoilWaterHeatingDesuperheater.cpp` |
| `OS:CoilPerformance:DX:Cooling` | `CoilPerformanceDXCooling` | `ParentObject` | `CoilPerformance:DX:Cooling` | `src/energyplus/ForwardTranslator/ForwardTranslateCoilPerformanceDXCooling.cpp` |
| `OS:CoilSystem:Cooling:DX:HeatExchangerAssisted` | `CoilSystemCoolingDXHeatExchangerAssisted` | `StraightComponent` | `CoilSystem:Cooling:DX:HeatExchangerAssisted` | `src/energyplus/ForwardTranslator/ForwardTranslateCoilSystemCoolingDXHeatExchangerAssisted.cpp` |
| `OS:CoilSystem:Cooling:Water` | `CoilSystemCoolingWater` | `StraightComponent` | `CoilSystem:Cooling:Water` | `src/energyplus/ForwardTranslator/ForwardTranslateCoilSystemCoolingWater.cpp` |
| `OS:CoilSystem:Cooling:Water:HeatExchangerAssisted` | `CoilSystemCoolingWaterHeatExchangerAssisted` | `StraightComponent` | `CoilSystem:Cooling:Water:HeatExchangerAssisted`, `SetpointManager:MixedAir` | `src/energyplus/ForwardTranslator/ForwardTranslateCoilSystemCoolingWaterHeatExchangerAssisted.cpp` |
| `OS:CoilSystem:IntegratedHeatPump:AirSource` | `CoilSystemIntegratedHeatPumpAirSource` | `StraightComponent` | `CoilSystem:IntegratedHeatPump:AirSource` | `src/energyplus/ForwardTranslator/ForwardTranslateCoilSystemIntegratedHeatPumpAirSource.cpp` |
| `OS:ComponentCost:Adjustments` | `ComponentCostAdjustments` | `ParentObject` |  |  |
| `OS:ComponentData` | `ComponentData` | `ResourceObject` |  |  |
| `OS:Connection` | `Connection` | `ModelObject` |  |  |
| `OS:Connector:Mixer` | `ConnectorMixer` | `Mixer` |  |  |
| `OS:Connector:Splitter` | `ConnectorSplitter` | `Splitter` |  |  |
| `OS:Construction` | `Construction` | `LayeredConstruction` | `Construction` | `src/energyplus/ForwardTranslator/ForwardTranslateConstruction.cpp` |
| `OS:Construction:AirBoundary` | `ConstructionAirBoundary` | `ConstructionBase` | `Construction:AirBoundary` | `src/energyplus/ForwardTranslator/ForwardTranslateConstructionAirBoundary.cpp` |
| `OS:Construction:CfactorUndergroundWall` | `CFactorUndergroundWallConstruction` | `ConstructionBase` | `Construction:CfactorUndergroundWall` | `src/energyplus/ForwardTranslator/ForwardTranslateCFactorUndergroundWallConstruction.cpp` |
| `OS:Construction:FfactorGroundFloor` | `FFactorGroundFloorConstruction` | `ConstructionBase` | `Construction:FfactorGroundFloor` | `src/energyplus/ForwardTranslator/ForwardTranslateFFactorGroundFloorConstruction.cpp` |
| `OS:Construction:InternalSource` | `ConstructionWithInternalSource` | `LayeredConstruction` | `Construction`, `ConstructionProperty:InternalHeatSource` | `src/energyplus/ForwardTranslator/ForwardTranslateConstructionWithInternalSource.cpp` |
| `OS:Construction:WindowDataFile` | `WindowDataFile` | `ConstructionBase` |  |  |
| `OS:Controller:MechanicalVentilation` | `ControllerMechanicalVentilation` | `ModelObject` | `Controller:MechanicalVentilation` | `src/energyplus/ForwardTranslator/ForwardTranslateControllerMechanicalVentilation.cpp` |
| `OS:Controller:OutdoorAir` | `ControllerOutdoorAir` | `ParentObject` | `Controller:OutdoorAir` | `src/energyplus/ForwardTranslator/ForwardTranslateControllerOutdoorAir.cpp` |
| `OS:Controller:WaterCoil` | `ControllerWaterCoil` | `HVACComponent` | `Controller:WaterCoil` | `src/energyplus/ForwardTranslator/ForwardTranslateControllerWaterCoil.cpp` |
| `OS:ConvergenceLimits` | `ConvergenceLimits` | `ModelObject` | `ConvergenceLimits` | `src/energyplus/ForwardTranslator/ForwardTranslateConvergenceLimits.cpp` |
| `OS:CoolingTower:SingleSpeed` | `CoolingTowerSingleSpeed` | `StraightComponent` | `CoolingTower:SingleSpeed` | `src/energyplus/ForwardTranslator/ForwardTranslateCoolingTowerSingleSpeed.cpp` |
| `OS:CoolingTower:TwoSpeed` | `CoolingTowerTwoSpeed` | `StraightComponent` | `CoolingTower:TwoSpeed` | `src/energyplus/ForwardTranslator/ForwardTranslateCoolingTowerTwoSpeed.cpp` |
| `OS:CoolingTower:VariableSpeed` | `CoolingTowerVariableSpeed` | `StraightComponent` | `CoolingTower:VariableSpeed` | `src/energyplus/ForwardTranslator/ForwardTranslateCoolingTowerVariableSpeed.cpp` |
| `OS:CoolingTowerPerformance:CoolTools` | `CoolingTowerPerformanceCoolTools` | `ModelObject` | `CoolingTowerPerformance:CoolTools` | `src/energyplus/ForwardTranslator/ForwardTranslateCoolingTowerPerformanceCoolTools.cpp` |
| `OS:CoolingTowerPerformance:YorkCalc` | `CoolingTowerPerformanceYorkCalc` | `ModelObject` | `CoolingTowerPerformance:YorkCalc` | `src/energyplus/ForwardTranslator/ForwardTranslateCoolingTowerPerformanceYorkCalc.cpp` |
| `OS:CurrencyType` | `CurrencyType` | `ParentObject` | `CurrencyType` | `src/energyplus/ForwardTranslator/ForwardTranslateCurrencyType.cpp` |
| `OS:Curve:Bicubic` | `CurveBicubic` | `Curve` | `Curve:Bicubic` | `src/energyplus/ForwardTranslator/ForwardTranslateCurveBicubic.cpp` |
| `OS:Curve:Biquadratic` | `CurveBiquadratic` | `Curve` | `Curve:Biquadratic` | `src/energyplus/ForwardTranslator/ForwardTranslateCurveBiquadratic.cpp` |
| `OS:Curve:Cubic` | `CurveCubic` | `Curve` | `Curve:Cubic` | `src/energyplus/ForwardTranslator/ForwardTranslateCurveCubic.cpp` |
| `OS:Curve:DoubleExponentialDecay` | `CurveDoubleExponentialDecay` | `Curve` | `Curve:DoubleExponentialDecay` | `src/energyplus/ForwardTranslator/ForwardTranslateCurveDoubleExponentialDecay.cpp` |
| `OS:Curve:Exponent` | `CurveExponent` | `Curve` | `Curve:Exponent` | `src/energyplus/ForwardTranslator/ForwardTranslateCurveExponent.cpp` |
| `OS:Curve:ExponentialDecay` | `CurveExponentialDecay` | `Curve` | `Curve:ExponentialDecay` | `src/energyplus/ForwardTranslator/ForwardTranslateCurveExponentialDecay.cpp` |
| `OS:Curve:ExponentialSkewNormal` | `CurveExponentialSkewNormal` | `Curve` | `Curve:ExponentialSkewNormal` | `src/energyplus/ForwardTranslator/ForwardTranslateCurveExponentialSkewNormal.cpp` |
| `OS:Curve:FanPressureRise` | `CurveFanPressureRise` | `Curve` | `Curve:FanPressureRise` | `src/energyplus/ForwardTranslator/ForwardTranslateCurveFanPressureRise.cpp` |
| `OS:Curve:Functional:PressureDrop` | `CurveFunctionalPressureDrop` | `Curve` | `Curve:Functional:PressureDrop` | `src/energyplus/ForwardTranslator/ForwardTranslateCurveFunctionalPressureDrop.cpp` |
| `OS:Curve:Linear` | `CurveLinear` | `Curve` | `Curve:Linear` | `src/energyplus/ForwardTranslator/ForwardTranslateCurveLinear.cpp` |
| `OS:Curve:QuadLinear` | `CurveQuadLinear` | `Curve` | `Curve:QuadLinear` | `src/energyplus/ForwardTranslator/ForwardTranslateCurveQuadLinear.cpp` |
| `OS:Curve:Quadratic` | `CurveQuadratic` | `Curve` | `Curve:Quadratic` | `src/energyplus/ForwardTranslator/ForwardTranslateCurveQuadratic.cpp` |
| `OS:Curve:QuadraticLinear` | `CurveQuadraticLinear` | `Curve` | `Curve:QuadraticLinear` | `src/energyplus/ForwardTranslator/ForwardTranslateCurveQuadraticLinear.cpp` |
| `OS:Curve:Quartic` | `CurveQuartic` | `Curve` | `Curve:Quartic` | `src/energyplus/ForwardTranslator/ForwardTranslateCurveQuartic.cpp` |
| `OS:Curve:QuintLinear` | `CurveQuintLinear` | `Curve` | `Curve:QuintLinear` | `src/energyplus/ForwardTranslator/ForwardTranslateCurveQuintLinear.cpp` |
| `OS:Curve:RectangularHyperbola1` | `CurveRectangularHyperbola1` | `Curve` | `Curve:RectangularHyperbola1` | `src/energyplus/ForwardTranslator/ForwardTranslateCurveRectangularHyperbola1.cpp` |
| `OS:Curve:RectangularHyperbola2` | `CurveRectangularHyperbola2` | `Curve` | `Curve:RectangularHyperbola2` | `src/energyplus/ForwardTranslator/ForwardTranslateCurveRectangularHyperbola2.cpp` |
| `OS:Curve:Sigmoid` | `CurveSigmoid` | `Curve` | `Curve:Sigmoid` | `src/energyplus/ForwardTranslator/ForwardTranslateCurveSigmoid.cpp` |
| `OS:Curve:Triquadratic` | `CurveTriquadratic` | `Curve` | `Curve:Triquadratic` | `src/energyplus/ForwardTranslator/ForwardTranslateCurveTriquadratic.cpp` |
| `OS:Daylighting:Control` | `DaylightingControl` | `SpaceItem` |  | `src/energyplus/ForwardTranslator/ForwardTranslateDaylightingControl.cpp` |
| `OS:DaylightingDevice:LightWell` | `DaylightingDeviceLightWell` | `ModelObject` | `DaylightingDevice:LightWell` | `src/energyplus/ForwardTranslator/ForwardTranslateDaylightingDeviceLightWell.cpp` |
| `OS:DaylightingDevice:Shelf` | `DaylightingDeviceShelf` | `ModelObject` | `DaylightingDevice:Shelf` | `src/energyplus/ForwardTranslator/ForwardTranslateDaylightingDeviceShelf.cpp` |
| `OS:DaylightingDevice:Tubular` | `DaylightingDeviceTubular` | `ModelObject` | `DaylightingDevice:Tubular` | `src/energyplus/ForwardTranslator/ForwardTranslateDaylightingDeviceTubular.cpp` |
| `OS:DefaultConstructionSet` | `DefaultConstructionSet` | `ResourceObject` |  |  |
| `OS:DefaultScheduleSet` | `DefaultScheduleSet` | `ResourceObject` |  |  |
| `OS:DefaultSubSurfaceConstructions` | `DefaultSubSurfaceConstructions` | `ResourceObject` |  |  |
| `OS:DefaultSurfaceConstructions` | `DefaultSurfaceConstructions` | `ResourceObject` |  |  |
| `OS:DesignSpecification:OutdoorAir` | `DesignSpecificationOutdoorAir` | `ResourceObject` |  |  |
| `OS:DesignSpecification:ZoneAirDistribution` | `DesignSpecificationZoneAirDistribution` | `ModelObject` |  |  |
| `OS:DistrictCooling` | `DistrictCooling` | `StraightComponent` | `DistrictCooling` | `src/energyplus/ForwardTranslator/ForwardTranslateDistrictCooling.cpp` |
| `OS:DistrictHeating:Steam` | `DistrictHeatingSteam` | `StraightComponent` | `DistrictHeating:Steam` | `src/energyplus/ForwardTranslator/ForwardTranslateDistrictHeatingSteam.cpp` |
| `OS:DistrictHeating:Water` | `DistrictHeatingWater` | `StraightComponent` | `DistrictHeating:Water` | `src/energyplus/ForwardTranslator/ForwardTranslateDistrictHeatingWater.cpp` |
| `OS:Duct` | `Duct` | `StraightComponent` | `Duct` | `src/energyplus/ForwardTranslator/ForwardTranslateDuct.cpp` |
| `OS:ElectricEquipment` | `ElectricEquipment` | `SpaceLoadInstance` | `ElectricEquipment` | `src/energyplus/ForwardTranslator/ForwardTranslateElectricEquipment.cpp` |
| `OS:ElectricEquipment:Definition` | `ElectricEquipmentDefinition` | `SpaceLoadDefinition` |  |  |
| `OS:ElectricEquipment:ITE:AirCooled` | `ElectricEquipmentITEAirCooled` | `SpaceLoadInstance` | `ElectricEquipment:ITE:AirCooled` | `src/energyplus/ForwardTranslator/ForwardTranslateElectricEquipmentITEAirCooled.cpp` |
| `OS:ElectricEquipment:ITE:AirCooled:Definition` | `ElectricEquipmentITEAirCooledDefinition` | `SpaceLoadDefinition` |  |  |
| `OS:ElectricLoadCenter:Distribution` | `ElectricLoadCenterDistribution` | `ParentObject` | `ElectricLoadCenter:Distribution`, `ElectricLoadCenter:Generators` | `src/energyplus/ForwardTranslator/ForwardTranslateElectricLoadCenterDistribution.cpp` |
| `OS:ElectricLoadCenter:Inverter:LookUpTable` | `ElectricLoadCenterInverterLookUpTable` | `Inverter` | `ElectricLoadCenter:Inverter:LookUpTable` | `src/energyplus/ForwardTranslator/ForwardTranslateElectricLoadCenterInverterLookUpTable.cpp` |
| `OS:ElectricLoadCenter:Inverter:PVWatts` | `ElectricLoadCenterInverterPVWatts` | `Inverter` | `ElectricLoadCenter:Inverter:PVWatts` | `src/energyplus/ForwardTranslator/ForwardTranslateElectricLoadCenterInverterPVWatts.cpp` |
| `OS:ElectricLoadCenter:Inverter:Simple` | `ElectricLoadCenterInverterSimple` | `Inverter` | `ElectricLoadCenter:Inverter:Simple` | `src/energyplus/ForwardTranslator/ForwardTranslateElectricLoadCenterInverterSimple.cpp` |
| `OS:ElectricLoadCenter:Storage:Converter` | `ElectricLoadCenterStorageConverter` | `ParentObject` | `ElectricLoadCenter:Storage:Converter` | `src/energyplus/ForwardTranslator/ForwardTranslateElectricLoadCenterStorageConverter.cpp` |
| `OS:ElectricLoadCenter:Storage:LiIonNMCBattery` | `ElectricLoadCenterStorageLiIonNMCBattery` | `ElectricalStorage` | `ElectricLoadCenter:Storage:LiIonNMCBattery` | `src/energyplus/ForwardTranslator/ForwardTranslateElectricLoadCenterStorageLiIonNMCBattery.cpp` |
| `OS:ElectricLoadCenter:Storage:Simple` | `ElectricLoadCenterStorageSimple` | `ElectricalStorage` | `ElectricLoadCenter:Storage:Simple` | `src/energyplus/ForwardTranslator/ForwardTranslateElectricLoadCenterStorageSimple.cpp` |
| `OS:ElectricLoadCenter:Transformer` | `ElectricLoadCenterTransformer` | `ModelObject` | `ElectricLoadCenter:Transformer` | `src/energyplus/ForwardTranslator/ForwardTranslateElectricLoadCenterTransformer.cpp` |
| `OS:EnergyManagementSystem:Actuator` | `EnergyManagementSystemActuator` | `ModelObject` | `EnergyManagementSystem:Actuator` | `src/energyplus/ForwardTranslator/ForwardTranslateEnergyManagementSystemActuator.cpp` |
| `OS:EnergyManagementSystem:ConstructionIndexVariable` | `EnergyManagementSystemConstructionIndexVariable` | `ModelObject` | `EnergyManagementSystem:ConstructionIndexVariable` | `src/energyplus/ForwardTranslator/ForwardTranslateEnergyManagementSystemConstructionIndexVariable.cpp` |
| `OS:EnergyManagementSystem:CurveOrTableIndexVariable` | `EnergyManagementSystemCurveOrTableIndexVariable` | `ModelObject` | `EnergyManagementSystem:CurveOrTableIndexVariable` | `src/energyplus/ForwardTranslator/ForwardTranslateEnergyManagementSystemCurveOrTableIndexVariable.cpp` |
| `OS:EnergyManagementSystem:GlobalVariable` | `EnergyManagementSystemGlobalVariable` | `ModelObject` | `EnergyManagementSystem:GlobalVariable` | `src/energyplus/ForwardTranslator/ForwardTranslateEnergyManagementSystemGlobalVariable.cpp` |
| `OS:EnergyManagementSystem:InternalVariable` | `EnergyManagementSystemInternalVariable` | `ModelObject` | `EnergyManagementSystem:InternalVariable` | `src/energyplus/ForwardTranslator/ForwardTranslateEnergyManagementSystemInternalVariable.cpp` |
| `OS:EnergyManagementSystem:MeteredOutputVariable` | `EnergyManagementSystemMeteredOutputVariable` | `ModelObject` | `EnergyManagementSystem:MeteredOutputVariable` | `src/energyplus/ForwardTranslator/ForwardTranslateEnergyManagementSystemMeteredOutputVariable.cpp` |
| `OS:EnergyManagementSystem:OutputVariable` | `EnergyManagementSystemOutputVariable` | `ModelObject` | `EnergyManagementSystem:OutputVariable` | `src/energyplus/ForwardTranslator/ForwardTranslateEnergyManagementSystemOutputVariable.cpp` |
| `OS:EnergyManagementSystem:Program` | `EnergyManagementSystemProgram` | `ModelObject` | `EnergyManagementSystem:Program` | `src/energyplus/ForwardTranslator/ForwardTranslateEnergyManagementSystemProgram.cpp` |
| `OS:EnergyManagementSystem:ProgramCallingManager` | `EnergyManagementSystemProgramCallingManager` | `ModelObject` | `EnergyManagementSystem:ProgramCallingManager` | `src/energyplus/ForwardTranslator/ForwardTranslateEnergyManagementSystemProgramCallingManager.cpp` |
| `OS:EnergyManagementSystem:Sensor` | `EnergyManagementSystemSensor` | `ModelObject` | `EnergyManagementSystem:Sensor` | `src/energyplus/ForwardTranslator/ForwardTranslateEnergyManagementSystemSensor.cpp` |
| `OS:EnergyManagementSystem:Subroutine` | `EnergyManagementSystemSubroutine` | `ModelObject` | `EnergyManagementSystem:Subroutine` | `src/energyplus/ForwardTranslator/ForwardTranslateEnergyManagementSystemSubroutine.cpp` |
| `OS:EnergyManagementSystem:TrendVariable` | `EnergyManagementSystemTrendVariable` | `ModelObject` | `EnergyManagementSystem:TrendVariable` | `src/energyplus/ForwardTranslator/ForwardTranslateEnergyManagementSystemTrendVariable.cpp` |
| `OS:EnvironmentalImpactFactors` | `EnvironmentalImpactFactors` | `ModelObject` | `EnvironmentalImpactFactors` | `src/energyplus/ForwardTranslator/ForwardTranslateEnvironmentalImpactFactors.cpp` |
| `OS:EvaporativeCooler:Direct:ResearchSpecial` | `EvaporativeCoolerDirectResearchSpecial` | `StraightComponent` | `EvaporativeCooler:Direct:ResearchSpecial` | `src/energyplus/ForwardTranslator/ForwardTranslateEvaporativeCoolerDirectResearchSpecial.cpp` |
| `OS:EvaporativeCooler:Indirect:ResearchSpecial` | `EvaporativeCoolerIndirectResearchSpecial` | `StraightComponent` | `EvaporativeCooler:Indirect:ResearchSpecial`, `OutdoorAir:NodeList` | `src/energyplus/ForwardTranslator/ForwardTranslateEvaporativeCoolerIndirectResearchSpecial.cpp` |
| `OS:EvaporativeFluidCooler:SingleSpeed` | `EvaporativeFluidCoolerSingleSpeed` | `StraightComponent` | `EvaporativeFluidCooler:SingleSpeed` | `src/energyplus/ForwardTranslator/ForwardTranslateEvaporativeFluidCoolerSingleSpeed.cpp` |
| `OS:EvaporativeFluidCooler:TwoSpeed` | `EvaporativeFluidCoolerTwoSpeed` | `StraightComponent` | `EvaporativeFluidCooler:TwoSpeed` | `src/energyplus/ForwardTranslator/ForwardTranslateEvaporativeFluidCoolerTwoSpeed.cpp` |
| `OS:Exterior:FuelEquipment` | `ExteriorFuelEquipment` | `ExteriorLoadInstance` | `Exterior:FuelEquipment` | `src/energyplus/ForwardTranslator/ForwardTranslateExteriorFuelEquipment.cpp` |
| `OS:Exterior:FuelEquipment:Definition` | `ExteriorFuelEquipmentDefinition` | `ExteriorLoadDefinition` |  |  |
| `OS:Exterior:Lights` | `ExteriorLights` | `ExteriorLoadInstance` | `Exterior:Lights` | `src/energyplus/ForwardTranslator/ForwardTranslateExteriorLights.cpp` |
| `OS:Exterior:Lights:Definition` | `ExteriorLightsDefinition` | `ExteriorLoadDefinition` |  |  |
| `OS:Exterior:WaterEquipment` | `ExteriorWaterEquipment` | `ExteriorLoadInstance` | `Exterior:WaterEquipment` | `src/energyplus/ForwardTranslator/ForwardTranslateExteriorWaterEquipment.cpp` |
| `OS:Exterior:WaterEquipment:Definition` | `ExteriorWaterEquipmentDefinition` | `ExteriorLoadDefinition` |  |  |
| `OS:External:File` | `ExternalFile` | `ResourceObject` |  |  |
| `OS:ExternalInterface` | `ExternalInterface` | `ModelObject` | `ExternalInterface` | `src/energyplus/ForwardTranslator/ForwardTranslateExternalInterface.cpp` |
| `OS:ExternalInterface:Actuator` | `ExternalInterfaceActuator` | `ModelObject` | `ExternalInterface:Actuator` | `src/energyplus/ForwardTranslator/ForwardTranslateExternalInterfaceActuator.cpp` |
| `OS:ExternalInterface:FunctionalMockupUnitExport:From:Variable` | `ExternalInterfaceFunctionalMockupUnitExportFromVariable` | `ModelObject` | `ExternalInterface:FunctionalMockupUnitExport:From:Variable` | `src/energyplus/ForwardTranslator/ForwardTranslateExternalInterfaceFunctionalMockupUnitExportFromVariable.cpp` |
| `OS:ExternalInterface:FunctionalMockupUnitExport:To:Actuator` | `ExternalInterfaceFunctionalMockupUnitExportToActuator` | `ModelObject` | `ExternalInterface:FunctionalMockupUnitExport:To:Actuator` | `src/energyplus/ForwardTranslator/ForwardTranslateExternalInterfaceFunctionalMockupUnitExportToActuator.cpp` |
| `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule` | `ExternalInterfaceFunctionalMockupUnitExportToSchedule` | `Schedule` | `ExternalInterface:FunctionalMockupUnitExport:To:Schedule` | `src/energyplus/ForwardTranslator/ForwardTranslateExternalInterfaceFunctionalMockupUnitExportToSchedule.cpp` |
| `OS:ExternalInterface:FunctionalMockupUnitExport:To:Variable` | `ExternalInterfaceFunctionalMockupUnitExportToVariable` | `ModelObject` | `ExternalInterface:FunctionalMockupUnitExport:To:Variable` | `src/energyplus/ForwardTranslator/ForwardTranslateExternalInterfaceFunctionalMockupUnitExportToVariable.cpp` |
| `OS:ExternalInterface:FunctionalMockupUnitImport` | `ExternalInterfaceFunctionalMockupUnitImport` | `ModelObject` | `ExternalInterface:FunctionalMockupUnitImport` | `src/energyplus/ForwardTranslator/ForwardTranslateExternalInterfaceFunctionalMockupUnitImport.cpp` |
| `OS:ExternalInterface:FunctionalMockupUnitImport:From:Variable` | `ExternalInterfaceFunctionalMockupUnitImportFromVariable` | `ModelObject` | `ExternalInterface:FunctionalMockupUnitImport:From:Variable` | `src/energyplus/ForwardTranslator/ForwardTranslateExternalInterfaceFunctionalMockupUnitImportFromVariable.cpp` |
| `OS:ExternalInterface:FunctionalMockupUnitImport:To:Actuator` | `ExternalInterfaceFunctionalMockupUnitImportToActuator` | `ModelObject` | `ExternalInterface:FunctionalMockupUnitImport:To:Actuator` | `src/energyplus/ForwardTranslator/ForwardTranslateExternalInterfaceFunctionalMockupUnitImportToActuator.cpp` |
| `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule` | `ExternalInterfaceFunctionalMockupUnitImportToSchedule` | `Schedule` | `ExternalInterface:FunctionalMockupUnitImport:To:Schedule` | `src/energyplus/ForwardTranslator/ForwardTranslateExternalInterfaceFunctionalMockupUnitImportToSchedule.cpp` |
| `OS:ExternalInterface:FunctionalMockupUnitImport:To:Variable` | `ExternalInterfaceFunctionalMockupUnitImportToVariable` | `ModelObject` | `ExternalInterface:FunctionalMockupUnitImport:To:Variable` | `src/energyplus/ForwardTranslator/ForwardTranslateExternalInterfaceFunctionalMockupUnitImportToVariable.cpp` |
| `OS:ExternalInterface:Schedule` | `ExternalInterfaceSchedule` | `Schedule` | `ExternalInterface:Schedule` | `src/energyplus/ForwardTranslator/ForwardTranslateExternalInterfaceSchedule.cpp` |
| `OS:ExternalInterface:Variable` | `ExternalInterfaceVariable` | `ModelObject` | `ExternalInterface:Variable` | `src/energyplus/ForwardTranslator/ForwardTranslateExternalInterfaceVariable.cpp` |
| `OS:Facility` | `Facility` | `ParentObject` |  |  |
| `OS:Fan:ComponentModel` | `FanComponentModel` | `StraightComponent` | `Fan:ComponentModel` | `src/energyplus/ForwardTranslator/ForwardTranslateFanComponentModel.cpp` |
| `OS:Fan:ConstantVolume` | `FanConstantVolume` | `StraightComponent` | `Fan:ConstantVolume` | `src/energyplus/ForwardTranslator/ForwardTranslateFanConstantVolume.cpp` |
| `OS:Fan:OnOff` | `FanOnOff` | `StraightComponent` | `Fan:OnOff` | `src/energyplus/ForwardTranslator/ForwardTranslateFanOnOff.cpp` |
| `OS:Fan:SystemModel` | `FanSystemModel` | `StraightComponent` | `Fan:SystemModel` | `src/energyplus/ForwardTranslator/ForwardTranslateFanSystemModel.cpp` |
| `OS:Fan:VariableVolume` | `FanVariableVolume` | `StraightComponent` | `Fan:VariableVolume` | `src/energyplus/ForwardTranslator/ForwardTranslateFanVariableVolume.cpp` |
| `OS:Fan:ZoneExhaust` | `FanZoneExhaust` | `ZoneHVACComponent` | `Fan:ZoneExhaust` | `src/energyplus/ForwardTranslator/ForwardTranslateFanZoneExhaust.cpp` |
| `OS:FluidCooler:SingleSpeed` | `FluidCoolerSingleSpeed` | `StraightComponent` | `FluidCooler:SingleSpeed` | `src/energyplus/ForwardTranslator/ForwardTranslateFluidCoolerSingleSpeed.cpp` |
| `OS:FluidCooler:TwoSpeed` | `FluidCoolerTwoSpeed` | `StraightComponent` | `FluidCooler:TwoSpeed` | `src/energyplus/ForwardTranslator/ForwardTranslateFluidCoolerTwoSpeed.cpp` |
| `OS:Foundation:Kiva` | `FoundationKiva` | `ModelObject` | `Foundation:Kiva` | `src/energyplus/ForwardTranslator/ForwardTranslateFoundationKiva.cpp` |
| `OS:Foundation:Kiva:Settings` | `FoundationKivaSettings` | `ModelObject` | `Foundation:Kiva:Settings` | `src/energyplus/ForwardTranslator/ForwardTranslateFoundationKivaSettings.cpp` |
| `OS:FuelFactors` | `FuelFactors` | `ModelObject` | `FuelFactors` | `src/energyplus/ForwardTranslator/ForwardTranslateFuelFactors.cpp` |
| `OS:GasEquipment` | `GasEquipment` | `SpaceLoadInstance` | `GasEquipment` | `src/energyplus/ForwardTranslator/ForwardTranslateGasEquipment.cpp` |
| `OS:GasEquipment:Definition` | `GasEquipmentDefinition` | `SpaceLoadDefinition` |  |  |
| `OS:Generator:FuelCell` | `GeneratorFuelCell` | `Generator` | `Generator:FuelCell` | `src/energyplus/ForwardTranslator/ForwardTranslateGeneratorFuelCell.cpp` |
| `OS:Generator:FuelCell:AirSupply` | `GeneratorFuelCellAirSupply` | `ModelObject` | `Generator:FuelCell:AirSupply`, `OutdoorAir:NodeList` | `src/energyplus/ForwardTranslator/ForwardTranslateGeneratorFuelCellAirSupply.cpp` |
| `OS:Generator:FuelCell:AuxiliaryHeater` | `GeneratorFuelCellAuxiliaryHeater` | `ModelObject` | `Generator:FuelCell:AuxiliaryHeater` | `src/energyplus/ForwardTranslator/ForwardTranslateGeneratorFuelCellAuxiliaryHeater.cpp` |
| `OS:Generator:FuelCell:ElectricalStorage` | `GeneratorFuelCellElectricalStorage` | `ModelObject` | `Generator:FuelCell:ElectricalStorage` | `src/energyplus/ForwardTranslator/ForwardTranslateGeneratorFuelCellElectricalStorage.cpp` |
| `OS:Generator:FuelCell:ExhaustGasToWaterHeatExchanger` | `GeneratorFuelCellExhaustGasToWaterHeatExchanger` | `StraightComponent` | `Generator:FuelCell:ExhaustGasToWaterHeatExchanger` | `src/energyplus/ForwardTranslator/ForwardTranslateGeneratorFuelCellExhaustGasToWaterHeatExchanger.cpp` |
| `OS:Generator:FuelCell:Inverter` | `GeneratorFuelCellInverter` | `ModelObject` | `Generator:FuelCell:Inverter` | `src/energyplus/ForwardTranslator/ForwardTranslateGeneratorFuelCellInverter.cpp` |
| `OS:Generator:FuelCell:PowerModule` | `GeneratorFuelCellPowerModule` | `ModelObject` | `Generator:FuelCell:PowerModule`, `OutdoorAir:NodeList` | `src/energyplus/ForwardTranslator/ForwardTranslateGeneratorFuelCellPowerModule.cpp` |
| `OS:Generator:FuelCell:StackCooler` | `GeneratorFuelCellStackCooler` | `StraightComponent` | `Generator:FuelCell:StackCooler` | `src/energyplus/ForwardTranslator/ForwardTranslateGeneratorFuelCellStackCooler.cpp` |
| `OS:Generator:FuelCell:WaterSupply` | `GeneratorFuelCellWaterSupply` | `ModelObject` | `Generator:FuelCell:WaterSupply` | `src/energyplus/ForwardTranslator/ForwardTranslateGeneratorFuelCellWaterSupply.cpp` |
| `OS:Generator:FuelSupply` | `GeneratorFuelSupply` | `ModelObject` | `Generator:FuelSupply` | `src/energyplus/ForwardTranslator/ForwardTranslateGeneratorFuelSupply.cpp` |
| `OS:Generator:MicroTurbine` | `GeneratorMicroTurbine` | `Generator` | `Generator:MicroTurbine` | `src/energyplus/ForwardTranslator/ForwardTranslateGeneratorMicroTurbine.cpp` |
| `OS:Generator:MicroTurbine:HeatRecovery` | `GeneratorMicroTurbineHeatRecovery` | `StraightComponent` |  |  |
| `OS:Generator:PVWatts` | `GeneratorPVWatts` | `Generator` | `Generator:PVWatts` | `src/energyplus/ForwardTranslator/ForwardTranslateGeneratorPVWatts.cpp` |
| `OS:Generator:Photovoltaic` | `GeneratorPhotovoltaic` | `Generator` | `Generator:Photovoltaic` | `src/energyplus/ForwardTranslator/ForwardTranslateGeneratorPhotovoltaic.cpp` |
| `OS:Generator:WindTurbine` | `GeneratorWindTurbine` | `Generator` | `Generator:WindTurbine` | `src/energyplus/ForwardTranslator/ForwardTranslateGeneratorWindTurbine.cpp` |
| `OS:Glare:Sensor` | `GlareSensor` | `SpaceItem` |  |  |
| `OS:GroundHeatExchanger:HorizontalTrench` | `GroundHeatExchangerHorizontalTrench` | `StraightComponent` | `GroundHeatExchanger:HorizontalTrench` | `src/energyplus/ForwardTranslator/ForwardTranslateGroundHeatExchangerHorizontalTrench.cpp` |
| `OS:GroundHeatExchanger:Vertical` | `GroundHeatExchangerVertical` | `StraightComponent` | `GroundHeatExchanger:ResponseFactors`, `GroundHeatExchanger:System`, `GroundHeatExchanger:Vertical:Properties` | `src/energyplus/ForwardTranslator/ForwardTranslateGroundHeatExchangerVertical.cpp` |
| `OS:HVACComponentList` | `` | `` |  |  |
| `OS:HeaderedPumps:ConstantSpeed` | `HeaderedPumpsConstantSpeed` | `StraightComponent` | `HeaderedPumps:ConstantSpeed` | `src/energyplus/ForwardTranslator/ForwardTranslateHeaderedPumpsConstantSpeed.cpp` |
| `OS:HeaderedPumps:VariableSpeed` | `HeaderedPumpsVariableSpeed` | `StraightComponent` | `HeaderedPumps:VariableSpeed` | `src/energyplus/ForwardTranslator/ForwardTranslateHeaderedPumpsVariableSpeed.cpp` |
| `OS:HeatBalanceAlgorithm` | `HeatBalanceAlgorithm` | `ModelObject` | `HeatBalanceAlgorithm` | `src/energyplus/ForwardTranslator/ForwardTranslateHeatBalanceAlgorithm.cpp` |
| `OS:HeatExchanger:AirToAir:SensibleAndLatent` | `HeatExchangerAirToAirSensibleAndLatent` | `AirToAirComponent` | `HeatExchanger:AirToAir:SensibleAndLatent` | `src/energyplus/ForwardTranslator/ForwardTranslateHeatExchangerAirToAirSensibleAndLatent.cpp` |
| `OS:HeatExchanger:Desiccant:BalancedFlow` | `HeatExchangerDesiccantBalancedFlow` | `AirToAirComponent` | `HeatExchanger:Desiccant:BalancedFlow` | `src/energyplus/ForwardTranslator/ForwardTranslateHeatExchangerDesiccantBalancedFlow.cpp` |
| `OS:HeatExchanger:Desiccant:BalancedFlow:PerformanceDataType1` | `HeatExchangerDesiccantBalancedFlowPerformanceDataType1` | `ResourceObject` | `HeatExchanger:Desiccant:BalancedFlow:PerformanceDataType1` | `src/energyplus/ForwardTranslator/ForwardTranslateHeatExchangerDesiccantBalancedFlowPerformanceDataType1.cpp` |
| `OS:HeatExchanger:FluidToFluid` | `HeatExchangerFluidToFluid` | `WaterToWaterComponent` | `HeatExchanger:FluidToFluid` | `src/energyplus/ForwardTranslator/ForwardTranslateHeatExchangerFluidToFluid.cpp` |
| `OS:HeatPump:AirToWater` | `HeatPumpAirToWater` | `StraightComponent` | `HeatPump:AirToWater`, `OutdoorAir:NodeList` | `src/energyplus/ForwardTranslator/ForwardTranslateHeatPumpAirToWater.cpp` |
| `OS:HeatPump:AirToWater:Cooling` | `HeatPumpAirToWaterCooling` | `StraightComponent` |  |  |
| `OS:HeatPump:AirToWater:Cooling:SpeedData` | `HeatPumpAirToWaterCoolingSpeedData` | `ResourceObject` |  |  |
| `OS:HeatPump:AirToWater:FuelFired:Cooling` | `HeatPumpAirToWaterFuelFiredCooling` | `StraightComponent` | `HeatPump:AirToWater:FuelFired:Cooling`, `OutdoorAir:Node` | `src/energyplus/ForwardTranslator/ForwardTranslateHeatPumpAirToWaterFuelFiredCooling.cpp` |
| `OS:HeatPump:AirToWater:FuelFired:Heating` | `HeatPumpAirToWaterFuelFiredHeating` | `StraightComponent` | `HeatPump:AirToWater:FuelFired:Heating`, `OutdoorAir:Node` | `src/energyplus/ForwardTranslator/ForwardTranslateHeatPumpAirToWaterFuelFiredHeating.cpp` |
| `OS:HeatPump:AirToWater:Heating` | `HeatPumpAirToWaterHeating` | `StraightComponent` |  |  |
| `OS:HeatPump:AirToWater:Heating:SpeedData` | `HeatPumpAirToWaterHeatingSpeedData` | `ResourceObject` |  |  |
| `OS:HeatPump:PlantLoop:EIR:Cooling` | `HeatPumpPlantLoopEIRCooling` | `WaterToWaterComponent` | `HeatPump:PlantLoop:EIR:Cooling`, `OutdoorAir:NodeList` | `src/energyplus/ForwardTranslator/ForwardTranslateHeatPumpPlantLoopEIRCooling.cpp` |
| `OS:HeatPump:PlantLoop:EIR:Heating` | `HeatPumpPlantLoopEIRHeating` | `WaterToWaterComponent` | `HeatPump:PlantLoop:EIR:Heating`, `OutdoorAir:NodeList` | `src/energyplus/ForwardTranslator/ForwardTranslateHeatPumpPlantLoopEIRHeating.cpp` |
| `OS:HeatPump:WaterToWater:EquationFit:Cooling` | `HeatPumpWaterToWaterEquationFitCooling` | `WaterToWaterComponent` | `HeatPump:WaterToWater:EquationFit:Cooling` | `src/energyplus/ForwardTranslator/ForwardTranslateHeatPumpWaterToWaterEquationFitCooling.cpp` |
| `OS:HeatPump:WaterToWater:EquationFit:Heating` | `HeatPumpWaterToWaterEquationFitHeating` | `WaterToWaterComponent` | `HeatPump:WaterToWater:EquationFit:Heating` | `src/energyplus/ForwardTranslator/ForwardTranslateHeatPumpWaterToWaterEquationFitHeating.cpp` |
| `OS:HotWaterEquipment` | `HotWaterEquipment` | `SpaceLoadInstance` | `HotWaterEquipment` | `src/energyplus/ForwardTranslator/ForwardTranslateHotWaterEquipment.cpp` |
| `OS:HotWaterEquipment:Definition` | `HotWaterEquipmentDefinition` | `SpaceLoadDefinition` |  |  |
| `OS:Humidifier:Steam:Electric` | `HumidifierSteamElectric` | `StraightComponent` | `Humidifier:Steam:Electric` | `src/energyplus/ForwardTranslator/ForwardTranslateHumidifierSteamElectric.cpp` |
| `OS:Humidifier:Steam:Gas` | `HumidifierSteamGas` | `StraightComponent` | `Humidifier:Steam:Gas` | `src/energyplus/ForwardTranslator/ForwardTranslateHumidifierSteamGas.cpp` |
| `OS:IlluminanceMap` | `IlluminanceMap` | `SpaceItem` |  | `src/energyplus/ForwardTranslator/ForwardTranslateIlluminanceMap.cpp` |
| `OS:InteriorPartitionSurface` | `InteriorPartitionSurface` | `PlanarSurface` | `InternalMass` | `src/energyplus/ForwardTranslator/ForwardTranslateInteriorPartitionSurface.cpp` |
| `OS:InteriorPartitionSurfaceGroup` | `InteriorPartitionSurfaceGroup` | `PlanarSurfaceGroup` |  | `src/energyplus/ForwardTranslator/ForwardTranslateInteriorPartitionSurfaceGroup.cpp` |
| `OS:InternalMass` | `InternalMass` | `SpaceLoadInstance` | `InternalMass` | `src/energyplus/ForwardTranslator/ForwardTranslateInternalMass.cpp` |
| `OS:InternalMass:Definition` | `InternalMassDefinition` | `SpaceLoadDefinition` |  |  |
| `OS:LifeCycleCost` | `LifeCycleCost` | `ModelObject` | `LifeCycleCost:NonrecurringCost`, `LifeCycleCost:RecurringCosts` | `src/energyplus/ForwardTranslator/ForwardTranslateLifeCycleCost.cpp` |
| `OS:LifeCycleCost:Parameters` | `LifeCycleCostParameters` | `ParentObject` | `LifeCycleCost:Parameters` | `src/energyplus/ForwardTranslator/ForwardTranslateLifeCycleCostParameters.cpp` |
| `OS:LifeCycleCost:UsePriceEscalation` | `LifeCycleCostUsePriceEscalation` | `ParentObject` |  |  |
| `OS:LightingDesignDay` | `LightingDesignDay` | `ModelObject` |  |  |
| `OS:LightingSimulationControl` | `LightingSimulationControl` | `ModelObject` |  |  |
| `OS:LightingSimulationZone` | `LightingSimulationZone` | `ModelObject` |  |  |
| `OS:Lights` | `Lights` | `SpaceLoadInstance` | `Lights` | `src/energyplus/ForwardTranslator/ForwardTranslateLights.cpp` |
| `OS:Lights:Definition` | `LightsDefinition` | `SpaceLoadDefinition` |  |  |
| `OS:LoadProfile:Plant` | `LoadProfilePlant` | `StraightComponent` | `LoadProfile:Plant` | `src/energyplus/ForwardTranslator/ForwardTranslateLoadProfilePlant.cpp` |
| `OS:Luminaire` | `Luminaire` | `SpaceLoadInstance` | `Lights` | `src/energyplus/ForwardTranslator/ForwardTranslateLuminaire.cpp` |
| `OS:Luminaire:Definition` | `LuminaireDefinition` | `SpaceLoadDefinition` |  |  |
| `OS:Material` | `StandardOpaqueMaterial` | `OpaqueMaterial` | `Material` | `src/energyplus/ForwardTranslator/ForwardTranslateStandardOpaqueMaterial.cpp` |
| `OS:Material:AirGap` | `AirGap` | `OpaqueMaterial` | `Material:AirGap` | `src/energyplus/ForwardTranslator/ForwardTranslateAirGap.cpp` |
| `OS:Material:InfraredTransparent` | `InfraredTransparentMaterial` | `ModelPartitionMaterial` | `Material:InfraredTransparent` | `src/energyplus/ForwardTranslator/ForwardTranslateInfraredTransparentMaterial.cpp` |
| `OS:Material:NoMass` | `MasslessOpaqueMaterial` | `OpaqueMaterial` | `Material:NoMass` | `src/energyplus/ForwardTranslator/ForwardTranslateMasslessOpaqueMaterial.cpp` |
| `OS:Material:RoofVegetation` | `RoofVegetation` | `OpaqueMaterial` | `Material:RoofVegetation` | `src/energyplus/ForwardTranslator/ForwardTranslateRoofVegetation.cpp` |
| `OS:MaterialProperty:GlazingSpectralData` | `MaterialPropertyGlazingSpectralData` | `ResourceObject` | `MaterialProperty:GlazingSpectralData` | `src/energyplus/ForwardTranslator/ForwardTranslateMaterialPropertyGlazingSpectralData.cpp` |
| `OS:MaterialProperty:MoisturePenetrationDepth:Settings` | `MaterialPropertyMoisturePenetrationDepthSettings` | `ModelObject` | `MaterialProperty:MoisturePenetrationDepth:Settings` | `src/energyplus/ForwardTranslator/ForwardTranslateMaterialPropertyMoisturePenetrationDepthSettings.cpp` |
| `OS:MaterialProperty:PhaseChange` | `MaterialPropertyPhaseChange` | `ModelObject` | `MaterialProperty:PhaseChange` | `src/energyplus/ForwardTranslator/ForwardTranslateMaterialPropertyPhaseChange.cpp` |
| `OS:MaterialProperty:PhaseChangeHysteresis` | `MaterialPropertyPhaseChangeHysteresis` | `ModelObject` | `MaterialProperty:PhaseChangeHysteresis` | `src/energyplus/ForwardTranslator/ForwardTranslateMaterialPropertyPhaseChangeHysteresis.cpp` |
| `OS:Meter:Custom` | `MeterCustom` | `ModelObject` | `Meter:Custom` | `src/energyplus/ForwardTranslator/ForwardTranslateMeterCustom.cpp` |
| `OS:Meter:CustomDecrement` | `MeterCustomDecrement` | `ModelObject` | `Meter:CustomDecrement` | `src/energyplus/ForwardTranslator/ForwardTranslateMeterCustomDecrement.cpp` |
| `OS:ModelObjectList` | `ModelObjectList` | `ModelObject` |  |  |
| `OS:Node` | `Node` | `StraightComponent` |  | `src/energyplus/ForwardTranslator/ForwardTranslateNode.cpp` |
| `OS:OtherEquipment` | `OtherEquipment` | `SpaceLoadInstance` | `OtherEquipment` | `src/energyplus/ForwardTranslator/ForwardTranslateOtherEquipment.cpp` |
| `OS:OtherEquipment:Definition` | `OtherEquipmentDefinition` | `SpaceLoadDefinition` |  |  |
| `OS:Output:Constructions` | `OutputConstructions` | `ModelObject` | `Output:Constructions` | `src/energyplus/ForwardTranslator/ForwardTranslateOutputConstructions.cpp` |
| `OS:Output:DebuggingData` | `OutputDebuggingData` | `ModelObject` | `Output:DebuggingData` | `src/energyplus/ForwardTranslator/ForwardTranslateOutputDebuggingData.cpp` |
| `OS:Output:Diagnostics` | `OutputDiagnostics` | `ModelObject` | `Output:Diagnostics` | `src/energyplus/ForwardTranslator/ForwardTranslateOutputDiagnostics.cpp` |
| `OS:Output:EnergyManagementSystem` | `OutputEnergyManagementSystem` | `ModelObject` | `Output:EnergyManagementSystem` | `src/energyplus/ForwardTranslator/ForwardTranslateOutputEnergyManagementSystem.cpp` |
| `OS:Output:EnvironmentalImpactFactors` | `OutputEnvironmentalImpactFactors` | `ModelObject` | `Output:EnvironmentalImpactFactors` | `src/energyplus/ForwardTranslator/ForwardTranslateOutputEnvironmentalImpactFactors.cpp` |
| `OS:Output:JSON` | `OutputJSON` | `ModelObject` | `Output:JSON` | `src/energyplus/ForwardTranslator/ForwardTranslateOutputJSON.cpp` |
| `OS:Output:Meter` | `OutputMeter` | `ModelObject` |  | `src/energyplus/ForwardTranslator/ForwardTranslateOutputMeter.cpp` |
| `OS:Output:SQLite` | `OutputSQLite` | `ModelObject` | `Output:SQLite` | `src/energyplus/ForwardTranslator/ForwardTranslateOutputSQLite.cpp` |
| `OS:Output:Schedules` | `OutputSchedules` | `ModelObject` | `Output:Schedules` | `src/energyplus/ForwardTranslator/ForwardTranslateOutputSchedules.cpp` |
| `OS:Output:Table:Annual` | `OutputTableAnnual` | `ModelObject` | `Output:Table:Annual` | `src/energyplus/ForwardTranslator/ForwardTranslateOutputTableAnnual.cpp` |
| `OS:Output:Table:Monthly` | `OutputTableMonthly` | `ModelObject` | `Output:Table:Monthly` | `src/energyplus/ForwardTranslator/ForwardTranslateOutputTableMonthly.cpp` |
| `OS:Output:Table:SummaryReports` | `OutputTableSummaryReports` | `ModelObject` | `Output:Table:SummaryReports` | `src/energyplus/ForwardTranslator/ForwardTranslateOutputTableSummaryReports.cpp` |
| `OS:Output:Variable` | `OutputVariable` | `ModelObject` | `Output:Variable` | `src/energyplus/ForwardTranslator/ForwardTranslateOutputVariable.cpp` |
| `OS:OutputControl:Files` | `OutputControlFiles` | `ModelObject` | `OutputControl:Files` | `src/energyplus/ForwardTranslator/ForwardTranslateOutputControlFiles.cpp` |
| `OS:OutputControl:ReportingTolerances` | `OutputControlReportingTolerances` | `ModelObject` | `OutputControl:ReportingTolerances` | `src/energyplus/ForwardTranslator/ForwardTranslateOutputControlReportingTolerances.cpp` |
| `OS:OutputControl:ResilienceSummaries` | `OutputControlResilienceSummaries` | `ModelObject` | `OutputControl:ResilienceSummaries` | `src/energyplus/ForwardTranslator/ForwardTranslateOutputControlResilienceSummaries.cpp` |
| `OS:OutputControl:Table:Style` | `OutputControlTableStyle` | `ModelObject` | `OutputControl:Table:Style` | `src/energyplus/ForwardTranslator/ForwardTranslateOutputControlTableStyle.cpp` |
| `OS:OutputControl:Timestamp` | `OutputControlTimestamp` | `ModelObject` | `OutputControl:Timestamp` | `src/energyplus/ForwardTranslator/ForwardTranslateOutputControlTimestamp.cpp` |
| `OS:People` | `People` | `SpaceLoadInstance` | `People` | `src/energyplus/ForwardTranslator/ForwardTranslatePeople.cpp` |
| `OS:People:Definition` | `PeopleDefinition` | `SpaceLoadDefinition` |  |  |
| `OS:PerformancePrecisionTradeoffs` | `PerformancePrecisionTradeoffs` | `ModelObject` | `PerformancePrecisionTradeoffs` | `src/energyplus/ForwardTranslator/ForwardTranslatePerformancePrecisionTradeoffs.cpp` |
| `OS:PhotovoltaicPerformance:Sandia` | `PhotovoltaicPerformanceSandia` | `PhotovoltaicPerformance` | `PhotovoltaicPerformance:Sandia` | `src/energyplus/ForwardTranslator/ForwardTranslatePhotovoltaicPerformanceSandia.cpp` |
| `OS:PhotovoltaicPerformance:Simple` | `PhotovoltaicPerformanceSimple` | `PhotovoltaicPerformance` | `PhotovoltaicPerformance:Simple` | `src/energyplus/ForwardTranslator/ForwardTranslatePhotovoltaicPerformanceSimple.cpp` |
| `OS:Pipe:Adiabatic` | `PipeAdiabatic` | `StraightComponent` | `Pipe:Adiabatic` | `src/energyplus/ForwardTranslator/ForwardTranslatePipeAdiabatic.cpp` |
| `OS:Pipe:Indoor` | `PipeIndoor` | `StraightComponent` | `Pipe:Indoor` | `src/energyplus/ForwardTranslator/ForwardTranslatePipeIndoor.cpp` |
| `OS:Pipe:Outdoor` | `PipeOutdoor` | `StraightComponent` | `OutdoorAir:NodeList`, `Pipe:Outdoor` | `src/energyplus/ForwardTranslator/ForwardTranslatePipeOutdoor.cpp` |
| `OS:PlantComponent:TemperatureSource` | `PlantComponentTemperatureSource` | `StraightComponent` | `PlantComponent:TemperatureSource` | `src/energyplus/ForwardTranslator/ForwardTranslatePlantComponentTemperatureSource.cpp` |
| `OS:PlantComponent:UserDefined` | `PlantComponentUserDefined` | `StraightComponent` | `PlantComponent:UserDefined` | `src/energyplus/ForwardTranslator/ForwardTranslatePlantComponentUserDefined.cpp` |
| `OS:PlantEquipmentOperation:CoolingLoad` | `PlantEquipmentOperationCoolingLoad` | `PlantEquipmentOperationRangeBasedScheme` | `PlantEquipmentList`, `PlantEquipmentOperation:CoolingLoad` | `src/energyplus/ForwardTranslator/ForwardTranslatePlantEquipmentOperationCoolingLoad.cpp` |
| `OS:PlantEquipmentOperation:HeatingLoad` | `PlantEquipmentOperationHeatingLoad` | `PlantEquipmentOperationRangeBasedScheme` | `PlantEquipmentList`, `PlantEquipmentOperation:HeatingLoad` | `src/energyplus/ForwardTranslator/ForwardTranslatePlantEquipmentOperationHeatingLoad.cpp` |
| `OS:PlantEquipmentOperation:OutdoorDewpoint` | `PlantEquipmentOperationOutdoorDewpoint` | `PlantEquipmentOperationRangeBasedScheme` | `PlantEquipmentList`, `PlantEquipmentOperation:OutdoorDewpoint` | `src/energyplus/ForwardTranslator/ForwardTranslatePlantEquipmentOperationOutdoorDewpoint.cpp` |
| `OS:PlantEquipmentOperation:OutdoorDewpointDifference` | `PlantEquipmentOperationOutdoorDewpointDifference` | `PlantEquipmentOperationRangeBasedScheme` | `PlantEquipmentList`, `PlantEquipmentOperation:OutdoorDewpointDifference` | `src/energyplus/ForwardTranslator/ForwardTranslatePlantEquipmentOperationOutdoorDewpointDifference.cpp` |
| `OS:PlantEquipmentOperation:OutdoorDryBulb` | `PlantEquipmentOperationOutdoorDryBulb` | `PlantEquipmentOperationRangeBasedScheme` | `PlantEquipmentList`, `PlantEquipmentOperation:OutdoorDryBulb` | `src/energyplus/ForwardTranslator/ForwardTranslatePlantEquipmentOperationOutdoorDryBulb.cpp` |
| `OS:PlantEquipmentOperation:OutdoorDryBulbDifference` | `PlantEquipmentOperationOutdoorDryBulbDifference` | `PlantEquipmentOperationRangeBasedScheme` | `PlantEquipmentList`, `PlantEquipmentOperation:OutdoorDryBulbDifference` | `src/energyplus/ForwardTranslator/ForwardTranslatePlantEquipmentOperationOutdoorDryBulbDifference.cpp` |
| `OS:PlantEquipmentOperation:OutdoorRelativeHumidity` | `PlantEquipmentOperationOutdoorRelativeHumidity` | `PlantEquipmentOperationRangeBasedScheme` | `PlantEquipmentList`, `PlantEquipmentOperation:OutdoorRelativeHumidity` | `src/energyplus/ForwardTranslator/ForwardTranslatePlantEquipmentOperationOutdoorRelativeHumidity.cpp` |
| `OS:PlantEquipmentOperation:OutdoorWetBulb` | `PlantEquipmentOperationOutdoorWetBulb` | `PlantEquipmentOperationRangeBasedScheme` | `PlantEquipmentList`, `PlantEquipmentOperation:OutdoorWetBulb` | `src/energyplus/ForwardTranslator/ForwardTranslatePlantEquipmentOperationOutdoorWetBulb.cpp` |
| `OS:PlantEquipmentOperation:OutdoorWetBulbDifference` | `PlantEquipmentOperationOutdoorWetBulbDifference` | `PlantEquipmentOperationRangeBasedScheme` | `PlantEquipmentList`, `PlantEquipmentOperation:OutdoorWetBulbDifference` | `src/energyplus/ForwardTranslator/ForwardTranslatePlantEquipmentOperationOutdoorWetBulbDifference.cpp` |
| `OS:PlantLoop` | `PlantLoop` | `Loop` | `Branch`, `BranchList`, `ConnectorList`, `Connector:Mixer`, `Connector:Splitter`, `Pipe:Adiabatic`, `PlantEquipmentList`, `PlantEquipmentOperationSchemes`, `PlantEquipmentOperation:ComponentSetpoint`, `PlantEquipmentOperation:CoolingLoad`, `PlantEquipmentOperation:HeatingLoad`, `PlantEquipmentOperation:Uncontrolled`, `PlantLoop` | `src/energyplus/ForwardTranslator/ForwardTranslatePlantEquipmentOperationSchemes.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslatePlantLoop.cpp` |
| `OS:PortList` | `PortList` | `ModelObject` | `NodeList` | `src/energyplus/ForwardTranslator/ForwardTranslatePortList.cpp` |
| `OS:ProgramControl` | `ProgramControl` | `ModelObject` |  |  |
| `OS:Pump:ConstantSpeed` | `PumpConstantSpeed` | `StraightComponent` | `Pump:ConstantSpeed` | `src/energyplus/ForwardTranslator/ForwardTranslatePumpConstantSpeed.cpp` |
| `OS:Pump:VariableSpeed` | `PumpVariableSpeed` | `StraightComponent` | `Pump:VariableSpeed` | `src/energyplus/ForwardTranslator/ForwardTranslatePumpVariableSpeed.cpp` |
| `OS:PythonPlugin:Instance` | `PythonPluginInstance` | `ResourceObject` | `PythonPlugin:Instance`, `PythonPlugin:SearchPaths` | `src/energyplus/ForwardTranslator/ForwardTranslatePythonPluginInstance.cpp` |
| `OS:PythonPlugin:OutputVariable` | `PythonPluginOutputVariable` | `ModelObject` | `PythonPlugin:OutputVariable` | `src/energyplus/ForwardTranslator/ForwardTranslatePythonPluginOutputVariable.cpp` |
| `OS:PythonPlugin:SearchPaths` | `PythonPluginSearchPaths` | `ModelObject` | `PythonPlugin:SearchPaths` | `src/energyplus/ForwardTranslator/ForwardTranslatePythonPluginSearchPaths.cpp` |
| `OS:PythonPlugin:TrendVariable` | `PythonPluginTrendVariable` | `ModelObject` | `PythonPlugin:TrendVariable` | `src/energyplus/ForwardTranslator/ForwardTranslatePythonPluginTrendVariable.cpp` |
| `OS:PythonPlugin:Variable` | `PythonPluginVariable` | `ModelObject` | `PythonPlugin:Variables` | `src/energyplus/ForwardTranslator/ForwardTranslatePythonPluginVariable.cpp` |
| `OS:RadianceParameters` | `RadianceParameters` | `ModelObject` |  |  |
| `OS:Refrigeration:AirChiller` | `RefrigerationAirChiller` | `ZoneHVACComponent` | `Refrigeration:AirChiller` | `src/energyplus/ForwardTranslator/ForwardTranslateRefrigerationAirChiller.cpp` |
| `OS:Refrigeration:Case` | `RefrigerationCase` | `ParentObject` | `Refrigeration:Case` | `src/energyplus/ForwardTranslator/ForwardTranslateRefrigerationCase.cpp` |
| `OS:Refrigeration:Compressor` | `RefrigerationCompressor` | `ParentObject` | `Refrigeration:Compressor` | `src/energyplus/ForwardTranslator/ForwardTranslateRefrigerationCompressor.cpp` |
| `OS:Refrigeration:CompressorRack` | `RefrigerationCompressorRack` | `StraightComponent` | `Refrigeration:CaseAndWalkInList`, `Refrigeration:CompressorRack` | `src/energyplus/ForwardTranslator/ForwardTranslateRefrigerationCompressorRack.cpp` |
| `OS:Refrigeration:Condenser:AirCooled` | `RefrigerationCondenserAirCooled` | `ParentObject` | `Refrigeration:Condenser:AirCooled` | `src/energyplus/ForwardTranslator/ForwardTranslateRefrigerationCondenserAirCooled.cpp` |
| `OS:Refrigeration:Condenser:Cascade` | `RefrigerationCondenserCascade` | `ModelObject` | `Refrigeration:Condenser:Cascade` | `src/energyplus/ForwardTranslator/ForwardTranslateRefrigerationCondenserCascade.cpp` |
| `OS:Refrigeration:Condenser:EvaporativeCooled` | `RefrigerationCondenserEvaporativeCooled` | `ParentObject` | `Refrigeration:Condenser:EvaporativeCooled` | `src/energyplus/ForwardTranslator/ForwardTranslateRefrigerationCondenserEvaporativeCooled.cpp` |
| `OS:Refrigeration:Condenser:WaterCooled` | `RefrigerationCondenserWaterCooled` | `StraightComponent` | `Refrigeration:Condenser:WaterCooled` | `src/energyplus/ForwardTranslator/ForwardTranslateRefrigerationCondenserWaterCooled.cpp` |
| `OS:Refrigeration:DefrostCycleParameters` | `RefrigerationDefrostCycleParameters` | `ModelObject` |  |  |
| `OS:Refrigeration:GasCooler:AirCooled` | `RefrigerationGasCoolerAirCooled` | `ParentObject` | `Refrigeration:GasCooler:AirCooled` | `src/energyplus/ForwardTranslator/ForwardTranslateRefrigerationGasCoolerAirCooled.cpp` |
| `OS:Refrigeration:SecondarySystem` | `RefrigerationSecondarySystem` | `ParentObject` | `Refrigeration:CaseAndWalkInList`, `Refrigeration:SecondarySystem` | `src/energyplus/ForwardTranslator/ForwardTranslateRefrigerationSecondarySystem.cpp` |
| `OS:Refrigeration:Subcooler:LiquidSuction` | `RefrigerationSubcoolerLiquidSuction` | `ModelObject` | `Refrigeration:Subcooler` | `src/energyplus/ForwardTranslator/ForwardTranslateRefrigerationSubcoolerLiquidSuction.cpp` |
| `OS:Refrigeration:Subcooler:Mechanical` | `RefrigerationSubcoolerMechanical` | `ModelObject` | `Refrigeration:Subcooler` | `src/energyplus/ForwardTranslator/ForwardTranslateRefrigerationSubcoolerMechanical.cpp` |
| `OS:Refrigeration:System` | `RefrigerationSystem` | `ModelObject` | `Refrigeration:CaseAndWalkInList`, `Refrigeration:CompressorList`, `Refrigeration:System`, `Refrigeration:TransferLoadList` | `src/energyplus/ForwardTranslator/ForwardTranslateRefrigerationSystem.cpp` |
| `OS:Refrigeration:TranscriticalSystem` | `RefrigerationTranscriticalSystem` | `ModelObject` | `Refrigeration:CaseAndWalkInList`, `Refrigeration:CompressorList`, `Refrigeration:TranscriticalSystem` | `src/energyplus/ForwardTranslator/ForwardTranslateRefrigerationTranscriticalSystem.cpp` |
| `OS:Refrigeration:WalkIn` | `RefrigerationWalkIn` | `ModelObject` | `Refrigeration:WalkIn` | `src/energyplus/ForwardTranslator/ForwardTranslateRefrigerationWalkIn.cpp` |
| `OS:Refrigeration:WalkIn:ZoneBoundary` | `RefrigerationWalkInZoneBoundary` | `ModelObject` |  |  |
| `OS:Rendering:Color` | `RenderingColor` | `ResourceObject` |  |  |
| `OS:RunPeriod` | `RunPeriod` | `ParentObject` | `RunPeriod` | `src/energyplus/ForwardTranslator/ForwardTranslateRunPeriod.cpp` |
| `OS:RunPeriodControl:DaylightSavingTime` | `RunPeriodControlDaylightSavingTime` | `ModelObject` | `RunPeriodControl:DaylightSavingTime` | `src/energyplus/ForwardTranslator/ForwardTranslateRunPeriodControlDaylightSavingTime.cpp` |
| `OS:RunPeriodControl:SpecialDays` | `RunPeriodControlSpecialDays` | `ModelObject` | `RunPeriodControl:SpecialDays` | `src/energyplus/ForwardTranslator/ForwardTranslateRunPeriodControlSpecialDays.cpp` |
| `OS:Schedule:Compact` | `ScheduleCompact` | `Schedule` | `Schedule:Compact` | `src/energyplus/ForwardTranslator/ForwardTranslateScheduleCompact.cpp` |
| `OS:Schedule:Constant` | `ScheduleConstant` | `Schedule` | `Schedule:Constant` | `src/energyplus/ForwardTranslator/ForwardTranslateScheduleConstant.cpp` |
| `OS:Schedule:Day` | `ScheduleDay` | `ScheduleBase` | `Schedule:Day:Interval` | `src/energyplus/ForwardTranslator/ForwardTranslateScheduleDay.cpp` |
| `OS:Schedule:File` | `ScheduleFile` | `ScheduleInterval` | `Schedule:File` | `src/energyplus/ForwardTranslator/ForwardTranslateScheduleFile.cpp` |
| `OS:Schedule:FixedInterval` | `ScheduleFixedInterval` | `ScheduleInterval` | `Schedule:Compact` | `src/energyplus/ForwardTranslator/ForwardTranslateScheduleFixedInterval.cpp` |
| `OS:Schedule:Rule` | `ScheduleRule` | `ParentObject` |  |  |
| `OS:Schedule:Ruleset` | `ScheduleRuleset` | `Schedule` | `Schedule:Year` | `src/energyplus/ForwardTranslator/ForwardTranslateScheduleRuleset.cpp` |
| `OS:Schedule:VariableInterval` | `ScheduleVariableInterval` | `ScheduleInterval` | `Schedule:Compact` | `src/energyplus/ForwardTranslator/ForwardTranslateScheduleVariableInterval.cpp` |
| `OS:Schedule:Week` | `ScheduleWeek` | `ResourceObject` | `Schedule:Week:Daily` | `src/energyplus/ForwardTranslator/ForwardTranslateScheduleWeek.cpp` |
| `OS:Schedule:Year` | `ScheduleYear` | `Schedule` | `Schedule:Year` | `src/energyplus/ForwardTranslator/ForwardTranslateScheduleYear.cpp` |
| `OS:ScheduleTypeLimits` | `ScheduleTypeLimits` | `ResourceObject` | `ScheduleTypeLimits` | `src/energyplus/ForwardTranslator/ForwardTranslateScheduleTypeLimits.cpp` |
| `OS:SetpointManager:Coldest` | `SetpointManagerColdest` | `SetpointManager` | `SetpointManager:Coldest` | `src/energyplus/ForwardTranslator/ForwardTranslateSetpointManagerColdest.cpp` |
| `OS:SetpointManager:FollowGroundTemperature` | `SetpointManagerFollowGroundTemperature` | `SetpointManager` | `SetpointManager:FollowGroundTemperature` | `src/energyplus/ForwardTranslator/ForwardTranslateSetpointManagerFollowGroundTemperature.cpp` |
| `OS:SetpointManager:FollowOutdoorAirTemperature` | `SetpointManagerFollowOutdoorAirTemperature` | `SetpointManager` | `SetpointManager:FollowOutdoorAirTemperature` | `src/energyplus/ForwardTranslator/ForwardTranslateSetpointManagerFollowOutdoorAirTemperature.cpp` |
| `OS:SetpointManager:FollowSystemNodeTemperature` | `SetpointManagerFollowSystemNodeTemperature` | `SetpointManager` | `SetpointManager:FollowSystemNodeTemperature` | `src/energyplus/ForwardTranslator/ForwardTranslateSetpointManagerFollowSystemNodeTemperature.cpp` |
| `OS:SetpointManager:MixedAir` | `SetpointManagerMixedAir` | `SetpointManager` | `SetpointManager:MixedAir` | `src/energyplus/ForwardTranslator/ForwardTranslateSetpointManagerMixedAir.cpp` |
| `OS:SetpointManager:MultiZone:Cooling:Average` | `SetpointManagerMultiZoneCoolingAverage` | `SetpointManager` | `SetpointManager:MultiZone:Cooling:Average` | `src/energyplus/ForwardTranslator/ForwardTranslateSetpointManagerMultiZoneCoolingAverage.cpp` |
| `OS:SetpointManager:MultiZone:Heating:Average` | `SetpointManagerMultiZoneHeatingAverage` | `SetpointManager` | `SetpointManager:MultiZone:Heating:Average` | `src/energyplus/ForwardTranslator/ForwardTranslateSetpointManagerMultiZoneHeatingAverage.cpp` |
| `OS:SetpointManager:MultiZone:Humidity:Maximum` | `SetpointManagerMultiZoneHumidityMaximum` | `SetpointManager` | `SetpointManager:MultiZone:Humidity:Maximum` | `src/energyplus/ForwardTranslator/ForwardTranslateSetpointManagerMultiZoneHumidityMaximum.cpp` |
| `OS:SetpointManager:MultiZone:Humidity:Minimum` | `SetpointManagerMultiZoneHumidityMinimum` | `SetpointManager` | `SetpointManager:MultiZone:Humidity:Minimum` | `src/energyplus/ForwardTranslator/ForwardTranslateSetpointManagerMultiZoneHumidityMinimum.cpp` |
| `OS:SetpointManager:MultiZone:MaximumHumidity:Average` | `SetpointManagerMultiZoneMaximumHumidityAverage` | `SetpointManager` | `SetpointManager:MultiZone:MaximumHumidity:Average` | `src/energyplus/ForwardTranslator/ForwardTranslateSetpointManagerMultiZoneMaximumHumidityAverage.cpp` |
| `OS:SetpointManager:MultiZone:MinimumHumidity:Average` | `SetpointManagerMultiZoneMinimumHumidityAverage` | `SetpointManager` | `SetpointManager:MultiZone:MinimumHumidity:Average` | `src/energyplus/ForwardTranslator/ForwardTranslateSetpointManagerMultiZoneMinimumHumidityAverage.cpp` |
| `OS:SetpointManager:OutdoorAirPretreat` | `SetpointManagerOutdoorAirPretreat` | `SetpointManager` | `SetpointManager:OutdoorAirPretreat` | `src/energyplus/ForwardTranslator/ForwardTranslateSetpointManagerOutdoorAirPretreat.cpp` |
| `OS:SetpointManager:OutdoorAirReset` | `SetpointManagerOutdoorAirReset` | `SetpointManager` | `SetpointManager:OutdoorAirReset` | `src/energyplus/ForwardTranslator/ForwardTranslateSetpointManagerOutdoorAirReset.cpp` |
| `OS:SetpointManager:Scheduled` | `SetpointManagerScheduled` | `SetpointManager` | `SetpointManager:Scheduled` | `src/energyplus/ForwardTranslator/ForwardTranslateSetpointManagerScheduled.cpp` |
| `OS:SetpointManager:Scheduled:DualSetpoint` | `SetpointManagerScheduledDualSetpoint` | `SetpointManager` | `SetpointManager:Scheduled:DualSetpoint` | `src/energyplus/ForwardTranslator/ForwardTranslateSetpointManagerScheduledDualSetpoint.cpp` |
| `OS:SetpointManager:SingleZone:Cooling` | `SetpointManagerSingleZoneCooling` | `SetpointManager` | `SetpointManager:SingleZone:Cooling` | `src/energyplus/ForwardTranslator/ForwardTranslateSetpointManagerSingleZoneCooling.cpp` |
| `OS:SetpointManager:SingleZone:Heating` | `SetpointManagerSingleZoneHeating` | `SetpointManager` | `SetpointManager:SingleZone:Heating` | `src/energyplus/ForwardTranslator/ForwardTranslateSetpointManagerSingleZoneHeating.cpp` |
| `OS:SetpointManager:SingleZone:Humidity:Maximum` | `SetpointManagerSingleZoneHumidityMaximum` | `SetpointManager` | `SetpointManager:SingleZone:Humidity:Maximum` | `src/energyplus/ForwardTranslator/ForwardTranslateSetpointManagerSingleZoneHumidityMaximum.cpp` |
| `OS:SetpointManager:SingleZone:Humidity:Minimum` | `SetpointManagerSingleZoneHumidityMinimum` | `SetpointManager` | `SetpointManager:SingleZone:Humidity:Minimum` | `src/energyplus/ForwardTranslator/ForwardTranslateSetpointManagerSingleZoneHumidityMinimum.cpp` |
| `OS:SetpointManager:SingleZone:OneStageCooling` | `SetpointManagerSingleZoneOneStageCooling` | `SetpointManager` | `SetpointManager:SingleZone:OneStageCooling` | `src/energyplus/ForwardTranslator/ForwardTranslateSetpointManagerSingleZoneOneStageCooling.cpp` |
| `OS:SetpointManager:SingleZone:OneStageHeating` | `SetpointManagerSingleZoneOneStageHeating` | `SetpointManager` | `SetpointManager:SingleZone:OneStageHeating` | `src/energyplus/ForwardTranslator/ForwardTranslateSetpointManagerSingleZoneOneStageHeating.cpp` |
| `OS:SetpointManager:SingleZone:Reheat` | `SetpointManagerSingleZoneReheat` | `SetpointManager` | `SetpointManager:SingleZone:Reheat` | `src/energyplus/ForwardTranslator/ForwardTranslateSetpointManagerSingleZoneReheat.cpp` |
| `OS:SetpointManager:SystemNodeReset:Humidity` | `SetpointManagerSystemNodeResetHumidity` | `SetpointManager` | `SetpointManager:SystemNodeReset:Humidity` | `src/energyplus/ForwardTranslator/ForwardTranslateSetpointManagerSystemNodeResetHumidity.cpp` |
| `OS:SetpointManager:SystemNodeReset:Temperature` | `SetpointManagerSystemNodeResetTemperature` | `SetpointManager` | `SetpointManager:SystemNodeReset:Temperature` | `src/energyplus/ForwardTranslator/ForwardTranslateSetpointManagerSystemNodeResetTemperature.cpp` |
| `OS:SetpointManager:Warmest` | `SetpointManagerWarmest` | `SetpointManager` | `SetpointManager:Warmest` | `src/energyplus/ForwardTranslator/ForwardTranslateSetpointManagerWarmest.cpp` |
| `OS:SetpointManager:WarmestTemperatureFlow` | `SetpointManagerWarmestTemperatureFlow` | `SetpointManager` | `SetpointManager:WarmestTemperatureFlow` | `src/energyplus/ForwardTranslator/ForwardTranslateSetpointManagerWarmestTemperatureFlow.cpp` |
| `OS:ShadingControl` | `ShadingControl` | `ResourceObject` | `WindowShadingControl` | `src/energyplus/ForwardTranslator/ForwardTranslateShadingControl.cpp` |
| `OS:ShadingSurface` | `ShadingSurface` | `PlanarSurface` |  | `src/energyplus/ForwardTranslator/ForwardTranslateShadingSurface.cpp` |
| `OS:ShadingSurfaceGroup` | `ShadingSurfaceGroup` | `PlanarSurfaceGroup` |  | `src/energyplus/ForwardTranslator/ForwardTranslateShadingSurfaceGroup.cpp` |
| `OS:ShadowCalculation` | `ShadowCalculation` | `ModelObject` | `ShadowCalculation`, `ZoneList` | `src/energyplus/ForwardTranslator/ForwardTranslateShadowCalculation.cpp` |
| `OS:SimulationControl` | `SimulationControl` | `ParentObject` | `SimulationControl` | `src/energyplus/ForwardTranslator/ForwardTranslateSimulationControl.cpp` |
| `OS:Site` | `Site` | `ParentObject` | `Site:Location` | `src/energyplus/ForwardTranslator/ForwardTranslateSite.cpp` |
| `OS:Site:GroundReflectance` | `SiteGroundReflectance` | `ModelObject` | `Site:GroundReflectance` | `src/energyplus/ForwardTranslator/ForwardTranslateSiteGroundReflectance.cpp` |
| `OS:Site:GroundTemperature:BuildingSurface` | `SiteGroundTemperatureBuildingSurface` | `ModelObject` | `Site:GroundTemperature:BuildingSurface` | `src/energyplus/ForwardTranslator/ForwardTranslateSiteGroundTemperatureBuildingSurface.cpp` |
| `OS:Site:GroundTemperature:Deep` | `SiteGroundTemperatureDeep` | `ModelObject` | `Site:GroundTemperature:Deep` | `src/energyplus/ForwardTranslator/ForwardTranslateSiteGroundTemperatureDeep.cpp` |
| `OS:Site:GroundTemperature:FCfactorMethod` | `SiteGroundTemperatureFCfactorMethod` | `ModelObject` | `Site:GroundTemperature:FCfactorMethod` | `src/energyplus/ForwardTranslator/ForwardTranslateSiteGroundTemperatureFCfactorMethod.cpp` |
| `OS:Site:GroundTemperature:Shallow` | `SiteGroundTemperatureShallow` | `ModelObject` | `Site:GroundTemperature:Shallow` | `src/energyplus/ForwardTranslator/ForwardTranslateSiteGroundTemperatureShallow.cpp` |
| `OS:Site:GroundTemperature:Undisturbed:KusudaAchenbach` | `SiteGroundTemperatureUndisturbedKusudaAchenbach` | `ModelObject` | `Site:GroundTemperature:Undisturbed:KusudaAchenbach` | `src/energyplus/ForwardTranslator/ForwardTranslateSiteGroundTemperatureUndisturbedKusudaAchenbach.cpp` |
| `OS:Site:GroundTemperature:Undisturbed:Xing` | `SiteGroundTemperatureUndisturbedXing` | `ModelObject` | `Site:GroundTemperature:Undisturbed:Xing` | `src/energyplus/ForwardTranslator/ForwardTranslateSiteGroundTemperatureUndisturbedXing.cpp` |
| `OS:Site:WaterMainsTemperature` | `SiteWaterMainsTemperature` | `ModelObject` | `Site:WaterMainsTemperature` | `src/energyplus/ForwardTranslator/ForwardTranslateSiteWaterMainsTemperature.cpp` |
| `OS:Sizing:Parameters` | `SizingParameters` | `ModelObject` | `Sizing:Parameters` | `src/energyplus/ForwardTranslator/ForwardTranslateSizingParameters.cpp` |
| `OS:Sizing:Plant` | `SizingPlant` | `ModelObject` | `Sizing:Plant` | `src/energyplus/ForwardTranslator/ForwardTranslateSizingPlant.cpp` |
| `OS:Sizing:System` | `SizingSystem` | `ModelObject` | `Sizing:System` | `src/energyplus/ForwardTranslator/ForwardTranslateSizingSystem.cpp` |
| `OS:Sizing:Zone` | `SizingZone` | `ModelObject` | `DesignSpecification:ZoneAirDistribution`, `Sizing:Zone` | `src/energyplus/ForwardTranslator/ForwardTranslateSizingZone.cpp` |
| `OS:SizingPeriod:DesignDay` | `DesignDay` | `SizingPeriod` | `SizingPeriod:DesignDay` | `src/energyplus/ForwardTranslator/ForwardTranslateDesignDay.cpp` |
| `OS:SizingPeriod:WeatherFileConditionType` | `WeatherFileConditionType` | `SizingPeriod` |  |  |
| `OS:SizingPeriod:WeatherFileDays` | `WeatherFileDays` | `SizingPeriod` |  |  |
| `OS:SolarCollector:FlatPlate:PhotovoltaicThermal` | `SolarCollectorFlatPlatePhotovoltaicThermal` | `StraightComponent` | `SolarCollector:FlatPlate:PhotovoltaicThermal` | `src/energyplus/ForwardTranslator/ForwardTranslateSolarCollectorFlatPlatePhotovoltaicThermal.cpp` |
| `OS:SolarCollector:FlatPlate:Water` | `SolarCollectorFlatPlateWater` | `StraightComponent` | `SolarCollector:FlatPlate:Water` | `src/energyplus/ForwardTranslator/ForwardTranslateSolarCollectorFlatPlateWater.cpp` |
| `OS:SolarCollector:IntegralCollectorStorage` | `SolarCollectorIntegralCollectorStorage` | `StraightComponent` | `SolarCollector:IntegralCollectorStorage` | `src/energyplus/ForwardTranslator/ForwardTranslateSolarCollectorIntegralCollectorStorage.cpp` |
| `OS:SolarCollectorPerformance:FlatPlate` | `SolarCollectorPerformanceFlatPlate` | `ModelObject` | `SolarCollectorPerformance:FlatPlate` | `src/energyplus/ForwardTranslator/ForwardTranslateSolarCollectorPerformanceFlatPlate.cpp` |
| `OS:SolarCollectorPerformance:IntegralCollectorStorage` | `SolarCollectorPerformanceIntegralCollectorStorage` | `ModelObject` | `SolarCollectorPerformance:IntegralCollectorStorage` | `src/energyplus/ForwardTranslator/ForwardTranslateSolarCollectorPerformanceIntegralCollectorStorage.cpp` |
| `OS:SolarCollectorPerformance:PhotovoltaicThermal:BIPVT` | `SolarCollectorPerformancePhotovoltaicThermalBIPVT` | `ModelObject` | `SolarCollectorPerformance:PhotovoltaicThermal:BIPVT` | `src/energyplus/ForwardTranslator/ForwardTranslateSolarCollectorPerformancePhotovoltaicThermalBIPVT.cpp` |
| `OS:SolarCollectorPerformance:PhotovoltaicThermal:Simple` | `SolarCollectorPerformancePhotovoltaicThermalSimple` | `ModelObject` | `SolarCollectorPerformance:PhotovoltaicThermal:Simple` | `src/energyplus/ForwardTranslator/ForwardTranslateSolarCollectorPerformancePhotovoltaicThermalSimple.cpp` |
| `OS:Space` | `Space` | `PlanarSurfaceGroup` | `Space` | `src/energyplus/ForwardTranslator/ForwardTranslateSpace.cpp` |
| `OS:SpaceInfiltration:DesignFlowRate` | `SpaceInfiltrationDesignFlowRate` | `SpaceLoad` | `ZoneInfiltration:DesignFlowRate` | `src/energyplus/ForwardTranslator/ForwardTranslateSpaceInfiltrationDesignFlowRate.cpp` |
| `OS:SpaceInfiltration:EffectiveLeakageArea` | `SpaceInfiltrationEffectiveLeakageArea` | `SpaceLoad` | `ZoneInfiltration:EffectiveLeakageArea` | `src/energyplus/ForwardTranslator/ForwardTranslateSpaceInfiltrationEffectiveLeakageArea.cpp` |
| `OS:SpaceInfiltration:FlowCoefficient` | `SpaceInfiltrationFlowCoefficient` | `SpaceLoad` | `ZoneInfiltration:FlowCoefficient` | `src/energyplus/ForwardTranslator/ForwardTranslateSpaceInfiltrationFlowCoefficient.cpp` |
| `OS:SpaceType` | `SpaceType` | `ResourceObject` | `SpaceList`, `ZoneList` | `src/energyplus/ForwardTranslator/ForwardTranslateSpaceType.cpp` |
| `OS:Splitter` | `` | `` |  |  |
| `OS:StandardsInformation:Construction` | `StandardsInformationConstruction` | `ModelObject` |  |  |
| `OS:StandardsInformation:Material` | `StandardsInformationMaterial` | `ModelObject` |  |  |
| `OS:SteamEquipment` | `SteamEquipment` | `SpaceLoadInstance` | `SteamEquipment` | `src/energyplus/ForwardTranslator/ForwardTranslateSteamEquipment.cpp` |
| `OS:SteamEquipment:Definition` | `SteamEquipmentDefinition` | `SpaceLoadDefinition` |  |  |
| `OS:SubSurface` | `SubSurface` | `PlanarSurface` | `FenestrationSurface:Detailed` | `src/energyplus/ForwardTranslator/ForwardTranslateSubSurface.cpp` |
| `OS:Surface` | `Surface` | `PlanarSurface` | `BuildingSurface:Detailed` | `src/energyplus/ForwardTranslator/ForwardTranslateSurface.cpp` |
| `OS:SurfaceControl:MovableInsulation` | `SurfaceControlMovableInsulation` | `ModelObject` | `SurfaceControl:MovableInsulation` | `src/energyplus/ForwardTranslator/ForwardTranslateSurfaceControlMovableInsulation.cpp` |
| `OS:SurfaceConvectionAlgorithm:Inside` | `InsideSurfaceConvectionAlgorithm` | `ModelObject` | `SurfaceConvectionAlgorithm:Inside` | `src/energyplus/ForwardTranslator/ForwardTranslateInsideSurfaceConvectionAlgorithm.cpp` |
| `OS:SurfaceConvectionAlgorithm:Outside` | `OutsideSurfaceConvectionAlgorithm` | `ModelObject` | `SurfaceConvectionAlgorithm:Outside` | `src/energyplus/ForwardTranslator/ForwardTranslateOutsideSurfaceConvectionAlgorithm.cpp` |
| `OS:SurfaceProperty:ConvectionCoefficients` | `SurfacePropertyConvectionCoefficients` | `ModelObject` | `SurfaceProperty:ConvectionCoefficients` | `src/energyplus/ForwardTranslator/ForwardTranslateSurfacePropertyConvectionCoefficients.cpp` |
| `OS:SurfaceProperty:ConvectionCoefficients:MultipleSurface` | `SurfacePropertyConvectionCoefficientsMultipleSurface` | `ModelObject` | `SurfaceProperty:ConvectionCoefficients:MultipleSurface` | `src/energyplus/ForwardTranslator/ForwardTranslateSurfacePropertyConvectionCoefficientsMultipleSurface.cpp` |
| `OS:SurfaceProperty:ExposedFoundationPerimeter` | `SurfacePropertyExposedFoundationPerimeter` | `ModelObject` | `SurfaceProperty:ExposedFoundationPerimeter` | `src/energyplus/ForwardTranslator/ForwardTranslateSurfacePropertyExposedFoundationPerimeter.cpp` |
| `OS:SurfaceProperty:GroundSurfaces` | `SurfacePropertyGroundSurfaces` | `ModelObject` | `SurfaceProperty:GroundSurfaces` | `src/energyplus/ForwardTranslator/ForwardTranslateSurfacePropertyGroundSurfaces.cpp` |
| `OS:SurfaceProperty:IncidentSolarMultiplier` | `SurfacePropertyIncidentSolarMultiplier` | `ModelObject` | `SurfaceProperty:IncidentSolarMultiplier` | `src/energyplus/ForwardTranslator/ForwardTranslateSurfacePropertyIncidentSolarMultiplier.cpp` |
| `OS:SurfaceProperty:LocalEnvironment` | `SurfacePropertyLocalEnvironment` | `ModelObject` | `SurfaceProperty:LocalEnvironment` | `src/energyplus/ForwardTranslator/ForwardTranslateSurfacePropertyLocalEnvironment.cpp` |
| `OS:SurfaceProperty:OtherSideCoefficients` | `SurfacePropertyOtherSideCoefficients` | `ResourceObject` | `SurfaceProperty:OtherSideCoefficients` | `src/energyplus/ForwardTranslator/ForwardTranslateSurfacePropertyOtherSideCoefficients.cpp` |
| `OS:SurfaceProperty:OtherSideConditionsModel` | `SurfacePropertyOtherSideConditionsModel` | `ResourceObject` | `SurfaceProperty:OtherSideConditionsModel` | `src/energyplus/ForwardTranslator/ForwardTranslateSurfacePropertyOtherSideConditionsModel.cpp` |
| `OS:SurfaceProperty:SurroundingSurfaces` | `SurfacePropertySurroundingSurfaces` | `ModelObject` | `SurfaceProperty:SurroundingSurfaces` | `src/energyplus/ForwardTranslator/ForwardTranslateSurfacePropertySurroundingSurfaces.cpp` |
| `OS:SwimmingPool:Indoor` | `SwimmingPoolIndoor` | `StraightComponent` | `SwimmingPool:Indoor` | `src/energyplus/ForwardTranslator/ForwardTranslateSwimmingPoolIndoor.cpp` |
| `OS:Table:IndependentVariable` | `TableIndependentVariable` | `ResourceObject` | `Table:IndependentVariable` | `src/energyplus/ForwardTranslator/ForwardTranslateTableIndependentVariable.cpp` |
| `OS:Table:Lookup` | `TableLookup` | `Curve` | `Table:IndependentVariableList`, `Table:Lookup` | `src/energyplus/ForwardTranslator/ForwardTranslateTableLookup.cpp` |
| `OS:Table:MultiVariableLookup` | `TableMultiVariableLookup` | `` | `Table:IndependentVariable`, `Table:IndependentVariableList`, `Table:Lookup` | `src/energyplus/ForwardTranslator/ForwardTranslateTableMultiVariableLookup.cpp` |
| `OS:TemperingValve` | `TemperingValve` | `StraightComponent` | `TemperingValve` | `src/energyplus/ForwardTranslator/ForwardTranslateTemperingValve.cpp` |
| `OS:ThermalStorage:ChilledWater:Stratified` | `ThermalStorageChilledWaterStratified` | `WaterToWaterComponent` | `OutdoorAir:NodeList`, `ThermalStorage:ChilledWater:Stratified` | `src/energyplus/ForwardTranslator/ForwardTranslateThermalStorageChilledWaterStratified.cpp` |
| `OS:ThermalStorage:Ice:Detailed` | `ThermalStorageIceDetailed` | `StraightComponent` | `ThermalStorage:Ice:Detailed` | `src/energyplus/ForwardTranslator/ForwardTranslateThermalStorageIceDetailed.cpp` |
| `OS:ThermalZone` | `ThermalZone` | `HVACComponent` | `Daylighting:Controls`, `Daylighting:ReferencePoint`, `DesignSpecification:OutdoorAir`, `HVACTemplate:Zone:IdealLoadsAirSystem`, `Output:IlluminanceMap`, `ScheduleTypeLimits`, `Schedule:Compact`, `Zone`, `ZoneControl:Thermostat`, `ZoneHVAC:EquipmentConnections`, `ZoneVentilation:DesignFlowRate` | `src/energyplus/ForwardTranslator/ForwardTranslateThermalZone.cpp` |
| `OS:ThermostatSetpoint:DualSetpoint` | `ThermostatSetpointDualSetpoint` | `Thermostat` | `ThermostatSetpoint:DualSetpoint`, `ThermostatSetpoint:SingleCooling`, `ThermostatSetpoint:SingleHeating` | `src/energyplus/ForwardTranslator/ForwardTranslateThermostatSetpointDualSetpoint.cpp` |
| `OS:Timestep` | `Timestep` | `ModelObject` | `Timestep` | `src/energyplus/ForwardTranslator/ForwardTranslateTimestep.cpp` |
| `OS:UnitarySystemPerformance:Multispeed` | `UnitarySystemPerformanceMultispeed` | `ModelObject` | `UnitarySystemPerformance:Multispeed` | `src/energyplus/ForwardTranslator/ForwardTranslateUnitarySystemPerformanceMultispeed.cpp` |
| `OS:UtilityBill` | `UtilityBill` | `ModelObject` |  |  |
| `OS:UtilityCost:Charge:Block` | `` | `` |  |  |
| `OS:UtilityCost:Charge:Simple` | `` | `` |  |  |
| `OS:UtilityCost:Computation` | `` | `` |  |  |
| `OS:UtilityCost:Qualify` | `` | `` |  |  |
| `OS:UtilityCost:Ratchet` | `` | `` |  |  |
| `OS:UtilityCost:Tariff` | `` | `` |  |  |
| `OS:UtilityCost:Variable` | `` | `` |  |  |
| `OS:Version` | `Version` | `ModelObject` | `Version` | `src/energyplus/ForwardTranslator/ForwardTranslateVersion.cpp` |
| `OS:WaterHeater:HeatPump` | `WaterHeaterHeatPump` | `ZoneHVACComponent` | `WaterHeater:HeatPump:PumpedCondenser` | `src/energyplus/ForwardTranslator/ForwardTranslateWaterHeaterHeatPump.cpp` |
| `OS:WaterHeater:HeatPump:WrappedCondenser` | `WaterHeaterHeatPumpWrappedCondenser` | `ZoneHVACComponent` | `WaterHeater:HeatPump:WrappedCondenser` | `src/energyplus/ForwardTranslator/ForwardTranslateWaterHeaterHeatPumpWrappedCondenser.cpp` |
| `OS:WaterHeater:Mixed` | `WaterHeaterMixed` | `WaterToWaterComponent` | `OutdoorAir:NodeList`, `WaterHeater:Mixed` | `src/energyplus/ForwardTranslator/ForwardTranslateWaterHeaterMixed.cpp` |
| `OS:WaterHeater:Sizing` | `WaterHeaterSizing` | `ModelObject` | `WaterHeater:Sizing` | `src/energyplus/ForwardTranslator/ForwardTranslateWaterHeaterSizing.cpp` |
| `OS:WaterHeater:Stratified` | `WaterHeaterStratified` | `WaterToWaterComponent` | `WaterHeater:Stratified` | `src/energyplus/ForwardTranslator/ForwardTranslateWaterHeaterStratified.cpp` |
| `OS:WaterUse:Connections` | `WaterUseConnections` | `StraightComponent` | `WaterUse:Connections` | `src/energyplus/ForwardTranslator/ForwardTranslateWaterUseConnections.cpp` |
| `OS:WaterUse:Equipment` | `WaterUseEquipment` | `SpaceLoadInstance` | `WaterUse:Equipment` | `src/energyplus/ForwardTranslator/ForwardTranslateWaterUseEquipment.cpp` |
| `OS:WaterUse:Equipment:Definition` | `WaterUseEquipmentDefinition` | `SpaceLoadDefinition` |  |  |
| `OS:WeatherFile` | `WeatherFile` | `ModelObject` |  |  |
| `OS:WeatherProperty:SkyTemperature` | `SkyTemperature` | `ModelObject` | `WeatherProperty:SkyTemperature` | `src/energyplus/ForwardTranslator/ForwardTranslateSkyTemperature.cpp` |
| `OS:WindowMaterial:Blind` | `Blind` | `ShadingMaterial` | `WindowMaterial:Blind` | `src/energyplus/ForwardTranslator/ForwardTranslateBlind.cpp` |
| `OS:WindowMaterial:DaylightRedirectionDevice` | `DaylightRedirectionDevice` | `ShadingMaterial` |  | `src/energyplus/ForwardTranslator/ForwardTranslateDaylightRedirectionDevice.cpp` |
| `OS:WindowMaterial:Gas` | `Gas` | `GasLayer` | `WindowMaterial:Gas` | `src/energyplus/ForwardTranslator/ForwardTranslateGas.cpp` |
| `OS:WindowMaterial:GasMixture` | `GasMixture` | `GasLayer` | `WindowMaterial:GasMixture` | `src/energyplus/ForwardTranslator/ForwardTranslateGasMixture.cpp` |
| `OS:WindowMaterial:Glazing` | `StandardGlazing` | `Glazing` | `WindowMaterial:Glazing` | `src/energyplus/ForwardTranslator/ForwardTranslateStandardGlazing.cpp` |
| `OS:WindowMaterial:Glazing:RefractionExtinctionMethod` | `RefractionExtinctionGlazing` | `Glazing` | `WindowMaterial:Glazing:RefractionExtinctionMethod` | `src/energyplus/ForwardTranslator/ForwardTranslateRefractionExtinctionGlazing.cpp` |
| `OS:WindowMaterial:GlazingGroup:Thermochromic` | `ThermochromicGlazing` | `Glazing` | `WindowMaterial:GlazingGroup:Thermochromic` | `src/energyplus/ForwardTranslator/ForwardTranslateThermochromicGlazing.cpp` |
| `OS:WindowMaterial:Screen` | `Screen` | `ShadingMaterial` | `WindowMaterial:Screen` | `src/energyplus/ForwardTranslator/ForwardTranslateScreen.cpp` |
| `OS:WindowMaterial:Shade` | `Shade` | `ShadingMaterial` | `WindowMaterial:Shade` | `src/energyplus/ForwardTranslator/ForwardTranslateShade.cpp` |
| `OS:WindowMaterial:SimpleGlazingSystem` | `SimpleGlazing` | `Glazing` | `WindowMaterial:SimpleGlazingSystem` | `src/energyplus/ForwardTranslator/ForwardTranslateSimpleGlazing.cpp` |
| `OS:WindowProperty:FrameAndDivider` | `WindowPropertyFrameAndDivider` | `ResourceObject` | `WindowProperty:FrameAndDivider` | `src/energyplus/ForwardTranslator/ForwardTranslateWindowPropertyFrameAndDivider.cpp` |
| `OS:YearDescription` | `YearDescription` | `ParentObject` |  |  |
| `OS:ZoneAirContaminantBalance` | `ZoneAirContaminantBalance` | `ModelObject` | `ZoneAirContaminantBalance` | `src/energyplus/ForwardTranslator/ForwardTranslateZoneAirContaminantBalance.cpp` |
| `OS:ZoneAirHeatBalanceAlgorithm` | `ZoneAirHeatBalanceAlgorithm` | `ModelObject` | `ZoneAirHeatBalanceAlgorithm` | `src/energyplus/ForwardTranslator/ForwardTranslateZoneAirHeatBalanceAlgorithm.cpp` |
| `OS:ZoneAirMassFlowConservation` | `ZoneAirMassFlowConservation` | `ModelObject` | `ZoneAirMassFlowConservation` | `src/energyplus/ForwardTranslator/ForwardTranslateZoneAirMassFlowConservation.cpp` |
| `OS:ZoneCapacitanceMultiplier:ResearchSpecial` | `ZoneCapacitanceMultiplierResearchSpecial` | `ModelObject` | `ZoneCapacitanceMultiplier:ResearchSpecial` | `src/energyplus/ForwardTranslator/ForwardTranslateZoneCapacitanceMultiplierResearchSpecial.cpp` |
| `OS:ZoneControl:ContaminantController` | `ZoneControlContaminantController` | `ModelObject` | `ZoneControl:ContaminantController` | `src/energyplus/ForwardTranslator/ForwardTranslateZoneControlContaminantController.cpp` |
| `OS:ZoneControl:Humidistat` | `ZoneControlHumidistat` | `ModelObject` | `ZoneControl:Humidistat` | `src/energyplus/ForwardTranslator/ForwardTranslateZoneControlHumidistat.cpp` |
| `OS:ZoneControl:Thermostat:StagedDualSetpoint` | `ZoneControlThermostatStagedDualSetpoint` | `Thermostat` | `ScheduleTypeLimits`, `Schedule:Compact`, `ThermostatSetpoint:DualSetpoint`, `ZoneControl:Thermostat`, `ZoneControl:Thermostat:StagedDualSetpoint` | `src/energyplus/ForwardTranslator/ForwardTranslateZoneControlThermostatStagedDualSetpoint.cpp` |
| `OS:ZoneHVAC:Baseboard:Convective:Electric` | `ZoneHVACBaseboardConvectiveElectric` | `ZoneHVACComponent` | `ZoneHVAC:Baseboard:Convective:Electric` | `src/energyplus/ForwardTranslator/ForwardTranslateZoneHVACBaseboardConvectiveElectric.cpp` |
| `OS:ZoneHVAC:Baseboard:Convective:Water` | `ZoneHVACBaseboardConvectiveWater` | `ZoneHVACComponent` | `ZoneHVAC:Baseboard:Convective:Water` | `src/energyplus/ForwardTranslator/ForwardTranslateZoneHVACBaseboardConvectiveWater.cpp` |
| `OS:ZoneHVAC:Baseboard:RadiantConvective:Electric` | `ZoneHVACBaseboardRadiantConvectiveElectric` | `ZoneHVACComponent` | `ZoneHVAC:Baseboard:RadiantConvective:Electric` | `src/energyplus/ForwardTranslator/ForwardTranslateZoneHVACBaseboardRadiantConvectiveElectric.cpp` |
| `OS:ZoneHVAC:Baseboard:RadiantConvective:Water` | `ZoneHVACBaseboardRadiantConvectiveWater` | `ZoneHVACComponent` | `ZoneHVAC:Baseboard:RadiantConvective:Water`, `ZoneHVAC:Baseboard:RadiantConvective:Water:Design` | `src/energyplus/ForwardTranslator/ForwardTranslateZoneHVACBaseboardRadiantConvectiveWater.cpp` |
| `OS:ZoneHVAC:CoolingPanel:RadiantConvective:Water` | `ZoneHVACCoolingPanelRadiantConvectiveWater` | `ZoneHVACComponent` | `ZoneHVAC:CoolingPanel:RadiantConvective:Water` | `src/energyplus/ForwardTranslator/ForwardTranslateZoneHVACCoolingPanelRadiantConvectiveWater.cpp` |
| `OS:ZoneHVAC:Dehumidifier:DX` | `ZoneHVACDehumidifierDX` | `ZoneHVACComponent` | `ZoneHVAC:Dehumidifier:DX` | `src/energyplus/ForwardTranslator/ForwardTranslateZoneHVACDehumidifierDX.cpp` |
| `OS:ZoneHVAC:EnergyRecoveryVentilator` | `ZoneHVACEnergyRecoveryVentilator` | `ZoneHVACComponent` | `OutdoorAir:NodeList`, `ZoneHVAC:EnergyRecoveryVentilator` | `src/energyplus/ForwardTranslator/ForwardTranslateZoneHVACEnergyRecoveryVentilator.cpp` |
| `OS:ZoneHVAC:EnergyRecoveryVentilator:Controller` | `ZoneHVACEnergyRecoveryVentilatorController` | `ParentObject` | `ZoneHVAC:EnergyRecoveryVentilator:Controller` | `src/energyplus/ForwardTranslator/ForwardTranslateZoneHVACEnergyRecoveryVentilatorController.cpp` |
| `OS:ZoneHVAC:EquipmentList` | `ZoneHVACEquipmentList` | `ModelObject` | `ZoneHVAC:EquipmentList`, `ZoneHVAC:RefrigerationChillerSet` | `src/energyplus/ForwardTranslator/ForwardTranslateZoneHVACEquipmentList.cpp` |
| `OS:ZoneHVAC:EvaporativeCoolerUnit` | `ZoneHVACEvaporativeCoolerUnit` | `ZoneHVACComponent` | `OutdoorAir:NodeList`, `ZoneHVAC:EvaporativeCoolerUnit` | `src/energyplus/ForwardTranslator/ForwardTranslateZoneHVACEvaporativeCoolerUnit.cpp` |
| `OS:ZoneHVAC:FourPipeFanCoil` | `ZoneHVACFourPipeFanCoil` | `ZoneHVACComponent` | `OutdoorAir:Mixer`, `OutdoorAir:NodeList`, `ZoneHVAC:FourPipeFanCoil` | `src/energyplus/ForwardTranslator/ForwardTranslateZoneHVACFourPipeFanCoil.cpp` |
| `OS:ZoneHVAC:HighTemperatureRadiant` | `ZoneHVACHighTemperatureRadiant` | `ZoneHVACComponent` | `ZoneHVAC:HighTemperatureRadiant` | `src/energyplus/ForwardTranslator/ForwardTranslateZoneHVACHighTemperatureRadiant.cpp` |
| `OS:ZoneHVAC:IdealLoadsAirSystem` | `ZoneHVACIdealLoadsAirSystem` | `ZoneHVACComponent` | `ZoneHVAC:IdealLoadsAirSystem` | `src/energyplus/ForwardTranslator/ForwardTranslateZoneHVACIdealLoadsAirSystem.cpp` |
| `OS:ZoneHVAC:LowTemperatureRadiant:ConstantFlow` | `ZoneHVACLowTempRadiantConstFlow` | `ZoneHVACComponent` | `ZoneHVAC:LowTemperatureRadiant:ConstantFlow`, `ZoneHVAC:LowTemperatureRadiant:ConstantFlow:Design`, `ZoneHVAC:LowTemperatureRadiant:SurfaceGroup` | `src/energyplus/ForwardTranslator/ForwardTranslateZoneHVACLowTempRadiantConstFlow.cpp` |
| `OS:ZoneHVAC:LowTemperatureRadiant:Electric` | `ZoneHVACLowTemperatureRadiantElectric` | `ZoneHVACComponent` | `ZoneHVAC:LowTemperatureRadiant:Electric`, `ZoneHVAC:LowTemperatureRadiant:SurfaceGroup` | `src/energyplus/ForwardTranslator/ForwardTranslateZoneHVACLowTemperatureRadiantElectric.cpp` |
| `OS:ZoneHVAC:LowTemperatureRadiant:VariableFlow` | `ZoneHVACLowTempRadiantVarFlow` | `ZoneHVACComponent` | `ZoneHVAC:LowTemperatureRadiant:SurfaceGroup`, `ZoneHVAC:LowTemperatureRadiant:VariableFlow`, `ZoneHVAC:LowTemperatureRadiant:VariableFlow:Design` | `src/energyplus/ForwardTranslator/ForwardTranslateZoneHVACLowTempRadiantVarFlow.cpp` |
| `OS:ZoneHVAC:PackagedTerminalAirConditioner` | `ZoneHVACPackagedTerminalAirConditioner` | `ZoneHVACComponent` | `OutdoorAir:Mixer`, `OutdoorAir:NodeList`, `ZoneHVAC:PackagedTerminalAirConditioner` | `src/energyplus/ForwardTranslator/ForwardTranslateZoneHVACPackagedTerminalAirConditioner.cpp` |
| `OS:ZoneHVAC:PackagedTerminalHeatPump` | `ZoneHVACPackagedTerminalHeatPump` | `ZoneHVACComponent` | `OutdoorAir:Mixer`, `OutdoorAir:NodeList`, `ZoneHVAC:PackagedTerminalHeatPump` | `src/energyplus/ForwardTranslator/ForwardTranslateZoneHVACPackagedTerminalHeatPump.cpp` |
| `OS:ZoneHVAC:TerminalUnit:VariableRefrigerantFlow` | `ZoneHVACTerminalUnitVariableRefrigerantFlow` | `ZoneHVACComponent` | `OutdoorAir:Mixer`, `OutdoorAir:NodeList`, `ZoneHVAC:TerminalUnit:VariableRefrigerantFlow` | `src/energyplus/ForwardTranslator/ForwardTranslateZoneHVACTerminalUnitVariableRefrigerantFlow.cpp` |
| `OS:ZoneHVAC:UnitHeater` | `ZoneHVACUnitHeater` | `ZoneHVACComponent` | `ZoneHVAC:UnitHeater` | `src/energyplus/ForwardTranslator/ForwardTranslateZoneHVACUnitHeater.cpp` |
| `OS:ZoneHVAC:UnitVentilator` | `ZoneHVACUnitVentilator` | `ZoneHVACComponent` | `OutdoorAir:NodeList`, `ZoneHVAC:UnitVentilator` | `src/energyplus/ForwardTranslator/ForwardTranslateZoneHVACUnitVentilator.cpp` |
| `OS:ZoneHVAC:WaterToAirHeatPump` | `ZoneHVACWaterToAirHeatPump` | `ZoneHVACComponent` | `OutdoorAir:Mixer`, `OutdoorAir:NodeList`, `ZoneHVAC:WaterToAirHeatPump` | `src/energyplus/ForwardTranslator/ForwardTranslateZoneHVACWaterToAirHeatPump.cpp` |
| `OS:ZoneMixing` | `ZoneMixing` | `ModelObject` | `ZoneMixing` | `src/energyplus/ForwardTranslator/ForwardTranslateZoneMixing.cpp` |
| `OS:ZoneProperty:UserViewFactors:BySurfaceName` | `ZonePropertyUserViewFactorsBySurfaceName` | `ModelObject` | `ZoneProperty:UserViewFactors:BySurfaceName` | `src/energyplus/ForwardTranslator/ForwardTranslateZonePropertyUserViewFactorsBySurfaceName.cpp` |
| `OS:ZoneVentilation:DesignFlowRate` | `ZoneVentilationDesignFlowRate` | `ZoneHVACComponent` | `ZoneVentilation:DesignFlowRate` | `src/energyplus/ForwardTranslator/ForwardTranslateZoneVentilationDesignFlowRate.cpp` |
| `OS:ZoneVentilation:WindandStackOpenArea` | `ZoneVentilationWindandStackOpenArea` | `ZoneHVACComponent` | `ZoneVentilation:WindandStackOpenArea` | `src/energyplus/ForwardTranslator/ForwardTranslateZoneVentilationWindandStackOpenArea.cpp` |

## OS Types With No EP Output Evidence

| OS IddObjectType | Model class | Direct OS base class | FT source file(s) |
| --- | --- | --- | --- |
| `OS:AdditionalProperties` | `AdditionalProperties` | `ModelObject` |  |
| `OS:AirConditioner:VariableRefrigerantFlow:FluidTemperatureControl:LoadingIndex` | `LoadingIndex` | `ParentObject` |  |
| `OS:AirLoopHVAC:UnitaryCoolOnly` | `` | `` |  |
| `OS:AirflowNetworkLeak` | `` | `` |  |
| `OS:AirflowNetworkPressureController` | `` | `` |  |
| `OS:AirflowNetworkReliefAirFlow` | `` | `` |  |
| `OS:BuildingStory` | `BuildingStory` | `ModelObject` |  |
| `OS:BuildingUnit` | `BuildingUnit` | `ModelObject` |  |
| `OS:CentralHeatPumpSystem:Module` | `CentralHeatPumpSystemModule` | `ParentObject` |  |
| `OS:ClimateZones` | `ClimateZones` | `ModelObject` |  |
| `OS:Coil:Cooling:CooledBeam` | `CoilCoolingCooledBeam` | `StraightComponent` |  |
| `OS:Coil:Cooling:DX:MultiSpeed:StageData` | `CoilCoolingDXMultiSpeedStageData` | `ParentObject` |  |
| `OS:Coil:Cooling:DX:VariableSpeed:SpeedData` | `CoilCoolingDXVariableSpeedSpeedData` | `ParentObject` |  |
| `OS:Coil:Cooling:FourPipeBeam` | `CoilCoolingFourPipeBeam` | `StraightComponent` |  |
| `OS:Coil:Cooling:LowTemperatureRadiant:ConstantFlow` | `CoilCoolingLowTempRadiantConstFlow` | `StraightComponent` |  |
| `OS:Coil:Cooling:LowTemperatureRadiant:VariableFlow` | `CoilCoolingLowTempRadiantVarFlow` | `StraightComponent` |  |
| `OS:Coil:Cooling:Water:Panel:Radiant` | `CoilCoolingWaterPanelRadiant` | `StraightComponent` |  |
| `OS:Coil:Cooling:WaterToAirHeatPump:VariableSpeedEquationFit:SpeedData` | `CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData` | `ParentObject` |  |
| `OS:Coil:Heating:DX:MultiSpeed:StageData` | `CoilHeatingDXMultiSpeedStageData` | `ParentObject` |  |
| `OS:Coil:Heating:DX:VariableSpeed:SpeedData` | `CoilHeatingDXVariableSpeedSpeedData` | `ParentObject` |  |
| `OS:Coil:Heating:Electric:MultiStage:StageData` | `CoilHeatingElectricMultiStageStageData` | `ModelObject` |  |
| `OS:Coil:Heating:FourPipeBeam` | `CoilHeatingFourPipeBeam` | `StraightComponent` |  |
| `OS:Coil:Heating:Gas:MultiStage:StageData` | `CoilHeatingGasMultiStageStageData` | `ModelObject` |  |
| `OS:Coil:Heating:LowTemperatureRadiant:ConstantFlow` | `CoilHeatingLowTempRadiantConstFlow` | `StraightComponent` |  |
| `OS:Coil:Heating:LowTemperatureRadiant:VariableFlow` | `CoilHeatingLowTempRadiantVarFlow` | `StraightComponent` |  |
| `OS:Coil:Heating:Water:Baseboard` | `CoilHeatingWaterBaseboard` | `StraightComponent` |  |
| `OS:Coil:Heating:Water:Baseboard:Radiant` | `CoilHeatingWaterBaseboardRadiant` | `StraightComponent` |  |
| `OS:Coil:Heating:WaterToAirHeatPump:VariableSpeedEquationFit:SpeedData` | `CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData` | `ParentObject` |  |
| `OS:Coil:WaterHeating:AirToWaterHeatPump:VariableSpeed:SpeedData` | `CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData` | `ParentObject` |  |
| `OS:ComponentCost:Adjustments` | `ComponentCostAdjustments` | `ParentObject` |  |
| `OS:ComponentData` | `ComponentData` | `ResourceObject` |  |
| `OS:Connection` | `Connection` | `ModelObject` |  |
| `OS:Connector:Mixer` | `ConnectorMixer` | `Mixer` |  |
| `OS:Connector:Splitter` | `ConnectorSplitter` | `Splitter` |  |
| `OS:Construction:WindowDataFile` | `WindowDataFile` | `ConstructionBase` |  |
| `OS:Daylighting:Control` | `DaylightingControl` | `SpaceItem` | `src/energyplus/ForwardTranslator/ForwardTranslateDaylightingControl.cpp` |
| `OS:DefaultConstructionSet` | `DefaultConstructionSet` | `ResourceObject` |  |
| `OS:DefaultScheduleSet` | `DefaultScheduleSet` | `ResourceObject` |  |
| `OS:DefaultSubSurfaceConstructions` | `DefaultSubSurfaceConstructions` | `ResourceObject` |  |
| `OS:DefaultSurfaceConstructions` | `DefaultSurfaceConstructions` | `ResourceObject` |  |
| `OS:DesignSpecification:OutdoorAir` | `DesignSpecificationOutdoorAir` | `ResourceObject` |  |
| `OS:DesignSpecification:ZoneAirDistribution` | `DesignSpecificationZoneAirDistribution` | `ModelObject` |  |
| `OS:ElectricEquipment:Definition` | `ElectricEquipmentDefinition` | `SpaceLoadDefinition` |  |
| `OS:ElectricEquipment:ITE:AirCooled:Definition` | `ElectricEquipmentITEAirCooledDefinition` | `SpaceLoadDefinition` |  |
| `OS:Exterior:FuelEquipment:Definition` | `ExteriorFuelEquipmentDefinition` | `ExteriorLoadDefinition` |  |
| `OS:Exterior:Lights:Definition` | `ExteriorLightsDefinition` | `ExteriorLoadDefinition` |  |
| `OS:Exterior:WaterEquipment:Definition` | `ExteriorWaterEquipmentDefinition` | `ExteriorLoadDefinition` |  |
| `OS:External:File` | `ExternalFile` | `ResourceObject` |  |
| `OS:Facility` | `Facility` | `ParentObject` |  |
| `OS:GasEquipment:Definition` | `GasEquipmentDefinition` | `SpaceLoadDefinition` |  |
| `OS:Generator:MicroTurbine:HeatRecovery` | `GeneratorMicroTurbineHeatRecovery` | `StraightComponent` |  |
| `OS:Glare:Sensor` | `GlareSensor` | `SpaceItem` |  |
| `OS:HVACComponentList` | `` | `` |  |
| `OS:HeatPump:AirToWater:Cooling` | `HeatPumpAirToWaterCooling` | `StraightComponent` |  |
| `OS:HeatPump:AirToWater:Cooling:SpeedData` | `HeatPumpAirToWaterCoolingSpeedData` | `ResourceObject` |  |
| `OS:HeatPump:AirToWater:Heating` | `HeatPumpAirToWaterHeating` | `StraightComponent` |  |
| `OS:HeatPump:AirToWater:Heating:SpeedData` | `HeatPumpAirToWaterHeatingSpeedData` | `ResourceObject` |  |
| `OS:HotWaterEquipment:Definition` | `HotWaterEquipmentDefinition` | `SpaceLoadDefinition` |  |
| `OS:IlluminanceMap` | `IlluminanceMap` | `SpaceItem` | `src/energyplus/ForwardTranslator/ForwardTranslateIlluminanceMap.cpp` |
| `OS:InteriorPartitionSurfaceGroup` | `InteriorPartitionSurfaceGroup` | `PlanarSurfaceGroup` | `src/energyplus/ForwardTranslator/ForwardTranslateInteriorPartitionSurfaceGroup.cpp` |
| `OS:InternalMass:Definition` | `InternalMassDefinition` | `SpaceLoadDefinition` |  |
| `OS:LifeCycleCost:UsePriceEscalation` | `LifeCycleCostUsePriceEscalation` | `ParentObject` |  |
| `OS:LightingDesignDay` | `LightingDesignDay` | `ModelObject` |  |
| `OS:LightingSimulationControl` | `LightingSimulationControl` | `ModelObject` |  |
| `OS:LightingSimulationZone` | `LightingSimulationZone` | `ModelObject` |  |
| `OS:Lights:Definition` | `LightsDefinition` | `SpaceLoadDefinition` |  |
| `OS:Luminaire:Definition` | `LuminaireDefinition` | `SpaceLoadDefinition` |  |
| `OS:ModelObjectList` | `ModelObjectList` | `ModelObject` |  |
| `OS:Node` | `Node` | `StraightComponent` | `src/energyplus/ForwardTranslator/ForwardTranslateNode.cpp` |
| `OS:OtherEquipment:Definition` | `OtherEquipmentDefinition` | `SpaceLoadDefinition` |  |
| `OS:Output:Meter` | `OutputMeter` | `ModelObject` | `src/energyplus/ForwardTranslator/ForwardTranslateOutputMeter.cpp` |
| `OS:People:Definition` | `PeopleDefinition` | `SpaceLoadDefinition` |  |
| `OS:ProgramControl` | `ProgramControl` | `ModelObject` |  |
| `OS:RadianceParameters` | `RadianceParameters` | `ModelObject` |  |
| `OS:Refrigeration:DefrostCycleParameters` | `RefrigerationDefrostCycleParameters` | `ModelObject` |  |
| `OS:Refrigeration:WalkIn:ZoneBoundary` | `RefrigerationWalkInZoneBoundary` | `ModelObject` |  |
| `OS:Rendering:Color` | `RenderingColor` | `ResourceObject` |  |
| `OS:Schedule:Rule` | `ScheduleRule` | `ParentObject` |  |
| `OS:ShadingSurface` | `ShadingSurface` | `PlanarSurface` | `src/energyplus/ForwardTranslator/ForwardTranslateShadingSurface.cpp` |
| `OS:ShadingSurfaceGroup` | `ShadingSurfaceGroup` | `PlanarSurfaceGroup` | `src/energyplus/ForwardTranslator/ForwardTranslateShadingSurfaceGroup.cpp` |
| `OS:SizingPeriod:WeatherFileConditionType` | `WeatherFileConditionType` | `SizingPeriod` |  |
| `OS:SizingPeriod:WeatherFileDays` | `WeatherFileDays` | `SizingPeriod` |  |
| `OS:Splitter` | `` | `` |  |
| `OS:StandardsInformation:Construction` | `StandardsInformationConstruction` | `ModelObject` |  |
| `OS:StandardsInformation:Material` | `StandardsInformationMaterial` | `ModelObject` |  |
| `OS:SteamEquipment:Definition` | `SteamEquipmentDefinition` | `SpaceLoadDefinition` |  |
| `OS:UtilityBill` | `UtilityBill` | `ModelObject` |  |
| `OS:UtilityCost:Charge:Block` | `` | `` |  |
| `OS:UtilityCost:Charge:Simple` | `` | `` |  |
| `OS:UtilityCost:Computation` | `` | `` |  |
| `OS:UtilityCost:Qualify` | `` | `` |  |
| `OS:UtilityCost:Ratchet` | `` | `` |  |
| `OS:UtilityCost:Tariff` | `` | `` |  |
| `OS:UtilityCost:Variable` | `` | `` |  |
| `OS:WaterUse:Equipment:Definition` | `WaterUseEquipmentDefinition` | `SpaceLoadDefinition` |  |
| `OS:WeatherFile` | `WeatherFile` | `ModelObject` |  |
| `OS:WindowMaterial:DaylightRedirectionDevice` | `DaylightRedirectionDevice` | `ShadingMaterial` | `src/energyplus/ForwardTranslator/ForwardTranslateDaylightRedirectionDevice.cpp` |
| `OS:YearDescription` | `YearDescription` | `ParentObject` |  |

## OS ModelObject Types Without E+ Name Alignment

Name alignment here is based on the canonical `openstudio::model` class name and the EnergyPlus IDD type name after normalizing away punctuation and case differences.

| OS IddObjectType | ModelObject Name | E+ IDD Type Name |
| --- | --- | --- |
| `OS:AirTerminal:SingleDuct:InletSideMixer` | `AirTerminalSingleDuctInletSideMixer` | `AirTerminal:SingleDuct:Mixer`, `ZoneHVAC:AirDistributionUnit` |
| `OS:AirflowNetworkConstantPressureDrop` | `AirflowNetworkConstantPressureDrop` | `AirflowNetwork:Distribution:Component:ConstantPressureDrop` |
| `OS:AirflowNetworkCrack` | `AirflowNetworkCrack` | `AirflowNetwork:MultiZone:Surface:Crack` |
| `OS:AirflowNetworkDetailedOpening` | `AirflowNetworkDetailedOpening` | `AirflowNetwork:MultiZone:Component:DetailedOpening` |
| `OS:AirflowNetworkDuct` | `AirflowNetworkDuct` | `AirflowNetwork:Distribution:Component:Duct` |
| `OS:AirflowNetworkDuctViewFactors` | `AirflowNetworkDuctViewFactors` | `AirflowNetwork:Distribution:DuctViewFactors` |
| `OS:AirflowNetworkEffectiveLeakageArea` | `AirflowNetworkEffectiveLeakageArea` | `AirflowNetwork:MultiZone:Surface:EffectiveLeakageArea` |
| `OS:AirflowNetworkEquivalentDuct` | `AirflowNetworkEquivalentDuct` | `AirflowNetwork:Distribution:Component:Coil`, `AirflowNetwork:Distribution:Component:HeatExchanger`, `AirflowNetwork:Distribution:Component:TerminalUnit` |
| `OS:AirflowNetworkExternalNode` | `AirflowNetworkExternalNode` | `AirflowNetwork:MultiZone:ExternalNode` |
| `OS:AirflowNetworkFan` | `AirflowNetworkFan` | `AirflowNetwork:Distribution:Component:Fan` |
| `OS:AirflowNetworkHorizontalOpening` | `AirflowNetworkHorizontalOpening` | `AirflowNetwork:MultiZone:Component:HorizontalOpening` |
| `OS:AirflowNetworkLeakageRatio` | `AirflowNetworkLeakageRatio` | `AirflowNetwork:Distribution:Component:LeakageRatio` |
| `OS:AirflowNetworkOutdoorAirflow` | `AirflowNetworkOutdoorAirflow` | `AirflowNetwork:Distribution:Component:OutdoorAirFlow` |
| `OS:AirflowNetworkReferenceCrackConditions` | `AirflowNetworkReferenceCrackConditions` | `AirflowNetwork:MultiZone:ReferenceCrackConditions` |
| `OS:AirflowNetworkSimpleOpening` | `AirflowNetworkSimpleOpening` | `AirflowNetwork:MultiZone:Component:SimpleOpening` |
| `OS:AirflowNetworkSpecifiedFlowRate` | `AirflowNetworkSpecifiedFlowRate` | `AirflowNetwork:MultiZone:SpecifiedFlowRate` |
| `OS:AirflowNetworkSurface` | `AirflowNetworkSurface` | `AirflowNetwork:MultiZone:Surface` |
| `OS:AirflowNetworkZone` | `AirflowNetworkZone` | `AirflowNetwork:MultiZone:Zone` |
| `OS:AirflowNetworkZoneExhaustFan` | `AirflowNetworkZoneExhaustFan` | `AirflowNetwork:MultiZone:Component:ZoneExhaustFan` |
| `OS:Coil:Heating:Gas` | `CoilHeatingGas` | `Coil:Heating:Fuel` |
| `OS:Coil:WaterHeating:AirToWaterHeatPump` | `CoilWaterHeatingAirToWaterHeatPump` | `Coil:WaterHeating:AirToWaterHeatPump:Pumped` |
| `OS:Construction:CfactorUndergroundWall` | `CFactorUndergroundWallConstruction` | `Construction:CfactorUndergroundWall` |
| `OS:Construction:FfactorGroundFloor` | `FFactorGroundFloorConstruction` | `Construction:FfactorGroundFloor` |
| `OS:Construction:InternalSource` | `ConstructionWithInternalSource` | `Construction`, `ConstructionProperty:InternalHeatSource` |
| `OS:GroundHeatExchanger:Vertical` | `GroundHeatExchangerVertical` | `GroundHeatExchanger:ResponseFactors`, `GroundHeatExchanger:System`, `GroundHeatExchanger:Vertical:Properties` |
| `OS:InteriorPartitionSurface` | `InteriorPartitionSurface` | `InternalMass` |
| `OS:LifeCycleCost` | `LifeCycleCost` | `LifeCycleCost:NonrecurringCost`, `LifeCycleCost:RecurringCosts` |
| `OS:Luminaire` | `Luminaire` | `Lights` |
| `OS:Material` | `StandardOpaqueMaterial` | `Material` |
| `OS:Material:AirGap` | `AirGap` | `Material:AirGap` |
| `OS:Material:InfraredTransparent` | `InfraredTransparentMaterial` | `Material:InfraredTransparent` |
| `OS:Material:NoMass` | `MasslessOpaqueMaterial` | `Material:NoMass` |
| `OS:Material:RoofVegetation` | `RoofVegetation` | `Material:RoofVegetation` |
| `OS:PortList` | `PortList` | `NodeList` |
| `OS:PythonPlugin:Variable` | `PythonPluginVariable` | `PythonPlugin:Variables` |
| `OS:Refrigeration:Subcooler:LiquidSuction` | `RefrigerationSubcoolerLiquidSuction` | `Refrigeration:Subcooler` |
| `OS:Refrigeration:Subcooler:Mechanical` | `RefrigerationSubcoolerMechanical` | `Refrigeration:Subcooler` |
| `OS:Schedule:Day` | `ScheduleDay` | `Schedule:Day:Interval` |
| `OS:Schedule:FixedInterval` | `ScheduleFixedInterval` | `Schedule:Compact` |
| `OS:Schedule:Ruleset` | `ScheduleRuleset` | `Schedule:Year` |
| `OS:Schedule:VariableInterval` | `ScheduleVariableInterval` | `Schedule:Compact` |
| `OS:Schedule:Week` | `ScheduleWeek` | `Schedule:Week:Daily` |
| `OS:ShadingControl` | `ShadingControl` | `WindowShadingControl` |
| `OS:Site` | `Site` | `Site:Location` |
| `OS:SizingPeriod:DesignDay` | `DesignDay` | `SizingPeriod:DesignDay` |
| `OS:SpaceInfiltration:DesignFlowRate` | `SpaceInfiltrationDesignFlowRate` | `ZoneInfiltration:DesignFlowRate` |
| `OS:SpaceInfiltration:EffectiveLeakageArea` | `SpaceInfiltrationEffectiveLeakageArea` | `ZoneInfiltration:EffectiveLeakageArea` |
| `OS:SpaceInfiltration:FlowCoefficient` | `SpaceInfiltrationFlowCoefficient` | `ZoneInfiltration:FlowCoefficient` |
| `OS:SpaceType` | `SpaceType` | `SpaceList`, `ZoneList` |
| `OS:SubSurface` | `SubSurface` | `FenestrationSurface:Detailed` |
| `OS:Surface` | `Surface` | `BuildingSurface:Detailed` |
| `OS:SurfaceConvectionAlgorithm:Inside` | `InsideSurfaceConvectionAlgorithm` | `SurfaceConvectionAlgorithm:Inside` |
| `OS:SurfaceConvectionAlgorithm:Outside` | `OutsideSurfaceConvectionAlgorithm` | `SurfaceConvectionAlgorithm:Outside` |
| `OS:Table:MultiVariableLookup` | `TableMultiVariableLookup` | `Table:IndependentVariable`, `Table:IndependentVariableList`, `Table:Lookup` |
| `OS:ThermalZone` | `ThermalZone` | `Daylighting:Controls`, `Daylighting:ReferencePoint`, `DesignSpecification:OutdoorAir`, `HVACTemplate:Zone:IdealLoadsAirSystem`, `Output:IlluminanceMap`, `ScheduleTypeLimits`, `Schedule:Compact`, `Zone`, `ZoneControl:Thermostat`, `ZoneHVAC:EquipmentConnections`, `ZoneVentilation:DesignFlowRate` |
| `OS:WaterHeater:HeatPump` | `WaterHeaterHeatPump` | `WaterHeater:HeatPump:PumpedCondenser` |
| `OS:WeatherProperty:SkyTemperature` | `SkyTemperature` | `WeatherProperty:SkyTemperature` |
| `OS:WindowMaterial:Blind` | `Blind` | `WindowMaterial:Blind` |
| `OS:WindowMaterial:Gas` | `Gas` | `WindowMaterial:Gas` |
| `OS:WindowMaterial:GasMixture` | `GasMixture` | `WindowMaterial:GasMixture` |
| `OS:WindowMaterial:Glazing` | `StandardGlazing` | `WindowMaterial:Glazing` |
| `OS:WindowMaterial:Glazing:RefractionExtinctionMethod` | `RefractionExtinctionGlazing` | `WindowMaterial:Glazing:RefractionExtinctionMethod` |
| `OS:WindowMaterial:GlazingGroup:Thermochromic` | `ThermochromicGlazing` | `WindowMaterial:GlazingGroup:Thermochromic` |
| `OS:WindowMaterial:Screen` | `Screen` | `WindowMaterial:Screen` |
| `OS:WindowMaterial:Shade` | `Shade` | `WindowMaterial:Shade` |
| `OS:WindowMaterial:SimpleGlazingSystem` | `SimpleGlazing` | `WindowMaterial:SimpleGlazingSystem` |
| `OS:ZoneHVAC:LowTemperatureRadiant:ConstantFlow` | `ZoneHVACLowTempRadiantConstFlow` | `ZoneHVAC:LowTemperatureRadiant:ConstantFlow`, `ZoneHVAC:LowTemperatureRadiant:ConstantFlow:Design`, `ZoneHVAC:LowTemperatureRadiant:SurfaceGroup` |
| `OS:ZoneHVAC:LowTemperatureRadiant:VariableFlow` | `ZoneHVACLowTempRadiantVarFlow` | `ZoneHVAC:LowTemperatureRadiant:SurfaceGroup`, `ZoneHVAC:LowTemperatureRadiant:VariableFlow`, `ZoneHVAC:LowTemperatureRadiant:VariableFlow:Design` |
