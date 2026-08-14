########################################################################################################################
#  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
#  See also https://openstudio.net/license
########################################################################################################################

from pathlib import Path

import openstudio


def test_optional_not_initialized():
    d = openstudio.OptionalDouble()
    assert not d.is_initialized()
    assert d.empty()
    assert not bool(d)
    assert isinstance(d.value_or(20.0), float)
    assert d.value_or(20.0) == 20.0
    assert isinstance(d.value_or(20), float)
    assert d.value_or(20) == 20.0


def test_optionalinitialized():
    d = openstudio.OptionalDouble(10.0)
    assert d.is_initialized()
    assert not d.empty()
    assert bool(d)
    assert isinstance(d.value_or(10.0), float)
    assert d.value_or(10.0) == 10.0
    assert isinstance(d.value_or(10), float)
    assert d.value_or(10) == 10.0


def test_path():
    """Assert you can load a model with a str or a pathlib.Path without throwing."""
    assert openstudio.model.Model.load("wrong.osm").empty()
    assert openstudio.model.Model.load(Path("wrong.osm")).empty()
    # And we still support toPath
    assert openstudio.model.Model.load(openstudio.toPath("wrong.osm")).empty()


def test_json():
    """We can return jsoncpp objects to a native python dict."""
    idfFile = openstudio.IdfFile(openstudio.IddFileType("EnergyPlus"))
    building = openstudio.IdfObject(openstudio.IddObjectType("Building"))
    building.setName("Building 1")
    building.setDouble(1, 0.0)  # North Axis
    idfFile.addObject(building)
    d = openstudio.epjson.toJSON(idfFile)
    assert isinstance(d, dict)
    assert "Version" in d
    assert "Building" in d
    assert d["Building"]["Building 1"]["north_axis"] == 0


def test_epmodel_loop_returns_wrapped_nodes():
    model = openstudio.epmodel.Model()
    air_loop = openstudio.epmodel.AirLoopHVAC(model, True)

    supply_outlet_nodes = air_loop.supplyOutletNodes()

    assert isinstance(supply_outlet_nodes, tuple)
    assert len(supply_outlet_nodes) == 2
    assert all(isinstance(node, openstudio.epmodel.Node) for node in supply_outlet_nodes)


def test_epmodel_doas_accepts_and_returns_wrapped_air_loops():
    model = openstudio.epmodel.Model()
    dedicated_oa = openstudio.epmodel.AirLoopHVACOutdoorAirSystem(model)
    doas = openstudio.epmodel.AirLoopHVACDedicatedOutdoorAirSystem(dedicated_oa)
    served_loop = openstudio.epmodel.AirLoopHVAC(model)
    served_oa = openstudio.epmodel.AirLoopHVACOutdoorAirSystem(model)

    assert served_oa.addToNode(served_loop.supplyOutletNode())
    assert doas.addAirLoop(served_loop)

    air_loops = doas.airLoops()
    assert len(air_loops) == 1
    assert isinstance(air_loops[0], openstudio.epmodel.AirLoopHVAC)
    assert air_loops[0].handle() == served_loop.handle()


def test_epmodel_sizing_plant_retarget_swaps_companions():
    model = openstudio.epmodel.Model()
    source_loop = openstudio.epmodel.PlantLoop(model)
    target_loop = openstudio.epmodel.PlantLoop(model)
    source_sizing = source_loop.sizingPlant()
    target_sizing = target_loop.sizingPlant()

    assert source_sizing.setPlantLoop(target_loop)
    assert source_sizing.plantLoop().handle() == target_loop.handle()
    assert target_sizing.plantLoop().handle() == source_loop.handle()
    assert target_loop.sizingPlant().handle() == source_sizing.handle()
    assert source_loop.sizingPlant().handle() == target_sizing.handle()
