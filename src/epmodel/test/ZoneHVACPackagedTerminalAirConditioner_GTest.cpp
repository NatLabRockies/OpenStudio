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
#include "../ResourceObject/ScheduleTypeLimits.hpp"
#include "../StraightComponent/Node.hpp"
#include "../ModelObject/OutdoorAirMixer.hpp"
#include "../ModelObject/OutdoorAirMixer_Impl.hpp"
#include "../StraightComponent/FanConstantVolume.hpp"
#include "../StraightComponent/FanConstantVolume_Impl.hpp"
#include "../StraightComponent/FanOnOff.hpp"
#include "../StraightComponent/FanOnOff_Impl.hpp"
#include "../StraightComponent/CoilCoolingDXSingleSpeed.hpp"
#include "../StraightComponent/CoilCoolingDXSingleSpeed_Impl.hpp"
#include "../StraightComponent/CoilHeatingElectric.hpp"
#include "../StraightComponent/CoilHeatingElectric_Impl.hpp"
#include "../WaterToAirComponent/CoilHeatingWater.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../HVACComponent/ThermalZone_Impl.hpp"

#include <utilities/core/Filesystem.hpp>
#include <utilities/core/UUID.hpp>
#include <utilities/idd/OutdoorAir_NodeList_FieldEnums.hxx>
#include <utilities/idd/AirLoopHVAC_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_PackagedTerminalAirConditioner_FieldEnums.hxx>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>
#include <utilities/idf/WorkspaceObject_Impl.hpp>

#include <utility>

using namespace openstudio::epmodel;

namespace {
class ScopedPtacFileRemoval
{
 public:
  explicit ScopedPtacFileRemoval(openstudio::path path) : m_path(std::move(path)) {}

  ~ScopedPtacFileRemoval() {
    boost::system::error_code error;
    boost::filesystem::remove(m_path, error);
  }

 private:
  openstudio::path m_path;
};

openstudio::path uniquePtacIdfPath(const std::string& stem) {
  return openstudio::tempDir() / openstudio::toPath(stem + "-" + openstudio::removeBraces(openstudio::createUUID()) + ".idf");
}

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

TEST_F(EPModelFixture, ZoneHVACPackagedTerminalAirConditioner_CanonicalizeDoesNotTraverseUnreadyAirLoop) {
  Model model;
  AirLoopHVAC unreadyAirLoop(model);
  ZoneHVACPackagedTerminalAirConditioner ptac(model);

  // This intentionally models load-order state: another AirLoop exists, but its
  // outlet NodeList relationship has not yet been canonicalized. PTAC repair must
  // classify its own managed Branch ownership without traversing that sibling.
  ASSERT_TRUE(unreadyAirLoop.setPointer(openstudio::AirLoopHVACFields::SupplySideOutletNodeNames, openstudio::Handle()));
  EXPECT_FALSE(unreadyAirLoop.getTarget(openstudio::AirLoopHVACFields::SupplySideOutletNodeNames));

  detail::LoadContext context{model, SanitizationPolicy::Repair, SanitizationReport{}, {}};
  ptac.getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->canonicalize(context);

  EXPECT_EQ(0u, context.report.errorCount);
  EXPECT_FALSE(unreadyAirLoop.getTarget(openstudio::AirLoopHVACFields::SupplySideOutletNodeNames));
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

TEST_F(EPModelFixture, ZoneHVACPackagedTerminalAirConditioner_ScheduleValidationAndBlankOnlyLoadRepair) {
  const auto idfPath = uniquePtacIdfPath("epmodel-ptac-schedule-repair");
  const ScopedPtacFileRemoval removeIdf(idfPath);

  Model model;
  FanConstantVolume fan(model);
  ZoneHVACPackagedTerminalAirConditioner blank(model);
  ZoneHVACPackagedTerminalAirConditioner unresolved(model);
  ASSERT_TRUE(blank.setName("Blank PTAC Schedules"));
  ASSERT_TRUE(unresolved.setName("Unresolved PTAC Schedules"));
  ASSERT_TRUE(blank.setSupplyAirFan(fan));

  ScheduleConstant availability(model);
  ScheduleConstant fanMode(model);
  ASSERT_TRUE(availability.setValue(1.0));
  ASSERT_TRUE(fanMode.setValue(0.0));
  ASSERT_TRUE(blank.setAvailabilitySchedule(availability));
  ASSERT_TRUE(blank.setSupplyAirFanOperatingModeSchedule(fanMode));
  ASSERT_TRUE(availability.scheduleTypeLimits());
  ASSERT_TRUE(fanMode.scheduleTypeLimits());
  EXPECT_EQ("Availability", availability.scheduleTypeLimits()->unitType());
  EXPECT_EQ("ControlMode", fanMode.scheduleTypeLimits()->unitType());

  ScheduleConstant incompatible(model);
  ScheduleTypeLimits temperatureLimits(model);
  ASSERT_TRUE(temperatureLimits.setLowerLimitValue(0.0));
  ASSERT_TRUE(temperatureLimits.setUpperLimitValue(1.0));
  ASSERT_TRUE(temperatureLimits.setNumericType("Discrete"));
  ASSERT_TRUE(temperatureLimits.setUnitType("Temperature"));
  ASSERT_TRUE(incompatible.setScheduleTypeLimits(temperatureLimits));
  EXPECT_FALSE(blank.setAvailabilitySchedule(incompatible));
  EXPECT_FALSE(blank.setSupplyAirFanOperatingModeSchedule(incompatible));
  EXPECT_EQ(availability.handle(), blank.availabilitySchedule().handle());
  EXPECT_EQ(fanMode.handle(), blank.supplyAirFanOperatingModeSchedule().handle());

  Model foreignModel;
  ScheduleConstant foreignSchedule(foreignModel);
  FanConstantVolume foreignFan(foreignModel);
  EXPECT_FALSE(blank.setAvailabilitySchedule(foreignSchedule));
  EXPECT_FALSE(blank.setSupplyAirFanOperatingModeSchedule(foreignSchedule));
  EXPECT_FALSE(blank.setSupplyAirFan(foreignFan));
  EXPECT_EQ(fan.handle(), blank.supplyAirFan().handle());

  constexpr unsigned availabilityField = openstudio::ZoneHVAC_PackagedTerminalAirConditionerFields::AvailabilityScheduleName;
  constexpr unsigned fanModeField = openstudio::ZoneHVAC_PackagedTerminalAirConditionerFields::SupplyAirFanOperatingModeScheduleName;
  auto blankImpl = blank.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  auto unresolvedImpl = unresolved.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(blankImpl);
  ASSERT_TRUE(unresolvedImpl);
  ASSERT_TRUE(blankImpl->setPointer(availabilityField, openstudio::Handle(), false));
  ASSERT_TRUE(blankImpl->openstudio::detail::IdfObject_Impl::setString(availabilityField, "", false));
  ASSERT_TRUE(blankImpl->setPointer(fanModeField, openstudio::Handle(), false));
  ASSERT_TRUE(blankImpl->openstudio::detail::IdfObject_Impl::setString(fanModeField, "", false));
  ASSERT_TRUE(unresolvedImpl->setPointer(availabilityField, openstudio::Handle(), false));
  ASSERT_TRUE(unresolvedImpl->openstudio::detail::IdfObject_Impl::setString(availabilityField, "Missing PTAC Availability", false));
  ASSERT_TRUE(unresolvedImpl->setPointer(fanModeField, openstudio::Handle(), false));
  ASSERT_TRUE(unresolvedImpl->openstudio::detail::IdfObject_Impl::setString(fanModeField, "Missing PTAC Fan Mode", false));

  const auto report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);
  EXPECT_GE(report.infoCount, 2u);
  EXPECT_EQ(model.alwaysOnDiscreteSchedule().handle(), blank.availabilitySchedule().handle());
  EXPECT_EQ(model.alwaysOnDiscreteSchedule().handle(), blank.supplyAirFanOperatingModeSchedule().handle());
  EXPECT_EQ("Missing PTAC Availability", unresolvedImpl->openstudio::detail::IdfObject_Impl::getString(availabilityField, false, true).value_or(""));
  EXPECT_EQ("Missing PTAC Fan Mode", unresolvedImpl->openstudio::detail::IdfObject_Impl::getString(fanModeField, false, true).value_or(""));

  Model reloadSource;
  FanConstantVolume reloadFan(reloadSource);
  CoilHeatingElectric reloadHeating(reloadSource);
  CoilCoolingDXSingleSpeed reloadCooling(reloadSource);
  ZoneHVACPackagedTerminalAirConditioner blankOnLoad(reloadSource);
  ASSERT_TRUE(blankOnLoad.setName("Blank PTAC Schedules On Load"));
  ASSERT_TRUE(blankOnLoad.setSupplyAirFan(reloadFan));
  ASSERT_TRUE(blankOnLoad.setHeatingCoil(reloadHeating));
  ASSERT_TRUE(blankOnLoad.setCoolingCoil(reloadCooling));
  auto blankOnLoadImpl = blankOnLoad.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(blankOnLoadImpl);
  ASSERT_TRUE(blankOnLoadImpl->setPointer(availabilityField, openstudio::Handle(), false));
  ASSERT_TRUE(blankOnLoadImpl->openstudio::detail::IdfObject_Impl::setString(availabilityField, "", false));
  ASSERT_TRUE(blankOnLoadImpl->setPointer(fanModeField, openstudio::Handle(), false));
  ASSERT_TRUE(blankOnLoadImpl->openstudio::detail::IdfObject_Impl::setString(fanModeField, "", false));
  ASSERT_TRUE(reloadSource.save(idfPath, true));
  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedBlank = loadedModel->getConcreteModelObjectByName<ZoneHVACPackagedTerminalAirConditioner>("Blank PTAC Schedules On Load");
  ASSERT_TRUE(loadedBlank);
  EXPECT_EQ(loadedModel->alwaysOnDiscreteSchedule().handle(), loadedBlank->availabilitySchedule().handle());
  EXPECT_EQ(loadedModel->alwaysOnDiscreteSchedule().handle(), loadedBlank->supplyAirFanOperatingModeSchedule().handle());
}

TEST_F(EPModelFixture, ZoneHVACPackagedTerminalAirConditioner_OwnsPersistedOutdoorAirPath) {
  const auto idfPath = uniquePtacIdfPath("epmodel-ptac-outdoor-air-path");
  const ScopedPtacFileRemoval removeIdf(idfPath);
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
}

TEST_F(EPModelFixture, ZoneHVACPackagedTerminalAirConditioner_ConfiguredRelationshipsSurviveReloadAndPostLoadMutation) {
  const auto firstIdfPath = uniquePtacIdfPath("epmodel-ptac-relationships-first");
  const auto secondIdfPath = uniquePtacIdfPath("epmodel-ptac-relationships-second");
  const ScopedPtacFileRemoval removeFirstIdf(firstIdfPath);
  const ScopedPtacFileRemoval removeSecondIdf(secondIdfPath);

  Model model;
  ScheduleConstant availability(model);
  ScheduleConstant fanMode(model);
  FanConstantVolume fan(model);
  CoilHeatingElectric heatingCoil(model);
  CoilCoolingDXSingleSpeed coolingCoil(model);
  ThermalZone firstZone(model);
  ThermalZone secondZone(model);
  ASSERT_TRUE(availability.setName("PTAC Original Availability"));
  ASSERT_TRUE(fanMode.setName("PTAC Original Fan Mode"));
  ASSERT_TRUE(fan.setName("PTAC Original Fan"));
  ASSERT_TRUE(heatingCoil.setName("PTAC Original Heating Coil"));
  ASSERT_TRUE(coolingCoil.setName("PTAC Original Cooling Coil"));
  ASSERT_TRUE(firstZone.setName("PTAC First Zone"));
  ASSERT_TRUE(secondZone.setName("PTAC Second Zone"));
  ASSERT_TRUE(availability.setValue(0.8));
  ASSERT_TRUE(fanMode.setValue(1.0));

  ZoneHVACPackagedTerminalAirConditioner ptac(model);
  ASSERT_TRUE(ptac.setName("Reloadable PTAC"));
  ASSERT_TRUE(ptac.setAvailabilitySchedule(availability));
  ASSERT_TRUE(ptac.setSupplyAirFanOperatingModeSchedule(fanMode));
  ASSERT_TRUE(ptac.setSupplyAirFan(fan));
  ASSERT_TRUE(ptac.setHeatingCoil(heatingCoil));
  ASSERT_TRUE(ptac.setCoolingCoil(coolingCoil));
  ASSERT_TRUE(ptac.setFanPlacement("DrawThrough"));
  ASSERT_TRUE(ptac.setSupplyAirFlowRateDuringCoolingOperation(0.45));
  ASSERT_TRUE(ptac.setOutdoorAirFlowRateDuringCoolingOperation(0.09));
  ASSERT_TRUE(ptac.setOutdoorAirFlowRateDuringHeatingOperation(0.06));
  ASSERT_TRUE(ptac.setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(0.02));
  ASSERT_TRUE(ptac.addToThermalZone(firstZone));

  EXPECT_FALSE(ptac.setSupplyAirFan(heatingCoil));
  EXPECT_FALSE(ptac.setHeatingCoil(coolingCoil));
  EXPECT_EQ(fan.handle(), ptac.supplyAirFan().handle());
  EXPECT_EQ(heatingCoil.handle(), ptac.heatingCoil().handle());
  ASSERT_TRUE(model.save(firstIdfPath, true));

  auto loadedModel = Model::load(firstIdfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedPtac = loadedModel->getConcreteModelObjectByName<ZoneHVACPackagedTerminalAirConditioner>("Reloadable PTAC");
  auto loadedFirstZone = loadedModel->getConcreteModelObjectByName<ThermalZone>("PTAC First Zone");
  auto loadedSecondZone = loadedModel->getConcreteModelObjectByName<ThermalZone>("PTAC Second Zone");
  auto loadedAvailability = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("PTAC Original Availability");
  auto loadedFanMode = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("PTAC Original Fan Mode");
  auto loadedFan = loadedModel->getConcreteModelObjectByName<FanConstantVolume>("PTAC Original Fan");
  auto loadedHeating = loadedModel->getConcreteModelObjectByName<CoilHeatingElectric>("PTAC Original Heating Coil");
  auto loadedCooling = loadedModel->getConcreteModelObjectByName<CoilCoolingDXSingleSpeed>("PTAC Original Cooling Coil");
  ASSERT_TRUE(loadedPtac);
  ASSERT_TRUE(loadedFirstZone);
  ASSERT_TRUE(loadedSecondZone);
  ASSERT_TRUE(loadedAvailability);
  ASSERT_TRUE(loadedFanMode);
  ASSERT_TRUE(loadedFan);
  ASSERT_TRUE(loadedHeating);
  ASSERT_TRUE(loadedCooling);
  EXPECT_EQ(loadedAvailability->handle(), loadedPtac->availabilitySchedule().handle());
  EXPECT_EQ(loadedFanMode->handle(), loadedPtac->supplyAirFanOperatingModeSchedule().handle());
  EXPECT_EQ(loadedFan->handle(), loadedPtac->supplyAirFan().handle());
  EXPECT_EQ(loadedHeating->handle(), loadedPtac->heatingCoil().handle());
  EXPECT_EQ(loadedCooling->handle(), loadedPtac->coolingCoil().handle());
  ASSERT_TRUE(loadedPtac->thermalZone());
  EXPECT_EQ(*loadedFirstZone, *loadedPtac->thermalZone());
  EXPECT_DOUBLE_EQ(0.45, loadedPtac->supplyAirFlowRateDuringCoolingOperation().get());
  EXPECT_EQ("Fan:ConstantVolume",
            loadedPtac->getString(openstudio::ZoneHVAC_PackagedTerminalAirConditionerFields::SupplyAirFanObjectType).value_or(""));
  EXPECT_EQ("Coil:Heating:Electric",
            loadedPtac->getString(openstudio::ZoneHVAC_PackagedTerminalAirConditionerFields::HeatingCoilObjectType).value_or(""));
  EXPECT_EQ("Coil:Cooling:DX:SingleSpeed",
            loadedPtac->getString(openstudio::ZoneHVAC_PackagedTerminalAirConditionerFields::CoolingCoilObjectType).value_or(""));
  auto loadedMixer =
    loadedPtac->getModelObjectTarget<OutdoorAirMixer>(openstudio::ZoneHVAC_PackagedTerminalAirConditionerFields::OutdoorAirMixerName);
  ASSERT_TRUE(loadedMixer);
  ASSERT_TRUE(loadedMixer->mixedAirNode());
  ASSERT_TRUE(loadedMixer->returnAirNode());
  ASSERT_TRUE(loadedMixer->outdoorAirNode());
  ASSERT_TRUE(loadedPtac->inletNode());
  ASSERT_TRUE(loadedCooling->inletModelObject());
  EXPECT_EQ(loadedCooling->inletModelObject()->handle(), loadedMixer->mixedAirNode()->handle());
  EXPECT_EQ(loadedPtac->inletNode()->handle(), loadedMixer->returnAirNode()->handle());
  EXPECT_EQ(1u, ptacOutdoorAirNodeListEntryCount(*loadedModel, loadedMixer->outdoorAirNode()->nameString()));

  ScheduleConstant replacementAvailability(*loadedModel);
  ScheduleConstant replacementFanMode(*loadedModel);
  FanOnOff replacementFan(*loadedModel);
  CoilHeatingElectric replacementHeating(*loadedModel);
  CoilCoolingDXSingleSpeed replacementCooling(*loadedModel);
  ASSERT_TRUE(replacementAvailability.setName("PTAC Replacement Availability"));
  ASSERT_TRUE(replacementFanMode.setName("PTAC Replacement Fan Mode"));
  ASSERT_TRUE(replacementFan.setName("PTAC Replacement Fan"));
  ASSERT_TRUE(replacementHeating.setName("PTAC Replacement Heating Coil"));
  ASSERT_TRUE(replacementCooling.setName("PTAC Replacement Cooling Coil"));
  ASSERT_TRUE(replacementAvailability.setValue(0.5));
  ASSERT_TRUE(replacementFanMode.setValue(0.0));
  ASSERT_TRUE(loadedPtac->setAvailabilitySchedule(replacementAvailability));
  ASSERT_TRUE(loadedPtac->setSupplyAirFanOperatingModeSchedule(replacementFanMode));
  ASSERT_TRUE(loadedPtac->setSupplyAirFan(replacementFan));
  ASSERT_TRUE(loadedPtac->setHeatingCoil(replacementHeating));
  ASSERT_TRUE(loadedPtac->setCoolingCoil(replacementCooling));
  ASSERT_TRUE(loadedPtac->setFanPlacement("BlowThrough"));
  ASSERT_TRUE(loadedPtac->setOutdoorAirFlowRateDuringCoolingOperation(0.0));
  ASSERT_TRUE(loadedPtac->setOutdoorAirFlowRateDuringHeatingOperation(0.0));
  ASSERT_TRUE(loadedPtac->setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(0.0));
  EXPECT_FALSE(loadedPtac->getModelObjectTarget<OutdoorAirMixer>(openstudio::ZoneHVAC_PackagedTerminalAirConditionerFields::OutdoorAirMixerName));
  ASSERT_TRUE(loadedPtac->setOutdoorAirFlowRateDuringCoolingOperation(0.08));
  ASSERT_TRUE(loadedPtac->setOutdoorAirFlowRateDuringHeatingOperation(0.05));
  ASSERT_TRUE(loadedPtac->setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(0.01));
  ASSERT_TRUE(loadedPtac->addToThermalZone(*loadedSecondZone));
  EXPECT_TRUE(loadedFirstZone->equipment().empty());
  ASSERT_EQ(1u, loadedSecondZone->equipment().size());
  EXPECT_EQ(loadedPtac->handle(), loadedSecondZone->equipment().front().handle());
  ASSERT_TRUE(loadedModel->save(secondIdfPath, true));

  auto reloadedModel = Model::load(secondIdfPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedPtac = reloadedModel->getConcreteModelObjectByName<ZoneHVACPackagedTerminalAirConditioner>("Reloadable PTAC");
  auto reloadedZone = reloadedModel->getConcreteModelObjectByName<ThermalZone>("PTAC Second Zone");
  auto reloadedAvailability = reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("PTAC Replacement Availability");
  auto reloadedFanMode = reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("PTAC Replacement Fan Mode");
  auto reloadedFan = reloadedModel->getConcreteModelObjectByName<FanOnOff>("PTAC Replacement Fan");
  auto reloadedHeating = reloadedModel->getConcreteModelObjectByName<CoilHeatingElectric>("PTAC Replacement Heating Coil");
  auto reloadedCooling = reloadedModel->getConcreteModelObjectByName<CoilCoolingDXSingleSpeed>("PTAC Replacement Cooling Coil");
  ASSERT_TRUE(reloadedPtac);
  ASSERT_TRUE(reloadedZone);
  ASSERT_TRUE(reloadedAvailability);
  ASSERT_TRUE(reloadedFanMode);
  ASSERT_TRUE(reloadedFan);
  ASSERT_TRUE(reloadedHeating);
  ASSERT_TRUE(reloadedCooling);
  EXPECT_EQ("BlowThrough", reloadedPtac->fanPlacement());
  EXPECT_EQ(reloadedAvailability->handle(), reloadedPtac->availabilitySchedule().handle());
  EXPECT_EQ(reloadedFanMode->handle(), reloadedPtac->supplyAirFanOperatingModeSchedule().handle());
  EXPECT_EQ(reloadedFan->handle(), reloadedPtac->supplyAirFan().handle());
  EXPECT_EQ(reloadedHeating->handle(), reloadedPtac->heatingCoil().handle());
  EXPECT_EQ(reloadedCooling->handle(), reloadedPtac->coolingCoil().handle());
  ASSERT_TRUE(reloadedPtac->thermalZone());
  EXPECT_EQ(*reloadedZone, *reloadedPtac->thermalZone());
  auto reloadedMixer =
    reloadedPtac->getModelObjectTarget<OutdoorAirMixer>(openstudio::ZoneHVAC_PackagedTerminalAirConditionerFields::OutdoorAirMixerName);
  ASSERT_TRUE(reloadedMixer);
  ASSERT_TRUE(reloadedMixer->mixedAirNode());
  ASSERT_TRUE(reloadedMixer->returnAirNode());
  ASSERT_TRUE(reloadedMixer->outdoorAirNode());
  ASSERT_TRUE(reloadedPtac->inletNode());
  ASSERT_TRUE(reloadedFan->inletModelObject());
  EXPECT_EQ(reloadedFan->inletModelObject()->handle(), reloadedMixer->mixedAirNode()->handle());
  EXPECT_EQ(reloadedPtac->inletNode()->handle(), reloadedMixer->returnAirNode()->handle());
  EXPECT_EQ(1u, ptacOutdoorAirNodeListEntryCount(*reloadedModel, reloadedMixer->outdoorAirNode()->nameString()));
  ASSERT_TRUE(reloadedPtac->fanOutletNode());
  ASSERT_TRUE(reloadedPtac->coolingCoilOutletNode());
  ASSERT_TRUE(reloadedPtac->heatingCoilOutletNode());
  ASSERT_TRUE(reloadedCooling->inletModelObject());
  ASSERT_TRUE(reloadedHeating->inletModelObject());
  ASSERT_TRUE(reloadedPtac->outletNode());
  EXPECT_EQ(reloadedPtac->fanOutletNode()->handle(), reloadedCooling->inletModelObject()->handle());
  EXPECT_EQ(reloadedPtac->coolingCoilOutletNode()->handle(), reloadedHeating->inletModelObject()->handle());
  EXPECT_EQ(reloadedPtac->heatingCoilOutletNode()->handle(), reloadedPtac->outletNode()->handle());

  const auto availabilityHandle = reloadedAvailability->handle();
  const auto fanModeHandle = reloadedFanMode->handle();
  const auto fanHandle = reloadedFan->handle();
  const auto heatingHandle = reloadedHeating->handle();
  const auto coolingHandle = reloadedCooling->handle();
  const auto outdoorAirNodeName = reloadedMixer->outdoorAirNode()->nameString();
  EXPECT_FALSE(reloadedPtac->remove().empty());
  EXPECT_TRUE(reloadedZone->equipment().empty());
  EXPECT_TRUE(reloadedModel->getObject(availabilityHandle));
  EXPECT_TRUE(reloadedModel->getObject(fanModeHandle));
  EXPECT_FALSE(reloadedModel->getObject(fanHandle));
  EXPECT_FALSE(reloadedModel->getObject(heatingHandle));
  EXPECT_FALSE(reloadedModel->getObject(coolingHandle));
  EXPECT_TRUE(reloadedModel->getConcreteModelObjects<OutdoorAirMixer>().empty());
  EXPECT_EQ(0u, ptacOutdoorAirNodeListEntryCount(*reloadedModel, outdoorAirNodeName));
}
