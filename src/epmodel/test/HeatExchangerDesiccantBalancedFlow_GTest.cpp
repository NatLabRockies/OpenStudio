/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../AirToAirComponent/HeatExchangerDesiccantBalancedFlow.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, HeatExchangerDesiccantBalancedFlow_DefaultConstructor) {
  Model model;
  HeatExchangerDesiccantBalancedFlow object(model);

  EXPECT_EQ(HeatExchangerDesiccantBalancedFlow::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, HeatExchangerDesiccantBalancedFlow_ScalarAccessors_RoundTrip) {
  Model model;
  HeatExchangerDesiccantBalancedFlow object(model);

  EXPECT_TRUE(object.setEconomizerLockout(false));
  EXPECT_FALSE(object.economizerLockout());

  EXPECT_TRUE(object.setEconomizerLockout(true));
  EXPECT_TRUE(object.economizerLockout());
}
