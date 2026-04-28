/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/HVACTemplateZoneBaseboardHeat.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, HVACTemplateZoneBaseboardHeat_DefaultConstructor) {
  Model model;
  HVACTemplateZoneBaseboardHeat object(model);
  EXPECT_EQ(HVACTemplateZoneBaseboardHeat::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, HVACTemplateZoneBaseboardHeat_ScalarAccessors_RoundTrip) {
  Model model;
  HVACTemplateZoneBaseboardHeat object(model);

  EXPECT_FALSE(object.zoneHeatingSizingFactor());
  EXPECT_TRUE(object.setZoneHeatingSizingFactor(1.1));
  ASSERT_TRUE(object.zoneHeatingSizingFactor());
  EXPECT_DOUBLE_EQ(1.1, object.zoneHeatingSizingFactor().get());
  object.resetZoneHeatingSizingFactor();
  EXPECT_FALSE(object.zoneHeatingSizingFactor());
  EXPECT_FALSE(object.setZoneHeatingSizingFactor(-0.1));

  EXPECT_TRUE(object.isBaseboardHeatingTypeDefaulted());
  EXPECT_TRUE(object.setBaseboardHeatingType("Electric"));
  EXPECT_EQ("Electric", object.baseboardHeatingType());
  EXPECT_FALSE(object.isBaseboardHeatingTypeDefaulted());
  EXPECT_FALSE(object.setBaseboardHeatingType("InvalidChoice"));
  object.resetBaseboardHeatingType();
  EXPECT_TRUE(object.isBaseboardHeatingTypeDefaulted());

  EXPECT_TRUE(object.isBaseboardHeatingCapacityDefaulted());
  EXPECT_TRUE(object.isBaseboardHeatingCapacityAutosized());
  EXPECT_TRUE(object.setBaseboardHeatingCapacity(8500.0));
  ASSERT_TRUE(object.baseboardHeatingCapacity());
  EXPECT_DOUBLE_EQ(8500.0, object.baseboardHeatingCapacity().get());
  EXPECT_FALSE(object.isBaseboardHeatingCapacityDefaulted());
  EXPECT_FALSE(object.isBaseboardHeatingCapacityAutosized());
  object.autosizeBaseboardHeatingCapacity();
  EXPECT_TRUE(object.isBaseboardHeatingCapacityAutosized());
  object.resetBaseboardHeatingCapacity();
  EXPECT_TRUE(object.isBaseboardHeatingCapacityDefaulted());

  EXPECT_TRUE(object.isOutdoorAirMethodDefaulted());
  EXPECT_TRUE(object.setOutdoorAirMethod("Flow/Zone"));
  EXPECT_EQ("Flow/Zone", object.outdoorAirMethod());
  EXPECT_FALSE(object.isOutdoorAirMethodDefaulted());
  EXPECT_FALSE(object.setOutdoorAirMethod("InvalidChoice"));
  object.resetOutdoorAirMethod();
  EXPECT_TRUE(object.isOutdoorAirMethodDefaulted());

  EXPECT_TRUE(object.isOutdoorAirFlowRateperPersonDefaulted());
  EXPECT_TRUE(object.setOutdoorAirFlowRateperPerson(0.015));
  EXPECT_DOUBLE_EQ(0.015, object.outdoorAirFlowRateperPerson());
  EXPECT_FALSE(object.isOutdoorAirFlowRateperPersonDefaulted());
  object.resetOutdoorAirFlowRateperPerson();
  EXPECT_TRUE(object.isOutdoorAirFlowRateperPersonDefaulted());

  EXPECT_TRUE(object.isOutdoorAirFlowRateperZoneFloorAreaDefaulted());
  EXPECT_TRUE(object.setOutdoorAirFlowRateperZoneFloorArea(0.001));
  EXPECT_DOUBLE_EQ(0.001, object.outdoorAirFlowRateperZoneFloorArea());
  EXPECT_FALSE(object.isOutdoorAirFlowRateperZoneFloorAreaDefaulted());
  object.resetOutdoorAirFlowRateperZoneFloorArea();
  EXPECT_TRUE(object.isOutdoorAirFlowRateperZoneFloorAreaDefaulted());

  EXPECT_TRUE(object.isOutdoorAirFlowRateperZoneDefaulted());
  EXPECT_TRUE(object.setOutdoorAirFlowRateperZone(0.2));
  EXPECT_DOUBLE_EQ(0.2, object.outdoorAirFlowRateperZone());
  EXPECT_FALSE(object.isOutdoorAirFlowRateperZoneDefaulted());
  object.resetOutdoorAirFlowRateperZone();
  EXPECT_TRUE(object.isOutdoorAirFlowRateperZoneDefaulted());

  EXPECT_GE(HVACTemplateZoneBaseboardHeat::baseboardHeatingTypeValues().size(), 1u);
  EXPECT_GE(HVACTemplateZoneBaseboardHeat::outdoorAirMethodValues().size(), 1u);
}
