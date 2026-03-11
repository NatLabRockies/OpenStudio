/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/ZoneAirHeatBalanceAlgorithm.hpp"

#include <algorithm>
#include <string>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneAirHeatBalanceAlgorithm_DefaultConstructor) {
  Model model;
  ZoneAirHeatBalanceAlgorithm algorithm(model);

  EXPECT_EQ(ZoneAirHeatBalanceAlgorithm::iddObjectType(), algorithm.iddObject().type());
  EXPECT_FALSE(algorithm.algorithm().empty());
  const auto validValues = ZoneAirHeatBalanceAlgorithm::validAlgorithmValues();
  EXPECT_NE(validValues.cend(), std::find(validValues.cbegin(), validValues.cend(), algorithm.algorithm()));

  EXPECT_FALSE(algorithm.doSpaceHeatBalanceforSizing());
  EXPECT_FALSE(algorithm.doSpaceHeatBalanceforSimulation());
}

TEST_F(EPModelFixture, ZoneAirHeatBalanceAlgorithm_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneAirHeatBalanceAlgorithm algorithm(model);

  const auto initialAlgorithm = algorithm.algorithm();
  const auto validValues = ZoneAirHeatBalanceAlgorithm::validAlgorithmValues();
  ASSERT_GT(validValues.size(), 1u);

  std::string alternative;
  for (const auto& candidate : validValues) {
    if (candidate != initialAlgorithm) {
      alternative = candidate;
      break;
    }
  }
  ASSERT_FALSE(alternative.empty());

  EXPECT_TRUE(algorithm.setAlgorithm(alternative));
  EXPECT_EQ(alternative, algorithm.algorithm());
  algorithm.resetAlgorithm();
  EXPECT_EQ(initialAlgorithm, algorithm.algorithm());
  EXPECT_TRUE(algorithm.isAlgorithmDefaulted());

  EXPECT_TRUE(algorithm.setDoSpaceHeatBalanceforSizing(true));
  EXPECT_TRUE(algorithm.doSpaceHeatBalanceforSizing());
  EXPECT_FALSE(algorithm.isDoSpaceHeatBalanceforSizingDefaulted());
  algorithm.resetDoSpaceHeatBalanceforSizing();
  EXPECT_FALSE(algorithm.doSpaceHeatBalanceforSizing());
  EXPECT_TRUE(algorithm.isDoSpaceHeatBalanceforSizingDefaulted());

  EXPECT_TRUE(algorithm.setDoSpaceHeatBalanceforSimulation(true));
  EXPECT_TRUE(algorithm.doSpaceHeatBalanceforSimulation());
  EXPECT_FALSE(algorithm.isDoSpaceHeatBalanceforSimulationDefaulted());
  algorithm.resetDoSpaceHeatBalanceforSimulation();
  EXPECT_FALSE(algorithm.doSpaceHeatBalanceforSimulation());
  EXPECT_TRUE(algorithm.isDoSpaceHeatBalanceforSimulationDefaulted());
}
