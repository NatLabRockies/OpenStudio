/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/GroundHeatTransferBasementInsulation.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, GroundHeatTransferBasementInsulation_DefaultConstructor) {
  Model model;
  GroundHeatTransferBasementInsulation object(model);
  EXPECT_EQ(GroundHeatTransferBasementInsulation::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, GroundHeatTransferBasementInsulation_ScalarAccessors_RoundTrip) {
  Model model;
  GroundHeatTransferBasementInsulation object(model);

  EXPECT_FALSE(object.rEXTRValueofanyexteriorinsulation());

  EXPECT_TRUE(object.setREXTRValueofanyexteriorinsulation(2.5));
  auto rEXTRValueofanyexteriorinsulation = object.rEXTRValueofanyexteriorinsulation();
  ASSERT_TRUE(rEXTRValueofanyexteriorinsulation);
  EXPECT_DOUBLE_EQ(2.5, *rEXTRValueofanyexteriorinsulation);
  object.resetREXTRValueofanyexteriorinsulation();
  EXPECT_FALSE(object.rEXTRValueofanyexteriorinsulation());

  EXPECT_TRUE(object.setINSFULLFlagIsthewallfullyinsulated(true));
  EXPECT_TRUE(object.iNSFULLFlagIsthewallfullyinsulated());
  EXPECT_TRUE(object.setINSFULLFlagIsthewallfullyinsulated(false));
  EXPECT_FALSE(object.iNSFULLFlagIsthewallfullyinsulated());
}
