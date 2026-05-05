/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Curve/CurveExponentialSkewNormal.hpp"

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

TEST_F(EPModelFixture, CurveExponentialSkewNormal_DefaultConstructor) {
  Model model;
  CurveExponentialSkewNormal curve(model);
  EXPECT_EQ(CurveExponentialSkewNormal::iddObjectType(), curve.iddObject().type());

  EXPECT_DOUBLE_EQ(1.0, curve.coefficient1C1());
  EXPECT_DOUBLE_EQ(1.0, curve.coefficient2C2());
  EXPECT_DOUBLE_EQ(-1.0, curve.coefficient3C3());
  EXPECT_DOUBLE_EQ(1.0, curve.coefficient4C4());
  EXPECT_DOUBLE_EQ(-1.0, curve.minimumValueofx());
  EXPECT_DOUBLE_EQ(1.0, curve.maximumValueofx());
  EXPECT_FALSE(curve.minimumCurveOutput());
  EXPECT_FALSE(curve.maximumCurveOutput());
  EXPECT_TRUE(curve.isInputUnitTypeforxDefaulted());
  EXPECT_TRUE(curve.isOutputUnitTypeDefaulted());
}

TEST_F(EPModelFixture, CurveExponentialSkewNormal_ScalarAccessors_RoundTrip) {
  Model model;
  CurveExponentialSkewNormal curve(model);

  EXPECT_TRUE(curve.setCoefficient1C1(1.1));
  EXPECT_TRUE(curve.setCoefficient2C2(2.2));
  EXPECT_TRUE(curve.setCoefficient3C3(3.3));
  EXPECT_TRUE(curve.setCoefficient4C4(4.4));
  EXPECT_TRUE(curve.setMinimumValueofx(-2.0));
  EXPECT_TRUE(curve.setMaximumValueofx(3.0));

  EXPECT_DOUBLE_EQ(1.1, curve.coefficient1C1());
  EXPECT_DOUBLE_EQ(2.2, curve.coefficient2C2());
  EXPECT_DOUBLE_EQ(3.3, curve.coefficient3C3());
  EXPECT_DOUBLE_EQ(4.4, curve.coefficient4C4());
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

  const auto xValues = CurveExponentialSkewNormal::validInputUnitTypeforxValues();
  ASSERT_FALSE(xValues.empty());
  const auto xDefault = curve.inputUnitTypeforx();
  auto xValue = firstNonEmptyDifferentFrom(xValues, xDefault);
  if (xValue.empty()) {
    xValue = firstNonEmpty(xValues);
  }
  ASSERT_FALSE(xValue.empty());
  EXPECT_TRUE(curve.setInputUnitTypeforx(xValue));
  EXPECT_EQ(xValue, curve.inputUnitTypeforx());
  if (!openstudio::istringEqual(xValue, xDefault)) {
    EXPECT_FALSE(curve.isInputUnitTypeforxDefaulted());
  }
  curve.resetInputUnitTypeforx();
  EXPECT_TRUE(curve.isInputUnitTypeforxDefaulted());

  const auto outputValues = CurveExponentialSkewNormal::validOutputUnitTypeValues();
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
