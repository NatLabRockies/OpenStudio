/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/MaterialPropertyMoisturePenetrationDepthSettings.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, MaterialPropertyMoisturePenetrationDepthSettings_DefaultConstructor) {
  Model model;
  MaterialPropertyMoisturePenetrationDepthSettings object(model);
  EXPECT_EQ(MaterialPropertyMoisturePenetrationDepthSettings::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, MaterialPropertyMoisturePenetrationDepthSettings_ScalarAccessors_RoundTrip) {
  Model model;
  MaterialPropertyMoisturePenetrationDepthSettings object(model);

  EXPECT_TRUE(object.setWaterVaporDiffusionResistanceFactor(8.9));
  EXPECT_DOUBLE_EQ(8.9, object.waterVaporDiffusionResistanceFactor());

  EXPECT_TRUE(object.setMoistureEquationCoefficientA(0.0069));
  EXPECT_TRUE(object.setMoistureEquationCoefficientB(0.9066));
  EXPECT_TRUE(object.setMoistureEquationCoefficientC(0.0404));
  EXPECT_TRUE(object.setMoistureEquationCoefficientD(22.1121));
  EXPECT_DOUBLE_EQ(0.0069, object.moistureEquationCoefficientA());
  EXPECT_DOUBLE_EQ(0.9066, object.moistureEquationCoefficientB());
  EXPECT_DOUBLE_EQ(0.0404, object.moistureEquationCoefficientC());
  EXPECT_DOUBLE_EQ(22.1121, object.moistureEquationCoefficientD());

  EXPECT_TRUE(object.setMoistureEquationCoefficients(0.019, 1.0, 0.0, 1.0));
  const auto coefficients = object.moistureEquationCoefficients();
  ASSERT_EQ(4u, coefficients.size());
  EXPECT_DOUBLE_EQ(0.019, coefficients[0]);
  EXPECT_DOUBLE_EQ(1.0, coefficients[1]);
  EXPECT_DOUBLE_EQ(0.0, coefficients[2]);
  EXPECT_DOUBLE_EQ(1.0, coefficients[3]);

  EXPECT_TRUE(object.setSurfaceLayerPenetrationDepth(0.1));
  ASSERT_TRUE(object.surfaceLayerPenetrationDepth());
  EXPECT_DOUBLE_EQ(0.1, object.surfaceLayerPenetrationDepth().get());
  EXPECT_FALSE(object.isSurfaceLayerPenetrationDepthAutocalculated());
  object.autocalculateSurfaceLayerPenetrationDepth();
  EXPECT_FALSE(object.surfaceLayerPenetrationDepth());
  EXPECT_TRUE(object.isSurfaceLayerPenetrationDepthAutocalculated());

  EXPECT_TRUE(object.setDeepLayerPenetrationDepth(0.0));
  ASSERT_TRUE(object.deepLayerPenetrationDepth());
  EXPECT_DOUBLE_EQ(0.0, object.deepLayerPenetrationDepth().get());
  EXPECT_FALSE(object.isDeepLayerPenetrationDepthAutocalculated());
  object.autocalculateDeepLayerPenetrationDepth();
  EXPECT_FALSE(object.deepLayerPenetrationDepth());
  EXPECT_TRUE(object.isDeepLayerPenetrationDepthAutocalculated());

  EXPECT_TRUE(object.setCoatingLayerThickness(0.005));
  EXPECT_TRUE(object.setCoatingLayerWaterVaporDiffusionResistanceFactor(140.0));
  EXPECT_DOUBLE_EQ(0.005, object.coatingLayerThickness());
  EXPECT_DOUBLE_EQ(140.0, object.coatingLayerWaterVaporDiffusionResistanceFactor());
}
