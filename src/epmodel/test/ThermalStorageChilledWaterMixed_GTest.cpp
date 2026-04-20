/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/ThermalStorageChilledWaterMixed.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ThermalStorageChilledWaterMixed_DefaultConstructor) {
  Model model;
  ThermalStorageChilledWaterMixed storage(model);
  EXPECT_EQ(ThermalStorageChilledWaterMixed::iddObjectType(), storage.iddObject().type());
}

TEST_F(EPModelFixture, ThermalStorageChilledWaterMixed_ScalarAccessors_RoundTrip) {
  Model model;
  ThermalStorageChilledWaterMixed storage(model);

  EXPECT_TRUE(storage.setAmbientTemperatureIndicator("Schedule"));
  EXPECT_EQ("Schedule", storage.ambientTemperatureIndicator());
  EXPECT_GE(ThermalStorageChilledWaterMixed::ambientTemperatureIndicatorValues().size(), 1u);

  EXPECT_TRUE(storage.setTankVolume(0.25));
  EXPECT_DOUBLE_EQ(0.25, storage.tankVolume());
  storage.resetTankVolume();
  EXPECT_TRUE(storage.isTankVolumeDefaulted());

  EXPECT_TRUE(storage.setDeadbandTemperatureDifference(0.6));
  EXPECT_DOUBLE_EQ(0.6, storage.deadbandTemperatureDifference());
  storage.resetDeadbandTemperatureDifference();
  EXPECT_TRUE(storage.isDeadbandTemperatureDifferenceDefaulted());

  EXPECT_TRUE(storage.setMinimumTemperatureLimit(4.0));
  ASSERT_TRUE(storage.minimumTemperatureLimit());
  EXPECT_DOUBLE_EQ(4.0, storage.minimumTemperatureLimit().get());
  storage.resetMinimumTemperatureLimit();
  EXPECT_FALSE(storage.minimumTemperatureLimit());

  EXPECT_TRUE(storage.setNominalCoolingCapacity(5000.0));
  ASSERT_TRUE(storage.nominalCoolingCapacity());
  EXPECT_DOUBLE_EQ(5000.0, storage.nominalCoolingCapacity().get());
  storage.resetNominalCoolingCapacity();
  EXPECT_FALSE(storage.nominalCoolingCapacity());

  EXPECT_TRUE(storage.setHeatGainCoefficientFromAmbientTemperature(12.5));
  ASSERT_TRUE(storage.heatGainCoefficientFromAmbientTemperature());
  EXPECT_DOUBLE_EQ(12.5, storage.heatGainCoefficientFromAmbientTemperature().get());
  storage.resetHeatGainCoefficientFromAmbientTemperature();
  EXPECT_FALSE(storage.heatGainCoefficientFromAmbientTemperature());

  EXPECT_TRUE(storage.setUseSideHeatTransferEffectiveness(0.75));
  EXPECT_DOUBLE_EQ(0.75, storage.useSideHeatTransferEffectiveness());
  storage.resetUseSideHeatTransferEffectiveness();
  EXPECT_TRUE(storage.isUseSideHeatTransferEffectivenessDefaulted());

  EXPECT_TRUE(storage.setUseSideDesignFlowRate(0.05));
  ASSERT_TRUE(storage.useSideDesignFlowRate());
  EXPECT_DOUBLE_EQ(0.05, storage.useSideDesignFlowRate().get());
  storage.autosizeUseSideDesignFlowRate();
  EXPECT_TRUE(storage.isUseSideDesignFlowRateAutosized());
  storage.resetUseSideDesignFlowRate();
  EXPECT_TRUE(storage.isUseSideDesignFlowRateDefaulted());

  EXPECT_TRUE(storage.setSourceSideHeatTransferEffectiveness(0.85));
  EXPECT_DOUBLE_EQ(0.85, storage.sourceSideHeatTransferEffectiveness());
  storage.resetSourceSideHeatTransferEffectiveness();
  EXPECT_TRUE(storage.isSourceSideHeatTransferEffectivenessDefaulted());

  EXPECT_TRUE(storage.setSourceSideDesignFlowRate(0.025));
  ASSERT_TRUE(storage.sourceSideDesignFlowRate());
  EXPECT_DOUBLE_EQ(0.025, storage.sourceSideDesignFlowRate().get());
  storage.autosizeSourceSideDesignFlowRate();
  EXPECT_TRUE(storage.isSourceSideDesignFlowRateAutosized());
  storage.resetSourceSideDesignFlowRate();
  EXPECT_TRUE(storage.isSourceSideDesignFlowRateDefaulted());

  EXPECT_TRUE(storage.setTankRecoveryTime(3.0));
  EXPECT_DOUBLE_EQ(3.0, storage.tankRecoveryTime());
  storage.resetTankRecoveryTime();
  EXPECT_TRUE(storage.isTankRecoveryTimeDefaulted());
}
