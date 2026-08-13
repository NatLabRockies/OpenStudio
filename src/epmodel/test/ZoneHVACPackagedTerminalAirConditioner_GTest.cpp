/***********************************************************************************************************************  
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.  
*  See also https://openstudio.net/license  
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ZoneHVACComponent/ZoneHVACPackagedTerminalAirConditioner.hpp"
#include "../ZoneHVACComponent/ZoneHVACPackagedTerminalAirConditioner_Impl.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../Schedule/ScheduleCompact.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../StraightComponent/Node.hpp"
#include "../ModelObject/OutdoorAirMixer.hpp"
#include "../ModelObject/OutdoorAirMixer_Impl.hpp"
#include "../StraightComponent/FanConstantVolume.hpp"
#include "../StraightComponent/CoilCoolingDXSingleSpeed.hpp"
#include "../StraightComponent/CoilCoolingDXSingleSpeed_Impl.hpp"
#include "../WaterToAirComponent/CoilHeatingWater.hpp"
#include "../HVACComponent/ThermalZone.hpp"

#include <utilities/idd/ZoneHVAC_PackagedTerminalAirConditioner_FieldEnums.hxx>
#include <utilities/idd/OutdoorAir_NodeList_FieldEnums.hxx>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>

using namespace openstudio::epmodel;

namespace {
unsigned ptacOutdoorAirNodeListEntryCount(const Model& model, const std::string& nodeName) {
  unsigned result = 0u;
  for (const auto& object : model.getObjectsByType(openstudio::IddObjectType::OutdoorAir_NodeList)) {
    for (const auto& group : object.extensibleGroups()) {
      auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
      if (!workspaceGroup) {
        continue;
      }
      const auto listedNodeName = workspaceGroup->getString(openstudio::OutdoorAir_NodeListExtensibleFields::NodeorNodeListName);
      if (listedNodeName && openstudio::istringEqual(*listedNodeName, nodeName)) {
        ++result;
      }
    }
  }
  return result;
}
}  // namespace

TEST_F(EPModelFixture, ZoneHVACPackagedTerminalAirConditioner_DefaultConstructor) {
  Model model;
  ZoneHVACPackagedTerminalAirConditioner ptac(model);

  EXPECT_FALSE(ptac.supplyAirFlowRateDuringCoolingOperation());
  EXPECT_FALSE(ptac.isSupplyAirFlowRateDuringCoolingOperationAutosized());
  EXPECT_FALSE(ptac.supplyAirFlowRateDuringHeatingOperation());
  EXPECT_FALSE(ptac.isSupplyAirFlowRateDuringHeatingOperationAutosized());
  EXPECT_FALSE(ptac.supplyAirFlowRateWhenNoCoolingorHeatingisNeeded());
  EXPECT_FALSE(ptac.isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized());
  EXPECT_FALSE(ptac.noLoadSupplyAirFlowRateControlSetToLowSpeed());
  EXPECT_FALSE(ptac.outdoorAirFlowRateDuringCoolingOperation());
  EXPECT_FALSE(ptac.isOutdoorAirFlowRateDuringCoolingOperationAutosized());
  EXPECT_FALSE(ptac.outdoorAirFlowRateDuringHeatingOperation());
  EXPECT_FALSE(ptac.isOutdoorAirFlowRateDuringHeatingOperationAutosized());
  EXPECT_FALSE(ptac.outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded());
  EXPECT_FALSE(ptac.isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized());
  EXPECT_TRUE(ptac.isFanPlacementDefaulted());
  EXPECT_EQ("", ptac.fanPlacement());
}

TEST_F(EPModelFixture, ZoneHVACPackagedTerminalAirConditioner_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneHVACPackagedTerminalAirConditioner ptac(model);

  EXPECT_TRUE(ptac.setSupplyAirFlowRateDuringCoolingOperation(0.5));
  ASSERT_TRUE(ptac.supplyAirFlowRateDuringCoolingOperation());
  EXPECT_DOUBLE_EQ(0.5, ptac.supplyAirFlowRateDuringCoolingOperation().get());
  EXPECT_FALSE(ptac.isSupplyAirFlowRateDuringCoolingOperationAutosized());
  ptac.autosizeSupplyAirFlowRateDuringCoolingOperation();
  EXPECT_TRUE(ptac.isSupplyAirFlowRateDuringCoolingOperationAutosized());
  EXPECT_FALSE(ptac.supplyAirFlowRateDuringCoolingOperation());

  EXPECT_TRUE(ptac.setSupplyAirFlowRateDuringHeatingOperation(0.55));
  ASSERT_TRUE(ptac.supplyAirFlowRateDuringHeatingOperation());
  EXPECT_DOUBLE_EQ(0.55, ptac.supplyAirFlowRateDuringHeatingOperation().get());
  ptac.autosizeSupplyAirFlowRateDuringHeatingOperation();
  EXPECT_TRUE(ptac.isSupplyAirFlowRateDuringHeatingOperationAutosized());

  EXPECT_TRUE(ptac.setSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded(0.12));
  ASSERT_TRUE(ptac.supplyAirFlowRateWhenNoCoolingorHeatingisNeeded());
  EXPECT_DOUBLE_EQ(0.12, ptac.supplyAirFlowRateWhenNoCoolingorHeatingisNeeded().get());
  ptac.resetSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
  EXPECT_FALSE(ptac.supplyAirFlowRateWhenNoCoolingorHeatingisNeeded());
  ptac.autosizeSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
  EXPECT_TRUE(ptac.isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized());

  EXPECT_TRUE(ptac.setNoLoadSupplyAirFlowRateControlSetToLowSpeed(true));
  EXPECT_TRUE(ptac.noLoadSupplyAirFlowRateControlSetToLowSpeed());

  EXPECT_TRUE(ptac.setOutdoorAirFlowRateDuringCoolingOperation(0.09));
  ptac.autosizeOutdoorAirFlowRateDuringCoolingOperation();
  EXPECT_TRUE(ptac.isOutdoorAirFlowRateDuringCoolingOperationAutosized());

  EXPECT_TRUE(ptac.setOutdoorAirFlowRateDuringHeatingOperation(0.06));
  ptac.autosizeOutdoorAirFlowRateDuringHeatingOperation();
  EXPECT_TRUE(ptac.isOutdoorAirFlowRateDuringHeatingOperationAutosized());

  EXPECT_TRUE(ptac.setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(0.02));
  ptac.resetOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
  EXPECT_FALSE(ptac.outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded());
  ptac.autosizeOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
  EXPECT_TRUE(ptac.isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized());

  EXPECT_TRUE(ptac.setFanPlacement("BlowThrough"));
  EXPECT_EQ("BlowThrough", ptac.fanPlacement());
  ptac.resetFanPlacement();
  EXPECT_TRUE(ptac.isFanPlacementDefaulted());
}

TEST_F(EPModelFixture, ZoneHVACPackagedTerminalAirConditioner_TopologyAndChildren) {
  Model model;
  FanConstantVolume fan(model);
  CoilHeatingWater heatingCoil(model);
  CoilCoolingDXSingleSpeed coolingCoil(model);
  ZoneHVACPackagedTerminalAirConditioner ptac(model);

  ASSERT_TRUE(ptac.setOutdoorAirFlowRateDuringCoolingOperation(0.0));
  ASSERT_TRUE(ptac.setOutdoorAirFlowRateDuringHeatingOperation(0.0));
  ASSERT_TRUE(ptac.setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(0.0));
  ASSERT_TRUE(ptac.setFanPlacement("DrawThrough"));
  EXPECT_TRUE(ptac.setSupplyAirFan(fan));
  EXPECT_TRUE(ptac.setHeatingCoil(heatingCoil));
  EXPECT_TRUE(ptac.setCoolingCoil(coolingCoil));

  const auto children = ptac.children();
  ASSERT_EQ(3u, children.size());
  EXPECT_EQ(heatingCoil, children[0]);
  EXPECT_EQ(fan, children[1]);
  EXPECT_EQ(coolingCoil, children[2]);

  ASSERT_TRUE(fan.containingZoneHVACComponent());
  ASSERT_TRUE(heatingCoil.containingZoneHVACComponent());
  ASSERT_TRUE(coolingCoil.containingZoneHVACComponent());
  EXPECT_EQ(ptac, fan.containingZoneHVACComponent().get());
  EXPECT_EQ(ptac, heatingCoil.containingZoneHVACComponent().get());
  EXPECT_EQ(ptac, coolingCoil.containingZoneHVACComponent().get());

  EXPECT_EQ(openstudio::ZoneHVAC_PackagedTerminalAirConditionerFields::AirInletNodeName, ptac.inletPort());
  EXPECT_EQ(openstudio::ZoneHVAC_PackagedTerminalAirConditionerFields::AirOutletNodeName, ptac.outletPort());

  auto ptacFanOutlet = ptac.fanOutletNode();
  auto ptacCoolingOutlet = ptac.coolingCoilOutletNode();
  auto ptacHeatingOutlet = ptac.heatingCoilOutletNode();
  auto fanInlet = fan.inletModelObject()->optionalCast<Node>();
  auto fanOutlet = fan.outletModelObject()->optionalCast<Node>();
  auto coolingInlet = coolingCoil.inletModelObject()->optionalCast<Node>();
  auto coolingOutlet = coolingCoil.outletModelObject()->optionalCast<Node>();
  auto heatingInlet = heatingCoil.airInletModelObject()->optionalCast<Node>();
  auto heatingOutlet = heatingCoil.airOutletModelObject()->optionalCast<Node>();
  ASSERT_TRUE(ptacFanOutlet);
  ASSERT_TRUE(ptacCoolingOutlet);
  ASSERT_TRUE(ptacHeatingOutlet);
  ASSERT_TRUE(fanInlet);
  ASSERT_TRUE(fanOutlet);
  ASSERT_TRUE(coolingInlet);
  ASSERT_TRUE(coolingOutlet);
  ASSERT_TRUE(heatingInlet);
  ASSERT_TRUE(heatingOutlet);

  EXPECT_EQ(*ptacCoolingOutlet, *coolingOutlet);
  EXPECT_EQ(*ptacCoolingOutlet, *heatingInlet);
  EXPECT_EQ(*ptacHeatingOutlet, *heatingOutlet);
  EXPECT_EQ(*ptacHeatingOutlet, *fanInlet);
  EXPECT_EQ(*ptacFanOutlet, *fanOutlet);

  ThermalZone zone(model);
  EXPECT_TRUE(ptac.addToThermalZone(zone));
  ASSERT_TRUE(ptac.thermalZone());
  ASSERT_TRUE(ptac.inletNode());
  ASSERT_TRUE(ptac.outletNode());
  EXPECT_EQ(zone, ptac.thermalZone().get());
  EXPECT_NE(ptac.inletNode()->handle(), ptac.outletNode()->handle());
  EXPECT_EQ(*ptac.inletNode(), *coolingInlet);
  EXPECT_EQ(*ptac.outletNode(), *ptacFanOutlet);
  auto detachedInlet = ptac.inletNode();
  auto detachedOutlet = ptac.outletNode();
  ptac.removeFromThermalZone();
  EXPECT_FALSE(ptac.thermalZone());
  ASSERT_TRUE(ptac.inletNode());
  ASSERT_TRUE(ptac.outletNode());
  EXPECT_EQ(*detachedInlet, *ptac.inletNode());
  EXPECT_EQ(*detachedOutlet, *ptac.outletNode());
}

TEST_F(EPModelFixture, ZoneHVACPackagedTerminalAirConditioner_NodeRolesMayAliasBoundaryNodes) {
  Model model;
  FanConstantVolume fan(model);
  CoilHeatingWater heatingCoil(model);
  CoilCoolingDXSingleSpeed coolingCoil(model);
  ZoneHVACPackagedTerminalAirConditioner ptac(model);

  ASSERT_TRUE(ptac.setOutdoorAirFlowRateDuringCoolingOperation(0.0));
  ASSERT_TRUE(ptac.setOutdoorAirFlowRateDuringHeatingOperation(0.0));
  ASSERT_TRUE(ptac.setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(0.0));
  ASSERT_TRUE(ptac.setFanPlacement("BlowThrough"));
  ASSERT_TRUE(ptac.setSupplyAirFan(fan));
  ASSERT_TRUE(ptac.setHeatingCoil(heatingCoil));
  ASSERT_TRUE(ptac.setCoolingCoil(coolingCoil));

  auto fanOutletNode = ptac.fanOutletNode();
  auto coolingCoilOutletNode = ptac.coolingCoilOutletNode();
  auto heatingCoilOutletNode = ptac.heatingCoilOutletNode();
  auto ptacOutlet = ptac.outletNode();
  ASSERT_TRUE(fanOutletNode);
  ASSERT_TRUE(coolingCoilOutletNode);
  ASSERT_TRUE(heatingCoilOutletNode);
  ASSERT_TRUE(ptacOutlet);

  EXPECT_EQ(*fanOutletNode, *coolingCoil.inletModelObject()->optionalCast<Node>());
  EXPECT_EQ(*coolingCoilOutletNode, *heatingCoil.airInletModelObject()->optionalCast<Node>());
  EXPECT_EQ(*heatingCoilOutletNode, *ptacOutlet);
}

TEST_F(EPModelFixture, ZoneHVACPackagedTerminalAirConditioner_ScheduleRelationships_RoundTrip) {
  Model model;
  ZoneHVACPackagedTerminalAirConditioner ptac(model);

  auto defaultAvailability = ptac.availabilitySchedule().optionalCast<ScheduleConstant>();
  ASSERT_TRUE(defaultAvailability);
  EXPECT_DOUBLE_EQ(1.0, defaultAvailability->value());
  auto defaultFanMode = ptac.supplyAirFanOperatingModeSchedule().optionalCast<ScheduleConstant>();
  ASSERT_TRUE(defaultFanMode);
  EXPECT_DOUBLE_EQ(1.0, defaultFanMode->value());

  ScheduleCompact availability(model);
  ScheduleCompact fanMode(model);
  ASSERT_TRUE(availability.setToConstantValue(0.6));
  ASSERT_TRUE(fanMode.setToConstantValue(0.0));

  EXPECT_TRUE(ptac.setAvailabilitySchedule(availability));
  EXPECT_TRUE(ptac.setSupplyAirFanOperatingModeSchedule(fanMode));
  EXPECT_EQ(availability.handle(), ptac.availabilitySchedule().handle());
  EXPECT_EQ(fanMode.handle(), ptac.supplyAirFanOperatingModeSchedule().handle());
}

TEST_F(EPModelFixture, ZoneHVACPackagedTerminalAirConditioner_InternalNodeRenamesSurviveCanonicalize) {
  Model model;
  FanConstantVolume fan(model);
  CoilHeatingWater heatingCoil(model);
  CoilCoolingDXSingleSpeed coolingCoil(model);
  ZoneHVACPackagedTerminalAirConditioner ptac(model);

  ASSERT_TRUE(ptac.setOutdoorAirFlowRateDuringCoolingOperation(0.0));
  ASSERT_TRUE(ptac.setOutdoorAirFlowRateDuringHeatingOperation(0.0));
  ASSERT_TRUE(ptac.setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(0.0));
  ASSERT_TRUE(ptac.setFanPlacement("DrawThrough"));
  ASSERT_TRUE(ptac.setSupplyAirFan(fan));
  ASSERT_TRUE(ptac.setHeatingCoil(heatingCoil));
  ASSERT_TRUE(ptac.setCoolingCoil(coolingCoil));

  auto fanOutletNode = ptac.fanOutletNode();
  auto coolingCoilOutletNode = ptac.coolingCoilOutletNode();
  auto heatingCoilOutletNode = ptac.heatingCoilOutletNode();
  ASSERT_TRUE(fanOutletNode);
  ASSERT_TRUE(coolingCoilOutletNode);
  ASSERT_TRUE(heatingCoilOutletNode);

  ASSERT_TRUE(fanOutletNode->setName("Custom PTAC Fan Outlet"));
  ASSERT_TRUE(coolingCoilOutletNode->setName("Custom PTAC Cooling Outlet"));
  ASSERT_TRUE(heatingCoilOutletNode->setName("Custom PTAC Heating Outlet"));

  auto report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);

  ASSERT_TRUE(ptac.fanOutletNode());
  ASSERT_TRUE(ptac.coolingCoilOutletNode());
  ASSERT_TRUE(ptac.heatingCoilOutletNode());
  EXPECT_EQ("Custom PTAC Fan Outlet", ptac.fanOutletNode()->nameString());
  EXPECT_EQ("Custom PTAC Cooling Outlet", ptac.coolingCoilOutletNode()->nameString());
  EXPECT_EQ("Custom PTAC Heating Outlet", ptac.heatingCoilOutletNode()->nameString());
}

TEST_F(EPModelFixture, ZoneHVACPackagedTerminalAirConditioner_ContainedChildTopologyMutationsAreRejected) {
  Model model;
  AirLoopHVAC airLoop(model);
  PlantLoop plantLoop(model);
  FanConstantVolume fan(model);
  CoilHeatingWater heatingCoil(model);
  CoilCoolingDXSingleSpeed coolingCoil(model);
  ZoneHVACPackagedTerminalAirConditioner ptac(model);

  ASSERT_TRUE(ptac.setOutdoorAirFlowRateDuringCoolingOperation(0.0));
  ASSERT_TRUE(ptac.setOutdoorAirFlowRateDuringHeatingOperation(0.0));
  ASSERT_TRUE(ptac.setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(0.0));
  ASSERT_TRUE(ptac.setFanPlacement("DrawThrough"));
  ASSERT_TRUE(ptac.setSupplyAirFan(fan));
  ASSERT_TRUE(ptac.setHeatingCoil(heatingCoil));
  ASSERT_TRUE(ptac.setCoolingCoil(coolingCoil));

  auto originalFanOutlet = ptac.fanOutletNode();
  auto originalCoolingOutlet = ptac.coolingCoilOutletNode();
  auto originalHeatingOutlet = ptac.heatingCoilOutletNode();
  ASSERT_TRUE(originalFanOutlet);
  ASSERT_TRUE(originalCoolingOutlet);
  ASSERT_TRUE(originalHeatingOutlet);

  auto supplyOutletNode = airLoop.supplyOutletNode();
  fan.disconnect();
  EXPECT_FALSE(fan.addToNode(supplyOutletNode));
  EXPECT_FALSE(fan.isRemovable());
  EXPECT_TRUE(fan.remove().empty());

  heatingCoil.disconnectAirSide();
  EXPECT_FALSE(heatingCoil.addToNode(supplyOutletNode));
  EXPECT_FALSE(heatingCoil.removeFromAirLoopHVAC());
  EXPECT_FALSE(heatingCoil.isRemovable());
  EXPECT_TRUE(heatingCoil.remove().empty());
  EXPECT_TRUE(plantLoop.addDemandBranchForComponent(heatingCoil));
  ASSERT_TRUE(heatingCoil.plantLoop());
  heatingCoil.disconnect();
  ASSERT_TRUE(heatingCoil.plantLoop());

  ASSERT_TRUE(ptac.fanOutletNode());
  ASSERT_TRUE(ptac.coolingCoilOutletNode());
  ASSERT_TRUE(ptac.heatingCoilOutletNode());
  EXPECT_EQ(*originalFanOutlet, *ptac.fanOutletNode());
  EXPECT_EQ(*originalCoolingOutlet, *ptac.coolingCoilOutletNode());
  EXPECT_EQ(*originalHeatingOutlet, *ptac.heatingCoilOutletNode());
}

TEST_F(EPModelFixture, ZoneHVACPackagedTerminalAirConditioner_CanonicalizeRepairsContainedNodePath) {
  Model model;
  FanConstantVolume fan(model);
  CoilHeatingWater heatingCoil(model);
  CoilCoolingDXSingleSpeed coolingCoil(model);
  ZoneHVACPackagedTerminalAirConditioner ptac(model);

  ASSERT_TRUE(ptac.setOutdoorAirFlowRateDuringCoolingOperation(0.0));
  ASSERT_TRUE(ptac.setOutdoorAirFlowRateDuringHeatingOperation(0.0));
  ASSERT_TRUE(ptac.setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(0.0));
  ASSERT_TRUE(ptac.setFanPlacement("DrawThrough"));
  ASSERT_TRUE(ptac.setSupplyAirFan(fan));
  ASSERT_TRUE(ptac.setHeatingCoil(heatingCoil));
  ASSERT_TRUE(ptac.setCoolingCoil(coolingCoil));

  auto expectedCoolingOutlet = ptac.coolingCoilOutletNode();
  auto expectedHeatingOutlet = ptac.heatingCoilOutletNode();
  auto expectedFanOutlet = ptac.fanOutletNode();
  ASSERT_TRUE(expectedCoolingOutlet);
  ASSERT_TRUE(expectedHeatingOutlet);
  ASSERT_TRUE(expectedFanOutlet);

  ASSERT_TRUE(ptac.inletNode());
  ASSERT_TRUE(ptac.outletNode());
  ASSERT_TRUE(coolingCoil.setPointer(coolingCoil.outletPort(), ptac.inletNode()->handle()));
  ASSERT_TRUE(heatingCoil.setPointer(heatingCoil.airInletPort(), ptac.inletNode()->handle()));
  ASSERT_TRUE(heatingCoil.setPointer(heatingCoil.airOutletPort(), ptac.outletNode()->handle()));
  ASSERT_TRUE(fan.setPointer(fan.inletPort(), ptac.outletNode()->handle()));
  ASSERT_TRUE(fan.setPointer(fan.outletPort(), ptac.inletNode()->handle()));

  auto report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);

  ASSERT_TRUE(ptac.coolingCoilOutletNode());
  ASSERT_TRUE(ptac.heatingCoilOutletNode());
  ASSERT_TRUE(ptac.fanOutletNode());
  EXPECT_EQ(*expectedCoolingOutlet, *ptac.coolingCoilOutletNode());
  EXPECT_EQ(*expectedHeatingOutlet, *ptac.heatingCoilOutletNode());
  EXPECT_EQ(*expectedFanOutlet, *ptac.fanOutletNode());
}

TEST_F(EPModelFixture, ZoneHVACPackagedTerminalAirConditioner_HiddenMixedAirNodeMaintenanceAndRepairStaySeparate) {
  Model model;
  FanConstantVolume fan(model);
  CoilHeatingWater heatingCoil(model);
  CoilCoolingDXSingleSpeed coolingCoil(model);
  ZoneHVACPackagedTerminalAirConditioner ptac(model);

  ASSERT_TRUE(ptac.setOutdoorAirFlowRateDuringCoolingOperation(0.09));
  ASSERT_TRUE(ptac.setOutdoorAirFlowRateDuringHeatingOperation(0.06));
  ASSERT_TRUE(ptac.setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(0.02));
  ASSERT_TRUE(ptac.setFanPlacement("DrawThrough"));
  ASSERT_TRUE(ptac.setSupplyAirFan(fan));
  ASSERT_TRUE(ptac.setHeatingCoil(heatingCoil));
  ASSERT_TRUE(ptac.setCoolingCoil(coolingCoil));

  auto ptacInlet = ptac.inletNode();
  auto coolingInlet = coolingCoil.inletModelObject()->optionalCast<Node>();
  ASSERT_TRUE(ptacInlet);
  ASSERT_TRUE(coolingInlet);
  EXPECT_NE(*ptacInlet, *coolingInlet);

  Node rogueMaintenanceMixedAir(model);
  ASSERT_TRUE(rogueMaintenanceMixedAir.setName("Rogue PTAC Maintenance Mixed Air"));
  ASSERT_TRUE(coolingCoil.setPointer(coolingCoil.inletPort(), rogueMaintenanceMixedAir.handle()));
  ASSERT_TRUE(ptac.setFanPlacement("DrawThrough"));
  ASSERT_TRUE(coolingCoil.inletModelObject()->optionalCast<Node>());
  EXPECT_NE(rogueMaintenanceMixedAir, *coolingCoil.inletModelObject()->optionalCast<Node>());

  Node rogueRepairMixedAir(model);
  ASSERT_TRUE(rogueRepairMixedAir.setName("Rogue PTAC Repair Mixed Air"));
  ASSERT_TRUE(coolingCoil.setPointer(coolingCoil.inletPort(), rogueRepairMixedAir.handle()));

  auto report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);
  ASSERT_TRUE(coolingCoil.inletModelObject()->optionalCast<Node>());
  EXPECT_EQ(rogueRepairMixedAir, *coolingCoil.inletModelObject()->optionalCast<Node>());
}

TEST_F(EPModelFixture, ZoneHVACPackagedTerminalAirConditioner_OwnsPersistedOutdoorAirPath) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-ptac-outdoor-air-path.idf");
  Model model;
  FanConstantVolume fan(model);
  CoilHeatingWater heatingCoil(model);
  CoilCoolingDXSingleSpeed coolingCoil(model);
  ZoneHVACPackagedTerminalAirConditioner ptac(model);
  ThermalZone zone(model);

  ASSERT_TRUE(ptac.setName("Outdoor Air PTAC"));
  ASSERT_TRUE(ptac.setFanPlacement("DrawThrough"));
  ASSERT_TRUE(ptac.setSupplyAirFan(fan));
  ASSERT_TRUE(ptac.setHeatingCoil(heatingCoil));
  ASSERT_TRUE(ptac.setCoolingCoil(coolingCoil));
  ASSERT_TRUE(ptac.setOutdoorAirFlowRateDuringCoolingOperation(0.09));
  ASSERT_TRUE(ptac.setOutdoorAirFlowRateDuringHeatingOperation(0.06));
  ASSERT_TRUE(ptac.setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(0.02));
  ASSERT_TRUE(ptac.addToThermalZone(zone));

  auto mixer = ptac.getModelObjectTarget<OutdoorAirMixer>(openstudio::ZoneHVAC_PackagedTerminalAirConditionerFields::OutdoorAirMixerName);
  ASSERT_TRUE(mixer);
  EXPECT_EQ("OutdoorAir:Mixer", ptac.getString(openstudio::ZoneHVAC_PackagedTerminalAirConditionerFields::OutdoorAirMixerObjectType).get());
  ASSERT_TRUE(mixer->mixedAirNode());
  ASSERT_TRUE(mixer->outdoorAirNode());
  ASSERT_TRUE(mixer->reliefAirNode());
  ASSERT_TRUE(mixer->returnAirNode());
  ASSERT_TRUE(ptac.inletNode());
  ASSERT_TRUE(coolingCoil.inletModelObject());
  EXPECT_EQ(coolingCoil.inletModelObject()->handle(), mixer->mixedAirNode()->handle());
  EXPECT_EQ(ptac.inletNode()->handle(), mixer->returnAirNode()->handle());
  EXPECT_EQ(1u, ptacOutdoorAirNodeListEntryCount(model, mixer->outdoorAirNode()->nameString()));
  EXPECT_EQ(4u, ptac.children().size());

  ASSERT_TRUE(model.save(idfPath, true));
  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedPTAC = loadedModel->getConcreteModelObjectByName<ZoneHVACPackagedTerminalAirConditioner>("Outdoor Air PTAC");
  ASSERT_TRUE(loadedPTAC);
  auto loadedMixer =
    loadedPTAC->getModelObjectTarget<OutdoorAirMixer>(openstudio::ZoneHVAC_PackagedTerminalAirConditionerFields::OutdoorAirMixerName);
  ASSERT_TRUE(loadedMixer);
  ASSERT_TRUE(loadedMixer->outdoorAirNode());
  EXPECT_EQ(1u, ptacOutdoorAirNodeListEntryCount(*loadedModel, loadedMixer->outdoorAirNode()->nameString()));

  const auto outdoorAirNodeName = loadedMixer->outdoorAirNode()->nameString();
  ASSERT_TRUE(loadedPTAC->setOutdoorAirFlowRateDuringCoolingOperation(0.0));
  ASSERT_TRUE(loadedPTAC->setOutdoorAirFlowRateDuringHeatingOperation(0.0));
  ASSERT_TRUE(loadedPTAC->setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(0.0));
  EXPECT_FALSE(loadedPTAC->getModelObjectTarget<OutdoorAirMixer>(openstudio::ZoneHVAC_PackagedTerminalAirConditionerFields::OutdoorAirMixerName));
  EXPECT_TRUE(loadedModel->getConcreteModelObjects<OutdoorAirMixer>().empty());
  EXPECT_EQ(0u, ptacOutdoorAirNodeListEntryCount(*loadedModel, outdoorAirNodeName));
  ASSERT_TRUE(loadedPTAC->inletNode());
  auto loadedCoolingCoil = loadedPTAC->coolingCoil().optionalCast<CoilCoolingDXSingleSpeed>();
  ASSERT_TRUE(loadedCoolingCoil);
  ASSERT_TRUE(loadedCoolingCoil->inletModelObject());
  EXPECT_EQ(loadedPTAC->inletNode()->handle(), loadedCoolingCoil->inletModelObject()->handle());

  openstudio::filesystem::remove(idfPath);
}
