/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../StraightComponent/Node.hpp"
#include "../StraightComponent/EvaporativeCoolerDirectResearchSpecial.hpp"
#include "../StraightComponent/EvaporativeCoolerIndirectResearchSpecial.hpp"
#include "../StraightComponent/FanSystemModel.hpp"
#include "../ZoneHVACComponent/ZoneHVACEvaporativeCoolerUnit.hpp"

#include <utilities/idd/ZoneHVAC_EvaporativeCoolerUnit_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneHVACEvaporativeCoolerUnit_DefaultConstructor) {
  Model model;
  ZoneHVACEvaporativeCoolerUnit cooler(model);

  EXPECT_EQ(ZoneHVACEvaporativeCoolerUnit::iddObjectType(), cooler.iddObject().type());
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
  EXPECT_EQ(zone, cooler.thermalZone().get());
  cooler.removeFromThermalZone();
  EXPECT_FALSE(cooler.thermalZone());
  EXPECT_FALSE(cooler.inletNode());
  EXPECT_FALSE(cooler.outletNode());
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
