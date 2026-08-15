/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../HVACComponent/ThermalZone_Impl.hpp"
#include "../Curve/CurveBicubic.hpp"
#include "../Curve/CurveBiquadratic.hpp"
#include "../Curve/CurveBiquadratic_Impl.hpp"
#include "../Curve/CurveQuadratic.hpp"
#include "../StraightComponent/AirConditionerVariableRefrigerantFlow.hpp"
#include "../StraightComponent/AirConditionerVariableRefrigerantFlow_Impl.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../ModelObject/ModelObject_Impl.hpp"
#include "../ResourceObject/ScheduleTypeLimits.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../StraightComponent/Node.hpp"
#include "../ZoneHVACComponent/ZoneHVACTerminalUnitVariableRefrigerantFlow.hpp"
#include "../ZoneHVACComponent/ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl.hpp"

#include <utilities/core/Filesystem.hpp>
#include <utilities/core/UUID.hpp>
#include <utilities/idd/AirConditioner_VariableRefrigerantFlow_FieldEnums.hxx>
#include <utilities/idd/ZoneTerminalUnitList_FieldEnums.hxx>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>
#include <utilities/idf/IdfObject_Impl.hpp>
#include <utilities/idf/WorkspaceObject_Impl.hpp>

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

}  // namespace

TEST_F(EPModelFixture, AirConditionerVariableRefrigerantFlow_DefaultConstructor) {
  Model model;
  AirConditionerVariableRefrigerantFlow vrf(model);
  EXPECT_EQ(AirConditionerVariableRefrigerantFlow::iddObjectType(), vrf.iddObject().type());
  EXPECT_FALSE(vrf.nameString().empty());
  EXPECT_TRUE(vrf.isCondenserTypeDefaulted());
  EXPECT_EQ("AirCooled", vrf.condenserType());
  EXPECT_EQ(model.alwaysOnDiscreteSchedule().handle(), vrf.availabilitySchedule().handle());
  EXPECT_FALSE(vrf.zoneforMasterThermostatLocation());
  EXPECT_FALSE(vrf.thermostatPrioritySchedule());
  EXPECT_FALSE(vrf.basinHeaterOperatingSchedule());
  EXPECT_FALSE(vrf.defrostEnergyInputRatioModifierFunctionofTemperatureCurve());
  EXPECT_TRUE(vrf.terminals().empty());
  const auto lists = model.getObjectsByType(openstudio::IddObjectType::ZoneTerminalUnitList);
  ASSERT_EQ(1u, lists.size());
  auto list = vrf.getModelObjectTarget<ModelObject>(openstudio::AirConditioner_VariableRefrigerantFlowFields::ZoneTerminalUnitListName);
  ASSERT_TRUE(list);
  EXPECT_EQ(lists.front().handle(), list->handle());
}

TEST_F(EPModelFixture, AirConditionerVariableRefrigerantFlow_DefrostEIRModifierCurve) {
  const auto idfPath = uniqueIdfPath("epmodel-vrf-defrost-eir-curve");
  const ScopedFileRemoval removeIdf(idfPath);
  Model model;
  Model foreignModel;
  AirConditionerVariableRefrigerantFlow vrf(model);
  ZoneHVACTerminalUnitVariableRefrigerantFlow terminal(model);
  CurveBiquadratic initialCurve(model);
  CurveBiquadratic replacementCurve(model);
  CurveBicubic alternateAllowedCurve(model);
  CurveQuadratic disallowedCurve(model);
  CurveBiquadratic foreignCurve(foreignModel);
  ASSERT_TRUE(vrf.setName("Standard VRF Defrost EIR"));
  ASSERT_TRUE(terminal.setName("Standard VRF Defrost EIR Terminal"));
  ASSERT_TRUE(initialCurve.setName("Standard VRF Initial Defrost EIR"));
  ASSERT_TRUE(replacementCurve.setName("Standard VRF Replacement Defrost EIR"));
  ASSERT_TRUE(alternateAllowedCurve.setName("Standard VRF Alternate Defrost EIR"));
  ASSERT_TRUE(vrf.addTerminal(terminal));

  constexpr unsigned field = openstudio::AirConditioner_VariableRefrigerantFlowFields::DefrostEnergyInputRatioModifierFunctionofTemperatureCurveName;
  EXPECT_FALSE(vrf.defrostEnergyInputRatioModifierFunctionofTemperatureCurve());
  EXPECT_TRUE(vrf.setDefrostEnergyInputRatioModifierFunctionofTemperatureCurve(initialCurve));
  ASSERT_TRUE(vrf.defrostEnergyInputRatioModifierFunctionofTemperatureCurve());
  EXPECT_EQ(initialCurve, *vrf.defrostEnergyInputRatioModifierFunctionofTemperatureCurve());
  EXPECT_TRUE(vrf.setDefrostEnergyInputRatioModifierFunctionofTemperatureCurve(alternateAllowedCurve));
  ASSERT_TRUE(vrf.defrostEnergyInputRatioModifierFunctionofTemperatureCurve());
  EXPECT_EQ(alternateAllowedCurve, *vrf.defrostEnergyInputRatioModifierFunctionofTemperatureCurve());
  EXPECT_FALSE(vrf.setDefrostEnergyInputRatioModifierFunctionofTemperatureCurve(disallowedCurve));
  EXPECT_FALSE(vrf.setDefrostEnergyInputRatioModifierFunctionofTemperatureCurve(foreignCurve));
  ASSERT_TRUE(vrf.defrostEnergyInputRatioModifierFunctionofTemperatureCurve());
  EXPECT_EQ(alternateAllowedCurve, *vrf.defrostEnergyInputRatioModifierFunctionofTemperatureCurve());

  auto workspaceImpl = vrf.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(workspaceImpl);
  ASSERT_TRUE(workspaceImpl->setPointer(field, openstudio::Handle(), false));
  ASSERT_TRUE(workspaceImpl->openstudio::detail::IdfObject_Impl::setString(field, "Unresolved Standard VRF Defrost EIR", false));
  EXPECT_FALSE(vrf.defrostEnergyInputRatioModifierFunctionofTemperatureCurve());
  vrf.resetDefrostEnergyInputRatioModifierFunctionofTemperatureCurve();
  EXPECT_FALSE(vrf.defrostEnergyInputRatioModifierFunctionofTemperatureCurve());
  EXPECT_EQ("", workspaceImpl->openstudio::detail::IdfObject_Impl::getString(field, false, true).value_or(""));

  ASSERT_TRUE(vrf.setDefrostEnergyInputRatioModifierFunctionofTemperatureCurve(initialCurve));
  ASSERT_TRUE(model.save(idfPath, true));
  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedVRF = loadedModel->getConcreteModelObjectByName<AirConditionerVariableRefrigerantFlow>("Standard VRF Defrost EIR");
  auto loadedTerminal = loadedModel->getConcreteModelObjectByName<ZoneHVACTerminalUnitVariableRefrigerantFlow>("Standard VRF Defrost EIR Terminal");
  auto loadedInitialCurve = loadedModel->getConcreteModelObjectByName<CurveBiquadratic>("Standard VRF Initial Defrost EIR");
  auto loadedReplacementCurve = loadedModel->getConcreteModelObjectByName<CurveBiquadratic>("Standard VRF Replacement Defrost EIR");
  ASSERT_TRUE(loadedVRF);
  ASSERT_TRUE(loadedTerminal);
  ASSERT_TRUE(loadedInitialCurve);
  ASSERT_TRUE(loadedReplacementCurve);
  ASSERT_TRUE(loadedVRF->defrostEnergyInputRatioModifierFunctionofTemperatureCurve());
  EXPECT_EQ(*loadedInitialCurve, *loadedVRF->defrostEnergyInputRatioModifierFunctionofTemperatureCurve());
  ASSERT_TRUE(loadedVRF->setDefrostEnergyInputRatioModifierFunctionofTemperatureCurve(*loadedReplacementCurve));
  ASSERT_TRUE(loadedModel->save(idfPath, true));

  auto replacedModel = Model::load(idfPath);
  ASSERT_TRUE(replacedModel);
  auto replacedVRF = replacedModel->getConcreteModelObjectByName<AirConditionerVariableRefrigerantFlow>("Standard VRF Defrost EIR");
  auto replacedCurve = replacedModel->getConcreteModelObjectByName<CurveBiquadratic>("Standard VRF Replacement Defrost EIR");
  ASSERT_TRUE(replacedVRF);
  ASSERT_TRUE(replacedCurve);
  ASSERT_TRUE(replacedVRF->defrostEnergyInputRatioModifierFunctionofTemperatureCurve());
  EXPECT_EQ(*replacedCurve, *replacedVRF->defrostEnergyInputRatioModifierFunctionofTemperatureCurve());
  replacedVRF->resetDefrostEnergyInputRatioModifierFunctionofTemperatureCurve();
  ASSERT_TRUE(replacedModel->save(idfPath, true));

  auto resetModel = Model::load(idfPath);
  ASSERT_TRUE(resetModel);
  auto resetVRF = resetModel->getConcreteModelObjectByName<AirConditionerVariableRefrigerantFlow>("Standard VRF Defrost EIR");
  auto resetTerminal = resetModel->getConcreteModelObjectByName<ZoneHVACTerminalUnitVariableRefrigerantFlow>("Standard VRF Defrost EIR Terminal");
  ASSERT_TRUE(resetVRF);
  ASSERT_TRUE(resetTerminal);
  EXPECT_FALSE(resetVRF->defrostEnergyInputRatioModifierFunctionofTemperatureCurve());
  ASSERT_EQ(1u, resetVRF->terminals().size());
  EXPECT_EQ(*resetTerminal, resetVRF->terminals().front());
  auto terminalList = resetVRF->getModelObjectTarget<ModelObject>(openstudio::AirConditioner_VariableRefrigerantFlowFields::ZoneTerminalUnitListName);
  ASSERT_TRUE(terminalList);
  CurveBiquadratic retainedCurve(*resetModel);
  ASSERT_TRUE(resetVRF->setDefrostEnergyInputRatioModifierFunctionofTemperatureCurve(retainedCurve));
  EXPECT_FALSE(resetVRF->remove().empty());
  EXPECT_TRUE(resetModel->getObject(retainedCurve.handle()));
  EXPECT_TRUE(resetModel->getObject(resetTerminal->handle()));
  EXPECT_FALSE(resetTerminal->vrfSystem());
  EXPECT_FALSE(resetModel->getObject(terminalList->handle()));
}

TEST_F(EPModelFixture, AirConditionerVariableRefrigerantFlow_ScalarAccessors_RoundTrip) {
  Model model;
  AirConditionerVariableRefrigerantFlow vrf(model);

  EXPECT_TRUE(vrf.setGrossRatedTotalCoolingCapacity(12345.0));
  ASSERT_TRUE(vrf.grossRatedTotalCoolingCapacity());
  EXPECT_DOUBLE_EQ(12345.0, vrf.grossRatedTotalCoolingCapacity().get());
  EXPECT_FALSE(vrf.isGrossRatedTotalCoolingCapacityAutosized());

  vrf.autosizeGrossRatedTotalCoolingCapacity();
  EXPECT_TRUE(vrf.isGrossRatedTotalCoolingCapacityAutosized());

  EXPECT_TRUE(vrf.setGrossRatedCoolingCOP(3.4));
  EXPECT_DOUBLE_EQ(3.4, vrf.grossRatedCoolingCOP());

  EXPECT_TRUE(vrf.setGrossRatedHeatingCapacity(9876.0));
  ASSERT_TRUE(vrf.grossRatedHeatingCapacity());
  EXPECT_DOUBLE_EQ(9876.0, vrf.grossRatedHeatingCapacity().get());
  EXPECT_FALSE(vrf.isGrossRatedHeatingCapacityAutosized());

  vrf.autosizeGrossRatedHeatingCapacity();
  EXPECT_TRUE(vrf.isGrossRatedHeatingCapacityAutosized());

  EXPECT_TRUE(vrf.setRatedHeatingCapacitySizingRatio(1.15));
  EXPECT_DOUBLE_EQ(1.15, vrf.ratedHeatingCapacitySizingRatio());

  const auto heatingValues = AirConditionerVariableRefrigerantFlow::heatingPerformanceCurveOutdoorTemperatureTypeValues();
  ASSERT_FALSE(heatingValues.empty());
  EXPECT_TRUE(vrf.setHeatingPerformanceCurveOutdoorTemperatureType(heatingValues.front()));
  EXPECT_EQ(heatingValues.front(), vrf.heatingPerformanceCurveOutdoorTemperatureType());

  EXPECT_TRUE(vrf.setHeatPumpWasteHeatRecovery(true));
  EXPECT_TRUE(vrf.heatPumpWasteHeatRecovery());
  EXPECT_TRUE(vrf.setHeatPumpWasteHeatRecovery(false));
  EXPECT_FALSE(vrf.heatPumpWasteHeatRecovery());

  EXPECT_TRUE(vrf.setNumberofCompressors(3));
  EXPECT_EQ(3, vrf.numberofCompressors());

  const auto defrostValues = AirConditionerVariableRefrigerantFlow::defrostStrategyValues();
  ASSERT_FALSE(defrostValues.empty());
  EXPECT_TRUE(vrf.setDefrostStrategy(defrostValues.front()));
  EXPECT_EQ(defrostValues.front(), vrf.defrostStrategy());

  const auto condenserValues = AirConditionerVariableRefrigerantFlow::condenserTypeValues();
  ASSERT_FALSE(condenserValues.empty());
  EXPECT_TRUE(vrf.setCondenserType(condenserValues.front()));
  EXPECT_FALSE(vrf.isCondenserTypeDefaulted());
  EXPECT_EQ(condenserValues.front(), vrf.condenserType());
  vrf.resetCondenserType();
  EXPECT_TRUE(vrf.isCondenserTypeDefaulted());
  EXPECT_EQ("AirCooled", vrf.condenserType());
}

TEST_F(EPModelFixture, AirConditionerVariableRefrigerantFlow_ControlRelationshipsValidateAndResetExactly) {
  Model model;
  AirConditionerVariableRefrigerantFlow vrf(model);

  ScheduleTypeLimits availabilityLimits(model);
  ASSERT_TRUE(availabilityLimits.setNumericType("Discrete"));
  ASSERT_TRUE(availabilityLimits.setUnitType("Availability"));
  ASSERT_TRUE(availabilityLimits.setLowerLimitValue(0.0));
  ASSERT_TRUE(availabilityLimits.setUpperLimitValue(1.0));
  ScheduleConstant availability(model);
  ScheduleConstant basin(model);
  ASSERT_TRUE(availability.setScheduleTypeLimits(availabilityLimits));
  ASSERT_TRUE(basin.setScheduleTypeLimits(availabilityLimits));

  ScheduleTypeLimits controlModeLimits(model);
  ASSERT_TRUE(controlModeLimits.setNumericType("Discrete"));
  ASSERT_TRUE(controlModeLimits.setUnitType("ControlMode"));
  ASSERT_TRUE(controlModeLimits.setLowerLimitValue(0.0));
  ASSERT_TRUE(controlModeLimits.setUpperLimitValue(1.0));
  ScheduleConstant priority(model);
  ASSERT_TRUE(priority.setScheduleTypeLimits(controlModeLimits));

  ThermalZone zone(model);
  ASSERT_TRUE(vrf.setAvailabilitySchedule(availability));
  ASSERT_TRUE(vrf.setThermostatPrioritySchedule(priority));
  ASSERT_TRUE(vrf.setBasinHeaterOperatingSchedule(basin));
  ASSERT_TRUE(vrf.setZoneforMasterThermostatLocation(zone));
  EXPECT_EQ(availability.handle(), vrf.availabilitySchedule().handle());
  ASSERT_TRUE(vrf.thermostatPrioritySchedule());
  ASSERT_TRUE(vrf.basinHeaterOperatingSchedule());
  ASSERT_TRUE(vrf.zoneforMasterThermostatLocation());
  EXPECT_EQ(priority.handle(), vrf.thermostatPrioritySchedule()->handle());
  EXPECT_EQ(basin.handle(), vrf.basinHeaterOperatingSchedule()->handle());
  EXPECT_EQ(zone.handle(), vrf.zoneforMasterThermostatLocation()->handle());

  ScheduleTypeLimits incompatibleLimits(model);
  ASSERT_TRUE(incompatibleLimits.setNumericType("Continuous"));
  ASSERT_TRUE(incompatibleLimits.setUnitType("Temperature"));
  ScheduleConstant incompatible(model);
  ASSERT_TRUE(incompatible.setScheduleTypeLimits(incompatibleLimits));
  EXPECT_FALSE(vrf.setAvailabilitySchedule(incompatible));
  EXPECT_FALSE(vrf.setThermostatPrioritySchedule(incompatible));
  EXPECT_FALSE(vrf.setBasinHeaterOperatingSchedule(incompatible));
  EXPECT_EQ(availability.handle(), vrf.availabilitySchedule().handle());
  EXPECT_EQ(priority.handle(), vrf.thermostatPrioritySchedule()->handle());
  EXPECT_EQ(basin.handle(), vrf.basinHeaterOperatingSchedule()->handle());

  Model foreignModel;
  ScheduleConstant foreignSchedule(foreignModel);
  ThermalZone foreignZone(foreignModel);
  EXPECT_FALSE(vrf.setAvailabilitySchedule(foreignSchedule));
  EXPECT_FALSE(vrf.setThermostatPrioritySchedule(foreignSchedule));
  EXPECT_FALSE(vrf.setBasinHeaterOperatingSchedule(foreignSchedule));
  EXPECT_FALSE(vrf.setZoneforMasterThermostatLocation(foreignZone));
  EXPECT_EQ(availability.handle(), vrf.availabilitySchedule().handle());
  EXPECT_EQ(priority.handle(), vrf.thermostatPrioritySchedule()->handle());
  EXPECT_EQ(basin.handle(), vrf.basinHeaterOperatingSchedule()->handle());
  EXPECT_EQ(zone.handle(), vrf.zoneforMasterThermostatLocation()->handle());

  AirConditionerVariableRefrigerantFlow unresolved(model);
  auto unresolvedImpl = unresolved.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(unresolvedImpl);
  const auto setUnresolvedRaw = [&](unsigned field, const std::string& value) {
    ASSERT_TRUE(unresolvedImpl->setPointer(field, openstudio::Handle(), false));
    ASSERT_TRUE(unresolvedImpl->openstudio::detail::IdfObject_Impl::setString(field, value, false));
  };
  const auto rawValue = [&](unsigned field) {
    return unresolvedImpl->openstudio::detail::IdfObject_Impl::getString(field, false, true).value_or("");
  };
  constexpr unsigned availabilityField = openstudio::AirConditioner_VariableRefrigerantFlowFields::AvailabilityScheduleName;
  constexpr unsigned priorityField = openstudio::AirConditioner_VariableRefrigerantFlowFields::ThermostatPriorityScheduleName;
  constexpr unsigned basinField = openstudio::AirConditioner_VariableRefrigerantFlowFields::BasinHeaterOperatingScheduleName;
  constexpr unsigned zoneField = openstudio::AirConditioner_VariableRefrigerantFlowFields::ZoneNameforMasterThermostatLocation;
  setUnresolvedRaw(availabilityField, "Missing VRF Availability");
  setUnresolvedRaw(priorityField, "Missing VRF Thermostat Priority");
  setUnresolvedRaw(basinField, "Missing VRF Basin Schedule");
  setUnresolvedRaw(zoneField, "Missing VRF Master Zone");
  EXPECT_FALSE(unresolved.setAvailabilitySchedule(incompatible));
  EXPECT_FALSE(unresolved.setThermostatPrioritySchedule(incompatible));
  EXPECT_FALSE(unresolved.setBasinHeaterOperatingSchedule(incompatible));
  EXPECT_FALSE(unresolved.setZoneforMasterThermostatLocation(foreignZone));
  EXPECT_EQ("Missing VRF Availability", rawValue(availabilityField));
  EXPECT_EQ("Missing VRF Thermostat Priority", rawValue(priorityField));
  EXPECT_EQ("Missing VRF Basin Schedule", rawValue(basinField));
  EXPECT_EQ("Missing VRF Master Zone", rawValue(zoneField));

  vrf.resetThermostatPrioritySchedule();
  vrf.resetBasinHeaterOperatingSchedule();
  vrf.resetZoneforMasterThermostatLocation();
  EXPECT_FALSE(vrf.thermostatPrioritySchedule());
  EXPECT_FALSE(vrf.basinHeaterOperatingSchedule());
  EXPECT_FALSE(vrf.zoneforMasterThermostatLocation());
  auto vrfImpl = vrf.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(vrfImpl);
  EXPECT_EQ("", vrfImpl->openstudio::detail::IdfObject_Impl::getString(priorityField, false, true).value_or(""));
  EXPECT_EQ("", vrfImpl->openstudio::detail::IdfObject_Impl::getString(basinField, false, true).value_or(""));
  EXPECT_EQ("", vrfImpl->openstudio::detail::IdfObject_Impl::getString(zoneField, false, true).value_or(""));
}

TEST_F(EPModelFixture, AirConditionerVariableRefrigerantFlow_CanonicalizationRepairsOnlyBlankAvailability) {
  const auto idfPath = uniqueIdfPath("epmodel-vrf-availability-repair");
  const ScopedFileRemoval removeIdf(idfPath);

  Model model;
  AirConditionerVariableRefrigerantFlow blank(model);
  AirConditionerVariableRefrigerantFlow unresolved(model);
  ASSERT_TRUE(blank.setName("Blank VRF Availability"));
  ASSERT_TRUE(unresolved.setName("Unresolved VRF Availability"));

  constexpr unsigned field = openstudio::AirConditioner_VariableRefrigerantFlowFields::AvailabilityScheduleName;
  auto blankImpl = blank.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  auto unresolvedImpl = unresolved.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(blankImpl);
  ASSERT_TRUE(unresolvedImpl);
  ASSERT_TRUE(blankImpl->setPointer(field, openstudio::Handle(), false));
  ASSERT_TRUE(blankImpl->openstudio::detail::IdfObject_Impl::setString(field, "", false));
  ASSERT_TRUE(unresolvedImpl->setPointer(field, openstudio::Handle(), false));
  ASSERT_TRUE(unresolvedImpl->openstudio::detail::IdfObject_Impl::setString(field, "Missing VRF Availability", false));

  const auto report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);
  EXPECT_GE(report.infoCount, 1u);
  EXPECT_EQ(model.alwaysOnDiscreteSchedule().handle(), blank.availabilitySchedule().handle());
  EXPECT_EQ("Missing VRF Availability", unresolvedImpl->openstudio::detail::IdfObject_Impl::getString(field, false, true).value_or(""));

  Model reloadSource;
  AirConditionerVariableRefrigerantFlow blankOnLoad(reloadSource);
  ASSERT_TRUE(blankOnLoad.setName("Blank VRF Availability On Load"));
  auto blankOnLoadImpl = blankOnLoad.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(blankOnLoadImpl);
  ASSERT_TRUE(blankOnLoadImpl->setPointer(field, openstudio::Handle(), false));
  ASSERT_TRUE(blankOnLoadImpl->openstudio::detail::IdfObject_Impl::setString(field, "", false));
  ASSERT_TRUE(reloadSource.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedBlank = loadedModel->getConcreteModelObjectByName<AirConditionerVariableRefrigerantFlow>("Blank VRF Availability On Load");
  ASSERT_TRUE(loadedBlank);
  EXPECT_EQ(loadedModel->alwaysOnDiscreteSchedule().handle(), loadedBlank->availabilitySchedule().handle());
}

TEST_F(EPModelFixture, AirConditionerVariableRefrigerantFlow_ControlRelationshipsSurviveReloadMutationResetAndRemoval) {
  const auto firstIdfPath = uniqueIdfPath("epmodel-vrf-relationships-first");
  const auto secondIdfPath = uniqueIdfPath("epmodel-vrf-relationships-second");
  const ScopedFileRemoval removeFirstIdf(firstIdfPath);
  const ScopedFileRemoval removeSecondIdf(secondIdfPath);

  Model model;
  ScheduleTypeLimits availabilityLimits(model);
  ASSERT_TRUE(availabilityLimits.setName("VRF Availability Limits"));
  ASSERT_TRUE(availabilityLimits.setNumericType("Discrete"));
  ASSERT_TRUE(availabilityLimits.setUnitType("Availability"));
  ASSERT_TRUE(availabilityLimits.setLowerLimitValue(0.0));
  ASSERT_TRUE(availabilityLimits.setUpperLimitValue(1.0));
  ScheduleTypeLimits controlModeLimits(model);
  ASSERT_TRUE(controlModeLimits.setName("VRF Control Mode Limits"));
  ASSERT_TRUE(controlModeLimits.setNumericType("Discrete"));
  ASSERT_TRUE(controlModeLimits.setUnitType("ControlMode"));
  ASSERT_TRUE(controlModeLimits.setLowerLimitValue(0.0));
  ASSERT_TRUE(controlModeLimits.setUpperLimitValue(1.0));

  ScheduleConstant availability(model);
  ScheduleConstant priority(model);
  ScheduleConstant basin(model);
  ASSERT_TRUE(availability.setName("Shared VRF Availability"));
  ASSERT_TRUE(priority.setName("Shared VRF Thermostat Priority"));
  ASSERT_TRUE(basin.setName("Shared VRF Basin Schedule"));
  ASSERT_TRUE(availability.setScheduleTypeLimits(availabilityLimits));
  ASSERT_TRUE(priority.setScheduleTypeLimits(controlModeLimits));
  ASSERT_TRUE(basin.setScheduleTypeLimits(availabilityLimits));
  ThermalZone zone(model);
  ASSERT_TRUE(zone.setName("Shared VRF Master Zone"));

  AirConditionerVariableRefrigerantFlow first(model);
  AirConditionerVariableRefrigerantFlow second(model);
  ASSERT_TRUE(first.setName("First Relationship VRF"));
  ASSERT_TRUE(second.setName("Second Relationship VRF"));
  for (auto* vrf : {&first, &second}) {
    ASSERT_TRUE(vrf->setAvailabilitySchedule(availability));
    ASSERT_TRUE(vrf->setThermostatPrioritySchedule(priority));
    ASSERT_TRUE(vrf->setBasinHeaterOperatingSchedule(basin));
    ASSERT_TRUE(vrf->setZoneforMasterThermostatLocation(zone));
  }
  ASSERT_TRUE(model.save(firstIdfPath, true));

  auto loadedModel = Model::load(firstIdfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedFirst = loadedModel->getConcreteModelObjectByName<AirConditionerVariableRefrigerantFlow>("First Relationship VRF");
  auto loadedSecond = loadedModel->getConcreteModelObjectByName<AirConditionerVariableRefrigerantFlow>("Second Relationship VRF");
  auto loadedAvailability = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("Shared VRF Availability");
  auto loadedPriority = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("Shared VRF Thermostat Priority");
  auto loadedBasin = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("Shared VRF Basin Schedule");
  auto loadedZone = loadedModel->getConcreteModelObjectByName<ThermalZone>("Shared VRF Master Zone");
  ASSERT_TRUE(loadedFirst);
  ASSERT_TRUE(loadedSecond);
  ASSERT_TRUE(loadedAvailability);
  ASSERT_TRUE(loadedPriority);
  ASSERT_TRUE(loadedBasin);
  ASSERT_TRUE(loadedZone);
  EXPECT_EQ(loadedAvailability->handle(), loadedFirst->availabilitySchedule().handle());
  EXPECT_EQ(loadedAvailability->handle(), loadedSecond->availabilitySchedule().handle());
  ASSERT_TRUE(loadedFirst->thermostatPrioritySchedule());
  ASSERT_TRUE(loadedFirst->basinHeaterOperatingSchedule());
  ASSERT_TRUE(loadedFirst->zoneforMasterThermostatLocation());
  ASSERT_TRUE(loadedSecond->thermostatPrioritySchedule());
  ASSERT_TRUE(loadedSecond->basinHeaterOperatingSchedule());
  ASSERT_TRUE(loadedSecond->zoneforMasterThermostatLocation());
  EXPECT_EQ(loadedPriority->handle(), loadedFirst->thermostatPrioritySchedule()->handle());
  EXPECT_EQ(loadedBasin->handle(), loadedFirst->basinHeaterOperatingSchedule()->handle());
  EXPECT_EQ(loadedZone->handle(), loadedFirst->zoneforMasterThermostatLocation()->handle());
  EXPECT_EQ(loadedPriority->handle(), loadedSecond->thermostatPrioritySchedule()->handle());
  EXPECT_EQ(loadedBasin->handle(), loadedSecond->basinHeaterOperatingSchedule()->handle());
  EXPECT_EQ(loadedZone->handle(), loadedSecond->zoneforMasterThermostatLocation()->handle());

  ScheduleTypeLimits replacementAvailabilityLimits(*loadedModel);
  ASSERT_TRUE(replacementAvailabilityLimits.setNumericType("Discrete"));
  ASSERT_TRUE(replacementAvailabilityLimits.setUnitType("Availability"));
  ASSERT_TRUE(replacementAvailabilityLimits.setLowerLimitValue(0.0));
  ASSERT_TRUE(replacementAvailabilityLimits.setUpperLimitValue(1.0));
  ScheduleTypeLimits replacementControlModeLimits(*loadedModel);
  ASSERT_TRUE(replacementControlModeLimits.setNumericType("Discrete"));
  ASSERT_TRUE(replacementControlModeLimits.setUnitType("ControlMode"));
  ASSERT_TRUE(replacementControlModeLimits.setLowerLimitValue(0.0));
  ASSERT_TRUE(replacementControlModeLimits.setUpperLimitValue(1.0));
  ScheduleConstant replacementAvailability(*loadedModel);
  ScheduleConstant replacementPriority(*loadedModel);
  ScheduleConstant replacementBasin(*loadedModel);
  ASSERT_TRUE(replacementAvailability.setName("Replacement VRF Availability"));
  ASSERT_TRUE(replacementPriority.setName("Replacement VRF Thermostat Priority"));
  ASSERT_TRUE(replacementBasin.setName("Replacement VRF Basin Schedule"));
  ASSERT_TRUE(replacementAvailability.setScheduleTypeLimits(replacementAvailabilityLimits));
  ASSERT_TRUE(replacementPriority.setScheduleTypeLimits(replacementControlModeLimits));
  ASSERT_TRUE(replacementBasin.setScheduleTypeLimits(replacementAvailabilityLimits));
  ThermalZone replacementZone(*loadedModel);
  ASSERT_TRUE(replacementZone.setName("Replacement VRF Master Zone"));
  ASSERT_TRUE(loadedFirst->setAvailabilitySchedule(replacementAvailability));
  ASSERT_TRUE(loadedFirst->setThermostatPrioritySchedule(replacementPriority));
  ASSERT_TRUE(loadedFirst->setBasinHeaterOperatingSchedule(replacementBasin));
  ASSERT_TRUE(loadedFirst->setZoneforMasterThermostatLocation(replacementZone));
  loadedFirst->resetThermostatPrioritySchedule();
  loadedFirst->resetBasinHeaterOperatingSchedule();
  loadedFirst->resetZoneforMasterThermostatLocation();
  ASSERT_TRUE(loadedModel->save(secondIdfPath, true));

  auto reloadedModel = Model::load(secondIdfPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedFirst = reloadedModel->getConcreteModelObjectByName<AirConditionerVariableRefrigerantFlow>("First Relationship VRF");
  auto reloadedSecond = reloadedModel->getConcreteModelObjectByName<AirConditionerVariableRefrigerantFlow>("Second Relationship VRF");
  auto reloadedOriginalAvailability = reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Shared VRF Availability");
  auto reloadedOriginalPriority = reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Shared VRF Thermostat Priority");
  auto reloadedOriginalBasin = reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Shared VRF Basin Schedule");
  auto reloadedOriginalZone = reloadedModel->getConcreteModelObjectByName<ThermalZone>("Shared VRF Master Zone");
  auto reloadedReplacementAvailability = reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Replacement VRF Availability");
  auto reloadedReplacementPriority = reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Replacement VRF Thermostat Priority");
  auto reloadedReplacementBasin = reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Replacement VRF Basin Schedule");
  auto reloadedReplacementZone = reloadedModel->getConcreteModelObjectByName<ThermalZone>("Replacement VRF Master Zone");
  ASSERT_TRUE(reloadedFirst);
  ASSERT_TRUE(reloadedSecond);
  ASSERT_TRUE(reloadedOriginalAvailability);
  ASSERT_TRUE(reloadedOriginalPriority);
  ASSERT_TRUE(reloadedOriginalBasin);
  ASSERT_TRUE(reloadedOriginalZone);
  ASSERT_TRUE(reloadedReplacementAvailability);
  ASSERT_TRUE(reloadedReplacementPriority);
  ASSERT_TRUE(reloadedReplacementBasin);
  ASSERT_TRUE(reloadedReplacementZone);
  EXPECT_EQ(reloadedReplacementAvailability->handle(), reloadedFirst->availabilitySchedule().handle());
  EXPECT_FALSE(reloadedFirst->thermostatPrioritySchedule());
  EXPECT_FALSE(reloadedFirst->basinHeaterOperatingSchedule());
  EXPECT_FALSE(reloadedFirst->zoneforMasterThermostatLocation());
  EXPECT_EQ(reloadedOriginalAvailability->handle(), reloadedSecond->availabilitySchedule().handle());
  ASSERT_TRUE(reloadedSecond->thermostatPrioritySchedule());
  ASSERT_TRUE(reloadedSecond->basinHeaterOperatingSchedule());
  ASSERT_TRUE(reloadedSecond->zoneforMasterThermostatLocation());
  EXPECT_EQ(reloadedOriginalPriority->handle(), reloadedSecond->thermostatPrioritySchedule()->handle());
  EXPECT_EQ(reloadedOriginalBasin->handle(), reloadedSecond->basinHeaterOperatingSchedule()->handle());
  EXPECT_EQ(reloadedOriginalZone->handle(), reloadedSecond->zoneforMasterThermostatLocation()->handle());

  EXPECT_FALSE(reloadedFirst->remove().empty());
  EXPECT_TRUE(reloadedModel->getObject(reloadedReplacementAvailability->handle()));
  EXPECT_TRUE(reloadedModel->getObject(reloadedReplacementPriority->handle()));
  EXPECT_TRUE(reloadedModel->getObject(reloadedReplacementBasin->handle()));
  EXPECT_TRUE(reloadedModel->getObject(reloadedReplacementZone->handle()));
  EXPECT_FALSE(reloadedSecond->remove().empty());
  EXPECT_TRUE(reloadedModel->getObject(reloadedOriginalAvailability->handle()));
  EXPECT_TRUE(reloadedModel->getObject(reloadedOriginalPriority->handle()));
  EXPECT_TRUE(reloadedModel->getObject(reloadedOriginalBasin->handle()));
  EXPECT_TRUE(reloadedModel->getObject(reloadedOriginalZone->handle()));
}

TEST_F(EPModelFixture, AirConditionerVariableRefrigerantFlow_AddToNode_DemandSideDefaultedCondenserType) {
  Model model;
  PlantLoop plantLoop(model);
  AirConditionerVariableRefrigerantFlow vrf(model);

  Node supplyOutletNode = plantLoop.supplyOutletNode();
  EXPECT_FALSE(vrf.addToNode(supplyOutletNode));
  EXPECT_FALSE(vrf.plantLoop());
  EXPECT_TRUE(vrf.isCondenserTypeDefaulted());
  EXPECT_EQ("AirCooled", vrf.condenserType());

  Node demandOutletNode = plantLoop.demandOutletNode();
  EXPECT_TRUE(vrf.addToNode(demandOutletNode));
  EXPECT_TRUE(vrf.plantLoop());
  EXPECT_TRUE(vrf.isCondenserTypeDefaulted());
  EXPECT_EQ("WaterCooled", vrf.condenserType());
  EXPECT_EQ(7u, plantLoop.demandComponents().size());
  EXPECT_EQ(1u, plantLoop.demandComponents(AirConditionerVariableRefrigerantFlow::iddObjectType()).size());

  ASSERT_TRUE(vrf.inletModelObject());
  ASSERT_TRUE(vrf.outletModelObject());
  EXPECT_NE(vrf.inletModelObject()->handle(), vrf.outletModelObject()->handle());
  EXPECT_EQ(demandOutletNode.handle(), vrf.outletModelObject()->handle());
  EXPECT_EQ(1u, plantLoop
                  .demandComponents(vrf.inletModelObject()->cast<Node>(), vrf.outletModelObject()->cast<Node>(),
                                    AirConditionerVariableRefrigerantFlow::iddObjectType())
                  .size());

  EXPECT_TRUE(vrf.removeFromLoop());
  EXPECT_FALSE(vrf.plantLoop());
  EXPECT_TRUE(vrf.isCondenserTypeDefaulted());
  EXPECT_EQ("AirCooled", vrf.condenserType());
  EXPECT_EQ(5u, plantLoop.demandComponents().size());
}

TEST_F(EPModelFixture, AirConditionerVariableRefrigerantFlow_TerminalRelationshipIsExclusiveAndRenameSafe) {
  Model model;
  AirConditionerVariableRefrigerantFlow first(model);
  AirConditionerVariableRefrigerantFlow second(model);
  ZoneHVACTerminalUnitVariableRefrigerantFlow terminal(model);

  ASSERT_TRUE(first.setName("First VRF Outdoor Unit"));
  ASSERT_TRUE(second.setName("Second VRF Outdoor Unit"));
  ASSERT_TRUE(terminal.setName("VRF Indoor Terminal"));
  EXPECT_TRUE(first.addTerminal(terminal));
  EXPECT_TRUE(first.addTerminal(terminal));
  ASSERT_EQ(1u, first.terminals().size());
  EXPECT_EQ(terminal.handle(), first.terminals().front().handle());
  ASSERT_TRUE(terminal.vrfSystem());
  EXPECT_EQ(first.handle(), terminal.vrfSystem()->handle());

  EXPECT_FALSE(second.addTerminal(terminal));
  EXPECT_TRUE(second.terminals().empty());
  ASSERT_TRUE(terminal.vrfSystem());
  EXPECT_EQ(first.handle(), terminal.vrfSystem()->handle());

  ASSERT_TRUE(terminal.setName("Renamed VRF Indoor Terminal"));
  ASSERT_EQ(1u, first.terminals().size());
  EXPECT_EQ(terminal.handle(), first.terminals().front().handle());
  auto list = first.getModelObjectTarget<ModelObject>(openstudio::AirConditioner_VariableRefrigerantFlowFields::ZoneTerminalUnitListName);
  ASSERT_TRUE(list);
  ASSERT_EQ(1u, list->extensibleGroups().size());
  auto group = list->extensibleGroups().front().optionalCast<openstudio::WorkspaceExtensibleGroup>();
  ASSERT_TRUE(group);
  auto target = group->getTarget(openstudio::ZoneTerminalUnitListExtensibleFields::ZoneTerminalUnitName);
  ASSERT_TRUE(target);
  EXPECT_EQ(terminal.handle(), target->handle());

  first.removeTerminal(terminal);
  EXPECT_TRUE(first.terminals().empty());
  EXPECT_FALSE(terminal.vrfSystem());
  EXPECT_TRUE(second.addTerminal(terminal));
  ASSERT_TRUE(terminal.vrfSystem());
  EXPECT_EQ(second.handle(), terminal.vrfSystem()->handle());
  second.removeAllTerminals();
  EXPECT_TRUE(second.terminals().empty());
  EXPECT_FALSE(terminal.vrfSystem());
}

TEST_F(EPModelFixture, AirConditionerVariableRefrigerantFlow_TerminalRelationshipRejectsForeignAndFluidControlTerminals) {
  Model model;
  Model foreignModel;
  AirConditionerVariableRefrigerantFlow system(model);
  ZoneHVACTerminalUnitVariableRefrigerantFlow foreignTerminal(foreignModel);
  ZoneHVACTerminalUnitVariableRefrigerantFlow fluidTerminal(model, true);

  EXPECT_FALSE(system.addTerminal(foreignTerminal));
  EXPECT_FALSE(system.addTerminal(fluidTerminal));
  EXPECT_TRUE(system.terminals().empty());
  EXPECT_FALSE(fluidTerminal.vrfSystem());
}

TEST_F(EPModelFixture, AirConditionerVariableRefrigerantFlow_TerminalRelationshipSurvivesReload) {
  const auto idfPath = uniqueIdfPath("epmodel-vrf-terminal-list-roundtrip");
  const ScopedFileRemoval removeIdf(idfPath);

  Model model;
  AirConditionerVariableRefrigerantFlow system(model);
  ZoneHVACTerminalUnitVariableRefrigerantFlow terminal(model);
  ASSERT_TRUE(system.setName("Roundtrip VRF Outdoor Unit"));
  ASSERT_TRUE(terminal.setName("Roundtrip VRF Indoor Terminal"));
  ASSERT_TRUE(system.addTerminal(terminal));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedSystem = loadedModel->getConcreteModelObjectByName<AirConditionerVariableRefrigerantFlow>("Roundtrip VRF Outdoor Unit");
  auto loadedTerminal = loadedModel->getConcreteModelObjectByName<ZoneHVACTerminalUnitVariableRefrigerantFlow>("Roundtrip VRF Indoor Terminal");
  ASSERT_TRUE(loadedSystem);
  ASSERT_TRUE(loadedTerminal);
  ASSERT_EQ(1u, loadedSystem->terminals().size());
  EXPECT_EQ(loadedTerminal->handle(), loadedSystem->terminals().front().handle());
  ASSERT_TRUE(loadedTerminal->vrfSystem());
  EXPECT_EQ(loadedSystem->handle(), loadedTerminal->vrfSystem()->handle());
  EXPECT_EQ(1u, loadedModel->getObjectsByType(openstudio::IddObjectType::ZoneTerminalUnitList).size());
}

TEST_F(EPModelFixture, AirConditionerVariableRefrigerantFlow_TerminalAndSystemRemovalOwnOnlyTheirTopology) {
  Model model;
  AirConditionerVariableRefrigerantFlow firstSystem(model);
  AirConditionerVariableRefrigerantFlow secondSystem(model);
  ZoneHVACTerminalUnitVariableRefrigerantFlow firstTerminal(model);
  ZoneHVACTerminalUnitVariableRefrigerantFlow secondTerminal(model);
  ASSERT_TRUE(firstSystem.addTerminal(firstTerminal));
  ASSERT_TRUE(secondSystem.addTerminal(secondTerminal));

  const auto firstTerminalHandle = firstTerminal.handle();
  EXPECT_FALSE(firstTerminal.remove().empty());
  EXPECT_FALSE(model.getObject(firstTerminalHandle));
  EXPECT_TRUE(firstSystem.terminals().empty());
  EXPECT_EQ(1u, secondSystem.terminals().size());
  EXPECT_EQ(2u, model.getObjectsByType(openstudio::IddObjectType::ZoneTerminalUnitList).size());

  const auto secondSystemHandle = secondSystem.handle();
  EXPECT_FALSE(secondSystem.remove().empty());
  EXPECT_FALSE(model.getObject(secondSystemHandle));
  EXPECT_TRUE(model.getObject(secondTerminal.handle()));
  EXPECT_FALSE(secondTerminal.vrfSystem());
  EXPECT_EQ(1u, model.getObjectsByType(openstudio::IddObjectType::ZoneTerminalUnitList).size());
}
