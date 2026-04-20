/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/DemandManagerThermostats.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, DemandManagerThermostats_DefaultConstructor) {
  Model model;
  DemandManagerThermostats object(model);
  EXPECT_EQ(DemandManagerThermostats::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, DemandManagerThermostats_ScalarAccessors_RoundTrip) {
  Model model;
  DemandManagerThermostats object(model);

  EXPECT_TRUE(object.setResetControl("Fixed"));
  EXPECT_EQ("Fixed", object.resetControl());

  EXPECT_TRUE(object.setMinimumResetDuration(30));
  ASSERT_TRUE(object.minimumResetDuration());
  EXPECT_EQ(30, object.minimumResetDuration().get());
  object.resetMinimumResetDuration();
  EXPECT_FALSE(object.minimumResetDuration());

  EXPECT_TRUE(object.setMaximumHeatingSetpointReset(1.2));
  EXPECT_DOUBLE_EQ(1.2, object.maximumHeatingSetpointReset());

  EXPECT_TRUE(object.setMaximumCoolingSetpointReset(1.3));
  EXPECT_DOUBLE_EQ(1.3, object.maximumCoolingSetpointReset());

  EXPECT_TRUE(object.setResetStepChange(0.1));
  ASSERT_TRUE(object.resetStepChange());
  EXPECT_DOUBLE_EQ(0.1, object.resetStepChange().get());
  object.resetResetStepChange();
  EXPECT_FALSE(object.resetStepChange());

  EXPECT_TRUE(object.setSelectionControl("RotateOne"));
  EXPECT_EQ("RotateOne", object.selectionControl());

  EXPECT_TRUE(object.setRotationDuration(15));
  ASSERT_TRUE(object.rotationDuration());
  EXPECT_EQ(15, object.rotationDuration().get());
  object.resetRotationDuration();
  EXPECT_FALSE(object.rotationDuration());
}
