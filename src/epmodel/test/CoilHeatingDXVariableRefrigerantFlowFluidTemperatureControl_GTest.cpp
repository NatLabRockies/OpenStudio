/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_DefaultConstructor) {
  Model model;
  CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl coil(model);
  EXPECT_EQ(CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl::iddObjectType(), coil.iddObject().type());
  EXPECT_FALSE(coil.nameString().empty());
}

TEST_F(EPModelFixture, CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_ScalarAccessors_RoundTrip) {
  Model model;
  CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl coil(model);

  EXPECT_TRUE(coil.setRatedTotalHeatingCapacity(12345.0));
  ASSERT_TRUE(coil.ratedTotalHeatingCapacity());
  EXPECT_DOUBLE_EQ(12345.0, coil.ratedTotalHeatingCapacity().get());
  EXPECT_FALSE(coil.isRatedTotalHeatingCapacityAutosized());
  coil.autosizeRatedTotalHeatingCapacity();
  EXPECT_TRUE(coil.isRatedTotalHeatingCapacityAutosized());

  EXPECT_TRUE(coil.setIndoorUnitReferenceSubcooling(7.5));
  EXPECT_DOUBLE_EQ(7.5, coil.indoorUnitReferenceSubcooling());
}
