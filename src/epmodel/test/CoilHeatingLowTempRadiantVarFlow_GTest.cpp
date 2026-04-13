/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <algorithm>
#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../StraightComponent/Node.hpp"
#include "../StraightComponent/CoilHeatingLowTempRadiantVarFlow.hpp"
#include "../StraightComponent/CoilHeatingLowTempRadiantVarFlow_Impl.hpp"
#include "../ZoneHVACComponent/ZoneHVACLowTempRadiantVarFlow.hpp"

using namespace openstudio;
using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilHeatingLowTempRadiantVarFlow_IsTransientCompanionView) {
  Model model;
  ZoneHVACLowTempRadiantVarFlow radiant(model);
  ASSERT_TRUE(radiant.setMaximumHotWaterFlow(0.004));
  auto heatingCoil = radiant.heatingCoil();
  ASSERT_TRUE(heatingCoil);
  auto typed = heatingCoil->cast<CoilHeatingLowTempRadiantVarFlow>();
  auto heatingImpl = typed.getImpl<openstudio::epmodel::detail::CoilHeatingLowTempRadiantVarFlow_Impl>();

  ASSERT_TRUE(heatingImpl);
  EXPECT_TRUE(heatingImpl->isTransient());
  ASSERT_TRUE(typed.containingZoneHVACComponent());
  EXPECT_EQ(radiant.handle(), typed.containingZoneHVACComponent()->handle());
}

TEST_F(EPModelFixture, CoilHeatingLowTempRadiantVarFlow_PlantLoopTraversalProjectsTransientChild) {
  Model model;
  PlantLoop plantLoop(model);
  ZoneHVACLowTempRadiantVarFlow radiant(model);
  ASSERT_TRUE(radiant.setMaximumHotWaterFlow(0.004));
  auto heatingCoil = radiant.heatingCoil()->cast<CoilHeatingLowTempRadiantVarFlow>();

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
