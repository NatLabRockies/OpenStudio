/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/SizingParameters.hpp"
#include "../ModelObject/SizingParameters_Impl.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SizingParameters_DefaultConstructor) {
  Model model;
  auto object = model.getUniqueModelObject<SizingParameters>();

  EXPECT_EQ(SizingParameters::iddObjectType(), object.iddObject().type());

  EXPECT_TRUE(object.isHeatingSizingFactorDefaulted());
  EXPECT_DOUBLE_EQ(1.0, object.heatingSizingFactor());

  EXPECT_TRUE(object.isCoolingSizingFactorDefaulted());
  EXPECT_DOUBLE_EQ(1.0, object.coolingSizingFactor());

  EXPECT_FALSE(object.timestepsinAveragingWindow());
}

TEST_F(EPModelFixture, SizingParameters_ScalarAccessors_RoundTrip) {
  Model model;
  auto object = model.getUniqueModelObject<SizingParameters>();

  EXPECT_TRUE(object.setHeatingSizingFactor(1.4));
  EXPECT_FALSE(object.isHeatingSizingFactorDefaulted());
  EXPECT_DOUBLE_EQ(1.4, object.heatingSizingFactor());
  object.resetHeatingSizingFactor();
  EXPECT_TRUE(object.isHeatingSizingFactorDefaulted());
  EXPECT_DOUBLE_EQ(1.0, object.heatingSizingFactor());

  EXPECT_TRUE(object.setCoolingSizingFactor(1.3));
  EXPECT_FALSE(object.isCoolingSizingFactorDefaulted());
  EXPECT_DOUBLE_EQ(1.3, object.coolingSizingFactor());
  object.resetCoolingSizingFactor();
  EXPECT_TRUE(object.isCoolingSizingFactorDefaulted());
  EXPECT_DOUBLE_EQ(1.0, object.coolingSizingFactor());

  EXPECT_TRUE(object.setTimestepsinAveragingWindow(6));
  ASSERT_TRUE(object.timestepsinAveragingWindow());
  EXPECT_EQ(6, object.timestepsinAveragingWindow().get());
  object.resetTimestepsinAveragingWindow();
  EXPECT_FALSE(object.timestepsinAveragingWindow());
}
