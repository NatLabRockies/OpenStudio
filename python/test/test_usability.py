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
