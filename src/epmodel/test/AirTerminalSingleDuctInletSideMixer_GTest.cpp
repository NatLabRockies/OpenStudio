/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include <algorithm>

#include "EPModelFixture.hpp"
#include "../StraightComponent/AirTerminalSingleDuctInletSideMixer.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Mixer/AirLoopHVACZoneMixer.hpp"
#include "../ModelObject/ModelObject.hpp"
#include "../ModelObject/ZoneHVACAirDistributionUnit.hpp"
#include "../ModelObject/ZoneHVACAirDistributionUnit_Impl.hpp"
#include "../StraightComponent/Node.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"

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

  auto secondaryFieldNode =
    terminal.getModelObjectTarget<Node>(openstudio::AirTerminal_SingleDuct_MixerFields::MixerSecondaryAirInletNodeName);
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
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  AirTerminalSingleDuctInletSideMixer terminal(model);
  Node standaloneNode(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  auto zoneAirNode = zone.zoneAirNode();

  EXPECT_FALSE(terminal.addToNode(standaloneNode));
  EXPECT_FALSE(terminal.addToNode(supplyInletNode));
  EXPECT_FALSE(terminal.addToNode(zoneAirNode));
  EXPECT_FALSE(terminal.inletModelObject());
  EXPECT_FALSE(terminal.outletModelObject());
  EXPECT_FALSE(terminal.airLoopHVAC());
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
  EXPECT_EQ(zoneAirNode, *mixerInletNode);
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

  auto secondaryFieldNode =
    terminal.getModelObjectTarget<Node>(openstudio::AirTerminal_SingleDuct_MixerFields::MixerSecondaryAirInletNodeName);
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
