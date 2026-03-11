/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../StraightComponent/PipeAdiabatic.hpp"
#include <utilities/idd/Pipe_Adiabatic_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, PipeAdiabatic_DefaultConstructor) {
  Model model;
  PipeAdiabatic pipe(model);
  EXPECT_EQ(PipeAdiabatic::iddObjectType(), pipe.iddObject().type());
  EXPECT_FALSE(pipe.nameString().empty());
  EXPECT_EQ(openstudio::Pipe_AdiabaticFields::InletNodeName, pipe.inletPort());
  EXPECT_EQ(openstudio::Pipe_AdiabaticFields::OutletNodeName, pipe.outletPort());
}

TEST_F(EPModelFixture, PipeAdiabatic_ScalarAccessors_RoundTrip) {
  Model model;
  PipeAdiabatic pipe(model);

  // Pipe:Adiabatic has no type-specific scalar accessors; verify base scalar roundtrip remains intact.
  EXPECT_TRUE(pipe.setName("Primary Loop Bypass Pipe"));
  EXPECT_EQ("Primary Loop Bypass Pipe", pipe.nameString());
}
