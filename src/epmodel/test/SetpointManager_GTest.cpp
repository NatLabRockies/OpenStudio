/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"

#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/AirLoopHVAC_Impl.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../Loop/PlantLoop_Impl.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../StraightComponent/FanConstantVolume.hpp"
#include "../StraightComponent/Node.hpp"
#include "../SetpointManager/SetpointManagerMixedAir.hpp"
#include "../SetpointManager/SetpointManagerColdest.hpp"
#include "../SetpointManager/SetpointManagerFollowGroundTemperature.hpp"
#include "../SetpointManager/SetpointManagerFollowOutdoorAirTemperature.hpp"
#include "../SetpointManager/SetpointManagerFollowSystemNodeTemperature.hpp"
#include "../SetpointManager/SetpointManagerScheduled.hpp"
#include "../SetpointManager/SetpointManagerScheduled_Impl.hpp"
#include "../SetpointManager/SetpointManagerScheduledDualSetpoint.hpp"
#include "../SetpointManager/SetpointManagerSingleZoneCooling.hpp"
#include "../SetpointManager/SetpointManagerSingleZoneOneStageCooling.hpp"
#include "../SetpointManager/SetpointManagerSingleZoneOneStageHeating.hpp"
#include "../SetpointManager/SetpointManagerSingleZoneHeating.hpp"
#include "../SetpointManager/SetpointManagerSingleZoneReheat.hpp"
#include "../SetpointManager/SetpointManagerWarmest.hpp"
#include "../SetpointManager/SetpointManagerWarmestTemperatureFlow.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../Schedule/ScheduleCompact.hpp"

#include <utilities/core/Filesystem.hpp>
#include <utilities/idd/SetpointManager_Scheduled_FieldEnums.hxx>
#include <utilities/idd/SetpointManager_SingleZone_Reheat_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SetpointManagerScheduled_DefaultConstructor) {
  Model model;
  SetpointManagerScheduled spm(model);
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::SetpointManager_Scheduled), spm.iddObject().type());
  EXPECT_FALSE(spm.nameString().empty());
}

TEST_F(EPModelFixture, SetpointManagerScheduled_ScalarAccessors_RoundTrip) {
  Model model;
  SetpointManagerScheduled spm(model);

  EXPECT_EQ("Temperature", spm.controlVariable());
  EXPECT_FALSE(spm.isControlVariableDefaulted());
  EXPECT_FALSE(spm.hasSchedule());

  const auto controlVariableValues = SetpointManagerScheduled::controlVariableValues();
  ASSERT_FALSE(controlVariableValues.empty());
  const auto controlVariable = controlVariableValues.back();
  ASSERT_TRUE(spm.setControlVariable(controlVariable));

  EXPECT_EQ(controlVariable, spm.controlVariable());
  EXPECT_FALSE(spm.isControlVariableDefaulted());

  spm.resetControlVariable();
  EXPECT_TRUE(spm.isControlVariableDefaulted());
  EXPECT_EQ("", spm.controlVariable());
}

TEST_F(EPModelFixture, SetpointManagerScheduled_ScheduleAccessors_RoundTrip) {
  Model model;
  ScheduleCompact compactSchedule(model);
  ASSERT_TRUE(compactSchedule.setName("SPM Schedule"));
  ASSERT_TRUE(compactSchedule.setToConstantValue(12.5));

  SetpointManagerScheduled spm(model);
  ASSERT_TRUE(spm.setSchedule(compactSchedule));

  EXPECT_TRUE(spm.hasSchedule());
  EXPECT_EQ(compactSchedule, spm.schedule());

  auto scheduleObject = spm.scheduleAsModelObject();
  ASSERT_TRUE(scheduleObject);
  EXPECT_EQ(compactSchedule.cast<ModelObject>(), *scheduleObject);

  EXPECT_TRUE(spm.setControlVariableAndSchedule("MaximumTemperature", compactSchedule));
  EXPECT_EQ("MaximumTemperature", spm.controlVariable());
  EXPECT_EQ(compactSchedule, spm.schedule());

  EXPECT_FALSE(spm.setControlVariable("DefinitelyInvalid"));
  EXPECT_EQ("MaximumTemperature", spm.controlVariable());
}

TEST_F(EPModelFixture, SetpointManagerScheduled_CanonicalizeReattachesNamedSchedule) {
  Model model;
  ScheduleCompact compactSchedule(model);
  ASSERT_TRUE(compactSchedule.setName("SPM Schedule"));
  ASSERT_TRUE(compactSchedule.setToConstantValue(0.75));

  SetpointManagerScheduled spm(model);
  ASSERT_TRUE(spm.setString(openstudio::SetpointManager_ScheduledFields::ScheduleName, compactSchedule.nameString()));

  auto report = model.canonicalize(SanitizationPolicy::Repair);
  EXPECT_EQ(0u, report.errorCount);
  EXPECT_TRUE(spm.hasSchedule());

  auto scheduleObject = spm.scheduleAsModelObject();
  ASSERT_TRUE(scheduleObject);
  EXPECT_EQ(compactSchedule.cast<ModelObject>(), *scheduleObject);
}

TEST_F(EPModelFixture, SetpointManagerScheduled_AddToPlantSupplyNode) {
  Model model;
  PlantLoop plantLoop(model);

  ScheduleCompact compactSchedule(model);
  ASSERT_TRUE(compactSchedule.setToConstantValue(12.5));

  SetpointManagerScheduled spm(model);
  ASSERT_TRUE(spm.setSchedule(compactSchedule));

  auto node = plantLoop.supplyOutletNode();
  ASSERT_TRUE(spm.addToNode(node));

  auto setpointNode = spm.setpointNode();
  ASSERT_TRUE(setpointNode);
  EXPECT_EQ(node, *setpointNode);
}

TEST_F(EPModelFixture, SetpointManagerScheduled_ControlRelationshipLifecycle) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-scheduled-setpoint-manager-lifecycle.idf");

  Model model;
  AirLoopHVAC airLoop(model);
  PlantLoop plantLoop(model);
  ASSERT_TRUE(airLoop.setName("Scheduled Control Air Loop"));
  ASSERT_TRUE(plantLoop.setName("Scheduled Control Plant Loop"));

  ScheduleConstant initialAirSchedule(model);
  ScheduleConstant replacementAirSchedule(model);
  ScheduleConstant plantSchedule(model);
  ASSERT_TRUE(initialAirSchedule.setName("Initial Air Setpoint Schedule"));
  ASSERT_TRUE(replacementAirSchedule.setName("Replacement Air Setpoint Schedule"));
  ASSERT_TRUE(plantSchedule.setName("Plant Setpoint Schedule"));
  ASSERT_TRUE(initialAirSchedule.setValue(12.0));
  ASSERT_TRUE(replacementAirSchedule.setValue(13.0));
  ASSERT_TRUE(plantSchedule.setValue(60.0));

  SetpointManagerScheduled airManager(model);
  SetpointManagerScheduled plantManager(model);
  ASSERT_TRUE(airManager.setName("Air Scheduled Setpoint Manager"));
  ASSERT_TRUE(plantManager.setName("Plant Scheduled Setpoint Manager"));
  ASSERT_TRUE(airManager.setSchedule(initialAirSchedule));
  ASSERT_TRUE(plantManager.setSchedule(plantSchedule));

  auto airNode = airLoop.supplyOutletNode();
  auto plantNode = plantLoop.supplyOutletNode();
  ASSERT_TRUE(airManager.addToNode(airNode));
  ASSERT_TRUE(plantManager.addToNode(plantNode));
  ASSERT_TRUE(plantLoop.setLoopTemperatureSetpointNode(plantNode));
  ASSERT_TRUE(airManager.setSchedule(replacementAirSchedule));

  ASSERT_TRUE(airManager.setpointNode());
  ASSERT_TRUE(plantManager.setpointNode());
  EXPECT_EQ(airNode, *airManager.setpointNode());
  EXPECT_EQ(plantNode, *plantManager.setpointNode());
  ASSERT_EQ(1u, airNode.setpointManagers().size());
  ASSERT_EQ(1u, plantNode.setpointManagers().size());
  EXPECT_EQ(airManager, airNode.setpointManagers().front());
  EXPECT_EQ(plantManager, plantNode.setpointManagers().front());
  EXPECT_EQ(replacementAirSchedule, airManager.schedule());
  EXPECT_EQ(plantNode, plantLoop.loopTemperatureSetpointNode());
  ASSERT_TRUE(airManager.loop());
  ASSERT_TRUE(airManager.airLoopHVAC());
  ASSERT_TRUE(plantManager.loop());
  ASSERT_TRUE(plantManager.plantLoop());
  EXPECT_EQ(airLoop.handle(), airManager.loop()->handle());
  EXPECT_EQ(airLoop, *airManager.airLoopHVAC());
  EXPECT_EQ(plantLoop.handle(), plantManager.loop()->handle());
  EXPECT_EQ(plantLoop, *plantManager.plantLoop());
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedAirLoop = loadedModel->getConcreteModelObjectByName<AirLoopHVAC>("Scheduled Control Air Loop");
  auto loadedPlantLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Scheduled Control Plant Loop");
  auto loadedAirManager = loadedModel->getConcreteModelObjectByName<SetpointManagerScheduled>("Air Scheduled Setpoint Manager");
  auto loadedPlantManager = loadedModel->getConcreteModelObjectByName<SetpointManagerScheduled>("Plant Scheduled Setpoint Manager");
  auto loadedAirSchedule = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("Replacement Air Setpoint Schedule");
  ASSERT_TRUE(loadedAirLoop);
  ASSERT_TRUE(loadedPlantLoop);
  ASSERT_TRUE(loadedAirManager);
  ASSERT_TRUE(loadedPlantManager);
  ASSERT_TRUE(loadedAirSchedule);

  auto loadedAirNode = loadedAirLoop->supplyOutletNode();
  auto loadedPlantNode = loadedPlantLoop->supplyOutletNode();
  ASSERT_TRUE(loadedAirManager->setpointNode());
  ASSERT_TRUE(loadedPlantManager->setpointNode());
  EXPECT_EQ(loadedAirNode, *loadedAirManager->setpointNode());
  EXPECT_EQ(loadedPlantNode, *loadedPlantManager->setpointNode());
  ASSERT_EQ(1u, loadedAirNode.setpointManagers().size());
  ASSERT_EQ(1u, loadedPlantNode.setpointManagers().size());
  EXPECT_EQ(*loadedAirManager, loadedAirNode.setpointManagers().front());
  EXPECT_EQ(*loadedPlantManager, loadedPlantNode.setpointManagers().front());
  EXPECT_EQ(*loadedAirSchedule, loadedAirManager->schedule());
  EXPECT_EQ(loadedPlantNode, loadedPlantLoop->loopTemperatureSetpointNode());
  EXPECT_EQ(2u, loadedAirLoop->supplyComponents().size());
  EXPECT_TRUE(loadedAirLoop->supplyComponent(loadedAirNode.handle()));
  EXPECT_TRUE(loadedAirNode.airLoopHVAC());
  ASSERT_TRUE(loadedAirManager->airLoopHVAC());
  ASSERT_TRUE(loadedPlantManager->plantLoop());
  ASSERT_TRUE(loadedAirManager->loop());
  ASSERT_TRUE(loadedPlantManager->loop());
  EXPECT_EQ(*loadedAirLoop, *loadedAirManager->airLoopHVAC());
  EXPECT_EQ(*loadedPlantLoop, *loadedPlantManager->plantLoop());
  EXPECT_EQ(loadedAirLoop->handle(), loadedAirManager->loop()->handle());
  EXPECT_EQ(loadedPlantLoop->handle(), loadedPlantManager->loop()->handle());

  ScheduleConstant postLoadPlantSchedule(*loadedModel);
  ASSERT_TRUE(postLoadPlantSchedule.setName("Post-load Plant Setpoint Schedule"));
  ASSERT_TRUE(postLoadPlantSchedule.setValue(55.0));
  ASSERT_TRUE(loadedPlantManager->setSchedule(postLoadPlantSchedule));
  EXPECT_EQ(postLoadPlantSchedule, loadedPlantManager->schedule());

  ScheduleConstant replacementManagerSchedule(*loadedModel);
  ASSERT_TRUE(replacementManagerSchedule.setName("Replacement Manager Schedule"));
  ASSERT_TRUE(replacementManagerSchedule.setValue(14.0));
  SetpointManagerScheduled replacementAirManager(*loadedModel);
  ASSERT_TRUE(replacementAirManager.setName("Replacement Air Scheduled Setpoint Manager"));
  ASSERT_TRUE(replacementAirManager.setSchedule(replacementManagerSchedule));
  const auto oldAirManagerHandle = loadedAirManager->handle();
  ASSERT_TRUE(replacementAirManager.addToNode(loadedAirNode));
  EXPECT_FALSE(loadedModel->getObject(oldAirManagerHandle));
  ASSERT_EQ(1u, loadedAirNode.setpointManagers().size());
  EXPECT_EQ(replacementAirManager, loadedAirNode.setpointManagers().front());

  const auto airLoopHandle = loadedAirLoop->handle();
  const auto plantLoopHandle = loadedPlantLoop->handle();
  EXPECT_FALSE(replacementAirManager.remove().empty());
  EXPECT_FALSE(loadedPlantManager->remove().empty());
  EXPECT_TRUE(loadedAirNode.setpointManagers().empty());
  EXPECT_TRUE(loadedPlantNode.setpointManagers().empty());
  EXPECT_TRUE(loadedModel->getObject(airLoopHandle));
  EXPECT_TRUE(loadedModel->getObject(plantLoopHandle));

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, SetpointManagerScheduledDualSetpoint_DefaultConstructor) {
  Model model;
  SetpointManagerScheduledDualSetpoint spm(model);
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::SetpointManager_Scheduled_DualSetpoint), spm.iddObject().type());
  EXPECT_FALSE(spm.nameString().empty());
}

TEST_F(EPModelFixture, SetpointManagerScheduledDualSetpoint_ScalarAccessors_RoundTrip) {
  Model model;
  SetpointManagerScheduledDualSetpoint spm(model);

  EXPECT_EQ("Temperature", spm.controlVariable());
  EXPECT_TRUE(spm.isAllowedOnPlantLoop());

  const auto controlVariableValues = SetpointManagerScheduledDualSetpoint::controlVariableValues();
  ASSERT_FALSE(controlVariableValues.empty());
  const auto controlVariable = controlVariableValues.front();
  ASSERT_TRUE(spm.setControlVariable(controlVariable));

  EXPECT_EQ(controlVariable, spm.controlVariable());
}

TEST_F(EPModelFixture, SetpointManagerSingleZoneCooling_DefaultConstructor) {
  Model model;
  SetpointManagerSingleZoneCooling spm(model);
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::SetpointManager_SingleZone_Cooling), spm.iddObject().type());
  EXPECT_FALSE(spm.nameString().empty());
}

TEST_F(EPModelFixture, SetpointManagerSingleZoneCooling_ScalarAccessors_RoundTrip) {
  Model model;
  SetpointManagerSingleZoneCooling spm(model);

  EXPECT_EQ("Temperature", spm.controlVariable());
  EXPECT_DOUBLE_EQ(-99.0, spm.minimumSupplyAirTemperature());
  EXPECT_DOUBLE_EQ(99.0, spm.maximumSupplyAirTemperature());

  ASSERT_TRUE(spm.setMinimumSupplyAirTemperature(11.5));
  ASSERT_TRUE(spm.setMaximumSupplyAirTemperature(18.75));

  EXPECT_DOUBLE_EQ(11.5, spm.minimumSupplyAirTemperature());
  EXPECT_DOUBLE_EQ(18.75, spm.maximumSupplyAirTemperature());
}

TEST_F(EPModelFixture, SetpointManagerSingleZoneOneStageCooling_DefaultConstructor) {
  Model model;
  SetpointManagerSingleZoneOneStageCooling spm(model);
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::SetpointManager_SingleZone_OneStageCooling), spm.iddObject().type());
  EXPECT_FALSE(spm.nameString().empty());
}

TEST_F(EPModelFixture, SetpointManagerSingleZoneOneStageCooling_ScalarAccessors_RoundTrip) {
  Model model;
  SetpointManagerSingleZoneOneStageCooling spm(model);

  EXPECT_EQ("Temperature", spm.controlVariable());
  EXPECT_DOUBLE_EQ(-99.0, spm.coolingStageOnSupplyAirSetpointTemperature());
  EXPECT_DOUBLE_EQ(99.0, spm.coolingStageOffSupplyAirSetpointTemperature());

  const auto controlVariableValues = SetpointManagerSingleZoneOneStageCooling::controlVariableValues();
  ASSERT_FALSE(controlVariableValues.empty());
  ASSERT_TRUE(spm.setControlVariable(controlVariableValues.front()));

  ASSERT_TRUE(spm.setCoolingStageOnSupplyAirSetpointTemperature(11.5));
  ASSERT_TRUE(spm.setCoolingStageOffSupplyAirSetpointTemperature(18.75));

  EXPECT_DOUBLE_EQ(11.5, spm.coolingStageOnSupplyAirSetpointTemperature());
  EXPECT_DOUBLE_EQ(18.75, spm.coolingStageOffSupplyAirSetpointTemperature());
}

TEST_F(EPModelFixture, SetpointManagerSingleZoneOneStageHeating_DefaultConstructor) {
  Model model;
  SetpointManagerSingleZoneOneStageHeating spm(model);
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::SetpointManager_SingleZone_OneStageHeating), spm.iddObject().type());
  EXPECT_FALSE(spm.nameString().empty());
}

TEST_F(EPModelFixture, SetpointManagerSingleZoneOneStageHeating_ScalarAccessors_RoundTrip) {
  Model model;
  SetpointManagerSingleZoneOneStageHeating spm(model);

  EXPECT_EQ("Temperature", spm.controlVariable());
  EXPECT_DOUBLE_EQ(99.0, spm.heatingStageOnSupplyAirSetpointTemperature());
  EXPECT_DOUBLE_EQ(-99.0, spm.heatingStageOffSupplyAirSetpointTemperature());

  const auto controlVariableValues = SetpointManagerSingleZoneOneStageHeating::controlVariableValues();
  ASSERT_FALSE(controlVariableValues.empty());
  ASSERT_TRUE(spm.setControlVariable(controlVariableValues.front()));

  ASSERT_TRUE(spm.setHeatingStageOnSupplyAirSetpointTemperature(41.25));
  ASSERT_TRUE(spm.setHeatingStageOffSupplyAirSetpointTemperature(17.5));

  EXPECT_DOUBLE_EQ(41.25, spm.heatingStageOnSupplyAirSetpointTemperature());
  EXPECT_DOUBLE_EQ(17.5, spm.heatingStageOffSupplyAirSetpointTemperature());
}

TEST_F(EPModelFixture, SetpointManagerSingleZoneHeating_DefaultConstructor) {
  Model model;
  SetpointManagerSingleZoneHeating spm(model);
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::SetpointManager_SingleZone_Heating), spm.iddObject().type());
  EXPECT_FALSE(spm.nameString().empty());
}

TEST_F(EPModelFixture, SetpointManagerSingleZoneHeating_ScalarAccessors_RoundTrip) {
  Model model;
  SetpointManagerSingleZoneHeating spm(model);

  EXPECT_EQ("Temperature", spm.controlVariable());
  EXPECT_DOUBLE_EQ(-99.0, spm.minimumSupplyAirTemperature());
  EXPECT_DOUBLE_EQ(99.0, spm.maximumSupplyAirTemperature());

  ASSERT_TRUE(spm.setMinimumSupplyAirTemperature(12.5));
  ASSERT_TRUE(spm.setMaximumSupplyAirTemperature(21.25));

  EXPECT_DOUBLE_EQ(12.5, spm.minimumSupplyAirTemperature());
  EXPECT_DOUBLE_EQ(21.25, spm.maximumSupplyAirTemperature());
}

TEST_F(EPModelFixture, SetpointManagerSingleZoneReheat_DefaultConstructor) {
  Model model;
  SetpointManagerSingleZoneReheat spm(model);
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::SetpointManager_SingleZone_Reheat), spm.iddObject().type());
  EXPECT_FALSE(spm.nameString().empty());
}

TEST_F(EPModelFixture, SetpointManagerSingleZoneReheat_ScalarAccessors_RoundTrip) {
  Model model;
  SetpointManagerSingleZoneReheat spm(model);

  EXPECT_EQ("Temperature", spm.controlVariable());
  EXPECT_DOUBLE_EQ(-99.0, spm.minimumSupplyAirTemperature());
  EXPECT_DOUBLE_EQ(99.0, spm.maximumSupplyAirTemperature());

  const auto controlVariableValues = SetpointManagerSingleZoneReheat::controlVariableValues();
  ASSERT_FALSE(controlVariableValues.empty());
  ASSERT_TRUE(spm.setControlVariable(controlVariableValues.front()));
  ASSERT_TRUE(spm.setMinimumSupplyAirTemperature(14.25));
  ASSERT_TRUE(spm.setMaximumSupplyAirTemperature(22.75));

  EXPECT_DOUBLE_EQ(14.25, spm.minimumSupplyAirTemperature());
  EXPECT_DOUBLE_EQ(22.75, spm.maximumSupplyAirTemperature());
}

TEST_F(EPModelFixture, SetpointManagerSingleZoneReheat_RemovalClearsManagedNodePointers) {
  Model model;
  Node zoneInletNode(model);
  SetpointManagerSingleZoneReheat spm(model);

  ASSERT_TRUE(spm.setPointer(openstudio::SetpointManager_SingleZone_ReheatFields::ZoneInletNodeName, zoneInletNode.handle()));
  ASSERT_EQ(1u, zoneInletNode.sources().size());
  EXPECT_EQ(spm.handle(), zoneInletNode.sources().front().handle());

  EXPECT_FALSE(spm.remove().empty());
  EXPECT_TRUE(zoneInletNode.sources().empty());
}

TEST_F(EPModelFixture, SetpointManagerColdest_DefaultConstructor) {
  Model model;
  SetpointManagerColdest spm(model);
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::SetpointManager_Coldest), spm.iddObject().type());
  EXPECT_FALSE(spm.nameString().empty());
}

TEST_F(EPModelFixture, SetpointManagerColdest_ScalarAccessors_RoundTrip) {
  Model model;
  SetpointManagerColdest spm(model);

  EXPECT_DOUBLE_EQ(20.0, spm.minimumSetpointTemperature());
  EXPECT_DOUBLE_EQ(50.0, spm.maximumSetpointTemperature());
  EXPECT_EQ("MinimumTemperature", spm.strategy());

  ASSERT_TRUE(spm.setMinimumSetpointTemperature(12.5));
  ASSERT_TRUE(spm.setMaximumSetpointTemperature(34.75));

  const auto strategyValues = SetpointManagerColdest::strategyValues();
  ASSERT_FALSE(strategyValues.empty());
  const auto strategy = strategyValues.front();
  ASSERT_TRUE(spm.setStrategy(strategy));

  EXPECT_DOUBLE_EQ(12.5, spm.minimumSetpointTemperature());
  EXPECT_DOUBLE_EQ(34.75, spm.maximumSetpointTemperature());
  EXPECT_EQ(strategy, spm.strategy());
}

TEST_F(EPModelFixture, SetpointManagerWarmest_DefaultConstructor) {
  Model model;
  SetpointManagerWarmest spm(model);
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::SetpointManager_Warmest), spm.iddObject().type());
  EXPECT_FALSE(spm.nameString().empty());
}

TEST_F(EPModelFixture, SetpointManagerWarmest_ScalarAccessors_RoundTrip) {
  Model model;
  SetpointManagerWarmest spm(model);

  EXPECT_DOUBLE_EQ(12.2, spm.minimumSetpointTemperature());
  EXPECT_DOUBLE_EQ(15.6, spm.maximumSetpointTemperature());
  EXPECT_EQ("MaximumTemperature", spm.strategy());

  ASSERT_TRUE(spm.setMinimumSetpointTemperature(13.1));
  ASSERT_TRUE(spm.setMaximumSetpointTemperature(17.4));

  const auto strategyValues = SetpointManagerWarmest::strategyValues();
  ASSERT_FALSE(strategyValues.empty());
  const auto strategy = strategyValues.front();
  ASSERT_TRUE(spm.setStrategy(strategy));

  EXPECT_DOUBLE_EQ(13.1, spm.minimumSetpointTemperature());
  EXPECT_DOUBLE_EQ(17.4, spm.maximumSetpointTemperature());
  EXPECT_EQ(strategy, spm.strategy());
}

TEST_F(EPModelFixture, SetpointManagerWarmestTemperatureFlow_DefaultConstructor) {
  Model model;
  SetpointManagerWarmestTemperatureFlow spm(model);
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::SetpointManager_WarmestTemperatureFlow), spm.iddObject().type());
  EXPECT_FALSE(spm.nameString().empty());
}

TEST_F(EPModelFixture, SetpointManagerWarmestTemperatureFlow_ScalarAccessors_RoundTrip) {
  Model model;
  SetpointManagerWarmestTemperatureFlow spm(model);

  EXPECT_DOUBLE_EQ(12.0, spm.minimumSetpointTemperature());
  EXPECT_DOUBLE_EQ(18.0, spm.maximumSetpointTemperature());
  EXPECT_EQ("TemperatureFirst", spm.strategy());
  EXPECT_DOUBLE_EQ(0.2, spm.minimumTurndownRatio());

  ASSERT_TRUE(spm.setMinimumSetpointTemperature(13.4));
  ASSERT_TRUE(spm.setMaximumSetpointTemperature(19.8));
  ASSERT_TRUE(spm.setMinimumTurndownRatio(0.45));

  const auto strategyValues = SetpointManagerWarmestTemperatureFlow::strategyValues();
  ASSERT_FALSE(strategyValues.empty());
  const auto strategy = strategyValues.front();
  ASSERT_TRUE(spm.setStrategy(strategy));

  EXPECT_DOUBLE_EQ(13.4, spm.minimumSetpointTemperature());
  EXPECT_DOUBLE_EQ(19.8, spm.maximumSetpointTemperature());
  EXPECT_EQ(strategy, spm.strategy());
  EXPECT_DOUBLE_EQ(0.45, spm.minimumTurndownRatio());
}

TEST_F(EPModelFixture, SetpointManagerFollowGroundTemperature_DefaultConstructor) {
  Model model;
  SetpointManagerFollowGroundTemperature spm(model);
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::SetpointManager_FollowGroundTemperature), spm.iddObject().type());
  EXPECT_FALSE(spm.nameString().empty());
}

TEST_F(EPModelFixture, SetpointManagerFollowGroundTemperature_ScalarAccessors_RoundTrip) {
  Model model;
  SetpointManagerFollowGroundTemperature spm(model);

  EXPECT_EQ("Site:GroundTemperature:BuildingSurface", spm.referenceGroundTemperatureObjectType());
  EXPECT_DOUBLE_EQ(0.0, spm.offsetTemperatureDifference());
  EXPECT_DOUBLE_EQ(80.0, spm.maximumSetpointTemperature());
  EXPECT_DOUBLE_EQ(10.0, spm.minimumSetpointTemperature());

  const auto referenceValues = SetpointManagerFollowGroundTemperature::referenceGroundTemperatureObjectTypeValues();
  ASSERT_FALSE(referenceValues.empty());
  const auto referenceType = referenceValues.front();

  ASSERT_TRUE(spm.setReferenceGroundTemperatureObjectType(referenceType));
  ASSERT_TRUE(spm.setOffsetTemperatureDifference(1.5));
  ASSERT_TRUE(spm.setMaximumSetpointTemperature(65.0));
  ASSERT_TRUE(spm.setMinimumSetpointTemperature(12.0));

  EXPECT_EQ(referenceType, spm.referenceGroundTemperatureObjectType());
  EXPECT_DOUBLE_EQ(1.5, spm.offsetTemperatureDifference());
  EXPECT_DOUBLE_EQ(65.0, spm.maximumSetpointTemperature());
  EXPECT_DOUBLE_EQ(12.0, spm.minimumSetpointTemperature());
}

TEST_F(EPModelFixture, SetpointManagerFollowOutdoorAirTemperature_DefaultConstructor) {
  Model model;
  SetpointManagerFollowOutdoorAirTemperature spm(model);
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::SetpointManager_FollowOutdoorAirTemperature), spm.iddObject().type());
  EXPECT_FALSE(spm.nameString().empty());
}

TEST_F(EPModelFixture, SetpointManagerFollowOutdoorAirTemperature_ScalarAccessors_RoundTrip) {
  Model model;
  SetpointManagerFollowOutdoorAirTemperature spm(model);

  EXPECT_EQ("Temperature", spm.controlVariable());
  EXPECT_EQ("OutdoorAirWetBulb", spm.referenceTemperatureType());
  EXPECT_DOUBLE_EQ(1.5, spm.offsetTemperatureDifference());
  EXPECT_DOUBLE_EQ(80.0, spm.maximumSetpointTemperature());
  EXPECT_DOUBLE_EQ(6.0, spm.minimumSetpointTemperature());

  ASSERT_TRUE(spm.setControlVariable("MaximumTemperature"));
  ASSERT_TRUE(spm.setReferenceTemperatureType("OutdoorAirDryBulb"));
  ASSERT_TRUE(spm.setOffsetTemperatureDifference(2.25));
  ASSERT_TRUE(spm.setMaximumSetpointTemperature(62.5));
  ASSERT_TRUE(spm.setMinimumSetpointTemperature(11.5));

  EXPECT_EQ("MaximumTemperature", spm.controlVariable());
  EXPECT_EQ("OutdoorAirDryBulb", spm.referenceTemperatureType());
  EXPECT_DOUBLE_EQ(2.25, spm.offsetTemperatureDifference());
  EXPECT_DOUBLE_EQ(62.5, spm.maximumSetpointTemperature());
  EXPECT_DOUBLE_EQ(11.5, spm.minimumSetpointTemperature());

  EXPECT_FALSE(spm.setReferenceTemperatureType("InvalidValue"));
}

TEST_F(EPModelFixture, SetpointManagerFollowSystemNodeTemperature_DefaultConstructor) {
  Model model;
  SetpointManagerFollowSystemNodeTemperature spm(model);
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::SetpointManager_FollowSystemNodeTemperature), spm.iddObject().type());
  EXPECT_FALSE(spm.nameString().empty());
}

TEST_F(EPModelFixture, SetpointManagerFollowSystemNodeTemperature_ScalarAccessors_RoundTrip) {
  Model model;
  SetpointManagerFollowSystemNodeTemperature spm(model);

  EXPECT_EQ("Temperature", spm.controlVariable());
  EXPECT_EQ("NodeDryBulb", spm.referenceTemperatureType());
  EXPECT_DOUBLE_EQ(0.0, spm.offsetTemperatureDifference());
  EXPECT_DOUBLE_EQ(100.0, spm.maximumLimitSetpointTemperature());
  EXPECT_DOUBLE_EQ(0.0, spm.minimumLimitSetpointTemperature());

  const auto controlVariableValues = SetpointManagerFollowSystemNodeTemperature::controlVariableValues();
  ASSERT_FALSE(controlVariableValues.empty());
  const auto referenceTemperatureTypeValues = SetpointManagerFollowSystemNodeTemperature::referenceTemperatureTypeValues();
  ASSERT_FALSE(referenceTemperatureTypeValues.empty());

  const auto controlVariable = controlVariableValues.front();
  const auto referenceTemperatureType = referenceTemperatureTypeValues.front();
  ASSERT_TRUE(spm.setControlVariable(controlVariable));
  ASSERT_TRUE(spm.setReferenceTemperatureType(referenceTemperatureType));
  ASSERT_TRUE(spm.setOffsetTemperatureDifference(2.5));
  ASSERT_TRUE(spm.setMaximumLimitSetpointTemperature(75.0));
  ASSERT_TRUE(spm.setMinimumLimitSetpointTemperature(5.0));

  EXPECT_EQ(controlVariable, spm.controlVariable());
  EXPECT_EQ(referenceTemperatureType, spm.referenceTemperatureType());
  EXPECT_DOUBLE_EQ(2.5, spm.offsetTemperatureDifference());
  EXPECT_DOUBLE_EQ(75.0, spm.maximumLimitSetpointTemperature());
  EXPECT_DOUBLE_EQ(5.0, spm.minimumLimitSetpointTemperature());

  EXPECT_FALSE(spm.setReferenceTemperatureType("InvalidValue"));
}

TEST_F(EPModelFixture, SetpointManagerScheduled_AddToNodeReplacesSameControlVariable) {
  Model model;
  AirLoopHVAC airLoop(model);
  auto node = airLoop.supplyOutletNode();

  SetpointManagerScheduled first(model);
  SetpointManagerScheduled second(model);

  ASSERT_TRUE(first.addToNode(node));
  ASSERT_TRUE(second.addToNode(node));

  auto scheduledManagers = model.getConcreteModelObjects<SetpointManagerScheduled>();
  ASSERT_EQ(1u, scheduledManagers.size());
  EXPECT_EQ(second, scheduledManagers.front());
}

TEST_F(EPModelFixture, SetpointManagerScheduled_AddToNodeRejectsOutboardOANode) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));

  auto outboardOANode = oaSystem.outboardOANode();
  ASSERT_TRUE(outboardOANode);

  SetpointManagerScheduled spm(model);
  EXPECT_FALSE(spm.addToNode(*outboardOANode));

  auto outboardReliefNode = oaSystem.outboardReliefNode();
  ASSERT_TRUE(outboardReliefNode);
  EXPECT_FALSE(spm.addToNode(*outboardReliefNode));

  auto mixedAirObject = oaSystem.mixedAirModelObject();
  ASSERT_TRUE(mixedAirObject);
  auto mixedAirNode = mixedAirObject->optionalCast<Node>();
  ASSERT_TRUE(mixedAirNode);
  ASSERT_TRUE(spm.addToNode(*mixedAirNode));
  ASSERT_TRUE(spm.airLoopHVACOutdoorAirSystem());
  ASSERT_TRUE(spm.airLoopHVAC());
  ASSERT_TRUE(spm.loop());
  EXPECT_EQ(oaSystem, *spm.airLoopHVACOutdoorAirSystem());
  EXPECT_EQ(airLoop, *spm.airLoopHVAC());
  EXPECT_EQ(airLoop.handle(), spm.loop()->handle());
}

TEST_F(EPModelFixture, SetpointManagerMixedAir_AddToNodeSetsReferenceAndFanNodes) {
  Model model;
  AirLoopHVAC airLoop(model);
  FanConstantVolume fan(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(fan.addToNode(supplyInletNode));

  SetpointManagerMixedAir spm(model);
  auto setpointNode = airLoop.supplyOutletNode();
  ASSERT_TRUE(spm.addToNode(setpointNode));

  auto expectedInlet = fan.inletModelObject();
  auto expectedOutlet = fan.outletModelObject();
  ASSERT_TRUE(expectedInlet);
  ASSERT_TRUE(expectedOutlet);
  auto expectedInletNode = expectedInlet->optionalCast<Node>();
  auto expectedOutletNode = expectedOutlet->optionalCast<Node>();
  ASSERT_TRUE(expectedInletNode);
  ASSERT_TRUE(expectedOutletNode);

  auto spmSetpoint = spm.setpointNode();
  ASSERT_TRUE(spmSetpoint);
  EXPECT_EQ(setpointNode, *spmSetpoint);
  auto referenceNode = spm.referenceSetpointNode();
  ASSERT_TRUE(referenceNode);
  EXPECT_EQ(airLoop.supplyOutletNode(), *referenceNode);
  auto fanInletNode = spm.fanInletNode();
  auto fanOutletNode = spm.fanOutletNode();
  ASSERT_TRUE(fanInletNode);
  ASSERT_TRUE(fanOutletNode);
  EXPECT_EQ(*expectedInletNode, *fanInletNode);
  EXPECT_EQ(*expectedOutletNode, *fanOutletNode);
}

TEST_F(EPModelFixture, SetpointManagerMixedAir_EagerRefreshAfterSupplyTopologyChange) {
  Model model;
  AirLoopHVAC airLoop(model);

  FanConstantVolume upstreamFan(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(upstreamFan.addToNode(supplyInletNode));

  SetpointManagerMixedAir spm(model);
  auto setpointNode = airLoop.supplyOutletNode();
  ASSERT_TRUE(spm.addToNode(setpointNode));

  FanConstantVolume downstreamFan(model);
  auto supplyOutletNode = airLoop.supplyOutletNode();
  ASSERT_TRUE(downstreamFan.addToNode(supplyOutletNode));

  auto expectedInlet = downstreamFan.inletModelObject();
  auto expectedOutlet = downstreamFan.outletModelObject();
  ASSERT_TRUE(expectedInlet);
  ASSERT_TRUE(expectedOutlet);
  auto expectedInletNode = expectedInlet->optionalCast<Node>();
  auto expectedOutletNode = expectedOutlet->optionalCast<Node>();
  ASSERT_TRUE(expectedInletNode);
  ASSERT_TRUE(expectedOutletNode);

  auto fanInletNode = spm.fanInletNode();
  auto fanOutletNode = spm.fanOutletNode();
  ASSERT_TRUE(fanInletNode);
  ASSERT_TRUE(fanOutletNode);
  EXPECT_EQ(*expectedInletNode, *fanInletNode);
  EXPECT_EQ(*expectedOutletNode, *fanOutletNode);
}

TEST_F(EPModelFixture, SetpointManagerSingleZoneReheat_AddToNodeSetsControlZoneFromDemandPath) {
  Model model;
  AirLoopHVAC airLoop(model);

  auto splitterOutletObject = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(splitterOutletObject);
  auto demandBranchNode = splitterOutletObject->optionalCast<openstudio::epmodel::Node>();
  ASSERT_TRUE(demandBranchNode);

  ThermalZone zone(model);
  ASSERT_TRUE(zone.addToNode(*demandBranchNode));

  SetpointManagerSingleZoneReheat spm(model);
  auto setpointNode = airLoop.supplyOutletNode();
  ASSERT_TRUE(spm.addToNode(setpointNode));

  auto controlZone = spm.controlZone();
  ASSERT_TRUE(controlZone);
  EXPECT_EQ(zone, *controlZone);

  auto zoneNode = spm.getModelObjectTarget<Node>(openstudio::SetpointManager_SingleZone_ReheatFields::ZoneNodeName);
  auto zoneInletNode = spm.getModelObjectTarget<Node>(openstudio::SetpointManager_SingleZone_ReheatFields::ZoneInletNodeName);
  auto resolvedSetpointNode = spm.getModelObjectTarget<Node>(openstudio::SetpointManager_SingleZone_ReheatFields::SetpointNodeorNodeListName);
  ASSERT_TRUE(zoneNode);
  ASSERT_TRUE(zoneInletNode);
  ASSERT_TRUE(resolvedSetpointNode);
  EXPECT_EQ(zone.zoneAirNode(), *zoneNode);
  EXPECT_EQ(zone.nameString() + " Demand Branch Node", zoneInletNode->nameString());
  EXPECT_EQ(setpointNode, *resolvedSetpointNode);
  const auto expectedZoneInletNode = *zoneInletNode;

  ASSERT_TRUE(spm.setString(openstudio::SetpointManager_SingleZone_ReheatFields::ZoneNodeName, ""));
  ASSERT_TRUE(spm.setString(openstudio::SetpointManager_SingleZone_ReheatFields::ZoneInletNodeName, ""));
  const auto report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);
  zoneNode = spm.getModelObjectTarget<Node>(openstudio::SetpointManager_SingleZone_ReheatFields::ZoneNodeName);
  zoneInletNode = spm.getModelObjectTarget<Node>(openstudio::SetpointManager_SingleZone_ReheatFields::ZoneInletNodeName);
  ASSERT_TRUE(zoneNode);
  ASSERT_TRUE(zoneInletNode);
  EXPECT_EQ(zone.zoneAirNode(), *zoneNode);
  EXPECT_EQ(expectedZoneInletNode, *zoneInletNode);
}
