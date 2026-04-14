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

TEST_F(EPModelFixture, HeatPumpWaterToWaterEquationFitCooling_DefaultConstructor) {
  Model model;
  HeatPumpWaterToWaterEquationFitCooling hp(model);

  EXPECT_EQ(HeatPumpWaterToWaterEquationFitCooling::iddObjectType(), hp.iddObject().type());
  EXPECT_NE(std::numeric_limits<unsigned>::max(), hp.supplyInletPort());
  EXPECT_NE(std::numeric_limits<unsigned>::max(), hp.demandInletPort());

  EXPECT_TRUE(hp.isReferenceLoadSideFlowRateAutosized());
  EXPECT_TRUE(hp.isReferenceSourceSideFlowRateAutosized());
  EXPECT_TRUE(hp.isRatedCoolingCapacityAutosized());
  EXPECT_TRUE(hp.isRatedCoolingPowerConsumptionAutosized());

  EXPECT_FALSE(hp.referenceLoadSideFlowRate());
  EXPECT_FALSE(hp.referenceSourceSideFlowRate());
  EXPECT_FALSE(hp.ratedCoolingCapacity());
  EXPECT_FALSE(hp.ratedCoolingPowerConsumption());
  EXPECT_DOUBLE_EQ(-999.0, hp.ratedLoadSideFlowRate());
  EXPECT_DOUBLE_EQ(-999.0, hp.ratedSourceSideFlowRate());
  EXPECT_EQ(CurveQuadLinear::iddObjectType(), hp.coolingCapacityCurve().iddObject().type());
  EXPECT_EQ(CurveQuadLinear::iddObjectType(), hp.coolingCompressorPowerCurve().iddObject().type());
  EXPECT_FALSE(hp.companionHeatingHeatPump());

  EXPECT_DOUBLE_EQ(8.0, hp.referenceCoefficientofPerformance());
  EXPECT_DOUBLE_EQ(1.0, hp.sizingFactor());
}

TEST_F(EPModelFixture, HeatPumpWaterToWaterEquationFitCooling_CurveConstructorAndSetters) {
  Model model;
  CurveQuadLinear capacityCurve(model);
  CurveQuadLinear powerCurve(model);

  HeatPumpWaterToWaterEquationFitCooling hp(model, capacityCurve, powerCurve);
  EXPECT_EQ(capacityCurve, hp.coolingCapacityCurve());
  EXPECT_EQ(powerCurve, hp.coolingCompressorPowerCurve());

  CurveQuadLinear replacementCapacity(model);
  CurveQuadLinear replacementPower(model);

  EXPECT_TRUE(hp.setCoolingCapacityCurve(replacementCapacity));
  EXPECT_TRUE(hp.setCoolingCompressorPowerCurve(replacementPower));

  EXPECT_EQ(replacementCapacity, hp.coolingCapacityCurve());
  EXPECT_EQ(replacementPower, hp.coolingCompressorPowerCurve());
}

TEST_F(EPModelFixture, HeatPumpWaterToWaterEquationFitCooling_CompanionHeatingHeatPumpRoundTrip) {
  Model model;
  HeatPumpWaterToWaterEquationFitCooling cooling(model);
  HeatPumpWaterToWaterEquationFitHeating heating(model);

  EXPECT_FALSE(cooling.companionHeatingHeatPump());
  EXPECT_TRUE(cooling.setCompanionHeatingHeatPump(heating));
  ASSERT_TRUE(cooling.companionHeatingHeatPump());
  EXPECT_EQ(heating, cooling.companionHeatingHeatPump().get());
}

TEST_F(EPModelFixture, HeatPumpWaterToWaterEquationFitCooling_DeprecatedCoefficientAliasesDelegateThroughStoredCurves) {
  Model model;
  HeatPumpWaterToWaterEquationFitCooling hp(model);

  EXPECT_TRUE(hp.setCoolingCapacityCoefficient1(1.1));
  EXPECT_TRUE(hp.setCoolingCapacityCoefficient2(1.2));
  EXPECT_TRUE(hp.setCoolingCapacityCoefficient3(1.3));
  EXPECT_TRUE(hp.setCoolingCapacityCoefficient4(1.4));
  EXPECT_TRUE(hp.setCoolingCapacityCoefficient5(1.5));
  EXPECT_DOUBLE_EQ(1.1, hp.coolingCapacityCoefficient1());
  EXPECT_DOUBLE_EQ(1.2, hp.coolingCapacityCoefficient2());
  EXPECT_DOUBLE_EQ(1.3, hp.coolingCapacityCoefficient3());
  EXPECT_DOUBLE_EQ(1.4, hp.coolingCapacityCoefficient4());
  EXPECT_DOUBLE_EQ(1.5, hp.coolingCapacityCoefficient5());

  EXPECT_TRUE(hp.setCoolingCompressorPowerCoefficient1(2.1));
  EXPECT_TRUE(hp.setCoolingCompressorPowerCoefficient2(2.2));
  EXPECT_TRUE(hp.setCoolingCompressorPowerCoefficient3(2.3));
  EXPECT_TRUE(hp.setCoolingCompressorPowerCoefficient4(2.4));
  EXPECT_TRUE(hp.setCoolingCompressorPowerCoefficient5(2.5));
  EXPECT_DOUBLE_EQ(2.1, hp.coolingCompressorPowerCoefficient1());
  EXPECT_DOUBLE_EQ(2.2, hp.coolingCompressorPowerCoefficient2());
  EXPECT_DOUBLE_EQ(2.3, hp.coolingCompressorPowerCoefficient3());
  EXPECT_DOUBLE_EQ(2.4, hp.coolingCompressorPowerCoefficient4());
  EXPECT_DOUBLE_EQ(2.5, hp.coolingCompressorPowerCoefficient5());
}

TEST_F(EPModelFixture, HeatPumpWaterToWaterEquationFitCooling_ScalarAccessors_RoundTrip) {
  Model model;
  HeatPumpWaterToWaterEquationFitCooling hp(model);

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

  EXPECT_TRUE(hp.setRatedCoolingCapacity(12450.0));
  ASSERT_TRUE(hp.ratedCoolingCapacity());
  EXPECT_DOUBLE_EQ(12450.0, *hp.ratedCoolingCapacity());
  hp.autosizeRatedCoolingCapacity();
  EXPECT_TRUE(hp.isRatedCoolingCapacityAutosized());
  EXPECT_FALSE(hp.ratedCoolingCapacity());

  EXPECT_TRUE(hp.setRatedCoolingPowerConsumption(3450.0));
  ASSERT_TRUE(hp.ratedCoolingPowerConsumption());
  EXPECT_DOUBLE_EQ(3450.0, *hp.ratedCoolingPowerConsumption());
  hp.autosizeRatedCoolingPowerConsumption();
  EXPECT_TRUE(hp.isRatedCoolingPowerConsumptionAutosized());
  EXPECT_FALSE(hp.ratedCoolingPowerConsumption());

  EXPECT_TRUE(hp.setReferenceCoefficientofPerformance(7.25));
  EXPECT_DOUBLE_EQ(7.25, hp.referenceCoefficientofPerformance());

  EXPECT_TRUE(hp.setSizingFactor(1.2));
  EXPECT_DOUBLE_EQ(1.2, hp.sizingFactor());
}
