/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/MeterCustomDecrement.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, MeterCustomDecrement_DefaultConstructor) {
  Model model;
  MeterCustomDecrement meterCustomDecrement(model, "Electricity:Facility");

  EXPECT_EQ(MeterCustomDecrement::iddObjectType(), meterCustomDecrement.iddObject().type());
  EXPECT_EQ("Electricity:Facility", meterCustomDecrement.sourceMeterName());
  ASSERT_TRUE(meterCustomDecrement.fuelType());
  EXPECT_EQ("Electricity", meterCustomDecrement.fuelType().get());
}

TEST_F(EPModelFixture, MeterCustomDecrement_ScalarAccessors_RoundTrip) {
  Model model;
  MeterCustomDecrement meterCustomDecrement(model, "Electricity:Facility");

  EXPECT_FALSE(MeterCustomDecrement::fuelTypeValues().empty());

  EXPECT_TRUE(meterCustomDecrement.setSourceMeterName("Gas:Facility"));
  EXPECT_EQ("Gas:Facility", meterCustomDecrement.sourceMeterName());

  EXPECT_TRUE(meterCustomDecrement.setFuelType("Generic"));
  ASSERT_TRUE(meterCustomDecrement.fuelType());
  EXPECT_EQ("Generic", meterCustomDecrement.fuelType().get());

  EXPECT_FALSE(meterCustomDecrement.setFuelType("InvalidFuelType"));
  ASSERT_TRUE(meterCustomDecrement.fuelType());
  EXPECT_EQ("Generic", meterCustomDecrement.fuelType().get());

  meterCustomDecrement.resetFuelType();
  EXPECT_FALSE(meterCustomDecrement.fuelType());
}
