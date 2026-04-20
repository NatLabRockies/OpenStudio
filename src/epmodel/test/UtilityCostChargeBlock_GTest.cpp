/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/UtilityCostChargeBlock.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, UtilityCostChargeBlock_DefaultConstructor) {
  Model model;
  UtilityCostChargeBlock block(model);

  EXPECT_EQ(UtilityCostChargeBlock::iddObjectType(), block.iddObject().type());
  EXPECT_FALSE(UtilityCostChargeBlock::seasonValues().empty());
  EXPECT_FALSE(UtilityCostChargeBlock::categoryVariableNameValues().empty());
}

TEST_F(EPModelFixture, UtilityCostChargeBlock_ScalarAccessors_RoundTrip) {
  Model model;
  UtilityCostChargeBlock block(model);

  EXPECT_TRUE(block.setSourceVariable("totalEnergy"));
  EXPECT_TRUE(block.setSeason("Summer"));
  EXPECT_TRUE(block.setCategoryVariableName("Total"));
  EXPECT_TRUE(block.setRemainingIntoVariable("unusedEnergy"));
  EXPECT_TRUE(block.setBlockSizeMultiplierValueorVariableName("1"));

  EXPECT_EQ("totalEnergy", block.sourceVariable());
  EXPECT_FALSE(block.isSeasonDefaulted());
  EXPECT_EQ("Summer", block.season());
  EXPECT_EQ("Total", block.categoryVariableName());
  EXPECT_EQ("unusedEnergy", block.remainingIntoVariable().get());
  EXPECT_EQ("1", block.blockSizeMultiplierValueorVariableName().get());

  block.resetSeason();
  EXPECT_TRUE(block.isSeasonDefaulted());
}
