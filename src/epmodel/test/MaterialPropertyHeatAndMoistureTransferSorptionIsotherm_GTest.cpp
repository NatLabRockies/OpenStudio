/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/MaterialPropertyHeatAndMoistureTransferSorptionIsotherm.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, MaterialPropertyHeatAndMoistureTransferSorptionIsotherm_DefaultConstructor) {
  Model model;
  MaterialPropertyHeatAndMoistureTransferSorptionIsotherm object(model);
  EXPECT_EQ(MaterialPropertyHeatAndMoistureTransferSorptionIsotherm::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, MaterialPropertyHeatAndMoistureTransferSorptionIsotherm_ScalarAccessors_RoundTrip) {
  Model model;
  MaterialPropertyHeatAndMoistureTransferSorptionIsotherm object(model);

  EXPECT_TRUE(object.setNumberofIsothermCoordinates(3));
  EXPECT_EQ(3, object.numberofIsothermCoordinates());
}
