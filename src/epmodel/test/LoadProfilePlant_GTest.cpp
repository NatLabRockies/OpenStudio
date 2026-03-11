/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../StraightComponent/LoadProfilePlant.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, LoadProfilePlant_DefaultConstructor) {
  Model model;
  LoadProfilePlant loadProfilePlant(model);
  EXPECT_EQ(LoadProfilePlant::iddObjectType(), loadProfilePlant.iddObject().type());
  EXPECT_FALSE(loadProfilePlant.nameString().empty());
}

TEST_F(EPModelFixture, LoadProfilePlant_ScalarAccessors_RoundTrip) {
  Model model;
  LoadProfilePlant loadProfilePlant(model);

  EXPECT_TRUE(loadProfilePlant.setPeakFlowRate(0.0023));
  EXPECT_DOUBLE_EQ(0.0023, loadProfilePlant.peakFlowRate());

  EXPECT_EQ(std::vector<std::string>({"Water", "Steam"}), LoadProfilePlant::plantLoopFluidTypeValues());
  EXPECT_TRUE(loadProfilePlant.isPlantLoopFluidTypeDefaulted());
  EXPECT_TRUE(loadProfilePlant.setPlantLoopFluidType("Steam"));
  EXPECT_EQ("Steam", loadProfilePlant.plantLoopFluidType());
  EXPECT_FALSE(loadProfilePlant.isPlantLoopFluidTypeDefaulted());
  loadProfilePlant.resetPlantLoopFluidType();
  EXPECT_TRUE(loadProfilePlant.isPlantLoopFluidTypeDefaulted());
  EXPECT_EQ("Water", loadProfilePlant.plantLoopFluidType());

  EXPECT_TRUE(loadProfilePlant.isDegreeofSubCoolingDefaulted());
  EXPECT_DOUBLE_EQ(5.0, loadProfilePlant.degreeofSubCooling());
  EXPECT_TRUE(loadProfilePlant.setDegreeofSubCooling(6.0));
  EXPECT_DOUBLE_EQ(6.0, loadProfilePlant.degreeofSubCooling());
  EXPECT_FALSE(loadProfilePlant.isDegreeofSubCoolingDefaulted());
  EXPECT_FALSE(loadProfilePlant.setDegreeofSubCooling(0.5));
  loadProfilePlant.resetDegreeofSubCooling();
  EXPECT_TRUE(loadProfilePlant.isDegreeofSubCoolingDefaulted());
  EXPECT_DOUBLE_EQ(5.0, loadProfilePlant.degreeofSubCooling());

  EXPECT_TRUE(loadProfilePlant.isDegreeofLoopSubCoolingDefaulted());
  EXPECT_DOUBLE_EQ(20.0, loadProfilePlant.degreeofLoopSubCooling());
  EXPECT_TRUE(loadProfilePlant.setDegreeofLoopSubCooling(21.0));
  EXPECT_DOUBLE_EQ(21.0, loadProfilePlant.degreeofLoopSubCooling());
  EXPECT_FALSE(loadProfilePlant.isDegreeofLoopSubCoolingDefaulted());
  EXPECT_FALSE(loadProfilePlant.setDegreeofLoopSubCooling(5.0));
  loadProfilePlant.resetDegreeofLoopSubCooling();
  EXPECT_TRUE(loadProfilePlant.isDegreeofLoopSubCoolingDefaulted());
  EXPECT_DOUBLE_EQ(20.0, loadProfilePlant.degreeofLoopSubCooling());
}
