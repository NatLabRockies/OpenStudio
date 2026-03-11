/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../SpaceLoad/SpaceInfiltrationDesignFlowRate.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SpaceInfiltrationDesignFlowRate_DefaultConstructor) {
  Model model;
  SpaceInfiltrationDesignFlowRate infiltration(model);

  EXPECT_EQ(SpaceInfiltrationDesignFlowRate::iddObjectType(), infiltration.iddObject().type());
  EXPECT_EQ("Flow/Zone", infiltration.designFlowRateCalculationMethod());
  ASSERT_TRUE(infiltration.designFlowRate());
  EXPECT_DOUBLE_EQ(0.0, infiltration.designFlowRate().get());
  EXPECT_EQ("Outdoor", infiltration.densityBasis());
}

TEST_F(EPModelFixture, SpaceInfiltrationDesignFlowRate_ScalarAccessors_RoundTrip) {
  Model model;
  SpaceInfiltrationDesignFlowRate infiltration(model);

  EXPECT_TRUE(infiltration.setDesignFlowRate(0.5));
  EXPECT_EQ("Flow/Zone", infiltration.designFlowRateCalculationMethod());
  ASSERT_TRUE(infiltration.designFlowRate());
  EXPECT_DOUBLE_EQ(0.5, infiltration.designFlowRate().get());

  EXPECT_TRUE(infiltration.setFlowperSpaceFloorArea(0.3));
  EXPECT_EQ("Flow/Area", infiltration.designFlowRateCalculationMethod());
  ASSERT_TRUE(infiltration.flowperSpaceFloorArea());
  EXPECT_DOUBLE_EQ(0.3, infiltration.flowperSpaceFloorArea().get());

  EXPECT_TRUE(infiltration.setFlowperExteriorWallArea(0.9));
  EXPECT_EQ("Flow/ExteriorWallArea", infiltration.designFlowRateCalculationMethod());
  ASSERT_TRUE(infiltration.flowperExteriorWallArea());
  EXPECT_DOUBLE_EQ(0.9, infiltration.flowperExteriorWallArea().get());

  EXPECT_TRUE(infiltration.setAirChangesperHour(2.1));
  EXPECT_EQ("AirChanges/Hour", infiltration.designFlowRateCalculationMethod());
  ASSERT_TRUE(infiltration.airChangesperHour());
  EXPECT_DOUBLE_EQ(2.1, infiltration.airChangesperHour().get());

  EXPECT_TRUE(infiltration.setConstantTermCoefficient(0.2));
  EXPECT_DOUBLE_EQ(0.2, infiltration.constantTermCoefficient());
  infiltration.resetConstantTermCoefficient();
  EXPECT_TRUE(infiltration.isConstantTermCoefficientDefaulted());

  EXPECT_TRUE(infiltration.setDensityBasis("Standard"));
  EXPECT_EQ("Standard", infiltration.densityBasis());
}
