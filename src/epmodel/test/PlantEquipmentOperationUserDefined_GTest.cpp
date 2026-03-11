/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/PlantEquipmentOperationUserDefined.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, PlantEquipmentOperationUserDefined_DefaultConstructor) {
  Model model;
  PlantEquipmentOperationUserDefined operation(model);

  EXPECT_EQ(PlantEquipmentOperationUserDefined::iddObjectType(), operation.iddObject().type());
}

TEST_F(EPModelFixture, PlantEquipmentOperationUserDefined_ScalarAccessors_RoundTrip) {
  Model model;
  PlantEquipmentOperationUserDefined operation(model);

  EXPECT_TRUE(operation.setName("User Defined Operation"));
  EXPECT_EQ("User Defined Operation", operation.nameString());
}
