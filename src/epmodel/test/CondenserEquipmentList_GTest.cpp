/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/CondenserEquipmentList.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CondenserEquipmentList_DefaultConstructor) {
  Model model;
  CondenserEquipmentList condenserEquipmentList(model);
  EXPECT_EQ(CondenserEquipmentList::iddObjectType(), condenserEquipmentList.iddObject().type());
}

TEST_F(EPModelFixture, CondenserEquipmentList_ScalarAccessors_RoundTrip) {
  Model model;
  CondenserEquipmentList condenserEquipmentList(model);

  EXPECT_TRUE(condenserEquipmentList.setName("Main Condenser Equipment List"));
  EXPECT_EQ("Main Condenser Equipment List", condenserEquipmentList.nameString());
}
