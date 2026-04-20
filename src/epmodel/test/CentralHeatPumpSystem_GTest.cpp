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

#include <utilities/idd/CentralHeatPumpSystem_FieldEnums.hxx>

#include <limits>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CentralHeatPumpSystem_DefaultConstructor) {
  Model model;
  CentralHeatPumpSystem centralHeatPumpSystem(model);
  EXPECT_EQ(CentralHeatPumpSystem::iddObjectType(), centralHeatPumpSystem.iddObject().type());
  EXPECT_EQ("SmartMixing", centralHeatPumpSystem.controlMethod());
  EXPECT_DOUBLE_EQ(0.0, centralHeatPumpSystem.ancillaryPower());
  EXPECT_EQ(openstudio::CentralHeatPumpSystemFields::CoolingLoopInletNodeName, centralHeatPumpSystem.supplyInletPort());
  EXPECT_EQ(openstudio::CentralHeatPumpSystemFields::CoolingLoopOutletNodeName, centralHeatPumpSystem.supplyOutletPort());
  EXPECT_EQ(openstudio::CentralHeatPumpSystemFields::SourceLoopInletNodeName, centralHeatPumpSystem.demandInletPort());
  EXPECT_EQ(openstudio::CentralHeatPumpSystemFields::SourceLoopOutletNodeName, centralHeatPumpSystem.demandOutletPort());
  EXPECT_EQ(openstudio::CentralHeatPumpSystemFields::HeatingLoopInletNodeName, centralHeatPumpSystem.tertiaryInletPort());
  EXPECT_EQ(openstudio::CentralHeatPumpSystemFields::HeatingLoopOutletNodeName, centralHeatPumpSystem.tertiaryOutletPort());
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
  PlantLoop coolingLoop2(model);
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
  EXPECT_FALSE(centralHeatPumpSystem.sourcePlantLoop());
  EXPECT_FALSE(centralHeatPumpSystem.heatingPlantLoop());

  EXPECT_TRUE(sourceLoop.addDemandBranchForComponent(centralHeatPumpSystem));
  ASSERT_TRUE(centralHeatPumpSystem.sourcePlantLoop());
  EXPECT_EQ(sourceLoop.handle(), centralHeatPumpSystem.sourcePlantLoop()->handle());
  EXPECT_FALSE(centralHeatPumpSystem.heatingPlantLoop());

  auto heatingSupplyOutletNode = heatingLoop.supplyOutletNode();
  EXPECT_TRUE(centralHeatPumpSystem.addToNode(heatingSupplyOutletNode));
  EXPECT_TRUE(centralHeatPumpSystem.tertiaryInletModelObject());
  EXPECT_TRUE(centralHeatPumpSystem.tertiaryOutletModelObject());
  ASSERT_TRUE(centralHeatPumpSystem.heatingPlantLoop());
  EXPECT_EQ(heatingLoop.handle(), centralHeatPumpSystem.heatingPlantLoop()->handle());

  auto sourceDemandInletNode = sourceLoop.demandInletNode();
  EXPECT_FALSE(centralHeatPumpSystem.addToTertiaryNode(sourceDemandInletNode));
  ASSERT_TRUE(centralHeatPumpSystem.coolingPlantLoop());
  EXPECT_EQ(coolingLoop.handle(), centralHeatPumpSystem.coolingPlantLoop()->handle());
  ASSERT_TRUE(centralHeatPumpSystem.sourcePlantLoop());
  EXPECT_EQ(sourceLoop.handle(), centralHeatPumpSystem.sourcePlantLoop()->handle());
  ASSERT_TRUE(centralHeatPumpSystem.heatingPlantLoop());
  EXPECT_EQ(heatingLoop.handle(), centralHeatPumpSystem.heatingPlantLoop()->handle());

  auto coolingSupplyOutletNode2 = coolingLoop2.supplyOutletNode();
  EXPECT_TRUE(centralHeatPumpSystem.addToNode(coolingSupplyOutletNode2));

  ASSERT_TRUE(centralHeatPumpSystem.coolingPlantLoop());
  EXPECT_EQ(coolingLoop2.handle(), centralHeatPumpSystem.coolingPlantLoop()->handle());
  ASSERT_TRUE(centralHeatPumpSystem.sourcePlantLoop());
  EXPECT_EQ(sourceLoop.handle(), centralHeatPumpSystem.sourcePlantLoop()->handle());
  ASSERT_TRUE(centralHeatPumpSystem.heatingPlantLoop());
  EXPECT_EQ(heatingLoop.handle(), centralHeatPumpSystem.heatingPlantLoop()->handle());

  EXPECT_TRUE(centralHeatPumpSystem.removeFromTertiaryPlantLoop());
  EXPECT_FALSE(centralHeatPumpSystem.heatingPlantLoop());

  EXPECT_TRUE(centralHeatPumpSystem.addToTertiaryNode(heatingSupplyOutletNode));
  ASSERT_TRUE(centralHeatPumpSystem.heatingPlantLoop());
  EXPECT_EQ(heatingLoop.handle(), centralHeatPumpSystem.heatingPlantLoop()->handle());
}
