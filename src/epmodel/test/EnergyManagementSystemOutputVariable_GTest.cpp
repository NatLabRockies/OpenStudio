/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/EnergyManagementSystemOutputVariable.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, EnergyManagementSystemOutputVariable_DefaultConstructor) {
  Model model;
  EnergyManagementSystemOutputVariable emsOutputVariable(model, "glob_var");

  EXPECT_EQ(EnergyManagementSystemOutputVariable::iddObjectType(), emsOutputVariable.iddObject().type());
  EXPECT_EQ("glob_var", emsOutputVariable.emsVariableName());
  EXPECT_EQ("Averaged", emsOutputVariable.typeOfDataInVariable());
  EXPECT_EQ("ZoneTimestep", emsOutputVariable.updateFrequency());
  EXPECT_TRUE(emsOutputVariable.units().empty());
}

TEST_F(EPModelFixture, EnergyManagementSystemOutputVariable_ScalarAccessors_RoundTrip) {
  Model model;
  EnergyManagementSystemOutputVariable emsOutputVariable(model, "glob_var");

  EXPECT_FALSE(EnergyManagementSystemOutputVariable::typeOfDataInVariableValues().empty());
  EXPECT_FALSE(EnergyManagementSystemOutputVariable::updateFrequencyValues().empty());

  EXPECT_TRUE(emsOutputVariable.setEMSVariableName("another_var"));
  EXPECT_EQ("another_var", emsOutputVariable.emsVariableName());

  EXPECT_TRUE(emsOutputVariable.setTypeOfDataInVariable("Summed"));
  EXPECT_EQ("Summed", emsOutputVariable.typeOfDataInVariable());

  EXPECT_TRUE(emsOutputVariable.setUpdateFrequency("SystemTimestep"));
  EXPECT_EQ("SystemTimestep", emsOutputVariable.updateFrequency());

  EXPECT_TRUE(emsOutputVariable.setUnits("W"));
  EXPECT_EQ("W", emsOutputVariable.units());

  emsOutputVariable.resetUnits();
  EXPECT_TRUE(emsOutputVariable.units().empty());
}
