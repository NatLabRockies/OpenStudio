/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/CoilHeatingDXVariableRefrigerantFlow.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilHeatingDXVariableRefrigerantFlow_DefaultConstructor) {
  Model model;
  CoilHeatingDXVariableRefrigerantFlow coil(model);
  EXPECT_EQ(CoilHeatingDXVariableRefrigerantFlow::iddObjectType(), coil.iddObject().type());
  EXPECT_FALSE(coil.nameString().empty());
}

TEST_F(EPModelFixture, CoilHeatingDXVariableRefrigerantFlow_ScalarAccessors_RoundTrip) {
  Model model;
  CoilHeatingDXVariableRefrigerantFlow coil(model);

  EXPECT_TRUE(coil.setRatedTotalHeatingCapacity(12345.0));
  ASSERT_TRUE(coil.ratedTotalHeatingCapacity());
  EXPECT_DOUBLE_EQ(12345.0, coil.ratedTotalHeatingCapacity().get());
  EXPECT_FALSE(coil.isRatedTotalHeatingCapacityAutosized());
  coil.autosizeRatedTotalHeatingCapacity();
  EXPECT_TRUE(coil.isRatedTotalHeatingCapacityAutosized());

  EXPECT_TRUE(coil.setRatedAirFlowRate(1.35));
  ASSERT_TRUE(coil.ratedAirFlowRate());
  EXPECT_DOUBLE_EQ(1.35, coil.ratedAirFlowRate().get());
  EXPECT_FALSE(coil.isRatedAirFlowRateAutosized());
  coil.autosizeRatedAirFlowRate();
  EXPECT_TRUE(coil.isRatedAirFlowRateAutosized());
}
