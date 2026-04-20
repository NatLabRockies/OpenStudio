/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/HVACTemplateZoneVAV.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, HVACTemplateZoneVAV_DefaultConstructor) {
  Model model;
  HVACTemplateZoneVAV object(model);
  EXPECT_EQ(HVACTemplateZoneVAV::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, HVACTemplateZoneVAV_ScalarAccessors_RoundTrip) {
  Model model;
  HVACTemplateZoneVAV object(model);

  EXPECT_TRUE(object.isSupplyAirMaximumFlowRateAutosized());
  EXPECT_TRUE(object.setSupplyAirMaximumFlowRate(1.3));
  ASSERT_TRUE(object.supplyAirMaximumFlowRate());
  EXPECT_DOUBLE_EQ(1.3, object.supplyAirMaximumFlowRate().get());
  object.autosizeSupplyAirMaximumFlowRate();
  EXPECT_TRUE(object.isSupplyAirMaximumFlowRateAutosized());

  EXPECT_TRUE(object.setZoneMinimumAirFlowInputMethod("Constant"));
  EXPECT_EQ("Constant", object.zoneMinimumAirFlowInputMethod());
  EXPECT_FALSE(object.setZoneMinimumAirFlowInputMethod("InvalidChoice"));

  EXPECT_TRUE(object.setConstantMinimumAirFlowFraction(0.35));
  EXPECT_DOUBLE_EQ(0.35, object.constantMinimumAirFlowFraction());
  EXPECT_FALSE(object.setConstantMinimumAirFlowFraction(1.1));

  EXPECT_TRUE(object.setFixedMinimumAirFlowRate(0.2));
  ASSERT_TRUE(object.fixedMinimumAirFlowRate());
  EXPECT_DOUBLE_EQ(0.2, object.fixedMinimumAirFlowRate().get());

  EXPECT_TRUE(object.setOutdoorAirMethod("Flow/Zone"));
  EXPECT_EQ("Flow/Zone", object.outdoorAirMethod());

  EXPECT_TRUE(object.setReheatCoilType("Electric"));
  EXPECT_EQ("Electric", object.reheatCoilType());
  EXPECT_TRUE(object.setDamperHeatingAction("Reverse"));
  EXPECT_EQ("Reverse", object.damperHeatingAction());

  EXPECT_TRUE(object.isMaximumFlowperZoneFloorAreaDuringReheatDefaulted());
  object.autocalculateMaximumFlowperZoneFloorAreaDuringReheat();
  EXPECT_TRUE(object.isMaximumFlowperZoneFloorAreaDuringReheatAutocalculated());

  EXPECT_TRUE(object.isMaximumFlowFractionDuringReheatDefaulted());
  object.autocalculateMaximumFlowFractionDuringReheat();
  EXPECT_TRUE(object.isMaximumFlowFractionDuringReheatAutocalculated());

  EXPECT_TRUE(object.isBaseboardHeatingCapacityAutosized());
  EXPECT_TRUE(object.setBaseboardHeatingCapacity(5000.0));
  ASSERT_TRUE(object.baseboardHeatingCapacity());
  EXPECT_DOUBLE_EQ(5000.0, object.baseboardHeatingCapacity().get());

  EXPECT_TRUE(object.setZoneCoolingDesignSupplyAirTemperatureInputMethod("TemperatureDifference"));
  EXPECT_EQ("TemperatureDifference", object.zoneCoolingDesignSupplyAirTemperatureInputMethod());

  EXPECT_TRUE(object.setZoneHeatingDesignSupplyAirTemperatureInputMethod("SupplyAirTemperature"));
  EXPECT_EQ("SupplyAirTemperature", object.zoneHeatingDesignSupplyAirTemperatureInputMethod());

  EXPECT_GE(HVACTemplateZoneVAV::zoneMinimumAirFlowInputMethodValues().size(), 1u);
  EXPECT_GE(HVACTemplateZoneVAV::outdoorAirMethodValues().size(), 1u);
  EXPECT_GE(HVACTemplateZoneVAV::reheatCoilTypeValues().size(), 1u);
  EXPECT_GE(HVACTemplateZoneVAV::damperHeatingActionValues().size(), 1u);
  EXPECT_GE(HVACTemplateZoneVAV::baseboardHeatingTypeValues().size(), 1u);
}
