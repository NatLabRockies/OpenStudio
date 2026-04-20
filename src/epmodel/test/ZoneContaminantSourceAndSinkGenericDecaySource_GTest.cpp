/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/ZoneContaminantSourceAndSinkGenericDecaySource.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneContaminantSourceAndSinkGenericDecaySource_DefaultConstructor) {
  Model model;
  ZoneContaminantSourceAndSinkGenericDecaySource zoneContaminant(model);
  EXPECT_EQ(ZoneContaminantSourceAndSinkGenericDecaySource::iddObjectType(), zoneContaminant.iddObject().type());
}

TEST_F(EPModelFixture, ZoneContaminantSourceAndSinkGenericDecaySource_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneContaminantSourceAndSinkGenericDecaySource zoneContaminant(model);

  constexpr double expectedInitialEmissionRate = 1.23e-4;
  EXPECT_TRUE(zoneContaminant.setInitialEmissionRate(expectedInitialEmissionRate));
  const auto initialEmissionRate = zoneContaminant.initialEmissionRate();
  ASSERT_TRUE(initialEmissionRate);
  EXPECT_DOUBLE_EQ(expectedInitialEmissionRate, *initialEmissionRate);
  zoneContaminant.resetInitialEmissionRate();
  EXPECT_FALSE(zoneContaminant.initialEmissionRate());

  constexpr double expectedDelayTimeConstant = 2.34;
  EXPECT_TRUE(zoneContaminant.setDelayTimeConstant(expectedDelayTimeConstant));
  const auto delayTimeConstant = zoneContaminant.delayTimeConstant();
  ASSERT_TRUE(delayTimeConstant);
  EXPECT_DOUBLE_EQ(expectedDelayTimeConstant, *delayTimeConstant);
  zoneContaminant.resetDelayTimeConstant();
  EXPECT_FALSE(zoneContaminant.delayTimeConstant());
}
