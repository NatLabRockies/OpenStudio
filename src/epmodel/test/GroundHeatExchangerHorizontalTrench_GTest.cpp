/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../StraightComponent/GroundHeatExchangerHorizontalTrench.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, GroundHeatExchangerHorizontalTrench_DefaultConstructor) {
  Model model;
  GroundHeatExchangerHorizontalTrench ghx(model);
  EXPECT_EQ(GroundHeatExchangerHorizontalTrench::iddObjectType(), ghx.iddObject().type());
  EXPECT_FALSE(ghx.nameString().empty());

  EXPECT_DOUBLE_EQ(0.004, ghx.designFlowRate());
  EXPECT_DOUBLE_EQ(75.0, ghx.trenchLengthinPipeAxialDirection());
  EXPECT_EQ(2, ghx.numberofTrenches());
  EXPECT_DOUBLE_EQ(2.0, ghx.horizontalSpacingBetweenPipes());
  EXPECT_DOUBLE_EQ(0.016, ghx.pipeInnerDiameter());
  EXPECT_DOUBLE_EQ(0.02667, ghx.pipeOuterDiameter());
  EXPECT_DOUBLE_EQ(1.25, ghx.burialDepth());
  EXPECT_DOUBLE_EQ(1.08, ghx.soilThermalConductivity());
  EXPECT_DOUBLE_EQ(962.0, ghx.soilDensity());
  EXPECT_DOUBLE_EQ(2576.0, ghx.soilSpecificHeat());
  EXPECT_DOUBLE_EQ(0.3895, ghx.pipeThermalConductivity());
  EXPECT_DOUBLE_EQ(641.0, ghx.pipeDensity());
  EXPECT_DOUBLE_EQ(2405.0, ghx.pipeSpecificHeat());
  EXPECT_DOUBLE_EQ(30.0, ghx.soilMoistureContentPercent());
  EXPECT_DOUBLE_EQ(50.0, ghx.soilMoistureContentPercentatSaturation());
  EXPECT_DOUBLE_EQ(0.408, ghx.evapotranspirationGroundCoverParameter());
}

TEST_F(EPModelFixture, GroundHeatExchangerHorizontalTrench_ScalarAccessors_RoundTrip) {
  Model model;
  GroundHeatExchangerHorizontalTrench ghx(model);

  EXPECT_TRUE(ghx.setDesignFlowRate(0.006));
  EXPECT_DOUBLE_EQ(0.006, ghx.designFlowRate());

  EXPECT_TRUE(ghx.setTrenchLengthinPipeAxialDirection(90.0));
  EXPECT_DOUBLE_EQ(90.0, ghx.trenchLengthinPipeAxialDirection());

  EXPECT_TRUE(ghx.setNumberofTrenches(3));
  EXPECT_EQ(3, ghx.numberofTrenches());

  EXPECT_TRUE(ghx.setHorizontalSpacingBetweenPipes(2.5));
  EXPECT_DOUBLE_EQ(2.5, ghx.horizontalSpacingBetweenPipes());

  EXPECT_TRUE(ghx.setPipeInnerDiameter(0.02));
  EXPECT_DOUBLE_EQ(0.02, ghx.pipeInnerDiameter());

  EXPECT_TRUE(ghx.setPipeOuterDiameter(0.03));
  EXPECT_DOUBLE_EQ(0.03, ghx.pipeOuterDiameter());

  EXPECT_TRUE(ghx.setBurialDepth(1.75));
  EXPECT_DOUBLE_EQ(1.75, ghx.burialDepth());

  EXPECT_TRUE(ghx.setSoilThermalConductivity(1.5));
  EXPECT_DOUBLE_EQ(1.5, ghx.soilThermalConductivity());

  EXPECT_TRUE(ghx.setSoilDensity(1000.0));
  EXPECT_DOUBLE_EQ(1000.0, ghx.soilDensity());

  EXPECT_TRUE(ghx.setSoilSpecificHeat(2600.0));
  EXPECT_DOUBLE_EQ(2600.0, ghx.soilSpecificHeat());

  EXPECT_TRUE(ghx.setPipeThermalConductivity(0.42));
  EXPECT_DOUBLE_EQ(0.42, ghx.pipeThermalConductivity());

  EXPECT_TRUE(ghx.setPipeDensity(700.0));
  EXPECT_DOUBLE_EQ(700.0, ghx.pipeDensity());

  EXPECT_TRUE(ghx.setPipeSpecificHeat(2500.0));
  EXPECT_DOUBLE_EQ(2500.0, ghx.pipeSpecificHeat());

  EXPECT_TRUE(ghx.setSoilMoistureContentPercent(35.0));
  EXPECT_DOUBLE_EQ(35.0, ghx.soilMoistureContentPercent());

  EXPECT_TRUE(ghx.setSoilMoistureContentPercentatSaturation(55.0));
  EXPECT_DOUBLE_EQ(55.0, ghx.soilMoistureContentPercentatSaturation());

  EXPECT_TRUE(ghx.setEvapotranspirationGroundCoverParameter(0.5));
  EXPECT_DOUBLE_EQ(0.5, ghx.evapotranspirationGroundCoverParameter());
}
