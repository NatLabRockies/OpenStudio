/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../StraightComponent/HumidifierSteamElectric.hpp"
#include "../StraightComponent/Node.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, HumidifierSteamElectric_DefaultConstructor) {
  Model model;
  HumidifierSteamElectric humidifier(model);
  EXPECT_EQ(HumidifierSteamElectric::iddObjectType(), humidifier.iddObject().type());
  EXPECT_FALSE(humidifier.nameString().empty());

  EXPECT_TRUE(humidifier.isRatedCapacityAutosized());
  EXPECT_FALSE(humidifier.ratedCapacity());

  ASSERT_TRUE(humidifier.ratedPower());
  EXPECT_DOUBLE_EQ(10200.0, humidifier.ratedPower().get());
  EXPECT_FALSE(humidifier.isRatedPowerAutosized());
}

TEST_F(EPModelFixture, HumidifierSteamElectric_ScalarAccessors_RoundTrip) {
  Model model;
  HumidifierSteamElectric humidifier(model);

  EXPECT_TRUE(humidifier.setRatedCapacity(0.42));
  ASSERT_TRUE(humidifier.ratedCapacity());
  EXPECT_DOUBLE_EQ(0.42, humidifier.ratedCapacity().get());
  EXPECT_FALSE(humidifier.isRatedCapacityAutosized());

  humidifier.autosizeRatedCapacity();
  EXPECT_TRUE(humidifier.isRatedCapacityAutosized());
  EXPECT_FALSE(humidifier.ratedCapacity());

  EXPECT_TRUE(humidifier.setRatedPower(9800.0));
  ASSERT_TRUE(humidifier.ratedPower());
  EXPECT_DOUBLE_EQ(9800.0, humidifier.ratedPower().get());
  EXPECT_FALSE(humidifier.isRatedPowerAutosized());

  humidifier.autosizeRatedPower();
  EXPECT_TRUE(humidifier.isRatedPowerAutosized());
  EXPECT_FALSE(humidifier.ratedPower());

  EXPECT_TRUE(humidifier.setRatedFanPower(110.0));
  ASSERT_TRUE(humidifier.ratedFanPower());
  EXPECT_DOUBLE_EQ(110.0, humidifier.ratedFanPower().get());
  humidifier.resetRatedFanPower();
  EXPECT_FALSE(humidifier.ratedFanPower());

  EXPECT_TRUE(humidifier.setStandbyPower(8.0));
  ASSERT_TRUE(humidifier.standbyPower());
  EXPECT_DOUBLE_EQ(8.0, humidifier.standbyPower().get());
  humidifier.resetStandbyPower();
  EXPECT_FALSE(humidifier.standbyPower());

  EXPECT_FALSE(humidifier.autosizedRatedCapacity());
  EXPECT_FALSE(humidifier.autosizedRatedPower());
}

TEST_F(EPModelFixture, HumidifierSteamElectric_AddToNodeSupplyOnly) {
  Model model;
  AirLoopHVAC airLoop(model);
  HumidifierSteamElectric supplyHumidifier(model);
  HumidifierSteamElectric demandHumidifier(model);

  auto supplyInletNode = airLoop.supplyInletNode();
  EXPECT_TRUE(supplyHumidifier.addToNode(supplyInletNode));
  ASSERT_TRUE(supplyHumidifier.inletModelObject());
  EXPECT_EQ(supplyInletNode, supplyHumidifier.inletModelObject()->cast<Node>());
  EXPECT_TRUE(supplyHumidifier.outletModelObject());

  auto demandInletNode = airLoop.demandInletNode();
  EXPECT_FALSE(demandHumidifier.addToNode(demandInletNode));
  EXPECT_FALSE(demandHumidifier.airLoopHVAC());
}

TEST_F(EPModelFixture, HumidifierSteamElectric_AddToNodeSupportsOutboardOANode) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));

  auto outboardOANode = oaSystem.outboardOANode();
  ASSERT_TRUE(outboardOANode);

  HumidifierSteamElectric humidifier(model);
  EXPECT_TRUE(humidifier.addToNode(*outboardOANode));
  EXPECT_EQ(3u, oaSystem.oaComponents().size());
}
