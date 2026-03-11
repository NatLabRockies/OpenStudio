/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/WindowPropertyAirflowControl.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, WindowPropertyAirflowControl_DefaultConstructor) {
  Model model;
  WindowPropertyAirflowControl airflowControl(model);
  EXPECT_EQ(WindowPropertyAirflowControl::iddObjectType(), airflowControl.iddObject().type());
}

TEST_F(EPModelFixture, WindowPropertyAirflowControl_ScalarAccessors_RoundTrip) {
  Model model;
  WindowPropertyAirflowControl airflowControl(model);

  EXPECT_TRUE(airflowControl.setAirflowSource("OutdoorAir"));
  EXPECT_EQ("OutdoorAir", airflowControl.airflowSource());
  EXPECT_FALSE(airflowControl.isAirflowSourceDefaulted());
  airflowControl.resetAirflowSource();
  EXPECT_TRUE(airflowControl.isAirflowSourceDefaulted());

  EXPECT_TRUE(airflowControl.setAirflowDestination("ReturnAir"));
  EXPECT_EQ("ReturnAir", airflowControl.airflowDestination());
  EXPECT_FALSE(airflowControl.isAirflowDestinationDefaulted());
  airflowControl.resetAirflowDestination();
  EXPECT_TRUE(airflowControl.isAirflowDestinationDefaulted());

  EXPECT_TRUE(airflowControl.setMaximumFlowRate(0.25));
  EXPECT_DOUBLE_EQ(0.25, airflowControl.maximumFlowRate());
  airflowControl.resetMaximumFlowRate();
  EXPECT_TRUE(airflowControl.isMaximumFlowRateDefaulted());

  EXPECT_TRUE(airflowControl.setAirflowControlType("AlwaysOff"));
  EXPECT_EQ("AlwaysOff", airflowControl.airflowControlType());
  EXPECT_FALSE(airflowControl.isAirflowControlTypeDefaulted());
  airflowControl.resetAirflowControlType();
  EXPECT_TRUE(airflowControl.isAirflowControlTypeDefaulted());

  EXPECT_TRUE(airflowControl.setAirflowIsScheduled(true));
  EXPECT_TRUE(airflowControl.airflowIsScheduled());
  EXPECT_FALSE(airflowControl.isAirflowIsScheduledDefaulted());
  EXPECT_TRUE(airflowControl.setAirflowIsScheduled(false));
  EXPECT_FALSE(airflowControl.airflowIsScheduled());
  airflowControl.resetAirflowIsScheduled();
  EXPECT_TRUE(airflowControl.isAirflowIsScheduledDefaulted());
}
