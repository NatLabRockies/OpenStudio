/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include <algorithm>

#include "EPModelFixture.hpp"
#include "../StraightComponent/AirTerminalSingleDuctInletSideMixer.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../HVACComponent/ThermalZone_Impl.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Mixer/AirLoopHVACZoneMixer.hpp"
#include "../ModelObject/ModelObject.hpp"
#include "../ModelObject/ZoneHVACEquipmentConnections.hpp"
#include "../ModelObject/ZoneHVACAirDistributionUnit.hpp"
#include "../ModelObject/ZoneHVACAirDistributionUnit_Impl.hpp"
#include "../StraightComponent/Node.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../ZoneHVACComponent/ZoneHVACUnitHeater.hpp"

#include <utilities/idd/ZoneHVAC_AirDistributionUnit_FieldEnums.hxx>

#include <utilities/idd/AirTerminal_SingleDuct_Mixer_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirTerminalSingleDuctInletSideMixer_DefaultConstructor) {
  Model model;
  AirTerminalSingleDuctInletSideMixer terminal(model);
  EXPECT_EQ(AirTerminalSingleDuctInletSideMixer::iddObjectType(), terminal.iddObject().type());
  EXPECT_FALSE(terminal.nameString().empty());

  EXPECT_EQ("CurrentOccupancy", terminal.perPersonVentilationRateMode());
  auto persistedMode = terminal.getString(openstudio::AirTerminal_SingleDuct_MixerFields::PerPersonVentilationRateMode, true);
  ASSERT_TRUE(persistedMode);
  EXPECT_EQ("CurrentOccupancy", *persistedMode);
  EXPECT_FALSE(terminal.secondaryAirInletNode());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctInletSideMixer_ScalarAccessors_RoundTrip) {
  Model model;
  AirTerminalSingleDuctInletSideMixer terminal(model);

  EXPECT_TRUE(terminal.setPerPersonVentilationRateMode("DesignOccupancy"));
  EXPECT_EQ("DesignOccupancy", terminal.perPersonVentilationRateMode());
  auto persistedMode = terminal.getString(openstudio::AirTerminal_SingleDuct_MixerFields::PerPersonVentilationRateMode, true);
  ASSERT_TRUE(persistedMode);
  EXPECT_EQ("DesignOccupancy", *persistedMode);
  auto persistedDsoa = terminal.getString(openstudio::AirTerminal_SingleDuct_MixerFields::DesignSpecificationOutdoorAirObjectName, true);
  ASSERT_TRUE(persistedDsoa);
  EXPECT_TRUE(persistedDsoa->empty());

  EXPECT_FALSE(terminal.setPerPersonVentilationRateMode("InvalidChoice"));

  const auto values = AirTerminalSingleDuctInletSideMixer::perPersonVentilationRateModeValues();
  EXPECT_FALSE(values.empty());
  EXPECT_NE(values.end(), std::find(values.begin(), values.end(), "CurrentOccupancy"));
  EXPECT_NE(values.end(), std::find(values.begin(), values.end(), "DesignOccupancy"));
}

TEST_F(EPModelFixture, AirTerminalSingleDuctInletSideMixer_PersistedFieldOrdinals_RoundTrip) {
  Model model;
  AirTerminalSingleDuctInletSideMixer terminal(model);
  Node primaryAirNode(model);
  Node outletNode(model);
  Node secondaryAirNode(model);
  primaryAirNode.setName("Primary Air Node");
  outletNode.setName("Outlet Node");
  secondaryAirNode.setName("Secondary Air Node");

  ASSERT_TRUE(terminal.setPointer(openstudio::AirTerminal_SingleDuct_MixerFields::MixerPrimaryAirInletNodeName, primaryAirNode.handle()));
  ASSERT_TRUE(terminal.setPointer(openstudio::AirTerminal_SingleDuct_MixerFields::MixerOutletNodeName, outletNode.handle()));
  ASSERT_TRUE(terminal.setPointer(openstudio::AirTerminal_SingleDuct_MixerFields::MixerSecondaryAirInletNodeName, secondaryAirNode.handle()));

  auto inlet = terminal.inletModelObject();
  ASSERT_TRUE(inlet);
  EXPECT_EQ(primaryAirNode.handle(), inlet->handle());

  auto outlet = terminal.outletModelObject();
  ASSERT_TRUE(outlet);
  EXPECT_EQ(outletNode.handle(), outlet->handle());

  auto secondary = terminal.secondaryAirInletNode();
  ASSERT_TRUE(secondary);
  EXPECT_EQ(secondaryAirNode, *secondary);

  auto primaryFieldNode = terminal.getModelObjectTarget<Node>(openstudio::AirTerminal_SingleDuct_MixerFields::MixerPrimaryAirInletNodeName);
  ASSERT_TRUE(primaryFieldNode);
  EXPECT_EQ(primaryAirNode, *primaryFieldNode);

  auto outletFieldNode = terminal.getModelObjectTarget<Node>(openstudio::AirTerminal_SingleDuct_MixerFields::MixerOutletNodeName);
  ASSERT_TRUE(outletFieldNode);
  EXPECT_EQ(outletNode, *outletFieldNode);

  auto secondaryFieldNode = terminal.getModelObjectTarget<Node>(openstudio::AirTerminal_SingleDuct_MixerFields::MixerSecondaryAirInletNodeName);
  ASSERT_TRUE(secondaryFieldNode);
  EXPECT_EQ(secondaryAirNode, *secondaryFieldNode);

  auto persistedPrimary = terminal.getString(openstudio::AirTerminal_SingleDuct_MixerFields::MixerPrimaryAirInletNodeName, true);
  ASSERT_TRUE(persistedPrimary);
  EXPECT_EQ(primaryAirNode.nameString(), *persistedPrimary);

  auto persistedOutlet = terminal.getString(openstudio::AirTerminal_SingleDuct_MixerFields::MixerOutletNodeName, true);
  ASSERT_TRUE(persistedOutlet);
  EXPECT_EQ(outletNode.nameString(), *persistedOutlet);

  auto persistedSecondary = terminal.getString(openstudio::AirTerminal_SingleDuct_MixerFields::MixerSecondaryAirInletNodeName, true);
  ASSERT_TRUE(persistedSecondary);
  EXPECT_EQ(secondaryAirNode.nameString(), *persistedSecondary);

  auto persistedZoneType = terminal.getString(openstudio::AirTerminal_SingleDuct_MixerFields::ZoneHVACUnitObjectType, true);
  ASSERT_TRUE(persistedZoneType);
  EXPECT_TRUE(persistedZoneType->empty());

  auto persistedZoneName = terminal.getString(openstudio::AirTerminal_SingleDuct_MixerFields::ZoneHVACUnitObjectName, true);
  ASSERT_TRUE(persistedZoneName);
  EXPECT_TRUE(persistedZoneName->empty());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctInletSideMixer_AddToNode_RejectsInvalidNodesAndContexts) {
  Model model;
  Model otherModel;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  AirTerminalSingleDuctInletSideMixer terminal(model);
  Node standaloneNode(model);
  Node foreignNode(otherModel);
  auto supplyInletNode = airLoop.supplyInletNode();
  auto zoneAirNode = zone.zoneAirNode();

  EXPECT_FALSE(terminal.addToNode(standaloneNode));
  EXPECT_FALSE(terminal.addToNode(foreignNode));
  EXPECT_FALSE(terminal.addToNode(supplyInletNode));
  EXPECT_FALSE(terminal.addToNode(zoneAirNode));
  EXPECT_FALSE(terminal.inletModelObject());
  EXPECT_FALSE(terminal.outletModelObject());
  EXPECT_FALSE(terminal.airLoopHVAC());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctInletSideMixer_AddToNode_RejectsAlreadyConnectedAndMismatchedBranch) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  AirTerminalSingleDuctInletSideMixer terminal(model);

  auto branchObject = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(branchObject);
  auto branchNode = branchObject->optionalCast<Node>();
  ASSERT_TRUE(branchNode);
  ASSERT_TRUE(zone.addToNode(*branchNode));
  auto zoneAirNode = zone.zoneAirNode();

  Node mismatchedMixerNode(model);
  ASSERT_TRUE(airLoop.zoneMixer().setInletModelObject(0u, mismatchedMixerNode.cast<ModelObject>()));

  EXPECT_FALSE(terminal.addToNode(zoneAirNode));
  EXPECT_FALSE(terminal.inletModelObject());
  EXPECT_FALSE(terminal.outletModelObject());
  EXPECT_TRUE(zone.equipment().empty());

  auto splitterOutlet = airLoop.zoneSplitter().outletModelObject(0u);
  ASSERT_TRUE(splitterOutlet);
  EXPECT_EQ(zoneAirNode.cast<ModelObject>(), *splitterOutlet);

  ASSERT_TRUE(airLoop.zoneMixer().setInletModelObject(0u, zoneAirNode.cast<ModelObject>()));
  ASSERT_TRUE(terminal.addToNode(zoneAirNode));

  auto inletObject = terminal.inletModelObject();
  ASSERT_TRUE(inletObject);
  auto inletNode = inletObject->optionalCast<Node>();
  ASSERT_TRUE(inletNode);

  EXPECT_FALSE(terminal.addToNode(zoneAirNode));
  EXPECT_EQ(1u, zone.equipment().size());

  splitterOutlet = airLoop.zoneSplitter().outletModelObject(0u);
  ASSERT_TRUE(splitterOutlet);
  EXPECT_EQ(inletNode->cast<ModelObject>(), *splitterOutlet);
}

TEST_F(EPModelFixture, AirTerminalSingleDuctInletSideMixer_AddToNode_ResolvesAirLoopHVACRegistersZoneEquipmentAndPreservesSecondaryAirNode) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  AirTerminalSingleDuctInletSideMixer terminal(model);
  ZoneHVACAirDistributionUnit adu(model);
  Node secondaryAirNode(model);
  secondaryAirNode.setName("Secondary Air Node");

  ASSERT_TRUE(terminal.setPointer(openstudio::AirTerminal_SingleDuct_MixerFields::MixerSecondaryAirInletNodeName, secondaryAirNode.handle()));
  auto aduImpl = adu.getImpl<detail::ZoneHVACAirDistributionUnit_Impl>();
  ASSERT_TRUE(aduImpl);
  ASSERT_TRUE(aduImpl->setAirTerminal(terminal.cast<ModelObject>()));

  auto branchObject = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(branchObject);
  auto branchNode = branchObject->optionalCast<Node>();
  ASSERT_TRUE(branchNode);
  ASSERT_TRUE(zone.addToNode(*branchNode));

  auto zoneAirNode = zone.zoneAirNode();
  ASSERT_TRUE(terminal.addToNode(zoneAirNode));

  auto linkedAirLoop = terminal.airLoopHVAC();
  ASSERT_TRUE(linkedAirLoop);
  EXPECT_EQ(airLoop, *linkedAirLoop);

  auto inletObject = terminal.inletModelObject();
  ASSERT_TRUE(inletObject);
  auto inletNode = inletObject->optionalCast<Node>();
  ASSERT_TRUE(inletNode);
  EXPECT_NE(zoneAirNode, *inletNode);

  auto outletObject = terminal.outletModelObject();
  ASSERT_TRUE(outletObject);
  auto outletNode = outletObject->optionalCast<Node>();
  ASSERT_TRUE(outletNode);
  EXPECT_EQ(zoneAirNode, *outletNode);

  auto persistedInlet = terminal.getString(openstudio::AirTerminal_SingleDuct_MixerFields::MixerPrimaryAirInletNodeName, true);
  ASSERT_TRUE(persistedInlet);
  EXPECT_EQ(inletNode->nameString(), *persistedInlet);

  auto persistedOutlet = terminal.getString(openstudio::AirTerminal_SingleDuct_MixerFields::MixerOutletNodeName, true);
  ASSERT_TRUE(persistedOutlet);
  EXPECT_EQ(zoneAirNode.nameString(), *persistedOutlet);

  auto splitterOutletObject = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(splitterOutletObject);
  auto splitterOutletNode = splitterOutletObject->optionalCast<Node>();
  ASSERT_TRUE(splitterOutletNode);
  EXPECT_EQ(*inletNode, *splitterOutletNode);

  auto mixerInletObject = airLoop.zoneMixer().lastInletModelObject();
  ASSERT_TRUE(mixerInletObject);
  auto mixerInletNode = mixerInletObject->optionalCast<Node>();
  ASSERT_TRUE(mixerInletNode);
  auto returnAirObject = zone.returnAirModelObject();
  ASSERT_TRUE(returnAirObject);
  EXPECT_EQ(*returnAirObject, mixerInletNode->cast<ModelObject>());
  EXPECT_NE(*splitterOutletNode, *mixerInletNode);

  auto resolvedSecondaryAirNode = terminal.secondaryAirInletNode();
  ASSERT_TRUE(resolvedSecondaryAirNode);
  EXPECT_EQ(secondaryAirNode, *resolvedSecondaryAirNode);

  auto persistedSecondary = terminal.getString(openstudio::AirTerminal_SingleDuct_MixerFields::MixerSecondaryAirInletNodeName, true);
  ASSERT_TRUE(persistedSecondary);
  EXPECT_EQ(secondaryAirNode.nameString(), *persistedSecondary);

  auto primaryFieldNode = terminal.getModelObjectTarget<Node>(openstudio::AirTerminal_SingleDuct_MixerFields::MixerPrimaryAirInletNodeName);
  ASSERT_TRUE(primaryFieldNode);
  EXPECT_EQ(*inletNode, *primaryFieldNode);

  auto outletFieldNode = terminal.getModelObjectTarget<Node>(openstudio::AirTerminal_SingleDuct_MixerFields::MixerOutletNodeName);
  ASSERT_TRUE(outletFieldNode);
  EXPECT_EQ(zoneAirNode, *outletFieldNode);

  auto secondaryFieldNode = terminal.getModelObjectTarget<Node>(openstudio::AirTerminal_SingleDuct_MixerFields::MixerSecondaryAirInletNodeName);
  ASSERT_TRUE(secondaryFieldNode);
  EXPECT_EQ(secondaryAirNode, *secondaryFieldNode);

  auto persistedZoneType = terminal.getString(openstudio::AirTerminal_SingleDuct_MixerFields::ZoneHVACUnitObjectType, true);
  ASSERT_TRUE(persistedZoneType);
  EXPECT_TRUE(persistedZoneType->empty());

  auto persistedZoneName = terminal.getString(openstudio::AirTerminal_SingleDuct_MixerFields::ZoneHVACUnitObjectName, true);
  ASSERT_TRUE(persistedZoneName);
  EXPECT_TRUE(persistedZoneName->empty());

  auto resolvedOutletNode = adu.outletNode();
  ASSERT_TRUE(resolvedOutletNode);
  EXPECT_EQ(zoneAirNode, resolvedOutletNode.get());

  const auto equipment = zone.equipment();
  ASSERT_EQ(1u, equipment.size());
  EXPECT_EQ(terminal.cast<ModelObject>(), equipment.front());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctInletSideMixer_RemoveFromLoop_CleansConnectivityWithoutRemovingTerminal) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  AirTerminalSingleDuctInletSideMixer terminal(model);
  ZoneHVACAirDistributionUnit adu(model);

  auto aduImpl = adu.getImpl<detail::ZoneHVACAirDistributionUnit_Impl>();
  ASSERT_TRUE(aduImpl);
  ASSERT_TRUE(aduImpl->setAirTerminal(terminal.cast<ModelObject>()));

  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  auto zoneAirNode = zone.zoneAirNode();

  auto inletObject = terminal.inletModelObject();
  ASSERT_TRUE(inletObject);
  auto inletNode = inletObject->optionalCast<Node>();
  ASSERT_TRUE(inletNode);
  const auto inletNodeHandle = inletNode->handle();

  ASSERT_TRUE(terminal.removeFromLoop());

  auto splitterOutlet = airLoop.zoneSplitter().outletModelObject(0u);
  ASSERT_TRUE(splitterOutlet);
  EXPECT_EQ(zoneAirNode.cast<ModelObject>(), *splitterOutlet);
  auto mixerInlet = airLoop.zoneMixer().inletModelObject(0u);
  ASSERT_TRUE(mixerInlet);
  auto returnAirObject = zone.returnAirModelObject();
  ASSERT_TRUE(returnAirObject);
  EXPECT_EQ(*returnAirObject, *mixerInlet);

  EXPECT_TRUE(zone.equipment().empty());
  EXPECT_FALSE(adu.outletNode());
  EXPECT_FALSE(adu.airTerminal());
  auto persistedADUType = adu.getString(openstudio::ZoneHVAC_AirDistributionUnitFields::AirTerminalObjectType, true);
  ASSERT_TRUE(persistedADUType);
  EXPECT_TRUE(persistedADUType->empty());
  EXPECT_FALSE(terminal.inletModelObject());
  EXPECT_FALSE(terminal.outletModelObject());
  EXPECT_FALSE(terminal.airLoopHVAC());
  EXPECT_TRUE(model.getObject(terminal.handle()));
  EXPECT_FALSE(model.getModelObject<Node>(inletNodeHandle));

  ASSERT_TRUE(aduImpl->setAirTerminal(terminal.cast<ModelObject>()));
  ASSERT_TRUE(terminal.addToNode(zoneAirNode));

  auto reattachedInletObject = terminal.inletModelObject();
  ASSERT_TRUE(reattachedInletObject);
  auto reattachedInletNode = reattachedInletObject->optionalCast<Node>();
  ASSERT_TRUE(reattachedInletNode);
  EXPECT_NE(inletNodeHandle, reattachedInletNode->handle());
  EXPECT_EQ(zoneAirNode, terminal.outletModelObject()->cast<Node>());
  EXPECT_EQ(1u, zone.equipment().size());
  EXPECT_EQ(terminal.cast<ModelObject>(), zone.equipment().front());
  auto reattachedADUOutlet = adu.outletNode();
  ASSERT_TRUE(reattachedADUOutlet);
  EXPECT_EQ(zoneAirNode, reattachedADUOutlet.get());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctInletSideMixer_Remove_DeletesTerminalAndCleansZoneReferences) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  AirTerminalSingleDuctInletSideMixer terminal(model);
  ZoneHVACAirDistributionUnit adu(model);

  auto aduImpl = adu.getImpl<detail::ZoneHVACAirDistributionUnit_Impl>();
  ASSERT_TRUE(aduImpl);
  ASSERT_TRUE(aduImpl->setAirTerminal(terminal.cast<ModelObject>()));

  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  const auto zoneAirNode = zone.zoneAirNode();

  auto inletObject = terminal.inletModelObject();
  ASSERT_TRUE(inletObject);
  auto inletNode = inletObject->optionalCast<Node>();
  ASSERT_TRUE(inletNode);
  const auto inletNodeHandle = inletNode->handle();

  const auto removedObjects = terminal.remove();
  EXPECT_FALSE(removedObjects.empty());

  auto splitterOutlet = airLoop.zoneSplitter().outletModelObject(0u);
  ASSERT_TRUE(splitterOutlet);
  EXPECT_EQ(zoneAirNode.cast<ModelObject>(), *splitterOutlet);
  auto mixerInlet = airLoop.zoneMixer().inletModelObject(0u);
  ASSERT_TRUE(mixerInlet);
  auto returnAirObject = zone.returnAirModelObject();
  ASSERT_TRUE(returnAirObject);
  EXPECT_EQ(*returnAirObject, *mixerInlet);

  EXPECT_TRUE(zone.equipment().empty());
  EXPECT_FALSE(adu.outletNode());
  EXPECT_FALSE(adu.airTerminal());
  EXPECT_FALSE(model.getObject(terminal.handle()));
  EXPECT_FALSE(model.getModelObject<Node>(inletNodeHandle));
}

TEST_F(EPModelFixture, AirTerminalSingleDuctInletSideMixer_RemoveFromLoop_RehomesDownstreamZoneHVACEquipment) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  AirTerminalSingleDuctInletSideMixer terminal(model);
  ZoneHVACUnitHeater unitHeater(model);

  auto branchObject = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(branchObject);
  auto branchNode = branchObject->optionalCast<Node>();
  ASSERT_TRUE(branchNode);
  ASSERT_TRUE(zone.addToNode(*branchNode));

  auto zoneAirNode = zone.zoneAirNode();
  ASSERT_TRUE(terminal.addToNode(zoneAirNode));
  ASSERT_TRUE(unitHeater.addToNode(zoneAirNode));
  ASSERT_TRUE(terminal.secondaryAirInletNode());

  ASSERT_TRUE(terminal.removeFromLoop());

  auto splitterOutlet = airLoop.zoneSplitter().outletModelObject(0u);
  ASSERT_TRUE(splitterOutlet);
  EXPECT_EQ(zoneAirNode.cast<ModelObject>(), *splitterOutlet);
  auto mixerInlet = airLoop.zoneMixer().inletModelObject(0u);
  ASSERT_TRUE(mixerInlet);
  auto returnAirObject = zone.returnAirModelObject();
  ASSERT_TRUE(returnAirObject);
  EXPECT_EQ(*returnAirObject, *mixerInlet);

  EXPECT_FALSE(terminal.secondaryAirInletNode());
  auto zoneHVACUnitType = terminal.getString(openstudio::AirTerminal_SingleDuct_MixerFields::ZoneHVACUnitObjectType, true);
  ASSERT_TRUE(zoneHVACUnitType);
  EXPECT_TRUE(zoneHVACUnitType->empty());
  auto zoneHVACUnitName = terminal.getString(openstudio::AirTerminal_SingleDuct_MixerFields::ZoneHVACUnitObjectName, true);
  ASSERT_TRUE(zoneHVACUnitName);
  EXPECT_TRUE(zoneHVACUnitName->empty());

  EXPECT_TRUE(model.getObject(terminal.handle()));
  EXPECT_FALSE(terminal.airLoopHVAC());
  EXPECT_FALSE(terminal.inletModelObject());
  EXPECT_FALSE(terminal.outletModelObject());

  auto unitHeaterZone = unitHeater.thermalZone();
  ASSERT_TRUE(unitHeaterZone);
  EXPECT_EQ(zone, *unitHeaterZone);
  auto unitHeaterInlet = unitHeater.inletNode();
  ASSERT_TRUE(unitHeaterInlet);
  auto unitHeaterOutlet = unitHeater.outletNode();
  ASSERT_TRUE(unitHeaterOutlet);
  EXPECT_NE(zoneAirNode, unitHeaterInlet.get());
  EXPECT_NE(zoneAirNode, unitHeaterOutlet.get());

  const auto equipment = zone.equipment();
  EXPECT_EQ(std::ranges::find(equipment, terminal.cast<ModelObject>()), equipment.end());
  EXPECT_NE(std::ranges::find(equipment, unitHeater.cast<ModelObject>()), equipment.end());

  auto connections = zone.getImpl<detail::ThermalZone_Impl>()->zoneHVACEquipmentConnections();
  ASSERT_TRUE(connections);
  const auto inletNodes = connections->zoneAirInletNodes();
  EXPECT_NE(std::ranges::find(inletNodes, unitHeaterOutlet.get()), inletNodes.end());
  const auto exhaustNodes = connections->zoneAirExhaustNodes();
  EXPECT_NE(std::ranges::find(exhaustNodes, unitHeaterInlet.get()), exhaustNodes.end());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctInletSideMixer_Remove_PreservesDownstreamZoneHVACEquipment) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  AirTerminalSingleDuctInletSideMixer terminal(model);
  ZoneHVACUnitHeater unitHeater(model);

  auto branchObject = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(branchObject);
  auto branchNode = branchObject->optionalCast<Node>();
  ASSERT_TRUE(branchNode);
  ASSERT_TRUE(zone.addToNode(*branchNode));

  auto zoneAirNode = zone.zoneAirNode();
  ASSERT_TRUE(terminal.addToNode(zoneAirNode));
  ASSERT_TRUE(unitHeater.addToNode(zoneAirNode));
  auto unitHeaterOutlet = unitHeater.outletNode();
  ASSERT_TRUE(unitHeaterOutlet);
  auto unitHeaterInlet = unitHeater.inletNode();
  ASSERT_TRUE(unitHeaterInlet);
  const auto inletSideMixerOutletHandle = unitHeaterOutlet->handle();
  const auto inletSideMixerInletHandle = unitHeaterInlet->handle();

  const auto removedObjects = terminal.remove();
  EXPECT_FALSE(removedObjects.empty());

  EXPECT_FALSE(model.getObject(terminal.handle()));

  auto unitHeaterZone = unitHeater.thermalZone();
  ASSERT_TRUE(unitHeaterZone);
  EXPECT_EQ(zone, *unitHeaterZone);
  auto rehomedUnitHeaterInlet = unitHeater.inletNode();
  ASSERT_TRUE(rehomedUnitHeaterInlet);
  auto rehomedUnitHeaterOutlet = unitHeater.outletNode();
  ASSERT_TRUE(rehomedUnitHeaterOutlet);
  EXPECT_NE(inletSideMixerInletHandle, rehomedUnitHeaterInlet->handle());
  EXPECT_NE(inletSideMixerOutletHandle, rehomedUnitHeaterOutlet->handle());

  const auto equipment = zone.equipment();
  EXPECT_NE(std::ranges::find(equipment, unitHeater.cast<ModelObject>()), equipment.end());

  auto connections = zone.getImpl<detail::ThermalZone_Impl>()->zoneHVACEquipmentConnections();
  ASSERT_TRUE(connections);
  const auto inletNodes = connections->zoneAirInletNodes();
  EXPECT_NE(std::ranges::find(inletNodes, rehomedUnitHeaterOutlet.get()), inletNodes.end());
  const auto exhaustNodes = connections->zoneAirExhaustNodes();
  EXPECT_NE(std::ranges::find(exhaustNodes, rehomedUnitHeaterInlet.get()), exhaustNodes.end());
}

TEST_F(EPModelFixture, ZoneHVACComponent_AddToNode_IntegratesWithInletSideMixer) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  AirTerminalSingleDuctInletSideMixer terminal(model);
  ZoneHVACUnitHeater unitHeater(model);

  auto branchObject = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(branchObject);
  auto branchNode = branchObject->optionalCast<Node>();
  ASSERT_TRUE(branchNode);
  ASSERT_TRUE(zone.addToNode(*branchNode));

  auto terminalOutletNode = zone.zoneAirNode();
  ASSERT_TRUE(terminal.addToNode(terminalOutletNode));
  ASSERT_TRUE(unitHeater.addToNode(terminalOutletNode));

  ASSERT_TRUE(unitHeater.inletNode());
  EXPECT_EQ(terminalOutletNode, unitHeater.inletNode().get());
  ASSERT_TRUE(unitHeater.outletNode());
  const auto unitHeaterOutletNode = unitHeater.outletNode().get();

  auto secondaryAirInlet = terminal.secondaryAirInletNode();
  ASSERT_TRUE(secondaryAirInlet);

  auto connections = zone.getImpl<detail::ThermalZone_Impl>()->zoneHVACEquipmentConnections();
  ASSERT_TRUE(connections);
  const auto inletNodes = connections->zoneAirInletNodes();
  EXPECT_NE(std::ranges::find(inletNodes, unitHeaterOutletNode), inletNodes.end());
  const auto exhaustNodes = connections->zoneAirExhaustNodes();
  EXPECT_NE(std::ranges::find(exhaustNodes, secondaryAirInlet.get()), exhaustNodes.end());

  const auto equipment = zone.equipment();
  EXPECT_NE(std::ranges::find(equipment, terminal.cast<ModelObject>()), equipment.end());
  EXPECT_NE(std::ranges::find(equipment, unitHeater.cast<ModelObject>()), equipment.end());

  auto zoneHVACUnitType = terminal.getString(openstudio::AirTerminal_SingleDuct_MixerFields::ZoneHVACUnitObjectType, true);
  ASSERT_TRUE(zoneHVACUnitType);
  EXPECT_EQ(unitHeater.iddObject().name(), *zoneHVACUnitType);
  auto zoneHVACUnitName = terminal.getString(openstudio::AirTerminal_SingleDuct_MixerFields::ZoneHVACUnitObjectName, true);
  ASSERT_TRUE(zoneHVACUnitName);
  EXPECT_EQ(unitHeater.nameString(), *zoneHVACUnitName);

  const auto demandComponents = airLoop.demandComponents();
  EXPECT_NE(std::ranges::find(demandComponents, unitHeater.cast<ModelObject>()), demandComponents.end());

  unitHeater.removeFromThermalZone();

  EXPECT_FALSE(unitHeater.thermalZone());
  EXPECT_FALSE(unitHeater.inletNode());
  EXPECT_FALSE(unitHeater.outletNode());
  EXPECT_FALSE(terminal.secondaryAirInletNode());
  const auto remainingEquipment = zone.equipment();
  EXPECT_EQ(std::ranges::find(remainingEquipment, unitHeater.cast<ModelObject>()), remainingEquipment.end());
  const auto remainingInletNodes = connections->zoneAirInletNodes();
  EXPECT_EQ(std::ranges::find(remainingInletNodes, unitHeaterOutletNode), remainingInletNodes.end());
  const auto remainingExhaustNodes = connections->zoneAirExhaustNodes();
  EXPECT_EQ(std::ranges::find(remainingExhaustNodes, secondaryAirInlet.get()), remainingExhaustNodes.end());
}
