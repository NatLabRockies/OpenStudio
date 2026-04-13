/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <algorithm>
#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../StraightComponent/Node.hpp"
#include "../StraightComponent/CoilCoolingLowTempRadiantVarFlow.hpp"
#include "../StraightComponent/CoilCoolingLowTempRadiantVarFlow_Impl.hpp"
#include "../ZoneHVACComponent/ZoneHVACLowTempRadiantVarFlow.hpp"

using namespace openstudio;
using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilCoolingLowTempRadiantVarFlow_IsTransientCompanionView) {
  Model model;
  ZoneHVACLowTempRadiantVarFlow radiant(model);
  ASSERT_TRUE(radiant.setMaximumColdWaterFlow(0.003));
  auto coolingCoil = radiant.coolingCoil();
  ASSERT_TRUE(coolingCoil);
  auto typed = coolingCoil->cast<CoilCoolingLowTempRadiantVarFlow>();
  auto coolingImpl = typed.getImpl<openstudio::epmodel::detail::CoilCoolingLowTempRadiantVarFlow_Impl>();

  ASSERT_TRUE(coolingImpl);
  EXPECT_TRUE(coolingImpl->isTransient());
  ASSERT_TRUE(typed.containingZoneHVACComponent());
  EXPECT_EQ(radiant.handle(), typed.containingZoneHVACComponent()->handle());
}

TEST_F(EPModelFixture, CoilCoolingLowTempRadiantVarFlow_PlantLoopTraversalProjectsTransientChild) {
  Model model;
  PlantLoop plantLoop(model);
  ZoneHVACLowTempRadiantVarFlow radiant(model);
  ASSERT_TRUE(radiant.setMaximumColdWaterFlow(0.003));
  auto coolingCoil = radiant.coolingCoil()->cast<CoilCoolingLowTempRadiantVarFlow>();

  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(coolingCoil));
  ASSERT_TRUE(coolingCoil.plantLoop());
  EXPECT_EQ(plantLoop.handle(), coolingCoil.plantLoop()->handle());
  EXPECT_FALSE(radiant.plantLoop());

  const auto demandComponents = plantLoop.demandComponents();
  EXPECT_TRUE(std::any_of(demandComponents.begin(), demandComponents.end(), [&](const auto& object) { return object.handle() == coolingCoil.handle(); }));
  EXPECT_FALSE(std::any_of(demandComponents.begin(), demandComponents.end(), [&](const auto& object) { return object.handle() == radiant.handle(); }));

  auto inletNode = coolingCoil.inletModelObject()->cast<Node>();
  ASSERT_TRUE(inletNode.outletModelObject());
  EXPECT_EQ(coolingCoil.handle(), inletNode.outletModelObject()->handle());

  ASSERT_TRUE(coolingCoil.removeFromLoop());
  EXPECT_FALSE(coolingCoil.plantLoop());
  EXPECT_FALSE(coolingCoil.inletModelObject());
  EXPECT_FALSE(coolingCoil.outletModelObject());
}
