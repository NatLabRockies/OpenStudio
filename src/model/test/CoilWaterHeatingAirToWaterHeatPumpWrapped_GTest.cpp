/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "ModelFixture.hpp"

#include "../CoilWaterHeatingAirToWaterHeatPumpWrapped.hpp"
#include "../CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl.hpp"
#include "../Schedule.hpp"
#include "../Schedule_Impl.hpp"
#include "../ScheduleConstant.hpp"
#include "../ScheduleConstant_Impl.hpp"

using namespace openstudio;
using namespace openstudio::model;

TEST_F(ModelFixture, CoilWaterHeatingAirToWaterHeatPumpWrapped) {

  Model m;
  CoilWaterHeatingAirToWaterHeatPumpWrapped coil(m);

  // Availability Schedule Name: Required Object
  auto alwaysOn = m.alwaysOnDiscreteSchedule();
  EXPECT_EQ(alwaysOn, coil.availabilitySchedule());
  ScheduleConstant scheduleConstant(m);
  EXPECT_TRUE(coil.setAvailabilitySchedule(scheduleConstant));
  EXPECT_EQ(scheduleConstant, coil.availabilitySchedule());
}