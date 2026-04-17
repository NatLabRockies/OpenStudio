#!/usr/bin/env python3
"""Generate an organizational view of OS IDD types.

Source:
- doc/idd-schema-alignment/idd_mapping.generated.md

Output:
- doc/idd-schema-alignment/idd_mapping_categories.generated.md
"""

from __future__ import annotations

from collections import defaultdict
from dataclasses import dataclass
from pathlib import Path
import re

ROOT = Path(__file__).resolve().parents[3]
IN_PATH = ROOT / "doc/idd-schema-alignment/idd_mapping.generated.md"
OUT_PATH = ROOT / "doc/idd-schema-alignment/idd_mapping_categories.generated.md"

CONCEPTUAL_FAMILY_ORDER = [
    "Airloop topology and distribution",
    "Air terminals and zone air distribution",
    "Central air, unitary, and VRF equipment",
    "Zone HVAC equipment",
    "Plant equipment and hydronic distribution",
    "Water heaters and thermal storage",
    "Generators, electrical, and CHP",
    "Refrigeration",
    "AirflowNetwork and natural ventilation",
    "Loads and water use",
    "Controls, schedules, and setpoint management",
    "Geometry, envelope, and materials",
    "Site, weather, simulation, and sizing",
    "Output, reporting, EMS, and external interfaces",
    "Performance curves and lookup tables",
    "Project metadata, defaults, and economics",
]

SPECIAL_BASE_ORDER = [
    "StraightComponent",
    "ZoneHVACComponent",
    "HVACComponent",
    "WaterToAirComponent",
    "WaterToWaterComponent",
    "PlantEquipmentOperationRangeBasedScheme",
    "AirToAirComponent",
    "Loop",
    "Mixer",
    "Splitter",
    "SetpointManager",
    "AvailabilityManager",
    "AirflowNetworkComponent",
    "AirflowNetworkNode",
    "AirflowNetworkLinkage",
    "SpaceLoadInstance",
    "SpaceLoadDefinition",
    "SpaceLoad",
    "ExteriorLoadInstance",
    "ExteriorLoadDefinition",
    "SpaceItem",
    "Schedule",
    "ScheduleInterval",
    "ScheduleBase",
    "SizingPeriod",
    "Curve",
    "Thermostat",
    "ConstructionBase",
    "LayeredConstruction",
    "OpaqueMaterial",
    "Glazing",
    "GasLayer",
    "ModelPartitionMaterial",
    "ShadingMaterial",
    "PlanarSurface",
    "PlanarSurfaceGroup",
    "Generator",
    "Inverter",
    "ElectricalStorage",
    "PhotovoltaicPerformance",
    "ResourceObject",
    "ParentObject",
    "ModelObject",
    "",
]

PREFIX_FAMILIES = [
    "Generator:FuelCell",
    "Generator:FuelSupply",
    "ElectricLoadCenter",
    "EnergyManagementSystem",
    "EnvironmentalImpactFactors",
    "ExternalInterface",
    "CoolingTowerPerformance",
    "ConvergenceLimits",
    "DaylightingDevice",
    "DesignSpecification",
    "MaterialProperty",
    "OutputControl",
    "PerformancePrecisionTradeoffs",
    "SolarCollectorPerformance",
    "StandardsInformation",
    "SurfaceProperty",
    "WindowProperty",
    "AirflowNetwork",
    "AvailabilityManager",
    "Building",
    "ClimateZones",
    "Connection",
    "Foundation",
    "FuelFactors",
    "HeatBalanceAlgorithm",
    "LifeCycleCost",
    "Lighting",
    "Meter",
    "ModelObjectList",
    "Output",
    "PythonPlugin",
    "Radiance",
    "Refrigeration",
    "RunPeriod",
    "SimulationControl",
    "Site",
    "Table",
    "UtilityCost",
    "YearDescription",
]

SPECIAL_SUBCATEGORY_ORDER = {
    "StraightComponent": [
        "Air terminals",
        "Airloop and central air equipment",
        "Zone and radiant coils",
        "Plant equipment",
        "Heat recovery and generator auxiliaries",
        "Other StraightComponents",
    ],
    "ZoneHVACComponent": [
        "Hybrid airloop-zone unitary equipment",
        "Zone HVAC equipment",
        "Zone ventilation and exhaust",
        "Heat pump water heaters",
        "Refrigeration zone equipment",
        "Other ZoneHVAC components",
    ],
    "HVACComponent": [
        "VRF system components",
        "Outdoor-air and controller infrastructure",
        "Water-heating HVAC components",
        "Thermal-zone infrastructure",
        "Other HVAC components",
    ],
    "WaterToAirComponent": [
        "Hydronic air coils",
        "Water-to-air heat pump coils",
        "User-defined water-to-air components",
        "Other WaterToAir components",
    ],
    "WaterToWaterComponent": [
        "Chillers",
        "Plant-loop and water-to-water heat pumps",
        "Thermal storage and water heaters",
        "Central plant connectors and heat exchangers",
        "Other WaterToWater components",
    ],
    "Mixer": [
        "Dual-duct air terminals",
        "Airloop mixers and plenums",
        "Connector mixers",
        "Other Mixer objects",
    ],
    "Splitter": [
        "Airloop splitters and plenums",
        "Connector splitters",
        "Other Splitter objects",
    ],
    "ModelObject": [
        "AirflowNetwork and natural ventilation support",
        "Controls, EMS, and external interface",
        "Output, reporting, and diagnostics",
        "Site, weather, and simulation settings",
        "Envelope, material, and surface properties",
        "Lighting, daylighting, and solar support",
        "Electrical generation and load-center support",
        "HVAC, sizing, and zone support",
        "Refrigeration and plant performance support",
        "Project metadata and misc infrastructure",
    ],
    "ParentObject": [
        "Coil and heat-pump performance data",
        "Electrical distribution and economic objects",
        "Refrigeration parent systems",
        "Building, site, and simulation containers",
        "HVAC controllers and parent infrastructure",
        "Other ParentObject types",
    ],
    "ResourceObject": [
        "Defaults, schedules, and space typing",
        "DX and heat-pump performance resources",
        "Material, glazing, and surface-property resources",
        "External data, tables, and metadata",
        "Controls and plugin resources",
        "Other ResourceObject types",
    ],
}


@dataclass(frozen=True)
class Row:
    os_idd_type: str
    model_class: str
    base_class: str
    ep_types: tuple[str, ...]
    ft_files: tuple[str, ...]

    @property
    def has_ep_output(self) -> bool:
        return bool(self.ep_types)


def parse_backtick_list(cell: str) -> tuple[str, ...]:
    items = re.findall(r"`([^`]+)`", cell)
    if items:
        return tuple(items)
    cell = cell.strip()
    return (cell,) if cell else ()


def parse_os_mapping_rows(text: str) -> list[Row]:
    lines = text.splitlines()
    in_table = False
    rows: list[Row] = []

    for line in lines:
        if line == "| OS IddObjectType | Model class | Direct OS base class | EP IddObjectType(s) produced | FT source file(s) |":
            in_table = True
            continue

        if not in_table:
            continue

        if not line.startswith("|"):
            break

        if line.startswith("| ---"):
            continue

        cells = [cell.strip().strip("`") for cell in line.strip().strip("|").split("|")]
        if len(cells) != 5:
            continue

        rows.append(
            Row(
                os_idd_type=cells[0],
                model_class=cells[1],
                base_class=cells[2],
                ep_types=parse_backtick_list(cells[3]),
                ft_files=parse_backtick_list(cells[4]),
            )
        )

    return rows


def conceptual_family_for_row(row: Row) -> str:
    name = row.os_idd_type
    base = row.base_class
    zone_radiant_coils = {
        "OS:Coil:Cooling:CooledBeam",
        "OS:Coil:Cooling:FourPipeBeam",
        "OS:Coil:Heating:FourPipeBeam",
        "OS:Coil:Cooling:Water:Panel:Radiant",
        "OS:Coil:Cooling:LowTemperatureRadiant:ConstantFlow",
        "OS:Coil:Cooling:LowTemperatureRadiant:VariableFlow",
        "OS:Coil:Heating:LowTemperatureRadiant:ConstantFlow",
        "OS:Coil:Heating:LowTemperatureRadiant:VariableFlow",
        "OS:Coil:Heating:Water:Baseboard",
        "OS:Coil:Heating:Water:Baseboard:Radiant",
    }

    if (
        name.startswith("OS:Generator:")
        or name.startswith("OS:ElectricLoadCenter:")
        or base in {"Generator", "Inverter", "ElectricalStorage", "PhotovoltaicPerformance"}
    ):
        return "Generators, electrical, and CHP"

    if name.startswith("OS:Refrigeration:"):
        return "Refrigeration"

    if name.startswith("OS:AirflowNetwork:") or name.startswith("OS:AirflowNetwork") or name == "OS:ZoneMixing":
        return "AirflowNetwork and natural ventilation"

    if (
        name.startswith("OS:Schedule")
        or name.startswith("OS:SetpointManager:")
        or name.startswith("OS:AvailabilityManager:")
        or name.startswith("OS:ZoneControl:")
        or base in {"Schedule", "ScheduleInterval", "ScheduleBase", "Thermostat", "AvailabilityManager", "SetpointManager"}
    ):
        return "Controls, schedules, and setpoint management"

    if (
        name.startswith("OS:EnergyManagementSystem:")
        or name.startswith("OS:ExternalInterface")
        or name.startswith("OS:PythonPlugin:")
        or name.startswith("OS:Output:")
        or name.startswith("OS:OutputControl:")
        or name.startswith("OS:Meter:")
        or name == "OS:ProgramControl"
        or name == "OS:RadianceParameters"
    ):
        return "Output, reporting, EMS, and external interfaces"

    if base == "Curve" or name.startswith("OS:Table:"):
        return "Performance curves and lookup tables"

    if (
        base in {
            "ConstructionBase",
            "LayeredConstruction",
            "OpaqueMaterial",
            "Glazing",
            "GasLayer",
            "ModelPartitionMaterial",
            "ShadingMaterial",
            "PlanarSurface",
            "PlanarSurfaceGroup",
        }
        or name.startswith("OS:MaterialProperty:")
        or name.startswith("OS:SurfaceProperty:")
        or name.startswith("OS:SurfaceControl:")
        or name.startswith("OS:SurfaceConvectionAlgorithm:")
        or name.startswith("OS:WindowProperty:")
        or name.startswith("OS:Foundation:")
        or name.startswith("OS:DaylightingDevice:")
        or name.startswith("OS:Daylighting:")
        or name.startswith("OS:Glare:")
        or name.startswith("OS:IlluminanceMap")
        or name.startswith("OS:ShadingControl")
        or name.startswith("OS:StandardsInformation:")
    ):
        return "Geometry, envelope, and materials"

    if (
        base in {"SpaceLoadInstance", "SpaceLoadDefinition", "SpaceLoad", "ExteriorLoadInstance", "ExteriorLoadDefinition", "SpaceItem"}
        or name.startswith("OS:WaterUse:")
    ):
        return "Loads and water use"

    if (
        name.startswith("OS:WaterHeater:")
        or name.startswith("OS:ThermalStorage:")
        or name.startswith("OS:Coil:WaterHeating:")
    ):
        return "Water heaters and thermal storage"

    if (
        base == "WaterToWaterComponent"
        or base == "PlantEquipmentOperationRangeBasedScheme"
        or name.startswith("OS:PlantLoop")
        or name.startswith("OS:PlantEquipmentOperation:")
        or name.startswith("OS:Boiler:")
        or name.startswith("OS:Chiller:")
        or name.startswith("OS:CoolingTower:")
        or name.startswith("OS:District")
        or name.startswith("OS:EvaporativeFluidCooler:")
        or name.startswith("OS:FluidCooler:")
        or name.startswith("OS:GroundHeatExchanger:")
        or name.startswith("OS:HeaderedPumps:")
        or name.startswith("OS:HeatPump:AirToWater")
        or name.startswith("OS:HeatPump:PlantLoop:")
        or name.startswith("OS:Pipe:")
        or name.startswith("OS:PlantComponent:")
        or name.startswith("OS:Pump:")
        or name.startswith("OS:LoadProfile:Plant")
        or name.startswith("OS:SolarCollector:")
        or name.startswith("OS:SolarCollectorPerformance:")
        or name.startswith("OS:SwimmingPool:")
        or name.startswith("OS:TemperingValve")
    ):
        return "Plant equipment and hydronic distribution"

    if (
        name.startswith("OS:AirTerminal:")
        or name == "OS:ZoneHVAC:EquipmentList"
        or name.startswith("OS:DesignSpecification:OutdoorAir")
        or name.startswith("OS:DesignSpecification:ZoneAirDistribution")
    ):
        return "Air terminals and zone air distribution"

    if (
        name.startswith("OS:AirConditioner:VariableRefrigerantFlow")
        or name.startswith("OS:AirLoopHVAC:Unitary")
        or name == "OS:AirLoopHVAC:UnitarySystem"
        or base in {"WaterToAirComponent", "AirToAirComponent"}
        or name.startswith("OS:CoilSystem:")
        or (name.startswith("OS:Fan:") and name != "OS:Fan:ZoneExhaust")
        or name.startswith("OS:Humidifier:")
        or name.startswith("OS:EvaporativeCooler:")
        or name.startswith("OS:HeatExchanger:AirToAir:")
        or name.startswith("OS:HeatExchanger:Desiccant:")
        or name.startswith("OS:Coil:Cooling:DX")
        or name.startswith("OS:Coil:Heating:DX")
        or (name.startswith("OS:Coil:Cooling:Water") and name not in zone_radiant_coils)
        or (name.startswith("OS:Coil:Heating:Water") and name not in zone_radiant_coils)
        or name == "OS:Coil:UserDefined"
        or name in {
            "OS:Coil:Heating:Electric",
            "OS:Coil:Heating:Electric:MultiStage",
            "OS:Coil:Heating:Gas",
            "OS:Coil:Heating:Gas:MultiStage",
        }
        or name in {
            "OS:AirLoopHVAC:OutdoorAirSystem",
            "OS:Controller:MechanicalVentilation",
            "OS:Controller:WaterCoil",
        }
    ):
        return "Central air, unitary, and VRF equipment"

    if (
        name == "OS:ThermalZone"
        or base == "ZoneHVACComponent"
        or name.startswith("OS:ZoneHVAC:")
        or name.startswith("OS:ZoneVentilation:")
        or name == "OS:Fan:ZoneExhaust"
        or "Radiant" in name
        or "Baseboard" in name
        or name in zone_radiant_coils
    ):
        return "Zone HVAC equipment"

    if (
        base in {"Loop", "Mixer", "Splitter"}
        or name == "OS:Node"
        or name == "OS:Duct"
        or name == "OS:Connection"
        or name == "OS:PortList"
        or name == "OS:HVACComponentList"
        or name == "OS:Splitter"
        or name.startswith("OS:AirLoopHVAC:")
        or name.startswith("OS:Connector:")
    ):
        return "Airloop topology and distribution"

    if (
        name.startswith("OS:ClimateZones")
        or name.startswith("OS:ConvergenceLimits")
        or name.startswith("OS:EnvironmentalImpactFactors")
        or name.startswith("OS:FuelFactors")
        or name.startswith("OS:HeatBalanceAlgorithm")
        or name.startswith("OS:PerformancePrecisionTradeoffs")
        or name.startswith("OS:RunPeriod")
        or name.startswith("OS:ShadowCalculation")
        or name.startswith("OS:Site:")
        or name.startswith("OS:Sizing:")
        or name.startswith("OS:SizingPeriod:")
        or name.startswith("OS:SimulationControl")
        or name.startswith("OS:Timestep")
        or name.startswith("OS:Version")
        or name.startswith("OS:Weather")
        or name.startswith("OS:YearDescription")
        or name.startswith("OS:ZoneAir")
        or name.startswith("OS:ZoneCapacitanceMultiplier:")
    ):
        return "Site, weather, simulation, and sizing"

    return "Project metadata, defaults, and economics"


def family_sort_key(item: tuple[str, list[Row]]) -> tuple[int, str]:
    family = item[0]
    try:
        idx = CONCEPTUAL_FAMILY_ORDER.index(family)
    except ValueError:
        idx = len(CONCEPTUAL_FAMILY_ORDER)
    return (idx, family)


def family_bucket(os_idd_type: str) -> str:
    body = os_idd_type[3:]

    for prefix in PREFIX_FAMILIES:
        if body.startswith(prefix):
            return prefix

    tokens = body.split(":")
    if not tokens:
        return "Other"

    first = tokens[0]
    second = tokens[1] if len(tokens) > 1 else ""

    if first in {
        "AirLoopHVAC",
        "AirTerminal",
        "AirflowNetwork",
        "AvailabilityManager",
        "CentralHeatPumpSystem",
        "DaylightingDevice",
        "ElectricLoadCenter",
        "EnergyManagementSystem",
        "ExternalInterface",
        "Foundation",
        "LifeCycleCost",
        "MaterialProperty",
        "Output",
        "PlantEquipmentOperation",
        "PythonPlugin",
        "Refrigeration",
        "Schedule",
        "SetpointManager",
        "SizingPeriod",
        "SurfaceProperty",
        "Table",
        "Thermostat",
        "UtilityCost",
        "WindowProperty",
        "ZoneHVAC",
        "ZoneVentilation",
    }:
        return first

    if first in {"AirConditioner", "Coil", "Exterior", "Generator", "HeatPump", "WaterHeater"} and second:
        if first == "Generator" and second == "FuelCell":
            return "Generator:FuelCell"
        return f"{first}:{second}"

    return first


def straight_component_bucket(row: Row) -> str:
    name = row.os_idd_type

    if name.startswith("OS:AirTerminal:"):
        return "Air terminals"

    if (
        name.startswith("OS:AirConditioner:VariableRefrigerantFlow")
        or name.startswith("OS:AirLoopHVAC:Unitary")
        or name.startswith("OS:CoilSystem:")
        or name.startswith("OS:Fan:")
        or name.startswith("OS:Humidifier:")
        or name.startswith("OS:EvaporativeCooler:")
        or name == "OS:Duct"
        or name.startswith("OS:Coil:Cooling:DX")
        or name.startswith("OS:Coil:Heating:DX")
        or name in {
            "OS:Coil:Heating:Electric",
            "OS:Coil:Heating:Electric:MultiStage",
            "OS:Coil:Heating:Gas",
            "OS:Coil:Heating:Gas:MultiStage",
        }
    ):
        return "Airloop and central air equipment"

    if (
        "Radiant" in name
        or "Beam" in name
        or "Induction" in name
        or "Baseboard" in name
        or name in {
            "OS:Coil:Cooling:CooledBeam",
            "OS:Coil:Cooling:FourPipeBeam",
            "OS:Coil:Heating:FourPipeBeam",
        }
    ):
        return "Zone and radiant coils"

    if (
        name.startswith("OS:Boiler:")
        or name.startswith("OS:CoolingTower:")
        or name.startswith("OS:District")
        or name.startswith("OS:EvaporativeFluidCooler:")
        or name.startswith("OS:FluidCooler:")
        or name.startswith("OS:GroundHeatExchanger:")
        or name.startswith("OS:HeaderedPumps:")
        or name.startswith("OS:HeatPump:AirToWater")
    ):
        return "Plant equipment"

    if (
        "Desuperheater" in name
        or name.startswith("OS:Generator:FuelCell:")
        or name.startswith("OS:Generator:MicroTurbine:")
    ):
        return "Heat recovery and generator auxiliaries"

    return "Other StraightComponents"


def zone_hvac_bucket(row: Row) -> str:
    name = row.os_idd_type

    if name == "OS:AirLoopHVAC:UnitarySystem":
        return "Hybrid airloop-zone unitary equipment"
    if name.startswith("OS:ZoneHVAC:"):
        return "Zone HVAC equipment"
    if name == "OS:Fan:ZoneExhaust" or name.startswith("OS:ZoneVentilation:"):
        return "Zone ventilation and exhaust"
    if name.startswith("OS:WaterHeater:HeatPump"):
        return "Heat pump water heaters"
    if name.startswith("OS:Refrigeration:AirChiller"):
        return "Refrigeration zone equipment"
    return "Other ZoneHVAC components"


def hvac_component_bucket(row: Row) -> str:
    name = row.os_idd_type

    if "VariableRefrigerantFlow" in name:
        return "VRF system components"
    if name.startswith("OS:AirLoopHVAC:OutdoorAirSystem") or name.startswith("OS:Controller:WaterCoil"):
        return "Outdoor-air and controller infrastructure"
    if name.startswith("OS:Coil:WaterHeating:"):
        return "Water-heating HVAC components"
    if name == "OS:ThermalZone":
        return "Thermal-zone infrastructure"
    return "Other HVAC components"


def water_to_air_bucket(row: Row) -> str:
    name = row.os_idd_type

    if "WaterToAirHeatPump" in name:
        return "Water-to-air heat pump coils"
    if name == "OS:Coil:UserDefined":
        return "User-defined water-to-air components"
    if name.startswith("OS:Coil:Cooling:Water") or name.startswith("OS:Coil:Heating:Water"):
        return "Hydronic air coils"
    return "Other WaterToAir components"


def water_to_water_bucket(row: Row) -> str:
    name = row.os_idd_type

    if name.startswith("OS:Chiller:"):
        return "Chillers"
    if name.startswith("OS:HeatPump:") or name.startswith("OS:CentralHeatPumpSystem"):
        return "Plant-loop and water-to-water heat pumps"
    if name.startswith("OS:ThermalStorage:") or name.startswith("OS:WaterHeater:"):
        return "Thermal storage and water heaters"
    if name.startswith("OS:HeatExchanger:"):
        return "Central plant connectors and heat exchangers"
    return "Other WaterToWater components"


def mixer_bucket(row: Row) -> str:
    name = row.os_idd_type
    if name.startswith("OS:AirTerminal:DualDuct:"):
        return "Dual-duct air terminals"
    if name == "OS:Connector:Mixer":
        return "Connector mixers"
    if name.startswith("OS:AirLoopHVAC:"):
        return "Airloop mixers and plenums"
    return "Other Mixer objects"


def splitter_bucket(row: Row) -> str:
    name = row.os_idd_type
    if name == "OS:Connector:Splitter":
        return "Connector splitters"
    if name.startswith("OS:AirLoopHVAC:"):
        return "Airloop splitters and plenums"
    return "Other Splitter objects"


def _matches(row: Row, prefixes: tuple[str, ...] = (), exact: tuple[str, ...] = ()) -> bool:
    return row.os_idd_type in exact or any(row.os_idd_type.startswith(prefix) for prefix in prefixes)


def model_object_bucket(row: Row) -> str:
    if _matches(
        row,
        prefixes=(
            "OS:AirflowNetwork",
            "OS:ZoneMixing",
        ),
    ):
        return "AirflowNetwork and natural ventilation support"

    if _matches(
        row,
        prefixes=(
            "OS:EnergyManagementSystem:",
            "OS:ExternalInterface",
            "OS:PythonPlugin:",
            "OS:ZoneControl:",
        ),
        exact=(
            "OS:ProgramControl",
            "OS:Controller:MechanicalVentilation",
        ),
    ):
        return "Controls, EMS, and external interface"

    if _matches(
        row,
        prefixes=(
            "OS:Output:",
            "OS:OutputControl:",
            "OS:Meter:",
            "OS:RadianceParameters",
        ),
    ):
        return "Output, reporting, and diagnostics"

    if _matches(
        row,
        prefixes=(
            "OS:ClimateZones",
            "OS:ConvergenceLimits",
            "OS:EnvironmentalImpactFactors",
            "OS:FuelFactors",
            "OS:Foundation:",
            "OS:HeatBalanceAlgorithm",
            "OS:PerformancePrecisionTradeoffs",
            "OS:RunPeriodControl:",
            "OS:ShadowCalculation",
            "OS:Site:",
            "OS:Timestep",
            "OS:Version",
            "OS:Weather",
            "OS:ZoneAir",
            "OS:ZoneCapacitanceMultiplier:",
        ),
    ):
        return "Site, weather, and simulation settings"

    if _matches(
        row,
        prefixes=(
            "OS:MaterialProperty:",
            "OS:StandardsInformation:",
            "OS:SurfaceControl:",
            "OS:SurfaceConvectionAlgorithm:",
            "OS:SurfaceProperty:",
            "OS:ZoneProperty:",
        ),
    ):
        return "Envelope, material, and surface properties"

    if _matches(
        row,
        prefixes=(
            "OS:DaylightingDevice:",
            "OS:Lighting",
            "OS:SolarCollectorPerformance:",
        ),
    ):
        return "Lighting, daylighting, and solar support"

    if _matches(
        row,
        prefixes=(
            "OS:ElectricLoadCenter:",
            "OS:Generator:FuelCell:",
            "OS:Generator:FuelSupply",
        ),
    ):
        return "Electrical generation and load-center support"

    if _matches(
        row,
        prefixes=(
            "OS:AirLoopHVAC:",
            "OS:Coil:",
            "OS:DesignSpecification:",
            "OS:Sizing:",
            "OS:UnitarySystemPerformance:",
            "OS:WaterHeater:Sizing",
            "OS:ZoneHVAC:",
        ),
        exact=(
            "OS:Connection",
            "OS:PortList",
        ),
    ):
        return "HVAC, sizing, and zone support"

    if _matches(
        row,
        prefixes=(
            "OS:CoolingTowerPerformance:",
            "OS:Refrigeration:",
        ),
    ):
        return "Refrigeration and plant performance support"

    return "Project metadata and misc infrastructure"


def parent_object_bucket(row: Row) -> str:
    if _matches(
        row,
        prefixes=(
            "OS:AirConditioner:VariableRefrigerantFlow:FluidTemperatureControl:LoadingIndex",
            "OS:CentralHeatPumpSystem:",
            "OS:ChillerHeaterPerformance:",
            "OS:Coil:",
            "OS:CoilPerformance:",
        ),
    ):
        return "Coil and heat-pump performance data"

    if _matches(
        row,
        prefixes=(
            "OS:ComponentCost:",
            "OS:CurrencyType",
            "OS:ElectricLoadCenter:",
            "OS:LifeCycleCost:",
        ),
    ):
        return "Electrical distribution and economic objects"

    if _matches(
        row,
        prefixes=(
            "OS:Refrigeration:",
        ),
    ):
        return "Refrigeration parent systems"

    if _matches(
        row,
        prefixes=(
            "OS:AirflowNetworkSimulationControl",
            "OS:Building",
            "OS:Facility",
            "OS:RunPeriod",
            "OS:Schedule:Rule",
            "OS:SimulationControl",
            "OS:Site",
            "OS:YearDescription",
        ),
    ):
        return "Building, site, and simulation containers"

    if _matches(
        row,
        prefixes=(
            "OS:Controller:",
            "OS:ZoneHVAC:",
        ),
    ):
        return "HVAC controllers and parent infrastructure"

    return "Other ParentObject types"


def resource_object_bucket(row: Row) -> str:
    if _matches(
        row,
        prefixes=(
            "OS:Default",
            "OS:DesignSpecification:OutdoorAir",
            "OS:Schedule:",
            "OS:ScheduleTypeLimits",
            "OS:SpaceType",
        ),
    ):
        return "Defaults, schedules, and space typing"

    if _matches(
        row,
        prefixes=(
            "OS:Coil:Cooling:DX:CurveFit:",
            "OS:HeatExchanger:Desiccant:BalancedFlow:PerformanceDataType1",
            "OS:HeatPump:AirToWater:",
        ),
    ):
        return "DX and heat-pump performance resources"

    if _matches(
        row,
        prefixes=(
            "OS:MaterialProperty:",
            "OS:ShadingControl",
            "OS:SurfaceProperty:",
            "OS:WindowProperty:",
        ),
    ):
        return "Material, glazing, and surface-property resources"

    if _matches(
        row,
        prefixes=(
            "OS:ComponentData",
            "OS:External:File",
            "OS:Rendering:Color",
            "OS:Table:",
        ),
    ):
        return "External data, tables, and metadata"

    if _matches(
        row,
        prefixes=(
            "OS:PythonPlugin:",
        ),
    ):
        return "Controls and plugin resources"

    return "Other ResourceObject types"


SPECIAL_BUCKETS = {
    "StraightComponent": straight_component_bucket,
    "ZoneHVACComponent": zone_hvac_bucket,
    "HVACComponent": hvac_component_bucket,
    "WaterToAirComponent": water_to_air_bucket,
    "WaterToWaterComponent": water_to_water_bucket,
    "Mixer": mixer_bucket,
    "Splitter": splitter_bucket,
    "ModelObject": model_object_bucket,
    "ParentObject": parent_object_bucket,
    "ResourceObject": resource_object_bucket,
}


def subcategory_for_row(row: Row) -> str:
    handler = SPECIAL_BUCKETS.get(row.base_class)
    if handler:
        return handler(row)
    return family_bucket(row.os_idd_type)


def base_sort_key(item: tuple[str, list[Row]]) -> tuple[int, int, str]:
    base, rows = item
    try:
        idx = SPECIAL_BASE_ORDER.index(base)
    except ValueError:
        idx = len(SPECIAL_BASE_ORDER)
    return (idx, -len(rows), base or "~")


def subcategory_sort_key(base: str, item: tuple[str, list[Row]]) -> tuple[int, str]:
    subcategory = item[0]
    ordered = SPECIAL_SUBCATEGORY_ORDER.get(base, [])
    if subcategory in ordered:
        return (ordered.index(subcategory), subcategory)
    return (len(ordered), subcategory)


def format_row(row: Row) -> str:
    entry = f"`{row.os_idd_type}`"
    if not row.has_ep_output:
        entry += " (no EP output evidence)"
    return entry


def main() -> None:
    rows = parse_os_mapping_rows(IN_PATH.read_text())

    by_base: dict[str, list[Row]] = defaultdict(list)
    for row in rows:
        by_base[row.base_class].append(row)

    by_family: dict[str, list[Row]] = defaultdict(list)
    for row in rows:
        by_family[conceptual_family_for_row(row)].append(row)

    lines: list[str] = []
    lines.append("# OS IDD Type Categories (Generated)")
    lines.append("")
    lines.append(
        "This file reorganizes `idd_mapping.generated.md` into review-oriented categories."
    )
    lines.append("")
    lines.append("## Method")
    lines.append("")
    lines.append("- Source rows: `doc/idd-schema-alignment/idd_mapping.generated.md` `OS -> EP (Full)`.")
    lines.append("- Primary grouping: curated conceptual families intended for review and status work.")
    lines.append(
        "- Secondary grouping: `Direct OS base class` from the mapping inventory, preserved within each conceptual family."
    )
    lines.append("- A row appears exactly once in this file.")
    lines.append("- `no EP output evidence` means the source mapping row had an empty `EP IddObjectType(s) produced` cell.")
    lines.append("")
    lines.append("## Conceptual Family Summary")
    lines.append("")
    lines.append("| Conceptual family | Count | Without EP output evidence |")
    lines.append("| --- | ---: | ---: |")

    for family, family_rows in sorted(by_family.items(), key=family_sort_key):
        no_ep = sum(1 for row in family_rows if not row.has_ep_output)
        lines.append(f"| {family} | {len(family_rows)} | {no_ep} |")

    lines.append("")
    lines.append("## Direct Base Class Summary")
    lines.append("")
    lines.append("| Direct OS base class | Count | Without EP output evidence |")
    lines.append("| --- | ---: | ---: |")

    for base, base_rows in sorted(by_base.items(), key=base_sort_key):
        label = f"`{base}`" if base else "_unresolved_"
        no_ep = sum(1 for row in base_rows if not row.has_ep_output)
        lines.append(f"| {label} | {len(base_rows)} | {no_ep} |")

    lines.append("")
    lines.append("## Categories")
    lines.append("")

    for family, family_rows in sorted(by_family.items(), key=family_sort_key):
        no_ep = sum(1 for row in family_rows if not row.has_ep_output)
        suffix = f"; {no_ep} without EP output evidence" if no_ep else ""
        lines.append(f"## {family} ({len(family_rows)}{suffix})")
        lines.append("")

        by_family_base: dict[str, list[Row]] = defaultdict(list)
        for row in sorted(family_rows, key=lambda r: (r.base_class or "~", r.os_idd_type)):
            by_family_base[row.base_class].append(row)

        for base, base_rows in sorted(by_family_base.items(), key=base_sort_key):
            label = f"`{base}`" if base else "Unresolved base class"
            lines.append(f"### {label} ({len(base_rows)})")
            lines.append("")
            lines.append(", ".join(format_row(row) for row in base_rows))
            lines.append("")

    OUT_PATH.write_text("\n".join(lines) + "\n")


if __name__ == "__main__":
    main()
