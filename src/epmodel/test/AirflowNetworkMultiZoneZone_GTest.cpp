/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/AirflowNetworkMultiZoneZone.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirflowNetworkMultiZoneZone_DefaultConstructor) {
  Model model;
  AirflowNetworkMultiZoneZone zone(model);
  EXPECT_EQ(AirflowNetworkMultiZoneZone::iddObjectType(), zone.iddObject().type());
}

TEST_F(EPModelFixture, AirflowNetworkMultiZoneZone_ScalarAccessors_RoundTrip) {
  Model model;
  AirflowNetworkMultiZoneZone zone(model);

  const auto controlModes = AirflowNetworkMultiZoneZone::ventilationControlModeValues();
  EXPECT_FALSE(controlModes.empty());
  EXPECT_EQ("NoVent", zone.ventilationControlMode());
  EXPECT_TRUE(zone.isVentilationControlModeDefaulted());
  EXPECT_TRUE(zone.setVentilationControlMode("Temperature"));
  EXPECT_EQ("Temperature", zone.ventilationControlMode());
  EXPECT_FALSE(zone.isVentilationControlModeDefaulted());
  zone.resetVentilationControlMode();
  EXPECT_TRUE(zone.isVentilationControlModeDefaulted());
  EXPECT_EQ("NoVent", zone.ventilationControlMode());

  EXPECT_TRUE(zone.isMinimumVentingOpenFactorDefaulted());
  EXPECT_DOUBLE_EQ(0.0, zone.minimumVentingOpenFactor());
  EXPECT_TRUE(zone.setMinimumVentingOpenFactor(0.35));
  EXPECT_DOUBLE_EQ(0.35, zone.minimumVentingOpenFactor());
  EXPECT_FALSE(zone.isMinimumVentingOpenFactorDefaulted());
  EXPECT_FALSE(zone.setMinimumVentingOpenFactor(-0.1));
  EXPECT_DOUBLE_EQ(0.35, zone.minimumVentingOpenFactor());
  zone.resetMinimumVentingOpenFactor();
  EXPECT_TRUE(zone.isMinimumVentingOpenFactorDefaulted());
  EXPECT_DOUBLE_EQ(0.0, zone.minimumVentingOpenFactor());

  EXPECT_TRUE(zone.isIndoorandOutdoorTemperatureDifferenceLowerLimitForMaximumVentingOpenFactorDefaulted());
  EXPECT_DOUBLE_EQ(0.0, zone.indoorandOutdoorTemperatureDifferenceLowerLimitForMaximumVentingOpenFactor());
  EXPECT_TRUE(zone.setIndoorandOutdoorTemperatureDifferenceLowerLimitForMaximumVentingOpenFactor(5.0));
  EXPECT_DOUBLE_EQ(5.0, zone.indoorandOutdoorTemperatureDifferenceLowerLimitForMaximumVentingOpenFactor());
  EXPECT_FALSE(zone.isIndoorandOutdoorTemperatureDifferenceLowerLimitForMaximumVentingOpenFactorDefaulted());
  zone.resetIndoorandOutdoorTemperatureDifferenceLowerLimitForMaximumVentingOpenFactor();
  EXPECT_TRUE(zone.isIndoorandOutdoorTemperatureDifferenceLowerLimitForMaximumVentingOpenFactorDefaulted());
  EXPECT_DOUBLE_EQ(0.0, zone.indoorandOutdoorTemperatureDifferenceLowerLimitForMaximumVentingOpenFactor());

  EXPECT_TRUE(zone.isIndoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactorDefaulted());
  EXPECT_DOUBLE_EQ(100.0, zone.indoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactor());
  EXPECT_TRUE(zone.setIndoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactor(9.0));
  EXPECT_DOUBLE_EQ(9.0, zone.indoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactor());
  EXPECT_FALSE(zone.isIndoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactorDefaulted());
  EXPECT_FALSE(zone.setIndoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactor(0.0));
  EXPECT_DOUBLE_EQ(9.0, zone.indoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactor());
  zone.resetIndoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactor();
  EXPECT_TRUE(zone.isIndoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactorDefaulted());
  EXPECT_DOUBLE_EQ(100.0, zone.indoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactor());

  EXPECT_TRUE(zone.isIndoorandOutdoorEnthalpyDifferenceLowerLimitForMaximumVentingOpenFactorDefaulted());
  EXPECT_DOUBLE_EQ(0.0, zone.indoorandOutdoorEnthalpyDifferenceLowerLimitForMaximumVentingOpenFactor());
  EXPECT_TRUE(zone.setIndoorandOutdoorEnthalpyDifferenceLowerLimitForMaximumVentingOpenFactor(1500.0));
  EXPECT_DOUBLE_EQ(1500.0, zone.indoorandOutdoorEnthalpyDifferenceLowerLimitForMaximumVentingOpenFactor());
  EXPECT_FALSE(zone.isIndoorandOutdoorEnthalpyDifferenceLowerLimitForMaximumVentingOpenFactorDefaulted());
  zone.resetIndoorandOutdoorEnthalpyDifferenceLowerLimitForMaximumVentingOpenFactor();
  EXPECT_TRUE(zone.isIndoorandOutdoorEnthalpyDifferenceLowerLimitForMaximumVentingOpenFactorDefaulted());
  EXPECT_DOUBLE_EQ(0.0, zone.indoorandOutdoorEnthalpyDifferenceLowerLimitForMaximumVentingOpenFactor());

  EXPECT_TRUE(zone.isIndoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactorDefaulted());
  EXPECT_DOUBLE_EQ(300000.0, zone.indoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactor());
  EXPECT_TRUE(zone.setIndoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactor(5000.0));
  EXPECT_DOUBLE_EQ(5000.0, zone.indoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactor());
  EXPECT_FALSE(zone.isIndoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactorDefaulted());
  EXPECT_FALSE(zone.setIndoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactor(0.0));
  EXPECT_DOUBLE_EQ(5000.0, zone.indoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactor());
  zone.resetIndoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactor();
  EXPECT_TRUE(zone.isIndoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactorDefaulted());
  EXPECT_DOUBLE_EQ(300000.0, zone.indoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactor());

  const auto algorithmValues = AirflowNetworkMultiZoneZone::singleSidedWindPressureCoefficientAlgorithmValues();
  EXPECT_FALSE(algorithmValues.empty());
  EXPECT_TRUE(zone.isSingleSidedWindPressureCoefficientAlgorithmDefaulted());
  EXPECT_EQ("Standard", zone.singleSidedWindPressureCoefficientAlgorithm());
  EXPECT_TRUE(zone.setSingleSidedWindPressureCoefficientAlgorithm("Advanced"));
  EXPECT_EQ("Advanced", zone.singleSidedWindPressureCoefficientAlgorithm());
  EXPECT_FALSE(zone.isSingleSidedWindPressureCoefficientAlgorithmDefaulted());
  zone.resetSingleSidedWindPressureCoefficientAlgorithm();
  EXPECT_TRUE(zone.isSingleSidedWindPressureCoefficientAlgorithmDefaulted());
  EXPECT_EQ("Standard", zone.singleSidedWindPressureCoefficientAlgorithm());

  EXPECT_TRUE(zone.isFacadeWidthDefaulted());
  EXPECT_DOUBLE_EQ(10.0, zone.facadeWidth());
  EXPECT_TRUE(zone.setFacadeWidth(17.2));
  EXPECT_DOUBLE_EQ(17.2, zone.facadeWidth());
  EXPECT_FALSE(zone.isFacadeWidthDefaulted());
  EXPECT_FALSE(zone.setFacadeWidth(-1.0));
  EXPECT_DOUBLE_EQ(17.2, zone.facadeWidth());
  zone.resetFacadeWidth();
  EXPECT_TRUE(zone.isFacadeWidthDefaulted());
  EXPECT_DOUBLE_EQ(10.0, zone.facadeWidth());
}
