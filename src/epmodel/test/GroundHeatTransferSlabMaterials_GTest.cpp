/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/GroundHeatTransferSlabMaterials.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, GroundHeatTransferSlabMaterials_DefaultConstructor) {
  Model model;
  GroundHeatTransferSlabMaterials object(model);
  EXPECT_EQ(GroundHeatTransferSlabMaterials::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, GroundHeatTransferSlabMaterials_ScalarAccessors_RoundTrip) {
  Model model;
  GroundHeatTransferSlabMaterials object(model);

  EXPECT_TRUE(object.setNMATNumberofmaterials(2.0));
  EXPECT_DOUBLE_EQ(2.0, object.nMATNumberofmaterials());
  EXPECT_FALSE(object.setNMATNumberofmaterials(0.0));

  EXPECT_TRUE(object.isALBEDOSurfaceAlbedoNoSnowDefaulted());
  EXPECT_TRUE(object.setALBEDOSurfaceAlbedoNoSnow(0.2));
  EXPECT_DOUBLE_EQ(0.2, object.aLBEDOSurfaceAlbedoNoSnow());
  EXPECT_FALSE(object.setALBEDOSurfaceAlbedoNoSnow(1.1));
  EXPECT_FALSE(object.isALBEDOSurfaceAlbedoNoSnowDefaulted());
  object.resetALBEDOSurfaceAlbedoNoSnow();
  EXPECT_TRUE(object.isALBEDOSurfaceAlbedoNoSnowDefaulted());

  EXPECT_TRUE(object.setALBEDOSurfaceAlbedoSnow(0.5));
  EXPECT_DOUBLE_EQ(0.5, object.aLBEDOSurfaceAlbedoSnow());

  EXPECT_TRUE(object.setEPSLWSurfaceEmissivityNoSnow(0.95));
  EXPECT_DOUBLE_EQ(0.95, object.ePSLWSurfaceEmissivityNoSnow());

  EXPECT_TRUE(object.setEPSLWSurfaceEmissivitySnow(0.86));
  EXPECT_DOUBLE_EQ(0.86, object.ePSLWSurfaceEmissivitySnow());

  EXPECT_TRUE(object.setZ0SurfaceRoughnessNoSnow(0.75));
  EXPECT_DOUBLE_EQ(0.75, object.z0SurfaceRoughnessNoSnow());

  EXPECT_TRUE(object.setZ0SurfaceRoughnessSnow(0.25));
  EXPECT_DOUBLE_EQ(0.25, object.z0SurfaceRoughnessSnow());

  EXPECT_TRUE(object.setHINIndoorHConvDownwardFlow(6.13));
  EXPECT_DOUBLE_EQ(6.13, object.hINIndoorHConvDownwardFlow());

  EXPECT_TRUE(object.setHINIndoorHConvUpward(9.26));
  EXPECT_DOUBLE_EQ(9.26, object.hINIndoorHConvUpward());
}
