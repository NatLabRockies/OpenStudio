/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/AirflowNetworkDistributionComponentDuct.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirflowNetworkDistributionComponentDuct_DefaultConstructor) {
  Model model;
  AirflowNetworkDistributionComponentDuct duct(model);
  EXPECT_EQ(AirflowNetworkDistributionComponentDuct::iddObjectType(), duct.iddObject().type());
}

TEST_F(EPModelFixture, AirflowNetworkDistributionComponentDuct_ScalarAccessors_RoundTrip) {
  Model model;
  AirflowNetworkDistributionComponentDuct duct(model);

  EXPECT_TRUE(duct.setDuctLength(2.5));
  EXPECT_DOUBLE_EQ(2.5, duct.ductLength());

  EXPECT_TRUE(duct.setHydraulicDiameter(0.48));
  EXPECT_DOUBLE_EQ(0.48, duct.hydraulicDiameter());

  EXPECT_TRUE(duct.setCrossSectionArea(0.17));
  EXPECT_DOUBLE_EQ(0.17, duct.crossSectionArea());

  EXPECT_TRUE(duct.isSurfaceRoughnessDefaulted());
  EXPECT_TRUE(duct.setSurfaceRoughness(0.0012));
  EXPECT_DOUBLE_EQ(0.0012, duct.surfaceRoughness());
  EXPECT_FALSE(duct.isSurfaceRoughnessDefaulted());
  duct.resetSurfaceRoughness();
  EXPECT_TRUE(duct.isSurfaceRoughnessDefaulted());

  EXPECT_TRUE(duct.isCoefficientforLocalDynamicLossDuetoFittingDefaulted());
  EXPECT_TRUE(duct.setCoefficientforLocalDynamicLossDuetoFitting(0.27));
  EXPECT_DOUBLE_EQ(0.27, duct.coefficientforLocalDynamicLossDuetoFitting());
  EXPECT_FALSE(duct.isCoefficientforLocalDynamicLossDuetoFittingDefaulted());
  duct.resetCoefficientforLocalDynamicLossDuetoFitting();
  EXPECT_TRUE(duct.isCoefficientforLocalDynamicLossDuetoFittingDefaulted());

  EXPECT_TRUE(duct.isHeatTransmittanceCoefficientUFactorforDuctWallConstructionDefaulted());
  EXPECT_TRUE(duct.setHeatTransmittanceCoefficientUFactorforDuctWallConstruction(0.88));
  EXPECT_DOUBLE_EQ(0.88, duct.heatTransmittanceCoefficientUFactorforDuctWallConstruction());
  EXPECT_FALSE(duct.isHeatTransmittanceCoefficientUFactorforDuctWallConstructionDefaulted());
  duct.resetHeatTransmittanceCoefficientUFactorforDuctWallConstruction();
  EXPECT_TRUE(duct.isHeatTransmittanceCoefficientUFactorforDuctWallConstructionDefaulted());

  EXPECT_TRUE(duct.isOverallMoistureTransmittanceCoefficientfromAirtoAirDefaulted());
  EXPECT_TRUE(duct.setOverallMoistureTransmittanceCoefficientfromAirtoAir(0.0023));
  EXPECT_DOUBLE_EQ(0.0023, duct.overallMoistureTransmittanceCoefficientfromAirtoAir());
  EXPECT_FALSE(duct.isOverallMoistureTransmittanceCoefficientfromAirtoAirDefaulted());
  duct.resetOverallMoistureTransmittanceCoefficientfromAirtoAir();
  EXPECT_TRUE(duct.isOverallMoistureTransmittanceCoefficientfromAirtoAirDefaulted());

  EXPECT_FALSE(duct.outsideConvectionCoefficient());
  EXPECT_TRUE(duct.setOutsideConvectionCoefficient(7.4));
  ASSERT_TRUE(duct.outsideConvectionCoefficient());
  EXPECT_DOUBLE_EQ(7.4, *duct.outsideConvectionCoefficient());
  duct.resetOutsideConvectionCoefficient();
  EXPECT_FALSE(duct.outsideConvectionCoefficient());

  EXPECT_FALSE(duct.insideConvectionCoefficient());
  EXPECT_TRUE(duct.setInsideConvectionCoefficient(5.9));
  ASSERT_TRUE(duct.insideConvectionCoefficient());
  EXPECT_DOUBLE_EQ(5.9, *duct.insideConvectionCoefficient());
  duct.resetInsideConvectionCoefficient();
  EXPECT_FALSE(duct.insideConvectionCoefficient());
}
