/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/PumpVariableSpeedCondensate.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, PumpVariableSpeedCondensate_DefaultConstructor) {
  Model model;
  PumpVariableSpeedCondensate pump(model);
  EXPECT_EQ(PumpVariableSpeedCondensate::iddObjectType(), pump.iddObject().type());
}

TEST_F(EPModelFixture, PumpVariableSpeedCondensate_ScalarAccessors_RoundTrip) {
  Model model;
  PumpVariableSpeedCondensate pump(model);

  EXPECT_TRUE(pump.setDesignSteamVolumeFlowRate(0.2));
  ASSERT_TRUE(pump.designSteamVolumeFlowRate());
  EXPECT_DOUBLE_EQ(0.2, pump.designSteamVolumeFlowRate().get());
  pump.autosizeDesignSteamVolumeFlowRate();
  EXPECT_TRUE(pump.isDesignSteamVolumeFlowRateAutosized());
  pump.resetDesignSteamVolumeFlowRate();
  EXPECT_FALSE(pump.designSteamVolumeFlowRate());

  EXPECT_TRUE(pump.setDesignPumpHead(210000.0));
  EXPECT_DOUBLE_EQ(210000.0, pump.designPumpHead());
  EXPECT_FALSE(pump.isDesignPumpHeadDefaulted());
  pump.resetDesignPumpHead();
  EXPECT_TRUE(pump.isDesignPumpHeadDefaulted());

  EXPECT_TRUE(pump.setDesignPowerConsumption(5000.0));
  ASSERT_TRUE(pump.designPowerConsumption());
  EXPECT_DOUBLE_EQ(5000.0, pump.designPowerConsumption().get());
  pump.autosizeDesignPowerConsumption();
  EXPECT_TRUE(pump.isDesignPowerConsumptionAutosized());
  pump.resetDesignPowerConsumption();
  EXPECT_FALSE(pump.designPowerConsumption());

  EXPECT_TRUE(pump.setMotorEfficiency(0.95));
  EXPECT_DOUBLE_EQ(0.95, pump.motorEfficiency());
  EXPECT_FALSE(pump.isMotorEfficiencyDefaulted());
  pump.resetMotorEfficiency();
  EXPECT_TRUE(pump.isMotorEfficiencyDefaulted());

  EXPECT_TRUE(pump.setFractionOfMotorInefficienciesToFluidStream(0.3));
  EXPECT_DOUBLE_EQ(0.3, pump.fractionOfMotorInefficienciesToFluidStream());
  pump.resetFractionOfMotorInefficienciesToFluidStream();
  EXPECT_TRUE(pump.isFractionOfMotorInefficienciesToFluidStreamDefaulted());

  EXPECT_TRUE(pump.setCoefficient1OfThePartLoadPerformanceCurve(0.1));
  EXPECT_DOUBLE_EQ(0.1, pump.coefficient1OfThePartLoadPerformanceCurve());
  pump.resetCoefficient1OfThePartLoadPerformanceCurve();
  EXPECT_TRUE(pump.isCoefficient1OfThePartLoadPerformanceCurveDefaulted());

  EXPECT_TRUE(pump.setCoefficient2OfThePartLoadPerformanceCurve(1.1));
  EXPECT_DOUBLE_EQ(1.1, pump.coefficient2OfThePartLoadPerformanceCurve());
  pump.resetCoefficient2OfThePartLoadPerformanceCurve();
  EXPECT_TRUE(pump.isCoefficient2OfThePartLoadPerformanceCurveDefaulted());

  EXPECT_TRUE(pump.setCoefficient3OfThePartLoadPerformanceCurve(0.5));
  EXPECT_DOUBLE_EQ(0.5, pump.coefficient3OfThePartLoadPerformanceCurve());
  pump.resetCoefficient3OfThePartLoadPerformanceCurve();
  EXPECT_TRUE(pump.isCoefficient3OfThePartLoadPerformanceCurveDefaulted());

  EXPECT_TRUE(pump.setCoefficient4OfThePartLoadPerformanceCurve(0.2));
  EXPECT_DOUBLE_EQ(0.2, pump.coefficient4OfThePartLoadPerformanceCurve());
  pump.resetCoefficient4OfThePartLoadPerformanceCurve();
  EXPECT_TRUE(pump.isCoefficient4OfThePartLoadPerformanceCurveDefaulted());

  EXPECT_TRUE(pump.setSkinLossRadiativeFraction(0.25));
  ASSERT_TRUE(pump.skinLossRadiativeFraction());
  EXPECT_DOUBLE_EQ(0.25, pump.skinLossRadiativeFraction().get());
  pump.resetSkinLossRadiativeFraction();
  EXPECT_FALSE(pump.skinLossRadiativeFraction());

  const auto designPowerSizingMethodValues = PumpVariableSpeedCondensate::designPowerSizingMethodValues();
  ASSERT_GE(designPowerSizingMethodValues.size(), 2u);
  EXPECT_TRUE(pump.setDesignPowerSizingMethod(designPowerSizingMethodValues.front()));
  EXPECT_EQ(designPowerSizingMethodValues.front(), pump.designPowerSizingMethod());
  pump.resetDesignPowerSizingMethod();
  EXPECT_TRUE(pump.isDesignPowerSizingMethodDefaulted());

  EXPECT_TRUE(pump.setDesignElectricPowerPerUnitFlowRate(450000.0));
  EXPECT_DOUBLE_EQ(450000.0, pump.designElectricPowerPerUnitFlowRate());
  pump.resetDesignElectricPowerPerUnitFlowRate();
  EXPECT_TRUE(pump.isDesignElectricPowerPerUnitFlowRateDefaulted());

  EXPECT_TRUE(pump.setDesignShaftPowerPerUnitFlowRatePerUnitHead(1.5));
  EXPECT_DOUBLE_EQ(1.5, pump.designShaftPowerPerUnitFlowRatePerUnitHead());
  pump.resetDesignShaftPowerPerUnitFlowRatePerUnitHead();
  EXPECT_TRUE(pump.isDesignShaftPowerPerUnitFlowRatePerUnitHeadDefaulted());

  EXPECT_TRUE(pump.setEndUseSubcategory("SteamCondensate"));
  EXPECT_EQ("SteamCondensate", pump.endUseSubcategory());
  EXPECT_FALSE(pump.isEndUseSubcategoryDefaulted());
  pump.resetEndUseSubcategory();
  EXPECT_TRUE(pump.isEndUseSubcategoryDefaulted());
}
