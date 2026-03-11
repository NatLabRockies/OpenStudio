/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../StraightComponent/BoilerHotWater.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, BoilerHotWater_DefaultConstructor) {
  Model model;
  BoilerHotWater boiler(model);
  EXPECT_EQ(BoilerHotWater::iddObjectType(), boiler.iddObject().type());
  EXPECT_FALSE(boiler.nameString().empty());
}

TEST_F(EPModelFixture, BoilerHotWater_ScalarAccessors_RoundTrip) {
  Model model;
  BoilerHotWater boiler(model);

  EXPECT_TRUE(boiler.setFuelType("NaturalGas"));
  EXPECT_EQ("NaturalGas", boiler.fuelType());

  EXPECT_TRUE(boiler.setNominalCapacity(12345.0));
  ASSERT_TRUE(boiler.nominalCapacity());
  EXPECT_DOUBLE_EQ(12345.0, boiler.nominalCapacity().get());
  EXPECT_FALSE(boiler.isNominalCapacityAutosized());
  boiler.autosizeNominalCapacity();
  EXPECT_TRUE(boiler.isNominalCapacityAutosized());

  EXPECT_TRUE(boiler.setDesignWaterFlowRate(0.005));
  ASSERT_TRUE(boiler.designWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.005, boiler.designWaterFlowRate().get());
  boiler.autosizeDesignWaterFlowRate();
  EXPECT_TRUE(boiler.isDesignWaterFlowRateAutosized());

  EXPECT_TRUE(boiler.setMinimumPartLoadRatio(0.2));
  EXPECT_DOUBLE_EQ(0.2, boiler.minimumPartLoadRatio());
  boiler.resetMinimumPartLoadRatio();
  EXPECT_TRUE(boiler.setMinimumPartLoadRatio(0.3));
  EXPECT_DOUBLE_EQ(0.3, boiler.minimumPartLoadRatio());

  EXPECT_TRUE(boiler.setBoilerFlowMode("VariableFlow"));
  EXPECT_EQ("LeavingSetpointModulated", boiler.boilerFlowMode());

  EXPECT_TRUE(boiler.setOnCycleParasiticElectricLoad(10.0));
  EXPECT_DOUBLE_EQ(10.0, boiler.onCycleParasiticElectricLoad());
}
