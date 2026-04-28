/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/DuctLossConduction.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, DuctLossConduction_DefaultConstructor) {
  Model model;
  DuctLossConduction ductLossConduction(model);
  EXPECT_EQ(DuctLossConduction::iddObjectType(), ductLossConduction.iddObject().type());
}

TEST_F(EPModelFixture, DuctLossConduction_ScalarAccessors_RoundTrip) {
  Model model;
  DuctLossConduction ductLossConduction(model);

  const auto environmentTypeValues = DuctLossConduction::environmentTypeValues();
  EXPECT_FALSE(environmentTypeValues.empty());
  EXPECT_TRUE(ductLossConduction.isEnvironmentTypeDefaulted());
  EXPECT_EQ("Zone", ductLossConduction.environmentType());

  EXPECT_TRUE(ductLossConduction.setEnvironmentType("Schedule"));
  EXPECT_EQ("Schedule", ductLossConduction.environmentType());
  EXPECT_FALSE(ductLossConduction.isEnvironmentTypeDefaulted());

  ductLossConduction.resetEnvironmentType();
  EXPECT_TRUE(ductLossConduction.isEnvironmentTypeDefaulted());
  EXPECT_EQ("Zone", ductLossConduction.environmentType());
}
