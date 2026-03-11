/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../StraightComponent/GroundHeatExchangerVertical.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, GroundHeatExchangerVertical_DefaultConstructor) {
  Model model;
  GroundHeatExchangerVertical ghx(model);
  EXPECT_EQ(GroundHeatExchangerVertical::iddObjectType(), ghx.iddObject().type());
  EXPECT_FALSE(ghx.nameString().empty());

  const auto numberofBoreHoles = ghx.numberofBoreHoles();
  ASSERT_TRUE(numberofBoreHoles);
  EXPECT_EQ(120, *numberofBoreHoles);
  EXPECT_DOUBLE_EQ(0.0005, ghx.gFunctionReferenceRatio());
  EXPECT_DOUBLE_EQ(1.0, ghx.boreHoleTopDepth());

  const auto boreHoleLength = ghx.boreHoleLength();
  ASSERT_TRUE(boreHoleLength);
  EXPECT_DOUBLE_EQ(76.2, *boreHoleLength);

  const auto boreHoleRadius = ghx.boreHoleRadius();
  ASSERT_TRUE(boreHoleRadius);
  EXPECT_DOUBLE_EQ(0.635080E-01, *boreHoleRadius);
}

TEST_F(EPModelFixture, GroundHeatExchangerVertical_ScalarAccessors_RoundTrip) {
  Model model;
  GroundHeatExchangerVertical ghx(model);

  EXPECT_TRUE(ghx.setNumberofBoreHoles(156));
  const auto numberofBoreHoles = ghx.numberofBoreHoles();
  ASSERT_TRUE(numberofBoreHoles);
  EXPECT_EQ(156, *numberofBoreHoles);

  ghx.resetNumberofBoreHoles();
  EXPECT_FALSE(ghx.numberofBoreHoles());

  EXPECT_TRUE(ghx.setGFunctionReferenceRatio(0.0012));
  EXPECT_DOUBLE_EQ(0.0012, ghx.gFunctionReferenceRatio());
  EXPECT_FALSE(ghx.isGFunctionReferenceRatioDefaulted());

  ghx.resetGFunctionReferenceRatio();
  EXPECT_TRUE(ghx.isGFunctionReferenceRatioDefaulted());

  EXPECT_TRUE(ghx.setBoreHoleTopDepth(1.25));
  EXPECT_DOUBLE_EQ(1.25, ghx.boreHoleTopDepth());

  EXPECT_TRUE(ghx.setBoreHoleLength(80.2));
  auto boreHoleLength = ghx.boreHoleLength();
  ASSERT_TRUE(boreHoleLength);
  EXPECT_DOUBLE_EQ(80.2, *boreHoleLength);
  ghx.resetBoreHoleLength();
  EXPECT_FALSE(ghx.boreHoleLength());

  EXPECT_TRUE(ghx.setBoreHoleRadius(0.07));
  auto boreHoleRadius = ghx.boreHoleRadius();
  ASSERT_TRUE(boreHoleRadius);
  EXPECT_DOUBLE_EQ(0.07, *boreHoleRadius);
  ghx.resetBoreHoleRadius();
  EXPECT_FALSE(ghx.boreHoleRadius());

  EXPECT_TRUE(ghx.setGroutThermalConductivity(0.72));
  auto groutThermalConductivity = ghx.groutThermalConductivity();
  ASSERT_TRUE(groutThermalConductivity);
  EXPECT_DOUBLE_EQ(0.72, *groutThermalConductivity);
  ghx.resetGroutThermalConductivity();
  EXPECT_FALSE(ghx.groutThermalConductivity());

  EXPECT_TRUE(ghx.setPipeThermalConductivity(0.45));
  auto pipeThermalConductivity = ghx.pipeThermalConductivity();
  ASSERT_TRUE(pipeThermalConductivity);
  EXPECT_DOUBLE_EQ(0.45, *pipeThermalConductivity);
  ghx.resetPipeThermalConductivity();
  EXPECT_FALSE(ghx.pipeThermalConductivity());

  EXPECT_TRUE(ghx.setPipeOutDiameter(0.03));
  auto pipeOutDiameter = ghx.pipeOutDiameter();
  ASSERT_TRUE(pipeOutDiameter);
  EXPECT_DOUBLE_EQ(0.03, *pipeOutDiameter);
  ghx.resetPipeOutDiameter();
  EXPECT_FALSE(ghx.pipeOutDiameter());

  EXPECT_TRUE(ghx.setUTubeDistance(0.028));
  auto uTubeDistance = ghx.uTubeDistance();
  ASSERT_TRUE(uTubeDistance);
  EXPECT_DOUBLE_EQ(0.028, *uTubeDistance);
  ghx.resetUTubeDistance();
  EXPECT_FALSE(ghx.uTubeDistance());

  EXPECT_TRUE(ghx.setPipeThickness(0.003));
  auto pipeThickness = ghx.pipeThickness();
  ASSERT_TRUE(pipeThickness);
  EXPECT_DOUBLE_EQ(0.003, *pipeThickness);
  ghx.resetPipeThickness();
  EXPECT_FALSE(ghx.pipeThickness());
}
