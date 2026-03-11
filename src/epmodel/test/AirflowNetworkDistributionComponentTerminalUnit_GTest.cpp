/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/AirflowNetworkDistributionComponentTerminalUnit.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirflowNetworkDistributionComponentTerminalUnit_DefaultConstructor) {
  Model model;
  AirflowNetworkDistributionComponentTerminalUnit terminalUnit(model);
  EXPECT_EQ(AirflowNetworkDistributionComponentTerminalUnit::iddObjectType(), terminalUnit.iddObject().type());
}

TEST_F(EPModelFixture, AirflowNetworkDistributionComponentTerminalUnit_ScalarAccessors_RoundTrip) {
  Model model;
  AirflowNetworkDistributionComponentTerminalUnit terminalUnit(model);

  const auto terminalUnitObjectTypeValues = AirflowNetworkDistributionComponentTerminalUnit::terminalUnitObjectTypeValues();
  ASSERT_FALSE(terminalUnitObjectTypeValues.empty());

  EXPECT_TRUE(terminalUnit.setTerminalUnitObjectType(terminalUnitObjectTypeValues.front()));
  EXPECT_EQ(terminalUnitObjectTypeValues.front(), terminalUnit.terminalUnitObjectType());

  EXPECT_TRUE(terminalUnit.setAirPathLength(1.7));
  EXPECT_DOUBLE_EQ(1.7, terminalUnit.airPathLength());

  EXPECT_TRUE(terminalUnit.setAirPathHydraulicDiameter(0.35));
  EXPECT_DOUBLE_EQ(0.35, terminalUnit.airPathHydraulicDiameter());
}
