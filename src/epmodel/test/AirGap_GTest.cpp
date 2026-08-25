/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../OpaqueMaterial/AirGap.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirGap_DefaultConstructor) {
  Model model;
  AirGap airGap(model);

  EXPECT_EQ(AirGap::iddObjectType(), airGap.iddObject().type());
  EXPECT_FALSE(airGap.nameString().empty());
  EXPECT_DOUBLE_EQ(0.1, airGap.thermalResistance());
}

TEST_F(EPModelFixture, AirGap_ScalarAccessors_RoundTrip) {
  Model model;
  AirGap airGap(model);

  EXPECT_TRUE(airGap.setThermalResistance(0.18));
  EXPECT_DOUBLE_EQ(0.18, airGap.thermalResistance());
}
