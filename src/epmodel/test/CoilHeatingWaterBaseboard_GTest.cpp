/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <algorithm>
#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../StraightComponent/CoilHeatingWaterBaseboard.hpp"
#include "../StraightComponent/CoilHeatingWaterBaseboard_Impl.hpp"
#include "../StraightComponent/Node.hpp"
#include "../ZoneHVACComponent/ZoneHVACBaseboardConvectiveWater.hpp"

using namespace openstudio;
using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilHeatingWaterBaseboard_IsTransientCompanionView) {
  Model model;
  ZoneHVACBaseboardConvectiveWater baseboard(model);
  auto heatingCoil = baseboard.heatingCoil();
  auto heatingImpl = heatingCoil.getImpl<openstudio::epmodel::detail::CoilHeatingWaterBaseboard_Impl>();

  ASSERT_TRUE(heatingImpl);
  EXPECT_TRUE(heatingImpl->isTransient());
  ASSERT_TRUE(heatingCoil.containingZoneHVACComponent());
  EXPECT_EQ(baseboard.handle(), heatingCoil.containingZoneHVACComponent()->handle());
}

TEST_F(EPModelFixture, CoilHeatingWaterBaseboard_PlantLoopTraversalProjectsTransientChild) {
  Model model;
  PlantLoop plantLoop(model);
  ZoneHVACBaseboardConvectiveWater baseboard(model);
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
