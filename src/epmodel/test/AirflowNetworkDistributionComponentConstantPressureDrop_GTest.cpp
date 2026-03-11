/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/AirflowNetworkDistributionComponentConstantPressureDrop.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirflowNetworkDistributionComponentConstantPressureDrop_DefaultConstructor) {
  Model model;
  AirflowNetworkDistributionComponentConstantPressureDrop constantPressureDrop(model);
  EXPECT_EQ(AirflowNetworkDistributionComponentConstantPressureDrop::iddObjectType(), constantPressureDrop.iddObject().type());
}

TEST_F(EPModelFixture, AirflowNetworkDistributionComponentConstantPressureDrop_ScalarAccessors_RoundTrip) {
  Model model;
  AirflowNetworkDistributionComponentConstantPressureDrop constantPressureDrop(model);

  EXPECT_TRUE(constantPressureDrop.setPressureDifferenceAcrosstheComponent(41.0));
  EXPECT_DOUBLE_EQ(41.0, constantPressureDrop.pressureDifferenceAcrosstheComponent());
}
