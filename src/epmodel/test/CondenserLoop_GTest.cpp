/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/CondenserLoop.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CondenserLoop_DefaultConstructor) {
  Model model;
  CondenserLoop condenserLoop(model);
  EXPECT_EQ(CondenserLoop::iddObjectType(), condenserLoop.iddObject().type());
}

TEST_F(EPModelFixture, CondenserLoop_ScalarAccessors_RoundTrip) {
  Model model;
  CondenserLoop condenserLoop(model);

  EXPECT_TRUE(condenserLoop.setName("Main Condenser Loop"));
  EXPECT_EQ("Main Condenser Loop", condenserLoop.nameString());

  EXPECT_TRUE(condenserLoop.setFluidType("Water"));
  EXPECT_EQ("Water", condenserLoop.fluidType());

  EXPECT_TRUE(condenserLoop.setMaximumLoopTemperature(35.0));
  EXPECT_NEAR(35.0, condenserLoop.maximumLoopTemperature(), 1e-9);

  EXPECT_TRUE(condenserLoop.setMinimumLoopTemperature(5.0));
  EXPECT_NEAR(5.0, condenserLoop.minimumLoopTemperature(), 1e-9);

  EXPECT_TRUE(condenserLoop.setMaximumLoopFlowRate(0.45));
  ASSERT_TRUE(condenserLoop.maximumLoopFlowRate());
  EXPECT_NEAR(0.45, condenserLoop.maximumLoopFlowRate().get(), 1e-9);

  EXPECT_TRUE(condenserLoop.setMinimumLoopFlowRate(0.02));
  EXPECT_NEAR(0.02, condenserLoop.minimumLoopFlowRate(), 1e-9);

  EXPECT_TRUE(condenserLoop.setCondenserLoopVolume(12.5));
  ASSERT_TRUE(condenserLoop.condenserLoopVolume());
  EXPECT_NEAR(12.5, condenserLoop.condenserLoopVolume().get(), 1e-9);

  EXPECT_TRUE(condenserLoop.setLoadDistributionScheme("SequentialLoad"));
  EXPECT_EQ("SequentialLoad", condenserLoop.loadDistributionScheme());

  EXPECT_TRUE(condenserLoop.setPressureSimulationType("None"));
  EXPECT_EQ("None", condenserLoop.pressureSimulationType());

  EXPECT_TRUE(condenserLoop.setLoopCirculationTime(3.0));
  EXPECT_NEAR(3.0, condenserLoop.loopCirculationTime(), 1e-9);

  condenserLoop.autosizeMaximumLoopFlowRate();
  EXPECT_TRUE(condenserLoop.isMaximumLoopFlowRateAutosized());

  condenserLoop.autocalculateCondenserLoopVolume();
  EXPECT_TRUE(condenserLoop.isCondenserLoopVolumeAutocalculated());
}
