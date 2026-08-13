/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Curve/CurveBiquadratic.hpp"
#include "../Curve/CurveQuadratic.hpp"
#include "../ResourceObject/CoilCoolingDXCurveFitSpeed.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilCoolingDXCurveFitSpeed_DefaultConstructor) {
  Model model;
  CoilCoolingDXCurveFitSpeed speed(model);
  EXPECT_EQ(CoilCoolingDXCurveFitSpeed::iddObjectType(), speed.iddObject().type());
  EXPECT_FALSE(speed.nameString().empty());
  EXPECT_DOUBLE_EQ(1.0, speed.grossTotalCoolingCapacityFraction());
  EXPECT_DOUBLE_EQ(1.0, speed.evaporatorAirFlowRateFraction());
  EXPECT_DOUBLE_EQ(1.0, speed.condenserAirFlowRateFraction());
  EXPECT_TRUE(speed.isGrossSensibleHeatRatioAutosized());
  EXPECT_DOUBLE_EQ(3.0, speed.grossCoolingCOP());
  EXPECT_DOUBLE_EQ(1.0, speed.activeFractionofCoilFaceArea());
  EXPECT_DOUBLE_EQ(773.3, speed.ratedEvaporatorFanPowerPerVolumeFlowRate2017());
  EXPECT_DOUBLE_EQ(934.4, speed.ratedEvaporatorFanPowerPerVolumeFlowRate2023());
  EXPECT_DOUBLE_EQ(1.0, speed.evaporativeCondenserPumpPowerFraction());
  EXPECT_DOUBLE_EQ(0.9, speed.evaporativeCondenserEffectiveness());
  EXPECT_DOUBLE_EQ(0.2, speed.ratedWasteHeatFractionofPowerInput());
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

TEST_F(EPModelFixture, CoilCoolingDXCurveFitSpeed_CurveRelationshipsRoundTrip) {
  Model model;
  CoilCoolingDXCurveFitSpeed speed(model);
  CurveBiquadratic totalCapacityTemperature(model);
  CurveQuadratic totalCapacityFlow(model);
  CurveBiquadratic energyInputRatioTemperature(model);
  CurveQuadratic energyInputRatioFlow(model);
  CurveQuadratic partLoadFraction(model);
  CurveBiquadratic wasteHeatTemperature(model);
  CurveBiquadratic sensibleHeatRatioTemperature(model);
  CurveQuadratic sensibleHeatRatioFlow(model);

  EXPECT_FALSE(speed.totalCoolingCapacityModifierFunctionofTemperatureCurve());
  EXPECT_FALSE(speed.totalCoolingCapacityModifierFunctionofAirFlowFractionCurve());
  EXPECT_FALSE(speed.energyInputRatioModifierFunctionofTemperatureCurve());
  EXPECT_FALSE(speed.energyInputRatioModifierFunctionofAirFlowFractionCurve());
  EXPECT_FALSE(speed.partLoadFractionCorrelationCurve());
  EXPECT_FALSE(speed.wasteHeatModifierFunctionofTemperatureCurve());
  EXPECT_FALSE(speed.sensibleHeatRatioModifierFunctionofTemperatureCurve());
  EXPECT_FALSE(speed.sensibleHeatRatioModifierFunctionofFlowFractionCurve());

  ASSERT_TRUE(speed.setTotalCoolingCapacityModifierFunctionofTemperatureCurve(totalCapacityTemperature));
  ASSERT_TRUE(speed.setTotalCoolingCapacityModifierFunctionofAirFlowFractionCurve(totalCapacityFlow));
  ASSERT_TRUE(speed.setEnergyInputRatioModifierFunctionofTemperatureCurve(energyInputRatioTemperature));
  ASSERT_TRUE(speed.setEnergyInputRatioModifierFunctionofAirFlowFractionCurve(energyInputRatioFlow));
  ASSERT_TRUE(speed.setPartLoadFractionCorrelationCurve(partLoadFraction));
  ASSERT_TRUE(speed.setWasteHeatModifierFunctionofTemperatureCurve(wasteHeatTemperature));
  ASSERT_TRUE(speed.setSensibleHeatRatioModifierFunctionofTemperatureCurve(sensibleHeatRatioTemperature));
  ASSERT_TRUE(speed.setSensibleHeatRatioModifierFunctionofFlowFractionCurve(sensibleHeatRatioFlow));

  EXPECT_EQ(totalCapacityTemperature.handle(), speed.totalCoolingCapacityModifierFunctionofTemperatureCurve()->handle());
  EXPECT_EQ(totalCapacityFlow.handle(), speed.totalCoolingCapacityModifierFunctionofAirFlowFractionCurve()->handle());
  EXPECT_EQ(energyInputRatioTemperature.handle(), speed.energyInputRatioModifierFunctionofTemperatureCurve()->handle());
  EXPECT_EQ(energyInputRatioFlow.handle(), speed.energyInputRatioModifierFunctionofAirFlowFractionCurve()->handle());
  EXPECT_EQ(partLoadFraction.handle(), speed.partLoadFractionCorrelationCurve()->handle());
  EXPECT_EQ(wasteHeatTemperature.handle(), speed.wasteHeatModifierFunctionofTemperatureCurve()->handle());
  EXPECT_EQ(sensibleHeatRatioTemperature.handle(), speed.sensibleHeatRatioModifierFunctionofTemperatureCurve()->handle());
  EXPECT_EQ(sensibleHeatRatioFlow.handle(), speed.sensibleHeatRatioModifierFunctionofFlowFractionCurve()->handle());

  Model otherModel;
  CurveBiquadratic foreignCurve(otherModel);
  EXPECT_FALSE(speed.setTotalCoolingCapacityModifierFunctionofTemperatureCurve(foreignCurve));
  EXPECT_EQ(totalCapacityTemperature.handle(), speed.totalCoolingCapacityModifierFunctionofTemperatureCurve()->handle());

  speed.resetTotalCoolingCapacityModifierFunctionofTemperatureCurve();
  speed.resetTotalCoolingCapacityModifierFunctionofAirFlowFractionCurve();
  speed.resetEnergyInputRatioModifierFunctionofTemperatureCurve();
  speed.resetEnergyInputRatioModifierFunctionofAirFlowFractionCurve();
  speed.resetPartLoadFractionCorrelationCurve();
  speed.resetWasteHeatModifierFunctionofTemperatureCurve();
  speed.resetSensibleHeatRatioModifierFunctionofTemperatureCurve();
  speed.resetSensibleHeatRatioModifierFunctionofFlowFractionCurve();
  EXPECT_FALSE(speed.totalCoolingCapacityModifierFunctionofTemperatureCurve());
  EXPECT_FALSE(speed.totalCoolingCapacityModifierFunctionofAirFlowFractionCurve());
  EXPECT_FALSE(speed.energyInputRatioModifierFunctionofTemperatureCurve());
  EXPECT_FALSE(speed.energyInputRatioModifierFunctionofAirFlowFractionCurve());
  EXPECT_FALSE(speed.partLoadFractionCorrelationCurve());
  EXPECT_FALSE(speed.wasteHeatModifierFunctionofTemperatureCurve());
  EXPECT_FALSE(speed.sensibleHeatRatioModifierFunctionofTemperatureCurve());
  EXPECT_FALSE(speed.sensibleHeatRatioModifierFunctionofFlowFractionCurve());
}
