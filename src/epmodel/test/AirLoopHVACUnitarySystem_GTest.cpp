/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../StraightComponent/CoilCoolingDXSingleSpeed.hpp"
#include "../StraightComponent/CoilHeatingElectric.hpp"
#include "../StraightComponent/FanConstantVolume.hpp"
#include "../StraightComponent/Node.hpp"
#include "../ZoneHVACComponent/AirLoopHVACUnitarySystem.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirLoopHVACUnitarySystem_DefaultConstructor) {
  Model model;
  AirLoopHVACUnitarySystem unitary(model);
  EXPECT_EQ(AirLoopHVACUnitarySystem::iddObjectType(), unitary.iddObject().type());
}

TEST_F(EPModelFixture, AirLoopHVACUnitarySystem_ScalarAccessors_RoundTrip) {
  Model model;
  AirLoopHVACUnitarySystem unitary(model);

  EXPECT_TRUE(unitary.setControlType("Load"));
  EXPECT_EQ("Load", unitary.controlType());

  EXPECT_TRUE(unitary.setUseDOASDXCoolingCoil(true));
  EXPECT_TRUE(unitary.useDOASDXCoolingCoil());
  EXPECT_FALSE(unitary.isUseDOASDXCoolingCoilDefaulted());

  EXPECT_TRUE(unitary.setDOASDXCoolingCoilLeavingMinimumAirTemperature(6.2));
  EXPECT_DOUBLE_EQ(6.2, unitary.dOASDXCoolingCoilLeavingMinimumAirTemperature());
  EXPECT_FALSE(unitary.isDOASDXCoolingCoilLeavingMinimumAirTemperatureAutosized());
  unitary.autosizeDOASDXCoolingCoilLeavingMinimumAirTemperature();
  EXPECT_TRUE(unitary.isDOASDXCoolingCoilLeavingMinimumAirTemperatureAutosized());

  EXPECT_TRUE(unitary.setSupplyAirFlowRateMethodDuringCoolingOperation("SupplyAirFlowRate"));
  EXPECT_EQ("SupplyAirFlowRate", unitary.supplyAirFlowRateMethodDuringCoolingOperation());
  EXPECT_TRUE(unitary.setSupplyAirFlowRateDuringCoolingOperation(1.1));
  ASSERT_TRUE(unitary.supplyAirFlowRateDuringCoolingOperation());
  EXPECT_DOUBLE_EQ(1.1, unitary.supplyAirFlowRateDuringCoolingOperation().get());
  unitary.autosizeSupplyAirFlowRateDuringCoolingOperation();
  EXPECT_TRUE(unitary.isSupplyAirFlowRateDuringCoolingOperationAutosized());

  EXPECT_TRUE(unitary.setSupplyAirFlowRateMethodWhenNoCoolingorHeatingisRequired("SupplyAirFlowRate"));
  EXPECT_TRUE(unitary.setSupplyAirFlowRateWhenNoCoolingorHeatingisRequired(0.8));
  ASSERT_TRUE(unitary.supplyAirFlowRateWhenNoCoolingorHeatingisRequired());
  EXPECT_DOUBLE_EQ(0.8, unitary.supplyAirFlowRateWhenNoCoolingorHeatingisRequired().get());
  unitary.autosizeSupplyAirFlowRateWhenNoCoolingorHeatingisRequired();
  EXPECT_TRUE(unitary.isSupplyAirFlowRateWhenNoCoolingorHeatingisRequiredAutosized());

  EXPECT_TRUE(unitary.setNoLoadSupplyAirFlowRateControlSetToLowSpeed(false));
  EXPECT_FALSE(unitary.noLoadSupplyAirFlowRateControlSetToLowSpeed());

  EXPECT_TRUE(unitary.setMaximumSupplyAirTemperature(44.4));
  ASSERT_TRUE(unitary.maximumSupplyAirTemperature());
  EXPECT_DOUBLE_EQ(44.4, unitary.maximumSupplyAirTemperature().get());
  unitary.autosizeMaximumSupplyAirTemperature();
  EXPECT_TRUE(unitary.isMaximumSupplyAirTemperatureAutosized());

  EXPECT_TRUE(unitary.setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(18.0));
  EXPECT_DOUBLE_EQ(18.0, unitary.maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation());

  EXPECT_TRUE(unitary.setAncilliaryOnCycleElectricPower(9.0));
  EXPECT_DOUBLE_EQ(9.0, unitary.ancilliaryOnCycleElectricPower());
  EXPECT_TRUE(unitary.setAncilliaryOffCycleElectricPower(8.0));
  EXPECT_DOUBLE_EQ(8.0, unitary.ancilliaryOffCycleElectricPower());
}

TEST_F(EPModelFixture, AirLoopHVACUnitarySystem_RelationshipAccessors_RoundTrip) {
  Model model;
  AirLoopHVACUnitarySystem unitary(model);
  ThermalZone zone(model);
  ScheduleConstant availability(model);
  ScheduleConstant fanMode(model);
  FanConstantVolume fan(model);
  CoilHeatingElectric heating(model);
  CoilCoolingDXSingleSpeed cooling(model);
  CoilHeatingElectric supplemental(model);

  ASSERT_TRUE(availability.setValue(0.85));
  ASSERT_TRUE(fanMode.setValue(1.0));

  EXPECT_TRUE(unitary.setControllingZoneorThermostatLocation(zone));
  ASSERT_TRUE(unitary.controllingZoneorThermostatLocation());
  EXPECT_EQ(zone, unitary.controllingZoneorThermostatLocation().get());
  unitary.resetControllingZoneorThermostatLocation();
  EXPECT_FALSE(unitary.controllingZoneorThermostatLocation());

  EXPECT_TRUE(unitary.setAvailabilitySchedule(availability));
  ASSERT_TRUE(unitary.availabilitySchedule());
  EXPECT_EQ(availability, unitary.availabilitySchedule().get());
  unitary.resetAvailabilitySchedule();
  EXPECT_FALSE(unitary.availabilitySchedule());

  EXPECT_TRUE(unitary.setSupplyFan(fan));
  ASSERT_TRUE(unitary.supplyFan());
  EXPECT_EQ(fan, unitary.supplyFan().get());
  unitary.resetSupplyFan();
  EXPECT_FALSE(unitary.supplyFan());

  EXPECT_TRUE(unitary.setSupplyAirFanOperatingModeSchedule(fanMode));
  ASSERT_TRUE(unitary.supplyAirFanOperatingModeSchedule());
  EXPECT_EQ(fanMode, unitary.supplyAirFanOperatingModeSchedule().get());
  unitary.resetSupplyAirFanOperatingModeSchedule();
  EXPECT_FALSE(unitary.supplyAirFanOperatingModeSchedule());

  EXPECT_FALSE(unitary.hasHeatingCoil());
  EXPECT_TRUE(unitary.setHeatingCoil(heating));
  EXPECT_TRUE(unitary.hasHeatingCoil());
  ASSERT_TRUE(unitary.heatingCoil());
  EXPECT_EQ(heating, unitary.heatingCoil().get());
  EXPECT_EQ("SupplyAirFlowRate", unitary.supplyAirFlowRateMethodDuringHeatingOperation());
  EXPECT_TRUE(unitary.isSupplyAirFlowRateDuringHeatingOperationAutosized());
  unitary.resetHeatingCoil();
  EXPECT_FALSE(unitary.hasHeatingCoil());
  EXPECT_FALSE(unitary.heatingCoil());
  EXPECT_EQ("None", unitary.supplyAirFlowRateMethodDuringHeatingOperation());

  EXPECT_FALSE(unitary.hasCoolingCoil());
  EXPECT_TRUE(unitary.setCoolingCoil(cooling));
  EXPECT_TRUE(unitary.hasCoolingCoil());
  ASSERT_TRUE(unitary.coolingCoil());
  EXPECT_EQ(cooling, unitary.coolingCoil().get());
  EXPECT_EQ("SupplyAirFlowRate", unitary.supplyAirFlowRateMethodDuringCoolingOperation());
  EXPECT_TRUE(unitary.isSupplyAirFlowRateDuringCoolingOperationAutosized());
  unitary.resetCoolingCoil();
  EXPECT_FALSE(unitary.hasCoolingCoil());
  EXPECT_FALSE(unitary.coolingCoil());
  EXPECT_EQ("None", unitary.supplyAirFlowRateMethodDuringCoolingOperation());

  EXPECT_TRUE(unitary.setSupplementalHeatingCoil(supplemental));
  ASSERT_TRUE(unitary.supplementalHeatingCoil());
  EXPECT_EQ(supplemental, unitary.supplementalHeatingCoil().get());
  unitary.resetSupplementalHeatingCoil();
  EXPECT_FALSE(unitary.supplementalHeatingCoil());
}

TEST_F(EPModelFixture, AirLoopHVACUnitarySystem_TopologyAndInternalNodes) {
  Model model;
  ThermalZone zone(model);
  FanConstantVolume fan(model);
  CoilHeatingElectric heating(model);
  CoilCoolingDXSingleSpeed cooling(model);
  CoilHeatingElectric supplemental(model);
  AirLoopHVACUnitarySystem unitary(model);

  ASSERT_TRUE(unitary.setFanPlacement("DrawThrough"));
  ASSERT_TRUE(unitary.setSupplyFan(fan));
  ASSERT_TRUE(unitary.setHeatingCoil(heating));
  ASSERT_TRUE(unitary.setCoolingCoil(cooling));
  ASSERT_TRUE(unitary.setSupplementalHeatingCoil(supplemental));
  ASSERT_TRUE(unitary.addToThermalZone(zone));

  ASSERT_TRUE(unitary.inletNode());
  ASSERT_TRUE(unitary.outletNode());
  auto fanInlet = fan.inletModelObject()->optionalCast<Node>();
  auto fanOutlet = fan.outletModelObject()->optionalCast<Node>();
  auto coolingInlet = cooling.inletModelObject()->optionalCast<Node>();
  auto coolingOutlet = cooling.outletModelObject()->optionalCast<Node>();
  auto heatingInlet = heating.inletModelObject()->optionalCast<Node>();
  auto heatingOutlet = heating.outletModelObject()->optionalCast<Node>();
  auto supplementalInlet = supplemental.inletModelObject()->optionalCast<Node>();
  auto supplementalOutlet = supplemental.outletModelObject()->optionalCast<Node>();
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

  EXPECT_EQ(*unitary.inletNode(), *coolingInlet);
  EXPECT_EQ(*unitary.coolingCoilOutletNode(), *coolingOutlet);
  EXPECT_EQ(*unitary.coolingCoilOutletNode(), *heatingInlet);
  EXPECT_EQ(*unitary.heatingCoilOutletNode(), *heatingOutlet);
  EXPECT_EQ(*unitary.heatingCoilOutletNode(), *fanInlet);
  EXPECT_EQ(*unitary.fanOutletNode(), *fanOutlet);
  EXPECT_EQ(*unitary.fanOutletNode(), *supplementalInlet);
  EXPECT_EQ(*unitary.outletNode(), *supplementalOutlet);
}

TEST_F(EPModelFixture, AirLoopHVACUnitarySystem_NodeRolesFollowBlowThroughOrder) {
  Model model;
  FanConstantVolume fan(model);
  CoilHeatingElectric heating(model);
  CoilCoolingDXSingleSpeed cooling(model);
  CoilHeatingElectric supplemental(model);
  AirLoopHVACUnitarySystem unitary(model);

  ASSERT_TRUE(unitary.setFanPlacement("BlowThrough"));
  ASSERT_TRUE(unitary.setSupplyFan(fan));
  ASSERT_TRUE(unitary.setHeatingCoil(heating));
  ASSERT_TRUE(unitary.setCoolingCoil(cooling));
  ASSERT_TRUE(unitary.setSupplementalHeatingCoil(supplemental));

  ASSERT_TRUE(unitary.fanOutletNode());
  ASSERT_TRUE(unitary.coolingCoilOutletNode());
  ASSERT_TRUE(unitary.heatingCoilOutletNode());
  ASSERT_TRUE(unitary.outletNode());

  EXPECT_EQ(*unitary.fanOutletNode(), *cooling.inletModelObject()->optionalCast<Node>());
  EXPECT_EQ(*unitary.coolingCoilOutletNode(), *heating.inletModelObject()->optionalCast<Node>());
  EXPECT_EQ(*unitary.heatingCoilOutletNode(), *supplemental.inletModelObject()->optionalCast<Node>());
  EXPECT_EQ(*unitary.outletNode(), *supplemental.outletModelObject()->optionalCast<Node>());
}

TEST_F(EPModelFixture, AirLoopHVACUnitarySystem_InternalNodeRenamesSurviveCanonicalize) {
  Model model;
  FanConstantVolume fan(model);
  CoilHeatingElectric heating(model);
  CoilCoolingDXSingleSpeed cooling(model);
  CoilHeatingElectric supplemental(model);
  AirLoopHVACUnitarySystem unitary(model);

  ASSERT_TRUE(unitary.setFanPlacement("DrawThrough"));
  ASSERT_TRUE(unitary.setSupplyFan(fan));
  ASSERT_TRUE(unitary.setHeatingCoil(heating));
  ASSERT_TRUE(unitary.setCoolingCoil(cooling));
  ASSERT_TRUE(unitary.setSupplementalHeatingCoil(supplemental));

  ASSERT_TRUE(unitary.fanOutletNode());
  ASSERT_TRUE(unitary.coolingCoilOutletNode());
  ASSERT_TRUE(unitary.heatingCoilOutletNode());
  ASSERT_TRUE(unitary.fanOutletNode()->setName("Custom UnitarySystem Fan Outlet"));
  ASSERT_TRUE(unitary.coolingCoilOutletNode()->setName("Custom UnitarySystem Cooling Outlet"));
  ASSERT_TRUE(unitary.heatingCoilOutletNode()->setName("Custom UnitarySystem Heating Outlet"));

  auto report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);

  ASSERT_TRUE(unitary.fanOutletNode());
  ASSERT_TRUE(unitary.coolingCoilOutletNode());
  ASSERT_TRUE(unitary.heatingCoilOutletNode());
  EXPECT_EQ("Custom UnitarySystem Fan Outlet", unitary.fanOutletNode()->nameString());
  EXPECT_EQ("Custom UnitarySystem Cooling Outlet", unitary.coolingCoilOutletNode()->nameString());
  EXPECT_EQ("Custom UnitarySystem Heating Outlet", unitary.heatingCoilOutletNode()->nameString());
}

TEST_F(EPModelFixture, AirLoopHVACUnitarySystem_CanonicalizeRepairsContainedNodePath) {
  Model model;
  FanConstantVolume fan(model);
  CoilHeatingElectric heating(model);
  CoilCoolingDXSingleSpeed cooling(model);
  CoilHeatingElectric supplemental(model);
  AirLoopHVACUnitarySystem unitary(model);

  ASSERT_TRUE(unitary.setFanPlacement("DrawThrough"));
  ASSERT_TRUE(unitary.setSupplyFan(fan));
  ASSERT_TRUE(unitary.setHeatingCoil(heating));
  ASSERT_TRUE(unitary.setCoolingCoil(cooling));
  ASSERT_TRUE(unitary.setSupplementalHeatingCoil(supplemental));

  auto expectedCoolingOutlet = unitary.coolingCoilOutletNode();
  auto expectedHeatingOutlet = unitary.heatingCoilOutletNode();
  auto expectedFanOutlet = unitary.fanOutletNode();
  ASSERT_TRUE(expectedCoolingOutlet);
  ASSERT_TRUE(expectedHeatingOutlet);
  ASSERT_TRUE(expectedFanOutlet);

  ASSERT_TRUE(unitary.inletNode());
  ASSERT_TRUE(unitary.outletNode());
  ASSERT_TRUE(cooling.setPointer(cooling.outletPort(), unitary.inletNode()->handle()));
  ASSERT_TRUE(heating.setPointer(heating.inletPort(), unitary.inletNode()->handle()));
  ASSERT_TRUE(heating.setPointer(heating.outletPort(), unitary.outletNode()->handle()));
  ASSERT_TRUE(fan.setPointer(fan.inletPort(), unitary.outletNode()->handle()));
  ASSERT_TRUE(fan.setPointer(fan.outletPort(), unitary.inletNode()->handle()));
  ASSERT_TRUE(supplemental.setPointer(supplemental.inletPort(), unitary.inletNode()->handle()));

  auto report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);

  ASSERT_TRUE(unitary.coolingCoilOutletNode());
  ASSERT_TRUE(unitary.heatingCoilOutletNode());
  ASSERT_TRUE(unitary.fanOutletNode());
  EXPECT_EQ(*expectedCoolingOutlet, *unitary.coolingCoilOutletNode());
  EXPECT_EQ(*expectedHeatingOutlet, *unitary.heatingCoilOutletNode());
  EXPECT_EQ(*expectedFanOutlet, *unitary.fanOutletNode());
}
