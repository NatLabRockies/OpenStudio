/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl_DefaultConstructor) {
  Model model;
  CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl coil(model);
  EXPECT_EQ(CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl::iddObjectType(), coil.iddObject().type());
  EXPECT_FALSE(coil.nameString().empty());
}

TEST_F(EPModelFixture, CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl_ScalarAccessors_RoundTrip) {
  Model model;
  CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl coil(model);

  EXPECT_TRUE(coil.setRatedTotalCoolingCapacity(12345.0));
  ASSERT_TRUE(coil.ratedTotalCoolingCapacity());
  EXPECT_DOUBLE_EQ(12345.0, coil.ratedTotalCoolingCapacity().get());
  EXPECT_FALSE(coil.isRatedTotalCoolingCapacityAutosized());
  coil.autosizeRatedTotalCoolingCapacity();
  EXPECT_TRUE(coil.isRatedTotalCoolingCapacityAutosized());

  EXPECT_TRUE(coil.setRatedSensibleHeatRatio(0.71));
  ASSERT_TRUE(coil.ratedSensibleHeatRatio());
  EXPECT_DOUBLE_EQ(0.71, coil.ratedSensibleHeatRatio().get());
  EXPECT_FALSE(coil.isRatedSensibleHeatRatioAutosized());
  coil.autosizeRatedSensibleHeatRatio();
  EXPECT_TRUE(coil.isRatedSensibleHeatRatioAutosized());

  EXPECT_TRUE(coil.setIndoorUnitReferenceSuperheating(8.25));
  EXPECT_DOUBLE_EQ(8.25, coil.indoorUnitReferenceSuperheating());
}
