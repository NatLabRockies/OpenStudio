/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/GroundHeatTransferBasementMatlProps.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, GroundHeatTransferBasementMatlProps_DefaultConstructor) {
  Model model;
  GroundHeatTransferBasementMatlProps object(model);
  EXPECT_EQ(GroundHeatTransferBasementMatlProps::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, GroundHeatTransferBasementMatlProps_ScalarAccessors_RoundTrip) {
  Model model;
  GroundHeatTransferBasementMatlProps object(model);

  EXPECT_TRUE(object.isDensityforFoundationWallDefaulted());
  EXPECT_TRUE(object.isSpecificheatforfoundationwallDefaulted());
  EXPECT_TRUE(object.isThermalconductivityforfoundationwallDefaulted());

  EXPECT_TRUE(object.setNMATNumberofmaterialsinthisdomain(6.0));
  EXPECT_DOUBLE_EQ(6.0, object.nMATNumberofmaterialsinthisdomain());
  EXPECT_FALSE(object.setNMATNumberofmaterialsinthisdomain(7.0));

  EXPECT_TRUE(object.setDensityforFoundationWall(2400.0));
  EXPECT_TRUE(object.setDensityforFloorSlab(2300.0));
  EXPECT_TRUE(object.setDensityforCeiling(320.0));
  EXPECT_TRUE(object.setDensityforSoil(1600.0));
  EXPECT_TRUE(object.setDensityforGravel(2100.0));
  EXPECT_TRUE(object.setDensityforWood(500.0));

  EXPECT_TRUE(object.setSpecificheatforfoundationwall(900.0));
  EXPECT_TRUE(object.setSpecificheatforfloorslab(910.0));
  EXPECT_TRUE(object.setSpecificheatforceiling(1540.0));
  EXPECT_TRUE(object.setSpecificheatforsoil(850.0));
  EXPECT_TRUE(object.setSpecificheatforgravel(730.0));
  EXPECT_TRUE(object.setSpecificheatforwood(1540.0));

  EXPECT_TRUE(object.setThermalconductivityforfoundationwall(1.5));
  EXPECT_TRUE(object.setThermalconductivityforfloorslab(1.45));
  EXPECT_TRUE(object.setThermalconductivityforceiling(0.1));
  EXPECT_TRUE(object.setThermalconductivityforsoil(1.2));
  EXPECT_TRUE(object.setThermalconductivityforgravel(2.0));
  EXPECT_TRUE(object.setThermalconductivityforwood(0.15));

  EXPECT_FALSE(object.setDensityforFoundationWall(0.0));

  EXPECT_DOUBLE_EQ(2400.0, object.densityforFoundationWall());
  EXPECT_DOUBLE_EQ(2300.0, object.densityforFloorSlab());
  EXPECT_DOUBLE_EQ(320.0, object.densityforCeiling());
  EXPECT_DOUBLE_EQ(1600.0, object.densityforSoil());
  EXPECT_DOUBLE_EQ(2100.0, object.densityforGravel());
  EXPECT_DOUBLE_EQ(500.0, object.densityforWood());

  EXPECT_DOUBLE_EQ(900.0, object.specificheatforfoundationwall());
  EXPECT_DOUBLE_EQ(910.0, object.specificheatforfloorslab());
  EXPECT_DOUBLE_EQ(1540.0, object.specificheatforceiling());
  EXPECT_DOUBLE_EQ(850.0, object.specificheatforsoil());
  EXPECT_DOUBLE_EQ(730.0, object.specificheatforgravel());
  EXPECT_DOUBLE_EQ(1540.0, object.specificheatforwood());

  EXPECT_DOUBLE_EQ(1.5, object.thermalconductivityforfoundationwall());
  EXPECT_DOUBLE_EQ(1.45, object.thermalconductivityforfloorslab());
  EXPECT_DOUBLE_EQ(0.1, object.thermalconductivityforceiling());
  EXPECT_DOUBLE_EQ(1.2, object.thermalconductivityforsoil());
  EXPECT_DOUBLE_EQ(2.0, object.thermalconductivityforgravel());
  EXPECT_DOUBLE_EQ(0.15, object.thermalconductivityforwood());

  EXPECT_FALSE(object.isDensityforFoundationWallDefaulted());
  object.resetDensityforFoundationWall();
  EXPECT_TRUE(object.isDensityforFoundationWallDefaulted());
}
