/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/AirflowNetworkMultiZoneSurface.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirflowNetworkMultiZoneSurface_DefaultConstructor) {
  Model model;
  AirflowNetworkMultiZoneSurface afnSurface(model);
  EXPECT_EQ(AirflowNetworkMultiZoneSurface::iddObjectType(), afnSurface.iddObject().type());
}

TEST_F(EPModelFixture, AirflowNetworkMultiZoneSurface_ScalarAccessors_RoundTrip) {
  Model model;
  AirflowNetworkMultiZoneSurface afnSurface(model);

  EXPECT_TRUE(afnSurface.isWindowDoorOpeningFactororCrackFactorDefaulted());
  EXPECT_DOUBLE_EQ(1.0, afnSurface.windowDoorOpeningFactororCrackFactor());
  EXPECT_TRUE(afnSurface.setWindowDoorOpeningFactororCrackFactor(0.8));
  EXPECT_DOUBLE_EQ(0.8, afnSurface.windowDoorOpeningFactororCrackFactor());
  EXPECT_FALSE(afnSurface.isWindowDoorOpeningFactororCrackFactorDefaulted());
  afnSurface.resetWindowDoorOpeningFactororCrackFactor();
  EXPECT_TRUE(afnSurface.isWindowDoorOpeningFactororCrackFactorDefaulted());
  EXPECT_DOUBLE_EQ(1.0, afnSurface.windowDoorOpeningFactororCrackFactor());

  EXPECT_TRUE(afnSurface.isVentilationControlModeDefaulted());
  EXPECT_EQ("ZoneLevel", afnSurface.ventilationControlMode());
  EXPECT_TRUE(afnSurface.setVentilationControlMode("NoVent"));
  EXPECT_EQ("NoVent", afnSurface.ventilationControlMode());
  EXPECT_FALSE(afnSurface.isVentilationControlModeDefaulted());
  afnSurface.resetVentilationControlMode();
  EXPECT_TRUE(afnSurface.isVentilationControlModeDefaulted());
  EXPECT_EQ("ZoneLevel", afnSurface.ventilationControlMode());

  EXPECT_TRUE(afnSurface.isMinimumVentingOpenFactorDefaulted());
  EXPECT_DOUBLE_EQ(0.0, afnSurface.minimumVentingOpenFactor());
  EXPECT_TRUE(afnSurface.setMinimumVentingOpenFactor(0.25));
  EXPECT_DOUBLE_EQ(0.25, afnSurface.minimumVentingOpenFactor());
  afnSurface.resetMinimumVentingOpenFactor();
  EXPECT_TRUE(afnSurface.isMinimumVentingOpenFactorDefaulted());
  EXPECT_DOUBLE_EQ(0.0, afnSurface.minimumVentingOpenFactor());

  EXPECT_TRUE(afnSurface.isEquivalentRectangleMethodDefaulted());
  EXPECT_EQ("PolygonHeight", afnSurface.equivalentRectangleMethod());
  EXPECT_TRUE(afnSurface.setEquivalentRectangleMethod("UserDefinedAspectRatio"));
  EXPECT_EQ("UserDefinedAspectRatio", afnSurface.equivalentRectangleMethod());
  EXPECT_FALSE(afnSurface.isEquivalentRectangleMethodDefaulted());
  afnSurface.resetEquivalentRectangleMethod();
  EXPECT_TRUE(afnSurface.isEquivalentRectangleMethodDefaulted());
  EXPECT_EQ("PolygonHeight", afnSurface.equivalentRectangleMethod());

  EXPECT_TRUE(afnSurface.isEquivalentRectangleAspectRatioDefaulted());
  EXPECT_DOUBLE_EQ(1.0, afnSurface.equivalentRectangleAspectRatio());
  EXPECT_TRUE(afnSurface.setEquivalentRectangleAspectRatio(1.3));
  EXPECT_DOUBLE_EQ(1.3, afnSurface.equivalentRectangleAspectRatio());
  EXPECT_FALSE(afnSurface.isEquivalentRectangleAspectRatioDefaulted());
  afnSurface.resetEquivalentRectangleAspectRatio();
  EXPECT_TRUE(afnSurface.isEquivalentRectangleAspectRatioDefaulted());
  EXPECT_DOUBLE_EQ(1.0, afnSurface.equivalentRectangleAspectRatio());

  EXPECT_TRUE(afnSurface.setIndoorandOutdoorTemperatureDifferenceLowerLimitForMaximumVentingOpenFactor(2.0));
  EXPECT_DOUBLE_EQ(2.0, afnSurface.indoorandOutdoorTemperatureDifferenceLowerLimitForMaximumVentingOpenFactor());
  EXPECT_TRUE(afnSurface.setIndoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactor(24.0));
  EXPECT_DOUBLE_EQ(24.0, afnSurface.indoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactor());
  EXPECT_TRUE(afnSurface.setIndoorandOutdoorEnthalpyDifferenceLowerLimitForMaximumVentingOpenFactor(1000.0));
  EXPECT_DOUBLE_EQ(1000.0, afnSurface.indoorandOutdoorEnthalpyDifferenceLowerLimitForMaximumVentingOpenFactor());
  EXPECT_TRUE(afnSurface.setIndoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactor(200000.0));
  EXPECT_DOUBLE_EQ(200000.0, afnSurface.indoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactor());

  const auto ventilationModes = AirflowNetworkMultiZoneSurface::ventilationControlModeValues();
  EXPECT_EQ(9u, ventilationModes.size());
  EXPECT_EQ("Temperature", ventilationModes[0]);
  EXPECT_EQ("AdjacentEnthalpy", ventilationModes[8]);

  const auto equivalentRectangleMethods = AirflowNetworkMultiZoneSurface::equivalentRectangleMethodValues();
  EXPECT_EQ(3u, equivalentRectangleMethods.size());
  EXPECT_EQ("PolygonHeight", equivalentRectangleMethods[0]);
  EXPECT_EQ("UserDefinedAspectRatio", equivalentRectangleMethods[2]);
}
