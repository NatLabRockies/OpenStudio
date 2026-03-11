/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ZoneHVACEquipmentList.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, API_ZoneHVACEquipmentList_DefaultConstructor) {
  Model model;
  ZoneHVACEquipmentList equipmentList(model);
  EXPECT_EQ(ZoneHVACEquipmentList::iddObjectType(), equipmentList.iddObject().type());
  EXPECT_FALSE(equipmentList.nameString().empty());
}
