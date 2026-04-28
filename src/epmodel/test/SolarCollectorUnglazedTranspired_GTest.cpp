/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/SolarCollectorUnglazedTranspired.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SolarCollectorUnglazedTranspired_DefaultConstructor) {
  Model model;
  SolarCollectorUnglazedTranspired collector(model);
  EXPECT_EQ(SolarCollectorUnglazedTranspired::iddObjectType(), collector.iddObject().type());
}

TEST_F(EPModelFixture, SolarCollectorUnglazedTranspired_ScalarAccessors_RoundTrip) {
  Model model;
  SolarCollectorUnglazedTranspired collector(model);

  EXPECT_TRUE(collector.setDiameterofPerforationsinCollector(0.001));
  EXPECT_DOUBLE_EQ(0.001, collector.diameterofPerforationsinCollector());

  EXPECT_TRUE(collector.setDistanceBetweenPerforationsinCollector(0.02));
  EXPECT_DOUBLE_EQ(0.02, collector.distanceBetweenPerforationsinCollector());

  EXPECT_TRUE(collector.setThermalEmissivityofCollectorSurface(0.95));
  EXPECT_DOUBLE_EQ(0.95, collector.thermalEmissivityofCollectorSurface());

  EXPECT_TRUE(collector.setSolarAbsorbtivityofCollectorSurface(0.85));
  EXPECT_DOUBLE_EQ(0.85, collector.solarAbsorbtivityofCollectorSurface());

  EXPECT_TRUE(collector.setEffectiveOverallHeightofCollector(3.0));
  EXPECT_DOUBLE_EQ(3.0, collector.effectiveOverallHeightofCollector());

  EXPECT_TRUE(collector.setEffectiveGapThicknessofPlenumBehindCollector(0.1));
  EXPECT_DOUBLE_EQ(0.1, collector.effectiveGapThicknessofPlenumBehindCollector());

  EXPECT_TRUE(collector.setEffectiveCrossSectionAreaofPlenumBehindCollector(4.5));
  EXPECT_DOUBLE_EQ(4.5, collector.effectiveCrossSectionAreaofPlenumBehindCollector());

  EXPECT_FALSE(collector.holeLayoutPatternforPitchValues().empty());
  EXPECT_TRUE(collector.setHoleLayoutPatternforPitch("Triangle"));
  EXPECT_EQ("Triangle", collector.holeLayoutPatternforPitch());
  EXPECT_FALSE(collector.isHoleLayoutPatternforPitchDefaulted());
  collector.resetHoleLayoutPatternforPitch();
  EXPECT_TRUE(collector.isHoleLayoutPatternforPitchDefaulted());

  EXPECT_FALSE(collector.heatExchangeEffectivenessCorrelationValues().empty());
  EXPECT_TRUE(collector.setHeatExchangeEffectivenessCorrelation("Kutscher1994"));
  EXPECT_EQ("Kutscher1994", collector.heatExchangeEffectivenessCorrelation());
  EXPECT_FALSE(collector.isHeatExchangeEffectivenessCorrelationDefaulted());
  collector.resetHeatExchangeEffectivenessCorrelation();
  EXPECT_TRUE(collector.isHeatExchangeEffectivenessCorrelationDefaulted());

  EXPECT_TRUE(collector.isRatioofActualCollectorSurfaceAreatoProjectedSurfaceAreaDefaulted());
  EXPECT_TRUE(collector.setRatioofActualCollectorSurfaceAreatoProjectedSurfaceArea(1.3));
  EXPECT_DOUBLE_EQ(1.3, collector.ratioofActualCollectorSurfaceAreatoProjectedSurfaceArea());
  collector.resetRatioofActualCollectorSurfaceAreatoProjectedSurfaceArea();
  EXPECT_TRUE(collector.isRatioofActualCollectorSurfaceAreatoProjectedSurfaceAreaDefaulted());

  EXPECT_FALSE(collector.roughnessofCollectorValues().empty());
  EXPECT_TRUE(collector.setRoughnessofCollector("Rough"));
  EXPECT_EQ("Rough", collector.roughnessofCollector());

  EXPECT_FALSE(collector.collectorThickness());
  EXPECT_TRUE(collector.setCollectorThickness(0.002));
  ASSERT_TRUE(collector.collectorThickness());
  EXPECT_DOUBLE_EQ(0.002, collector.collectorThickness().get());
  collector.resetCollectorThickness();
  EXPECT_FALSE(collector.collectorThickness());

  EXPECT_TRUE(collector.isEffectivenessforPerforationswithRespecttoWindDefaulted());
  EXPECT_TRUE(collector.setEffectivenessforPerforationswithRespecttoWind(0.33));
  EXPECT_DOUBLE_EQ(0.33, collector.effectivenessforPerforationswithRespecttoWind());
  collector.resetEffectivenessforPerforationswithRespecttoWind();
  EXPECT_TRUE(collector.isEffectivenessforPerforationswithRespecttoWindDefaulted());

  EXPECT_TRUE(collector.isDischargeCoefficientforOpeningswithRespecttoBuoyancyDrivenFlowDefaulted());
  EXPECT_TRUE(collector.setDischargeCoefficientforOpeningswithRespecttoBuoyancyDrivenFlow(0.78));
  EXPECT_DOUBLE_EQ(0.78, collector.dischargeCoefficientforOpeningswithRespecttoBuoyancyDrivenFlow());
  collector.resetDischargeCoefficientforOpeningswithRespecttoBuoyancyDrivenFlow();
  EXPECT_TRUE(collector.isDischargeCoefficientforOpeningswithRespecttoBuoyancyDrivenFlowDefaulted());
}
