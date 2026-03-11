/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>
#include <string>

#include "EPModelFixture.hpp"
#include "../ResourceObject/SurfacePropertyOtherSideConditionsModel.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SurfacePropertyOtherSideConditionsModel_DefaultConstructor) {
  Model model;
  SurfacePropertyOtherSideConditionsModel other(model);
  EXPECT_EQ(SurfacePropertyOtherSideConditionsModel::iddObjectType(), other.iddObject().type());
}

TEST_F(EPModelFixture, SurfacePropertyOtherSideConditionsModel_ScalarAccessors_RoundTrip) {
  Model model;
  SurfacePropertyOtherSideConditionsModel other(model);

  const auto values = SurfacePropertyOtherSideConditionsModel::typeOfModelingValues();
  const auto value = values.empty() ? std::string("GapConvectionRadiation") : values.front();
  EXPECT_TRUE(other.setTypeOfModeling(value));
  EXPECT_EQ(value, other.typeOfModeling());
  EXPECT_FALSE(other.isTypeOfModelingDefaulted());
  other.resetTypeOfModeling();
  EXPECT_TRUE(other.isTypeOfModelingDefaulted());
}
