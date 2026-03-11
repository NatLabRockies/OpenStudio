/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ConstructionBase/CFactorUndergroundWallConstruction.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CFactorUndergroundWallConstruction_DefaultConstructor) {
  Model model;
  CFactorUndergroundWallConstruction object(model);
  EXPECT_EQ(CFactorUndergroundWallConstruction::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, CFactorUndergroundWallConstruction_ScalarAccessors_RoundTrip) {
  Model model;
  CFactorUndergroundWallConstruction object(model);

  EXPECT_DOUBLE_EQ(0.1, object.cFactor());
  EXPECT_DOUBLE_EQ(0.1, object.height());

  EXPECT_TRUE(object.setCFactor(2.4));
  EXPECT_DOUBLE_EQ(2.4, object.cFactor());

  EXPECT_TRUE(object.setHeight(3.6));
  EXPECT_DOUBLE_EQ(3.6, object.height());
}
