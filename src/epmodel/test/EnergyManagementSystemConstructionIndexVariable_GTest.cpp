/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/EnergyManagementSystemConstructionIndexVariable.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, EnergyManagementSystemConstructionIndexVariable_DefaultConstructor) {
  Model model;
  EnergyManagementSystemConstructionIndexVariable emsConstructionIndexVariable(model);
  EXPECT_EQ(EnergyManagementSystemConstructionIndexVariable::iddObjectType(), emsConstructionIndexVariable.iddObject().type());
}

TEST_F(EPModelFixture, EnergyManagementSystemConstructionIndexVariable_ScalarAccessors_RoundTrip) {
  Model model;
  EnergyManagementSystemConstructionIndexVariable emsConstructionIndexVariable(model);

  EXPECT_TRUE(emsConstructionIndexVariable.setName("EMS Construction Index"));
  EXPECT_EQ("EMS_Construction_Index", emsConstructionIndexVariable.nameString());
}
