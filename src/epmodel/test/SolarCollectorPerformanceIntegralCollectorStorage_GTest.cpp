/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/SolarCollectorPerformanceIntegralCollectorStorage.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SolarCollectorPerformanceIntegralCollectorStorage_DefaultConstructor) {
  Model model;
  SolarCollectorPerformanceIntegralCollectorStorage object(model);
  EXPECT_EQ(SolarCollectorPerformanceIntegralCollectorStorage::iddObjectType(), object.iddObject().type());
  EXPECT_FALSE(object.nameString().empty());
}

TEST_F(EPModelFixture, SolarCollectorPerformanceIntegralCollectorStorage_ScalarAccessors_RoundTrip) {
  Model model;
  SolarCollectorPerformanceIntegralCollectorStorage object(model);

  const auto iCSCollectorTypeValues = SolarCollectorPerformanceIntegralCollectorStorage::iCSCollectorTypeValues();
  EXPECT_FALSE(iCSCollectorTypeValues.empty());
  EXPECT_TRUE(object.setICSCollectorType(iCSCollectorTypeValues.front()));
  EXPECT_EQ(iCSCollectorTypeValues.front(), object.iCSCollectorType());

  EXPECT_TRUE(object.setGrossArea(2.98));
  EXPECT_DOUBLE_EQ(2.98, object.grossArea());

  EXPECT_TRUE(object.setCollectorWaterVolume(0.1862));
  EXPECT_DOUBLE_EQ(0.1862, object.collectorWaterVolume());

  EXPECT_TRUE(object.setBottomHeatLossConductance(0.40));
  EXPECT_DOUBLE_EQ(0.40, object.bottomHeatLossConductance());

  EXPECT_TRUE(object.setSideHeatLossConductance(0.50));
  EXPECT_DOUBLE_EQ(0.50, object.sideHeatLossConductance());

  EXPECT_TRUE(object.setAspectRatio(0.8));
  EXPECT_DOUBLE_EQ(0.8, object.aspectRatio());

  EXPECT_TRUE(object.setCollectorSideHeight(0.21));
  EXPECT_DOUBLE_EQ(0.21, object.collectorSideHeight());

  EXPECT_TRUE(object.setThermalMassOfAbsorberPlate(385.0));
  EXPECT_DOUBLE_EQ(385.0, object.thermalMassOfAbsorberPlate());

  EXPECT_TRUE(object.setNumberOfCovers(1));
  EXPECT_EQ(1, object.numberOfCovers());

  EXPECT_TRUE(object.setCoverSpacing(0.03));
  EXPECT_DOUBLE_EQ(0.03, object.coverSpacing());

  EXPECT_TRUE(object.setRefractiveIndexOfOuterCover(1.526));
  EXPECT_DOUBLE_EQ(1.526, object.refractiveIndexOfOuterCover());

  EXPECT_TRUE(object.setExtinctionCoefficientTimesThicknessOfOuterCover(0.045));
  EXPECT_DOUBLE_EQ(0.045, object.extinctionCoefficientTimesThicknessOfOuterCover());

  EXPECT_TRUE(object.setEmissivityOfOuterCover(0.86));
  EXPECT_DOUBLE_EQ(0.86, object.emissivityOfOuterCover());

  EXPECT_TRUE(object.setRefractiveIndexOfInnerCover(1.37));
  EXPECT_DOUBLE_EQ(1.37, object.refractiveIndexOfInnerCover());

  EXPECT_TRUE(object.setExtinctionCoefficientTimesThicknessOfTheInnerCover(0.012));
  EXPECT_DOUBLE_EQ(0.012, object.extinctionCoefficientTimesThicknessOfTheInnerCover());

  EXPECT_TRUE(object.setEmissivityOfInnerCover(0.89));
  EXPECT_DOUBLE_EQ(0.89, object.emissivityOfInnerCover());

  EXPECT_TRUE(object.setAbsorptanceOfAbsorberPlate(0.96));
  EXPECT_DOUBLE_EQ(0.96, object.absorptanceOfAbsorberPlate());

  EXPECT_TRUE(object.setEmissivityOfAbsorberPlate(0.12));
  EXPECT_DOUBLE_EQ(0.12, object.emissivityOfAbsorberPlate());

  object.resetICSCollectorType();
  EXPECT_TRUE(object.isICSCollectorTypeDefaulted());

  object.resetBottomHeatLossConductance();
  EXPECT_TRUE(object.isBottomHeatLossConductanceDefaulted());

  object.resetSideHeatLossConductance();
  EXPECT_TRUE(object.isSideHeatLossConductanceDefaulted());

  object.resetAspectRatio();
  EXPECT_TRUE(object.isAspectRatioDefaulted());

  object.resetCollectorSideHeight();
  EXPECT_TRUE(object.isCollectorSideHeightDefaulted());

  object.resetThermalMassOfAbsorberPlate();
  EXPECT_TRUE(object.isThermalMassOfAbsorberPlateDefaulted());

  object.resetNumberOfCovers();
  EXPECT_TRUE(object.isNumberOfCoversDefaulted());

  object.resetCoverSpacing();
  EXPECT_TRUE(object.isCoverSpacingDefaulted());

  object.resetRefractiveIndexOfOuterCover();
  EXPECT_TRUE(object.isRefractiveIndexOfOuterCoverDefaulted());

  object.resetExtinctionCoefficientTimesThicknessOfOuterCover();
  EXPECT_TRUE(object.isExtinctionCoefficientTimesThicknessOfOuterCoverDefaulted());

  object.resetEmissivityOfOuterCover();
  EXPECT_TRUE(object.isEmissivityOfOuterCoverDefaulted());

  object.resetRefractiveIndexOfInnerCover();
  EXPECT_TRUE(object.isRefractiveIndexOfInnerCoverDefaulted());

  object.resetExtinctionCoefficientTimesThicknessOfTheInnerCover();
  EXPECT_TRUE(object.isExtinctionCoefficientTimesThicknessOfTheInnerCoverDefaulted());

  object.resetEmissivityOfInnerCover();
  EXPECT_TRUE(object.isEmissivityOfInnerCoverDefaulted());

  object.resetAbsorptanceOfAbsorberPlate();
  EXPECT_TRUE(object.isAbsorptanceOfAbsorberPlateDefaulted());

  object.resetEmissivityOfAbsorberPlate();
  EXPECT_TRUE(object.isEmissivityOfAbsorberPlateDefaulted());
}
