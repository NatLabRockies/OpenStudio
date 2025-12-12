/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>
#include "ModelFixture.hpp"
#include "../CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit.hpp"
#include "../CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl.hpp"
#include "../Curve.hpp"
#include "../Curve_Impl.hpp"
#include "../CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData.hpp"
#include "../CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl.hpp"
#include "../Schedule.hpp"
#include "../Schedule_Impl.hpp"
#include "../ScheduleConstant.hpp"
#include "../ScheduleConstant_Impl.hpp"
#include "../ScheduleTypeLimits.hpp"
#include "../ScheduleTypeLimits_Impl.hpp"

using namespace openstudio;
using namespace openstudio::model;

TEST_F(ModelFixture, CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit) {
  ::testing::FLAGS_gtest_death_test_style = "threadsafe";

  ASSERT_EXIT(
    {
      Model m;
      CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit coil(m);

      exit(0);
    },
    ::testing::ExitedWithCode(0), "");

  Model m;
  CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit coil(m);

  auto alwaysOn = m.alwaysOnDiscreteSchedule();
  EXPECT_EQ(alwaysOn, coil.availabilitySchedule());
  ScheduleConstant scheduleConstant(m);
  EXPECT_TRUE(coil.setAvailabilitySchedule(scheduleConstant));
  EXPECT_EQ(scheduleConstant, coil.availabilitySchedule());
}

TEST_F(ModelFixture, CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Remove) {
  Model m;
  auto count = m.modelObjects().size();

  CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit coil(m);
  CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData speed(m);
  coil.addSpeed(speed);
  coil.remove();

  auto curves = m.getModelObjects<model::Curve>();
  auto schedules = m.getConcreteModelObjects<model::ScheduleConstant>();
  auto limits = m.getConcreteModelObjects<model::ScheduleTypeLimits>();

  EXPECT_EQ(count + schedules.size() + limits.size(), m.modelObjects().size() - curves.size());
}
