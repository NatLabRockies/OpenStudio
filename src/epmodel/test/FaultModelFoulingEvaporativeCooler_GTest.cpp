/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/FaultModelFoulingEvaporativeCooler.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, FaultModelFoulingEvaporativeCooler_DefaultConstructor) {
  Model model;
  FaultModelFoulingEvaporativeCooler fault(model);
  EXPECT_EQ(FaultModelFoulingEvaporativeCooler::iddObjectType(), fault.iddObject().type());

  const auto values = FaultModelFoulingEvaporativeCooler::evaporativeCoolerObjectTypeValues();
  EXPECT_FALSE(values.empty());

  EXPECT_TRUE(fault.isFoulingFactorDefaulted());
  EXPECT_DOUBLE_EQ(1.0, fault.foulingFactor());
}

TEST_F(EPModelFixture, FaultModelFoulingEvaporativeCooler_ScalarAccessors_RoundTrip) {
  Model model;
  FaultModelFoulingEvaporativeCooler fault(model);

  EXPECT_TRUE(fault.setEvaporativeCoolerObjectType("EvaporativeCooler:Indirect:WetCoil"));
  EXPECT_EQ("EvaporativeCooler:Indirect:WetCoil", fault.evaporativeCoolerObjectType());

  EXPECT_FALSE(fault.setEvaporativeCoolerObjectType("InvalidEvaporativeCoolerObjectType"));
  EXPECT_EQ("EvaporativeCooler:Indirect:WetCoil", fault.evaporativeCoolerObjectType());

  EXPECT_TRUE(fault.setFoulingFactor(0.85));
  EXPECT_DOUBLE_EQ(0.85, fault.foulingFactor());
  EXPECT_FALSE(fault.isFoulingFactorDefaulted());

  EXPECT_FALSE(fault.setFoulingFactor(1.1));
  EXPECT_DOUBLE_EQ(0.85, fault.foulingFactor());

  fault.resetFoulingFactor();
  EXPECT_TRUE(fault.isFoulingFactorDefaulted());
  EXPECT_DOUBLE_EQ(1.0, fault.foulingFactor());
}
