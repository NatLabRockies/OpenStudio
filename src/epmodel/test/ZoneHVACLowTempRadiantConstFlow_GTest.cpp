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
#include "../PlanarSurface/Surface.hpp"
#include "../PlanarSurfaceGroup/Space.hpp"
#include "../StraightComponent/Node.hpp"
#include "../ZoneHVACComponent/ZoneHVACLowTempRadiantConstFlow.hpp"
#include <utilities/idd/BuildingSurface_Detailed_FieldEnums.hxx>
#include <utilities/idd/ConstructionProperty_InternalHeatSource_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_LowTemperatureRadiant_ConstantFlow_FieldEnums.hxx>
#include <utilities/idf/IdfExtensibleGroup.hpp>

#include <array>
#include <algorithm>

using namespace openstudio;
using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneHVACLowTempRadiantConstFlow_DefaultConstructor) {
  Model model;
  ZoneHVACLowTempRadiantConstFlow radiant(model);

  EXPECT_FALSE(radiant.hydronicTubingLength());
  EXPECT_FALSE(radiant.ratedFlowRate());
  EXPECT_EQ(0u, radiant.inletPort());
  EXPECT_EQ(0u, radiant.outletPort());
  ASSERT_EQ(2u, radiant.children().size());
  EXPECT_FALSE(radiant.autosizedHydronicTubingLength());
  EXPECT_FALSE(radiant.autosizedRatedFlowRate());
}

TEST_F(EPModelFixture, ZoneHVACLowTempRadiantConstFlow_ConvenienceConstructorsAndParentCoilSetters) {
  Model model;
  ScheduleConstant availability(model);
  ASSERT_TRUE(availability.setValue(1.0));

  ZoneHVACLowTempRadiantConstFlow source(model);
  auto sourceHeating = source.heatingCoil();
  auto sourceCooling = source.coolingCoil();

  ScheduleConstant heatingHighWater(model);
  ScheduleConstant heatingLowWater(model);
  ScheduleConstant heatingHighControl(model);
  ScheduleConstant heatingLowControl(model);
  ScheduleConstant coolingHighWater(model);
  ScheduleConstant coolingLowWater(model);
  ScheduleConstant coolingHighControl(model);
  ScheduleConstant coolingLowControl(model);

  ASSERT_TRUE(heatingHighWater.setValue(60.0));
  ASSERT_TRUE(heatingLowWater.setValue(35.0));
  ASSERT_TRUE(heatingHighControl.setValue(23.0));
  ASSERT_TRUE(heatingLowControl.setValue(20.0));
  ASSERT_TRUE(coolingHighWater.setValue(18.0));
  ASSERT_TRUE(coolingLowWater.setValue(12.0));
  ASSERT_TRUE(coolingHighControl.setValue(26.0));
  ASSERT_TRUE(coolingLowControl.setValue(22.0));

  ASSERT_TRUE(sourceHeating.setHeatingHighWaterTemperatureSchedule(heatingHighWater));
  ASSERT_TRUE(sourceHeating.setHeatingLowWaterTemperatureSchedule(heatingLowWater));
  ASSERT_TRUE(sourceHeating.setHeatingHighControlTemperatureSchedule(heatingHighControl));
  ASSERT_TRUE(sourceHeating.setHeatingLowControlTemperatureSchedule(heatingLowControl));

  ASSERT_TRUE(sourceCooling.setCoolingHighWaterTemperatureSchedule(coolingHighWater));
  ASSERT_TRUE(sourceCooling.setCoolingLowWaterTemperatureSchedule(coolingLowWater));
  ASSERT_TRUE(sourceCooling.setCoolingHighControlTemperatureSchedule(coolingHighControl));
  ASSERT_TRUE(sourceCooling.setCoolingLowControlTemperatureSchedule(coolingLowControl));
  ASSERT_TRUE(sourceCooling.setCondensationControlType("VariableOff"));
  ASSERT_TRUE(sourceCooling.setCondensationControlDewpointOffset(1.5));

  ZoneHVACLowTempRadiantConstFlow autosized(model, availability, sourceHeating, sourceCooling);
  ASSERT_TRUE(autosized.availabilitySchedule());
  EXPECT_EQ(availability.handle(), autosized.availabilitySchedule()->handle());
  EXPECT_TRUE(autosized.isHydronicTubingLengthAutosized());
  EXPECT_FALSE(autosized.autosizedHydronicTubingLength());

  ASSERT_TRUE(autosized.heatingCoil().heatingHighWaterTemperatureSchedule());
  EXPECT_EQ(heatingHighWater.handle(), autosized.heatingCoil().heatingHighWaterTemperatureSchedule()->handle());
  ASSERT_TRUE(autosized.coolingCoil().coolingHighWaterTemperatureSchedule());
  EXPECT_EQ(coolingHighWater.handle(), autosized.coolingCoil().coolingHighWaterTemperatureSchedule()->handle());
  EXPECT_EQ("VariableOff", autosized.coolingCoil().condensationControlType());
  EXPECT_DOUBLE_EQ(1.5, autosized.coolingCoil().condensationControlDewpointOffset());

  ZoneHVACLowTempRadiantConstFlow explicitLength(model, availability, sourceHeating, sourceCooling, 125.0);
  ASSERT_TRUE(explicitLength.hydronicTubingLength());
  EXPECT_DOUBLE_EQ(125.0, explicitLength.hydronicTubingLength().get());

  ZoneHVACLowTempRadiantConstFlow copied(model);
  EXPECT_TRUE(copied.setHeatingCoil(sourceHeating));
  EXPECT_TRUE(copied.setCoolingCoil(sourceCooling));

  ASSERT_TRUE(copied.heatingCoil().heatingLowControlTemperatureSchedule());
  EXPECT_EQ(heatingLowControl.handle(), copied.heatingCoil().heatingLowControlTemperatureSchedule()->handle());
  ASSERT_TRUE(copied.coolingCoil().coolingLowControlTemperatureSchedule());
  EXPECT_EQ(coolingLowControl.handle(), copied.coolingCoil().coolingLowControlTemperatureSchedule()->handle());
  EXPECT_EQ("VariableOff", copied.coolingCoil().condensationControlType());
  EXPECT_DOUBLE_EQ(1.5, copied.coolingCoil().condensationControlDewpointOffset());
}

TEST_F(EPModelFixture, ZoneHVACLowTempRadiantConstFlow_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneHVACLowTempRadiantConstFlow radiant(model);

  EXPECT_TRUE(radiant.setHydronicTubingLength(200.0));
  ASSERT_TRUE(radiant.hydronicTubingLength());
  EXPECT_DOUBLE_EQ(200.0, radiant.hydronicTubingLength().get());
  radiant.autosizeHydronicTubingLength();
  EXPECT_TRUE(radiant.isHydronicTubingLengthAutosized());
  EXPECT_FALSE(radiant.autosizedHydronicTubingLength());

  EXPECT_TRUE(radiant.setRatedFlowRate(0.25));
  ASSERT_TRUE(radiant.ratedFlowRate());
  EXPECT_DOUBLE_EQ(0.25, radiant.ratedFlowRate().get());
  radiant.autosizeRatedFlowRate();
  EXPECT_TRUE(radiant.isRatedFlowRateAutosized());
  EXPECT_FALSE(radiant.autosizedRatedFlowRate());

  EXPECT_TRUE(radiant.setRatedPumpHead(150000));
  EXPECT_DOUBLE_EQ(150000, radiant.ratedPumpHead());
  radiant.resetRatedPumpHead();
  EXPECT_TRUE(radiant.isRatedPumpHeadDefaulted());

  EXPECT_TRUE(radiant.setRatedPowerConsumption(1200));
  ASSERT_TRUE(radiant.ratedPowerConsumption());
  EXPECT_DOUBLE_EQ(1200, radiant.ratedPowerConsumption().get());
  radiant.resetRatedPowerConsumption();
  EXPECT_FALSE(radiant.ratedPowerConsumption());

  EXPECT_TRUE(radiant.setFluidtoRadiantSurfaceHeatTransferModel("ISOStandard"));
  EXPECT_EQ("ISOStandard", radiant.fluidtoRadiantSurfaceHeatTransferModel());
  radiant.resetFluidtoRadiantSurfaceHeatTransferModel();
  EXPECT_TRUE(radiant.isFluidtoRadiantSurfaceHeatTransferModelDefaulted());

  EXPECT_TRUE(radiant.setHydronicTubingInsideDiameter(0.02));
  EXPECT_DOUBLE_EQ(0.02, radiant.hydronicTubingInsideDiameter());
  radiant.resetHydronicTubingInsideDiameter();
  EXPECT_TRUE(radiant.isHydronicTubingInsideDiameterDefaulted());

  EXPECT_TRUE(radiant.setHydronicTubingOutsideDiameter(0.024));
  EXPECT_DOUBLE_EQ(0.024, radiant.hydronicTubingOutsideDiameter());
  radiant.resetHydronicTubingOutsideDiameter();
  EXPECT_TRUE(radiant.isHydronicTubingOutsideDiameterDefaulted());

  EXPECT_TRUE(radiant.setHydronicTubingConductivity(0.45));
  EXPECT_DOUBLE_EQ(0.45, radiant.hydronicTubingConductivity());
  radiant.resetHydronicTubingConductivity();
  EXPECT_TRUE(radiant.isHydronicTubingConductivityDefaulted());

  EXPECT_TRUE(radiant.setTemperatureControlType("SurfaceFaceTemperature"));
  EXPECT_EQ("SurfaceFaceTemperature", radiant.temperatureControlType());
  radiant.resetTemperatureControlType();
  EXPECT_TRUE(radiant.isTemperatureControlTypeDefaulted());

  EXPECT_TRUE(radiant.setRunningMeanOutdoorDryBulbTemperatureWeightingFactor(0.5));
  EXPECT_DOUBLE_EQ(0.5, radiant.runningMeanOutdoorDryBulbTemperatureWeightingFactor());
  radiant.resetRunningMeanOutdoorDryBulbTemperatureWeightingFactor();
  EXPECT_TRUE(radiant.isRunningMeanOutdoorDryBulbTemperatureWeightingFactorDefaulted());

  EXPECT_TRUE(radiant.setMotorEfficiency(0.95));
  EXPECT_DOUBLE_EQ(0.95, radiant.motorEfficiency());
  radiant.resetMotorEfficiency();
  EXPECT_TRUE(radiant.isMotorEfficiencyDefaulted());

  EXPECT_TRUE(radiant.setFractionofMotorInefficienciestoFluidStream(0.1));
  EXPECT_DOUBLE_EQ(0.1, radiant.fractionofMotorInefficienciestoFluidStream());
  radiant.resetFractionofMotorInefficienciestoFluidStream();
  EXPECT_TRUE(radiant.isFractionofMotorInefficienciestoFluidStreamDefaulted());

  EXPECT_TRUE(radiant.setNumberofCircuits("CalculateFromCircuitLength"));
  EXPECT_EQ("CalculateFromCircuitLength", radiant.numberofCircuits());
  radiant.resetNumberofCircuits();
  EXPECT_TRUE(radiant.isNumberofCircuitsDefaulted());

  EXPECT_TRUE(radiant.setCircuitLength(200.0));
  EXPECT_DOUBLE_EQ(200.0, radiant.circuitLength());
  radiant.resetCircuitLength();
  EXPECT_TRUE(radiant.isCircuitLengthDefaulted());
}

TEST_F(EPModelFixture, ZoneHVACLowTempRadiantConstFlow_ZoneAttachment) {
  Model model;
  ThermalZone zone(model);
  ZoneHVACLowTempRadiantConstFlow radiant(model);

  EXPECT_TRUE(radiant.addToThermalZone(zone));
  ASSERT_TRUE(radiant.thermalZone());
  EXPECT_EQ(zone, radiant.thermalZone().get());
  EXPECT_FALSE(radiant.inletNode());
  EXPECT_FALSE(radiant.outletNode());

  radiant.removeFromThermalZone();
  EXPECT_FALSE(radiant.thermalZone());
}

TEST_F(EPModelFixture, ZoneHVACLowTempRadiantConstFlow_TransientCompanionCoils_WriteThroughParentStorage) {
  Model model;
  ZoneHVACLowTempRadiantConstFlow radiant(model);

  ScheduleConstant availability(model);
  ScheduleConstant pump(model);
  ScheduleConstant changeover(model);
  ScheduleConstant heatingHighWater(model);
  ScheduleConstant heatingLowWater(model);
  ScheduleConstant heatingHighControl(model);
  ScheduleConstant heatingLowControl(model);
  ScheduleConstant coolingHighWater(model);
  ScheduleConstant coolingLowWater(model);
  ScheduleConstant coolingHighControl(model);
  ScheduleConstant coolingLowControl(model);

  ASSERT_TRUE(availability.setValue(1.0));
  ASSERT_TRUE(pump.setValue(0.5));
  ASSERT_TRUE(changeover.setValue(2.0));
  ASSERT_TRUE(heatingHighWater.setValue(60.0));
  ASSERT_TRUE(heatingLowWater.setValue(35.0));
  ASSERT_TRUE(heatingHighControl.setValue(23.0));
  ASSERT_TRUE(heatingLowControl.setValue(20.0));
  ASSERT_TRUE(coolingHighWater.setValue(18.0));
  ASSERT_TRUE(coolingLowWater.setValue(12.0));
  ASSERT_TRUE(coolingHighControl.setValue(26.0));
  ASSERT_TRUE(coolingLowControl.setValue(22.0));

  EXPECT_TRUE(radiant.setAvailabilitySchedule(availability));
  EXPECT_TRUE(radiant.setPumpFlowRateSchedule(pump));
  EXPECT_TRUE(radiant.setChangeoverDelayTimePeriodSchedule(changeover));

  auto heatingCoil = radiant.heatingCoil();
  auto coolingCoil = radiant.coolingCoil();

  EXPECT_TRUE(heatingCoil.setHeatingHighWaterTemperatureSchedule(heatingHighWater));
  EXPECT_TRUE(heatingCoil.setHeatingLowWaterTemperatureSchedule(heatingLowWater));
  EXPECT_TRUE(heatingCoil.setHeatingHighControlTemperatureSchedule(heatingHighControl));
  EXPECT_TRUE(heatingCoil.setHeatingLowControlTemperatureSchedule(heatingLowControl));

  EXPECT_TRUE(coolingCoil.setCoolingHighWaterTemperatureSchedule(coolingHighWater));
  EXPECT_TRUE(coolingCoil.setCoolingLowWaterTemperatureSchedule(coolingLowWater));
  EXPECT_TRUE(coolingCoil.setCoolingHighControlTemperatureSchedule(coolingHighControl));
  EXPECT_TRUE(coolingCoil.setCoolingLowControlTemperatureSchedule(coolingLowControl));
  EXPECT_TRUE(coolingCoil.setCondensationControlType("VariableOff"));
  EXPECT_TRUE(coolingCoil.setCondensationControlDewpointOffset(1.5));

  ASSERT_TRUE(radiant.availabilitySchedule());
  EXPECT_EQ(availability.handle(), radiant.availabilitySchedule()->handle());
  ASSERT_TRUE(radiant.pumpFlowRateSchedule());
  EXPECT_EQ(pump.handle(), radiant.pumpFlowRateSchedule()->handle());
  ASSERT_TRUE(radiant.changeoverDelayTimePeriodSchedule());
  EXPECT_EQ(changeover.handle(), radiant.changeoverDelayTimePeriodSchedule()->handle());

  ASSERT_TRUE(heatingCoil.heatingHighWaterTemperatureSchedule());
  EXPECT_EQ(heatingHighWater.handle(), heatingCoil.heatingHighWaterTemperatureSchedule()->handle());
  ASSERT_TRUE(heatingCoil.heatingLowWaterTemperatureSchedule());
  EXPECT_EQ(heatingLowWater.handle(), heatingCoil.heatingLowWaterTemperatureSchedule()->handle());
  ASSERT_TRUE(heatingCoil.heatingHighControlTemperatureSchedule());
  EXPECT_EQ(heatingHighControl.handle(), heatingCoil.heatingHighControlTemperatureSchedule()->handle());
  ASSERT_TRUE(heatingCoil.heatingLowControlTemperatureSchedule());
  EXPECT_EQ(heatingLowControl.handle(), heatingCoil.heatingLowControlTemperatureSchedule()->handle());

  ASSERT_TRUE(coolingCoil.coolingHighWaterTemperatureSchedule());
  EXPECT_EQ(coolingHighWater.handle(), coolingCoil.coolingHighWaterTemperatureSchedule()->handle());
  ASSERT_TRUE(coolingCoil.coolingLowWaterTemperatureSchedule());
  EXPECT_EQ(coolingLowWater.handle(), coolingCoil.coolingLowWaterTemperatureSchedule()->handle());
  ASSERT_TRUE(coolingCoil.coolingHighControlTemperatureSchedule());
  EXPECT_EQ(coolingHighControl.handle(), coolingCoil.coolingHighControlTemperatureSchedule()->handle());
  ASSERT_TRUE(coolingCoil.coolingLowControlTemperatureSchedule());
  EXPECT_EQ(coolingLowControl.handle(), coolingCoil.coolingLowControlTemperatureSchedule()->handle());
  EXPECT_EQ("VariableOff", coolingCoil.condensationControlType());
  EXPECT_DOUBLE_EQ(1.5, coolingCoil.condensationControlDewpointOffset());
}

TEST_F(EPModelFixture, ZoneHVACLowTempRadiantConstFlow_TransientCompanionCoils_ResolveParentWaterNodes) {
  Model model;
  ZoneHVACLowTempRadiantConstFlow radiant(model);

  Node heatingInlet = model.getOrCreateTransientByName<Node>("Radiant Heating Inlet");
  Node heatingOutlet = model.getOrCreateTransientByName<Node>("Radiant Heating Outlet");
  Node coolingInlet = model.getOrCreateTransientByName<Node>("Radiant Cooling Inlet");
  Node coolingOutlet = model.getOrCreateTransientByName<Node>("Radiant Cooling Outlet");

  ASSERT_TRUE(
    radiant.setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HeatingWaterInletNodeName, heatingInlet.handle()));
  ASSERT_TRUE(
    radiant.setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HeatingWaterOutletNodeName, heatingOutlet.handle()));
  ASSERT_TRUE(
    radiant.setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::CoolingWaterInletNodeName, coolingInlet.handle()));
  ASSERT_TRUE(
    radiant.setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::CoolingWaterOutletNodeName, coolingOutlet.handle()));

  auto heatingCoil = radiant.heatingCoil();
  auto coolingCoil = radiant.coolingCoil();

  ASSERT_TRUE(heatingCoil.inletModelObject());
  EXPECT_EQ(heatingInlet.handle(), heatingCoil.inletModelObject()->handle());
  ASSERT_TRUE(heatingCoil.outletModelObject());
  EXPECT_EQ(heatingOutlet.handle(), heatingCoil.outletModelObject()->handle());
  ASSERT_TRUE(coolingCoil.inletModelObject());
  EXPECT_EQ(coolingInlet.handle(), coolingCoil.inletModelObject()->handle());
  ASSERT_TRUE(coolingCoil.outletModelObject());
  EXPECT_EQ(coolingOutlet.handle(), coolingCoil.outletModelObject()->handle());

  EXPECT_FALSE(heatingCoil.addToNode(heatingInlet));
  EXPECT_FALSE(coolingCoil.addToNode(coolingInlet));
}

TEST_F(EPModelFixture, ZoneHVACLowTempRadiantConstFlow_RadiantSurfaceType_RewritesPersistedSurfaceGroup) {
  Model model;
  ThermalZone zone(model);
  Space space(model);
  ASSERT_TRUE(space.setThermalZone(zone));

  // This test currently has to set up the radiant-eligible envelope state
  // through low-level fields because epmodel does not yet have much developed
  // surface/surface-group/construction convenience on the envelope side. That
  // is acceptable for now because the production implementation is working with
  // the same persisted EnergyPlus fields, but this test should be revisited
  // once richer envelope wrappers exist.
  ModelObject construction = ModelObject::create(IddObjectType::Construction, model);
  ConstructionWithInternalSource radiantConstruction(model);
  ASSERT_TRUE(radiantConstruction.setPointer(openstudio::ConstructionProperty_InternalHeatSourceFields::ConstructionName, construction.handle()));

  auto makeSurface = [&](const std::string& name, const std::string& surfaceType,
                         const std::vector<std::array<double, 3>>& vertices) -> Surface {
    Surface surface(model);
    EXPECT_TRUE(surface.setName(name));
    EXPECT_TRUE(surface.setSurfaceType(surfaceType));
    EXPECT_TRUE(surface.setPointer(openstudio::BuildingSurface_DetailedFields::ConstructionName, construction.handle()));
    EXPECT_TRUE(surface.setPointer(openstudio::BuildingSurface_DetailedFields::SpaceName, space.handle()));
    for (const auto& vertex : vertices) {
      auto group = surface.pushExtensibleGroup();
      EXPECT_TRUE(group.setDouble(openstudio::BuildingSurface_DetailedExtensibleFields::VertexXcoordinate, vertex[0]));
      EXPECT_TRUE(group.setDouble(openstudio::BuildingSurface_DetailedExtensibleFields::VertexYcoordinate, vertex[1]));
      EXPECT_TRUE(group.setDouble(openstudio::BuildingSurface_DetailedExtensibleFields::VertexZcoordinate, vertex[2]));
    }
    return surface;
  };

  auto floor = makeSurface("Radiant Floor", "Floor", {{0.0, 0.0, 0.0}, {4.0, 0.0, 0.0}, {4.0, 3.0, 0.0}, {0.0, 3.0, 0.0}});
  auto ceiling = makeSurface("Radiant Ceiling", "Roof", {{0.0, 0.0, 3.0}, {4.0, 0.0, 3.0}, {4.0, 3.0, 3.0}, {0.0, 3.0, 3.0}});
  auto wall = makeSurface("Radiant Wall", "Wall", {{0.0, 0.0, 0.0}, {4.0, 0.0, 0.0}, {4.0, 0.0, 3.0}, {0.0, 0.0, 3.0}});

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

  ZoneHVACLowTempRadiantConstFlow radiant(model);
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
