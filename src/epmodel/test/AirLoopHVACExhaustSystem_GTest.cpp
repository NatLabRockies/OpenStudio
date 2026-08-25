/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../HVACComponent/ThermalZone_Impl.hpp"
#include "../Mixer/AirLoopHVACZoneMixer.hpp"
#include "../Mixer/AirLoopHVACZoneMixer_Impl.hpp"
#include "../ModelObject/AirflowNetworkDistributionComponentFan.hpp"
#include "../ModelObject/NodeList.hpp"
#include "../ModelObject/NodeList_Impl.hpp"
#include "../ModelObject/ZoneHVACEquipmentConnections.hpp"
#include "../ModelObject/ZoneHVACEquipmentConnections_Impl.hpp"
#include "../ModelObject/ZoneHVACEquipmentList.hpp"
#include "../StraightComponent/Node.hpp"
#include "../StraightComponent/FanComponentModel.hpp"
#include "../StraightComponent/FanSystemModel.hpp"
#include "../ZoneHVACComponent/FanZoneExhaust.hpp"
#include "../ModelObject/AirLoopHVACExhaustSystem.hpp"
#include "../ModelObject/AirLoopHVACExhaustSystem_Impl.hpp"
#include "../ModelObject/ZoneHVACExhaustControl.hpp"
#include "../ModelObject/ZoneHVACExhaustControl_Impl.hpp"

#include <utilities/idd/AirLoopHVAC_ExhaustSystem_FieldEnums.hxx>
#include <utilities/idd/AirflowNetwork_Distribution_Component_Fan_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_EquipmentConnections_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_ExhaustControl_FieldEnums.hxx>

#include <algorithm>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirLoopHVACExhaustSystem_DefaultConstructor) {
  Model model;
  AirLoopHVACExhaustSystem exhaustSystem(model);
  EXPECT_EQ(AirLoopHVACExhaustSystem::iddObjectType(), exhaustSystem.iddObject().type());
}

TEST_F(EPModelFixture, AirLoopHVACExhaustSystem_ScalarAccessors_RoundTrip) {
  Model model;
  AirLoopHVACExhaustSystem exhaustSystem(model);

  EXPECT_TRUE(exhaustSystem.setName("Main Exhaust System"));
  EXPECT_EQ("Main Exhaust System", exhaustSystem.nameString());
}

TEST_F(EPModelFixture, AirLoopHVACExhaustSystem_RelationshipsAreTypedAndFanTypeValidated) {
  Model model;
  AirLoopHVACExhaustSystem exhaustSystem(model);
  AirLoopHVACZoneMixer mixer(model);
  FanSystemModel systemFan(model);
  FanComponentModel componentFan(model);

  EXPECT_FALSE(exhaustSystem.zoneMixer());
  EXPECT_FALSE(exhaustSystem.fan());

  ASSERT_TRUE(exhaustSystem.setPointer(openstudio::AirLoopHVAC_ExhaustSystemFields::ZoneMixerName, mixer.handle()));
  ASSERT_TRUE(exhaustSystem.setString(openstudio::AirLoopHVAC_ExhaustSystemFields::FanObjectType, "Fan:SystemModel"));
  ASSERT_TRUE(exhaustSystem.setPointer(openstudio::AirLoopHVAC_ExhaustSystemFields::FanName, systemFan.handle()));
  ASSERT_TRUE(exhaustSystem.zoneMixer());
  ASSERT_TRUE(exhaustSystem.fan());
  EXPECT_EQ(mixer, *exhaustSystem.zoneMixer());
  EXPECT_EQ(systemFan.cast<HVACComponent>(), *exhaustSystem.fan());

  ASSERT_TRUE(exhaustSystem.setString(openstudio::AirLoopHVAC_ExhaustSystemFields::FanObjectType, "Fan:ComponentModel"));
  EXPECT_FALSE(exhaustSystem.fan());

  ASSERT_TRUE(exhaustSystem.setPointer(openstudio::AirLoopHVAC_ExhaustSystemFields::FanName, componentFan.handle()));
  ASSERT_TRUE(exhaustSystem.fan());
  EXPECT_EQ(componentFan.cast<HVACComponent>(), *exhaustSystem.fan());
}

TEST_F(EPModelFixture, AirLoopHVACExhaustSystem_RelationshipsSurviveReloadAndRename) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-airloop-exhaust-system-roundtrip.idf");

  Model model;
  AirLoopHVACExhaustSystem exhaustSystem(model);
  AirLoopHVACZoneMixer mixer(model);
  FanSystemModel fan(model);
  ASSERT_TRUE(exhaustSystem.setName("Roundtrip Exhaust System"));
  ASSERT_TRUE(mixer.setName("Roundtrip Exhaust Mixer"));
  ASSERT_TRUE(fan.setName("Roundtrip Exhaust Fan"));
  ASSERT_TRUE(exhaustSystem.setPointer(openstudio::AirLoopHVAC_ExhaustSystemFields::ZoneMixerName, mixer.handle()));
  ASSERT_TRUE(exhaustSystem.setString(openstudio::AirLoopHVAC_ExhaustSystemFields::FanObjectType, "Fan:SystemModel"));
  ASSERT_TRUE(exhaustSystem.setPointer(openstudio::AirLoopHVAC_ExhaustSystemFields::FanName, fan.handle()));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedSystem = loadedModel->getConcreteModelObjectByName<AirLoopHVACExhaustSystem>("Roundtrip Exhaust System");
  ASSERT_TRUE(loadedSystem);
  ASSERT_TRUE(loadedSystem->zoneMixer());
  ASSERT_TRUE(loadedSystem->fan());
  EXPECT_EQ("Roundtrip Exhaust Mixer", loadedSystem->zoneMixer()->nameString());
  EXPECT_EQ("Roundtrip Exhaust Fan", loadedSystem->fan()->nameString());

  ASSERT_TRUE(loadedSystem->fan()->setName("Renamed Roundtrip Exhaust Fan"));
  ASSERT_TRUE(loadedSystem->fan());
  EXPECT_EQ("Renamed Roundtrip Exhaust Fan", loadedSystem->fan()->nameString());

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, AirLoopHVACExhaustSystem_OwnerConstructorsWireSupportedFans) {
  Model model;
  FanSystemModel systemFan(model);
  FanComponentModel componentFan(model);
  AirLoopHVACExhaustSystem systemModelOwner(model, systemFan);
  AirLoopHVACExhaustSystem componentModelOwner(model, componentFan);

  const auto expectWired = [](const AirLoopHVACExhaustSystem& system, const auto& expectedFan) {
    ASSERT_TRUE(system.zoneMixer());
    ASSERT_TRUE(system.fan());
    EXPECT_EQ(expectedFan.template cast<HVACComponent>(), *system.fan());
    ASSERT_TRUE(system.zoneMixer()->outletModelObject());
    ASSERT_TRUE(expectedFan.inletModelObject());
    ASSERT_TRUE(expectedFan.outletModelObject());
    EXPECT_EQ(*system.zoneMixer()->outletModelObject(), *expectedFan.inletModelObject());
    EXPECT_NE(*expectedFan.inletModelObject(), *expectedFan.outletModelObject());
  };

  expectWired(systemModelOwner, systemFan);
  expectWired(componentModelOwner, componentFan);
}

TEST_F(EPModelFixture, AirLoopHVACExhaustSystem_OwnerConstructorRejectsConnectedAndCrossModelFansWithoutResidue) {
  Model model;
  FanSystemModel connectedFan(model);
  Node existingInlet(model);
  ASSERT_TRUE(connectedFan.setPointer(connectedFan.inletPort(), existingInlet.handle()));

  EXPECT_THROW({ AirLoopHVACExhaustSystem rejected(model, connectedFan); }, std::runtime_error);
  EXPECT_TRUE(model.getConcreteModelObjects<AirLoopHVACExhaustSystem>().empty());
  EXPECT_TRUE(model.getConcreteModelObjects<AirLoopHVACZoneMixer>().empty());
  ASSERT_TRUE(connectedFan.inletModelObject());
  EXPECT_EQ(existingInlet.cast<ModelObject>(), *connectedFan.inletModelObject());

  Model otherModel;
  FanSystemModel otherFan(otherModel);
  EXPECT_THROW({ AirLoopHVACExhaustSystem rejected(model, otherFan); }, std::runtime_error);
  EXPECT_TRUE(model.getConcreteModelObjects<AirLoopHVACExhaustSystem>().empty());
  EXPECT_TRUE(model.getConcreteModelObjects<AirLoopHVACZoneMixer>().empty());

  FanSystemModel claimedFan(model);
  AirLoopHVACExhaustSystem claimant(model);
  ASSERT_TRUE(claimant.setString(openstudio::AirLoopHVAC_ExhaustSystemFields::FanObjectType, "Fan:SystemModel"));
  ASSERT_TRUE(claimant.setPointer(openstudio::AirLoopHVAC_ExhaustSystemFields::FanName, claimedFan.handle()));
  EXPECT_THROW({ AirLoopHVACExhaustSystem rejected(model, claimedFan); }, std::runtime_error);
  EXPECT_EQ(1u, model.getConcreteModelObjects<AirLoopHVACExhaustSystem>().size());
  EXPECT_TRUE(model.getConcreteModelObjects<AirLoopHVACZoneMixer>().empty());
}

TEST_F(EPModelFixture, AirLoopHVACExhaustSystem_AddsAndRemovesZoneControlsWithoutOwningFan) {
  Model model;
  ThermalZone firstZone(model);
  ThermalZone secondZone(model);
  FanSystemModel fan(model);
  AirLoopHVACExhaustSystem system(model, fan);
  Node existingExhaustNode(model);
  auto firstConnections = firstZone.getImpl<detail::ThermalZone_Impl>()->getZoneHVACEquipmentConnections();
  auto firstConnectionsImpl = firstConnections.getImpl<detail::ZoneHVACEquipmentConnections_Impl>();
  ASSERT_TRUE(firstConnectionsImpl);
  ASSERT_TRUE(firstConnectionsImpl->addZoneAirExhaustNode(existingExhaustNode));
  auto existingExhaustTarget = firstConnections.getTarget(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirExhaustNodeorNodeListName);
  ASSERT_TRUE(existingExhaustTarget);
  auto existingExhaustNodeList = existingExhaustTarget->optionalCast<NodeList>();
  ASSERT_TRUE(existingExhaustNodeList);

  auto firstControl = system.addZone(firstZone);
  auto secondControl = system.addZone(secondZone);
  ASSERT_TRUE(firstControl);
  ASSERT_TRUE(secondControl);
  ASSERT_TRUE(firstControl->inletNode());
  ASSERT_TRUE(firstControl->outletNode());
  ASSERT_TRUE(firstControl->thermalZone());
  EXPECT_EQ(firstZone, *firstControl->thermalZone());
  ASSERT_TRUE(firstControl->airLoopHVACExhaustSystem());
  EXPECT_EQ(system, *firstControl->airLoopHVACExhaustSystem());
  const auto controls = system.zoneHVACExhaustControls();
  ASSERT_EQ(2u, controls.size());
  EXPECT_EQ(*firstControl, controls[0]);
  EXPECT_EQ(*secondControl, controls[1]);

  EXPECT_EQ((std::vector<Node>{existingExhaustNode, *firstControl->inletNode()}), firstConnections.zoneAirExhaustNodes());
  ASSERT_TRUE(firstConnections.getTarget(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirExhaustNodeorNodeListName));
  EXPECT_EQ(existingExhaustNodeList->handle(),
            firstConnections.getTarget(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirExhaustNodeorNodeListName)->handle());
  EXPECT_TRUE(firstConnections.zoneHVACEquipmentList().equipment().empty());
  ASSERT_TRUE(system.zoneMixer());
  const auto mixerInlets = system.zoneMixer()->inletModelObjects();
  ASSERT_EQ(2u, mixerInlets.size());
  EXPECT_EQ(firstControl->outletNode()->cast<ModelObject>(), mixerInlets[0]);
  EXPECT_EQ(secondControl->outletNode()->cast<ModelObject>(), mixerInlets[1]);

  const auto firstControlHandle = firstControl->handle();
  const auto firstInletHandle = firstControl->inletNode()->handle();
  const auto firstOutletHandle = firstControl->outletNode()->handle();
  ASSERT_TRUE(system.removeZoneHVACExhaustControl(*firstControl));
  EXPECT_FALSE(model.getObject(firstControlHandle));
  EXPECT_FALSE(model.getObject(firstInletHandle));
  EXPECT_FALSE(model.getObject(firstOutletHandle));
  EXPECT_EQ(std::vector<Node>{existingExhaustNode}, firstConnections.zoneAirExhaustNodes());
  ASSERT_TRUE(firstConnections.getTarget(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirExhaustNodeorNodeListName));
  EXPECT_EQ(existingExhaustNodeList->handle(),
            firstConnections.getTarget(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirExhaustNodeorNodeListName)->handle());
  ASSERT_EQ(1u, system.zoneHVACExhaustControls().size());
  EXPECT_EQ(*secondControl, system.zoneHVACExhaustControls().front());

  auto replacement = system.addZone(firstZone);
  ASSERT_TRUE(replacement);
  const auto fanHandle = fan.handle();
  const auto mixerHandle = system.zoneMixer()->handle();
  const auto secondControlHandle = secondControl->handle();
  EXPECT_FALSE(system.remove().empty());
  EXPECT_FALSE(model.getObject(mixerHandle));
  EXPECT_FALSE(model.getObject(secondControlHandle));
  ASSERT_TRUE(model.getObject(fanHandle));
  EXPECT_FALSE(fan.inletModelObject());
  EXPECT_FALSE(fan.outletModelObject());
}

TEST_F(EPModelFixture, AirLoopHVACExhaustSystem_RejectsSharedZoneExhaustNodeListWithoutResidue) {
  Model model;
  ThermalZone firstZone(model);
  ThermalZone secondZone(model);
  FanSystemModel fan(model);
  AirLoopHVACExhaustSystem system(model, fan);
  auto firstConnections = firstZone.getImpl<detail::ThermalZone_Impl>()->getZoneHVACEquipmentConnections();
  auto secondConnections = secondZone.getImpl<detail::ThermalZone_Impl>()->getZoneHVACEquipmentConnections();
  Node existingExhaustNode(model);
  NodeList sharedExhaustNodes(model);
  auto sharedListImpl = sharedExhaustNodes.getImpl<detail::NodeList_Impl>();
  ASSERT_TRUE(sharedListImpl);
  ASSERT_TRUE(sharedListImpl->addNode(existingExhaustNode));
  constexpr unsigned exhaustField = openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirExhaustNodeorNodeListName;
  ASSERT_TRUE(firstConnections.setPointer(exhaustField, sharedExhaustNodes.handle()));
  ASSERT_TRUE(secondConnections.setPointer(exhaustField, sharedExhaustNodes.handle()));

  const auto nodeCount = model.getConcreteModelObjects<Node>().size();
  ASSERT_TRUE(system.zoneMixer());
  EXPECT_TRUE(system.zoneMixer()->inletModelObjects().empty());
  EXPECT_FALSE(system.addZone(firstZone));

  EXPECT_EQ(nodeCount, model.getConcreteModelObjects<Node>().size());
  EXPECT_TRUE(model.getConcreteModelObjects<ZoneHVACExhaustControl>().empty());
  EXPECT_TRUE(system.zoneMixer()->inletModelObjects().empty());
  EXPECT_EQ(std::vector<Node>{existingExhaustNode}, firstConnections.zoneAirExhaustNodes());
  EXPECT_EQ(std::vector<Node>{existingExhaustNode}, secondConnections.zoneAirExhaustNodes());
  EXPECT_TRUE(model.getObject(sharedExhaustNodes.handle()));
}

TEST_F(EPModelFixture, AirLoopHVACExhaustSystem_ControlsFollowMixerOrderRatherThanModelOrder) {
  Model model;
  ThermalZone firstZone(model);
  ThermalZone secondZone(model);
  FanSystemModel fan(model);
  AirLoopHVACExhaustSystem system(model, fan);
  auto firstControl = system.addZone(firstZone);
  auto secondControl = system.addZone(secondZone);
  ASSERT_TRUE(firstControl);
  ASSERT_TRUE(secondControl);
  ASSERT_TRUE(firstControl->outletNode());
  ASSERT_TRUE(secondControl->outletNode());
  ASSERT_TRUE(system.zoneMixer());

  auto mixer = *system.zoneMixer();
  ASSERT_TRUE(mixer.setInletModelObject(0, secondControl->outletNode()->cast<ModelObject>()));
  ASSERT_TRUE(mixer.setInletModelObject(1, firstControl->outletNode()->cast<ModelObject>()));

  const auto controls = system.zoneHVACExhaustControls();
  ASSERT_EQ(2u, controls.size());
  EXPECT_EQ(*secondControl, controls[0]);
  EXPECT_EQ(*firstControl, controls[1]);
}

TEST_F(EPModelFixture, AirLoopHVACExhaustSystem_RemovalRejectsAliasedControlNodesBeforeMutation) {
  Model model;
  ThermalZone zone(model);
  FanSystemModel fan(model);
  AirLoopHVACExhaustSystem system(model, fan);
  auto firstControl = system.addZone(zone);
  auto secondControl = system.addZone(zone);
  ASSERT_TRUE(firstControl);
  ASSERT_TRUE(secondControl);
  ASSERT_TRUE(firstControl->inletNode());
  const auto firstHandle = firstControl->handle();
  const auto secondHandle = secondControl->handle();
  ASSERT_TRUE(secondControl->setPointer(openstudio::ZoneHVAC_ExhaustControlFields::InletNodeName, firstControl->inletNode()->handle()));
  auto connections = zone.getImpl<detail::ThermalZone_Impl>()->getZoneHVACEquipmentConnections();
  const auto exhaustNodesBefore = connections.zoneAirExhaustNodes();
  ASSERT_TRUE(system.zoneMixer());
  const auto mixerInletsBefore = system.zoneMixer()->inletModelObjects();

  EXPECT_TRUE(system.remove().empty());

  EXPECT_TRUE(model.getObject(system.handle()));
  EXPECT_TRUE(model.getObject(firstHandle));
  EXPECT_TRUE(model.getObject(secondHandle));
  EXPECT_EQ(exhaustNodesBefore, connections.zoneAirExhaustNodes());
  EXPECT_EQ(mixerInletsBefore, system.zoneMixer()->inletModelObjects());
}

TEST_F(EPModelFixture, AirLoopHVACExhaustSystem_RemovalRejectsExternalControlNodeClaimsBeforeMutation) {
  Model model;
  ThermalZone zone(model);
  FanSystemModel centralFan(model);
  AirLoopHVACExhaustSystem system(model, centralFan);
  auto control = system.addZone(zone);
  ASSERT_TRUE(control);
  ASSERT_TRUE(control->inletNode());
  FanZoneExhaust zoneFan(model);
  ASSERT_TRUE(zoneFan.addToThermalZone(zone));
  ASSERT_TRUE(zoneFan.setPointer(zoneFan.inletPort(), control->inletNode()->handle()));
  const auto controlHandle = control->handle();
  auto connections = zone.getImpl<detail::ThermalZone_Impl>()->getZoneHVACEquipmentConnections();
  const auto exhaustNodesBefore = connections.zoneAirExhaustNodes();
  ASSERT_TRUE(system.zoneMixer());
  const auto mixerInletsBefore = system.zoneMixer()->inletModelObjects();

  EXPECT_TRUE(system.remove().empty());

  EXPECT_TRUE(model.getObject(system.handle()));
  EXPECT_TRUE(model.getObject(controlHandle));
  EXPECT_TRUE(model.getObject(zoneFan.handle()));
  ASSERT_TRUE(zoneFan.inletNode());
  EXPECT_EQ(control->inletNode()->handle(), zoneFan.inletNode()->handle());
  EXPECT_EQ(exhaustNodesBefore, connections.zoneAirExhaustNodes());
  EXPECT_EQ(mixerInletsBefore, system.zoneMixer()->inletModelObjects());
}

TEST_F(EPModelFixture, AirLoopHVACExhaustSystem_RemovalRetainsAndDisconnectsReferencedFan) {
  Model model;
  FanSystemModel fan(model);
  AirLoopHVACExhaustSystem system(model, fan);
  AirflowNetworkDistributionComponentFan companion(model);
  ASSERT_TRUE(companion.setPointer(openstudio::AirflowNetwork_Distribution_Component_FanFields::FanName, fan.handle()));
  ASSERT_TRUE(companion.setString(openstudio::AirflowNetwork_Distribution_Component_FanFields::SupplyFanObjectType, "Fan:SystemModel"));
  ASSERT_TRUE(fan.inletModelObject());
  ASSERT_TRUE(fan.outletModelObject());
  const auto inletHandle = fan.inletModelObject()->handle();
  const auto outletHandle = fan.outletModelObject()->handle();

  EXPECT_FALSE(system.remove().empty());

  EXPECT_TRUE(model.getObject(fan.handle()));
  EXPECT_TRUE(model.getObject(companion.handle()));
  ASSERT_TRUE(companion.getTarget(openstudio::AirflowNetwork_Distribution_Component_FanFields::FanName));
  EXPECT_EQ(fan.handle(), companion.getTarget(openstudio::AirflowNetwork_Distribution_Component_FanFields::FanName)->handle());
  EXPECT_FALSE(fan.inletModelObject());
  EXPECT_FALSE(fan.outletModelObject());
  EXPECT_FALSE(model.getObject(inletHandle));
  EXPECT_FALSE(model.getObject(outletHandle));
}

TEST_F(EPModelFixture, AirLoopHVACExhaustSystem_RemovalRejectsCompetingFanOwner) {
  Model model;
  FanSystemModel fan(model);
  AirLoopHVACExhaustSystem system(model, fan);
  AirLoopHVACExhaustSystem competingOwner(model);
  ASSERT_TRUE(competingOwner.setString(openstudio::AirLoopHVAC_ExhaustSystemFields::FanObjectType, "Fan:SystemModel"));
  ASSERT_TRUE(competingOwner.setPointer(openstudio::AirLoopHVAC_ExhaustSystemFields::FanName, fan.handle()));
  ASSERT_TRUE(fan.inletModelObject());
  ASSERT_TRUE(fan.outletModelObject());

  EXPECT_TRUE(system.remove().empty());

  EXPECT_TRUE(model.getObject(system.handle()));
  EXPECT_TRUE(model.getObject(competingOwner.handle()));
  EXPECT_TRUE(fan.inletModelObject());
  EXPECT_TRUE(fan.outletModelObject());
}

TEST_F(EPModelFixture, AirLoopHVACExhaustSystem_RoutedLifecycleSurvivesReload) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-central-exhaust-owner-roundtrip.idf");

  Model model;
  ThermalZone firstZone(model);
  ThermalZone secondZone(model);
  FanSystemModel fan(model);
  AirLoopHVACExhaustSystem system(model, fan);
  ASSERT_TRUE(firstZone.setName("Central Exhaust First Zone"));
  ASSERT_TRUE(secondZone.setName("Central Exhaust Second Zone"));
  ASSERT_TRUE(system.setName("Central Exhaust Owner"));
  ASSERT_TRUE(system.addZone(firstZone));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedSystem = loadedModel->getConcreteModelObjectByName<AirLoopHVACExhaustSystem>("Central Exhaust Owner");
  auto loadedFirstZone = loadedModel->getConcreteModelObjectByName<ThermalZone>("Central Exhaust First Zone");
  auto loadedSecondZone = loadedModel->getConcreteModelObjectByName<ThermalZone>("Central Exhaust Second Zone");
  ASSERT_TRUE(loadedSystem);
  ASSERT_TRUE(loadedFirstZone);
  ASSERT_TRUE(loadedSecondZone);
  ASSERT_EQ(1u, loadedSystem->zoneHVACExhaustControls().size());
  auto loadedFirstControl = loadedSystem->zoneHVACExhaustControls().front();
  auto loadedSecondControl = loadedSystem->addZone(*loadedSecondZone);
  ASSERT_TRUE(loadedSecondControl);
  const auto loadedControls = loadedSystem->zoneHVACExhaustControls();
  ASSERT_EQ(2u, loadedControls.size());
  EXPECT_EQ(loadedFirstControl, loadedControls[0]);
  EXPECT_EQ(*loadedSecondControl, loadedControls[1]);
  EXPECT_FALSE(loadedFirstControl.remove().empty());
  ASSERT_EQ(1u, loadedSystem->zoneHVACExhaustControls().size());
  ASSERT_TRUE(loadedSystem->zoneHVACExhaustControls().front().thermalZone());
  EXPECT_EQ(*loadedSecondZone, *loadedSystem->zoneHVACExhaustControls().front().thermalZone());

  openstudio::filesystem::remove(idfPath);
}
