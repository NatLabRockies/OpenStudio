/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/MaterialPropertyHeatAndMoistureTransferThermalConductivity.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, MaterialPropertyHeatAndMoistureTransferThermalConductivity_DefaultConstructor) {
  Model model;
  MaterialPropertyHeatAndMoistureTransferThermalConductivity object(model);
  EXPECT_EQ(MaterialPropertyHeatAndMoistureTransferThermalConductivity::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, MaterialPropertyHeatAndMoistureTransferThermalConductivity_ScalarAccessors_RoundTrip) {
  Model model;
  MaterialPropertyHeatAndMoistureTransferThermalConductivity object(model);

  EXPECT_TRUE(object.setNumberofThermalCoordinates(3));
  EXPECT_EQ(3, object.numberofThermalCoordinates());
}
