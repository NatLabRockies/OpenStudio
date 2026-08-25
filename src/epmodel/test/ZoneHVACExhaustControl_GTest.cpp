/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../HVACComponent/ThermalZone_Impl.hpp"
#include "../Mixer/AirLoopHVACZoneMixer.hpp"
#include "../ModelObject/NodeList.hpp"
#include "../ModelObject/NodeList_Impl.hpp"
#include "../ModelObject/ZoneHVACEquipmentConnections.hpp"
#include "../ModelObject/ZoneHVACEquipmentConnections_Impl.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../StraightComponent/FanSystemModel.hpp"
#include "../StraightComponent/Node.hpp"
#include "../ModelObject/AirLoopHVACExhaustSystem.hpp"
#include "../ModelObject/AirLoopHVACExhaustSystem_Impl.hpp"
#include "../ModelObject/ZoneHVACExhaustControl.hpp"
#include "../ModelObject/ZoneHVACExhaustControl_Impl.hpp"

#include <utilities/idd/AirLoopHVAC_ExhaustSystem_FieldEnums.hxx>
#include <utilities/idd/NodeList_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_EquipmentConnections_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_ExhaustControl_FieldEnums.hxx>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneHVACExhaustControl_DefaultConstructor) {
  Model model;
  ZoneHVACExhaustControl exhaust(model);

  EXPECT_EQ(ZoneHVACExhaustControl::iddObjectType(), exhaust.iddObject().type());
  EXPECT_EQ("Scheduled", exhaust.flowControlType());
  EXPECT_FALSE(exhaust.isFlowControlTypeDefaulted());
  EXPECT_TRUE(exhaust.isDesignExhaustFlowRateAutosized());
}

TEST_F(EPModelFixture, ZoneHVACExhaustControl_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneHVACExhaustControl exhaust(model);

  EXPECT_TRUE(exhaust.setFlowControlType("FollowSupply"));
  EXPECT_FALSE(exhaust.isFlowControlTypeDefaulted());
  EXPECT_TRUE(exhaust.setDesignExhaustFlowRate(0.15));
  EXPECT_FALSE(exhaust.isDesignExhaustFlowRateAutosized());
  ASSERT_TRUE(exhaust.designExhaustFlowRate());
  EXPECT_DOUBLE_EQ(0.15, exhaust.designExhaustFlowRate().value());

  exhaust.autosizeDesignExhaustFlowRate();
  EXPECT_TRUE(exhaust.isDesignExhaustFlowRateAutosized());

  exhaust.resetDesignExhaustFlowRate();
  EXPECT_TRUE(exhaust.isDesignExhaustFlowRateAutosized());

  exhaust.resetFlowControlType();
  EXPECT_TRUE(exhaust.isFlowControlTypeDefaulted());
}

TEST_F(EPModelFixture, ZoneHVACExhaustControl_RelationshipsAndUniqueExhaustSystemOwnership) {
  Model model;
  ThermalZone zone(model);
  ZoneHVACExhaustControl control(model);
  Node inlet(model);
  Node outlet(model);
  NodeList supplyNodes(model);
  ScheduleConstant availability(model);
  ScheduleConstant flowFraction(model);
  ScheduleConstant minimumTemperature(model);
  ScheduleConstant minimumFraction(model);
  ScheduleConstant balancedFraction(model);

  ASSERT_TRUE(control.setPointer(openstudio::ZoneHVAC_ExhaustControlFields::AvailabilityScheduleName, availability.handle()));
  ASSERT_TRUE(control.setPointer(openstudio::ZoneHVAC_ExhaustControlFields::ZoneName, zone.handle()));
  ASSERT_TRUE(control.setPointer(openstudio::ZoneHVAC_ExhaustControlFields::InletNodeName, inlet.handle()));
  ASSERT_TRUE(control.setPointer(openstudio::ZoneHVAC_ExhaustControlFields::OutletNodeName, outlet.handle()));
  ASSERT_TRUE(control.setPointer(openstudio::ZoneHVAC_ExhaustControlFields::ExhaustFlowFractionScheduleName, flowFraction.handle()));
  ASSERT_TRUE(control.setPointer(openstudio::ZoneHVAC_ExhaustControlFields::SupplyNodeorNodeListName, supplyNodes.handle()));
  ASSERT_TRUE(control.setPointer(openstudio::ZoneHVAC_ExhaustControlFields::MinimumZoneTemperatureLimitScheduleName, minimumTemperature.handle()));
  ASSERT_TRUE(control.setPointer(openstudio::ZoneHVAC_ExhaustControlFields::MinimumExhaustFlowFractionScheduleName, minimumFraction.handle()));
  ASSERT_TRUE(control.setPointer(openstudio::ZoneHVAC_ExhaustControlFields::BalancedExhaustFractionScheduleName, balancedFraction.handle()));

  ASSERT_TRUE(control.availabilitySchedule());
  ASSERT_TRUE(control.thermalZone());
  ASSERT_TRUE(control.inletNode());
  ASSERT_TRUE(control.outletNode());
  ASSERT_TRUE(control.exhaustFlowFractionSchedule());
  ASSERT_TRUE(control.supplyNodeorNodeList());
  ASSERT_TRUE(control.minimumZoneTemperatureLimitSchedule());
  ASSERT_TRUE(control.minimumExhaustFlowFractionSchedule());
  ASSERT_TRUE(control.balancedExhaustFractionSchedule());
  EXPECT_EQ(availability, *control.availabilitySchedule());
  EXPECT_EQ(zone, *control.thermalZone());
  EXPECT_EQ(inlet, *control.inletNode());
  EXPECT_EQ(outlet, *control.outletNode());
  EXPECT_EQ(flowFraction, *control.exhaustFlowFractionSchedule());
  EXPECT_EQ(supplyNodes.cast<ModelObject>(), *control.supplyNodeorNodeList());
  EXPECT_EQ(minimumTemperature, *control.minimumZoneTemperatureLimitSchedule());
  EXPECT_EQ(minimumFraction, *control.minimumExhaustFlowFractionSchedule());
  EXPECT_EQ(balancedFraction, *control.balancedExhaustFractionSchedule());
  EXPECT_FALSE(control.airLoopHVACExhaustSystem());

  AirLoopHVACZoneMixer firstMixer(model);
  FanSystemModel firstFan(model);
  AirLoopHVACExhaustSystem firstSystem(model);
  ASSERT_TRUE(firstSystem.setPointer(openstudio::AirLoopHVAC_ExhaustSystemFields::ZoneMixerName, firstMixer.handle()));
  ASSERT_TRUE(firstSystem.setString(openstudio::AirLoopHVAC_ExhaustSystemFields::FanObjectType, "Fan:SystemModel"));
  ASSERT_TRUE(firstSystem.setPointer(openstudio::AirLoopHVAC_ExhaustSystemFields::FanName, firstFan.handle()));
  ASSERT_TRUE(firstMixer.setInletModelObject(0, outlet));
  ASSERT_EQ(1u, firstSystem.zoneHVACExhaustControls().size());
  EXPECT_EQ(control, firstSystem.zoneHVACExhaustControls().front());
  ASSERT_TRUE(control.airLoopHVACExhaustSystem());
  EXPECT_EQ(firstSystem, *control.airLoopHVACExhaustSystem());

  AirLoopHVACZoneMixer secondMixer(model);
  FanSystemModel secondFan(model);
  AirLoopHVACExhaustSystem secondSystem(model);
  ASSERT_TRUE(secondSystem.setPointer(openstudio::AirLoopHVAC_ExhaustSystemFields::ZoneMixerName, secondMixer.handle()));
  ASSERT_TRUE(secondSystem.setString(openstudio::AirLoopHVAC_ExhaustSystemFields::FanObjectType, "Fan:SystemModel"));
  ASSERT_TRUE(secondSystem.setPointer(openstudio::AirLoopHVAC_ExhaustSystemFields::FanName, secondFan.handle()));
  ASSERT_TRUE(secondMixer.setInletModelObject(0, outlet));
  EXPECT_FALSE(control.airLoopHVACExhaustSystem());
  EXPECT_TRUE(firstSystem.zoneHVACExhaustControls().empty());
  EXPECT_TRUE(secondSystem.zoneHVACExhaustControls().empty());
  EXPECT_TRUE(control.remove().empty());
  EXPECT_TRUE(model.getObject(control.handle()));
}

TEST_F(EPModelFixture, ZoneHVACExhaustControl_RoutedOwnershipSurvivesReload) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-zone-exhaust-control-roundtrip.idf");

  Model model;
  ThermalZone zone(model);
  ZoneHVACExhaustControl control(model);
  Node inlet(model);
  Node outlet(model);
  AirLoopHVACZoneMixer mixer(model);
  FanSystemModel fan(model);
  AirLoopHVACExhaustSystem system(model);
  ASSERT_TRUE(zone.setName("Roundtrip Exhaust Zone"));
  ASSERT_TRUE(control.setName("Roundtrip Exhaust Control"));
  ASSERT_TRUE(inlet.setName("Roundtrip Zone Exhaust Inlet"));
  ASSERT_TRUE(outlet.setName("Roundtrip Zone Exhaust Outlet"));
  ASSERT_TRUE(mixer.setName("Roundtrip Central Exhaust Mixer"));
  ASSERT_TRUE(fan.setName("Roundtrip Central Exhaust Fan"));
  ASSERT_TRUE(system.setName("Roundtrip Central Exhaust System"));
  ASSERT_TRUE(control.setPointer(openstudio::ZoneHVAC_ExhaustControlFields::ZoneName, zone.handle()));
  ASSERT_TRUE(control.setPointer(openstudio::ZoneHVAC_ExhaustControlFields::InletNodeName, inlet.handle()));
  ASSERT_TRUE(control.setPointer(openstudio::ZoneHVAC_ExhaustControlFields::OutletNodeName, outlet.handle()));
  ASSERT_TRUE(mixer.setInletModelObject(0, outlet));
  ASSERT_TRUE(system.setPointer(openstudio::AirLoopHVAC_ExhaustSystemFields::ZoneMixerName, mixer.handle()));
  ASSERT_TRUE(system.setString(openstudio::AirLoopHVAC_ExhaustSystemFields::FanObjectType, "Fan:SystemModel"));
  ASSERT_TRUE(system.setPointer(openstudio::AirLoopHVAC_ExhaustSystemFields::FanName, fan.handle()));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedControl = loadedModel->getConcreteModelObjectByName<ZoneHVACExhaustControl>("Roundtrip Exhaust Control");
  auto loadedSystem = loadedModel->getConcreteModelObjectByName<AirLoopHVACExhaustSystem>("Roundtrip Central Exhaust System");
  ASSERT_TRUE(loadedControl);
  ASSERT_TRUE(loadedSystem);
  ASSERT_TRUE(loadedControl->thermalZone());
  ASSERT_TRUE(loadedControl->inletNode());
  ASSERT_TRUE(loadedControl->outletNode());
  ASSERT_TRUE(loadedControl->airLoopHVACExhaustSystem());
  EXPECT_EQ(*loadedSystem, *loadedControl->airLoopHVACExhaustSystem());
  ASSERT_EQ(1u, loadedSystem->zoneHVACExhaustControls().size());
  EXPECT_EQ(*loadedControl, loadedSystem->zoneHVACExhaustControls().front());

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, ZoneHVACExhaustControl_StandaloneRemovalRejectsOrphanMixerMembership) {
  Model model;
  ZoneHVACExhaustControl control(model);
  Node outlet(model);
  AirLoopHVACZoneMixer mixer(model);
  ASSERT_TRUE(control.setPointer(openstudio::ZoneHVAC_ExhaustControlFields::OutletNodeName, outlet.handle()));
  ASSERT_TRUE(mixer.setInletModelObject(0u, outlet));

  EXPECT_TRUE(control.remove().empty());
  EXPECT_TRUE(model.getObject(control.handle()));
  ASSERT_EQ(1u, mixer.inletModelObjects().size());
  EXPECT_EQ(outlet.cast<ModelObject>(), mixer.inletModelObjects().front());
}

TEST_F(EPModelFixture, ZoneHVACExhaustControl_StandaloneRemovalRejectsDuplicateZoneRegistration) {
  Model model;
  ThermalZone zone(model);
  ZoneHVACExhaustControl control(model);
  Node inlet(model);
  Node outlet(model);
  NodeList duplicateExhaustNodes(model);
  ASSERT_TRUE(control.setPointer(openstudio::ZoneHVAC_ExhaustControlFields::ZoneName, zone.handle()));
  ASSERT_TRUE(control.setPointer(openstudio::ZoneHVAC_ExhaustControlFields::InletNodeName, inlet.handle()));
  ASSERT_TRUE(control.setPointer(openstudio::ZoneHVAC_ExhaustControlFields::OutletNodeName, outlet.handle()));
  for (unsigned i = 0u; i < 2u; ++i) {
    auto group = duplicateExhaustNodes.pushExtensibleGroup().optionalCast<openstudio::WorkspaceExtensibleGroup>();
    ASSERT_TRUE(group);
    ASSERT_TRUE(group->setPointer(openstudio::NodeListExtensibleFields::NodeName, inlet.handle()));
  }
  auto connections = zone.getImpl<detail::ThermalZone_Impl>()->getZoneHVACEquipmentConnections();
  ASSERT_TRUE(
    connections.setPointer(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirExhaustNodeorNodeListName, duplicateExhaustNodes.handle()));

  EXPECT_TRUE(control.remove().empty());
  EXPECT_TRUE(model.getObject(control.handle()));
  EXPECT_EQ((std::vector<Node>{inlet, inlet}), connections.zoneAirExhaustNodes());
}

TEST_F(EPModelFixture, ZoneHVACExhaustControl_StandaloneRemovalRejectsExternalNodeClaims) {
  Model model;
  ThermalZone zone(model);
  ZoneHVACExhaustControl control(model);
  ZoneHVACExhaustControl competingControl(model);
  Node inlet(model);
  Node outlet(model);
  ASSERT_TRUE(control.setPointer(openstudio::ZoneHVAC_ExhaustControlFields::ZoneName, zone.handle()));
  ASSERT_TRUE(control.setPointer(openstudio::ZoneHVAC_ExhaustControlFields::InletNodeName, inlet.handle()));
  ASSERT_TRUE(control.setPointer(openstudio::ZoneHVAC_ExhaustControlFields::OutletNodeName, outlet.handle()));
  ASSERT_TRUE(competingControl.setPointer(openstudio::ZoneHVAC_ExhaustControlFields::InletNodeName, inlet.handle()));
  auto connections = zone.getImpl<detail::ThermalZone_Impl>()->getZoneHVACEquipmentConnections();
  auto connectionsImpl = connections.getImpl<detail::ZoneHVACEquipmentConnections_Impl>();
  ASSERT_TRUE(connectionsImpl);
  ASSERT_TRUE(connectionsImpl->addZoneAirExhaustNode(inlet));
  const auto exhaustNodesBefore = connections.zoneAirExhaustNodes();

  EXPECT_TRUE(control.remove().empty());

  EXPECT_TRUE(model.getObject(control.handle()));
  EXPECT_TRUE(model.getObject(competingControl.handle()));
  EXPECT_EQ(exhaustNodesBefore, connections.zoneAirExhaustNodes());
}
