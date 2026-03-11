/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include <algorithm>
#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/ZoneAirBalanceOutdoorAir.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneAirBalanceOutdoorAir_DefaultConstructor) {
  Model model;
  ZoneAirBalanceOutdoorAir zoneAirBalanceOutdoorAir(model);
  EXPECT_EQ(ZoneAirBalanceOutdoorAir::iddObjectType(), zoneAirBalanceOutdoorAir.iddObject().type());
  EXPECT_EQ("Quadrature", zoneAirBalanceOutdoorAir.airBalanceMethod());
  EXPECT_DOUBLE_EQ(0.0, zoneAirBalanceOutdoorAir.inducedOutdoorAirDueToUnbalancedDuctLeakage());
}

TEST_F(EPModelFixture, ZoneAirBalanceOutdoorAir_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneAirBalanceOutdoorAir zoneAirBalanceOutdoorAir(model);

  const auto values = ZoneAirBalanceOutdoorAir::airBalanceMethodValues();
  EXPECT_NE(values.end(), std::find(values.begin(), values.end(), "Quadrature"));
  EXPECT_NE(values.end(), std::find(values.begin(), values.end(), "None"));

  EXPECT_TRUE(zoneAirBalanceOutdoorAir.setAirBalanceMethod("None"));
  EXPECT_EQ("None", zoneAirBalanceOutdoorAir.airBalanceMethod());
  EXPECT_FALSE(zoneAirBalanceOutdoorAir.isAirBalanceMethodDefaulted());
  zoneAirBalanceOutdoorAir.resetAirBalanceMethod();
  EXPECT_TRUE(zoneAirBalanceOutdoorAir.isAirBalanceMethodDefaulted());

  EXPECT_TRUE(zoneAirBalanceOutdoorAir.setInducedOutdoorAirDueToUnbalancedDuctLeakage(1.25));
  EXPECT_DOUBLE_EQ(1.25, zoneAirBalanceOutdoorAir.inducedOutdoorAirDueToUnbalancedDuctLeakage());
  zoneAirBalanceOutdoorAir.resetInducedOutdoorAirDueToUnbalancedDuctLeakage();
  EXPECT_TRUE(zoneAirBalanceOutdoorAir.isInducedOutdoorAirDueToUnbalancedDuctLeakageDefaulted());
}
