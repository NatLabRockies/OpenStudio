#!/usr/bin/env python3
"""Generate a minimal AirLoopHVAC model and export OSM + IDF."""

from pathlib import Path

import openstudio


def _is_hvac_related(idd_name: str) -> bool:
    # Keep HVAC objects and their direct dependencies (nodes, branches, curves, schedules).
    keep_exact = {
        "Zone",
        "ZoneHVAC:EquipmentConnections",
        "ZoneHVAC:EquipmentList",
        "ZoneHVAC:AirDistributionUnit",
        "AirTerminal:SingleDuct:Uncontrolled",
        "AirTerminal:SingleDuct:ConstantVolume:NoReheat",
        "Fan:ConstantVolume",
        "Coil:Cooling:DX:SingleSpeed",
        "Coil:Heating:Electric",
        "AirLoopHVAC",
        "AirLoopHVAC:SupplyPath",
        "AirLoopHVAC:ZoneSplitter",
        "AirLoopHVAC:ZoneMixer",
        "Branch",
        "BranchList",
        "Connector:Splitter",
        "Connector:Mixer",
        "Node",
        "NodeList",
        "Schedule:Constant",
        "ScheduleTypeLimits",
        "Curve:Biquadratic",
        "Curve:Quadratic",
    }

    keep_prefixes = (
        "SetpointManager:",
        "Controller:",
        "OutdoorAir:",
    )

    if idd_name in keep_exact:
        return True
    return any(idd_name.startswith(prefix) for prefix in keep_prefixes)


def _strip_non_hvac_objects(idf: openstudio.Workspace) -> None:
    to_remove = []
    for obj in idf.objects():
        idd_name = obj.iddObject().name()
        if not _is_hvac_related(idd_name):
            to_remove.append(obj.handle())
    if to_remove:
        idf.removeObjects(to_remove)


def main() -> None:
    # Resolve output paths relative to doc/idd-schema-alignment/.
    base_dir = Path(__file__).resolve().parents[1]
    osm_path = base_dir / "minimal_airloop.osm"
    idf_path = base_dir / "minimal_airloop.idf"

    model = openstudio.model.Model()

    # One thermal zone with minimal geometry so it translates.
    thermal_zone = openstudio.model.ThermalZone(model)
    space = openstudio.model.Space(model)
    space.setThermalZone(thermal_zone)

    # Simple rectangular floor surface to ensure the zone is translated.
    points = openstudio.Point3dVector()
    points.append(openstudio.Point3d(0, 0, 0))
    points.append(openstudio.Point3d(10, 0, 0))
    points.append(openstudio.Point3d(10, 10, 0))
    points.append(openstudio.Point3d(0, 10, 0))
    surface = openstudio.model.Surface(points, model)
    surface.setSpace(space)
    surface.setSurfaceType("Floor")
    surface.setOutsideBoundaryCondition("Adiabatic")

    # Create air loop and required supply-side components.
    air_loop = openstudio.model.AirLoopHVAC(model)

    fan = openstudio.model.FanConstantVolume(model)
    coil_cooling = openstudio.model.CoilCoolingDXSingleSpeed(model)
    coil_heating = openstudio.model.CoilHeatingElectric(model)

    # Place components on the supply side in order: fan -> cooling -> heating.
    fan.addToNode(air_loop.supplyInletNode())
    coil_cooling.addToNode(air_loop.supplyInletNode())
    coil_heating.addToNode(air_loop.supplyInletNode())

    # Add a terminal and connect the zone to the air loop.
    always_on = model.alwaysOnDiscreteSchedule()
    terminal = openstudio.model.AirTerminalSingleDuctUncontrolled(model, always_on)
    air_loop.addBranchForZone(thermal_zone, terminal)

    # Save the OpenStudio model.
    model.save(openstudio.path(str(osm_path)), True)

    # Translate to EnergyPlus IDF and save.
    translator = openstudio.energyplus.ForwardTranslator()
    idf = translator.translateModel(model)
    _strip_non_hvac_objects(idf)
    idf.save(openstudio.path(str(idf_path)), True)



if __name__ == "__main__":
    main()
