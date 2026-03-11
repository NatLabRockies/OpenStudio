/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/FaultModelTemperatureSensorOffsetReturnAir.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, FaultModelTemperatureSensorOffsetReturnAir_DefaultConstructor) {
  Model model;
  FaultModelTemperatureSensorOffsetReturnAir fault(model);
  EXPECT_EQ(FaultModelTemperatureSensorOffsetReturnAir::iddObjectType(), fault.iddObject().type());

  EXPECT_TRUE(fault.isTemperatureSensorOffsetDefaulted());
  EXPECT_DOUBLE_EQ(0.0, fault.temperatureSensorOffset());
}

TEST_F(EPModelFixture, FaultModelTemperatureSensorOffsetReturnAir_ScalarAccessors_RoundTrip) {
  Model model;
  FaultModelTemperatureSensorOffsetReturnAir fault(model);

  EXPECT_TRUE(fault.setTemperatureSensorOffset(0.25));
  EXPECT_DOUBLE_EQ(0.25, fault.temperatureSensorOffset());
  EXPECT_FALSE(fault.isTemperatureSensorOffsetDefaulted());

  EXPECT_TRUE(fault.setTemperatureSensorOffset(-0.5));
  EXPECT_DOUBLE_EQ(-0.5, fault.temperatureSensorOffset());

  EXPECT_FALSE(fault.setTemperatureSensorOffset(10.0));
  EXPECT_DOUBLE_EQ(-0.5, fault.temperatureSensorOffset());

  fault.resetTemperatureSensorOffset();
  EXPECT_TRUE(fault.isTemperatureSensorOffsetDefaulted());
  EXPECT_DOUBLE_EQ(0.0, fault.temperatureSensorOffset());
}
