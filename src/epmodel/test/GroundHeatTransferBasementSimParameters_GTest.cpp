/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/GroundHeatTransferBasementSimParameters.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, GroundHeatTransferBasementSimParameters_DefaultConstructor) {
  Model model;
  GroundHeatTransferBasementSimParameters object(model);
  EXPECT_EQ(GroundHeatTransferBasementSimParameters::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, GroundHeatTransferBasementSimParameters_ScalarAccessors_RoundTrip) {
  Model model;
  GroundHeatTransferBasementSimParameters object(model);

  EXPECT_FALSE(object.fMultiplierfortheADIsolution());
  EXPECT_TRUE(object.isIYRSMaximumnumberofyearlyiterationsDefaulted());

  EXPECT_TRUE(object.setFMultiplierfortheADIsolution(0.3));
  auto fMultiplierfortheADIsolution = object.fMultiplierfortheADIsolution();
  ASSERT_TRUE(fMultiplierfortheADIsolution);
  EXPECT_DOUBLE_EQ(0.3, *fMultiplierfortheADIsolution);

  EXPECT_TRUE(object.setIYRSMaximumnumberofyearlyiterations(25));
  EXPECT_EQ(25, object.iYRSMaximumnumberofyearlyiterations());
  EXPECT_FALSE(object.isIYRSMaximumnumberofyearlyiterationsDefaulted());

  EXPECT_FALSE(object.setFMultiplierfortheADIsolution(1.1));
  EXPECT_FALSE(object.setIYRSMaximumnumberofyearlyiterations(-1));

  object.resetFMultiplierfortheADIsolution();
  EXPECT_FALSE(object.fMultiplierfortheADIsolution());

  object.resetIYRSMaximumnumberofyearlyiterations();
  EXPECT_TRUE(object.isIYRSMaximumnumberofyearlyiterationsDefaulted());
  EXPECT_EQ(15, object.iYRSMaximumnumberofyearlyiterations());
}
