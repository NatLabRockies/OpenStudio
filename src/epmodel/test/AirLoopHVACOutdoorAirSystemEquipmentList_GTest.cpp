/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/AirLoopHVACOutdoorAirSystemEquipmentList.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirLoopHVACOutdoorAirSystemEquipmentList_DefaultConstructor) {
  Model model;
  AirLoopHVACOutdoorAirSystemEquipmentList equipmentList(model);
  EXPECT_EQ(AirLoopHVACOutdoorAirSystemEquipmentList::iddObjectType(), equipmentList.iddObject().type());
}

TEST_F(EPModelFixture, AirLoopHVACOutdoorAirSystemEquipmentList_ScalarAccessors_RoundTrip) {
  Model model;
  AirLoopHVACOutdoorAirSystemEquipmentList equipmentList(model);

  EXPECT_TRUE(equipmentList.setName("Main OA Equipment List"));
  EXPECT_EQ("Main OA Equipment List", equipmentList.nameString());
}
