/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../StraightComponent/Node.hpp"
#include "../StraightComponent/PumpVariableSpeed.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, PumpVariableSpeed_DefaultConstructor) {
  Model model;
  PumpVariableSpeed pump(model);
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::Pump_VariableSpeed), pump.iddObject().type());
  EXPECT_FALSE(pump.nameString().empty());
  EXPECT_FALSE(pump.isPumpControlTypeDefaulted());
  EXPECT_EQ("Intermittent", pump.pumpControlType());
  EXPECT_DOUBLE_EQ(0.5, pump.skinLossRadiativeFraction());
  EXPECT_EQ("PowerPerFlowPerPressure", pump.designPowerSizingMethod());
  EXPECT_DOUBLE_EQ(348701.1, pump.designElectricPowerPerUnitFlowRate());
  EXPECT_DOUBLE_EQ(1.282051282, pump.designShaftPowerPerUnitFlowRatePerUnitHead());
  EXPECT_DOUBLE_EQ(0.0, pump.designMinimumFlowRateFraction());
  EXPECT_EQ("General", pump.endUseSubcategory());
}

TEST_F(EPModelFixture, PumpVariableSpeed_ScalarAccessors_RoundTrip) {
  Model model;
  PumpVariableSpeed pump(model);

  EXPECT_TRUE(pump.isRatedFlowRateDefaulted());
  EXPECT_TRUE(pump.setRatedFlowRate(0.31));
  ASSERT_TRUE(pump.ratedFlowRate());
  EXPECT_DOUBLE_EQ(0.31, pump.ratedFlowRate().get());
  EXPECT_FALSE(pump.isRatedFlowRateDefaulted());

  pump.autosizeRatedFlowRate();
  EXPECT_TRUE(pump.isRatedFlowRateAutosized());

  pump.resetRatedFlowRate();
  EXPECT_FALSE(pump.ratedFlowRate());
  EXPECT_FALSE(pump.isRatedFlowRateAutosized());

  EXPECT_TRUE(pump.setRatedPumpHead(420.0));
  EXPECT_DOUBLE_EQ(420.0, pump.ratedPumpHead());
  pump.resetRatedPumpHead();
  EXPECT_TRUE(pump.isRatedPumpHeadDefaulted());

  EXPECT_TRUE(pump.setRatedPowerConsumption(820.0));
  ASSERT_TRUE(pump.ratedPowerConsumption());
  EXPECT_DOUBLE_EQ(820.0, pump.ratedPowerConsumption().get());
  EXPECT_FALSE(pump.isRatedPowerConsumptionDefaulted());

  pump.autosizeRatedPowerConsumption();
  EXPECT_TRUE(pump.isRatedPowerConsumptionAutosized());

  pump.resetRatedPowerConsumption();
  EXPECT_FALSE(pump.ratedPowerConsumption());
  EXPECT_FALSE(pump.isRatedPowerConsumptionAutosized());

  EXPECT_TRUE(pump.isMotorEfficiencyDefaulted());
  EXPECT_TRUE(pump.setMotorEfficiency(0.91));
  EXPECT_DOUBLE_EQ(0.91, pump.motorEfficiency());
  pump.resetMotorEfficiency();
  EXPECT_TRUE(pump.isMotorEfficiencyDefaulted());

  EXPECT_TRUE(pump.isFractionofMotorInefficienciestoFluidStreamDefaulted());
  EXPECT_TRUE(pump.setFractionofMotorInefficienciestoFluidStream(0.4));
  EXPECT_DOUBLE_EQ(0.4, pump.fractionofMotorInefficienciestoFluidStream());
  pump.resetFractionofMotorInefficienciestoFluidStream();
  EXPECT_TRUE(pump.isFractionofMotorInefficienciestoFluidStreamDefaulted());

  EXPECT_TRUE(pump.setCoefficient1ofthePartLoadPerformanceCurve(0.0012));
  EXPECT_DOUBLE_EQ(0.0012, pump.coefficient1ofthePartLoadPerformanceCurve());
  pump.resetCoefficient1ofthePartLoadPerformanceCurve();

  EXPECT_TRUE(pump.setCoefficient2ofthePartLoadPerformanceCurve(0.0034));
  EXPECT_DOUBLE_EQ(0.0034, pump.coefficient2ofthePartLoadPerformanceCurve());
  pump.resetCoefficient2ofthePartLoadPerformanceCurve();

  EXPECT_TRUE(pump.setCoefficient3ofthePartLoadPerformanceCurve(1.23));
  EXPECT_DOUBLE_EQ(1.23, pump.coefficient3ofthePartLoadPerformanceCurve());
  pump.resetCoefficient3ofthePartLoadPerformanceCurve();

  EXPECT_TRUE(pump.setCoefficient4ofthePartLoadPerformanceCurve(-0.12));
  EXPECT_DOUBLE_EQ(-0.12, pump.coefficient4ofthePartLoadPerformanceCurve());
  pump.resetCoefficient4ofthePartLoadPerformanceCurve();

  EXPECT_TRUE(pump.isMinimumFlowRateDefaulted());
  EXPECT_TRUE(pump.setMinimumFlowRate(0.05));
  EXPECT_DOUBLE_EQ(0.05, pump.minimumFlowRate());
  pump.resetMinimumFlowRate();
  EXPECT_TRUE(pump.isMinimumFlowRateDefaulted());

  const auto controlTypes = PumpVariableSpeed::pumpControlTypeValues();
  ASSERT_FALSE(controlTypes.empty());
  EXPECT_TRUE(pump.setPumpControlType(controlTypes.front()));
  EXPECT_EQ(controlTypes.front(), pump.pumpControlType());
  EXPECT_FALSE(pump.isPumpControlTypeDefaulted());
  pump.resetPumpControlType();
  EXPECT_TRUE(pump.isPumpControlTypeDefaulted());

  EXPECT_FALSE(pump.impellerDiameter());
  EXPECT_TRUE(pump.setImpellerDiameter(0.12));
  ASSERT_TRUE(pump.impellerDiameter());
  EXPECT_DOUBLE_EQ(0.12, pump.impellerDiameter().get());
  pump.resetImpellerDiameter();
  EXPECT_FALSE(pump.impellerDiameter());

  const auto vfdValues = PumpVariableSpeed::vfdControlTypeValues();
  ASSERT_FALSE(vfdValues.empty());
  EXPECT_TRUE(pump.setVFDControlType(vfdValues.front()));
  ASSERT_TRUE(pump.vFDControlType());
  EXPECT_EQ(vfdValues.front(), pump.vFDControlType().get());
  pump.resetVFDControlType();

  EXPECT_TRUE(pump.setSkinLossRadiativeFraction(0.54));
  EXPECT_DOUBLE_EQ(0.54, pump.skinLossRadiativeFraction());

  const auto designMethods = PumpVariableSpeed::designPowerSizingMethodValues();
  ASSERT_FALSE(designMethods.empty());
  EXPECT_TRUE(pump.setDesignPowerSizingMethod(designMethods.front()));
  EXPECT_EQ(designMethods.front(), pump.designPowerSizingMethod());

  EXPECT_TRUE(pump.setDesignElectricPowerPerUnitFlowRate(348701.0));
  EXPECT_DOUBLE_EQ(348701.0, pump.designElectricPowerPerUnitFlowRate());

  EXPECT_TRUE(pump.setDesignShaftPowerPerUnitFlowRatePerUnitHead(1.1));
  EXPECT_DOUBLE_EQ(1.1, pump.designShaftPowerPerUnitFlowRatePerUnitHead());

  EXPECT_TRUE(pump.setDesignMinimumFlowRateFraction(0.1));
  EXPECT_DOUBLE_EQ(0.1, pump.designMinimumFlowRateFraction());

  EXPECT_TRUE(pump.setEndUseSubcategory("General"));
  EXPECT_EQ("General", pump.endUseSubcategory());
}

TEST_F(EPModelFixture, PumpVariableSpeed_AddToNode_PlantOnly) {
  Model model;
  PumpVariableSpeed pump(model);

  AirLoopHVAC airLoop(model);
  auto airSupplyOutletNode = airLoop.supplyOutletNode();
  EXPECT_FALSE(pump.addToNode(airSupplyOutletNode));
  EXPECT_EQ(2u, airLoop.supplyComponents().size());

  PlantLoop plantLoop(model);
  auto supplyOutletNode = plantLoop.supplyOutletNode();
  EXPECT_TRUE(pump.addToNode(supplyOutletNode));
  EXPECT_EQ(7u, plantLoop.supplyComponents().size());

  auto demandOutletNode = plantLoop.demandOutletNode();
  EXPECT_TRUE(pump.addToNode(demandOutletNode));
  EXPECT_EQ(7u, plantLoop.demandComponents().size());

  PumpVariableSpeed pump2(model);
  EXPECT_TRUE(pump2.addToNode(demandOutletNode));
  EXPECT_EQ(9u, plantLoop.demandComponents().size());
}
