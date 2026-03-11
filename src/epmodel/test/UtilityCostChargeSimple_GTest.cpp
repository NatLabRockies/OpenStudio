/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/UtilityCostChargeSimple.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, UtilityCostChargeSimple_DefaultConstructor) {
  Model model;
  UtilityCostChargeSimple simple(model);

  EXPECT_EQ(UtilityCostChargeSimple::iddObjectType(), simple.iddObject().type());
  EXPECT_FALSE(UtilityCostChargeSimple::seasonValues().empty());
  EXPECT_FALSE(UtilityCostChargeSimple::categoryVariableNameValues().empty());
}

TEST_F(EPModelFixture, UtilityCostChargeSimple_ScalarAccessors_RoundTrip) {
  Model model;
  UtilityCostChargeSimple simple(model);

  EXPECT_TRUE(simple.setSourceVariable("totalEnergy"));
  EXPECT_TRUE(simple.setSeason("Winter"));
  EXPECT_TRUE(simple.setCategoryVariableName("Taxes"));
  EXPECT_TRUE(simple.setCostPerUnitValueorVariableName("0.05"));

  EXPECT_EQ("totalEnergy", simple.sourceVariable());
  EXPECT_TRUE(simple.season());
  EXPECT_EQ("Winter", simple.season().get());
  EXPECT_EQ("Taxes", simple.categoryVariableName());
  EXPECT_EQ("0.05", simple.costPerUnitValueorVariableName());

  simple.resetSeason();
  EXPECT_FALSE(simple.season());
}
