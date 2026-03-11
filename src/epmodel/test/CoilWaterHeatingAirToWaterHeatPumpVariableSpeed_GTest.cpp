/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include <algorithm>

#include "EPModelFixture.hpp"
#include "../HVACComponent/CoilWaterHeatingAirToWaterHeatPumpVariableSpeed.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_DefaultConstructor) {
  Model model;
  CoilWaterHeatingAirToWaterHeatPumpVariableSpeed coil(model);
  EXPECT_EQ(CoilWaterHeatingAirToWaterHeatPumpVariableSpeed::iddObjectType(), coil.iddObject().type());
  EXPECT_FALSE(coil.nameString().empty());
}

TEST_F(EPModelFixture, CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_ScalarAccessors_RoundTrip) {
  Model model;
  CoilWaterHeatingAirToWaterHeatPumpVariableSpeed coil(model);

  EXPECT_TRUE(coil.setNominalSpeedLevel(2));
  EXPECT_EQ(2, coil.nominalSpeedLevel());

  EXPECT_TRUE(coil.setRatedWaterHeatingCapacity(4200.0));
  EXPECT_DOUBLE_EQ(4200.0, coil.ratedWaterHeatingCapacity());

  EXPECT_TRUE(coil.setRatedEvaporatorInletAirDryBulbTemperature(29.44));
  EXPECT_DOUBLE_EQ(29.44, coil.ratedEvaporatorInletAirDryBulbTemperature());

  EXPECT_TRUE(coil.setRatedEvaporatorInletAirWetBulbTemperature(22.22));
  EXPECT_DOUBLE_EQ(22.22, coil.ratedEvaporatorInletAirWetBulbTemperature());

  EXPECT_TRUE(coil.setRatedCondenserInletWaterTemperature(55.72));
  EXPECT_DOUBLE_EQ(55.72, coil.ratedCondenserInletWaterTemperature());

  EXPECT_TRUE(coil.setRatedEvaporatorAirFlowRate(0.52));
  ASSERT_TRUE(coil.ratedEvaporatorAirFlowRate());
  EXPECT_DOUBLE_EQ(0.52, coil.ratedEvaporatorAirFlowRate().get());
  coil.autocalculateRatedEvaporatorAirFlowRate();
  EXPECT_TRUE(coil.isRatedEvaporatorAirFlowRateAutocalculated());

  EXPECT_TRUE(coil.setRatedCondenserWaterFlowRate(0.12));
  ASSERT_TRUE(coil.ratedCondenserWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.12, coil.ratedCondenserWaterFlowRate().get());
  coil.autocalculateRatedCondenserWaterFlowRate();
  EXPECT_TRUE(coil.isRatedCondenserWaterFlowRateAutocalculated());

  EXPECT_TRUE(coil.setEvaporatorFanPowerIncludedinRatedCOP("Yes"));
  EXPECT_EQ("Yes", coil.evaporatorFanPowerIncludedinRatedCOP());

  EXPECT_TRUE(coil.setCondenserPumpPowerIncludedinRatedCOP("No"));
  EXPECT_EQ("No", coil.condenserPumpPowerIncludedinRatedCOP());

  EXPECT_TRUE(coil.setCondenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP("No"));
  EXPECT_EQ("No", coil.condenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP());

  EXPECT_TRUE(coil.setFractionofCondenserPumpHeattoWater(0.2));
  EXPECT_DOUBLE_EQ(0.2, coil.fractionofCondenserPumpHeattoWater());

  EXPECT_TRUE(coil.setCrankcaseHeaterCapacity(100.0));
  EXPECT_DOUBLE_EQ(100.0, coil.crankcaseHeaterCapacity());

  EXPECT_TRUE(coil.setMaximumAmbientTemperatureforCrankcaseHeaterOperation(10.0));
  EXPECT_DOUBLE_EQ(10.0, coil.maximumAmbientTemperatureforCrankcaseHeaterOperation());

  const auto temperatureTypeChoices = CoilWaterHeatingAirToWaterHeatPumpVariableSpeed::evaporatorAirTemperatureTypeforCurveObjectsValues();
  EXPECT_FALSE(temperatureTypeChoices.empty());
  EXPECT_TRUE(std::find(temperatureTypeChoices.begin(), temperatureTypeChoices.end(), "WetBulbTemperature") !=
              temperatureTypeChoices.end());

  EXPECT_TRUE(coil.setEvaporatorAirTemperatureTypeforCurveObjects("WetBulbTemperature"));
  EXPECT_EQ("WetBulbTemperature", coil.evaporatorAirTemperatureTypeforCurveObjects());
}
