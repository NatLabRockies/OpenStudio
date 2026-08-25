/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../HVACComponent/ThermalZone_Impl.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../Loop/PlantLoop_Impl.hpp"
#include "../Schedule/ScheduleCompact.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../StraightComponent/CoilHeatingElectric.hpp"
#include "../StraightComponent/CoilHeatingElectric_Impl.hpp"
#include "../StraightComponent/FanConstantVolume.hpp"
#include "../StraightComponent/FanSystemModel.hpp"
#include "../StraightComponent/FanSystemModel_Impl.hpp"
#include "../StraightComponent/Node.hpp"
#include "../WaterToAirComponent/CoilCoolingWater.hpp"
#include "../WaterToAirComponent/CoilCoolingWater_Impl.hpp"
#include "../ZoneHVACComponent/ZoneHVACUnitVentilator.hpp"
#include "../ZoneHVACComponent/ZoneHVACUnitVentilator_Impl.hpp"

#include <utilities/core/Filesystem.hpp>
#include <utilities/core/UUID.hpp>
#include <utilities/idd/ZoneHVAC_UnitVentilator_FieldEnums.hxx>

#include <algorithm>
#include <utility>

using namespace openstudio::epmodel;

namespace {

class ScopedFileRemoval
{
 public:
  explicit ScopedFileRemoval(openstudio::path path) : m_path(std::move(path)) {}

  ~ScopedFileRemoval() {
    boost::system::error_code error;
    boost::filesystem::remove(m_path, error);
  }

 private:
  openstudio::path m_path;
};

void expectUnitVentilatorAirPath(const ZoneHVACUnitVentilator& ventilator, const FanSystemModel& fan, const CoilCoolingWater& coolingCoil,
                                 const CoilHeatingElectric& heatingCoil) {
  const auto ventilatorInlet = ventilator.inletNode();
  const auto ventilatorOutlet = ventilator.outletNode();
  const auto mixedAir = ventilator.mixedAirNode();
  const auto outdoorAir = ventilator.outdoorAirNode();
  const auto exhaustAir = ventilator.exhaustAirNode();
  const auto fanOutlet = ventilator.fanOutletNode();
  const auto coolingOutlet = ventilator.coolingCoilOutletNode();
  const auto fanInlet = fan.inletModelObject();
  const auto fanOutletObject = fan.outletModelObject();
  const auto coolingInlet = coolingCoil.airInletModelObject();
  const auto coolingOutletObject = coolingCoil.airOutletModelObject();
  const auto heatingInlet = heatingCoil.inletModelObject();
  const auto heatingOutlet = heatingCoil.outletModelObject();

  ASSERT_TRUE(ventilatorInlet);
  ASSERT_TRUE(ventilatorOutlet);
  ASSERT_TRUE(mixedAir);
  ASSERT_TRUE(outdoorAir);
  ASSERT_TRUE(exhaustAir);
  ASSERT_TRUE(fanOutlet);
  ASSERT_TRUE(coolingOutlet);
  ASSERT_TRUE(fanInlet);
  ASSERT_TRUE(fanOutletObject);
  ASSERT_TRUE(coolingInlet);
  ASSERT_TRUE(coolingOutletObject);
  ASSERT_TRUE(heatingInlet);
  ASSERT_TRUE(heatingOutlet);

  EXPECT_EQ(mixedAir->handle(), fanInlet->handle());
  EXPECT_EQ(fanOutlet->handle(), fanOutletObject->handle());
  EXPECT_EQ(fanOutlet->handle(), coolingInlet->handle());
  EXPECT_EQ(coolingOutlet->handle(), coolingOutletObject->handle());
  EXPECT_EQ(coolingOutlet->handle(), heatingInlet->handle());
  EXPECT_EQ(ventilatorOutlet->handle(), heatingOutlet->handle());
  EXPECT_NE(ventilatorInlet->handle(), mixedAir->handle());
  EXPECT_NE(mixedAir->handle(), fanOutlet->handle());
  EXPECT_NE(fanOutlet->handle(), coolingOutlet->handle());
  EXPECT_NE(coolingOutlet->handle(), ventilatorOutlet->handle());
  EXPECT_NE(outdoorAir->handle(), mixedAir->handle());
  EXPECT_NE(exhaustAir->handle(), mixedAir->handle());

  ASSERT_TRUE(fan.containingHVACComponent());
  ASSERT_TRUE(coolingCoil.containingHVACComponent());
  ASSERT_TRUE(heatingCoil.containingHVACComponent());
  EXPECT_EQ(ventilator.handle(), fan.containingHVACComponent()->handle());
  EXPECT_EQ(ventilator.handle(), coolingCoil.containingHVACComponent()->handle());
  EXPECT_EQ(ventilator.handle(), heatingCoil.containingHVACComponent()->handle());
}

}  // namespace

TEST_F(EPModelFixture, ZoneHVACUnitVentilator_DefaultConstructor) {
  Model model;
  ZoneHVACUnitVentilator ventilator(model);

  EXPECT_EQ(ZoneHVACUnitVentilator::iddObjectType(), ventilator.iddObject().type());
  EXPECT_TRUE(ventilator.isMaximumSupplyAirFlowRateAutosized());
  EXPECT_EQ("VariablePercent", ventilator.outdoorAirControlType());
  EXPECT_TRUE(ventilator.isMinimumOutdoorAirFlowRateAutosized());
  EXPECT_TRUE(ventilator.isMaximumOutdoorAirFlowRateAutosized());
  EXPECT_DOUBLE_EQ(0.001, ventilator.heatingConvergenceTolerance());
  EXPECT_DOUBLE_EQ(0.001, ventilator.coolingConvergenceTolerance());
}

TEST_F(EPModelFixture, ZoneHVACUnitVentilator_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneHVACUnitVentilator ventilator(model);

  EXPECT_TRUE(ventilator.setMaximumSupplyAirFlowRate(0.42));
  EXPECT_FALSE(ventilator.isMaximumSupplyAirFlowRateAutosized());

  auto controlTypes = ZoneHVACUnitVentilator::outdoorAirControlTypeValues();
  ASSERT_FALSE(controlTypes.empty());
  std::string overrideType = controlTypes[0];
  if (overrideType == "VariablePercent" && controlTypes.size() > 1) {
    overrideType = controlTypes[1];
  }
  EXPECT_TRUE(ventilator.setOutdoorAirControlType(overrideType));
  EXPECT_EQ(overrideType, ventilator.outdoorAirControlType());

  EXPECT_TRUE(ventilator.setMinimumOutdoorAirFlowRate(0.1));
  EXPECT_TRUE(ventilator.setMaximumOutdoorAirFlowRate(0.52));
  EXPECT_TRUE(ventilator.setHeatingConvergenceTolerance(0.005));
  EXPECT_TRUE(ventilator.setCoolingConvergenceTolerance(0.004));

  ASSERT_TRUE(ventilator.minimumOutdoorAirFlowRate());
  EXPECT_DOUBLE_EQ(0.1, ventilator.minimumOutdoorAirFlowRate().value());
  ASSERT_TRUE(ventilator.maximumOutdoorAirFlowRate());
  EXPECT_DOUBLE_EQ(0.52, ventilator.maximumOutdoorAirFlowRate().value());
  EXPECT_DOUBLE_EQ(0.005, ventilator.heatingConvergenceTolerance());
  EXPECT_DOUBLE_EQ(0.004, ventilator.coolingConvergenceTolerance());

  ventilator.autosizeMaximumSupplyAirFlowRate();
  EXPECT_TRUE(ventilator.isMaximumSupplyAirFlowRateAutosized());
  EXPECT_FALSE(ventilator.maximumSupplyAirFlowRate());

  ventilator.autosizeMinimumOutdoorAirFlowRate();
  EXPECT_TRUE(ventilator.isMinimumOutdoorAirFlowRateAutosized());
  EXPECT_FALSE(ventilator.minimumOutdoorAirFlowRate());

  ventilator.autosizeMaximumOutdoorAirFlowRate();
  EXPECT_TRUE(ventilator.isMaximumOutdoorAirFlowRateAutosized());
  EXPECT_FALSE(ventilator.maximumOutdoorAirFlowRate());
}

TEST_F(EPModelFixture, ZoneHVACUnitVentilator_TopologyAndChildren) {
  Model model;
  ThermalZone zone(model);
  ZoneHVACUnitVentilator ventilator(model);
  FanConstantVolume supplyFan(model);
  CoilHeatingElectric heatingCoil(model);
  CoilCoolingWater coolingCoil(model);

  EXPECT_EQ(openstudio::ZoneHVAC_UnitVentilatorFields::AirInletNodeName, ventilator.inletPort());
  EXPECT_EQ(openstudio::ZoneHVAC_UnitVentilatorFields::AirOutletNodeName, ventilator.outletPort());

  EXPECT_TRUE(ventilator.setSupplyAirFan(supplyFan));
  EXPECT_TRUE(ventilator.setHeatingCoil(heatingCoil));
  EXPECT_TRUE(ventilator.setCoolingCoil(coolingCoil));
  EXPECT_TRUE(ventilator.inletNode());
  EXPECT_TRUE(ventilator.outletNode());
  EXPECT_TRUE(ventilator.mixedAirNode());
  EXPECT_TRUE(ventilator.outdoorAirNode());
  EXPECT_TRUE(ventilator.exhaustAirNode());
  EXPECT_TRUE(ventilator.fanOutletNode());
  EXPECT_TRUE(ventilator.coolingCoilOutletNode());

  EXPECT_TRUE(ventilator.addToThermalZone(zone));
  ASSERT_TRUE(ventilator.thermalZone());
  EXPECT_EQ(zone, ventilator.thermalZone().get());
  EXPECT_TRUE(ventilator.inletNode());
  EXPECT_TRUE(ventilator.outletNode());
  EXPECT_TRUE(ventilator.mixedAirNode());
  EXPECT_TRUE(ventilator.outdoorAirNode());
  EXPECT_TRUE(ventilator.exhaustAirNode());
  EXPECT_TRUE(ventilator.fanOutletNode());
  EXPECT_TRUE(ventilator.coolingCoilOutletNode());

  const auto children = ventilator.children();
  ASSERT_EQ(3u, children.size());
  EXPECT_EQ(supplyFan, children[0]);
  EXPECT_EQ(heatingCoil, children[1]);
  EXPECT_EQ(coolingCoil, children[2]);

  ventilator.removeFromThermalZone();
  EXPECT_FALSE(ventilator.thermalZone());
  EXPECT_TRUE(ventilator.inletNode());
  EXPECT_TRUE(ventilator.outletNode());
  EXPECT_TRUE(ventilator.mixedAirNode());
  EXPECT_TRUE(ventilator.outdoorAirNode());
  EXPECT_TRUE(ventilator.exhaustAirNode());
  EXPECT_TRUE(ventilator.fanOutletNode());
  EXPECT_TRUE(ventilator.coolingCoilOutletNode());
}

TEST_F(EPModelFixture, ZoneHVACUnitVentilator_HvacRelationships_RoundTrip) {
  Model model;
  ZoneHVACUnitVentilator ventilator(model);

  auto defaultSchedule = ventilator.availabilitySchedule().optionalCast<ScheduleConstant>();
  ASSERT_TRUE(defaultSchedule);
  EXPECT_DOUBLE_EQ(1.0, defaultSchedule->value());

  ScheduleCompact availability(model);
  ScheduleCompact minimumOutdoorAir(model);
  ScheduleCompact maximumOutdoorAir(model);
  ScheduleCompact fanMode(model);
  ASSERT_TRUE(availability.setToConstantValue(0.5));
  ASSERT_TRUE(minimumOutdoorAir.setToConstantValue(0.2));
  ASSERT_TRUE(maximumOutdoorAir.setToConstantValue(0.7));
  ASSERT_TRUE(fanMode.setToConstantValue(1.0));

  EXPECT_TRUE(ventilator.setAvailabilitySchedule(availability));
  EXPECT_TRUE(ventilator.setMinimumOutdoorAirSchedule(minimumOutdoorAir));
  EXPECT_TRUE(ventilator.setMaximumOutdoorAirFractionorTemperatureSchedule(maximumOutdoorAir));
  EXPECT_TRUE(ventilator.setSupplyAirFanOperatingModeSchedule(fanMode));

  EXPECT_EQ(availability.handle(), ventilator.availabilitySchedule().handle());
  EXPECT_EQ(minimumOutdoorAir.handle(), ventilator.minimumOutdoorAirSchedule().handle());
  EXPECT_EQ(maximumOutdoorAir.handle(), ventilator.maximumOutdoorAirFractionorTemperatureSchedule().handle());
  ASSERT_TRUE(ventilator.supplyAirFanOperatingModeSchedule());
  EXPECT_EQ(fanMode.handle(), ventilator.supplyAirFanOperatingModeSchedule()->handle());

  FanConstantVolume supplyFan(model);
  CoilHeatingElectric heatingCoil(model);
  CoilCoolingWater coolingCoil(model);
  EXPECT_TRUE(ventilator.setSupplyAirFan(supplyFan));
  EXPECT_TRUE(ventilator.setHeatingCoil(heatingCoil));
  EXPECT_TRUE(ventilator.setCoolingCoil(coolingCoil));
  EXPECT_EQ(supplyFan.handle(), ventilator.supplyAirFan().handle());
  ASSERT_TRUE(ventilator.heatingCoil());
  EXPECT_EQ(heatingCoil.handle(), ventilator.heatingCoil()->handle());
  ASSERT_TRUE(ventilator.coolingCoil());
  EXPECT_EQ(coolingCoil.handle(), ventilator.coolingCoil()->handle());

  auto fanType = ventilator.getString(openstudio::ZoneHVAC_UnitVentilatorFields::SupplyAirFanObjectType, true);
  auto heatingType = ventilator.getString(openstudio::ZoneHVAC_UnitVentilatorFields::HeatingCoilObjectType, true);
  auto coolingType = ventilator.getString(openstudio::ZoneHVAC_UnitVentilatorFields::CoolingCoilObjectType, true);
  auto coilOption = ventilator.getString(openstudio::ZoneHVAC_UnitVentilatorFields::CoilOption, true);
  ASSERT_TRUE(fanType);
  ASSERT_TRUE(heatingType);
  ASSERT_TRUE(coolingType);
  ASSERT_TRUE(coilOption);
  EXPECT_EQ(supplyFan.iddObject().name(), *fanType);
  EXPECT_EQ(heatingCoil.iddObject().name(), *heatingType);
  EXPECT_EQ(coolingCoil.iddObject().name(), *coolingType);
  EXPECT_EQ("HeatingAndCooling", *coilOption);

  ventilator.resetSupplyAirFanOperatingModeSchedule();
  EXPECT_FALSE(ventilator.supplyAirFanOperatingModeSchedule());
  ventilator.resetHeatingCoil();
  EXPECT_FALSE(ventilator.heatingCoil());
  ASSERT_TRUE(ventilator.fanOutletNode());
  ASSERT_TRUE(ventilator.coolingCoilOutletNode());
  ASSERT_TRUE(coolingCoil.airOutletModelObject());
  EXPECT_EQ(*ventilator.fanOutletNode(), *coolingCoil.airInletModelObject()->optionalCast<Node>());
  EXPECT_EQ(*ventilator.coolingCoilOutletNode(), *coolingCoil.airOutletModelObject()->optionalCast<Node>());

  ventilator.resetCoolingCoil();
  EXPECT_FALSE(ventilator.coolingCoil());
  EXPECT_TRUE(ventilator.mixedAirNode());
  EXPECT_TRUE(ventilator.outdoorAirNode());
  EXPECT_TRUE(ventilator.exhaustAirNode());
  ASSERT_TRUE(ventilator.fanOutletNode());
  ASSERT_TRUE(supplyFan.outletModelObject());
  EXPECT_EQ(*ventilator.fanOutletNode(), *supplyFan.outletModelObject()->optionalCast<Node>());
  EXPECT_EQ(*ventilator.fanOutletNode(), *ventilator.outletNode());
  EXPECT_FALSE(ventilator.coolingCoilOutletNode());

  coilOption = ventilator.getString(openstudio::ZoneHVAC_UnitVentilatorFields::CoilOption, true);
  ASSERT_TRUE(coilOption);
  EXPECT_EQ("None", *coilOption);
}

TEST_F(EPModelFixture, ZoneHVACUnitVentilator_ContainedNodePath_RoundTrip) {
  Model model;
  ZoneHVACUnitVentilator ventilator(model);
  FanConstantVolume supplyFan(model);
  CoilHeatingElectric heatingCoil(model);
  CoilCoolingWater coolingCoil(model);

  ASSERT_TRUE(ventilator.setSupplyAirFan(supplyFan));
  ASSERT_TRUE(ventilator.setHeatingCoil(heatingCoil));
  ASSERT_TRUE(ventilator.setCoolingCoil(coolingCoil));

  auto ventilatorInlet = ventilator.inletNode();
  auto ventilatorOutlet = ventilator.outletNode();
  auto mixedAirNode = ventilator.mixedAirNode();
  auto outdoorAirNode = ventilator.outdoorAirNode();
  auto exhaustAirNode = ventilator.exhaustAirNode();
  auto fanOutletNode = ventilator.fanOutletNode();
  auto coolingCoilOutletNode = ventilator.coolingCoilOutletNode();
  auto fanInlet = supplyFan.inletModelObject();
  auto fanOutlet = supplyFan.outletModelObject();
  auto coolingInlet = coolingCoil.airInletModelObject();
  auto coolingOutlet = coolingCoil.airOutletModelObject();
  auto heatingInlet = heatingCoil.inletModelObject();
  auto heatingOutlet = heatingCoil.outletModelObject();

  ASSERT_TRUE(ventilatorInlet);
  ASSERT_TRUE(ventilatorOutlet);
  ASSERT_TRUE(mixedAirNode);
  ASSERT_TRUE(outdoorAirNode);
  ASSERT_TRUE(exhaustAirNode);
  ASSERT_TRUE(fanOutletNode);
  ASSERT_TRUE(coolingCoilOutletNode);
  ASSERT_TRUE(fanInlet);
  ASSERT_TRUE(fanOutlet);
  ASSERT_TRUE(coolingInlet);
  ASSERT_TRUE(coolingOutlet);
  ASSERT_TRUE(heatingInlet);
  ASSERT_TRUE(heatingOutlet);

  auto fanInletNode = fanInlet->optionalCast<Node>();
  auto fanOutletNodeObject = fanOutlet->optionalCast<Node>();
  auto coolingInletNode = coolingInlet->optionalCast<Node>();
  auto coolingOutletNodeObject = coolingOutlet->optionalCast<Node>();
  auto heatingInletNode = heatingInlet->optionalCast<Node>();
  auto heatingOutletNode = heatingOutlet->optionalCast<Node>();
  ASSERT_TRUE(fanInletNode);
  ASSERT_TRUE(fanOutletNodeObject);
  ASSERT_TRUE(coolingInletNode);
  ASSERT_TRUE(coolingOutletNodeObject);
  ASSERT_TRUE(heatingInletNode);
  ASSERT_TRUE(heatingOutletNode);

  EXPECT_EQ(*mixedAirNode, *fanInletNode);
  EXPECT_EQ(*fanOutletNode, *fanOutletNodeObject);
  EXPECT_EQ(*fanOutletNodeObject, *coolingInletNode);
  EXPECT_EQ(*coolingCoilOutletNode, *coolingOutletNodeObject);
  EXPECT_EQ(*coolingOutletNodeObject, *heatingInletNode);
  EXPECT_EQ(*heatingOutletNode, *ventilatorOutlet);
  EXPECT_NE(*ventilatorInlet, *mixedAirNode);
  EXPECT_NE(*mixedAirNode, *fanOutletNode);
  EXPECT_NE(*fanOutletNode, *coolingCoilOutletNode);
  EXPECT_NE(*coolingCoilOutletNode, *ventilatorOutlet);
  EXPECT_NE(*outdoorAirNode, *mixedAirNode);
  EXPECT_NE(*exhaustAirNode, *mixedAirNode);

  ASSERT_TRUE(supplyFan.containingHVACComponent());
  ASSERT_TRUE(heatingCoil.containingHVACComponent());
  ASSERT_TRUE(coolingCoil.containingHVACComponent());
  EXPECT_EQ(ventilator, supplyFan.containingHVACComponent().get());
  EXPECT_EQ(ventilator, heatingCoil.containingHVACComponent().get());
  EXPECT_EQ(ventilator, coolingCoil.containingHVACComponent().get());
}

TEST_F(EPModelFixture, ZoneHVACUnitVentilator_NodeRolesMayAliasBoundaryNodes) {
  Model model;
  ZoneHVACUnitVentilator ventilator(model);
  FanConstantVolume supplyFan(model);
  CoilCoolingWater coolingCoil(model);

  ASSERT_TRUE(ventilator.setSupplyAirFan(supplyFan));
  ASSERT_TRUE(ventilator.setCoolingCoil(coolingCoil));

  auto fanOutletNode = ventilator.fanOutletNode();
  auto coolingCoilOutletNode = ventilator.coolingCoilOutletNode();
  auto ventilatorOutlet = ventilator.outletNode();
  ASSERT_TRUE(fanOutletNode);
  ASSERT_TRUE(coolingCoilOutletNode);
  ASSERT_TRUE(ventilatorOutlet);

  EXPECT_EQ(*fanOutletNode, *coolingCoil.airInletModelObject()->optionalCast<Node>());
  EXPECT_EQ(*coolingCoilOutletNode, *coolingCoil.airOutletModelObject()->optionalCast<Node>());
  EXPECT_EQ(*coolingCoilOutletNode, *ventilatorOutlet);

  ventilator.resetCoolingCoil();
  ASSERT_TRUE(ventilator.fanOutletNode());
  EXPECT_EQ(*ventilator.fanOutletNode(), *ventilator.outletNode());
  EXPECT_FALSE(ventilator.coolingCoilOutletNode());
}

TEST_F(EPModelFixture, ZoneHVACUnitVentilator_InternalNodeRenamesSurviveCanonicalize) {
  Model model;
  ZoneHVACUnitVentilator ventilator(model);
  FanConstantVolume supplyFan(model);
  CoilHeatingElectric heatingCoil(model);
  CoilCoolingWater coolingCoil(model);

  ASSERT_TRUE(ventilator.setSupplyAirFan(supplyFan));
  ASSERT_TRUE(ventilator.setHeatingCoil(heatingCoil));
  ASSERT_TRUE(ventilator.setCoolingCoil(coolingCoil));

  auto mixedAirNode = ventilator.mixedAirNode();
  auto outdoorAirNode = ventilator.outdoorAirNode();
  auto exhaustAirNode = ventilator.exhaustAirNode();
  auto fanOutletNode = ventilator.fanOutletNode();
  auto coolingCoilOutletNode = ventilator.coolingCoilOutletNode();
  ASSERT_TRUE(mixedAirNode);
  ASSERT_TRUE(outdoorAirNode);
  ASSERT_TRUE(exhaustAirNode);
  ASSERT_TRUE(fanOutletNode);
  ASSERT_TRUE(coolingCoilOutletNode);

  ASSERT_TRUE(mixedAirNode->setName("Custom Unit Ventilator Mixed Air"));
  ASSERT_TRUE(outdoorAirNode->setName("Custom Unit Ventilator Outdoor Air"));
  ASSERT_TRUE(exhaustAirNode->setName("Custom Unit Ventilator Exhaust Air"));
  ASSERT_TRUE(fanOutletNode->setName("Custom Unit Ventilator Fan Outlet"));
  ASSERT_TRUE(coolingCoilOutletNode->setName("Custom Unit Ventilator Cooling Outlet"));

  auto report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);

  auto renamedMixedAirNode = ventilator.mixedAirNode();
  auto renamedOutdoorAirNode = ventilator.outdoorAirNode();
  auto renamedExhaustAirNode = ventilator.exhaustAirNode();
  auto renamedFanOutletNode = ventilator.fanOutletNode();
  auto renamedCoolingCoilOutletNode = ventilator.coolingCoilOutletNode();
  ASSERT_TRUE(renamedMixedAirNode);
  ASSERT_TRUE(renamedOutdoorAirNode);
  ASSERT_TRUE(renamedExhaustAirNode);
  ASSERT_TRUE(renamedFanOutletNode);
  ASSERT_TRUE(renamedCoolingCoilOutletNode);

  EXPECT_EQ("Custom Unit Ventilator Mixed Air", renamedMixedAirNode->nameString());
  EXPECT_EQ("Custom Unit Ventilator Outdoor Air", renamedOutdoorAirNode->nameString());
  EXPECT_EQ("Custom Unit Ventilator Exhaust Air", renamedExhaustAirNode->nameString());
  EXPECT_EQ("Custom Unit Ventilator Fan Outlet", renamedFanOutletNode->nameString());
  EXPECT_EQ("Custom Unit Ventilator Cooling Outlet", renamedCoolingCoilOutletNode->nameString());
  EXPECT_EQ(*renamedMixedAirNode, *supplyFan.inletModelObject()->optionalCast<Node>());
  EXPECT_EQ(*renamedFanOutletNode, *coolingCoil.airInletModelObject()->optionalCast<Node>());
  EXPECT_EQ(*renamedCoolingCoilOutletNode, *heatingCoil.inletModelObject()->optionalCast<Node>());
}

TEST_F(EPModelFixture, ZoneHVACUnitVentilator_ContainedChildTopologyMutationsAreRejected) {
  Model model;
  AirLoopHVAC airLoop(model);
  PlantLoop plantLoop(model);
  ZoneHVACUnitVentilator ventilator(model);
  FanConstantVolume supplyFan(model);
  CoilHeatingElectric heatingCoil(model);
  CoilCoolingWater coolingCoil(model);

  ASSERT_TRUE(ventilator.setSupplyAirFan(supplyFan));
  ASSERT_TRUE(ventilator.setHeatingCoil(heatingCoil));
  ASSERT_TRUE(ventilator.setCoolingCoil(coolingCoil));

  auto originalMixedAirNode = ventilator.mixedAirNode();
  auto originalFanOutletNode = ventilator.fanOutletNode();
  auto originalCoolingCoilOutletNode = ventilator.coolingCoilOutletNode();
  auto fanInlet = supplyFan.inletModelObject();
  auto coolingInlet = coolingCoil.airInletModelObject();
  auto heatingInlet = heatingCoil.inletModelObject();
  ASSERT_TRUE(originalMixedAirNode);
  ASSERT_TRUE(originalFanOutletNode);
  ASSERT_TRUE(originalCoolingCoilOutletNode);
  ASSERT_TRUE(fanInlet);
  ASSERT_TRUE(coolingInlet);
  ASSERT_TRUE(heatingInlet);

  supplyFan.disconnect();
  auto supplyOutletNode = airLoop.supplyOutletNode();
  EXPECT_FALSE(supplyFan.addToNode(supplyOutletNode));
  EXPECT_FALSE(supplyFan.isRemovable());
  EXPECT_TRUE(supplyFan.remove().empty());

  coolingCoil.disconnectAirSide();
  EXPECT_FALSE(coolingCoil.addToNode(supplyOutletNode));
  EXPECT_FALSE(coolingCoil.removeFromAirLoopHVAC());
  EXPECT_FALSE(coolingCoil.isRemovable());
  EXPECT_TRUE(coolingCoil.remove().empty());
  EXPECT_TRUE(plantLoop.addDemandBranchForComponent(coolingCoil));
  ASSERT_TRUE(coolingCoil.plantLoop());
  EXPECT_EQ(plantLoop, coolingCoil.plantLoop().get());
  coolingCoil.disconnect();
  ASSERT_TRUE(coolingCoil.plantLoop());
  EXPECT_EQ(plantLoop, coolingCoil.plantLoop().get());

  auto currentMixedAirNode = ventilator.mixedAirNode();
  auto currentFanOutletNode = ventilator.fanOutletNode();
  auto currentCoolingCoilOutletNode = ventilator.coolingCoilOutletNode();
  auto fanInletNode = fanInlet->optionalCast<Node>();
  auto coolingInletNode = coolingInlet->optionalCast<Node>();
  auto heatingInletNode = heatingInlet->optionalCast<Node>();
  ASSERT_TRUE(currentMixedAirNode);
  ASSERT_TRUE(currentFanOutletNode);
  ASSERT_TRUE(currentCoolingCoilOutletNode);
  ASSERT_TRUE(fanInletNode);
  ASSERT_TRUE(coolingInletNode);
  ASSERT_TRUE(heatingInletNode);

  EXPECT_EQ(*originalMixedAirNode, *currentMixedAirNode);
  EXPECT_EQ(*originalFanOutletNode, *currentFanOutletNode);
  EXPECT_EQ(*originalCoolingCoilOutletNode, *currentCoolingCoilOutletNode);
  EXPECT_EQ(*currentMixedAirNode, *fanInletNode);
  EXPECT_EQ(*currentFanOutletNode, *coolingInletNode);
  EXPECT_EQ(*currentCoolingCoilOutletNode, *heatingInletNode);

  const auto children = ventilator.children();
  ASSERT_EQ(3u, children.size());
  EXPECT_EQ(supplyFan, children[0]);
  EXPECT_EQ(heatingCoil, children[1]);
  EXPECT_EQ(coolingCoil, children[2]);
}

TEST_F(EPModelFixture, ZoneHVACUnitVentilator_OwnerMutationsRebuildContainedPathWithoutSalvage) {
  Model model;
  ZoneHVACUnitVentilator ventilator(model);
  FanConstantVolume supplyFan(model);
  CoilHeatingElectric heatingCoil(model);
  CoilCoolingWater coolingCoil(model);

  ASSERT_TRUE(ventilator.setSupplyAirFan(supplyFan));
  ASSERT_TRUE(ventilator.setHeatingCoil(heatingCoil));
  ASSERT_TRUE(ventilator.setCoolingCoil(coolingCoil));

  Node rogueFanOutlet(model);
  ASSERT_TRUE(rogueFanOutlet.setName("Rogue Owner Mutation Fan Outlet"));
  Node rogueCoolingOutlet(model);
  ASSERT_TRUE(rogueCoolingOutlet.setName("Rogue Owner Mutation Cooling Outlet"));

  ASSERT_TRUE(supplyFan.setPointer(supplyFan.outletPort(), rogueFanOutlet.handle()));
  ASSERT_TRUE(coolingCoil.setPointer(coolingCoil.airInletPort(), rogueFanOutlet.handle()));
  ASSERT_TRUE(coolingCoil.setPointer(coolingCoil.airOutletPort(), rogueCoolingOutlet.handle()));
  ASSERT_TRUE(heatingCoil.setPointer(heatingCoil.inletPort(), rogueCoolingOutlet.handle()));

  ventilator.resetCoolingCoil();
  ASSERT_TRUE(ventilator.setCoolingCoil(coolingCoil));

  auto repairedFanOutletNode = ventilator.fanOutletNode();
  auto repairedCoolingCoilOutletNode = ventilator.coolingCoilOutletNode();
  ASSERT_TRUE(repairedFanOutletNode);
  ASSERT_TRUE(repairedCoolingCoilOutletNode);

  EXPECT_NE("Rogue Owner Mutation Fan Outlet", repairedFanOutletNode->nameString());
  EXPECT_NE("Rogue Owner Mutation Cooling Outlet", repairedCoolingCoilOutletNode->nameString());
  EXPECT_EQ(*repairedFanOutletNode, *coolingCoil.airInletModelObject()->optionalCast<Node>());
  EXPECT_EQ(*repairedCoolingCoilOutletNode, *heatingCoil.inletModelObject()->optionalCast<Node>());
}

TEST_F(EPModelFixture, ZoneHVACUnitVentilator_CanonicalizeRepairsContainedNodePath) {
  Model model;
  ZoneHVACUnitVentilator ventilator(model);
  FanConstantVolume supplyFan(model);
  CoilHeatingElectric heatingCoil(model);
  CoilCoolingWater coolingCoil(model);

  ASSERT_TRUE(ventilator.setSupplyAirFan(supplyFan));
  ASSERT_TRUE(ventilator.setHeatingCoil(heatingCoil));
  ASSERT_TRUE(ventilator.setCoolingCoil(coolingCoil));

  auto expectedMixedAir = ventilator.mixedAirNode();
  auto expectedVentilatorOutlet = ventilator.outletNode();
  ASSERT_TRUE(expectedMixedAir);
  ASSERT_TRUE(expectedVentilatorOutlet);

  Node rogueFanOutlet(model);
  ASSERT_TRUE(rogueFanOutlet.setName("Rogue Unit Ventilator Fan Outlet"));
  Node rogueCoolingOutlet(model);
  ASSERT_TRUE(rogueCoolingOutlet.setName("Rogue Unit Ventilator Cooling Outlet"));

  ASSERT_TRUE(supplyFan.setPointer(supplyFan.inletPort(), ventilator.inletNode()->handle()));
  ASSERT_TRUE(supplyFan.setPointer(supplyFan.outletPort(), rogueFanOutlet.handle()));
  ASSERT_TRUE(coolingCoil.setPointer(coolingCoil.airInletPort(), rogueFanOutlet.handle()));
  ASSERT_TRUE(coolingCoil.setPointer(coolingCoil.airOutletPort(), rogueCoolingOutlet.handle()));
  ASSERT_TRUE(heatingCoil.setPointer(heatingCoil.inletPort(), rogueCoolingOutlet.handle()));
  ASSERT_TRUE(heatingCoil.setPointer(heatingCoil.outletPort(), expectedMixedAir->handle()));

  auto report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);

  auto repairedMixedAirNode = ventilator.mixedAirNode();
  auto repairedFanOutletNode = ventilator.fanOutletNode();
  auto repairedCoolingCoilOutletNode = ventilator.coolingCoilOutletNode();
  auto repairedHeatingOutletNode = heatingCoil.outletModelObject()->optionalCast<Node>();
  ASSERT_TRUE(repairedMixedAirNode);
  ASSERT_TRUE(repairedFanOutletNode);
  ASSERT_TRUE(repairedCoolingCoilOutletNode);
  ASSERT_TRUE(repairedHeatingOutletNode);

  EXPECT_EQ(*expectedMixedAir, *repairedMixedAirNode);
  EXPECT_EQ("Rogue Unit Ventilator Fan Outlet", repairedFanOutletNode->nameString());
  EXPECT_EQ("Rogue Unit Ventilator Cooling Outlet", repairedCoolingCoilOutletNode->nameString());
  EXPECT_EQ(*repairedMixedAirNode, *supplyFan.inletModelObject()->optionalCast<Node>());
  EXPECT_EQ(*repairedFanOutletNode, *coolingCoil.airInletModelObject()->optionalCast<Node>());
  EXPECT_EQ(*repairedCoolingCoilOutletNode, *heatingCoil.inletModelObject()->optionalCast<Node>());
  EXPECT_EQ(*expectedVentilatorOutlet, *repairedHeatingOutletNode);
}

TEST_F(EPModelFixture, ZoneHVACUnitVentilator_BridgeTopologySurvivesReloadAndFurtherChanges) {
  const auto idfPath =
    openstudio::tempDir() / openstudio::toPath("epmodel-unit-ventilator-" + openstudio::removeBraces(openstudio::createUUID()) + ".idf");
  const ScopedFileRemoval removeIdf(idfPath);

  Model model;
  ThermalZone zone(model);
  PlantLoop chilledWaterLoop(model);
  ZoneHVACUnitVentilator ventilator(model);
  FanSystemModel fan(model);
  CoilCoolingWater coolingCoil(model);
  CoilHeatingElectric heatingCoil(model);

  ASSERT_TRUE(zone.setName("Unit Ventilator Bridge Zone"));
  ASSERT_TRUE(chilledWaterLoop.setName("Unit Ventilator Bridge Chilled Water Loop"));
  ASSERT_TRUE(ventilator.setName("Unit Ventilator Bridge"));
  ASSERT_TRUE(fan.setName("Unit Ventilator Bridge Fan"));
  ASSERT_TRUE(coolingCoil.setName("Unit Ventilator Bridge Cooling Coil"));
  ASSERT_TRUE(heatingCoil.setName("Unit Ventilator Bridge Electric Heating Coil"));
  ASSERT_TRUE(ventilator.setMaximumSupplyAirFlowRate(0.81));
  ASSERT_TRUE(ventilator.setMinimumOutdoorAirFlowRate(0.12));
  ASSERT_TRUE(ventilator.setMaximumOutdoorAirFlowRate(0.34));
  ASSERT_TRUE(fan.setDesignPressureRise(615.0));
  ASSERT_TRUE(ventilator.setSupplyAirFan(fan));
  ASSERT_TRUE(ventilator.setCoolingCoil(coolingCoil));
  ASSERT_TRUE(ventilator.setHeatingCoil(heatingCoil));
  ASSERT_TRUE(ventilator.addToThermalZone(zone));
  ASSERT_TRUE(chilledWaterLoop.addDemandBranchForComponent(coolingCoil));

  ASSERT_TRUE(ventilator.outdoorAirNode());
  ASSERT_TRUE(ventilator.exhaustAirNode());
  ASSERT_TRUE(ventilator.outdoorAirNode()->setName("Unit Ventilator Bridge Outdoor Air Node"));
  ASSERT_TRUE(ventilator.exhaustAirNode()->setName("Unit Ventilator Bridge Exhaust Air Node"));
  expectUnitVentilatorAirPath(ventilator, fan, coolingCoil, heatingCoil);
  ASSERT_TRUE(ventilator.thermalZone());
  EXPECT_EQ(zone.handle(), ventilator.thermalZone()->handle());
  ASSERT_TRUE(coolingCoil.plantLoop());
  EXPECT_EQ(chilledWaterLoop.handle(), coolingCoil.plantLoop()->handle());
  ASSERT_EQ(3u, ventilator.children().size());
  EXPECT_EQ(fan.handle(), ventilator.children()[0].handle());
  EXPECT_EQ(heatingCoil.handle(), ventilator.children()[1].handle());
  EXPECT_EQ(coolingCoil.handle(), ventilator.children()[2].handle());
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedZone = loadedModel->getConcreteModelObjectByName<ThermalZone>("Unit Ventilator Bridge Zone");
  auto loadedLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Unit Ventilator Bridge Chilled Water Loop");
  auto loadedVentilator = loadedModel->getConcreteModelObjectByName<ZoneHVACUnitVentilator>("Unit Ventilator Bridge");
  auto loadedFan = loadedModel->getConcreteModelObjectByName<FanSystemModel>("Unit Ventilator Bridge Fan");
  auto loadedCoolingCoil = loadedModel->getConcreteModelObjectByName<CoilCoolingWater>("Unit Ventilator Bridge Cooling Coil");
  auto loadedHeatingCoil = loadedModel->getConcreteModelObjectByName<CoilHeatingElectric>("Unit Ventilator Bridge Electric Heating Coil");
  ASSERT_TRUE(loadedZone);
  ASSERT_TRUE(loadedLoop);
  ASSERT_TRUE(loadedVentilator);
  ASSERT_TRUE(loadedFan);
  ASSERT_TRUE(loadedCoolingCoil);
  ASSERT_TRUE(loadedHeatingCoil);

  expectUnitVentilatorAirPath(*loadedVentilator, *loadedFan, *loadedCoolingCoil, *loadedHeatingCoil);
  EXPECT_DOUBLE_EQ(0.81, loadedVentilator->maximumSupplyAirFlowRate().value());
  EXPECT_DOUBLE_EQ(0.12, loadedVentilator->minimumOutdoorAirFlowRate().value());
  EXPECT_DOUBLE_EQ(0.34, loadedVentilator->maximumOutdoorAirFlowRate().value());
  EXPECT_DOUBLE_EQ(615.0, loadedFan->designPressureRise());
  ASSERT_TRUE(loadedVentilator->outdoorAirNode());
  ASSERT_TRUE(loadedVentilator->exhaustAirNode());
  EXPECT_EQ("Unit Ventilator Bridge Outdoor Air Node", loadedVentilator->outdoorAirNode()->nameString());
  EXPECT_EQ("Unit Ventilator Bridge Exhaust Air Node", loadedVentilator->exhaustAirNode()->nameString());
  ASSERT_TRUE(loadedVentilator->thermalZone());
  EXPECT_EQ(loadedZone->handle(), loadedVentilator->thermalZone()->handle());
  ASSERT_TRUE(loadedCoolingCoil->plantLoop());
  EXPECT_EQ(loadedLoop->handle(), loadedCoolingCoil->plantLoop()->handle());

  const auto coolingAirInlet = loadedCoolingCoil->airInletModelObject();
  const auto coolingAirOutlet = loadedCoolingCoil->airOutletModelObject();
  ASSERT_TRUE(coolingAirInlet);
  ASSERT_TRUE(coolingAirOutlet);
  ASSERT_TRUE(loadedLoop->removeDemandBranchWithComponent(*loadedCoolingCoil));
  EXPECT_FALSE(loadedCoolingCoil->plantLoop());
  EXPECT_EQ(coolingAirInlet->handle(), loadedCoolingCoil->airInletModelObject()->handle());
  EXPECT_EQ(coolingAirOutlet->handle(), loadedCoolingCoil->airOutletModelObject()->handle());
  ASSERT_TRUE(loadedLoop->addDemandBranchForComponent(*loadedCoolingCoil));
  ASSERT_TRUE(loadedCoolingCoil->plantLoop());
  EXPECT_EQ(loadedLoop->handle(), loadedCoolingCoil->plantLoop()->handle());

  loadedVentilator->removeFromThermalZone();
  EXPECT_FALSE(loadedVentilator->thermalZone());
  ASSERT_TRUE(loadedVentilator->addToThermalZone(*loadedZone));
  ASSERT_TRUE(loadedVentilator->thermalZone());
  EXPECT_EQ(loadedZone->handle(), loadedVentilator->thermalZone()->handle());

  CoilHeatingElectric replacementHeatingCoil(*loadedModel);
  ASSERT_TRUE(replacementHeatingCoil.setName("Unit Ventilator Bridge Replacement Electric Heating Coil"));
  ASSERT_TRUE(loadedVentilator->setHeatingCoil(replacementHeatingCoil));
  EXPECT_FALSE(loadedHeatingCoil->containingHVACComponent());
  EXPECT_FALSE(loadedHeatingCoil->remove().empty());
  expectUnitVentilatorAirPath(*loadedVentilator, *loadedFan, *loadedCoolingCoil, replacementHeatingCoil);
  ASSERT_TRUE(loadedVentilator->outdoorAirNode()->setName("Unit Ventilator Bridge Renamed Outdoor Air Node"));
  ASSERT_TRUE(loadedFan->setDesignPressureRise(625.0));
  ASSERT_TRUE(loadedModel->save(idfPath, true));

  auto reloadedModel = Model::load(idfPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedVentilator = reloadedModel->getConcreteModelObjectByName<ZoneHVACUnitVentilator>("Unit Ventilator Bridge");
  auto reloadedFan = reloadedModel->getConcreteModelObjectByName<FanSystemModel>("Unit Ventilator Bridge Fan");
  auto reloadedCoolingCoil = reloadedModel->getConcreteModelObjectByName<CoilCoolingWater>("Unit Ventilator Bridge Cooling Coil");
  auto reloadedHeatingCoil =
    reloadedModel->getConcreteModelObjectByName<CoilHeatingElectric>("Unit Ventilator Bridge Replacement Electric Heating Coil");
  ASSERT_TRUE(reloadedVentilator);
  ASSERT_TRUE(reloadedFan);
  ASSERT_TRUE(reloadedCoolingCoil);
  ASSERT_TRUE(reloadedHeatingCoil);
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<CoilHeatingElectric>("Unit Ventilator Bridge Electric Heating Coil"));
  expectUnitVentilatorAirPath(*reloadedVentilator, *reloadedFan, *reloadedCoolingCoil, *reloadedHeatingCoil);
  ASSERT_TRUE(reloadedCoolingCoil->plantLoop());
  EXPECT_EQ("Unit Ventilator Bridge Chilled Water Loop", reloadedCoolingCoil->plantLoop()->nameString());
  ASSERT_TRUE(reloadedVentilator->thermalZone());
  EXPECT_EQ("Unit Ventilator Bridge Zone", reloadedVentilator->thermalZone()->nameString());
  EXPECT_EQ("Unit Ventilator Bridge Renamed Outdoor Air Node", reloadedVentilator->outdoorAirNode()->nameString());
  EXPECT_DOUBLE_EQ(625.0, reloadedFan->designPressureRise());
}
