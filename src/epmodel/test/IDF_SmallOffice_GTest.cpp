/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"

#include "../AirLoopHVAC.hpp"
#include "../AirLoopHVAC_Impl.hpp"
#include "../AirLoopHVACOutdoorAirSystem.hpp"
#include "../AirLoopHVACOutdoorAirSystem_Impl.hpp"
#include "../AirLoopHVACReturnPath.hpp"
#include "../AirLoopHVACReturnPath_Impl.hpp"
#include "../AirTerminalSingleDuctConstantVolumeNoReheat.hpp"
#include "../AirTerminalSingleDuctConstantVolumeNoReheat_Impl.hpp"
#include "../AvailabilityManager.hpp"
#include "../AvailabilityManagerAssignmentList.hpp"
#include "../AvailabilityManagerAssignmentList_Impl.hpp"
#include "../AvailabilityManagerNightCycle.hpp"
#include "../AvailabilityManagerNightCycle_Impl.hpp"
#include "../ControllerOutdoorAir.hpp"
#include "../CoilCoolingDXSingleSpeed.hpp"
#include "../CoilCoolingDXSingleSpeed_Impl.hpp"
#include "../CoilHeatingGas.hpp"
#include "../CoilHeatingGas_Impl.hpp"
#include "../CoilSystemCoolingDX.hpp"
#include "../CoilSystemCoolingDX_Impl.hpp"
#include "../FanConstantVolume.hpp"
#include "../FanConstantVolume_Impl.hpp"
#include "../AirLoopHVACSupplyPath.hpp"
#include "../AirLoopHVACSupplyPath_Impl.hpp"
#include "../AirLoopHVACZoneMixer.hpp"
#include "../AirLoopHVACZoneSplitter.hpp"
#include "../Node.hpp"
#include "../SizingZone.hpp"
#include "../SizingZone_Impl.hpp"
#include "../Space.hpp"
#include "../Space_Impl.hpp"
#include "../SetpointManagerMixedAir.hpp"
#include "../SetpointManagerMixedAir_Impl.hpp"
#include "../SetpointManagerScheduled.hpp"
#include "../SetpointManagerScheduled_Impl.hpp"
#include "../SetpointManagerSingleZoneReheat.hpp"
#include "../SetpointManagerSingleZoneReheat_Impl.hpp"
#include "../ThermalZone.hpp"
#include "../ThermalZone_Impl.hpp"
#include "../ZoneHVACAirDistributionUnit.hpp"
#include "../ZoneHVACAirDistributionUnit_Impl.hpp"
#include "../ZoneHVACEquipmentConnections.hpp"
#include "../ZoneHVACEquipmentConnections_Impl.hpp"
#include "../ZoneHVACEquipmentList.hpp"
#include "../ZoneHVACEquipmentList_Impl.hpp"
#include <algorithm>
#include <resources.hxx>
#include <utilities/core/Compare.hpp>
#include <utilities/idd/OutdoorAir_Mixer_FieldEnums.hxx>

using namespace openstudio::epmodel;

class SmallOfficeIDFFixture : public EPModelFixture
{
 protected:
  static openstudio::path smallOfficeIdfPath() {
    return resourcesPath() / openstudio::toPath("energyplus/SmallOffice/SmallOffice.idf");
  }

  static boost::optional<Model> loadSmallOfficeModel() {
    return Model::load(smallOfficeIdfPath());
  }
};

TEST_F(SmallOfficeIDFFixture, AirLoopHVAC_IDF_SupplyComponentsIncludeFanConstantVolume) {
  auto model = loadSmallOfficeModel();
  ASSERT_TRUE(model);

  auto fans = model->getConcreteModelObjects<FanConstantVolume>();
  ASSERT_FALSE(fans.empty());

  for (auto& fan : fans) {
    auto airLoop = fan.airLoopHVAC();
    ASSERT_TRUE(airLoop);

    auto comps = airLoop->supplyComponents();
    EXPECT_GT(comps.size(), 1u);

    const auto fanFound = std::ranges::any_of(comps, [&](const ModelObject& mo) { return mo == fan; });
    EXPECT_TRUE(fanFound);
  }
}

TEST_F(SmallOfficeIDFFixture, AirLoopHVAC_IDF_PathAndZoneObjectsResolveAndLink) {
  auto model = loadSmallOfficeModel();
  ASSERT_TRUE(model);

  auto airLoops = model->getConcreteModelObjects<AirLoopHVAC>();
  ASSERT_FALSE(airLoops.empty());

  for (auto& airLoop : airLoops) {
    auto impl = airLoop.getImpl<detail::AirLoopHVAC_Impl>();
    ASSERT_TRUE(impl);

    const auto supplyPath = impl->airLoopHVACSupplyPath();
    const auto returnPath = impl->airLoopHVACReturnPath();
    const auto zoneSplitter = airLoop.zoneSplitter();
    const auto zoneMixer = airLoop.zoneMixer();

    auto linkedLoop = supplyPath.airLoopHVAC();
    ASSERT_TRUE(linkedLoop);
    EXPECT_EQ(airLoop, linkedLoop.get());

    linkedLoop = returnPath.airLoopHVAC();
    ASSERT_TRUE(linkedLoop);
    EXPECT_EQ(airLoop, linkedLoop.get());

    linkedLoop = zoneSplitter.airLoopHVAC();
    ASSERT_TRUE(linkedLoop);
    EXPECT_EQ(airLoop, linkedLoop.get());

    linkedLoop = zoneMixer.airLoopHVAC();
    ASSERT_TRUE(linkedLoop);
    EXPECT_EQ(airLoop, linkedLoop.get());

    EXPECT_EQ(supplyPath, impl->airLoopHVACSupplyPath());
    EXPECT_EQ(returnPath, impl->airLoopHVACReturnPath());
    EXPECT_EQ(zoneSplitter, airLoop.zoneSplitter());
    EXPECT_EQ(zoneMixer, airLoop.zoneMixer());

    auto splitterBranchNode = zoneSplitter.lastOutletModelObject();
    ASSERT_TRUE(splitterBranchNode);
    ASSERT_TRUE(splitterBranchNode->optionalCast<Node>());

    auto mixerBranchNode = zoneMixer.lastInletModelObject();
    ASSERT_TRUE(mixerBranchNode);
    ASSERT_TRUE(mixerBranchNode->optionalCast<Node>());

    // For native IDF with zones, splitter outlets and mixer inlets should come from their own fields,
    // not be collapsed to a single default branch node.
    const auto splitterOutlets = zoneSplitter.outletModelObjects();
    const auto mixerInlets = zoneMixer.inletModelObjects();
    ASSERT_FALSE(splitterOutlets.empty());
    ASSERT_FALSE(mixerInlets.empty());
    EXPECT_EQ(splitterOutlets.size(), mixerInlets.size());
  }
}

TEST_F(SmallOfficeIDFFixture, AirLoopHVAC_IDF_AirDistributionUnitWrapsNoReheatTerminal) {
  auto model = loadSmallOfficeModel();
  ASSERT_TRUE(model);

  const auto terminals = model->getConcreteModelObjects<AirTerminalSingleDuctConstantVolumeNoReheat>();
  const auto airDistributionUnits = model->getConcreteModelObjects<ZoneHVACAirDistributionUnit>();
  ASSERT_FALSE(terminals.empty());
  ASSERT_EQ(terminals.size(), airDistributionUnits.size());

  std::vector<std::string> terminalNames;
  terminalNames.reserve(terminals.size());
  for (const auto& terminal : terminals) {
    terminalNames.push_back(terminal.nameString());
  }

  for (const auto& airDistributionUnit : airDistributionUnits) {
    auto terminalObject = airDistributionUnit.airTerminal();
    ASSERT_TRUE(terminalObject);

    auto terminalName = terminalObject->name();
    ASSERT_TRUE(terminalName);
    const auto it = std::find_if(terminalNames.begin(), terminalNames.end(),
                                 [&](const std::string& name) { return openstudio::istringEqual(name, *terminalName); });
    EXPECT_NE(it, terminalNames.end());
    const auto terminalIt = std::find_if(terminals.begin(), terminals.end(), [&](const AirTerminalSingleDuctConstantVolumeNoReheat& terminal) {
      return openstudio::istringEqual(terminal.nameString(), *terminalName);
    });
    ASSERT_NE(terminalIt, terminals.end());
    const auto& terminal = *terminalIt;

    auto airDistributionUnitOutletNode = airDistributionUnit.outletNode();
    ASSERT_TRUE(airDistributionUnitOutletNode);
    EXPECT_FALSE(airDistributionUnitOutletNode->nameString().empty());
    auto terminalOutletObject = terminal.outletModelObject();
    ASSERT_TRUE(terminalOutletObject);
    auto terminalOutletNode = terminalOutletObject->optionalCast<Node>();
    ASSERT_TRUE(terminalOutletNode);
    EXPECT_EQ(*terminalOutletNode, *airDistributionUnitOutletNode);

    ASSERT_TRUE(airDistributionUnitOutletNode->setName(airDistributionUnitOutletNode->nameString() + " Renamed"));
    auto renamedOutlet = airDistributionUnit.outletNode();
    ASSERT_TRUE(renamedOutlet);
    EXPECT_EQ(*airDistributionUnitOutletNode, *renamedOutlet);
    terminalOutletObject = terminal.outletModelObject();
    ASSERT_TRUE(terminalOutletObject);
    terminalOutletNode = terminalOutletObject->optionalCast<Node>();
    ASSERT_TRUE(terminalOutletNode);
    EXPECT_EQ(*terminalOutletNode, *renamedOutlet);
  }
}

TEST_F(SmallOfficeIDFFixture, AirLoopHVAC_IDF_DemandComponentsBuildPathPerLoop) {
  auto model = loadSmallOfficeModel();
  ASSERT_TRUE(model);

  const auto airLoops = model->getConcreteModelObjects<AirLoopHVAC>();
  ASSERT_FALSE(airLoops.empty());

  for (const auto& airLoop : airLoops) {
    const auto demandComponents = airLoop.demandComponents();
    ASSERT_GE(demandComponents.size(), 5u);

    const auto hasSplitter = std::ranges::any_of(
      demandComponents, [](const ModelObject& object) { return object.iddObject().type() == openstudio::IddObjectType::AirLoopHVAC_ZoneSplitter; });
    const auto hasMixer = std::ranges::any_of(
      demandComponents, [](const ModelObject& object) { return object.iddObject().type() == openstudio::IddObjectType::AirLoopHVAC_ZoneMixer; });
    EXPECT_TRUE(hasSplitter);
    EXPECT_TRUE(hasMixer);
  }
}

TEST_F(SmallOfficeIDFFixture, AirLoopHVAC_IDF_ZoneHVACEquipmentListObjectsLoad) {
  auto model = loadSmallOfficeModel();
  ASSERT_TRUE(model);

  const auto equipmentLists = model->getConcreteModelObjects<ZoneHVACEquipmentList>();
  const auto equipmentConnections = model->getConcreteModelObjects<ZoneHVACEquipmentConnections>();
  ASSERT_FALSE(equipmentLists.empty());
  EXPECT_EQ(equipmentConnections.size(), equipmentLists.size());
}

TEST_F(SmallOfficeIDFFixture, AirLoopHVAC_IDF_LoopNonMutationApis) {
  auto model = loadSmallOfficeModel();
  ASSERT_TRUE(model);

  const auto airLoops = model->getConcreteModelObjects<AirLoopHVAC>();
  ASSERT_FALSE(airLoops.empty());

  for (const auto& airLoop : airLoops) {
    auto supplyInletNode = airLoop.supplyInletNode();
    auto supplyOutletNode = airLoop.supplyOutletNode();
    auto demandInletNode = airLoop.demandInletNode();
    auto demandOutletNode = airLoop.demandOutletNode();
    EXPECT_FALSE(supplyInletNode.nameString().empty());
    EXPECT_FALSE(supplyOutletNode.nameString().empty());
    EXPECT_FALSE(demandInletNode.nameString().empty());
    EXPECT_FALSE(demandOutletNode.nameString().empty());

    const auto supplyOutletNodes = airLoop.supplyOutletNodes();
    ASSERT_FALSE(supplyOutletNodes.empty());
    const auto demandInletNodes = airLoop.demandInletNodes();
    ASSERT_FALSE(demandInletNodes.empty());

    const auto supplyComponents = airLoop.supplyComponents();
    const auto demandComponents = airLoop.demandComponents();
    const auto allComponents = airLoop.components();
    ASSERT_FALSE(supplyComponents.empty());
    ASSERT_FALSE(demandComponents.empty());
    ASSERT_FALSE(allComponents.empty());

    auto maybeSupplyComponent = airLoop.supplyComponent(supplyComponents.front().handle());
    ASSERT_TRUE(maybeSupplyComponent);
    EXPECT_EQ(supplyComponents.front(), maybeSupplyComponent.get());

    auto maybeDemandComponent = airLoop.demandComponent(demandComponents.front().handle());
    ASSERT_TRUE(maybeDemandComponent);
    EXPECT_EQ(demandComponents.front(), maybeDemandComponent.get());

    auto maybeAnyComponent = airLoop.component(allComponents.front().handle());
    ASSERT_TRUE(maybeAnyComponent);
    EXPECT_EQ(allComponents.front(), maybeAnyComponent.get());

    auto zoneSplitter = airLoop.zoneSplitter();
    auto zoneMixer = airLoop.zoneMixer();
    EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::AirLoopHVAC_ZoneSplitter), zoneSplitter.iddObject().type());
    EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::AirLoopHVAC_ZoneMixer), zoneMixer.iddObject().type());
  }
}

TEST_F(SmallOfficeIDFFixture, AirLoopHVAC_IDF_OutdoorAirSystemNonMutationApis) {
  auto model = loadSmallOfficeModel();
  ASSERT_TRUE(model);

  const auto airLoops = model->getConcreteModelObjects<AirLoopHVAC>();
  const auto outdoorAirSystems = model->getConcreteModelObjects<AirLoopHVACOutdoorAirSystem>();
  ASSERT_FALSE(airLoops.empty());
  ASSERT_FALSE(outdoorAirSystems.empty());

  for (const auto& outdoorAirSystem : outdoorAirSystems) {
    EXPECT_EQ(openstudio::OutdoorAir_MixerFields::ReturnAirStreamNodeName, outdoorAirSystem.returnAirPort());
    EXPECT_EQ(openstudio::OutdoorAir_MixerFields::OutdoorAirStreamNodeName, outdoorAirSystem.outdoorAirPort());
    EXPECT_EQ(openstudio::OutdoorAir_MixerFields::ReliefAirStreamNodeName, outdoorAirSystem.reliefAirPort());
    EXPECT_EQ(openstudio::OutdoorAir_MixerFields::MixedAirNodeName, outdoorAirSystem.mixedAirPort());

    auto returnAirObject = outdoorAirSystem.returnAirModelObject();
    auto mixedAirObject = outdoorAirSystem.mixedAirModelObject();
    ASSERT_TRUE(returnAirObject);
    ASSERT_TRUE(mixedAirObject);
    EXPECT_TRUE(returnAirObject->optionalCast<Node>());
    EXPECT_TRUE(mixedAirObject->optionalCast<Node>());
    EXPECT_FALSE(returnAirObject->nameString().empty());
    EXPECT_FALSE(mixedAirObject->nameString().empty());

    bool foundOnLoopSupplySide = false;
    boost::optional<AirLoopHVAC> expectedLoop;
    for (const auto& airLoop : airLoops) {
      const auto supplyComponents = airLoop.supplyComponents();
      if (std::ranges::any_of(supplyComponents, [&](const ModelObject& object) { return object == outdoorAirSystem.cast<ModelObject>(); })) {
        foundOnLoopSupplySide = true;
        expectedLoop = airLoop;
        break;
      }
    }
    EXPECT_TRUE(foundOnLoopSupplySide);
    auto oaLoop = outdoorAirSystem.airLoopHVAC();
    ASSERT_TRUE(oaLoop);
    ASSERT_TRUE(expectedLoop);
    EXPECT_EQ(*expectedLoop, *oaLoop);

    auto controllerOutdoorAir = outdoorAirSystem.getControllerOutdoorAir();
    EXPECT_EQ(ControllerOutdoorAir::iddObjectType(), controllerOutdoorAir.iddObject().type());
    auto controllerSystem = controllerOutdoorAir.airLoopHVACOutdoorAirSystem();
    ASSERT_TRUE(controllerSystem);
    EXPECT_EQ(outdoorAirSystem, *controllerSystem);
  }
}

TEST_F(SmallOfficeIDFFixture, AirLoopHVAC_IDF_LoadsSetpointManagersAndCoilsAsConcreteTypes) {
  auto model = loadSmallOfficeModel();
  ASSERT_TRUE(model);

  const auto mixedAirManagers = model->getConcreteModelObjects<SetpointManagerMixedAir>();
  const auto scheduledManagers = model->getConcreteModelObjects<SetpointManagerScheduled>();
  const auto singleZoneReheatManagers = model->getConcreteModelObjects<SetpointManagerSingleZoneReheat>();
  const auto dxCoils = model->getConcreteModelObjects<CoilCoolingDXSingleSpeed>();
  const auto gasHeatingCoils = model->getConcreteModelObjects<CoilHeatingGas>();
  const auto dxCoilSystems = model->getConcreteModelObjects<CoilSystemCoolingDX>();

  EXPECT_FALSE(mixedAirManagers.empty());
  EXPECT_FALSE(scheduledManagers.empty());
  EXPECT_FALSE(singleZoneReheatManagers.empty());
  EXPECT_FALSE(dxCoils.empty());
  EXPECT_FALSE(gasHeatingCoils.empty());
  EXPECT_FALSE(dxCoilSystems.empty());
}

TEST_F(SmallOfficeIDFFixture, AirLoopHVAC_IDF_LoadsAvailabilityManagersAsConcreteTypes) {
  auto model = loadSmallOfficeModel();
  ASSERT_TRUE(model);

  const auto availabilityManagerAssignmentLists = model->getConcreteModelObjects<AvailabilityManagerAssignmentList>();
  const auto nightCycleManagers = model->getConcreteModelObjects<AvailabilityManagerNightCycle>();

  EXPECT_FALSE(availabilityManagerAssignmentLists.empty());
  EXPECT_FALSE(nightCycleManagers.empty());
}

TEST_F(SmallOfficeIDFFixture, AirLoopHVAC_IDF_AvailabilityManagersRoundTrip) {
  auto model = loadSmallOfficeModel();
  ASSERT_TRUE(model);

  const auto airLoops = model->getConcreteModelObjects<AirLoopHVAC>();
  const auto assignmentLists = model->getConcreteModelObjects<AvailabilityManagerAssignmentList>();
  ASSERT_FALSE(airLoops.empty());
  ASSERT_FALSE(assignmentLists.empty());

  for (const auto& airLoop : airLoops) {
    const auto managers = airLoop.availabilityManagers();
    ASSERT_FALSE(managers.empty());

    bool sawNightCycle = false;
    for (const auto& manager : managers) {
      EXPECT_TRUE(manager.loop());

      auto nightCycle = manager.optionalCast<AvailabilityManagerNightCycle>();
      if (nightCycle) {
        sawNightCycle = true;
        auto owningLoop = nightCycle->airLoopHVAC();
        ASSERT_TRUE(owningLoop);
        EXPECT_EQ(airLoop, *owningLoop);
      }
    }

    EXPECT_TRUE(sawNightCycle);
  }
}

TEST_F(SmallOfficeIDFFixture, AirLoopHVAC_IDF_CoilSystemCoolingDX_ImplOnlyNavigationRoundTrip) {
  auto model = loadSmallOfficeModel();
  ASSERT_TRUE(model);

  const auto coilSystems = model->getConcreteModelObjects<CoilSystemCoolingDX>();
  const auto dxCoils = model->getConcreteModelObjects<CoilCoolingDXSingleSpeed>();
  ASSERT_FALSE(coilSystems.empty());
  ASSERT_FALSE(dxCoils.empty());

  unsigned validated = 0u;
  for (const auto& coilSystem : coilSystems) {
    auto systemImpl = coilSystem.getImpl<openstudio::epmodel::detail::CoilSystemCoolingDX_Impl>();
    ASSERT_TRUE(systemImpl);

    auto coolingCoilObject = systemImpl->coolingCoil();
    ASSERT_TRUE(coolingCoilObject);

    const auto coilIt = std::find_if(dxCoils.begin(), dxCoils.end(),
                                     [&](const CoilCoolingDXSingleSpeed& coil) { return coil.cast<ModelObject>() == *coolingCoilObject; });
    ASSERT_NE(coilIt, dxCoils.end());
    const auto& coolingCoil = *coilIt;

    auto coolingCoilImpl = coolingCoil.getImpl<openstudio::epmodel::detail::CoilCoolingDXSingleSpeed_Impl>();
    ASSERT_TRUE(coolingCoilImpl);
    auto coilSystemFromCoil = coolingCoilImpl->coilSystemCoolingDX();
    ASSERT_TRUE(coilSystemFromCoil);
    EXPECT_EQ(coilSystem, *coilSystemFromCoil);

    ++validated;
  }

  EXPECT_GT(validated, 0u);
}

TEST_F(SmallOfficeIDFFixture, AirLoopHVAC_IDF_NodeSetpointManagersRoundTrip) {
  auto model = loadSmallOfficeModel();
  ASSERT_TRUE(model);

  const auto mixedAirManagers = model->getConcreteModelObjects<SetpointManagerMixedAir>();
  const auto scheduledManagers = model->getConcreteModelObjects<SetpointManagerScheduled>();
  const auto singleZoneReheatManagers = model->getConcreteModelObjects<SetpointManagerSingleZoneReheat>();

  const auto nodeContains = [](const Node& node, const SetpointManager& targetSPM) {
    const auto nodeSPMs = node.setpointManagers();
    return std::ranges::any_of(nodeSPMs, [&](const SetpointManager& spm) { return spm == targetSPM; });
  };

  unsigned validated = 0u;

  for (const auto& spm : mixedAirManagers) {
    auto node = spm.setpointNode();
    if (!node) {
      continue;
    }
    EXPECT_TRUE(nodeContains(*node, spm));
    ++validated;
  }

  for (const auto& spm : scheduledManagers) {
    auto node = spm.setpointNode();
    if (!node) {
      continue;
    }
    EXPECT_TRUE(nodeContains(*node, spm));
    ++validated;
  }

  for (const auto& spm : singleZoneReheatManagers) {
    auto node = spm.setpointNode();
    if (!node) {
      continue;
    }
    EXPECT_TRUE(nodeContains(*node, spm));
    ++validated;
  }

  EXPECT_GT(validated, 0u);
}

TEST_F(SmallOfficeIDFFixture, AirLoopHVAC_IDF_TerminalAndNodeNonMutationApis) {
  auto model = loadSmallOfficeModel();
  ASSERT_TRUE(model);

  const auto terminals = model->getConcreteModelObjects<AirTerminalSingleDuctConstantVolumeNoReheat>();
  ASSERT_FALSE(terminals.empty());

  for (const auto& terminal : terminals) {
    auto airLoop = terminal.airLoopHVAC();
    ASSERT_TRUE(airLoop);

    auto inletObject = terminal.inletModelObject();
    auto outletObject = terminal.outletModelObject();
    ASSERT_TRUE(inletObject);
    ASSERT_TRUE(outletObject);
    EXPECT_TRUE(inletObject->optionalCast<Node>());
    EXPECT_TRUE(outletObject->optionalCast<Node>());
  }

  const auto fans = model->getConcreteModelObjects<FanConstantVolume>();
  ASSERT_FALSE(fans.empty());
  for (const auto& fan : fans) {
    auto inletObject = fan.inletModelObject();
    auto outletObject = fan.outletModelObject();
    ASSERT_TRUE(inletObject);
    ASSERT_TRUE(outletObject);
    EXPECT_TRUE(inletObject->optionalCast<Node>());
    EXPECT_TRUE(outletObject->optionalCast<Node>());
    EXPECT_TRUE(fan.airLoopHVAC());
  }
}

TEST_F(SmallOfficeIDFFixture, AirLoopHVAC_IDF_SpacesAndSizingZonesLinkToThermalZones) {
  auto model = loadSmallOfficeModel();
  ASSERT_TRUE(model);

  const auto spaces = model->getConcreteModelObjects<Space>();
  const auto thermalZones = model->getConcreteModelObjects<ThermalZone>();
  const auto sizingZones = model->getConcreteModelObjects<SizingZone>();
  ASSERT_FALSE(thermalZones.empty());
  ASSERT_FALSE(sizingZones.empty());

  for (const auto& zone : thermalZones) {
    auto zoneSizing = zone.sizingZone();
    EXPECT_EQ(zone, zoneSizing.thermalZone());
  }

  if (!spaces.empty()) {
    unsigned spacesWithThermalZone = 0;
    for (const auto& space : spaces) {
      auto zone = space.thermalZone();
      if (zone) {
        ++spacesWithThermalZone;
      }
    }
    EXPECT_GT(spacesWithThermalZone, 0u);
  }
}

TEST_F(SmallOfficeIDFFixture, AirLoopHVAC_IDF_BranchAndBranchListNonMutationApis) {
  auto model = loadSmallOfficeModel();
  ASSERT_TRUE(model);

  const auto airLoops = model->getConcreteModelObjects<AirLoopHVAC>();
  ASSERT_FALSE(airLoops.empty());

  bool sawBranchViaList = false;
  for (const auto& airLoop : airLoops) {
    auto impl = airLoop.getImpl<detail::AirLoopHVAC_Impl>();
    ASSERT_TRUE(impl);
    const auto branchList = impl->branchList();
    const auto listedBranches = branchList.branches();
    for (const auto& branch : listedBranches) {
      sawBranchViaList = true;
      const auto components = branch.components();
      for (unsigned i = 0; i < components.size(); ++i) {
        auto inletNode = branch.componentInletNode(i);
        auto outletNode = branch.componentOutletNode(i);
        EXPECT_TRUE(inletNode);
        EXPECT_TRUE(outletNode);
      }
    }
  }
  EXPECT_TRUE(sawBranchViaList);
}

TEST_F(SmallOfficeIDFFixture, AirLoopHVAC_IDF_ZoneHVACEquipmentConnectionsNonMutationApis) {
  auto model = loadSmallOfficeModel();
  ASSERT_TRUE(model);

  const auto equipmentConnections = model->getConcreteModelObjects<ZoneHVACEquipmentConnections>();
  ASSERT_FALSE(equipmentConnections.empty());

  for (const auto& connection : equipmentConnections) {
    auto thermalZone = connection.thermalZone();
    auto zoneAirInletNode = connection.zoneAirInletNode();
    auto zoneReturnAirNode = connection.zoneReturnAirNode();
    const auto zoneAirInletNodes = connection.zoneAirInletNodes();
    const auto zoneReturnAirNodes = connection.zoneReturnAirNodes();
    EXPECT_TRUE(thermalZone);
    if (!zoneAirInletNodes.empty() && zoneAirInletNode) {
      EXPECT_EQ(*zoneAirInletNode, zoneAirInletNodes.front());
    }
    if (!zoneReturnAirNodes.empty() && zoneReturnAirNode) {
      EXPECT_EQ(*zoneReturnAirNode, zoneReturnAirNodes.front());
    }
  }
}

TEST_F(SmallOfficeIDFFixture, AirLoopHVAC_IDF_NodeRenamesPreserveTopologyLinks) {
  auto model = loadSmallOfficeModel();
  ASSERT_TRUE(model);

  const auto airLoops = model->getConcreteModelObjects<AirLoopHVAC>();
  const auto supplyPaths = model->getConcreteModelObjects<AirLoopHVACSupplyPath>();
  const auto returnPaths = model->getConcreteModelObjects<AirLoopHVACReturnPath>();
  const auto terminals = model->getConcreteModelObjects<AirTerminalSingleDuctConstantVolumeNoReheat>();
  const auto fans = model->getConcreteModelObjects<FanConstantVolume>();

  ASSERT_FALSE(airLoops.empty());
  ASSERT_FALSE(supplyPaths.empty());
  ASSERT_FALSE(returnPaths.empty());
  ASSERT_FALSE(terminals.empty());
  ASSERT_FALSE(fans.empty());

  std::vector<std::pair<AirLoopHVACSupplyPath, AirLoopHVAC>> supplyPathLinks;
  for (const auto& supplyPath : supplyPaths) {
    auto loop = supplyPath.airLoopHVAC();
    ASSERT_TRUE(loop);
    supplyPathLinks.emplace_back(supplyPath, *loop);
  }

  std::vector<std::pair<AirLoopHVACReturnPath, AirLoopHVAC>> returnPathLinks;
  for (const auto& returnPath : returnPaths) {
    auto loop = returnPath.airLoopHVAC();
    ASSERT_TRUE(loop);
    returnPathLinks.emplace_back(returnPath, *loop);
  }

  std::vector<std::pair<FanConstantVolume, AirLoopHVAC>> fanLinks;
  for (const auto& fan : fans) {
    auto loop = fan.airLoopHVAC();
    ASSERT_TRUE(loop);
    fanLinks.emplace_back(fan, *loop);
  }

  std::vector<std::pair<AirLoopHVACZoneSplitter, AirLoopHVAC>> splitterLinks;
  std::vector<std::pair<AirLoopHVACZoneMixer, AirLoopHVAC>> mixerLinks;
  for (const auto& airLoop : airLoops) {
    splitterLinks.emplace_back(airLoop.zoneSplitter(), airLoop);
    mixerLinks.emplace_back(airLoop.zoneMixer(), airLoop);
  }

  for (const auto& airLoop : airLoops) {
    auto demandInletNode = airLoop.demandInletNode();
    auto demandOutletNode = airLoop.demandOutletNode();
    ASSERT_TRUE(demandInletNode.setName(demandInletNode.nameString() + " Renamed"));
    ASSERT_TRUE(demandOutletNode.setName(demandOutletNode.nameString() + " Renamed"));
  }

  for (const auto& terminal : terminals) {
    auto inletObject = terminal.inletModelObject();
    ASSERT_TRUE(inletObject);
    auto inletNode = inletObject->optionalCast<Node>();
    ASSERT_TRUE(inletNode);
    ASSERT_TRUE(inletNode->setName(inletNode->nameString() + " Renamed"));
  }

  for (const auto& fan : fans) {
    auto inletObject = fan.inletModelObject();
    auto outletObject = fan.outletModelObject();
    ASSERT_TRUE(inletObject);
    ASSERT_TRUE(outletObject);
    auto inletNode = inletObject->optionalCast<Node>();
    auto outletNode = outletObject->optionalCast<Node>();
    ASSERT_TRUE(inletNode);
    ASSERT_TRUE(outletNode);
    ASSERT_TRUE(inletNode->setName(inletNode->nameString() + " Renamed"));
    ASSERT_TRUE(outletNode->setName(outletNode->nameString() + " Renamed"));
  }

  for (const auto& [supplyPath, expectedLoop] : supplyPathLinks) {
    auto loop = supplyPath.airLoopHVAC();
    ASSERT_TRUE(loop);
    EXPECT_EQ(expectedLoop, *loop);
  }

  for (const auto& [returnPath, expectedLoop] : returnPathLinks) {
    auto loop = returnPath.airLoopHVAC();
    ASSERT_TRUE(loop);
    EXPECT_EQ(expectedLoop, *loop);
  }

  for (const auto& terminal : terminals) {
    auto inletObject = terminal.inletModelObject();
    ASSERT_TRUE(inletObject);
    EXPECT_TRUE(inletObject->optionalCast<Node>());
  }

  for (const auto& [splitter, expectedLoop] : splitterLinks) {
    auto loop = splitter.airLoopHVAC();
    ASSERT_TRUE(loop);
    EXPECT_EQ(expectedLoop, *loop);
  }

  for (const auto& [mixer, expectedLoop] : mixerLinks) {
    auto loop = mixer.airLoopHVAC();
    ASSERT_TRUE(loop);
    EXPECT_EQ(expectedLoop, *loop);
  }

  for (const auto& [fan, expectedLoop] : fanLinks) {
    auto loop = fan.airLoopHVAC();
    ASSERT_TRUE(loop);
    EXPECT_EQ(expectedLoop, *loop);
  }
}

TEST_F(SmallOfficeIDFFixture, AirLoopHVAC_IDF_HvacComponentRenamesPreserveTopologyLinks) {
  auto model = loadSmallOfficeModel();
  ASSERT_TRUE(model);

  const auto airLoops = model->getConcreteModelObjects<AirLoopHVAC>();
  const auto terminals = model->getConcreteModelObjects<AirTerminalSingleDuctConstantVolumeNoReheat>();
  const auto fans = model->getConcreteModelObjects<FanConstantVolume>();
  const auto airDistributionUnits = model->getConcreteModelObjects<ZoneHVACAirDistributionUnit>();

  ASSERT_FALSE(airLoops.empty());
  ASSERT_FALSE(terminals.empty());
  ASSERT_FALSE(fans.empty());
  ASSERT_FALSE(airDistributionUnits.empty());

  std::vector<std::pair<AirTerminalSingleDuctConstantVolumeNoReheat, AirLoopHVAC>> terminalLinks;
  for (const auto& terminal : terminals) {
    auto loop = terminal.airLoopHVAC();
    ASSERT_TRUE(loop);
    terminalLinks.emplace_back(terminal, *loop);
  }

  std::vector<std::pair<FanConstantVolume, AirLoopHVAC>> fanLinks;
  for (const auto& fan : fans) {
    auto loop = fan.airLoopHVAC();
    ASSERT_TRUE(loop);
    fanLinks.emplace_back(fan, *loop);
  }

  std::vector<std::pair<ZoneHVACAirDistributionUnit, std::string>> aduToTerminalName;
  for (const auto& adu : airDistributionUnits) {
    auto terminalObject = adu.airTerminal();
    ASSERT_TRUE(terminalObject);
    auto terminalName = terminalObject->name();
    ASSERT_TRUE(terminalName);
    aduToTerminalName.emplace_back(adu, *terminalName);
  }

  for (auto& fan : model->getConcreteModelObjects<FanConstantVolume>()) {
    ASSERT_TRUE(fan.setName(fan.nameString() + " Renamed"));
  }
  for (auto& terminal : model->getConcreteModelObjects<AirTerminalSingleDuctConstantVolumeNoReheat>()) {
    ASSERT_TRUE(terminal.setName(terminal.nameString() + " Renamed"));
  }
  for (auto& airLoop : model->getConcreteModelObjects<AirLoopHVAC>()) {
    auto zoneSplitter = airLoop.zoneSplitter();
    auto zoneMixer = airLoop.zoneMixer();
    ASSERT_TRUE(zoneSplitter.setName(zoneSplitter.nameString() + " Renamed"));
    ASSERT_TRUE(zoneMixer.setName(zoneMixer.nameString() + " Renamed"));
  }

  for (const auto& [fan, expectedLoop] : fanLinks) {
    auto loop = fan.airLoopHVAC();
    ASSERT_TRUE(loop);
    EXPECT_EQ(expectedLoop, *loop);
    auto maybeSupplyComponent = loop->supplyComponent(fan.handle());
    ASSERT_TRUE(maybeSupplyComponent);
    EXPECT_EQ(fan.cast<ModelObject>(), *maybeSupplyComponent);
  }

  for (const auto& [terminal, expectedLoop] : terminalLinks) {
    auto loop = terminal.airLoopHVAC();
    ASSERT_TRUE(loop);
    EXPECT_EQ(expectedLoop, *loop);
  }

  for (const auto& [adu, oldTerminalName] : aduToTerminalName) {
    auto terminalObject = adu.airTerminal();
    ASSERT_TRUE(terminalObject);
    auto terminalName = terminalObject->name();
    ASSERT_TRUE(terminalName);
    EXPECT_NE(*terminalName, oldTerminalName);
  }
}
