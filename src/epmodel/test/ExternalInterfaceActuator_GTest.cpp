/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/ExternalInterfaceActuator.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ExternalInterfaceActuator_DefaultConstructor) {
  Model model;
  ExternalInterfaceActuator actuator(model);
  EXPECT_EQ(ExternalInterfaceActuator::iddObjectType(), actuator.iddObject().type());
}

TEST_F(EPModelFixture, ExternalInterfaceActuator_ScalarAccessors_RoundTrip) {
  Model model;
  ExternalInterfaceActuator actuator(model);

  EXPECT_TRUE(actuator.setActuatedComponentType("Fan"));
  EXPECT_EQ("Fan", actuator.actuatedComponentType());

  EXPECT_TRUE(actuator.setActuatedComponentControlType("Fan Air Mass Flow Rate"));
  EXPECT_EQ("Fan Air Mass Flow Rate", actuator.actuatedComponentControlType());

  EXPECT_FALSE(actuator.optionalInitialValue());
  EXPECT_TRUE(actuator.setOptionalInitialValue(1.0));
  ASSERT_TRUE(actuator.optionalInitialValue());
  EXPECT_DOUBLE_EQ(1.0, actuator.optionalInitialValue().get());
  actuator.resetOptionalInitialValue();
  EXPECT_FALSE(actuator.optionalInitialValue());
}
