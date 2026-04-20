/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/ThermalStoragePCM.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ThermalStoragePCM_DefaultConstructor) {
  Model model;
  ThermalStoragePCM storage(model);
  EXPECT_EQ(ThermalStoragePCM::iddObjectType(), storage.iddObject().type());
}

TEST_F(EPModelFixture, ThermalStoragePCM_ScalarAccessors_RoundTrip) {
  Model model;
  ThermalStoragePCM storage(model);

  EXPECT_TRUE(storage.setTankCapacity(5000.0));
  ASSERT_TRUE(storage.tankCapacity());
  EXPECT_DOUBLE_EQ(5000.0, storage.tankCapacity().get());
  storage.autosizeTankCapacity();
  EXPECT_TRUE(storage.isTankCapacityAutosized());

  EXPECT_TRUE(storage.isHeatLossRateDefaulted());
  EXPECT_TRUE(storage.setHeatLossRate(250.0));
  ASSERT_TRUE(storage.heatLossRate());
  EXPECT_DOUBLE_EQ(250.0, storage.heatLossRate().get());
  storage.resetHeatLossRate();
  EXPECT_TRUE(storage.isHeatLossRateDefaulted());

  EXPECT_TRUE(storage.setUseSideDesignFlowRate(0.005));
  ASSERT_TRUE(storage.useSideDesignFlowRate());
  EXPECT_DOUBLE_EQ(0.005, storage.useSideDesignFlowRate().get());
  storage.autosizeUseSideDesignFlowRate();
  EXPECT_TRUE(storage.isUseSideDesignFlowRateAutosized());

  EXPECT_TRUE(storage.setPlantSideDesignFlowRate(0.006));
  ASSERT_TRUE(storage.plantSideDesignFlowRate());
  EXPECT_DOUBLE_EQ(0.006, storage.plantSideDesignFlowRate().get());
  storage.autosizePlantSideDesignFlowRate();
  EXPECT_TRUE(storage.isPlantSideDesignFlowRateAutosized());
}
