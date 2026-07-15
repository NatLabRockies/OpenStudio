/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Curve/CurveTriquadratic.hpp"

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

TEST_F(EPModelFixture, CurveTriquadratic_DefaultConstructor) {
  Model model;
  CurveTriquadratic curve(model);
  EXPECT_EQ(CurveTriquadratic::iddObjectType(), curve.iddObject().type());

  EXPECT_FALSE(curve.coefficient1Constant());
  EXPECT_FALSE(curve.coefficient27xTIMESYTIMESZ());
  EXPECT_FALSE(curve.minimumValueofx());
  EXPECT_FALSE(curve.maximumValueofx());
  EXPECT_FALSE(curve.minimumValueofy());
  EXPECT_FALSE(curve.maximumValueofy());
  EXPECT_FALSE(curve.minimumValueofz());
  EXPECT_FALSE(curve.maximumValueofz());
  EXPECT_FALSE(curve.minimumCurveOutput());
  EXPECT_FALSE(curve.maximumCurveOutput());

  EXPECT_TRUE(curve.isInputUnitTypeforXDefaulted());
  EXPECT_TRUE(curve.isInputUnitTypeforYDefaulted());
  EXPECT_TRUE(curve.isInputUnitTypeforZDefaulted());
  EXPECT_TRUE(curve.isOutputUnitTypeDefaulted());
}

TEST_F(EPModelFixture, CurveTriquadratic_ScalarAccessors_RoundTrip) {
  Model model;
  CurveTriquadratic curve(model);

  EXPECT_TRUE(curve.setCoefficient1Constant(1.1));
  EXPECT_TRUE(curve.setCoefficient8xPOW2TIMESYPOW2(8.8));
  EXPECT_TRUE(curve.setCoefficient14xTIMESZPOW2(14.4));
  EXPECT_TRUE(curve.setCoefficient20xPOW2TIMESYPOW2TIMESZPOW2(20.2));
  EXPECT_TRUE(curve.setCoefficient27xTIMESYTIMESZ(27.7));

  ASSERT_TRUE(curve.coefficient1Constant());
  ASSERT_TRUE(curve.coefficient8xPOW2TIMESYPOW2());
  ASSERT_TRUE(curve.coefficient14xTIMESZPOW2());
  ASSERT_TRUE(curve.coefficient20xPOW2TIMESYPOW2TIMESZPOW2());
  ASSERT_TRUE(curve.coefficient27xTIMESYTIMESZ());

  EXPECT_DOUBLE_EQ(1.1, *curve.coefficient1Constant());
  EXPECT_DOUBLE_EQ(8.8, *curve.coefficient8xPOW2TIMESYPOW2());
  EXPECT_DOUBLE_EQ(14.4, *curve.coefficient14xTIMESZPOW2());
  EXPECT_DOUBLE_EQ(20.2, *curve.coefficient20xPOW2TIMESYPOW2TIMESZPOW2());
  EXPECT_DOUBLE_EQ(27.7, *curve.coefficient27xTIMESYTIMESZ());

  curve.resetCoefficient8xPOW2TIMESYPOW2();
  EXPECT_FALSE(curve.coefficient8xPOW2TIMESYPOW2());

  EXPECT_TRUE(curve.setMinimumValueofx(-1.0));
  EXPECT_TRUE(curve.setMaximumValueofx(1.0));
  EXPECT_TRUE(curve.setMinimumValueofy(-2.0));
  EXPECT_TRUE(curve.setMaximumValueofy(2.0));
  EXPECT_TRUE(curve.setMinimumValueofz(-3.0));
  EXPECT_TRUE(curve.setMaximumValueofz(3.0));

  ASSERT_TRUE(curve.minimumValueofx());
  ASSERT_TRUE(curve.maximumValueofx());
  ASSERT_TRUE(curve.minimumValueofy());
  ASSERT_TRUE(curve.maximumValueofy());
  ASSERT_TRUE(curve.minimumValueofz());
  ASSERT_TRUE(curve.maximumValueofz());

  EXPECT_DOUBLE_EQ(-1.0, *curve.minimumValueofx());
  EXPECT_DOUBLE_EQ(1.0, *curve.maximumValueofx());
  EXPECT_DOUBLE_EQ(-2.0, *curve.minimumValueofy());
  EXPECT_DOUBLE_EQ(2.0, *curve.maximumValueofy());
  EXPECT_DOUBLE_EQ(-3.0, *curve.minimumValueofz());
  EXPECT_DOUBLE_EQ(3.0, *curve.maximumValueofz());

  EXPECT_TRUE(curve.setMinimumCurveOutput(-10.0));
  EXPECT_TRUE(curve.setMaximumCurveOutput(10.0));
  ASSERT_TRUE(curve.minimumCurveOutput());
  ASSERT_TRUE(curve.maximumCurveOutput());
  EXPECT_DOUBLE_EQ(-10.0, *curve.minimumCurveOutput());
  EXPECT_DOUBLE_EQ(10.0, *curve.maximumCurveOutput());

  curve.resetMinimumCurveOutput();
  curve.resetMaximumCurveOutput();
  EXPECT_FALSE(curve.minimumCurveOutput());
  EXPECT_FALSE(curve.maximumCurveOutput());

  const auto xValues = CurveTriquadratic::validInputUnitTypeforXValues();
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

  const auto yValues = CurveTriquadratic::validInputUnitTypeforYValues();
  ASSERT_FALSE(yValues.empty());
  const auto yDefault = curve.inputUnitTypeforY();
  auto yValue = firstNonEmptyDifferentFrom(yValues, yDefault);
  if (yValue.empty()) {
    yValue = firstNonEmpty(yValues);
  }
  ASSERT_FALSE(yValue.empty());
  EXPECT_TRUE(curve.setInputUnitTypeforY(yValue));
  EXPECT_EQ(yValue, curve.inputUnitTypeforY());
  if (!openstudio::istringEqual(yValue, yDefault)) {
    EXPECT_FALSE(curve.isInputUnitTypeforYDefaulted());
  }
  curve.resetInputUnitTypeforY();
  EXPECT_TRUE(curve.isInputUnitTypeforYDefaulted());

  const auto zValues = CurveTriquadratic::validInputUnitTypeforZValues();
  ASSERT_FALSE(zValues.empty());
  const auto zDefault = curve.inputUnitTypeforZ();
  auto zValue = firstNonEmptyDifferentFrom(zValues, zDefault);
  if (zValue.empty()) {
    zValue = firstNonEmpty(zValues);
  }
  ASSERT_FALSE(zValue.empty());
  EXPECT_TRUE(curve.setInputUnitTypeforZ(zValue));
  EXPECT_EQ(zValue, curve.inputUnitTypeforZ());
  if (!openstudio::istringEqual(zValue, zDefault)) {
    EXPECT_FALSE(curve.isInputUnitTypeforZDefaulted());
  }
  curve.resetInputUnitTypeforZ();
  EXPECT_TRUE(curve.isInputUnitTypeforZDefaulted());

  const auto outputValues = CurveTriquadratic::validOutputUnitTypeValues();
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
