/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"

#include "../SizingZone.hpp"
#include "../ThermalZone.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, API_SizingZone_DefaultConstructor) {
  Model model;
  ThermalZone zone(model);
  SizingZone sizingZone(model, zone);
  EXPECT_EQ(SizingZone::iddObjectType(), sizingZone.iddObject().type());
  EXPECT_EQ(zone, sizingZone.thermalZone());
}

TEST_F(EPModelFixture, API_ThermalZone_SizingZoneNonOptionalGetter) {
  Model model;
  ThermalZone zone(model);

  auto sizingZone = zone.sizingZone();
  EXPECT_EQ(zone, sizingZone.thermalZone());

  auto secondRead = zone.sizingZone();
  EXPECT_EQ(sizingZone, secondRead);
}
