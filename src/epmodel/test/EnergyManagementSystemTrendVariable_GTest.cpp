/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/EnergyManagementSystemTrendVariable.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, EnergyManagementSystemTrendVariable_DefaultConstructor) {
  Model model;
  EnergyManagementSystemTrendVariable emsTrendVariable(model, "glob_var");

  EXPECT_EQ(EnergyManagementSystemTrendVariable::iddObjectType(), emsTrendVariable.iddObject().type());
  EXPECT_EQ("glob_var", emsTrendVariable.emsVariableName());
  EXPECT_EQ(1, emsTrendVariable.numberOfTimestepsToBeLogged());
}

TEST_F(EPModelFixture, EnergyManagementSystemTrendVariable_ScalarAccessors_RoundTrip) {
  Model model;
  EnergyManagementSystemTrendVariable emsTrendVariable(model, "glob_var");

  EXPECT_TRUE(emsTrendVariable.setEMSVariableName("glob_var_2"));
  EXPECT_EQ("glob_var_2", emsTrendVariable.emsVariableName());

  EXPECT_TRUE(emsTrendVariable.setNumberOfTimestepsToBeLogged(2));
  EXPECT_EQ(2, emsTrendVariable.numberOfTimestepsToBeLogged());
}
