/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../StraightComponent/SolarCollectorFlatPlateWater.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SolarCollectorFlatPlateWater_DefaultConstructor) {
  Model model;
  SolarCollectorFlatPlateWater object(model);
  EXPECT_EQ(SolarCollectorFlatPlateWater::iddObjectType(), object.iddObject().type());
  EXPECT_FALSE(object.nameString().empty());
}

TEST_F(EPModelFixture, SolarCollectorFlatPlateWater_ScalarAccessors_RoundTrip) {
  Model model;
  SolarCollectorFlatPlateWater object(model);

  EXPECT_FALSE(object.maximumFlowRate());

  EXPECT_TRUE(object.setMaximumFlowRate(0.00123));
  ASSERT_TRUE(object.maximumFlowRate());
  EXPECT_DOUBLE_EQ(0.00123, object.maximumFlowRate().get());

  object.resetMaximumFlowRate();
  EXPECT_FALSE(object.maximumFlowRate());
}
