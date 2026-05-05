/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Curve/CurveBicubic.hpp"

#include <algorithm>

using namespace openstudio::epmodel;

namespace {

std::string firstNonEmpty(const std::vector<std::string>& values) {
  auto it = std::find_if(values.begin(), values.end(), [](const auto& value) { return !value.empty(); });
  if (it != values.end()) {
    return *it;
  }
  return {};
}

}  // namespace

TEST_F(EPModelFixture, CurveBicubic_DefaultConstructor) {
  Model model;
  CurveBicubic curve(model);
  EXPECT_EQ(CurveBicubic::iddObjectType(), curve.iddObject().type());

  EXPECT_DOUBLE_EQ(0.0, curve.coefficient1Constant());
  EXPECT_DOUBLE_EQ(0.0, curve.coefficient10xTIMESYPOW2());
  EXPECT_DOUBLE_EQ(0.0, curve.minimumValueofx());
  EXPECT_DOUBLE_EQ(1.0, curve.maximumValueofx());
  EXPECT_DOUBLE_EQ(0.0, curve.minimumValueofy());
  EXPECT_DOUBLE_EQ(1.0, curve.maximumValueofy());
  EXPECT_FALSE(curve.minimumCurveOutput());
  EXPECT_FALSE(curve.maximumCurveOutput());
}

TEST_F(EPModelFixture, CurveBicubic_ScalarAccessors_RoundTrip) {
  Model model;
  CurveBicubic curve(model);

  EXPECT_TRUE(curve.setCoefficient1Constant(1.1));
  EXPECT_TRUE(curve.setCoefficient2x(2.2));
  EXPECT_TRUE(curve.setCoefficient3xPOW2(3.3));
  EXPECT_TRUE(curve.setCoefficient4y(4.4));
  EXPECT_TRUE(curve.setCoefficient5yPOW2(5.5));
  EXPECT_TRUE(curve.setCoefficient6xTIMESY(6.6));
  EXPECT_TRUE(curve.setCoefficient7xPOW3(7.7));
  EXPECT_TRUE(curve.setCoefficient8yPOW3(8.8));
  EXPECT_TRUE(curve.setCoefficient9xPOW2TIMESY(9.9));
  EXPECT_TRUE(curve.setCoefficient10xTIMESYPOW2(10.1));
  EXPECT_TRUE(curve.setMinimumValueofx(-2.0));
  EXPECT_TRUE(curve.setMaximumValueofx(3.0));
  EXPECT_TRUE(curve.setMinimumValueofy(-4.0));
  EXPECT_TRUE(curve.setMaximumValueofy(5.0));

  EXPECT_DOUBLE_EQ(1.1, curve.coefficient1Constant());
  EXPECT_DOUBLE_EQ(2.2, curve.coefficient2x());
  EXPECT_DOUBLE_EQ(3.3, curve.coefficient3xPOW2());
  EXPECT_DOUBLE_EQ(4.4, curve.coefficient4y());
  EXPECT_DOUBLE_EQ(5.5, curve.coefficient5yPOW2());
  EXPECT_DOUBLE_EQ(6.6, curve.coefficient6xTIMESY());
  EXPECT_DOUBLE_EQ(7.7, curve.coefficient7xPOW3());
  EXPECT_DOUBLE_EQ(8.8, curve.coefficient8yPOW3());
  EXPECT_DOUBLE_EQ(9.9, curve.coefficient9xPOW2TIMESY());
  EXPECT_DOUBLE_EQ(10.1, curve.coefficient10xTIMESYPOW2());
  EXPECT_DOUBLE_EQ(-2.0, curve.minimumValueofx());
  EXPECT_DOUBLE_EQ(3.0, curve.maximumValueofx());
  EXPECT_DOUBLE_EQ(-4.0, curve.minimumValueofy());
  EXPECT_DOUBLE_EQ(5.0, curve.maximumValueofy());

  EXPECT_TRUE(curve.setMinimumCurveOutput(-1.0));
  ASSERT_TRUE(curve.minimumCurveOutput());
  EXPECT_DOUBLE_EQ(-1.0, *curve.minimumCurveOutput());
  curve.resetMinimumCurveOutput();
  EXPECT_FALSE(curve.minimumCurveOutput());

  EXPECT_TRUE(curve.setMaximumCurveOutput(1.0));
  ASSERT_TRUE(curve.maximumCurveOutput());
  EXPECT_DOUBLE_EQ(1.0, *curve.maximumCurveOutput());
  curve.resetMaximumCurveOutput();
  EXPECT_FALSE(curve.maximumCurveOutput());

  const auto xValues = CurveBicubic::validInputUnitTypeforXValues();
  ASSERT_FALSE(xValues.empty());
  const auto xValue = firstNonEmpty(xValues);
  ASSERT_FALSE(xValue.empty());
  EXPECT_TRUE(curve.setInputUnitTypeforX(xValue));
  EXPECT_EQ(xValue, curve.inputUnitTypeforX());
  EXPECT_FALSE(curve.isInputUnitTypeforXDefaulted());
  curve.resetInputUnitTypeforX();
  EXPECT_TRUE(curve.isInputUnitTypeforXDefaulted());

  const auto yValues = CurveBicubic::validInputUnitTypeforYValues();
  ASSERT_FALSE(yValues.empty());
  const auto yValue = firstNonEmpty(yValues);
  ASSERT_FALSE(yValue.empty());
  EXPECT_TRUE(curve.setInputUnitTypeforY(yValue));
  EXPECT_EQ(yValue, curve.inputUnitTypeforY());
  EXPECT_FALSE(curve.isInputUnitTypeforYDefaulted());
  curve.resetInputUnitTypeforY();
  EXPECT_TRUE(curve.isInputUnitTypeforYDefaulted());

  const auto outputValues = CurveBicubic::validOutputUnitTypeValues();
  ASSERT_FALSE(outputValues.empty());
  const auto outputValue = firstNonEmpty(outputValues);
  ASSERT_FALSE(outputValue.empty());
  EXPECT_TRUE(curve.setOutputUnitType(outputValue));
  EXPECT_EQ(outputValue, curve.outputUnitType());
  EXPECT_FALSE(curve.isOutputUnitTypeDefaulted());
  curve.resetOutputUnitType();
  EXPECT_TRUE(curve.isOutputUnitTypeDefaulted());
}
