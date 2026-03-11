/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/HeatBalanceAlgorithm.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, HeatBalanceAlgorithm_DefaultConstructor) {
  Model model;
  HeatBalanceAlgorithm object(model);

  EXPECT_EQ(HeatBalanceAlgorithm::iddObjectType(), object.iddObject().type());

  EXPECT_FALSE(object.isAlgorithmDefaulted());
  EXPECT_EQ("ConductionTransferFunction", object.algorithm());
  EXPECT_FALSE(object.isSurfaceTemperatureUpperLimitDefaulted());
  EXPECT_DOUBLE_EQ(200.0, object.surfaceTemperatureUpperLimit());
}

TEST_F(EPModelFixture, HeatBalanceAlgorithm_ScalarAccessors_RoundTrip) {
  Model model;
  HeatBalanceAlgorithm object(model);

  EXPECT_TRUE(object.setAlgorithm("MoisturePenetrationDepthConductionTransferFunction"));
  EXPECT_EQ("MoisturePenetrationDepthConductionTransferFunction", object.algorithm());
  EXPECT_FALSE(object.isAlgorithmDefaulted());
  object.resetAlgorithm();
  EXPECT_TRUE(object.isAlgorithmDefaulted());

  EXPECT_TRUE(object.setSurfaceTemperatureUpperLimit(250.0));
  EXPECT_DOUBLE_EQ(250.0, object.surfaceTemperatureUpperLimit());
  EXPECT_FALSE(object.isSurfaceTemperatureUpperLimitDefaulted());
  object.resetSurfaceTemperatureUpperLimit();
  EXPECT_TRUE(object.isSurfaceTemperatureUpperLimitDefaulted());

  EXPECT_TRUE(object.setMinimumSurfaceConvectionHeatTransferCoefficientValue(0.25));
  EXPECT_DOUBLE_EQ(0.25, object.minimumSurfaceConvectionHeatTransferCoefficientValue());
  EXPECT_FALSE(object.isMinimumSurfaceConvectionHeatTransferCoefficientValueDefaulted());
  object.resetMinimumSurfaceConvectionHeatTransferCoefficientValue();
  EXPECT_TRUE(object.isMinimumSurfaceConvectionHeatTransferCoefficientValueDefaulted());

  EXPECT_TRUE(object.setMaximumSurfaceConvectionHeatTransferCoefficientValue(2500.0));
  EXPECT_DOUBLE_EQ(2500.0, object.maximumSurfaceConvectionHeatTransferCoefficientValue());
  EXPECT_FALSE(object.isMaximumSurfaceConvectionHeatTransferCoefficientValueDefaulted());
  object.resetMaximumSurfaceConvectionHeatTransferCoefficientValue();
  EXPECT_TRUE(object.isMaximumSurfaceConvectionHeatTransferCoefficientValueDefaulted());

  const auto values = HeatBalanceAlgorithm::algorithmValues();
  EXPECT_GE(values.size(), 1u);
}
