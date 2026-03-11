/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/ExternalInterfaceFunctionalMockupUnitImportToVariable.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ExternalInterfaceFunctionalMockupUnitImportToVariable_DefaultConstructor) {
  Model model;
  ExternalInterfaceFunctionalMockupUnitImportToVariable object(model);
  EXPECT_EQ(ExternalInterfaceFunctionalMockupUnitImportToVariable::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, ExternalInterfaceFunctionalMockupUnitImportToVariable_ScalarAccessors_RoundTrip) {
  Model model;
  ExternalInterfaceFunctionalMockupUnitImportToVariable object(model);

  EXPECT_TRUE(object.setFMUInstanceName("fmuInstance"));
  EXPECT_EQ("fmuInstance", object.fMUInstanceName());

  EXPECT_TRUE(object.setFMUVariableName("fmuVariable"));
  EXPECT_EQ("fmuVariable", object.fMUVariableName());

  EXPECT_TRUE(object.setInitialValue(12.5));
  EXPECT_DOUBLE_EQ(12.5, object.initialValue());
}
