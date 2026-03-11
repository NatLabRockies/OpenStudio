/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/DemandManagerLights.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, DemandManagerLights_DefaultConstructor) {
  Model model;
  DemandManagerLights object(model);
  EXPECT_EQ(DemandManagerLights::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, DemandManagerLights_ScalarAccessors_RoundTrip) {
  Model model;
  DemandManagerLights object(model);

  EXPECT_TRUE(object.setLimitControl("Fixed"));
  EXPECT_EQ("Fixed", object.limitControl());

  EXPECT_TRUE(object.setMinimumLimitDuration(30));
  ASSERT_TRUE(object.minimumLimitDuration());
  EXPECT_EQ(30, object.minimumLimitDuration().get());
  object.resetMinimumLimitDuration();
  EXPECT_FALSE(object.minimumLimitDuration());

  EXPECT_TRUE(object.setMaximumLimitFraction(0.6));
  ASSERT_TRUE(object.maximumLimitFraction());
  EXPECT_DOUBLE_EQ(0.6, object.maximumLimitFraction().get());
  object.resetMaximumLimitFraction();
  EXPECT_FALSE(object.maximumLimitFraction());

  EXPECT_TRUE(object.setLimitStepChange(0.05));
  ASSERT_TRUE(object.limitStepChange());
  EXPECT_DOUBLE_EQ(0.05, object.limitStepChange().get());
  object.resetLimitStepChange();
  EXPECT_FALSE(object.limitStepChange());

  EXPECT_TRUE(object.setSelectionControl("RotateOne"));
  EXPECT_EQ("RotateOne", object.selectionControl());

  EXPECT_TRUE(object.setRotationDuration(15));
  ASSERT_TRUE(object.rotationDuration());
  EXPECT_EQ(15, object.rotationDuration().get());
  object.resetRotationDuration();
  EXPECT_FALSE(object.rotationDuration());
}
