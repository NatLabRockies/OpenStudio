/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/GroundHeatExchangerVerticalSizingRectangle.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, GroundHeatExchangerVerticalSizingRectangle_DefaultConstructor) {
  Model model;
  GroundHeatExchangerVerticalSizingRectangle ghx(model);
  EXPECT_EQ(GroundHeatExchangerVerticalSizingRectangle::iddObjectType(), ghx.iddObject().type());
  EXPECT_FALSE(ghx.nameString().empty());

  EXPECT_DOUBLE_EQ(0.0005, ghx.designFlowRatePerBorehole());
  EXPECT_TRUE(ghx.isDesignFlowRatePerBoreholeDefaulted());

  EXPECT_DOUBLE_EQ(100.0, ghx.availableBoreholeFieldLength());
  EXPECT_DOUBLE_EQ(100.0, ghx.availableBoreholeFieldWidth());
  EXPECT_DOUBLE_EQ(100.0, ghx.maximumNumberofBoreholes());

  EXPECT_DOUBLE_EQ(4.0, ghx.minimumBoreholeSpacing());
  EXPECT_TRUE(ghx.isMinimumBoreholeSpacingDefaulted());
  EXPECT_DOUBLE_EQ(6.0, ghx.maximumBoreholeSpacing());
  EXPECT_TRUE(ghx.isMaximumBoreholeSpacingDefaulted());
  EXPECT_DOUBLE_EQ(60.0, ghx.minimumBoreholeVerticalLength());
  EXPECT_TRUE(ghx.isMinimumBoreholeVerticalLengthDefaulted());
  EXPECT_DOUBLE_EQ(135.0, ghx.maximumBoreholeVerticalLength());
  EXPECT_TRUE(ghx.isMaximumBoreholeVerticalLengthDefaulted());
  EXPECT_DOUBLE_EQ(5.0, ghx.minimumExitingFluidTemperatureforSizing());
  EXPECT_TRUE(ghx.isMinimumExitingFluidTemperatureforSizingDefaulted());
  EXPECT_DOUBLE_EQ(35.0, ghx.maximumExitingFluidTemperatureforSizing());
  EXPECT_TRUE(ghx.isMaximumExitingFluidTemperatureforSizingDefaulted());
}

TEST_F(EPModelFixture, GroundHeatExchangerVerticalSizingRectangle_ScalarAccessors_RoundTrip) {
  Model model;
  GroundHeatExchangerVerticalSizingRectangle ghx(model);

  EXPECT_TRUE(ghx.setDesignFlowRatePerBorehole(0.001));
  EXPECT_DOUBLE_EQ(0.001, ghx.designFlowRatePerBorehole());
  EXPECT_FALSE(ghx.isDesignFlowRatePerBoreholeDefaulted());
  ghx.resetDesignFlowRatePerBorehole();
  EXPECT_TRUE(ghx.isDesignFlowRatePerBoreholeDefaulted());
  EXPECT_DOUBLE_EQ(0.0005, ghx.designFlowRatePerBorehole());

  EXPECT_TRUE(ghx.setAvailableBoreholeFieldLength(180.0));
  EXPECT_DOUBLE_EQ(180.0, ghx.availableBoreholeFieldLength());

  EXPECT_TRUE(ghx.setAvailableBoreholeFieldWidth(95.0));
  EXPECT_DOUBLE_EQ(95.0, ghx.availableBoreholeFieldWidth());

  EXPECT_TRUE(ghx.setMaximumNumberofBoreholes(240.0));
  EXPECT_DOUBLE_EQ(240.0, ghx.maximumNumberofBoreholes());

  EXPECT_TRUE(ghx.setMinimumBoreholeSpacing(4.5));
  EXPECT_DOUBLE_EQ(4.5, ghx.minimumBoreholeSpacing());
  EXPECT_FALSE(ghx.isMinimumBoreholeSpacingDefaulted());
  ghx.resetMinimumBoreholeSpacing();
  EXPECT_TRUE(ghx.isMinimumBoreholeSpacingDefaulted());
  EXPECT_DOUBLE_EQ(4.0, ghx.minimumBoreholeSpacing());

  EXPECT_TRUE(ghx.setMaximumBoreholeSpacing(8.0));
  EXPECT_DOUBLE_EQ(8.0, ghx.maximumBoreholeSpacing());
  EXPECT_FALSE(ghx.isMaximumBoreholeSpacingDefaulted());
  ghx.resetMaximumBoreholeSpacing();
  EXPECT_TRUE(ghx.isMaximumBoreholeSpacingDefaulted());
  EXPECT_DOUBLE_EQ(6.0, ghx.maximumBoreholeSpacing());

  EXPECT_TRUE(ghx.setMinimumBoreholeVerticalLength(70.0));
  EXPECT_DOUBLE_EQ(70.0, ghx.minimumBoreholeVerticalLength());
  EXPECT_FALSE(ghx.isMinimumBoreholeVerticalLengthDefaulted());
  ghx.resetMinimumBoreholeVerticalLength();
  EXPECT_TRUE(ghx.isMinimumBoreholeVerticalLengthDefaulted());
  EXPECT_DOUBLE_EQ(60.0, ghx.minimumBoreholeVerticalLength());

  EXPECT_TRUE(ghx.setMaximumBoreholeVerticalLength(150.0));
  EXPECT_DOUBLE_EQ(150.0, ghx.maximumBoreholeVerticalLength());
  EXPECT_FALSE(ghx.isMaximumBoreholeVerticalLengthDefaulted());
  ghx.resetMaximumBoreholeVerticalLength();
  EXPECT_TRUE(ghx.isMaximumBoreholeVerticalLengthDefaulted());
  EXPECT_DOUBLE_EQ(135.0, ghx.maximumBoreholeVerticalLength());

  EXPECT_TRUE(ghx.setMinimumExitingFluidTemperatureforSizing(6.0));
  EXPECT_DOUBLE_EQ(6.0, ghx.minimumExitingFluidTemperatureforSizing());
  EXPECT_FALSE(ghx.isMinimumExitingFluidTemperatureforSizingDefaulted());
  ghx.resetMinimumExitingFluidTemperatureforSizing();
  EXPECT_TRUE(ghx.isMinimumExitingFluidTemperatureforSizingDefaulted());
  EXPECT_DOUBLE_EQ(5.0, ghx.minimumExitingFluidTemperatureforSizing());

  EXPECT_TRUE(ghx.setMaximumExitingFluidTemperatureforSizing(33.0));
  EXPECT_DOUBLE_EQ(33.0, ghx.maximumExitingFluidTemperatureforSizing());
  EXPECT_FALSE(ghx.isMaximumExitingFluidTemperatureforSizingDefaulted());
  ghx.resetMaximumExitingFluidTemperatureforSizing();
  EXPECT_TRUE(ghx.isMaximumExitingFluidTemperatureforSizingDefaulted());
  EXPECT_DOUBLE_EQ(35.0, ghx.maximumExitingFluidTemperatureforSizing());

  EXPECT_FALSE(ghx.setDesignFlowRatePerBorehole(0.0));
  EXPECT_FALSE(ghx.setAvailableBoreholeFieldLength(0.0));
}
