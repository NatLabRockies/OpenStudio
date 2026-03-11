/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/MeterCustom.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, MeterCustom_DefaultConstructor) {
  Model model;
  MeterCustom meterCustom(model);

  EXPECT_EQ(MeterCustom::iddObjectType(), meterCustom.iddObject().type());
  ASSERT_TRUE(meterCustom.fuelType());
  EXPECT_EQ("Electricity", meterCustom.fuelType().get());
}

TEST_F(EPModelFixture, MeterCustom_ScalarAccessors_RoundTrip) {
  Model model;
  MeterCustom meterCustom(model);

  EXPECT_FALSE(MeterCustom::fuelTypeValues().empty());

  EXPECT_TRUE(meterCustom.setFuelType("Generic"));
  ASSERT_TRUE(meterCustom.fuelType());
  EXPECT_EQ("Generic", meterCustom.fuelType().get());

  EXPECT_FALSE(meterCustom.setFuelType("InvalidFuelType"));
  ASSERT_TRUE(meterCustom.fuelType());
  EXPECT_EQ("Generic", meterCustom.fuelType().get());

  meterCustom.resetFuelType();
  ASSERT_TRUE(meterCustom.fuelType());
  EXPECT_EQ("Electricity", meterCustom.fuelType().get());
}
