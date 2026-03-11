/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../StraightComponent/CoilCoolingDXTwoSpeed.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilCoolingDXTwoSpeed_DefaultConstructor) {
  Model model;
  CoilCoolingDXTwoSpeed coil(model);
  EXPECT_EQ(CoilCoolingDXTwoSpeed::iddObjectType(), coil.iddObject().type());
  EXPECT_FALSE(coil.nameString().empty());

  EXPECT_TRUE(coil.isRatedHighSpeedTotalCoolingCapacityAutosized());
  EXPECT_TRUE(coil.isRatedHighSpeedSensibleHeatRatioAutosized());
  EXPECT_DOUBLE_EQ(3.0, coil.ratedHighSpeedCOP());
  EXPECT_TRUE(coil.isRatedHighSpeedAirFlowRateAutosized());
  EXPECT_DOUBLE_EQ(773.3, coil.ratedHighSpeedEvaporatorFanPowerPerVolumeFlowRate2017());
  EXPECT_DOUBLE_EQ(934.4, coil.ratedHighSpeedEvaporatorFanPowerPerVolumeFlowRate2023());

  EXPECT_TRUE(coil.isRatedLowSpeedTotalCoolingCapacityAutosized());
  EXPECT_DOUBLE_EQ(0.69, coil.ratedLowSpeedSensibleHeatRatio().get());
  EXPECT_DOUBLE_EQ(3.0, coil.ratedLowSpeedCOP());
  EXPECT_TRUE(coil.isRatedLowSpeedAirFlowRateAutosized());
  EXPECT_DOUBLE_EQ(773.3, coil.ratedLowSpeedEvaporatorFanPowerPerVolumeFlowRate2017());
  EXPECT_DOUBLE_EQ(934.4, coil.ratedLowSpeedEvaporatorFanPowerPerVolumeFlowRate2023());

  EXPECT_EQ("AirCooled", coil.condenserType());
  EXPECT_DOUBLE_EQ(0.9, coil.highSpeedEvaporativeCondenserEffectiveness());
  EXPECT_TRUE(coil.isHighSpeedEvaporativeCondenserAirFlowRateAutosized());
  EXPECT_TRUE(coil.isHighSpeedEvaporativeCondenserPumpRatedPowerConsumptionAutosized());
  EXPECT_DOUBLE_EQ(0.9, coil.lowSpeedEvaporativeCondenserEffectiveness());
  EXPECT_TRUE(coil.isLowSpeedEvaporativeCondenserAirFlowRateAutosized());
  EXPECT_TRUE(coil.isLowSpeedEvaporativeCondenserPumpRatedPowerConsumptionAutosized());

  EXPECT_DOUBLE_EQ(0.0, coil.basinHeaterCapacity());
  EXPECT_DOUBLE_EQ(2.0, coil.basinHeaterSetpointTemperature());
  EXPECT_DOUBLE_EQ(-25.0, coil.minimumOutdoorDryBulbTemperatureforCompressorOperation());
  EXPECT_DOUBLE_EQ(773.3, coil.unitInternalStaticAirPressure());
}

TEST_F(EPModelFixture, CoilCoolingDXTwoSpeed_ScalarAccessors_RoundTrip) {
  Model model;
  CoilCoolingDXTwoSpeed coil(model);

  ASSERT_FALSE(CoilCoolingDXTwoSpeed::condenserTypeValues().empty());

  EXPECT_TRUE(coil.setRatedHighSpeedTotalCoolingCapacity(10000.0));
  ASSERT_TRUE(coil.ratedHighSpeedTotalCoolingCapacity());
  EXPECT_DOUBLE_EQ(10000.0, coil.ratedHighSpeedTotalCoolingCapacity().get());
  EXPECT_FALSE(coil.isRatedHighSpeedTotalCoolingCapacityAutosized());
  coil.autosizeRatedHighSpeedTotalCoolingCapacity();
  EXPECT_TRUE(coil.isRatedHighSpeedTotalCoolingCapacityAutosized());

  EXPECT_TRUE(coil.setRatedHighSpeedSensibleHeatRatio(0.72));
  ASSERT_TRUE(coil.ratedHighSpeedSensibleHeatRatio());
  EXPECT_DOUBLE_EQ(0.72, coil.ratedHighSpeedSensibleHeatRatio().get());
  EXPECT_FALSE(coil.isRatedHighSpeedSensibleHeatRatioAutosized());
  coil.autosizeRatedHighSpeedSensibleHeatRatio();
  EXPECT_TRUE(coil.isRatedHighSpeedSensibleHeatRatioAutosized());

  EXPECT_TRUE(coil.setRatedHighSpeedCOP(3.6));
  EXPECT_DOUBLE_EQ(3.6, coil.ratedHighSpeedCOP());

  EXPECT_TRUE(coil.setRatedHighSpeedAirFlowRate(1.25));
  ASSERT_TRUE(coil.ratedHighSpeedAirFlowRate());
  EXPECT_DOUBLE_EQ(1.25, coil.ratedHighSpeedAirFlowRate().get());
  EXPECT_FALSE(coil.isRatedHighSpeedAirFlowRateAutosized());
  coil.autosizeRatedHighSpeedAirFlowRate();
  EXPECT_TRUE(coil.isRatedHighSpeedAirFlowRateAutosized());

  EXPECT_TRUE(coil.setRatedHighSpeedEvaporatorFanPowerPerVolumeFlowRate2017(700.0));
  EXPECT_DOUBLE_EQ(700.0, coil.ratedHighSpeedEvaporatorFanPowerPerVolumeFlowRate2017());
  EXPECT_TRUE(coil.setRatedHighSpeedEvaporatorFanPowerPerVolumeFlowRate2023(900.0));
  EXPECT_DOUBLE_EQ(900.0, coil.ratedHighSpeedEvaporatorFanPowerPerVolumeFlowRate2023());

  EXPECT_TRUE(coil.setRatedLowSpeedTotalCoolingCapacity(4200.0));
  ASSERT_TRUE(coil.ratedLowSpeedTotalCoolingCapacity());
  EXPECT_DOUBLE_EQ(4200.0, coil.ratedLowSpeedTotalCoolingCapacity().get());
  EXPECT_FALSE(coil.isRatedLowSpeedTotalCoolingCapacityAutosized());
  coil.autosizeRatedLowSpeedTotalCoolingCapacity();
  EXPECT_TRUE(coil.isRatedLowSpeedTotalCoolingCapacityAutosized());

  EXPECT_TRUE(coil.setRatedLowSpeedSensibleHeatRatio(0.66));
  ASSERT_TRUE(coil.ratedLowSpeedSensibleHeatRatio());
  EXPECT_DOUBLE_EQ(0.66, coil.ratedLowSpeedSensibleHeatRatio().get());
  EXPECT_FALSE(coil.isRatedLowSpeedSensibleHeatRatioAutosized());
  coil.autosizeRatedLowSpeedSensibleHeatRatio();
  EXPECT_TRUE(coil.isRatedLowSpeedSensibleHeatRatioAutosized());

  EXPECT_TRUE(coil.setRatedLowSpeedCOP(2.9));
  EXPECT_DOUBLE_EQ(2.9, coil.ratedLowSpeedCOP());

  EXPECT_TRUE(coil.setRatedLowSpeedAirFlowRate(0.85));
  ASSERT_TRUE(coil.ratedLowSpeedAirFlowRate());
  EXPECT_DOUBLE_EQ(0.85, coil.ratedLowSpeedAirFlowRate().get());
  EXPECT_FALSE(coil.isRatedLowSpeedAirFlowRateAutosized());
  coil.autosizeRatedLowSpeedAirFlowRate();
  EXPECT_TRUE(coil.isRatedLowSpeedAirFlowRateAutosized());

  EXPECT_TRUE(coil.setRatedLowSpeedEvaporatorFanPowerPerVolumeFlowRate2017(650.0));
  EXPECT_DOUBLE_EQ(650.0, coil.ratedLowSpeedEvaporatorFanPowerPerVolumeFlowRate2017());
  EXPECT_TRUE(coil.setRatedLowSpeedEvaporatorFanPowerPerVolumeFlowRate2023(850.0));
  EXPECT_DOUBLE_EQ(850.0, coil.ratedLowSpeedEvaporatorFanPowerPerVolumeFlowRate2023());

  EXPECT_TRUE(coil.setCondenserType("EvaporativelyCooled"));
  EXPECT_EQ("EvaporativelyCooled", coil.condenserType());

  EXPECT_TRUE(coil.setHighSpeedEvaporativeCondenserEffectiveness(0.82));
  EXPECT_DOUBLE_EQ(0.82, coil.highSpeedEvaporativeCondenserEffectiveness());
  EXPECT_TRUE(coil.setHighSpeedEvaporativeCondenserAirFlowRate(0.40));
  ASSERT_TRUE(coil.highSpeedEvaporativeCondenserAirFlowRate());
  EXPECT_DOUBLE_EQ(0.40, coil.highSpeedEvaporativeCondenserAirFlowRate().get());
  EXPECT_FALSE(coil.isHighSpeedEvaporativeCondenserAirFlowRateAutosized());
  coil.autosizeHighSpeedEvaporativeCondenserAirFlowRate();
  EXPECT_TRUE(coil.isHighSpeedEvaporativeCondenserAirFlowRateAutosized());
  EXPECT_TRUE(coil.setHighSpeedEvaporativeCondenserPumpRatedPowerConsumption(125.0));
  ASSERT_TRUE(coil.highSpeedEvaporativeCondenserPumpRatedPowerConsumption());
  EXPECT_DOUBLE_EQ(125.0, coil.highSpeedEvaporativeCondenserPumpRatedPowerConsumption().get());
  EXPECT_FALSE(coil.isHighSpeedEvaporativeCondenserPumpRatedPowerConsumptionAutosized());
  coil.autosizeHighSpeedEvaporativeCondenserPumpRatedPowerConsumption();
  EXPECT_TRUE(coil.isHighSpeedEvaporativeCondenserPumpRatedPowerConsumptionAutosized());

  EXPECT_TRUE(coil.setLowSpeedEvaporativeCondenserEffectiveness(0.79));
  EXPECT_DOUBLE_EQ(0.79, coil.lowSpeedEvaporativeCondenserEffectiveness());
  EXPECT_TRUE(coil.setLowSpeedEvaporativeCondenserAirFlowRate(0.30));
  ASSERT_TRUE(coil.lowSpeedEvaporativeCondenserAirFlowRate());
  EXPECT_DOUBLE_EQ(0.30, coil.lowSpeedEvaporativeCondenserAirFlowRate().get());
  EXPECT_FALSE(coil.isLowSpeedEvaporativeCondenserAirFlowRateAutosized());
  coil.autosizeLowSpeedEvaporativeCondenserAirFlowRate();
  EXPECT_TRUE(coil.isLowSpeedEvaporativeCondenserAirFlowRateAutosized());
  EXPECT_TRUE(coil.setLowSpeedEvaporativeCondenserPumpRatedPowerConsumption(95.0));
  ASSERT_TRUE(coil.lowSpeedEvaporativeCondenserPumpRatedPowerConsumption());
  EXPECT_DOUBLE_EQ(95.0, coil.lowSpeedEvaporativeCondenserPumpRatedPowerConsumption().get());
  EXPECT_FALSE(coil.isLowSpeedEvaporativeCondenserPumpRatedPowerConsumptionAutosized());
  coil.autosizeLowSpeedEvaporativeCondenserPumpRatedPowerConsumption();
  EXPECT_TRUE(coil.isLowSpeedEvaporativeCondenserPumpRatedPowerConsumptionAutosized());

  EXPECT_TRUE(coil.setBasinHeaterCapacity(25.0));
  EXPECT_DOUBLE_EQ(25.0, coil.basinHeaterCapacity());
  EXPECT_TRUE(coil.setBasinHeaterSetpointTemperature(3.5));
  EXPECT_DOUBLE_EQ(3.5, coil.basinHeaterSetpointTemperature());

  EXPECT_TRUE(coil.setMinimumOutdoorDryBulbTemperatureforCompressorOperation(-10.0));
  EXPECT_DOUBLE_EQ(-10.0, coil.minimumOutdoorDryBulbTemperatureforCompressorOperation());

  EXPECT_TRUE(coil.setUnitInternalStaticAirPressure(710.0));
  EXPECT_DOUBLE_EQ(710.0, coil.unitInternalStaticAirPressure());
}
