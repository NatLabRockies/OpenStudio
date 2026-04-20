/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/PipeAdiabaticSteam.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, PipeAdiabaticSteam_DefaultConstructor) {
  Model model;
  PipeAdiabaticSteam pipe(model);
  EXPECT_EQ(PipeAdiabaticSteam::iddObjectType(), pipe.iddObject().type());
}

TEST_F(EPModelFixture, PipeAdiabaticSteam_ScalarAccessors_RoundTrip) {
  Model model;
  PipeAdiabaticSteam pipe(model);

  // Pipe:Adiabatic:Steam has no type-specific scalar accessors; verify base scalar roundtrip remains intact.
  EXPECT_TRUE(pipe.setName("Primary Steam Loop Bypass Pipe"));
  EXPECT_EQ("Primary Steam Loop Bypass Pipe", pipe.nameString());
}
