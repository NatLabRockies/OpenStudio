/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/FluidPropertiesGlycolConcentration.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, FluidPropertiesGlycolConcentration_DefaultConstructor) {
  Model model;
  FluidPropertiesGlycolConcentration fluidPropertiesGlycolConcentration(model);
  EXPECT_EQ(FluidPropertiesGlycolConcentration::iddObjectType(), fluidPropertiesGlycolConcentration.iddObject().type());
}

TEST_F(EPModelFixture, FluidPropertiesGlycolConcentration_ScalarAccessors_RoundTrip) {
  Model model;
  FluidPropertiesGlycolConcentration fluidPropertiesGlycolConcentration(model);

  const auto glycolTypeValues = FluidPropertiesGlycolConcentration::glycolTypeValues();
  EXPECT_FALSE(glycolTypeValues.empty());

  EXPECT_TRUE(fluidPropertiesGlycolConcentration.setGlycolType("EthyleneGlycol"));
  EXPECT_EQ("EthyleneGlycol", fluidPropertiesGlycolConcentration.glycolType());
  EXPECT_FALSE(fluidPropertiesGlycolConcentration.setGlycolType("NotAValidType"));
  EXPECT_EQ("EthyleneGlycol", fluidPropertiesGlycolConcentration.glycolType());

  EXPECT_FALSE(fluidPropertiesGlycolConcentration.glycolConcentration());
  EXPECT_TRUE(fluidPropertiesGlycolConcentration.setGlycolConcentration(0.35));
  ASSERT_TRUE(fluidPropertiesGlycolConcentration.glycolConcentration());
  EXPECT_DOUBLE_EQ(0.35, *fluidPropertiesGlycolConcentration.glycolConcentration());
  EXPECT_FALSE(fluidPropertiesGlycolConcentration.setGlycolConcentration(1.5));
  ASSERT_TRUE(fluidPropertiesGlycolConcentration.glycolConcentration());
  EXPECT_DOUBLE_EQ(0.35, *fluidPropertiesGlycolConcentration.glycolConcentration());
  fluidPropertiesGlycolConcentration.resetGlycolConcentration();
  EXPECT_FALSE(fluidPropertiesGlycolConcentration.glycolConcentration());
}
