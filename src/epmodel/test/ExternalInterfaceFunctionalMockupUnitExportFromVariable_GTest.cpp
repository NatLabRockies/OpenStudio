/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/ExternalInterfaceFunctionalMockupUnitExportFromVariable.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ExternalInterfaceFunctionalMockupUnitExportFromVariable_Constructor) {
  Model model;
  ExternalInterfaceFunctionalMockupUnitExportFromVariable object(model, "ZONE ONE", "Zone Mean Air Temperature", "fmuVar");
  EXPECT_EQ(ExternalInterfaceFunctionalMockupUnitExportFromVariable::iddObjectType(), object.iddObject().type());
  EXPECT_EQ("ZONE ONE", object.outputVariableIndexKeyName());
  EXPECT_EQ("Zone Mean Air Temperature", object.outputVariableName());
  EXPECT_EQ("fmuVar", object.fMUVariableName());
}

TEST_F(EPModelFixture, ExternalInterfaceFunctionalMockupUnitExportFromVariable_ScalarAccessors_RoundTrip) {
  Model model;
  ExternalInterfaceFunctionalMockupUnitExportFromVariable object(model, "ZONE ONE", "Zone Mean Air Temperature", "fmuVar");

  EXPECT_TRUE(object.setOutputVariableIndexKeyName("ZONE TWO"));
  EXPECT_EQ("ZONE TWO", object.outputVariableIndexKeyName());

  EXPECT_TRUE(object.setOutputVariableName("Zone Air Humidity Ratio"));
  EXPECT_EQ("Zone Air Humidity Ratio", object.outputVariableName());

  EXPECT_TRUE(object.setFMUVariableName("fmuVar2"));
  EXPECT_EQ("fmuVar2", object.fMUVariableName());
}
