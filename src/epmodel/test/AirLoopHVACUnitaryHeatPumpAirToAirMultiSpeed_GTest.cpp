/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../StraightComponent/AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed.hpp"
#include "../StraightComponent/CoilCoolingDXMultiSpeed.hpp"
#include "../StraightComponent/CoilHeatingElectric.hpp"
#include "../StraightComponent/CoilHeatingElectricMultiStage.hpp"
#include "../StraightComponent/FanOnOff.hpp"
#include "../StraightComponent/Node.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../WaterToAirComponent/CoilHeatingWater.hpp"
#include <utilities/idd/IddEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_DefaultConstructor) {
  Model model;
  AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed unitary(model);
  EXPECT_EQ(AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::iddObjectType(), unitary.iddObject().type());
}

TEST_F(EPModelFixture, AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_RelationshipConstructorAndChildren) {
  Model model;
  FanOnOff fan(model);
  CoilHeatingElectricMultiStage heating(model);
  CoilCoolingDXMultiSpeed cooling(model);
  CoilHeatingElectric supplemental(model);

  AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed unitary(model, fan, heating, cooling, supplemental);

  EXPECT_EQ(fan.handle(), unitary.supplyAirFan().handle());
  EXPECT_EQ(heating.handle(), unitary.heatingCoil().handle());
  EXPECT_EQ(cooling.handle(), unitary.coolingCoil().handle());
  EXPECT_EQ(supplemental.handle(), unitary.supplementalHeatingCoil().handle());

  const auto children = unitary.children();
  ASSERT_EQ(4u, children.size());
  EXPECT_EQ(fan.handle(), children[0].handle());
  EXPECT_EQ(heating.handle(), children[1].handle());
  EXPECT_EQ(cooling.handle(), children[2].handle());
  EXPECT_EQ(supplemental.handle(), children[3].handle());
}

TEST_F(EPModelFixture, AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_ScalarAccessors_RoundTrip) {
  Model model;
  AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed unitary(model);

  EXPECT_TRUE(unitary.setSupplyAirFanPlacement("DrawThrough"));
  EXPECT_EQ("DrawThrough", unitary.supplyAirFanPlacement());

  EXPECT_TRUE(unitary.setDXHeatingCoilSizingRatio(1.15));
  EXPECT_DOUBLE_EQ(1.15, unitary.dXHeatingCoilSizingRatio());

  EXPECT_TRUE(unitary.setMaximumSupplyAirTemperaturefromSupplementalHeater(44.0));
  ASSERT_TRUE(unitary.maximumSupplyAirTemperaturefromSupplementalHeater());
  EXPECT_DOUBLE_EQ(44.0, unitary.maximumSupplyAirTemperaturefromSupplementalHeater().get());
  EXPECT_FALSE(unitary.isMaximumSupplyAirTemperaturefromSupplementalHeaterAutosized());
  unitary.autosizeMaximumSupplyAirTemperaturefromSupplementalHeater();
  EXPECT_TRUE(unitary.isMaximumSupplyAirTemperaturefromSupplementalHeaterAutosized());

  EXPECT_TRUE(unitary.setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(18.5));
  EXPECT_DOUBLE_EQ(18.5, unitary.maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation());

  EXPECT_TRUE(unitary.setAuxiliaryOnCycleElectricPower(12.0));
  EXPECT_DOUBLE_EQ(12.0, unitary.auxiliaryOnCycleElectricPower());

  EXPECT_TRUE(unitary.setAuxiliaryOffCycleElectricPower(8.0));
  EXPECT_DOUBLE_EQ(8.0, unitary.auxiliaryOffCycleElectricPower());

  EXPECT_TRUE(unitary.setDesignHeatRecoveryWaterFlowRate(0.001));
  EXPECT_DOUBLE_EQ(0.001, unitary.designHeatRecoveryWaterFlowRate());

  EXPECT_TRUE(unitary.setMaximumTemperatureforHeatRecovery(75.0));
  EXPECT_DOUBLE_EQ(75.0, unitary.maximumTemperatureforHeatRecovery());

  EXPECT_TRUE(unitary.setSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded(0.55));
  ASSERT_TRUE(unitary.supplyAirFlowRateWhenNoCoolingorHeatingisNeeded());
  EXPECT_DOUBLE_EQ(0.55, unitary.supplyAirFlowRateWhenNoCoolingorHeatingisNeeded().get());
  EXPECT_FALSE(unitary.isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized());
  unitary.autosizeSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
  EXPECT_TRUE(unitary.isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized());

  EXPECT_TRUE(unitary.setNumberofSpeedsforHeating(3));
  EXPECT_EQ(3, unitary.numberofSpeedsforHeating());

  EXPECT_TRUE(unitary.setNumberofSpeedsforCooling(4));
  EXPECT_EQ(4, unitary.numberofSpeedsforCooling());

  EXPECT_TRUE(unitary.setSpeed1SupplyAirFlowRateDuringHeatingOperation(0.7));
  ASSERT_TRUE(unitary.speed1SupplyAirFlowRateDuringHeatingOperation());
  EXPECT_DOUBLE_EQ(0.7, unitary.speed1SupplyAirFlowRateDuringHeatingOperation().get());
  EXPECT_FALSE(unitary.isSpeed1SupplyAirFlowRateDuringHeatingOperationAutosized());
  unitary.autosizeSpeed1SupplyAirFlowRateDuringHeatingOperation();
  EXPECT_TRUE(unitary.isSpeed1SupplyAirFlowRateDuringHeatingOperationAutosized());

  EXPECT_TRUE(unitary.setSpeed2SupplyAirFlowRateDuringHeatingOperation(0.8));
  ASSERT_TRUE(unitary.speed2SupplyAirFlowRateDuringHeatingOperation());
  EXPECT_DOUBLE_EQ(0.8, unitary.speed2SupplyAirFlowRateDuringHeatingOperation().get());
  EXPECT_FALSE(unitary.isSpeed2SupplyAirFlowRateDuringHeatingOperationAutosized());
  unitary.autosizeSpeed2SupplyAirFlowRateDuringHeatingOperation();
  EXPECT_TRUE(unitary.isSpeed2SupplyAirFlowRateDuringHeatingOperationAutosized());

  EXPECT_TRUE(unitary.setSpeed3SupplyAirFlowRateDuringHeatingOperation(0.9));
  ASSERT_TRUE(unitary.speed3SupplyAirFlowRateDuringHeatingOperation());
  EXPECT_DOUBLE_EQ(0.9, unitary.speed3SupplyAirFlowRateDuringHeatingOperation().get());
  EXPECT_FALSE(unitary.isSpeed3SupplyAirFlowRateDuringHeatingOperationAutosized());
  unitary.autosizeSpeed3SupplyAirFlowRateDuringHeatingOperation();
  EXPECT_TRUE(unitary.isSpeed3SupplyAirFlowRateDuringHeatingOperationAutosized());

  EXPECT_TRUE(unitary.setSpeed4SupplyAirFlowRateDuringHeatingOperation(1.0));
  ASSERT_TRUE(unitary.speed4SupplyAirFlowRateDuringHeatingOperation());
  EXPECT_DOUBLE_EQ(1.0, unitary.speed4SupplyAirFlowRateDuringHeatingOperation().get());
  EXPECT_FALSE(unitary.isSpeed4SupplyAirFlowRateDuringHeatingOperationAutosized());
  unitary.autosizeSpeed4SupplyAirFlowRateDuringHeatingOperation();
  EXPECT_TRUE(unitary.isSpeed4SupplyAirFlowRateDuringHeatingOperationAutosized());

  EXPECT_TRUE(unitary.setSpeed1SupplyAirFlowRateDuringCoolingOperation(0.75));
  ASSERT_TRUE(unitary.speed1SupplyAirFlowRateDuringCoolingOperation());
  EXPECT_DOUBLE_EQ(0.75, unitary.speed1SupplyAirFlowRateDuringCoolingOperation().get());
  EXPECT_FALSE(unitary.isSpeed1SupplyAirFlowRateDuringCoolingOperationAutosized());
  unitary.autosizeSpeed1SupplyAirFlowRateDuringCoolingOperation();
  EXPECT_TRUE(unitary.isSpeed1SupplyAirFlowRateDuringCoolingOperationAutosized());

  EXPECT_TRUE(unitary.setSpeed2SupplyAirFlowRateDuringCoolingOperation(0.85));
  ASSERT_TRUE(unitary.speed2SupplyAirFlowRateDuringCoolingOperation());
  EXPECT_DOUBLE_EQ(0.85, unitary.speed2SupplyAirFlowRateDuringCoolingOperation().get());
  EXPECT_FALSE(unitary.isSpeed2SupplyAirFlowRateDuringCoolingOperationAutosized());
  unitary.autosizeSpeed2SupplyAirFlowRateDuringCoolingOperation();
  EXPECT_TRUE(unitary.isSpeed2SupplyAirFlowRateDuringCoolingOperationAutosized());

  EXPECT_TRUE(unitary.setSpeed3SupplyAirFlowRateDuringCoolingOperation(0.95));
  ASSERT_TRUE(unitary.speed3SupplyAirFlowRateDuringCoolingOperation());
  EXPECT_DOUBLE_EQ(0.95, unitary.speed3SupplyAirFlowRateDuringCoolingOperation().get());
  EXPECT_FALSE(unitary.isSpeed3SupplyAirFlowRateDuringCoolingOperationAutosized());
  unitary.autosizeSpeed3SupplyAirFlowRateDuringCoolingOperation();
  EXPECT_TRUE(unitary.isSpeed3SupplyAirFlowRateDuringCoolingOperationAutosized());

  EXPECT_TRUE(unitary.setSpeed4SupplyAirFlowRateDuringCoolingOperation(1.05));
  ASSERT_TRUE(unitary.speed4SupplyAirFlowRateDuringCoolingOperation());
  EXPECT_DOUBLE_EQ(1.05, unitary.speed4SupplyAirFlowRateDuringCoolingOperation().get());
  EXPECT_FALSE(unitary.isSpeed4SupplyAirFlowRateDuringCoolingOperationAutosized());
  unitary.autosizeSpeed4SupplyAirFlowRateDuringCoolingOperation();
  EXPECT_TRUE(unitary.isSpeed4SupplyAirFlowRateDuringCoolingOperationAutosized());
}

TEST_F(EPModelFixture, AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_RelationshipAccessors_RoundTrip) {
  Model model;
  AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed unitary(model);
  ScheduleConstant availability(model);
  ScheduleConstant fanMode(model);
  ThermalZone zone(model);
  FanOnOff fan(model);
  CoilHeatingElectricMultiStage heating(model);
  CoilCoolingDXMultiSpeed cooling(model);
  CoilHeatingElectric supplemental(model);

  ASSERT_TRUE(availability.setValue(0.8));
  ASSERT_TRUE(fanMode.setValue(1.0));

  EXPECT_TRUE(unitary.setAvailabilitySchedule(availability));
  ASSERT_TRUE(unitary.availabilitySchedule());
  EXPECT_EQ(availability, unitary.availabilitySchedule().get());
  unitary.resetAvailabilitySchedule();
  EXPECT_FALSE(unitary.availabilitySchedule());

  EXPECT_TRUE(unitary.setControllingZoneorThermostatLocation(zone));
  ASSERT_TRUE(unitary.controllingZoneorThermostatLocation());
  EXPECT_EQ(zone, unitary.controllingZoneorThermostatLocation().get());
  unitary.resetControllingZoneorThermostatLocation();
  EXPECT_FALSE(unitary.controllingZoneorThermostatLocation());

  EXPECT_TRUE(unitary.setSupplyAirFan(fan));
  EXPECT_EQ(fan, unitary.supplyAirFan());

  EXPECT_TRUE(unitary.setSupplyAirFanOperatingModeSchedule(fanMode));
  EXPECT_EQ(fanMode, unitary.supplyAirFanOperatingModeSchedule());

  EXPECT_TRUE(unitary.setHeatingCoil(heating));
  EXPECT_EQ(heating, unitary.heatingCoil());

  EXPECT_TRUE(unitary.setCoolingCoil(cooling));
  EXPECT_EQ(cooling, unitary.coolingCoil());

  EXPECT_TRUE(unitary.setSupplementalHeatingCoil(supplemental));
  EXPECT_EQ(supplemental, unitary.supplementalHeatingCoil());
}

TEST_F(EPModelFixture, AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_AddToNodeSupplyOnly) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed unitary(model);

  auto supplyInlet = airLoop.supplyInletNode();
  EXPECT_TRUE(unitary.addToNode(supplyInlet));

  const auto supplyComponents = airLoop.supplyComponents(openstudio::IddObjectType::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeed);
  ASSERT_EQ(1u, supplyComponents.size());
  EXPECT_EQ(unitary, supplyComponents.front());

  auto loop = unitary.airLoopHVAC();
  ASSERT_TRUE(loop);
  EXPECT_EQ(airLoop, *loop);
}

TEST_F(EPModelFixture, AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_AddToNodeRejectsDemand) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed unitary(model);

  auto demandInlet = airLoop.demandInletNode();
  EXPECT_FALSE(unitary.addToNode(demandInlet));
  EXPECT_FALSE(unitary.airLoopHVAC());
}

TEST_F(EPModelFixture, AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_TopologyAndInternalNodes) {
  Model model;
  AirLoopHVAC airLoop(model);
  FanOnOff fan(model);
  CoilHeatingElectricMultiStage heating(model);
  CoilCoolingDXMultiSpeed cooling(model);
  CoilHeatingWater supplemental(model);
  AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed unitary(model);

  ASSERT_TRUE(unitary.setSupplyAirFanPlacement("DrawThrough"));
  ASSERT_TRUE(unitary.setSupplyAirFan(fan));
  ASSERT_TRUE(unitary.setHeatingCoil(heating));
  ASSERT_TRUE(unitary.setCoolingCoil(cooling));
  ASSERT_TRUE(unitary.setSupplementalHeatingCoil(supplemental));
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
  auto supplementalInlet = supplemental.airInletModelObject()->optionalCast<Node>();
  auto supplementalOutlet = supplemental.airOutletModelObject()->optionalCast<Node>();
  ASSERT_TRUE(unitaryInlet);
  ASSERT_TRUE(unitaryOutlet);
  ASSERT_TRUE(fanInlet);
  ASSERT_TRUE(fanOutlet);
  ASSERT_TRUE(coolingInlet);
  ASSERT_TRUE(coolingOutlet);
  ASSERT_TRUE(heatingInlet);
  ASSERT_TRUE(heatingOutlet);
  ASSERT_TRUE(supplementalInlet);
  ASSERT_TRUE(supplementalOutlet);
  ASSERT_TRUE(unitary.fanOutletNode());
  ASSERT_TRUE(unitary.coolingCoilOutletNode());
  ASSERT_TRUE(unitary.heatingCoilOutletNode());

  EXPECT_EQ(*unitaryInlet, *coolingInlet);
  EXPECT_EQ(*unitary.coolingCoilOutletNode(), *coolingOutlet);
  EXPECT_EQ(*unitary.coolingCoilOutletNode(), *heatingInlet);
  EXPECT_EQ(*unitary.heatingCoilOutletNode(), *heatingOutlet);
  EXPECT_EQ(*unitary.heatingCoilOutletNode(), *fanInlet);
  EXPECT_EQ(*unitary.fanOutletNode(), *fanOutlet);
  EXPECT_EQ(*unitary.fanOutletNode(), *supplementalInlet);
  EXPECT_EQ(*unitaryOutlet, *supplementalOutlet);
}

TEST_F(EPModelFixture, AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_NodeRolesFollowBlowThroughOrder) {
  Model model;
  FanOnOff fan(model);
  CoilHeatingElectricMultiStage heating(model);
  CoilCoolingDXMultiSpeed cooling(model);
  CoilHeatingElectric supplemental(model);
  AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed unitary(model);

  ASSERT_TRUE(unitary.setSupplyAirFanPlacement("BlowThrough"));
  ASSERT_TRUE(unitary.setSupplyAirFan(fan));
  ASSERT_TRUE(unitary.setHeatingCoil(heating));
  ASSERT_TRUE(unitary.setCoolingCoil(cooling));
  ASSERT_TRUE(unitary.setSupplementalHeatingCoil(supplemental));

  ASSERT_TRUE(unitary.fanOutletNode());
  ASSERT_TRUE(unitary.coolingCoilOutletNode());
  ASSERT_TRUE(unitary.heatingCoilOutletNode());
  ASSERT_TRUE(unitary.outletModelObject());

  EXPECT_EQ(*unitary.fanOutletNode(), *cooling.inletModelObject()->optionalCast<Node>());
  EXPECT_EQ(*unitary.coolingCoilOutletNode(), *heating.inletModelObject()->optionalCast<Node>());
  EXPECT_EQ(*unitary.heatingCoilOutletNode(), *supplemental.inletModelObject()->optionalCast<Node>());
  EXPECT_EQ(*unitary.outletModelObject()->optionalCast<Node>(), *supplemental.outletModelObject()->optionalCast<Node>());
}

TEST_F(EPModelFixture, AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_InternalNodeRenamesSurviveCanonicalize) {
  Model model;
  FanOnOff fan(model);
  CoilHeatingElectricMultiStage heating(model);
  CoilCoolingDXMultiSpeed cooling(model);
  CoilHeatingElectric supplemental(model);
  AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed unitary(model);

  ASSERT_TRUE(unitary.setSupplyAirFanPlacement("DrawThrough"));
  ASSERT_TRUE(unitary.setSupplyAirFan(fan));
  ASSERT_TRUE(unitary.setHeatingCoil(heating));
  ASSERT_TRUE(unitary.setCoolingCoil(cooling));
  ASSERT_TRUE(unitary.setSupplementalHeatingCoil(supplemental));

  ASSERT_TRUE(unitary.fanOutletNode());
  ASSERT_TRUE(unitary.coolingCoilOutletNode());
  ASSERT_TRUE(unitary.heatingCoilOutletNode());
  ASSERT_TRUE(unitary.fanOutletNode()->setName("Custom MultiSpeed Fan Outlet"));
  ASSERT_TRUE(unitary.coolingCoilOutletNode()->setName("Custom MultiSpeed Cooling Outlet"));
  ASSERT_TRUE(unitary.heatingCoilOutletNode()->setName("Custom MultiSpeed Heating Outlet"));

  auto report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);

  ASSERT_TRUE(unitary.fanOutletNode());
  ASSERT_TRUE(unitary.coolingCoilOutletNode());
  ASSERT_TRUE(unitary.heatingCoilOutletNode());
  EXPECT_EQ("Custom MultiSpeed Fan Outlet", unitary.fanOutletNode()->nameString());
  EXPECT_EQ("Custom MultiSpeed Cooling Outlet", unitary.coolingCoilOutletNode()->nameString());
  EXPECT_EQ("Custom MultiSpeed Heating Outlet", unitary.heatingCoilOutletNode()->nameString());
}

TEST_F(EPModelFixture, AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_CanonicalizeRepairsContainedNodePath) {
  Model model;
  FanOnOff fan(model);
  CoilHeatingElectricMultiStage heating(model);
  CoilCoolingDXMultiSpeed cooling(model);
  CoilHeatingElectric supplemental(model);
  AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed unitary(model);

  ASSERT_TRUE(unitary.setSupplyAirFanPlacement("DrawThrough"));
  ASSERT_TRUE(unitary.setSupplyAirFan(fan));
  ASSERT_TRUE(unitary.setHeatingCoil(heating));
  ASSERT_TRUE(unitary.setCoolingCoil(cooling));
  ASSERT_TRUE(unitary.setSupplementalHeatingCoil(supplemental));

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
  ASSERT_TRUE(supplemental.setPointer(supplemental.inletPort(), unitaryInlet->handle()));

  auto report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);

  ASSERT_TRUE(unitary.coolingCoilOutletNode());
  ASSERT_TRUE(unitary.heatingCoilOutletNode());
  ASSERT_TRUE(unitary.fanOutletNode());
  EXPECT_EQ(*expectedCoolingOutlet, *unitary.coolingCoilOutletNode());
  EXPECT_EQ(*expectedHeatingOutlet, *unitary.heatingCoilOutletNode());
  EXPECT_EQ(*expectedFanOutlet, *unitary.fanOutletNode());
}
