/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include <algorithm>

#include "EPModelFixture.hpp"
#include "../ModelObject/CoilSystemHeatingDX.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilSystemHeatingDX_DefaultConstructor) {
  Model model;
  CoilSystemHeatingDX coilSystem(model);
  EXPECT_EQ(CoilSystemHeatingDX::iddObjectType(), coilSystem.iddObject().type());
  EXPECT_FALSE(coilSystem.nameString().empty());
}

TEST_F(EPModelFixture, CoilSystemHeatingDX_ScalarAccessors_RoundTrip) {
  Model model;
  CoilSystemHeatingDX coilSystem(model);

  const auto heatingCoilObjectTypes = CoilSystemHeatingDX::heatingCoilObjectTypeValues();
  EXPECT_FALSE(heatingCoilObjectTypes.empty());
  EXPECT_TRUE(std::find(heatingCoilObjectTypes.begin(), heatingCoilObjectTypes.end(), "Coil:Heating:DX:SingleSpeed") != heatingCoilObjectTypes.end());
  EXPECT_TRUE(std::find(heatingCoilObjectTypes.begin(), heatingCoilObjectTypes.end(), "Coil:Heating:DX:VariableSpeed")
              != heatingCoilObjectTypes.end());

  EXPECT_TRUE(coilSystem.setHeatingCoilObjectType("Coil:Heating:DX:SingleSpeed"));
  EXPECT_EQ("Coil:Heating:DX:SingleSpeed", coilSystem.heatingCoilObjectType());
  EXPECT_TRUE(coilSystem.setHeatingCoilObjectType("Coil:Heating:DX:VariableSpeed"));
  EXPECT_EQ("Coil:Heating:DX:VariableSpeed", coilSystem.heatingCoilObjectType());
  EXPECT_FALSE(coilSystem.setHeatingCoilObjectType("Invalid Heating Coil Type"));
}
