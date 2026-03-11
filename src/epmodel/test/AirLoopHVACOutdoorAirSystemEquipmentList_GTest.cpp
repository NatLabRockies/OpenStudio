/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../AirLoopHVACOutdoorAirSystemEquipmentList.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, API_AirLoopHVACOutdoorAirSystemEquipmentList_DefaultConstructor) {
  Model model;
  AirLoopHVACOutdoorAirSystemEquipmentList equipmentList(model);
  EXPECT_EQ(AirLoopHVACOutdoorAirSystemEquipmentList::iddObjectType(), equipmentList.iddObject().type());
}
