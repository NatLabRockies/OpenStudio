/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ParentObject/RefrigerationSecondarySystem.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, RefrigerationSecondarySystem_DefaultConstructor) {
  Model model;
  RefrigerationSecondarySystem secondarySystem(model);
  EXPECT_EQ(RefrigerationSecondarySystem::iddObjectType(), openstudio::IddObjectType::Refrigeration_SecondarySystem);
}

TEST_F(EPModelFixture, RefrigerationSecondarySystem_ScalarAccessors_RoundTrip) {
  Model model;
  RefrigerationSecondarySystem secondarySystem(model);

  EXPECT_TRUE(secondarySystem.setEvaporatorEvaporatingTemperature(-12.5));
  EXPECT_DOUBLE_EQ(-12.5, secondarySystem.evaporatorEvaporatingTemperature());

  EXPECT_TRUE(secondarySystem.setEvaporatorApproachTemperatureDifference(3.1));
  EXPECT_DOUBLE_EQ(3.1, secondarySystem.evaporatorApproachTemperatureDifference());

  EXPECT_TRUE(secondarySystem.setEvaporatorRangeTemperatureDifference(5.0));
  EXPECT_DOUBLE_EQ(5.0, secondarySystem.evaporatorRangeTemperatureDifference().get());
  secondarySystem.resetEvaporatorRangeTemperatureDifference();
  EXPECT_FALSE(secondarySystem.evaporatorRangeTemperatureDifference());

  EXPECT_TRUE(secondarySystem.setNumberofPumpsinLoop(3));
  EXPECT_EQ(3, secondarySystem.numberofPumpsinLoop());
  secondarySystem.resetNumberofPumpsinLoop();
  EXPECT_TRUE(secondarySystem.isNumberofPumpsinLoopDefaulted());

  EXPECT_TRUE(secondarySystem.setTotalPumpFlowRate(0.003));
  EXPECT_DOUBLE_EQ(0.003, secondarySystem.totalPumpFlowRate().get());
  secondarySystem.resetTotalPumpFlowRate();
  EXPECT_FALSE(secondarySystem.totalPumpFlowRate());

  EXPECT_TRUE(secondarySystem.setTotalPumpPower(450.0));
  EXPECT_DOUBLE_EQ(450.0, secondarySystem.totalPumpPower().get());
  secondarySystem.resetTotalPumpPower();
  EXPECT_FALSE(secondarySystem.totalPumpPower());

  EXPECT_TRUE(secondarySystem.setTotalPumpHead(2.1e5));
  EXPECT_DOUBLE_EQ(2.1e5, secondarySystem.totalPumpHead().get());
  secondarySystem.resetTotalPumpHead();
  EXPECT_FALSE(secondarySystem.totalPumpHead());

  EXPECT_TRUE(secondarySystem.setPhaseChangeCirculatingRate(3.3));
  EXPECT_DOUBLE_EQ(3.3, secondarySystem.phaseChangeCirculatingRate());
  secondarySystem.resetPhaseChangeCirculatingRate();
  EXPECT_TRUE(secondarySystem.isPhaseChangeCirculatingRateDefaulted());

  EXPECT_TRUE(secondarySystem.setPumpMotorHeattoFluid(0.92));
  EXPECT_DOUBLE_EQ(0.92, secondarySystem.pumpMotorHeattoFluid());
  secondarySystem.resetPumpMotorHeattoFluid();
  EXPECT_TRUE(secondarySystem.isPumpMotorHeattoFluidDefaulted());

  EXPECT_TRUE(secondarySystem.setSumUADistributionPiping(1.2));
  EXPECT_DOUBLE_EQ(1.2, secondarySystem.sumUADistributionPiping());
  secondarySystem.resetSumUADistributionPiping();
  EXPECT_TRUE(secondarySystem.isSumUADistributionPipingDefaulted());

  EXPECT_TRUE(secondarySystem.setSumUAReceiverSeparatorShell(2.4));
  EXPECT_DOUBLE_EQ(2.4, secondarySystem.sumUAReceiverSeparatorShell());
  secondarySystem.resetSumUAReceiverSeparatorShell();
  EXPECT_TRUE(secondarySystem.isSumUAReceiverSeparatorShellDefaulted());

  EXPECT_TRUE(secondarySystem.setEvaporatorRefrigerantInventory(15.0));
  EXPECT_DOUBLE_EQ(15.0, secondarySystem.evaporatorRefrigerantInventory());
  secondarySystem.resetEvaporatorRefrigerantInventory();
  EXPECT_TRUE(secondarySystem.isEvaporatorRefrigerantInventoryDefaulted());

  EXPECT_TRUE(secondarySystem.setEndUseSubcategory("Custom"));
  EXPECT_EQ("Custom", secondarySystem.endUseSubcategory());
  secondarySystem.resetEndUseSubcategory();
  EXPECT_TRUE(secondarySystem.isEndUseSubcategoryDefaulted());

  const auto pumpDriveTypes = RefrigerationSecondarySystem::pumpDriveTypeValues();
  ASSERT_FALSE(pumpDriveTypes.empty());
  EXPECT_TRUE(secondarySystem.setPumpDriveType(pumpDriveTypes.back()));
  EXPECT_EQ(pumpDriveTypes.back(), secondarySystem.pumpDriveType());
  secondarySystem.resetPumpDriveType();
  EXPECT_TRUE(secondarySystem.isPumpDriveTypeDefaulted());
}
