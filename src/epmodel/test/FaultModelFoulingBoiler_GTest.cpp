/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/FaultModelFoulingBoiler.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, FaultModelFoulingBoiler_DefaultConstructor) {
  Model model;
  FaultModelFoulingBoiler fault(model);
  EXPECT_EQ(FaultModelFoulingBoiler::iddObjectType(), fault.iddObject().type());

  const auto values = FaultModelFoulingBoiler::boilerObjectTypeValues();
  EXPECT_FALSE(values.empty());

  EXPECT_TRUE(fault.isFoulingFactorDefaulted());
  EXPECT_DOUBLE_EQ(1.0, fault.foulingFactor());
}

TEST_F(EPModelFixture, FaultModelFoulingBoiler_ScalarAccessors_RoundTrip) {
  Model model;
  FaultModelFoulingBoiler fault(model);

  EXPECT_TRUE(fault.setBoilerObjectType("Boiler:HotWater"));
  EXPECT_EQ("Boiler:HotWater", fault.boilerObjectType());

  EXPECT_FALSE(fault.setBoilerObjectType("InvalidBoilerObjectType"));
  EXPECT_EQ("Boiler:HotWater", fault.boilerObjectType());

  EXPECT_TRUE(fault.setFoulingFactor(0.85));
  EXPECT_DOUBLE_EQ(0.85, fault.foulingFactor());
  EXPECT_FALSE(fault.isFoulingFactorDefaulted());

  EXPECT_FALSE(fault.setFoulingFactor(1.1));
  EXPECT_DOUBLE_EQ(0.85, fault.foulingFactor());

  fault.resetFoulingFactor();
  EXPECT_TRUE(fault.isFoulingFactorDefaulted());
  EXPECT_DOUBLE_EQ(1.0, fault.foulingFactor());
}
