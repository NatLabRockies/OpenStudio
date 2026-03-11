/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/FaultModelEnthalpySensorOffsetOutdoorAir.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, FaultModelEnthalpySensorOffsetOutdoorAir_DefaultConstructor) {
  Model model;
  FaultModelEnthalpySensorOffsetOutdoorAir fault(model);
  EXPECT_EQ(FaultModelEnthalpySensorOffsetOutdoorAir::iddObjectType(), fault.iddObject().type());

  EXPECT_TRUE(fault.isEnthalpySensorOffsetDefaulted());
  EXPECT_DOUBLE_EQ(0.0, fault.enthalpySensorOffset());
}

TEST_F(EPModelFixture, FaultModelEnthalpySensorOffsetOutdoorAir_ScalarAccessors_RoundTrip) {
  Model model;
  FaultModelEnthalpySensorOffsetOutdoorAir fault(model);

  EXPECT_TRUE(fault.setEnthalpySensorOffset(1250.0));
  EXPECT_DOUBLE_EQ(1250.0, fault.enthalpySensorOffset());
  EXPECT_FALSE(fault.isEnthalpySensorOffsetDefaulted());

  fault.resetEnthalpySensorOffset();
  EXPECT_TRUE(fault.isEnthalpySensorOffsetDefaulted());
  EXPECT_DOUBLE_EQ(0.0, fault.enthalpySensorOffset());
}
