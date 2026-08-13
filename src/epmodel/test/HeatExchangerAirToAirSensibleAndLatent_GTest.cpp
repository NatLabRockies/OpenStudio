/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../AirToAirComponent/HeatExchangerAirToAirSensibleAndLatent.hpp"
#include "../AirToAirComponent/HeatExchangerAirToAirSensibleAndLatent_Impl.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem_Impl.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../ModelObject/AirLoopHVACDedicatedOutdoorAirSystem.hpp"
#include "../ModelObject/AirLoopHVACDedicatedOutdoorAirSystem_Impl.hpp"
#include "../ModelObject/AirLoopHVACMixer.hpp"
#include "../ModelObject/AirLoopHVACMixer_Impl.hpp"
#include "../ModelObject/OutdoorAirMixer.hpp"
#include "../ModelObject/OutdoorAirMixer_Impl.hpp"
#include "../StraightComponent/Node.hpp"

#include <utilities/idd/AirLoopHVAC_DedicatedOutdoorAirSystem_FieldEnums.hxx>
#include <utilities/idd/AirLoopHVAC_Mixer_FieldEnums.hxx>
#include <utilities/idd/OutdoorAir_Mixer_FieldEnums.hxx>

#include <algorithm>

using namespace openstudio::epmodel;

namespace {

std::string firstNonEmpty(const std::vector<std::string>& values) {
  auto it = std::find_if(values.begin(), values.end(), [](const auto& value) { return !value.empty(); });
  if (it != values.end()) {
    return *it;
  }
  return {};
}

std::vector<openstudio::Handle> objectHandles(const std::vector<ModelObject>& objects) {
  std::vector<openstudio::Handle> result;
  result.reserve(objects.size());
  std::ranges::transform(objects, std::back_inserter(result), [](const auto& object) { return object.handle(); });
  return result;
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

TEST_F(EPModelFixture, HeatExchangerAirToAirSensibleAndLatent_DedicatedMixerFollowsReliefStreamAcrossReloadAndMutation) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-doas-heat-recovery-roundtrip.idf");

  Model model;
  AirLoopHVACOutdoorAirSystem dedicatedOA(model);
  AirLoopHVACDedicatedOutdoorAirSystem doas(dedicatedOA);
  HeatExchangerAirToAirSensibleAndLatent hx(model);
  ASSERT_TRUE(dedicatedOA.setName("Roundtrip Heat Recovery OA System"));
  ASSERT_TRUE(doas.setName("Roundtrip Heat Recovery DOAS"));
  ASSERT_TRUE(hx.setName("Roundtrip Heat Exchanger"));

  auto outdoorNode = dedicatedOA.outboardOANode();
  ASSERT_TRUE(outdoorNode);
  ASSERT_TRUE(hx.addToNode(*outdoorNode));

  auto mixers = model.getConcreteModelObjects<AirLoopHVACMixer>();
  ASSERT_EQ(1u, mixers.size());
  auto mixerOutlet = mixers.front().getModelObjectTarget<Node>(openstudio::AirLoopHVAC_MixerFields::OutletNodeName);
  auto secondaryInlet = hx.secondaryAirInletModelObject();
  ASSERT_TRUE(mixerOutlet);
  ASSERT_TRUE(secondaryInlet);
  EXPECT_EQ(*mixerOutlet, secondaryInlet->cast<Node>());
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedOA = loadedModel->getConcreteModelObjectByName<AirLoopHVACOutdoorAirSystem>("Roundtrip Heat Recovery OA System");
  auto loadedHX = loadedModel->getConcreteModelObjectByName<HeatExchangerAirToAirSensibleAndLatent>("Roundtrip Heat Exchanger");
  auto loadedMixers = loadedModel->getConcreteModelObjects<AirLoopHVACMixer>();
  ASSERT_TRUE(loadedOA);
  ASSERT_TRUE(loadedHX);
  ASSERT_EQ(1u, loadedMixers.size());
  auto loadedMixerOutlet = loadedMixers.front().getModelObjectTarget<Node>(openstudio::AirLoopHVAC_MixerFields::OutletNodeName);
  auto loadedSecondaryInlet = loadedHX->secondaryAirInletModelObject();
  ASSERT_TRUE(loadedMixerOutlet);
  ASSERT_TRUE(loadedSecondaryInlet);
  EXPECT_EQ(*loadedMixerOutlet, loadedSecondaryInlet->cast<Node>());
  EXPECT_TRUE(loadedOA->oaComponent(loadedHX->handle()));
  EXPECT_TRUE(loadedOA->reliefComponent(loadedHX->handle()));

  EXPECT_FALSE(loadedHX->remove().empty());
  EXPECT_EQ(1u, loadedOA->oaComponents().size());
  EXPECT_EQ(1u, loadedOA->reliefComponents().size());
  loadedMixerOutlet = loadedMixers.front().getModelObjectTarget<Node>(openstudio::AirLoopHVAC_MixerFields::OutletNodeName);
  auto restoredReliefNode = loadedOA->reliefAirModelObject();
  ASSERT_TRUE(loadedMixerOutlet);
  ASSERT_TRUE(restoredReliefNode);
  EXPECT_EQ(*loadedMixerOutlet, restoredReliefNode->cast<Node>());

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, HeatExchangerAirToAirSensibleAndLatent_RejectsMissingDedicatedMixerWithoutPartialPlacement) {
  Model model;
  AirLoopHVACOutdoorAirSystem dedicatedOA(model);
  AirLoopHVACDedicatedOutdoorAirSystem doas(dedicatedOA);
  HeatExchangerAirToAirSensibleAndLatent hx(model);

  const auto outdoorBefore = objectHandles(dedicatedOA.oaComponents());
  const auto reliefBefore = objectHandles(dedicatedOA.reliefComponents());
  auto outdoorNode = dedicatedOA.outboardOANode();
  ASSERT_TRUE(outdoorNode);
  auto connectorMixer = doas.getTarget(openstudio::AirLoopHVAC_DedicatedOutdoorAirSystemFields::AirLoopHVAC_MixerName);
  ASSERT_TRUE(connectorMixer);
  ASSERT_TRUE(doas.getImpl<detail::ModelObject_Impl>()->setPointer(openstudio::AirLoopHVAC_DedicatedOutdoorAirSystemFields::AirLoopHVAC_MixerName,
                                                                   openstudio::Handle(), false));

  EXPECT_FALSE(hx.addToNode(*outdoorNode));
  EXPECT_EQ(outdoorBefore, objectHandles(dedicatedOA.oaComponents()));
  EXPECT_EQ(reliefBefore, objectHandles(dedicatedOA.reliefComponents()));
  EXPECT_FALSE(dedicatedOA.component(hx.handle()));
  EXPECT_FALSE(hx.primaryAirInletModelObject());
  EXPECT_FALSE(hx.primaryAirOutletModelObject());
  EXPECT_FALSE(hx.secondaryAirInletModelObject());
  EXPECT_FALSE(hx.secondaryAirOutletModelObject());

  ASSERT_TRUE(doas.setPointer(openstudio::AirLoopHVAC_DedicatedOutdoorAirSystemFields::AirLoopHVAC_MixerName, connectorMixer->handle()));
}

TEST_F(EPModelFixture, HeatExchangerAirToAirSensibleAndLatent_RejectsIncompleteRemovalWithoutChangingOutdoorStream) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));
  auto outdoorNode = oaSystem.outboardOANode();
  ASSERT_TRUE(outdoorNode);

  HeatExchangerAirToAirSensibleAndLatent hx(model);
  ASSERT_TRUE(hx.addToNode(*outdoorNode));
  auto outboardReliefNode = oaSystem.outboardReliefNode();
  ASSERT_TRUE(outboardReliefNode);
  auto mixers = model.getConcreteModelObjects<OutdoorAirMixer>();
  ASSERT_EQ(1u, mixers.size());
  ASSERT_TRUE(mixers.front().getImpl<detail::ModelObject_Impl>()->setPointer(openstudio::OutdoorAir_MixerFields::ReliefAirStreamNodeName,
                                                                             outboardReliefNode->handle(), false));

  const auto outdoorBefore = objectHandles(oaSystem.oaComponents());
  const auto reliefBefore = objectHandles(oaSystem.reliefComponents());
  EXPECT_TRUE(oaSystem.oaComponent(hx.handle()));
  EXPECT_FALSE(oaSystem.reliefComponent(hx.handle()));

  EXPECT_TRUE(hx.remove().empty());
  EXPECT_TRUE(model.getObject(hx.handle()));
  EXPECT_EQ(outdoorBefore, objectHandles(oaSystem.oaComponents()));
  EXPECT_EQ(reliefBefore, objectHandles(oaSystem.reliefComponents()));
  EXPECT_TRUE(hx.primaryAirInletModelObject());
  EXPECT_TRUE(hx.primaryAirOutletModelObject());
  EXPECT_TRUE(hx.secondaryAirInletModelObject());
  EXPECT_TRUE(hx.secondaryAirOutletModelObject());
}
