/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/EnergyManagementSystemGlobalVariable.hpp"

#include <utilities/idd/EnergyManagementSystem_GlobalVariable_FieldEnums.hxx>
#include <utilities/idf/IdfExtensibleGroup.hpp>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, EnergyManagementSystemGlobalVariable_DefaultConstructor) {
  Model model;
  EnergyManagementSystemGlobalVariable globalVariable(model, "glob_var");
  EXPECT_EQ(EnergyManagementSystemGlobalVariable::iddObjectType(), globalVariable.iddObject().type());

  ASSERT_EQ(1u, globalVariable.numExtensibleGroups());
  const auto groups = globalVariable.extensibleGroups();
  ASSERT_FALSE(groups.empty());
  const auto value = groups.front().getString(openstudio::EnergyManagementSystem_GlobalVariableExtensibleFields::ErlVariableName, true);
  ASSERT_TRUE(value);
  EXPECT_EQ("glob_var", *value);
}

TEST_F(EPModelFixture, EnergyManagementSystemGlobalVariable_ScalarAccessors_RoundTrip) {
  Model model;
  EnergyManagementSystemGlobalVariable globalVariable(model, "glob_var");

  ASSERT_EQ(1u, globalVariable.numExtensibleGroups());
  auto groups = globalVariable.extensibleGroups();
  ASSERT_FALSE(groups.empty());

  EXPECT_TRUE(groups.front().setString(openstudio::EnergyManagementSystem_GlobalVariableExtensibleFields::ErlVariableName, "glob_var_2"));

  const auto value = groups.front().getString(openstudio::EnergyManagementSystem_GlobalVariableExtensibleFields::ErlVariableName, true);
  ASSERT_TRUE(value);
  EXPECT_EQ("glob_var_2", *value);
}
