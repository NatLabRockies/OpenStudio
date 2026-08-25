/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../AirToAirComponent/HeatExchangerDesiccantBalancedFlow.hpp"
#include "../AirToAirComponent/HeatExchangerDesiccantBalancedFlow_Impl.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem_Impl.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../ResourceObject/HeatExchangerDesiccantBalancedFlowPerformanceDataType1.hpp"
#include "../ResourceObject/HeatExchangerDesiccantBalancedFlowPerformanceDataType1_Impl.hpp"
#include "../ResourceObject/ScheduleTypeLimits.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../StraightComponent/Node.hpp"

#include <utilities/idd/HeatExchanger_Desiccant_BalancedFlow_FieldEnums.hxx>

#include <stdexcept>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, HeatExchangerDesiccantBalancedFlow_DefaultConstructor) {
  Model model;
  HeatExchangerDesiccantBalancedFlow object(model);

  EXPECT_EQ(HeatExchangerDesiccantBalancedFlow::iddObjectType(), object.iddObject().type());
  EXPECT_EQ(model.alwaysOnDiscreteSchedule(), object.availabilitySchedule());
  EXPECT_EQ(1u, model.getConcreteModelObjects<HeatExchangerDesiccantBalancedFlowPerformanceDataType1>().size());
  EXPECT_EQ(model.getConcreteModelObjects<HeatExchangerDesiccantBalancedFlowPerformanceDataType1>().front(), object.heatExchangerPerformance());
  EXPECT_TRUE(object.economizerLockout());
}

TEST_F(EPModelFixture, HeatExchangerDesiccantBalancedFlow_CanonicalizeRepairsRequiredRelationships) {
  Model model;
  HeatExchangerDesiccantBalancedFlow object(model);
  const auto originalPerformance = object.heatExchangerPerformance();

  ASSERT_TRUE(object.setString(openstudio::HeatExchanger_Desiccant_BalancedFlowFields::AvailabilityScheduleName, ""));
  ASSERT_TRUE(object.setString(openstudio::HeatExchanger_Desiccant_BalancedFlowFields::HeatExchangerPerformanceName, ""));

  auto report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);
  EXPECT_EQ(model.alwaysOnDiscreteSchedule(), object.availabilitySchedule());
  EXPECT_NE(originalPerformance, object.heatExchangerPerformance());
  EXPECT_EQ(object.heatExchangerPerformance().iddObject().name(),
            object.getString(openstudio::HeatExchanger_Desiccant_BalancedFlowFields::HeatExchangerPerformanceObjectType).get());

  const auto performanceCount = model.getConcreteModelObjects<HeatExchangerDesiccantBalancedFlowPerformanceDataType1>().size();
  report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);
  EXPECT_EQ(performanceCount, model.getConcreteModelObjects<HeatExchangerDesiccantBalancedFlowPerformanceDataType1>().size());
}

TEST_F(EPModelFixture, HeatExchangerDesiccantBalancedFlow_RelationshipAccessorsAndValidation) {
  Model model;
  HeatExchangerDesiccantBalancedFlow object(model);
  const auto originalPerformance = object.heatExchangerPerformance();

  ScheduleConstant availability(model);
  ASSERT_TRUE(availability.setValue(0.5));
  ASSERT_TRUE(object.setAvailabilitySchedule(availability));
  EXPECT_EQ(availability, object.availabilitySchedule());

  ScheduleConstant wrongSchedule(model);
  ASSERT_TRUE(wrongSchedule.setValue(21.0));
  ScheduleTypeLimits temperatureLimits(model);
  ASSERT_TRUE(temperatureLimits.setUnitType("Temperature"));
  ASSERT_TRUE(wrongSchedule.setScheduleTypeLimits(temperatureLimits));
  EXPECT_FALSE(object.setAvailabilitySchedule(wrongSchedule));
  EXPECT_EQ(availability, object.availabilitySchedule());

  HeatExchangerDesiccantBalancedFlowPerformanceDataType1 replacement(model);
  ASSERT_TRUE(replacement.setName("Replacement Desiccant Performance"));
  ASSERT_TRUE(object.setHeatExchangerPerformance(replacement));
  EXPECT_EQ(replacement, object.heatExchangerPerformance());
  EXPECT_TRUE(model.getObject(originalPerformance.handle()));
  EXPECT_EQ(replacement.iddObject().name(),
            object.getString(openstudio::HeatExchanger_Desiccant_BalancedFlowFields::HeatExchangerPerformanceObjectType).get());

  Model otherModel;
  HeatExchangerDesiccantBalancedFlowPerformanceDataType1 foreignPerformance(otherModel);
  EXPECT_FALSE(object.setHeatExchangerPerformance(foreignPerformance));
  EXPECT_EQ(replacement, object.heatExchangerPerformance());
  const auto heatExchangerCount = model.getConcreteModelObjects<HeatExchangerDesiccantBalancedFlow>().size();
  EXPECT_THROW(HeatExchangerDesiccantBalancedFlow(model, foreignPerformance), std::invalid_argument);
  EXPECT_EQ(heatExchangerCount, model.getConcreteModelObjects<HeatExchangerDesiccantBalancedFlow>().size());

  HeatExchangerDesiccantBalancedFlow constructedWithPerformance(model, replacement);
  EXPECT_EQ(replacement, constructedWithPerformance.heatExchangerPerformance());
  EXPECT_EQ(model.alwaysOnDiscreteSchedule(), constructedWithPerformance.availabilitySchedule());
  EXPECT_TRUE(constructedWithPerformance.economizerLockout());
}

TEST_F(EPModelFixture, HeatExchangerDesiccantBalancedFlow_PerformanceChildRemovalFollowsSharing) {
  Model model;
  HeatExchangerDesiccantBalancedFlow object(model);
  const auto originalPerformance = object.heatExchangerPerformance();
  HeatExchangerDesiccantBalancedFlowPerformanceDataType1 replacement(model);
  ASSERT_TRUE(object.setHeatExchangerPerformance(replacement));
  ASSERT_EQ(1u, object.children().size());
  EXPECT_EQ(replacement, object.children().front());

  const auto objectHandle = object.handle();
  const auto replacementHandle = replacement.handle();
  object.remove();
  EXPECT_FALSE(model.getObject(objectHandle));
  EXPECT_FALSE(model.getObject(replacementHandle));
  EXPECT_TRUE(model.getObject(originalPerformance.handle()));

  HeatExchangerDesiccantBalancedFlowPerformanceDataType1 sharedPerformance(model);
  HeatExchangerDesiccantBalancedFlow first(model, sharedPerformance);
  HeatExchangerDesiccantBalancedFlow second(model, sharedPerformance);
  const auto sharedHandle = sharedPerformance.handle();
  first.remove();
  EXPECT_TRUE(model.getObject(sharedHandle));
  EXPECT_EQ(sharedPerformance, second.heatExchangerPerformance());
  second.remove();
  EXPECT_FALSE(model.getObject(sharedHandle));
}

TEST_F(EPModelFixture, HeatExchangerDesiccantBalancedFlow_ScalarAccessors_RoundTrip) {
  Model model;
  HeatExchangerDesiccantBalancedFlow object(model);

  EXPECT_TRUE(object.setEconomizerLockout(false));
  EXPECT_FALSE(object.economizerLockout());

  EXPECT_TRUE(object.setEconomizerLockout(true));
  EXPECT_TRUE(object.economizerLockout());
}

TEST_F(EPModelFixture, HeatExchangerDesiccantBalancedFlow_AddToOANodeBuildsBothStreams) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));

  auto outboardOANode = oaSystem.outboardOANode();
  ASSERT_TRUE(outboardOANode);

  HeatExchangerDesiccantBalancedFlow object(model);
  ASSERT_TRUE(object.addToNode(*outboardOANode));

  EXPECT_EQ(3u, oaSystem.oaComponents().size());
  EXPECT_EQ(3u, oaSystem.reliefComponents().size());
  EXPECT_TRUE(object.primaryAirInletModelObject());
  EXPECT_TRUE(object.primaryAirOutletModelObject());
  EXPECT_TRUE(object.secondaryAirInletModelObject());
  EXPECT_TRUE(object.secondaryAirOutletModelObject());
}

TEST_F(EPModelFixture, HeatExchangerDesiccantBalancedFlow_AddToReliefNodeBuildsBothStreams) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));

  auto outboardReliefNode = oaSystem.outboardReliefNode();
  ASSERT_TRUE(outboardReliefNode);

  HeatExchangerDesiccantBalancedFlow object(model);
  ASSERT_TRUE(object.addToNode(*outboardReliefNode));

  EXPECT_EQ(3u, oaSystem.oaComponents().size());
  EXPECT_EQ(3u, oaSystem.reliefComponents().size());
  EXPECT_TRUE(object.primaryAirInletModelObject());
  EXPECT_TRUE(object.primaryAirOutletModelObject());
  EXPECT_TRUE(object.secondaryAirInletModelObject());
  EXPECT_TRUE(object.secondaryAirOutletModelObject());
}

TEST_F(EPModelFixture, HeatExchangerDesiccantBalancedFlow_RemoveDetachesFromOutdoorAirSystemWhenAddedFromReliefSide) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));

  auto outboardReliefNode = oaSystem.outboardReliefNode();
  ASSERT_TRUE(outboardReliefNode);

  HeatExchangerDesiccantBalancedFlow object(model);
  ASSERT_TRUE(object.addToNode(*outboardReliefNode));
  ASSERT_EQ(3u, oaSystem.oaComponents().size());
  ASSERT_EQ(3u, oaSystem.reliefComponents().size());
  const auto objectHandle = object.handle();

  object.remove();

  EXPECT_EQ(1u, oaSystem.oaComponents().size());
  EXPECT_EQ(1u, oaSystem.reliefComponents().size());
  EXPECT_FALSE(oaSystem.oaComponent(objectHandle));
  EXPECT_FALSE(oaSystem.reliefComponent(objectHandle));
}

TEST_F(EPModelFixture, HeatExchangerDesiccantBalancedFlow_OutdoorAirTopologyAndRelationshipsSurviveReload) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-desiccant-heat-recovery-roundtrip.idf");

  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  HeatExchangerDesiccantBalancedFlowPerformanceDataType1 performance(model);
  HeatExchangerDesiccantBalancedFlow heatExchanger(model, performance);
  ASSERT_TRUE(airLoop.setName("Desiccant Heat Recovery Air Loop"));
  ASSERT_TRUE(oaSystem.setName("Desiccant Heat Recovery OA System"));
  ASSERT_TRUE(performance.setName("Desiccant Heat Recovery Performance"));
  ASSERT_TRUE(heatExchanger.setName("Desiccant Heat Recovery"));
  ScheduleConstant availability(model);
  ASSERT_TRUE(availability.setName("Desiccant Heat Recovery Availability"));
  ASSERT_TRUE(availability.setValue(0.5));
  ASSERT_TRUE(heatExchanger.setAvailabilitySchedule(availability));

  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));
  auto outboardOANode = oaSystem.outboardOANode();
  ASSERT_TRUE(outboardOANode);
  ASSERT_TRUE(heatExchanger.addToNode(*outboardOANode));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedOA = loadedModel->getConcreteModelObjectByName<AirLoopHVACOutdoorAirSystem>("Desiccant Heat Recovery OA System");
  auto loadedHeatExchanger = loadedModel->getConcreteModelObjectByName<HeatExchangerDesiccantBalancedFlow>("Desiccant Heat Recovery");
  auto loadedPerformance =
    loadedModel->getConcreteModelObjectByName<HeatExchangerDesiccantBalancedFlowPerformanceDataType1>("Desiccant Heat Recovery Performance");
  ASSERT_TRUE(loadedOA);
  ASSERT_TRUE(loadedHeatExchanger);
  ASSERT_TRUE(loadedPerformance);
  EXPECT_TRUE(loadedOA->oaComponent(loadedHeatExchanger->handle()));
  EXPECT_TRUE(loadedOA->reliefComponent(loadedHeatExchanger->handle()));
  EXPECT_EQ(*loadedPerformance, loadedHeatExchanger->heatExchangerPerformance());
  EXPECT_EQ("Desiccant Heat Recovery Availability", loadedHeatExchanger->availabilitySchedule().nameString());
  EXPECT_TRUE(loadedHeatExchanger->primaryAirInletModelObject());
  EXPECT_TRUE(loadedHeatExchanger->primaryAirOutletModelObject());
  EXPECT_TRUE(loadedHeatExchanger->secondaryAirInletModelObject());
  EXPECT_TRUE(loadedHeatExchanger->secondaryAirOutletModelObject());

  const auto loadedHeatExchangerHandle = loadedHeatExchanger->handle();
  const auto loadedPerformanceHandle = loadedPerformance->handle();
  loadedHeatExchanger->remove();
  EXPECT_FALSE(loadedModel->getObject(loadedHeatExchangerHandle));
  EXPECT_FALSE(loadedModel->getObject(loadedPerformanceHandle));
  EXPECT_EQ(1u, loadedOA->oaComponents().size());
  EXPECT_EQ(1u, loadedOA->reliefComponents().size());

  openstudio::filesystem::remove(idfPath);
}
