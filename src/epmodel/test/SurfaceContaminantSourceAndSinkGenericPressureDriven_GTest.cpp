/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/SurfaceContaminantSourceAndSinkGenericPressureDriven.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SurfaceContaminantSourceAndSinkGenericPressureDriven_DefaultConstructor) {
  Model model;
  SurfaceContaminantSourceAndSinkGenericPressureDriven obj(model);
  EXPECT_EQ(SurfaceContaminantSourceAndSinkGenericPressureDriven::iddObjectType(), obj.iddObject().type());
}

TEST_F(EPModelFixture, SurfaceContaminantSourceAndSinkGenericPressureDriven_ScalarAccessors_RoundTrip) {
  Model model;
  SurfaceContaminantSourceAndSinkGenericPressureDriven obj(model);

  // Design Generation Rate Coefficient: optional, minimum 0.0 (inclusive), no default
  EXPECT_FALSE(obj.designGenerationRateCoefficient());
  EXPECT_TRUE(obj.setDesignGenerationRateCoefficient(0.5));
  ASSERT_TRUE(obj.designGenerationRateCoefficient());
  EXPECT_DOUBLE_EQ(0.5, obj.designGenerationRateCoefficient().get());
  // boundary: 0.0 is valid (minimum 0.0 inclusive)
  EXPECT_TRUE(obj.setDesignGenerationRateCoefficient(0.0));
  ASSERT_TRUE(obj.designGenerationRateCoefficient());
  EXPECT_DOUBLE_EQ(0.0, obj.designGenerationRateCoefficient().get());
  // below minimum should fail
  EXPECT_FALSE(obj.setDesignGenerationRateCoefficient(-0.1));
  // reset
  obj.resetDesignGenerationRateCoefficient();
  EXPECT_FALSE(obj.designGenerationRateCoefficient());

  // Generation Exponent: optional, minimum> 0.0 (exclusive), maximum 1.0, no default
  EXPECT_FALSE(obj.generationExponent());
  EXPECT_TRUE(obj.setGenerationExponent(0.5));
  ASSERT_TRUE(obj.generationExponent());
  EXPECT_DOUBLE_EQ(0.5, obj.generationExponent().get());
  // boundary: 0.0 is invalid (minimum> 0.0 exclusive)
  EXPECT_FALSE(obj.setGenerationExponent(0.0));
  // negative should fail
  EXPECT_FALSE(obj.setGenerationExponent(-1.0));
  // small positive should succeed
  EXPECT_TRUE(obj.setGenerationExponent(0.001));
  ASSERT_TRUE(obj.generationExponent());
  EXPECT_DOUBLE_EQ(0.001, obj.generationExponent().get());
  // maximum boundary: 1.0 should succeed
  EXPECT_TRUE(obj.setGenerationExponent(1.0));
  ASSERT_TRUE(obj.generationExponent());
  EXPECT_DOUBLE_EQ(1.0, obj.generationExponent().get());
  // above maximum should fail
  EXPECT_FALSE(obj.setGenerationExponent(1.1));
  // reset
  obj.resetGenerationExponent();
  EXPECT_FALSE(obj.generationExponent());
}
