/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Curve/CurveQuadLinear.hpp"
#include "../Curve/CurveQuadLinear_Impl.hpp"
#include "../WaterToWaterComponent/HeatPumpWaterToWaterEquationFitCooling.hpp"
#include "../WaterToWaterComponent/HeatPumpWaterToWaterEquationFitHeating.hpp"

#include <limits>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, HeatPumpWaterToWaterEquationFitHeating_DefaultConstructor) {
  Model model;
  HeatPumpWaterToWaterEquationFitHeating hp(model);

  EXPECT_EQ(HeatPumpWaterToWaterEquationFitHeating::iddObjectType(), hp.iddObject().type());
  EXPECT_NE(std::numeric_limits<unsigned>::max(), hp.supplyInletPort());
  EXPECT_NE(std::numeric_limits<unsigned>::max(), hp.demandInletPort());

  EXPECT_TRUE(hp.isReferenceLoadSideFlowRateAutosized());
  EXPECT_TRUE(hp.isReferenceSourceSideFlowRateAutosized());
  EXPECT_TRUE(hp.isRatedHeatingCapacityAutosized());
  EXPECT_TRUE(hp.isRatedHeatingPowerConsumptionAutosized());

  EXPECT_FALSE(hp.referenceLoadSideFlowRate());
  EXPECT_FALSE(hp.referenceSourceSideFlowRate());
  EXPECT_FALSE(hp.ratedHeatingCapacity());
  EXPECT_FALSE(hp.ratedHeatingPowerConsumption());
  EXPECT_DOUBLE_EQ(-999.0, hp.ratedLoadSideFlowRate());
  EXPECT_DOUBLE_EQ(-999.0, hp.ratedSourceSideFlowRate());
  EXPECT_EQ(CurveQuadLinear::iddObjectType(), hp.heatingCapacityCurve().iddObject().type());
  EXPECT_EQ(CurveQuadLinear::iddObjectType(), hp.heatingCompressorPowerCurve().iddObject().type());
  EXPECT_FALSE(hp.companionCoolingHeatPump());

  EXPECT_DOUBLE_EQ(7.5, hp.referenceCoefficientofPerformance());
  EXPECT_DOUBLE_EQ(1.0, hp.sizingFactor());
}

TEST_F(EPModelFixture, HeatPumpWaterToWaterEquationFitHeating_CurveConstructorAndSetters) {
  Model model;
  CurveQuadLinear capacityCurve(model);
  CurveQuadLinear powerCurve(model);

  HeatPumpWaterToWaterEquationFitHeating hp(model, capacityCurve, powerCurve);
  EXPECT_EQ(capacityCurve, hp.heatingCapacityCurve());
  EXPECT_EQ(powerCurve, hp.heatingCompressorPowerCurve());

  CurveQuadLinear replacementCapacity(model);
  CurveQuadLinear replacementPower(model);

  EXPECT_TRUE(hp.setHeatingCapacityCurve(replacementCapacity));
  EXPECT_TRUE(hp.setHeatingCompressorPowerCurve(replacementPower));

  EXPECT_EQ(replacementCapacity, hp.heatingCapacityCurve());
  EXPECT_EQ(replacementPower, hp.heatingCompressorPowerCurve());
}

TEST_F(EPModelFixture, HeatPumpWaterToWaterEquationFitHeating_CompanionCoolingHeatPumpRoundTrip) {
  Model model;
  HeatPumpWaterToWaterEquationFitHeating heating(model);
  HeatPumpWaterToWaterEquationFitCooling cooling(model);

  EXPECT_FALSE(heating.companionCoolingHeatPump());
  EXPECT_TRUE(heating.setCompanionCoolingHeatPump(cooling));
  ASSERT_TRUE(heating.companionCoolingHeatPump());
  EXPECT_EQ(cooling, heating.companionCoolingHeatPump().get());
}

TEST_F(EPModelFixture, HeatPumpWaterToWaterEquationFitHeating_DeprecatedCoefficientAliasesDelegateThroughStoredCurves) {
  Model model;
  HeatPumpWaterToWaterEquationFitHeating hp(model);

  EXPECT_TRUE(hp.setHeatingCapacityCoefficient1(1.1));
  EXPECT_TRUE(hp.setHeatingCapacityCoefficient2(1.2));
  EXPECT_TRUE(hp.setHeatingCapacityCoefficient3(1.3));
  EXPECT_TRUE(hp.setHeatingCapacityCoefficient4(1.4));
  EXPECT_TRUE(hp.setHeatingCapacityCoefficient5(1.5));
  EXPECT_DOUBLE_EQ(1.1, hp.heatingCapacityCoefficient1());
  EXPECT_DOUBLE_EQ(1.2, hp.heatingCapacityCoefficient2());
  EXPECT_DOUBLE_EQ(1.3, hp.heatingCapacityCoefficient3());
  EXPECT_DOUBLE_EQ(1.4, hp.heatingCapacityCoefficient4());
  EXPECT_DOUBLE_EQ(1.5, hp.heatingCapacityCoefficient5());

  EXPECT_TRUE(hp.setHeatingCompressorPowerCoefficient1(2.1));
  EXPECT_TRUE(hp.setHeatingCompressorPowerCoefficient2(2.2));
  EXPECT_TRUE(hp.setHeatingCompressorPowerCoefficient3(2.3));
  EXPECT_TRUE(hp.setHeatingCompressorPowerCoefficient4(2.4));
  EXPECT_TRUE(hp.setHeatingCompressorPowerCoefficient5(2.5));
  EXPECT_DOUBLE_EQ(2.1, hp.heatingCompressorPowerCoefficient1());
  EXPECT_DOUBLE_EQ(2.2, hp.heatingCompressorPowerCoefficient2());
  EXPECT_DOUBLE_EQ(2.3, hp.heatingCompressorPowerCoefficient3());
  EXPECT_DOUBLE_EQ(2.4, hp.heatingCompressorPowerCoefficient4());
  EXPECT_DOUBLE_EQ(2.5, hp.heatingCompressorPowerCoefficient5());
}

TEST_F(EPModelFixture, HeatPumpWaterToWaterEquationFitHeating_ScalarAccessors_RoundTrip) {
  Model model;
  HeatPumpWaterToWaterEquationFitHeating hp(model);

  EXPECT_TRUE(hp.setReferenceLoadSideFlowRate(0.101));
  ASSERT_TRUE(hp.referenceLoadSideFlowRate());
  EXPECT_DOUBLE_EQ(0.101, *hp.referenceLoadSideFlowRate());
  EXPECT_DOUBLE_EQ(0.101, hp.ratedLoadSideFlowRate());

  EXPECT_TRUE(hp.setRatedLoadSideFlowRate(0.111));
  ASSERT_TRUE(hp.referenceLoadSideFlowRate());
  EXPECT_DOUBLE_EQ(0.111, *hp.referenceLoadSideFlowRate());
  EXPECT_DOUBLE_EQ(0.111, hp.ratedLoadSideFlowRate());

  hp.autosizeReferenceLoadSideFlowRate();
  EXPECT_TRUE(hp.isReferenceLoadSideFlowRateAutosized());
  EXPECT_DOUBLE_EQ(-999.0, hp.ratedLoadSideFlowRate());

  EXPECT_TRUE(hp.setReferenceSourceSideFlowRate(0.202));
  ASSERT_TRUE(hp.referenceSourceSideFlowRate());
  EXPECT_DOUBLE_EQ(0.202, *hp.referenceSourceSideFlowRate());
  EXPECT_DOUBLE_EQ(0.202, hp.ratedSourceSideFlowRate());

  EXPECT_TRUE(hp.setRatedSourceSideFlowRate(0.222));
  ASSERT_TRUE(hp.referenceSourceSideFlowRate());
  EXPECT_DOUBLE_EQ(0.222, *hp.referenceSourceSideFlowRate());
  EXPECT_DOUBLE_EQ(0.222, hp.ratedSourceSideFlowRate());

  hp.autosizeReferenceSourceSideFlowRate();
  EXPECT_TRUE(hp.isReferenceSourceSideFlowRateAutosized());
  EXPECT_DOUBLE_EQ(-999.0, hp.ratedSourceSideFlowRate());

  EXPECT_TRUE(hp.setRatedHeatingCapacity(12450.0));
  ASSERT_TRUE(hp.ratedHeatingCapacity());
  EXPECT_DOUBLE_EQ(12450.0, *hp.ratedHeatingCapacity());
  hp.autosizeRatedHeatingCapacity();
  EXPECT_TRUE(hp.isRatedHeatingCapacityAutosized());
  EXPECT_FALSE(hp.ratedHeatingCapacity());

  EXPECT_TRUE(hp.setRatedHeatingPowerConsumption(3450.0));
  ASSERT_TRUE(hp.ratedHeatingPowerConsumption());
  EXPECT_DOUBLE_EQ(3450.0, *hp.ratedHeatingPowerConsumption());
  hp.autosizeRatedHeatingPowerConsumption();
  EXPECT_TRUE(hp.isRatedHeatingPowerConsumptionAutosized());
  EXPECT_FALSE(hp.ratedHeatingPowerConsumption());

  EXPECT_TRUE(hp.setReferenceCoefficientofPerformance(6.5));
  EXPECT_DOUBLE_EQ(6.5, hp.referenceCoefficientofPerformance());

  EXPECT_TRUE(hp.setSizingFactor(1.2));
  EXPECT_DOUBLE_EQ(1.2, hp.sizingFactor());
}
