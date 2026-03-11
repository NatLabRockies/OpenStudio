/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ParentObject/RefrigerationCondenserAirCooled.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, RefrigerationCondenserAirCooled_DefaultConstructor) {
  Model model;
  RefrigerationCondenserAirCooled condenser(model);
  EXPECT_EQ(RefrigerationCondenserAirCooled::iddObjectType(), openstudio::IddObjectType::Refrigeration_Condenser_AirCooled);
}

TEST_F(EPModelFixture, RefrigerationCondenserAirCooled_ScalarAccessors_RoundTrip) {
  Model model;
  RefrigerationCondenserAirCooled condenser(model);

  EXPECT_TRUE(condenser.setRatedSubcoolingTemperatureDifference(4.5));
  EXPECT_DOUBLE_EQ(4.5, condenser.ratedSubcoolingTemperatureDifference());
  EXPECT_FALSE(condenser.isRatedSubcoolingTemperatureDifferenceDefaulted());
  condenser.resetRatedSubcoolingTemperatureDifference();
  EXPECT_TRUE(condenser.isRatedSubcoolingTemperatureDifferenceDefaulted());

  const auto fanSpeedTypes = RefrigerationCondenserAirCooled::condenserFanSpeedControlTypeValues();
  ASSERT_FALSE(fanSpeedTypes.empty());
  EXPECT_TRUE(condenser.setCondenserFanSpeedControlType(fanSpeedTypes.back()));
  EXPECT_EQ(fanSpeedTypes.back(), condenser.condenserFanSpeedControlType());
  condenser.resetCondenserFanSpeedControlType();
  EXPECT_TRUE(condenser.isCondenserFanSpeedControlTypeDefaulted());

  EXPECT_TRUE(condenser.setRatedFanPower(350.0));
  EXPECT_DOUBLE_EQ(350.0, condenser.ratedFanPower());

  EXPECT_TRUE(condenser.setMinimumFanAirFlowRatio(0.33));
  EXPECT_DOUBLE_EQ(0.33, condenser.minimumFanAirFlowRatio());

  EXPECT_TRUE(condenser.setEndUseSubcategory("CustomCategory"));
  EXPECT_EQ("CustomCategory", condenser.endUseSubcategory());
  condenser.resetEndUseSubcategory();
  EXPECT_TRUE(condenser.isEndUseSubcategoryDefaulted());

  EXPECT_TRUE(condenser.setCondenserRefrigerantOperatingChargeInventory(1.25));
  EXPECT_DOUBLE_EQ(1.25, condenser.condenserRefrigerantOperatingChargeInventory());

  EXPECT_TRUE(condenser.setCondensateReceiverRefrigerantInventory(2.5));
  EXPECT_DOUBLE_EQ(2.5, condenser.condensateReceiverRefrigerantInventory());

  EXPECT_TRUE(condenser.setCondensatePipingRefrigerantInventory(3.75));
  EXPECT_DOUBLE_EQ(3.75, condenser.condensatePipingRefrigerantInventory());
}
