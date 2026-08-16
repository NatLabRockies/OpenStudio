/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Curve/CurveBiquadratic.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../ParentObject/RefrigerationCondenserAirCooled.hpp"
#include "../ResourceObject/ScheduleTypeLimits.hpp"
#include "../Schedule/Schedule.hpp"
#include "../Schedule/Schedule_Impl.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../StraightComponent/CoilWaterHeatingDesuperheater.hpp"
#include "../StraightComponent/CoilWaterHeatingDesuperheater_Impl.hpp"
#include "../StraightComponent/Node.hpp"

#include <utilities/core/Filesystem.hpp>
#include <utilities/core/UUID.hpp>
#include <utilities/idd/Coil_WaterHeating_Desuperheater_FieldEnums.hxx>
#include <utilities/idf/IdfObject_Impl.hpp>
#include <utilities/idf/WorkspaceObject_Impl.hpp>

#include <array>
#include <utility>

using namespace openstudio::epmodel;

namespace {

class ScopedDesuperheaterFileRemoval
{
 public:
  explicit ScopedDesuperheaterFileRemoval(openstudio::path path) : m_path(std::move(path)) {}

  ~ScopedDesuperheaterFileRemoval() {
    boost::system::error_code error;
    boost::filesystem::remove(m_path, error);
  }

 private:
  openstudio::path m_path;
};

openstudio::path uniqueDesuperheaterPath(const std::string& stem) {
  return openstudio::tempDir() / openstudio::toPath(stem + "-" + openstudio::removeBraces(openstudio::createUUID()) + ".idf");
}

}  // namespace

TEST_F(EPModelFixture, CoilWaterHeatingDesuperheater_DefaultConstructor) {
  Model model;
  CoilWaterHeatingDesuperheater coil(model);
  EXPECT_EQ(CoilWaterHeatingDesuperheater::iddObjectType(), coil.iddObject().type());
  EXPECT_FALSE(coil.nameString().empty());
  EXPECT_EQ(model.alwaysOnDiscreteSchedule().handle(), coil.availabilitySchedule().handle());

  EXPECT_DOUBLE_EQ(5.0, coil.deadBandTemperatureDifference());
  EXPECT_FALSE(coil.isDeadBandTemperatureDifferenceDefaulted());
  EXPECT_FALSE(coil.ratedHeatReclaimRecoveryEfficiency());
  EXPECT_FALSE(coil.heatReclaimEfficiencyFunctionofTemperatureCurve());
  EXPECT_FALSE(coil.heatingSource());

  EXPECT_DOUBLE_EQ(50.0, coil.ratedInletWaterTemperature());
  EXPECT_DOUBLE_EQ(35.0, coil.ratedOutdoorAirTemperature());
  EXPECT_DOUBLE_EQ(60.0, coil.maximumInletWaterTemperatureforHeatReclaim());
  EXPECT_DOUBLE_EQ(0.0001, coil.waterFlowRate());

  EXPECT_DOUBLE_EQ(100.0, coil.waterPumpPower());
  EXPECT_FALSE(coil.isWaterPumpPowerDefaulted());
  EXPECT_DOUBLE_EQ(0.2, coil.fractionofPumpHeattoWater());
  EXPECT_FALSE(coil.isFractionofPumpHeattoWaterDefaulted());

  EXPECT_DOUBLE_EQ(0.0, coil.onCycleParasiticElectricLoad());
  EXPECT_FALSE(coil.isOnCycleParasiticElectricLoadDefaulted());
  EXPECT_DOUBLE_EQ(0.0, coil.offCycleParasiticElectricLoad());
  EXPECT_FALSE(coil.isOffCycleParasiticElectricLoadDefaulted());

  // The retained one-argument EnergyPlus constructor intentionally leaves the required setpoint relationship incomplete.
  const auto report = model.canonicalize(SanitizationPolicy::ReportOnly);
  EXPECT_EQ(0u, report.errorCount);
  EXPECT_GE(report.warningCount, 1u);
}

TEST_F(EPModelFixture, CoilWaterHeatingDesuperheater_CanonicalConstructorAndLegacyCompletion) {
  Model model;
  ScheduleConstant setpoint(model);
  ASSERT_TRUE(setpoint.setValue(60.0));
  CoilWaterHeatingDesuperheater canonicalCoil(model, setpoint);
  EXPECT_EQ(setpoint.handle(), canonicalCoil.setpointTemperatureSchedule().handle());
  EXPECT_EQ(model.alwaysOnDiscreteSchedule().handle(), canonicalCoil.availabilitySchedule().handle());
  ASSERT_TRUE(setpoint.scheduleTypeLimits());
  EXPECT_EQ("Continuous", setpoint.scheduleTypeLimits()->numericType().value_or(""));
  EXPECT_EQ("Temperature", setpoint.scheduleTypeLimits()->unitType());

  CoilWaterHeatingDesuperheater legacyCoil(model);
  const auto incompleteReport = model.canonicalize(SanitizationPolicy::ReportOnly);
  EXPECT_EQ(0u, incompleteReport.errorCount);
  EXPECT_GE(incompleteReport.warningCount, 1u);
  const auto scheduleCount = model.getConcreteModelObjects<ScheduleConstant>().size();
  const auto repairReport = model.canonicalize(SanitizationPolicy::Repair);
  EXPECT_EQ(0u, repairReport.errorCount);
  EXPECT_GE(repairReport.warningCount, 1u);
  EXPECT_EQ(scheduleCount, model.getConcreteModelObjects<ScheduleConstant>().size());
  ASSERT_TRUE(legacyCoil.setSetpointTemperatureSchedule(setpoint));
  EXPECT_EQ(setpoint.handle(), legacyCoil.setpointTemperatureSchedule().handle());

  Model foreignModel;
  ScheduleConstant foreignSetpoint(foreignModel);
  const auto coilCount = model.getConcreteModelObjects<CoilWaterHeatingDesuperheater>().size();
  EXPECT_ANY_THROW({ CoilWaterHeatingDesuperheater rejected(model, foreignSetpoint); });
  EXPECT_EQ(coilCount, model.getConcreteModelObjects<CoilWaterHeatingDesuperheater>().size());
}

TEST_F(EPModelFixture, CoilWaterHeatingDesuperheater_ScheduleInferenceValidationAndPreservation) {
  Model model;
  ScheduleConstant initialSetpoint(model);
  ScheduleConstant initialAvailability(model);
  ASSERT_TRUE(initialSetpoint.setValue(58.0));
  ASSERT_TRUE(initialAvailability.setValue(1.0));
  CoilWaterHeatingDesuperheater coil(model, initialSetpoint);
  ASSERT_TRUE(coil.setAvailabilitySchedule(initialAvailability));

  ScheduleConstant inferredAvailability(model);
  ScheduleConstant inferredSetpoint(model);
  ASSERT_TRUE(inferredAvailability.setValue(0.5));
  ASSERT_TRUE(inferredSetpoint.setValue(62.0));
  ASSERT_TRUE(coil.setAvailabilitySchedule(inferredAvailability));
  ASSERT_TRUE(coil.setSetpointTemperatureSchedule(inferredSetpoint));
  ASSERT_TRUE(inferredAvailability.scheduleTypeLimits());
  EXPECT_EQ("Discrete", inferredAvailability.scheduleTypeLimits()->numericType().value_or(""));
  EXPECT_EQ("Availability", inferredAvailability.scheduleTypeLimits()->unitType());
  EXPECT_DOUBLE_EQ(0.0, inferredAvailability.scheduleTypeLimits()->lowerLimitValue().value_or(-1.0));
  EXPECT_DOUBLE_EQ(1.0, inferredAvailability.scheduleTypeLimits()->upperLimitValue().value_or(-1.0));
  ASSERT_TRUE(inferredSetpoint.scheduleTypeLimits());
  EXPECT_EQ("Continuous", inferredSetpoint.scheduleTypeLimits()->numericType().value_or(""));
  EXPECT_EQ("Temperature", inferredSetpoint.scheduleTypeLimits()->unitType());
  EXPECT_FALSE(inferredSetpoint.scheduleTypeLimits()->lowerLimitValue());
  EXPECT_FALSE(inferredSetpoint.scheduleTypeLimits()->upperLimitValue());

  const auto availabilityHandle = coil.availabilitySchedule().handle();
  const auto setpointHandle = coil.setpointTemperatureSchedule().handle();
  EXPECT_FALSE(coil.setAvailabilitySchedule(inferredSetpoint));
  EXPECT_FALSE(coil.setSetpointTemperatureSchedule(inferredAvailability));
  EXPECT_EQ(availabilityHandle, coil.availabilitySchedule().handle());
  EXPECT_EQ(setpointHandle, coil.setpointTemperatureSchedule().handle());

  ScheduleConstant wrongAvailabilityNumericType(model);
  ScheduleTypeLimits continuousAvailabilityLimits(model);
  ASSERT_TRUE(continuousAvailabilityLimits.setNumericType("Continuous"));
  ASSERT_TRUE(continuousAvailabilityLimits.setUnitType("Availability"));
  ASSERT_TRUE(continuousAvailabilityLimits.setLowerLimitValue(0.0));
  ASSERT_TRUE(continuousAvailabilityLimits.setUpperLimitValue(1.0));
  ASSERT_TRUE(wrongAvailabilityNumericType.setScheduleTypeLimits(continuousAvailabilityLimits));
  EXPECT_FALSE(coil.setAvailabilitySchedule(wrongAvailabilityNumericType));

  ScheduleConstant wrongSetpointUnit(model);
  ScheduleTypeLimits continuousDimensionlessLimits(model);
  ASSERT_TRUE(continuousDimensionlessLimits.setNumericType("Continuous"));
  ASSERT_TRUE(continuousDimensionlessLimits.setUnitType("Dimensionless"));
  ASSERT_TRUE(wrongSetpointUnit.setScheduleTypeLimits(continuousDimensionlessLimits));
  EXPECT_FALSE(coil.setSetpointTemperatureSchedule(wrongSetpointUnit));
  EXPECT_EQ(availabilityHandle, coil.availabilitySchedule().handle());
  EXPECT_EQ(setpointHandle, coil.setpointTemperatureSchedule().handle());

  Model foreignModel;
  ScheduleConstant foreignSchedule(foreignModel);
  EXPECT_FALSE(coil.setAvailabilitySchedule(foreignSchedule));
  EXPECT_FALSE(coil.setSetpointTemperatureSchedule(foreignSchedule));
  EXPECT_EQ(availabilityHandle, coil.availabilitySchedule().handle());
  EXPECT_EQ(setpointHandle, coil.setpointTemperatureSchedule().handle());
}

TEST_F(EPModelFixture, CoilWaterHeatingDesuperheater_AvailabilityResetRequiresCanonicalRepair) {
  Model model;
  ScheduleConstant setpoint(model);
  CoilWaterHeatingDesuperheater coil(model, setpoint);

  coil.resetAvailabilitySchedule();
  const auto reportOnly = model.canonicalize(SanitizationPolicy::ReportOnly);
  EXPECT_EQ(0u, reportOnly.errorCount);
  EXPECT_GE(reportOnly.warningCount, 1u);

  const auto repairReport = model.canonicalize(SanitizationPolicy::Repair);
  EXPECT_EQ(0u, repairReport.errorCount);
  EXPECT_GE(repairReport.infoCount, 1u);
  EXPECT_EQ(model.alwaysOnDiscreteSchedule().handle(), coil.availabilitySchedule().handle());
}

TEST_F(EPModelFixture, CoilWaterHeatingDesuperheater_CanonicalizesOnlyUniqueCompatibleScheduleEvidence) {
  Model model;
  ScheduleConstant recoverableAvailability(model);
  ScheduleConstant recoverableSetpoint(model);
  ScheduleConstant duplicateFirst(model);
  ScheduleConstant duplicateSecond(model);
  ScheduleConstant incompatibleAvailability(model);
  ScheduleConstant incompatibleSetpoint(model);
  ScheduleTypeLimits temperatureLimits(model);
  ScheduleTypeLimits availabilityLimits(model);
  ASSERT_TRUE(recoverableAvailability.setName("Recoverable Desuperheater Availability"));
  ASSERT_TRUE(recoverableSetpoint.setName("Recoverable Desuperheater Setpoint"));
  ASSERT_TRUE(duplicateFirst.setName("Ambiguous Desuperheater Schedule"));
  ASSERT_TRUE(incompatibleAvailability.setName("Incompatible Desuperheater Availability"));
  ASSERT_TRUE(incompatibleSetpoint.setName("Incompatible Desuperheater Setpoint"));
  ASSERT_TRUE(temperatureLimits.setNumericType("Continuous"));
  ASSERT_TRUE(temperatureLimits.setUnitType("Temperature"));
  ASSERT_TRUE(availabilityLimits.setNumericType("Discrete"));
  ASSERT_TRUE(availabilityLimits.setUnitType("Availability"));
  ASSERT_TRUE(availabilityLimits.setLowerLimitValue(0.0));
  ASSERT_TRUE(availabilityLimits.setUpperLimitValue(1.0));
  ASSERT_TRUE(incompatibleAvailability.setScheduleTypeLimits(temperatureLimits));
  ASSERT_TRUE(incompatibleSetpoint.setScheduleTypeLimits(availabilityLimits));

  auto duplicateSecondImpl = duplicateSecond.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(duplicateSecondImpl);
  // Imported EnergyPlus files may contain duplicate eligible names; public name setters deliberately disambiguate them.
  ASSERT_TRUE(duplicateSecondImpl->openstudio::detail::IdfObject_Impl::setString(0u, "Ambiguous Desuperheater Schedule", false));

  CoilWaterHeatingDesuperheater recoverable(model);
  CoilWaterHeatingDesuperheater unresolved(model);
  CoilWaterHeatingDesuperheater ambiguous(model);
  CoilWaterHeatingDesuperheater managedIncompatible(model);
  auto recoverableImpl = recoverable.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  auto unresolvedImpl = unresolved.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  auto ambiguousImpl = ambiguous.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  auto managedIncompatibleImpl = managedIncompatible.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(recoverableImpl);
  ASSERT_TRUE(unresolvedImpl);
  ASSERT_TRUE(ambiguousImpl);
  ASSERT_TRUE(managedIncompatibleImpl);

  constexpr auto availabilityField = openstudio::Coil_WaterHeating_DesuperheaterFields::AvailabilityScheduleName;
  constexpr auto setpointField = openstudio::Coil_WaterHeating_DesuperheaterFields::SetpointTemperatureScheduleName;
  const auto setRawEvidence = [](const std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>& impl, unsigned field, const std::string& value) {
    return impl->setPointer(field, openstudio::Handle(), false) && impl->openstudio::detail::IdfObject_Impl::setString(field, value, false);
  };

  // These low-level writes intentionally model unique, unresolved, ambiguous, and incompatible imported schedule evidence.
  ASSERT_TRUE(setRawEvidence(recoverableImpl, availabilityField, recoverableAvailability.nameString()));
  ASSERT_TRUE(setRawEvidence(recoverableImpl, setpointField, recoverableSetpoint.nameString()));
  ASSERT_TRUE(setRawEvidence(unresolvedImpl, availabilityField, "Missing Desuperheater Availability"));
  ASSERT_TRUE(setRawEvidence(unresolvedImpl, setpointField, "Missing Desuperheater Setpoint"));
  ASSERT_TRUE(setRawEvidence(ambiguousImpl, setpointField, "Ambiguous Desuperheater Schedule"));
  ASSERT_TRUE(managedIncompatibleImpl->setPointer(availabilityField, incompatibleAvailability.handle(), false));
  ASSERT_TRUE(managedIncompatibleImpl->setPointer(setpointField, incompatibleSetpoint.handle(), false));

  // Failed public assignments must not discard pre-existing unresolved raw evidence.
  EXPECT_FALSE(unresolved.setAvailabilitySchedule(incompatibleAvailability));
  EXPECT_FALSE(unresolved.setSetpointTemperatureSchedule(incompatibleSetpoint));
  Model foreignModel;
  ScheduleConstant foreignSchedule(foreignModel);
  EXPECT_FALSE(unresolved.setAvailabilitySchedule(foreignSchedule));
  EXPECT_FALSE(unresolved.setSetpointTemperatureSchedule(foreignSchedule));
  EXPECT_EQ("Missing Desuperheater Availability",
            unresolvedImpl->openstudio::detail::IdfObject_Impl::getString(availabilityField, false, true).value_or(""));
  EXPECT_EQ("Missing Desuperheater Setpoint", unresolvedImpl->openstudio::detail::IdfObject_Impl::getString(setpointField, false, true).value_or(""));

  const auto report = model.canonicalize(SanitizationPolicy::Repair);
  EXPECT_EQ(0u, report.errorCount);
  EXPECT_GE(report.warningCount, 5u);
  EXPECT_EQ(recoverableAvailability.handle(), recoverable.availabilitySchedule().handle());
  EXPECT_EQ(recoverableSetpoint.handle(), recoverable.setpointTemperatureSchedule().handle());
  ASSERT_TRUE(recoverableAvailability.scheduleTypeLimits());
  ASSERT_TRUE(recoverableSetpoint.scheduleTypeLimits());
  EXPECT_EQ("Discrete", recoverableAvailability.scheduleTypeLimits()->numericType().value_or(""));
  EXPECT_EQ("Temperature", recoverableSetpoint.scheduleTypeLimits()->unitType());
  EXPECT_EQ("Missing Desuperheater Availability",
            unresolvedImpl->openstudio::detail::IdfObject_Impl::getString(availabilityField, false, true).value_or(""));
  EXPECT_EQ("Missing Desuperheater Setpoint", unresolvedImpl->openstudio::detail::IdfObject_Impl::getString(setpointField, false, true).value_or(""));
  EXPECT_EQ("Ambiguous Desuperheater Schedule",
            ambiguousImpl->openstudio::detail::IdfObject_Impl::getString(setpointField, false, true).value_or(""));
  ASSERT_TRUE(managedIncompatibleImpl->getTarget(availabilityField));
  ASSERT_TRUE(managedIncompatibleImpl->getTarget(setpointField));
  EXPECT_EQ(incompatibleAvailability.handle(), managedIncompatibleImpl->getTarget(availabilityField)->handle());
  EXPECT_EQ(incompatibleSetpoint.handle(), managedIncompatibleImpl->getTarget(setpointField)->handle());
}

TEST_F(EPModelFixture, CoilWaterHeatingDesuperheater_SchedulesSurviveReloadReplacementAndRemoval) {
  const auto firstPath = uniqueDesuperheaterPath("epmodel-desuperheater-schedules-first");
  const auto secondPath = uniqueDesuperheaterPath("epmodel-desuperheater-schedules-second");
  const ScopedDesuperheaterFileRemoval removeFirst(firstPath);
  const ScopedDesuperheaterFileRemoval removeSecond(secondPath);

  Model model;
  ScheduleConstant originalAvailability(model);
  ScheduleConstant originalSetpoint(model);
  ASSERT_TRUE(originalAvailability.setName("Original Desuperheater Availability"));
  ASSERT_TRUE(originalSetpoint.setName("Original Desuperheater Setpoint"));
  ASSERT_TRUE(originalAvailability.setValue(1.0));
  ASSERT_TRUE(originalSetpoint.setValue(60.0));
  CoilWaterHeatingDesuperheater coil(model, originalSetpoint);
  ASSERT_TRUE(coil.setName("Reloadable Desuperheater"));
  ASSERT_TRUE(coil.setAvailabilitySchedule(originalAvailability));
  ASSERT_TRUE(model.save(firstPath, true));

  auto loadedModel = Model::load(firstPath);
  ASSERT_TRUE(loadedModel);
  auto loadedCoil = loadedModel->getConcreteModelObjectByName<CoilWaterHeatingDesuperheater>("Reloadable Desuperheater");
  auto loadedOriginalAvailability = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("Original Desuperheater Availability");
  auto loadedOriginalSetpoint = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("Original Desuperheater Setpoint");
  ASSERT_TRUE(loadedCoil);
  ASSERT_TRUE(loadedOriginalAvailability);
  ASSERT_TRUE(loadedOriginalSetpoint);
  EXPECT_EQ(loadedOriginalAvailability->handle(), loadedCoil->availabilitySchedule().handle());
  EXPECT_EQ(loadedOriginalSetpoint->handle(), loadedCoil->setpointTemperatureSchedule().handle());

  ScheduleConstant replacementAvailability(*loadedModel);
  ScheduleConstant replacementSetpoint(*loadedModel);
  ASSERT_TRUE(replacementAvailability.setName("Replacement Desuperheater Availability"));
  ASSERT_TRUE(replacementSetpoint.setName("Replacement Desuperheater Setpoint"));
  ASSERT_TRUE(replacementAvailability.setValue(0.5));
  ASSERT_TRUE(replacementSetpoint.setValue(63.0));
  ASSERT_TRUE(loadedCoil->setAvailabilitySchedule(replacementAvailability));
  ASSERT_TRUE(loadedCoil->setSetpointTemperatureSchedule(replacementSetpoint));
  ASSERT_TRUE(loadedModel->save(secondPath, true));

  auto reloadedModel = Model::load(secondPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedCoil = reloadedModel->getConcreteModelObjectByName<CoilWaterHeatingDesuperheater>("Reloadable Desuperheater");
  auto reloadedOriginalAvailability = reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Original Desuperheater Availability");
  auto reloadedOriginalSetpoint = reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Original Desuperheater Setpoint");
  auto reloadedReplacementAvailability = reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Replacement Desuperheater Availability");
  auto reloadedReplacementSetpoint = reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Replacement Desuperheater Setpoint");
  ASSERT_TRUE(reloadedCoil);
  ASSERT_TRUE(reloadedOriginalAvailability);
  ASSERT_TRUE(reloadedOriginalSetpoint);
  ASSERT_TRUE(reloadedReplacementAvailability);
  ASSERT_TRUE(reloadedReplacementSetpoint);
  EXPECT_EQ(reloadedReplacementAvailability->handle(), reloadedCoil->availabilitySchedule().handle());
  EXPECT_EQ(reloadedReplacementSetpoint->handle(), reloadedCoil->setpointTemperatureSchedule().handle());

  const std::array<openstudio::Handle, 4> scheduleHandles{reloadedOriginalAvailability->handle(), reloadedOriginalSetpoint->handle(),
                                                          reloadedReplacementAvailability->handle(), reloadedReplacementSetpoint->handle()};
  EXPECT_FALSE(reloadedCoil->remove().empty());
  for (const auto& handle : scheduleHandles) {
    EXPECT_TRUE(reloadedModel->getObject(handle));
  }
}

TEST_F(EPModelFixture, CoilWaterHeatingDesuperheater_ScalarAccessors_RoundTrip) {
  Model model;
  CoilWaterHeatingDesuperheater coil(model);
  ScheduleConstant availability(model);
  ASSERT_TRUE(availability.setValue(0.5));
  CurveBiquadratic curve(model);
  ASSERT_TRUE(curve.setCoefficient1Constant(0.8));
  ASSERT_TRUE(curve.setCoefficient2x(0.1));
  ASSERT_TRUE(curve.setCoefficient3xPOW2(0.0));
  ASSERT_TRUE(curve.setCoefficient4y(0.1));
  ASSERT_TRUE(curve.setCoefficient5yPOW2(0.0));
  ASSERT_TRUE(curve.setCoefficient6xTIMESY(0.0));
  RefrigerationCondenserAirCooled condenser(model);

  EXPECT_TRUE(coil.setAvailabilitySchedule(availability));
  EXPECT_EQ(availability.handle(), coil.availabilitySchedule().handle());
  ASSERT_TRUE(coil.getTarget(openstudio::Coil_WaterHeating_DesuperheaterFields::AvailabilityScheduleName));
  EXPECT_EQ(availability.handle(), coil.getTarget(openstudio::Coil_WaterHeating_DesuperheaterFields::AvailabilityScheduleName)->handle());

  EXPECT_TRUE(coil.setHeatReclaimEfficiencyFunctionofTemperatureCurve(curve));
  ASSERT_TRUE(coil.heatReclaimEfficiencyFunctionofTemperatureCurve());
  EXPECT_EQ(curve.handle(), coil.heatReclaimEfficiencyFunctionofTemperatureCurve()->handle());

  EXPECT_TRUE(coil.setHeatingSource(condenser));
  ASSERT_TRUE(coil.heatingSource());
  EXPECT_EQ(condenser.handle(), coil.heatingSource()->handle());

  const auto children = coil.children();
  ASSERT_EQ(1u, children.size());
  EXPECT_EQ(curve.handle(), children[0].handle());

  EXPECT_TRUE(coil.setDeadBandTemperatureDifference(3.3));
  EXPECT_DOUBLE_EQ(3.3, coil.deadBandTemperatureDifference());
  EXPECT_FALSE(coil.isDeadBandTemperatureDifferenceDefaulted());
  coil.resetDeadBandTemperatureDifference();
  EXPECT_TRUE(coil.isDeadBandTemperatureDifferenceDefaulted());

  EXPECT_TRUE(coil.setRatedHeatReclaimRecoveryEfficiency(0.27));
  ASSERT_TRUE(coil.ratedHeatReclaimRecoveryEfficiency());
  EXPECT_DOUBLE_EQ(0.27, *coil.ratedHeatReclaimRecoveryEfficiency());
  coil.resetRatedHeatReclaimRecoveryEfficiency();
  EXPECT_FALSE(coil.ratedHeatReclaimRecoveryEfficiency());

  EXPECT_TRUE(coil.setRatedInletWaterTemperature(48.0));
  EXPECT_DOUBLE_EQ(48.0, coil.ratedInletWaterTemperature());
  EXPECT_TRUE(coil.setRatedOutdoorAirTemperature(30.0));
  EXPECT_DOUBLE_EQ(30.0, coil.ratedOutdoorAirTemperature());
  EXPECT_TRUE(coil.setMaximumInletWaterTemperatureforHeatReclaim(58.0));
  EXPECT_DOUBLE_EQ(58.0, coil.maximumInletWaterTemperatureforHeatReclaim());
  EXPECT_TRUE(coil.setWaterFlowRate(0.00023));
  EXPECT_DOUBLE_EQ(0.00023, coil.waterFlowRate());

  EXPECT_TRUE(coil.setWaterPumpPower(333.0));
  EXPECT_DOUBLE_EQ(333.0, coil.waterPumpPower());
  EXPECT_FALSE(coil.isWaterPumpPowerDefaulted());
  coil.resetWaterPumpPower();
  EXPECT_TRUE(coil.isWaterPumpPowerDefaulted());

  EXPECT_TRUE(coil.setFractionofPumpHeattoWater(0.61));
  EXPECT_DOUBLE_EQ(0.61, coil.fractionofPumpHeattoWater());
  EXPECT_FALSE(coil.isFractionofPumpHeattoWaterDefaulted());
  coil.resetFractionofPumpHeattoWater();
  EXPECT_TRUE(coil.isFractionofPumpHeattoWaterDefaulted());

  EXPECT_TRUE(coil.setOnCycleParasiticElectricLoad(125.0));
  EXPECT_DOUBLE_EQ(125.0, coil.onCycleParasiticElectricLoad());
  EXPECT_FALSE(coil.isOnCycleParasiticElectricLoadDefaulted());
  coil.resetOnCycleParasiticElectricLoad();
  EXPECT_TRUE(coil.isOnCycleParasiticElectricLoadDefaulted());

  EXPECT_TRUE(coil.setOffCycleParasiticElectricLoad(44.0));
  EXPECT_DOUBLE_EQ(44.0, coil.offCycleParasiticElectricLoad());
  EXPECT_FALSE(coil.isOffCycleParasiticElectricLoadDefaulted());
  coil.resetOffCycleParasiticElectricLoad();
  EXPECT_TRUE(coil.isOffCycleParasiticElectricLoadDefaulted());

  coil.resetHeatReclaimEfficiencyFunctionofTemperatureCurve();
  EXPECT_FALSE(coil.heatReclaimEfficiencyFunctionofTemperatureCurve());
  EXPECT_TRUE(coil.children().empty());

  coil.resetHeatingSource();
  EXPECT_FALSE(coil.heatingSource());
}

TEST_F(EPModelFixture, CoilWaterHeatingDesuperheater_AddToNode_RejectedAcrossLoopTypes) {
  Model model;
  CoilWaterHeatingDesuperheater coil(model);

  AirLoopHVAC airLoop(model);
  auto supplyOutletNode = airLoop.supplyOutletNode();
  EXPECT_FALSE(coil.addToNode(supplyOutletNode));
  EXPECT_EQ((unsigned)2, airLoop.supplyComponents().size());

  auto splitterBranch = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(splitterBranch);
  auto splitterBranchNode = splitterBranch->optionalCast<Node>();
  ASSERT_TRUE(splitterBranchNode);
  EXPECT_FALSE(coil.addToNode(*splitterBranchNode));
  EXPECT_EQ((unsigned)5, airLoop.demandComponents().size());

  PlantLoop plantLoop(model);
  auto plantSupplyNode = plantLoop.supplyOutletNode();
  EXPECT_FALSE(coil.addToNode(plantSupplyNode));
  EXPECT_EQ((unsigned)5, plantLoop.supplyComponents().size());

  auto plantDemandNode = plantLoop.demandOutletNode();
  EXPECT_FALSE(coil.addToNode(plantDemandNode));
  EXPECT_EQ((unsigned)5, plantLoop.demandComponents().size());
}
