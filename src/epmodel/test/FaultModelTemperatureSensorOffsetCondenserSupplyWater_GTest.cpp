/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/FaultModelTemperatureSensorOffsetCondenserSupplyWater.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, FaultModelTemperatureSensorOffsetCondenserSupplyWater_DefaultConstructor) {
  Model model;
  FaultModelTemperatureSensorOffsetCondenserSupplyWater fault(model);
  EXPECT_EQ(FaultModelTemperatureSensorOffsetCondenserSupplyWater::iddObjectType(), fault.iddObject().type());

  EXPECT_TRUE(fault.isReferenceSensorOffsetDefaulted());
  EXPECT_DOUBLE_EQ(0.0, fault.referenceSensorOffset());
}

TEST_F(EPModelFixture, FaultModelTemperatureSensorOffsetCondenserSupplyWater_ScalarAccessors_RoundTrip) {
  Model model;
  FaultModelTemperatureSensorOffsetCondenserSupplyWater fault(model);

  EXPECT_TRUE(fault.setReferenceSensorOffset(0.01));
  EXPECT_DOUBLE_EQ(0.01, fault.referenceSensorOffset());
  EXPECT_FALSE(fault.isReferenceSensorOffsetDefaulted());

  EXPECT_TRUE(fault.setReferenceSensorOffset(0.02));
  EXPECT_DOUBLE_EQ(0.02, fault.referenceSensorOffset());

  EXPECT_FALSE(fault.setReferenceSensorOffset(10.0));
  EXPECT_DOUBLE_EQ(0.02, fault.referenceSensorOffset());

  fault.resetReferenceSensorOffset();
  EXPECT_TRUE(fault.isReferenceSensorOffsetDefaulted());
  EXPECT_DOUBLE_EQ(0.0, fault.referenceSensorOffset());
}
