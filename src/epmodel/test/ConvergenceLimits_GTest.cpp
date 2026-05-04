/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/ConvergenceLimits.hpp"
#include "../ModelObject/ConvergenceLimits_Impl.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ConvergenceLimits_DefaultConstructor) {
  Model model;
  auto convergenceLimits = model.getUniqueModelObject<ConvergenceLimits>();
  EXPECT_EQ(ConvergenceLimits::iddObjectType(), convergenceLimits.iddObject().type());

  ASSERT_TRUE(convergenceLimits.minimumSystemTimestep());
  EXPECT_EQ(1, convergenceLimits.minimumSystemTimestep().get());
}

TEST_F(EPModelFixture, ConvergenceLimits_ScalarAccessors_RoundTrip) {
  Model model;
  auto convergenceLimits = model.getUniqueModelObject<ConvergenceLimits>();

  EXPECT_TRUE(convergenceLimits.setMinimumSystemTimestep(2));
  ASSERT_TRUE(convergenceLimits.minimumSystemTimestep());
  EXPECT_EQ(2, convergenceLimits.minimumSystemTimestep().get());

  EXPECT_TRUE(convergenceLimits.setMaximumHVACIterations(33));
  EXPECT_EQ(33, convergenceLimits.maximumHVACIterations());
  EXPECT_FALSE(convergenceLimits.isMaximumHVACIterationsDefaulted());
  convergenceLimits.resetMaximumHVACIterations();
  EXPECT_TRUE(convergenceLimits.isMaximumHVACIterationsDefaulted());

  EXPECT_TRUE(convergenceLimits.setMinimumPlantIterations(4));
  EXPECT_EQ(4, convergenceLimits.minimumPlantIterations());
  EXPECT_FALSE(convergenceLimits.isMinimumPlantIterationsDefaulted());
  convergenceLimits.resetMinimumPlantIterations();
  EXPECT_TRUE(convergenceLimits.isMinimumPlantIterationsDefaulted());

  EXPECT_TRUE(convergenceLimits.setMaximumPlantIterations(9));
  EXPECT_EQ(9, convergenceLimits.maximumPlantIterations());
  EXPECT_FALSE(convergenceLimits.isMaximumPlantIterationsDefaulted());
  convergenceLimits.resetMaximumPlantIterations();
  EXPECT_TRUE(convergenceLimits.isMaximumPlantIterationsDefaulted());
}
