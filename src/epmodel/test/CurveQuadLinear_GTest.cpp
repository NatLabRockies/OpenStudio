/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Curve/CurveQuadLinear.hpp"

#include <utilities/core/StringHelpers.hpp>

#include <algorithm>
#include <functional>

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

void expectSetAndResetUnitType(CurveQuadLinear& curve, const std::vector<std::string>& values, const std::string& defaultValue,
                               const std::function<bool(const std::string&)>& setter, const std::function<std::string()>& getter,
                               const std::function<bool()>& isDefaulted, const std::function<void()>& resetter) {
  ASSERT_FALSE(values.empty());
  auto value = firstNonEmptyDifferentFrom(values, defaultValue);
  if (value.empty()) {
    value = firstNonEmpty(values);
  }
  ASSERT_FALSE(value.empty());

  EXPECT_TRUE(setter(value));
  EXPECT_EQ(value, getter());
  if (!openstudio::istringEqual(value, defaultValue)) {
    EXPECT_FALSE(isDefaulted());
  }
  resetter();
  EXPECT_TRUE(isDefaulted());
}

}  // namespace

TEST_F(EPModelFixture, CurveQuadLinear_DefaultConstructor) {
  Model model;
  CurveQuadLinear curve(model);
  EXPECT_EQ(CurveQuadLinear::iddObjectType(), curve.iddObject().type());

  EXPECT_DOUBLE_EQ(0.0, curve.coefficient1Constant());
  EXPECT_DOUBLE_EQ(1.0, curve.coefficient2w());
  EXPECT_DOUBLE_EQ(1.0, curve.coefficient3x());
  EXPECT_DOUBLE_EQ(1.0, curve.coefficient4y());
  EXPECT_DOUBLE_EQ(1.0, curve.coefficient5z());
  EXPECT_DOUBLE_EQ(-100.0, curve.minimumValueofw());
  EXPECT_DOUBLE_EQ(100.0, curve.maximumValueofw());
  EXPECT_DOUBLE_EQ(-100.0, curve.minimumValueofx());
  EXPECT_DOUBLE_EQ(100.0, curve.maximumValueofx());
  EXPECT_DOUBLE_EQ(0.0, curve.minimumValueofy());
  EXPECT_DOUBLE_EQ(100.0, curve.maximumValueofy());
  EXPECT_DOUBLE_EQ(0.0, curve.minimumValueofz());
  EXPECT_DOUBLE_EQ(100.0, curve.maximumValueofz());
  EXPECT_FALSE(curve.minimumCurveOutput());
  EXPECT_FALSE(curve.maximumCurveOutput());
  EXPECT_TRUE(curve.isInputUnitTypeforwDefaulted());
  EXPECT_TRUE(curve.isInputUnitTypeforxDefaulted());
  EXPECT_TRUE(curve.isInputUnitTypeforyDefaulted());
  EXPECT_TRUE(curve.isInputUnitTypeforzDefaulted());
}

TEST_F(EPModelFixture, CurveQuadLinear_ScalarAccessors_RoundTrip) {
  Model model;
  CurveQuadLinear curve(model);

  EXPECT_TRUE(curve.setCoefficient1Constant(1.1));
  EXPECT_TRUE(curve.setCoefficient2w(2.2));
  EXPECT_TRUE(curve.setCoefficient3x(3.3));
  EXPECT_TRUE(curve.setCoefficient4y(4.4));
  EXPECT_TRUE(curve.setCoefficient5z(5.5));
  EXPECT_TRUE(curve.setMinimumValueofw(-9.0));
  EXPECT_TRUE(curve.setMaximumValueofw(9.0));
  EXPECT_TRUE(curve.setMinimumValueofx(-8.0));
  EXPECT_TRUE(curve.setMaximumValueofx(8.0));
  EXPECT_TRUE(curve.setMinimumValueofy(-7.0));
  EXPECT_TRUE(curve.setMaximumValueofy(7.0));
  EXPECT_TRUE(curve.setMinimumValueofz(-6.0));
  EXPECT_TRUE(curve.setMaximumValueofz(6.0));

  EXPECT_DOUBLE_EQ(1.1, curve.coefficient1Constant());
  EXPECT_DOUBLE_EQ(2.2, curve.coefficient2w());
  EXPECT_DOUBLE_EQ(3.3, curve.coefficient3x());
  EXPECT_DOUBLE_EQ(4.4, curve.coefficient4y());
  EXPECT_DOUBLE_EQ(5.5, curve.coefficient5z());
  EXPECT_DOUBLE_EQ(-9.0, curve.minimumValueofw());
  EXPECT_DOUBLE_EQ(9.0, curve.maximumValueofw());
  EXPECT_DOUBLE_EQ(-8.0, curve.minimumValueofx());
  EXPECT_DOUBLE_EQ(8.0, curve.maximumValueofx());
  EXPECT_DOUBLE_EQ(-7.0, curve.minimumValueofy());
  EXPECT_DOUBLE_EQ(7.0, curve.maximumValueofy());
  EXPECT_DOUBLE_EQ(-6.0, curve.minimumValueofz());
  EXPECT_DOUBLE_EQ(6.0, curve.maximumValueofz());

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

  expectSetAndResetUnitType(curve, CurveQuadLinear::inputUnitTypeforwValues(), curve.inputUnitTypeforw(),
                            [&](const std::string& v) { return curve.setInputUnitTypeforw(v); },
                            [&]() { return curve.inputUnitTypeforw(); }, [&]() { return curve.isInputUnitTypeforwDefaulted(); },
                            [&]() { curve.resetInputUnitTypeforw(); });

  expectSetAndResetUnitType(curve, CurveQuadLinear::inputUnitTypeforxValues(), curve.inputUnitTypeforx(),
                            [&](const std::string& v) { return curve.setInputUnitTypeforx(v); },
                            [&]() { return curve.inputUnitTypeforx(); }, [&]() { return curve.isInputUnitTypeforxDefaulted(); },
                            [&]() { curve.resetInputUnitTypeforx(); });

  expectSetAndResetUnitType(curve, CurveQuadLinear::inputUnitTypeforyValues(), curve.inputUnitTypefory(),
                            [&](const std::string& v) { return curve.setInputUnitTypefory(v); },
                            [&]() { return curve.inputUnitTypefory(); }, [&]() { return curve.isInputUnitTypeforyDefaulted(); },
                            [&]() { curve.resetInputUnitTypefory(); });

  expectSetAndResetUnitType(curve, CurveQuadLinear::inputUnitTypeforzValues(), curve.inputUnitTypeforz(),
                            [&](const std::string& v) { return curve.setInputUnitTypeforz(v); },
                            [&]() { return curve.inputUnitTypeforz(); }, [&]() { return curve.isInputUnitTypeforzDefaulted(); },
                            [&]() { curve.resetInputUnitTypeforz(); });
}
