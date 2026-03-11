/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/AirflowNetworkDistributionComponentFan.hpp"
#include <utilities/idd/AirflowNetwork_Distribution_Component_Fan_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirflowNetworkDistributionComponentFan_DefaultConstructor) {
  Model model;
  AirflowNetworkDistributionComponentFan fan(model);
  EXPECT_EQ(AirflowNetworkDistributionComponentFan::iddObjectType(), fan.iddObject().type());
}

TEST_F(EPModelFixture, AirflowNetworkDistributionComponentFan_ScalarAccessors_RoundTrip) {
  Model model;
  AirflowNetworkDistributionComponentFan fan(model);

  EXPECT_FALSE(fan.setName("Main AFN Distribution Fan"));
  EXPECT_TRUE(fan.nameString().empty());

  EXPECT_TRUE(fan.setString(openstudio::AirflowNetwork_Distribution_Component_FanFields::SupplyFanObjectType, "Fan:VariableVolume"));
  auto supplyFanObjectType = fan.getString(openstudio::AirflowNetwork_Distribution_Component_FanFields::SupplyFanObjectType, true);
  ASSERT_TRUE(supplyFanObjectType);
  EXPECT_EQ("Fan:VariableVolume", *supplyFanObjectType);
}
