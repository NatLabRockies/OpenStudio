/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../HVACComponent/ThermalZone_Impl.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../Schedule/ScheduleCompact.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../StraightComponent/AirTerminalSingleDuctInletSideMixer.hpp"
#include "../StraightComponent/AirTerminalSingleDuctInletSideMixer_Impl.hpp"
#include "../StraightComponent/FanConstantVolume.hpp"
#include "../StraightComponent/FanConstantVolume_Impl.hpp"
#include "../StraightComponent/Node.hpp"
#include "../WaterToAirComponent/CoilCoolingWater.hpp"
#include "../WaterToAirComponent/CoilCoolingWater_Impl.hpp"
#include "../WaterToAirComponent/CoilHeatingWater.hpp"
#include "../WaterToAirComponent/CoilHeatingWater_Impl.hpp"
#include "../ZoneHVACComponent/ZoneHVACFourPipeFanCoil.hpp"
#include "../ZoneHVACComponent/ZoneHVACFourPipeFanCoil_Impl.hpp"
#include <utilities/idd/ZoneHVAC_FourPipeFanCoil_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, API_ZoneHVACFourPipeFanCoil_DefaultConstructor) {
  Model model;
  ZoneHVACFourPipeFanCoil coil(model);
  EXPECT_EQ(ZoneHVACFourPipeFanCoil::iddObjectType(), coil.iddObject().type());
  EXPECT_FALSE(coil.nameString().empty());
}

TEST_F(EPModelFixture, ZoneHVACFourPipeFanCoil_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneHVACFourPipeFanCoil coil(model);

  const auto capacityMethods = ZoneHVACFourPipeFanCoil::capacityControlMethodValues();
  ASSERT_FALSE(capacityMethods.empty());
  EXPECT_TRUE(coil.setCapacityControlMethod(capacityMethods.front()));
  EXPECT_EQ(capacityMethods.front(), coil.capacityControlMethod());

  EXPECT_TRUE(coil.setMaximumSupplyAirFlowRate(1.2));
  ASSERT_TRUE(coil.maximumSupplyAirFlowRate());
  EXPECT_DOUBLE_EQ(1.2, coil.maximumSupplyAirFlowRate().get());
  coil.autosizeMaximumSupplyAirFlowRate();
  EXPECT_TRUE(coil.isMaximumSupplyAirFlowRateAutosized());

  EXPECT_TRUE(coil.setLowSpeedSupplyAirFlowRatio(0.35));
  EXPECT_DOUBLE_EQ(0.35, coil.lowSpeedSupplyAirFlowRatio());
  coil.resetLowSpeedSupplyAirFlowRatio();
  EXPECT_TRUE(coil.isLowSpeedSupplyAirFlowRatioDefaulted());

  EXPECT_TRUE(coil.setMediumSpeedSupplyAirFlowRatio(0.6));
  EXPECT_DOUBLE_EQ(0.6, coil.mediumSpeedSupplyAirFlowRatio());
  coil.resetMediumSpeedSupplyAirFlowRatio();
  EXPECT_TRUE(coil.isMediumSpeedSupplyAirFlowRatioDefaulted());

  EXPECT_TRUE(coil.setMaximumOutdoorAirFlowRate(0.45));
  coil.autosizeMaximumOutdoorAirFlowRate();
  EXPECT_TRUE(coil.isMaximumOutdoorAirFlowRateAutosized());

  const auto mixerTypes = ZoneHVACFourPipeFanCoil::outdoorAirMixerObjectTypeValues();
  ASSERT_FALSE(mixerTypes.empty());
  EXPECT_TRUE(coil.setOutdoorAirMixerObjectType(mixerTypes.front()));
  EXPECT_EQ(mixerTypes.front(), coil.outdoorAirMixerObjectType());

  EXPECT_TRUE(coil.setMaximumColdWaterFlowRate(0.18));
  coil.autosizeMaximumColdWaterFlowRate();
  EXPECT_TRUE(coil.isMaximumColdWaterFlowRateAutosized());

  EXPECT_TRUE(coil.setMinimumColdWaterFlowRate(0.08));
  EXPECT_DOUBLE_EQ(0.08, coil.minimumColdWaterFlowRate());
  coil.resetMinimumColdWaterFlowRate();
  EXPECT_TRUE(coil.isMinimumColdWaterFlowRateDefaulted());

  EXPECT_TRUE(coil.setCoolingConvergenceTolerance(0.007));
  EXPECT_DOUBLE_EQ(0.007, coil.coolingConvergenceTolerance());
  coil.resetCoolingConvergenceTolerance();
  EXPECT_TRUE(coil.isCoolingConvergenceToleranceDefaulted());

  EXPECT_TRUE(coil.setMaximumHotWaterFlowRate(0.25));
  coil.autosizeMaximumHotWaterFlowRate();
  EXPECT_TRUE(coil.isMaximumHotWaterFlowRateAutosized());

  EXPECT_TRUE(coil.setMinimumHotWaterFlowRate(0.12));
  EXPECT_DOUBLE_EQ(0.12, coil.minimumHotWaterFlowRate());
  coil.resetMinimumHotWaterFlowRate();
  EXPECT_TRUE(coil.isMinimumHotWaterFlowRateDefaulted());

  EXPECT_TRUE(coil.setHeatingConvergenceTolerance(0.003));
  EXPECT_DOUBLE_EQ(0.003, coil.heatingConvergenceTolerance());
  coil.resetHeatingConvergenceTolerance();
  EXPECT_TRUE(coil.isHeatingConvergenceToleranceDefaulted());

  coil.autosizeMinimumSupplyAirTemperatureInCoolingMode();
  EXPECT_TRUE(coil.isMinimumSupplyAirTemperatureInCoolingModeAutosized());

  coil.autosizeMaximumSupplyAirTemperatureInHeatingMode();
  EXPECT_TRUE(coil.isMaximumSupplyAirTemperatureInHeatingModeAutosized());
}

TEST_F(EPModelFixture, ZoneHVACFourPipeFanCoil_ChildrenAndZoneTopology) {
  Model model;
  FanConstantVolume fan(model);
  CoilCoolingWater coolingCoil(model);
  CoilHeatingWater heatingCoil(model);
  ZoneHVACFourPipeFanCoil coil(model);
  ThermalZone zone(model);

  ASSERT_TRUE(coil.setCapacityControlMethod("ConstantFanVariableFlow"));
  ASSERT_TRUE(coil.setSupplyAirFan(fan));
  ASSERT_TRUE(coil.setCoolingCoil(coolingCoil));
  ASSERT_TRUE(coil.setHeatingCoil(heatingCoil));

  ASSERT_TRUE(coil.inletNode());
  ASSERT_TRUE(coil.outletNode());
  ASSERT_TRUE(coil.fanOutletNode());
  ASSERT_TRUE(coil.coolingCoilOutletNode());

  const auto children = coil.children();
  ASSERT_EQ(3u, children.size());
  EXPECT_EQ(fan, children[0]);
  EXPECT_EQ(coolingCoil, children[1]);
  EXPECT_EQ(heatingCoil, children[2]);

  ASSERT_TRUE(fan.containingHVACComponent());
  ASSERT_TRUE(coolingCoil.containingHVACComponent());
  ASSERT_TRUE(heatingCoil.containingHVACComponent());
  EXPECT_EQ(coil, fan.containingHVACComponent().get());
  EXPECT_EQ(coil, coolingCoil.containingHVACComponent().get());
  EXPECT_EQ(coil, heatingCoil.containingHVACComponent().get());

  ASSERT_TRUE(coil.addToThermalZone(zone));
  ASSERT_TRUE(coil.thermalZone());
  EXPECT_EQ(zone, coil.thermalZone().get());

  coil.removeFromThermalZone();
  EXPECT_FALSE(coil.thermalZone());
  EXPECT_TRUE(coil.inletNode());
  EXPECT_TRUE(coil.outletNode());
  EXPECT_TRUE(coil.fanOutletNode());
  EXPECT_TRUE(coil.coolingCoilOutletNode());
}

TEST_F(EPModelFixture, ZoneHVACFourPipeFanCoil_InletSideMixerAttachmentRewiresContainedAirPath) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  AirTerminalSingleDuctInletSideMixer terminal(model);
  FanConstantVolume fan(model);
  CoilCoolingWater coolingCoil(model);
  CoilHeatingWater heatingCoil(model);
  ZoneHVACFourPipeFanCoil fanCoil(model);
  ASSERT_TRUE(fanCoil.setCapacityControlMethod("ConstantFanVariableFlow"));
  ASSERT_TRUE(fanCoil.setSupplyAirFan(fan));
  ASSERT_TRUE(fanCoil.setCoolingCoil(coolingCoil));
  ASSERT_TRUE(fanCoil.setHeatingCoil(heatingCoil));
  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  auto terminalOutlet = terminal.outletModelObject();
  ASSERT_TRUE(terminalOutlet);
  auto terminalOutletNode = terminalOutlet->optionalCast<Node>();
  ASSERT_TRUE(terminalOutletNode);

  ASSERT_TRUE(fanCoil.addToNode(*terminalOutletNode));
  ASSERT_TRUE(fanCoil.inletNode());
  ASSERT_TRUE(fanCoil.outletNode());
  ASSERT_TRUE(fan.inletModelObject());
  ASSERT_TRUE(fan.outletModelObject());
  ASSERT_TRUE(coolingCoil.airInletModelObject());
  ASSERT_TRUE(coolingCoil.airOutletModelObject());
  ASSERT_TRUE(heatingCoil.airInletModelObject());
  ASSERT_TRUE(heatingCoil.airOutletModelObject());

  EXPECT_EQ(fanCoil.inletNode()->cast<ModelObject>(), fan.inletModelObject().get());
  EXPECT_EQ(fan.outletModelObject().get(), coolingCoil.airInletModelObject().get());
  EXPECT_EQ(coolingCoil.airOutletModelObject().get(), heatingCoil.airInletModelObject().get());
  EXPECT_EQ(fanCoil.outletNode()->cast<ModelObject>(), heatingCoil.airOutletModelObject().get());
  ASSERT_TRUE(terminal.secondaryAirInletNode());
  ASSERT_TRUE(fanCoil.thermalZone());
  EXPECT_EQ(zone, fanCoil.thermalZone().get());
}

TEST_F(EPModelFixture, ZoneHVACFourPipeFanCoil_InletSideMixerAttachmentSurvivesReload) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-inlet-side-mixer-fan-coil-path.idf");
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  AirTerminalSingleDuctInletSideMixer terminal(model);
  FanConstantVolume fan(model);
  CoilCoolingWater coolingCoil(model);
  CoilHeatingWater heatingCoil(model);
  ZoneHVACFourPipeFanCoil fanCoil(model);
  ASSERT_TRUE(fanCoil.setCapacityControlMethod("ConstantFanVariableFlow"));
  ASSERT_TRUE(fanCoil.setSupplyAirFan(fan));
  ASSERT_TRUE(fanCoil.setCoolingCoil(coolingCoil));
  ASSERT_TRUE(fanCoil.setHeatingCoil(heatingCoil));
  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  auto terminalOutlet = terminal.outletModelObject();
  ASSERT_TRUE(terminalOutlet);
  auto terminalOutletNode = terminalOutlet->optionalCast<Node>();
  ASSERT_TRUE(terminalOutletNode);
  ASSERT_TRUE(fanCoil.addToNode(*terminalOutletNode));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  const auto loadedTerminals = loadedModel->getConcreteModelObjects<AirTerminalSingleDuctInletSideMixer>();
  const auto loadedFanCoils = loadedModel->getConcreteModelObjects<ZoneHVACFourPipeFanCoil>();
  const auto loadedZones = loadedModel->getConcreteModelObjects<ThermalZone>();
  ASSERT_EQ(1u, loadedTerminals.size());
  ASSERT_EQ(1u, loadedFanCoils.size());
  ASSERT_EQ(1u, loadedZones.size());
  const auto loadedTerminal = loadedTerminals.front();
  const auto loadedFanCoil = loadedFanCoils.front();
  const auto loadedFan = loadedFanCoil.supplyAirFan().optionalCast<FanConstantVolume>();
  const auto loadedCoolingCoil = loadedFanCoil.coolingCoil().optionalCast<CoilCoolingWater>();
  const auto loadedHeatingCoil = loadedFanCoil.heatingCoil().optionalCast<CoilHeatingWater>();
  ASSERT_TRUE(loadedFan);
  ASSERT_TRUE(loadedCoolingCoil);
  ASSERT_TRUE(loadedHeatingCoil);
  ASSERT_TRUE(loadedTerminal.outletModelObject());
  ASSERT_TRUE(loadedFanCoil.inletNode());
  ASSERT_TRUE(loadedFanCoil.outletNode());
  ASSERT_TRUE(loadedFan->inletModelObject());
  ASSERT_TRUE(loadedFan->outletModelObject());
  ASSERT_TRUE(loadedCoolingCoil->airInletModelObject());
  ASSERT_TRUE(loadedCoolingCoil->airOutletModelObject());
  ASSERT_TRUE(loadedHeatingCoil->airInletModelObject());
  ASSERT_TRUE(loadedHeatingCoil->airOutletModelObject());

  EXPECT_EQ(loadedTerminal.outletModelObject().get(), loadedFanCoil.inletNode()->cast<ModelObject>());
  EXPECT_EQ(loadedFanCoil.inletNode()->cast<ModelObject>(), loadedFan->inletModelObject().get());
  EXPECT_EQ(loadedFan->outletModelObject().get(), loadedCoolingCoil->airInletModelObject().get());
  EXPECT_EQ(loadedCoolingCoil->airOutletModelObject().get(), loadedHeatingCoil->airInletModelObject().get());
  EXPECT_EQ(loadedFanCoil.outletNode()->cast<ModelObject>(), loadedHeatingCoil->airOutletModelObject().get());
  ASSERT_TRUE(loadedTerminal.secondaryAirInletNode());
  ASSERT_TRUE(loadedFanCoil.thermalZone());
  EXPECT_EQ(loadedZones.front(), loadedFanCoil.thermalZone().get());
}

TEST_F(EPModelFixture, ZoneHVACFourPipeFanCoil_RejectsAndRepairsSharedChildren) {
  Model model;
  ZoneHVACFourPipeFanCoil first(model);
  ZoneHVACFourPipeFanCoil second(model);
  FanConstantVolume firstFan(model);
  FanConstantVolume secondFan(model);
  CoilCoolingWater firstCoolingCoil(model);
  CoilCoolingWater secondCoolingCoil(model);
  CoilHeatingWater firstHeatingCoil(model);
  CoilHeatingWater secondHeatingCoil(model);

  ASSERT_TRUE(first.setCapacityControlMethod("ConstantFanVariableFlow"));
  ASSERT_TRUE(second.setCapacityControlMethod("ConstantFanVariableFlow"));
  ASSERT_TRUE(first.setSupplyAirFan(firstFan));
  ASSERT_TRUE(first.setCoolingCoil(firstCoolingCoil));
  ASSERT_TRUE(first.setHeatingCoil(firstHeatingCoil));
  ASSERT_TRUE(second.setSupplyAirFan(secondFan));
  ASSERT_TRUE(second.setCoolingCoil(secondCoolingCoil));
  ASSERT_TRUE(second.setHeatingCoil(secondHeatingCoil));

  EXPECT_FALSE(second.setSupplyAirFan(firstFan));
  EXPECT_FALSE(second.setCoolingCoil(firstCoolingCoil));
  EXPECT_FALSE(second.setHeatingCoil(firstHeatingCoil));
  EXPECT_EQ(secondFan, second.supplyAirFan());
  EXPECT_EQ(secondCoolingCoil, second.coolingCoil());
  EXPECT_EQ(secondHeatingCoil, second.heatingCoil());

  auto secondImpl = second.getImpl<detail::ZoneHVACFourPipeFanCoil_Impl>();
  ASSERT_TRUE(secondImpl);
  ASSERT_TRUE(secondImpl->setPointer(openstudio::ZoneHVAC_FourPipeFanCoilFields::SupplyAirFanName, firstFan.handle(), false));
  ASSERT_TRUE(secondImpl->setPointer(openstudio::ZoneHVAC_FourPipeFanCoilFields::CoolingCoilName, firstCoolingCoil.handle(), false));
  ASSERT_TRUE(secondImpl->setPointer(openstudio::ZoneHVAC_FourPipeFanCoilFields::HeatingCoilName, firstHeatingCoil.handle(), false));
  const auto expectedOwner = firstFan.containingHVACComponent();
  ASSERT_TRUE(expectedOwner);
  ASSERT_TRUE(firstCoolingCoil.containingHVACComponent());
  ASSERT_TRUE(firstHeatingCoil.containingHVACComponent());
  ASSERT_EQ(expectedOwner->handle(), firstCoolingCoil.containingHVACComponent()->handle());
  ASSERT_EQ(expectedOwner->handle(), firstHeatingCoil.containingHVACComponent()->handle());
  model.canonicalize();

  const auto otherFanCoil = expectedOwner->handle() == first.handle() ? second : first;
  EXPECT_FALSE(otherFanCoil.getTarget(openstudio::ZoneHVAC_FourPipeFanCoilFields::SupplyAirFanName));
  EXPECT_FALSE(otherFanCoil.getTarget(openstudio::ZoneHVAC_FourPipeFanCoilFields::CoolingCoilName));
  EXPECT_FALSE(otherFanCoil.getTarget(openstudio::ZoneHVAC_FourPipeFanCoilFields::HeatingCoilName));
  ASSERT_TRUE(firstFan.containingHVACComponent());
  ASSERT_TRUE(firstCoolingCoil.containingHVACComponent());
  ASSERT_TRUE(firstHeatingCoil.containingHVACComponent());
  EXPECT_EQ(expectedOwner->handle(), firstFan.containingHVACComponent()->handle());
  EXPECT_EQ(expectedOwner->handle(), firstCoolingCoil.containingHVACComponent()->handle());
  EXPECT_EQ(expectedOwner->handle(), firstHeatingCoil.containingHVACComponent()->handle());
}

TEST_F(EPModelFixture, ZoneHVACFourPipeFanCoil_RejectsAirLoopChildrenWithoutRewiringThem) {
  Model model;
  AirLoopHVAC airLoop(model);
  FanConstantVolume fan(model);
  CoilCoolingWater coolingCoil(model);
  CoilHeatingWater heatingCoil(model);
  ZoneHVACFourPipeFanCoil fanCoil(model);
  ASSERT_TRUE(fanCoil.setCapacityControlMethod("ConstantFanVariableFlow"));
  auto supplyInletNode = airLoop.supplyInletNode();
  auto supplyOutletNode = airLoop.supplyOutletNode();
  ASSERT_TRUE(fan.addToNode(supplyInletNode));
  ASSERT_TRUE(coolingCoil.addToNode(supplyOutletNode));
  ASSERT_TRUE(heatingCoil.addToNode(supplyOutletNode));
  const auto fanInlet = fan.inletModelObject();
  const auto fanOutlet = fan.outletModelObject();
  const auto coolingInlet = coolingCoil.airInletModelObject();
  const auto coolingOutlet = coolingCoil.airOutletModelObject();
  const auto heatingInlet = heatingCoil.airInletModelObject();
  const auto heatingOutlet = heatingCoil.airOutletModelObject();
  ASSERT_TRUE(fanInlet);
  ASSERT_TRUE(fanOutlet);
  ASSERT_TRUE(coolingInlet);
  ASSERT_TRUE(coolingOutlet);
  ASSERT_TRUE(heatingInlet);
  ASSERT_TRUE(heatingOutlet);

  EXPECT_FALSE(fanCoil.setSupplyAirFan(fan));
  EXPECT_FALSE(fanCoil.setCoolingCoil(coolingCoil));
  EXPECT_FALSE(fanCoil.setHeatingCoil(heatingCoil));
  EXPECT_EQ(fanInlet.get(), fan.inletModelObject().get());
  EXPECT_EQ(fanOutlet.get(), fan.outletModelObject().get());
  EXPECT_EQ(coolingInlet.get(), coolingCoil.airInletModelObject().get());
  EXPECT_EQ(coolingOutlet.get(), coolingCoil.airOutletModelObject().get());
  EXPECT_EQ(heatingInlet.get(), heatingCoil.airInletModelObject().get());
  EXPECT_EQ(heatingOutlet.get(), heatingCoil.airOutletModelObject().get());

  auto fanCoilImpl = fanCoil.getImpl<detail::ZoneHVACFourPipeFanCoil_Impl>();
  ASSERT_TRUE(fanCoilImpl);
  ASSERT_TRUE(fanCoilImpl->setPointer(openstudio::ZoneHVAC_FourPipeFanCoilFields::SupplyAirFanName, fan.handle(), false));
  ASSERT_TRUE(fanCoilImpl->setPointer(openstudio::ZoneHVAC_FourPipeFanCoilFields::CoolingCoilName, coolingCoil.handle(), false));
  ASSERT_TRUE(fanCoilImpl->setPointer(openstudio::ZoneHVAC_FourPipeFanCoilFields::HeatingCoilName, heatingCoil.handle(), false));
  model.canonicalize();

  EXPECT_FALSE(fanCoil.getTarget(openstudio::ZoneHVAC_FourPipeFanCoilFields::SupplyAirFanName));
  EXPECT_FALSE(fanCoil.getTarget(openstudio::ZoneHVAC_FourPipeFanCoilFields::CoolingCoilName));
  EXPECT_FALSE(fanCoil.getTarget(openstudio::ZoneHVAC_FourPipeFanCoilFields::HeatingCoilName));
  EXPECT_TRUE(airLoop.component(fan.handle()));
  EXPECT_TRUE(airLoop.component(coolingCoil.handle()));
  EXPECT_TRUE(airLoop.component(heatingCoil.handle()));
  EXPECT_EQ(fanInlet.get(), fan.inletModelObject().get());
  EXPECT_EQ(fanOutlet.get(), fan.outletModelObject().get());
  EXPECT_EQ(coolingInlet.get(), coolingCoil.airInletModelObject().get());
  EXPECT_EQ(coolingOutlet.get(), coolingCoil.airOutletModelObject().get());
  EXPECT_EQ(heatingInlet.get(), heatingCoil.airInletModelObject().get());
  EXPECT_EQ(heatingOutlet.get(), heatingCoil.airOutletModelObject().get());
}

TEST_F(EPModelFixture, ZoneHVACFourPipeFanCoil_ScheduleRelationships_RoundTrip) {
  Model model;
  ZoneHVACFourPipeFanCoil coil(model);

  auto defaultSchedule = coil.availabilitySchedule().optionalCast<ScheduleConstant>();
  ASSERT_TRUE(defaultSchedule);
  EXPECT_DOUBLE_EQ(1.0, defaultSchedule->value());

  ScheduleCompact availability(model);
  ScheduleCompact outdoorAir(model);
  ScheduleCompact fanMode(model);
  ASSERT_TRUE(availability.setToConstantValue(0.3));
  ASSERT_TRUE(outdoorAir.setToConstantValue(0.4));
  ASSERT_TRUE(fanMode.setToConstantValue(1.0));

  EXPECT_TRUE(coil.setAvailabilitySchedule(availability));
  EXPECT_TRUE(coil.setOutdoorAirSchedule(outdoorAir));
  EXPECT_TRUE(coil.setSupplyAirFanOperatingModeSchedule(fanMode));
  EXPECT_EQ(availability.handle(), coil.availabilitySchedule().handle());
  ASSERT_TRUE(coil.outdoorAirSchedule());
  EXPECT_EQ(outdoorAir.handle(), coil.outdoorAirSchedule()->handle());
  ASSERT_TRUE(coil.supplyAirFanOperatingModeSchedule());
  EXPECT_EQ(fanMode.handle(), coil.supplyAirFanOperatingModeSchedule()->handle());

  coil.resetOutdoorAirSchedule();
  EXPECT_FALSE(coil.outdoorAirSchedule());
  coil.resetSupplyAirFanOperatingModeSchedule();
  EXPECT_FALSE(coil.supplyAirFanOperatingModeSchedule());
}

TEST_F(EPModelFixture, ZoneHVACFourPipeFanCoil_HvacRelationships_RoundTrip) {
  Model model;
  ZoneHVACFourPipeFanCoil coil(model);
  FanConstantVolume fan(model);
  CoilCoolingWater coolingCoil(model);
  CoilHeatingWater heatingCoil(model);

  ASSERT_TRUE(coil.setCapacityControlMethod("ConstantFanVariableFlow"));
  EXPECT_TRUE(coil.setSupplyAirFan(fan));
  EXPECT_TRUE(coil.setCoolingCoil(coolingCoil));
  EXPECT_TRUE(coil.setHeatingCoil(heatingCoil));
  EXPECT_EQ(fan.handle(), coil.supplyAirFan().handle());
  EXPECT_EQ(coolingCoil.handle(), coil.coolingCoil().handle());
  EXPECT_EQ(heatingCoil.handle(), coil.heatingCoil().handle());

  auto fanType = coil.getString(openstudio::ZoneHVAC_FourPipeFanCoilFields::SupplyAirFanObjectType, true);
  auto coolingType = coil.getString(openstudio::ZoneHVAC_FourPipeFanCoilFields::CoolingCoilObjectType, true);
  auto heatingType = coil.getString(openstudio::ZoneHVAC_FourPipeFanCoilFields::HeatingCoilObjectType, true);
  ASSERT_TRUE(fanType);
  ASSERT_TRUE(coolingType);
  ASSERT_TRUE(heatingType);
  EXPECT_EQ(fan.iddObject().name(), *fanType);
  EXPECT_EQ(coolingCoil.iddObject().name(), *coolingType);
  EXPECT_EQ(heatingCoil.iddObject().name(), *heatingType);
}

TEST_F(EPModelFixture, ZoneHVACFourPipeFanCoil_ContainedNodePath_RoundTrip) {
  Model model;
  ZoneHVACFourPipeFanCoil coil(model);
  FanConstantVolume fan(model);
  CoilCoolingWater coolingCoil(model);
  CoilHeatingWater heatingCoil(model);

  ASSERT_TRUE(coil.setCapacityControlMethod("ConstantFanVariableFlow"));
  ASSERT_TRUE(coil.setSupplyAirFan(fan));
  ASSERT_TRUE(coil.setCoolingCoil(coolingCoil));
  ASSERT_TRUE(coil.setHeatingCoil(heatingCoil));

  auto coilInlet = coil.inletNode();
  auto coilOutlet = coil.outletNode();
  auto fanOutletNode = coil.fanOutletNode();
  auto coolingOutletNode = coil.coolingCoilOutletNode();
  auto fanInlet = fan.inletModelObject();
  auto fanOutlet = fan.outletModelObject();
  auto coolingInlet = coolingCoil.airInletModelObject();
  auto coolingOutlet = coolingCoil.airOutletModelObject();
  auto heatingInlet = heatingCoil.airInletModelObject();
  auto heatingOutlet = heatingCoil.airOutletModelObject();

  ASSERT_TRUE(coilInlet);
  ASSERT_TRUE(coilOutlet);
  ASSERT_TRUE(fanOutletNode);
  ASSERT_TRUE(coolingOutletNode);
  ASSERT_TRUE(fanInlet);
  ASSERT_TRUE(fanOutlet);
  ASSERT_TRUE(coolingInlet);
  ASSERT_TRUE(coolingOutlet);
  ASSERT_TRUE(heatingInlet);
  ASSERT_TRUE(heatingOutlet);

  EXPECT_EQ(*coilInlet, *fanInlet->optionalCast<Node>());
  EXPECT_EQ(*fanOutletNode, *fanOutlet->optionalCast<Node>());
  EXPECT_EQ(*fanOutletNode, *coolingInlet->optionalCast<Node>());
  EXPECT_EQ(*coolingOutletNode, *coolingOutlet->optionalCast<Node>());
  EXPECT_EQ(*coolingOutletNode, *heatingInlet->optionalCast<Node>());
  EXPECT_EQ(*coilOutlet, *heatingOutlet->optionalCast<Node>());
  EXPECT_NE(*coilInlet, *fanOutletNode);
  EXPECT_NE(*fanOutletNode, *coolingOutletNode);
  EXPECT_NE(*coolingOutletNode, *coilOutlet);

  ASSERT_TRUE(fan.containingHVACComponent());
  ASSERT_TRUE(coolingCoil.containingHVACComponent());
  ASSERT_TRUE(heatingCoil.containingHVACComponent());
  EXPECT_EQ(coil, fan.containingHVACComponent().get());
  EXPECT_EQ(coil, coolingCoil.containingHVACComponent().get());
  EXPECT_EQ(coil, heatingCoil.containingHVACComponent().get());
}

TEST_F(EPModelFixture, ZoneHVACFourPipeFanCoil_NodeRolesMayAliasBoundaryNodes) {
  Model model;
  ZoneHVACFourPipeFanCoil coil(model);
  FanConstantVolume fan(model);
  CoilCoolingWater coolingCoil(model);

  ASSERT_TRUE(coil.setCapacityControlMethod("ConstantFanVariableFlow"));
  ASSERT_TRUE(coil.setSupplyAirFan(fan));
  ASSERT_TRUE(coil.setCoolingCoil(coolingCoil));

  ASSERT_TRUE(coil.fanOutletNode());
  ASSERT_TRUE(coil.coolingCoilOutletNode());
  EXPECT_EQ(*coil.fanOutletNode(), *coolingCoil.airInletModelObject()->optionalCast<Node>());
  EXPECT_EQ(*coil.coolingCoilOutletNode(), *coolingCoil.airOutletModelObject()->optionalCast<Node>());
  EXPECT_EQ(*coil.coolingCoilOutletNode(), *coil.outletNode());

  Model model2;
  ZoneHVACFourPipeFanCoil fanOnlyCoil(model2);
  FanConstantVolume loneFan(model2);
  ASSERT_TRUE(fanOnlyCoil.setCapacityControlMethod("ConstantFanVariableFlow"));
  ASSERT_TRUE(fanOnlyCoil.setSupplyAirFan(loneFan));
  ASSERT_TRUE(fanOnlyCoil.fanOutletNode());
  EXPECT_EQ(*fanOnlyCoil.inletNode(), *loneFan.inletModelObject()->optionalCast<Node>());
  EXPECT_EQ(*fanOnlyCoil.fanOutletNode(), *fanOnlyCoil.outletNode());
  EXPECT_FALSE(fanOnlyCoil.coolingCoilOutletNode());
}

TEST_F(EPModelFixture, ZoneHVACFourPipeFanCoil_InternalNodeRenamesSurviveCanonicalize) {
  Model model;
  ZoneHVACFourPipeFanCoil coil(model);
  FanConstantVolume fan(model);
  CoilCoolingWater coolingCoil(model);
  CoilHeatingWater heatingCoil(model);

  ASSERT_TRUE(coil.setCapacityControlMethod("ConstantFanVariableFlow"));
  ASSERT_TRUE(coil.setSupplyAirFan(fan));
  ASSERT_TRUE(coil.setCoolingCoil(coolingCoil));
  ASSERT_TRUE(coil.setHeatingCoil(heatingCoil));

  ASSERT_TRUE(coil.fanOutletNode());
  ASSERT_TRUE(coil.coolingCoilOutletNode());
  ASSERT_TRUE(coil.fanOutletNode()->setName("Custom Four Pipe Fan Outlet"));
  ASSERT_TRUE(coil.coolingCoilOutletNode()->setName("Custom Four Pipe Cooling Outlet"));

  auto report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);

  EXPECT_EQ("Custom Four Pipe Fan Outlet", coil.fanOutletNode()->nameString());
  EXPECT_EQ("Custom Four Pipe Cooling Outlet", coil.coolingCoilOutletNode()->nameString());
  EXPECT_EQ(*coil.inletNode(), *fan.inletModelObject()->optionalCast<Node>());
  EXPECT_EQ(*coil.fanOutletNode(), *coolingCoil.airInletModelObject()->optionalCast<Node>());
  EXPECT_EQ(*coil.coolingCoilOutletNode(), *heatingCoil.airInletModelObject()->optionalCast<Node>());
}

TEST_F(EPModelFixture, ZoneHVACFourPipeFanCoil_ContainedChildTopologyMutationsAreRejected) {
  Model model;
  AirLoopHVAC airLoop(model);
  PlantLoop plantLoop(model);
  ZoneHVACFourPipeFanCoil coil(model);
  FanConstantVolume fan(model);
  CoilCoolingWater coolingCoil(model);
  CoilHeatingWater heatingCoil(model);

  ASSERT_TRUE(coil.setCapacityControlMethod("ConstantFanVariableFlow"));
  ASSERT_TRUE(coil.setSupplyAirFan(fan));
  ASSERT_TRUE(coil.setCoolingCoil(coolingCoil));
  ASSERT_TRUE(coil.setHeatingCoil(heatingCoil));

  auto originalInlet = coil.inletNode();
  auto originalFanOutlet = coil.fanOutletNode();
  auto originalCoolingOutlet = coil.coolingCoilOutletNode();
  ASSERT_TRUE(originalInlet);
  ASSERT_TRUE(originalFanOutlet);
  ASSERT_TRUE(originalCoolingOutlet);

  auto supplyOutletNode = airLoop.supplyOutletNode();

  fan.disconnect();
  EXPECT_FALSE(fan.addToNode(supplyOutletNode));
  EXPECT_FALSE(fan.isRemovable());
  EXPECT_TRUE(fan.remove().empty());

  coolingCoil.disconnectAirSide();
  EXPECT_FALSE(coolingCoil.addToNode(supplyOutletNode));
  EXPECT_FALSE(coolingCoil.removeFromAirLoopHVAC());
  EXPECT_FALSE(coolingCoil.isRemovable());
  EXPECT_TRUE(coolingCoil.remove().empty());
  EXPECT_TRUE(plantLoop.addDemandBranchForComponent(coolingCoil));
  ASSERT_TRUE(coolingCoil.plantLoop());
  EXPECT_EQ(plantLoop, coolingCoil.plantLoop().get());
  coolingCoil.disconnect();
  ASSERT_TRUE(coolingCoil.plantLoop());
  EXPECT_EQ(plantLoop, coolingCoil.plantLoop().get());

  heatingCoil.disconnectAirSide();
  EXPECT_FALSE(heatingCoil.addToNode(supplyOutletNode));
  EXPECT_FALSE(heatingCoil.removeFromAirLoopHVAC());
  EXPECT_FALSE(heatingCoil.isRemovable());
  EXPECT_TRUE(heatingCoil.remove().empty());

  EXPECT_EQ(*originalInlet, *coil.inletNode());
  EXPECT_EQ(*originalFanOutlet, *coil.fanOutletNode());
  EXPECT_EQ(*originalCoolingOutlet, *coil.coolingCoilOutletNode());
  EXPECT_EQ(*coil.inletNode(), *fan.inletModelObject()->optionalCast<Node>());
  EXPECT_EQ(*coil.fanOutletNode(), *coolingCoil.airInletModelObject()->optionalCast<Node>());
  EXPECT_EQ(*coil.coolingCoilOutletNode(), *heatingCoil.airInletModelObject()->optionalCast<Node>());
}

TEST_F(EPModelFixture, ZoneHVACFourPipeFanCoil_PlantAttachedOwnedChildLifecycle) {
  Model model;
  PlantLoop chilledWaterLoop(model);
  PlantLoop hotWaterLoop(model);
  FanConstantVolume fan(model);
  CoilCoolingWater originalCoolingCoil(model);
  CoilCoolingWater replacementCoolingCoil(model);
  CoilHeatingWater heatingCoil(model);
  ZoneHVACFourPipeFanCoil fanCoil(model);

  ASSERT_TRUE(fanCoil.setCapacityControlMethod("ConstantFanVariableFlow"));
  ASSERT_TRUE(fanCoil.setSupplyAirFan(fan));
  ASSERT_TRUE(fanCoil.setCoolingCoil(originalCoolingCoil));
  ASSERT_TRUE(fanCoil.setHeatingCoil(heatingCoil));
  ASSERT_TRUE(chilledWaterLoop.addDemandBranchForComponent(originalCoolingCoil));
  ASSERT_TRUE(hotWaterLoop.addDemandBranchForComponent(heatingCoil));
  ASSERT_TRUE(originalCoolingCoil.plantLoop());
  ASSERT_TRUE(heatingCoil.plantLoop());
  EXPECT_EQ(chilledWaterLoop, originalCoolingCoil.plantLoop().get());
  EXPECT_EQ(hotWaterLoop, heatingCoil.plantLoop().get());
  EXPECT_FALSE(originalCoolingCoil.isRemovable());
  EXPECT_FALSE(heatingCoil.isRemovable());

  ASSERT_TRUE(fanCoil.setCoolingCoil(replacementCoolingCoil));
  EXPECT_TRUE(originalCoolingCoil.isRemovable());
  ASSERT_TRUE(originalCoolingCoil.plantLoop());
  EXPECT_EQ(chilledWaterLoop, originalCoolingCoil.plantLoop().get());
  EXPECT_TRUE(chilledWaterLoop.demandComponent(originalCoolingCoil.handle()));
  EXPECT_FALSE(replacementCoolingCoil.isRemovable());

  ASSERT_TRUE(chilledWaterLoop.addDemandBranchForComponent(replacementCoolingCoil));
  ASSERT_TRUE(replacementCoolingCoil.plantLoop());
  EXPECT_EQ(chilledWaterLoop, replacementCoolingCoil.plantLoop().get());

  const auto fanCoilHandle = fanCoil.handle();
  const auto fanHandle = fan.handle();
  const auto originalCoolingCoilHandle = originalCoolingCoil.handle();
  const auto replacementCoolingCoilHandle = replacementCoolingCoil.handle();
  const auto heatingCoilHandle = heatingCoil.handle();

  EXPECT_FALSE(fanCoil.remove().empty());
  EXPECT_FALSE(model.getObject(fanCoilHandle));
  EXPECT_FALSE(model.getObject(fanHandle));
  EXPECT_TRUE(model.getObject(originalCoolingCoilHandle));
  EXPECT_FALSE(model.getObject(replacementCoolingCoilHandle));
  EXPECT_FALSE(model.getObject(heatingCoilHandle));
  EXPECT_TRUE(chilledWaterLoop.demandComponent(originalCoolingCoilHandle));
  EXPECT_FALSE(chilledWaterLoop.demandComponent(replacementCoolingCoilHandle));
  EXPECT_FALSE(hotWaterLoop.demandComponent(heatingCoilHandle));
}

TEST_F(EPModelFixture, ZoneHVACFourPipeFanCoil_OwnerMutationsRebuildContainedPathWithoutSalvage) {
  Model model;
  ZoneHVACFourPipeFanCoil coil(model);
  FanConstantVolume fan(model);
  CoilCoolingWater coolingCoil(model);
  CoilHeatingWater heatingCoil(model);

  ASSERT_TRUE(coil.setCapacityControlMethod("ConstantFanVariableFlow"));
  ASSERT_TRUE(coil.setSupplyAirFan(fan));
  ASSERT_TRUE(coil.setCoolingCoil(coolingCoil));
  ASSERT_TRUE(coil.setHeatingCoil(heatingCoil));

  Node rogueMixedAir(model);
  ASSERT_TRUE(rogueMixedAir.setName("Rogue Four Pipe Mixed Air"));
  Node rogueFanOutlet(model);
  ASSERT_TRUE(rogueFanOutlet.setName("Rogue Four Pipe Fan Outlet"));
  Node rogueCoolingOutlet(model);
  ASSERT_TRUE(rogueCoolingOutlet.setName("Rogue Four Pipe Cooling Outlet"));

  ASSERT_TRUE(fan.setPointer(fan.inletPort(), rogueMixedAir.handle()));
  ASSERT_TRUE(fan.setPointer(fan.outletPort(), rogueFanOutlet.handle()));
  ASSERT_TRUE(coolingCoil.setPointer(coolingCoil.airInletPort(), rogueFanOutlet.handle()));
  ASSERT_TRUE(coolingCoil.setPointer(coolingCoil.airOutletPort(), rogueCoolingOutlet.handle()));
  ASSERT_TRUE(heatingCoil.setPointer(heatingCoil.airInletPort(), rogueCoolingOutlet.handle()));

  CoilCoolingWater replacementCoolingCoil(model);
  ASSERT_TRUE(coil.setCoolingCoil(replacementCoolingCoil));
  ASSERT_TRUE(coil.setCoolingCoil(coolingCoil));

  EXPECT_NE("Rogue Four Pipe Mixed Air", coil.inletNode()->nameString());
  EXPECT_NE("Rogue Four Pipe Fan Outlet", coil.fanOutletNode()->nameString());
  EXPECT_NE("Rogue Four Pipe Cooling Outlet", coil.coolingCoilOutletNode()->nameString());
  EXPECT_EQ(*coil.inletNode(), *fan.inletModelObject()->optionalCast<Node>());
  EXPECT_EQ(*coil.fanOutletNode(), *coolingCoil.airInletModelObject()->optionalCast<Node>());
  EXPECT_EQ(*coil.coolingCoilOutletNode(), *heatingCoil.airInletModelObject()->optionalCast<Node>());
}

TEST_F(EPModelFixture, ZoneHVACFourPipeFanCoil_CanonicalizeRepairsContainedNodePath) {
  Model model;
  ZoneHVACFourPipeFanCoil coil(model);
  FanConstantVolume fan(model);
  CoilCoolingWater coolingCoil(model);
  CoilHeatingWater heatingCoil(model);

  ASSERT_TRUE(coil.setCapacityControlMethod("ConstantFanVariableFlow"));
  ASSERT_TRUE(coil.setSupplyAirFan(fan));
  ASSERT_TRUE(coil.setCoolingCoil(coolingCoil));
  ASSERT_TRUE(coil.setHeatingCoil(heatingCoil));

  auto expectedInlet = coil.inletNode();
  auto expectedOutlet = coil.outletNode();
  ASSERT_TRUE(expectedInlet);
  ASSERT_TRUE(expectedOutlet);

  Node rogueFanOutlet(model);
  ASSERT_TRUE(rogueFanOutlet.setName("Rogue Four Pipe Fan Outlet"));
  Node rogueCoolingOutlet(model);
  ASSERT_TRUE(rogueCoolingOutlet.setName("Rogue Four Pipe Cooling Outlet"));

  ASSERT_TRUE(fan.setPointer(fan.inletPort(), coil.inletNode()->handle()));
  ASSERT_TRUE(fan.setPointer(fan.outletPort(), rogueFanOutlet.handle()));
  ASSERT_TRUE(coolingCoil.setPointer(coolingCoil.airInletPort(), rogueFanOutlet.handle()));
  ASSERT_TRUE(coolingCoil.setPointer(coolingCoil.airOutletPort(), rogueCoolingOutlet.handle()));
  ASSERT_TRUE(heatingCoil.setPointer(heatingCoil.airInletPort(), rogueCoolingOutlet.handle()));
  ASSERT_TRUE(heatingCoil.setPointer(heatingCoil.airOutletPort(), expectedInlet->handle()));

  auto report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);

  EXPECT_EQ(*expectedInlet, *coil.inletNode());
  EXPECT_EQ("Rogue Four Pipe Fan Outlet", coil.fanOutletNode()->nameString());
  EXPECT_EQ("Rogue Four Pipe Cooling Outlet", coil.coolingCoilOutletNode()->nameString());
  EXPECT_EQ(*coil.inletNode(), *fan.inletModelObject()->optionalCast<Node>());
  EXPECT_EQ(*coil.fanOutletNode(), *coolingCoil.airInletModelObject()->optionalCast<Node>());
  EXPECT_EQ(*coil.coolingCoilOutletNode(), *heatingCoil.airInletModelObject()->optionalCast<Node>());
  EXPECT_EQ(*expectedOutlet, *heatingCoil.airOutletModelObject()->optionalCast<Node>());
}
