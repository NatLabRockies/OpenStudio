/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/ZoneContaminantSourceAndSinkGenericDepositionRateSink.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneContaminantSourceAndSinkGenericDepositionRateSink_DefaultConstructor) {
  Model model;
  ZoneContaminantSourceAndSinkGenericDepositionRateSink sink(model);
  EXPECT_EQ(ZoneContaminantSourceAndSinkGenericDepositionRateSink::iddObjectType(), sink.iddObject().type());
}

TEST_F(EPModelFixture, ZoneContaminantSourceAndSinkGenericDepositionRateSink_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneContaminantSourceAndSinkGenericDepositionRateSink sink(model);

  constexpr double expectedDepositionRate = 3.21e-3;
  EXPECT_TRUE(sink.setDepositionRate(expectedDepositionRate));
  const auto depositionRate = sink.depositionRate();
  ASSERT_TRUE(depositionRate);
  EXPECT_DOUBLE_EQ(expectedDepositionRate, *depositionRate);

  EXPECT_TRUE(sink.setDepositionRate(0.0));
  const auto zeroDepositionRate = sink.depositionRate();
  ASSERT_TRUE(zeroDepositionRate);
  EXPECT_DOUBLE_EQ(0.0, *zeroDepositionRate);

  EXPECT_FALSE(sink.setDepositionRate(-0.1));

  sink.resetDepositionRate();
  EXPECT_FALSE(sink.depositionRate());
}
