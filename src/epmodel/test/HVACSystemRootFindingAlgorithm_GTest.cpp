/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/HVACSystemRootFindingAlgorithm.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, HVACSystemRootFindingAlgorithm_DefaultConstructor) {
  Model model;
  HVACSystemRootFindingAlgorithm object(model);
  EXPECT_EQ(HVACSystemRootFindingAlgorithm::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, HVACSystemRootFindingAlgorithm_ScalarAccessors_RoundTrip) {
  Model model;
  HVACSystemRootFindingAlgorithm object(model);

  EXPECT_TRUE(object.isAlgorithmDefaulted());
  EXPECT_EQ("RegulaFalsi", object.algorithm());
  EXPECT_TRUE(object.setAlgorithm("BisectionThenRegulaFalsi"));
  EXPECT_EQ("BisectionThenRegulaFalsi", object.algorithm());
  EXPECT_FALSE(object.isAlgorithmDefaulted());
  object.resetAlgorithm();
  EXPECT_FALSE(object.isAlgorithmDefaulted());
  EXPECT_EQ("RegulaFalsi", object.algorithm());

  EXPECT_TRUE(object.isNumberofIterationsBeforeAlgorithmSwitchDefaulted());
  EXPECT_EQ(5, object.numberofIterationsBeforeAlgorithmSwitch());
  EXPECT_TRUE(object.setNumberofIterationsBeforeAlgorithmSwitch(8));
  EXPECT_EQ(8, object.numberofIterationsBeforeAlgorithmSwitch());
  EXPECT_FALSE(object.isNumberofIterationsBeforeAlgorithmSwitchDefaulted());
  object.resetNumberofIterationsBeforeAlgorithmSwitch();
  EXPECT_TRUE(object.isNumberofIterationsBeforeAlgorithmSwitchDefaulted());
  EXPECT_EQ(5, object.numberofIterationsBeforeAlgorithmSwitch());

  const auto values = HVACSystemRootFindingAlgorithm::algorithmValues();
  EXPECT_GE(values.size(), 1u);
}
