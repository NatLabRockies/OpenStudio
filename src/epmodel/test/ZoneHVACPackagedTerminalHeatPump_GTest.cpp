/***********************************************************************************************************************  
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.  
*  See also https://openstudio.net/license  
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ZoneHVACComponent/ZoneHVACPackagedTerminalHeatPump.hpp"
#include "../ZoneHVACComponent/ZoneHVACPackagedTerminalHeatPump_Impl.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../HVACComponent/ThermalZone_Impl.hpp"
#include "../Schedule/ScheduleCompact.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../ResourceObject/ScheduleTypeLimits.hpp"
#include "../StraightComponent/Node.hpp"
#include "../ModelObject/OutdoorAirMixer.hpp"
#include "../ModelObject/OutdoorAirMixer_Impl.hpp"
#include "../StraightComponent/CoilCoolingDXSingleSpeed.hpp"
#include "../StraightComponent/CoilCoolingDXSingleSpeed_Impl.hpp"
#include "../StraightComponent/CoilHeatingDXSingleSpeed.hpp"
#include "../StraightComponent/CoilHeatingDXSingleSpeed_Impl.hpp"
#include "../StraightComponent/CoilHeatingElectric.hpp"
#include "../StraightComponent/CoilHeatingElectric_Impl.hpp"
#include "../StraightComponent/FanConstantVolume.hpp"
#include "../StraightComponent/FanConstantVolume_Impl.hpp"
#include "../StraightComponent/FanOnOff.hpp"
#include "../StraightComponent/FanOnOff_Impl.hpp"
#include "../WaterToAirComponent/CoilHeatingWater.hpp"

#include <utilities/core/Filesystem.hpp>
#include <utilities/core/UUID.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/OutdoorAir_NodeList_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_PackagedTerminalHeatPump_FieldEnums.hxx>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>
#include <utilities/idf/WorkspaceObject_Impl.hpp>

#include <utility>

using namespace openstudio::epmodel;

namespace {
class ScopedPthpFileRemoval
{
 public:
  explicit ScopedPthpFileRemoval(openstudio::path path) : m_path(std::move(path)) {}

  ~ScopedPthpFileRemoval() {
    boost::system::error_code error;
    boost::filesystem::remove(m_path, error);
  }

 private:
  openstudio::path m_path;
};

openstudio::path uniquePthpIdfPath(const std::string& stem) {
  return openstudio::tempDir() / openstudio::toPath(stem + "-" + openstudio::removeBraces(openstudio::createUUID()) + ".idf");
}

unsigned pthpOutdoorAirNodeListEntryCount(const Model& model, const std::string& nodeName) {
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

TEST_F(EPModelFixture, ZoneHVACPackagedTerminalHeatPump_DefaultConstructor) {
  Model model;
  ZoneHVACPackagedTerminalHeatPump pthp(model);

  EXPECT_FALSE(pthp.supplyAirFlowRateDuringCoolingOperation());
  EXPECT_FALSE(pthp.isSupplyAirFlowRateDuringCoolingOperationAutosized());
  EXPECT_FALSE(pthp.supplyAirFlowRateDuringHeatingOperation());
  EXPECT_FALSE(pthp.isSupplyAirFlowRateDuringHeatingOperationAutosized());
  EXPECT_FALSE(pthp.supplyAirFlowRateWhenNoCoolingorHeatingisNeeded());
  EXPECT_FALSE(pthp.isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized());
  EXPECT_FALSE(pthp.noLoadSupplyAirFlowRateControlSetToLowSpeed());
  EXPECT_FALSE(pthp.outdoorAirFlowRateDuringCoolingOperation());
  EXPECT_FALSE(pthp.isOutdoorAirFlowRateDuringCoolingOperationAutosized());
  EXPECT_FALSE(pthp.outdoorAirFlowRateDuringHeatingOperation());
  EXPECT_FALSE(pthp.isOutdoorAirFlowRateDuringHeatingOperationAutosized());
  EXPECT_FALSE(pthp.outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded());
  EXPECT_FALSE(pthp.isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized());
  EXPECT_TRUE(pthp.isHeatingConvergenceToleranceDefaulted());
  EXPECT_TRUE(pthp.isMinimumOutdoorDryBulbTemperatureforCompressorOperationDefaulted());
  EXPECT_TRUE(pthp.isCoolingConvergenceToleranceDefaulted());
  EXPECT_TRUE(pthp.isMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperationDefaulted());
  EXPECT_TRUE(pthp.isFanPlacementDefaulted());
  EXPECT_EQ("", pthp.fanPlacement());
}

TEST_F(EPModelFixture, ZoneHVACPackagedTerminalHeatPump_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneHVACPackagedTerminalHeatPump pthp(model);

  EXPECT_TRUE(pthp.setSupplyAirFlowRateDuringCoolingOperation(0.55));
  ASSERT_TRUE(pthp.supplyAirFlowRateDuringCoolingOperation());
  EXPECT_DOUBLE_EQ(0.55, pthp.supplyAirFlowRateDuringCoolingOperation().get());
  EXPECT_FALSE(pthp.isSupplyAirFlowRateDuringCoolingOperationAutosized());
  pthp.autosizeSupplyAirFlowRateDuringCoolingOperation();
  EXPECT_TRUE(pthp.isSupplyAirFlowRateDuringCoolingOperationAutosized());

  EXPECT_TRUE(pthp.setSupplyAirFlowRateDuringHeatingOperation(0.6));
  ASSERT_TRUE(pthp.supplyAirFlowRateDuringHeatingOperation());
  EXPECT_DOUBLE_EQ(0.6, pthp.supplyAirFlowRateDuringHeatingOperation().get());
  pthp.autosizeSupplyAirFlowRateDuringHeatingOperation();
  EXPECT_TRUE(pthp.isSupplyAirFlowRateDuringHeatingOperationAutosized());

  EXPECT_TRUE(pthp.setSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded(0.15));
  ASSERT_TRUE(pthp.supplyAirFlowRateWhenNoCoolingorHeatingisNeeded());
  EXPECT_DOUBLE_EQ(0.15, pthp.supplyAirFlowRateWhenNoCoolingorHeatingisNeeded().get());
  pthp.resetSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
  EXPECT_FALSE(pthp.supplyAirFlowRateWhenNoCoolingorHeatingisNeeded());
  pthp.autosizeSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
  EXPECT_TRUE(pthp.isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized());

  EXPECT_TRUE(pthp.setNoLoadSupplyAirFlowRateControlSetToLowSpeed(true));
  EXPECT_TRUE(pthp.noLoadSupplyAirFlowRateControlSetToLowSpeed());

  EXPECT_TRUE(pthp.setOutdoorAirFlowRateDuringCoolingOperation(0.2));
  pthp.autosizeOutdoorAirFlowRateDuringCoolingOperation();
  EXPECT_TRUE(pthp.isOutdoorAirFlowRateDuringCoolingOperationAutosized());

  EXPECT_TRUE(pthp.setOutdoorAirFlowRateDuringHeatingOperation(0.18));
  pthp.autosizeOutdoorAirFlowRateDuringHeatingOperation();
  EXPECT_TRUE(pthp.isOutdoorAirFlowRateDuringHeatingOperationAutosized());

  EXPECT_TRUE(pthp.setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(0.05));
  pthp.resetOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
  EXPECT_FALSE(pthp.outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded());
  pthp.autosizeOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
  EXPECT_TRUE(pthp.isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized());

  EXPECT_TRUE(pthp.setHeatingConvergenceTolerance(0.0025));
  EXPECT_DOUBLE_EQ(0.0025, pthp.heatingConvergenceTolerance());
  pthp.resetHeatingConvergenceTolerance();
  EXPECT_TRUE(pthp.isHeatingConvergenceToleranceDefaulted());

  const double legacyMinOdb = pthp.minimumOutdoorDryBulbTemperatureforCompressorOperation();
  EXPECT_FALSE(pthp.setMinimumOutdoorDryBulbTemperatureforCompressorOperation(-18.0));
  EXPECT_DOUBLE_EQ(legacyMinOdb, pthp.minimumOutdoorDryBulbTemperatureforCompressorOperation());
  pthp.resetMinimumOutdoorDryBulbTemperatureforCompressorOperation();
  EXPECT_TRUE(pthp.isMinimumOutdoorDryBulbTemperatureforCompressorOperationDefaulted());

  EXPECT_TRUE(pthp.setCoolingConvergenceTolerance(0.0027));
  EXPECT_DOUBLE_EQ(0.0027, pthp.coolingConvergenceTolerance());
  pthp.resetCoolingConvergenceTolerance();
  EXPECT_TRUE(pthp.isCoolingConvergenceToleranceDefaulted());

  EXPECT_TRUE(pthp.setMaximumSupplyAirTemperaturefromSupplementalHeater(60.0));
  ASSERT_TRUE(pthp.maximumSupplyAirTemperaturefromSupplementalHeater());
  EXPECT_DOUBLE_EQ(60.0, pthp.maximumSupplyAirTemperaturefromSupplementalHeater().get());
  pthp.autosizeMaximumSupplyAirTemperaturefromSupplementalHeater();
  EXPECT_TRUE(pthp.isMaximumSupplyAirTemperaturefromSupplementalHeaterAutosized());

  EXPECT_TRUE(pthp.setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(18.0));
  EXPECT_DOUBLE_EQ(18.0, pthp.maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation());
  pthp.resetMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation();
  EXPECT_TRUE(pthp.isMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperationDefaulted());

  EXPECT_TRUE(pthp.setFanPlacement("BlowThrough"));
  EXPECT_EQ("BlowThrough", pthp.fanPlacement());
  pthp.resetFanPlacement();
  EXPECT_TRUE(pthp.isFanPlacementDefaulted());

  EXPECT_TRUE(pthp.setDXHeatingCoilSizingRatio(1.1));
  EXPECT_DOUBLE_EQ(1.1, pthp.dXHeatingCoilSizingRatio());
}

TEST_F(EPModelFixture, ZoneHVACPackagedTerminalHeatPump_TopologyAndChildren) {
  Model model;
  FanOnOff fan(model);
  CoilHeatingDXSingleSpeed heatingCoil(model);
  CoilCoolingDXSingleSpeed coolingCoil(model);
  CoilHeatingWater supplementalHeatingCoil(model);
  ZoneHVACPackagedTerminalHeatPump pthp(model);

  ASSERT_TRUE(pthp.setOutdoorAirFlowRateDuringCoolingOperation(0.0));
  ASSERT_TRUE(pthp.setOutdoorAirFlowRateDuringHeatingOperation(0.0));
  ASSERT_TRUE(pthp.setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(0.0));
  ASSERT_TRUE(pthp.setFanPlacement("DrawThrough"));
  EXPECT_EQ(openstudio::ZoneHVAC_PackagedTerminalHeatPumpFields::AirInletNodeName, pthp.inletPort());
  EXPECT_EQ(openstudio::ZoneHVAC_PackagedTerminalHeatPumpFields::AirOutletNodeName, pthp.outletPort());

  EXPECT_TRUE(pthp.setSupplyAirFan(fan));
  EXPECT_TRUE(pthp.setHeatingCoil(heatingCoil));
  EXPECT_TRUE(pthp.setCoolingCoil(coolingCoil));
  EXPECT_TRUE(pthp.setSupplementalHeatingCoil(supplementalHeatingCoil));

  EXPECT_EQ(fan, pthp.supplyAirFan());
  EXPECT_EQ(heatingCoil, pthp.heatingCoil());
  EXPECT_EQ(coolingCoil, pthp.coolingCoil());
  EXPECT_EQ(supplementalHeatingCoil, pthp.supplementalHeatingCoil());

  const auto children = pthp.children();
  ASSERT_EQ(4u, children.size());
  EXPECT_EQ(fan, children.at(0));
  EXPECT_EQ(heatingCoil, children.at(1));
  EXPECT_EQ(coolingCoil, children.at(2));
  EXPECT_EQ(supplementalHeatingCoil, children.at(3));

  EXPECT_EQ(pthp, fan.containingZoneHVACComponent().get());
  EXPECT_EQ(pthp, heatingCoil.containingZoneHVACComponent().get());
  EXPECT_EQ(pthp, coolingCoil.containingZoneHVACComponent().get());
  EXPECT_EQ(pthp, supplementalHeatingCoil.containingZoneHVACComponent().get());

  ThermalZone zone(model);
  EXPECT_TRUE(pthp.addToThermalZone(zone));
  ASSERT_TRUE(pthp.inletNode());
  ASSERT_TRUE(pthp.outletNode());
  auto fanInlet = fan.inletModelObject()->optionalCast<Node>();
  auto fanOutlet = fan.outletModelObject()->optionalCast<Node>();
  auto coolingInlet = coolingCoil.inletModelObject()->optionalCast<Node>();
  auto coolingOutlet = coolingCoil.outletModelObject()->optionalCast<Node>();
  auto heatingInlet = heatingCoil.inletModelObject()->optionalCast<Node>();
  auto heatingOutlet = heatingCoil.outletModelObject()->optionalCast<Node>();
  auto supplementalInlet = supplementalHeatingCoil.airInletModelObject()->optionalCast<Node>();
  auto supplementalOutlet = supplementalHeatingCoil.airOutletModelObject()->optionalCast<Node>();
  ASSERT_TRUE(fanInlet);
  ASSERT_TRUE(fanOutlet);
  ASSERT_TRUE(coolingInlet);
  ASSERT_TRUE(coolingOutlet);
  ASSERT_TRUE(heatingInlet);
  ASSERT_TRUE(heatingOutlet);
  ASSERT_TRUE(supplementalInlet);
  ASSERT_TRUE(supplementalOutlet);
  ASSERT_TRUE(pthp.fanOutletNode());
  ASSERT_TRUE(pthp.coolingCoilOutletNode());
  ASSERT_TRUE(pthp.heatingCoilOutletNode());

  EXPECT_EQ(*pthp.inletNode(), *coolingInlet);
  EXPECT_EQ(*pthp.coolingCoilOutletNode(), *coolingOutlet);
  EXPECT_EQ(*pthp.coolingCoilOutletNode(), *heatingInlet);
  EXPECT_EQ(*pthp.heatingCoilOutletNode(), *heatingOutlet);
  EXPECT_EQ(*pthp.heatingCoilOutletNode(), *fanInlet);
  EXPECT_EQ(*pthp.fanOutletNode(), *fanOutlet);
  EXPECT_EQ(*pthp.fanOutletNode(), *supplementalInlet);
  EXPECT_EQ(*pthp.outletNode(), *supplementalOutlet);
  EXPECT_TRUE(pthp.thermalZone());
  pthp.removeFromThermalZone();
  EXPECT_FALSE(pthp.thermalZone());
}

TEST_F(EPModelFixture, ZoneHVACPackagedTerminalHeatPump_ScheduleRelationships_RoundTrip) {
  Model model;
  ZoneHVACPackagedTerminalHeatPump pthp(model);

  auto defaultAvailability = pthp.availabilitySchedule().optionalCast<ScheduleConstant>();
  ASSERT_TRUE(defaultAvailability);
  EXPECT_DOUBLE_EQ(1.0, defaultAvailability->value());
  auto defaultFanMode = pthp.supplyAirFanOperatingModeSchedule().optionalCast<ScheduleConstant>();
  ASSERT_TRUE(defaultFanMode);
  EXPECT_DOUBLE_EQ(1.0, defaultFanMode->value());

  ScheduleCompact availability(model);
  ScheduleCompact fanMode(model);
  ASSERT_TRUE(availability.setToConstantValue(0.6));
  ASSERT_TRUE(fanMode.setToConstantValue(0.0));

  EXPECT_TRUE(pthp.setAvailabilitySchedule(availability));
  EXPECT_TRUE(pthp.setSupplyAirFanOperatingModeSchedule(fanMode));
  EXPECT_EQ(availability.handle(), pthp.availabilitySchedule().handle());
  EXPECT_EQ(fanMode.handle(), pthp.supplyAirFanOperatingModeSchedule().handle());
}

TEST_F(EPModelFixture, ZoneHVACPackagedTerminalHeatPump_NodeRolesFollowBlowThroughOrder) {
  Model model;
  FanOnOff fan(model);
  CoilHeatingDXSingleSpeed heatingCoil(model);
  CoilCoolingDXSingleSpeed coolingCoil(model);
  CoilHeatingWater supplementalHeatingCoil(model);
  ZoneHVACPackagedTerminalHeatPump pthp(model);

  ASSERT_TRUE(pthp.setOutdoorAirFlowRateDuringCoolingOperation(0.0));
  ASSERT_TRUE(pthp.setOutdoorAirFlowRateDuringHeatingOperation(0.0));
  ASSERT_TRUE(pthp.setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(0.0));
  ASSERT_TRUE(pthp.setFanPlacement("BlowThrough"));
  ASSERT_TRUE(pthp.setSupplyAirFan(fan));
  ASSERT_TRUE(pthp.setHeatingCoil(heatingCoil));
  ASSERT_TRUE(pthp.setCoolingCoil(coolingCoil));
  ASSERT_TRUE(pthp.setSupplementalHeatingCoil(supplementalHeatingCoil));

  ASSERT_TRUE(pthp.fanOutletNode());
  ASSERT_TRUE(pthp.coolingCoilOutletNode());
  ASSERT_TRUE(pthp.heatingCoilOutletNode());
  ASSERT_TRUE(pthp.outletNode());

  EXPECT_EQ(*pthp.fanOutletNode(), *coolingCoil.inletModelObject()->optionalCast<Node>());
  EXPECT_EQ(*pthp.coolingCoilOutletNode(), *heatingCoil.inletModelObject()->optionalCast<Node>());
  EXPECT_EQ(*pthp.heatingCoilOutletNode(), *supplementalHeatingCoil.airInletModelObject()->optionalCast<Node>());
  EXPECT_EQ(*pthp.outletNode(), *supplementalHeatingCoil.airOutletModelObject()->optionalCast<Node>());
}

TEST_F(EPModelFixture, ZoneHVACPackagedTerminalHeatPump_InternalNodeRenamesSurviveCanonicalize) {
  Model model;
  FanOnOff fan(model);
  CoilHeatingDXSingleSpeed heatingCoil(model);
  CoilCoolingDXSingleSpeed coolingCoil(model);
  CoilHeatingWater supplementalHeatingCoil(model);
  ZoneHVACPackagedTerminalHeatPump pthp(model);

  ASSERT_TRUE(pthp.setOutdoorAirFlowRateDuringCoolingOperation(0.0));
  ASSERT_TRUE(pthp.setOutdoorAirFlowRateDuringHeatingOperation(0.0));
  ASSERT_TRUE(pthp.setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(0.0));
  ASSERT_TRUE(pthp.setFanPlacement("DrawThrough"));
  ASSERT_TRUE(pthp.setSupplyAirFan(fan));
  ASSERT_TRUE(pthp.setHeatingCoil(heatingCoil));
  ASSERT_TRUE(pthp.setCoolingCoil(coolingCoil));
  ASSERT_TRUE(pthp.setSupplementalHeatingCoil(supplementalHeatingCoil));

  ASSERT_TRUE(pthp.fanOutletNode());
  ASSERT_TRUE(pthp.coolingCoilOutletNode());
  ASSERT_TRUE(pthp.heatingCoilOutletNode());

  ASSERT_TRUE(pthp.fanOutletNode()->setName("Custom PTHP Fan Outlet"));
  ASSERT_TRUE(pthp.coolingCoilOutletNode()->setName("Custom PTHP Cooling Outlet"));
  ASSERT_TRUE(pthp.heatingCoilOutletNode()->setName("Custom PTHP Heating Outlet"));

  auto report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);

  ASSERT_TRUE(pthp.fanOutletNode());
  ASSERT_TRUE(pthp.coolingCoilOutletNode());
  ASSERT_TRUE(pthp.heatingCoilOutletNode());
  EXPECT_EQ("Custom PTHP Fan Outlet", pthp.fanOutletNode()->nameString());
  EXPECT_EQ("Custom PTHP Cooling Outlet", pthp.coolingCoilOutletNode()->nameString());
  EXPECT_EQ("Custom PTHP Heating Outlet", pthp.heatingCoilOutletNode()->nameString());
}

TEST_F(EPModelFixture, ZoneHVACPackagedTerminalHeatPump_ContainedChildTopologyMutationsAreRejected) {
  Model model;
  AirLoopHVAC airLoop(model);
  PlantLoop plantLoop(model);
  FanOnOff fan(model);
  CoilHeatingDXSingleSpeed heatingCoil(model);
  CoilCoolingDXSingleSpeed coolingCoil(model);
  CoilHeatingWater supplementalHeatingCoil(model);
  ZoneHVACPackagedTerminalHeatPump pthp(model);

  ASSERT_TRUE(pthp.setOutdoorAirFlowRateDuringCoolingOperation(0.0));
  ASSERT_TRUE(pthp.setOutdoorAirFlowRateDuringHeatingOperation(0.0));
  ASSERT_TRUE(pthp.setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(0.0));
  ASSERT_TRUE(pthp.setFanPlacement("DrawThrough"));
  ASSERT_TRUE(pthp.setSupplyAirFan(fan));
  ASSERT_TRUE(pthp.setHeatingCoil(heatingCoil));
  ASSERT_TRUE(pthp.setCoolingCoil(coolingCoil));
  ASSERT_TRUE(pthp.setSupplementalHeatingCoil(supplementalHeatingCoil));

  auto originalFanOutlet = pthp.fanOutletNode();
  auto originalCoolingOutlet = pthp.coolingCoilOutletNode();
  auto originalHeatingOutlet = pthp.heatingCoilOutletNode();
  ASSERT_TRUE(originalFanOutlet);
  ASSERT_TRUE(originalCoolingOutlet);
  ASSERT_TRUE(originalHeatingOutlet);

  auto supplyOutletNode = airLoop.supplyOutletNode();
  fan.disconnect();
  EXPECT_FALSE(fan.addToNode(supplyOutletNode));
  EXPECT_FALSE(fan.isRemovable());
  EXPECT_TRUE(fan.remove().empty());

  heatingCoil.disconnect();
  EXPECT_FALSE(heatingCoil.addToNode(supplyOutletNode));
  EXPECT_FALSE(heatingCoil.isRemovable());
  EXPECT_TRUE(heatingCoil.remove().empty());

  coolingCoil.disconnect();
  EXPECT_FALSE(coolingCoil.addToNode(supplyOutletNode));
  EXPECT_FALSE(coolingCoil.isRemovable());
  EXPECT_TRUE(coolingCoil.remove().empty());

  supplementalHeatingCoil.disconnectAirSide();
  EXPECT_FALSE(supplementalHeatingCoil.addToNode(supplyOutletNode));
  EXPECT_FALSE(supplementalHeatingCoil.removeFromAirLoopHVAC());
  EXPECT_FALSE(supplementalHeatingCoil.isRemovable());
  EXPECT_TRUE(supplementalHeatingCoil.remove().empty());
  EXPECT_TRUE(plantLoop.addDemandBranchForComponent(supplementalHeatingCoil));
  ASSERT_TRUE(supplementalHeatingCoil.plantLoop());
  supplementalHeatingCoil.disconnect();
  ASSERT_TRUE(supplementalHeatingCoil.plantLoop());

  ASSERT_TRUE(pthp.fanOutletNode());
  ASSERT_TRUE(pthp.coolingCoilOutletNode());
  ASSERT_TRUE(pthp.heatingCoilOutletNode());
  EXPECT_EQ(*originalFanOutlet, *pthp.fanOutletNode());
  EXPECT_EQ(*originalCoolingOutlet, *pthp.coolingCoilOutletNode());
  EXPECT_EQ(*originalHeatingOutlet, *pthp.heatingCoilOutletNode());
}

TEST_F(EPModelFixture, ZoneHVACPackagedTerminalHeatPump_CanonicalizeRepairsContainedNodePath) {
  Model model;
  FanOnOff fan(model);
  CoilHeatingDXSingleSpeed heatingCoil(model);
  CoilCoolingDXSingleSpeed coolingCoil(model);
  CoilHeatingWater supplementalHeatingCoil(model);
  ZoneHVACPackagedTerminalHeatPump pthp(model);

  ASSERT_TRUE(pthp.setOutdoorAirFlowRateDuringCoolingOperation(0.0));
  ASSERT_TRUE(pthp.setOutdoorAirFlowRateDuringHeatingOperation(0.0));
  ASSERT_TRUE(pthp.setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(0.0));
  ASSERT_TRUE(pthp.setFanPlacement("DrawThrough"));
  ASSERT_TRUE(pthp.setSupplyAirFan(fan));
  ASSERT_TRUE(pthp.setHeatingCoil(heatingCoil));
  ASSERT_TRUE(pthp.setCoolingCoil(coolingCoil));
  ASSERT_TRUE(pthp.setSupplementalHeatingCoil(supplementalHeatingCoil));

  auto expectedCoolingOutlet = pthp.coolingCoilOutletNode();
  auto expectedHeatingOutlet = pthp.heatingCoilOutletNode();
  auto expectedFanOutlet = pthp.fanOutletNode();
  ASSERT_TRUE(expectedCoolingOutlet);
  ASSERT_TRUE(expectedHeatingOutlet);
  ASSERT_TRUE(expectedFanOutlet);

  ASSERT_TRUE(pthp.inletNode());
  ASSERT_TRUE(pthp.outletNode());
  ASSERT_TRUE(coolingCoil.setPointer(coolingCoil.outletPort(), pthp.inletNode()->handle()));
  ASSERT_TRUE(heatingCoil.setPointer(heatingCoil.inletPort(), pthp.inletNode()->handle()));
  ASSERT_TRUE(heatingCoil.setPointer(heatingCoil.outletPort(), pthp.outletNode()->handle()));
  ASSERT_TRUE(fan.setPointer(fan.inletPort(), pthp.outletNode()->handle()));
  ASSERT_TRUE(fan.setPointer(fan.outletPort(), pthp.inletNode()->handle()));
  ASSERT_TRUE(supplementalHeatingCoil.setPointer(supplementalHeatingCoil.airInletPort(), pthp.inletNode()->handle()));

  auto report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);

  ASSERT_TRUE(pthp.coolingCoilOutletNode());
  ASSERT_TRUE(pthp.heatingCoilOutletNode());
  ASSERT_TRUE(pthp.fanOutletNode());
  EXPECT_EQ(*expectedCoolingOutlet, *pthp.coolingCoilOutletNode());
  EXPECT_EQ(*expectedHeatingOutlet, *pthp.heatingCoilOutletNode());
  EXPECT_EQ(*expectedFanOutlet, *pthp.fanOutletNode());
}

TEST_F(EPModelFixture, ZoneHVACPackagedTerminalHeatPump_HiddenMixedAirNodeMaintenanceAndRepairStaySeparate) {
  Model model;
  FanOnOff fan(model);
  CoilHeatingDXSingleSpeed heatingCoil(model);
  CoilCoolingDXSingleSpeed coolingCoil(model);
  CoilHeatingWater supplementalHeatingCoil(model);
  ZoneHVACPackagedTerminalHeatPump pthp(model);

  ASSERT_TRUE(pthp.setOutdoorAirFlowRateDuringCoolingOperation(0.09));
  ASSERT_TRUE(pthp.setOutdoorAirFlowRateDuringHeatingOperation(0.06));
  ASSERT_TRUE(pthp.setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(0.02));
  ASSERT_TRUE(pthp.setFanPlacement("DrawThrough"));
  ASSERT_TRUE(pthp.setSupplyAirFan(fan));
  ASSERT_TRUE(pthp.setHeatingCoil(heatingCoil));
  ASSERT_TRUE(pthp.setCoolingCoil(coolingCoil));
  ASSERT_TRUE(pthp.setSupplementalHeatingCoil(supplementalHeatingCoil));

  auto pthpInlet = pthp.inletNode();
  auto coolingInlet = coolingCoil.inletModelObject()->optionalCast<Node>();
  ASSERT_TRUE(pthpInlet);
  ASSERT_TRUE(coolingInlet);
  EXPECT_NE(*pthpInlet, *coolingInlet);

  Node rogueMaintenanceMixedAir(model);
  ASSERT_TRUE(rogueMaintenanceMixedAir.setName("Rogue PTHP Maintenance Mixed Air"));
  ASSERT_TRUE(coolingCoil.setPointer(coolingCoil.inletPort(), rogueMaintenanceMixedAir.handle()));
  ASSERT_TRUE(pthp.setFanPlacement("DrawThrough"));
  ASSERT_TRUE(coolingCoil.inletModelObject()->optionalCast<Node>());
  EXPECT_NE(rogueMaintenanceMixedAir, *coolingCoil.inletModelObject()->optionalCast<Node>());

  Node rogueRepairMixedAir(model);
  ASSERT_TRUE(rogueRepairMixedAir.setName("Rogue PTHP Repair Mixed Air"));
  ASSERT_TRUE(coolingCoil.setPointer(coolingCoil.inletPort(), rogueRepairMixedAir.handle()));

  auto report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);
  ASSERT_TRUE(coolingCoil.inletModelObject()->optionalCast<Node>());
  EXPECT_EQ(rogueRepairMixedAir, *coolingCoil.inletModelObject()->optionalCast<Node>());
}

TEST_F(EPModelFixture, ZoneHVACPackagedTerminalHeatPump_ScheduleValidationAndBlankOnlyLoadRepair) {
  const auto idfPath = uniquePthpIdfPath("epmodel-pthp-schedule-repair");
  const ScopedPthpFileRemoval removeIdf(idfPath);

  Model model;
  FanOnOff fan(model);
  ZoneHVACPackagedTerminalHeatPump blank(model);
  ZoneHVACPackagedTerminalHeatPump unresolved(model);
  ASSERT_TRUE(blank.setName("Blank PTHP Schedules"));
  ASSERT_TRUE(unresolved.setName("Unresolved PTHP Schedules"));
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
  FanOnOff foreignFan(foreignModel);
  EXPECT_FALSE(blank.setAvailabilitySchedule(foreignSchedule));
  EXPECT_FALSE(blank.setSupplyAirFanOperatingModeSchedule(foreignSchedule));
  EXPECT_FALSE(blank.setSupplyAirFan(foreignFan));
  EXPECT_EQ(fan.handle(), blank.supplyAirFan().handle());

  constexpr unsigned availabilityField = openstudio::ZoneHVAC_PackagedTerminalHeatPumpFields::AvailabilityScheduleName;
  constexpr unsigned fanModeField = openstudio::ZoneHVAC_PackagedTerminalHeatPumpFields::SupplyAirFanOperatingModeScheduleName;
  auto blankImpl = blank.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  auto unresolvedImpl = unresolved.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(blankImpl);
  ASSERT_TRUE(unresolvedImpl);
  ASSERT_TRUE(blankImpl->setPointer(availabilityField, openstudio::Handle(), false));
  ASSERT_TRUE(blankImpl->openstudio::detail::IdfObject_Impl::setString(availabilityField, "", false));
  ASSERT_TRUE(blankImpl->setPointer(fanModeField, openstudio::Handle(), false));
  ASSERT_TRUE(blankImpl->openstudio::detail::IdfObject_Impl::setString(fanModeField, "", false));
  ASSERT_TRUE(unresolvedImpl->setPointer(availabilityField, openstudio::Handle(), false));
  ASSERT_TRUE(unresolvedImpl->openstudio::detail::IdfObject_Impl::setString(availabilityField, "Missing PTHP Availability", false));
  ASSERT_TRUE(unresolvedImpl->setPointer(fanModeField, openstudio::Handle(), false));
  ASSERT_TRUE(unresolvedImpl->openstudio::detail::IdfObject_Impl::setString(fanModeField, "Missing PTHP Fan Mode", false));

  const auto report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);
  EXPECT_GE(report.infoCount, 2u);
  EXPECT_EQ(model.alwaysOnDiscreteSchedule().handle(), blank.availabilitySchedule().handle());
  auto repairedFanMode = blank.supplyAirFanOperatingModeSchedule().optionalCast<ScheduleConstant>();
  ASSERT_TRUE(repairedFanMode);
  EXPECT_DOUBLE_EQ(0.0, repairedFanMode->value());
  EXPECT_EQ("Missing PTHP Availability", unresolvedImpl->openstudio::detail::IdfObject_Impl::getString(availabilityField, false, true).value_or(""));
  EXPECT_EQ("Missing PTHP Fan Mode", unresolvedImpl->openstudio::detail::IdfObject_Impl::getString(fanModeField, false, true).value_or(""));

  Model reloadSource;
  FanOnOff reloadFan(reloadSource);
  CoilHeatingDXSingleSpeed reloadHeating(reloadSource);
  CoilCoolingDXSingleSpeed reloadCooling(reloadSource);
  CoilHeatingElectric reloadSupplemental(reloadSource);
  ZoneHVACPackagedTerminalHeatPump blankOnLoad(reloadSource);
  ASSERT_TRUE(blankOnLoad.setName("Blank PTHP Schedules On Load"));
  ASSERT_TRUE(blankOnLoad.setSupplyAirFan(reloadFan));
  ASSERT_TRUE(blankOnLoad.setHeatingCoil(reloadHeating));
  ASSERT_TRUE(blankOnLoad.setCoolingCoil(reloadCooling));
  ASSERT_TRUE(blankOnLoad.setSupplementalHeatingCoil(reloadSupplemental));
  auto blankOnLoadImpl = blankOnLoad.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(blankOnLoadImpl);
  ASSERT_TRUE(blankOnLoadImpl->setPointer(availabilityField, openstudio::Handle(), false));
  ASSERT_TRUE(blankOnLoadImpl->openstudio::detail::IdfObject_Impl::setString(availabilityField, "", false));
  ASSERT_TRUE(blankOnLoadImpl->setPointer(fanModeField, openstudio::Handle(), false));
  ASSERT_TRUE(blankOnLoadImpl->openstudio::detail::IdfObject_Impl::setString(fanModeField, "", false));
  ASSERT_TRUE(reloadSource.save(idfPath, true));
  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedBlank = loadedModel->getConcreteModelObjectByName<ZoneHVACPackagedTerminalHeatPump>("Blank PTHP Schedules On Load");
  ASSERT_TRUE(loadedBlank);
  EXPECT_EQ(loadedModel->alwaysOnDiscreteSchedule().handle(), loadedBlank->availabilitySchedule().handle());
  auto loadedFanMode = loadedBlank->supplyAirFanOperatingModeSchedule().optionalCast<ScheduleConstant>();
  ASSERT_TRUE(loadedFanMode);
  EXPECT_DOUBLE_EQ(0.0, loadedFanMode->value());
}

TEST_F(EPModelFixture, ZoneHVACPackagedTerminalHeatPump_OutdoorAirPathFollowsFlowAndRemovalLifecycle) {
  Model model;
  FanOnOff fan(model);
  CoilHeatingDXSingleSpeed heatingCoil(model);
  CoilCoolingDXSingleSpeed coolingCoil(model);
  CoilHeatingWater supplementalHeatingCoil(model);
  ZoneHVACPackagedTerminalHeatPump pthp(model);
  ThermalZone zone(model);

  ASSERT_TRUE(pthp.setName("Outdoor Air PTHP"));
  ASSERT_TRUE(pthp.setFanPlacement("BlowThrough"));
  ASSERT_TRUE(pthp.setSupplyAirFan(fan));
  ASSERT_TRUE(pthp.setHeatingCoil(heatingCoil));
  ASSERT_TRUE(pthp.setCoolingCoil(coolingCoil));
  ASSERT_TRUE(pthp.setSupplementalHeatingCoil(supplementalHeatingCoil));
  ASSERT_TRUE(pthp.setOutdoorAirFlowRateDuringCoolingOperation(0.09));
  ASSERT_TRUE(pthp.setOutdoorAirFlowRateDuringHeatingOperation(0.06));
  ASSERT_TRUE(pthp.setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(0.02));
  ASSERT_TRUE(pthp.addToThermalZone(zone));

  auto mixer = pthp.getModelObjectTarget<OutdoorAirMixer>(openstudio::ZoneHVAC_PackagedTerminalHeatPumpFields::OutdoorAirMixerName);
  ASSERT_TRUE(mixer);
  EXPECT_EQ("OutdoorAir:Mixer", pthp.getString(openstudio::ZoneHVAC_PackagedTerminalHeatPumpFields::OutdoorAirMixerObjectType).get());
  ASSERT_TRUE(mixer->mixedAirNode());
  ASSERT_TRUE(mixer->outdoorAirNode());
  ASSERT_TRUE(mixer->reliefAirNode());
  ASSERT_TRUE(mixer->returnAirNode());
  ASSERT_TRUE(pthp.inletNode());
  ASSERT_TRUE(fan.inletModelObject());
  EXPECT_EQ(fan.inletModelObject()->handle(), mixer->mixedAirNode()->handle());
  EXPECT_EQ(pthp.inletNode()->handle(), mixer->returnAirNode()->handle());
  EXPECT_EQ(1u, model.getObjectsByType(openstudio::IddObjectType::OutdoorAir_NodeList).size());
  EXPECT_EQ(5u, pthp.children().size());

  ASSERT_TRUE(pthp.setOutdoorAirFlowRateDuringCoolingOperation(0.0));
  ASSERT_TRUE(pthp.setOutdoorAirFlowRateDuringHeatingOperation(0.0));
  ASSERT_TRUE(pthp.setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(0.0));
  EXPECT_FALSE(pthp.getModelObjectTarget<OutdoorAirMixer>(openstudio::ZoneHVAC_PackagedTerminalHeatPumpFields::OutdoorAirMixerName));
  EXPECT_TRUE(model.getConcreteModelObjects<OutdoorAirMixer>().empty());
  EXPECT_TRUE(model.getObjectsByType(openstudio::IddObjectType::OutdoorAir_NodeList).empty());
  ASSERT_TRUE(pthp.inletNode());
  ASSERT_TRUE(fan.inletModelObject());
  EXPECT_EQ(pthp.inletNode()->handle(), fan.inletModelObject()->handle());

  ASSERT_TRUE(pthp.setOutdoorAirFlowRateDuringCoolingOperation(0.09));
  EXPECT_TRUE(pthp.getModelObjectTarget<OutdoorAirMixer>(openstudio::ZoneHVAC_PackagedTerminalHeatPumpFields::OutdoorAirMixerName));
  EXPECT_EQ(1u, model.getObjectsByType(openstudio::IddObjectType::OutdoorAir_NodeList).size());
  EXPECT_FALSE(pthp.remove().empty());
  EXPECT_TRUE(model.getConcreteModelObjects<OutdoorAirMixer>().empty());
  EXPECT_TRUE(model.getObjectsByType(openstudio::IddObjectType::OutdoorAir_NodeList).empty());
}

TEST_F(EPModelFixture, ZoneHVACPackagedTerminalHeatPump_ConfiguredRelationshipsSurviveReloadAndPostLoadMutation) {
  const auto firstIdfPath = uniquePthpIdfPath("epmodel-pthp-relationships-first");
  const auto secondIdfPath = uniquePthpIdfPath("epmodel-pthp-relationships-second");
  const ScopedPthpFileRemoval removeFirstIdf(firstIdfPath);
  const ScopedPthpFileRemoval removeSecondIdf(secondIdfPath);

  Model model;
  ScheduleConstant availability(model);
  ScheduleConstant fanMode(model);
  FanOnOff fan(model);
  CoilHeatingDXSingleSpeed heatingCoil(model);
  CoilCoolingDXSingleSpeed coolingCoil(model);
  CoilHeatingElectric supplementalCoil(model);
  ThermalZone firstZone(model);
  ThermalZone secondZone(model);
  ASSERT_TRUE(availability.setName("PTHP Original Availability"));
  ASSERT_TRUE(fanMode.setName("PTHP Original Fan Mode"));
  ASSERT_TRUE(fan.setName("PTHP Original Fan"));
  ASSERT_TRUE(heatingCoil.setName("PTHP Original Heating Coil"));
  ASSERT_TRUE(coolingCoil.setName("PTHP Original Cooling Coil"));
  ASSERT_TRUE(supplementalCoil.setName("PTHP Original Supplemental Coil"));
  ASSERT_TRUE(firstZone.setName("PTHP First Zone"));
  ASSERT_TRUE(secondZone.setName("PTHP Second Zone"));
  ASSERT_TRUE(availability.setValue(0.8));
  ASSERT_TRUE(fanMode.setValue(0.0));

  ZoneHVACPackagedTerminalHeatPump pthp(model);
  ASSERT_TRUE(pthp.setName("Reloadable PTHP"));
  ASSERT_TRUE(pthp.setAvailabilitySchedule(availability));
  ASSERT_TRUE(pthp.setSupplyAirFanOperatingModeSchedule(fanMode));
  ASSERT_TRUE(pthp.setSupplyAirFan(fan));
  ASSERT_TRUE(pthp.setHeatingCoil(heatingCoil));
  ASSERT_TRUE(pthp.setCoolingCoil(coolingCoil));
  ASSERT_TRUE(pthp.setSupplementalHeatingCoil(supplementalCoil));
  ASSERT_TRUE(pthp.setFanPlacement("DrawThrough"));
  ASSERT_TRUE(pthp.setSupplyAirFlowRateDuringCoolingOperation(0.45));
  ASSERT_TRUE(pthp.setDXHeatingCoilSizingRatio(1.15));
  ASSERT_TRUE(pthp.setOutdoorAirFlowRateDuringCoolingOperation(0.09));
  ASSERT_TRUE(pthp.setOutdoorAirFlowRateDuringHeatingOperation(0.06));
  ASSERT_TRUE(pthp.setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(0.02));
  ASSERT_TRUE(pthp.addToThermalZone(firstZone));

  EXPECT_FALSE(pthp.setSupplyAirFan(supplementalCoil));
  EXPECT_FALSE(pthp.setHeatingCoil(supplementalCoil));
  EXPECT_FALSE(pthp.setSupplementalHeatingCoil(heatingCoil));
  EXPECT_EQ(fan.handle(), pthp.supplyAirFan().handle());
  EXPECT_EQ(heatingCoil.handle(), pthp.heatingCoil().handle());
  EXPECT_EQ(supplementalCoil.handle(), pthp.supplementalHeatingCoil().handle());
  ASSERT_TRUE(model.save(firstIdfPath, true));

  auto loadedModel = Model::load(firstIdfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedPthp = loadedModel->getConcreteModelObjectByName<ZoneHVACPackagedTerminalHeatPump>("Reloadable PTHP");
  auto loadedFirstZone = loadedModel->getConcreteModelObjectByName<ThermalZone>("PTHP First Zone");
  auto loadedSecondZone = loadedModel->getConcreteModelObjectByName<ThermalZone>("PTHP Second Zone");
  auto loadedAvailability = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("PTHP Original Availability");
  auto loadedFanMode = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("PTHP Original Fan Mode");
  auto loadedFan = loadedModel->getConcreteModelObjectByName<FanOnOff>("PTHP Original Fan");
  auto loadedHeating = loadedModel->getConcreteModelObjectByName<CoilHeatingDXSingleSpeed>("PTHP Original Heating Coil");
  auto loadedCooling = loadedModel->getConcreteModelObjectByName<CoilCoolingDXSingleSpeed>("PTHP Original Cooling Coil");
  auto loadedSupplemental = loadedModel->getConcreteModelObjectByName<CoilHeatingElectric>("PTHP Original Supplemental Coil");
  ASSERT_TRUE(loadedPthp);
  ASSERT_TRUE(loadedFirstZone);
  ASSERT_TRUE(loadedSecondZone);
  ASSERT_TRUE(loadedAvailability);
  ASSERT_TRUE(loadedFanMode);
  ASSERT_TRUE(loadedFan);
  ASSERT_TRUE(loadedHeating);
  ASSERT_TRUE(loadedCooling);
  ASSERT_TRUE(loadedSupplemental);
  EXPECT_EQ(loadedAvailability->handle(), loadedPthp->availabilitySchedule().handle());
  EXPECT_EQ(loadedFanMode->handle(), loadedPthp->supplyAirFanOperatingModeSchedule().handle());
  EXPECT_EQ(loadedFan->handle(), loadedPthp->supplyAirFan().handle());
  EXPECT_EQ(loadedHeating->handle(), loadedPthp->heatingCoil().handle());
  EXPECT_EQ(loadedCooling->handle(), loadedPthp->coolingCoil().handle());
  EXPECT_EQ(loadedSupplemental->handle(), loadedPthp->supplementalHeatingCoil().handle());
  ASSERT_TRUE(loadedPthp->thermalZone());
  EXPECT_EQ(*loadedFirstZone, *loadedPthp->thermalZone());
  EXPECT_DOUBLE_EQ(0.45, loadedPthp->supplyAirFlowRateDuringCoolingOperation().get());
  EXPECT_DOUBLE_EQ(1.15, loadedPthp->dXHeatingCoilSizingRatio());
  EXPECT_EQ("Fan:OnOff", loadedPthp->getString(openstudio::ZoneHVAC_PackagedTerminalHeatPumpFields::SupplyAirFanObjectType).value_or(""));
  EXPECT_EQ("Coil:Heating:DX:SingleSpeed",
            loadedPthp->getString(openstudio::ZoneHVAC_PackagedTerminalHeatPumpFields::HeatingCoilObjectType).value_or(""));
  EXPECT_EQ("Coil:Cooling:DX:SingleSpeed",
            loadedPthp->getString(openstudio::ZoneHVAC_PackagedTerminalHeatPumpFields::CoolingCoilObjectType).value_or(""));
  EXPECT_EQ("Coil:Heating:Electric",
            loadedPthp->getString(openstudio::ZoneHVAC_PackagedTerminalHeatPumpFields::SupplementalHeatingCoilObjectType).value_or(""));
  auto loadedMixer = loadedPthp->getModelObjectTarget<OutdoorAirMixer>(openstudio::ZoneHVAC_PackagedTerminalHeatPumpFields::OutdoorAirMixerName);
  ASSERT_TRUE(loadedMixer);
  ASSERT_TRUE(loadedMixer->mixedAirNode());
  ASSERT_TRUE(loadedMixer->returnAirNode());
  ASSERT_TRUE(loadedMixer->outdoorAirNode());
  ASSERT_TRUE(loadedPthp->inletNode());
  ASSERT_TRUE(loadedCooling->inletModelObject());
  EXPECT_EQ(loadedCooling->inletModelObject()->handle(), loadedMixer->mixedAirNode()->handle());
  EXPECT_EQ(loadedPthp->inletNode()->handle(), loadedMixer->returnAirNode()->handle());
  EXPECT_EQ(1u, pthpOutdoorAirNodeListEntryCount(*loadedModel, loadedMixer->outdoorAirNode()->nameString()));

  ScheduleConstant replacementAvailability(*loadedModel);
  ScheduleConstant replacementFanMode(*loadedModel);
  FanConstantVolume replacementFan(*loadedModel);
  CoilHeatingDXSingleSpeed replacementHeating(*loadedModel);
  CoilCoolingDXSingleSpeed replacementCooling(*loadedModel);
  CoilHeatingElectric replacementSupplemental(*loadedModel);
  ASSERT_TRUE(replacementAvailability.setName("PTHP Replacement Availability"));
  ASSERT_TRUE(replacementFanMode.setName("PTHP Replacement Fan Mode"));
  ASSERT_TRUE(replacementFan.setName("PTHP Replacement Fan"));
  ASSERT_TRUE(replacementHeating.setName("PTHP Replacement Heating Coil"));
  ASSERT_TRUE(replacementCooling.setName("PTHP Replacement Cooling Coil"));
  ASSERT_TRUE(replacementSupplemental.setName("PTHP Replacement Supplemental Coil"));
  ASSERT_TRUE(replacementAvailability.setValue(0.5));
  ASSERT_TRUE(replacementFanMode.setValue(1.0));
  ASSERT_TRUE(loadedPthp->setAvailabilitySchedule(replacementAvailability));
  ASSERT_TRUE(loadedPthp->setSupplyAirFanOperatingModeSchedule(replacementFanMode));
  ASSERT_TRUE(loadedPthp->setSupplyAirFan(replacementFan));
  ASSERT_TRUE(loadedPthp->setHeatingCoil(replacementHeating));
  ASSERT_TRUE(loadedPthp->setCoolingCoil(replacementCooling));
  ASSERT_TRUE(loadedPthp->setSupplementalHeatingCoil(replacementSupplemental));
  ASSERT_TRUE(loadedPthp->setFanPlacement("BlowThrough"));
  ASSERT_TRUE(loadedPthp->setOutdoorAirFlowRateDuringCoolingOperation(0.0));
  ASSERT_TRUE(loadedPthp->setOutdoorAirFlowRateDuringHeatingOperation(0.0));
  ASSERT_TRUE(loadedPthp->setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(0.0));
  EXPECT_FALSE(loadedPthp->getModelObjectTarget<OutdoorAirMixer>(openstudio::ZoneHVAC_PackagedTerminalHeatPumpFields::OutdoorAirMixerName));
  ASSERT_TRUE(loadedPthp->setOutdoorAirFlowRateDuringCoolingOperation(0.08));
  ASSERT_TRUE(loadedPthp->setOutdoorAirFlowRateDuringHeatingOperation(0.05));
  ASSERT_TRUE(loadedPthp->setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(0.01));
  ASSERT_TRUE(loadedPthp->addToThermalZone(*loadedSecondZone));
  EXPECT_TRUE(loadedFirstZone->equipment().empty());
  ASSERT_EQ(1u, loadedSecondZone->equipment().size());
  EXPECT_EQ(loadedPthp->handle(), loadedSecondZone->equipment().front().handle());
  ASSERT_TRUE(loadedModel->save(secondIdfPath, true));

  auto reloadedModel = Model::load(secondIdfPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedPthp = reloadedModel->getConcreteModelObjectByName<ZoneHVACPackagedTerminalHeatPump>("Reloadable PTHP");
  auto reloadedZone = reloadedModel->getConcreteModelObjectByName<ThermalZone>("PTHP Second Zone");
  auto reloadedAvailability = reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("PTHP Replacement Availability");
  auto reloadedFanMode = reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("PTHP Replacement Fan Mode");
  auto reloadedFan = reloadedModel->getConcreteModelObjectByName<FanConstantVolume>("PTHP Replacement Fan");
  auto reloadedHeating = reloadedModel->getConcreteModelObjectByName<CoilHeatingDXSingleSpeed>("PTHP Replacement Heating Coil");
  auto reloadedCooling = reloadedModel->getConcreteModelObjectByName<CoilCoolingDXSingleSpeed>("PTHP Replacement Cooling Coil");
  auto reloadedSupplemental = reloadedModel->getConcreteModelObjectByName<CoilHeatingElectric>("PTHP Replacement Supplemental Coil");
  ASSERT_TRUE(reloadedPthp);
  ASSERT_TRUE(reloadedZone);
  ASSERT_TRUE(reloadedAvailability);
  ASSERT_TRUE(reloadedFanMode);
  ASSERT_TRUE(reloadedFan);
  ASSERT_TRUE(reloadedHeating);
  ASSERT_TRUE(reloadedCooling);
  ASSERT_TRUE(reloadedSupplemental);
  EXPECT_EQ("BlowThrough", reloadedPthp->fanPlacement());
  EXPECT_EQ(reloadedAvailability->handle(), reloadedPthp->availabilitySchedule().handle());
  EXPECT_EQ(reloadedFanMode->handle(), reloadedPthp->supplyAirFanOperatingModeSchedule().handle());
  EXPECT_EQ(reloadedFan->handle(), reloadedPthp->supplyAirFan().handle());
  EXPECT_EQ(reloadedHeating->handle(), reloadedPthp->heatingCoil().handle());
  EXPECT_EQ(reloadedCooling->handle(), reloadedPthp->coolingCoil().handle());
  EXPECT_EQ(reloadedSupplemental->handle(), reloadedPthp->supplementalHeatingCoil().handle());
  ASSERT_TRUE(reloadedPthp->thermalZone());
  EXPECT_EQ(*reloadedZone, *reloadedPthp->thermalZone());
  auto reloadedMixer = reloadedPthp->getModelObjectTarget<OutdoorAirMixer>(openstudio::ZoneHVAC_PackagedTerminalHeatPumpFields::OutdoorAirMixerName);
  ASSERT_TRUE(reloadedMixer);
  ASSERT_TRUE(reloadedMixer->mixedAirNode());
  ASSERT_TRUE(reloadedMixer->returnAirNode());
  ASSERT_TRUE(reloadedMixer->outdoorAirNode());
  ASSERT_TRUE(reloadedPthp->inletNode());
  ASSERT_TRUE(reloadedFan->inletModelObject());
  EXPECT_EQ(reloadedFan->inletModelObject()->handle(), reloadedMixer->mixedAirNode()->handle());
  EXPECT_EQ(reloadedPthp->inletNode()->handle(), reloadedMixer->returnAirNode()->handle());
  EXPECT_EQ(1u, pthpOutdoorAirNodeListEntryCount(*reloadedModel, reloadedMixer->outdoorAirNode()->nameString()));
  ASSERT_TRUE(reloadedPthp->fanOutletNode());
  ASSERT_TRUE(reloadedPthp->coolingCoilOutletNode());
  ASSERT_TRUE(reloadedPthp->heatingCoilOutletNode());
  ASSERT_TRUE(reloadedCooling->inletModelObject());
  ASSERT_TRUE(reloadedHeating->inletModelObject());
  ASSERT_TRUE(reloadedSupplemental->inletModelObject());
  ASSERT_TRUE(reloadedSupplemental->outletModelObject());
  ASSERT_TRUE(reloadedPthp->outletNode());
  EXPECT_EQ(reloadedPthp->fanOutletNode()->handle(), reloadedCooling->inletModelObject()->handle());
  EXPECT_EQ(reloadedPthp->coolingCoilOutletNode()->handle(), reloadedHeating->inletModelObject()->handle());
  EXPECT_EQ(reloadedPthp->heatingCoilOutletNode()->handle(), reloadedSupplemental->inletModelObject()->handle());
  EXPECT_EQ(reloadedSupplemental->outletModelObject()->handle(), reloadedPthp->outletNode()->handle());

  const auto availabilityHandle = reloadedAvailability->handle();
  const auto fanModeHandle = reloadedFanMode->handle();
  const auto fanHandle = reloadedFan->handle();
  const auto heatingHandle = reloadedHeating->handle();
  const auto coolingHandle = reloadedCooling->handle();
  const auto supplementalHandle = reloadedSupplemental->handle();
  const auto outdoorAirNodeName = reloadedMixer->outdoorAirNode()->nameString();
  EXPECT_FALSE(reloadedPthp->remove().empty());
  EXPECT_TRUE(reloadedZone->equipment().empty());
  EXPECT_TRUE(reloadedModel->getObject(availabilityHandle));
  EXPECT_TRUE(reloadedModel->getObject(fanModeHandle));
  EXPECT_TRUE(reloadedModel->getObject(fanHandle));
  EXPECT_TRUE(reloadedModel->getObject(heatingHandle));
  EXPECT_TRUE(reloadedModel->getObject(coolingHandle));
  EXPECT_TRUE(reloadedModel->getObject(supplementalHandle));
  EXPECT_TRUE(reloadedModel->getConcreteModelObjects<OutdoorAirMixer>().empty());
  EXPECT_EQ(0u, pthpOutdoorAirNodeListEntryCount(*reloadedModel, outdoorAirNodeName));
}
