/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/ZoneHVACWindowAirConditioner.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneHVACWindowAirConditioner_DefaultConstructor) {
  Model model;
  ZoneHVACWindowAirConditioner unit(model);
  EXPECT_EQ(ZoneHVACWindowAirConditioner::iddObjectType(), unit.iddObject().type());
  EXPECT_FALSE(unit.maximumSupplyAirFlowRate());
  EXPECT_FALSE(unit.maximumOutdoorAirFlowRate());
}

TEST_F(EPModelFixture, ZoneHVACWindowAirConditioner_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneHVACWindowAirConditioner unit(model);

  ASSERT_TRUE(unit.setMaximumSupplyAirFlowRate(0.35));
  ASSERT_TRUE(unit.setMaximumOutdoorAirFlowRate(0.08));

  ASSERT_TRUE(unit.maximumSupplyAirFlowRate());
  ASSERT_TRUE(unit.maximumOutdoorAirFlowRate());
  EXPECT_DOUBLE_EQ(0.35, *unit.maximumSupplyAirFlowRate());
  EXPECT_DOUBLE_EQ(0.08, *unit.maximumOutdoorAirFlowRate());

  unit.autosizeMaximumSupplyAirFlowRate();
  unit.autosizeMaximumOutdoorAirFlowRate();

  EXPECT_TRUE(unit.isMaximumSupplyAirFlowRateAutosized());
  EXPECT_TRUE(unit.isMaximumOutdoorAirFlowRateAutosized());
  EXPECT_FALSE(unit.maximumSupplyAirFlowRate());
  EXPECT_FALSE(unit.maximumOutdoorAirFlowRate());

  const auto outdoorAirMixerTypes = ZoneHVACWindowAirConditioner::outdoorAirMixerObjectTypeValues();
  ASSERT_FALSE(outdoorAirMixerTypes.empty());
  ASSERT_TRUE(unit.setOutdoorAirMixerObjectType(outdoorAirMixerTypes.front()));
  EXPECT_EQ(outdoorAirMixerTypes.front(), unit.outdoorAirMixerObjectType());

  const auto supplyFanTypes = ZoneHVACWindowAirConditioner::supplyAirFanObjectTypeValues();
  ASSERT_FALSE(supplyFanTypes.empty());
  ASSERT_TRUE(unit.setSupplyAirFanObjectType(supplyFanTypes.front()));
  EXPECT_EQ(supplyFanTypes.front(), unit.supplyAirFanObjectType());

  const auto coolingCoilTypes = ZoneHVACWindowAirConditioner::coolingCoilObjectTypeValues();
  ASSERT_FALSE(coolingCoilTypes.empty());
  ASSERT_TRUE(unit.setCoolingCoilObjectType(coolingCoilTypes.front()));
  EXPECT_EQ(coolingCoilTypes.front(), unit.coolingCoilObjectType());

  const auto fanPlacements = ZoneHVACWindowAirConditioner::fanPlacementValues();
  ASSERT_FALSE(fanPlacements.empty());
  ASSERT_TRUE(unit.setFanPlacement(fanPlacements.front()));
  EXPECT_EQ(fanPlacements.front(), unit.fanPlacement());
}
