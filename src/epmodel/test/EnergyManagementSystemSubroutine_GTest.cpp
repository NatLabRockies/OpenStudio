/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/EnergyManagementSystemSubroutine.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, EnergyManagementSystemSubroutine_DefaultConstructor) {
  Model model;
  EnergyManagementSystemSubroutine emsSubroutine(model);
  EXPECT_EQ(EnergyManagementSystemSubroutine::iddObjectType(), emsSubroutine.iddObject().type());
}

TEST_F(EPModelFixture, EnergyManagementSystemSubroutine_ScalarAccessors_RoundTrip) {
  Model model;
  EnergyManagementSystemSubroutine emsSubroutine(model);

  EXPECT_TRUE(emsSubroutine.setName("EMS Subroutine"));
  EXPECT_EQ("EMS_Subroutine", emsSubroutine.nameString());
}
