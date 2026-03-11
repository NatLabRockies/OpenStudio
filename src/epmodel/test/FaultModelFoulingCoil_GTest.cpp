/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/FaultModelFoulingCoil.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, FaultModelFoulingCoil_DefaultConstructor) {
  Model model;
  FaultModelFoulingCoil fault(model);
  EXPECT_EQ(FaultModelFoulingCoil::iddObjectType(), fault.iddObject().type());

  const auto values = FaultModelFoulingCoil::foulingInputMethodValues();
  EXPECT_FALSE(values.empty());

  EXPECT_TRUE(fault.isFoulingInputMethodDefaulted());
  EXPECT_EQ("FouledUARated", fault.foulingInputMethod());

  EXPECT_FALSE(fault.uAFouled());

  EXPECT_TRUE(fault.isWaterSideFoulingFactorDefaulted());
  EXPECT_DOUBLE_EQ(0.0, fault.waterSideFoulingFactor());
  EXPECT_TRUE(fault.isAirSideFoulingFactorDefaulted());
  EXPECT_DOUBLE_EQ(0.0, fault.airSideFoulingFactor());
  EXPECT_FALSE(fault.outsideCoilSurfaceArea());
  EXPECT_TRUE(fault.isInsidetoOutsideCoilSurfaceAreaRatioDefaulted());
  EXPECT_DOUBLE_EQ(0.07, fault.insidetoOutsideCoilSurfaceAreaRatio());
}

TEST_F(EPModelFixture, FaultModelFoulingCoil_ScalarAccessors_RoundTrip) {
  Model model;
  FaultModelFoulingCoil fault(model);

  EXPECT_TRUE(fault.setFoulingInputMethod("FoulingFactor"));
  EXPECT_EQ("FoulingFactor", fault.foulingInputMethod());
  EXPECT_FALSE(fault.isFoulingInputMethodDefaulted());
  EXPECT_FALSE(fault.setFoulingInputMethod("InvalidFoulingInputMethod"));
  EXPECT_EQ("FoulingFactor", fault.foulingInputMethod());
  fault.resetFoulingInputMethod();
  EXPECT_TRUE(fault.isFoulingInputMethodDefaulted());
  EXPECT_EQ("FouledUARated", fault.foulingInputMethod());

  EXPECT_TRUE(fault.setUAFouled(520.0));
  ASSERT_TRUE(fault.uAFouled());
  EXPECT_DOUBLE_EQ(520.0, fault.uAFouled().get());
  EXPECT_FALSE(fault.setUAFouled(0.0));
  ASSERT_TRUE(fault.uAFouled());
  EXPECT_DOUBLE_EQ(520.0, fault.uAFouled().get());
  fault.resetUAFouled();
  EXPECT_FALSE(fault.uAFouled());

  EXPECT_TRUE(fault.setWaterSideFoulingFactor(0.002));
  EXPECT_FALSE(fault.isWaterSideFoulingFactorDefaulted());
  EXPECT_DOUBLE_EQ(0.002, fault.waterSideFoulingFactor());
  EXPECT_FALSE(fault.setWaterSideFoulingFactor(-0.1));
  EXPECT_DOUBLE_EQ(0.002, fault.waterSideFoulingFactor());
  fault.resetWaterSideFoulingFactor();
  EXPECT_TRUE(fault.isWaterSideFoulingFactorDefaulted());
  EXPECT_DOUBLE_EQ(0.0, fault.waterSideFoulingFactor());

  EXPECT_TRUE(fault.setAirSideFoulingFactor(0.003));
  EXPECT_FALSE(fault.isAirSideFoulingFactorDefaulted());
  EXPECT_DOUBLE_EQ(0.003, fault.airSideFoulingFactor());
  EXPECT_FALSE(fault.setAirSideFoulingFactor(-0.2));
  EXPECT_DOUBLE_EQ(0.003, fault.airSideFoulingFactor());
  fault.resetAirSideFoulingFactor();
  EXPECT_TRUE(fault.isAirSideFoulingFactorDefaulted());
  EXPECT_DOUBLE_EQ(0.0, fault.airSideFoulingFactor());

  EXPECT_TRUE(fault.setOutsideCoilSurfaceArea(8.6));
  ASSERT_TRUE(fault.outsideCoilSurfaceArea());
  EXPECT_DOUBLE_EQ(8.6, fault.outsideCoilSurfaceArea().get());
  EXPECT_FALSE(fault.setOutsideCoilSurfaceArea(0.0));
  ASSERT_TRUE(fault.outsideCoilSurfaceArea());
  EXPECT_DOUBLE_EQ(8.6, fault.outsideCoilSurfaceArea().get());
  fault.resetOutsideCoilSurfaceArea();
  EXPECT_FALSE(fault.outsideCoilSurfaceArea());

  EXPECT_TRUE(fault.setInsidetoOutsideCoilSurfaceAreaRatio(0.12));
  EXPECT_FALSE(fault.isInsidetoOutsideCoilSurfaceAreaRatioDefaulted());
  EXPECT_DOUBLE_EQ(0.12, fault.insidetoOutsideCoilSurfaceAreaRatio());
  EXPECT_FALSE(fault.setInsidetoOutsideCoilSurfaceAreaRatio(0.0));
  EXPECT_DOUBLE_EQ(0.12, fault.insidetoOutsideCoilSurfaceAreaRatio());
  fault.resetInsidetoOutsideCoilSurfaceAreaRatio();
  EXPECT_TRUE(fault.isInsidetoOutsideCoilSurfaceAreaRatioDefaulted());
  EXPECT_DOUBLE_EQ(0.07, fault.insidetoOutsideCoilSurfaceAreaRatio());
}
