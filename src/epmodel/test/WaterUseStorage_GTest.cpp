/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/WaterUseStorage.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, WaterUseStorage_DefaultConstructor) {
  Model model;
  WaterUseStorage storage(model);
  EXPECT_EQ(WaterUseStorage::iddObjectType(), storage.iddObject().type());
}

TEST_F(EPModelFixture, WaterUseStorage_ScalarAccessors_RoundTrip) {
  Model model;
  WaterUseStorage storage(model);

  EXPECT_TRUE(storage.setWaterQualitySubcategory("Reclaimed"));
  ASSERT_TRUE(storage.waterQualitySubcategory());
  EXPECT_EQ("Reclaimed", *storage.waterQualitySubcategory());

  EXPECT_TRUE(storage.setMaximumCapacity(1.23));
  ASSERT_TRUE(storage.maximumCapacity());
  EXPECT_DOUBLE_EQ(1.23, *storage.maximumCapacity());

  EXPECT_TRUE(storage.setInitialVolume(0.5));
  ASSERT_TRUE(storage.initialVolume());
  EXPECT_DOUBLE_EQ(0.5, *storage.initialVolume());

  EXPECT_TRUE(storage.setDesignInFlowRate(0.001));
  ASSERT_TRUE(storage.designInFlowRate());
  EXPECT_DOUBLE_EQ(0.001, *storage.designInFlowRate());

  EXPECT_TRUE(storage.setDesignOutFlowRate(0.002));
  ASSERT_TRUE(storage.designOutFlowRate());
  EXPECT_DOUBLE_EQ(0.002, *storage.designOutFlowRate());

  EXPECT_TRUE(storage.setTypeOfSupplyControlledByFloatValve("Mains"));
  ASSERT_TRUE(storage.typeOfSupplyControlledByFloatValve());
  EXPECT_EQ("Mains", *storage.typeOfSupplyControlledByFloatValve());

  EXPECT_TRUE(storage.setFloatValveOnCapacity(0.4));
  ASSERT_TRUE(storage.floatValveOnCapacity());
  EXPECT_DOUBLE_EQ(0.4, *storage.floatValveOnCapacity());

  EXPECT_TRUE(storage.setFloatValveOffCapacity(0.6));
  ASSERT_TRUE(storage.floatValveOffCapacity());
  EXPECT_DOUBLE_EQ(0.6, *storage.floatValveOffCapacity());

  EXPECT_TRUE(storage.setBackupMainsCapacity(0.7));
  ASSERT_TRUE(storage.backupMainsCapacity());
  EXPECT_DOUBLE_EQ(0.7, *storage.backupMainsCapacity());

  EXPECT_TRUE(storage.setWaterThermalMode("ScheduledTemperature"));
  ASSERT_TRUE(storage.waterThermalMode());
  EXPECT_EQ("ScheduledTemperature", *storage.waterThermalMode());

  EXPECT_TRUE(storage.setAmbientTemperatureIndicator("Zone"));
  ASSERT_TRUE(storage.ambientTemperatureIndicator());
  EXPECT_EQ("Zone", *storage.ambientTemperatureIndicator());

  EXPECT_TRUE(storage.setTankSurfaceArea(2.5));
  ASSERT_TRUE(storage.tankSurfaceArea());
  EXPECT_DOUBLE_EQ(2.5, *storage.tankSurfaceArea());

  EXPECT_TRUE(storage.setTankUValue(0.1));
  ASSERT_TRUE(storage.tankUValue());
  EXPECT_DOUBLE_EQ(0.1, *storage.tankUValue());
}
