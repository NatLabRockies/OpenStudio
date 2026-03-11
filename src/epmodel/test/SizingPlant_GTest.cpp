/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"

#include "../Loop/PlantLoop.hpp"
#include "../ModelObject/SizingPlant.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SizingPlant_DefaultConstructor) {
  Model model;
  PlantLoop plantLoop(model);
  SizingPlant sizingPlant(model, plantLoop);

  EXPECT_EQ(SizingPlant::iddObjectType(), sizingPlant.iddObject().type());

  EXPECT_EQ("Heating", sizingPlant.loopType());
  EXPECT_DOUBLE_EQ(82.0, sizingPlant.designLoopExitTemperature());
  EXPECT_DOUBLE_EQ(11.0, sizingPlant.loopDesignTemperatureDifference());
  EXPECT_EQ("NonCoincident", sizingPlant.sizingOption());
  EXPECT_EQ(1, sizingPlant.zoneTimestepsinAveragingWindow());
  EXPECT_EQ("None", sizingPlant.coincidentSizingFactorMode());
}

TEST_F(EPModelFixture, SizingPlant_ScalarAccessors_RoundTrip) {
  Model model;
  PlantLoop plantLoop(model);
  SizingPlant sizingPlant(model, plantLoop);

  EXPECT_EQ(std::vector<std::string>({"Heating", "Cooling", "Condenser", "Steam"}), SizingPlant::loopTypeValues());
  EXPECT_EQ(std::vector<std::string>({"Coincident", "NonCoincident"}), SizingPlant::sizingOptionValues());
  EXPECT_EQ(std::vector<std::string>({"None", "GlobalHeatingSizingFactor", "GlobalCoolingSizingFactor", "LoopComponentSizingFactor"}),
            SizingPlant::coincidentSizingFactorModeValues());

  EXPECT_TRUE(sizingPlant.setLoopType("Cooling"));
  EXPECT_EQ("Cooling", sizingPlant.loopType());
  EXPECT_FALSE(sizingPlant.setLoopType("NotARealLoopType"));

  EXPECT_TRUE(sizingPlant.setDesignLoopExitTemperature(7.22));
  EXPECT_DOUBLE_EQ(7.22, sizingPlant.designLoopExitTemperature());

  EXPECT_TRUE(sizingPlant.setLoopDesignTemperatureDifference(6.67));
  EXPECT_DOUBLE_EQ(6.67, sizingPlant.loopDesignTemperatureDifference());
  EXPECT_FALSE(sizingPlant.setLoopDesignTemperatureDifference(0.0));

  EXPECT_TRUE(sizingPlant.setSizingOption("Coincident"));
  EXPECT_EQ("Coincident", sizingPlant.sizingOption());
  EXPECT_FALSE(sizingPlant.setSizingOption("InvalidSizingOption"));

  EXPECT_TRUE(sizingPlant.setZoneTimestepsinAveragingWindow(6));
  EXPECT_EQ(6, sizingPlant.zoneTimestepsinAveragingWindow());
  EXPECT_FALSE(sizingPlant.setZoneTimestepsinAveragingWindow(0));

  EXPECT_TRUE(sizingPlant.setCoincidentSizingFactorMode("GlobalCoolingSizingFactor"));
  EXPECT_EQ("GlobalCoolingSizingFactor", sizingPlant.coincidentSizingFactorMode());
  EXPECT_FALSE(sizingPlant.setCoincidentSizingFactorMode("InvalidCoincidentSizingFactorMode"));
}
