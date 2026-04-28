/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "scaffolds/UtilityCostRatchet.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, UtilityCostRatchet_DefaultConstructor) {
  Model model;
  UtilityCostRatchet ratchet(model);

  EXPECT_EQ(UtilityCostRatchet::iddObjectType(), ratchet.iddObject().type());
  EXPECT_FALSE(UtilityCostRatchet::seasonFromValues().empty());
  EXPECT_FALSE(UtilityCostRatchet::seasonToValues().empty());
  EXPECT_FALSE(ratchet.multiplierValueorVariableName());
  EXPECT_FALSE(ratchet.offsetValueorVariableName());
}

TEST_F(EPModelFixture, UtilityCostRatchet_ScalarAccessors_RoundTrip) {
  Model model;
  UtilityCostRatchet ratchet(model);

  ASSERT_FALSE(UtilityCostRatchet::seasonFromValues().empty());
  ASSERT_FALSE(UtilityCostRatchet::seasonToValues().empty());

  const auto seasonFrom = UtilityCostRatchet::seasonFromValues().front();
  const auto seasonTo = UtilityCostRatchet::seasonToValues().front();

  EXPECT_TRUE(ratchet.setBaselineSourceVariable("baseline"));
  EXPECT_TRUE(ratchet.setAdjustmentSourceVariable("adjust"));
  EXPECT_TRUE(ratchet.setSeasonFrom(seasonFrom));
  EXPECT_TRUE(ratchet.setSeasonTo(seasonTo));
  EXPECT_TRUE(ratchet.setMultiplierValueorVariableName("multiplier"));
  EXPECT_TRUE(ratchet.setOffsetValueorVariableName("offset"));

  EXPECT_EQ("baseline", ratchet.baselineSourceVariable());
  EXPECT_EQ("adjust", ratchet.adjustmentSourceVariable());
  EXPECT_EQ(seasonFrom, ratchet.seasonFrom());
  EXPECT_EQ(seasonTo, ratchet.seasonTo());
  EXPECT_TRUE(ratchet.multiplierValueorVariableName());
  EXPECT_EQ("multiplier", *ratchet.multiplierValueorVariableName());
  EXPECT_TRUE(ratchet.offsetValueorVariableName());
  EXPECT_EQ("offset", *ratchet.offsetValueorVariableName());

  ratchet.resetMultiplierValueorVariableName();
  EXPECT_TRUE(ratchet.multiplierValueorVariableName());
  EXPECT_TRUE(ratchet.multiplierValueorVariableName()->empty());

  ratchet.resetOffsetValueorVariableName();
  EXPECT_TRUE(ratchet.offsetValueorVariableName());
  EXPECT_TRUE(ratchet.offsetValueorVariableName()->empty());
}
