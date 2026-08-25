/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../LayeredConstruction/ConstructionWithInternalSource.hpp"
#include "../ModelObject/ModelObject.hpp"
#include "../ModelObject/ZoneHVACLowTempRadiantVarFlowDesign.hpp"
#include "../ModelObject/ZoneHVACLowTemperatureRadiantSurfaceGroup.hpp"
#include "../PlanarSurface/Surface.hpp"
#include "../PlanarSurfaceGroup/Space.hpp"
#include "../StraightComponent/CoilCoolingLowTempRadiantVarFlow.hpp"
#include "../StraightComponent/CoilCoolingLowTempRadiantVarFlow_Impl.hpp"
#include "../StraightComponent/CoilHeatingLowTempRadiantVarFlow.hpp"
#include "../StraightComponent/CoilHeatingLowTempRadiantVarFlow_Impl.hpp"
#include "../StraightComponent/Node.hpp"
#include "../ZoneHVACComponent/ZoneHVACLowTempRadiantVarFlow.hpp"

#include <utilities/idd/BuildingSurface_Detailed_FieldEnums.hxx>
#include <utilities/idd/ConstructionProperty_InternalHeatSource_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_LowTemperatureRadiant_VariableFlow_FieldEnums.hxx>
#include <utilities/idf/IdfExtensibleGroup.hpp>
#include <utilities/geometry/Point3d.hpp>

#include <array>
#include <algorithm>

using namespace openstudio;
using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneHVACLowTempRadiantVarFlow_DefaultConstructor) {
  Model model;
  ZoneHVACLowTempRadiantVarFlow radiant(model);

  EXPECT_FALSE(radiant.heatingCoil());
  EXPECT_FALSE(radiant.coolingCoil());
  EXPECT_TRUE(radiant.children().empty());
  EXPECT_TRUE(radiant.designObject());
  EXPECT_FALSE(radiant.surfaceGroup());
  EXPECT_FALSE(radiant.hydronicTubingLength());
  EXPECT_FALSE(radiant.autosizedHydronicTubingLength());
  EXPECT_EQ(0u, radiant.inletPort());
  EXPECT_EQ(0u, radiant.outletPort());
}

TEST_F(EPModelFixture, ZoneHVACLowTempRadiantVarFlow_ConvenienceConstructorAndParentCoilSetters) {
  Model model;
  ScheduleConstant availability(model);
  ScheduleConstant heatingControl(model);
  ScheduleConstant coolingControl(model);
  ASSERT_TRUE(availability.setValue(1.0));
  ASSERT_TRUE(heatingControl.setValue(22.0));
  ASSERT_TRUE(coolingControl.setValue(26.0));

  ZoneHVACLowTempRadiantVarFlow source(model);
  ASSERT_TRUE(source.setMaximumHotWaterFlow(0.004));
  ASSERT_TRUE(source.setMaximumColdWaterFlow(0.003));
  ASSERT_TRUE(source.setHeatingDesignCapacity(1200.0));
  ASSERT_TRUE(source.setCoolingDesignCapacity(900.0));

  auto sourceHeating = source.heatingCoil();
  auto sourceCooling = source.coolingCoil();
  ASSERT_TRUE(sourceHeating);
  ASSERT_TRUE(sourceCooling);
  ASSERT_TRUE(sourceHeating->optionalCast<CoilHeatingLowTempRadiantVarFlow>());
  ASSERT_TRUE(sourceCooling->optionalCast<CoilCoolingLowTempRadiantVarFlow>());

  auto sourceHeatingCoil = sourceHeating->cast<CoilHeatingLowTempRadiantVarFlow>();
  auto sourceCoolingCoil = sourceCooling->cast<CoilCoolingLowTempRadiantVarFlow>();

  ASSERT_TRUE(sourceHeatingCoil.setHeatingControlTemperatureSchedule(heatingControl));
  ASSERT_TRUE(sourceHeatingCoil.setHeatingDesignCapacityMethod("CapacityPerFloorArea"));
  ASSERT_TRUE(sourceHeatingCoil.setHeatingDesignCapacityPerFloorArea(42.5));
  ASSERT_TRUE(sourceHeatingCoil.setFractionofAutosizedHeatingDesignCapacity(1.1));
  ASSERT_TRUE(sourceHeatingCoil.setHeatingControlThrottlingRange(0.8));

  ASSERT_TRUE(sourceCoolingCoil.setCoolingControlTemperatureSchedule(coolingControl));
  ASSERT_TRUE(sourceCoolingCoil.setCoolingDesignCapacityMethod("CapacityPerFloorArea"));
  ASSERT_TRUE(sourceCoolingCoil.setCoolingDesignCapacityPerFloorArea(27.0));
  ASSERT_TRUE(sourceCoolingCoil.setFractionofAutosizedCoolingDesignCapacity(0.7));
  ASSERT_TRUE(sourceCoolingCoil.setCoolingControlThrottlingRange(0.9));
  ASSERT_TRUE(sourceCoolingCoil.setCondensationControlType("VariableOff"));
  ASSERT_TRUE(sourceCoolingCoil.setCondensationControlDewpointOffset(1.5));

  ZoneHVACLowTempRadiantVarFlow radiant(model, availability, *sourceHeating, *sourceCooling);
  ASSERT_TRUE(radiant.availabilitySchedule());
  EXPECT_EQ(availability.handle(), radiant.availabilitySchedule()->handle());
  ASSERT_TRUE(radiant.heatingCoil());
  ASSERT_TRUE(radiant.coolingCoil());
  EXPECT_DOUBLE_EQ(0.004, radiant.maximumHotWaterFlow().get());
  EXPECT_DOUBLE_EQ(0.003, radiant.maximumColdWaterFlow().get());
  EXPECT_DOUBLE_EQ(1200.0, radiant.heatingDesignCapacity().get());
  EXPECT_DOUBLE_EQ(900.0, radiant.coolingDesignCapacity().get());

  auto heating = radiant.heatingCoil()->cast<CoilHeatingLowTempRadiantVarFlow>();
  auto cooling = radiant.coolingCoil()->cast<CoilCoolingLowTempRadiantVarFlow>();
  ASSERT_TRUE(heating.heatingControlTemperatureSchedule());
  EXPECT_EQ(heatingControl.handle(), heating.heatingControlTemperatureSchedule()->handle());
  ASSERT_TRUE(cooling.coolingControlTemperatureSchedule());
  EXPECT_EQ(coolingControl.handle(), cooling.coolingControlTemperatureSchedule()->handle());
  EXPECT_EQ("CapacityPerFloorArea", heating.heatingDesignCapacityMethod());
  EXPECT_EQ("CapacityPerFloorArea", cooling.coolingDesignCapacityMethod());
  EXPECT_DOUBLE_EQ(42.5, heating.heatingDesignCapacityPerFloorArea());
  EXPECT_DOUBLE_EQ(27.0, cooling.coolingDesignCapacityPerFloorArea());
  EXPECT_DOUBLE_EQ(1.1, heating.fractionofAutosizedHeatingDesignCapacity());
  EXPECT_DOUBLE_EQ(0.7, cooling.fractionofAutosizedCoolingDesignCapacity());
  EXPECT_DOUBLE_EQ(0.8, heating.heatingControlThrottlingRange());
  EXPECT_DOUBLE_EQ(0.9, cooling.coolingControlThrottlingRange());
  EXPECT_EQ("VariableOff", cooling.condensationControlType());
  EXPECT_DOUBLE_EQ(1.5, cooling.condensationControlDewpointOffset());
}

TEST_F(EPModelFixture, ZoneHVACLowTempRadiantVarFlow_TransientCompanionCoils_ResolveParentWaterNodesAndReset) {
  Model model;
  ZoneHVACLowTempRadiantVarFlow radiant(model);

  ASSERT_TRUE(radiant.setMaximumHotWaterFlow(0.004));
  ASSERT_TRUE(radiant.setMaximumColdWaterFlow(0.003));
  ASSERT_TRUE(radiant.heatingCoil());
  ASSERT_TRUE(radiant.coolingCoil());

  Node heatingInlet = model.getOrCreateTransientByName<Node>("Radiant Var Heating Inlet");
  Node heatingOutlet = model.getOrCreateTransientByName<Node>("Radiant Var Heating Outlet");
  Node coolingInlet = model.getOrCreateTransientByName<Node>("Radiant Var Cooling Inlet");
  Node coolingOutlet = model.getOrCreateTransientByName<Node>("Radiant Var Cooling Outlet");

  ASSERT_TRUE(radiant.setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::HeatingWaterInletNodeName, heatingInlet.handle()));
  ASSERT_TRUE(radiant.setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::HeatingWaterOutletNodeName, heatingOutlet.handle()));
  ASSERT_TRUE(radiant.setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::CoolingWaterInletNodeName, coolingInlet.handle()));
  ASSERT_TRUE(radiant.setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::CoolingWaterOutletNodeName, coolingOutlet.handle()));

  auto heating = radiant.heatingCoil()->cast<CoilHeatingLowTempRadiantVarFlow>();
  auto cooling = radiant.coolingCoil()->cast<CoilCoolingLowTempRadiantVarFlow>();

  ASSERT_TRUE(heating.inletModelObject());
  EXPECT_EQ(heatingInlet.handle(), heating.inletModelObject()->handle());
  ASSERT_TRUE(heating.outletModelObject());
  EXPECT_EQ(heatingOutlet.handle(), heating.outletModelObject()->handle());
  ASSERT_TRUE(cooling.inletModelObject());
  EXPECT_EQ(coolingInlet.handle(), cooling.inletModelObject()->handle());
  ASSERT_TRUE(cooling.outletModelObject());
  EXPECT_EQ(coolingOutlet.handle(), cooling.outletModelObject()->handle());

  EXPECT_FALSE(heating.addToNode(heatingInlet));
  EXPECT_FALSE(cooling.addToNode(coolingInlet));

  radiant.resetHeatingCoil();
  radiant.resetCoolingCoil();
  EXPECT_FALSE(radiant.heatingCoil());
  EXPECT_FALSE(radiant.coolingCoil());
  EXPECT_TRUE(radiant.children().empty());
}

TEST_F(EPModelFixture, ZoneHVACLowTempRadiantVarFlow_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneHVACLowTempRadiantVarFlow radiant(model);

  EXPECT_TRUE(radiant.setHydronicTubingLength(200.5));
  ASSERT_TRUE(radiant.hydronicTubingLength());
  EXPECT_DOUBLE_EQ(200.5, radiant.hydronicTubingLength().get());
  radiant.autosizeHydronicTubingLength();
  EXPECT_TRUE(radiant.isHydronicTubingLengthAutosized());

  EXPECT_TRUE(radiant.setNumberofCircuits("CalculateFromCircuitLength"));
  EXPECT_EQ("CalculateFromCircuitLength", radiant.numberofCircuits());
  radiant.resetNumberofCircuits();
  EXPECT_TRUE(radiant.isNumberofCircuitsDefaulted());

  EXPECT_TRUE(radiant.setCircuitLength(150.0));
  EXPECT_DOUBLE_EQ(150.0, radiant.circuitLength());
  radiant.resetCircuitLength();
  EXPECT_TRUE(radiant.isCircuitLengthDefaulted());

  EXPECT_TRUE(radiant.setFluidtoRadiantSurfaceHeatTransferModel("ISOStandard"));
  EXPECT_EQ("ISOStandard", radiant.fluidtoRadiantSurfaceHeatTransferModel());
  radiant.resetFluidtoRadiantSurfaceHeatTransferModel();
  EXPECT_TRUE(radiant.isFluidtoRadiantSurfaceHeatTransferModelDefaulted());

  EXPECT_TRUE(radiant.setHydronicTubingInsideDiameter(0.02));
  EXPECT_DOUBLE_EQ(0.02, radiant.hydronicTubingInsideDiameter());
  radiant.resetHydronicTubingInsideDiameter();
  EXPECT_TRUE(radiant.isHydronicTubingInsideDiameterDefaulted());

  EXPECT_TRUE(radiant.setHydronicTubingOutsideDiameter(0.03));
  EXPECT_DOUBLE_EQ(0.03, radiant.hydronicTubingOutsideDiameter());
  radiant.resetHydronicTubingOutsideDiameter();
  EXPECT_TRUE(radiant.isHydronicTubingOutsideDiameterDefaulted());

  EXPECT_TRUE(radiant.setHydronicTubingConductivity(0.4));
  EXPECT_DOUBLE_EQ(0.4, radiant.hydronicTubingConductivity());
  radiant.resetHydronicTubingConductivity();
  EXPECT_TRUE(radiant.isHydronicTubingConductivityDefaulted());

  EXPECT_TRUE(radiant.setTemperatureControlType("SurfaceFaceTemperature"));
  EXPECT_EQ("SurfaceFaceTemperature", radiant.temperatureControlType());
  radiant.resetTemperatureControlType();
  EXPECT_TRUE(radiant.isTemperatureControlTypeDefaulted());

  EXPECT_TRUE(radiant.setSetpointControlType("ZeroFlowPower"));
  EXPECT_EQ("ZeroFlowPower", radiant.setpointControlType());
  radiant.resetSetpointControlType();
  EXPECT_TRUE(radiant.isSetpointControlTypeDefaulted());

  EXPECT_TRUE(radiant.setHeatingDesignCapacityMethod("CapacityPerFloorArea"));
  EXPECT_EQ("CapacityPerFloorArea", radiant.heatingDesignCapacityMethod());
  radiant.resetHeatingDesignCapacityMethod();
  EXPECT_TRUE(radiant.isHeatingDesignCapacityMethodDefaulted());

  EXPECT_FALSE(radiant.heatingDesignCapacityPerFloorArea());
  EXPECT_TRUE(radiant.setHeatingDesignCapacityPerFloorArea(42.5));
  ASSERT_TRUE(radiant.heatingDesignCapacityPerFloorArea());
  EXPECT_DOUBLE_EQ(42.5, radiant.heatingDesignCapacityPerFloorArea().get());
  radiant.resetHeatingDesignCapacityPerFloorArea();
  EXPECT_FALSE(radiant.heatingDesignCapacityPerFloorArea());

  EXPECT_DOUBLE_EQ(1.0, radiant.fractionofAutosizedHeatingDesignCapacity());
  EXPECT_TRUE(radiant.setFractionofAutosizedHeatingDesignCapacity(1.2));
  EXPECT_DOUBLE_EQ(1.2, radiant.fractionofAutosizedHeatingDesignCapacity());
  radiant.resetFractionofAutosizedHeatingDesignCapacity();
  EXPECT_DOUBLE_EQ(1.0, radiant.fractionofAutosizedHeatingDesignCapacity());

  EXPECT_DOUBLE_EQ(0.5, radiant.heatingControlThrottlingRange());
  EXPECT_TRUE(radiant.setHeatingControlThrottlingRange(0.8));
  EXPECT_DOUBLE_EQ(0.8, radiant.heatingControlThrottlingRange());
  radiant.resetHeatingControlThrottlingRange();
  EXPECT_DOUBLE_EQ(0.5, radiant.heatingControlThrottlingRange());

  EXPECT_TRUE(radiant.setCoolingDesignCapacityMethod("FractionOfAutosizedCoolingCapacity"));
  EXPECT_EQ("FractionOfAutosizedCoolingCapacity", radiant.coolingDesignCapacityMethod());
  radiant.resetCoolingDesignCapacityMethod();
  EXPECT_TRUE(radiant.isCoolingDesignCapacityMethodDefaulted());

  EXPECT_FALSE(radiant.coolingDesignCapacityPerFloorArea());
  EXPECT_TRUE(radiant.setCoolingDesignCapacityPerFloorArea(27.0));
  ASSERT_TRUE(radiant.coolingDesignCapacityPerFloorArea());
  EXPECT_DOUBLE_EQ(27.0, radiant.coolingDesignCapacityPerFloorArea().get());
  radiant.resetCoolingDesignCapacityPerFloorArea();
  EXPECT_FALSE(radiant.coolingDesignCapacityPerFloorArea());

  EXPECT_FALSE(radiant.fractionofAutosizedCoolingDesignCapacity());
  EXPECT_TRUE(radiant.setFractionofAutosizedCoolingDesignCapacity(0.8));
  ASSERT_TRUE(radiant.fractionofAutosizedCoolingDesignCapacity());
  EXPECT_DOUBLE_EQ(0.8, radiant.fractionofAutosizedCoolingDesignCapacity().get());
  radiant.resetFractionofAutosizedCoolingDesignCapacity();
  EXPECT_FALSE(radiant.fractionofAutosizedCoolingDesignCapacity());

  EXPECT_DOUBLE_EQ(0.5, radiant.coolingControlThrottlingRange());
  EXPECT_TRUE(radiant.setCoolingControlThrottlingRange(0.9));
  EXPECT_DOUBLE_EQ(0.9, radiant.coolingControlThrottlingRange());
  radiant.resetCoolingControlThrottlingRange();
  EXPECT_DOUBLE_EQ(0.5, radiant.coolingControlThrottlingRange());

  EXPECT_TRUE(radiant.setCondensationControlType("VariableOff"));
  EXPECT_EQ("VariableOff", radiant.condensationControlType());
  radiant.resetCondensationControlType();
  EXPECT_TRUE(radiant.isCondensationControlTypeDefaulted());

  EXPECT_DOUBLE_EQ(1.0, radiant.condensationControlDewpointOffset());
  EXPECT_TRUE(radiant.setCondensationControlDewpointOffset(2.5));
  EXPECT_DOUBLE_EQ(2.5, radiant.condensationControlDewpointOffset());
  radiant.resetCondensationControlDewpointOffset();
  EXPECT_DOUBLE_EQ(1.0, radiant.condensationControlDewpointOffset());
}

TEST_F(EPModelFixture, ZoneHVACLowTempRadiantVarFlow_RadiantSurfaceType_RewritesPersistedSurfaceGroup) {
  Model model;
  ThermalZone zone(model);
  Space space(model);
  ASSERT_TRUE(space.setThermalZone(zone));

  // This still uses low-level envelope setup because the surface and surface
  // group side of epmodel is not fleshed out yet. The production code is using
  // the same persisted fields today, so this is an honest test of the current
  // storage model, but it should be revisited once richer envelope wrappers
  // exist.
  ModelObject construction = ModelObject::create(IddObjectType::Construction, model);
  ConstructionWithInternalSource radiantConstruction(model);
  ASSERT_TRUE(radiantConstruction.setPointer(openstudio::ConstructionProperty_InternalHeatSourceFields::ConstructionName, construction.handle()));

  auto makeSurface = [&](const std::string& name, const std::string& surfaceType, const std::vector<Point3d>& vertices) -> Surface {
    Surface surface(vertices, model);
    EXPECT_TRUE(surface.setName(name));
    EXPECT_TRUE(surface.setSurfaceType(surfaceType));
    EXPECT_TRUE(surface.setPointer(openstudio::BuildingSurface_DetailedFields::ConstructionName, construction.handle()));
    EXPECT_TRUE(surface.setPointer(openstudio::BuildingSurface_DetailedFields::SpaceName, space.handle()));

    return surface;
  };

  auto floor = makeSurface("Radiant Var Floor", "Floor", {{0.0, 0.0, 0.0}, {4.0, 0.0, 0.0}, {4.0, 3.0, 0.0}, {0.0, 3.0, 0.0}});
  auto ceiling = makeSurface("Radiant Var Ceiling", "Roof", {{0.0, 0.0, 3.0}, {4.0, 0.0, 3.0}, {4.0, 3.0, 3.0}, {0.0, 3.0, 3.0}});
  auto wall = makeSurface("Radiant Var Wall", "Wall", {{0.0, 0.0, 0.0}, {4.0, 0.0, 0.0}, {4.0, 0.0, 3.0}, {0.0, 0.0, 3.0}});

  auto sortedHandles = [](const std::vector<Surface>& surfaces) {
    std::vector<Handle> result;
    result.reserve(surfaces.size());
    for (const auto& surface : surfaces) {
      result.push_back(surface.handle());
    }
    std::sort(result.begin(), result.end());
    return result;
  };

  auto sortedExpected = [](std::vector<Handle> handles) {
    std::sort(handles.begin(), handles.end());
    return handles;
  };

  ZoneHVACLowTempRadiantVarFlow radiant(model);
  ASSERT_TRUE(radiant.addToThermalZone(zone));

  EXPECT_TRUE(radiant.setRadiantSurfaceType("Floors"));
  ASSERT_TRUE(radiant.radiantSurfaceType());
  EXPECT_EQ("Floors", *radiant.radiantSurfaceType());
  ASSERT_EQ(1u, radiant.surfaces().size());
  EXPECT_EQ(floor.handle(), radiant.surfaces().front().handle());

  EXPECT_TRUE(radiant.setRadiantSurfaceType("CeilingsandFloors"));
  ASSERT_TRUE(radiant.radiantSurfaceType());
  EXPECT_EQ("CeilingsandFloors", *radiant.radiantSurfaceType());
  ASSERT_EQ(2u, radiant.surfaces().size());
  EXPECT_EQ(sortedExpected({ceiling.handle(), floor.handle()}), sortedHandles(radiant.surfaces()));

  EXPECT_TRUE(radiant.setRadiantSurfaceType("AllSurfaces"));
  ASSERT_TRUE(radiant.radiantSurfaceType());
  EXPECT_EQ("AllSurfaces", *radiant.radiantSurfaceType());
  ASSERT_EQ(3u, radiant.surfaces().size());
  EXPECT_EQ(sortedExpected({ceiling.handle(), floor.handle(), wall.handle()}), sortedHandles(radiant.surfaces()));

  radiant.resetRadiantSurfaceType();
  ASSERT_TRUE(radiant.radiantSurfaceType());
  EXPECT_EQ("Ceilings", *radiant.radiantSurfaceType());
  ASSERT_EQ(1u, radiant.surfaces().size());
  EXPECT_EQ(ceiling.handle(), radiant.surfaces().front().handle());
}

TEST_F(EPModelFixture, ZoneHVACLowTempRadiantVarFlow_ZoneAttachment) {
  Model model;
  ThermalZone zone(model);
  ZoneHVACLowTempRadiantVarFlow radiant(model);

  EXPECT_TRUE(radiant.addToThermalZone(zone));
  ASSERT_TRUE(radiant.thermalZone());
  EXPECT_EQ(zone, radiant.thermalZone().get());
  EXPECT_FALSE(radiant.inletNode());
  EXPECT_FALSE(radiant.outletNode());

  radiant.removeFromThermalZone();
  EXPECT_FALSE(radiant.thermalZone());
}
