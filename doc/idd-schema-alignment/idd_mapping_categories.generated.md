# OS IDD Type Categories (Generated)

This file reorganizes `idd_mapping.generated.md` into review-oriented categories.

## Method

- Source rows: `doc/idd-schema-alignment/idd_mapping.generated.md` `OS -> EP (Full)`.
- Primary grouping: curated conceptual families intended for review and status work.
- Secondary grouping: `Direct OS base class` from the mapping inventory, preserved within each conceptual family.
- A row appears exactly once in this file.
- `no EP output evidence` means the source mapping row had an empty `EP IddObjectType(s) produced` cell.

## Conceptual Family Summary

| Conceptual family | Count | Without EP output evidence |
| --- | ---: | ---: |
| Airloop topology and distribution | 14 | 6 |
| Air terminals and zone air distribution | 18 | 2 |
| Central air, unitary, and VRF equipment | 62 | 8 |
| Zone HVAC equipment | 35 | 10 |
| Plant equipment and hydronic distribution | 61 | 4 |
| Water heaters and thermal storage | 12 | 1 |
| Generators, electrical, and CHP | 25 | 1 |
| Refrigeration | 17 | 2 |
| AirflowNetwork and natural ventilation | 26 | 3 |
| Loads and water use | 32 | 14 |
| Controls, schedules, and setpoint management | 56 | 1 |
| Geometry, envelope, and materials | 56 | 10 |
| Site, weather, simulation, and sizing | 35 | 5 |
| Output, reporting, EMS, and external interfaces | 49 | 3 |
| Performance curves and lookup tables | 22 | 0 |
| Project metadata, defaults, and economics | 43 | 28 |

## Direct Base Class Summary

| Direct OS base class | Count | Without EP output evidence |
| --- | ---: | ---: |
| `StraightComponent` | 98 | 14 |
| `ZoneHVACComponent` | 27 | 0 |
| `HVACComponent` | 11 | 0 |
| `WaterToAirComponent` | 7 | 0 |
| `WaterToWaterComponent` | 14 | 0 |
| `PlantEquipmentOperationRangeBasedScheme` | 9 | 0 |
| `AirToAirComponent` | 2 | 0 |
| `Loop` | 2 | 0 |
| `Mixer` | 6 | 1 |
| `Splitter` | 3 | 1 |
| `SetpointManager` | 26 | 0 |
| `AvailabilityManager` | 12 | 0 |
| `AirflowNetworkComponent` | 10 | 0 |
| `AirflowNetworkNode` | 3 | 0 |
| `AirflowNetworkLinkage` | 2 | 0 |
| `SpaceLoadInstance` | 11 | 0 |
| `SpaceLoadDefinition` | 11 | 11 |
| `SpaceLoad` | 3 | 0 |
| `ExteriorLoadInstance` | 3 | 0 |
| `ExteriorLoadDefinition` | 3 | 3 |
| `SpaceItem` | 3 | 3 |
| `Schedule` | 7 | 0 |
| `ScheduleInterval` | 3 | 0 |
| `ScheduleBase` | 1 | 0 |
| `SizingPeriod` | 3 | 2 |
| `Curve` | 20 | 0 |
| `Thermostat` | 2 | 0 |
| `ConstructionBase` | 4 | 1 |
| `LayeredConstruction` | 2 | 0 |
| `OpaqueMaterial` | 4 | 0 |
| `Glazing` | 4 | 0 |
| `GasLayer` | 2 | 0 |
| `ModelPartitionMaterial` | 1 | 0 |
| `ShadingMaterial` | 4 | 1 |
| `PlanarSurface` | 4 | 1 |
| `PlanarSurfaceGroup` | 3 | 2 |
| `Generator` | 5 | 0 |
| `Inverter` | 3 | 0 |
| `ElectricalStorage` | 2 | 0 |
| `PhotovoltaicPerformance` | 2 | 0 |
| `ResourceObject` | 24 | 10 |
| `ParentObject` | 33 | 14 |
| `ModelObject` | 150 | 21 |
| _unresolved_ | 14 | 13 |

## Categories

## Airloop topology and distribution (14; 6 without EP output evidence)

### `StraightComponent` (2)

`OS:Duct`, `OS:Node` (no EP output evidence)

### `Loop` (1)

`OS:AirLoopHVAC`

### `Mixer` (3)

`OS:AirLoopHVAC:ReturnPlenum`, `OS:AirLoopHVAC:ZoneMixer`, `OS:Connector:Mixer` (no EP output evidence)

### `Splitter` (3)

`OS:AirLoopHVAC:SupplyPlenum`, `OS:AirLoopHVAC:ZoneSplitter`, `OS:Connector:Splitter` (no EP output evidence)

### `ModelObject` (3)

`OS:AirLoopHVAC:DedicatedOutdoorAirSystem`, `OS:Connection` (no EP output evidence), `OS:PortList`

### Unresolved base class (2)

`OS:HVACComponentList` (no EP output evidence), `OS:Splitter` (no EP output evidence)

## Air terminals and zone air distribution (18; 2 without EP output evidence)

### `StraightComponent` (12)

`OS:AirTerminal:SingleDuct:ConstantVolume:CooledBeam`, `OS:AirTerminal:SingleDuct:ConstantVolume:FourPipeBeam`, `OS:AirTerminal:SingleDuct:ConstantVolume:FourPipeInduction`, `OS:AirTerminal:SingleDuct:ConstantVolume:NoReheat`, `OS:AirTerminal:SingleDuct:ConstantVolume:Reheat`, `OS:AirTerminal:SingleDuct:InletSideMixer`, `OS:AirTerminal:SingleDuct:ParallelPIU:Reheat`, `OS:AirTerminal:SingleDuct:SeriesPIU:Reheat`, `OS:AirTerminal:SingleDuct:VAV:HeatAndCool:NoReheat`, `OS:AirTerminal:SingleDuct:VAV:HeatAndCool:Reheat`, `OS:AirTerminal:SingleDuct:VAV:NoReheat`, `OS:AirTerminal:SingleDuct:VAV:Reheat`

### `Mixer` (3)

`OS:AirTerminal:DualDuct:ConstantVolume`, `OS:AirTerminal:DualDuct:VAV`, `OS:AirTerminal:DualDuct:VAV:OutdoorAir`

### `ResourceObject` (1)

`OS:DesignSpecification:OutdoorAir` (no EP output evidence)

### `ModelObject` (2)

`OS:DesignSpecification:ZoneAirDistribution` (no EP output evidence), `OS:ZoneHVAC:EquipmentList`

## Central air, unitary, and VRF equipment (62; 8 without EP output evidence)

### `StraightComponent` (31)

`OS:AirConditioner:VariableRefrigerantFlow`, `OS:AirLoopHVAC:UnitaryHeatCool:VAVChangeoverBypass`, `OS:AirLoopHVAC:UnitaryHeatPump:AirToAir`, `OS:AirLoopHVAC:UnitaryHeatPump:AirToAir:MultiSpeed`, `OS:Coil:Cooling:DX`, `OS:Coil:Cooling:DX:MultiSpeed`, `OS:Coil:Cooling:DX:SingleSpeed`, `OS:Coil:Cooling:DX:SingleSpeed:ThermalStorage`, `OS:Coil:Cooling:DX:TwoSpeed`, `OS:Coil:Cooling:DX:TwoStageWithHumidityControlMode`, `OS:Coil:Cooling:DX:VariableSpeed`, `OS:Coil:Heating:DX:MultiSpeed`, `OS:Coil:Heating:DX:SingleSpeed`, `OS:Coil:Heating:DX:VariableSpeed`, `OS:Coil:Heating:Electric`, `OS:Coil:Heating:Electric:MultiStage`, `OS:Coil:Heating:Gas`, `OS:Coil:Heating:Gas:MultiStage`, `OS:CoilSystem:Cooling:DX:HeatExchangerAssisted`, `OS:CoilSystem:Cooling:Water`, `OS:CoilSystem:Cooling:Water:HeatExchangerAssisted`, `OS:CoilSystem:IntegratedHeatPump:AirSource`, `OS:EvaporativeCooler:Direct:ResearchSpecial`, `OS:EvaporativeCooler:Indirect:ResearchSpecial`, `OS:Fan:ComponentModel`, `OS:Fan:ConstantVolume`, `OS:Fan:OnOff`, `OS:Fan:SystemModel`, `OS:Fan:VariableVolume`, `OS:Humidifier:Steam:Electric`, `OS:Humidifier:Steam:Gas`

### `ZoneHVACComponent` (1)

`OS:AirLoopHVAC:UnitarySystem`

### `HVACComponent` (8)

`OS:AirConditioner:VariableRefrigerantFlow:FluidTemperatureControl`, `OS:AirConditioner:VariableRefrigerantFlow:FluidTemperatureControl:HR`, `OS:AirLoopHVAC:OutdoorAirSystem`, `OS:Coil:Cooling:DX:VariableRefrigerantFlow`, `OS:Coil:Cooling:DX:VariableRefrigerantFlow:FluidTemperatureControl`, `OS:Coil:Heating:DX:VariableRefrigerantFlow`, `OS:Coil:Heating:DX:VariableRefrigerantFlow:FluidTemperatureControl`, `OS:Controller:WaterCoil`

### `WaterToAirComponent` (7)

`OS:Coil:Cooling:Water`, `OS:Coil:Cooling:WaterToAirHeatPump:EquationFit`, `OS:Coil:Cooling:WaterToAirHeatPump:VariableSpeedEquationFit`, `OS:Coil:Heating:Water`, `OS:Coil:Heating:WaterToAirHeatPump:EquationFit`, `OS:Coil:Heating:WaterToAirHeatPump:VariableSpeedEquationFit`, `OS:Coil:UserDefined`

### `AirToAirComponent` (2)

`OS:HeatExchanger:AirToAir:SensibleAndLatent`, `OS:HeatExchanger:Desiccant:BalancedFlow`

### `ResourceObject` (4)

`OS:Coil:Cooling:DX:CurveFit:OperatingMode`, `OS:Coil:Cooling:DX:CurveFit:Performance`, `OS:Coil:Cooling:DX:CurveFit:Speed`, `OS:HeatExchanger:Desiccant:BalancedFlow:PerformanceDataType1`

### `ParentObject` (7)

`OS:AirConditioner:VariableRefrigerantFlow:FluidTemperatureControl:LoadingIndex` (no EP output evidence), `OS:Coil:Cooling:DX:MultiSpeed:StageData` (no EP output evidence), `OS:Coil:Cooling:DX:VariableSpeed:SpeedData` (no EP output evidence), `OS:Coil:Cooling:WaterToAirHeatPump:VariableSpeedEquationFit:SpeedData` (no EP output evidence), `OS:Coil:Heating:DX:MultiSpeed:StageData` (no EP output evidence), `OS:Coil:Heating:DX:VariableSpeed:SpeedData` (no EP output evidence), `OS:Coil:Heating:WaterToAirHeatPump:VariableSpeedEquationFit:SpeedData` (no EP output evidence)

### `ModelObject` (1)

`OS:Controller:MechanicalVentilation`

### Unresolved base class (1)

`OS:AirLoopHVAC:UnitaryCoolOnly` (no EP output evidence)

## Zone HVAC equipment (35; 10 without EP output evidence)

### `StraightComponent` (10)

`OS:Coil:Cooling:CooledBeam` (no EP output evidence), `OS:Coil:Cooling:FourPipeBeam` (no EP output evidence), `OS:Coil:Cooling:LowTemperatureRadiant:ConstantFlow` (no EP output evidence), `OS:Coil:Cooling:LowTemperatureRadiant:VariableFlow` (no EP output evidence), `OS:Coil:Cooling:Water:Panel:Radiant` (no EP output evidence), `OS:Coil:Heating:FourPipeBeam` (no EP output evidence), `OS:Coil:Heating:LowTemperatureRadiant:ConstantFlow` (no EP output evidence), `OS:Coil:Heating:LowTemperatureRadiant:VariableFlow` (no EP output evidence), `OS:Coil:Heating:Water:Baseboard` (no EP output evidence), `OS:Coil:Heating:Water:Baseboard:Radiant` (no EP output evidence)

### `ZoneHVACComponent` (23)

`OS:Fan:ZoneExhaust`, `OS:ZoneHVAC:Baseboard:Convective:Electric`, `OS:ZoneHVAC:Baseboard:Convective:Water`, `OS:ZoneHVAC:Baseboard:RadiantConvective:Electric`, `OS:ZoneHVAC:Baseboard:RadiantConvective:Water`, `OS:ZoneHVAC:CoolingPanel:RadiantConvective:Water`, `OS:ZoneHVAC:Dehumidifier:DX`, `OS:ZoneHVAC:EnergyRecoveryVentilator`, `OS:ZoneHVAC:EvaporativeCoolerUnit`, `OS:ZoneHVAC:FourPipeFanCoil`, `OS:ZoneHVAC:HighTemperatureRadiant`, `OS:ZoneHVAC:IdealLoadsAirSystem`, `OS:ZoneHVAC:LowTemperatureRadiant:ConstantFlow`, `OS:ZoneHVAC:LowTemperatureRadiant:Electric`, `OS:ZoneHVAC:LowTemperatureRadiant:VariableFlow`, `OS:ZoneHVAC:PackagedTerminalAirConditioner`, `OS:ZoneHVAC:PackagedTerminalHeatPump`, `OS:ZoneHVAC:TerminalUnit:VariableRefrigerantFlow`, `OS:ZoneHVAC:UnitHeater`, `OS:ZoneHVAC:UnitVentilator`, `OS:ZoneHVAC:WaterToAirHeatPump`, `OS:ZoneVentilation:DesignFlowRate`, `OS:ZoneVentilation:WindandStackOpenArea`

### `HVACComponent` (1)

`OS:ThermalZone`

### `ParentObject` (1)

`OS:ZoneHVAC:EnergyRecoveryVentilator:Controller`

## Plant equipment and hydronic distribution (61; 4 without EP output evidence)

### `StraightComponent` (34)

`OS:Boiler:HotWater`, `OS:Boiler:Steam`, `OS:CoolingTower:SingleSpeed`, `OS:CoolingTower:TwoSpeed`, `OS:CoolingTower:VariableSpeed`, `OS:DistrictCooling`, `OS:DistrictHeating:Steam`, `OS:DistrictHeating:Water`, `OS:EvaporativeFluidCooler:SingleSpeed`, `OS:EvaporativeFluidCooler:TwoSpeed`, `OS:FluidCooler:SingleSpeed`, `OS:FluidCooler:TwoSpeed`, `OS:GroundHeatExchanger:HorizontalTrench`, `OS:GroundHeatExchanger:Vertical`, `OS:HeaderedPumps:ConstantSpeed`, `OS:HeaderedPumps:VariableSpeed`, `OS:HeatPump:AirToWater`, `OS:HeatPump:AirToWater:Cooling` (no EP output evidence), `OS:HeatPump:AirToWater:FuelFired:Cooling`, `OS:HeatPump:AirToWater:FuelFired:Heating`, `OS:HeatPump:AirToWater:Heating` (no EP output evidence), `OS:LoadProfile:Plant`, `OS:Pipe:Adiabatic`, `OS:Pipe:Indoor`, `OS:Pipe:Outdoor`, `OS:PlantComponent:TemperatureSource`, `OS:PlantComponent:UserDefined`, `OS:Pump:ConstantSpeed`, `OS:Pump:VariableSpeed`, `OS:SolarCollector:FlatPlate:PhotovoltaicThermal`, `OS:SolarCollector:FlatPlate:Water`, `OS:SolarCollector:IntegralCollectorStorage`, `OS:SwimmingPool:Indoor`, `OS:TemperingValve`

### `WaterToWaterComponent` (11)

`OS:CentralHeatPumpSystem`, `OS:Chiller:Absorption`, `OS:Chiller:Absorption:Indirect`, `OS:Chiller:Electric:ASHRAE205`, `OS:Chiller:Electric:EIR`, `OS:Chiller:Electric:ReformulatedEIR`, `OS:HeatExchanger:FluidToFluid`, `OS:HeatPump:PlantLoop:EIR:Cooling`, `OS:HeatPump:PlantLoop:EIR:Heating`, `OS:HeatPump:WaterToWater:EquationFit:Cooling`, `OS:HeatPump:WaterToWater:EquationFit:Heating`

### `PlantEquipmentOperationRangeBasedScheme` (9)

`OS:PlantEquipmentOperation:CoolingLoad`, `OS:PlantEquipmentOperation:HeatingLoad`, `OS:PlantEquipmentOperation:OutdoorDewpoint`, `OS:PlantEquipmentOperation:OutdoorDewpointDifference`, `OS:PlantEquipmentOperation:OutdoorDryBulb`, `OS:PlantEquipmentOperation:OutdoorDryBulbDifference`, `OS:PlantEquipmentOperation:OutdoorRelativeHumidity`, `OS:PlantEquipmentOperation:OutdoorWetBulb`, `OS:PlantEquipmentOperation:OutdoorWetBulbDifference`

### `Loop` (1)

`OS:PlantLoop`

### `ResourceObject` (2)

`OS:HeatPump:AirToWater:Cooling:SpeedData` (no EP output evidence), `OS:HeatPump:AirToWater:Heating:SpeedData` (no EP output evidence)

### `ModelObject` (4)

`OS:SolarCollectorPerformance:FlatPlate`, `OS:SolarCollectorPerformance:IntegralCollectorStorage`, `OS:SolarCollectorPerformance:PhotovoltaicThermal:BIPVT`, `OS:SolarCollectorPerformance:PhotovoltaicThermal:Simple`

## Water heaters and thermal storage (12; 1 without EP output evidence)

### `StraightComponent` (2)

`OS:Coil:WaterHeating:Desuperheater`, `OS:ThermalStorage:Ice:Detailed`

### `ZoneHVACComponent` (2)

`OS:WaterHeater:HeatPump`, `OS:WaterHeater:HeatPump:WrappedCondenser`

### `HVACComponent` (2)

`OS:Coil:WaterHeating:AirToWaterHeatPump`, `OS:Coil:WaterHeating:AirToWaterHeatPump:VariableSpeed`

### `WaterToWaterComponent` (3)

`OS:ThermalStorage:ChilledWater:Stratified`, `OS:WaterHeater:Mixed`, `OS:WaterHeater:Stratified`

### `ParentObject` (1)

`OS:Coil:WaterHeating:AirToWaterHeatPump:VariableSpeed:SpeedData` (no EP output evidence)

### `ModelObject` (2)

`OS:Coil:WaterHeating:AirToWaterHeatPump:Wrapped`, `OS:WaterHeater:Sizing`

## Generators, electrical, and CHP (25; 1 without EP output evidence)

### `StraightComponent` (3)

`OS:Generator:FuelCell:ExhaustGasToWaterHeatExchanger`, `OS:Generator:FuelCell:StackCooler`, `OS:Generator:MicroTurbine:HeatRecovery` (no EP output evidence)

### `Generator` (5)

`OS:Generator:FuelCell`, `OS:Generator:MicroTurbine`, `OS:Generator:PVWatts`, `OS:Generator:Photovoltaic`, `OS:Generator:WindTurbine`

### `Inverter` (3)

`OS:ElectricLoadCenter:Inverter:LookUpTable`, `OS:ElectricLoadCenter:Inverter:PVWatts`, `OS:ElectricLoadCenter:Inverter:Simple`

### `ElectricalStorage` (2)

`OS:ElectricLoadCenter:Storage:LiIonNMCBattery`, `OS:ElectricLoadCenter:Storage:Simple`

### `PhotovoltaicPerformance` (2)

`OS:PhotovoltaicPerformance:Sandia`, `OS:PhotovoltaicPerformance:Simple`

### `ParentObject` (2)

`OS:ElectricLoadCenter:Distribution`, `OS:ElectricLoadCenter:Storage:Converter`

### `ModelObject` (8)

`OS:ElectricLoadCenter:Transformer`, `OS:Generator:FuelCell:AirSupply`, `OS:Generator:FuelCell:AuxiliaryHeater`, `OS:Generator:FuelCell:ElectricalStorage`, `OS:Generator:FuelCell:Inverter`, `OS:Generator:FuelCell:PowerModule`, `OS:Generator:FuelCell:WaterSupply`, `OS:Generator:FuelSupply`

## Refrigeration (17; 2 without EP output evidence)

### `StraightComponent` (2)

`OS:Refrigeration:CompressorRack`, `OS:Refrigeration:Condenser:WaterCooled`

### `ZoneHVACComponent` (1)

`OS:Refrigeration:AirChiller`

### `ParentObject` (6)

`OS:Refrigeration:Case`, `OS:Refrigeration:Compressor`, `OS:Refrigeration:Condenser:AirCooled`, `OS:Refrigeration:Condenser:EvaporativeCooled`, `OS:Refrigeration:GasCooler:AirCooled`, `OS:Refrigeration:SecondarySystem`

### `ModelObject` (8)

`OS:Refrigeration:Condenser:Cascade`, `OS:Refrigeration:DefrostCycleParameters` (no EP output evidence), `OS:Refrigeration:Subcooler:LiquidSuction`, `OS:Refrigeration:Subcooler:Mechanical`, `OS:Refrigeration:System`, `OS:Refrigeration:TranscriticalSystem`, `OS:Refrigeration:WalkIn`, `OS:Refrigeration:WalkIn:ZoneBoundary` (no EP output evidence)

## AirflowNetwork and natural ventilation (26; 3 without EP output evidence)

### `AirflowNetworkComponent` (10)

`OS:AirflowNetworkCrack`, `OS:AirflowNetworkDetailedOpening`, `OS:AirflowNetworkDuct`, `OS:AirflowNetworkEffectiveLeakageArea`, `OS:AirflowNetworkEquivalentDuct`, `OS:AirflowNetworkFan`, `OS:AirflowNetworkHorizontalOpening`, `OS:AirflowNetworkLeakageRatio`, `OS:AirflowNetworkSimpleOpening`, `OS:AirflowNetworkSpecifiedFlowRate`

### `AirflowNetworkNode` (3)

`OS:AirflowNetworkDistributionNode`, `OS:AirflowNetworkExternalNode`, `OS:AirflowNetworkZone`

### `AirflowNetworkLinkage` (2)

`OS:AirflowNetworkDistributionLinkage`, `OS:AirflowNetworkSurface`

### `ParentObject` (1)

`OS:AirflowNetworkSimulationControl`

### `ModelObject` (7)

`OS:AirflowNetworkConstantPressureDrop`, `OS:AirflowNetworkDuctViewFactors`, `OS:AirflowNetworkOccupantVentilationControl`, `OS:AirflowNetworkOutdoorAirflow`, `OS:AirflowNetworkReferenceCrackConditions`, `OS:AirflowNetworkZoneExhaustFan`, `OS:ZoneMixing`

### Unresolved base class (3)

`OS:AirflowNetworkLeak` (no EP output evidence), `OS:AirflowNetworkPressureController` (no EP output evidence), `OS:AirflowNetworkReliefAirFlow` (no EP output evidence)

## Loads and water use (32; 14 without EP output evidence)

### `StraightComponent` (1)

`OS:WaterUse:Connections`

### `SpaceLoadInstance` (11)

`OS:ElectricEquipment`, `OS:ElectricEquipment:ITE:AirCooled`, `OS:GasEquipment`, `OS:HotWaterEquipment`, `OS:InternalMass`, `OS:Lights`, `OS:Luminaire`, `OS:OtherEquipment`, `OS:People`, `OS:SteamEquipment`, `OS:WaterUse:Equipment`

### `SpaceLoadDefinition` (11)

`OS:ElectricEquipment:Definition` (no EP output evidence), `OS:ElectricEquipment:ITE:AirCooled:Definition` (no EP output evidence), `OS:GasEquipment:Definition` (no EP output evidence), `OS:HotWaterEquipment:Definition` (no EP output evidence), `OS:InternalMass:Definition` (no EP output evidence), `OS:Lights:Definition` (no EP output evidence), `OS:Luminaire:Definition` (no EP output evidence), `OS:OtherEquipment:Definition` (no EP output evidence), `OS:People:Definition` (no EP output evidence), `OS:SteamEquipment:Definition` (no EP output evidence), `OS:WaterUse:Equipment:Definition` (no EP output evidence)

### `SpaceLoad` (3)

`OS:SpaceInfiltration:DesignFlowRate`, `OS:SpaceInfiltration:EffectiveLeakageArea`, `OS:SpaceInfiltration:FlowCoefficient`

### `ExteriorLoadInstance` (3)

`OS:Exterior:FuelEquipment`, `OS:Exterior:Lights`, `OS:Exterior:WaterEquipment`

### `ExteriorLoadDefinition` (3)

`OS:Exterior:FuelEquipment:Definition` (no EP output evidence), `OS:Exterior:Lights:Definition` (no EP output evidence), `OS:Exterior:WaterEquipment:Definition` (no EP output evidence)

## Controls, schedules, and setpoint management (56; 1 without EP output evidence)

### `SetpointManager` (26)

`OS:SetpointManager:Coldest`, `OS:SetpointManager:FollowGroundTemperature`, `OS:SetpointManager:FollowOutdoorAirTemperature`, `OS:SetpointManager:FollowSystemNodeTemperature`, `OS:SetpointManager:MixedAir`, `OS:SetpointManager:MultiZone:Cooling:Average`, `OS:SetpointManager:MultiZone:Heating:Average`, `OS:SetpointManager:MultiZone:Humidity:Maximum`, `OS:SetpointManager:MultiZone:Humidity:Minimum`, `OS:SetpointManager:MultiZone:MaximumHumidity:Average`, `OS:SetpointManager:MultiZone:MinimumHumidity:Average`, `OS:SetpointManager:OutdoorAirPretreat`, `OS:SetpointManager:OutdoorAirReset`, `OS:SetpointManager:Scheduled`, `OS:SetpointManager:Scheduled:DualSetpoint`, `OS:SetpointManager:SingleZone:Cooling`, `OS:SetpointManager:SingleZone:Heating`, `OS:SetpointManager:SingleZone:Humidity:Maximum`, `OS:SetpointManager:SingleZone:Humidity:Minimum`, `OS:SetpointManager:SingleZone:OneStageCooling`, `OS:SetpointManager:SingleZone:OneStageHeating`, `OS:SetpointManager:SingleZone:Reheat`, `OS:SetpointManager:SystemNodeReset:Humidity`, `OS:SetpointManager:SystemNodeReset:Temperature`, `OS:SetpointManager:Warmest`, `OS:SetpointManager:WarmestTemperatureFlow`

### `AvailabilityManager` (12)

`OS:AvailabilityManager:DifferentialThermostat`, `OS:AvailabilityManager:HighTemperatureTurnOff`, `OS:AvailabilityManager:HighTemperatureTurnOn`, `OS:AvailabilityManager:HybridVentilation`, `OS:AvailabilityManager:LowTemperatureTurnOff`, `OS:AvailabilityManager:LowTemperatureTurnOn`, `OS:AvailabilityManager:NightCycle`, `OS:AvailabilityManager:NightVentilation`, `OS:AvailabilityManager:OptimumStart`, `OS:AvailabilityManager:Scheduled`, `OS:AvailabilityManager:ScheduledOff`, `OS:AvailabilityManager:ScheduledOn`

### `Schedule` (7)

`OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:Ruleset`, `OS:Schedule:Year`

### `ScheduleInterval` (3)

`OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:VariableInterval`

### `ScheduleBase` (1)

`OS:Schedule:Day`

### `Thermostat` (2)

`OS:ThermostatSetpoint:DualSetpoint`, `OS:ZoneControl:Thermostat:StagedDualSetpoint`

### `ResourceObject` (2)

`OS:Schedule:Week`, `OS:ScheduleTypeLimits`

### `ParentObject` (1)

`OS:Schedule:Rule` (no EP output evidence)

### `ModelObject` (2)

`OS:ZoneControl:ContaminantController`, `OS:ZoneControl:Humidistat`

## Geometry, envelope, and materials (56; 10 without EP output evidence)

### `SpaceItem` (3)

`OS:Daylighting:Control` (no EP output evidence), `OS:Glare:Sensor` (no EP output evidence), `OS:IlluminanceMap` (no EP output evidence)

### `ConstructionBase` (4)

`OS:Construction:AirBoundary`, `OS:Construction:CfactorUndergroundWall`, `OS:Construction:FfactorGroundFloor`, `OS:Construction:WindowDataFile` (no EP output evidence)

### `LayeredConstruction` (2)

`OS:Construction`, `OS:Construction:InternalSource`

### `OpaqueMaterial` (4)

`OS:Material`, `OS:Material:AirGap`, `OS:Material:NoMass`, `OS:Material:RoofVegetation`

### `Glazing` (4)

`OS:WindowMaterial:Glazing`, `OS:WindowMaterial:Glazing:RefractionExtinctionMethod`, `OS:WindowMaterial:GlazingGroup:Thermochromic`, `OS:WindowMaterial:SimpleGlazingSystem`

### `GasLayer` (2)

`OS:WindowMaterial:Gas`, `OS:WindowMaterial:GasMixture`

### `ModelPartitionMaterial` (1)

`OS:Material:InfraredTransparent`

### `ShadingMaterial` (4)

`OS:WindowMaterial:Blind`, `OS:WindowMaterial:DaylightRedirectionDevice` (no EP output evidence), `OS:WindowMaterial:Screen`, `OS:WindowMaterial:Shade`

### `PlanarSurface` (4)

`OS:InteriorPartitionSurface`, `OS:ShadingSurface` (no EP output evidence), `OS:SubSurface`, `OS:Surface`

### `PlanarSurfaceGroup` (3)

`OS:InteriorPartitionSurfaceGroup` (no EP output evidence), `OS:ShadingSurfaceGroup` (no EP output evidence), `OS:Space`

### `ResourceObject` (5)

`OS:MaterialProperty:GlazingSpectralData`, `OS:ShadingControl`, `OS:SurfaceProperty:OtherSideCoefficients`, `OS:SurfaceProperty:OtherSideConditionsModel`, `OS:WindowProperty:FrameAndDivider`

### `ModelObject` (20)

`OS:DaylightingDevice:LightWell`, `OS:DaylightingDevice:Shelf`, `OS:DaylightingDevice:Tubular`, `OS:Foundation:Kiva`, `OS:Foundation:Kiva:Settings`, `OS:MaterialProperty:MoisturePenetrationDepth:Settings`, `OS:MaterialProperty:PhaseChange`, `OS:MaterialProperty:PhaseChangeHysteresis`, `OS:StandardsInformation:Construction` (no EP output evidence), `OS:StandardsInformation:Material` (no EP output evidence), `OS:SurfaceControl:MovableInsulation`, `OS:SurfaceConvectionAlgorithm:Inside`, `OS:SurfaceConvectionAlgorithm:Outside`, `OS:SurfaceProperty:ConvectionCoefficients`, `OS:SurfaceProperty:ConvectionCoefficients:MultipleSurface`, `OS:SurfaceProperty:ExposedFoundationPerimeter`, `OS:SurfaceProperty:GroundSurfaces`, `OS:SurfaceProperty:IncidentSolarMultiplier`, `OS:SurfaceProperty:LocalEnvironment`, `OS:SurfaceProperty:SurroundingSurfaces`

## Site, weather, simulation, and sizing (35; 5 without EP output evidence)

### `SizingPeriod` (3)

`OS:SizingPeriod:DesignDay`, `OS:SizingPeriod:WeatherFileConditionType` (no EP output evidence), `OS:SizingPeriod:WeatherFileDays` (no EP output evidence)

### `ParentObject` (3)

`OS:RunPeriod`, `OS:SimulationControl`, `OS:YearDescription` (no EP output evidence)

### `ModelObject` (29)

`OS:ClimateZones` (no EP output evidence), `OS:ConvergenceLimits`, `OS:EnvironmentalImpactFactors`, `OS:FuelFactors`, `OS:HeatBalanceAlgorithm`, `OS:PerformancePrecisionTradeoffs`, `OS:RunPeriodControl:DaylightSavingTime`, `OS:RunPeriodControl:SpecialDays`, `OS:ShadowCalculation`, `OS:Site:GroundReflectance`, `OS:Site:GroundTemperature:BuildingSurface`, `OS:Site:GroundTemperature:Deep`, `OS:Site:GroundTemperature:FCfactorMethod`, `OS:Site:GroundTemperature:Shallow`, `OS:Site:GroundTemperature:Undisturbed:KusudaAchenbach`, `OS:Site:GroundTemperature:Undisturbed:Xing`, `OS:Site:WaterMainsTemperature`, `OS:Sizing:Parameters`, `OS:Sizing:Plant`, `OS:Sizing:System`, `OS:Sizing:Zone`, `OS:Timestep`, `OS:Version`, `OS:WeatherFile` (no EP output evidence), `OS:WeatherProperty:SkyTemperature`, `OS:ZoneAirContaminantBalance`, `OS:ZoneAirHeatBalanceAlgorithm`, `OS:ZoneAirMassFlowConservation`, `OS:ZoneCapacitanceMultiplier:ResearchSpecial`

## Output, reporting, EMS, and external interfaces (49; 3 without EP output evidence)

### `ResourceObject` (1)

`OS:PythonPlugin:Instance`

### `ModelObject` (48)

`OS:EnergyManagementSystem:Actuator`, `OS:EnergyManagementSystem:ConstructionIndexVariable`, `OS:EnergyManagementSystem:CurveOrTableIndexVariable`, `OS:EnergyManagementSystem:GlobalVariable`, `OS:EnergyManagementSystem:InternalVariable`, `OS:EnergyManagementSystem:MeteredOutputVariable`, `OS:EnergyManagementSystem:OutputVariable`, `OS:EnergyManagementSystem:Program`, `OS:EnergyManagementSystem:ProgramCallingManager`, `OS:EnergyManagementSystem:Sensor`, `OS:EnergyManagementSystem:Subroutine`, `OS:EnergyManagementSystem:TrendVariable`, `OS:ExternalInterface`, `OS:ExternalInterface:Actuator`, `OS:ExternalInterface:FunctionalMockupUnitExport:From:Variable`, `OS:ExternalInterface:FunctionalMockupUnitExport:To:Actuator`, `OS:ExternalInterface:FunctionalMockupUnitExport:To:Variable`, `OS:ExternalInterface:FunctionalMockupUnitImport`, `OS:ExternalInterface:FunctionalMockupUnitImport:From:Variable`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Actuator`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Variable`, `OS:ExternalInterface:Variable`, `OS:Meter:Custom`, `OS:Meter:CustomDecrement`, `OS:Output:Constructions`, `OS:Output:DebuggingData`, `OS:Output:Diagnostics`, `OS:Output:EnergyManagementSystem`, `OS:Output:EnvironmentalImpactFactors`, `OS:Output:JSON`, `OS:Output:Meter` (no EP output evidence), `OS:Output:SQLite`, `OS:Output:Schedules`, `OS:Output:Table:Annual`, `OS:Output:Table:Monthly`, `OS:Output:Table:SummaryReports`, `OS:Output:Variable`, `OS:OutputControl:Files`, `OS:OutputControl:ReportingTolerances`, `OS:OutputControl:ResilienceSummaries`, `OS:OutputControl:Table:Style`, `OS:OutputControl:Timestamp`, `OS:ProgramControl` (no EP output evidence), `OS:PythonPlugin:OutputVariable`, `OS:PythonPlugin:SearchPaths`, `OS:PythonPlugin:TrendVariable`, `OS:PythonPlugin:Variable`, `OS:RadianceParameters` (no EP output evidence)

## Performance curves and lookup tables (22)

### `Curve` (20)

`OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:FanPressureRise`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:QuadLinear`, `OS:Curve:Quadratic`, `OS:Curve:QuadraticLinear`, `OS:Curve:Quartic`, `OS:Curve:QuintLinear`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Curve:Triquadratic`, `OS:Table:Lookup`

### `ResourceObject` (1)

`OS:Table:IndependentVariable`

### Unresolved base class (1)

`OS:Table:MultiVariableLookup`

## Project metadata, defaults, and economics (43; 28 without EP output evidence)

### `StraightComponent` (1)

`OS:Coil:Heating:Desuperheater`

### `ResourceObject` (8)

`OS:ComponentData` (no EP output evidence), `OS:DefaultConstructionSet` (no EP output evidence), `OS:DefaultScheduleSet` (no EP output evidence), `OS:DefaultSubSurfaceConstructions` (no EP output evidence), `OS:DefaultSurfaceConstructions` (no EP output evidence), `OS:External:File` (no EP output evidence), `OS:Rendering:Color` (no EP output evidence), `OS:SpaceType`

### `ParentObject` (11)

`OS:Building`, `OS:CentralHeatPumpSystem:Module` (no EP output evidence), `OS:ChillerHeaterPerformance:Electric:EIR`, `OS:CoilPerformance:DX:Cooling`, `OS:ComponentCost:Adjustments` (no EP output evidence), `OS:Controller:OutdoorAir`, `OS:CurrencyType`, `OS:Facility` (no EP output evidence), `OS:LifeCycleCost:Parameters`, `OS:LifeCycleCost:UsePriceEscalation` (no EP output evidence), `OS:Site`

### `ModelObject` (16)

`OS:AdditionalProperties` (no EP output evidence), `OS:AvailabilityManagerAssignmentList`, `OS:BuildingStory` (no EP output evidence), `OS:BuildingUnit` (no EP output evidence), `OS:Coil:Heating:Electric:MultiStage:StageData` (no EP output evidence), `OS:Coil:Heating:Gas:MultiStage:StageData` (no EP output evidence), `OS:CoolingTowerPerformance:CoolTools`, `OS:CoolingTowerPerformance:YorkCalc`, `OS:LifeCycleCost`, `OS:LightingDesignDay` (no EP output evidence), `OS:LightingSimulationControl` (no EP output evidence), `OS:LightingSimulationZone` (no EP output evidence), `OS:ModelObjectList` (no EP output evidence), `OS:UnitarySystemPerformance:Multispeed`, `OS:UtilityBill` (no EP output evidence), `OS:ZoneProperty:UserViewFactors:BySurfaceName`

### Unresolved base class (7)

`OS:UtilityCost:Charge:Block` (no EP output evidence), `OS:UtilityCost:Charge:Simple` (no EP output evidence), `OS:UtilityCost:Computation` (no EP output evidence), `OS:UtilityCost:Qualify` (no EP output evidence), `OS:UtilityCost:Ratchet` (no EP output evidence), `OS:UtilityCost:Tariff` (no EP output evidence), `OS:UtilityCost:Variable` (no EP output evidence)

