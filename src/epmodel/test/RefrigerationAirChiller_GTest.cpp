/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ZoneHVACComponent/RefrigerationAirChiller.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, RefrigerationAirChiller_DefaultConstructor) {
  Model model;
  RefrigerationAirChiller chiller(model);

  EXPECT_EQ(RefrigerationAirChiller::iddObjectType(), chiller.iddObject().type());
  EXPECT_EQ("UnitLoadFactorSensibleOnly", chiller.capacityRatingType());
  EXPECT_EQ("LinearSHR60", chiller.capacityCorrectionCurveType());
  EXPECT_DOUBLE_EQ(0.0, chiller.ratedCoolingSourceTemperature());
  EXPECT_DOUBLE_EQ(10.0, chiller.ratedTemperatureDifferenceDT1());
  EXPECT_DOUBLE_EQ(1000.0, chiller.ratedTotalHeatingPower());
  EXPECT_DOUBLE_EQ(1.0, chiller.ratedAirFlow());
  EXPECT_EQ("Fixed", chiller.fanSpeedControlType());
  EXPECT_EQ("Electric", chiller.defrostType());
  EXPECT_EQ("TimeSchedule", chiller.defrostControlType());
  EXPECT_EQ("Middle", chiller.verticalLocation());
  EXPECT_TRUE(chiller.isRatedRelativeHumidityDefaulted());
}

TEST_F(EPModelFixture, RefrigerationAirChiller_ScalarAccessors_RoundTrip) {
  Model model;
  RefrigerationAirChiller chiller(model);

  EXPECT_TRUE(chiller.setCapacityRatingType("CapacityTotalSpecificConditions"));
  EXPECT_TRUE(chiller.setRatedUnitLoadFactor(1500.0));
  EXPECT_TRUE(chiller.setRatedCapacity(4250.0));
  EXPECT_TRUE(chiller.setRatedRelativeHumidity(72.0));
  EXPECT_TRUE(chiller.setMaximumTemperatureDifferenceBetweenInletAirandEvaporatingTemperature(16.0));
  EXPECT_TRUE(chiller.setCoilMaterialCorrectionFactor(1.25));
  EXPECT_TRUE(chiller.setRefrigerantCorrectionFactor(0.92));
  EXPECT_TRUE(chiller.setCapacityCorrectionCurveType("QuadraticSHR"));
  EXPECT_TRUE(chiller.setSHR60CorrectionFactor(1.55));
  EXPECT_TRUE(chiller.setFanSpeedControlType("VariableSpeed"));
  EXPECT_TRUE(chiller.setRatedFanPower(425.0));
  EXPECT_TRUE(chiller.setMinimumFanAirFlowRatio(0.4));
  EXPECT_TRUE(chiller.setDefrostType("HotFluid"));
  EXPECT_TRUE(chiller.setDefrostControlType("TemperatureTermination"));
  EXPECT_TRUE(chiller.setDefrostPower(250.0));
  EXPECT_TRUE(chiller.setTemperatureTerminationDefrostFractiontoIce(0.85));
  EXPECT_TRUE(chiller.setVerticalLocation("Ceiling"));
  EXPECT_TRUE(chiller.setAverageRefrigerantChargeInventory(12.5));

  EXPECT_EQ("CapacityTotalSpecificConditions", chiller.capacityRatingType());
  ASSERT_TRUE(chiller.ratedUnitLoadFactor());
  EXPECT_DOUBLE_EQ(1500.0, chiller.ratedUnitLoadFactor().value());
  ASSERT_TRUE(chiller.ratedCapacity());
  EXPECT_DOUBLE_EQ(4250.0, chiller.ratedCapacity().value());
  EXPECT_DOUBLE_EQ(72.0, chiller.ratedRelativeHumidity());
  EXPECT_DOUBLE_EQ(16.0, chiller.maximumTemperatureDifferenceBetweenInletAirandEvaporatingTemperature().value());
  EXPECT_DOUBLE_EQ(1.25, chiller.coilMaterialCorrectionFactor());
  EXPECT_DOUBLE_EQ(0.92, chiller.refrigerantCorrectionFactor());
  EXPECT_EQ("QuadraticSHR", chiller.capacityCorrectionCurveType());
  EXPECT_DOUBLE_EQ(1.55, chiller.sHR60CorrectionFactor());
  EXPECT_EQ("VariableSpeed", chiller.fanSpeedControlType());
  EXPECT_FALSE(chiller.isFanSpeedControlTypeDefaulted());
  EXPECT_DOUBLE_EQ(425.0, chiller.ratedFanPower());
  EXPECT_FALSE(chiller.isRatedFanPowerDefaulted());
  EXPECT_DOUBLE_EQ(0.4, chiller.minimumFanAirFlowRatio());
  EXPECT_EQ("HotFluid", chiller.defrostType());
  EXPECT_FALSE(chiller.isDefrostTypeDefaulted());
  EXPECT_EQ("TemperatureTermination", chiller.defrostControlType());
  EXPECT_FALSE(chiller.isDefrostControlTypeDefaulted());
  ASSERT_TRUE(chiller.defrostPower());
  EXPECT_DOUBLE_EQ(250.0, chiller.defrostPower().value());
  ASSERT_TRUE(chiller.temperatureTerminationDefrostFractiontoIce());
  EXPECT_DOUBLE_EQ(0.85, chiller.temperatureTerminationDefrostFractiontoIce().value());
  EXPECT_EQ("Ceiling", chiller.verticalLocation());
  EXPECT_DOUBLE_EQ(12.5, chiller.averageRefrigerantChargeInventory());

  chiller.resetRatedUnitLoadFactor();
  EXPECT_FALSE(chiller.ratedUnitLoadFactor());
  chiller.resetRatedCapacity();
  EXPECT_FALSE(chiller.ratedCapacity());
  chiller.resetRatedRelativeHumidity();
  EXPECT_TRUE(chiller.isRatedRelativeHumidityDefaulted());
  chiller.resetCapacityCorrectionCurveType();
  EXPECT_TRUE(chiller.isCapacityCorrectionCurveTypeDefaulted());
  chiller.resetFanSpeedControlType();
  EXPECT_TRUE(chiller.isFanSpeedControlTypeDefaulted());
  chiller.resetRatedFanPower();
  EXPECT_TRUE(chiller.isRatedFanPowerDefaulted());
  chiller.resetMinimumFanAirFlowRatio();
  EXPECT_TRUE(chiller.isMinimumFanAirFlowRatioDefaulted());
  chiller.resetDefrostType();
  EXPECT_TRUE(chiller.isDefrostTypeDefaulted());
  chiller.resetDefrostControlType();
  EXPECT_TRUE(chiller.isDefrostControlTypeDefaulted());
  chiller.resetDefrostPower();
  EXPECT_FALSE(chiller.defrostPower());
  chiller.resetTemperatureTerminationDefrostFractiontoIce();
  EXPECT_FALSE(chiller.temperatureTerminationDefrostFractiontoIce());
  chiller.resetVerticalLocation();
  EXPECT_TRUE(chiller.isVerticalLocationDefaulted());
  chiller.resetAverageRefrigerantChargeInventory();
  EXPECT_TRUE(chiller.isAverageRefrigerantChargeInventoryDefaulted());
}
