/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <algorithm>
#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/ZoneHVACEquipmentList.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, API_ZoneHVACEquipmentList_DefaultConstructor) {
  Model model;
  ZoneHVACEquipmentList equipmentList(model);
  EXPECT_EQ(ZoneHVACEquipmentList::iddObjectType(), equipmentList.iddObject().type());
  EXPECT_FALSE(equipmentList.nameString().empty());
}

TEST_F(EPModelFixture, API_ZoneHVACEquipmentList_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneHVACEquipmentList equipmentList(model);

  const auto values = ZoneHVACEquipmentList::loadDistributionSchemeValues();
  EXPECT_FALSE(values.empty());
  EXPECT_EQ(values, ZoneHVACEquipmentList::validLoadDistributionSchemeValues());
  EXPECT_NE(values.cend(), std::find(values.cbegin(), values.cend(), equipmentList.loadDistributionScheme()));

  EXPECT_TRUE(equipmentList.setLoadDistributionScheme("Uniform"));
  EXPECT_EQ("UniformLoad", equipmentList.loadDistributionScheme());
  EXPECT_FALSE(equipmentList.isLoadDistributionSchemeDefaulted());

  equipmentList.resetLoadDistributionScheme();
  EXPECT_TRUE(equipmentList.isLoadDistributionSchemeDefaulted());
  EXPECT_EQ("SequentialLoad", equipmentList.loadDistributionScheme());
}
