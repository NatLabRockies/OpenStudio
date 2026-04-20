/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/MaterialPropertyHeatAndMoistureTransferSettings.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, MaterialPropertyHeatAndMoistureTransferSettings_DefaultConstructor) {
  Model model;
  MaterialPropertyHeatAndMoistureTransferSettings object(model);
  EXPECT_EQ(MaterialPropertyHeatAndMoistureTransferSettings::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, MaterialPropertyHeatAndMoistureTransferSettings_ScalarAccessors_RoundTrip) {
  Model model;
  MaterialPropertyHeatAndMoistureTransferSettings object(model);

  EXPECT_TRUE(object.setPorosity(0.35));
  EXPECT_DOUBLE_EQ(0.35, object.porosity());

  EXPECT_TRUE(object.isInitialWaterContentRatioDefaulted());
  EXPECT_TRUE(object.setInitialWaterContentRatio(0.31));
  EXPECT_FALSE(object.isInitialWaterContentRatioDefaulted());
  EXPECT_DOUBLE_EQ(0.31, object.initialWaterContentRatio());

  object.resetInitialWaterContentRatio();
  EXPECT_TRUE(object.isInitialWaterContentRatioDefaulted());
  EXPECT_DOUBLE_EQ(0.2, object.initialWaterContentRatio());
}
