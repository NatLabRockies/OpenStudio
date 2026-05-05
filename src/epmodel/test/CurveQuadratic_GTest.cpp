/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Curve/CurveQuadratic.hpp"

#include <utilities/core/StringHelpers.hpp>

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

std::string firstNonEmptyDifferentFrom(const std::vector<std::string>& values, const std::string& baseline) {
  auto it =
    std::find_if(values.begin(), values.end(), [&](const auto& value) { return !value.empty() && !openstudio::istringEqual(value, baseline); });
  if (it != values.end()) {
    return *it;
  }
  return {};
}

}  // namespace

TEST_F(EPModelFixture, CurveQuadratic_DefaultConstructor) {
  Model model;
  CurveQuadratic curve(model);
  EXPECT_EQ(CurveQuadratic::iddObjectType(), curve.iddObject().type());

  EXPECT_DOUBLE_EQ(0.0, curve.coefficient1Constant());
  EXPECT_DOUBLE_EQ(0.0, curve.coefficient2x());
  EXPECT_DOUBLE_EQ(1.0, curve.coefficient3xPOW2());
  EXPECT_DOUBLE_EQ(0.0, curve.minimumValueofx());
  EXPECT_DOUBLE_EQ(1.0, curve.maximumValueofx());
  EXPECT_FALSE(curve.minimumCurveOutput());
  EXPECT_FALSE(curve.maximumCurveOutput());
  EXPECT_TRUE(curve.isInputUnitTypeforXDefaulted());
  EXPECT_TRUE(curve.isOutputUnitTypeDefaulted());
}

TEST_F(EPModelFixture, CurveQuadratic_ScalarAccessors_RoundTrip) {
  Model model;
  CurveQuadratic curve(model);

  EXPECT_TRUE(curve.setCoefficient1Constant(1.1));
  EXPECT_TRUE(curve.setCoefficient2x(2.2));
  EXPECT_TRUE(curve.setCoefficient3xPOW2(3.3));
  EXPECT_TRUE(curve.setMinimumValueofx(-2.0));
  EXPECT_TRUE(curve.setMaximumValueofx(3.0));

  EXPECT_DOUBLE_EQ(1.1, curve.coefficient1Constant());
  EXPECT_DOUBLE_EQ(2.2, curve.coefficient2x());
  EXPECT_DOUBLE_EQ(3.3, curve.coefficient3xPOW2());
  EXPECT_DOUBLE_EQ(-2.0, curve.minimumValueofx());
  EXPECT_DOUBLE_EQ(3.0, curve.maximumValueofx());

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

  const auto xValues = CurveQuadratic::validInputUnitTypeforXValues();
  ASSERT_FALSE(xValues.empty());
  const auto xDefault = curve.inputUnitTypeforX();
  auto xValue = firstNonEmptyDifferentFrom(xValues, xDefault);
  if (xValue.empty()) {
    xValue = firstNonEmpty(xValues);
  }
  ASSERT_FALSE(xValue.empty());
  EXPECT_TRUE(curve.setInputUnitTypeforX(xValue));
  EXPECT_EQ(xValue, curve.inputUnitTypeforX());
  if (!openstudio::istringEqual(xValue, xDefault)) {
    EXPECT_FALSE(curve.isInputUnitTypeforXDefaulted());
  }
  curve.resetInputUnitTypeforX();
  EXPECT_TRUE(curve.isInputUnitTypeforXDefaulted());

  const auto outputValues = CurveQuadratic::validOutputUnitTypeValues();
  ASSERT_FALSE(outputValues.empty());
  const auto outputDefault = curve.outputUnitType();
  auto outputValue = firstNonEmptyDifferentFrom(outputValues, outputDefault);
  if (outputValue.empty()) {
    outputValue = firstNonEmpty(outputValues);
  }
  ASSERT_FALSE(outputValue.empty());
  EXPECT_TRUE(curve.setOutputUnitType(outputValue));
  EXPECT_EQ(outputValue, curve.outputUnitType());
  if (!openstudio::istringEqual(outputValue, outputDefault)) {
    EXPECT_FALSE(curve.isOutputUnitTypeDefaulted());
  }
  curve.resetOutputUnitType();
  EXPECT_TRUE(curve.isOutputUnitTypeDefaulted());
}
