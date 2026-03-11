/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/SpaceHVACEquipmentConnections.hpp"
#include <utilities/idd/SpaceHVAC_EquipmentConnections_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SpaceHVACEquipmentConnections_DefaultConstructor) {
  Model model;
  SpaceHVACEquipmentConnections object(model);
  EXPECT_EQ(SpaceHVACEquipmentConnections::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, SpaceHVACEquipmentConnections_ScalarAccessors_RoundTrip) {
  Model model;
  SpaceHVACEquipmentConnections object(model);

  EXPECT_TRUE(object.setString(openstudio::SpaceHVAC_EquipmentConnectionsFields::SpaceAirNodeName, "Space Air Node 1"));
  EXPECT_EQ("Space Air Node 1", object.getString(openstudio::SpaceHVAC_EquipmentConnectionsFields::SpaceAirNodeName).get());
}
