/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/CoilCoolingWaterDetailedGeometry.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilCoolingWaterDetailedGeometry_DefaultConstructor) {
  Model model;
  CoilCoolingWaterDetailedGeometry coil(model);
  EXPECT_EQ(CoilCoolingWaterDetailedGeometry::iddObjectType(), coil.iddObject().type());
}

TEST_F(EPModelFixture, CoilCoolingWaterDetailedGeometry_ScalarAccessors_RoundTrip) {
  Model model;
  CoilCoolingWaterDetailedGeometry coil(model);

  EXPECT_TRUE(coil.setMaximumWaterFlowRate(0.0012));
  ASSERT_TRUE(coil.maximumWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.0012, coil.maximumWaterFlowRate().get());
  EXPECT_FALSE(coil.isMaximumWaterFlowRateAutosized());
  coil.autosizeMaximumWaterFlowRate();
  EXPECT_TRUE(coil.isMaximumWaterFlowRateAutosized());
  coil.resetMaximumWaterFlowRate();
  EXPECT_FALSE(coil.maximumWaterFlowRate());

  EXPECT_TRUE(coil.isFinThicknessDefaulted());
  EXPECT_TRUE(coil.setFinThickness(0.0016));
  EXPECT_DOUBLE_EQ(0.0016, coil.finThickness());
  EXPECT_FALSE(coil.isFinThicknessDefaulted());
  coil.resetFinThickness();
  EXPECT_TRUE(coil.isFinThicknessDefaulted());

  EXPECT_TRUE(coil.setNumberofTubeRows(5.0));
  EXPECT_DOUBLE_EQ(5.0, coil.numberofTubeRows());
  coil.resetNumberofTubeRows();
  EXPECT_TRUE(coil.isNumberofTubeRowsDefaulted());

  EXPECT_TRUE(coil.setNumberofTubesperRow(36.0));
  ASSERT_TRUE(coil.numberofTubesperRow());
  EXPECT_DOUBLE_EQ(36.0, coil.numberofTubesperRow().get());
  EXPECT_FALSE(coil.isNumberofTubesperRowAutosized());
  coil.autosizeNumberofTubesperRow();
  EXPECT_TRUE(coil.isNumberofTubesperRowAutosized());

  EXPECT_TRUE(coil.setDesignWaterTemperatureDifference(4.0));
  ASSERT_TRUE(coil.designWaterTemperatureDifference());
  EXPECT_DOUBLE_EQ(4.0, coil.designWaterTemperatureDifference().get());
  coil.resetDesignWaterTemperatureDifference();
  EXPECT_FALSE(coil.designWaterTemperatureDifference());

  EXPECT_TRUE(coil.setDesignInletWaterTemperature(6.9));
  ASSERT_TRUE(coil.designInletWaterTemperature());
  EXPECT_DOUBLE_EQ(6.9, coil.designInletWaterTemperature().get());
  EXPECT_FALSE(coil.isDesignInletWaterTemperatureAutosized());
  coil.autosizeDesignInletWaterTemperature();
  EXPECT_TRUE(coil.isDesignInletWaterTemperatureAutosized());
}
