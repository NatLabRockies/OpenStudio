/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/DemandManagerVentilation.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, DemandManagerVentilation_DefaultConstructor) {
  Model model;
  DemandManagerVentilation object(model);
  EXPECT_EQ(DemandManagerVentilation::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, DemandManagerVentilation_ScalarAccessors_RoundTrip) {
  Model model;
  DemandManagerVentilation object(model);

  EXPECT_FALSE(DemandManagerVentilation::limitControlValues().empty());
  EXPECT_FALSE(DemandManagerVentilation::selectionControlValues().empty());

  EXPECT_TRUE(object.setLimitControl("FixedRate"));
  EXPECT_EQ("FixedRate", object.limitControl());

  EXPECT_TRUE(object.setMinimumLimitDuration(30));
  ASSERT_TRUE(object.minimumLimitDuration());
  EXPECT_EQ(30, object.minimumLimitDuration().get());
  object.resetMinimumLimitDuration();
  EXPECT_FALSE(object.minimumLimitDuration());

  EXPECT_TRUE(object.setFixedRate(0.2));
  ASSERT_TRUE(object.fixedRate());
  EXPECT_DOUBLE_EQ(0.2, object.fixedRate().get());
  object.resetFixedRate();
  EXPECT_FALSE(object.fixedRate());

  EXPECT_TRUE(object.setReductionRatio(0.35));
  ASSERT_TRUE(object.reductionRatio());
  EXPECT_DOUBLE_EQ(0.35, object.reductionRatio().get());
  EXPECT_FALSE(object.setReductionRatio(1.1));
  EXPECT_DOUBLE_EQ(0.35, object.reductionRatio().get());
  object.resetReductionRatio();
  EXPECT_FALSE(object.reductionRatio());

  EXPECT_TRUE(object.setLimitStepChange(0.05));
  ASSERT_TRUE(object.limitStepChange());
  EXPECT_DOUBLE_EQ(0.05, object.limitStepChange().get());
  object.resetLimitStepChange();
  EXPECT_FALSE(object.limitStepChange());

  EXPECT_TRUE(object.isSelectionControlDefaulted());
  EXPECT_EQ("All", object.selectionControl());
  EXPECT_TRUE(object.setSelectionControl("RotateOne"));
  EXPECT_EQ("RotateOne", object.selectionControl());
  EXPECT_FALSE(object.isSelectionControlDefaulted());
  object.resetSelectionControl();
  EXPECT_TRUE(object.isSelectionControlDefaulted());
  EXPECT_EQ("All", object.selectionControl());

  EXPECT_TRUE(object.setRotationDuration(15));
  ASSERT_TRUE(object.rotationDuration());
  EXPECT_EQ(15, object.rotationDuration().get());
  object.resetRotationDuration();
  EXPECT_FALSE(object.rotationDuration());
}
