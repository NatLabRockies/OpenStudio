/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/MaterialPropertyHeatAndMoistureTransferSuction.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, MaterialPropertyHeatAndMoistureTransferSuction_DefaultConstructor) {
  Model model;
  MaterialPropertyHeatAndMoistureTransferSuction object(model);
  EXPECT_EQ(MaterialPropertyHeatAndMoistureTransferSuction::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, MaterialPropertyHeatAndMoistureTransferSuction_ScalarAccessors_RoundTrip) {
  Model model;
  MaterialPropertyHeatAndMoistureTransferSuction object(model);

  EXPECT_TRUE(object.setNumberofSuctionpoints(3));
  EXPECT_EQ(3, object.numberofSuctionpoints());
}
