/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../StraightComponent/Node.hpp"
#include "../WaterToWaterComponent/CentralHeatPumpSystem.hpp"

#include <limits>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CentralHeatPumpSystem_DefaultConstructor) {
  Model model;
  CentralHeatPumpSystem centralHeatPumpSystem(model);
  EXPECT_EQ(CentralHeatPumpSystem::iddObjectType(), centralHeatPumpSystem.iddObject().type());
  EXPECT_EQ("SmartMixing", centralHeatPumpSystem.controlMethod());
  EXPECT_DOUBLE_EQ(0.0, centralHeatPumpSystem.ancillaryPower());
  EXPECT_NE(std::numeric_limits<unsigned>::max(), centralHeatPumpSystem.supplyInletPort());
  EXPECT_NE(std::numeric_limits<unsigned>::max(), centralHeatPumpSystem.demandInletPort());
  EXPECT_NE(std::numeric_limits<unsigned>::max(), centralHeatPumpSystem.tertiaryInletPort());
  EXPECT_FALSE(centralHeatPumpSystem.ancillaryOperationSchedule());
}

TEST_F(EPModelFixture, CentralHeatPumpSystem_ScalarAccessors_RoundTrip) {
  Model model;
  CentralHeatPumpSystem centralHeatPumpSystem(model);

  const auto values = CentralHeatPumpSystem::controlMethodValues();
  ASSERT_FALSE(values.empty());
  EXPECT_TRUE(centralHeatPumpSystem.setControlMethod(values.front()));
  EXPECT_EQ(values.front(), centralHeatPumpSystem.controlMethod());

  EXPECT_TRUE(centralHeatPumpSystem.setAncillaryPower(17.25));
  EXPECT_DOUBLE_EQ(17.25, centralHeatPumpSystem.ancillaryPower());
}

TEST_F(EPModelFixture, CentralHeatPumpSystem_RelationshipAndThreeLoopTopology) {
  Model model;
  CentralHeatPumpSystem centralHeatPumpSystem(model);
  ScheduleConstant ancillarySchedule(model);
  PlantLoop coolingLoop(model);
  PlantLoop sourceLoop(model);
  PlantLoop heatingLoop(model);

  ASSERT_TRUE(ancillarySchedule.setValue(1.0));

  EXPECT_TRUE(centralHeatPumpSystem.setAncillaryOperationSchedule(ancillarySchedule));
  ASSERT_TRUE(centralHeatPumpSystem.ancillaryOperationSchedule());
  EXPECT_EQ(ancillarySchedule.handle(), centralHeatPumpSystem.ancillaryOperationSchedule()->handle());
  centralHeatPumpSystem.resetAncillaryOperationSchedule();
  EXPECT_FALSE(centralHeatPumpSystem.ancillaryOperationSchedule());

  EXPECT_TRUE(coolingLoop.addSupplyBranchForComponent(centralHeatPumpSystem));
  ASSERT_TRUE(centralHeatPumpSystem.coolingPlantLoop());
  EXPECT_EQ(coolingLoop.handle(), centralHeatPumpSystem.coolingPlantLoop()->handle());

  EXPECT_TRUE(sourceLoop.addDemandBranchForComponent(centralHeatPumpSystem));
  ASSERT_TRUE(centralHeatPumpSystem.sourcePlantLoop());
  EXPECT_EQ(sourceLoop.handle(), centralHeatPumpSystem.sourcePlantLoop()->handle());

  auto heatingSupplyOutletNode = heatingLoop.supplyOutletNode();
  EXPECT_TRUE(centralHeatPumpSystem.addToTertiaryNode(heatingSupplyOutletNode));
  EXPECT_TRUE(centralHeatPumpSystem.tertiaryInletModelObject());
  EXPECT_TRUE(centralHeatPumpSystem.tertiaryOutletModelObject());
}
