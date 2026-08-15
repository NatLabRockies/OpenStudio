/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../AirToAirComponent/HeatExchangerAirToAirSensibleAndLatent.hpp"
#include "../AirToAirComponent/HeatExchangerAirToAirSensibleAndLatent_Impl.hpp"
#include "../Curve/CurveBiquadratic.hpp"
#include "../Curve/CurveExponent.hpp"
#include "../Curve/CurveExponent_Impl.hpp"
#include "../Curve/CurveLinear.hpp"
#include "../Curve/CurveLinear_Impl.hpp"
#include "../Curve/CurveQuadratic.hpp"
#include "../Curve/CurveQuadratic_Impl.hpp"
#include "../Curve/TableLookup.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem_Impl.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../ModelObject/AirLoopHVACDedicatedOutdoorAirSystem.hpp"
#include "../ModelObject/AirLoopHVACDedicatedOutdoorAirSystem_Impl.hpp"
#include "../ModelObject/AirLoopHVACMixer.hpp"
#include "../ModelObject/AirLoopHVACMixer_Impl.hpp"
#include "../ModelObject/OutdoorAirMixer.hpp"
#include "../ModelObject/OutdoorAirMixer_Impl.hpp"
#include "../ResourceObject/ScheduleTypeLimits.hpp"
#include "../Schedule/Schedule.hpp"
#include "../Schedule/Schedule_Impl.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../StraightComponent/Node.hpp"

#include <utilities/core/Filesystem.hpp>
#include <utilities/core/UUID.hpp>
#include <utilities/idd/AirLoopHVAC_DedicatedOutdoorAirSystem_FieldEnums.hxx>
#include <utilities/idd/AirLoopHVAC_Mixer_FieldEnums.hxx>
#include <utilities/idd/HeatExchanger_AirToAir_SensibleAndLatent_FieldEnums.hxx>
#include <utilities/idd/OutdoorAir_Mixer_FieldEnums.hxx>
#include <utilities/idf/WorkspaceObject_Impl.hpp>

#include <algorithm>
#include <array>
#include <utility>

using namespace openstudio::epmodel;

namespace {

class ScopedFileRemoval
{
 public:
  explicit ScopedFileRemoval(openstudio::path path) : m_path(std::move(path)) {}

  ~ScopedFileRemoval() {
    boost::system::error_code error;
    boost::filesystem::remove(m_path, error);
  }

 private:
  openstudio::path m_path;
};

openstudio::path uniqueIdfPath(const std::string& stem) {
  return openstudio::tempDir() / openstudio::toPath(stem + "-" + openstudio::removeBraces(openstudio::createUUID()) + ".idf");
}

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

std::array<std::string, 4> heatExchangerPortNames(const HeatExchangerAirToAirSensibleAndLatent& heatExchanger) {
  const auto objectName = [](const boost::optional<ModelObject>& object) { return object ? object->nameString() : std::string{}; };
  return {objectName(heatExchanger.primaryAirInletModelObject()), objectName(heatExchanger.primaryAirOutletModelObject()),
          objectName(heatExchanger.secondaryAirInletModelObject()), objectName(heatExchanger.secondaryAirOutletModelObject())};
}

}  // namespace

TEST_F(EPModelFixture, HeatExchangerAirToAirSensibleAndLatent_DefaultConstructor) {
  Model model;
  HeatExchangerAirToAirSensibleAndLatent object(model);

  EXPECT_EQ(HeatExchangerAirToAirSensibleAndLatent::iddObjectType(), object.iddObject().type());
  EXPECT_EQ(model.alwaysOnDiscreteSchedule(), object.availabilitySchedule());
  EXPECT_FALSE(object.sensibleEffectivenessofHeatingAirFlowCurve());
  EXPECT_FALSE(object.latentEffectivenessofHeatingAirFlowCurve());
  EXPECT_FALSE(object.sensibleEffectivenessofCoolingAirFlowCurve());
  EXPECT_FALSE(object.latentEffectivenessofCoolingAirFlowCurve());
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

TEST_F(EPModelFixture, HeatExchangerAirToAirSensibleAndLatent_RelationshipAccessorsSetResetAndScheduleTypeLimits) {
  Model model;
  HeatExchangerAirToAirSensibleAndLatent heatExchanger(model);
  ScheduleConstant availability(model);
  CurveLinear sensibleHeating(model);
  TableLookup latentHeating(model);
  CurveQuadratic sensibleCooling(model);
  CurveExponent latentCooling(model);

  ASSERT_TRUE(availability.setValue(1.0));
  EXPECT_TRUE(heatExchanger.setAvailabilitySchedule(availability));
  EXPECT_EQ(availability, heatExchanger.availabilitySchedule());
  ASSERT_TRUE(availability.scheduleTypeLimits());
  const auto availabilityLimits = *availability.scheduleTypeLimits();
  ASSERT_TRUE(availabilityLimits.numericType());
  EXPECT_EQ("Discrete", *availabilityLimits.numericType());
  EXPECT_EQ("Availability", availabilityLimits.unitType());
  ASSERT_TRUE(availabilityLimits.lowerLimitValue());
  ASSERT_TRUE(availabilityLimits.upperLimitValue());
  EXPECT_DOUBLE_EQ(0.0, *availabilityLimits.lowerLimitValue());
  EXPECT_DOUBLE_EQ(1.0, *availabilityLimits.upperLimitValue());

  EXPECT_TRUE(heatExchanger.setSensibleEffectivenessofHeatingAirFlowCurve(sensibleHeating));
  EXPECT_TRUE(heatExchanger.setLatentEffectivenessofHeatingAirFlowCurve(latentHeating));
  EXPECT_TRUE(heatExchanger.setSensibleEffectivenessofCoolingAirFlowCurve(sensibleCooling));
  EXPECT_TRUE(heatExchanger.setLatentEffectivenessofCoolingAirFlowCurve(latentCooling));
  ASSERT_TRUE(heatExchanger.sensibleEffectivenessofHeatingAirFlowCurve());
  ASSERT_TRUE(heatExchanger.latentEffectivenessofHeatingAirFlowCurve());
  ASSERT_TRUE(heatExchanger.sensibleEffectivenessofCoolingAirFlowCurve());
  ASSERT_TRUE(heatExchanger.latentEffectivenessofCoolingAirFlowCurve());
  EXPECT_EQ(sensibleHeating.handle(), heatExchanger.sensibleEffectivenessofHeatingAirFlowCurve()->handle());
  EXPECT_EQ(latentHeating.handle(), heatExchanger.latentEffectivenessofHeatingAirFlowCurve()->handle());
  EXPECT_EQ(sensibleCooling.handle(), heatExchanger.sensibleEffectivenessofCoolingAirFlowCurve()->handle());
  EXPECT_EQ(latentCooling.handle(), heatExchanger.latentEffectivenessofCoolingAirFlowCurve()->handle());

  const std::array<openstudio::Handle, 4> curveHandles = {sensibleHeating.handle(), latentHeating.handle(), sensibleCooling.handle(),
                                                          latentCooling.handle()};
  heatExchanger.resetSensibleEffectivenessofHeatingAirFlowCurve();
  heatExchanger.resetLatentEffectivenessofHeatingAirFlowCurve();
  heatExchanger.resetSensibleEffectivenessofCoolingAirFlowCurve();
  heatExchanger.resetLatentEffectivenessofCoolingAirFlowCurve();
  EXPECT_FALSE(heatExchanger.sensibleEffectivenessofHeatingAirFlowCurve());
  EXPECT_FALSE(heatExchanger.latentEffectivenessofHeatingAirFlowCurve());
  EXPECT_FALSE(heatExchanger.sensibleEffectivenessofCoolingAirFlowCurve());
  EXPECT_FALSE(heatExchanger.latentEffectivenessofCoolingAirFlowCurve());
  for (const auto& handle : curveHandles) {
    EXPECT_TRUE(model.getObject(handle));
  }
}

TEST_F(EPModelFixture, HeatExchangerAirToAirSensibleAndLatent_RelationshipSettersRejectWithoutChangingTopologyOrRawText) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));
  auto outdoorNode = oaSystem.outboardOANode();
  ASSERT_TRUE(outdoorNode);

  HeatExchangerAirToAirSensibleAndLatent heatExchanger(model);
  ASSERT_TRUE(heatExchanger.addToNode(*outdoorNode));
  ScheduleConstant availability(model);
  CurveLinear acceptedCurve(model);
  ASSERT_TRUE(availability.setValue(1.0));
  ASSERT_TRUE(heatExchanger.setAvailabilitySchedule(availability));
  ASSERT_TRUE(heatExchanger.setSensibleEffectivenessofHeatingAirFlowCurve(acceptedCurve));
  ASSERT_TRUE(heatExchanger.setLatentEffectivenessofHeatingAirFlowCurve(acceptedCurve));
  ASSERT_TRUE(heatExchanger.setSensibleEffectivenessofCoolingAirFlowCurve(acceptedCurve));
  ASSERT_TRUE(heatExchanger.setLatentEffectivenessofCoolingAirFlowCurve(acceptedCurve));

  const auto outdoorBefore = objectHandles(oaSystem.oaComponents());
  const auto reliefBefore = objectHandles(oaSystem.reliefComponents());
  const auto portNamesBefore = heatExchangerPortNames(heatExchanger);

  Model foreignModel;
  ScheduleConstant foreignSchedule(foreignModel);
  CurveLinear foreignCurve(foreignModel);
  EXPECT_FALSE(heatExchanger.setAvailabilitySchedule(foreignSchedule));
  EXPECT_FALSE(heatExchanger.setSensibleEffectivenessofHeatingAirFlowCurve(foreignCurve));
  EXPECT_EQ(availability, heatExchanger.availabilitySchedule());
  ASSERT_TRUE(heatExchanger.sensibleEffectivenessofHeatingAirFlowCurve());
  EXPECT_EQ(acceptedCurve.handle(), heatExchanger.sensibleEffectivenessofHeatingAirFlowCurve()->handle());

  ScheduleConstant incompatibleAvailability(model);
  ScheduleTypeLimits temperatureLimits(model);
  ASSERT_TRUE(temperatureLimits.setLowerLimitValue(0.0));
  ASSERT_TRUE(temperatureLimits.setUpperLimitValue(1.0));
  ASSERT_TRUE(temperatureLimits.setNumericType("Discrete"));
  ASSERT_TRUE(temperatureLimits.setUnitType("Temperature"));
  ASSERT_TRUE(incompatibleAvailability.setScheduleTypeLimits(temperatureLimits));
  CurveBiquadratic rejectedCurve(model);
  EXPECT_FALSE(heatExchanger.setAvailabilitySchedule(incompatibleAvailability));
  EXPECT_FALSE(heatExchanger.setSensibleEffectivenessofHeatingAirFlowCurve(rejectedCurve));
  EXPECT_FALSE(heatExchanger.setLatentEffectivenessofHeatingAirFlowCurve(rejectedCurve));
  EXPECT_FALSE(heatExchanger.setSensibleEffectivenessofCoolingAirFlowCurve(rejectedCurve));
  EXPECT_FALSE(heatExchanger.setLatentEffectivenessofCoolingAirFlowCurve(rejectedCurve));
  EXPECT_EQ(availability, heatExchanger.availabilitySchedule());

  auto heatExchangerWorkspaceImpl = heatExchanger.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(heatExchangerWorkspaceImpl);
  const auto setUnresolvedRaw = [&](unsigned field, const std::string& value) {
    EXPECT_TRUE(heatExchangerWorkspaceImpl->setPointer(field, openstudio::Handle(), false));
    EXPECT_TRUE(heatExchangerWorkspaceImpl->openstudio::detail::IdfObject_Impl::setString(field, value, false));
  };
  const auto rawValue = [&](unsigned field) {
    return heatExchangerWorkspaceImpl->openstudio::detail::IdfObject_Impl::getString(field, false, true).value_or("");
  };

  constexpr unsigned availabilityField = openstudio::HeatExchanger_AirToAir_SensibleAndLatentFields::AvailabilityScheduleName;
  constexpr unsigned sensibleHeatingField =
    openstudio::HeatExchanger_AirToAir_SensibleAndLatentFields::SensibleEffectivenessofHeatingAirFlowCurveName;
  constexpr unsigned latentHeatingField = openstudio::HeatExchanger_AirToAir_SensibleAndLatentFields::LatentEffectivenessofHeatingAirFlowCurveName;
  constexpr unsigned sensibleCoolingField =
    openstudio::HeatExchanger_AirToAir_SensibleAndLatentFields::SensibleEffectivenessofCoolingAirFlowCurveName;
  constexpr unsigned latentCoolingField = openstudio::HeatExchanger_AirToAir_SensibleAndLatentFields::LatentEffectivenessofCoolingAirFlowCurveName;
  setUnresolvedRaw(availabilityField, "Unresolved Heat Exchanger Availability");
  setUnresolvedRaw(sensibleHeatingField, "Unresolved Sensible Heating Curve");
  setUnresolvedRaw(latentHeatingField, "Unresolved Latent Heating Curve");
  setUnresolvedRaw(sensibleCoolingField, "Unresolved Sensible Cooling Curve");
  setUnresolvedRaw(latentCoolingField, "Unresolved Latent Cooling Curve");

  EXPECT_FALSE(heatExchanger.setAvailabilitySchedule(incompatibleAvailability));
  EXPECT_FALSE(heatExchanger.setSensibleEffectivenessofHeatingAirFlowCurve(rejectedCurve));
  EXPECT_FALSE(heatExchanger.setLatentEffectivenessofHeatingAirFlowCurve(rejectedCurve));
  EXPECT_FALSE(heatExchanger.setSensibleEffectivenessofCoolingAirFlowCurve(rejectedCurve));
  EXPECT_FALSE(heatExchanger.setLatentEffectivenessofCoolingAirFlowCurve(rejectedCurve));
  EXPECT_EQ("Unresolved Heat Exchanger Availability", rawValue(availabilityField));
  EXPECT_EQ("Unresolved Sensible Heating Curve", rawValue(sensibleHeatingField));
  EXPECT_EQ("Unresolved Latent Heating Curve", rawValue(latentHeatingField));
  EXPECT_EQ("Unresolved Sensible Cooling Curve", rawValue(sensibleCoolingField));
  EXPECT_EQ("Unresolved Latent Cooling Curve", rawValue(latentCoolingField));
  EXPECT_EQ(outdoorBefore, objectHandles(oaSystem.oaComponents()));
  EXPECT_EQ(reliefBefore, objectHandles(oaSystem.reliefComponents()));
  EXPECT_EQ(portNamesBefore, heatExchangerPortNames(heatExchanger));
}

TEST_F(EPModelFixture, HeatExchangerAirToAirSensibleAndLatent_LoadRepairsRequiredAvailabilitySchedule) {
  const auto idfPath = uniqueIdfPath("epmodel-heat-exchanger-required-availability-repair");
  const ScopedFileRemoval removeIdf(idfPath);

  Model model;
  HeatExchangerAirToAirSensibleAndLatent heatExchanger(model);
  ASSERT_TRUE(heatExchanger.setName("Heat Exchanger Missing Availability"));
  auto heatExchangerWorkspaceImpl = heatExchanger.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(heatExchangerWorkspaceImpl);
  constexpr unsigned availabilityField = openstudio::HeatExchanger_AirToAir_SensibleAndLatentFields::AvailabilityScheduleName;
  ASSERT_TRUE(heatExchangerWorkspaceImpl->setPointer(availabilityField, openstudio::Handle(), false));
  ASSERT_TRUE(heatExchangerWorkspaceImpl->openstudio::detail::IdfObject_Impl::setString(availabilityField, "Missing Availability Schedule", false));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedHeatExchanger = loadedModel->getConcreteModelObjectByName<HeatExchangerAirToAirSensibleAndLatent>("Heat Exchanger Missing Availability");
  ASSERT_TRUE(loadedHeatExchanger);
  EXPECT_EQ(loadedModel->alwaysOnDiscreteSchedule(), loadedHeatExchanger->availabilitySchedule());
  const auto repairedScheduleHandle = loadedHeatExchanger->availabilitySchedule().handle();
  const auto scheduleCount = loadedModel->getModelObjects<Schedule>().size();

  auto report = loadedModel->canonicalize();
  EXPECT_EQ(0u, report.errorCount);
  EXPECT_EQ(repairedScheduleHandle, loadedHeatExchanger->availabilitySchedule().handle());
  EXPECT_EQ(scheduleCount, loadedModel->getModelObjects<Schedule>().size());
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
  const auto idfPath = uniqueIdfPath("epmodel-doas-heat-recovery-roundtrip");
  const ScopedFileRemoval removeIdf(idfPath);

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
}

TEST_F(EPModelFixture, HeatExchangerAirToAirSensibleAndLatent_RelationshipsSurviveReloadPostLoadMutationAndRemoval) {
  const auto firstIdfPath = uniqueIdfPath("epmodel-heat-exchanger-relationships-first");
  const auto secondIdfPath = uniqueIdfPath("epmodel-heat-exchanger-relationships-second");
  const ScopedFileRemoval removeFirstIdf(firstIdfPath);
  const ScopedFileRemoval removeSecondIdf(secondIdfPath);

  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  ASSERT_TRUE(airLoop.setName("Relationship Heat Recovery Air Loop"));
  ASSERT_TRUE(oaSystem.setName("Relationship Heat Recovery OA System"));
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));
  auto outdoorNode = oaSystem.outboardOANode();
  ASSERT_TRUE(outdoorNode);

  HeatExchangerAirToAirSensibleAndLatent heatExchanger(model);
  ScheduleConstant availability(model);
  CurveLinear sensibleHeating(model);
  CurveLinear latentHeating(model);
  CurveQuadratic sensibleCooling(model);
  CurveExponent latentCooling(model);
  ASSERT_TRUE(heatExchanger.setName("Relationship Heat Exchanger"));
  ASSERT_TRUE(availability.setName("Relationship Heat Exchanger Availability"));
  ASSERT_TRUE(sensibleHeating.setName("Relationship Sensible Heating Curve"));
  ASSERT_TRUE(latentHeating.setName("Relationship Latent Heating Curve"));
  ASSERT_TRUE(sensibleCooling.setName("Relationship Sensible Cooling Curve"));
  ASSERT_TRUE(latentCooling.setName("Relationship Latent Cooling Curve"));
  ASSERT_TRUE(availability.setValue(1.0));
  ASSERT_TRUE(heatExchanger.setAvailabilitySchedule(availability));
  ASSERT_TRUE(heatExchanger.setSensibleEffectivenessofHeatingAirFlowCurve(sensibleHeating));
  ASSERT_TRUE(heatExchanger.setLatentEffectivenessofHeatingAirFlowCurve(latentHeating));
  ASSERT_TRUE(heatExchanger.setSensibleEffectivenessofCoolingAirFlowCurve(sensibleCooling));
  ASSERT_TRUE(heatExchanger.setLatentEffectivenessofCoolingAirFlowCurve(latentCooling));
  ASSERT_TRUE(heatExchanger.addToNode(*outdoorNode));
  const auto originalPortNames = heatExchangerPortNames(heatExchanger);
  ASSERT_TRUE(std::ranges::none_of(originalPortNames, [](const auto& name) { return name.empty(); }));
  ASSERT_TRUE(model.save(firstIdfPath, true));

  auto loadedModel = Model::load(firstIdfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedOA = loadedModel->getConcreteModelObjectByName<AirLoopHVACOutdoorAirSystem>("Relationship Heat Recovery OA System");
  auto loadedHeatExchanger = loadedModel->getConcreteModelObjectByName<HeatExchangerAirToAirSensibleAndLatent>("Relationship Heat Exchanger");
  auto loadedAvailability = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("Relationship Heat Exchanger Availability");
  auto loadedSensibleHeating = loadedModel->getConcreteModelObjectByName<CurveLinear>("Relationship Sensible Heating Curve");
  auto loadedLatentHeating = loadedModel->getConcreteModelObjectByName<CurveLinear>("Relationship Latent Heating Curve");
  auto loadedSensibleCooling = loadedModel->getConcreteModelObjectByName<CurveQuadratic>("Relationship Sensible Cooling Curve");
  auto loadedLatentCooling = loadedModel->getConcreteModelObjectByName<CurveExponent>("Relationship Latent Cooling Curve");
  ASSERT_TRUE(loadedOA);
  ASSERT_TRUE(loadedHeatExchanger);
  ASSERT_TRUE(loadedAvailability);
  ASSERT_TRUE(loadedSensibleHeating);
  ASSERT_TRUE(loadedLatentHeating);
  ASSERT_TRUE(loadedSensibleCooling);
  ASSERT_TRUE(loadedLatentCooling);
  EXPECT_EQ(loadedAvailability->handle(), loadedHeatExchanger->availabilitySchedule().handle());
  ASSERT_TRUE(loadedHeatExchanger->sensibleEffectivenessofHeatingAirFlowCurve());
  ASSERT_TRUE(loadedHeatExchanger->latentEffectivenessofHeatingAirFlowCurve());
  ASSERT_TRUE(loadedHeatExchanger->sensibleEffectivenessofCoolingAirFlowCurve());
  ASSERT_TRUE(loadedHeatExchanger->latentEffectivenessofCoolingAirFlowCurve());
  EXPECT_EQ(loadedSensibleHeating->handle(), loadedHeatExchanger->sensibleEffectivenessofHeatingAirFlowCurve()->handle());
  EXPECT_EQ(loadedLatentHeating->handle(), loadedHeatExchanger->latentEffectivenessofHeatingAirFlowCurve()->handle());
  EXPECT_EQ(loadedSensibleCooling->handle(), loadedHeatExchanger->sensibleEffectivenessofCoolingAirFlowCurve()->handle());
  EXPECT_EQ(loadedLatentCooling->handle(), loadedHeatExchanger->latentEffectivenessofCoolingAirFlowCurve()->handle());
  EXPECT_TRUE(loadedOA->oaComponent(loadedHeatExchanger->handle()));
  EXPECT_TRUE(loadedOA->reliefComponent(loadedHeatExchanger->handle()));
  EXPECT_EQ(originalPortNames, heatExchangerPortNames(*loadedHeatExchanger));

  const auto outdoorBeforeMutation = objectHandles(loadedOA->oaComponents());
  const auto reliefBeforeMutation = objectHandles(loadedOA->reliefComponents());
  const auto portsBeforeMutation = heatExchangerPortNames(*loadedHeatExchanger);
  ScheduleConstant replacementAvailability(*loadedModel);
  CurveLinear replacementSensibleHeating(*loadedModel);
  ASSERT_TRUE(replacementAvailability.setName("Replacement Heat Exchanger Availability"));
  ASSERT_TRUE(replacementAvailability.setValue(1.0));
  ASSERT_TRUE(replacementSensibleHeating.setName("Replacement Sensible Heating Curve"));
  ASSERT_TRUE(loadedHeatExchanger->setAvailabilitySchedule(replacementAvailability));
  ASSERT_TRUE(loadedHeatExchanger->setSensibleEffectivenessofHeatingAirFlowCurve(replacementSensibleHeating));
  loadedHeatExchanger->resetLatentEffectivenessofHeatingAirFlowCurve();
  EXPECT_EQ(outdoorBeforeMutation, objectHandles(loadedOA->oaComponents()));
  EXPECT_EQ(reliefBeforeMutation, objectHandles(loadedOA->reliefComponents()));
  EXPECT_EQ(portsBeforeMutation, heatExchangerPortNames(*loadedHeatExchanger));
  ASSERT_TRUE(loadedModel->save(secondIdfPath, true));

  auto reloadedModel = Model::load(secondIdfPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedOA = reloadedModel->getConcreteModelObjectByName<AirLoopHVACOutdoorAirSystem>("Relationship Heat Recovery OA System");
  auto reloadedHeatExchanger = reloadedModel->getConcreteModelObjectByName<HeatExchangerAirToAirSensibleAndLatent>("Relationship Heat Exchanger");
  auto reloadedAvailability = reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Replacement Heat Exchanger Availability");
  auto reloadedSensibleHeating = reloadedModel->getConcreteModelObjectByName<CurveLinear>("Replacement Sensible Heating Curve");
  auto reloadedSensibleCooling = reloadedModel->getConcreteModelObjectByName<CurveQuadratic>("Relationship Sensible Cooling Curve");
  auto reloadedLatentCooling = reloadedModel->getConcreteModelObjectByName<CurveExponent>("Relationship Latent Cooling Curve");
  ASSERT_TRUE(reloadedOA);
  ASSERT_TRUE(reloadedHeatExchanger);
  ASSERT_TRUE(reloadedAvailability);
  ASSERT_TRUE(reloadedSensibleHeating);
  ASSERT_TRUE(reloadedSensibleCooling);
  ASSERT_TRUE(reloadedLatentCooling);
  EXPECT_EQ(reloadedAvailability->handle(), reloadedHeatExchanger->availabilitySchedule().handle());
  ASSERT_TRUE(reloadedHeatExchanger->sensibleEffectivenessofHeatingAirFlowCurve());
  EXPECT_EQ(reloadedSensibleHeating->handle(), reloadedHeatExchanger->sensibleEffectivenessofHeatingAirFlowCurve()->handle());
  EXPECT_FALSE(reloadedHeatExchanger->latentEffectivenessofHeatingAirFlowCurve());
  ASSERT_TRUE(reloadedHeatExchanger->sensibleEffectivenessofCoolingAirFlowCurve());
  ASSERT_TRUE(reloadedHeatExchanger->latentEffectivenessofCoolingAirFlowCurve());
  EXPECT_EQ(reloadedSensibleCooling->handle(), reloadedHeatExchanger->sensibleEffectivenessofCoolingAirFlowCurve()->handle());
  EXPECT_EQ(reloadedLatentCooling->handle(), reloadedHeatExchanger->latentEffectivenessofCoolingAirFlowCurve()->handle());
  EXPECT_TRUE(reloadedOA->oaComponent(reloadedHeatExchanger->handle()));
  EXPECT_TRUE(reloadedOA->reliefComponent(reloadedHeatExchanger->handle()));
  EXPECT_EQ(originalPortNames, heatExchangerPortNames(*reloadedHeatExchanger));

  const auto heatExchangerHandle = reloadedHeatExchanger->handle();
  const std::array<openstudio::Handle, 4> retainedResourceHandles = {reloadedAvailability->handle(), reloadedSensibleHeating->handle(),
                                                                     reloadedSensibleCooling->handle(), reloadedLatentCooling->handle()};
  EXPECT_FALSE(reloadedHeatExchanger->remove().empty());
  EXPECT_FALSE(reloadedModel->getObject(heatExchangerHandle));
  EXPECT_FALSE(reloadedOA->oaComponent(heatExchangerHandle));
  EXPECT_FALSE(reloadedOA->reliefComponent(heatExchangerHandle));
  EXPECT_EQ(1u, reloadedOA->oaComponents().size());
  EXPECT_EQ(1u, reloadedOA->reliefComponents().size());
  for (const auto& handle : retainedResourceHandles) {
    EXPECT_TRUE(reloadedModel->getObject(handle));
  }
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
