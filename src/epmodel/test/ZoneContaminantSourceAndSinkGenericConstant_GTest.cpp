/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/ZoneContaminantSourceAndSinkGenericConstant.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneContaminantSourceAndSinkGenericConstant_DefaultConstructor) {
  Model model;
  ZoneContaminantSourceAndSinkGenericConstant zoneContaminant(model);
  EXPECT_EQ(ZoneContaminantSourceAndSinkGenericConstant::iddObjectType(), zoneContaminant.iddObject().type());
}

TEST_F(EPModelFixture, ZoneContaminantSourceAndSinkGenericConstant_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneContaminantSourceAndSinkGenericConstant zoneContaminant(model);

  constexpr double expectedGenerationRate = 1.23e-4;
  EXPECT_TRUE(zoneContaminant.setDesignGenerationRate(expectedGenerationRate));
  const auto generationRate = zoneContaminant.designGenerationRate();
  ASSERT_TRUE(generationRate);
  EXPECT_DOUBLE_EQ(expectedGenerationRate, *generationRate);
  zoneContaminant.resetDesignGenerationRate();
  EXPECT_FALSE(zoneContaminant.designGenerationRate());

  constexpr double expectedRemovalCoefficient = 4.56e-4;
  EXPECT_TRUE(zoneContaminant.setDesignRemovalCoefficient(expectedRemovalCoefficient));
  const auto removalCoefficient = zoneContaminant.designRemovalCoefficient();
  ASSERT_TRUE(removalCoefficient);
  EXPECT_DOUBLE_EQ(expectedRemovalCoefficient, *removalCoefficient);
  zoneContaminant.resetDesignRemovalCoefficient();
  EXPECT_FALSE(zoneContaminant.designRemovalCoefficient());
}
