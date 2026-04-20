/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/HVACTemplateThermostat.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, HVACTemplateThermostat_DefaultConstructor) {
  Model model;
  HVACTemplateThermostat object(model);
  EXPECT_EQ(HVACTemplateThermostat::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, HVACTemplateThermostat_ScalarAccessors_RoundTrip) {
  Model model;
  HVACTemplateThermostat object(model);

  EXPECT_FALSE(object.constantHeatingSetpoint());
  EXPECT_FALSE(object.constantCoolingSetpoint());

  EXPECT_TRUE(object.setConstantHeatingSetpoint(20.5));
  ASSERT_TRUE(object.constantHeatingSetpoint());
  EXPECT_DOUBLE_EQ(20.5, object.constantHeatingSetpoint().get());

  EXPECT_TRUE(object.setConstantCoolingSetpoint(24.0));
  ASSERT_TRUE(object.constantCoolingSetpoint());
  EXPECT_DOUBLE_EQ(24.0, object.constantCoolingSetpoint().get());

  object.resetConstantHeatingSetpoint();
  object.resetConstantCoolingSetpoint();

  EXPECT_FALSE(object.constantHeatingSetpoint());
  EXPECT_FALSE(object.constantCoolingSetpoint());
}
