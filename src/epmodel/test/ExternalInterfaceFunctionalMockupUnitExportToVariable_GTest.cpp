/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/ExternalInterfaceFunctionalMockupUnitExportToVariable.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ExternalInterfaceFunctionalMockupUnitExportToVariable_Constructor) {
  Model model;
  ExternalInterfaceFunctionalMockupUnitExportToVariable object(model, "fmuVar", 10.0);
  EXPECT_EQ(ExternalInterfaceFunctionalMockupUnitExportToVariable::iddObjectType(), object.iddObject().type());
  EXPECT_EQ("fmuVar", object.fMUVariableName());
  EXPECT_DOUBLE_EQ(10.0, object.initialValue());
}

TEST_F(EPModelFixture, ExternalInterfaceFunctionalMockupUnitExportToVariable_ScalarAccessors_RoundTrip) {
  Model model;
  ExternalInterfaceFunctionalMockupUnitExportToVariable object(model, "fmuVar", 10.0);

  EXPECT_TRUE(object.setFMUVariableName("fmuVar2"));
  EXPECT_EQ("fmuVar2", object.fMUVariableName());

  EXPECT_TRUE(object.setInitialValue(22.5));
  EXPECT_DOUBLE_EQ(22.5, object.initialValue());
}
