/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/GroundHeatTransferSlabZFACE.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, GroundHeatTransferSlabZFACE_DefaultConstructor) {
  Model model;
  GroundHeatTransferSlabZFACE object(model);
  EXPECT_EQ(GroundHeatTransferSlabZFACE::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, GroundHeatTransferSlabZFACE_ScalarAccessors_RoundTrip) {
  Model model;
  GroundHeatTransferSlabZFACE object(model);

  EXPECT_TRUE(object.setString(0, "1.25"));
  const auto n1 = object.getString(0, true);
  ASSERT_TRUE(n1);
  EXPECT_EQ("1.25", *n1);
}
