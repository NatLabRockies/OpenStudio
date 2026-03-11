/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/GroundHeatTransferSlabBldgProps.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, GroundHeatTransferSlabBldgProps_DefaultConstructor) {
  Model model;
  GroundHeatTransferSlabBldgProps object(model);
  EXPECT_EQ(GroundHeatTransferSlabBldgProps::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, GroundHeatTransferSlabBldgProps_ScalarAccessors_RoundTrip) {
  Model model;
  GroundHeatTransferSlabBldgProps object(model);

  EXPECT_TRUE(object.isIyrsNumberofyearstoiterateDefaulted());
  EXPECT_TRUE(object.setIyrsNumberofyearstoiterate(12.0));
  EXPECT_DOUBLE_EQ(12.0, object.iyrsNumberofyearstoiterate());
  EXPECT_FALSE(object.isIyrsNumberofyearstoiterateDefaulted());
  object.resetIyrsNumberofyearstoiterate();
  EXPECT_TRUE(object.isIyrsNumberofyearstoiterateDefaulted());

  EXPECT_FALSE(object.shapeSlabshape());
  EXPECT_TRUE(object.setShapeSlabshape(0.0));
  ASSERT_TRUE(object.shapeSlabshape());
  EXPECT_DOUBLE_EQ(0.0, object.shapeSlabshape().get());
  object.resetShapeSlabshape();
  EXPECT_FALSE(object.shapeSlabshape());

  EXPECT_FALSE(object.hbldgBuildingheight());
  EXPECT_TRUE(object.setHbldgBuildingheight(8.0));
  ASSERT_TRUE(object.hbldgBuildingheight());
  EXPECT_DOUBLE_EQ(8.0, object.hbldgBuildingheight().get());
  object.resetHbldgBuildingheight();
  EXPECT_FALSE(object.hbldgBuildingheight());

  EXPECT_TRUE(object.isTin1JanuaryIndoorAverageTemperatureSetpointDefaulted());
  EXPECT_TRUE(object.setTin1JanuaryIndoorAverageTemperatureSetpoint(21.5));
  EXPECT_DOUBLE_EQ(21.5, object.tin1JanuaryIndoorAverageTemperatureSetpoint());
  EXPECT_FALSE(object.isTin1JanuaryIndoorAverageTemperatureSetpointDefaulted());
  object.resetTin1JanuaryIndoorAverageTemperatureSetpoint();
  EXPECT_TRUE(object.isTin1JanuaryIndoorAverageTemperatureSetpointDefaulted());

  EXPECT_TRUE(object.setTin2FebruaryIndoorAverageTemperatureSetpoint(21.6));
  EXPECT_DOUBLE_EQ(21.6, object.tin2FebruaryIndoorAverageTemperatureSetpoint());
  EXPECT_TRUE(object.setTin3MarchIndoorAverageTemperatureSetpoint(21.7));
  EXPECT_DOUBLE_EQ(21.7, object.tin3MarchIndoorAverageTemperatureSetpoint());
  EXPECT_TRUE(object.setTin4AprilIndoorAverageTemperatureSetpoint(21.8));
  EXPECT_DOUBLE_EQ(21.8, object.tin4AprilIndoorAverageTemperatureSetpoint());
  EXPECT_TRUE(object.setTin5MayIndoorAverageTemperatureSetpoint(21.9));
  EXPECT_DOUBLE_EQ(21.9, object.tin5MayIndoorAverageTemperatureSetpoint());
  EXPECT_TRUE(object.setTin6JuneIndoorAverageTemperatureSetpoint(22.0));
  EXPECT_DOUBLE_EQ(22.0, object.tin6JuneIndoorAverageTemperatureSetpoint());
  EXPECT_TRUE(object.setTin7JulyIndoorAverageTemperatureSetpoint(22.1));
  EXPECT_DOUBLE_EQ(22.1, object.tin7JulyIndoorAverageTemperatureSetpoint());
  EXPECT_TRUE(object.setTin8AugustIndoorAverageTemperatureSetpoint(22.2));
  EXPECT_DOUBLE_EQ(22.2, object.tin8AugustIndoorAverageTemperatureSetpoint());
  EXPECT_TRUE(object.setTin9SeptemberIndoorAverageTemperatureSetpoint(22.3));
  EXPECT_DOUBLE_EQ(22.3, object.tin9SeptemberIndoorAverageTemperatureSetpoint());
  EXPECT_TRUE(object.setTin10OctoberIndoorAverageTemperatureSetpoint(22.4));
  EXPECT_DOUBLE_EQ(22.4, object.tin10OctoberIndoorAverageTemperatureSetpoint());
  EXPECT_TRUE(object.setTin11NovemberIndoorAverageTemperatureSetpoint(22.5));
  EXPECT_DOUBLE_EQ(22.5, object.tin11NovemberIndoorAverageTemperatureSetpoint());
  EXPECT_TRUE(object.setTin12DecemberIndoorAverageTemperatureSetpoint(22.6));
  EXPECT_DOUBLE_EQ(22.6, object.tin12DecemberIndoorAverageTemperatureSetpoint());

  EXPECT_TRUE(object.isTinAmpDailyIndoorsinewavevariationamplitudeDefaulted());
  EXPECT_TRUE(object.setTinAmpDailyIndoorsinewavevariationamplitude(1.1));
  EXPECT_DOUBLE_EQ(1.1, object.tinAmpDailyIndoorsinewavevariationamplitude());
  EXPECT_FALSE(object.isTinAmpDailyIndoorsinewavevariationamplitudeDefaulted());
  object.resetTinAmpDailyIndoorsinewavevariationamplitude();
  EXPECT_TRUE(object.isTinAmpDailyIndoorsinewavevariationamplitudeDefaulted());

  EXPECT_TRUE(object.isConvTolConvergenceToleranceDefaulted());
  EXPECT_TRUE(object.setConvTolConvergenceTolerance(0.05));
  EXPECT_DOUBLE_EQ(0.05, object.convTolConvergenceTolerance());
  EXPECT_FALSE(object.isConvTolConvergenceToleranceDefaulted());
  object.resetConvTolConvergenceTolerance();
  EXPECT_TRUE(object.isConvTolConvergenceToleranceDefaulted());
}
