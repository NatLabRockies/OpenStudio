/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/AirLoopHVAC_Impl.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem_Impl.hpp"
#include "../ResourceObject/ScheduleTypeLimits.hpp"
#include "../Schedule/ScheduleCompact.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../Schedule/ScheduleYear.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../StraightComponent/FanConstantVolume.hpp"
#include "../StraightComponent/FanConstantVolume_Impl.hpp"
#include "../StraightComponent/Node.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, FanConstantVolume_DefaultConstructor) {
  Model model;
  FanConstantVolume fan(model);
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::Fan_ConstantVolume), fan.iddObject().type());
  EXPECT_FALSE(fan.nameString().empty());
  auto defaultSchedule = fan.availabilitySchedule();
  auto constantSchedule = defaultSchedule.optionalCast<ScheduleConstant>();
  ASSERT_TRUE(constantSchedule);
  EXPECT_DOUBLE_EQ(1.0, constantSchedule->value());
  EXPECT_TRUE(fan.isMaximumFlowRateAutosized());
  EXPECT_EQ("General", fan.endUseSubcategory());
}

TEST_F(EPModelFixture, FanConstantVolume_AvailabilitySchedule_RoundTripAndValidation) {
  Model model;
  FanConstantVolume fan(model);

  ScheduleCompact compactSchedule(model);
  ASSERT_TRUE(compactSchedule.setToConstantValue(0.4));
  EXPECT_TRUE(fan.setAvailabilitySchedule(compactSchedule));
  EXPECT_EQ(compactSchedule.cast<ModelObject>(), fan.availabilitySchedule().cast<ModelObject>());
  ASSERT_TRUE(compactSchedule.scheduleTypeLimits());
  EXPECT_EQ("Availability", compactSchedule.scheduleTypeLimits()->unitType());

  ScheduleYear yearSchedule(model);
  EXPECT_TRUE(fan.setAvailabilitySchedule(yearSchedule));
  EXPECT_EQ(yearSchedule.cast<ModelObject>(), fan.availabilitySchedule().cast<ModelObject>());
  ASSERT_TRUE(yearSchedule.scheduleTypeLimits());
  EXPECT_EQ("Availability", yearSchedule.scheduleTypeLimits()->unitType());

  ScheduleConstant wrongSchedule(model);
  ASSERT_TRUE(wrongSchedule.setValue(22.0));
  ScheduleTypeLimits temperatureLimits(model);
  ASSERT_TRUE(temperatureLimits.setUnitType("Temperature"));
  ASSERT_TRUE(wrongSchedule.setScheduleTypeLimits(temperatureLimits));
  EXPECT_FALSE(fan.setAvailabilitySchedule(wrongSchedule));
}

TEST_F(EPModelFixture, FanConstantVolume_AddToNodeAcceptsAirLoopSupplyNode) {
  Model model;
  AirLoopHVAC airLoop(model);
  FanConstantVolume fan(model);

  auto supplyInletNode = airLoop.supplyInletNode();
  EXPECT_TRUE(fan.addToNode(supplyInletNode));
}

TEST_F(EPModelFixture, FanConstantVolume_AddToNodeSupportsOutboardOANode) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));

  auto outboardOANode = oaSystem.outboardOANode();
  ASSERT_TRUE(outboardOANode);
  FanConstantVolume fan(model);
  EXPECT_TRUE(fan.addToNode(*outboardOANode));
  EXPECT_EQ(3u, oaSystem.oaComponents().size());
}

TEST_F(EPModelFixture, FanConstantVolume_RemoveDetachesFromOutdoorAirSystem) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));

  auto outboardOANode = oaSystem.outboardOANode();
  ASSERT_TRUE(outboardOANode);

  FanConstantVolume fan(model);
  ASSERT_TRUE(fan.addToNode(*outboardOANode));
  ASSERT_EQ(3u, oaSystem.oaComponents().size());
  const auto fanHandle = fan.handle();

  fan.remove();

  EXPECT_LT(oaSystem.oaComponents().size(), 3u);
  EXPECT_FALSE(oaSystem.component(fanHandle));
}

TEST_F(EPModelFixture, FanConstantVolume_AddToNodeRejectsDemandBranchNode) {
  Model model;
  AirLoopHVAC airLoop(model);
  FanConstantVolume fan(model);

  auto splitterBranchNode = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(splitterBranchNode);
  auto branchNode = splitterBranchNode->optionalCast<Node>();
  ASSERT_TRUE(branchNode);
  EXPECT_FALSE(fan.addToNode(*branchNode));
}

TEST_F(EPModelFixture, FanConstantVolume_AddToNodeRejectsDemandInletAndOutletNodes) {
  Model model;
  AirLoopHVAC airLoop(model);
  FanConstantVolume fan(model);

  auto demandInletNode = airLoop.demandInletNode();
  auto demandOutletNode = airLoop.demandOutletNode();
  EXPECT_FALSE(fan.addToNode(demandInletNode));
  EXPECT_FALSE(fan.addToNode(demandOutletNode));
}

TEST_F(EPModelFixture, FanConstantVolume_TopologyCharacterization_CurrentBehavior) {
  {
    SCOPED_TRACE("insert at the air-loop supply inlet shared with an outdoor-air system");
    Model model;
    AirLoopHVAC airLoop(model);
    AirLoopHVACOutdoorAirSystem oaSystem(model);
    auto supplyInletNode = airLoop.supplyInletNode();
    ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));

    FanConstantVolume fan(model);
    EXPECT_TRUE(fan.addToNode(supplyInletNode));
    EXPECT_EQ(5u, airLoop.supplyComponents().size());
    EXPECT_TRUE(fan.loop());
    EXPECT_FALSE(oaSystem.component(fan.handle()));
    EXPECT_FALSE(fan.airLoopHVACOutdoorAirSystem());
  }

  {
    SCOPED_TRACE("move across outdoor-air and relief paths, then detach and reinsert");
    Model model;
    AirLoopHVAC airLoop(model);
    auto supplyInletNode = airLoop.supplyInletNode();
    AirLoopHVACOutdoorAirSystem oaSystem(model);
    ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));
    auto outboardOANode = oaSystem.outboardOANode();
    auto outboardReliefNode = oaSystem.outboardReliefNode();
    ASSERT_TRUE(outboardOANode);
    ASSERT_TRUE(outboardReliefNode);

    FanConstantVolume fan(model);
    ASSERT_TRUE(fan.addToNode(*outboardOANode));
    EXPECT_EQ(3u, airLoop.supplyComponents().size());
    EXPECT_EQ(3u, oaSystem.oaComponents().size());
    EXPECT_EQ(1u, oaSystem.reliefComponents().size());
    EXPECT_TRUE(oaSystem.oaComponent(fan.handle()));
    ASSERT_TRUE(fan.airLoopHVACOutdoorAirSystem());
    EXPECT_EQ(oaSystem.handle(), fan.airLoopHVACOutdoorAirSystem()->handle());

    ASSERT_TRUE(fan.addToNode(*outboardReliefNode));
    EXPECT_EQ(1u, oaSystem.oaComponents().size());
    EXPECT_EQ(3u, oaSystem.reliefComponents().size());
    EXPECT_TRUE(oaSystem.reliefComponent(fan.handle()));
    ASSERT_TRUE(fan.airLoopHVACOutdoorAirSystem());
    EXPECT_EQ(oaSystem.handle(), fan.airLoopHVACOutdoorAirSystem()->handle());

    EXPECT_TRUE(fan.removeFromLoop());
    EXPECT_EQ(1u, oaSystem.oaComponents().size());
    EXPECT_EQ(1u, oaSystem.reliefComponents().size());
    EXPECT_FALSE(oaSystem.component(fan.handle()));
    EXPECT_FALSE(fan.loop());
    EXPECT_FALSE(fan.airLoopHVAC());
    EXPECT_FALSE(fan.airLoopHVACOutdoorAirSystem());
    EXPECT_FALSE(fan.inletModelObject());
    EXPECT_FALSE(fan.outletModelObject());

    auto currentOutboardOANode = oaSystem.outboardOANode();
    ASSERT_TRUE(currentOutboardOANode);
    EXPECT_TRUE(fan.addToNode(*currentOutboardOANode));
    EXPECT_EQ(3u, oaSystem.oaComponents().size());
    EXPECT_TRUE(oaSystem.oaComponent(fan.handle()));
    ASSERT_TRUE(fan.airLoopHVACOutdoorAirSystem());
    EXPECT_EQ(oaSystem.handle(), fan.airLoopHVACOutdoorAirSystem()->handle());
  }

  {
    SCOPED_TRACE("disconnect an outdoor-air component");
    Model model;
    AirLoopHVAC airLoop(model);
    AirLoopHVACOutdoorAirSystem oaSystem(model);
    auto supplyInletNode = airLoop.supplyInletNode();
    ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));
    auto outboardOANode = oaSystem.outboardOANode();
    ASSERT_TRUE(outboardOANode);

    FanConstantVolume fan(model);
    ASSERT_TRUE(fan.addToNode(*outboardOANode));
    fan.disconnect();

    EXPECT_EQ(1u, oaSystem.oaComponents().size());
    EXPECT_FALSE(oaSystem.component(fan.handle()));
    EXPECT_FALSE(fan.loop());
    EXPECT_FALSE(fan.airLoopHVAC());
    EXPECT_FALSE(fan.airLoopHVACOutdoorAirSystem());
    EXPECT_FALSE(fan.inletModelObject());
    EXPECT_FALSE(fan.outletModelObject());
  }
}

TEST_F(EPModelFixture, FanConstantVolume_OutdoorAirTopologySurvivesSaveLoadAndMutation) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-fan-oa-topology-roundtrip.idf");

  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  FanConstantVolume fan(model);
  ASSERT_TRUE(airLoop.setName("Roundtrip Fan Air Loop"));
  ASSERT_TRUE(oaSystem.setName("Roundtrip Fan OA System"));
  ASSERT_TRUE(fan.setName("Roundtrip OA Fan"));
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));
  auto outboardOANode = oaSystem.outboardOANode();
  ASSERT_TRUE(outboardOANode);
  ASSERT_TRUE(fan.addToNode(*outboardOANode));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedAirLoop = loadedModel->getConcreteModelObjectByName<AirLoopHVAC>("Roundtrip Fan Air Loop");
  auto loadedOASystem = loadedModel->getConcreteModelObjectByName<AirLoopHVACOutdoorAirSystem>("Roundtrip Fan OA System");
  auto loadedFan = loadedModel->getConcreteModelObjectByName<FanConstantVolume>("Roundtrip OA Fan");
  ASSERT_TRUE(loadedAirLoop);
  ASSERT_TRUE(loadedOASystem);
  ASSERT_TRUE(loadedFan);

  EXPECT_EQ(3u, loadedAirLoop->supplyComponents().size());
  EXPECT_EQ(3u, loadedOASystem->oaComponents().size());
  EXPECT_EQ(1u, loadedOASystem->reliefComponents().size());
  EXPECT_TRUE(loadedOASystem->oaComponent(loadedFan->handle()));
  ASSERT_TRUE(loadedFan->airLoopHVAC());
  EXPECT_EQ(loadedAirLoop->handle(), loadedFan->airLoopHVAC()->handle());
  ASSERT_TRUE(loadedFan->airLoopHVACOutdoorAirSystem());
  EXPECT_EQ(loadedOASystem->handle(), loadedFan->airLoopHVACOutdoorAirSystem()->handle());
  EXPECT_TRUE(loadedFan->inletModelObject());
  EXPECT_TRUE(loadedFan->outletModelObject());

  ASSERT_TRUE(loadedFan->removeFromLoop());
  EXPECT_EQ(1u, loadedOASystem->oaComponents().size());
  EXPECT_FALSE(loadedFan->airLoopHVACOutdoorAirSystem());
  EXPECT_FALSE(loadedFan->inletModelObject());
  EXPECT_FALSE(loadedFan->outletModelObject());
  auto loadedOutboardOANode = loadedOASystem->outboardOANode();
  ASSERT_TRUE(loadedOutboardOANode);
  ASSERT_TRUE(loadedFan->addToNode(*loadedOutboardOANode));
  EXPECT_EQ(3u, loadedOASystem->oaComponents().size());
  EXPECT_TRUE(loadedOASystem->oaComponent(loadedFan->handle()));
  ASSERT_TRUE(loadedFan->airLoopHVACOutdoorAirSystem());
  EXPECT_EQ(loadedOASystem->handle(), loadedFan->airLoopHVACOutdoorAirSystem()->handle());

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, FanConstantVolume_ScalarAccessors_RoundTrip) {
  Model model;
  FanConstantVolume fan(model);

  EXPECT_TRUE(fan.setFanTotalEfficiency(0.81));
  EXPECT_DOUBLE_EQ(0.81, fan.fanTotalEfficiency());
  EXPECT_DOUBLE_EQ(0.81, fan.fanEfficiency());

  EXPECT_TRUE(fan.setFanEfficiency(0.79));
  EXPECT_DOUBLE_EQ(0.79, fan.fanTotalEfficiency());

  EXPECT_TRUE(fan.setPressureRise(620.0));
  EXPECT_DOUBLE_EQ(620.0, fan.pressureRise());

  EXPECT_TRUE(fan.setMaximumFlowRate(1.35));
  ASSERT_TRUE(fan.maximumFlowRate());
  EXPECT_DOUBLE_EQ(1.35, fan.maximumFlowRate().get());
  EXPECT_FALSE(fan.isMaximumFlowRateAutosized());

  fan.autosizeMaximumFlowRate();
  EXPECT_TRUE(fan.isMaximumFlowRateAutosized());

  fan.resetMaximumFlowRate();
  EXPECT_FALSE(fan.maximumFlowRate());
  EXPECT_FALSE(fan.isMaximumFlowRateAutosized());

  EXPECT_TRUE(fan.setMotorEfficiency(0.88));
  EXPECT_DOUBLE_EQ(0.88, fan.motorEfficiency());

  EXPECT_TRUE(fan.setMotorInAirstreamFraction(0.9));
  EXPECT_DOUBLE_EQ(0.9, fan.motorInAirstreamFraction());

  EXPECT_TRUE(fan.setEndUseSubcategory("Fans"));
  EXPECT_EQ("Fans", fan.endUseSubcategory());
}
