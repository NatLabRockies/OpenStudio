/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ZoneHVACComponent/ZoneHVACEnergyRecoveryVentilator.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneHVACEnergyRecoveryVentilator_DefaultConstructor) {
  Model model;
  ZoneHVACEnergyRecoveryVentilator ventilator(model);

  EXPECT_EQ(ZoneHVACEnergyRecoveryVentilator::iddObjectType(), ventilator.iddObject().type());
  EXPECT_FALSE(ventilator.supplyAirFlowRate());
  EXPECT_TRUE(ventilator.isSupplyAirFlowRateAutosized());
  EXPECT_FALSE(ventilator.exhaustAirFlowRate());
  EXPECT_TRUE(ventilator.isExhaustAirFlowRateAutosized());
  EXPECT_DOUBLE_EQ(0.000508, ventilator.ventilationRateperUnitFloorArea());
  EXPECT_DOUBLE_EQ(0.00236, ventilator.ventilationRateperOccupant());
}

TEST_F(EPModelFixture, ZoneHVACEnergyRecoveryVentilator_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneHVACEnergyRecoveryVentilator ventilator(model);

  EXPECT_TRUE(ventilator.setSupplyAirFlowRate(0.45));
  EXPECT_TRUE(ventilator.setExhaustAirFlowRate(0.35));
  EXPECT_TRUE(ventilator.setVentilationRateperUnitFloorArea(0.001));
  EXPECT_TRUE(ventilator.setVentilationRateperOccupant(0.003));

  ASSERT_TRUE(ventilator.supplyAirFlowRate());
  ASSERT_TRUE(ventilator.exhaustAirFlowRate());
  EXPECT_DOUBLE_EQ(0.45, ventilator.supplyAirFlowRate().get());
  EXPECT_DOUBLE_EQ(0.35, ventilator.exhaustAirFlowRate().get());
  EXPECT_DOUBLE_EQ(0.001, ventilator.ventilationRateperUnitFloorArea());
  EXPECT_DOUBLE_EQ(0.003, ventilator.ventilationRateperOccupant());
  EXPECT_FALSE(ventilator.isSupplyAirFlowRateAutosized());
  EXPECT_FALSE(ventilator.isExhaustAirFlowRateAutosized());

  ventilator.autosizeSupplyAirFlowRate();
  ventilator.autosizeExhaustAirFlowRate();

  EXPECT_TRUE(ventilator.isSupplyAirFlowRateAutosized());
  EXPECT_TRUE(ventilator.isExhaustAirFlowRateAutosized());
  EXPECT_FALSE(ventilator.supplyAirFlowRate());
  EXPECT_FALSE(ventilator.exhaustAirFlowRate());
}
