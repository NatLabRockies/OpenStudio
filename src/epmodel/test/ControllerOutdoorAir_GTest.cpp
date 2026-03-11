/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"

#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/AirLoopHVAC_Impl.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../ControllerMechanicalVentilation.hpp"
#include "../ControllerMechanicalVentilation_Impl.hpp"
#include "../ControllerOutdoorAir.hpp"
#include "../DesignSpecificationOutdoorAir.hpp"
#include "../Node.hpp"
#include "../SizingZone.hpp"
#include "../Space.hpp"
#include "../ThermalZone.hpp"
#include "../ThermalZone_Impl.hpp"

#include <utilities/idd/Controller_MechanicalVentilation_FieldEnums.hxx>
#include <utilities/idd/Sizing_Zone_FieldEnums.hxx>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>

#include <algorithm>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, API_ControllerOutdoorAir_DefaultConstructor) {
  Model model;
  ControllerOutdoorAir controller(model);
  EXPECT_EQ(ControllerOutdoorAir::iddObjectType(), controller.iddObject().type());
}

TEST_F(EPModelFixture, API_ControllerOutdoorAir_ControllerMechanicalVentilationOnDemandCreation) {
  Model model;
  ControllerOutdoorAir controller(model);
  const auto numCMV = [&model]() {
    return model.getObjectsByType(openstudio::IddObjectType::Controller_MechanicalVentilation).size();
  };

  EXPECT_EQ(0, numCMV());

  auto controllerMechanicalVentilation = controller.controllerMechanicalVentilation();
  EXPECT_EQ(ControllerMechanicalVentilation::iddObjectType(), controllerMechanicalVentilation.iddObject().type());
  ASSERT_EQ(1, numCMV());

  auto secondRead = controller.controllerMechanicalVentilation();
  EXPECT_EQ(secondRead, controllerMechanicalVentilation);
}

TEST_F(EPModelFixture, API_ControllerOutdoorAir_Canonicalize_DoesNotSynthesizeCMVWithoutServedZoneDSOA) {
  Model model;
  const auto numCMV = [&model]() {
    return model.getObjectsByType(openstudio::IddObjectType::Controller_MechanicalVentilation).size();
  };
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem outdoorAirSystem(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(outdoorAirSystem.addToNode(supplyInletNode));

  ThermalZone zone(model);
  auto branchObject = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(branchObject);
  auto branchNode = branchObject->optionalCast<Node>();
  ASSERT_TRUE(branchNode);
  ASSERT_TRUE(zone.addToNode(*branchNode));

  auto controller = outdoorAirSystem.getControllerOutdoorAir();
  EXPECT_EQ(0, numCMV());

  model.canonicalize(SanitizationPolicy::Repair);

  controller = outdoorAirSystem.getControllerOutdoorAir();
  EXPECT_EQ(0, numCMV());
}

TEST_F(EPModelFixture, API_ControllerOutdoorAir_Canonicalize_SynthesizesCMVAndZoneEntriesForServedZoneDSOA) {
  Model model;
  const auto numCMV = [&model]() {
    return model.getObjectsByType(openstudio::IddObjectType::Controller_MechanicalVentilation).size();
  };
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem outdoorAirSystem(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(outdoorAirSystem.addToNode(supplyInletNode));

  ThermalZone zone(model);
  auto branchObject = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(branchObject);
  auto branchNode = branchObject->optionalCast<Node>();
  ASSERT_TRUE(branchNode);
  ASSERT_TRUE(zone.addToNode(*branchNode));

  Space space(model);
  ASSERT_TRUE(space.setThermalZone(zone));
  DesignSpecificationOutdoorAir dsoa(model);
  ASSERT_TRUE(space.setDesignSpecificationOutdoorAir(dsoa));

  auto controller = outdoorAirSystem.getControllerOutdoorAir();
  EXPECT_EQ(0, numCMV());

  model.canonicalize(SanitizationPolicy::Repair);

  controller = outdoorAirSystem.getControllerOutdoorAir();
  ASSERT_EQ(1, numCMV());
  auto cmv = controller.controllerMechanicalVentilation();
  ASSERT_EQ(1u, cmv.numExtensibleGroups());

  auto group = cmv.extensibleGroups().front();
  auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
  ASSERT_TRUE(workspaceGroup);

  auto zoneTarget = workspaceGroup->getTarget(openstudio::Controller_MechanicalVentilationExtensibleFields::ZoneorZoneListName);
  ASSERT_TRUE(zoneTarget);
  auto zoneCast = zoneTarget->optionalCast<ThermalZone>();
  ASSERT_TRUE(zoneCast);
  EXPECT_EQ(zone, *zoneCast);

  auto dsoaTarget = workspaceGroup->getTarget(openstudio::Controller_MechanicalVentilationExtensibleFields::DesignSpecificationOutdoorAirObjectName);
  ASSERT_TRUE(dsoaTarget);
  auto sizingZone = zone.sizingZone();
  auto expectedDsoaObject =
    sizingZone.getModelObjectTarget<ModelObject>(openstudio::Sizing_ZoneFields::DesignSpecificationOutdoorAirObjectName);
  ASSERT_TRUE(expectedDsoaObject);
  auto dsoaAsModelObject = dsoaTarget->optionalCast<ModelObject>();
  ASSERT_TRUE(dsoaAsModelObject);
  EXPECT_EQ(*expectedDsoaObject, *dsoaAsModelObject);
}

TEST_F(EPModelFixture, API_ControllerMechanicalVentilation_ImplOnlyZoneOutdoorAirEntries_LoopScoped) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem outdoorAirSystem(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(outdoorAirSystem.addToNode(supplyInletNode));

  ThermalZone zoneWithDSOA(model);
  auto branchObject = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(branchObject);
  auto branchNode = branchObject->optionalCast<Node>();
  ASSERT_TRUE(branchNode);
  ASSERT_TRUE(zoneWithDSOA.addToNode(*branchNode));

  Space spaceWithDSOA(model);
  ASSERT_TRUE(spaceWithDSOA.setThermalZone(zoneWithDSOA));
  DesignSpecificationOutdoorAir dsoa(model);
  ASSERT_TRUE(spaceWithDSOA.setDesignSpecificationOutdoorAir(dsoa));

  auto cmv = outdoorAirSystem.getControllerOutdoorAir().controllerMechanicalVentilation();
  airLoop.getImpl<openstudio::epmodel::detail::AirLoopHVAC_Impl>()->syncControllerMechanicalVentilationZoneOutdoorAirEntries();
  auto entries = cmv.getImpl<openstudio::epmodel::detail::ControllerMechanicalVentilation_Impl>()->zoneOutdoorAirEntries();
  ASSERT_EQ(1u, entries.size());
  EXPECT_EQ(zoneWithDSOA, entries.front().first);
}

TEST_F(EPModelFixture, API_ControllerMechanicalVentilation_RebuildOnThermalZoneAddToNode) {
  Model model;
  AirLoopHVAC loopA(model);
  AirLoopHVACOutdoorAirSystem oaA(model);
  auto supplyInletNodeA = loopA.supplyInletNode();
  ASSERT_TRUE(oaA.addToNode(supplyInletNodeA));
  AirLoopHVAC loopB(model);
  AirLoopHVACOutdoorAirSystem oaB(model);
  auto supplyInletNodeB = loopB.supplyInletNode();
  ASSERT_TRUE(oaB.addToNode(supplyInletNodeB));

  auto branchObjA = loopA.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(branchObjA);
  auto branchNodeA = branchObjA->optionalCast<Node>();
  ASSERT_TRUE(branchNodeA);
  auto branchObjB = loopB.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(branchObjB);
  auto branchNodeB = branchObjB->optionalCast<Node>();
  ASSERT_TRUE(branchNodeB);

  ThermalZone zone(model);
  ASSERT_TRUE(zone.addToNode(*branchNodeA));
  Space space(model);
  ASSERT_TRUE(space.setThermalZone(zone));
  DesignSpecificationOutdoorAir dsoa(model);
  ASSERT_TRUE(space.setDesignSpecificationOutdoorAir(dsoa));

  auto cmvA = oaA.getControllerOutdoorAir().controllerMechanicalVentilation();
  auto cmvB = oaB.getControllerOutdoorAir().controllerMechanicalVentilation();
  loopA.getImpl<openstudio::epmodel::detail::AirLoopHVAC_Impl>()->syncControllerMechanicalVentilationZoneOutdoorAirEntries();
  loopB.getImpl<openstudio::epmodel::detail::AirLoopHVAC_Impl>()->syncControllerMechanicalVentilationZoneOutdoorAirEntries();

  auto entriesA = cmvA.getImpl<openstudio::epmodel::detail::ControllerMechanicalVentilation_Impl>()->zoneOutdoorAirEntries();
  auto entriesB = cmvB.getImpl<openstudio::epmodel::detail::ControllerMechanicalVentilation_Impl>()->zoneOutdoorAirEntries();
  ASSERT_EQ(1u, entriesA.size());
  EXPECT_EQ(zone, entriesA.front().first);

  ASSERT_TRUE(zone.addToNode(*branchNodeB));

  entriesB = cmvB.getImpl<openstudio::epmodel::detail::ControllerMechanicalVentilation_Impl>()->zoneOutdoorAirEntries();
  ASSERT_EQ(1u, entriesB.size());
  EXPECT_EQ(zone, entriesB.front().first);
}
