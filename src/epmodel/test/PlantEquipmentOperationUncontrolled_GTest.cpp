/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/PlantEquipmentOperationUncontrolled.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, PlantEquipmentOperationUncontrolled_DefaultConstructor) {
  Model model;
  PlantEquipmentOperationUncontrolled scheme(model);

  EXPECT_EQ(PlantEquipmentOperationUncontrolled::iddObjectType(), scheme.iddObject().type());
}

TEST_F(EPModelFixture, PlantEquipmentOperationUncontrolled_ScalarAccessors_RoundTrip) {
  Model model;
  PlantEquipmentOperationUncontrolled scheme(model);

  EXPECT_TRUE(scheme.setName("Uncontrolled Operation"));
  EXPECT_EQ("Uncontrolled Operation", scheme.nameString());
}
