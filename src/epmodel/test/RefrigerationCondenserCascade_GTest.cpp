/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/RefrigerationCondenserCascade.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, RefrigerationCondenserCascade_DefaultConstructor) {
  Model model;
  RefrigerationCondenserCascade cascade(model);
  EXPECT_EQ(RefrigerationCondenserCascade::iddObjectType(), openstudio::IddObjectType("Refrigeration_Condenser_Cascade"));
}

TEST_F(EPModelFixture, RefrigerationCondenserCascade_ScalarAccessors_RoundTrip) {
  Model model;
  RefrigerationCondenserCascade cascade(model);

  EXPECT_TRUE(cascade.setRatedCondensingTemperature(-5.5));
  EXPECT_DOUBLE_EQ(-5.5, cascade.ratedCondensingTemperature());

  EXPECT_TRUE(cascade.setRatedApproachTemperatureDifference(4.7));
  EXPECT_DOUBLE_EQ(4.7, cascade.ratedApproachTemperatureDifference());
  EXPECT_FALSE(cascade.isRatedApproachTemperatureDifferenceDefaulted());
  cascade.resetRatedApproachTemperatureDifference();
  EXPECT_TRUE(cascade.isRatedApproachTemperatureDifferenceDefaulted());

  EXPECT_TRUE(cascade.setRatedEffectiveTotalHeatRejectionRate(21000.0));
  EXPECT_DOUBLE_EQ(21000.0, cascade.ratedEffectiveTotalHeatRejectionRate());

  const auto controlTypes = RefrigerationCondenserCascade::condensingTemperatureControlTypeValues();
  ASSERT_FALSE(controlTypes.empty());
  EXPECT_TRUE(cascade.setCondensingTemperatureControlType(controlTypes[0]));
  EXPECT_EQ(controlTypes[0], cascade.condensingTemperatureControlType());
  cascade.resetCondensingTemperatureControlType();
  EXPECT_TRUE(cascade.isCondensingTemperatureControlTypeDefaulted());

  EXPECT_TRUE(cascade.setCondenserRefrigerantOperatingChargeInventory(1.25));
  ASSERT_TRUE(cascade.condenserRefrigerantOperatingChargeInventory());
  EXPECT_DOUBLE_EQ(1.25, cascade.condenserRefrigerantOperatingChargeInventory().get());

  EXPECT_TRUE(cascade.setCondensateReceiverRefrigerantInventory(2.5));
  ASSERT_TRUE(cascade.condensateReceiverRefrigerantInventory());
  EXPECT_DOUBLE_EQ(2.5, cascade.condensateReceiverRefrigerantInventory().get());

  EXPECT_TRUE(cascade.setCondensatePipingRefrigerantInventory(3.75));
  ASSERT_TRUE(cascade.condensatePipingRefrigerantInventory());
  EXPECT_DOUBLE_EQ(3.75, cascade.condensatePipingRefrigerantInventory().get());
}
