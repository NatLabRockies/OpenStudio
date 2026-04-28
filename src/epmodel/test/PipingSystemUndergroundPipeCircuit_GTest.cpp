/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/PipingSystemUndergroundPipeCircuit.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, PipingSystemUndergroundPipeCircuit_DefaultConstructor) {
  Model model;
  PipingSystemUndergroundPipeCircuit pipeCircuit(model);
  EXPECT_EQ(PipingSystemUndergroundPipeCircuit::iddObjectType(), pipeCircuit.iddObject().type());
  EXPECT_FALSE(pipeCircuit.nameString().empty());

  EXPECT_TRUE(pipeCircuit.isConvergenceCriterionfortheInnerRadialIterationLoopDefaulted());
  EXPECT_TRUE(pipeCircuit.isMaximumIterationsintheInnerRadialIterationLoopDefaulted());
  EXPECT_TRUE(pipeCircuit.isNumberofSoilNodesintheInnerRadialNearPipeMeshRegionDefaulted());

  EXPECT_DOUBLE_EQ(0.001, pipeCircuit.convergenceCriterionfortheInnerRadialIterationLoop());
  EXPECT_EQ(500, pipeCircuit.maximumIterationsintheInnerRadialIterationLoop());
  EXPECT_EQ(3, pipeCircuit.numberofSoilNodesintheInnerRadialNearPipeMeshRegion());
}

TEST_F(EPModelFixture, PipingSystemUndergroundPipeCircuit_ScalarAccessors_RoundTrip) {
  Model model;
  PipingSystemUndergroundPipeCircuit pipeCircuit(model);

  EXPECT_TRUE(pipeCircuit.setPipeThermalConductivity(0.38));
  EXPECT_TRUE(pipeCircuit.setPipeDensity(980.0));
  EXPECT_TRUE(pipeCircuit.setPipeSpecificHeat(1900.0));
  EXPECT_TRUE(pipeCircuit.setPipeInnerDiameter(0.08));
  EXPECT_TRUE(pipeCircuit.setPipeOuterDiameter(0.10));
  EXPECT_TRUE(pipeCircuit.setDesignFlowRate(0.0015));
  EXPECT_TRUE(pipeCircuit.setConvergenceCriterionfortheInnerRadialIterationLoop(0.01));
  EXPECT_TRUE(pipeCircuit.setMaximumIterationsintheInnerRadialIterationLoop(750));
  EXPECT_TRUE(pipeCircuit.setNumberofSoilNodesintheInnerRadialNearPipeMeshRegion(7));
  EXPECT_TRUE(pipeCircuit.setRadialThicknessofInnerRadialNearPipeMeshRegion(0.25));
  EXPECT_TRUE(pipeCircuit.setNumberofPipeSegmentsEnteredforthisPipeCircuit(3));

  EXPECT_DOUBLE_EQ(0.38, pipeCircuit.pipeThermalConductivity());
  EXPECT_DOUBLE_EQ(980.0, pipeCircuit.pipeDensity());
  EXPECT_DOUBLE_EQ(1900.0, pipeCircuit.pipeSpecificHeat());
  EXPECT_DOUBLE_EQ(0.08, pipeCircuit.pipeInnerDiameter());
  EXPECT_DOUBLE_EQ(0.10, pipeCircuit.pipeOuterDiameter());
  EXPECT_DOUBLE_EQ(0.0015, pipeCircuit.designFlowRate());
  EXPECT_DOUBLE_EQ(0.01, pipeCircuit.convergenceCriterionfortheInnerRadialIterationLoop());
  EXPECT_EQ(750, pipeCircuit.maximumIterationsintheInnerRadialIterationLoop());
  EXPECT_EQ(7, pipeCircuit.numberofSoilNodesintheInnerRadialNearPipeMeshRegion());
  EXPECT_DOUBLE_EQ(0.25, pipeCircuit.radialThicknessofInnerRadialNearPipeMeshRegion());
  EXPECT_EQ(3, pipeCircuit.numberofPipeSegmentsEnteredforthisPipeCircuit());

  EXPECT_FALSE(pipeCircuit.isConvergenceCriterionfortheInnerRadialIterationLoopDefaulted());
  EXPECT_FALSE(pipeCircuit.isMaximumIterationsintheInnerRadialIterationLoopDefaulted());
  EXPECT_FALSE(pipeCircuit.isNumberofSoilNodesintheInnerRadialNearPipeMeshRegionDefaulted());

  pipeCircuit.resetConvergenceCriterionfortheInnerRadialIterationLoop();
  pipeCircuit.resetMaximumIterationsintheInnerRadialIterationLoop();
  pipeCircuit.resetNumberofSoilNodesintheInnerRadialNearPipeMeshRegion();

  EXPECT_TRUE(pipeCircuit.isConvergenceCriterionfortheInnerRadialIterationLoopDefaulted());
  EXPECT_TRUE(pipeCircuit.isMaximumIterationsintheInnerRadialIterationLoopDefaulted());
  EXPECT_TRUE(pipeCircuit.isNumberofSoilNodesintheInnerRadialNearPipeMeshRegionDefaulted());

  EXPECT_FALSE(pipeCircuit.setPipeThermalConductivity(-1.0));
  EXPECT_FALSE(pipeCircuit.setMaximumIterationsintheInnerRadialIterationLoop(2));
  EXPECT_FALSE(pipeCircuit.setNumberofSoilNodesintheInnerRadialNearPipeMeshRegion(0));
  EXPECT_FALSE(pipeCircuit.setNumberofPipeSegmentsEnteredforthisPipeCircuit(0));
}
