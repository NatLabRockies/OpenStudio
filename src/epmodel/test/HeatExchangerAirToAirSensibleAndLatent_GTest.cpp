/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../AirToAirComponent/HeatExchangerAirToAirSensibleAndLatent.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../StraightComponent/Node.hpp"

#include <algorithm>

using namespace openstudio::epmodel;

namespace {

std::string firstNonEmpty(const std::vector<std::string>& values) {
  auto it = std::find_if(values.begin(), values.end(), [](const auto& value) {
    return !value.empty();
  });
  if (it != values.end()) {
    return *it;
  }
  return {};
}

}  // namespace

TEST_F(EPModelFixture, HeatExchangerAirToAirSensibleAndLatent_DefaultConstructor) {
  Model model;
  HeatExchangerAirToAirSensibleAndLatent object(model);

  EXPECT_EQ(HeatExchangerAirToAirSensibleAndLatent::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, HeatExchangerAirToAirSensibleAndLatent_ScalarAccessors_RoundTrip) {
  Model model;
  HeatExchangerAirToAirSensibleAndLatent object(model);

  EXPECT_TRUE(object.setNominalSupplyAirFlowRate(1.25));
  ASSERT_TRUE(object.nominalSupplyAirFlowRate());
  EXPECT_DOUBLE_EQ(1.25, object.nominalSupplyAirFlowRate().get());
  EXPECT_FALSE(object.isNominalSupplyAirFlowRateAutosized());

  object.autosizeNominalSupplyAirFlowRate();
  EXPECT_TRUE(object.isNominalSupplyAirFlowRateAutosized());

  EXPECT_TRUE(object.setSensibleEffectivenessat100HeatingAirFlow(0.78));
  EXPECT_DOUBLE_EQ(0.78, object.sensibleEffectivenessat100HeatingAirFlow());

  EXPECT_TRUE(object.setLatentEffectivenessat100HeatingAirFlow(0.61));
  EXPECT_DOUBLE_EQ(0.61, object.latentEffectivenessat100HeatingAirFlow());

  EXPECT_TRUE(object.setSensibleEffectivenessat100CoolingAirFlow(0.76));
  EXPECT_DOUBLE_EQ(0.76, object.sensibleEffectivenessat100CoolingAirFlow());

  EXPECT_TRUE(object.setLatentEffectivenessat100CoolingAirFlow(0.58));
  EXPECT_DOUBLE_EQ(0.58, object.latentEffectivenessat100CoolingAirFlow());

  EXPECT_TRUE(object.setNominalElectricPower(245.0));
  EXPECT_DOUBLE_EQ(245.0, object.nominalElectricPower());

  EXPECT_TRUE(object.setSupplyAirOutletTemperatureControl(true));
  EXPECT_TRUE(object.supplyAirOutletTemperatureControl());

  EXPECT_TRUE(object.setEconomizerLockout(false));
  EXPECT_FALSE(object.economizerLockout());

  EXPECT_TRUE(object.setThresholdTemperature(-7.5));
  EXPECT_DOUBLE_EQ(-7.5, object.thresholdTemperature());
  EXPECT_FALSE(object.isThresholdTemperatureDefaulted());

  object.resetThresholdTemperature();
  EXPECT_TRUE(object.isThresholdTemperatureDefaulted());

  EXPECT_TRUE(object.setInitialDefrostTimeFraction(0.10));
  ASSERT_TRUE(object.initialDefrostTimeFraction());
  EXPECT_DOUBLE_EQ(0.10, object.initialDefrostTimeFraction().get());

  object.resetInitialDefrostTimeFraction();
  EXPECT_TRUE(object.initialDefrostTimeFraction());

  EXPECT_TRUE(object.setRateofDefrostTimeFractionIncrease(0.02));
  ASSERT_TRUE(object.rateofDefrostTimeFractionIncrease());
  EXPECT_DOUBLE_EQ(0.02, object.rateofDefrostTimeFractionIncrease().get());

  object.resetRateofDefrostTimeFractionIncrease();
  EXPECT_TRUE(object.rateofDefrostTimeFractionIncrease());

  const auto hxTypes = HeatExchangerAirToAirSensibleAndLatent::heatExchangerTypeValues();
  const auto frostTypes = HeatExchangerAirToAirSensibleAndLatent::frostControlTypeValues();
  ASSERT_GE(hxTypes.size(), 1u);
  ASSERT_GE(frostTypes.size(), 1u);

  const auto hxType = firstNonEmpty(hxTypes);
  const auto frostType = firstNonEmpty(frostTypes);
  ASSERT_FALSE(hxType.empty());
  ASSERT_FALSE(frostType.empty());

  EXPECT_TRUE(object.setHeatExchangerType(hxType));
  EXPECT_EQ(hxType, object.heatExchangerType());

  EXPECT_TRUE(object.setFrostControlType(frostType));
  EXPECT_EQ(frostType, object.frostControlType());
}

TEST_F(EPModelFixture, HeatExchangerAirToAirSensibleAndLatent_AddToOANodeBuildsBothStreams) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));

  auto outboardOANode = oaSystem.outboardOANode();
  ASSERT_TRUE(outboardOANode);

  HeatExchangerAirToAirSensibleAndLatent hx(model);
  ASSERT_TRUE(hx.addToNode(*outboardOANode));

  EXPECT_EQ(3u, oaSystem.oaComponents().size());
  EXPECT_EQ(3u, oaSystem.reliefComponents().size());
  EXPECT_TRUE(hx.primaryAirInletModelObject());
  EXPECT_TRUE(hx.primaryAirOutletModelObject());
  EXPECT_TRUE(hx.secondaryAirInletModelObject());
  EXPECT_TRUE(hx.secondaryAirOutletModelObject());
}

TEST_F(EPModelFixture, HeatExchangerAirToAirSensibleAndLatent_AddToReliefNodeBuildsBothStreams) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));

  auto outboardReliefNode = oaSystem.outboardReliefNode();
  ASSERT_TRUE(outboardReliefNode);

  HeatExchangerAirToAirSensibleAndLatent hx(model);
  ASSERT_TRUE(hx.addToNode(*outboardReliefNode));

  EXPECT_EQ(3u, oaSystem.oaComponents().size());
  EXPECT_EQ(3u, oaSystem.reliefComponents().size());
  EXPECT_TRUE(hx.primaryAirInletModelObject());
  EXPECT_TRUE(hx.primaryAirOutletModelObject());
  EXPECT_TRUE(hx.secondaryAirInletModelObject());
  EXPECT_TRUE(hx.secondaryAirOutletModelObject());
}

TEST_F(EPModelFixture, HeatExchangerAirToAirSensibleAndLatent_RemoveDetachesFromOutdoorAirSystem) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));

  auto outboardOANode = oaSystem.outboardOANode();
  ASSERT_TRUE(outboardOANode);

  HeatExchangerAirToAirSensibleAndLatent hx(model);
  ASSERT_TRUE(hx.addToNode(*outboardOANode));
  ASSERT_EQ(3u, oaSystem.oaComponents().size());
  ASSERT_EQ(3u, oaSystem.reliefComponents().size());
  const auto hxHandle = hx.handle();

  hx.remove();

  EXPECT_LT(oaSystem.oaComponents().size(), 3u);
  EXPECT_LT(oaSystem.reliefComponents().size(), 3u);
  EXPECT_FALSE(oaSystem.oaComponent(hxHandle));
  EXPECT_FALSE(oaSystem.reliefComponent(hxHandle));
}

TEST_F(EPModelFixture, HeatExchangerAirToAirSensibleAndLatent_RemoveDetachesFromOutdoorAirSystemWhenAddedFromReliefSide) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));

  auto outboardReliefNode = oaSystem.outboardReliefNode();
  ASSERT_TRUE(outboardReliefNode);

  HeatExchangerAirToAirSensibleAndLatent hx(model);
  ASSERT_TRUE(hx.addToNode(*outboardReliefNode));
  ASSERT_EQ(3u, oaSystem.oaComponents().size());
  ASSERT_EQ(3u, oaSystem.reliefComponents().size());
  const auto hxHandle = hx.handle();

  hx.remove();

  EXPECT_EQ(1u, oaSystem.oaComponents().size());
  EXPECT_EQ(1u, oaSystem.reliefComponents().size());
  EXPECT_FALSE(oaSystem.oaComponent(hxHandle));
  EXPECT_FALSE(oaSystem.reliefComponent(hxHandle));
}
