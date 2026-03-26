/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../StraightComponent/Node.hpp"
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

TEST_F(EPModelFixture, PipeAdiabatic_AddToNode_PlantOnly) {
  Model model;
  PipeAdiabatic pipe(model);

  AirLoopHVAC airLoop(model);
  auto airSupplyOutletNode = airLoop.supplyOutletNode();
  EXPECT_FALSE(pipe.addToNode(airSupplyOutletNode));
  EXPECT_EQ(2u, airLoop.supplyComponents().size());

  PlantLoop plantLoop(model);
  auto supplyOutletNode = plantLoop.supplyOutletNode();
  EXPECT_TRUE(pipe.addToNode(supplyOutletNode));
  EXPECT_EQ(7u, plantLoop.supplyComponents().size());

  auto demandOutletNode = plantLoop.demandOutletNode();
  EXPECT_TRUE(pipe.addToNode(demandOutletNode));
  EXPECT_EQ(7u, plantLoop.demandComponents().size());

  PipeAdiabatic pipe2(model);
  EXPECT_TRUE(pipe2.addToNode(demandOutletNode));
  EXPECT_EQ(9u, plantLoop.demandComponents().size());
}
