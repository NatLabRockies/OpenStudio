/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include <algorithm>

#include "EPModelFixture.hpp"
#include "../HVACComponent/CoilWaterHeatingAirToWaterHeatPump.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilWaterHeatingAirToWaterHeatPump_DefaultConstructor) {
  Model model;
  CoilWaterHeatingAirToWaterHeatPump coil(model);
  EXPECT_EQ(CoilWaterHeatingAirToWaterHeatPump::iddObjectType(), coil.iddObject().type());
  EXPECT_FALSE(coil.nameString().empty());
}

TEST_F(EPModelFixture, CoilWaterHeatingAirToWaterHeatPump_ScalarAccessors_RoundTrip) {
  Model model;
  CoilWaterHeatingAirToWaterHeatPump coil(model);

  EXPECT_TRUE(coil.setRatedHeatingCapacity(4200.0));
  EXPECT_DOUBLE_EQ(4200.0, coil.ratedHeatingCapacity());

  EXPECT_TRUE(coil.setRatedCOP(3.4));
  EXPECT_DOUBLE_EQ(3.4, coil.ratedCOP());

  EXPECT_TRUE(coil.setRatedSensibleHeatRatio(0.88));
  EXPECT_DOUBLE_EQ(0.88, coil.ratedSensibleHeatRatio());

  EXPECT_TRUE(coil.setRatedEvaporatorInletAirDryBulbTemperature(29.44));
  EXPECT_DOUBLE_EQ(29.44, coil.ratedEvaporatorInletAirDryBulbTemperature());

  EXPECT_TRUE(coil.setRatedEvaporatorInletAirWetBulbTemperature(22.22));
  EXPECT_DOUBLE_EQ(22.22, coil.ratedEvaporatorInletAirWetBulbTemperature());

  EXPECT_TRUE(coil.setRatedCondenserInletWaterTemperature(55.72));
  EXPECT_DOUBLE_EQ(55.72, coil.ratedCondenserInletWaterTemperature());

  EXPECT_TRUE(coil.setRatedEvaporatorAirFlowRate(0.52));
  ASSERT_TRUE(coil.ratedEvaporatorAirFlowRate());
  EXPECT_DOUBLE_EQ(0.52, coil.ratedEvaporatorAirFlowRate().get());
  coil.autosizeRatedEvaporatorAirFlowRate();
  EXPECT_TRUE(coil.isRatedEvaporatorAirFlowRateAutosized());

  EXPECT_TRUE(coil.setRatedCondenserWaterFlowRate(0.12));
  ASSERT_TRUE(coil.ratedCondenserWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.12, coil.ratedCondenserWaterFlowRate().get());
  coil.autosizeRatedCondenserWaterFlowRate();
  EXPECT_TRUE(coil.isRatedCondenserWaterFlowRateAutosized());

  EXPECT_TRUE(coil.setEvaporatorFanPowerIncludedinRatedCOP(true));
  EXPECT_TRUE(coil.evaporatorFanPowerIncludedinRatedCOP());

  EXPECT_TRUE(coil.setCondenserPumpPowerIncludedinRatedCOP(false));
  EXPECT_FALSE(coil.condenserPumpPowerIncludedinRatedCOP());

  EXPECT_TRUE(coil.setCondenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP(false));
  EXPECT_FALSE(coil.condenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP());

  EXPECT_TRUE(coil.setCondenserWaterPumpPower(300.0));
  EXPECT_DOUBLE_EQ(300.0, coil.condenserWaterPumpPower());

  EXPECT_TRUE(coil.setFractionofCondenserPumpHeattoWater(0.2));
  EXPECT_DOUBLE_EQ(0.2, coil.fractionofCondenserPumpHeattoWater());

  EXPECT_TRUE(coil.setCrankcaseHeaterCapacity(100.0));
  EXPECT_DOUBLE_EQ(100.0, coil.crankcaseHeaterCapacity());

  EXPECT_TRUE(coil.setMaximumAmbientTemperatureforCrankcaseHeaterOperation(10.0));
  EXPECT_DOUBLE_EQ(10.0, coil.maximumAmbientTemperatureforCrankcaseHeaterOperation());

  const auto temperatureTypeChoices = CoilWaterHeatingAirToWaterHeatPump::evaporatorAirTemperatureTypeforCurveObjectsValues();
  EXPECT_FALSE(temperatureTypeChoices.empty());
  EXPECT_TRUE(std::find(temperatureTypeChoices.begin(), temperatureTypeChoices.end(), "WetBulbTemperature") != temperatureTypeChoices.end());

  EXPECT_TRUE(coil.setEvaporatorAirTemperatureTypeforCurveObjects("WetBulbTemperature"));
  EXPECT_EQ("WetBulbTemperature", coil.evaporatorAirTemperatureTypeforCurveObjects());
}
