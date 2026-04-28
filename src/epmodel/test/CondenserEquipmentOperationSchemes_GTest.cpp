/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/CondenserEquipmentOperationSchemes.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CondenserEquipmentOperationSchemes_DefaultConstructor) {
  Model model;
  CondenserEquipmentOperationSchemes condenserEquipmentOperationSchemes(model);
  EXPECT_EQ(CondenserEquipmentOperationSchemes::iddObjectType(), condenserEquipmentOperationSchemes.iddObject().type());
}

TEST_F(EPModelFixture, CondenserEquipmentOperationSchemes_ScalarAccessors_RoundTrip) {
  Model model;
  CondenserEquipmentOperationSchemes condenserEquipmentOperationSchemes(model);

  EXPECT_TRUE(condenserEquipmentOperationSchemes.setName("Main Condenser Equipment Operation Schemes"));
  EXPECT_EQ("Main Condenser Equipment Operation Schemes", condenserEquipmentOperationSchemes.nameString());
}
