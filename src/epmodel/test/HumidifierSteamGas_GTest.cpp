/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include <utilities/idd/Humidifier_Steam_Gas_FieldEnums.hxx>
#include <utilities/core/Filesystem.hpp>
#include <utilities/core/UUID.hpp>
#include <utilities/idf/WorkspaceObject_Impl.hpp>

#include "EPModelFixture.hpp"
#include "../Curve/CurveBiquadratic.hpp"
#include "../Curve/CurveLinear.hpp"
#include "../Curve/CurveLinear_Impl.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../ResourceObject/ScheduleTypeLimits.hpp"
#include "../Schedule/ScheduleCompact.hpp"
#include "../Schedule/ScheduleCompact_Impl.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../StraightComponent/HumidifierSteamGas.hpp"
#include "../StraightComponent/HumidifierSteamGas_Impl.hpp"
#include "../StraightComponent/Node.hpp"

#include <utility>

using namespace openstudio::epmodel;

namespace {
class ScopedHumidifierFileRemoval
{
 public:
  explicit ScopedHumidifierFileRemoval(openstudio::path path) : m_path(std::move(path)) {}
  ~ScopedHumidifierFileRemoval() {
    boost::system::error_code error;
    boost::filesystem::remove(m_path, error);
  }

 private:
  openstudio::path m_path;
};

openstudio::path uniqueHumidifierPath(const std::string& stem) {
  return openstudio::tempDir() / openstudio::toPath(stem + "-" + openstudio::removeBraces(openstudio::createUUID()) + ".idf");
}
}  // namespace

TEST_F(EPModelFixture, HumidifierSteamGas_DefaultConstructor) {
  Model model;
  HumidifierSteamGas humidifier(model);
  EXPECT_EQ(HumidifierSteamGas::iddObjectType(), humidifier.iddObject().type());
  EXPECT_FALSE(humidifier.nameString().empty());

  const std::vector<std::string> expectedInletWaterTemperatureOptionValues{"FixedInletWaterTemperature", "VariableInletWaterTemperature"};
  EXPECT_EQ(expectedInletWaterTemperatureOptionValues, HumidifierSteamGas::inletWaterTemperatureOptionValues());

  EXPECT_TRUE(humidifier.isRatedCapacityAutosized());
  EXPECT_FALSE(humidifier.ratedCapacity());

  ASSERT_TRUE(humidifier.ratedGasUseRate());
  EXPECT_DOUBLE_EQ(104000.0, humidifier.ratedGasUseRate().get());
  EXPECT_FALSE(humidifier.isRatedGasUseRateAutosized());

  EXPECT_FALSE(humidifier.availabilitySchedule());

  EXPECT_DOUBLE_EQ(0.8, humidifier.thermalEfficiency());
  EXPECT_TRUE(humidifier.isThermalEfficiencyDefaulted());
  EXPECT_FALSE(humidifier.thermalEfficiencyModifierCurve());

  EXPECT_FALSE(humidifier.ratedFanPower());

  EXPECT_DOUBLE_EQ(0.0, humidifier.auxiliaryElectricPower());
  EXPECT_TRUE(humidifier.isAuxiliaryElectricPowerDefaulted());

  EXPECT_EQ("FixedInletWaterTemperature", humidifier.inletWaterTemperatureOption());
  EXPECT_TRUE(humidifier.isInletWaterTemperatureOptionDefaulted());

  const auto waterStorageTankName = humidifier.getString(openstudio::Humidifier_Steam_GasFields::WaterStorageTankName, true);
  ASSERT_TRUE(waterStorageTankName);
  EXPECT_TRUE(waterStorageTankName->empty());
}

TEST_F(EPModelFixture, HumidifierSteamGas_ThermalEfficiencyModifierCurveValidationAndReset) {
  Model model;
  AirLoopHVAC airLoop(model);
  HumidifierSteamGas humidifier(model);
  auto supplyOutlet = airLoop.supplyOutletNode();
  ASSERT_TRUE(humidifier.addToNode(supplyOutlet));
  ASSERT_TRUE(humidifier.airLoopHVAC());
  ASSERT_TRUE(humidifier.inletModelObject());
  ASSERT_TRUE(humidifier.outletModelObject());
  const auto airLoopHandle = humidifier.airLoopHVAC()->handle();
  const auto inletHandle = humidifier.inletModelObject()->handle();
  const auto outletHandle = humidifier.outletModelObject()->handle();

  CurveLinear allowed(model);
  CurveBiquadratic disallowed(model);
  ASSERT_TRUE(humidifier.setThermalEfficiencyModifierCurve(allowed));
  ASSERT_TRUE(humidifier.thermalEfficiencyModifierCurve());
  EXPECT_EQ(allowed.handle(), humidifier.thermalEfficiencyModifierCurve()->handle());

  Model foreignModel;
  CurveLinear foreign(foreignModel);
  EXPECT_FALSE(humidifier.setThermalEfficiencyModifierCurve(disallowed));
  EXPECT_FALSE(humidifier.setThermalEfficiencyModifierCurve(foreign));
  ASSERT_TRUE(humidifier.thermalEfficiencyModifierCurve());
  EXPECT_EQ(allowed.handle(), humidifier.thermalEfficiencyModifierCurve()->handle());
  EXPECT_EQ(airLoopHandle, humidifier.airLoopHVAC()->handle());
  EXPECT_EQ(inletHandle, humidifier.inletModelObject()->handle());
  EXPECT_EQ(outletHandle, humidifier.outletModelObject()->handle());

  constexpr auto field = openstudio::Humidifier_Steam_GasFields::ThermalEfficiencyModifierCurveName;
  auto workspaceImpl = humidifier.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(workspaceImpl);
  ASSERT_TRUE(workspaceImpl->setPointer(field, openstudio::Handle(), false));
  ASSERT_TRUE(workspaceImpl->openstudio::detail::IdfObject_Impl::setString(field, "Unresolved Humidifier Efficiency Curve", false));
  EXPECT_FALSE(humidifier.setThermalEfficiencyModifierCurve(disallowed));
  EXPECT_EQ("Unresolved Humidifier Efficiency Curve", workspaceImpl->openstudio::detail::IdfObject_Impl::getString(field, false, true).value_or(""));

  humidifier.resetThermalEfficiencyModifierCurve();
  EXPECT_FALSE(humidifier.thermalEfficiencyModifierCurve());
  EXPECT_TRUE(workspaceImpl->openstudio::detail::IdfObject_Impl::getString(field, false, true).value_or("").empty());
}

TEST_F(EPModelFixture, HumidifierSteamGas_ThermalEfficiencyModifierCurveSurvivesReloadReplacementAndRemoval) {
  const auto firstPath = uniqueHumidifierPath("epmodel-humidifier-steam-gas-curve-first");
  const auto secondPath = uniqueHumidifierPath("epmodel-humidifier-steam-gas-curve-second");
  const ScopedHumidifierFileRemoval removeFirst(firstPath);
  const ScopedHumidifierFileRemoval removeSecond(secondPath);

  Model model;
  AirLoopHVAC airLoop(model);
  HumidifierSteamGas humidifier(model);
  ScheduleCompact availability(model);
  CurveLinear original(model);
  ASSERT_TRUE(humidifier.setName("Reloadable Gas Steam Humidifier"));
  ASSERT_TRUE(availability.setName("Gas Steam Humidifier Availability"));
  ASSERT_TRUE(availability.setToConstantValue(1.0));
  ASSERT_TRUE(original.setName("Original Gas Steam Humidifier Efficiency Curve"));
  ASSERT_TRUE(humidifier.setAvailabilitySchedule(availability));
  ASSERT_TRUE(humidifier.setThermalEfficiencyModifierCurve(original));
  auto supplyOutlet = airLoop.supplyOutletNode();
  ASSERT_TRUE(humidifier.addToNode(supplyOutlet));
  ASSERT_TRUE(model.save(firstPath, true));

  auto loadedModel = Model::load(firstPath);
  ASSERT_TRUE(loadedModel);
  auto loadedHumidifier = loadedModel->getConcreteModelObjectByName<HumidifierSteamGas>("Reloadable Gas Steam Humidifier");
  auto loadedOriginal = loadedModel->getConcreteModelObjectByName<CurveLinear>("Original Gas Steam Humidifier Efficiency Curve");
  auto loadedAvailability = loadedModel->getConcreteModelObjectByName<ScheduleCompact>("Gas Steam Humidifier Availability");
  ASSERT_TRUE(loadedHumidifier);
  ASSERT_TRUE(loadedOriginal);
  ASSERT_TRUE(loadedAvailability);
  ASSERT_TRUE(loadedHumidifier->thermalEfficiencyModifierCurve());
  EXPECT_EQ(loadedOriginal->handle(), loadedHumidifier->thermalEfficiencyModifierCurve()->handle());
  ASSERT_TRUE(loadedHumidifier->availabilitySchedule());
  EXPECT_EQ(loadedAvailability->handle(), loadedHumidifier->availabilitySchedule()->handle());
  EXPECT_TRUE(loadedHumidifier->airLoopHVAC());
  EXPECT_TRUE(loadedHumidifier->inletModelObject());
  EXPECT_TRUE(loadedHumidifier->outletModelObject());

  CurveLinear replacement(*loadedModel);
  ASSERT_TRUE(replacement.setName("Replacement Gas Steam Humidifier Efficiency Curve"));
  ASSERT_TRUE(loadedHumidifier->setThermalEfficiencyModifierCurve(replacement));
  ASSERT_TRUE(loadedModel->save(secondPath, true));

  auto reloadedModel = Model::load(secondPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedHumidifier = reloadedModel->getConcreteModelObjectByName<HumidifierSteamGas>("Reloadable Gas Steam Humidifier");
  auto reloadedOriginal = reloadedModel->getConcreteModelObjectByName<CurveLinear>("Original Gas Steam Humidifier Efficiency Curve");
  auto reloadedReplacement = reloadedModel->getConcreteModelObjectByName<CurveLinear>("Replacement Gas Steam Humidifier Efficiency Curve");
  auto reloadedAvailability = reloadedModel->getConcreteModelObjectByName<ScheduleCompact>("Gas Steam Humidifier Availability");
  ASSERT_TRUE(reloadedHumidifier);
  ASSERT_TRUE(reloadedOriginal);
  ASSERT_TRUE(reloadedReplacement);
  ASSERT_TRUE(reloadedAvailability);
  ASSERT_TRUE(reloadedHumidifier->thermalEfficiencyModifierCurve());
  EXPECT_EQ(reloadedReplacement->handle(), reloadedHumidifier->thermalEfficiencyModifierCurve()->handle());
  reloadedHumidifier->resetThermalEfficiencyModifierCurve();
  ASSERT_TRUE(reloadedModel->save(secondPath, true));

  auto resetModel = Model::load(secondPath);
  ASSERT_TRUE(resetModel);
  auto resetHumidifier = resetModel->getConcreteModelObjectByName<HumidifierSteamGas>("Reloadable Gas Steam Humidifier");
  auto resetOriginal = resetModel->getConcreteModelObjectByName<CurveLinear>("Original Gas Steam Humidifier Efficiency Curve");
  auto resetReplacement = resetModel->getConcreteModelObjectByName<CurveLinear>("Replacement Gas Steam Humidifier Efficiency Curve");
  auto resetAvailability = resetModel->getConcreteModelObjectByName<ScheduleCompact>("Gas Steam Humidifier Availability");
  ASSERT_TRUE(resetHumidifier);
  ASSERT_TRUE(resetOriginal);
  ASSERT_TRUE(resetReplacement);
  ASSERT_TRUE(resetAvailability);
  EXPECT_FALSE(resetHumidifier->thermalEfficiencyModifierCurve());
  EXPECT_TRUE(resetHumidifier->airLoopHVAC());
  EXPECT_FALSE(resetHumidifier->remove().empty());
  EXPECT_TRUE(resetModel->getObject(resetOriginal->handle()));
  EXPECT_TRUE(resetModel->getObject(resetReplacement->handle()));
  EXPECT_TRUE(resetModel->getObject(resetAvailability->handle()));
}

TEST_F(EPModelFixture, HumidifierSteamGas_ScalarAccessors_RoundTrip) {
  Model model;
  HumidifierSteamGas humidifier(model);

  EXPECT_TRUE(humidifier.setRatedCapacity(0.42));
  ASSERT_TRUE(humidifier.ratedCapacity());
  EXPECT_DOUBLE_EQ(0.42, humidifier.ratedCapacity().get());
  EXPECT_FALSE(humidifier.isRatedCapacityAutosized());
  humidifier.autosizeRatedCapacity();
  EXPECT_TRUE(humidifier.isRatedCapacityAutosized());
  EXPECT_FALSE(humidifier.ratedCapacity());

  EXPECT_TRUE(humidifier.setRatedGasUseRate(1234.0));
  ASSERT_TRUE(humidifier.ratedGasUseRate());
  EXPECT_DOUBLE_EQ(1234.0, humidifier.ratedGasUseRate().get());
  EXPECT_FALSE(humidifier.isRatedGasUseRateAutosized());
  humidifier.autosizeRatedGasUseRate();
  EXPECT_TRUE(humidifier.isRatedGasUseRateAutosized());
  EXPECT_FALSE(humidifier.ratedGasUseRate());
  humidifier.resetRatedGasUseRate();
  EXPECT_FALSE(humidifier.ratedGasUseRate());
  EXPECT_FALSE(humidifier.isRatedGasUseRateAutosized());

  EXPECT_TRUE(humidifier.setThermalEfficiency(0.9));
  EXPECT_DOUBLE_EQ(0.9, humidifier.thermalEfficiency());
  EXPECT_FALSE(humidifier.isThermalEfficiencyDefaulted());
  humidifier.resetThermalEfficiency();
  EXPECT_DOUBLE_EQ(0.8, humidifier.thermalEfficiency());
  EXPECT_TRUE(humidifier.isThermalEfficiencyDefaulted());

  EXPECT_TRUE(humidifier.setRatedFanPower(110.0));
  ASSERT_TRUE(humidifier.ratedFanPower());
  EXPECT_DOUBLE_EQ(110.0, humidifier.ratedFanPower().get());
  humidifier.resetRatedFanPower();
  EXPECT_FALSE(humidifier.ratedFanPower());

  EXPECT_TRUE(humidifier.setAuxiliaryElectricPower(8.0));
  EXPECT_DOUBLE_EQ(8.0, humidifier.auxiliaryElectricPower());
  EXPECT_FALSE(humidifier.isAuxiliaryElectricPowerDefaulted());
  humidifier.resetAuxiliaryElectricPower();
  EXPECT_DOUBLE_EQ(0.0, humidifier.auxiliaryElectricPower());
  EXPECT_TRUE(humidifier.isAuxiliaryElectricPowerDefaulted());

  EXPECT_TRUE(humidifier.setInletWaterTemperatureOption("VariableInletWaterTemperature"));
  EXPECT_EQ("VariableInletWaterTemperature", humidifier.inletWaterTemperatureOption());
  EXPECT_FALSE(humidifier.isInletWaterTemperatureOptionDefaulted());
  humidifier.resetInletWaterTemperatureOption();
  EXPECT_EQ("FixedInletWaterTemperature", humidifier.inletWaterTemperatureOption());
  EXPECT_TRUE(humidifier.isInletWaterTemperatureOptionDefaulted());

  EXPECT_FALSE(humidifier.autosizedRatedCapacity());
  EXPECT_FALSE(humidifier.autosizedRatedGasUseRate());
}

TEST_F(EPModelFixture, HumidifierSteamGas_AvailabilitySchedule_RoundTripAndValidation) {
  Model model;
  HumidifierSteamGas humidifier(model);

  ScheduleCompact compactSchedule(model);
  ASSERT_TRUE(compactSchedule.setToConstantValue(0.5));
  EXPECT_TRUE(humidifier.setAvailabilitySchedule(compactSchedule));
  ASSERT_TRUE(humidifier.availabilitySchedule());
  EXPECT_EQ(compactSchedule.cast<ModelObject>(), humidifier.availabilitySchedule()->cast<ModelObject>());
  ASSERT_TRUE(compactSchedule.scheduleTypeLimits());
  EXPECT_EQ("Availability", compactSchedule.scheduleTypeLimits()->unitType());

  ScheduleConstant discreteAvailabilitySchedule(model);
  ASSERT_TRUE(discreteAvailabilitySchedule.setValue(1.0));
  ScheduleTypeLimits discreteAvailabilityLimits(model);
  ASSERT_TRUE(discreteAvailabilityLimits.setUnitType("Availability"));
  ASSERT_TRUE(discreteAvailabilityLimits.setNumericType("Discrete"));
  ASSERT_TRUE(discreteAvailabilityLimits.setLowerLimitValue(0.0));
  ASSERT_TRUE(discreteAvailabilityLimits.setUpperLimitValue(1.0));
  ASSERT_TRUE(discreteAvailabilitySchedule.setScheduleTypeLimits(discreteAvailabilityLimits));
  EXPECT_TRUE(humidifier.setAvailabilitySchedule(discreteAvailabilitySchedule));
  ASSERT_TRUE(humidifier.availabilitySchedule());
  EXPECT_EQ(discreteAvailabilitySchedule.cast<ModelObject>(), humidifier.availabilitySchedule()->cast<ModelObject>());

  ScheduleConstant wrongSchedule(model);
  ASSERT_TRUE(wrongSchedule.setValue(20.0));
  ScheduleTypeLimits temperatureLimits(model);
  ASSERT_TRUE(temperatureLimits.setUnitType("Temperature"));
  ASSERT_TRUE(wrongSchedule.setScheduleTypeLimits(temperatureLimits));
  EXPECT_FALSE(humidifier.setAvailabilitySchedule(wrongSchedule));
  ASSERT_TRUE(humidifier.availabilitySchedule());
  EXPECT_EQ(discreteAvailabilitySchedule.cast<ModelObject>(), humidifier.availabilitySchedule()->cast<ModelObject>());

  humidifier.resetAvailabilitySchedule();
  EXPECT_FALSE(humidifier.availabilitySchedule());
}

TEST_F(EPModelFixture, HumidifierSteamGas_AddToNodeSupplyOnlyAndClone) {
  Model model;
  AirLoopHVAC airLoop(model);
  HumidifierSteamGas supplyHumidifier(model);
  HumidifierSteamGas demandHumidifier(model);

  EXPECT_EQ(2u, airLoop.supplyComponents().size());

  auto supplyOutletNode = airLoop.supplyOutletNode();
  EXPECT_TRUE(supplyHumidifier.addToNode(supplyOutletNode));
  EXPECT_EQ(3u, airLoop.supplyComponents().size());
  EXPECT_EQ(1u, airLoop.supplyComponents(HumidifierSteamGas::iddObjectType()).size());
  ASSERT_TRUE(supplyHumidifier.airLoopHVAC());
  ASSERT_TRUE(supplyHumidifier.inletModelObject());
  ASSERT_TRUE(supplyHumidifier.outletModelObject());
  EXPECT_EQ(supplyOutletNode, supplyHumidifier.outletModelObject()->cast<Node>());

  auto demandBranchObject = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(demandBranchObject);
  auto demandBranchNode = demandBranchObject->optionalCast<Node>();
  ASSERT_TRUE(demandBranchNode);
  EXPECT_FALSE(demandHumidifier.addToNode(*demandBranchNode));
  EXPECT_FALSE(demandHumidifier.airLoopHVAC());

  Node unconnectedNode(model);
  EXPECT_FALSE(demandHumidifier.addToNode(unconnectedNode));

  PlantLoop plantLoop(model);
  auto plantSupplyOutletNode = plantLoop.supplyOutletNode();
  EXPECT_FALSE(demandHumidifier.addToNode(plantSupplyOutletNode));
  EXPECT_FALSE(demandHumidifier.plantLoop());

  auto plantDemandOutletNode = plantLoop.demandOutletNode();
  EXPECT_FALSE(demandHumidifier.addToNode(plantDemandOutletNode));
  EXPECT_FALSE(demandHumidifier.plantLoop());

  auto supplyHumidifierCloneObject = model.addObject(supplyHumidifier.idfObject());
  ASSERT_TRUE(supplyHumidifierCloneObject);
  auto supplyHumidifierClone = supplyHumidifierCloneObject->cast<HumidifierSteamGas>();

  supplyOutletNode = airLoop.supplyOutletNode();
  EXPECT_TRUE(supplyHumidifierClone.addToNode(supplyOutletNode));
  EXPECT_EQ(2u, airLoop.supplyComponents(HumidifierSteamGas::iddObjectType()).size());
  ASSERT_TRUE(supplyHumidifierClone.airLoopHVAC());
  ASSERT_TRUE(supplyHumidifierClone.inletModelObject());
  ASSERT_TRUE(supplyHumidifierClone.outletModelObject());
}

TEST_F(EPModelFixture, HumidifierSteamGas_AddToNodeSupportsOutboardOANodeAndReliefNode) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));

  auto outboardOANode = oaSystem.outboardOANode();
  ASSERT_TRUE(outboardOANode);

  HumidifierSteamGas oaHumidifier(model);
  EXPECT_TRUE(oaHumidifier.addToNode(*outboardOANode));
  ASSERT_TRUE(oaHumidifier.inletModelObject());
  EXPECT_EQ(*outboardOANode, oaHumidifier.inletModelObject()->cast<Node>());
  EXPECT_EQ(3u, oaSystem.oaComponents().size());

  auto outboardReliefNode = oaSystem.outboardReliefNode();
  ASSERT_TRUE(outboardReliefNode);

  HumidifierSteamGas reliefHumidifier(model);
  EXPECT_TRUE(reliefHumidifier.addToNode(*outboardReliefNode));
  ASSERT_TRUE(reliefHumidifier.outletModelObject());
  EXPECT_EQ(*outboardReliefNode, reliefHumidifier.outletModelObject()->cast<Node>());
  EXPECT_EQ(3u, oaSystem.reliefComponents().size());
}
