/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/EnergyManagementSystemCurveOrTableIndexVariable.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, EnergyManagementSystemCurveOrTableIndexVariable_DefaultConstructor) {
  Model model;
  EnergyManagementSystemCurveOrTableIndexVariable emsCurveOrTableIndexVariable(model);
  EXPECT_EQ(EnergyManagementSystemCurveOrTableIndexVariable::iddObjectType(), emsCurveOrTableIndexVariable.iddObject().type());
}

TEST_F(EPModelFixture, EnergyManagementSystemCurveOrTableIndexVariable_ScalarAccessors_RoundTrip) {
  Model model;
  EnergyManagementSystemCurveOrTableIndexVariable emsCurveOrTableIndexVariable(model);

  EXPECT_TRUE(emsCurveOrTableIndexVariable.setName("EMS Curve Or Table Index"));
  EXPECT_EQ("EMS_Curve_Or_Table_Index", emsCurveOrTableIndexVariable.nameString());
}
