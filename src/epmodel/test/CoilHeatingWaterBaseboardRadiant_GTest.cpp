/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <algorithm>
#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../StraightComponent/CoilHeatingWaterBaseboardRadiant.hpp"
#include "../StraightComponent/CoilHeatingWaterBaseboardRadiant_Impl.hpp"
#include "../StraightComponent/Node.hpp"
#include "../ZoneHVACComponent/ZoneHVACBaseboardRadiantConvectiveWater.hpp"

using namespace openstudio;
using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilHeatingWaterBaseboardRadiant_IsTransientCompanionView) {
  Model model;
  ZoneHVACBaseboardRadiantConvectiveWater baseboard(model);
  auto heatingCoil = baseboard.heatingCoil();
  auto heatingImpl = heatingCoil.getImpl<openstudio::epmodel::detail::CoilHeatingWaterBaseboardRadiant_Impl>();

  ASSERT_TRUE(heatingImpl);
  EXPECT_TRUE(heatingImpl->isTransient());
  ASSERT_TRUE(heatingCoil.containingZoneHVACComponent());
  EXPECT_EQ(baseboard.handle(), heatingCoil.containingZoneHVACComponent()->handle());
}

TEST_F(EPModelFixture, CoilHeatingWaterBaseboardRadiant_PlantLoopTraversalProjectsTransientChild) {
  Model model;
  PlantLoop plantLoop(model);
  ZoneHVACBaseboardRadiantConvectiveWater baseboard(model);
  auto heatingCoil = baseboard.heatingCoil();

  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(heatingCoil));
  ASSERT_TRUE(heatingCoil.plantLoop());
  EXPECT_EQ(plantLoop.handle(), heatingCoil.plantLoop()->handle());
  EXPECT_FALSE(baseboard.plantLoop());

  const auto demandComponents = plantLoop.demandComponents();
  EXPECT_TRUE(std::any_of(demandComponents.begin(), demandComponents.end(),
                          [&](const auto& object) { return object.handle() == heatingCoil.handle(); }));
  EXPECT_FALSE(std::any_of(demandComponents.begin(), demandComponents.end(),
                           [&](const auto& object) { return object.handle() == baseboard.handle(); }));

  auto inletNode = heatingCoil.inletModelObject()->cast<Node>();
  ASSERT_TRUE(inletNode.outletModelObject());
  EXPECT_EQ(heatingCoil.handle(), inletNode.outletModelObject()->handle());

  ASSERT_TRUE(heatingCoil.removeFromLoop());
  EXPECT_FALSE(heatingCoil.plantLoop());
  EXPECT_FALSE(heatingCoil.inletModelObject());
  EXPECT_FALSE(heatingCoil.outletModelObject());
}
