/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../WaterToAirComponent/CoilHeatingWaterToAirHeatPumpEquationFit.hpp"

#include <utilities/idd/Coil_Heating_WaterToAirHeatPump_EquationFit_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilHeatingWaterToAirHeatPumpEquationFit_DefaultConstructor) {
  Model model;
  CoilHeatingWaterToAirHeatPumpEquationFit coil(model);
  EXPECT_EQ(CoilHeatingWaterToAirHeatPumpEquationFit::iddObjectType(), coil.iddObject().type());
  EXPECT_EQ(openstudio::Coil_Heating_WaterToAirHeatPump_EquationFitFields::AirInletNodeName, coil.airInletPort());
  EXPECT_EQ(openstudio::Coil_Heating_WaterToAirHeatPump_EquationFitFields::AirOutletNodeName, coil.airOutletPort());
  EXPECT_EQ(openstudio::Coil_Heating_WaterToAirHeatPump_EquationFitFields::WaterInletNodeName, coil.waterInletPort());
  EXPECT_EQ(openstudio::Coil_Heating_WaterToAirHeatPump_EquationFitFields::WaterOutletNodeName, coil.waterOutletPort());
  EXPECT_FALSE(coil.airInletModelObject());
  EXPECT_FALSE(coil.airOutletModelObject());
  EXPECT_FALSE(coil.waterInletModelObject());
  EXPECT_FALSE(coil.waterOutletModelObject());
}

TEST_F(EPModelFixture, CoilHeatingWaterToAirHeatPumpEquationFit_ScalarAccessors_RoundTrip) {
  Model model;
  CoilHeatingWaterToAirHeatPumpEquationFit coil(model);

  EXPECT_TRUE(coil.setRatedAirFlowRate(0.73));
  ASSERT_TRUE(coil.ratedAirFlowRate());
  EXPECT_DOUBLE_EQ(0.73, coil.ratedAirFlowRate().get());
  EXPECT_FALSE(coil.isRatedAirFlowRateAutosized());
  coil.autosizeRatedAirFlowRate();
  EXPECT_TRUE(coil.isRatedAirFlowRateAutosized());
  coil.resetRatedAirFlowRate();
  EXPECT_TRUE(coil.isRatedAirFlowRateDefaulted());

  EXPECT_TRUE(coil.setRatedWaterFlowRate(0.0033));
  ASSERT_TRUE(coil.ratedWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.0033, coil.ratedWaterFlowRate().get());
  EXPECT_FALSE(coil.isRatedWaterFlowRateAutosized());
  coil.autosizeRatedWaterFlowRate();
  EXPECT_TRUE(coil.isRatedWaterFlowRateAutosized());
  coil.resetRatedWaterFlowRate();
  EXPECT_TRUE(coil.isRatedWaterFlowRateDefaulted());

  EXPECT_TRUE(coil.setRatedHeatingCapacity(8300.0));
  ASSERT_TRUE(coil.ratedHeatingCapacity());
  EXPECT_DOUBLE_EQ(8300.0, coil.ratedHeatingCapacity().get());
  EXPECT_FALSE(coil.isRatedHeatingCapacityAutosized());
  coil.autosizeRatedHeatingCapacity();
  EXPECT_TRUE(coil.isRatedHeatingCapacityAutosized());
  coil.resetRatedHeatingCapacity();
  EXPECT_TRUE(coil.isRatedHeatingCapacityDefaulted());

  EXPECT_TRUE(coil.isRatedHeatingCoefficientofPerformanceDefaulted());
  EXPECT_TRUE(coil.setRatedHeatingCoefficientofPerformance(4.5));
  EXPECT_DOUBLE_EQ(4.5, coil.ratedHeatingCoefficientofPerformance());
  EXPECT_FALSE(coil.isRatedHeatingCoefficientofPerformanceDefaulted());
  coil.resetRatedHeatingCoefficientofPerformance();
  EXPECT_TRUE(coil.isRatedHeatingCoefficientofPerformanceDefaulted());

  EXPECT_TRUE(coil.setRatedEnteringWaterTemperature(20.0));
  EXPECT_DOUBLE_EQ(20.0, coil.ratedEnteringWaterTemperature());

  EXPECT_TRUE(coil.setRatedEnteringAirDryBulbTemperature(20.0));
  EXPECT_DOUBLE_EQ(20.0, coil.ratedEnteringAirDryBulbTemperature());

  EXPECT_TRUE(coil.setRatioofRatedHeatingCapacitytoRatedCoolingCapacity(1.25));
  EXPECT_DOUBLE_EQ(1.25, coil.ratioofRatedHeatingCapacitytoRatedCoolingCapacity());
}
