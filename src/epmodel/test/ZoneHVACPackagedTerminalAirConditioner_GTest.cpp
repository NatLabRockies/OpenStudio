/***********************************************************************************************************************  
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.  
*  See also https://openstudio.net/license  
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ZoneHVACComponent/ZoneHVACPackagedTerminalAirConditioner.hpp"
#include "../Schedule/ScheduleCompact.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../StraightComponent/Node.hpp"
#include "../StraightComponent/FanConstantVolume.hpp"
#include "../StraightComponent/CoilCoolingDXSingleSpeed.hpp"
#include "../WaterToAirComponent/CoilHeatingWater.hpp"
#include "../HVACComponent/ThermalZone.hpp"

#include <utilities/idd/ZoneHVAC_PackagedTerminalAirConditioner_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneHVACPackagedTerminalAirConditioner_DefaultConstructor) {
  Model model;
  ZoneHVACPackagedTerminalAirConditioner ptac(model);

  EXPECT_FALSE(ptac.supplyAirFlowRateDuringCoolingOperation());
  EXPECT_FALSE(ptac.isSupplyAirFlowRateDuringCoolingOperationAutosized());
  EXPECT_FALSE(ptac.supplyAirFlowRateDuringHeatingOperation());
  EXPECT_FALSE(ptac.isSupplyAirFlowRateDuringHeatingOperationAutosized());
  EXPECT_FALSE(ptac.supplyAirFlowRateWhenNoCoolingorHeatingisNeeded());
  EXPECT_FALSE(ptac.isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized());
  EXPECT_FALSE(ptac.noLoadSupplyAirFlowRateControlSetToLowSpeed());
  EXPECT_FALSE(ptac.outdoorAirFlowRateDuringCoolingOperation());
  EXPECT_FALSE(ptac.isOutdoorAirFlowRateDuringCoolingOperationAutosized());
  EXPECT_FALSE(ptac.outdoorAirFlowRateDuringHeatingOperation());
  EXPECT_FALSE(ptac.isOutdoorAirFlowRateDuringHeatingOperationAutosized());
  EXPECT_FALSE(ptac.outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded());
  EXPECT_FALSE(ptac.isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized());
  EXPECT_TRUE(ptac.isFanPlacementDefaulted());
  EXPECT_EQ("", ptac.fanPlacement());
}

TEST_F(EPModelFixture, ZoneHVACPackagedTerminalAirConditioner_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneHVACPackagedTerminalAirConditioner ptac(model);

  EXPECT_TRUE(ptac.setSupplyAirFlowRateDuringCoolingOperation(0.5));
  ASSERT_TRUE(ptac.supplyAirFlowRateDuringCoolingOperation());
  EXPECT_DOUBLE_EQ(0.5, ptac.supplyAirFlowRateDuringCoolingOperation().get());
  EXPECT_FALSE(ptac.isSupplyAirFlowRateDuringCoolingOperationAutosized());
  ptac.autosizeSupplyAirFlowRateDuringCoolingOperation();
  EXPECT_TRUE(ptac.isSupplyAirFlowRateDuringCoolingOperationAutosized());
  EXPECT_FALSE(ptac.supplyAirFlowRateDuringCoolingOperation());

  EXPECT_TRUE(ptac.setSupplyAirFlowRateDuringHeatingOperation(0.55));
  ASSERT_TRUE(ptac.supplyAirFlowRateDuringHeatingOperation());
  EXPECT_DOUBLE_EQ(0.55, ptac.supplyAirFlowRateDuringHeatingOperation().get());
  ptac.autosizeSupplyAirFlowRateDuringHeatingOperation();
  EXPECT_TRUE(ptac.isSupplyAirFlowRateDuringHeatingOperationAutosized());

  EXPECT_TRUE(ptac.setSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded(0.12));
  ASSERT_TRUE(ptac.supplyAirFlowRateWhenNoCoolingorHeatingisNeeded());
  EXPECT_DOUBLE_EQ(0.12, ptac.supplyAirFlowRateWhenNoCoolingorHeatingisNeeded().get());
  ptac.resetSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
  EXPECT_FALSE(ptac.supplyAirFlowRateWhenNoCoolingorHeatingisNeeded());
  ptac.autosizeSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
  EXPECT_TRUE(ptac.isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized());

  EXPECT_TRUE(ptac.setNoLoadSupplyAirFlowRateControlSetToLowSpeed(true));
  EXPECT_TRUE(ptac.noLoadSupplyAirFlowRateControlSetToLowSpeed());

  EXPECT_TRUE(ptac.setOutdoorAirFlowRateDuringCoolingOperation(0.09));
  ptac.autosizeOutdoorAirFlowRateDuringCoolingOperation();
  EXPECT_TRUE(ptac.isOutdoorAirFlowRateDuringCoolingOperationAutosized());

  EXPECT_TRUE(ptac.setOutdoorAirFlowRateDuringHeatingOperation(0.06));
  ptac.autosizeOutdoorAirFlowRateDuringHeatingOperation();
  EXPECT_TRUE(ptac.isOutdoorAirFlowRateDuringHeatingOperationAutosized());

  EXPECT_TRUE(ptac.setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(0.02));
  ptac.resetOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
  EXPECT_FALSE(ptac.outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded());
  ptac.autosizeOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
  EXPECT_TRUE(ptac.isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized());

  EXPECT_TRUE(ptac.setFanPlacement("BlowThrough"));
  EXPECT_EQ("BlowThrough", ptac.fanPlacement());
  ptac.resetFanPlacement();
  EXPECT_TRUE(ptac.isFanPlacementDefaulted());
}

TEST_F(EPModelFixture, ZoneHVACPackagedTerminalAirConditioner_TopologyAndChildren) {
  Model model;
  FanConstantVolume fan(model);
  CoilHeatingWater heatingCoil(model);
  CoilCoolingDXSingleSpeed coolingCoil(model);
  ZoneHVACPackagedTerminalAirConditioner ptac(model);

  EXPECT_TRUE(ptac.setSupplyAirFan(fan));
  EXPECT_TRUE(ptac.setHeatingCoil(heatingCoil));
  EXPECT_TRUE(ptac.setCoolingCoil(coolingCoil));

  const auto children = ptac.children();
  ASSERT_EQ(3u, children.size());
  EXPECT_EQ(heatingCoil, children[0]);
  EXPECT_EQ(fan, children[1]);
  EXPECT_EQ(coolingCoil, children[2]);

  ASSERT_TRUE(fan.containingZoneHVACComponent());
  ASSERT_TRUE(heatingCoil.containingZoneHVACComponent());
  ASSERT_TRUE(coolingCoil.containingZoneHVACComponent());
  EXPECT_EQ(ptac, fan.containingZoneHVACComponent().get());
  EXPECT_EQ(ptac, heatingCoil.containingZoneHVACComponent().get());
  EXPECT_EQ(ptac, coolingCoil.containingZoneHVACComponent().get());

  EXPECT_EQ(openstudio::ZoneHVAC_PackagedTerminalAirConditionerFields::AirInletNodeName, ptac.inletPort());
  EXPECT_EQ(openstudio::ZoneHVAC_PackagedTerminalAirConditionerFields::AirOutletNodeName, ptac.outletPort());

  ThermalZone zone(model);
  EXPECT_TRUE(ptac.addToThermalZone(zone));
  ASSERT_TRUE(ptac.thermalZone());
  ASSERT_TRUE(ptac.inletNode());
  ASSERT_TRUE(ptac.outletNode());
  EXPECT_EQ(zone, ptac.thermalZone().get());
  EXPECT_NE(ptac.inletNode()->handle(), ptac.outletNode()->handle());
  ptac.removeFromThermalZone();
  EXPECT_FALSE(ptac.thermalZone());
  EXPECT_FALSE(ptac.inletNode());
  EXPECT_FALSE(ptac.outletNode());
}

TEST_F(EPModelFixture, ZoneHVACPackagedTerminalAirConditioner_ScheduleRelationships_RoundTrip) {
  Model model;
  ZoneHVACPackagedTerminalAirConditioner ptac(model);

  auto defaultAvailability = ptac.availabilitySchedule().optionalCast<ScheduleConstant>();
  ASSERT_TRUE(defaultAvailability);
  EXPECT_DOUBLE_EQ(1.0, defaultAvailability->value());
  auto defaultFanMode = ptac.supplyAirFanOperatingModeSchedule().optionalCast<ScheduleConstant>();
  ASSERT_TRUE(defaultFanMode);
  EXPECT_DOUBLE_EQ(1.0, defaultFanMode->value());

  ScheduleCompact availability(model);
  ScheduleCompact fanMode(model);
  ASSERT_TRUE(availability.setToConstantValue(0.6));
  ASSERT_TRUE(fanMode.setToConstantValue(0.0));

  EXPECT_TRUE(ptac.setAvailabilitySchedule(availability));
  EXPECT_TRUE(ptac.setSupplyAirFanOperatingModeSchedule(fanMode));
  EXPECT_EQ(availability.handle(), ptac.availabilitySchedule().handle());
  EXPECT_EQ(fanMode.handle(), ptac.supplyAirFanOperatingModeSchedule().handle());
}
