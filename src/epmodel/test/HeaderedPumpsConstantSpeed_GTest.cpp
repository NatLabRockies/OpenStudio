/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../StraightComponent/HeaderedPumpsConstantSpeed.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, HeaderedPumpsConstantSpeed_DefaultConstructor) {
  Model model;
  HeaderedPumpsConstantSpeed pump(model);
  EXPECT_EQ(HeaderedPumpsConstantSpeed::iddObjectType(), pump.iddObject().type());
  EXPECT_FALSE(pump.nameString().empty());

  EXPECT_TRUE(pump.isTotalRatedFlowRateAutosized());
  EXPECT_FALSE(pump.totalRatedFlowRate());
  EXPECT_EQ(2, pump.numberofPumpsinBank());
  EXPECT_EQ("Sequential", pump.flowSequencingControlScheme());
  EXPECT_DOUBLE_EQ(179352.0, pump.ratedPumpHead());
  EXPECT_TRUE(pump.isRatedPowerConsumptionAutosized());
  EXPECT_FALSE(pump.ratedPowerConsumption());
  EXPECT_DOUBLE_EQ(0.9, pump.motorEfficiency());
  EXPECT_DOUBLE_EQ(0.0, pump.fractionofMotorInefficienciestoFluidStream());
  EXPECT_EQ("Continuous", pump.pumpControlType());
  EXPECT_DOUBLE_EQ(0.1, pump.skinLossRadiativeFraction());
  EXPECT_EQ("PowerPerFlowPerPressure", pump.designPowerSizingMethod());
  EXPECT_DOUBLE_EQ(348701.1, pump.designElectricPowerPerUnitFlowRate());
  EXPECT_DOUBLE_EQ(1.282051282, pump.designShaftPowerPerUnitFlowRatePerUnitHead());
  EXPECT_EQ("General", pump.endUseSubcategory());
}

TEST_F(EPModelFixture, HeaderedPumpsConstantSpeed_ScalarAccessors_RoundTrip) {
  Model model;
  HeaderedPumpsConstantSpeed pump(model);

  ASSERT_FALSE(HeaderedPumpsConstantSpeed::flowSequencingControlSchemeValues().empty());
  ASSERT_FALSE(HeaderedPumpsConstantSpeed::pumpControlTypeValues().empty());
  ASSERT_FALSE(HeaderedPumpsConstantSpeed::designPowerSizingMethodValues().empty());

  auto flowSequencingControlScheme = HeaderedPumpsConstantSpeed::flowSequencingControlSchemeValues().front();
  if (flowSequencingControlScheme == pump.flowSequencingControlScheme() &&
      HeaderedPumpsConstantSpeed::flowSequencingControlSchemeValues().size() > 1) {
    flowSequencingControlScheme = HeaderedPumpsConstantSpeed::flowSequencingControlSchemeValues()[1];
  }

  auto pumpControlType = HeaderedPumpsConstantSpeed::pumpControlTypeValues().front();
  if (pumpControlType == pump.pumpControlType() && HeaderedPumpsConstantSpeed::pumpControlTypeValues().size() > 1) {
    pumpControlType = HeaderedPumpsConstantSpeed::pumpControlTypeValues()[1];
  }

  auto designPowerSizingMethod = HeaderedPumpsConstantSpeed::designPowerSizingMethodValues().front();
  if (designPowerSizingMethod == pump.designPowerSizingMethod() &&
      HeaderedPumpsConstantSpeed::designPowerSizingMethodValues().size() > 1) {
    designPowerSizingMethod = HeaderedPumpsConstantSpeed::designPowerSizingMethodValues()[1];
  }

  EXPECT_TRUE(pump.setTotalRatedFlowRate(0.009));
  ASSERT_TRUE(pump.totalRatedFlowRate());
  EXPECT_DOUBLE_EQ(0.009, pump.totalRatedFlowRate().get());
  EXPECT_FALSE(pump.isTotalRatedFlowRateAutosized());

  pump.autosizeTotalRatedFlowRate();
  EXPECT_TRUE(pump.isTotalRatedFlowRateAutosized());
  EXPECT_FALSE(pump.totalRatedFlowRate());

  EXPECT_TRUE(pump.setNumberofPumpsinBank(3));
  EXPECT_EQ(3, pump.numberofPumpsinBank());

  EXPECT_TRUE(pump.setFlowSequencingControlScheme(flowSequencingControlScheme));
  EXPECT_EQ(flowSequencingControlScheme, pump.flowSequencingControlScheme());

  EXPECT_TRUE(pump.setRatedPumpHead(250000.0));
  EXPECT_DOUBLE_EQ(250000.0, pump.ratedPumpHead());

  EXPECT_TRUE(pump.setRatedPowerConsumption(2000.0));
  ASSERT_TRUE(pump.ratedPowerConsumption());
  EXPECT_DOUBLE_EQ(2000.0, pump.ratedPowerConsumption().get());
  EXPECT_FALSE(pump.isRatedPowerConsumptionAutosized());

  pump.autosizeRatedPowerConsumption();
  EXPECT_TRUE(pump.isRatedPowerConsumptionAutosized());
  EXPECT_FALSE(pump.ratedPowerConsumption());

  EXPECT_TRUE(pump.setMotorEfficiency(0.85));
  EXPECT_DOUBLE_EQ(0.85, pump.motorEfficiency());

  EXPECT_TRUE(pump.setFractionofMotorInefficienciestoFluidStream(0.05));
  EXPECT_DOUBLE_EQ(0.05, pump.fractionofMotorInefficienciestoFluidStream());

  EXPECT_TRUE(pump.setPumpControlType(pumpControlType));
  EXPECT_EQ(pumpControlType, pump.pumpControlType());

  EXPECT_TRUE(pump.setSkinLossRadiativeFraction(0.2));
  EXPECT_DOUBLE_EQ(0.2, pump.skinLossRadiativeFraction());

  EXPECT_TRUE(pump.setDesignPowerSizingMethod(designPowerSizingMethod));
  EXPECT_EQ(designPowerSizingMethod, pump.designPowerSizingMethod());

  EXPECT_TRUE(pump.setDesignElectricPowerPerUnitFlowRate(400000.0));
  EXPECT_DOUBLE_EQ(400000.0, pump.designElectricPowerPerUnitFlowRate());

  EXPECT_TRUE(pump.setDesignShaftPowerPerUnitFlowRatePerUnitHead(1.5));
  EXPECT_DOUBLE_EQ(1.5, pump.designShaftPowerPerUnitFlowRatePerUnitHead());

  EXPECT_TRUE(pump.setEndUseSubcategory("Pumps"));
  EXPECT_EQ("Pumps", pump.endUseSubcategory());

  EXPECT_FALSE(pump.autosizedTotalRatedFlowRate());
  EXPECT_FALSE(pump.autosizedRatedPowerConsumption());
}
