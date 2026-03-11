/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ResourceObject/CoilCoolingDXCurveFitSpeed.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilCoolingDXCurveFitSpeed_DefaultConstructor) {
  Model model;
  CoilCoolingDXCurveFitSpeed speed(model);
  EXPECT_EQ(CoilCoolingDXCurveFitSpeed::iddObjectType(), speed.iddObject().type());
  EXPECT_FALSE(speed.nameString().empty());
}

TEST_F(EPModelFixture, CoilCoolingDXCurveFitSpeed_ScalarAccessors_RoundTrip) {
  Model model;
  CoilCoolingDXCurveFitSpeed speed(model);

  EXPECT_TRUE(speed.setGrossTotalCoolingCapacityFraction(0.91));
  EXPECT_DOUBLE_EQ(0.91, speed.grossTotalCoolingCapacityFraction());

  EXPECT_TRUE(speed.setEvaporatorAirFlowRateFraction(0.87));
  EXPECT_DOUBLE_EQ(0.87, speed.evaporatorAirFlowRateFraction());

  EXPECT_TRUE(speed.setCondenserAirFlowRateFraction(0.95));
  EXPECT_DOUBLE_EQ(0.95, speed.condenserAirFlowRateFraction());

  EXPECT_FALSE(speed.grossSensibleHeatRatio());
  EXPECT_TRUE(speed.setGrossSensibleHeatRatio(0.73));
  ASSERT_TRUE(speed.grossSensibleHeatRatio());
  EXPECT_DOUBLE_EQ(0.73, speed.grossSensibleHeatRatio().get());

  speed.autosizeGrossSensibleHeatRatio();
  EXPECT_TRUE(speed.isGrossSensibleHeatRatioAutosized());

  EXPECT_TRUE(speed.setGrossCoolingCOP(3.6));
  EXPECT_DOUBLE_EQ(3.6, speed.grossCoolingCOP());

  EXPECT_TRUE(speed.setActiveFractionofCoilFaceArea(0.93));
  EXPECT_DOUBLE_EQ(0.93, speed.activeFractionofCoilFaceArea());

  EXPECT_TRUE(speed.setRatedEvaporatorFanPowerPerVolumeFlowRate(730.0));
  EXPECT_DOUBLE_EQ(730.0, speed.ratedEvaporatorFanPowerPerVolumeFlowRate());
  EXPECT_DOUBLE_EQ(730.0, speed.ratedEvaporatorFanPowerPerVolumeFlowRate2017());

  EXPECT_TRUE(speed.setRatedEvaporatorFanPowerPerVolumeFlowRate2023(840.0));
  EXPECT_DOUBLE_EQ(840.0, speed.ratedEvaporatorFanPowerPerVolumeFlowRate2023());

  EXPECT_TRUE(speed.setEvaporativeCondenserPumpPowerFraction(0.06));
  EXPECT_DOUBLE_EQ(0.06, speed.evaporativeCondenserPumpPowerFraction());

  EXPECT_TRUE(speed.setEvaporativeCondenserEffectiveness(0.88));
  EXPECT_DOUBLE_EQ(0.88, speed.evaporativeCondenserEffectiveness());

  EXPECT_TRUE(speed.setRatedWasteHeatFractionofPowerInput(0.14));
  EXPECT_DOUBLE_EQ(0.14, speed.ratedWasteHeatFractionofPowerInput());

  EXPECT_FALSE(speed.autosizedGrossSensibleHeatRatio());
}
