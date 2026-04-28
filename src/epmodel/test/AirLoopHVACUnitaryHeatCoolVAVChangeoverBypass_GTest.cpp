/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../StraightComponent/AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass.hpp"
#include "../StraightComponent/CoilCoolingDXSingleSpeed.hpp"
#include "../StraightComponent/CoilHeatingElectric.hpp"
#include "../StraightComponent/FanConstantVolume.hpp"
#include "../StraightComponent/Node.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_DefaultConstructor) {
  Model model;
  AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass unitary(model);
  EXPECT_EQ(AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::iddObjectType(), unitary.iddObject().type());
}

TEST_F(EPModelFixture, AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_RelationshipConstructorAndChildren) {
  Model model;
  FanConstantVolume fan(model);
  CoilCoolingDXSingleSpeed cooling(model);
  CoilHeatingElectric heating(model);

  AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass unitary(model, fan, cooling, heating);

  EXPECT_EQ(fan.handle(), unitary.supplyAirFan().handle());
  EXPECT_EQ(cooling.handle(), unitary.coolingCoil().handle());
  EXPECT_EQ(heating.handle(), unitary.heatingCoil().handle());

  const auto children = unitary.children();
  ASSERT_EQ(3u, children.size());
  EXPECT_EQ(fan.handle(), children[0].handle());
  EXPECT_EQ(cooling.handle(), children[1].handle());
  EXPECT_EQ(heating.handle(), children[2].handle());
}

TEST_F(EPModelFixture, AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_ScalarAccessors_RoundTrip) {
  Model model;
  AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass unitary(model);

  EXPECT_TRUE(unitary.setSystemAirFlowRateDuringCoolingOperation(1.1));
  ASSERT_TRUE(unitary.systemAirFlowRateDuringCoolingOperation());
  EXPECT_DOUBLE_EQ(1.1, unitary.systemAirFlowRateDuringCoolingOperation().get());
  EXPECT_FALSE(unitary.isSystemAirFlowRateDuringCoolingOperationAutosized());
  unitary.autosizeSystemAirFlowRateDuringCoolingOperation();
  EXPECT_TRUE(unitary.isSystemAirFlowRateDuringCoolingOperationAutosized());

  EXPECT_TRUE(unitary.setSystemAirFlowRateDuringHeatingOperation(1.2));
  ASSERT_TRUE(unitary.systemAirFlowRateDuringHeatingOperation());
  EXPECT_DOUBLE_EQ(1.2, unitary.systemAirFlowRateDuringHeatingOperation().get());
  EXPECT_FALSE(unitary.isSystemAirFlowRateDuringHeatingOperationAutosized());
  unitary.autosizeSystemAirFlowRateDuringHeatingOperation();
  EXPECT_TRUE(unitary.isSystemAirFlowRateDuringHeatingOperationAutosized());

  EXPECT_TRUE(unitary.setSystemAirFlowRateWhenNoCoolingorHeatingisNeeded(0.7));
  ASSERT_TRUE(unitary.systemAirFlowRateWhenNoCoolingorHeatingisNeeded());
  EXPECT_DOUBLE_EQ(0.7, unitary.systemAirFlowRateWhenNoCoolingorHeatingisNeeded().get());
  EXPECT_FALSE(unitary.isSystemAirFlowRateWhenNoCoolingorHeatingisNeededAutosized());
  unitary.autosizeSystemAirFlowRateWhenNoCoolingorHeatingisNeeded();
  EXPECT_TRUE(unitary.isSystemAirFlowRateWhenNoCoolingorHeatingisNeededAutosized());

  EXPECT_TRUE(unitary.setOutdoorAirFlowRateDuringCoolingOperation(0.3));
  ASSERT_TRUE(unitary.outdoorAirFlowRateDuringCoolingOperation());
  EXPECT_DOUBLE_EQ(0.3, unitary.outdoorAirFlowRateDuringCoolingOperation().get());
  EXPECT_FALSE(unitary.isOutdoorAirFlowRateDuringCoolingOperationAutosized());
  unitary.autosizeOutdoorAirFlowRateDuringCoolingOperation();
  EXPECT_TRUE(unitary.isOutdoorAirFlowRateDuringCoolingOperationAutosized());

  EXPECT_TRUE(unitary.setOutdoorAirFlowRateDuringHeatingOperation(0.35));
  ASSERT_TRUE(unitary.outdoorAirFlowRateDuringHeatingOperation());
  EXPECT_DOUBLE_EQ(0.35, unitary.outdoorAirFlowRateDuringHeatingOperation().get());
  EXPECT_FALSE(unitary.isOutdoorAirFlowRateDuringHeatingOperationAutosized());
  unitary.autosizeOutdoorAirFlowRateDuringHeatingOperation();
  EXPECT_TRUE(unitary.isOutdoorAirFlowRateDuringHeatingOperationAutosized());

  EXPECT_TRUE(unitary.setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(0.2));
  ASSERT_TRUE(unitary.outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded());
  EXPECT_DOUBLE_EQ(0.2, unitary.outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded().get());
  EXPECT_FALSE(unitary.isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized());
  unitary.autosizeOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
  EXPECT_TRUE(unitary.isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized());

  EXPECT_TRUE(unitary.setSupplyAirFanPlacement("DrawThrough"));
  EXPECT_EQ("DrawThrough", unitary.supplyAirFanPlacement());

  EXPECT_TRUE(unitary.setPriorityControlMode("ZonePriority"));
  EXPECT_EQ("ZonePriority", unitary.priorityControlMode());

  EXPECT_TRUE(unitary.setMinimumOutletAirTemperatureDuringCoolingOperation(9.5));
  EXPECT_DOUBLE_EQ(9.5, unitary.minimumOutletAirTemperatureDuringCoolingOperation());

  EXPECT_TRUE(unitary.setMaximumOutletAirTemperatureDuringHeatingOperation(48.0));
  EXPECT_DOUBLE_EQ(48.0, unitary.maximumOutletAirTemperatureDuringHeatingOperation());

  EXPECT_TRUE(unitary.setDehumidificationControlType("CoolReheat"));
  EXPECT_EQ("CoolReheat", unitary.dehumidificationControlType());

  EXPECT_TRUE(unitary.setMinimumRuntimeBeforeOperatingModeChange(0.25));
  EXPECT_DOUBLE_EQ(0.25, unitary.minimumRuntimeBeforeOperatingModeChange());
}

TEST_F(EPModelFixture, AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_RelationshipAccessors_RoundTrip) {
  Model model;
  AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass unitary(model);
  ScheduleConstant availability(model);
  ScheduleConstant oaMultiplier(model);
  ScheduleConstant fanMode(model);
  FanConstantVolume fan(model);
  CoilCoolingDXSingleSpeed cooling(model);
  CoilHeatingElectric heating(model);

  ASSERT_TRUE(availability.setValue(0.9));
  ASSERT_TRUE(oaMultiplier.setValue(0.6));
  ASSERT_TRUE(fanMode.setValue(1.0));

  EXPECT_TRUE(unitary.setAvailabilitySchedule(availability));
  ASSERT_TRUE(unitary.availabilitySchedule());
  EXPECT_EQ(availability, unitary.availabilitySchedule().get());
  unitary.resetAvailabilitySchedule();
  EXPECT_FALSE(unitary.availabilitySchedule());

  EXPECT_TRUE(unitary.setOutdoorAirFlowRateMultiplierSchedule(oaMultiplier));
  ASSERT_TRUE(unitary.outdoorAirFlowRateMultiplierSchedule());
  EXPECT_EQ(oaMultiplier, unitary.outdoorAirFlowRateMultiplierSchedule().get());
  unitary.resetOutdoorAirFlowRateMultiplierSchedule();
  EXPECT_FALSE(unitary.outdoorAirFlowRateMultiplierSchedule());

  EXPECT_TRUE(unitary.setSupplyAirFan(fan));
  EXPECT_EQ(fan, unitary.supplyAirFan());

  EXPECT_TRUE(unitary.setSupplyAirFanOperatingModeSchedule(fanMode));
  ASSERT_TRUE(unitary.supplyAirFanOperatingModeSchedule());
  EXPECT_EQ(fanMode, unitary.supplyAirFanOperatingModeSchedule().get());
  unitary.resetSupplyAirFanOperatingModeSchedule();
  EXPECT_FALSE(unitary.supplyAirFanOperatingModeSchedule());

  EXPECT_TRUE(unitary.setCoolingCoil(cooling));
  EXPECT_EQ(cooling, unitary.coolingCoil());

  EXPECT_TRUE(unitary.setHeatingCoil(heating));
  EXPECT_EQ(heating, unitary.heatingCoil());
}

TEST_F(EPModelFixture, AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_AddToNodeSupplyOnly) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass supplyUnitary(model);
  AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass demandUnitary(model);

  auto supplyInletNode = airLoop.supplyInletNode();
  EXPECT_TRUE(supplyUnitary.addToNode(supplyInletNode));
  ASSERT_TRUE(supplyUnitary.inletModelObject());
  EXPECT_EQ(supplyInletNode, supplyUnitary.inletModelObject()->cast<Node>());
  EXPECT_TRUE(supplyUnitary.outletModelObject());

  auto demandInletNode = airLoop.demandInletNode();
  EXPECT_FALSE(demandUnitary.addToNode(demandInletNode));
  EXPECT_FALSE(demandUnitary.airLoopHVAC());
}

TEST_F(EPModelFixture, AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_TopologyAndInternalNodes) {
  Model model;
  AirLoopHVAC airLoop(model);
  FanConstantVolume fan(model);
  CoilCoolingDXSingleSpeed cooling(model);
  CoilHeatingElectric heating(model);
  AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass unitary(model);

  ASSERT_TRUE(unitary.setSupplyAirFanPlacement("DrawThrough"));
  ASSERT_TRUE(unitary.setSupplyAirFan(fan));
  ASSERT_TRUE(unitary.setCoolingCoil(cooling));
  ASSERT_TRUE(unitary.setHeatingCoil(heating));
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(unitary.addToNode(supplyInletNode));

  auto unitaryInlet = unitary.inletModelObject()->optionalCast<Node>();
  auto unitaryOutlet = unitary.outletModelObject()->optionalCast<Node>();
  auto fanInlet = fan.inletModelObject()->optionalCast<Node>();
  auto fanOutlet = fan.outletModelObject()->optionalCast<Node>();
  auto coolingInlet = cooling.inletModelObject()->optionalCast<Node>();
  auto coolingOutlet = cooling.outletModelObject()->optionalCast<Node>();
  auto heatingInlet = heating.inletModelObject()->optionalCast<Node>();
  auto heatingOutlet = heating.outletModelObject()->optionalCast<Node>();
  ASSERT_TRUE(unitaryInlet);
  ASSERT_TRUE(unitaryOutlet);
  ASSERT_TRUE(fanInlet);
  ASSERT_TRUE(fanOutlet);
  ASSERT_TRUE(coolingInlet);
  ASSERT_TRUE(coolingOutlet);
  ASSERT_TRUE(heatingInlet);
  ASSERT_TRUE(heatingOutlet);
  ASSERT_TRUE(unitary.fanOutletNode());
  ASSERT_TRUE(unitary.coolingCoilOutletNode());
  ASSERT_TRUE(unitary.heatingCoilOutletNode());

  EXPECT_EQ(*unitaryInlet, *coolingInlet);
  EXPECT_EQ(*unitary.coolingCoilOutletNode(), *coolingOutlet);
  EXPECT_EQ(*unitary.coolingCoilOutletNode(), *heatingInlet);
  EXPECT_EQ(*unitary.heatingCoilOutletNode(), *heatingOutlet);
  EXPECT_EQ(*unitary.heatingCoilOutletNode(), *fanInlet);
  EXPECT_EQ(*unitary.fanOutletNode(), *fanOutlet);
  EXPECT_EQ(*unitaryOutlet, *fanOutlet);
}

TEST_F(EPModelFixture, AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_NodeRolesFollowBlowThroughOrder) {
  Model model;
  FanConstantVolume fan(model);
  CoilCoolingDXSingleSpeed cooling(model);
  CoilHeatingElectric heating(model);
  AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass unitary(model);

  ASSERT_TRUE(unitary.setSupplyAirFanPlacement("BlowThrough"));
  ASSERT_TRUE(unitary.setSupplyAirFan(fan));
  ASSERT_TRUE(unitary.setCoolingCoil(cooling));
  ASSERT_TRUE(unitary.setHeatingCoil(heating));

  ASSERT_TRUE(unitary.fanOutletNode());
  ASSERT_TRUE(unitary.coolingCoilOutletNode());
  ASSERT_TRUE(unitary.heatingCoilOutletNode());
  ASSERT_TRUE(unitary.outletModelObject());

  EXPECT_EQ(*unitary.fanOutletNode(), *cooling.inletModelObject()->optionalCast<Node>());
  EXPECT_EQ(*unitary.coolingCoilOutletNode(), *heating.inletModelObject()->optionalCast<Node>());
  EXPECT_EQ(*unitary.heatingCoilOutletNode(), *unitary.outletModelObject()->optionalCast<Node>());
}

TEST_F(EPModelFixture, AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_InternalNodeRenamesSurviveCanonicalize) {
  Model model;
  FanConstantVolume fan(model);
  CoilCoolingDXSingleSpeed cooling(model);
  CoilHeatingElectric heating(model);
  AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass unitary(model);

  ASSERT_TRUE(unitary.setSupplyAirFanPlacement("DrawThrough"));
  ASSERT_TRUE(unitary.setSupplyAirFan(fan));
  ASSERT_TRUE(unitary.setCoolingCoil(cooling));
  ASSERT_TRUE(unitary.setHeatingCoil(heating));

  ASSERT_TRUE(unitary.fanOutletNode());
  ASSERT_TRUE(unitary.coolingCoilOutletNode());
  ASSERT_TRUE(unitary.heatingCoilOutletNode());
  ASSERT_TRUE(unitary.fanOutletNode()->setName("Custom Changeover Fan Outlet"));
  ASSERT_TRUE(unitary.coolingCoilOutletNode()->setName("Custom Changeover Cooling Outlet"));
  ASSERT_TRUE(unitary.heatingCoilOutletNode()->setName("Custom Changeover Heating Outlet"));

  auto report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);

  ASSERT_TRUE(unitary.fanOutletNode());
  ASSERT_TRUE(unitary.coolingCoilOutletNode());
  ASSERT_TRUE(unitary.heatingCoilOutletNode());
  EXPECT_EQ("Custom Changeover Fan Outlet", unitary.fanOutletNode()->nameString());
  EXPECT_EQ("Custom Changeover Cooling Outlet", unitary.coolingCoilOutletNode()->nameString());
  EXPECT_EQ("Custom Changeover Heating Outlet", unitary.heatingCoilOutletNode()->nameString());
}

TEST_F(EPModelFixture, AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_CanonicalizeRepairsContainedNodePath) {
  Model model;
  FanConstantVolume fan(model);
  CoilCoolingDXSingleSpeed cooling(model);
  CoilHeatingElectric heating(model);
  AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass unitary(model);

  ASSERT_TRUE(unitary.setSupplyAirFanPlacement("DrawThrough"));
  ASSERT_TRUE(unitary.setSupplyAirFan(fan));
  ASSERT_TRUE(unitary.setCoolingCoil(cooling));
  ASSERT_TRUE(unitary.setHeatingCoil(heating));

  auto expectedCoolingOutlet = unitary.coolingCoilOutletNode();
  auto expectedHeatingOutlet = unitary.heatingCoilOutletNode();
  auto expectedFanOutlet = unitary.fanOutletNode();
  ASSERT_TRUE(expectedCoolingOutlet);
  ASSERT_TRUE(expectedHeatingOutlet);
  ASSERT_TRUE(expectedFanOutlet);

  auto unitaryInlet = unitary.inletModelObject()->optionalCast<Node>();
  auto unitaryOutlet = unitary.outletModelObject()->optionalCast<Node>();
  ASSERT_TRUE(unitaryInlet);
  ASSERT_TRUE(unitaryOutlet);
  ASSERT_TRUE(cooling.setPointer(cooling.outletPort(), unitaryInlet->handle()));
  ASSERT_TRUE(heating.setPointer(heating.inletPort(), unitaryInlet->handle()));
  ASSERT_TRUE(heating.setPointer(heating.outletPort(), unitaryOutlet->handle()));
  ASSERT_TRUE(fan.setPointer(fan.inletPort(), unitaryOutlet->handle()));
  ASSERT_TRUE(fan.setPointer(fan.outletPort(), unitaryInlet->handle()));

  auto report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);

  ASSERT_TRUE(unitary.coolingCoilOutletNode());
  ASSERT_TRUE(unitary.heatingCoilOutletNode());
  ASSERT_TRUE(unitary.fanOutletNode());
  EXPECT_EQ(*expectedCoolingOutlet, *unitary.coolingCoilOutletNode());
  EXPECT_EQ(*expectedHeatingOutlet, *unitary.heatingCoilOutletNode());
  EXPECT_EQ(*expectedFanOutlet, *unitary.fanOutletNode());
}
