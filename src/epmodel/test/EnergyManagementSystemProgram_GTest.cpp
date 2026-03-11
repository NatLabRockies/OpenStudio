/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/EnergyManagementSystemProgram.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, EnergyManagementSystemProgram_DefaultConstructor) {
  Model model;
  EnergyManagementSystemProgram emsProgram(model);
  EXPECT_EQ(EnergyManagementSystemProgram::iddObjectType(), emsProgram.iddObject().type());
}

TEST_F(EPModelFixture, EnergyManagementSystemProgram_ScalarAccessors_RoundTrip) {
  Model model;
  EnergyManagementSystemProgram emsProgram(model);

  EXPECT_TRUE(emsProgram.setName("EMS Program"));
  EXPECT_EQ("EMS_Program", emsProgram.nameString());
}
