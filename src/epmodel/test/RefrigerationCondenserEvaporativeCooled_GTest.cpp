/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ParentObject/RefrigerationCondenserEvaporativeCooled.hpp"

#include <utilities/idd/IddEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, RefrigerationCondenserEvaporativeCooled_DefaultConstructor) {
  Model model;
  RefrigerationCondenserEvaporativeCooled condenser(model);
  EXPECT_EQ(RefrigerationCondenserEvaporativeCooled::iddObjectType(), openstudio::IddObjectType::Refrigeration_Condenser_EvaporativeCooled);
}

TEST_F(EPModelFixture, RefrigerationCondenserEvaporativeCooled_ScalarAccessors_RoundTrip) {
  Model model;
  RefrigerationCondenserEvaporativeCooled condenser(model);

  EXPECT_TRUE(condenser.setRatedEffectiveTotalHeatRejectionRate(62000.0));
  EXPECT_DOUBLE_EQ(62000.0, condenser.ratedEffectiveTotalHeatRejectionRate());

  EXPECT_TRUE(condenser.setRatedSubcoolingTemperatureDifference(4.5));
  EXPECT_DOUBLE_EQ(4.5, condenser.ratedSubcoolingTemperatureDifference());
  EXPECT_FALSE(condenser.isRatedSubcoolingTemperatureDifferenceDefaulted());
  condenser.resetRatedSubcoolingTemperatureDifference();
  EXPECT_TRUE(condenser.isRatedSubcoolingTemperatureDifferenceDefaulted());

  const auto fanSpeedTypes = RefrigerationCondenserEvaporativeCooled::fanSpeedControlTypeValues();
  ASSERT_FALSE(fanSpeedTypes.empty());
  EXPECT_TRUE(condenser.setFanSpeedControlType(fanSpeedTypes.front()));
  EXPECT_EQ(fanSpeedTypes.front(), condenser.fanSpeedControlType());
  condenser.resetFanSpeedControlType();
  EXPECT_TRUE(condenser.isFanSpeedControlTypeDefaulted());

  EXPECT_TRUE(condenser.setRatedFanPower(8700.0));
  EXPECT_DOUBLE_EQ(8700.0, condenser.ratedFanPower());

  EXPECT_TRUE(condenser.setMinimumFanAirFlowRatio(0.35));
  EXPECT_DOUBLE_EQ(0.35, condenser.minimumFanAirFlowRatio());
  condenser.resetMinimumFanAirFlowRatio();
  EXPECT_TRUE(condenser.isMinimumFanAirFlowRatioDefaulted());

  EXPECT_TRUE(condenser.setApproachTemperatureConstantTerm(7.1));
  EXPECT_DOUBLE_EQ(7.1, condenser.approachTemperatureConstantTerm());
  condenser.resetApproachTemperatureConstantTerm();
  EXPECT_TRUE(condenser.isApproachTemperatureConstantTermDefaulted());

  EXPECT_TRUE(condenser.setApproachTemperatureCoefficient2(0.75));
  EXPECT_DOUBLE_EQ(0.75, condenser.approachTemperatureCoefficient2());
  condenser.resetApproachTemperatureCoefficient2();
  EXPECT_TRUE(condenser.isApproachTemperatureCoefficient2Defaulted());

  EXPECT_TRUE(condenser.setApproachTemperatureCoefficient3(18.0));
  EXPECT_DOUBLE_EQ(18.0, condenser.approachTemperatureCoefficient3());
  condenser.resetApproachTemperatureCoefficient3();
  EXPECT_TRUE(condenser.isApproachTemperatureCoefficient3Defaulted());

  EXPECT_TRUE(condenser.setApproachTemperatureCoefficient4(-0.18));
  EXPECT_DOUBLE_EQ(-0.18, condenser.approachTemperatureCoefficient4());
  condenser.resetApproachTemperatureCoefficient4();
  EXPECT_TRUE(condenser.isApproachTemperatureCoefficient4Defaulted());

  EXPECT_TRUE(condenser.setMinimumCapacityFactor(0.65));
  EXPECT_DOUBLE_EQ(0.65, condenser.minimumCapacityFactor());
  condenser.resetMinimumCapacityFactor();
  EXPECT_TRUE(condenser.isMinimumCapacityFactorDefaulted());

  EXPECT_TRUE(condenser.setMaximumCapacityFactor(3.5));
  EXPECT_DOUBLE_EQ(3.5, condenser.maximumCapacityFactor());
  condenser.resetMaximumCapacityFactor();
  EXPECT_TRUE(condenser.isMaximumCapacityFactorDefaulted());

  EXPECT_TRUE(condenser.setRatedAirFlowRate(2.65));
  ASSERT_TRUE(condenser.ratedAirFlowRate());
  EXPECT_DOUBLE_EQ(2.65, condenser.ratedAirFlowRate().get());
  EXPECT_FALSE(condenser.isRatedAirFlowRateAutocalculated());
  condenser.autocalculateRatedAirFlowRate();
  EXPECT_TRUE(condenser.isRatedAirFlowRateAutocalculated());
  condenser.resetRatedAirFlowRate();
  EXPECT_FALSE(condenser.ratedAirFlowRate());

  EXPECT_TRUE(condenser.setBasinHeaterCapacity(220.0));
  EXPECT_DOUBLE_EQ(220.0, condenser.basinHeaterCapacity());
  condenser.resetBasinHeaterCapacity();
  EXPECT_TRUE(condenser.isBasinHeaterCapacityDefaulted());

  EXPECT_TRUE(condenser.setBasinHeaterSetpointTemperature(3.5));
  EXPECT_DOUBLE_EQ(3.5, condenser.basinHeaterSetpointTemperature());
  condenser.resetBasinHeaterSetpointTemperature();
  EXPECT_TRUE(condenser.isBasinHeaterSetpointTemperatureDefaulted());

  EXPECT_TRUE(condenser.setRatedWaterPumpPower(1450.0));
  ASSERT_TRUE(condenser.ratedWaterPumpPower());
  EXPECT_DOUBLE_EQ(1450.0, condenser.ratedWaterPumpPower().get());
  EXPECT_FALSE(condenser.isRatedWaterPumpPowerAutocalculated());
  condenser.autocalculateRatedWaterPumpPower();
  EXPECT_TRUE(condenser.isRatedWaterPumpPowerAutocalculated());
  condenser.resetRatedWaterPumpPower();
  EXPECT_TRUE(condenser.isRatedWaterPumpPowerDefaulted());
  EXPECT_FALSE(condenser.isRatedWaterPumpPowerAutocalculated());

  EXPECT_TRUE(condenser.setEndUseSubcategory("RefrigCategory"));
  EXPECT_EQ("RefrigCategory", condenser.endUseSubcategory());
  condenser.resetEndUseSubcategory();
  EXPECT_TRUE(condenser.isEndUseSubcategoryDefaulted());

  EXPECT_TRUE(condenser.setCondenserRefrigerantOperatingChargeInventory(0.95));
  EXPECT_DOUBLE_EQ(0.95, condenser.condenserRefrigerantOperatingChargeInventory());
  condenser.resetCondenserRefrigerantOperatingChargeInventory();
  EXPECT_TRUE(condenser.isCondenserRefrigerantOperatingChargeInventoryDefaulted());

  EXPECT_TRUE(condenser.setCondensateReceiverRefrigerantInventory(1.8));
  EXPECT_DOUBLE_EQ(1.8, condenser.condensateReceiverRefrigerantInventory());
  condenser.resetCondensateReceiverRefrigerantInventory();
  EXPECT_TRUE(condenser.isCondensateReceiverRefrigerantInventoryDefaulted());

  EXPECT_TRUE(condenser.setCondensatePipingRefrigerantInventory(2.45));
  EXPECT_DOUBLE_EQ(2.45, condenser.condensatePipingRefrigerantInventory());
  condenser.resetCondensatePipingRefrigerantInventory();
  EXPECT_TRUE(condenser.isCondensatePipingRefrigerantInventoryDefaulted());
}
