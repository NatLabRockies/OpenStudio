/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../StraightComponent/HeatPumpAirToWaterFuelFiredHeating.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, HeatPumpAirToWaterFuelFiredHeating_DefaultConstructor) {
  Model model;
  HeatPumpAirToWaterFuelFiredHeating hp(model);

  EXPECT_EQ(HeatPumpAirToWaterFuelFiredHeating::iddObjectType(), hp.iddObject().type());
  EXPECT_FALSE(hp.nameString().empty());

  EXPECT_EQ("NaturalGas", hp.fuelType());
  EXPECT_TRUE(hp.isNominalHeatingCapacityAutosized());
  EXPECT_DOUBLE_EQ(1.0, hp.nominalCOP());
  EXPECT_TRUE(hp.isDesignFlowRateAutosized());
  EXPECT_DOUBLE_EQ(60.0, hp.designSupplyTemperature());
  ASSERT_TRUE(hp.designTemperatureLift());
  EXPECT_DOUBLE_EQ(11.1, hp.designTemperatureLift().get());
  EXPECT_DOUBLE_EQ(1.0, hp.sizingFactor());
  EXPECT_EQ("NotModulated", hp.flowMode());
  EXPECT_EQ("DryBulb", hp.outdoorAirTemperatureCurveInputVariable());
  EXPECT_EQ("EnteringCondenser", hp.waterTemperatureCurveInputVariable());
  EXPECT_DOUBLE_EQ(0.1, hp.minimumPartLoadRatio());
  EXPECT_DOUBLE_EQ(1.0, hp.maximumPartLoadRatio());
  EXPECT_EQ("Timed", hp.defrostControlType());
  EXPECT_DOUBLE_EQ(0.0, hp.defrostOperationTimeFraction());
  EXPECT_DOUBLE_EQ(0.0, hp.resistiveDefrostHeaterCapacity());
  EXPECT_DOUBLE_EQ(5.0, hp.maximumOutdoorDrybulbTemperatureforDefrostOperation());
  EXPECT_DOUBLE_EQ(0.0, hp.nominalAuxiliaryElectricPower());
  EXPECT_DOUBLE_EQ(0.0, hp.standbyElectricPower());
  EXPECT_DOUBLE_EQ(0.25, hp.minimumUnloadingRatio());
}

TEST_F(EPModelFixture, HeatPumpAirToWaterFuelFiredHeating_ScalarAccessors_RoundTrip) {
  Model model;
  HeatPumpAirToWaterFuelFiredHeating hp(model);

  const auto fuelTypeValues = HeatPumpAirToWaterFuelFiredHeating::fuelTypeValues();
  ASSERT_FALSE(fuelTypeValues.empty());
  EXPECT_TRUE(hp.setFuelType(fuelTypeValues.front()));
  EXPECT_EQ(fuelTypeValues.front(), hp.fuelType());

  EXPECT_TRUE(hp.setEndUseSubcategory("Process"));
  EXPECT_EQ("Process", hp.endUseSubcategory());
  hp.resetEndUseSubcategory();
  EXPECT_TRUE(hp.isEndUseSubcategoryDefaulted());

  EXPECT_TRUE(hp.setNominalHeatingCapacity(15000.0));
  ASSERT_TRUE(hp.nominalHeatingCapacity());
  EXPECT_DOUBLE_EQ(15000.0, hp.nominalHeatingCapacity().get());
  hp.autosizeNominalHeatingCapacity();
  EXPECT_TRUE(hp.isNominalHeatingCapacityAutosized());
  hp.resetNominalHeatingCapacity();
  EXPECT_FALSE(hp.nominalHeatingCapacity());

  EXPECT_TRUE(hp.setNominalCOP(1.45));
  EXPECT_DOUBLE_EQ(1.45, hp.nominalCOP());

  EXPECT_TRUE(hp.setDesignFlowRate(0.020));
  ASSERT_TRUE(hp.designFlowRate());
  EXPECT_DOUBLE_EQ(0.020, hp.designFlowRate().get());
  hp.autosizeDesignFlowRate();
  EXPECT_TRUE(hp.isDesignFlowRateAutosized());
  hp.resetDesignFlowRate();
  EXPECT_FALSE(hp.designFlowRate());

  EXPECT_TRUE(hp.setDesignSupplyTemperature(55.0));
  EXPECT_DOUBLE_EQ(55.0, hp.designSupplyTemperature());

  EXPECT_TRUE(hp.setDesignTemperatureLift(10.0));
  ASSERT_TRUE(hp.designTemperatureLift());
  EXPECT_DOUBLE_EQ(10.0, hp.designTemperatureLift().get());
  hp.autosizeDesignTemperatureLift();
  EXPECT_TRUE(hp.isDesignTemperatureLiftAutosized());

  EXPECT_TRUE(hp.setSizingFactor(1.15));
  EXPECT_DOUBLE_EQ(1.15, hp.sizingFactor());

  const auto flowModeValues = HeatPumpAirToWaterFuelFiredHeating::flowModeValues();
  ASSERT_FALSE(flowModeValues.empty());
  EXPECT_TRUE(hp.setFlowMode(flowModeValues.front()));
  EXPECT_EQ(flowModeValues.front(), hp.flowMode());

  const auto outdoorCurveInputValues = HeatPumpAirToWaterFuelFiredHeating::outdoorAirTemperatureCurveInputVariableValues();
  ASSERT_FALSE(outdoorCurveInputValues.empty());
  EXPECT_TRUE(hp.setOutdoorAirTemperatureCurveInputVariable(outdoorCurveInputValues.front()));
  EXPECT_EQ(outdoorCurveInputValues.front(), hp.outdoorAirTemperatureCurveInputVariable());

  const auto waterCurveInputValues = HeatPumpAirToWaterFuelFiredHeating::waterTemperatureCurveInputVariableValues();
  ASSERT_FALSE(waterCurveInputValues.empty());
  EXPECT_TRUE(hp.setWaterTemperatureCurveInputVariable(waterCurveInputValues.front()));
  EXPECT_EQ(waterCurveInputValues.front(), hp.waterTemperatureCurveInputVariable());

  EXPECT_TRUE(hp.setMinimumPartLoadRatio(0.2));
  EXPECT_DOUBLE_EQ(0.2, hp.minimumPartLoadRatio());

  EXPECT_TRUE(hp.setMaximumPartLoadRatio(0.95));
  EXPECT_DOUBLE_EQ(0.95, hp.maximumPartLoadRatio());

  const auto defrostControlTypeValues = HeatPumpAirToWaterFuelFiredHeating::defrostControlTypeValues();
  ASSERT_FALSE(defrostControlTypeValues.empty());
  EXPECT_TRUE(hp.setDefrostControlType(defrostControlTypeValues.front()));
  EXPECT_EQ(defrostControlTypeValues.front(), hp.defrostControlType());

  EXPECT_TRUE(hp.setDefrostOperationTimeFraction(0.15));
  EXPECT_DOUBLE_EQ(0.15, hp.defrostOperationTimeFraction());

  EXPECT_TRUE(hp.setResistiveDefrostHeaterCapacity(500.0));
  EXPECT_DOUBLE_EQ(500.0, hp.resistiveDefrostHeaterCapacity());

  EXPECT_TRUE(hp.setMaximumOutdoorDrybulbTemperatureforDefrostOperation(3.0));
  EXPECT_DOUBLE_EQ(3.0, hp.maximumOutdoorDrybulbTemperatureforDefrostOperation());

  EXPECT_TRUE(hp.setNominalAuxiliaryElectricPower(250.0));
  EXPECT_DOUBLE_EQ(250.0, hp.nominalAuxiliaryElectricPower());

  EXPECT_TRUE(hp.setStandbyElectricPower(40.0));
  EXPECT_DOUBLE_EQ(40.0, hp.standbyElectricPower());

  EXPECT_TRUE(hp.setMinimumUnloadingRatio(0.5));
  EXPECT_DOUBLE_EQ(0.5, hp.minimumUnloadingRatio());
}
