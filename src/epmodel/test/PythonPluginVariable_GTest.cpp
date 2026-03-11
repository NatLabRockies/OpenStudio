/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"

#include "../ModelObject/PythonPluginTrendVariable.hpp"
#include "../ModelObject/PythonPluginOutputVariable.hpp"
#include "../ModelObject/PythonPluginVariable.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, API_PythonPluginVariable_DefaultConstructor) {
  Model model;
  PythonPluginVariable variable(model);
  EXPECT_EQ(PythonPluginVariable::iddObjectType(), variable.iddObject().type());
  EXPECT_TRUE(variable.pythonPluginTrendVariables().empty());
  EXPECT_TRUE(variable.pythonPluginOutputVariables().empty());
}

TEST_F(EPModelFixture, PythonPluginVariable_ScalarAccessors_RoundTrip) {
  Model model;
  PythonPluginVariable variable(model);
  EXPECT_TRUE(variable.setName("PyVar"));
  EXPECT_EQ("PyVar", variable.nameString());
}
