/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../StraightComponent/HeatPumpAirToWaterFuelFiredCooling.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, HeatPumpAirToWaterFuelFiredCooling_DefaultConstructor) {
  Model model;
  HeatPumpAirToWaterFuelFiredCooling hp(model);

  EXPECT_EQ(HeatPumpAirToWaterFuelFiredCooling::iddObjectType(), hp.iddObject().type());
  EXPECT_FALSE(hp.nameString().empty());

  EXPECT_EQ("NaturalGas", hp.fuelType());
  EXPECT_TRUE(hp.isNominalCoolingCapacityAutosized());
  EXPECT_DOUBLE_EQ(1.0, hp.nominalCOP());
  EXPECT_TRUE(hp.isDesignFlowRateAutosized());
  EXPECT_DOUBLE_EQ(7.0, hp.designSupplyTemperature());
  EXPECT_DOUBLE_EQ(11.1, hp.designTemperatureLift().get());
  EXPECT_DOUBLE_EQ(1.0, hp.sizingFactor());
  EXPECT_EQ("NotModulated", hp.flowMode());
  EXPECT_EQ("DryBulb", hp.outdoorAirTemperatureCurveInputVariable());
  EXPECT_EQ("EnteringEvaporator", hp.waterTemperatureCurveInputVariable());
  EXPECT_DOUBLE_EQ(0.1, hp.minimumPartLoadRatio());
  EXPECT_DOUBLE_EQ(1.0, hp.maximumPartLoadRatio());
  EXPECT_DOUBLE_EQ(0.0, hp.nominalAuxiliaryElectricPower());
  EXPECT_DOUBLE_EQ(0.0, hp.standbyElectricPower());
  EXPECT_DOUBLE_EQ(0.25, hp.minimumUnloadingRatio());
}

TEST_F(EPModelFixture, HeatPumpAirToWaterFuelFiredCooling_ScalarAccessors_RoundTrip) {
  Model model;
  HeatPumpAirToWaterFuelFiredCooling hp(model);

  const auto fuelTypeValues = HeatPumpAirToWaterFuelFiredCooling::fuelTypeValues();
  ASSERT_FALSE(fuelTypeValues.empty());
  EXPECT_TRUE(hp.setFuelType(fuelTypeValues.front()));
  EXPECT_EQ(fuelTypeValues.front(), hp.fuelType());

  EXPECT_TRUE(hp.setEndUseSubcategory("Process"));
  EXPECT_EQ("Process", hp.endUseSubcategory());
  hp.resetEndUseSubcategory();
  EXPECT_TRUE(hp.isEndUseSubcategoryDefaulted());

  EXPECT_TRUE(hp.setNominalCoolingCapacity(12000.0));
  ASSERT_TRUE(hp.nominalCoolingCapacity());
  EXPECT_DOUBLE_EQ(12000.0, hp.nominalCoolingCapacity().get());
  hp.autosizeNominalCoolingCapacity();
  EXPECT_TRUE(hp.isNominalCoolingCapacityAutosized());
  hp.resetNominalCoolingCapacity();
  EXPECT_FALSE(hp.nominalCoolingCapacity());

  EXPECT_TRUE(hp.setNominalCOP(1.35));
  EXPECT_DOUBLE_EQ(1.35, hp.nominalCOP());

  EXPECT_TRUE(hp.setDesignFlowRate(0.015));
  ASSERT_TRUE(hp.designFlowRate());
  EXPECT_DOUBLE_EQ(0.015, hp.designFlowRate().get());
  hp.autosizeDesignFlowRate();
  EXPECT_TRUE(hp.isDesignFlowRateAutosized());
  hp.resetDesignFlowRate();
  EXPECT_FALSE(hp.designFlowRate());

  EXPECT_TRUE(hp.setDesignSupplyTemperature(6.7));
  EXPECT_DOUBLE_EQ(6.7, hp.designSupplyTemperature());

  EXPECT_TRUE(hp.setDesignTemperatureLift(9.8));
  ASSERT_TRUE(hp.designTemperatureLift());
  EXPECT_DOUBLE_EQ(9.8, hp.designTemperatureLift().get());
  hp.autosizeDesignTemperatureLift();
  EXPECT_TRUE(hp.isDesignTemperatureLiftAutosized());

  EXPECT_TRUE(hp.setSizingFactor(1.2));
  EXPECT_DOUBLE_EQ(1.2, hp.sizingFactor());

  const auto flowModeValues = HeatPumpAirToWaterFuelFiredCooling::flowModeValues();
  ASSERT_FALSE(flowModeValues.empty());
  EXPECT_TRUE(hp.setFlowMode(flowModeValues.front()));
  EXPECT_EQ(flowModeValues.front(), hp.flowMode());

  const auto outdoorCurveInputValues = HeatPumpAirToWaterFuelFiredCooling::outdoorAirTemperatureCurveInputVariableValues();
  ASSERT_FALSE(outdoorCurveInputValues.empty());
  EXPECT_TRUE(hp.setOutdoorAirTemperatureCurveInputVariable(outdoorCurveInputValues.front()));
  EXPECT_EQ(outdoorCurveInputValues.front(), hp.outdoorAirTemperatureCurveInputVariable());

  const auto waterCurveInputValues = HeatPumpAirToWaterFuelFiredCooling::waterTemperatureCurveInputVariableValues();
  ASSERT_FALSE(waterCurveInputValues.empty());
  EXPECT_TRUE(hp.setWaterTemperatureCurveInputVariable(waterCurveInputValues.front()));
  EXPECT_EQ(waterCurveInputValues.front(), hp.waterTemperatureCurveInputVariable());

  EXPECT_TRUE(hp.setMinimumPartLoadRatio(0.2));
  EXPECT_DOUBLE_EQ(0.2, hp.minimumPartLoadRatio());

  EXPECT_TRUE(hp.setMaximumPartLoadRatio(0.95));
  EXPECT_DOUBLE_EQ(0.95, hp.maximumPartLoadRatio());

  EXPECT_TRUE(hp.setNominalAuxiliaryElectricPower(150.0));
  EXPECT_DOUBLE_EQ(150.0, hp.nominalAuxiliaryElectricPower());

  EXPECT_TRUE(hp.setStandbyElectricPower(23.0));
  EXPECT_DOUBLE_EQ(23.0, hp.standbyElectricPower());

  EXPECT_TRUE(hp.setMinimumUnloadingRatio(0.4));
  EXPECT_DOUBLE_EQ(0.4, hp.minimumUnloadingRatio());
}
