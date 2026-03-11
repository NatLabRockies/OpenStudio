/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/ExternalInterfaceVariable.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ExternalInterfaceVariable_Constructor) {
  Model model;
  ExternalInterfaceVariable variable(model, "myExternalVar", 2.5);
  EXPECT_EQ(ExternalInterfaceVariable::iddObjectType(), variable.iddObject().type());
  EXPECT_EQ("myExternalVar", variable.nameString());
  EXPECT_DOUBLE_EQ(2.5, variable.initialValue());
}

TEST_F(EPModelFixture, ExternalInterfaceVariable_ScalarAccessors_RoundTrip) {
  Model model;
  ExternalInterfaceVariable variable(model, "myExternalVar", 2.5);

  EXPECT_TRUE(variable.setInitialValue(11.75));
  EXPECT_DOUBLE_EQ(11.75, variable.initialValue());
}
