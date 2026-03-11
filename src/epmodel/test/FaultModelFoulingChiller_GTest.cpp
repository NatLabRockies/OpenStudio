/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/FaultModelFoulingChiller.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, FaultModelFoulingChiller_DefaultConstructor) {
  Model model;
  FaultModelFoulingChiller fault(model);
  EXPECT_EQ(FaultModelFoulingChiller::iddObjectType(), fault.iddObject().type());

  const auto values = FaultModelFoulingChiller::chillerObjectTypeValues();
  EXPECT_FALSE(values.empty());

  EXPECT_TRUE(fault.isFoulingFactorDefaulted());
  EXPECT_DOUBLE_EQ(1.0, fault.foulingFactor());
}

TEST_F(EPModelFixture, FaultModelFoulingChiller_ScalarAccessors_RoundTrip) {
  Model model;
  FaultModelFoulingChiller fault(model);

  EXPECT_TRUE(fault.setChillerObjectType("Chiller:Electric:EIR"));
  EXPECT_EQ("Chiller:Electric:EIR", fault.chillerObjectType());

  EXPECT_FALSE(fault.setChillerObjectType("InvalidChillerObjectType"));
  EXPECT_EQ("Chiller:Electric:EIR", fault.chillerObjectType());

  EXPECT_TRUE(fault.setFoulingFactor(0.85));
  EXPECT_DOUBLE_EQ(0.85, fault.foulingFactor());
  EXPECT_FALSE(fault.isFoulingFactorDefaulted());

  EXPECT_FALSE(fault.setFoulingFactor(1.1));
  EXPECT_DOUBLE_EQ(0.85, fault.foulingFactor());

  fault.resetFoulingFactor();
  EXPECT_TRUE(fault.isFoulingFactorDefaulted());
  EXPECT_DOUBLE_EQ(1.0, fault.foulingFactor());
}
