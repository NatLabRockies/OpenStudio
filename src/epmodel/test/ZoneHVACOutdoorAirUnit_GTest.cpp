/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/ZoneHVACOutdoorAirUnit.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, API_ZoneHVACOutdoorAirUnit_DefaultConstructor) {
  Model model;
  ZoneHVACOutdoorAirUnit unit(model);

  EXPECT_EQ(ZoneHVACOutdoorAirUnit::iddObjectType(), unit.iddObject().type());
  EXPECT_FALSE(unit.nameString().empty());
}

TEST_F(EPModelFixture, API_ZoneHVACOutdoorAirUnit_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneHVACOutdoorAirUnit unit(model);

  const double outdoorFlow = 0.5;
  EXPECT_TRUE(unit.setOutdoorAirFlowRate(outdoorFlow));
  ASSERT_TRUE(unit.outdoorAirFlowRate());
  EXPECT_DOUBLE_EQ(outdoorFlow, unit.outdoorAirFlowRate().get());

  const double exhaustFlow = 0.4;
  EXPECT_TRUE(unit.setExhaustAirFlowRate(exhaustFlow));
  ASSERT_TRUE(unit.exhaustAirFlowRate());
  EXPECT_DOUBLE_EQ(exhaustFlow, unit.exhaustAirFlowRate().get());

  const auto supplyFanPlacementValues = ZoneHVACOutdoorAirUnit::supplyFanPlacementValues();
  ASSERT_FALSE(supplyFanPlacementValues.empty());
  EXPECT_TRUE(unit.setSupplyFanPlacement(supplyFanPlacementValues.front()));
  EXPECT_FALSE(unit.isSupplyFanPlacementDefaulted());
  EXPECT_EQ(supplyFanPlacementValues.front(), unit.supplyFanPlacement());

  const auto unitControlValues = ZoneHVACOutdoorAirUnit::unitControlTypeValues();
  ASSERT_FALSE(unitControlValues.empty());
  EXPECT_TRUE(unit.setUnitControlType(unitControlValues.back()));
  EXPECT_FALSE(unit.isUnitControlTypeDefaulted());
  EXPECT_EQ(unitControlValues.back(), unit.unitControlType());

  unit.autosizeExhaustAirFlowRate();
  EXPECT_TRUE(unit.isExhaustAirFlowRateAutosized());
  EXPECT_FALSE(unit.exhaustAirFlowRate());

  unit.resetExhaustAirFlowRate();
  EXPECT_FALSE(unit.isExhaustAirFlowRateAutosized());

  unit.resetSupplyFanPlacement();
  EXPECT_TRUE(unit.isSupplyFanPlacementDefaulted());

  unit.resetUnitControlType();
  EXPECT_TRUE(unit.isUnitControlTypeDefaulted());
}
