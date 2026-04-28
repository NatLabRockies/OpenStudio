/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/ZoneHVACOutdoorAirUnitEquipmentList.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, API_ZoneHVACOutdoorAirUnitEquipmentList_DefaultConstructor) {
  Model model;
  ZoneHVACOutdoorAirUnitEquipmentList equipmentList(model);

  EXPECT_EQ(ZoneHVACOutdoorAirUnitEquipmentList::iddObjectType(), equipmentList.iddObject().type());
}

TEST_F(EPModelFixture, API_ZoneHVACOutdoorAirUnitEquipmentList_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneHVACOutdoorAirUnitEquipmentList equipmentList(model);

  EXPECT_TRUE(equipmentList.setName("Outdoor Air Unit Equipment"));
  EXPECT_EQ("Outdoor Air Unit Equipment", equipmentList.nameString());
}
