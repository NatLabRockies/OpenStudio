/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../StraightComponent/Node.hpp"
#include "../StraightComponent/FanConstantVolume.hpp"
#include "../Schedule/ScheduleCompact.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../WaterToAirComponent/CoilCoolingWater.hpp"
#include "../WaterToAirComponent/CoilHeatingWater.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../ZoneHVACComponent/ZoneHVACFourPipeFanCoil.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, API_ZoneHVACFourPipeFanCoil_DefaultConstructor) {
  Model model;
  ZoneHVACFourPipeFanCoil coil(model);
  EXPECT_EQ(ZoneHVACFourPipeFanCoil::iddObjectType(), coil.iddObject().type());
  EXPECT_FALSE(coil.nameString().empty());
}

TEST_F(EPModelFixture, ZoneHVACFourPipeFanCoil_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneHVACFourPipeFanCoil coil(model);

  const auto capacityMethods = ZoneHVACFourPipeFanCoil::capacityControlMethodValues();
  ASSERT_FALSE(capacityMethods.empty());
  EXPECT_TRUE(coil.setCapacityControlMethod(capacityMethods.front()));
  EXPECT_EQ(capacityMethods.front(), coil.capacityControlMethod());

  EXPECT_TRUE(coil.setMaximumSupplyAirFlowRate(1.2));
  ASSERT_TRUE(coil.maximumSupplyAirFlowRate());
  EXPECT_DOUBLE_EQ(1.2, coil.maximumSupplyAirFlowRate().get());
  coil.autosizeMaximumSupplyAirFlowRate();
  EXPECT_TRUE(coil.isMaximumSupplyAirFlowRateAutosized());

  EXPECT_TRUE(coil.setLowSpeedSupplyAirFlowRatio(0.35));
  EXPECT_DOUBLE_EQ(0.35, coil.lowSpeedSupplyAirFlowRatio());
  coil.resetLowSpeedSupplyAirFlowRatio();
  EXPECT_TRUE(coil.isLowSpeedSupplyAirFlowRatioDefaulted());

  EXPECT_TRUE(coil.setMediumSpeedSupplyAirFlowRatio(0.6));
  EXPECT_DOUBLE_EQ(0.6, coil.mediumSpeedSupplyAirFlowRatio());
  coil.resetMediumSpeedSupplyAirFlowRatio();
  EXPECT_TRUE(coil.isMediumSpeedSupplyAirFlowRatioDefaulted());

  EXPECT_TRUE(coil.setMaximumOutdoorAirFlowRate(0.45));
  coil.autosizeMaximumOutdoorAirFlowRate();
  EXPECT_TRUE(coil.isMaximumOutdoorAirFlowRateAutosized());

  const auto mixerTypes = ZoneHVACFourPipeFanCoil::outdoorAirMixerObjectTypeValues();
  ASSERT_FALSE(mixerTypes.empty());
  EXPECT_TRUE(coil.setOutdoorAirMixerObjectType(mixerTypes.front()));
  EXPECT_EQ(mixerTypes.front(), coil.outdoorAirMixerObjectType());

  EXPECT_TRUE(coil.setMaximumColdWaterFlowRate(0.18));
  coil.autosizeMaximumColdWaterFlowRate();
  EXPECT_TRUE(coil.isMaximumColdWaterFlowRateAutosized());

  EXPECT_TRUE(coil.setMinimumColdWaterFlowRate(0.08));
  EXPECT_DOUBLE_EQ(0.08, coil.minimumColdWaterFlowRate());
  coil.resetMinimumColdWaterFlowRate();
  EXPECT_TRUE(coil.isMinimumColdWaterFlowRateDefaulted());

  EXPECT_TRUE(coil.setCoolingConvergenceTolerance(0.007));
  EXPECT_DOUBLE_EQ(0.007, coil.coolingConvergenceTolerance());
  coil.resetCoolingConvergenceTolerance();
  EXPECT_TRUE(coil.isCoolingConvergenceToleranceDefaulted());

  EXPECT_TRUE(coil.setMaximumHotWaterFlowRate(0.25));
  coil.autosizeMaximumHotWaterFlowRate();
  EXPECT_TRUE(coil.isMaximumHotWaterFlowRateAutosized());

  EXPECT_TRUE(coil.setMinimumHotWaterFlowRate(0.12));
  EXPECT_DOUBLE_EQ(0.12, coil.minimumHotWaterFlowRate());
  coil.resetMinimumHotWaterFlowRate();
  EXPECT_TRUE(coil.isMinimumHotWaterFlowRateDefaulted());

  EXPECT_TRUE(coil.setHeatingConvergenceTolerance(0.003));
  EXPECT_DOUBLE_EQ(0.003, coil.heatingConvergenceTolerance());
  coil.resetHeatingConvergenceTolerance();
  EXPECT_TRUE(coil.isHeatingConvergenceToleranceDefaulted());

  coil.autosizeMinimumSupplyAirTemperatureInCoolingMode();
  EXPECT_TRUE(coil.isMinimumSupplyAirTemperatureInCoolingModeAutosized());

  coil.autosizeMaximumSupplyAirTemperatureInHeatingMode();
  EXPECT_TRUE(coil.isMaximumSupplyAirTemperatureInHeatingModeAutosized());
}

TEST_F(EPModelFixture, ZoneHVACFourPipeFanCoil_ChildrenAndZoneTopology) {
  Model model;
  FanConstantVolume fan(model);
  CoilCoolingWater coolingCoil(model);
  CoilHeatingWater heatingCoil(model);
  ZoneHVACFourPipeFanCoil coil(model);
  ThermalZone zone(model);

  ASSERT_TRUE(coil.setCapacityControlMethod("ConstantFanVariableFlow"));
  ASSERT_TRUE(coil.setSupplyAirFan(fan));
  ASSERT_TRUE(coil.setCoolingCoil(coolingCoil));
  ASSERT_TRUE(coil.setHeatingCoil(heatingCoil));

  const auto children = coil.children();
  ASSERT_EQ(3u, children.size());
  EXPECT_EQ(fan.handle(), children[0].handle());
  EXPECT_EQ(coolingCoil.handle(), children[1].handle());
  EXPECT_EQ(heatingCoil.handle(), children[2].handle());

  ASSERT_TRUE(fan.containingZoneHVACComponent());
  ASSERT_TRUE(coolingCoil.containingZoneHVACComponent());
  ASSERT_TRUE(heatingCoil.containingZoneHVACComponent());
  EXPECT_EQ(coil, fan.containingZoneHVACComponent().get());
  EXPECT_EQ(coil, coolingCoil.containingZoneHVACComponent().get());
  EXPECT_EQ(coil, heatingCoil.containingZoneHVACComponent().get());

  ASSERT_TRUE(coil.addToThermalZone(zone));
  ASSERT_TRUE(coil.inletNode());
  ASSERT_TRUE(coil.outletNode());
  EXPECT_EQ(zone, coil.thermalZone().get());

  coil.removeFromThermalZone();
  EXPECT_FALSE(coil.thermalZone());
  EXPECT_FALSE(coil.inletNode());
  EXPECT_FALSE(coil.outletNode());
}

TEST_F(EPModelFixture, ZoneHVACFourPipeFanCoil_ScheduleRelationships_RoundTrip) {
  Model model;
  ZoneHVACFourPipeFanCoil coil(model);

  auto defaultSchedule = coil.availabilitySchedule().optionalCast<ScheduleConstant>();
  ASSERT_TRUE(defaultSchedule);
  EXPECT_DOUBLE_EQ(1.0, defaultSchedule->value());

  ScheduleCompact availability(model);
  ScheduleCompact outdoorAir(model);
  ScheduleCompact fanMode(model);
  ASSERT_TRUE(availability.setToConstantValue(0.3));
  ASSERT_TRUE(outdoorAir.setToConstantValue(0.4));
  ASSERT_TRUE(fanMode.setToConstantValue(1.0));

  EXPECT_TRUE(coil.setAvailabilitySchedule(availability));
  EXPECT_TRUE(coil.setOutdoorAirSchedule(outdoorAir));
  EXPECT_TRUE(coil.setSupplyAirFanOperatingModeSchedule(fanMode));
  EXPECT_EQ(availability.handle(), coil.availabilitySchedule().handle());
  ASSERT_TRUE(coil.outdoorAirSchedule());
  EXPECT_EQ(outdoorAir.handle(), coil.outdoorAirSchedule()->handle());
  ASSERT_TRUE(coil.supplyAirFanOperatingModeSchedule());
  EXPECT_EQ(fanMode.handle(), coil.supplyAirFanOperatingModeSchedule()->handle());

  coil.resetOutdoorAirSchedule();
  EXPECT_FALSE(coil.outdoorAirSchedule());
  coil.resetSupplyAirFanOperatingModeSchedule();
  EXPECT_FALSE(coil.supplyAirFanOperatingModeSchedule());
}
