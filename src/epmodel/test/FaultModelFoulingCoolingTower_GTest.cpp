/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/FaultModelFoulingCoolingTower.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, FaultModelFoulingCoolingTower_DefaultConstructor) {
  Model model;
  FaultModelFoulingCoolingTower fault(model);
  EXPECT_EQ(FaultModelFoulingCoolingTower::iddObjectType(), fault.iddObject().type());

  const auto values = FaultModelFoulingCoolingTower::coolingTowerObjectTypeValues();
  EXPECT_FALSE(values.empty());

  EXPECT_FALSE(fault.referenceUAReductionFactor());
}

TEST_F(EPModelFixture, FaultModelFoulingCoolingTower_ScalarAccessors_RoundTrip) {
  Model model;
  FaultModelFoulingCoolingTower fault(model);

  EXPECT_TRUE(fault.setCoolingTowerObjectType("CoolingTower:SingleSpeed"));
  EXPECT_EQ("CoolingTower:SingleSpeed", fault.coolingTowerObjectType());

  EXPECT_FALSE(fault.setCoolingTowerObjectType("InvalidCoolingTowerObjectType"));
  EXPECT_EQ("CoolingTower:SingleSpeed", fault.coolingTowerObjectType());

  EXPECT_TRUE(fault.setReferenceUAReductionFactor(0.85));
  ASSERT_TRUE(fault.referenceUAReductionFactor());
  EXPECT_DOUBLE_EQ(0.85, fault.referenceUAReductionFactor().get());

  EXPECT_FALSE(fault.setReferenceUAReductionFactor(0.0));
  ASSERT_TRUE(fault.referenceUAReductionFactor());
  EXPECT_DOUBLE_EQ(0.85, fault.referenceUAReductionFactor().get());

  fault.resetReferenceUAReductionFactor();
  EXPECT_FALSE(fault.referenceUAReductionFactor());
}
