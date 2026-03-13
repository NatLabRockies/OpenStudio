/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Curve/CurveChillerPartLoadWithLift.hpp"

#include <utilities/core/StringHelpers.hpp>

#include <algorithm>

using namespace openstudio::epmodel;

namespace {

std::string firstNonEmpty(const std::vector<std::string>& values) {
  auto it = std::find_if(values.begin(), values.end(), [](const auto& value) {
    return !value.empty();
  });
  if (it != values.end()) {
    return *it;
  }
  return {};
}

std::string firstNonEmptyDifferentFrom(const std::vector<std::string>& values, const std::string& baseline) {
  auto it = std::find_if(values.begin(), values.end(), [&](const auto& value) {
    return !value.empty() && !openstudio::istringEqual(value, baseline);
  });
  if (it != values.end()) {
    return *it;
  }
  return {};
}

}  // namespace

TEST_F(EPModelFixture, CurveChillerPartLoadWithLift_DefaultConstructor) {
  Model model;
  CurveChillerPartLoadWithLift curve(model);
  EXPECT_EQ(CurveChillerPartLoadWithLift::iddObjectType(), curve.iddObject().type());

  EXPECT_DOUBLE_EQ(0.0, curve.coefficient1C1());
  EXPECT_DOUBLE_EQ(0.0, curve.coefficient2C2());
  EXPECT_DOUBLE_EQ(0.0, curve.coefficient3C3());
  EXPECT_DOUBLE_EQ(0.0, curve.coefficient4C4());
  EXPECT_DOUBLE_EQ(0.0, curve.coefficient5C5());
  EXPECT_DOUBLE_EQ(0.0, curve.coefficient6C6());
  EXPECT_DOUBLE_EQ(0.0, curve.coefficient7C7());
  EXPECT_DOUBLE_EQ(0.0, curve.coefficient8C8());
  EXPECT_DOUBLE_EQ(0.0, curve.coefficient9C9());
  EXPECT_DOUBLE_EQ(0.0, curve.coefficient10C10());
  EXPECT_DOUBLE_EQ(0.0, curve.coefficient11C11());
  EXPECT_DOUBLE_EQ(0.0, curve.coefficient12C12());
  EXPECT_DOUBLE_EQ(0.0, curve.minimumValueofx());
  EXPECT_DOUBLE_EQ(1.0, curve.maximumValueofx());
  EXPECT_DOUBLE_EQ(0.0, curve.minimumValueofy());
  EXPECT_DOUBLE_EQ(1.0, curve.maximumValueofy());
  EXPECT_DOUBLE_EQ(0.0, curve.minimumValueofz());
  EXPECT_DOUBLE_EQ(1.0, curve.maximumValueofz());
  EXPECT_FALSE(curve.minimumCurveOutput());
  EXPECT_FALSE(curve.maximumCurveOutput());
}

TEST_F(EPModelFixture, CurveChillerPartLoadWithLift_ScalarAccessors_RoundTrip) {
  Model model;
  CurveChillerPartLoadWithLift curve(model);

  EXPECT_TRUE(curve.setCoefficient1C1(1.1));
  EXPECT_TRUE(curve.setCoefficient2C2(2.2));
  EXPECT_TRUE(curve.setCoefficient3C3(3.3));
  EXPECT_TRUE(curve.setCoefficient4C4(4.4));
  EXPECT_TRUE(curve.setCoefficient5C5(5.5));
  EXPECT_TRUE(curve.setCoefficient6C6(6.6));
  EXPECT_TRUE(curve.setCoefficient7C7(7.7));
  EXPECT_TRUE(curve.setCoefficient8C8(8.8));
  EXPECT_TRUE(curve.setCoefficient9C9(9.9));
  EXPECT_TRUE(curve.setCoefficient10C10(10.1));
  EXPECT_TRUE(curve.setCoefficient11C11(11.1));
  EXPECT_TRUE(curve.setCoefficient12C12(12.1));
  EXPECT_TRUE(curve.setMinimumValueofx(-2.0));
  EXPECT_TRUE(curve.setMaximumValueofx(3.0));
  EXPECT_TRUE(curve.setMinimumValueofy(-4.0));
  EXPECT_TRUE(curve.setMaximumValueofy(5.0));
  EXPECT_TRUE(curve.setMinimumValueofz(-6.0));
  EXPECT_TRUE(curve.setMaximumValueofz(7.0));

  EXPECT_DOUBLE_EQ(1.1, curve.coefficient1C1());
  EXPECT_DOUBLE_EQ(2.2, curve.coefficient2C2());
  EXPECT_DOUBLE_EQ(3.3, curve.coefficient3C3());
  EXPECT_DOUBLE_EQ(4.4, curve.coefficient4C4());
  EXPECT_DOUBLE_EQ(5.5, curve.coefficient5C5());
  EXPECT_DOUBLE_EQ(6.6, curve.coefficient6C6());
  EXPECT_DOUBLE_EQ(7.7, curve.coefficient7C7());
  EXPECT_DOUBLE_EQ(8.8, curve.coefficient8C8());
  EXPECT_DOUBLE_EQ(9.9, curve.coefficient9C9());
  EXPECT_DOUBLE_EQ(10.1, curve.coefficient10C10());
  EXPECT_DOUBLE_EQ(11.1, curve.coefficient11C11());
  EXPECT_DOUBLE_EQ(12.1, curve.coefficient12C12());
  EXPECT_DOUBLE_EQ(-2.0, curve.minimumValueofx());
  EXPECT_DOUBLE_EQ(3.0, curve.maximumValueofx());
  EXPECT_DOUBLE_EQ(-4.0, curve.minimumValueofy());
  EXPECT_DOUBLE_EQ(5.0, curve.maximumValueofy());
  EXPECT_DOUBLE_EQ(-6.0, curve.minimumValueofz());
  EXPECT_DOUBLE_EQ(7.0, curve.maximumValueofz());

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

  const auto xValues = CurveChillerPartLoadWithLift::validInputUnitTypeforxValues();
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

  const auto yValues = CurveChillerPartLoadWithLift::validInputUnitTypeforyValues();
  ASSERT_FALSE(yValues.empty());
  const auto yDefault = curve.inputUnitTypefory();
  auto yValue = firstNonEmptyDifferentFrom(yValues, yDefault);
  if (yValue.empty()) {
    yValue = firstNonEmpty(yValues);
  }
  ASSERT_FALSE(yValue.empty());
  EXPECT_TRUE(curve.setInputUnitTypefory(yValue));
  EXPECT_EQ(yValue, curve.inputUnitTypefory());
  if (!openstudio::istringEqual(yValue, yDefault)) {
    EXPECT_FALSE(curve.isInputUnitTypeforyDefaulted());
  }
  curve.resetInputUnitTypefory();
  EXPECT_TRUE(curve.isInputUnitTypeforyDefaulted());

  const auto zValues = CurveChillerPartLoadWithLift::validInputUnitTypeforzValues();
  ASSERT_FALSE(zValues.empty());
  const auto zDefault = curve.inputUnitTypeforz();
  auto zValue = firstNonEmptyDifferentFrom(zValues, zDefault);
  if (zValue.empty()) {
    zValue = firstNonEmpty(zValues);
  }
  ASSERT_FALSE(zValue.empty());
  EXPECT_TRUE(curve.setInputUnitTypeforz(zValue));
  EXPECT_EQ(zValue, curve.inputUnitTypeforz());
  if (!openstudio::istringEqual(zValue, zDefault)) {
    EXPECT_FALSE(curve.isInputUnitTypeforzDefaulted());
  }
  curve.resetInputUnitTypeforz();
  EXPECT_TRUE(curve.isInputUnitTypeforzDefaulted());

  const auto outputValues = CurveChillerPartLoadWithLift::validOutputUnitTypeValues();
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
