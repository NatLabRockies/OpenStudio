/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/ExternalInterfaceFunctionalMockupUnitImportToActuator.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ExternalInterfaceFunctionalMockupUnitImportToActuator_DefaultConstructor) {
  Model model;
  ExternalInterfaceFunctionalMockupUnitImportToActuator object(model);
  EXPECT_EQ(ExternalInterfaceFunctionalMockupUnitImportToActuator::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, ExternalInterfaceFunctionalMockupUnitImportToActuator_ScalarAccessors_RoundTrip) {
  Model model;
  ExternalInterfaceFunctionalMockupUnitImportToActuator object(model);

  EXPECT_TRUE(object.setActuatedComponentType("Fan"));
  EXPECT_EQ("Fan", object.actuatedComponentType());

  EXPECT_TRUE(object.setActuatedComponentControlType("Fan Air Mass Flow Rate"));
  EXPECT_EQ("Fan Air Mass Flow Rate", object.actuatedComponentControlType());

  EXPECT_TRUE(object.setFMUInstanceName("fmuInstance"));
  EXPECT_EQ("fmuInstance", object.fMUInstanceName());

  EXPECT_TRUE(object.setFMUVariableName("fmuVariable"));
  EXPECT_EQ("fmuVariable", object.fMUVariableName());

  EXPECT_TRUE(object.setInitialValue(5.0));
  EXPECT_DOUBLE_EQ(5.0, object.initialValue());
}
