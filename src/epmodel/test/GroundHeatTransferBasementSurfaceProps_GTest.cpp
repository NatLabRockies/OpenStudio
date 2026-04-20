/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/GroundHeatTransferBasementSurfaceProps.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, GroundHeatTransferBasementSurfaceProps_DefaultConstructor) {
  Model model;
  GroundHeatTransferBasementSurfaceProps object(model);
  EXPECT_EQ(GroundHeatTransferBasementSurfaceProps::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, GroundHeatTransferBasementSurfaceProps_ScalarAccessors_RoundTrip) {
  Model model;
  GroundHeatTransferBasementSurfaceProps object(model);

  EXPECT_TRUE(object.isALBEDOSurfacealbedoforNosnowconditionsDefaulted());
  EXPECT_TRUE(object.isALBEDOSurfacealbedoforsnowconditionsDefaulted());
  EXPECT_TRUE(object.isEPSLNSurfaceemissivityNoSnowDefaulted());
  EXPECT_TRUE(object.isEPSLNSurfaceemissivitywithSnowDefaulted());
  EXPECT_TRUE(object.isVEGHTSurfaceroughnessNosnowconditionsDefaulted());
  EXPECT_TRUE(object.isVEGHTSurfaceroughnessSnowconditionsDefaulted());
  EXPECT_TRUE(object.isPETFlagPotentialevapotranspirationonDefaulted());

  EXPECT_TRUE(object.setALBEDOSurfacealbedoforNosnowconditions(0.2));
  EXPECT_TRUE(object.setALBEDOSurfacealbedoforsnowconditions(0.5));
  EXPECT_TRUE(object.setEPSLNSurfaceemissivityNoSnow(0.93));
  EXPECT_TRUE(object.setEPSLNSurfaceemissivitywithSnow(0.85));
  EXPECT_TRUE(object.setVEGHTSurfaceroughnessNosnowconditions(5.0));
  EXPECT_TRUE(object.setVEGHTSurfaceroughnessSnowconditions(0.5));
  EXPECT_TRUE(object.setPETFlagPotentialevapotranspirationon(true));

  EXPECT_DOUBLE_EQ(0.2, object.aLBEDOSurfacealbedoforNosnowconditions());
  EXPECT_DOUBLE_EQ(0.5, object.aLBEDOSurfacealbedoforsnowconditions());
  EXPECT_DOUBLE_EQ(0.93, object.ePSLNSurfaceemissivityNoSnow());
  EXPECT_DOUBLE_EQ(0.85, object.ePSLNSurfaceemissivitywithSnow());
  EXPECT_DOUBLE_EQ(5.0, object.vEGHTSurfaceroughnessNosnowconditions());
  EXPECT_DOUBLE_EQ(0.5, object.vEGHTSurfaceroughnessSnowconditions());
  EXPECT_TRUE(object.pETFlagPotentialevapotranspirationon());

  EXPECT_FALSE(object.setALBEDOSurfacealbedoforNosnowconditions(1.2));

  EXPECT_FALSE(object.isPETFlagPotentialevapotranspirationonDefaulted());
  object.resetPETFlagPotentialevapotranspirationon();
  EXPECT_TRUE(object.isPETFlagPotentialevapotranspirationonDefaulted());
}
