/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <algorithm>
#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../StraightComponent/Node.hpp"
#include "../StraightComponent/CoilHeatingLowTempRadiantConstFlow.hpp"
#include "../StraightComponent/CoilHeatingLowTempRadiantConstFlow_Impl.hpp"
#include "../ZoneHVACComponent/ZoneHVACLowTempRadiantConstFlow.hpp"

using namespace openstudio;
using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilHeatingLowTempRadiantConstFlow_IsTransientCompanionView) {
  Model model;
  ZoneHVACLowTempRadiantConstFlow radiant(model);
  auto heatingCoil = radiant.heatingCoil();
  auto heatingImpl = heatingCoil.getImpl<openstudio::epmodel::detail::CoilHeatingLowTempRadiantConstFlow_Impl>();

  ASSERT_TRUE(heatingImpl);
  EXPECT_TRUE(heatingImpl->isTransient());
  ASSERT_TRUE(heatingCoil.containingZoneHVACComponent());
  EXPECT_EQ(radiant.handle(), heatingCoil.containingZoneHVACComponent()->handle());
}

TEST_F(EPModelFixture, CoilHeatingLowTempRadiantConstFlow_PlantLoopTraversalProjectsTransientChild) {
  Model model;
  PlantLoop plantLoop(model);
  ZoneHVACLowTempRadiantConstFlow radiant(model);
  auto heatingCoil = radiant.heatingCoil();

  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(heatingCoil));
  ASSERT_TRUE(heatingCoil.plantLoop());
  EXPECT_EQ(plantLoop.handle(), heatingCoil.plantLoop()->handle());
  EXPECT_FALSE(radiant.plantLoop());

  const auto demandComponents = plantLoop.demandComponents();
  EXPECT_TRUE(std::any_of(demandComponents.begin(), demandComponents.end(), [&](const auto& object) { return object.handle() == heatingCoil.handle(); }));
  EXPECT_FALSE(std::any_of(demandComponents.begin(), demandComponents.end(), [&](const auto& object) { return object.handle() == radiant.handle(); }));

  auto inletNode = heatingCoil.inletModelObject()->cast<Node>();
  ASSERT_TRUE(inletNode.outletModelObject());
  EXPECT_EQ(heatingCoil.handle(), inletNode.outletModelObject()->handle());

  ASSERT_TRUE(heatingCoil.removeFromLoop());
  EXPECT_FALSE(heatingCoil.plantLoop());
  EXPECT_FALSE(heatingCoil.inletModelObject());
  EXPECT_FALSE(heatingCoil.outletModelObject());
}
