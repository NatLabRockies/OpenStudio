/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/GroundHeatTransferSlabMatlProps.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, GroundHeatTransferSlabMatlProps_DefaultConstructor) {
  Model model;
  GroundHeatTransferSlabMatlProps object(model);
  EXPECT_EQ(GroundHeatTransferSlabMatlProps::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, GroundHeatTransferSlabMatlProps_ScalarAccessors_RoundTrip) {
  Model model;
  GroundHeatTransferSlabMatlProps object(model);

  EXPECT_TRUE(object.isRHOSlabMaterialdensityDefaulted());
  EXPECT_TRUE(object.isRHOSoilDensityDefaulted());
  EXPECT_TRUE(object.isCPSlabCPDefaulted());
  EXPECT_TRUE(object.isCPSoilCPDefaulted());
  EXPECT_TRUE(object.isTCONSlabkDefaulted());
  EXPECT_TRUE(object.isTCONSoilkDefaulted());

  EXPECT_TRUE(object.setRHOSlabMaterialdensity(2300.0));
  EXPECT_TRUE(object.setRHOSoilDensity(1300.0));
  EXPECT_TRUE(object.setCPSlabCP(950.0));
  EXPECT_TRUE(object.setCPSoilCP(1250.0));
  EXPECT_TRUE(object.setTCONSlabk(0.95));
  EXPECT_TRUE(object.setTCONSoilk(1.05));

  EXPECT_FALSE(object.setRHOSlabMaterialdensity(0.0));

  EXPECT_DOUBLE_EQ(2300.0, object.rHOSlabMaterialdensity());
  EXPECT_DOUBLE_EQ(1300.0, object.rHOSoilDensity());
  EXPECT_DOUBLE_EQ(950.0, object.cPSlabCP());
  EXPECT_DOUBLE_EQ(1250.0, object.cPSoilCP());
  EXPECT_DOUBLE_EQ(0.95, object.tCONSlabk());
  EXPECT_DOUBLE_EQ(1.05, object.tCONSoilk());

  EXPECT_FALSE(object.isRHOSlabMaterialdensityDefaulted());
  object.resetRHOSlabMaterialdensity();
  EXPECT_TRUE(object.isRHOSlabMaterialdensityDefaulted());
}
