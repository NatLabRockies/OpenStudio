/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../StraightComponent/PipeIndoor.hpp"
#include <utilities/idd/Pipe_Indoor_FieldEnums.hxx>
#include <algorithm>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, PipeIndoor_DefaultConstructor) {
  Model model;
  PipeIndoor pipe(model);
  EXPECT_EQ(PipeIndoor::iddObjectType(), pipe.iddObject().type());
  EXPECT_FALSE(pipe.nameString().empty());

  EXPECT_EQ(openstudio::Pipe_IndoorFields::FluidInletNodeName, pipe.inletPort());
  EXPECT_EQ(openstudio::Pipe_IndoorFields::FluidOutletNodeName, pipe.outletPort());

  EXPECT_EQ("Zone", pipe.environmentType());
  EXPECT_DOUBLE_EQ(0.05, pipe.pipeInsideDiameter());
  EXPECT_DOUBLE_EQ(100.0, pipe.pipeLength());
}

TEST_F(EPModelFixture, PipeIndoor_ScalarAccessors_RoundTrip) {
  Model model;
  PipeIndoor pipe(model);

  const auto envValues = PipeIndoor::environmentTypeValues();
  EXPECT_TRUE(std::find(envValues.begin(), envValues.end(), "Zone") != envValues.end());
  EXPECT_TRUE(std::find(envValues.begin(), envValues.end(), "Schedule") != envValues.end());

  EXPECT_TRUE(pipe.setEnvironmentType("Schedule"));
  EXPECT_EQ("Schedule", pipe.environmentType());

  EXPECT_TRUE(pipe.setPipeInsideDiameter(0.125));
  EXPECT_DOUBLE_EQ(0.125, pipe.pipeInsideDiameter());

  EXPECT_TRUE(pipe.setPipeLength(42.0));
  EXPECT_DOUBLE_EQ(42.0, pipe.pipeLength());

  EXPECT_FALSE(pipe.setEnvironmentType("InvalidOption"));
}
