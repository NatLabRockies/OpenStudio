/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>
#include "ModelFixture.hpp"
#include "../CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit.hpp"
#include "../CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl.hpp"
#include "../Curve.hpp"
#include "../Curve_Impl.hpp"
#include "../CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData.hpp"
#include "../CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl.hpp"
#include "../Schedule.hpp"
#include "../Schedule_Impl.hpp"
#include "../ScheduleConstant.hpp"
#include "../ScheduleConstant_Impl.hpp"
#include "../ScheduleTypeLimits.hpp"
#include "../ScheduleTypeLimits_Impl.hpp"

using namespace openstudio;
using namespace openstudio::model;

TEST_F(ModelFixture, CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit) {
  ::testing::FLAGS_gtest_death_test_style = "threadsafe";

  ASSERT_EXIT(
    {
      Model m;
      CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit coil(m);

      exit(0);
    },
    ::testing::ExitedWithCode(0), "");

  Model m;
  CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit coil(m);

  auto alwaysOn = m.alwaysOnDiscreteSchedule();
  EXPECT_EQ(alwaysOn, coil.availabilitySchedule());
  ScheduleConstant scheduleConstant(m);
  EXPECT_TRUE(coil.setAvailabilitySchedule(scheduleConstant));
  EXPECT_EQ(scheduleConstant, coil.availabilitySchedule());
}

TEST_F(ModelFixture, CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Remove) {
  Model m;
  auto count = m.modelObjects().size();

  CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit coil(m);
  CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData speed(m);
  coil.addSpeed(speed);
  coil.remove();

  auto curves = m.getModelObjects<model::Curve>();
  auto schedules = m.getConcreteModelObjects<model::ScheduleConstant>();
  auto limits = m.getConcreteModelObjects<model::ScheduleTypeLimits>();

  EXPECT_EQ(count + schedules.size() + limits.size(), m.modelObjects().size() - curves.size());
}

TEST_F(ModelFixture, CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_2320_NewFields) {
  Model m;

  CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit coil(m);

  // E+ 23.2.0 defaults Maximum Cycling Rate and Latent Capacity Time Constant to 0.0, we don't, cf #4999
  EXPECT_EQ(2.5, coil.maximumCyclingRate());
  EXPECT_EQ(60.0, coil.latentCapacityTimeConstant());
  // Test IDD defaults
  EXPECT_EQ(60.0, coil.fanDelayTime());

  EXPECT_TRUE(coil.setMaximumCyclingRate(3.5));
  EXPECT_EQ(3.5, coil.maximumCyclingRate());
  EXPECT_FALSE(coil.setMaximumCyclingRate(-12.5));
  EXPECT_EQ(3.5, coil.maximumCyclingRate());

  EXPECT_TRUE(coil.setLatentCapacityTimeConstant(90.0));
  EXPECT_EQ(90.0, coil.latentCapacityTimeConstant());
  EXPECT_FALSE(coil.setLatentCapacityTimeConstant(-12.5));
  EXPECT_EQ(90.0, coil.latentCapacityTimeConstant());

  EXPECT_TRUE(coil.setFanDelayTime(120.0));
  EXPECT_EQ(120.0, coil.fanDelayTime());
  EXPECT_FALSE(coil.setFanDelayTime(-12.5));
  EXPECT_EQ(120.0, coil.fanDelayTime());
}
