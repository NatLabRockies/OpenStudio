/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/FaultModelTemperatureSensorOffsetOutdoorAir.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, FaultModelTemperatureSensorOffsetOutdoorAir_DefaultConstructor) {
  Model model;
  FaultModelTemperatureSensorOffsetOutdoorAir fault(model);
  EXPECT_EQ(FaultModelTemperatureSensorOffsetOutdoorAir::iddObjectType(), fault.iddObject().type());

  EXPECT_TRUE(fault.isTemperatureSensorOffsetDefaulted());
  EXPECT_DOUBLE_EQ(0.0, fault.temperatureSensorOffset());
}

TEST_F(EPModelFixture, FaultModelTemperatureSensorOffsetOutdoorAir_ScalarAccessors_RoundTrip) {
  Model model;
  FaultModelTemperatureSensorOffsetOutdoorAir fault(model);

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
