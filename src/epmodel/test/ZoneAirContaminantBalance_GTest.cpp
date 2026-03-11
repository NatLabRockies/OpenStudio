/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/ZoneAirContaminantBalance.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneAirContaminantBalance_DefaultConstructor) {
  Model model;
  ZoneAirContaminantBalance cab(model);
  EXPECT_EQ(ZoneAirContaminantBalance::iddObjectType(), cab.iddObject().type());
  EXPECT_FALSE(cab.carbonDioxideConcentration());
  EXPECT_FALSE(cab.genericContaminantConcentration());
}

TEST_F(EPModelFixture, ZoneAirContaminantBalance_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneAirContaminantBalance cab(model);

  EXPECT_TRUE(cab.setCarbonDioxideConcentration(true));
  EXPECT_TRUE(cab.carbonDioxideConcentration());
  cab.setCarbonDioxideConcentrationNoFail(false);
  EXPECT_FALSE(cab.carbonDioxideConcentration());
  cab.resetCarbonDioxideConcentration();
  EXPECT_TRUE(cab.isCarbonDioxideConcentrationDefaulted());

  EXPECT_TRUE(cab.setGenericContaminantConcentration(true));
  EXPECT_TRUE(cab.genericContaminantConcentration());
  EXPECT_TRUE(cab.setGenericContaminantConcentration(false));
  EXPECT_FALSE(cab.genericContaminantConcentration());
  cab.resetGenericContaminantConcentration();
  EXPECT_TRUE(cab.isGenericContaminantConcentrationDefaulted());
}
