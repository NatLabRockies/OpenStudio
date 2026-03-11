/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../WaterToWaterComponent/CentralHeatPumpSystem.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CentralHeatPumpSystem_DefaultConstructor) {
  Model model;
  CentralHeatPumpSystem centralHeatPumpSystem(model);
  EXPECT_EQ(CentralHeatPumpSystem::iddObjectType(), centralHeatPumpSystem.iddObject().type());
  EXPECT_EQ("SmartMixing", centralHeatPumpSystem.controlMethod());
  EXPECT_DOUBLE_EQ(0.0, centralHeatPumpSystem.ancillaryPower());
}

TEST_F(EPModelFixture, CentralHeatPumpSystem_ScalarAccessors_RoundTrip) {
  Model model;
  CentralHeatPumpSystem centralHeatPumpSystem(model);

  const auto values = CentralHeatPumpSystem::controlMethodValues();
  ASSERT_FALSE(values.empty());
  EXPECT_TRUE(centralHeatPumpSystem.setControlMethod(values.front()));
  EXPECT_EQ(values.front(), centralHeatPumpSystem.controlMethod());

  EXPECT_TRUE(centralHeatPumpSystem.setAncillaryPower(17.25));
  EXPECT_DOUBLE_EQ(17.25, centralHeatPumpSystem.ancillaryPower());
}
