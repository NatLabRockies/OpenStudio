# OS IDD Object Relationships (HVAC)

This document lists **object-list based relationships** between HVAC-related OpenStudio IDD object types.

## How this was derived

- Source of truth: `resources/model/OpenStudio.idd`.
- mapping object set: `doc/idd-schema-alignment/idd_mapping.generated.md` (all `OS:*` rows).
- For each object, fields with `\object-list` are treated as outgoing references.
- Target objects are inferred by matching `\object-list <ListName>` to objects whose fields declare `\reference <ListName>`.
- Relationships are **schema-based only** (no implicit C++ translator relationships).

## Update / Reproduce

- Parse `resources/model/OpenStudio.idd` into object blocks and fields.
- Collect HVAC object types from `doc/idd-schema-alignment/idd_mapping.generated.md` (`OS:*` rows).
- For each HVAC object, list each field that declares `\object-list`; emit one row per field/object-list pair.
- Resolve targets by linking `\object-list <ListName>` to objects that declare `\reference <ListName>`.
- If a target list is very large (more than 25 entries) or is `AllObjects`, suppress the expanded list and report the count instead.
- Record HVAC objects missing from `OpenStudio.idd` and those with no `\object-list` fields.

## Relationships

### `OS:AdditionalProperties`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A2` Object Name | `AllObjects` | 6 targets (suppressed; list is `AllObjects`) |

### `OS:AirConditioner:VariableRefrigerantFlow`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Cooling Energy Input Ratio Modifier Function of Low Part-Load Ratio Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A1` Cooling Energy Input Ratio Modifier Function of Low Part-Load Ratio Curve Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A1` Cooling Energy Input Ratio Modifier Function of Low Part-Load Ratio Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A11` Cooling Energy Input Ratio Modifier Function of High Part-Load Ratio Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A12` Cooling Combination Ratio Correction Factor Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A13` Maximum Outdoor Temperature in Heating Mode | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A14` Heating Capacity Ratio Modifier Function of Low Temperature Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A15` Heating Capacity Ratio Boundary Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A16` Heating Capacity Ratio Modifier Function of High Temperature Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A17` Heating Energy Input Ratio Modifier Function of Low Temperature Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A18` Heating Energy Input Ratio Boundary Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A19` Heating Energy Input Ratio Modifier Function of High Temperature Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A21` Heating Energy Input Ratio Modifier Function of Low Part-Load Ratio Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A22` Heating Energy Input Ratio Modifier Function of High Part-Load Ratio Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A23` Heating Combination Ratio Correction Factor Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A24` Heating Part-Load Fraction Correlation Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A25` Zone Name for Master Thermostat Location | `ThermalZoneNames` | `OS:ThermalZone` |
| `A27` Thermostat Priority Schedule | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A28` Zone Terminal Unit List | `ModelObjectLists` | `OS:ModelObjectList` |
| `A30` Piping Correction Factor for Length in Cooling Mode Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A30` Piping Correction Factor for Length in Cooling Mode Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A31` Piping Correction Factor for Length in Heating Mode Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A31` Piping Correction Factor for Length in Heating Mode Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A34` Defrost Energy Input Ratio Modifier Function of Temperature Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A36` Condenser Inlet Node | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A37` Condenser Outlet Node | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A38` Supply Water Storage Tank | `WaterStorageTankNames` | No `\reference` matches found |
| `A39` Basin Heater Operating Schedule | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A41` Heat Recovery Cooling Capacity Modifier Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A42` Heat Recovery Cooling Energy Modifier Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A43` Heat Recovery Heating Capacity Modifier Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A44` Heat Recovery Heating Energy Modifier Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |

### `OS:AirConditioner:VariableRefrigerantFlow:FluidTemperatureControl`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Reference Evaporating Temperature for Indoor Unit | `ModelObjectLists` | `OS:ModelObjectList` |
| `A1` Reference Evaporating Temperature for Indoor Unit | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `N16` Outdoor Unit Condensing Temperature Function of Subcooling Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A11` Defrost Energy Input Ratio Modifier Function of Temperature Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A12` Loading Index List | `ModelObjectLists` | `OS:ModelObjectList` |

### `OS:AirConditioner:VariableRefrigerantFlow:FluidTemperatureControl:HR`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Reference Evaporating Temperature for Indoor Unit | `ModelObjectLists` | `OS:ModelObjectList` |
| `A1` Reference Evaporating Temperature for Indoor Unit | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `N22` Outdoor Unit Condensing Temperature Function of Subcooling Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A11` Defrost Energy Input Ratio Modifier Function of Temperature Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A12` Loading Index List | `ModelObjectLists` | `OS:ModelObjectList` |

### `OS:AirConditioner:VariableRefrigerantFlow:FluidTemperatureControl:LoadingIndex`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Evaporative Capacity Multiplier Function of Temperature Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A4` Compressor Power Multiplier Function of Temperature Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |

### `OS:AirLoopHVAC`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Controller List Name | `ControllerLists` | No `\reference` matches found |
| `A4` Availability Schedule | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A5` Availability Manager List Name | `SystemAvailabilityManagerLists` | `OS:AvailabilityManagerAssignmentList` |
| `A6` Branch List Name | `BranchLists` | No `\reference` matches found |
| `A7` Connector List Name | `ConnectorLists` | No `\reference` matches found |
| `A8` Supply Side Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A9` Demand Side Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A10` Demand Side Inlet Node A | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A11` Supply Side Outlet Node A | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A12` Demand Side Inlet Node B | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A13` Supply Side Outlet Node B | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A14` Return Air Bypass Flow Temperature Setpoint Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A15` Demand Mixer Name | `ConnectionObject` | 140 targets (suppressed; list is `ConnectionObject`) |
| `A16` Demand Splitter A Name | `ConnectionObject` | 140 targets (suppressed; list is `ConnectionObject`) |
| `A17` Demand Splitter B Name | `ConnectionObject` | 140 targets (suppressed; list is `ConnectionObject`) |
| `A18` Supply Splitter Name | `ConnectionObject` | 140 targets (suppressed; list is `ConnectionObject`) |

### `OS:AirLoopHVAC:DedicatedOutdoorAirSystem`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Outdoor Air System | `AirLoopHVACOASysNames` | `OS:AirLoopHVAC:OutdoorAirSystem` |
| `A3` Outdoor Air System | `ConnectionObject` | 140 targets (suppressed; list is `ConnectionObject`) |
| `A4` Availability Schedule | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A5` Air Loop 1 | `AirPrimaryLoops` | `OS:AirLoopHVAC` |

### `OS:AirLoopHVAC:OutdoorAirSystem`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Controller Name | `OutdoorAirController` | `OS:Controller:OutdoorAir` |
| `A4` Outdoor Air Equipment List Name | `AirLoopOAEquipmentLists` | No `\reference` matches found |
| `A5` Availability Manager List Name | `SystemAvailabilityManagerLists` | `OS:AvailabilityManagerAssignmentList` |
| `A6` Mixed Air Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A7` Outdoor Air Stream Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A8` Relief Air Stream Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A9` Return Air Stream Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |

### `OS:AirLoopHVAC:ReturnPlenum`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` ThermalZone | `ThermalZoneNames` | `OS:ThermalZone` |
| `A4` Outlet Node | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A5` Induced Air Outlet Port List | `PortLists` | No `\reference` matches found |
| `A6` Inlet 1 Node | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |

### `OS:AirLoopHVAC:SupplyPlenum`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Thermal Zone | `ThermalZoneNames` | `OS:ThermalZone` |
| `A4` Inlet Node | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A5` Outlet 1 Node | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |

### `OS:AirLoopHVAC:UnitaryCoolOnly`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Availability Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A4` DX Cooling Coil System Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A5` DX Cooling Coil System Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A8` Cooling Coil Name | `CoolingCoilsDX` | `OS:Coil:Cooling:DX:SingleSpeed`, `OS:Coil:Cooling:DX:TwoSpeed`, `OS:Coil:Cooling:DX:TwoStageWithHumidityControlMode`, `OS:CoilSystem:Cooling:DX:HeatExchangerAssisted` |

### `OS:AirLoopHVAC:UnitaryHeatCool:VAVChangeoverBypass`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A2` Outdoor Air Mixer | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A2` Outdoor Air Mixer | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A10` Supply Air Fan | `FansCVandOnOff` | `OS:Fan:ConstantVolume`, `OS:Fan:OnOff` |
| `A10` Supply Air Fan | `FansSystemModel` | `OS:Fan:SystemModel` |
| `A12` Supply Air Fan Operating Mode Schedule | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A13` Cooling Coil | `CoolingCoilsDXMultiModeOrSingleSpeed` | `OS:Coil:Cooling:DX:SingleSpeed`, `OS:Coil:Cooling:DX:TwoStageWithHumidityControlMode`, `OS:CoilSystem:Cooling:DX:HeatExchangerAssisted` |
| `A13` Cooling Coil | `CoolingCoilsDXVariableSpeed` | `OS:Coil:Cooling:DX:VariableSpeed` |
| `A14` Heating Coil | `HeatingCoilName` | `OS:Coil:Heating:Electric`, `OS:Coil:Heating:Gas`, `OS:Coil:Heating:Water` |
| `A14` Heating Coil | `HeatingCoilsDXSingleSpeed` | `OS:Coil:Heating:DX:SingleSpeed`, `OS:Coil:Heating:DX:VariableRefrigerantFlow` |
| `A14` Heating Coil | `HeatingCoilsDXVariableSpeed` | `OS:Coil:Heating:DX:VariableSpeed` |
| `A17` Minimum Runtime Before Operating Mode Change | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |

### `OS:AirLoopHVAC:UnitaryHeatPump:AirToAir`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Availability Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A4` Air Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A5` Air Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A6` Controlling Zone or Thermostat Location | `ThermalZoneNames` | `OS:ThermalZone` |
| `A7` Supply Air Fan Name | `FansCVandOnOff` | `OS:Fan:ConstantVolume`, `OS:Fan:OnOff` |
| `A8` Heating Coil Name | `HeatingCoilsDXSingleSpeed` | `OS:Coil:Heating:DX:SingleSpeed`, `OS:Coil:Heating:DX:VariableRefrigerantFlow` |
| `A8` Heating Coil Name | `HeatingCoilsDXVariableSpeed` | `OS:Coil:Heating:DX:VariableSpeed` |
| `A8` Heating Coil Name | `IntegratedHeatPumps` | `OS:CoilSystem:IntegratedHeatPump:AirSource` |
| `A9` Cooling Coil Name | `CoolingCoilsDXSingleSpeed` | `OS:Coil:Cooling:DX:SingleSpeed`, `OS:CoilSystem:Cooling:DX:HeatExchangerAssisted` |
| `A9` Cooling Coil Name | `CoolingCoilsDXVariableSpeed` | `OS:Coil:Cooling:DX:VariableSpeed` |
| `A9` Cooling Coil Name | `IntegratedHeatPumps` | `OS:CoilSystem:IntegratedHeatPump:AirSource` |
| `A10` Supplemental Heating Coil Name | `HeatingCoilsGasElec` | `OS:Coil:Heating:Electric`, `OS:Coil:Heating:Gas` |
| `A10` Supplemental Heating Coil Name | `HeatingCoilsWater` | `OS:Coil:Heating:Water` |
| `A12` Supply Air Fan Operating Mode Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:AirLoopHVAC:UnitaryHeatPump:AirToAir:MultiSpeed`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Availability Schedule | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A4` Air Inlet Node | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A5` Air Outlet Node | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A6` Controlling Zone or Thermostat Location | `ThermalZoneNames` | `OS:ThermalZone` |
| `A7` Supply Air Fan | `FansCVandOnOff` | `OS:Fan:ConstantVolume`, `OS:Fan:OnOff` |
| `A8` Supply Air Fan Operating Mode Schedule | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A10` Heating Coil | `HeatingCoilsDXMultiSpeed` | No `\reference` matches found |
| `A10` Heating Coil | `HeatingCoilsElectricMultiStage` | `OS:Coil:Heating:Electric:MultiStage` |
| `A10` Heating Coil | `HeatingCoilsGasMultiStage` | `OS:Coil:Heating:Gas:MultiStage` |
| `A11` Cooling Coil | `CoolingCoilsDXMultiSpeed` | `OS:Coil:Cooling:DX:MultiSpeed` |
| `A12` Design Heat Recovery Water Flow Rate | `HeatingCoilName` | `OS:Coil:Heating:Electric`, `OS:Coil:Heating:Gas`, `OS:Coil:Heating:Water` |
| `A13` Heat Recovery Water Inlet Node | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A14` Supply Air Flow Rate When No Cooling or Heating is Needed | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |

### `OS:AirLoopHVAC:UnitarySystem`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A4` Controlling Zone or Thermostat Location | `ThermalZoneNames` | `OS:ThermalZone` |
| `A6` Availability Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A7` Air Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A8` Air Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A9` Supply Fan Name | `Fans` | `OS:Fan:ComponentModel`, `OS:Fan:ConstantVolume`, `OS:Fan:OnOff`, `OS:Fan:SystemModel`, `OS:Fan:VariableVolume` |
| `A11` Supply Air Fan Operating Mode Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A12` Heating Coil Name | `HeatingCoilName` | `OS:Coil:Heating:Electric`, `OS:Coil:Heating:Gas`, `OS:Coil:Heating:Water` |
| `A12` Heating Coil Name | `HeatingCoilsDX` | `OS:Coil:Heating:DX:SingleSpeed`, `OS:Coil:Heating:DX:VariableRefrigerantFlow` |
| `A12` Heating Coil Name | `HeatingCoilsDXMultiSpeed` | No `\reference` matches found |
| `A12` Heating Coil Name | `HeatingCoilsDXVariableSpeed` | `OS:Coil:Heating:DX:VariableSpeed` |
| `A12` Heating Coil Name | `HeatingCoilsDesuperheater` | `OS:Coil:Heating:Desuperheater` |
| `A12` Heating Coil Name | `HeatingCoilsElectricMultiStage` | `OS:Coil:Heating:Electric:MultiStage` |
| `A12` Heating Coil Name | `HeatingCoilsGasMultiStage` | `OS:Coil:Heating:Gas:MultiStage` |
| `A12` Heating Coil Name | `HeatingCoilsWaterToAirHP` | `OS:Coil:Heating:WaterToAirHeatPump:EquationFit` |
| `A12` Heating Coil Name | `HeatingCoilsWaterToAirVSHP` | `OS:Coil:Heating:WaterToAirHeatPump:VariableSpeedEquationFit` |
| `A12` Heating Coil Name | `UserDefinedCoil` | `OS:Coil:UserDefined` |
| `A13` Cooling Coil Name | `CoilCoolingDX` | `OS:Coil:Cooling:DX` |
| `A13` Cooling Coil Name | `CoolingCoilsDX` | `OS:Coil:Cooling:DX:SingleSpeed`, `OS:Coil:Cooling:DX:TwoSpeed`, `OS:Coil:Cooling:DX:TwoStageWithHumidityControlMode`, `OS:CoilSystem:Cooling:DX:HeatExchangerAssisted` |
| `A13` Cooling Coil Name | `CoolingCoilsDXMultiSpeed` | `OS:Coil:Cooling:DX:MultiSpeed` |
| `A13` Cooling Coil Name | `CoolingCoilsDXVariableSpeed` | `OS:Coil:Cooling:DX:VariableSpeed` |
| `A13` Cooling Coil Name | `CoolingCoilsWater` | `OS:Coil:Cooling:Water`, `OS:CoilSystem:Cooling:Water:HeatExchangerAssisted` |
| `A13` Cooling Coil Name | `CoolingCoilsWaterToAirHP` | `OS:Coil:Cooling:WaterToAirHeatPump:EquationFit` |
| `A13` Cooling Coil Name | `CoolingCoilsWaterToAirVSHP` | `OS:Coil:Cooling:WaterToAirHeatPump:VariableSpeedEquationFit` |
| `A13` Cooling Coil Name | `UserDefinedCoil` | `OS:Coil:UserDefined` |
| `A16` Supplemental Heating Coil Name | `HeatingCoilName` | `OS:Coil:Heating:Electric`, `OS:Coil:Heating:Gas`, `OS:Coil:Heating:Water` |
| `A16` Supplemental Heating Coil Name | `HeatingCoilsDesuperheater` | `OS:Coil:Heating:Desuperheater` |
| `A16` Supplemental Heating Coil Name | `HeatingCoilsElectricMultiStage` | `OS:Coil:Heating:Electric:MultiStage` |
| `A16` Supplemental Heating Coil Name | `UserDefinedCoil` | `OS:Coil:UserDefined` |
| `A22` Heat Recovery Water Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A23` Heat Recovery Water Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A24` Design Specification Multispeed Object Name | `UnitarySystemPerformaceNames` | `OS:UnitarySystemPerformance:Multispeed` |

### `OS:AirLoopHVAC:ZoneMixer`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A4` Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |

### `OS:AirLoopHVAC:ZoneSplitter`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A4` Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |

### `OS:AirTerminal:DualDuct:ConstantVolume`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Maximum Air Flow Rate | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A1` Maximum Air Flow Rate | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:AirTerminal:DualDuct:VAV`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Minimum Air Flow Turndown Schedule Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A1` Minimum Air Flow Turndown Schedule Name | `DesignSpecificationOutdoorAirNames` | `OS:DesignSpecification:OutdoorAir` |
| `A1` Minimum Air Flow Turndown Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:AirTerminal:DualDuct:VAV:OutdoorAir`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Per Person Ventilation Rate Mode | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A1` Per Person Ventilation Rate Mode | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:AirTerminal:SingleDuct:ConstantVolume:CooledBeam`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Availability Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A5` Supply Air Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A6` Supply Air Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A7` Cooling Coil Name | `CoolingCoilCooledBeam` | `OS:Coil:Cooling:CooledBeam` |

### `OS:AirTerminal:SingleDuct:ConstantVolume:FourPipeBeam`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Rated Primary Air Flow Rate per Beam Length | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A1` Rated Primary Air Flow Rate per Beam Length | `CoolingCoilFourPipeBeam` | `OS:Coil:Cooling:FourPipeBeam` |
| `A1` Rated Primary Air Flow Rate per Beam Length | `HeatingCoilFourPipeBeam` | `OS:Coil:Heating:FourPipeBeam` |
| `A1` Rated Primary Air Flow Rate per Beam Length | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:AirTerminal:SingleDuct:ConstantVolume:FourPipeInduction`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A2` Availability Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A4` Supply Air Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A5` Induced Air Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A6` Air Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A7` Heating Coil Name | `HeatingCoilName` | `OS:Coil:Heating:Electric`, `OS:Coil:Heating:Gas`, `OS:Coil:Heating:Water` |
| `A8` Cooling Coil Name | `CoolingCoilName` | `OS:Coil:Cooling:Water` |
| `A9` Zone Mixer Name | `ZoneMixers` | `OS:AirLoopHVAC:ZoneMixer` |

### `OS:AirTerminal:SingleDuct:ConstantVolume:NoReheat`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Availability Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A4` Air Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A5` Air Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |

### `OS:AirTerminal:SingleDuct:ConstantVolume:Reheat`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Availability Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A4` Air Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A5` Air Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A6` Reheat Coil Name | `HeatingCoilName` | `OS:Coil:Heating:Electric`, `OS:Coil:Heating:Gas`, `OS:Coil:Heating:Water` |

### `OS:AirTerminal:SingleDuct:InletSideMixer`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Terminal Unit Outlet | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A4` Terminal Unit Primary Air Inlet | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A5` Terminal Unit Secondary Air Inlet | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |

### `OS:AirTerminal:SingleDuct:ParallelPIU:Reheat`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Availability Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A4` Supply Air Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A5` Secondary Air Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A6` Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A7` Reheat Coil Air Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A8` Zone Mixer Name | `ZoneMixers` | `OS:AirLoopHVAC:ZoneMixer` |
| `A9` Fan Name | `FansCV` | `OS:Fan:ConstantVolume` |
| `A9` Fan Name | `FansSystemModel` | `OS:Fan:SystemModel` |
| `A10` Reheat Coil Name | `HeatingCoilName` | `OS:Coil:Heating:Electric`, `OS:Coil:Heating:Gas`, `OS:Coil:Heating:Water` |

### `OS:AirTerminal:SingleDuct:SeriesPIU:Reheat`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A2` Availability Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A4` Supply Air Inlet Node | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A5` Secondary Air Inlet Node | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A6` Outlet Node | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A7` Reheat Coil Air Inlet Node | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A8` Zone Mixer Name | `ZoneMixers` | `OS:AirLoopHVAC:ZoneMixer` |
| `A9` Fan Name | `FansCV` | `OS:Fan:ConstantVolume` |
| `A9` Fan Name | `FansSystemModel` | `OS:Fan:SystemModel` |
| `A10` Reheat Coil Name | `HeatingCoilName` | `OS:Coil:Heating:Electric`, `OS:Coil:Heating:Gas`, `OS:Coil:Heating:Water` |

### `OS:AirTerminal:SingleDuct:VAV:HeatAndCool:NoReheat`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A2` Availability Schedule | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A4` Air Outlet | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A5` Air Inlet | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A6` Minimum Air Flow Turndown Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:AirTerminal:SingleDuct:VAV:HeatAndCool:Reheat`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A2` Availability Schedule | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A5` Air Inlet | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A6` Reheat Coil | `HeatingCoilName` | `OS:Coil:Heating:Electric`, `OS:Coil:Heating:Gas`, `OS:Coil:Heating:Water` |
| `A7` Air Outlet | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A8` Minimum Air Flow Turndown Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:AirTerminal:SingleDuct:VAV:NoReheat`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Availability Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A4` Air Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A5` Air Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `N1` Minimum Air Flow Turndown Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:AirTerminal:SingleDuct:VAV:Reheat`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Availability Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A5` Air Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A7` Minimum Air Flow Fraction Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A9` Reheat Coil Name | `HeatingCoilName` | `OS:Coil:Heating:Electric`, `OS:Coil:Heating:Gas`, `OS:Coil:Heating:Water` |
| `A10` Air Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A13` Minimum Air Flow Turndown Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:AirflowNetworkCrack`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Reference Crack Conditions | `ReferenceCrackConditions` | `OS:AirflowNetworkReferenceCrackConditions` |

### `OS:AirflowNetworkDistributionLinkage`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Node 1 Name | `AirflowNetworkNodeAndZoneNames` | `OS:AirflowNetworkDistributionNode`, `OS:AirflowNetworkZone` |
| `A4` Node 2 Name | `AirflowNetworkNodeAndZoneNames` | `OS:AirflowNetworkDistributionNode`, `OS:AirflowNetworkZone` |
| `A5` Component Name | `AirflowNetworkComponentNames` | `OS:AirflowNetworkConstantPressureDrop`, `OS:AirflowNetworkDuct`, `OS:AirflowNetworkEquivalentDuct`, `OS:AirflowNetworkFan`, `OS:AirflowNetworkLeak`, `OS:AirflowNetworkLeakageRatio` |
| `A6` Thermal Zone Name | `ZoneNames` | No `\reference` matches found |

### `OS:AirflowNetworkDistributionNode`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Component Name or Node Name | `AirflowNetworkNodeComponentNames` | `OS:AirLoopHVAC:ZoneMixer`, `OS:AirLoopHVAC:ZoneSplitter`, `OS:Node` |

### `OS:AirflowNetworkDuctViewFactors`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A2` Linkage Name | `AirflowNetworkComponentNames` | `OS:AirflowNetworkConstantPressureDrop`, `OS:AirflowNetworkDuct`, `OS:AirflowNetworkEquivalentDuct`, `OS:AirflowNetworkFan`, `OS:AirflowNetworkLeak`, `OS:AirflowNetworkLeakageRatio` |
| `A3` Surface 1 Name | `AllHeatTranSurfNames` | `OS:InternalMass`, `OS:SubSurface`, `OS:Surface` |

### `OS:AirflowNetworkEquivalentDuct`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Component Name | `AFNCoilNames` | `OS:Coil:Cooling:DX`, `OS:Coil:Cooling:DX:MultiSpeed`, `OS:Coil:Cooling:DX:SingleSpeed`, `OS:Coil:Cooling:DX:TwoSpeed`, `OS:Coil:Cooling:DX:TwoStageWithHumidityControlMode`, `OS:Coil:Cooling:DX:VariableSpeed`, `OS:Coil:Cooling:Water`, `OS:Coil:Cooling:WaterToAirHeatPump:EquationFit`, `OS:Coil:Cooling:WaterToAirHeatPump:VariableSpeedEquationFit`, `OS:Coil:Heating:DX:SingleSpeed`, `OS:Coil:Heating:DX:VariableSpeed`, `OS:Coil:Heating:Desuperheater`, `OS:Coil:Heating:Electric`, `OS:Coil:Heating:Gas`, `OS:Coil:Heating:Water`, `OS:Coil:Heating:WaterToAirHeatPump:EquationFit`, `OS:Coil:Heating:WaterToAirHeatPump:VariableSpeedEquationFit` |
| `A3` Component Name | `AFNHeatExchangerNames` | `OS:HeatExchanger:AirToAir:SensibleAndLatent`, `OS:HeatExchanger:Desiccant:BalancedFlow` |
| `A3` Component Name | `AFNTerminalUnitNames` | No `\reference` matches found |

### `OS:AirflowNetworkExternalNode`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Wind Pressure Coefficient Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |

### `OS:AirflowNetworkFan`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Fan Name | `FansCVandOnOffandVAV` | `OS:Fan:ConstantVolume`, `OS:Fan:OnOff`, `OS:Fan:VariableVolume` |
| `A3` Fan Name | `FansSystemModel` | `OS:Fan:SystemModel` |

### `OS:AirflowNetworkOccupantVentilationControl`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Thermal Comfort Low Temperature Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A4` Thermal Comfort High Temperature Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A6` Opening Probability Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A7` Closing Probability Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:AirflowNetworkOutdoorAirflow`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A2` Name | `OutdoorAirController` | `OS:Controller:OutdoorAir` |
| `A3` Crack Name | `CrackNames` | `OS:AirflowNetworkCrack` |

### `OS:AirflowNetworkPressureController`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Control Zone Name | `ZoneNames` | No `\reference` matches found |
| `A5` Control Object Name | `AFNReliefAirFlowNames` | `OS:AirflowNetworkReliefAirFlow` |
| `A5` Control Object Name | `FansZoneExhaust` | `OS:Fan:ZoneExhaust` |
| `A6` Pressure Control Availability Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A7` Pressure Setpoint Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:AirflowNetworkReliefAirFlow`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Reference Crack Conditions | `ReferenceCrackConditions` | `OS:AirflowNetworkReferenceCrackConditions` |

### `OS:AirflowNetworkSurface`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A2` Surface Name | `SurfAndSubSurfNames` | `OS:SubSurface`, `OS:Surface` |
| `A3` Leakage Component Name | `SurfaceAirflowLeakageNames` | `OS:AirflowNetworkCrack`, `OS:AirflowNetworkDetailedOpening`, `OS:AirflowNetworkEffectiveLeakageArea`, `OS:AirflowNetworkHorizontalOpening`, `OS:AirflowNetworkOutdoorAirflow`, `OS:AirflowNetworkSimpleOpening`, `OS:AirflowNetworkSpecifiedFlowRate`, `OS:AirflowNetworkZoneExhaustFan` |
| `A4` External Node Name | `ExternalNodeNames` | `OS:AirflowNetworkExternalNode` |
| `A6` Ventilation Control Zone Temperature Setpoint Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A7` Venting Availability Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A8` Occupant Ventilation Control Name | `AirflowNetworkOccupantVentilationControlNames` | `OS:AirflowNetworkOccupantVentilationControl` |

### `OS:AirflowNetworkZone`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Thermal Zone Name | `ThermalZoneNames` | `OS:ThermalZone` |
| `A5` Ventilation Control Zone Temperature Setpoint Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A6` Venting Availability Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A8` Occupant Ventilation Control Name | `AirflowNetworkOccupantVentilationControlNames` | `OS:AirflowNetworkOccupantVentilationControl` |

### `OS:AirflowNetworkZoneExhaustFan`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A2` Name | `FansZoneExhaust` | `OS:Fan:ZoneExhaust` |
| `A3` Crack Name | `CrackNames` | `OS:AirflowNetworkCrack` |

### `OS:AvailabilityManager:DifferentialThermostat`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Temperature Difference Off Limit | `Node` | `OS:Node` |

### `OS:AvailabilityManager:HighTemperatureTurnOff`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Temperature | `Node` | `OS:Node` |

### `OS:AvailabilityManager:HighTemperatureTurnOn`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Temperature | `Node` | `OS:Node` |

### `OS:AvailabilityManager:HybridVentilation`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Simple Airflow Control Type Schedule | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A1` Simple Airflow Control Type Schedule | `ThermalZoneNames` | `OS:ThermalZone` |
| `A1` Simple Airflow Control Type Schedule | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A10` Minimum Ventilation Time | `VentilationNames` | `OS:ZoneVentilation:DesignFlowRate` |

### `OS:AvailabilityManager:LowTemperatureTurnOff`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Applicability Schedule Name | `Node` | `OS:Node` |
| `A1` Applicability Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:AvailabilityManager:LowTemperatureTurnOn`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Temperature | `Node` | `OS:Node` |

### `OS:AvailabilityManager:NightCycle`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Heating Zone Fans Only Zone or Zone List Name | `ModelObjectLists` | `OS:ModelObjectList` |
| `A1` Heating Zone Fans Only Zone or Zone List Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:AvailabilityManager:NightVentilation`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Control Zone | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A1` Control Zone | `ThermalZoneNames` | `OS:ThermalZone` |

### `OS:AvailabilityManager:OptimumStart`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Control Algorithm | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A1` Control Algorithm | `ThermalZoneListNames` | No `\reference` matches found |
| `A1` Control Algorithm | `ThermalZoneNames` | `OS:ThermalZone` |

### `OS:AvailabilityManager:Scheduled`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:AvailabilityManager:ScheduledOff`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:AvailabilityManager:ScheduledOn`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:AvailabilityManagerAssignmentList`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Availability Manager Name | `SystemAvailabilityManagers` | `OS:AvailabilityManager:DifferentialThermostat`, `OS:AvailabilityManager:HighTemperatureTurnOff`, `OS:AvailabilityManager:HighTemperatureTurnOn`, `OS:AvailabilityManager:HybridVentilation`, `OS:AvailabilityManager:LowTemperatureTurnOff`, `OS:AvailabilityManager:LowTemperatureTurnOn`, `OS:AvailabilityManager:NightCycle`, `OS:AvailabilityManager:NightVentilation`, `OS:AvailabilityManager:OptimumStart`, `OS:AvailabilityManager:Scheduled`, `OS:AvailabilityManager:ScheduledOff`, `OS:AvailabilityManager:ScheduledOn` |

### `OS:Boiler:HotWater`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A5` Normalized Boiler Efficiency Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A5` Normalized Boiler Efficiency Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A6` Boiler Water Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A7` Boiler Water Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |

### `OS:Boiler:Steam`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `N10` Steam Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |

### `OS:Building`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A4` Space Type Name | `SpaceTypeNames` | `OS:SpaceType` |
| `A5` Default Construction Set Name | `DefaultConstructionSetNames` | `OS:DefaultConstructionSet` |
| `A6` Default Schedule Set Name | `DefaultScheduleSetNames` | `OS:DefaultScheduleSet` |

### `OS:BuildingStory`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Default Construction Set Name | `DefaultConstructionSetNames` | `OS:DefaultConstructionSet` |
| `A4` Default Schedule Set Name | `DefaultScheduleSetNames` | `OS:DefaultScheduleSet` |
| `A5` Group Rendering Name | `GroupRenderingNames` | `OS:Rendering:Color` |

### `OS:BuildingUnit`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Rendering Color | `GroupRenderingNames` | `OS:Rendering:Color` |

### `OS:CentralHeatPumpSystem`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A4` Cooling Loop Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A5` Cooling Loop Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A6` Source Loop Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A7` Source Loop Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A8` Heating Loop Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A9` Heating Loop Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A10` Ancillary Operation Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A11` Chiller Heater Module List Name | `ModelObjectLists` | `OS:ModelObjectList` |

### `OS:Chiller:Absorption`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Coefficient 1 of the Hot Water or Steam Use Part Load Ratio Curve | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `N15` Generator Heat Source Type | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |

### `OS:Chiller:Absorption:Indirect`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Design Chilled Water Flow Rate | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A8` Generator Heat Input Function of Part Load Ratio Curve | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A9` Generator Inlet Node | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A9` Generator Inlet Node | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A11` Generator Outlet Node | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A12` Capacity Correction Function of Condenser Temperature Curve | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A13` Capacity Correction Function of Chilled Water Temperature Curve | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A14` Capacity Correction Function of Generator Temperature Curve | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A15` Generator Heat Input Correction Function of Condenser Temperature Curve | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A16` Generator Heat Input Correction Function of Chilled Water Temperature Curve | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |

### `OS:Chiller:Electric:ASHRAE205`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Representation File Name | `ExternalFileNames` | `OS:External:File` |
| `N2` Ambient Temperature Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A7` Ambient Temperature Zone Name | `ThermalZoneNames` | `OS:ThermalZone` |
| `A9` Chilled Water Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A10` Chilled Water Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A12` Condenser Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A13` Condenser Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A16` Oil Cooler Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A17` Oil Cooler Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A19` Auxiliary Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A20` Auxiliary Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A22` Heat Recovery Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A22` Heat Recovery Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |

### `OS:Chiller:Electric:EIR`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Cooling Capacity Function of Temperature Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A4` Electric Input to Cooling Output Ratio Function of Temperature Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A5` Electric Input to Cooling Output Ratio Function of Part Load Ratio Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A6` Chilled Water Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A7` Chilled Water Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A8` Condenser Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A9` Condenser Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A12` Heat Recovery Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A13` Heat Recovery Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A14` Basin Heater Operating Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A15` Heat Recovery Inlet High Temperature Limit Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A16` Heat Recovery Leaving Temperature Setpoint Node Name | `Node` | `OS:Node` |
| `A19` Condenser Loop Flow Rate Fraction Function of Loop Part Load Ratio Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A20` Temperature Difference Across Condenser Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A21` Thermosiphon Capacity Fraction Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |

### `OS:Chiller:Electric:ReformulatedEIR`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Cooling Capacity Function of Temperature Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A4` Electric Input to Cooling Output Ratio Function of Temperature Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A6` Electric Input to Cooling Output Ratio Function of Part Load Ratio Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A6` Electric Input to Cooling Output Ratio Function of Part Load Ratio Curve Name | `TrivariateFunctions` | `OS:Curve:Triquadratic`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A7` Chilled Water Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A8` Chilled Water Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A9` Condenser Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A10` Condenser Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A12` Heat Recovery Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A13` Heat Recovery Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A14` Heat Recovery Inlet High Temperature Limit Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A15` Heat Recovery Leaving Temperature Setpoint Node Name | `Node` | `OS:Node` |
| `A18` Condenser Loop Flow Rate Fraction Function of Loop Part Load Ratio Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A19` Temperature Difference Across Condenser Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A20` Thermosiphon Capacity Fraction Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |

### `OS:ChillerHeaterPerformance:Electric:EIR`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `N15` Cooling Mode Electric Input to Cooling Output Ratio Function of Part Load Ratio Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `N15` Cooling Mode Electric Input to Cooling Output Ratio Function of Part Load Ratio Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A10` Heating Mode Cooling Capacity Function of Temperature Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A11` Heating Mode Electric Input to Cooling Output Ratio Function of Temperature Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A12` Heating Mode Electric Input to Cooling Output Ratio Function of Part Load Ratio Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A12` Heating Mode Electric Input to Cooling Output Ratio Function of Part Load Ratio Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |

### `OS:Coil:Cooling:CooledBeam`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A2` Chilled Water Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |

### `OS:Coil:Cooling:DX`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Evaporator Inlet Node | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A4` Evaporator Outlet Node | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A5` Availability Schedule | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A6` Condenser Zone | `ThermalZoneNames` | `OS:ThermalZone` |
| `A9` Performance Object | `DXCoolingPerformanceNames` | `OS:Coil:Cooling:DX:CurveFit:Performance` |
| `A10` Condensate Collection Water Storage Tank Name | `WaterStorageTankNames` | No `\reference` matches found |
| `A11` Evaporative Condenser Supply Water Storage Tank Name | `WaterStorageTankNames` | No `\reference` matches found |

### `OS:Coil:Cooling:DX:CurveFit:OperatingMode`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A5` Speed 1 | `DXCoolingSpeedNames` | `OS:Coil:Cooling:DX:CurveFit:Speed` |

### `OS:Coil:Cooling:DX:CurveFit:Performance`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Crankcase Heater Capacity Function of Temperature Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A5` Evaporative Condenser Basin Heater Operating Schedule | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A7` Base Operating Mode | `DXCoolingOperatingModeNames` | `OS:Coil:Cooling:DX:CurveFit:OperatingMode` |
| `A8` Alternative Operating Mode 1 | `DXCoolingOperatingModeNames` | `OS:Coil:Cooling:DX:CurveFit:OperatingMode` |
| `A9` Alternative Operating Mode 2 | `DXCoolingOperatingModeNames` | `OS:Coil:Cooling:DX:CurveFit:OperatingMode` |

### `OS:Coil:Cooling:DX:CurveFit:Speed`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Total Cooling Capacity Modifier Function of Temperature Curve | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A3` Total Cooling Capacity Modifier Function of Temperature Curve | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A4` Total Cooling Capacity Modifier Function of Air Flow Fraction Curve | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A5` Energy Input Ratio Modifier Function of Temperature Curve | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A5` Energy Input Ratio Modifier Function of Temperature Curve | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A6` Energy Input Ratio Modifier Function of Air Flow Fraction Curve | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A7` Part Load Fraction Correlation Curve | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A8` Waste Heat Modifier Function of Temperature Curve | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A9` Sensible Heat Ratio Modifier Function of Temperature Curve | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A10` Sensible Heat Ratio Modifier Function of Flow Fraction Curve | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |

### `OS:Coil:Cooling:DX:MultiSpeed`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Apply Part Load Fraction to Speeds Greater than 1 | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A1` Apply Part Load Fraction to Speeds Greater than 1 | `Node` | `OS:Node` |
| `A1` Apply Part Load Fraction to Speeds Greater than 1 | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A12` Maximum Outdoor Dry-Bulb Temperature for Crankcase Heater Operation | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A13` Basin Heater Operating Schedule | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A15` Stage 1 | `CoilCoolingDXMultiSpeedStageData` | `OS:Coil:Cooling:DX:MultiSpeed:StageData` |

### `OS:Coil:Cooling:DX:MultiSpeed:StageData`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Total Cooling Capacity Function of Temperature Curve | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A4` Total Cooling Capacity Function of Flow Fraction Curve | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A5` Energy Input Ratio Function of Temperature Curve | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A6` Energy Input Ratio Function of Flow Fraction Curve | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A7` Part Load Fraction Correlation Curve | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A8` Waste Heat Function of Temperature Curve | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |

### `OS:Coil:Cooling:DX:SingleSpeed`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Availability Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A4` Air Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A5` Air Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A6` Total Cooling Capacity Function of Temperature Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A7` Total Cooling Capacity Function of Flow Fraction Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A8` Energy Input Ratio Function of Temperature Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A9` Energy Input Ratio Function of Flow Fraction Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A10` Part Load Fraction Correlation Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A13` Crankcase Heater Capacity Function of Temperature Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A14` Supply Water Storage Tank Name | `WaterStorageTankNames` | No `\reference` matches found |
| `A15` Condensate Collection Water Storage Tank Name | `WaterStorageTankNames` | No `\reference` matches found |
| `A16` Basin Heater Operating Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:Coil:Cooling:DX:SingleSpeed:ThermalStorage`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `N6` Evaporator Air Inlet Node | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A9` Cooling Only Mode Rated Sensible Heat Ratio | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A11` Cooling Only Mode Total Evaporator Cooling Capacity Function of Temperature Curve | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A12` Cooling Only Mode Total Evaporator Cooling Capacity Function of Flow Fraction Curve | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A13` Cooling Only Mode Energy Input Ratio Function of Temperature Curve | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A14` Cooling Only Mode Energy Input Ratio Function of Flow Fraction Curve | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A15` Cooling Only Mode Part Load Fraction Correlation Curve | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A16` Cooling Only Mode Sensible Heat Ratio Function of Temperature Curve | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A17` Cooling Only Mode Sensible Heat Ratio Function of Flow Fraction Curve | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A19` Cooling And Charge Mode Total Evaporator Cooling Capacity Function of Temperature Curve | `TrivariateFunctions` | `OS:Curve:Triquadratic`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A20` Cooling And Charge Mode Total Evaporator Cooling Capacity Function of Flow Fraction Curve | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A21` Cooling And Charge Mode Evaporator Energy Input Ratio Function of Temperature Curve | `TrivariateFunctions` | `OS:Curve:Triquadratic`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A22` Cooling And Charge Mode Evaporator Energy Input Ratio Function of Flow Fraction Curve | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A23` Cooling And Charge Mode Evaporator Part Load Fraction Correlation Curve | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A24` Cooling And Charge Mode Storage Charge Capacity Function of Temperature Curve | `TrivariateFunctions` | `OS:Curve:Triquadratic`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A25` Cooling And Charge Mode Storage Charge Capacity Function of Total Evaporator PLR Curve | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A26` Cooling And Charge Mode Storage Energy Input Ratio Function of Temperature Curve | `TrivariateFunctions` | `OS:Curve:Triquadratic`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A27` Cooling And Charge Mode Storage Energy Input Ratio Function of Flow Fraction Curve | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A28` Cooling And Charge Mode Storage Energy Part Load Fraction Correlation Curve | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A29` Cooling And Charge Mode Sensible Heat Ratio Function of Temperature Curve | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A29` Cooling And Charge Mode Sensible Heat Ratio Function of Temperature Curve | `TrivariateFunctions` | `OS:Curve:Triquadratic`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A30` Cooling And Charge Mode Sensible Heat Ratio Function of Flow Fraction Curve | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A32` Cooling And Discharge Mode Total Evaporator Cooling Capacity Function of Temperature Curve | `TrivariateFunctions` | `OS:Curve:Triquadratic`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A33` Cooling And Discharge Mode Total Evaporator Cooling Capacity Function of Flow Fraction Curve | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A34` Cooling And Discharge Mode Evaporator Energy Input Ratio Function of Temperature Curve | `TrivariateFunctions` | `OS:Curve:Triquadratic`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A35` Cooling And Discharge Mode Evaporator Energy Input Ratio Function of Flow Fraction Curve | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A36` Cooling And Discharge Mode Evaporator Part Load Fraction Correlation Curve | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A37` Cooling And Discharge Mode Storage Discharge Capacity Function of Temperature Curve | `TrivariateFunctions` | `OS:Curve:Triquadratic`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A38` Cooling And Discharge Mode Storage Discharge Capacity Function of Flow Fraction Curve | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A39` Cooling And Discharge Mode Storage Discharge Capacity Function of Total Evaporator PLR Curve | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A40` Cooling And Discharge Mode Storage Energy Input Ratio Function of Temperature Curve | `TrivariateFunctions` | `OS:Curve:Triquadratic`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A41` Cooling And Discharge Mode Storage Energy Input Ratio Function of Flow Fraction Curve | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A42` Cooling And Discharge Mode Storage Energy Part Load Fraction Correlation Curve | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A43` Cooling And Discharge Mode Sensible Heat Ratio Function of Temperature Curve | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A43` Cooling And Discharge Mode Sensible Heat Ratio Function of Temperature Curve | `TrivariateFunctions` | `OS:Curve:Triquadratic`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A44` Cooling And Discharge Mode Sensible Heat Ratio Function of Flow Fraction Curve | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A46` Charge Only Mode Storage Charge Capacity Function of Temperature Curve | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A47` Charge Only Mode Storage Energy Input Ratio Function of Temperature Curve | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A49` Discharge Only Mode Storage Discharge Capacity Function of Temperature Curve | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A50` Discharge Only Mode Storage Discharge Capacity Function of Flow Fraction Curve | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A51` Discharge Only Mode Energy Input Ratio Function of Temperature Curve | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A52` Discharge Only Mode Energy Input Ratio Function of Flow Fraction Curve | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A53` Discharge Only Mode Part Load Fraction Correlation Curve | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A54` Discharge Only Mode Sensible Heat Ratio Function of Temperature Curve | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A54` Discharge Only Mode Sensible Heat Ratio Function of Temperature Curve | `TrivariateFunctions` | `OS:Curve:Triquadratic`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A55` Discharge Only Mode Sensible Heat Ratio Function of Flow Fraction Curve | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A59` Basin Heater Availability Schedule | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A60` Supply Water Storage Tank | `WaterStorageTankNames` | No `\reference` matches found |
| `A61` Condensate Collection Water Storage Tank | `WaterStorageTankNames` | No `\reference` matches found |

### `OS:Coil:Cooling:DX:TwoSpeed`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Availability Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A4` Air Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A5` Air Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A6` Total Cooling Capacity Function of Temperature Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A7` Total Cooling Capacity Function of Flow Fraction Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A8` Energy Input Ratio Function of Temperature Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A9` Energy Input Ratio Function of Flow Fraction Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A10` Part Load Fraction Correlation Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A11` Low Speed Total Cooling Capacity Function of Temperature Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A12` Low Speed Energy Input Ratio Function of Temperature Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A15` Supply Water Storage Tank Name | `WaterStorageTankNames` | No `\reference` matches found |
| `A16` Condensate Collection Water Storage Tank Name | `WaterStorageTankNames` | No `\reference` matches found |
| `A17` Basin Heater Operating Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:Coil:Cooling:DX:TwoStageWithHumidityControlMode`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Normal Mode Stage 1 Plus 2 Coil Performance | `CoilPerformanceDX` | `OS:CoilPerformance:DX:Cooling` |
| `A1` Normal Mode Stage 1 Plus 2 Coil Performance | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A1` Normal Mode Stage 1 Plus 2 Coil Performance | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A1` Normal Mode Stage 1 Plus 2 Coil Performance | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A9` Dehumidification Mode 1 Stage 1 Coil Performance | `CoilPerformanceDX` | `OS:CoilPerformance:DX:Cooling` |
| `A10` Dehumidification Mode 1 Stage 1 Plus 2 Coil Performance | `CoilPerformanceDX` | `OS:CoilPerformance:DX:Cooling` |
| `A11` Supply Water Storage Tank | `WaterStorageTankNames` | No `\reference` matches found |
| `A12` Condensate Collection Water Storage Tank | `WaterStorageTankNames` | No `\reference` matches found |
| `A13` Basin Heater Operating Schedule | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:Coil:Cooling:DX:VariableRefrigerantFlow`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Coil Air Outlet Node | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A1` Coil Air Outlet Node | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A1` Coil Air Outlet Node | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A1` Coil Air Outlet Node | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |

### `OS:Coil:Cooling:DX:VariableRefrigerantFlow:FluidTemperatureControl`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Availability Schedule | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A4` Coil Air Inlet Node | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A5` Coil Air Outlet Node | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A6` Indoor Unit Evaporating Temperature Function of Superheating Curve | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |

### `OS:Coil:Cooling:DX:VariableSpeed`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Availability Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A4` Indoor Air Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A5` Indoor Air Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A6` Energy Part Load Fraction Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A9` Crankcase Heater Capacity Function of Temperature Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A10` Supply Water Storage Tank Name | `WaterStorageTankNames` | No `\reference` matches found |
| `A11` Condensate Collection Water Storage Tank Name | `WaterStorageTankNames` | No `\reference` matches found |
| `A12` Basin Heater Operating Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A13` Speed Data List | `ModelObjectLists` | `OS:ModelObjectList` |

### `OS:Coil:Cooling:DX:VariableSpeed:SpeedData`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Total Cooling Capacity Function of Temperature Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A4` Total Cooling Capacity Function of Air Flow Fraction Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A5` Energy Input Ratio Function of Temperature Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A6` Energy Input Ratio Function of Air Flow Fraction Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |

### `OS:Coil:Cooling:FourPipeBeam`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A2` Beam Cooling Capacity Chilled Water Flow Modification Factor Curve Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A2` Beam Cooling Capacity Chilled Water Flow Modification Factor Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |

### `OS:Coil:Cooling:LowTemperatureRadiant:ConstantFlow`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Cooling Water Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A4` Cooling Water Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A5` Cooling High Water Temperature Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A6` Cooling Low Water Temperature Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A7` Cooling High Control Temperature Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A8` Cooling Low Control Temperature Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:Coil:Cooling:Water`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Availability Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A4` Water Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A5` Water Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A6` Air Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A7` Air Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |

### `OS:Coil:Cooling:WaterToAirHeatPump:EquationFit`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Availability Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A4` Water Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A5` Water Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A6` Air Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A7` Air Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A8` Total Cooling Capacity Curve Name | `QuadvariateFunctions` | `OS:Curve:QuadLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A9` Sensible Cooling Capacity Curve Name | `QuintvariateFunctions` | `OS:Curve:QuintLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A10` Cooling Power Consumption Curve Name | `QuadvariateFunctions` | `OS:Curve:QuadLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A11` Part Load Fraction Correlation Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |

### `OS:Coil:Cooling:WaterToAirHeatPump:VariableSpeedEquationFit`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Availability Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A4` Water-to-Refrigerant HX Water Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A5` Water-to-Refrigerant HX Water Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A6` Indoor Air Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A7` Indoor Air Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A9` Energy Part Load Fraction Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A10` Speed Data List | `ModelObjectLists` | `OS:ModelObjectList` |

### `OS:Coil:Cooling:WaterToAirHeatPump:VariableSpeedEquationFit:SpeedData`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Total Cooling Capacity Function of Temperature Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A4` Total Cooling Capacity Function of Air Flow Fraction Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A5` Total Cooling Capacity Function of Water Flow Fraction Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A6` Energy Input Ratio Function of Temperature Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A7` Energy Input Ratio Function of Air Flow Fraction Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A8` Energy Input Ratio Function of Water Flow Fraction Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A9` Waste Heat Function of Temperature Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |

### `OS:Coil:Heating:DX:MultiSpeed`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A12` Stage 1 | `CoilHeatingDXMultiSpeedStageData` | No `\reference` matches found |

### `OS:Coil:Heating:DX:SingleSpeed`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Availability Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A4` Air Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A5` Air Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A6` Total Heating Capacity Function of Temperature Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A6` Total Heating Capacity Function of Temperature Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A7` Total Heating Capacity Function of Flow Fraction Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A8` Energy Input Ratio Function of Temperature Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A8` Energy Input Ratio Function of Temperature Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A9` Energy Input Ratio Function of Flow Fraction Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A10` Part Load Fraction Correlation Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A11` Defrost Energy Input Ratio Function of Temperature Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A12` Crankcase Heater Capacity Function of Temperature Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |

### `OS:Coil:Heating:DX:VariableRefrigerantFlow`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Heating Capacity Modifier Function of Flow Fraction Curve | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A1` Heating Capacity Modifier Function of Flow Fraction Curve | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A1` Heating Capacity Modifier Function of Flow Fraction Curve | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A1` Heating Capacity Modifier Function of Flow Fraction Curve | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |

### `OS:Coil:Heating:DX:VariableRefrigerantFlow:FluidTemperatureControl`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Availability Schedule | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A4` Coil Air Inlet Node | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A5` Coil Air Outlet Node | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A6` Indoor Unit Condensing Temperature Function of Subcooling Curve | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |

### `OS:Coil:Heating:DX:VariableSpeed`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Availability Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A4` Indoor Air Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A5` Indoor Air Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A6` Energy Part Load Fraction Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A7` Defrost Energy Input Ratio Function of Temperature Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A8` Crankcase Heater Capacity Function of Temperature Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A11` Speed Data List | `ModelObjectLists` | `OS:ModelObjectList` |

### `OS:Coil:Heating:DX:VariableSpeed:SpeedData`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Heating Capacity Function of Temperature Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A4` Total  Heating Capacity Function of Air Flow Fraction Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A5` Energy Input Ratio Function of Temperature Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A6` Energy Input Ratio Function of Air Flow Fraction Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |

### `OS:Coil:Heating:Desuperheater`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Availability Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A4` Air Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A5` Air Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A6` Heating Source Name | `DesuperHeatingCoilSources` | `OS:Coil:Cooling:DX`, `OS:Coil:Cooling:DX:SingleSpeed`, `OS:Coil:Cooling:DX:TwoSpeed`, `OS:Coil:Cooling:DX:TwoStageWithHumidityControlMode`, `OS:Coil:Cooling:DX:VariableSpeed`, `OS:Refrigeration:CompressorRack`, `OS:Refrigeration:Condenser:AirCooled`, `OS:Refrigeration:Condenser:EvaporativeCooled`, `OS:Refrigeration:Condenser:WaterCooled` |

### `OS:Coil:Heating:Electric`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Availability Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A4` Air Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A5` Air Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A6` Temperature Setpoint Node Name | `Node` | `OS:Node` |

### `OS:Coil:Heating:Electric:MultiStage`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Air Outlet Node | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A1` Air Outlet Node | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A7` Stage 1 | `CoilHeatingElectricMultiStageStageData` | `OS:Coil:Heating:Electric:MultiStage:StageData` |

### `OS:Coil:Heating:FourPipeBeam`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A2` Hot Water Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A4` Beam Heating Capacity Hot Water Flow Modification Factor Curve Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A4` Beam Heating Capacity Hot Water Flow Modification Factor Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |

### `OS:Coil:Heating:Gas`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Availability Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A4` Air Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A5` Air Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A7` Part Load Fraction Correlation Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |

### `OS:Coil:Heating:Gas:MultiStage`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Availability Schedule | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A4` Air Inlet Node | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A5` Air Outlet Node | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A6` Part Load Fraction Correlation Curve | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A7` Stage 1 | `CoilHeatingGasMultiStageStageData` | `OS:Coil:Heating:Gas:MultiStage:StageData` |

### `OS:Coil:Heating:Water`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Availability Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A4` Water Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A5` Water Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A6` Air Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A7` Air Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |

### `OS:Coil:Heating:Water:Baseboard`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A4` Water Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A5` Water Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |

### `OS:Coil:Heating:Water:Baseboard:Radiant`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A4` Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |

### `OS:Coil:Heating:WaterToAirHeatPump:EquationFit`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Availability Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A4` Water Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A5` Water Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A6` Air Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A7` Air Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A8` Heating Capacity Curve Name | `QuadvariateFunctions` | `OS:Curve:QuadLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A9` Heating Power Consumption Curve Name | `QuadvariateFunctions` | `OS:Curve:QuadLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A10` Part Load Fraction Correlation Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |

### `OS:Coil:Heating:WaterToAirHeatPump:VariableSpeedEquationFit`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Availability Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A4` Water-to-Refrigerant HX Water Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A5` Water-to-Refrigerant HX Water Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A6` Indoor Air Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A7` Indoor Air Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A8` Energy Part Load Fraction Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A9` Speed Data List | `ModelObjectLists` | `OS:ModelObjectList` |

### `OS:Coil:Heating:WaterToAirHeatPump:VariableSpeedEquationFit:SpeedData`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Heating Capacity Function of Temperature Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A4` Total Heating Capacity Function of Air Flow Fraction Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A5` Heating Capacity Function of Water Flow Fraction Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A6` Energy Input Ratio Function of Temperature Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A7` Energy Input Ratio Function of Air Flow Fraction Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A8` Energy Input Ratio Function of Water Flow Fraction Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A9` Waste Heat Function of Temperature Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |

### `OS:Coil:UserDefined`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Overall Model Simulation Program Calling Manager Name | `ErlProgramCallingManagerNames` | `OS:EnergyManagementSystem:ProgramCallingManager` |
| `A4` Model Setup and Sizing Program Calling Manager Name | `ErlProgramCallingManagerNames` | `OS:EnergyManagementSystem:ProgramCallingManager` |
| `A5` Air Connection 1 Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A6` Air Connection 1 Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A8` Plant Connection Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A9` Plant Connection Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A10` Ambient Zone Name | `ThermalZoneNames` | `OS:ThermalZone` |
| `A11` Overall Simulation Program Name | `ErlProgramNames` | `OS:EnergyManagementSystem:Program` |
| `A12` Initialization Simulation Program Name | `ErlProgramNames` | `OS:EnergyManagementSystem:Program` |
| `A13` Air Outlet Temperature Actuator | `ErlActuatorNames` | `OS:EnergyManagementSystem:Actuator` |
| `A14` Air Outlet Humidity Ratio Actuator | `ErlActuatorNames` | `OS:EnergyManagementSystem:Actuator` |
| `A15` Air Mass Flow Rate Actuator | `ErlActuatorNames` | `OS:EnergyManagementSystem:Actuator` |
| `A16` Plant Minimum Mass Flow Rate Actuator | `ErlActuatorNames` | `OS:EnergyManagementSystem:Actuator` |
| `A17` Plant Maximum Mass Flow Rate Actuator | `ErlActuatorNames` | `OS:EnergyManagementSystem:Actuator` |
| `A18` Plant Design Volume Flow Rate Actuator | `ErlActuatorNames` | `OS:EnergyManagementSystem:Actuator` |
| `A19` Plant Outlet Temperature Actuator | `ErlActuatorNames` | `OS:EnergyManagementSystem:Actuator` |
| `A20` Plant Mass Flow Rate Actuator | `ErlActuatorNames` | `OS:EnergyManagementSystem:Actuator` |

### `OS:Coil:WaterHeating:AirToWaterHeatPump`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Condenser Water Pump Power | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `N10` Condenser Water Inlet Node | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A10` Condenser Water Outlet Node | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A11` Crankcase Heater Capacity Function of Temperature Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A13` Heating Capacity Function of Temperature Curve | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A13` Heating Capacity Function of Temperature Curve | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A14` Heating Capacity Function of Air Flow Fraction Curve | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A15` Heating Capacity Function of Water Flow Fraction Curve | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A16` Heating COP Function of Temperature Curve | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A16` Heating COP Function of Temperature Curve | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A17` Heating COP Function of Air Flow Fraction Curve | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A18` Heating COP Function of Water Flow Fraction Curve | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A19` Part Load Fraction Correlation Curve | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |

### `OS:Coil:WaterHeating:AirToWaterHeatPump:VariableSpeed`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Availability Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A7` Evaporator Air Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A8` Evaporator Air Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A9` Condenser Water Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A10` Condenser Water Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A11` Crankcase Heater Capacity Function of Temperature Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A13` Part Load Fraction Correlation Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A14` Speed Data List | `ModelObjectLists` | `OS:ModelObjectList` |

### `OS:Coil:WaterHeating:AirToWaterHeatPump:VariableSpeed:SpeedData`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Total Water Heating Capacity Function of Temperature Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A4` Total Water Heating Capacity Function of Air Flow Fraction Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A5` Total Water Heating Capacity Function of Water Flow Fraction Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A6` COP Function of Temperature Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A7` COP Function of Air Flow Fraction Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A8` COP Function of Water Flow Fraction Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |

### `OS:Coil:WaterHeating:AirToWaterHeatPump:Wrapped`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Evaporator Fan Power Included in Rated COP | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A5` Evaporator Air Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A6` Evaporator Air Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A7` Crankcase Heater Capacity Function of Temperature Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A9` Heating Capacity Function of Temperature Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A9` Heating Capacity Function of Temperature Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A10` Heating Capacity Function of Air Flow Fraction Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A11` Heating COP Function of Temperature Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A11` Heating COP Function of Temperature Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A12` Heating COP Function of Air Flow Fraction Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A13` Part Load Fraction Correlation Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |

### `OS:Coil:WaterHeating:Desuperheater`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Availability Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A4` Setpoint Temperature Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A5` Heat Reclaim Efficiency Function of Temperature Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A6` Water Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A7` Water Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A8` Heating Source Name | `CoilCoolingDX` | `OS:Coil:Cooling:DX` |
| `A8` Heating Source Name | `DesuperHeatingCoilSources` | `OS:Coil:Cooling:DX`, `OS:Coil:Cooling:DX:SingleSpeed`, `OS:Coil:Cooling:DX:TwoSpeed`, `OS:Coil:Cooling:DX:TwoStageWithHumidityControlMode`, `OS:Coil:Cooling:DX:VariableSpeed`, `OS:Refrigeration:CompressorRack`, `OS:Refrigeration:Condenser:AirCooled`, `OS:Refrigeration:Condenser:EvaporativeCooled`, `OS:Refrigeration:Condenser:WaterCooled` |
| `A8` Heating Source Name | `DesuperHeatingWaterOnlySources` | `OS:Coil:Cooling:DX:MultiSpeed`, `OS:Coil:Cooling:WaterToAirHeatPump:EquationFit`, `OS:Coil:Cooling:WaterToAirHeatPump:VariableSpeedEquationFit` |

### `OS:CoilPerformance:DX:Cooling`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Evaporative Condenser Effectiveness | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A1` Evaporative Condenser Effectiveness | `Node` | `OS:Node` |
| `A1` Evaporative Condenser Effectiveness | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A10` Sensible Heat Ratio Function of Temperature Curve | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A11` Sensible Heat Ratio Function of Flow Fraction Curve | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |

### `OS:CoilSystem:Cooling:DX:HeatExchangerAssisted`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Air Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A4` Cooling Coil | `CoilCoolingDX` | `OS:Coil:Cooling:DX` |
| `A4` Cooling Coil | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A4` Cooling Coil | `CoolingCoilsDXSingleSpeed` | `OS:Coil:Cooling:DX:SingleSpeed`, `OS:CoilSystem:Cooling:DX:HeatExchangerAssisted` |
| `A4` Cooling Coil | `CoolingCoilsDXVariableSpeed` | `OS:Coil:Cooling:DX:VariableSpeed` |
| `A4` Cooling Coil | `HXAirToAirNames` | `OS:HeatExchanger:AirToAir:SensibleAndLatent`, `OS:HeatExchanger:Desiccant:BalancedFlow` |

### `OS:CoilSystem:Cooling:Water`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Air Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A4` Air Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A5` Availability Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A6` Cooling Coil | `CoolingCoilsWater` | `OS:Coil:Cooling:Water`, `OS:CoilSystem:Cooling:Water:HeatExchangerAssisted` |
| `A11` Companion Coil Used For Heat Recovery | `CoolingCoilsWater` | `OS:Coil:Cooling:Water`, `OS:CoilSystem:Cooling:Water:HeatExchangerAssisted` |

### `OS:CoilSystem:Cooling:Water:HeatExchangerAssisted`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Air Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A4` Cooling Coil | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A4` Cooling Coil | `CoolingCoilsWaterNoHX` | `OS:Coil:Cooling:Water` |
| `A4` Cooling Coil | `HXAirToAirSensibleAndLatentNames` | `OS:HeatExchanger:AirToAir:SensibleAndLatent` |

### `OS:CoilSystem:IntegratedHeatPump:AirSource`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Air Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A4` Air Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A5` Supply Hot Water Flow Sensor Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A6` Space Cooling Coil | `CoolingCoilsDXVariableSpeed` | `OS:Coil:Cooling:DX:VariableSpeed` |
| `A7` Space Heating Coil | `HeatingCoilsDXVariableSpeed` | `OS:Coil:Heating:DX:VariableSpeed` |
| `A8` Dedicated Water Heating Coil | `HeatPumpWaterHeaterDXCoilsVariableSpeed` | `OS:Coil:WaterHeating:AirToWaterHeatPump:VariableSpeed` |
| `A9` SCWH Coil | `HeatPumpWaterHeaterDXCoilsVariableSpeed` | `OS:Coil:WaterHeating:AirToWaterHeatPump:VariableSpeed` |
| `A10` SCDWH Cooling Coil | `CoolingCoilsDXVariableSpeed` | `OS:Coil:Cooling:DX:VariableSpeed` |
| `A11` SCDWH Water Heating Coil | `HeatPumpWaterHeaterDXCoilsVariableSpeed` | `OS:Coil:WaterHeating:AirToWaterHeatPump:VariableSpeed` |
| `A12` SHDWH Heating Coil | `HeatingCoilsDXVariableSpeed` | `OS:Coil:Heating:DX:VariableSpeed` |
| `A13` SHDWH Water Heating Coil | `HeatPumpWaterHeaterDXCoilsVariableSpeed` | `OS:Coil:WaterHeating:AirToWaterHeatPump:VariableSpeed` |

### `OS:ComponentData`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A7` Name of Object | `AllObjects` | 6 targets (suppressed; list is `AllObjects`) |

### `OS:Connection`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A2` Source Object | `ConnectionObject` | 140 targets (suppressed; list is `ConnectionObject`) |
| `A3` Target Object | `ConnectionObject` | 140 targets (suppressed; list is `ConnectionObject`) |

### `OS:Connector:Mixer`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Outlet Branch Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A4` Inlet Branch Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |

### `OS:Connector:Splitter`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Inlet Branch Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A4` Outlet Branch Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |

### `OS:Construction`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Surface Rendering Name | `SurfaceRenderingNames` | `OS:Rendering:Color` |
| `A4` Layer | `MaterialNames` | `OS:Material`, `OS:Material:AirGap`, `OS:Material:InfraredTransparent`, `OS:Material:NoMass`, `OS:Material:RoofVegetation`, `OS:WindowMaterial:Blind`, `OS:WindowMaterial:DaylightRedirectionDevice`, `OS:WindowMaterial:Gas`, `OS:WindowMaterial:GasMixture`, `OS:WindowMaterial:Glazing`, `OS:WindowMaterial:Glazing:RefractionExtinctionMethod`, `OS:WindowMaterial:GlazingGroup:Thermochromic`, `OS:WindowMaterial:Screen`, `OS:WindowMaterial:Shade`, `OS:WindowMaterial:SimpleGlazingSystem` |

### `OS:Construction:AirBoundary`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A4` Simple Mixing Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A5` Surface Rendering Name | `SurfaceRenderingNames` | `OS:Rendering:Color` |

### `OS:Construction:CfactorUndergroundWall`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Surface Rendering Name | `SurfaceRenderingNames` | `OS:Rendering:Color` |

### `OS:Construction:FfactorGroundFloor`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Surface Rendering Name | `SurfaceRenderingNames` | `OS:Rendering:Color` |

### `OS:Construction:InternalSource`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Surface Rendering Name | `SurfaceRenderingNames` | `OS:Rendering:Color` |
| `A4` Layer | `MaterialNames` | `OS:Material`, `OS:Material:AirGap`, `OS:Material:InfraredTransparent`, `OS:Material:NoMass`, `OS:Material:RoofVegetation`, `OS:WindowMaterial:Blind`, `OS:WindowMaterial:DaylightRedirectionDevice`, `OS:WindowMaterial:Gas`, `OS:WindowMaterial:GasMixture`, `OS:WindowMaterial:Glazing`, `OS:WindowMaterial:Glazing:RefractionExtinctionMethod`, `OS:WindowMaterial:GlazingGroup:Thermochromic`, `OS:WindowMaterial:Screen`, `OS:WindowMaterial:Shade`, `OS:WindowMaterial:SimpleGlazingSystem` |

### `OS:Construction:WindowDataFile`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A4` Surface Rendering Name | `SurfaceRenderingNames` | `OS:Rendering:Color` |

### `OS:Controller:MechanicalVentilation`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Availability Schedule | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A6` Thermal Zone | `ThermalZoneNames` | `OS:ThermalZone` |
| `A7` Design Specification Outdoor Air Object | `DesignSpecificationOutdoorAirNames` | `OS:DesignSpecification:OutdoorAir` |
| `A8` Design Specification Zone Air Distribution Object | `DesignSpecificationZoneAirDistributionNames` | `OS:DesignSpecification:ZoneAirDistribution` |

### `OS:Controller:OutdoorAir`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A9` Electronic Enthalpy Limit Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A12` Minimum Outdoor Air Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A13` Minimum Fraction of Outdoor Air Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A14` Maximum Fraction of Outdoor Air Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A15` Controller Mechanical Ventilation | `ControllerMechanicalVentilationNames` | `OS:Controller:MechanicalVentilation` |
| `A16` Time of Day Economizer Control Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A18` Humidistat Control Zone Name | `ThermalZoneNames` | `OS:ThermalZone` |

### `OS:Controller:WaterCoil`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Water Coil Name | `ConnectionObject` | 140 targets (suppressed; list is `ConnectionObject`) |
| `A7` Sensor Node Name | `Node` | `OS:Node` |
| `A8` Actuator Node Name | `Node` | `OS:Node` |

### `OS:CoolingTower:SingleSpeed`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `N10` Evaporation Loss Factor | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `N13` Outdoor Air Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `N13` Outdoor Air Inlet Node Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:CoolingTower:TwoSpeed`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A2` Low Fan Speed U-Factor Times Area Value | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `N22` Evaporation Loss Mode | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `N25` Blowdown Makeup Water Usage Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A10` Supply Water Storage Tank Name | `WaterStorageTankNames` | No `\reference` matches found |
| `A11` Outdoor Air Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |

### `OS:CoolingTower:VariableSpeed`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `N10` Evaporation Loss Mode | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A11` Blowdown Makeup Water Usage Schedule | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A12` Supply Water Storage Tank | `WaterStorageTankNames` | No `\reference` matches found |
| `A13` Outdoor Air Inlet Node | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |

### `OS:Daylighting:Control`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Space Name | `SpaceNames` | `OS:Space` |

### `OS:DaylightingDevice:LightWell`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Exterior Window Name | `SubSurfNames` | `OS:SubSurface` |

### `OS:DaylightingDevice:Shelf`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Window Name | `SubSurfNames` | `OS:SubSurface` |
| `A4` Inside Shelf Name | `InteriorPartitionSurfaceNames` | `OS:InteriorPartitionSurface` |
| `A5` Outside Shelf Name | `AttachedShadingSurfNames` | `OS:ShadingSurface` |

### `OS:DaylightingDevice:Tubular`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Transition Zone Length 1 | `ConstructionNames` | `OS:Construction`, `OS:Construction:AirBoundary`, `OS:Construction:CfactorUndergroundWall`, `OS:Construction:FfactorGroundFloor`, `OS:Construction:InternalSource`, `OS:Construction:WindowDataFile` |
| `A1` Transition Zone Length 1 | `SubSurfNames` | `OS:SubSurface` |
| `A1` Transition Zone Length 1 | `ThermalZoneNames` | `OS:ThermalZone` |

### `OS:DefaultConstructionSet`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Default Exterior Surface Constructions Name | `DefaultSurfaceConstructionsNames` | `OS:DefaultSurfaceConstructions` |
| `A4` Default Interior Surface Constructions Name | `DefaultSurfaceConstructionsNames` | `OS:DefaultSurfaceConstructions` |
| `A5` Default Ground Contact Surface Constructions Name | `DefaultSurfaceConstructionsNames` | `OS:DefaultSurfaceConstructions` |
| `A6` Default Exterior SubSurface Constructions Name | `DefaultSubSurfaceConstructionsNames` | `OS:DefaultSubSurfaceConstructions` |
| `A7` Default Interior SubSurface Constructions Name | `DefaultSubSurfaceConstructionsNames` | `OS:DefaultSubSurfaceConstructions` |
| `A8` Interior Partition Construction Name | `ConstructionNames` | `OS:Construction`, `OS:Construction:AirBoundary`, `OS:Construction:CfactorUndergroundWall`, `OS:Construction:FfactorGroundFloor`, `OS:Construction:InternalSource`, `OS:Construction:WindowDataFile` |
| `A9` Space Shading Construction Name | `ConstructionNames` | `OS:Construction`, `OS:Construction:AirBoundary`, `OS:Construction:CfactorUndergroundWall`, `OS:Construction:FfactorGroundFloor`, `OS:Construction:InternalSource`, `OS:Construction:WindowDataFile` |
| `A10` Building Shading Construction Name | `ConstructionNames` | `OS:Construction`, `OS:Construction:AirBoundary`, `OS:Construction:CfactorUndergroundWall`, `OS:Construction:FfactorGroundFloor`, `OS:Construction:InternalSource`, `OS:Construction:WindowDataFile` |
| `A11` Site Shading Construction Name | `ConstructionNames` | `OS:Construction`, `OS:Construction:AirBoundary`, `OS:Construction:CfactorUndergroundWall`, `OS:Construction:FfactorGroundFloor`, `OS:Construction:InternalSource`, `OS:Construction:WindowDataFile` |
| `A12` Adiabatic Surface Construction Name | `ConstructionNames` | `OS:Construction`, `OS:Construction:AirBoundary`, `OS:Construction:CfactorUndergroundWall`, `OS:Construction:FfactorGroundFloor`, `OS:Construction:InternalSource`, `OS:Construction:WindowDataFile` |

### `OS:DefaultScheduleSet`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Hours of Operation Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A4` Number of People Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A5` People Activity Level Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A6` Lighting Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A7` Electric Equipment Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A8` Gas Equipment Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A9` Hot Water Equipment Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A10` Infiltration Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A11` Steam Equipment Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A12` Other Equipment Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:DefaultSubSurfaceConstructions`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Fixed Window Construction Name | `ConstructionNames` | `OS:Construction`, `OS:Construction:AirBoundary`, `OS:Construction:CfactorUndergroundWall`, `OS:Construction:FfactorGroundFloor`, `OS:Construction:InternalSource`, `OS:Construction:WindowDataFile` |
| `A4` Operable Window Construction Name | `ConstructionNames` | `OS:Construction`, `OS:Construction:AirBoundary`, `OS:Construction:CfactorUndergroundWall`, `OS:Construction:FfactorGroundFloor`, `OS:Construction:InternalSource`, `OS:Construction:WindowDataFile` |
| `A5` Door Construction Name | `ConstructionNames` | `OS:Construction`, `OS:Construction:AirBoundary`, `OS:Construction:CfactorUndergroundWall`, `OS:Construction:FfactorGroundFloor`, `OS:Construction:InternalSource`, `OS:Construction:WindowDataFile` |
| `A6` Glass Door Construction Name | `ConstructionNames` | `OS:Construction`, `OS:Construction:AirBoundary`, `OS:Construction:CfactorUndergroundWall`, `OS:Construction:FfactorGroundFloor`, `OS:Construction:InternalSource`, `OS:Construction:WindowDataFile` |
| `A7` Overhead Door Construction Name | `ConstructionNames` | `OS:Construction`, `OS:Construction:AirBoundary`, `OS:Construction:CfactorUndergroundWall`, `OS:Construction:FfactorGroundFloor`, `OS:Construction:InternalSource`, `OS:Construction:WindowDataFile` |
| `A8` Skylight Construction Name | `ConstructionNames` | `OS:Construction`, `OS:Construction:AirBoundary`, `OS:Construction:CfactorUndergroundWall`, `OS:Construction:FfactorGroundFloor`, `OS:Construction:InternalSource`, `OS:Construction:WindowDataFile` |
| `A9` Tubular Daylight Dome Construction Name | `ConstructionNames` | `OS:Construction`, `OS:Construction:AirBoundary`, `OS:Construction:CfactorUndergroundWall`, `OS:Construction:FfactorGroundFloor`, `OS:Construction:InternalSource`, `OS:Construction:WindowDataFile` |
| `A10` Tubular Daylight Diffuser Construction Name | `ConstructionNames` | `OS:Construction`, `OS:Construction:AirBoundary`, `OS:Construction:CfactorUndergroundWall`, `OS:Construction:FfactorGroundFloor`, `OS:Construction:InternalSource`, `OS:Construction:WindowDataFile` |

### `OS:DefaultSurfaceConstructions`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Floor Construction Name | `ConstructionNames` | `OS:Construction`, `OS:Construction:AirBoundary`, `OS:Construction:CfactorUndergroundWall`, `OS:Construction:FfactorGroundFloor`, `OS:Construction:InternalSource`, `OS:Construction:WindowDataFile` |
| `A4` Wall Construction Name | `ConstructionNames` | `OS:Construction`, `OS:Construction:AirBoundary`, `OS:Construction:CfactorUndergroundWall`, `OS:Construction:FfactorGroundFloor`, `OS:Construction:InternalSource`, `OS:Construction:WindowDataFile` |
| `A5` Roof Ceiling Construction Name | `ConstructionNames` | `OS:Construction`, `OS:Construction:AirBoundary`, `OS:Construction:CfactorUndergroundWall`, `OS:Construction:FfactorGroundFloor`, `OS:Construction:InternalSource`, `OS:Construction:WindowDataFile` |

### `OS:DesignSpecification:OutdoorAir`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A4` Outdoor Air Flow Rate Fraction Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:DesignSpecification:ZoneAirDistribution`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Zone Air Distribution Effectiveness Schedule | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:DistrictHeating:Steam`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Capacity Fraction Schedule | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A1` Capacity Fraction Schedule | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:DistrictHeating:Water`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Capacity Fraction Schedule | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A1` Capacity Fraction Schedule | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:Duct`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Inlet Node | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A4` Outlet Node | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |

### `OS:ElectricEquipment`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Electric Equipment Definition Name | `ElectricEquipmentDefinitionNames` | `OS:ElectricEquipment:Definition` |
| `A4` Space or SpaceType Name | `SpaceAndSpaceTypeNames` | `OS:Space`, `OS:SpaceType` |
| `A5` Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:ElectricEquipment:ITE:AirCooled`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Electric Equipment ITE AirCooled Definition Name | `ElectricEquipmentITEAirCooledDefinitionNames` | `OS:ElectricEquipment:ITE:AirCooled:Definition` |
| `A4` Space or SpaceType Name | `SpaceAndSpaceTypeNames` | `OS:Space`, `OS:SpaceType` |
| `A5` Design Power Input Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A6` CPU Loading Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:ElectricEquipment:ITE:AirCooled:Definition`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Design Fan Power Input Fraction | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `N4` Fan Power Input Function of Flow Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `N4` Fan Power Input Function of Flow Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A10` Design Electric Power Supply Efficiency | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A11` Fraction of Electric Power Supply Losses to Zone | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A12` Supply Temperature Difference Schedule | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A13` Return Temperature Difference Schedule | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:ElectricLoadCenter:Distribution`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A10` Transformer Object Name | `TransformerNames` | `OS:ElectricLoadCenter:Transformer` |
| `A13` Design Storage Control Charge Power | `ConverterList` | No `\reference` matches found |
| `A14` Design Storage Control Discharge Power | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A15` Storage Discharge Power Fraction Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A16` Storage Control Utility Demand Target Fraction Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:ElectricLoadCenter:Storage:Converter`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `N2` Radiative Fraction | `ThermalZoneNames` | `OS:ThermalZone` |
| `N2` Radiative Fraction | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |

### `OS:ElectricLoadCenter:Storage:LiIonNMCBattery`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Availability Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A4` Zone Name | `ThermalZoneNames` | `OS:ThermalZone` |

### `OS:ElectricLoadCenter:Storage:Simple`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Availability Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A4` Radiative Fraction for Zone Heat Gains | `ThermalZoneNames` | `OS:ThermalZone` |

### `OS:ElectricLoadCenter:Transformer`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Availability Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A5` Zone Name | `ThermalZoneNames` | `OS:ThermalZone` |

### `OS:EnergyManagementSystem:Actuator`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Actuated Component Name | `AllObjects` | 6 targets (suppressed; list is `AllObjects`) |
| `A6` Zone or Space Name | `SpaceNames` | `OS:Space` |
| `A6` Zone or Space Name | `ThermalZoneNames` | `OS:ThermalZone` |

### `OS:EnergyManagementSystem:ConstructionIndexVariable`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Construction Object Name | `ConstructionNames` | `OS:Construction`, `OS:Construction:AirBoundary`, `OS:Construction:CfactorUndergroundWall`, `OS:Construction:FfactorGroundFloor`, `OS:Construction:InternalSource`, `OS:Construction:WindowDataFile` |

### `OS:EnergyManagementSystem:CurveOrTableIndexVariable`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Curve or Table Object Name | `AllCurves` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:FanPressureRise`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:QuadLinear`, `OS:Curve:Quadratic`, `OS:Curve:QuadraticLinear`, `OS:Curve:Quartic`, `OS:Curve:QuintLinear`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Curve:Triquadratic`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |

### `OS:EnergyManagementSystem:MeteredOutputVariable`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A5` EMS Program or Subroutine Name | `ErlProgramSubroutineNames` | `OS:EnergyManagementSystem:Program`, `OS:EnergyManagementSystem:Subroutine` |

### `OS:EnergyManagementSystem:OutputVariable`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A6` EMS Program or Subroutine Name | `ErlProgramSubroutineNames` | `OS:EnergyManagementSystem:Program`, `OS:EnergyManagementSystem:Subroutine` |

### `OS:EnergyManagementSystem:ProgramCallingManager`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A4` Program Name | `ErlProgramNames` | `OS:EnergyManagementSystem:Program` |

### `OS:EnergyManagementSystem:TrendVariable`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` EMS Variable Name | `ErlVariableNames` | `OS:EnergyManagementSystem:Actuator`, `OS:EnergyManagementSystem:ConstructionIndexVariable`, `OS:EnergyManagementSystem:CurveOrTableIndexVariable`, `OS:EnergyManagementSystem:GlobalVariable`, `OS:EnergyManagementSystem:InternalVariable`, `OS:EnergyManagementSystem:Sensor`, `OS:EnergyManagementSystem:TrendVariable`, `OS:ExternalInterface:Actuator`, `OS:ExternalInterface:FunctionalMockupUnitExport:To:Actuator`, `OS:ExternalInterface:FunctionalMockupUnitExport:To:Variable`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Actuator`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Variable`, `OS:ExternalInterface:Variable` |

### `OS:EvaporativeCooler:Direct:ResearchSpecial`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Availability Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A4` Air Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A5` Air Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A6` Sensor Node Name | `Node` | `OS:Node` |
| `A7` Effectiveness Flow Ratio Modifier Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A8` Water Pump Power Modifier Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |

### `OS:EvaporativeCooler:Indirect:ResearchSpecial`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Dewpoint Effectiveness Factor | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A1` Dewpoint Effectiveness Factor | `Node` | `OS:Node` |
| `A1` Dewpoint Effectiveness Factor | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A10` Primary Design Air Flow Rate | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A10` Primary Design Air Flow Rate | `WaterStorageTankNames` | No `\reference` matches found |

### `OS:EvaporativeFluidCooler:SingleSpeed`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Standard Design Capacity | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |

### `OS:Exterior:FuelEquipment`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Exterior Fuel Equipment Definition Name | `ExteriorFuelEquipmentDefinitionNames` | `OS:Exterior:FuelEquipment:Definition` |
| `A4` Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:Exterior:Lights`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Exterior Lights Definition Name | `ExteriorLightsDefinitionNames` | `OS:Exterior:Lights:Definition` |
| `A4` Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:Exterior:WaterEquipment`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Exterior Water Equipment Definition Name | `ExteriorWaterEquipmentDefinitionNames` | `OS:Exterior:WaterEquipment:Definition` |
| `A4` Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:ExternalInterface:Actuator`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Actuated Component Control Type | `AllObjects` | 6 targets (suppressed; list is `AllObjects`) |

### `OS:ExternalInterface:FunctionalMockupUnitExport:To:Actuator`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Initial Value | `AllObjects` | 6 targets (suppressed; list is `AllObjects`) |

### `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Initial Value | `ScheduleTypeLimitsNames` | `OS:ScheduleTypeLimits` |

### `OS:ExternalInterface:FunctionalMockupUnitImport:From:Variable`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` FMU Variable Name | `FMUFileName` | `OS:ExternalInterface:FunctionalMockupUnitImport` |

### `OS:ExternalInterface:FunctionalMockupUnitImport:To:Actuator`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Initial Value | `AllObjects` | 6 targets (suppressed; list is `AllObjects`) |
| `A1` Initial Value | `FMUFileName` | `OS:ExternalInterface:FunctionalMockupUnitImport` |

### `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Initial Value | `FMUFileName` | `OS:ExternalInterface:FunctionalMockupUnitImport` |
| `A1` Initial Value | `ScheduleTypeLimitsNames` | `OS:ScheduleTypeLimits` |

### `OS:ExternalInterface:FunctionalMockupUnitImport:To:Variable`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Initial Value | `FMUFileName` | `OS:ExternalInterface:FunctionalMockupUnitImport` |

### `OS:ExternalInterface:Schedule`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Schedule Type Limits Name | `ScheduleTypeLimitsNames` | `OS:ScheduleTypeLimits` |

### `OS:Fan:ComponentModel`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Normalized Fan Static Efficiency Curve Name-Non-Stall Region | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A1` Normalized Fan Static Efficiency Curve Name-Non-Stall Region | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A1` Normalized Fan Static Efficiency Curve Name-Non-Stall Region | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A1` Normalized Fan Static Efficiency Curve Name-Non-Stall Region | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A10` End-Use Subcategory | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |

### `OS:Fan:ConstantVolume`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Availability Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A4` Air Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A5` Air Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |

### `OS:Fan:OnOff`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Availability Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A4` Air Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A5` Air Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A6` Fan Power Ratio Function of Speed Ratio Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A7` Fan Efficiency Ratio Function of Speed Ratio Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |

### `OS:Fan:SystemModel`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Electric Power Per Unit Flow Rate Per Unit Pressure | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A1` Electric Power Per Unit Flow Rate Per Unit Pressure | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `N9` Electric Power Function of Flow Fraction Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `N11` Motor Loss Zone Name | `ThermalZoneNames` | `OS:ThermalZone` |

### `OS:Fan:VariableVolume`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Availability Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A4` Air Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A5` Air Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |

### `OS:Fan:ZoneExhaust`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Availability Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A4` Air Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A5` Air Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A7` Flow Fraction Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A9` Minimum Zone Temperature Limit Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A10` Balanced Exhaust Fraction Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:FluidCooler:SingleSpeed`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Water Inlet Node | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A4` Water Outlet Node | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `N8` Outdoor Air Inlet Node | `Node` | `OS:Node` |

### `OS:FluidCooler:TwoSpeed`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Water Inlet Node | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A4` Water Outlet Node | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A6` Outdoor Air Inlet Node | `Node` | `OS:Node` |

### `OS:Foundation:Kiva`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Interior Horizontal Insulation Material Name | `MaterialNames` | `OS:Material`, `OS:Material:AirGap`, `OS:Material:InfraredTransparent`, `OS:Material:NoMass`, `OS:Material:RoofVegetation`, `OS:WindowMaterial:Blind`, `OS:WindowMaterial:DaylightRedirectionDevice`, `OS:WindowMaterial:Gas`, `OS:WindowMaterial:GasMixture`, `OS:WindowMaterial:Glazing`, `OS:WindowMaterial:Glazing:RefractionExtinctionMethod`, `OS:WindowMaterial:GlazingGroup:Thermochromic`, `OS:WindowMaterial:Screen`, `OS:WindowMaterial:Shade`, `OS:WindowMaterial:SimpleGlazingSystem` |
| `A4` Interior Vertical Insulation Material Name | `MaterialNames` | `OS:Material`, `OS:Material:AirGap`, `OS:Material:InfraredTransparent`, `OS:Material:NoMass`, `OS:Material:RoofVegetation`, `OS:WindowMaterial:Blind`, `OS:WindowMaterial:DaylightRedirectionDevice`, `OS:WindowMaterial:Gas`, `OS:WindowMaterial:GasMixture`, `OS:WindowMaterial:Glazing`, `OS:WindowMaterial:Glazing:RefractionExtinctionMethod`, `OS:WindowMaterial:GlazingGroup:Thermochromic`, `OS:WindowMaterial:Screen`, `OS:WindowMaterial:Shade`, `OS:WindowMaterial:SimpleGlazingSystem` |
| `A5` Exterior Horizontal Insulation Material Name | `MaterialNames` | `OS:Material`, `OS:Material:AirGap`, `OS:Material:InfraredTransparent`, `OS:Material:NoMass`, `OS:Material:RoofVegetation`, `OS:WindowMaterial:Blind`, `OS:WindowMaterial:DaylightRedirectionDevice`, `OS:WindowMaterial:Gas`, `OS:WindowMaterial:GasMixture`, `OS:WindowMaterial:Glazing`, `OS:WindowMaterial:Glazing:RefractionExtinctionMethod`, `OS:WindowMaterial:GlazingGroup:Thermochromic`, `OS:WindowMaterial:Screen`, `OS:WindowMaterial:Shade`, `OS:WindowMaterial:SimpleGlazingSystem` |
| `A6` Exterior Vertical Insulation Material Name | `MaterialNames` | `OS:Material`, `OS:Material:AirGap`, `OS:Material:InfraredTransparent`, `OS:Material:NoMass`, `OS:Material:RoofVegetation`, `OS:WindowMaterial:Blind`, `OS:WindowMaterial:DaylightRedirectionDevice`, `OS:WindowMaterial:Gas`, `OS:WindowMaterial:GasMixture`, `OS:WindowMaterial:Glazing`, `OS:WindowMaterial:Glazing:RefractionExtinctionMethod`, `OS:WindowMaterial:GlazingGroup:Thermochromic`, `OS:WindowMaterial:Screen`, `OS:WindowMaterial:Shade`, `OS:WindowMaterial:SimpleGlazingSystem` |
| `A7` Footing Wall Construction Name | `ConstructionNames` | `OS:Construction`, `OS:Construction:AirBoundary`, `OS:Construction:CfactorUndergroundWall`, `OS:Construction:FfactorGroundFloor`, `OS:Construction:InternalSource`, `OS:Construction:WindowDataFile` |
| `A8` Footing Material Name | `MaterialNames` | `OS:Material`, `OS:Material:AirGap`, `OS:Material:InfraredTransparent`, `OS:Material:NoMass`, `OS:Material:RoofVegetation`, `OS:WindowMaterial:Blind`, `OS:WindowMaterial:DaylightRedirectionDevice`, `OS:WindowMaterial:Gas`, `OS:WindowMaterial:GasMixture`, `OS:WindowMaterial:Glazing`, `OS:WindowMaterial:Glazing:RefractionExtinctionMethod`, `OS:WindowMaterial:GlazingGroup:Thermochromic`, `OS:WindowMaterial:Screen`, `OS:WindowMaterial:Shade`, `OS:WindowMaterial:SimpleGlazingSystem` |
| `A9` Custom Block Material Name 1 | `MaterialNames` | `OS:Material`, `OS:Material:AirGap`, `OS:Material:InfraredTransparent`, `OS:Material:NoMass`, `OS:Material:RoofVegetation`, `OS:WindowMaterial:Blind`, `OS:WindowMaterial:DaylightRedirectionDevice`, `OS:WindowMaterial:Gas`, `OS:WindowMaterial:GasMixture`, `OS:WindowMaterial:Glazing`, `OS:WindowMaterial:Glazing:RefractionExtinctionMethod`, `OS:WindowMaterial:GlazingGroup:Thermochromic`, `OS:WindowMaterial:Screen`, `OS:WindowMaterial:Shade`, `OS:WindowMaterial:SimpleGlazingSystem` |

### `OS:FuelFactors`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Source Energy Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A4` CO2 Emission Factor Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A5` CO Emission Factor Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A6` CH4 Emission Factor Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A7` NOx Emission Factor Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A8` N2O Emission Factor Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A9` SO2 Emission Factor Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A10` PM Emission Factor Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A11` PM10 Emission Factor Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A12` PM2.5 Emission Factor Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A13` NH3 Emission Factor Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A14` NMVOC Emission Factor Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A15` Hg Emission Factor Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A16` Pb Emission Factor Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A17` Water Emission Factor Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A18` Nuclear High Level Emission Factor Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A19` Nuclear Low Level Emission Factor Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:GasEquipment`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Gas Equipment Definition Name | `GasEquipmentDefinitionNames` | `OS:GasEquipment:Definition` |
| `A4` Space or SpaceType Name | `SpaceAndSpaceTypeNames` | `OS:Space`, `OS:SpaceType` |
| `A5` Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:Generator:FuelCell`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Power Module Name | `FCPMNames` | `OS:Generator:FuelCell:PowerModule` |
| `A4` Air Supply Name | `FCAirSupNames` | `OS:Generator:FuelCell:AirSupply` |
| `A5` Fuel Supply Name | `GenFuelSupNames` | `OS:Generator:FuelSupply` |
| `A6` Water Supply Name | `FCWaterSupNames` | `OS:Generator:FuelCell:WaterSupply` |
| `A7` Auxiliary Heater Name | `FCAuxHeatNames` | `OS:Generator:FuelCell:AuxiliaryHeater` |
| `A8` Heat Exchanger Name | `FCExhaustHXNames` | `OS:Generator:FuelCell:ExhaustGasToWaterHeatExchanger` |
| `A9` Electrical Storage Name | `FCStorageNames` | `OS:Generator:FuelCell:ElectricalStorage` |
| `A10` Inverter Name | `FCInverterNames` | `OS:Generator:FuelCell:Inverter` |
| `A11` Stack Cooler Name | `FCStackCoolerNames` | `OS:Generator:FuelCell:StackCooler` |

### `OS:Generator:FuelCell:AirSupply`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Air Inlet Node Name | `Node` | `OS:Node` |
| `A4` Blower Power Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A6` Air Rate Function of Electric Power Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A7` Air Rate Function of Fuel Rate Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |

### `OS:Generator:FuelCell:AuxiliaryHeater`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A4` Zone Name to Receive Skin Losses | `ThermalZoneNames` | `OS:ThermalZone` |

### `OS:Generator:FuelCell:ExhaustGasToWaterHeatExchanger`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Heat Recovery Water Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A4` Heat Recovery Water Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A5` Exhaust Outlet Air Node Name | `Node` | `OS:Node` |

### `OS:Generator:FuelCell:Inverter`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A4` Efficiency Function of DC Power Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |

### `OS:Generator:FuelCell:PowerModule`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A4` Efficiency Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A6` Zone Name | `ThermalZoneNames` | `OS:ThermalZone` |
| `A7` Skin Loss Quadratic Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A8` Dilution Outlet Air Node Name | `Node` | `OS:Node` |

### `OS:Generator:FuelCell:StackCooler`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Heat Recovery Water Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A4` Heat Recovery Water Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |

### `OS:Generator:FuelCell:WaterSupply`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Reformer Water Flow Rate Function of Fuel Rate Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A4` Reformer Water Pump Power Function of Fuel Rate Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A6` Water Temperature Reference Node Name | `Node` | `OS:Node` |
| `A7` Water Temperature Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:Generator:FuelSupply`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A4` Fuel Temperature Reference Node Name | `Node` | `OS:Node` |
| `A5` Fuel Temperature Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A6` Compressor Power Multiplier Function of Fuel Rate Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |

### `OS:Generator:MicroTurbine`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Availability Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A4` Electrical Power Function of Temperature and Elevation Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A5` Electrical Efficiency Function of Temperature Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A6` Electrical Efficiency Function of Part Load Ratio Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A8` Ancillary Power Function of Fuel Input Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A9` Generator MicroTurbine Heat Recovery Name | `MicroTurbineHeatRecoveryNames` | `OS:Generator:MicroTurbine:HeatRecovery` |
| `A10` Combustion Air Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A11` Combustion Air Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A12` Exhaust Air Flow Rate Function of Temperature Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A13` Exhaust Air Flow Rate Function of Part Load Ratio Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A14` Exhaust Air Temperature Function of Temperature Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A15` Exhaust Air Temperature Function of Part Load Ratio Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |

### `OS:Generator:MicroTurbine:HeatRecovery`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Heat Recovery Water Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A4` Heat Recovery Rate Function of Inlet Water Temperature Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A4` Heat Recovery Rate Function of Inlet Water Temperature Curve Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A4` Heat Recovery Rate Function of Inlet Water Temperature Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A10` Heat Recovery Rate Function of Water Flow Rate Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |

### `OS:Generator:PVWatts`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A6` Surface Name | `AllShadingAndHTSurfNames` | `OS:ShadingSurface`, `OS:SubSurface`, `OS:Surface` |

### `OS:Generator:WindTurbine`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Availability Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:Glare:Sensor`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Space Name | `SpaceNames` | `OS:Space` |

### `OS:GroundHeatExchanger:HorizontalTrench`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Soil Density | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A5` Undisturbed Ground Temperature Model | `UndisturbedGroundTempModels` | `OS:Site:GroundTemperature:Undisturbed:KusudaAchenbach`, `OS:Site:GroundTemperature:Undisturbed:Xing` |

### `OS:GroundHeatExchanger:Vertical`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A4` Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A5` Undisturbed Ground Temperature Model | `UndisturbedGroundTempModels` | `OS:Site:GroundTemperature:Undisturbed:KusudaAchenbach`, `OS:Site:GroundTemperature:Undisturbed:Xing` |

### `OS:HVACComponentList`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A2` HVACComponent 1 | `AllObjects` | 6 targets (suppressed; list is `AllObjects`) |

### `OS:HeaderedPumps:ConstantSpeed`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Skin Loss Radiative Fraction | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A1` Skin Loss Radiative Fraction | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A1` Skin Loss Radiative Fraction | `ThermalZoneNames` | `OS:ThermalZone` |

### `OS:HeaderedPumps:VariableSpeed`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Coefficient 3 of the Part Load Performance Curve | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `N11` Thermal Zone | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `N11` Thermal Zone | `ThermalZoneNames` | `OS:ThermalZone` |

### `OS:HeatExchanger:AirToAir:SensibleAndLatent`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Availability Schedule | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A4` Supply Air Inlet Node | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A5` Supply Air Outlet Node | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A6` Exhaust Air Inlet Node | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A7` Exhaust Air Outlet Node | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A12` Sensible Effectiveness of Heating Air Flow Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A13` Latent Effectiveness of Heating Air Flow Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A14` Sensible Effectiveness of Cooling Air Flow Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A15` Latent Effectiveness of Cooling Air Flow Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |

### `OS:HeatExchanger:Desiccant:BalancedFlow`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Availability Schedule | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A4` Regeneration Air Inlet Node | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A5` Regeneration Air Outlet Node | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A6` Process Air Inlet Node | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A7` Process Air Outlet Node | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A8` Heat Exchanger Performance | `DesiccantHXPerfData` | No `\reference` matches found |

### `OS:HeatExchanger:FluidToFluid`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A12` Component Override Loop Supply Side Inlet Node | `Node` | `OS:Node` |
| `A13` Component Override Loop Demand Side Inlet Node | `Node` | `OS:Node` |

### `OS:HeatPump:AirToWater`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A5` Operating Mode Control Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A9` Defrost Energy Input Ratio Function of Temperature Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A11` Crankcase Heater Capacity Function of Temperature Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A12` Heating Operation Mode | `HeatPumpAirToWaterHeating` | `OS:HeatPump:AirToWater:Heating` |
| `A13` Cooling Operation Mode | `HeatPumpAirToWaterCooling` | `OS:HeatPump:AirToWater:Cooling` |

### `OS:HeatPump:AirToWater:Cooling`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Availability Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A4` Minimum Leaving Water Temperature Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A5` Maximum Leaving Water Temperature Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A6` Chilled Water Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A7` Chilled Water Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A8` Speed Data List | `ModelObjectLists` | `OS:ModelObjectList` |
| `A9` Booster Mode On Speed | `HeatPumpAirToWaterCoolingSpeedData` | `OS:HeatPump:AirToWater:Cooling:SpeedData` |

### `OS:HeatPump:AirToWater:Cooling:SpeedData`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Normalized Cooling Capacity Function of Temperature Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A4` Cooling Energy Input Ratio Function of Temperature Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A5` Cooling Energy Input Ratio Function of PLR Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |

### `OS:HeatPump:AirToWater:FuelFired:Cooling`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Water Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A4` Water Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A5` Air Source Node Name | `OutdoorAirNodeNames` | No `\reference` matches found |
| `A6` Companion Heating Heat Pump Name | `HeatPumpAirToWaterFuelFiredHeatingNames` | `OS:HeatPump:AirToWater:FuelFired:Heating` |

### `OS:HeatPump:AirToWater:FuelFired:Heating`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Water Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A4` Water Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A5` Air Source Node Name | `OutdoorAirNodeNames` | No `\reference` matches found |
| `A6` Companion Cooling Heat Pump Name | `HeatPumpAirToWaterFuelFiredCoolingNames` | `OS:HeatPump:AirToWater:FuelFired:Cooling` |

### `OS:HeatPump:AirToWater:Heating`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Availability Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A4` Minimum Leaving Water Temperature Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A5` Maximum Leaving Water Temperature Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A6` Hot Water Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A7` Hot Water Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A8` Speed Data List | `ModelObjectLists` | `OS:ModelObjectList` |
| `A9` Booster Mode On Speed | `HeatPumpAirToWaterHeatingSpeedData` | `OS:HeatPump:AirToWater:Heating:SpeedData` |

### `OS:HeatPump:AirToWater:Heating:SpeedData`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Normalized Heating Capacity Function of Temperature Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A4` Heating Energy Input Ratio Function of Temperature Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A5` Heating Energy Input Ratio Function of PLR Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |

### `OS:HeatPump:PlantLoop:EIR:Cooling`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Load Side Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A4` Load Side Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A6` Source Side Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A7` Source Side Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A8` Heat Recovery Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A9` Heat Recovery Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A10` Companion Heat Pump Name | `PLHPHeatingNames` | `OS:HeatPump:PlantLoop:EIR:Heating` |
| `A11` Capacity Modifier Function of Temperature Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A12` Electric Input to Output Ratio Modifier Function of Temperature Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A13` Electric Input to Output Ratio Modifier Function of Part Load Ratio Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `N10` Minimum Supply Water Temperature Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `N11` Maximum Supply Water Temperature Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A16` Heat Recovery Capacity Modifier Function of Temperature Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A17` Heat Recovery Electric Input to Output Ratio Modifier Function of Temperature Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A18` Thermosiphon Capacity Fraction Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |

### `OS:HeatPump:PlantLoop:EIR:Heating`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Load Side Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A4` Load Side Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A6` Source Side Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A7` Source Side Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A8` Heat Recovery Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A9` Heat Recovery Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A10` Companion Heat Pump Name | `PLHPCoolingNames` | `OS:HeatPump:PlantLoop:EIR:Cooling` |
| `A11` Capacity Modifier Function of Temperature Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A12` Electric Input to Output Ratio Modifier Function of Temperature Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A13` Electric Input to Output Ratio Modifier Function of Part Load Ratio Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A17` Minimum Supply Water Temperature Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A18` Maximum Supply Water Temperature Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A19` Dry Outdoor Correction Factor Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A21` Defrost Energy Input Ratio Function of Temperature Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A22` Timed Empirical Defrost Frequency Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A23` Timed Empirical Defrost Heat Load Penalty Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A23` Timed Empirical Defrost Heat Load Penalty Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A24` Timed Empirical Defrost Heat Input Energy Fraction Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A24` Timed Empirical Defrost Heat Input Energy Fraction Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A25` Heat Recovery Capacity Modifier Function of Temperature Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A26` Heat Recovery Electric Input to Output Ratio Modifier Function of Temperature Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |

### `OS:HeatPump:WaterToWater:EquationFit:Cooling`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Source Side Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A4` Source Side Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A5` Load Side Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A6` Load Side Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A7` Cooling Capacity Curve Name | `QuadvariateFunctions` | `OS:Curve:QuadLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A8` Cooling Compressor Power Curve Name | `QuadvariateFunctions` | `OS:Curve:QuadLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `N6` Companion Heating Heat Pump Name | `WWHPHeatingNames` | `OS:HeatPump:WaterToWater:EquationFit:Heating` |

### `OS:HeatPump:WaterToWater:EquationFit:Heating`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Source Side Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A4` Source Side Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A5` Load Side Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A6` Load Side Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A7` Heating Capacity Curve Name | `QuadvariateFunctions` | `OS:Curve:QuadLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A8` Heating Compressor Power Curve Name | `QuadvariateFunctions` | `OS:Curve:QuadLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `N6` Companion Cooling Heat Pump Name | `WWHPCoolingNames` | `OS:HeatPump:WaterToWater:EquationFit:Cooling` |

### `OS:HotWaterEquipment`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Hot Water Equipment Definition Name | `HotWaterEquipmentDefinitionNames` | `OS:HotWaterEquipment:Definition` |
| `A4` Space or SpaceType Name | `SpaceAndSpaceTypeNames` | `OS:Space`, `OS:SpaceType` |
| `A5` Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:Humidifier:Steam:Electric`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Availability Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A4` Air Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A5` Air Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A6` Water Storage Tank Name | `WaterStorageTankNames` | No `\reference` matches found |

### `OS:Humidifier:Steam:Gas`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Availability Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A4` Thermal Efficiency Modifier Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A5` Air Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A6` Air Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A7` Water Storage Tank Name | `WaterStorageTankNames` | No `\reference` matches found |

### `OS:IlluminanceMap`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Space Name | `SpaceNames` | `OS:Space` |

### `OS:InteriorPartitionSurface`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Construction Name | `ConstructionNames` | `OS:Construction`, `OS:Construction:AirBoundary`, `OS:Construction:CfactorUndergroundWall`, `OS:Construction:FfactorGroundFloor`, `OS:Construction:InternalSource`, `OS:Construction:WindowDataFile` |
| `A4` Interior Partition Surface Group Name | `InteriorPartitionSurfaceGroupNames` | `OS:InteriorPartitionSurfaceGroup` |

### `OS:InteriorPartitionSurfaceGroup`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Space Name | `SpaceNames` | `OS:Space` |

### `OS:InternalMass`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Internal Mass Definition Name | `InternalMassDefinitionNames` | `OS:InternalMass:Definition` |
| `A4` Space or SpaceType Name | `SpaceAndSpaceTypeNames` | `OS:Space`, `OS:SpaceType` |

### `OS:InternalMass:Definition`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Construction Name | `ConstructionNames` | `OS:Construction`, `OS:Construction:AirBoundary`, `OS:Construction:CfactorUndergroundWall`, `OS:Construction:FfactorGroundFloor`, `OS:Construction:InternalSource`, `OS:Construction:WindowDataFile` |

### `OS:LifeCycleCost`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A5` Item Name | `AllObjects` | 6 targets (suppressed; list is `AllObjects`) |

### `OS:LightingSimulationZone`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Group Rendering Name | `GroupRenderingNames` | `OS:Rendering:Color` |
| `A4` Planar Surface Group Name | `PlanarSurfaceGroupNames` | `OS:InteriorPartitionSurfaceGroup`, `OS:ShadingSurfaceGroup`, `OS:Space` |

### `OS:Lights`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Lights Definition Name | `LightsDefinitionNames` | `OS:Lights:Definition` |
| `A4` Space or SpaceType Name | `SpaceAndSpaceTypeNames` | `OS:Space`, `OS:SpaceType` |
| `A5` Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:Luminaire`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Luminaire Definition Name | `LuminaireDefinitionNames` | `OS:Luminaire:Definition` |
| `A4` Space or SpaceType Name | `SpaceAndSpaceTypeNames` | `OS:Space`, `OS:SpaceType` |
| `A5` Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:MaterialProperty:MoisturePenetrationDepth:Settings`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A2` Material Name | `MaterialWithPropertyNames` | `OS:Material`, `OS:Material:NoMass` |

### `OS:MaterialProperty:PhaseChange`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A2` Material Name | `MaterialWithPropertyNames` | `OS:Material`, `OS:Material:NoMass` |

### `OS:MaterialProperty:PhaseChangeHysteresis`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A2` Material Name | `MaterialWithPropertyNames` | `OS:Material`, `OS:Material:NoMass` |

### `OS:ModelObjectList`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Model Object 1 | `AllObjects` | 6 targets (suppressed; list is `AllObjects`) |

### `OS:Node`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `N1` Inlet Port | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `N2` Outlet Port | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |

### `OS:OtherEquipment`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Other Equipment Definition Name | `OtherEquipmentDefinitionNames` | `OS:OtherEquipment:Definition` |
| `A4` Space or SpaceType Name | `SpaceAndSpaceTypeNames` | `OS:Space`, `OS:SpaceType` |
| `A5` Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:Output:Table:Annual`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A4` Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:Output:Variable`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A6` Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:People`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` People Definition Name | `PeopleDefinitionNames` | `OS:People:Definition` |
| `A4` Space or SpaceType Name | `SpaceAndSpaceTypeNames` | `OS:Space`, `OS:SpaceType` |
| `A5` Number of People Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A6` Activity Level Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A7` Surface Name/Angle Factor List Name | `AllHeatTranAngFacNames` | `OS:InternalMass`, `OS:SubSurface`, `OS:Surface` |
| `A8` Work Efficiency Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A10` Clothing Insulation Calculation Method Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A11` Clothing Insulation Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A12` Air Velocity Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A13` Ankle Level Air Velocity Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:Pipe:Adiabatic`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A4` Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |

### `OS:Pipe:Indoor`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Construction | `ConstructionNames` | `OS:Construction`, `OS:Construction:AirBoundary`, `OS:Construction:CfactorUndergroundWall`, `OS:Construction:FfactorGroundFloor`, `OS:Construction:InternalSource`, `OS:Construction:WindowDataFile` |
| `A4` Fluid Inlet Node | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A5` Fluid Outlet Node | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A7` Ambient Temperature Zone | `ThermalZoneNames` | `OS:ThermalZone` |
| `A8` Ambient Temperature Schedule | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A9` Ambient Air Velocity Schedule | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:Pipe:Outdoor`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Construction | `ConstructionNames` | `OS:Construction`, `OS:Construction:AirBoundary`, `OS:Construction:CfactorUndergroundWall`, `OS:Construction:FfactorGroundFloor`, `OS:Construction:InternalSource`, `OS:Construction:WindowDataFile` |
| `A4` Fluid Inlet Node | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A5` Fluid Outlet Node | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A6` Ambient Temperature Outdoor Air Node | `Node` | `OS:Node` |

### `OS:PlantComponent:UserDefined`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Main Model Program Calling Manager Name | `ErlProgramCallingManagerNames` | `OS:EnergyManagementSystem:ProgramCallingManager` |
| `A4` Main Model Program Name | `ErlProgramNames` | `OS:EnergyManagementSystem:Program` |
| `A5` Plant Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A6` Plant Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A9` Plant Initialization Program Calling Manager Name | `ErlProgramCallingManagerNames` | `OS:EnergyManagementSystem:ProgramCallingManager` |
| `A10` Plant Initialization Program Name | `ErlProgramNames` | `OS:EnergyManagementSystem:Program` |
| `A11` Plant Simulation Program Calling Manager Name | `ErlProgramCallingManagerNames` | `OS:EnergyManagementSystem:ProgramCallingManager` |
| `A12` Plant Simulation Program Name | `ErlProgramNames` | `OS:EnergyManagementSystem:Program` |
| `A13` Design Volume Flow Rate Actuator | `ErlActuatorNames` | `OS:EnergyManagementSystem:Actuator` |
| `A14` Minimum Mass Flow Rate Actuator | `ErlActuatorNames` | `OS:EnergyManagementSystem:Actuator` |
| `A15` Maximum Mass Flow Rate Actuator | `ErlActuatorNames` | `OS:EnergyManagementSystem:Actuator` |
| `A16` Minimum Loading Capacity Actuator | `ErlActuatorNames` | `OS:EnergyManagementSystem:Actuator` |
| `A17` Maximum Loading Capacity Actuator | `ErlActuatorNames` | `OS:EnergyManagementSystem:Actuator` |
| `A18` Optimal Loading Capacity Actuator | `ErlActuatorNames` | `OS:EnergyManagementSystem:Actuator` |
| `A19` Outlet Temperature Actuator | `ErlActuatorNames` | `OS:EnergyManagementSystem:Actuator` |
| `A20` Mass Flow Rate Actuator | `ErlActuatorNames` | `OS:EnergyManagementSystem:Actuator` |

### `OS:PlantEquipmentOperation:CoolingLoad`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Range 1 Equipment List Name | `ModelObjectLists` | `OS:ModelObjectList` |

### `OS:PlantEquipmentOperation:HeatingLoad`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Range 1 Equipment List Name | `ModelObjectLists` | `OS:ModelObjectList` |

### `OS:PlantEquipmentOperation:OutdoorDewpoint`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Range 1 Equipment List Name | `ModelObjectLists` | `OS:ModelObjectList` |

### `OS:PlantEquipmentOperation:OutdoorDewpointDifference`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Reference Temperature Node Name | `Node` | `OS:Node` |
| `A4` Range 1 Equipment List Name | `ModelObjectLists` | `OS:ModelObjectList` |

### `OS:PlantEquipmentOperation:OutdoorDryBulb`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Range 1 Equipment List Name | `ModelObjectLists` | `OS:ModelObjectList` |

### `OS:PlantEquipmentOperation:OutdoorDryBulbDifference`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Reference Temperature Node Name | `Node` | `OS:Node` |
| `A4` Range 1 Equipment List Name | `ModelObjectLists` | `OS:ModelObjectList` |

### `OS:PlantEquipmentOperation:OutdoorRelativeHumidity`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Range 1 Equipment List Name | `ModelObjectLists` | `OS:ModelObjectList` |

### `OS:PlantEquipmentOperation:OutdoorWetBulb`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Range 1 Equipment List Name | `ModelObjectLists` | `OS:ModelObjectList` |

### `OS:PlantEquipmentOperation:OutdoorWetBulbDifference`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Reference Temperature Node Name | `Node` | `OS:Node` |
| `A4` Range 1 Equipment List Name | `ModelObjectLists` | `OS:ModelObjectList` |

### `OS:PlantLoop`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A5` Plant Equipment Operation Heating Load | `ControlSchemeList` | `OS:PlantEquipmentOperation:CoolingLoad`, `OS:PlantEquipmentOperation:HeatingLoad`, `OS:PlantEquipmentOperation:OutdoorDewpoint`, `OS:PlantEquipmentOperation:OutdoorDewpointDifference`, `OS:PlantEquipmentOperation:OutdoorDryBulb`, `OS:PlantEquipmentOperation:OutdoorDryBulbDifference`, `OS:PlantEquipmentOperation:OutdoorRelativeHumidity`, `OS:PlantEquipmentOperation:OutdoorWetBulb`, `OS:PlantEquipmentOperation:OutdoorWetBulbDifference` |
| `A6` Plant Equipment Operation Cooling Load | `ControlSchemeList` | `OS:PlantEquipmentOperation:CoolingLoad`, `OS:PlantEquipmentOperation:HeatingLoad`, `OS:PlantEquipmentOperation:OutdoorDewpoint`, `OS:PlantEquipmentOperation:OutdoorDewpointDifference`, `OS:PlantEquipmentOperation:OutdoorDryBulb`, `OS:PlantEquipmentOperation:OutdoorDryBulbDifference`, `OS:PlantEquipmentOperation:OutdoorRelativeHumidity`, `OS:PlantEquipmentOperation:OutdoorWetBulb`, `OS:PlantEquipmentOperation:OutdoorWetBulbDifference` |
| `A7` Primary Plant Equipment Operation Scheme | `ControlSchemeList` | `OS:PlantEquipmentOperation:CoolingLoad`, `OS:PlantEquipmentOperation:HeatingLoad`, `OS:PlantEquipmentOperation:OutdoorDewpoint`, `OS:PlantEquipmentOperation:OutdoorDewpointDifference`, `OS:PlantEquipmentOperation:OutdoorDryBulb`, `OS:PlantEquipmentOperation:OutdoorDryBulbDifference`, `OS:PlantEquipmentOperation:OutdoorRelativeHumidity`, `OS:PlantEquipmentOperation:OutdoorWetBulb`, `OS:PlantEquipmentOperation:OutdoorWetBulbDifference` |
| `A8` Loop Temperature Setpoint Node Name | `Node` | `OS:Node` |
| `A9` Plant Side Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A10` Plant Side Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A11` Plant Side Branch List Name | `BranchLists` | No `\reference` matches found |
| `A12` Demand Side Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A13` Demand Side Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A14` Demand Side Branch List Name | `BranchLists` | No `\reference` matches found |
| `A15` Demand Side Connector List Name | `ConnectorLists` | No `\reference` matches found |
| `A17` Availability Manager List Name | `SystemAvailabilityManagerLists` | `OS:AvailabilityManagerAssignmentList` |
| `A21` Plant Equipment Operation Heating Load Schedule | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A22` Plant Equipment Operation Cooling Load Schedule | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A23` Primary Plant Equipment Operation Scheme Schedule | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A24` Component Setpoint Operation Scheme Schedule | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A25` Demand Mixer Name | `ConnectionObject` | 140 targets (suppressed; list is `ConnectionObject`) |
| `A26` Demand Splitter Name | `ConnectionObject` | 140 targets (suppressed; list is `ConnectionObject`) |
| `A27` Supply Mixer Name | `ConnectionObject` | 140 targets (suppressed; list is `ConnectionObject`) |
| `A28` Supply Splitter Name | `ConnectionObject` | 140 targets (suppressed; list is `ConnectionObject`) |

### `OS:PortList`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A2` HVAC Component | `ConnectionObject` | 140 targets (suppressed; list is `ConnectionObject`) |
| `A3` Port 1 | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |

### `OS:Pump:ConstantSpeed`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A2` Rotational Speed | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A2` Rotational Speed | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A2` Rotational Speed | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A8` Zone | `ThermalZoneNames` | `OS:ThermalZone` |

### `OS:Pump:VariableSpeed`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A4` Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A6` Pump Flow Rate Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A7` Pump Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A9` Pump RPM Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A10` Minimum Pressure Schedule | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A11` Maximum Pressure Schedule | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A12` Minimum RPM Schedule | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A13` Maximum RPM Schedule | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A14` Zone Name | `ThermalZoneNames` | `OS:ThermalZone` |

### `OS:PythonPlugin:Instance`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A4` External File Name | `ExternalFileNames` | `OS:External:File` |

### `OS:PythonPlugin:OutputVariable`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Python Plugin Variable Name | `PythonPluginVariables` | `OS:PythonPlugin:OutputVariable`, `OS:PythonPlugin:TrendVariable`, `OS:PythonPlugin:Variable` |

### `OS:PythonPlugin:TrendVariable`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Number of Timesteps to be Logged | `PythonPluginVariables` | `OS:PythonPlugin:OutputVariable`, `OS:PythonPlugin:TrendVariable`, `OS:PythonPlugin:Variable` |

### `OS:Refrigeration:AirChiller`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Availability Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A6` Capacity Correction Curve Name | `TrivariateFunctions` | `OS:Curve:Triquadratic`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A6` Capacity Correction Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A7` Heating Power Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A11` Defrost Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A12` Defrost Drip-Down Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:Refrigeration:Case`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Availability Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A4` Zone Name | `ThermalZoneNames` | `OS:ThermalZone` |
| `A6` Latent Case Credit Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A7` Case Lighting Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A10` Case Defrost Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A11` Case Defrost Drip-Down Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A13` Defrost Energy Correction Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A14` Refrigerated Case Restocking Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A15` Case Credit Fraction Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A17` Case Defrost Cycle Parameters Name | `RefrigerationDefrostCycleParameters` | `OS:Refrigeration:DefrostCycleParameters` |

### `OS:Refrigeration:Compressor`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Refrigeration Compressor Power Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A4` Refrigeration Compressor Capacity Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A7` Transcritical Compressor Power Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A8` Transcritical Compressor Capacity Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |

### `OS:Refrigeration:CompressorRack`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A4` Compressor Rack COP Function of Temperature Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A5` Condenser Fan Power Function of Temperature Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A7` Water-Cooled Condenser Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A8` Water-Cooled Condenser Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A10` Water-Cooled Condenser Outlet Temperature Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A11` Evaporative Condenser Availability Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A12` Evaporative Water Supply Tank Name | `WaterStorageTankNames` | No `\reference` matches found |
| `A15` Refrigerated CaseAndWalkInList Name | `ModelObjectLists` | `OS:ModelObjectList` |
| `A16` Heat Rejection Zone Name | `ThermalZoneNames` | `OS:ThermalZone` |

### `OS:Refrigeration:Condenser:AirCooled`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Rated Effective Total Heat Rejection Rate Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A5` Air Inlet Zone Name | `ThermalZoneNames` | `OS:ThermalZone` |

### `OS:Refrigeration:Condenser:EvaporativeCooled`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A5` Evaporative Water Supply Tank Name | `WaterStorageTankNames` | No `\reference` matches found |
| `A6` Evaporative Condenser Availability Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:Refrigeration:Condenser:WaterCooled`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Water Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A4` Water Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A6` Water Outlet Temperature Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:Refrigeration:GasCooler:AirCooled`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Rated Total Heat Rejection Rate Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |

### `OS:Refrigeration:SecondarySystem`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Refrigerated CaseAndWalkInList Name | `ModelObjectLists` | `OS:ModelObjectList` |
| `A6` Variable Speed Pump Cubic Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A7` Distribution Piping Zone Name | `ThermalZoneNames` | `OS:ThermalZone` |
| `A8` Receiver/Separator Zone Name | `ThermalZoneNames` | `OS:ThermalZone` |

### `OS:Refrigeration:Subcooler:Mechanical`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Capacity-Providing System | `RefrigerationSystemNames` | `OS:Refrigeration:System`, `OS:Refrigeration:TranscriticalSystem` |

### `OS:Refrigeration:System`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Refrigerated CaseAndWalkInList Name | `ModelObjectLists` | `OS:ModelObjectList` |
| `A4` Refrigeration TransferLoad List Name | `ModelObjectLists` | `OS:ModelObjectList` |
| `A5` Refrigeration Condenser Name | `RefrigerationAllTypesCondenserNames` | `OS:Refrigeration:Condenser:AirCooled`, `OS:Refrigeration:Condenser:Cascade`, `OS:Refrigeration:Condenser:EvaporativeCooled`, `OS:Refrigeration:Condenser:WaterCooled` |
| `A6` CompressorList Name | `ModelObjectLists` | `OS:ModelObjectList` |
| `A9` Mechanical Subcooler Name | `RefrigerationSubcoolerNames` | `OS:Refrigeration:Subcooler:LiquidSuction`, `OS:Refrigeration:Subcooler:Mechanical` |
| `A10` Liquid Suction Heat Exchanger Subcooler Name | `RefrigerationSubcoolerNames` | `OS:Refrigeration:Subcooler:LiquidSuction`, `OS:Refrigeration:Subcooler:Mechanical` |
| `A11` Suction Piping Zone Name | `ThermalZoneNames` | `OS:ThermalZone` |
| `A14` High-Stage CompressorList Name | `ModelObjectLists` | `OS:ModelObjectList` |

### `OS:Refrigeration:TranscriticalSystem`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Medium Temperature Refrigerated CaseAndWalkInList Name | `ModelObjectLists` | `OS:ModelObjectList` |
| `A4` Low Temperature Refrigerated CaseAndWalkInList Name | `ModelObjectLists` | `OS:ModelObjectList` |
| `A5` Refrigeration Gas Cooler Name | `RefrigerationAllTypesGasCoolerNames` | `OS:Refrigeration:GasCooler:AirCooled` |
| `A6` High Pressure CompressorList Name | `ModelObjectLists` | `OS:ModelObjectList` |
| `A7` Low Pressure CompressorList Name | `ModelObjectLists` | `OS:ModelObjectList` |
| `A9` Medium Temperature Suction Piping Zone Name | `ThermalZoneNames` | `OS:ThermalZone` |
| `A10` Low Temperature Suction Piping Zone Name | `ThermalZoneNames` | `OS:ThermalZone` |

### `OS:Refrigeration:WalkIn`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Availability Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A4` Heating Power Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A5` Lighting Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A8` Defrost Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A9` Defrost Drip-Down Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A10` Restocking Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A11` WalkIn Defrost Cycle Parameters Name | `RefrigerationDefrostCycleParameters` | `OS:Refrigeration:DefrostCycleParameters` |
| `A12` WalkIn Zone Boundary | `RefrigerationWalkInZoneBoundaryNames` | `OS:Refrigeration:WalkIn:ZoneBoundary` |

### `OS:Refrigeration:WalkIn:ZoneBoundary`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Zone Name | `ThermalZoneNames` | `OS:ThermalZone` |
| `A4` Glass Reach In Door Opening Schedule Name Facing Zone | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A5` Stocking Door Opening Schedule Name Facing Zone | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:Schedule:Compact`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Schedule Type Limits Name | `ScheduleTypeLimitsNames` | `OS:ScheduleTypeLimits` |

### `OS:Schedule:Constant`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Schedule Type Limits Name | `ScheduleTypeLimitsNames` | `OS:ScheduleTypeLimits` |

### `OS:Schedule:Day`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Schedule Type Limits Name | `ScheduleTypeLimitsNames` | `OS:ScheduleTypeLimits` |

### `OS:Schedule:File`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Schedule Type Limits Name | `ScheduleTypeLimitsNames` | `OS:ScheduleTypeLimits` |
| `A4` External File Name | `ExternalFileNames` | `OS:External:File` |

### `OS:Schedule:FixedInterval`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Schedule Type Limits Name | `ScheduleTypeLimitsNames` | `OS:ScheduleTypeLimits` |

### `OS:Schedule:Rule`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Schedule Ruleset Name | `ScheduleRulesetNames` | `OS:Schedule:Ruleset` |
| `A4` Day Schedule Name | `DayScheduleNames` | `OS:Schedule:Day` |

### `OS:Schedule:Ruleset`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Schedule Type Limits Name | `ScheduleTypeLimitsNames` | `OS:ScheduleTypeLimits` |
| `A4` Default Day Schedule Name | `DayScheduleNames` | `OS:Schedule:Day` |
| `A5` Summer Design Day Schedule Name | `DayScheduleNames` | `OS:Schedule:Day` |
| `A6` Winter Design Day Schedule Name | `DayScheduleNames` | `OS:Schedule:Day` |
| `A7` Holiday Schedule Name | `DayScheduleNames` | `OS:Schedule:Day` |
| `A8` Custom Day 1 Schedule Name | `DayScheduleNames` | `OS:Schedule:Day` |
| `A9` Custom Day 2 Schedule Name | `DayScheduleNames` | `OS:Schedule:Day` |

### `OS:Schedule:VariableInterval`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Schedule Type Limits Name | `ScheduleTypeLimitsNames` | `OS:ScheduleTypeLimits` |

### `OS:Schedule:Week`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Schedule Rendering Name | `ScheduleRenderingNames` | No `\reference` matches found |
| `A4` Sunday Schedule:Day Name | `DayScheduleNames` | `OS:Schedule:Day` |
| `A5` Monday Schedule:Day Name | `DayScheduleNames` | `OS:Schedule:Day` |
| `A6` Tuesday Schedule:Day Name | `DayScheduleNames` | `OS:Schedule:Day` |
| `A7` Wednesday Schedule:Day Name | `DayScheduleNames` | `OS:Schedule:Day` |
| `A8` Thursday Schedule:Day Name | `DayScheduleNames` | `OS:Schedule:Day` |
| `A9` Friday Schedule:Day Name | `DayScheduleNames` | `OS:Schedule:Day` |
| `A10` Saturday Schedule:Day Name | `DayScheduleNames` | `OS:Schedule:Day` |
| `A11` Holiday Schedule:Day Name | `DayScheduleNames` | `OS:Schedule:Day` |
| `A12` SummerDesignDay Schedule:Day Name | `DayScheduleNames` | `OS:Schedule:Day` |
| `A13` WinterDesignDay Schedule:Day Name | `DayScheduleNames` | `OS:Schedule:Day` |
| `A14` CustomDay1 Schedule:Day Name | `DayScheduleNames` | `OS:Schedule:Day` |
| `A15` CustomDay2 Schedule:Day Name | `DayScheduleNames` | `OS:Schedule:Day` |

### `OS:Schedule:Year`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Schedule Type Limits Name | `ScheduleTypeLimitsNames` | `OS:ScheduleTypeLimits` |
| `A4` Week Schedule Until Date | `WeekScheduleNames` | `OS:Schedule:Week` |

### `OS:SetpointManager:FollowOutdoorAirTemperature`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Setpoint Node or NodeList Name | `Node` | `OS:Node` |

### `OS:SetpointManager:FollowSystemNodeTemperature`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A4` Setpoint Node or NodeList Name | `Node` | `OS:Node` |

### `OS:SetpointManager:MixedAir`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A4` Reference Setpoint Node Name | `Node` | `OS:Node` |
| `A5` Fan Inlet Node Name | `Node` | `OS:Node` |
| `A6` Fan Outlet Node Name | `Node` | `OS:Node` |
| `A7` Setpoint Node or NodeList Name | `Node` | `OS:Node` |

### `OS:SetpointManager:MultiZone:Humidity:Minimum`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Setpoint Node or NodeList Name | `Node` | `OS:Node` |

### `OS:SetpointManager:MultiZone:MinimumHumidity:Average`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Setpoint Node or NodeList Name | `Node` | `OS:Node` |

### `OS:SetpointManager:OutdoorAirPretreat`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A4` Reference Setpoint Node Name | `Node` | `OS:Node` |
| `A5` Mixed Air Stream Node Name | `Node` | `OS:Node` |
| `A6` Outdoor Air Stream Node Name | `Node` | `OS:Node` |
| `A7` Return Air Stream Node Name | `Node` | `OS:Node` |
| `A8` Setpoint Node or NodeList Name | `Node` | `OS:Node` |

### `OS:SetpointManager:OutdoorAirReset`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Outdoor High Temperature 2 | `Node` | `OS:Node` |
| `A1` Outdoor High Temperature 2 | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:SetpointManager:Scheduled`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A4` Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A5` Setpoint Node or NodeList Name | `Node` | `OS:Node` |

### `OS:SetpointManager:Scheduled:DualSetpoint`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A4` High Setpoint Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A5` Low Setpoint Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A6` Setpoint Node or NodeList Name | `Node` | `OS:Node` |

### `OS:SetpointManager:SingleZone:Humidity:Minimum`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A4` Setpoint Node or NodeList Name | `Node` | `OS:Node` |
| `A5` Control Zone Name | `ThermalZoneNames` | `OS:ThermalZone` |

### `OS:SetpointManager:SingleZone:Reheat`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Control Zone Name | `ThermalZoneNames` | `OS:ThermalZone` |
| `A4` Setpoint Node or NodeList Name | `Node` | `OS:Node` |

### `OS:SetpointManager:Warmest`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Setpoint Node or NodeList Name | `Node` | `OS:Node` |

### `OS:SetpointManager:WarmestTemperatureFlow`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Minimum Turndown Ratio | `Node` | `OS:Node` |

### `OS:ShadingControl`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A5` Glare Control Is Active | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A5` Glare Control Is Active | `WindowShadesScreensAndBlinds` | `OS:WindowMaterial:Blind`, `OS:WindowMaterial:DaylightRedirectionDevice`, `OS:WindowMaterial:Screen`, `OS:WindowMaterial:Shade` |
| `A11` Setpoint 2 | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A13` Sub Surface Name 1 | `GlazedExtSubSurfNames` | `OS:SubSurface` |

### `OS:ShadingSurface`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Construction Name | `ConstructionNames` | `OS:Construction`, `OS:Construction:AirBoundary`, `OS:Construction:CfactorUndergroundWall`, `OS:Construction:FfactorGroundFloor`, `OS:Construction:InternalSource`, `OS:Construction:WindowDataFile` |
| `A4` Shading Surface Group Name | `ShadingSurfaceGroupNames` | `OS:ShadingSurfaceGroup` |
| `A5` Transmittance Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:ShadingSurfaceGroup`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A4` Space Name | `SpaceNames` | `OS:Space` |
| `A5` Shaded Object Name | `SurfAndSubSurfNames` | `OS:SubSurface`, `OS:Surface` |

### `OS:ShadowCalculation`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Shading Zone Group | `ModelObjectLists` | `OS:ModelObjectList` |

### `OS:Site:WaterMainsTemperature`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Temperature Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:Sizing:Plant`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A2` Plant or Condenser Loop Name | `PlantLoops` | `OS:PlantLoop` |

### `OS:Sizing:System`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A2` AirLoop Name | `AirPrimaryLoops` | `OS:AirLoopHVAC` |

### `OS:Sizing:Zone`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A2` Zone or ZoneList Name | `ThermalZoneNames` | `OS:ThermalZone` |
| `A11` Zone Humidistat Dehumidification Set Point Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A12` Zone Humidistat Humidification Set Point Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:SizingPeriod:DesignDay`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A8` Humidity Condition Day Schedule Name | `DayScheduleNames` | `OS:Schedule:Day` |
| `A10` Dry-Bulb Temperature Range Modifier Day Schedule Name | `DayScheduleNames` | `OS:Schedule:Day` |
| `A12` Beam Solar Day Schedule Name | `DayScheduleNames` | `OS:Schedule:Day` |
| `A13` Diffuse Solar Day Schedule Name | `DayScheduleNames` | `OS:Schedule:Day` |

### `OS:SolarCollector:FlatPlate:PhotovoltaicThermal`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Design Flow Rate | `AllShadingAndHTSurfNames` | `OS:ShadingSurface`, `OS:SubSurface`, `OS:Surface` |
| `A1` Design Flow Rate | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A1` Design Flow Rate | `FlatPlatePVTParameters` | `OS:SolarCollectorPerformance:PhotovoltaicThermal:BIPVT`, `OS:SolarCollectorPerformance:PhotovoltaicThermal:Simple` |
| `A1` Design Flow Rate | `PVGeneratorNames` | No `\reference` matches found |

### `OS:SolarCollector:FlatPlate:Water`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Maximum Flow Rate | `AllShadingAndHTSurfNames` | `OS:ShadingSurface`, `OS:SubSurface`, `OS:Surface` |
| `A1` Maximum Flow Rate | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A1` Maximum Flow Rate | `FlatPlateSolarCollectorParameters` | `OS:SolarCollectorPerformance:FlatPlate` |

### `OS:SolarCollector:IntegralCollectorStorage`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Maximum Flow Rate | `AllShadingAndHTSurfNames` | `OS:ShadingSurface`, `OS:SubSurface`, `OS:Surface` |
| `A1` Maximum Flow Rate | `CollectorStoragePerformance` | `OS:SolarCollectorPerformance:IntegralCollectorStorage` |
| `A1` Maximum Flow Rate | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |

### `OS:SolarCollectorPerformance:PhotovoltaicThermal:BIPVT`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Glass Extinction Coefficient | `OSCMNames` | `OS:SurfaceProperty:OtherSideConditionsModel` |
| `A3` Glass Extinction Coefficient | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:SolarCollectorPerformance:PhotovoltaicThermal:Simple`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Front Surface Emittance | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:Space`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Space Type Name | `SpaceTypeNames` | `OS:SpaceType` |
| `A4` Default Construction Set Name | `DefaultConstructionSetNames` | `OS:DefaultConstructionSet` |
| `A5` Default Schedule Set Name | `DefaultScheduleSetNames` | `OS:DefaultScheduleSet` |
| `A6` Building Story Name | `BuildingStoryNames` | `OS:BuildingStory` |
| `A7` Thermal Zone Name | `ThermalZoneNames` | `OS:ThermalZone` |
| `A9` Design Specification Outdoor Air Object Name | `DesignSpecificationOutdoorAirNames` | `OS:DesignSpecification:OutdoorAir` |
| `A10` Building Unit Name | `BuildingUnitNames` | `OS:BuildingUnit` |

### `OS:SpaceInfiltration:DesignFlowRate`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Space or SpaceType Name | `SpaceAndSpaceTypeNames` | `OS:Space`, `OS:SpaceType` |
| `A4` Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:SpaceInfiltration:EffectiveLeakageArea`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Wind Coefficient | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A1` Wind Coefficient | `SpaceAndSpaceTypeNames` | `OS:Space`, `OS:SpaceType` |

### `OS:SpaceInfiltration:FlowCoefficient`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Shelter Factor | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A3` Shelter Factor | `SpaceAndSpaceTypeNames` | `OS:Space`, `OS:SpaceType` |

### `OS:SpaceType`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Default Construction Set Name | `DefaultConstructionSetNames` | `OS:DefaultConstructionSet` |
| `A4` Default Schedule Set Name | `DefaultScheduleSetNames` | `OS:DefaultScheduleSet` |
| `A5` Group Rendering Name | `GroupRenderingNames` | `OS:Rendering:Color` |
| `A6` Design Specification Outdoor Air Object Name | `DesignSpecificationOutdoorAirNames` | `OS:DesignSpecification:OutdoorAir` |

### `OS:StandardsInformation:Construction`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A2` Construction Name | `ConstructionNames` | `OS:Construction`, `OS:Construction:AirBoundary`, `OS:Construction:CfactorUndergroundWall`, `OS:Construction:FfactorGroundFloor`, `OS:Construction:InternalSource`, `OS:Construction:WindowDataFile` |

### `OS:StandardsInformation:Material`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A2` Material Name | `MaterialNames` | `OS:Material`, `OS:Material:AirGap`, `OS:Material:InfraredTransparent`, `OS:Material:NoMass`, `OS:Material:RoofVegetation`, `OS:WindowMaterial:Blind`, `OS:WindowMaterial:DaylightRedirectionDevice`, `OS:WindowMaterial:Gas`, `OS:WindowMaterial:GasMixture`, `OS:WindowMaterial:Glazing`, `OS:WindowMaterial:Glazing:RefractionExtinctionMethod`, `OS:WindowMaterial:GlazingGroup:Thermochromic`, `OS:WindowMaterial:Screen`, `OS:WindowMaterial:Shade`, `OS:WindowMaterial:SimpleGlazingSystem` |

### `OS:SteamEquipment`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Steam Equipment Definition Name | `SteamEquipmentDefinitionNames` | `OS:SteamEquipment:Definition` |
| `A4` Space or SpaceType Name | `SpaceAndSpaceTypeNames` | `OS:Space`, `OS:SpaceType` |
| `A5` Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:SubSurface`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A4` Construction Name | `ConstructionNames` | `OS:Construction`, `OS:Construction:AirBoundary`, `OS:Construction:CfactorUndergroundWall`, `OS:Construction:FfactorGroundFloor`, `OS:Construction:InternalSource`, `OS:Construction:WindowDataFile` |
| `A5` Surface Name | `SurfaceNames` | `OS:Surface` |
| `A6` Outside Boundary Condition Object | `OutFaceEnvNames` | `OS:Foundation:Kiva`, `OS:SubSurface`, `OS:Surface`, `OS:SurfaceProperty:OtherSideCoefficients`, `OS:SurfaceProperty:OtherSideConditionsModel` |
| `A7` Frame and Divider Name | `WindowFrameAndDividerNames` | No `\reference` matches found |

### `OS:Surface`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A4` Construction Name | `ConstructionNames` | `OS:Construction`, `OS:Construction:AirBoundary`, `OS:Construction:CfactorUndergroundWall`, `OS:Construction:FfactorGroundFloor`, `OS:Construction:InternalSource`, `OS:Construction:WindowDataFile` |
| `A5` Space Name | `SpaceNames` | `OS:Space` |
| `A7` Outside Boundary Condition Object | `OutFaceEnvNames` | `OS:Foundation:Kiva`, `OS:SubSurface`, `OS:Surface`, `OS:SurfaceProperty:OtherSideCoefficients`, `OS:SurfaceProperty:OtherSideConditionsModel` |

### `OS:SurfaceControl:MovableInsulation`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Surface Name | `SurfaceNames` | `OS:Surface` |
| `A4` Material Name | `MaterialNames` | `OS:Material`, `OS:Material:AirGap`, `OS:Material:InfraredTransparent`, `OS:Material:NoMass`, `OS:Material:RoofVegetation`, `OS:WindowMaterial:Blind`, `OS:WindowMaterial:DaylightRedirectionDevice`, `OS:WindowMaterial:Gas`, `OS:WindowMaterial:GasMixture`, `OS:WindowMaterial:Glazing`, `OS:WindowMaterial:Glazing:RefractionExtinctionMethod`, `OS:WindowMaterial:GlazingGroup:Thermochromic`, `OS:WindowMaterial:Screen`, `OS:WindowMaterial:Shade`, `OS:WindowMaterial:SimpleGlazingSystem` |
| `A5` Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:SurfaceProperty:ConvectionCoefficients`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A2` Surface Name | `AllHeatTranSurfNames` | `OS:InternalMass`, `OS:SubSurface`, `OS:Surface` |
| `A5` Convection Coefficient 1 Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A6` Convection Coefficient 1 User Curve Name | `UserConvectionModels` | No `\reference` matches found |
| `A9` Convection Coefficient 2 Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A10` Convection Coefficient 2 User Curve Name | `UserConvectionModels` | No `\reference` matches found |

### `OS:SurfaceProperty:ConvectionCoefficients:MultipleSurface`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A5` Convection Coefficient 1 Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A6` Convection Coefficient 1 User Curve Name | `UserConvectionModels` | No `\reference` matches found |
| `A9` Convection Coefficient 2 Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A10` Convection Coefficient 2 User Curve Name | `UserConvectionModels` | No `\reference` matches found |

### `OS:SurfaceProperty:ExposedFoundationPerimeter`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A2` Surface Name | `FloorSurfaceNames` | `OS:Surface` |

### `OS:SurfaceProperty:GroundSurfaces`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A4` Ground Surface 1 Temperature Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A5` Ground Surface 1 Reflectance Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:SurfaceProperty:IncidentSolarMultiplier`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A2` Surface Name | `GlazedExtSubSurfNames` | `OS:SubSurface` |
| `A3` Incident Solar Multiplier Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:SurfaceProperty:LocalEnvironment`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Exterior Surface Name | `AllHeatTranSurfNames` | `OS:InternalMass`, `OS:SubSurface`, `OS:Surface` |
| `A4` External Shading Fraction Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A5` Surrounding Surfaces Object Name | `SurroundingSurfacesNames` | `OS:SurfaceProperty:SurroundingSurfaces` |
| `A6` Outdoor Air Node Name | `OutdoorAirNodeNames` | No `\reference` matches found |
| `A7` Ground Surfaces Object Name | `GroundSurfacesNames` | `OS:SurfaceProperty:GroundSurfaces` |

### `OS:SurfaceProperty:OtherSideCoefficients`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Constant Temperature Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:SurfaceProperty:SurroundingSurfaces`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Sky Temperature Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A4` Ground Temperature Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A6` Surrounding Surface 1 Temperature Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:SwimmingPool:Indoor`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Surface Name | `FloorSurfaceNames` | `OS:Surface` |
| `A4` Activity Factor Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A5` Make-up Water Supply Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A6` Cover Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A7` Pool Water Inlet Node | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A8` Pool Water Outlet Node | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A9` Setpoint Temperature Schedule | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A10` People Schedule | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A11` People Heat Gain Schedule | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:Table:IndependentVariable`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A6` External File Name | `ExternalFileNames` | `OS:External:File` |

### `OS:Table:Lookup`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Independent Variable List Name | `ModelObjectLists` | `OS:ModelObjectList` |
| `A6` External File Name | `ExternalFileNames` | `OS:External:File` |

### `OS:TemperingValve`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A4` Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A5` Stream 2 Source Node | `Node` | `OS:Node` |
| `A6` Temperature Setpoint Node | `Node` | `OS:Node` |
| `A7` Pump Outlet Node | `Node` | `OS:Node` |

### `OS:ThermalStorage:ChilledWater:Stratified`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `N5` Ambient Temperature Outdoor Air Node Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `N5` Ambient Temperature Outdoor Air Node Name | `ThermalZoneNames` | `OS:ThermalZone` |
| `N8` Use Side Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A10` Use Side Heat Transfer Effectiveness | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A11` Use Side Availability Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A12` Source Side Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A13` Source Side Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A14` Source Side Availability Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:ThermalStorage:Ice:Detailed`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Thaw Process Indicator | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A1` Thaw Process Indicator | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A1` Thaw Process Indicator | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:ThermalZone`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A6` Zone Air Inlet Port List | `PortLists` | No `\reference` matches found |
| `A7` Zone Air Exhaust Port List | `PortLists` | No `\reference` matches found |
| `A8` Zone Air Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A9` Zone Return Air Port List | `PortLists` | No `\reference` matches found |
| `A10` Primary Daylighting Control Name | `DaylightingControlNames` | `OS:Daylighting:Control` |
| `A11` Secondary Daylighting Control Name | `DaylightingControlNames` | `OS:Daylighting:Control` |
| `A12` Illuminance Map Name | `IlluminanceMapNames` | `OS:IlluminanceMap` |
| `A13` Group Rendering Name | `GroupRenderingNames` | `OS:Rendering:Color` |
| `A14` Thermostat Name | `ThermostatNames` | `OS:ThermostatSetpoint:DualSetpoint`, `OS:ZoneControl:Thermostat:StagedDualSetpoint` |
| `A16` Humidistat Name | `HumidistatNames` | `OS:ZoneControl:Humidistat` |
| `A17` Daylighting Controls Availability Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:ThermostatSetpoint:DualSetpoint`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Heating Setpoint Temperature Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A4` Cooling Setpoint Temperature Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:UtilityCost:Charge:Block`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Tariff Name | `UtilityCostTariffs` | `OS:UtilityCost:Tariff` |

### `OS:UtilityCost:Charge:Simple`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Tariff Name | `UtilityCostTariffs` | `OS:UtilityCost:Tariff` |

### `OS:UtilityCost:Computation`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Tariff Name | `UtilityCostTariffs` | `OS:UtilityCost:Tariff` |

### `OS:UtilityCost:Qualify`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A2` Tariff Name | `UtilityCostTariffs` | `OS:UtilityCost:Tariff` |

### `OS:UtilityCost:Ratchet`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Tariff Name | `UtilityCostTariffs` | `OS:UtilityCost:Tariff` |

### `OS:UtilityCost:Tariff`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A5` Time of Use Period Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A6` Season Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A7` Month Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A11` Real Time Pricing Charge Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A12` Customer Baseline Load Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:UtilityCost:Variable`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Tariff Name | `UtilityCostTariffs` | `OS:UtilityCost:Tariff` |

### `OS:WaterHeater:HeatPump`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Availability Schedule | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A4` Outdoor Air Node | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A4` Outdoor Air Node | `Node` | `OS:Node` |
| `A4` Outdoor Air Node | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A9` Inlet Air Temperature Schedule | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A10` Inlet Air Humidity Schedule | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A11` Tank | `WaterHeaterNames` | `OS:WaterHeater:Mixed`, `OS:WaterHeater:Stratified` |
| `A12` Maximum Inlet Air Temperature for Compressor Operation | `HeatPumpWaterHeaterDXCoils` | `OS:Coil:WaterHeating:AirToWaterHeatPump` |
| `A12` Maximum Inlet Air Temperature for Compressor Operation | `HeatPumpWaterHeaterDXCoilsVariableSpeed` | `OS:Coil:WaterHeating:AirToWaterHeatPump:VariableSpeed` |
| `A12` Maximum Inlet Air Temperature for Compressor Operation | `IntegratedHeatPumps` | `OS:CoilSystem:IntegratedHeatPump:AirSource` |
| `A14` Compressor Ambient Temperature Schedule | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A15` Fan | `FansOnOff` | `OS:Fan:OnOff` |
| `A15` Fan | `FansSystemModel` | `OS:Fan:SystemModel` |
| `A18` Inlet Air Mixer Schedule | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:WaterHeater:HeatPump:WrappedCondenser`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Availability Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A4` Dead Band Temperature Difference | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `N3` Inlet Air Temperature Schedule Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `N3` Inlet Air Temperature Schedule Name | `Node` | `OS:Node` |
| `N3` Inlet Air Temperature Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A10` Inlet Air Humidity Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A11` Tank Name | `WaterHeaterStratifiedNames` | `OS:WaterHeater:Stratified` |
| `A12` Maximum Inlet Air Temperature for Compressor Operation | `HeatPumpWaterHeaterDXCoilsWrapped` | `OS:Coil:WaterHeating:AirToWaterHeatPump:Wrapped` |
| `A14` Compressor Ambient Temperature Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A15` Fan Name | `FansOnOff` | `OS:Fan:OnOff` |
| `A15` Fan Name | `FansSystemModel` | `OS:Fan:SystemModel` |
| `A18` Inlet Air Mixer Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:WaterHeater:Mixed`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Off Cycle Parasitic Fuel Type | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A1` Off Cycle Parasitic Fuel Type | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `N12` Ambient Temperature Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A11` Ambient Temperature Thermal Zone Name | `ThermalZoneNames` | `OS:ThermalZone` |
| `A13` Use Flow Rate Fraction Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A14` Cold Water Supply Temperature Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A15` Use Side Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A16` Use Side Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A17` Source Side Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A18` Source Side Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A20` Indirect Alternate Setpoint Temperature Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:WaterHeater:Sizing`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Recovery Capacity per Floor Area | `ThermalStorageWaterNames` | No `\reference` matches found |
| `A1` Recovery Capacity per Floor Area | `WaterHeaterNames` | `OS:WaterHeater:Mixed`, `OS:WaterHeater:Stratified` |

### `OS:WaterHeater:Stratified`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A6` Heater 1 Setpoint Temperature Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A7` Heater 2 Setpoint Temperature Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A12` Ambient Temperature Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A13` Ambient Temperature Thermal Zone Name | `ThermalZoneNames` | `OS:ThermalZone` |
| `A15` Use Flow Rate Fraction Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A16` Cold Water Supply Temperature Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A17` Use Side Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A18` Use Side Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A19` Source Side Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A20` Source Side Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A23` Indirect Alternate Setpoint Temperature Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:WaterUse:Connections`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A4` Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A5` Supply Water Storage Tank Name | `WaterStorageTankNames` | No `\reference` matches found |
| `A6` Reclamation Water Storage Tank Name | `WaterStorageTankNames` | No `\reference` matches found |
| `A7` Hot Water Supply Temperature Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A8` Cold Water Supply Temperature Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A11` Water Use Equipment 1 Name | `WaterUseEquipmentNames` | `OS:WaterUse:Equipment` |

### `OS:WaterUse:Equipment`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Water Use Equipment Definition Name | `WaterUseEquipmentDefinitionNames` | `OS:WaterUse:Equipment:Definition` |
| `A4` Space Name | `SpaceNames` | `OS:Space` |
| `A5` Flow Rate Fraction Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:WaterUse:Equipment:Definition`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Latent Fraction Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:WeatherProperty:SkyTemperature`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A2` Name | `RunPeriodsAndDesignDays` | `OS:RunPeriod`, `OS:SizingPeriod:DesignDay`, `OS:SizingPeriod:WeatherFileConditionType`, `OS:SizingPeriod:WeatherFileDays` |
| `A4` Schedule Name | `ScheduleAndDayScheduleNames` | `OS:Schedule:Day` |

### `OS:WindowMaterial:Glazing`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A4` Window Glass Spectral Data Set Name | `SpectralDataSets` | `OS:MaterialProperty:GlazingSpectralData` |

### `OS:WindowMaterial:GlazingGroup:Thermochromic`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Window Material Glazing Name | `GlazingMaterialNames` | `OS:WindowMaterial:Glazing`, `OS:WindowMaterial:Glazing:RefractionExtinctionMethod`, `OS:WindowMaterial:GlazingGroup:Thermochromic`, `OS:WindowMaterial:SimpleGlazingSystem` |

### `OS:ZoneAirContaminantBalance`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Outdoor Carbon Dioxide Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:ZoneControl:ContaminantController`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Generic Contaminant Setpoint Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A1` Generic Contaminant Setpoint Schedule Name | `ThermalZoneNames` | `OS:ThermalZone` |

### `OS:ZoneControl:Humidistat`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Humidifying Relative Humidity Setpoint Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A4` Dehumidifying Relative Humidity Setpoint Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:ZoneControl:Thermostat:StagedDualSetpoint`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Stage 1 Cooling Temperature Offset | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:ZoneHVAC:Baseboard:Convective:Water`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A4` Heating Coil Name | `BaseboardHeatingCoil` | `OS:Coil:Heating:Water:Baseboard` |

### `OS:ZoneHVAC:Baseboard:RadiantConvective:Water`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Availability Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A4` Heating Coil Name | `RadiantBaseboardHeatingCoil` | `OS:Coil:Heating:Water:Baseboard:Radiant` |

### `OS:ZoneHVAC:Dehumidifier:DX`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Availability Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A4` Air Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A5` Air Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A6` Water Removal Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A7` Energy Factor Curve Name | `BivariateFunctions` | `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:FanPressureRise`, `OS:Curve:QuadraticLinear`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A8` Part Load Fraction Correlation Curve Name | `UnivariateFunctions` | `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:Quadratic`, `OS:Curve:Quartic`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Table:Lookup`, `OS:Table:MultiVariableLookup` |
| `A9` Condensate Collection Water Storage Tank Name | `WaterStorageTankNames` | No `\reference` matches found |

### `OS:ZoneHVAC:EnergyRecoveryVentilator`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A10` Air Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |

### `OS:ZoneHVAC:EquipmentList`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Thermal Zone | `AllObjects` | 6 targets (suppressed; list is `AllObjects`) |
| `A4` Zone Equipment 1 Sequential Heating Fraction Schedule Name | `AllObjects` | 6 targets (suppressed; list is `AllObjects`) |
| `A4` Zone Equipment 1 Sequential Heating Fraction Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:ZoneHVAC:EvaporativeCoolerUnit`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Availability Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A4` Availability Manager List Name | `SystemAvailabilityManagerLists` | `OS:AvailabilityManagerAssignmentList` |
| `A5` Outdoor Air Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A6` Cooler Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A7` Zone Relief Air Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A8` Supply Air Fan Name | `Fans` | `OS:Fan:ComponentModel`, `OS:Fan:ConstantVolume`, `OS:Fan:OnOff`, `OS:Fan:SystemModel`, `OS:Fan:VariableVolume` |
| `A11` First Evaporative Cooler | `EvapCoolerNames` | `OS:EvaporativeCooler:Direct:ResearchSpecial`, `OS:EvaporativeCooler:Indirect:ResearchSpecial` |
| `A12` Second Evaporative Cooler | `EvapCoolerNames` | `OS:EvaporativeCooler:Direct:ResearchSpecial`, `OS:EvaporativeCooler:Indirect:ResearchSpecial` |
| `A13` Design Specification ZoneHVAC Sizing | `DesignSpecificationZoneHVACSizingName` | No `\reference` matches found |

### `OS:ZoneHVAC:FourPipeFanCoil`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A8` Outdoor Air Mixer Name | `OutdoorAirMixers` | No `\reference` matches found |
| `A10` Supply Air Fan Name | `FansCVandOnOffandVAV` | `OS:Fan:ConstantVolume`, `OS:Fan:OnOff`, `OS:Fan:VariableVolume` |
| `A10` Supply Air Fan Name | `FansSystemModel` | `OS:Fan:SystemModel` |
| `A11` Cooling Convergence Tolerance | `CoolingCoilsWater` | `OS:Coil:Cooling:Water`, `OS:CoilSystem:Cooling:Water:HeatExchangerAssisted` |
| `A12` Minimum Hot Water Flow Rate | `HeatingCoilName` | `OS:Coil:Heating:Electric`, `OS:Coil:Heating:Gas`, `OS:Coil:Heating:Water` |
| `A12` Minimum Hot Water Flow Rate | `HeatingCoilsWater` | `OS:Coil:Heating:Water` |
| `A13` Supply Air Fan Operating Mode Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:ZoneHVAC:HighTemperatureRadiant`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A2` Heating Setpoint Temperature Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:ZoneHVAC:IdealLoadsAirSystem`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A12` Design Specification Outdoor Air Object Name | `DesignSpecificationOutdoorAirNames` | `OS:DesignSpecification:OutdoorAir` |
| `A16` Design Specification ZoneHVAC Sizing Object Name | `DesignSpecificationZoneHVACSizingName` | No `\reference` matches found |
| `A17` Heating Fuel Efficiency Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A19` Cooling Fuel Efficiency Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:ZoneHVAC:LowTemperatureRadiant:ConstantFlow`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A11` Changeover Delay Time Period Schedule | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:ZoneHVAC:LowTemperatureRadiant:Electric`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A6` Heating Setpoint Temperature Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:ZoneHVAC:LowTemperatureRadiant:VariableFlow`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A11` Changeover Delay Time Period Schedule | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:ZoneHVAC:PackagedTerminalAirConditioner`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Availability Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A4` Air Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A5` Air Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A7` Outdoor Air Mixer Name | `OutdoorAirMixers` | No `\reference` matches found |
| `A9` Supply Air Fan Name | `FansCVandOnOff` | `OS:Fan:ConstantVolume`, `OS:Fan:OnOff` |
| `A9` Supply Air Fan Name | `FansSystemModel` | `OS:Fan:SystemModel` |
| `A10` Heating Coil Name | `HeatingCoilName` | `OS:Coil:Heating:Electric`, `OS:Coil:Heating:Gas`, `OS:Coil:Heating:Water` |
| `A11` Cooling Coil Name | `CoilCoolingDX` | `OS:Coil:Cooling:DX` |
| `A11` Cooling Coil Name | `CoolingCoilsDXSingleSpeed` | `OS:Coil:Cooling:DX:SingleSpeed`, `OS:CoilSystem:Cooling:DX:HeatExchangerAssisted` |
| `A11` Cooling Coil Name | `CoolingCoilsDXVariableSpeed` | `OS:Coil:Cooling:DX:VariableSpeed` |
| `A13` Supply Air Fan Operating Mode Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:ZoneHVAC:PackagedTerminalHeatPump`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Availability Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A4` Air Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A5` Air Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A9` Supply Air Fan Name | `FansCVandOnOff` | `OS:Fan:ConstantVolume`, `OS:Fan:OnOff` |
| `A9` Supply Air Fan Name | `FansSystemModel` | `OS:Fan:SystemModel` |
| `A10` Heating Coil Name | `HeatingCoilsDXSingleSpeed` | `OS:Coil:Heating:DX:SingleSpeed`, `OS:Coil:Heating:DX:VariableRefrigerantFlow` |
| `A10` Heating Coil Name | `HeatingCoilsDXVariableSpeed` | `OS:Coil:Heating:DX:VariableSpeed` |
| `A11` Cooling Coil Name | `CoilCoolingDX` | `OS:Coil:Cooling:DX` |
| `A11` Cooling Coil Name | `CoolingCoilsDXSingleSpeed` | `OS:Coil:Cooling:DX:SingleSpeed`, `OS:CoilSystem:Cooling:DX:HeatExchangerAssisted` |
| `A11` Cooling Coil Name | `CoolingCoilsDXVariableSpeed` | `OS:Coil:Cooling:DX:VariableSpeed` |
| `A12` Supplemental Heating Coil Name | `HeatingCoilName` | `OS:Coil:Heating:Electric`, `OS:Coil:Heating:Gas`, `OS:Coil:Heating:Water` |
| `A14` Supply Air Fan Operating Mode Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:ZoneHVAC:TerminalUnit:VariableRefrigerantFlow`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A10` Cooling Coil | `CoolingCoilsDXVarRefrigFlow` | `OS:Coil:Cooling:DX:VariableRefrigerantFlow` |
| `A10` Cooling Coil | `CoolingCoilsDXVarRefrigFlowFluidTemperatureControl` | `OS:Coil:Cooling:DX:VariableRefrigerantFlow:FluidTemperatureControl` |
| `A11` Zone Terminal Unit Off Parasitic Electric Energy Use | `HeatingCoilsDXVarRefrigFlow` | `OS:Coil:Heating:DX:VariableRefrigerantFlow` |
| `A11` Zone Terminal Unit Off Parasitic Electric Energy Use | `HeatingCoilsDXVarRefrigFlowFluidTemperatureControl` | `OS:Coil:Heating:DX:VariableRefrigerantFlow:FluidTemperatureControl` |
| `A12` Availability Manager List Name | `SystemAvailabilityManagerLists` | `OS:AvailabilityManagerAssignmentList` |
| `A13` Design Specification ZoneHVAC Sizing Object Name | `DesignSpecificationZoneHVACSizingName` | No `\reference` matches found |
| `A14` Supplemental Heating Coil Name | `HeatingCoilName` | `OS:Coil:Heating:Electric`, `OS:Coil:Heating:Gas`, `OS:Coil:Heating:Water` |
| `A15` Controlling Zone or Thermostat Location | `ThermalZoneNames` | `OS:ThermalZone` |

### `OS:ZoneHVAC:UnitVentilator`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A9` Supply Air Fan Name | `FansCVandOnOffandVAV` | `OS:Fan:ConstantVolume`, `OS:Fan:OnOff`, `OS:Fan:VariableVolume` |
| `A9` Supply Air Fan Name | `FansSystemModel` | `OS:Fan:SystemModel` |
| `A10` Supply Air Fan Operating Mode Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A11` Heating Convergence Tolerance | `HeatingCoilName` | `OS:Coil:Heating:Electric`, `OS:Coil:Heating:Gas`, `OS:Coil:Heating:Water` |
| `A12` Cooling Convergence Tolerance | `CoolingCoilsWater` | `OS:Coil:Cooling:Water`, `OS:CoilSystem:Cooling:Water:HeatExchangerAssisted` |
| `A13` Availability Manager List Name | `SystemAvailabilityManagerLists` | `OS:AvailabilityManagerAssignmentList` |
| `A14` Design Specification ZoneHVAC Sizing Object Name | `DesignSpecificationZoneHVACSizingName` | No `\reference` matches found |

### `OS:ZoneHVAC:WaterToAirHeatPump`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A3` Availability Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A4` Air Inlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A5` Air Outlet Node Name | `ConnectionNames` | Hardcoded reference in IddObject (ConnectionNames); targets not declared in IDD |
| `A6` Outdoor Air Mixer Name | `OutdoorAirMixers` | No `\reference` matches found |
| `A8` Supply Air Fan Name | `FansOnOff` | `OS:Fan:OnOff` |
| `A8` Supply Air Fan Name | `FansSystemModel` | `OS:Fan:SystemModel` |
| `A9` Heating Coil Name | `HeatingCoilsWaterToAirHP` | `OS:Coil:Heating:WaterToAirHeatPump:EquationFit` |
| `A9` Heating Coil Name | `HeatingCoilsWaterToAirVSHP` | `OS:Coil:Heating:WaterToAirHeatPump:VariableSpeedEquationFit` |
| `A10` Cooling Coil Name | `CoolingCoilsWaterToAirHP` | `OS:Coil:Cooling:WaterToAirHeatPump:EquationFit` |
| `A10` Cooling Coil Name | `CoolingCoilsWaterToAirVSHP` | `OS:Coil:Cooling:WaterToAirHeatPump:VariableSpeedEquationFit` |
| `A11` Supplemental Heating Coil Name | `HeatingCoilName` | `OS:Coil:Heating:Electric`, `OS:Coil:Heating:Gas`, `OS:Coil:Heating:Water` |
| `A14` Supply Air Fan Operating Mode Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A15` Availability Manager List Name | `SystemAvailabilityManagerLists` | `OS:AvailabilityManagerAssignmentList` |
| `A17` Design Specification ZoneHVAC Sizing Object Name | `DesignSpecificationZoneHVACSizingName` | No `\reference` matches found |

### `OS:ZoneMixing`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Minimum Source Temperature Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A1` Minimum Source Temperature Schedule Name | `SpaceNames` | `OS:Space` |
| `A1` Minimum Source Temperature Schedule Name | `ThermalZoneNames` | `OS:ThermalZone` |
| `A11` Maximum Source Temperature Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A12` Minimum Outdoor Temperature Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A13` Maximum Outdoor Temperature Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:ZoneProperty:UserViewFactors:BySurfaceName`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A2` Thermal Zone Name | `ThermalZoneNames` | `OS:ThermalZone` |
| `A3` From Surface Name 1 | `AllHeatTranSurfNames` | `OS:InternalMass`, `OS:SubSurface`, `OS:Surface` |
| `A4` To Surface Name 1 | `AllHeatTranSurfNames` | `OS:InternalMass`, `OS:SubSurface`, `OS:Surface` |

### `OS:ZoneVentilation:DesignFlowRate`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `A1` Velocity Term Coefficient | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `N11` Minimum Indoor Temperature Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `N12` Maximum Indoor Temperature Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `N13` Delta Temperature Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `N14` Minimum Outdoor Temperature Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |
| `A10` Maximum Outdoor Temperature Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

### `OS:ZoneVentilation:WindandStackOpenArea`

| Field | Object List | Target OS IddObjectTypes |
| --- | --- | --- |
| `N10` Maximum Outdoor Temperature Schedule Name | `ScheduleNames` | `OS:ExternalInterface:FunctionalMockupUnitExport:To:Schedule`, `OS:ExternalInterface:FunctionalMockupUnitImport:To:Schedule`, `OS:ExternalInterface:Schedule`, `OS:Schedule:Compact`, `OS:Schedule:Constant`, `OS:Schedule:File`, `OS:Schedule:FixedInterval`, `OS:Schedule:Ruleset`, `OS:Schedule:VariableInterval`, `OS:Schedule:Year` |

## HVAC Objects Without Object-List References

`OS:AirflowNetworkConstantPressureDrop`, `OS:AirflowNetworkDetailedOpening`, `OS:AirflowNetworkDuct`, `OS:AirflowNetworkEffectiveLeakageArea`, `OS:AirflowNetworkHorizontalOpening`, `OS:AirflowNetworkLeak`, `OS:AirflowNetworkLeakageRatio`, `OS:AirflowNetworkReferenceCrackConditions`, `OS:AirflowNetworkSimpleOpening`, `OS:AirflowNetworkSimulationControl`, `OS:AirflowNetworkSpecifiedFlowRate`, `OS:CentralHeatPumpSystem:Module`, `OS:ClimateZones`, `OS:Coil:Cooling:LowTemperatureRadiant:VariableFlow`, `OS:Coil:Cooling:Water:Panel:Radiant`, `OS:Coil:Heating:DX:MultiSpeed:StageData`, `OS:Coil:Heating:Electric:MultiStage:StageData`, `OS:Coil:Heating:Gas:MultiStage:StageData`, `OS:Coil:Heating:LowTemperatureRadiant:ConstantFlow`, `OS:Coil:Heating:LowTemperatureRadiant:VariableFlow`, `OS:ComponentCost:Adjustments`, `OS:ConvergenceLimits`, `OS:CoolingTowerPerformance:CoolTools`, `OS:CoolingTowerPerformance:YorkCalc`, `OS:CurrencyType`, `OS:Curve:Bicubic`, `OS:Curve:Biquadratic`, `OS:Curve:Cubic`, `OS:Curve:DoubleExponentialDecay`, `OS:Curve:Exponent`, `OS:Curve:ExponentialDecay`, `OS:Curve:ExponentialSkewNormal`, `OS:Curve:FanPressureRise`, `OS:Curve:Functional:PressureDrop`, `OS:Curve:Linear`, `OS:Curve:QuadLinear`, `OS:Curve:Quadratic`, `OS:Curve:QuadraticLinear`, `OS:Curve:Quartic`, `OS:Curve:QuintLinear`, `OS:Curve:RectangularHyperbola1`, `OS:Curve:RectangularHyperbola2`, `OS:Curve:Sigmoid`, `OS:Curve:Triquadratic`, `OS:DistrictCooling`, `OS:ElectricEquipment:Definition`, `OS:ElectricLoadCenter:Inverter:LookUpTable`, `OS:ElectricLoadCenter:Inverter:PVWatts`, `OS:ElectricLoadCenter:Inverter:Simple`, `OS:EnergyManagementSystem:GlobalVariable`, `OS:EnergyManagementSystem:InternalVariable`, `OS:EnergyManagementSystem:Program`, `OS:EnergyManagementSystem:Sensor`, `OS:EnergyManagementSystem:Subroutine`, `OS:EnvironmentalImpactFactors`, `OS:EvaporativeFluidCooler:TwoSpeed`, `OS:Exterior:FuelEquipment:Definition`, `OS:Exterior:Lights:Definition`, `OS:Exterior:WaterEquipment:Definition`, `OS:External:File`, `OS:ExternalInterface`, `OS:ExternalInterface:FunctionalMockupUnitExport:From:Variable`, `OS:ExternalInterface:FunctionalMockupUnitExport:To:Variable`, `OS:ExternalInterface:FunctionalMockupUnitImport`, `OS:ExternalInterface:Variable`, `OS:Facility`, `OS:Foundation:Kiva:Settings`, `OS:GasEquipment:Definition`, `OS:Generator:FuelCell:ElectricalStorage`, `OS:Generator:Photovoltaic`, `OS:HeatBalanceAlgorithm`, `OS:HeatExchanger:Desiccant:BalancedFlow:PerformanceDataType1`, `OS:HotWaterEquipment:Definition`, `OS:LifeCycleCost:Parameters`, `OS:LifeCycleCost:UsePriceEscalation`, `OS:LightingDesignDay`, `OS:LightingSimulationControl`, `OS:Lights:Definition`, `OS:LoadProfile:Plant`, `OS:Luminaire:Definition`, `OS:Material`, `OS:Material:AirGap`, `OS:Material:InfraredTransparent`, `OS:Material:NoMass`, `OS:Material:RoofVegetation`, `OS:MaterialProperty:GlazingSpectralData`, `OS:Meter:Custom`, `OS:Meter:CustomDecrement`, `OS:OtherEquipment:Definition`, `OS:Output:Constructions`, `OS:Output:DebuggingData`, `OS:Output:Diagnostics`, `OS:Output:EnergyManagementSystem`, `OS:Output:EnvironmentalImpactFactors`, `OS:Output:JSON`, `OS:Output:Meter`, `OS:Output:SQLite`, `OS:Output:Schedules`, `OS:Output:Table:Monthly`, `OS:Output:Table:SummaryReports`, `OS:OutputControl:Files`, `OS:OutputControl:ReportingTolerances`, `OS:OutputControl:ResilienceSummaries`, `OS:OutputControl:Table:Style`, `OS:OutputControl:Timestamp`, `OS:People:Definition`, `OS:PerformancePrecisionTradeoffs`, `OS:PhotovoltaicPerformance:Sandia`, `OS:PhotovoltaicPerformance:Simple`, `OS:PlantComponent:TemperatureSource`, `OS:ProgramControl`, `OS:PythonPlugin:SearchPaths`, `OS:PythonPlugin:Variable`, `OS:RadianceParameters`, `OS:Refrigeration:Condenser:Cascade`, `OS:Refrigeration:DefrostCycleParameters`, `OS:Refrigeration:Subcooler:LiquidSuction`, `OS:Rendering:Color`, `OS:RunPeriod`, `OS:RunPeriodControl:DaylightSavingTime`, `OS:RunPeriodControl:SpecialDays`, `OS:ScheduleTypeLimits`, `OS:SetpointManager:Coldest`, `OS:SetpointManager:FollowGroundTemperature`, `OS:SetpointManager:MultiZone:Cooling:Average`, `OS:SetpointManager:MultiZone:Heating:Average`, `OS:SetpointManager:MultiZone:Humidity:Maximum`, `OS:SetpointManager:MultiZone:MaximumHumidity:Average`, `OS:SetpointManager:SingleZone:Cooling`, `OS:SetpointManager:SingleZone:Heating`, `OS:SetpointManager:SingleZone:Humidity:Maximum`, `OS:SetpointManager:SingleZone:OneStageCooling`, `OS:SetpointManager:SingleZone:OneStageHeating`, `OS:SetpointManager:SystemNodeReset:Humidity`, `OS:SetpointManager:SystemNodeReset:Temperature`, `OS:SimulationControl`, `OS:Site`, `OS:Site:GroundReflectance`, `OS:Site:GroundTemperature:BuildingSurface`, `OS:Site:GroundTemperature:Deep`, `OS:Site:GroundTemperature:FCfactorMethod`, `OS:Site:GroundTemperature:Shallow`, `OS:Site:GroundTemperature:Undisturbed:KusudaAchenbach`, `OS:Site:GroundTemperature:Undisturbed:Xing`, `OS:Sizing:Parameters`, `OS:SizingPeriod:WeatherFileConditionType`, `OS:SizingPeriod:WeatherFileDays`, `OS:SolarCollectorPerformance:FlatPlate`, `OS:SolarCollectorPerformance:IntegralCollectorStorage`, `OS:Splitter`, `OS:SteamEquipment:Definition`, `OS:SurfaceConvectionAlgorithm:Inside`, `OS:SurfaceConvectionAlgorithm:Outside`, `OS:SurfaceProperty:OtherSideConditionsModel`, `OS:Table:MultiVariableLookup`, `OS:Timestep`, `OS:UnitarySystemPerformance:Multispeed`, `OS:UtilityBill`, `OS:Version`, `OS:WeatherFile`, `OS:WindowMaterial:Blind`, `OS:WindowMaterial:DaylightRedirectionDevice`, `OS:WindowMaterial:Gas`, `OS:WindowMaterial:GasMixture`, `OS:WindowMaterial:Glazing:RefractionExtinctionMethod`, `OS:WindowMaterial:Screen`, `OS:WindowMaterial:Shade`, `OS:WindowMaterial:SimpleGlazingSystem`, `OS:WindowProperty:FrameAndDivider`, `OS:YearDescription`, `OS:ZoneAirHeatBalanceAlgorithm`, `OS:ZoneAirMassFlowConservation`, `OS:ZoneCapacitanceMultiplier:ResearchSpecial`, `OS:ZoneHVAC:Baseboard:Convective:Electric`, `OS:ZoneHVAC:Baseboard:RadiantConvective:Electric`, `OS:ZoneHVAC:CoolingPanel:RadiantConvective:Water`, `OS:ZoneHVAC:EnergyRecoveryVentilator:Controller`, `OS:ZoneHVAC:UnitHeater`

