/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/ZoneContaminantSourceAndSinkCarbonDioxide.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneContaminantSourceAndSinkCarbonDioxide_DefaultConstructor) {
  Model model;
  ZoneContaminantSourceAndSinkCarbonDioxide zoneContaminant(model);
  EXPECT_EQ(ZoneContaminantSourceAndSinkCarbonDioxide::iddObjectType(), zoneContaminant.iddObject().type());
}

TEST_F(EPModelFixture, ZoneContaminantSourceAndSinkCarbonDioxide_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneContaminantSourceAndSinkCarbonDioxide zoneContaminant(model);

  constexpr double expectedRate = 1.23e-4;
  EXPECT_TRUE(zoneContaminant.setDesignGenerationRate(expectedRate));

  const auto rate = zoneContaminant.designGenerationRate();
  ASSERT_TRUE(rate);
  EXPECT_DOUBLE_EQ(expectedRate, *rate);

  zoneContaminant.resetDesignGenerationRate();
  EXPECT_FALSE(zoneContaminant.designGenerationRate());
}
