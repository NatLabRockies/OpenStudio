/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include <algorithm>

#include "EPModelFixture.hpp"

#include <utilities/idd/WaterUse_Connections_FieldEnums.hxx>
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../ResourceObject/ScheduleTypeLimits.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../SpaceLoadInstance/WaterUseEquipment.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../StraightComponent/Node.hpp"
#include "../StraightComponent/WaterUseConnections.hpp"
#include "../StraightComponent/WaterUseConnections_Impl.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, WaterUseConnections_DefaultConstructor) {
  Model model;
  WaterUseConnections connections(model);
  EXPECT_EQ("None", connections.drainWaterHeatExchangerType());
  EXPECT_EQ("Plant", connections.drainWaterHeatExchangerDestination());
}

TEST_F(EPModelFixture, WaterUseConnections_ScheduleRelationships_RoundTrip) {
  Model model;
  WaterUseConnections connections(model);

  ScheduleConstant hotSchedule(model);
  ASSERT_TRUE(hotSchedule.setValue(60.0));
  EXPECT_TRUE(connections.setHotWaterSupplyTemperatureSchedule(hotSchedule));
  ASSERT_TRUE(connections.hotWaterSupplyTemperatureSchedule());
  EXPECT_EQ(hotSchedule.handle(), connections.hotWaterSupplyTemperatureSchedule()->handle());
  ASSERT_TRUE(hotSchedule.scheduleTypeLimits());
  EXPECT_EQ("Temperature", hotSchedule.scheduleTypeLimits()->unitType());
  ASSERT_TRUE(hotSchedule.scheduleTypeLimits()->numericType());
  EXPECT_EQ("Continuous", hotSchedule.scheduleTypeLimits()->numericType().get());

  ScheduleConstant coldSchedule(model);
  ASSERT_TRUE(coldSchedule.setValue(12.0));
  EXPECT_TRUE(connections.setColdWaterSupplyTemperatureSchedule(coldSchedule));
  ASSERT_TRUE(connections.coldWaterSupplyTemperatureSchedule());
  EXPECT_EQ(coldSchedule.handle(), connections.coldWaterSupplyTemperatureSchedule()->handle());
  ASSERT_TRUE(coldSchedule.scheduleTypeLimits());
  EXPECT_EQ("Temperature", coldSchedule.scheduleTypeLimits()->unitType());
  ASSERT_TRUE(coldSchedule.scheduleTypeLimits()->numericType());
  EXPECT_EQ("Continuous", coldSchedule.scheduleTypeLimits()->numericType().get());

  ScheduleConstant incompatibleSchedule(model);
  ASSERT_TRUE(incompatibleSchedule.setValue(1.0));
  ScheduleTypeLimits availabilityLimits(model);
  ASSERT_TRUE(availabilityLimits.setUnitType("Availability"));
  ASSERT_TRUE(incompatibleSchedule.setScheduleTypeLimits(availabilityLimits));

  EXPECT_FALSE(connections.setColdWaterSupplyTemperatureSchedule(incompatibleSchedule));
  ASSERT_TRUE(connections.coldWaterSupplyTemperatureSchedule());
  EXPECT_EQ(coldSchedule.handle(), connections.coldWaterSupplyTemperatureSchedule()->handle());

  connections.resetHotWaterSupplyTemperatureSchedule();
  EXPECT_FALSE(connections.hotWaterSupplyTemperatureSchedule());
  ASSERT_TRUE(connections.coldWaterSupplyTemperatureSchedule());
  EXPECT_EQ(coldSchedule.handle(), connections.coldWaterSupplyTemperatureSchedule()->handle());

  connections.resetColdWaterSupplyTemperatureSchedule();
  EXPECT_FALSE(connections.coldWaterSupplyTemperatureSchedule());
}

TEST_F(EPModelFixture, WaterUseConnections_ScheduleRelationships_RejectIncompatibleNumericTypeAndForeignModel) {
  Model model;
  WaterUseConnections connections(model);

  ScheduleConstant validSchedule(model);
  ASSERT_TRUE(validSchedule.setValue(55.0));
  EXPECT_TRUE(connections.setHotWaterSupplyTemperatureSchedule(validSchedule));

  ScheduleConstant discreteTemperatureSchedule(model);
  ASSERT_TRUE(discreteTemperatureSchedule.setValue(50.0));
  ScheduleTypeLimits discreteTemperatureLimits(model);
  ASSERT_TRUE(discreteTemperatureLimits.setUnitType("Temperature"));
  ASSERT_TRUE(discreteTemperatureLimits.setNumericType("Discrete"));
  ASSERT_TRUE(discreteTemperatureSchedule.setScheduleTypeLimits(discreteTemperatureLimits));
  EXPECT_FALSE(connections.setHotWaterSupplyTemperatureSchedule(discreteTemperatureSchedule));
  ASSERT_TRUE(connections.hotWaterSupplyTemperatureSchedule());
  EXPECT_EQ(validSchedule.handle(), connections.hotWaterSupplyTemperatureSchedule()->handle());

  Model otherModel;
  ScheduleConstant foreignSchedule(otherModel);
  ASSERT_TRUE(foreignSchedule.setValue(45.0));
  EXPECT_FALSE(connections.setHotWaterSupplyTemperatureSchedule(foreignSchedule));
  ASSERT_TRUE(connections.hotWaterSupplyTemperatureSchedule());
  EXPECT_EQ(validSchedule.handle(), connections.hotWaterSupplyTemperatureSchedule()->handle());
}

TEST_F(EPModelFixture, WaterUseConnections_WaterUseEquipment_ExtensibleOwnership) {
  Model model;
  WaterUseConnections connections(model);

  WaterUseEquipment equipment1(model);
  WaterUseEquipment equipment2(model);
  WaterUseEquipment equipment3(model);

  EXPECT_TRUE(connections.addWaterUseEquipment(equipment1));
  EXPECT_TRUE(connections.addWaterUseEquipment(equipment2));
  EXPECT_TRUE(connections.addWaterUseEquipment(equipment3));

  auto equipment = connections.waterUseEquipment();
  ASSERT_EQ(3u, equipment.size());
  EXPECT_EQ(equipment1.handle(), equipment[0].handle());
  EXPECT_EQ(equipment2.handle(), equipment[1].handle());
  EXPECT_EQ(equipment3.handle(), equipment[2].handle());

  EXPECT_TRUE(connections.removeWaterUseEquipment(equipment2));
  equipment = connections.waterUseEquipment();
  ASSERT_EQ(2u, equipment.size());
  EXPECT_EQ(equipment1.handle(), equipment[0].handle());
  EXPECT_EQ(equipment3.handle(), equipment[1].handle());

  auto cloneObject = model.addObject(connections.idfObject());
  ASSERT_TRUE(cloneObject);
  auto clone = cloneObject->cast<WaterUseConnections>();
  auto clonedEquipment = clone.waterUseEquipment();
  ASSERT_EQ(2u, clonedEquipment.size());
  EXPECT_EQ(equipment1.handle(), clonedEquipment[0].handle());
  EXPECT_EQ(equipment3.handle(), clonedEquipment[1].handle());
}

TEST_F(EPModelFixture, WaterUseConnections_WaterUseEquipment_RejectsForeignModelAndRemovesFirstDuplicate) {
  Model model;
  WaterUseConnections connections(model);

  WaterUseEquipment equipment1(model);
  WaterUseEquipment equipment2(model);
  EXPECT_TRUE(connections.addWaterUseEquipment(equipment1));
  EXPECT_TRUE(connections.addWaterUseEquipment(equipment2));
  EXPECT_TRUE(connections.addWaterUseEquipment(equipment1));

  auto equipment = connections.waterUseEquipment();
  ASSERT_EQ(3u, equipment.size());
  EXPECT_EQ(equipment1.handle(), equipment[0].handle());
  EXPECT_EQ(equipment2.handle(), equipment[1].handle());
  EXPECT_EQ(equipment1.handle(), equipment[2].handle());

  EXPECT_TRUE(connections.removeWaterUseEquipment(equipment1));
  equipment = connections.waterUseEquipment();
  ASSERT_EQ(2u, equipment.size());
  EXPECT_EQ(equipment2.handle(), equipment[0].handle());
  EXPECT_EQ(equipment1.handle(), equipment[1].handle());

  WaterUseEquipment missing(model);
  EXPECT_FALSE(connections.removeWaterUseEquipment(missing));

  Model otherModel;
  WaterUseEquipment foreignEquipment(otherModel);
  EXPECT_FALSE(connections.addWaterUseEquipment(foreignEquipment));
}

TEST_F(EPModelFixture, WaterUseConnections_AddToNode_PlantDemandOnly) {
  Model model;
  WaterUseConnections rejectedConnections(model);

  AirLoopHVAC airLoop(model);
  Node airSupplyOutletNode = airLoop.supplyOutletNode();
  const auto initialAirSupplyCount = airLoop.supplyComponents().size();
  EXPECT_FALSE(rejectedConnections.addToNode(airSupplyOutletNode));
  EXPECT_EQ(initialAirSupplyCount, airLoop.supplyComponents().size());

  Node airDemandNode = airLoop.zoneSplitter().lastOutletModelObject()->cast<Node>();
  const auto initialAirDemandCount = airLoop.demandComponents().size();
  EXPECT_FALSE(rejectedConnections.addToNode(airDemandNode));
  EXPECT_EQ(initialAirDemandCount, airLoop.demandComponents().size());

  PlantLoop plantLoop(model);
  Node plantSupplyOutletNode = plantLoop.supplyOutletNode();
  const auto initialPlantSupplyCount = plantLoop.supplyComponents().size();
  EXPECT_FALSE(rejectedConnections.addToNode(plantSupplyOutletNode));
  EXPECT_EQ(initialPlantSupplyCount, plantLoop.supplyComponents().size());

  Node unconnectedNode = model.getOrCreateTransientByName<Node>("Unconnected WaterUseConnections Node");
  EXPECT_FALSE(rejectedConnections.addToNode(unconnectedNode));
  EXPECT_FALSE(rejectedConnections.loop());
  EXPECT_FALSE(rejectedConnections.inletModelObject());
  EXPECT_FALSE(rejectedConnections.outletModelObject());

  WaterUseConnections connections(model);
  Node plantDemandOutletNode = plantLoop.demandOutletNode();
  const auto initialPlantDemandCount = plantLoop.demandComponents().size();
  EXPECT_TRUE(connections.addToNode(plantDemandOutletNode));
  EXPECT_GT(plantLoop.demandComponents().size(), initialPlantDemandCount);
  ASSERT_TRUE(connections.plantLoop());
  EXPECT_EQ(plantLoop.handle(), connections.plantLoop()->handle());
  ASSERT_TRUE(connections.inletModelObject());
  ASSERT_TRUE(connections.outletModelObject());

  auto inletNode = connections.inletModelObject()->optionalCast<Node>();
  auto outletNode = connections.outletModelObject()->optionalCast<Node>();
  ASSERT_TRUE(inletNode);
  ASSERT_TRUE(outletNode);
  EXPECT_EQ(connections.getModelObjectTarget<Node>(openstudio::WaterUse_ConnectionsFields::InletNodeName)->handle(), inletNode->handle());
  EXPECT_EQ(connections.getModelObjectTarget<Node>(openstudio::WaterUse_ConnectionsFields::OutletNodeName)->handle(), outletNode->handle());

  auto cloneObject = model.addObject(connections.idfObject());
  ASSERT_TRUE(cloneObject);
  auto clone = cloneObject->cast<WaterUseConnections>();
  Node freshDemandOutletNode = plantLoop.demandOutletNode();
  EXPECT_TRUE(clone.addToNode(freshDemandOutletNode));
  EXPECT_EQ(2u, plantLoop.demandComponents(WaterUseConnections::iddObjectType()).size());

  PlantLoop secondPlantLoop(model);
  WaterUseConnections inletSideConnections(model);
  Node plantDemandInletNode = secondPlantLoop.demandInletNode();
  const auto initialSecondDemandCount = secondPlantLoop.demandComponents().size();
  EXPECT_TRUE(inletSideConnections.addToNode(plantDemandInletNode));
  EXPECT_GT(secondPlantLoop.demandComponents().size(), initialSecondDemandCount);
  ASSERT_TRUE(inletSideConnections.plantLoop());
  EXPECT_EQ(secondPlantLoop.handle(), inletSideConnections.plantLoop()->handle());
  ASSERT_TRUE(inletSideConnections.inletModelObject());
  ASSERT_TRUE(inletSideConnections.outletModelObject());
}

TEST_F(EPModelFixture, WaterUseConnections_ScalarAccessors_RoundTrip) {
  Model model;
  WaterUseConnections connections(model);

  const auto typeValues = WaterUseConnections::drainWaterHeatExchangerTypeValues();
  EXPECT_NE(typeValues.end(), std::find(typeValues.begin(), typeValues.end(), "None"));
  EXPECT_NE(typeValues.end(), std::find(typeValues.begin(), typeValues.end(), "CrossFlow"));

  const auto destinationValues = WaterUseConnections::drainWaterHeatExchangerDestinationValues();
  EXPECT_NE(destinationValues.end(), std::find(destinationValues.begin(), destinationValues.end(), "Plant"));
  EXPECT_NE(destinationValues.end(), std::find(destinationValues.begin(), destinationValues.end(), "Equipment"));

  EXPECT_FALSE(connections.setDrainWaterHeatExchangerType("Idea1"));
  EXPECT_TRUE(connections.setDrainWaterHeatExchangerType("CounterFlow"));
  EXPECT_EQ("CounterFlow", connections.drainWaterHeatExchangerType());

  EXPECT_FALSE(connections.setDrainWaterHeatExchangerDestination("Eqiupment"));
  EXPECT_TRUE(connections.setDrainWaterHeatExchangerDestination("Equipment"));
  EXPECT_EQ("Equipment", connections.drainWaterHeatExchangerDestination());

  EXPECT_FALSE(connections.setDrainWaterHeatExchangerUFactorTimesArea(-1.0));
  EXPECT_TRUE(connections.setDrainWaterHeatExchangerUFactorTimesArea(123.0));
  ASSERT_TRUE(connections.drainWaterHeatExchangerUFactorTimesArea());
  EXPECT_DOUBLE_EQ(123.0, connections.drainWaterHeatExchangerUFactorTimesArea().get());
  connections.resetDrainWaterHeatExchangerUFactorTimesArea();
  EXPECT_FALSE(connections.drainWaterHeatExchangerUFactorTimesArea());
}
