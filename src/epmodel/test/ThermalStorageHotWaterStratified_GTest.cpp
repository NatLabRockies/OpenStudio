/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/ThermalStorageHotWaterStratified.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ThermalStorageHotWaterStratified_DefaultConstructor) {
  Model model;
  ThermalStorageHotWaterStratified storage(model);
  EXPECT_EQ(ThermalStorageHotWaterStratified::iddObjectType(), storage.iddObject().type());
}

TEST_F(EPModelFixture, ThermalStorageHotWaterStratified_ScalarAccessors_RoundTrip) {
  Model model;
  ThermalStorageHotWaterStratified storage(model);

  EXPECT_TRUE(storage.setTankVolume(1.1));
  EXPECT_DOUBLE_EQ(1.1, storage.tankVolume());

  EXPECT_TRUE(storage.setTankShape("HorizontalCylinder"));
  EXPECT_EQ("HorizontalCylinder", storage.tankShape());
  EXPECT_GE(ThermalStorageHotWaterStratified::tankShapeValues().size(), 1u);
  storage.resetTankShape();
  EXPECT_TRUE(storage.isTankShapeDefaulted());

  EXPECT_TRUE(storage.setTankPerimeter(5.0));
  ASSERT_TRUE(storage.tankPerimeter());
  EXPECT_DOUBLE_EQ(5.0, storage.tankPerimeter().get());
  storage.resetTankPerimeter();
  EXPECT_FALSE(storage.tankPerimeter());

  EXPECT_TRUE(storage.setDeadbandTemperatureDifference(0.3));
  EXPECT_DOUBLE_EQ(0.3, storage.deadbandTemperatureDifference());
  storage.resetDeadbandTemperatureDifference();
  EXPECT_TRUE(storage.isDeadbandTemperatureDifferenceDefaulted());

  EXPECT_TRUE(storage.setUniformSkinLossCoefficientPerUnitAreaToAmbientTemperature(0.35));
  ASSERT_TRUE(storage.uniformSkinLossCoefficientPerUnitAreaToAmbientTemperature());
  EXPECT_DOUBLE_EQ(0.35, storage.uniformSkinLossCoefficientPerUnitAreaToAmbientTemperature().get());
  storage.resetUniformSkinLossCoefficientPerUnitAreaToAmbientTemperature();
  EXPECT_FALSE(storage.uniformSkinLossCoefficientPerUnitAreaToAmbientTemperature());

  EXPECT_TRUE(storage.setUseSideFlowDirectionSchedule("1"));
  ASSERT_TRUE(storage.useSideFlowDirectionSchedule());
  EXPECT_EQ("1", storage.useSideFlowDirectionSchedule().get());
  storage.resetUseSideFlowDirectionSchedule();
  ASSERT_TRUE(storage.useSideFlowDirectionSchedule());
  EXPECT_TRUE(storage.useSideFlowDirectionSchedule()->empty());

  EXPECT_TRUE(storage.setUseSideHeatTransferEffectiveness(0.8));
  EXPECT_DOUBLE_EQ(0.8, storage.useSideHeatTransferEffectiveness());
  storage.resetUseSideHeatTransferEffectiveness();
  EXPECT_TRUE(storage.isUseSideHeatTransferEffectivenessDefaulted());

  EXPECT_TRUE(storage.setUseSideInletHeight(1.2));
  ASSERT_TRUE(storage.useSideInletHeight());
  EXPECT_DOUBLE_EQ(1.2, storage.useSideInletHeight().get());
  storage.autocalculateUseSideInletHeight();
  EXPECT_TRUE(storage.isUseSideInletHeightAutocalculated());
  storage.resetUseSideInletHeight();
  EXPECT_TRUE(storage.isUseSideInletHeightDefaulted());

  EXPECT_TRUE(storage.setUseSideDesignFlowRate(0.08));
  ASSERT_TRUE(storage.useSideDesignFlowRate());
  EXPECT_DOUBLE_EQ(0.08, storage.useSideDesignFlowRate().get());
  storage.autosizeUseSideDesignFlowRate();
  EXPECT_TRUE(storage.isUseSideDesignFlowRateAutosized());
  storage.resetUseSideDesignFlowRate();
  EXPECT_TRUE(storage.isUseSideDesignFlowRateDefaulted());

  EXPECT_TRUE(storage.setSourceSideFlowDirectionSchedule("-1"));
  ASSERT_TRUE(storage.sourceSideFlowDirectionSchedule());
  EXPECT_EQ("-1", storage.sourceSideFlowDirectionSchedule().get());
  storage.resetSourceSideFlowDirectionSchedule();
  ASSERT_TRUE(storage.sourceSideFlowDirectionSchedule());
  EXPECT_TRUE(storage.sourceSideFlowDirectionSchedule()->empty());

  EXPECT_TRUE(storage.setSourceSideHeatTransferEffectiveness(0.6));
  EXPECT_DOUBLE_EQ(0.6, storage.sourceSideHeatTransferEffectiveness());
  storage.resetSourceSideHeatTransferEffectiveness();
  EXPECT_TRUE(storage.isSourceSideHeatTransferEffectivenessDefaulted());

  EXPECT_TRUE(storage.setSourceSideOutletHeight(0.7));
  ASSERT_TRUE(storage.sourceSideOutletHeight());
  EXPECT_DOUBLE_EQ(0.7, storage.sourceSideOutletHeight().get());
  storage.autocalculateSourceSideOutletHeight();
  EXPECT_TRUE(storage.isSourceSideOutletHeightAutocalculated());
  storage.resetSourceSideOutletHeight();
  EXPECT_TRUE(storage.isSourceSideOutletHeightDefaulted());

  EXPECT_TRUE(storage.setSourceSideDesignFlowRate(0.035));
  ASSERT_TRUE(storage.sourceSideDesignFlowRate());
  EXPECT_DOUBLE_EQ(0.035, storage.sourceSideDesignFlowRate().get());
  storage.autosizeSourceSideDesignFlowRate();
  EXPECT_TRUE(storage.isSourceSideDesignFlowRateAutosized());
  storage.resetSourceSideDesignFlowRate();
  EXPECT_TRUE(storage.isSourceSideDesignFlowRateDefaulted());

  EXPECT_TRUE(storage.setTankRecoveryTime(5.5));
  EXPECT_DOUBLE_EQ(5.5, storage.tankRecoveryTime());
  storage.resetTankRecoveryTime();
  EXPECT_TRUE(storage.isTankRecoveryTimeDefaulted());

  EXPECT_TRUE(storage.setInletMode("Seeking"));
  EXPECT_EQ("Seeking", storage.inletMode());
  EXPECT_GE(ThermalStorageHotWaterStratified::inletModeValues().size(), 1u);
  storage.resetInletMode();
  EXPECT_TRUE(storage.isInletModeDefaulted());

  EXPECT_TRUE(storage.setNumberOfNodes(3));
  EXPECT_EQ(3, storage.numberOfNodes());
  storage.resetNumberOfNodes();
  EXPECT_TRUE(storage.isNumberOfNodesDefaulted());

  EXPECT_TRUE(storage.setAdditionalDestratificationConductivity(0.2));
  EXPECT_DOUBLE_EQ(0.2, storage.additionalDestratificationConductivity());
  storage.resetAdditionalDestratificationConductivity();
  EXPECT_TRUE(storage.isAdditionalDestratificationConductivityDefaulted());

  EXPECT_TRUE(storage.setNode10AdditionalLossCoefficient(2.4));
  EXPECT_DOUBLE_EQ(2.4, storage.node10AdditionalLossCoefficient());
  storage.resetNode10AdditionalLossCoefficient();
  EXPECT_TRUE(storage.isNode10AdditionalLossCoefficientDefaulted());

  EXPECT_TRUE(storage.setAmbientTemperatureIndicator("Outdoors"));
  EXPECT_EQ("Outdoors", storage.ambientTemperatureIndicator());
  EXPECT_GE(ThermalStorageHotWaterStratified::ambientTemperatureIndicatorValues().size(), 1u);

  EXPECT_TRUE(storage.setNominalHeatingCapacity(1200.0));
  ASSERT_TRUE(storage.nominalHeatingCapacity());
  EXPECT_DOUBLE_EQ(1200.0, storage.nominalHeatingCapacity().get());
  storage.autosizeNominalHeatingCapacity();
  EXPECT_TRUE(storage.isNominalHeatingCapacityAutosized());
  storage.resetNominalHeatingCapacity();
  EXPECT_TRUE(storage.isNominalHeatingCapacityDefaulted());
}
