/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../StraightComponent/AirLoopHVACUnitaryHeatPumpAirToAir.hpp"
#include "../StraightComponent/CoilCoolingDXSingleSpeed.hpp"
#include "../StraightComponent/CoilHeatingDXSingleSpeed.hpp"
#include "../StraightComponent/CoilHeatingElectric.hpp"
#include "../StraightComponent/FanOnOff.hpp"
#include "../StraightComponent/Node.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../WaterToAirComponent/CoilHeatingWater.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirLoopHVACUnitaryHeatPumpAirToAir_DefaultConstructor) {
  Model model;
  AirLoopHVACUnitaryHeatPumpAirToAir unitary(model);
  EXPECT_EQ(AirLoopHVACUnitaryHeatPumpAirToAir::iddObjectType(), unitary.iddObject().type());
}

TEST_F(EPModelFixture, AirLoopHVACUnitaryHeatPumpAirToAir_ScalarAccessors_RoundTrip) {
  Model model;
  AirLoopHVACUnitaryHeatPumpAirToAir unitary(model);

  EXPECT_TRUE(unitary.setSupplyAirFlowRateDuringCoolingOperation(1.1));
  ASSERT_TRUE(unitary.supplyAirFlowRateDuringCoolingOperation());
  EXPECT_DOUBLE_EQ(1.1, unitary.supplyAirFlowRateDuringCoolingOperation().get());
  EXPECT_FALSE(unitary.isSupplyAirFlowRateDuringCoolingOperationAutosized());
  unitary.autosizeSupplyAirFlowRateDuringCoolingOperation();
  EXPECT_TRUE(unitary.isSupplyAirFlowRateDuringCoolingOperationAutosized());

  EXPECT_TRUE(unitary.setSupplyAirFlowRateDuringHeatingOperation(1.2));
  ASSERT_TRUE(unitary.supplyAirFlowRateDuringHeatingOperation());
  EXPECT_DOUBLE_EQ(1.2, unitary.supplyAirFlowRateDuringHeatingOperation().get());
  EXPECT_FALSE(unitary.isSupplyAirFlowRateDuringHeatingOperationAutosized());
  unitary.autosizeSupplyAirFlowRateDuringHeatingOperation();
  EXPECT_TRUE(unitary.isSupplyAirFlowRateDuringHeatingOperationAutosized());

  EXPECT_TRUE(unitary.setSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded(0.6));
  ASSERT_TRUE(unitary.supplyAirFlowRateWhenNoCoolingorHeatingisNeeded());
  EXPECT_DOUBLE_EQ(0.6, unitary.supplyAirFlowRateWhenNoCoolingorHeatingisNeeded().get());
  EXPECT_FALSE(unitary.isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized());
  unitary.resetSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
  EXPECT_FALSE(unitary.supplyAirFlowRateWhenNoCoolingorHeatingisNeeded());
  unitary.autosizeSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
  EXPECT_TRUE(unitary.isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized());

  EXPECT_TRUE(unitary.setMaximumSupplyAirTemperaturefromSupplementalHeater(45.0));
  ASSERT_TRUE(unitary.maximumSupplyAirTemperaturefromSupplementalHeater());
  EXPECT_DOUBLE_EQ(45.0, unitary.maximumSupplyAirTemperaturefromSupplementalHeater().get());
  EXPECT_FALSE(unitary.isMaximumSupplyAirTemperaturefromSupplementalHeaterAutosized());
  unitary.autosizeMaximumSupplyAirTemperaturefromSupplementalHeater();
  EXPECT_TRUE(unitary.isMaximumSupplyAirTemperaturefromSupplementalHeaterAutosized());

  EXPECT_TRUE(unitary.setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(18.5));
  EXPECT_DOUBLE_EQ(18.5, unitary.maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation());
  EXPECT_FALSE(unitary.isMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperationDefaulted());
  unitary.resetMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation();
  EXPECT_TRUE(unitary.isMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperationDefaulted());

  EXPECT_TRUE(unitary.setFanPlacement("DrawThrough"));
  EXPECT_EQ("DrawThrough", unitary.fanPlacement());
  EXPECT_FALSE(unitary.isFanPlacementDefaulted());
  unitary.resetFanPlacement();
  EXPECT_TRUE(unitary.isFanPlacementDefaulted());

  EXPECT_TRUE(unitary.setDehumidificationControlType("CoolReheat"));
  EXPECT_EQ("CoolReheat", unitary.dehumidificationControlType());
  EXPECT_FALSE(unitary.isDehumidificationControlTypeDefaulted());
  unitary.resetDehumidificationControlType();
  EXPECT_TRUE(unitary.isDehumidificationControlTypeDefaulted());

  EXPECT_TRUE(unitary.setDXHeatingCoilSizingRatio(1.15));
  EXPECT_DOUBLE_EQ(1.15, unitary.dXHeatingCoilSizingRatio());
}

TEST_F(EPModelFixture, AirLoopHVACUnitaryHeatPumpAirToAir_RelationshipAccessors_RoundTrip) {
  Model model;
  AirLoopHVACUnitaryHeatPumpAirToAir unitary(model);
  ScheduleConstant availability(model);
  ScheduleConstant fanMode(model);
  ThermalZone zone(model);
  FanOnOff fan(model);
  CoilHeatingDXSingleSpeed heating(model);
  CoilCoolingDXSingleSpeed cooling(model);
  CoilHeatingElectric supplemental(model);

  ASSERT_TRUE(availability.setValue(0.75));
  ASSERT_TRUE(fanMode.setValue(0.0));

  EXPECT_TRUE(unitary.setAvailabilitySchedule(availability));
  EXPECT_EQ(availability, unitary.availabilitySchedule());

  EXPECT_TRUE(unitary.setControllingZone(zone));
  ASSERT_TRUE(unitary.controllingZone());
  EXPECT_EQ(zone, unitary.controllingZone().get());
  unitary.resetControllingZone();
  EXPECT_FALSE(unitary.controllingZone());

  EXPECT_TRUE(unitary.setSupplyAirFan(fan));
  EXPECT_EQ(fan, unitary.supplyAirFan());

  EXPECT_TRUE(unitary.setHeatingCoil(heating));
  EXPECT_EQ(heating, unitary.heatingCoil());

  EXPECT_TRUE(unitary.setCoolingCoil(cooling));
  EXPECT_EQ(cooling, unitary.coolingCoil());

  EXPECT_TRUE(unitary.setSupplementalHeatingCoil(supplemental));
  EXPECT_EQ(supplemental, unitary.supplementalHeatingCoil());

  EXPECT_TRUE(unitary.setSupplyAirFanOperatingModeSchedule(fanMode));
  ASSERT_TRUE(unitary.supplyAirFanOperatingModeSchedule());
  EXPECT_EQ(fanMode, unitary.supplyAirFanOperatingModeSchedule().get());
  unitary.resetSupplyAirFanOperatingModeSchedule();
  EXPECT_FALSE(unitary.supplyAirFanOperatingModeSchedule());
}

TEST_F(EPModelFixture, AirLoopHVACUnitaryHeatPumpAirToAir_TopologyAndInternalNodes) {
  Model model;
  AirLoopHVAC airLoop(model);
  FanOnOff fan(model);
  CoilHeatingDXSingleSpeed heating(model);
  CoilCoolingDXSingleSpeed cooling(model);
  CoilHeatingWater supplemental(model);
  AirLoopHVACUnitaryHeatPumpAirToAir unitary(model);

  ASSERT_TRUE(unitary.setFanPlacement("DrawThrough"));
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

TEST_F(EPModelFixture, AirLoopHVACUnitaryHeatPumpAirToAir_NodeRolesFollowBlowThroughOrder) {
  Model model;
  FanOnOff fan(model);
  CoilHeatingDXSingleSpeed heating(model);
  CoilCoolingDXSingleSpeed cooling(model);
  CoilHeatingElectric supplemental(model);
  AirLoopHVACUnitaryHeatPumpAirToAir unitary(model);

  ASSERT_TRUE(unitary.setFanPlacement("BlowThrough"));
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

TEST_F(EPModelFixture, AirLoopHVACUnitaryHeatPumpAirToAir_InternalNodeRenamesSurviveCanonicalize) {
  Model model;
  FanOnOff fan(model);
  CoilHeatingDXSingleSpeed heating(model);
  CoilCoolingDXSingleSpeed cooling(model);
  CoilHeatingElectric supplemental(model);
  AirLoopHVACUnitaryHeatPumpAirToAir unitary(model);

  ASSERT_TRUE(unitary.setFanPlacement("DrawThrough"));
  ASSERT_TRUE(unitary.setSupplyAirFan(fan));
  ASSERT_TRUE(unitary.setHeatingCoil(heating));
  ASSERT_TRUE(unitary.setCoolingCoil(cooling));
  ASSERT_TRUE(unitary.setSupplementalHeatingCoil(supplemental));

  ASSERT_TRUE(unitary.fanOutletNode());
  ASSERT_TRUE(unitary.coolingCoilOutletNode());
  ASSERT_TRUE(unitary.heatingCoilOutletNode());
  ASSERT_TRUE(unitary.fanOutletNode()->setName("Custom Unitary Fan Outlet"));
  ASSERT_TRUE(unitary.coolingCoilOutletNode()->setName("Custom Unitary Cooling Outlet"));
  ASSERT_TRUE(unitary.heatingCoilOutletNode()->setName("Custom Unitary Heating Outlet"));

  auto report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);

  ASSERT_TRUE(unitary.fanOutletNode());
  ASSERT_TRUE(unitary.coolingCoilOutletNode());
  ASSERT_TRUE(unitary.heatingCoilOutletNode());
  EXPECT_EQ("Custom Unitary Fan Outlet", unitary.fanOutletNode()->nameString());
  EXPECT_EQ("Custom Unitary Cooling Outlet", unitary.coolingCoilOutletNode()->nameString());
  EXPECT_EQ("Custom Unitary Heating Outlet", unitary.heatingCoilOutletNode()->nameString());
}

TEST_F(EPModelFixture, AirLoopHVACUnitaryHeatPumpAirToAir_CanonicalizeRepairsContainedNodePath) {
  Model model;
  FanOnOff fan(model);
  CoilHeatingDXSingleSpeed heating(model);
  CoilCoolingDXSingleSpeed cooling(model);
  CoilHeatingElectric supplemental(model);
  AirLoopHVACUnitaryHeatPumpAirToAir unitary(model);

  ASSERT_TRUE(unitary.setFanPlacement("DrawThrough"));
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
