/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../StraightComponent/Node.hpp"
#include "../StraightComponent/HeaderedPumpsVariableSpeed.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, HeaderedPumpsVariableSpeed_DefaultConstructor) {
  Model model;
  HeaderedPumpsVariableSpeed pump(model);
  EXPECT_EQ(HeaderedPumpsVariableSpeed::iddObjectType(), pump.iddObject().type());
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
  EXPECT_DOUBLE_EQ(0.0, pump.coefficient1ofthePartLoadPerformanceCurve());
  EXPECT_DOUBLE_EQ(1.0, pump.coefficient2ofthePartLoadPerformanceCurve());
  EXPECT_DOUBLE_EQ(0.0, pump.coefficient3ofthePartLoadPerformanceCurve());
  EXPECT_DOUBLE_EQ(0.0, pump.coefficient4ofthePartLoadPerformanceCurve());
  EXPECT_DOUBLE_EQ(0.0, pump.minimumFlowRateFraction());
  EXPECT_EQ("Continuous", pump.pumpControlType());
  EXPECT_DOUBLE_EQ(0.1, pump.skinLossRadiativeFraction());
  EXPECT_EQ("PowerPerFlowPerPressure", pump.designPowerSizingMethod());
  EXPECT_DOUBLE_EQ(348701.1, pump.designElectricPowerPerUnitFlowRate());
  EXPECT_DOUBLE_EQ(1.282051282, pump.designShaftPowerPerUnitFlowRatePerUnitHead());
  EXPECT_EQ("General", pump.endUseSubcategory());
}

TEST_F(EPModelFixture, HeaderedPumpsVariableSpeed_ScalarAccessors_RoundTrip) {
  Model model;
  HeaderedPumpsVariableSpeed pump(model);

  ASSERT_FALSE(HeaderedPumpsVariableSpeed::flowSequencingControlSchemeValues().empty());
  ASSERT_FALSE(HeaderedPumpsVariableSpeed::pumpControlTypeValues().empty());
  ASSERT_FALSE(HeaderedPumpsVariableSpeed::designPowerSizingMethodValues().empty());

  auto flowSequencingControlScheme = HeaderedPumpsVariableSpeed::flowSequencingControlSchemeValues().front();
  if (flowSequencingControlScheme == pump.flowSequencingControlScheme()
      && HeaderedPumpsVariableSpeed::flowSequencingControlSchemeValues().size() > 1) {
    flowSequencingControlScheme = HeaderedPumpsVariableSpeed::flowSequencingControlSchemeValues()[1];
  }

  auto pumpControlType = HeaderedPumpsVariableSpeed::pumpControlTypeValues().front();
  if (pumpControlType == pump.pumpControlType() && HeaderedPumpsVariableSpeed::pumpControlTypeValues().size() > 1) {
    pumpControlType = HeaderedPumpsVariableSpeed::pumpControlTypeValues()[1];
  }

  auto designPowerSizingMethod = HeaderedPumpsVariableSpeed::designPowerSizingMethodValues().front();
  if (designPowerSizingMethod == pump.designPowerSizingMethod() && HeaderedPumpsVariableSpeed::designPowerSizingMethodValues().size() > 1) {
    designPowerSizingMethod = HeaderedPumpsVariableSpeed::designPowerSizingMethodValues()[1];
  }

  EXPECT_TRUE(pump.setTotalRatedFlowRate(0.009));
  ASSERT_TRUE(pump.totalRatedFlowRate());
  EXPECT_DOUBLE_EQ(0.009, pump.totalRatedFlowRate().get());
  EXPECT_FALSE(pump.isTotalRatedFlowRateAutosized());

  pump.autosizeTotalRatedFlowRate();
  EXPECT_TRUE(pump.isTotalRatedFlowRateAutosized());
  EXPECT_FALSE(pump.totalRatedFlowRate());

  EXPECT_TRUE(pump.setNumberofPumpsinBank(4));
  EXPECT_EQ(4, pump.numberofPumpsinBank());

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

  EXPECT_TRUE(pump.setCoefficient1ofthePartLoadPerformanceCurve(0.1));
  EXPECT_DOUBLE_EQ(0.1, pump.coefficient1ofthePartLoadPerformanceCurve());

  EXPECT_TRUE(pump.setCoefficient2ofthePartLoadPerformanceCurve(0.8));
  EXPECT_DOUBLE_EQ(0.8, pump.coefficient2ofthePartLoadPerformanceCurve());

  EXPECT_TRUE(pump.setCoefficient3ofthePartLoadPerformanceCurve(0.05));
  EXPECT_DOUBLE_EQ(0.05, pump.coefficient3ofthePartLoadPerformanceCurve());

  EXPECT_TRUE(pump.setCoefficient4ofthePartLoadPerformanceCurve(0.05));
  EXPECT_DOUBLE_EQ(0.05, pump.coefficient4ofthePartLoadPerformanceCurve());

  EXPECT_TRUE(pump.setMinimumFlowRateFraction(0.2));
  EXPECT_DOUBLE_EQ(0.2, pump.minimumFlowRateFraction());

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

TEST_F(EPModelFixture, HeaderedPumpsVariableSpeed_AddToNode_PlantOnly) {
  Model model;
  HeaderedPumpsVariableSpeed pump(model);

  AirLoopHVAC airLoop(model);
  Node airSupplyOutletNode = airLoop.supplyOutletNode();
  EXPECT_FALSE(pump.addToNode(airSupplyOutletNode));
  EXPECT_EQ(2u, airLoop.supplyComponents().size());

  Node airDemandNode = airLoop.zoneSplitter().lastOutletModelObject()->cast<Node>();
  EXPECT_FALSE(pump.addToNode(airDemandNode));
  EXPECT_EQ(5u, airLoop.demandComponents().size());

  PlantLoop plantLoop(model);
  Node plantSupplyOutletNode = plantLoop.supplyOutletNode();
  EXPECT_TRUE(pump.addToNode(plantSupplyOutletNode));
  EXPECT_EQ(7u, plantLoop.supplyComponents().size());

  Node plantDemandOutletNode = plantLoop.demandOutletNode();
  EXPECT_TRUE(pump.addToNode(plantDemandOutletNode));
  EXPECT_EQ(7u, plantLoop.demandComponents().size());

  HeaderedPumpsVariableSpeed pump2(model);
  EXPECT_TRUE(pump2.addToNode(plantDemandOutletNode));
  EXPECT_EQ(9u, plantLoop.demandComponents().size());
}
