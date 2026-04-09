/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../StraightComponent/Node.hpp"
#include "../StraightComponent/EvaporativeCoolerDirectResearchSpecial.hpp"
#include "../StraightComponent/EvaporativeCoolerIndirectResearchSpecial.hpp"
#include "../StraightComponent/FanSystemModel.hpp"
#include "../ZoneHVACComponent/ZoneHVACEvaporativeCoolerUnit.hpp"

#include <utilities/idd/EvaporativeCooler_Direct_ResearchSpecial_FieldEnums.hxx>
#include <utilities/idd/Fan_SystemModel_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_EvaporativeCoolerUnit_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneHVACEvaporativeCoolerUnit_DefaultConstructor) {
  Model model;
  ZoneHVACEvaporativeCoolerUnit cooler(model);

  EXPECT_EQ(ZoneHVACEvaporativeCoolerUnit::iddObjectType(), cooler.iddObject().type());
  EXPECT_EQ(openstudio::IddObjectType::Schedule_Constant, cooler.availabilitySchedule().iddObject().type().value());
  EXPECT_EQ(openstudio::IddObjectType::Fan_SystemModel, cooler.supplyAirFan().iddObject().type().value());
  EXPECT_EQ(openstudio::IddObjectType::EvaporativeCooler_Direct_ResearchSpecial, cooler.firstEvaporativeCooler().iddObject().type().value());
  EXPECT_FALSE(cooler.secondEvaporativeCooler());
  EXPECT_TRUE(cooler.isDesignSupplyAirFlowRateAutosized());
  EXPECT_EQ("BlowThrough", cooler.fanPlacement());
  EXPECT_EQ("ZoneTemperatureDeadbandOnOffCycling", cooler.coolerUnitControlMethod());
  EXPECT_DOUBLE_EQ(1.0, cooler.throttlingRangeTemperatureDifference());
  EXPECT_DOUBLE_EQ(100.0, cooler.coolingLoadControlThresholdHeatTransferRate());
  EXPECT_DOUBLE_EQ(100.0, cooler.shutOffRelativeHumidity());
}

TEST_F(EPModelFixture, ZoneHVACEvaporativeCoolerUnit_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneHVACEvaporativeCoolerUnit cooler(model);

  EXPECT_TRUE(cooler.setDesignSupplyAirFlowRate(0.5));
  EXPECT_FALSE(cooler.isDesignSupplyAirFlowRateAutosized());
  EXPECT_TRUE(cooler.setFanPlacement("DrawThrough"));
  EXPECT_TRUE(cooler.setCoolerUnitControlMethod("ZoneCoolingLoadOnOffCycling"));
  EXPECT_TRUE(cooler.setThrottlingRangeTemperatureDifference(2.0));
  EXPECT_TRUE(cooler.setCoolingLoadControlThresholdHeatTransferRate(200.0));
  EXPECT_TRUE(cooler.setShutOffRelativeHumidity(40.0));

  ASSERT_TRUE(cooler.designSupplyAirFlowRate());
  EXPECT_DOUBLE_EQ(0.5, cooler.designSupplyAirFlowRate().value());
  EXPECT_EQ("DrawThrough", cooler.fanPlacement());
  EXPECT_EQ("ZoneCoolingLoadOnOffCycling", cooler.coolerUnitControlMethod());
  EXPECT_DOUBLE_EQ(2.0, cooler.throttlingRangeTemperatureDifference());
  EXPECT_DOUBLE_EQ(200.0, cooler.coolingLoadControlThresholdHeatTransferRate());
  EXPECT_DOUBLE_EQ(40.0, cooler.shutOffRelativeHumidity());

  cooler.autosizeDesignSupplyAirFlowRate();
  EXPECT_TRUE(cooler.isDesignSupplyAirFlowRateAutosized());
}

TEST_F(EPModelFixture, ZoneHVACEvaporativeCoolerUnit_PortsAndZoneAttachment) {
  Model model;
  ZoneHVACEvaporativeCoolerUnit cooler(model);
  ThermalZone zone(model);

  EXPECT_EQ(openstudio::ZoneHVAC_EvaporativeCoolerUnitFields::ZoneReliefAirNodeName, cooler.inletPort());
  EXPECT_EQ(openstudio::ZoneHVAC_EvaporativeCoolerUnitFields::CoolerOutletNodeName, cooler.outletPort());

  EXPECT_TRUE(cooler.addToThermalZone(zone));
  ASSERT_TRUE(cooler.inletNode());
  ASSERT_TRUE(cooler.outletNode());
  ASSERT_TRUE(cooler.outdoorAirNode());
  ASSERT_TRUE(cooler.fanOutletNode());
  ASSERT_TRUE(cooler.firstEvaporativeCoolerOutletNode());
  EXPECT_EQ(zone, cooler.thermalZone().get());
  cooler.removeFromThermalZone();
  EXPECT_FALSE(cooler.thermalZone());
  EXPECT_TRUE(cooler.inletNode());
  EXPECT_TRUE(cooler.outletNode());
}

TEST_F(EPModelFixture, ZoneHVACEvaporativeCoolerUnit_RelationshipsAndOwnedNodes) {
  Model model;
  ZoneHVACEvaporativeCoolerUnit cooler(model);
  FanSystemModel fan(model);
  EvaporativeCoolerDirectResearchSpecial firstCooler(model);
  EvaporativeCoolerIndirectResearchSpecial secondCooler(model);

  EXPECT_TRUE(cooler.setSupplyAirFan(fan));
  EXPECT_TRUE(cooler.setFirstEvaporativeCooler(firstCooler));
  EXPECT_TRUE(cooler.setSecondEvaporativeCooler(secondCooler));
  EXPECT_TRUE(cooler.setFanPlacement("DrawThrough"));

  ASSERT_TRUE(cooler.outdoorAirNode());
  ASSERT_TRUE(cooler.fanOutletNode());
  ASSERT_TRUE(cooler.firstEvaporativeCoolerOutletNode());

  auto fanInlet = fan.inletModelObject()->optionalCast<Node>();
  auto fanOutlet = fan.outletModelObject()->optionalCast<Node>();
  auto firstInlet = firstCooler.inletModelObject()->optionalCast<Node>();
  auto firstOutlet = firstCooler.outletModelObject()->optionalCast<Node>();
  auto secondInlet = secondCooler.inletModelObject()->optionalCast<Node>();
  auto secondOutlet = secondCooler.outletModelObject()->optionalCast<Node>();
  ASSERT_TRUE(fanInlet);
  ASSERT_TRUE(fanOutlet);
  ASSERT_TRUE(firstInlet);
  ASSERT_TRUE(firstOutlet);
  ASSERT_TRUE(secondInlet);
  ASSERT_TRUE(secondOutlet);

  EXPECT_EQ(*cooler.outdoorAirNode(), *firstInlet);
  EXPECT_EQ(*cooler.firstEvaporativeCoolerOutletNode(), *firstOutlet);
  EXPECT_EQ(*cooler.firstEvaporativeCoolerOutletNode(), *secondInlet);
  EXPECT_EQ(*cooler.fanOutletNode(), *fanOutlet);
  EXPECT_EQ(*cooler.fanOutletNode(), *cooler.outletNode());
  EXPECT_EQ(*secondOutlet, *fanInlet);

  const auto children = cooler.children();
  ASSERT_EQ(3u, children.size());
  EXPECT_EQ(fan.handle(), children[0].handle());
  EXPECT_EQ(firstCooler.handle(), children[1].handle());
  EXPECT_EQ(secondCooler.handle(), children[2].handle());
}

TEST_F(EPModelFixture, ZoneHVACEvaporativeCoolerUnit_ChildrenOrderAndContent) {
  Model model;
  ZoneHVACEvaporativeCoolerUnit cooler(model);
  FanSystemModel fan(model);
  EvaporativeCoolerDirectResearchSpecial firstEvaporativeCooler(model);
  EvaporativeCoolerIndirectResearchSpecial secondEvaporativeCooler(model);

  EXPECT_TRUE(cooler.setPointer(openstudio::ZoneHVAC_EvaporativeCoolerUnitFields::SupplyAirFanName, fan.handle()));
  EXPECT_TRUE(cooler.setPointer(openstudio::ZoneHVAC_EvaporativeCoolerUnitFields::FirstEvaporativeCoolerObjectName, firstEvaporativeCooler.handle()));
  EXPECT_TRUE(cooler.setPointer(openstudio::ZoneHVAC_EvaporativeCoolerUnitFields::SecondEvaporativeCoolerName, secondEvaporativeCooler.handle()));

  const auto children = cooler.children();
  ASSERT_EQ(3u, children.size());
  EXPECT_EQ(fan.handle(), children[0].handle());
  EXPECT_EQ(firstEvaporativeCooler.handle(), children[1].handle());
  EXPECT_EQ(secondEvaporativeCooler.handle(), children[2].handle());
}

TEST_F(EPModelFixture, ZoneHVACEvaporativeCoolerUnit_ContainedChildTopologyEditsAreRejectedAndCanonicalizationRepairsRawDrift) {
  Model model;
  ZoneHVACEvaporativeCoolerUnit cooler(model);
  FanSystemModel fan(model);
  EvaporativeCoolerDirectResearchSpecial firstCooler(model);
  ASSERT_TRUE(cooler.setSupplyAirFan(fan));
  ASSERT_TRUE(cooler.setFirstEvaporativeCooler(firstCooler));
  Node strayNode(model);

  auto originalFanInlet = fan.inletModelObject()->optionalCast<Node>();
  ASSERT_TRUE(originalFanInlet);

  fan.disconnect();
  EXPECT_EQ(*originalFanInlet, *fan.inletModelObject()->optionalCast<Node>());

  ASSERT_TRUE(fan.setPointer(openstudio::Fan_SystemModelFields::AirInletNodeName, strayNode.handle()));
  ASSERT_TRUE(firstCooler.setPointer(openstudio::EvaporativeCooler_Direct_ResearchSpecialFields::AirInletNodeName, strayNode.handle()));

  model.canonicalize(SanitizationPolicy::Repair);

  auto repairedOutdoorAirNode = cooler.outdoorAirNode();
  auto repairedFanOutletNode = cooler.fanOutletNode();
  ASSERT_TRUE(repairedOutdoorAirNode);
  ASSERT_TRUE(repairedFanOutletNode);
  EXPECT_EQ(*repairedOutdoorAirNode, *fan.inletModelObject()->optionalCast<Node>());
  EXPECT_EQ(*repairedFanOutletNode, *firstCooler.inletModelObject()->optionalCast<Node>());
}
