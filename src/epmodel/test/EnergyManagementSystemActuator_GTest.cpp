/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/EnergyManagementSystemActuator.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, EnergyManagementSystemActuator_DefaultConstructor) {
  Model model;
  EnergyManagementSystemActuator actuator(model);
  EXPECT_EQ(EnergyManagementSystemActuator::iddObjectType(), actuator.iddObject().type());
}

TEST_F(EPModelFixture, EnergyManagementSystemActuator_ScalarAccessors_RoundTrip) {
  Model model;
  EnergyManagementSystemActuator actuator(model);

  EXPECT_TRUE(actuator.setActuatedComponentType("Fan"));
  EXPECT_EQ("Fan", actuator.actuatedComponentType());

  EXPECT_TRUE(actuator.setActuatedComponentControlType("Fan Air Mass Flow Rate"));
  EXPECT_EQ("Fan Air Mass Flow Rate", actuator.actuatedComponentControlType());
}
