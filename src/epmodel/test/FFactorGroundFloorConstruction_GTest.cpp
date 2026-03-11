/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ConstructionBase/FFactorGroundFloorConstruction.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, FFactorGroundFloorConstruction_DefaultConstructor) {
  Model model;
  FFactorGroundFloorConstruction object(model);
  EXPECT_EQ(FFactorGroundFloorConstruction::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, FFactorGroundFloorConstruction_ScalarAccessors_RoundTrip) {
  Model model;
  FFactorGroundFloorConstruction object(model);

  EXPECT_DOUBLE_EQ(0.1, object.fFactor());
  EXPECT_DOUBLE_EQ(0.1, object.area());
  EXPECT_DOUBLE_EQ(0.1, object.perimeterExposed());

  EXPECT_TRUE(object.setFFactor(2.5));
  EXPECT_DOUBLE_EQ(2.5, object.fFactor());

  EXPECT_TRUE(object.setArea(55.0));
  EXPECT_DOUBLE_EQ(55.0, object.area());

  EXPECT_TRUE(object.setPerimeterExposed(18.2));
  EXPECT_DOUBLE_EQ(18.2, object.perimeterExposed());
}
