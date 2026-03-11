/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ResourceObject/HeatExchangerDesiccantBalancedFlowPerformanceDataType1.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, HeatExchangerDesiccantBalancedFlowPerformanceDataType1_DefaultConstructor) {
  Model model;
  HeatExchangerDesiccantBalancedFlowPerformanceDataType1 performance(model);

  EXPECT_EQ(HeatExchangerDesiccantBalancedFlowPerformanceDataType1::iddObjectType(), performance.iddObject().type());
  EXPECT_FALSE(performance.nameString().empty());

  EXPECT_TRUE(performance.isNominalAirFlowRateAutosized());
  EXPECT_TRUE(performance.isNominalAirFaceVelocityAutosized());
}

TEST_F(EPModelFixture, HeatExchangerDesiccantBalancedFlowPerformanceDataType1_ScalarAccessors_RoundTrip) {
  Model model;
  HeatExchangerDesiccantBalancedFlowPerformanceDataType1 performance(model);

  EXPECT_TRUE(performance.setNominalAirFlowRate(1.25));
  ASSERT_TRUE(performance.nominalAirFlowRate());
  EXPECT_DOUBLE_EQ(1.25, *performance.nominalAirFlowRate());
  EXPECT_FALSE(performance.isNominalAirFlowRateAutosized());

  EXPECT_TRUE(performance.setNominalAirFaceVelocity(3.5));
  ASSERT_TRUE(performance.nominalAirFaceVelocity());
  EXPECT_DOUBLE_EQ(3.5, *performance.nominalAirFaceVelocity());
  EXPECT_FALSE(performance.isNominalAirFaceVelocityAutosized());

  EXPECT_TRUE(performance.setNominalElectricPower(77.0));
  EXPECT_DOUBLE_EQ(77.0, performance.nominalElectricPower());

  EXPECT_TRUE(performance.setTemperatureEquationCoefficient1(-1.2));
  EXPECT_DOUBLE_EQ(-1.2, performance.temperatureEquationCoefficient1());

  EXPECT_TRUE(performance.setHumidityRatioEquationCoefficient8(0.42));
  EXPECT_DOUBLE_EQ(0.42, performance.humidityRatioEquationCoefficient8());

  EXPECT_TRUE(performance.setMaximumProcessInletAirRelativeHumidityforHumidityRatioEquation(95.0));
  EXPECT_DOUBLE_EQ(95.0, performance.maximumProcessInletAirRelativeHumidityforHumidityRatioEquation());

  performance.autosizeNominalAirFlowRate();
  performance.autosizeNominalAirFaceVelocity();
  EXPECT_TRUE(performance.isNominalAirFlowRateAutosized());
  EXPECT_TRUE(performance.isNominalAirFaceVelocityAutosized());

  performance.autosize();
  EXPECT_FALSE(performance.autosizedNominalAirFlowRate());
  EXPECT_FALSE(performance.autosizedNominalAirFaceVelocity());

  performance.applySizingValues();
  EXPECT_TRUE(performance.isNominalAirFlowRateAutosized());
  EXPECT_TRUE(performance.isNominalAirFaceVelocityAutosized());
}
