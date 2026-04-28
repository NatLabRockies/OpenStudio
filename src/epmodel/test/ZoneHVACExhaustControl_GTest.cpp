/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/ZoneHVACExhaustControl.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneHVACExhaustControl_DefaultConstructor) {
  Model model;
  ZoneHVACExhaustControl exhaust(model);

  EXPECT_EQ(ZoneHVACExhaustControl::iddObjectType(), exhaust.iddObject().type());
  EXPECT_EQ("Scheduled", exhaust.flowControlType());
  EXPECT_FALSE(exhaust.isFlowControlTypeDefaulted());
  EXPECT_TRUE(exhaust.isDesignExhaustFlowRateAutosized());
}

TEST_F(EPModelFixture, ZoneHVACExhaustControl_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneHVACExhaustControl exhaust(model);

  EXPECT_TRUE(exhaust.setFlowControlType("FollowSupply"));
  EXPECT_FALSE(exhaust.isFlowControlTypeDefaulted());
  EXPECT_TRUE(exhaust.setDesignExhaustFlowRate(0.15));
  EXPECT_FALSE(exhaust.isDesignExhaustFlowRateAutosized());
  ASSERT_TRUE(exhaust.designExhaustFlowRate());
  EXPECT_DOUBLE_EQ(0.15, exhaust.designExhaustFlowRate().value());

  exhaust.autosizeDesignExhaustFlowRate();
  EXPECT_TRUE(exhaust.isDesignExhaustFlowRateAutosized());

  exhaust.resetDesignExhaustFlowRate();
  EXPECT_TRUE(exhaust.isDesignExhaustFlowRateAutosized());

  exhaust.resetFlowControlType();
  EXPECT_TRUE(exhaust.isFlowControlTypeDefaulted());
}
