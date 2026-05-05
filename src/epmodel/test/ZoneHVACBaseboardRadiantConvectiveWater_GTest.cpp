/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../Schedule/Schedule.hpp"
#include "../StraightComponent/CoilHeatingWaterBaseboardRadiant.hpp"
#include "../StraightComponent/Node.hpp"
#include "../ZoneHVACComponent/ZoneHVACBaseboardRadiantConvectiveWater.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneHVACBaseboardRadiantConvectiveWater_DefaultConstructor) {
  Model model;
  ZoneHVACBaseboardRadiantConvectiveWater baseboard(model);

  auto alwaysOn = baseboard.availabilitySchedule().cast<ScheduleConstant>();
  EXPECT_DOUBLE_EQ(1.0, alwaysOn.value());
  EXPECT_DOUBLE_EQ(0.3, baseboard.fractionRadiant());
  EXPECT_DOUBLE_EQ(0.3, baseboard.fractionofRadiantEnergyIncidentonPeople());
  EXPECT_DOUBLE_EQ(87.78, baseboard.heatingCoil().ratedAverageWaterTemperature());
  EXPECT_DOUBLE_EQ(0.063, baseboard.heatingCoil().ratedWaterMassFlowRate());
}

TEST_F(EPModelFixture, ZoneHVACBaseboardRadiantConvectiveWater_CanonicalParentSurface_RoundTrip) {
  Model model;
  ZoneHVACBaseboardRadiantConvectiveWater baseboard(model);
  ScheduleConstant availability(model);

  EXPECT_TRUE(baseboard.setAvailabilitySchedule(availability));
  EXPECT_EQ(availability.handle(), baseboard.availabilitySchedule().handle());

  EXPECT_TRUE(baseboard.setFractionRadiant(0.42));
  EXPECT_DOUBLE_EQ(0.42, baseboard.fractionRadiant());

  EXPECT_TRUE(baseboard.setFractionofRadiantEnergyIncidentonPeople(0.18));
  EXPECT_DOUBLE_EQ(0.18, baseboard.fractionofRadiantEnergyIncidentonPeople());

  ASSERT_EQ(1u, baseboard.children().size());
  EXPECT_EQ(baseboard.heatingCoil().handle(), baseboard.children()[0].handle());
}

TEST_F(EPModelFixture, ZoneHVACBaseboardRadiantConvectiveWater_FlattenedAndCanonicalViewsStayAligned) {
  Model model;
  ZoneHVACBaseboardRadiantConvectiveWater baseboard(model);
  auto heatingCoil = baseboard.heatingCoil();

  EXPECT_TRUE(baseboard.setRatedAverageWaterTemperature(71.0));
  EXPECT_DOUBLE_EQ(71.0, heatingCoil.ratedAverageWaterTemperature());

  EXPECT_TRUE(heatingCoil.setRatedWaterMassFlowRate(0.15));
  ASSERT_TRUE(baseboard.ratedWaterMassFlowRate());
  EXPECT_DOUBLE_EQ(0.15, *baseboard.ratedWaterMassFlowRate());

  EXPECT_TRUE(heatingCoil.setHeatingDesignCapacityMethod("CapacityPerFloorArea"));
  EXPECT_EQ("CapacityPerFloorArea", heatingCoil.heatingDesignCapacityMethod());

  EXPECT_TRUE(heatingCoil.setHeatingDesignCapacityPerFloorArea(0.8));
  EXPECT_DOUBLE_EQ(0.8, heatingCoil.heatingDesignCapacityPerFloorArea());

  EXPECT_TRUE(heatingCoil.setFractionofAutosizedHeatingDesignCapacity(0.9));
  EXPECT_DOUBLE_EQ(0.9, heatingCoil.fractionofAutosizedHeatingDesignCapacity());

  EXPECT_TRUE(heatingCoil.setConvergenceTolerance(0.002));
  EXPECT_DOUBLE_EQ(0.002, heatingCoil.convergenceTolerance());
}

TEST_F(EPModelFixture, ZoneHVACBaseboardRadiantConvectiveWater_ZoneAttachmentRoundTrip) {
  Model model;
  ThermalZone zone(model);
  ZoneHVACBaseboardRadiantConvectiveWater baseboard(model);

  EXPECT_EQ(0u, baseboard.inletPort());
  EXPECT_EQ(0u, baseboard.outletPort());
  EXPECT_FALSE(baseboard.inletNode());
  EXPECT_FALSE(baseboard.outletNode());
  EXPECT_FALSE(baseboard.thermalZone());

  EXPECT_TRUE(baseboard.addToThermalZone(zone));
  ASSERT_TRUE(baseboard.thermalZone());
  EXPECT_EQ(zone, *baseboard.thermalZone());

  baseboard.removeFromThermalZone();
  EXPECT_FALSE(baseboard.thermalZone());
  EXPECT_FALSE(baseboard.inletNode());
  EXPECT_FALSE(baseboard.outletNode());
}
