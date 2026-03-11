/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/FaultModelThermostatOffset.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, FaultModelThermostatOffset_DefaultConstructor) {
  Model model;
  FaultModelThermostatOffset fault(model);
  EXPECT_EQ(FaultModelThermostatOffset::iddObjectType(), fault.iddObject().type());

  EXPECT_TRUE(fault.isReferenceThermostatOffsetDefaulted());
  EXPECT_DOUBLE_EQ(2.0, fault.referenceThermostatOffset());
}

TEST_F(EPModelFixture, FaultModelThermostatOffset_ScalarAccessors_RoundTrip) {
  Model model;
  FaultModelThermostatOffset fault(model);

  EXPECT_TRUE(fault.setReferenceThermostatOffset(-3.25));
  EXPECT_FALSE(fault.isReferenceThermostatOffsetDefaulted());
  EXPECT_DOUBLE_EQ(-3.25, fault.referenceThermostatOffset());

  EXPECT_FALSE(fault.setReferenceThermostatOffset(10.0));
  EXPECT_DOUBLE_EQ(-3.25, fault.referenceThermostatOffset());

  EXPECT_FALSE(fault.setReferenceThermostatOffset(-10.0));
  EXPECT_DOUBLE_EQ(-3.25, fault.referenceThermostatOffset());

  fault.resetReferenceThermostatOffset();
  EXPECT_TRUE(fault.isReferenceThermostatOffsetDefaulted());
  EXPECT_DOUBLE_EQ(2.0, fault.referenceThermostatOffset());
}
