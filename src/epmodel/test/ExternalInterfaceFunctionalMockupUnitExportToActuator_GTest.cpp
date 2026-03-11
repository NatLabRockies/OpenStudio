/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/ExternalInterfaceFunctionalMockupUnitExportToActuator.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ExternalInterfaceFunctionalMockupUnitExportToActuator_DefaultConstructor) {
  Model model;
  ExternalInterfaceFunctionalMockupUnitExportToActuator object(model);
  EXPECT_EQ(ExternalInterfaceFunctionalMockupUnitExportToActuator::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, ExternalInterfaceFunctionalMockupUnitExportToActuator_ScalarAccessors_RoundTrip) {
  Model model;
  ExternalInterfaceFunctionalMockupUnitExportToActuator object(model);

  EXPECT_TRUE(object.setActuatedComponentType("Fan"));
  EXPECT_EQ("Fan", object.actuatedComponentType());

  EXPECT_TRUE(object.setActuatedComponentControlType("Fan Air Mass Flow Rate"));
  EXPECT_EQ("Fan Air Mass Flow Rate", object.actuatedComponentControlType());

  EXPECT_TRUE(object.setFMUVariableName("fan_fmu_var"));
  EXPECT_EQ("fan_fmu_var", object.fMUVariableName());

  EXPECT_FALSE(object.initialValue());
  EXPECT_TRUE(object.setInitialValue(10.0));
  ASSERT_TRUE(object.initialValue());
  EXPECT_DOUBLE_EQ(10.0, object.initialValue().get());
}
