/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../StraightComponent/PipeOutdoor.hpp"
#include <utilities/idd/Pipe_Outdoor_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, PipeOutdoor_DefaultConstructor) {
  Model model;
  PipeOutdoor pipe(model);
  EXPECT_EQ(PipeOutdoor::iddObjectType(), pipe.iddObject().type());
  EXPECT_FALSE(pipe.nameString().empty());

  EXPECT_EQ(openstudio::Pipe_OutdoorFields::FluidInletNodeName, pipe.inletPort());
  EXPECT_EQ(openstudio::Pipe_OutdoorFields::FluidOutletNodeName, pipe.outletPort());

  EXPECT_DOUBLE_EQ(0.05, pipe.pipeInsideDiameter());
  EXPECT_DOUBLE_EQ(100.0, pipe.pipeLength());
}

TEST_F(EPModelFixture, PipeOutdoor_ScalarAccessors_RoundTrip) {
  Model model;
  PipeOutdoor pipe(model);

  EXPECT_TRUE(pipe.setPipeInsideDiameter(0.125));
  EXPECT_DOUBLE_EQ(0.125, pipe.pipeInsideDiameter());

  EXPECT_TRUE(pipe.setPipeLength(42.0));
  EXPECT_DOUBLE_EQ(42.0, pipe.pipeLength());
}
