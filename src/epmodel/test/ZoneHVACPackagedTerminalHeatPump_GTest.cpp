/***********************************************************************************************************************  
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.  
*  See also https://openstudio.net/license  
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ZoneHVACComponent/ZoneHVACPackagedTerminalHeatPump.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../Schedule/ScheduleCompact.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../StraightComponent/Node.hpp"
#include "../StraightComponent/CoilCoolingDXSingleSpeed.hpp"
#include "../StraightComponent/CoilHeatingDXSingleSpeed.hpp"
#include "../StraightComponent/CoilHeatingElectric.hpp"
#include "../StraightComponent/FanOnOff.hpp"
#include "../WaterToAirComponent/CoilHeatingWater.hpp"

#include <utilities/idd/ZoneHVAC_PackagedTerminalHeatPump_FieldEnums.hxx>

using namespace openstudio::epmodel;

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
