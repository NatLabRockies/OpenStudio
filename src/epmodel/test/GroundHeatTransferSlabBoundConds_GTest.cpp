/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/GroundHeatTransferSlabBoundConds.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, GroundHeatTransferSlabBoundConds_DefaultConstructor) {
  Model model;
  GroundHeatTransferSlabBoundConds object(model);
  EXPECT_EQ(GroundHeatTransferSlabBoundConds::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, GroundHeatTransferSlabBoundConds_ScalarAccessors_RoundTrip) {
  Model model;
  GroundHeatTransferSlabBoundConds object(model);

  EXPECT_FALSE(object.tDEEPin());
  EXPECT_FALSE(object.uSERHUserspecifiedgroundsurfaceheattransfercoefficient());

  EXPECT_TRUE(object.setEVTRIssurfaceevapotranspirationmodeled(true));
  EXPECT_TRUE(object.eVTRIssurfaceevapotranspirationmodeled());
  EXPECT_TRUE(object.setEVTRIssurfaceevapotranspirationmodeled(false));
  EXPECT_FALSE(object.eVTRIssurfaceevapotranspirationmodeled());

  EXPECT_TRUE(object.setFIXBCIsthelowerboundaryatafixedtemperature(true));
  EXPECT_TRUE(object.fIXBCIsthelowerboundaryatafixedtemperature());
  EXPECT_TRUE(object.setFIXBCIsthelowerboundaryatafixedtemperature(false));
  EXPECT_FALSE(object.fIXBCIsthelowerboundaryatafixedtemperature());

  EXPECT_TRUE(object.setUSRHflagIsthegroundsurfacehspecifiedbytheuser(true));
  EXPECT_TRUE(object.uSRHflagIsthegroundsurfacehspecifiedbytheuser());
  EXPECT_TRUE(object.setUSRHflagIsthegroundsurfacehspecifiedbytheuser(false));
  EXPECT_FALSE(object.uSRHflagIsthegroundsurfacehspecifiedbytheuser());

  EXPECT_TRUE(object.setTDEEPin(13.5));
  ASSERT_TRUE(object.tDEEPin());
  EXPECT_DOUBLE_EQ(13.5, object.tDEEPin().get());
  object.resetTDEEPin();
  EXPECT_FALSE(object.tDEEPin());

  EXPECT_TRUE(object.setUSERHUserspecifiedgroundsurfaceheattransfercoefficient(7.2));
  ASSERT_TRUE(object.uSERHUserspecifiedgroundsurfaceheattransfercoefficient());
  EXPECT_DOUBLE_EQ(7.2, object.uSERHUserspecifiedgroundsurfaceheattransfercoefficient().get());
  object.resetUSERHUserspecifiedgroundsurfaceheattransfercoefficient();
  EXPECT_FALSE(object.uSERHUserspecifiedgroundsurfaceheattransfercoefficient());
}
