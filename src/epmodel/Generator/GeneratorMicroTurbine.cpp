/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "GeneratorMicroTurbine.hpp"
#include "GeneratorMicroTurbine_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Generator_MicroTurbine_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

GeneratorMicroTurbine::GeneratorMicroTurbine(const Model& model) : ModelObject(GeneratorMicroTurbine::iddObjectType(), model) {}

GeneratorMicroTurbine::GeneratorMicroTurbine(std::shared_ptr<detail::GeneratorMicroTurbine_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType GeneratorMicroTurbine::iddObjectType() {
  return IddObjectType::Generator_MicroTurbine;
}

std::vector<std::string> GeneratorMicroTurbine::validFuelTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Generator_MicroTurbineFields::FuelType);
}

double GeneratorMicroTurbine::referenceElectricalPowerOutput() const {
  return getImpl<detail::GeneratorMicroTurbine_Impl>()->referenceElectricalPowerOutput();
}

bool GeneratorMicroTurbine::setReferenceElectricalPowerOutput(double referenceElectricalPowerOutput) {
  return getImpl<detail::GeneratorMicroTurbine_Impl>()->setReferenceElectricalPowerOutput(referenceElectricalPowerOutput);
}

double GeneratorMicroTurbine::minimumFullLoadElectricalPowerOutput() const {
  return getImpl<detail::GeneratorMicroTurbine_Impl>()->minimumFullLoadElectricalPowerOutput();
}

bool GeneratorMicroTurbine::isMinimumFullLoadElectricalPowerOutputDefaulted() const {
  return getImpl<detail::GeneratorMicroTurbine_Impl>()->isMinimumFullLoadElectricalPowerOutputDefaulted();
}

bool GeneratorMicroTurbine::setMinimumFullLoadElectricalPowerOutput(double minimumFullLoadElectricalPowerOutput) {
  return getImpl<detail::GeneratorMicroTurbine_Impl>()->setMinimumFullLoadElectricalPowerOutput(minimumFullLoadElectricalPowerOutput);
}

void GeneratorMicroTurbine::resetMinimumFullLoadElectricalPowerOutput() {
  getImpl<detail::GeneratorMicroTurbine_Impl>()->resetMinimumFullLoadElectricalPowerOutput();
}

double GeneratorMicroTurbine::maximumFullLoadElectricalPowerOutput() const {
  return getImpl<detail::GeneratorMicroTurbine_Impl>()->maximumFullLoadElectricalPowerOutput();
}

bool GeneratorMicroTurbine::isMaximumFullLoadElectricalPowerOutputDefaulted() const {
  return getImpl<detail::GeneratorMicroTurbine_Impl>()->isMaximumFullLoadElectricalPowerOutputDefaulted();
}

bool GeneratorMicroTurbine::setMaximumFullLoadElectricalPowerOutput(double maximumFullLoadElectricalPowerOutput) {
  return getImpl<detail::GeneratorMicroTurbine_Impl>()->setMaximumFullLoadElectricalPowerOutput(maximumFullLoadElectricalPowerOutput);
}

void GeneratorMicroTurbine::resetMaximumFullLoadElectricalPowerOutput() {
  getImpl<detail::GeneratorMicroTurbine_Impl>()->resetMaximumFullLoadElectricalPowerOutput();
}

double GeneratorMicroTurbine::referenceElectricalEfficiencyUsingLowerHeatingValue() const {
  return getImpl<detail::GeneratorMicroTurbine_Impl>()->referenceElectricalEfficiencyUsingLowerHeatingValue();
}

bool GeneratorMicroTurbine::setReferenceElectricalEfficiencyUsingLowerHeatingValue(double referenceElectricalEfficiencyUsingLowerHeatingValue) {
  return getImpl<detail::GeneratorMicroTurbine_Impl>()->setReferenceElectricalEfficiencyUsingLowerHeatingValue(
    referenceElectricalEfficiencyUsingLowerHeatingValue);
}

double GeneratorMicroTurbine::referenceCombustionAirInletTemperature() const {
  return getImpl<detail::GeneratorMicroTurbine_Impl>()->referenceCombustionAirInletTemperature();
}

bool GeneratorMicroTurbine::isReferenceCombustionAirInletTemperatureDefaulted() const {
  return getImpl<detail::GeneratorMicroTurbine_Impl>()->isReferenceCombustionAirInletTemperatureDefaulted();
}

bool GeneratorMicroTurbine::setReferenceCombustionAirInletTemperature(double referenceCombustionAirInletTemperature) {
  return getImpl<detail::GeneratorMicroTurbine_Impl>()->setReferenceCombustionAirInletTemperature(referenceCombustionAirInletTemperature);
}

void GeneratorMicroTurbine::resetReferenceCombustionAirInletTemperature() {
  getImpl<detail::GeneratorMicroTurbine_Impl>()->resetReferenceCombustionAirInletTemperature();
}

double GeneratorMicroTurbine::referenceCombustionAirInletHumidityRatio() const {
  return getImpl<detail::GeneratorMicroTurbine_Impl>()->referenceCombustionAirInletHumidityRatio();
}

bool GeneratorMicroTurbine::isReferenceCombustionAirInletHumidityRatioDefaulted() const {
  return getImpl<detail::GeneratorMicroTurbine_Impl>()->isReferenceCombustionAirInletHumidityRatioDefaulted();
}

bool GeneratorMicroTurbine::setReferenceCombustionAirInletHumidityRatio(double referenceCombustionAirInletHumidityRatio) {
  return getImpl<detail::GeneratorMicroTurbine_Impl>()->setReferenceCombustionAirInletHumidityRatio(referenceCombustionAirInletHumidityRatio);
}

void GeneratorMicroTurbine::resetReferenceCombustionAirInletHumidityRatio() {
  getImpl<detail::GeneratorMicroTurbine_Impl>()->resetReferenceCombustionAirInletHumidityRatio();
}

double GeneratorMicroTurbine::referenceElevation() const {
  return getImpl<detail::GeneratorMicroTurbine_Impl>()->referenceElevation();
}

bool GeneratorMicroTurbine::isReferenceElevationDefaulted() const {
  return getImpl<detail::GeneratorMicroTurbine_Impl>()->isReferenceElevationDefaulted();
}

bool GeneratorMicroTurbine::setReferenceElevation(double referenceElevation) {
  return getImpl<detail::GeneratorMicroTurbine_Impl>()->setReferenceElevation(referenceElevation);
}

void GeneratorMicroTurbine::resetReferenceElevation() {
  getImpl<detail::GeneratorMicroTurbine_Impl>()->resetReferenceElevation();
}

std::string GeneratorMicroTurbine::fuelType() const {
  return getImpl<detail::GeneratorMicroTurbine_Impl>()->fuelType();
}

bool GeneratorMicroTurbine::isFuelTypeDefaulted() const {
  return getImpl<detail::GeneratorMicroTurbine_Impl>()->isFuelTypeDefaulted();
}

bool GeneratorMicroTurbine::setFuelType(const std::string& fuelType) {
  return getImpl<detail::GeneratorMicroTurbine_Impl>()->setFuelType(fuelType);
}

void GeneratorMicroTurbine::resetFuelType() {
  getImpl<detail::GeneratorMicroTurbine_Impl>()->resetFuelType();
}

double GeneratorMicroTurbine::fuelHigherHeatingValue() const {
  return getImpl<detail::GeneratorMicroTurbine_Impl>()->fuelHigherHeatingValue();
}

bool GeneratorMicroTurbine::isFuelHigherHeatingValueDefaulted() const {
  return getImpl<detail::GeneratorMicroTurbine_Impl>()->isFuelHigherHeatingValueDefaulted();
}

bool GeneratorMicroTurbine::setFuelHigherHeatingValue(double fuelHigherHeatingValue) {
  return getImpl<detail::GeneratorMicroTurbine_Impl>()->setFuelHigherHeatingValue(fuelHigherHeatingValue);
}

void GeneratorMicroTurbine::resetFuelHigherHeatingValue() {
  getImpl<detail::GeneratorMicroTurbine_Impl>()->resetFuelHigherHeatingValue();
}

double GeneratorMicroTurbine::fuelLowerHeatingValue() const {
  return getImpl<detail::GeneratorMicroTurbine_Impl>()->fuelLowerHeatingValue();
}

bool GeneratorMicroTurbine::isFuelLowerHeatingValueDefaulted() const {
  return getImpl<detail::GeneratorMicroTurbine_Impl>()->isFuelLowerHeatingValueDefaulted();
}

bool GeneratorMicroTurbine::setFuelLowerHeatingValue(double fuelLowerHeatingValue) {
  return getImpl<detail::GeneratorMicroTurbine_Impl>()->setFuelLowerHeatingValue(fuelLowerHeatingValue);
}

void GeneratorMicroTurbine::resetFuelLowerHeatingValue() {
  getImpl<detail::GeneratorMicroTurbine_Impl>()->resetFuelLowerHeatingValue();
}

double GeneratorMicroTurbine::standbyPower() const {
  return getImpl<detail::GeneratorMicroTurbine_Impl>()->standbyPower();
}

bool GeneratorMicroTurbine::isStandbyPowerDefaulted() const {
  return getImpl<detail::GeneratorMicroTurbine_Impl>()->isStandbyPowerDefaulted();
}

bool GeneratorMicroTurbine::setStandbyPower(double standbyPower) {
  return getImpl<detail::GeneratorMicroTurbine_Impl>()->setStandbyPower(standbyPower);
}

void GeneratorMicroTurbine::resetStandbyPower() {
  getImpl<detail::GeneratorMicroTurbine_Impl>()->resetStandbyPower();
}

double GeneratorMicroTurbine::ancillaryPower() const {
  return getImpl<detail::GeneratorMicroTurbine_Impl>()->ancillaryPower();
}

bool GeneratorMicroTurbine::isAncillaryPowerDefaulted() const {
  return getImpl<detail::GeneratorMicroTurbine_Impl>()->isAncillaryPowerDefaulted();
}

bool GeneratorMicroTurbine::setAncillaryPower(double ancillaryPower) {
  return getImpl<detail::GeneratorMicroTurbine_Impl>()->setAncillaryPower(ancillaryPower);
}

void GeneratorMicroTurbine::resetAncillaryPower() {
  getImpl<detail::GeneratorMicroTurbine_Impl>()->resetAncillaryPower();
}

boost::optional<double> GeneratorMicroTurbine::referenceExhaustAirMassFlowRate() const {
  return getImpl<detail::GeneratorMicroTurbine_Impl>()->referenceExhaustAirMassFlowRate();
}

bool GeneratorMicroTurbine::setReferenceExhaustAirMassFlowRate(double referenceExhaustAirMassFlowRate) {
  return getImpl<detail::GeneratorMicroTurbine_Impl>()->setReferenceExhaustAirMassFlowRate(referenceExhaustAirMassFlowRate);
}

void GeneratorMicroTurbine::resetReferenceExhaustAirMassFlowRate() {
  getImpl<detail::GeneratorMicroTurbine_Impl>()->resetReferenceExhaustAirMassFlowRate();
}

boost::optional<double> GeneratorMicroTurbine::nominalExhaustAirOutletTemperature() const {
  return getImpl<detail::GeneratorMicroTurbine_Impl>()->nominalExhaustAirOutletTemperature();
}

bool GeneratorMicroTurbine::setNominalExhaustAirOutletTemperature(double nominalExhaustAirOutletTemperature) {
  return getImpl<detail::GeneratorMicroTurbine_Impl>()->setNominalExhaustAirOutletTemperature(nominalExhaustAirOutletTemperature);
}

void GeneratorMicroTurbine::resetNominalExhaustAirOutletTemperature() {
  getImpl<detail::GeneratorMicroTurbine_Impl>()->resetNominalExhaustAirOutletTemperature();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

double GeneratorMicroTurbine_Impl::referenceElectricalPowerOutput() const {
  const auto value = getDouble(openstudio::Generator_MicroTurbineFields::ReferenceElectricalPowerOutput, true);
  OS_ASSERT(value);
  return *value;
}

bool GeneratorMicroTurbine_Impl::setReferenceElectricalPowerOutput(double referenceElectricalPowerOutput) {
  return setDouble(openstudio::Generator_MicroTurbineFields::ReferenceElectricalPowerOutput, referenceElectricalPowerOutput);
}

double GeneratorMicroTurbine_Impl::minimumFullLoadElectricalPowerOutput() const {
  if (auto value = getDouble(openstudio::Generator_MicroTurbineFields::MinimumFullLoadElectricalPowerOutput, false)) {
    return *value;
  }
  return 0.0;
}

bool GeneratorMicroTurbine_Impl::isMinimumFullLoadElectricalPowerOutputDefaulted() const {
  return isEmpty(openstudio::Generator_MicroTurbineFields::MinimumFullLoadElectricalPowerOutput);
}

bool GeneratorMicroTurbine_Impl::setMinimumFullLoadElectricalPowerOutput(double minimumFullLoadElectricalPowerOutput) {
  return setDouble(openstudio::Generator_MicroTurbineFields::MinimumFullLoadElectricalPowerOutput, minimumFullLoadElectricalPowerOutput);
}

void GeneratorMicroTurbine_Impl::resetMinimumFullLoadElectricalPowerOutput() {
  OS_ASSERT(setString(openstudio::Generator_MicroTurbineFields::MinimumFullLoadElectricalPowerOutput, ""));
}

double GeneratorMicroTurbine_Impl::maximumFullLoadElectricalPowerOutput() const {
  if (auto value = getDouble(openstudio::Generator_MicroTurbineFields::MaximumFullLoadElectricalPowerOutput, true)) {
    return *value;
  }
  return referenceElectricalPowerOutput();
}

bool GeneratorMicroTurbine_Impl::isMaximumFullLoadElectricalPowerOutputDefaulted() const {
  return isEmpty(openstudio::Generator_MicroTurbineFields::MaximumFullLoadElectricalPowerOutput);
}

bool GeneratorMicroTurbine_Impl::setMaximumFullLoadElectricalPowerOutput(double maximumFullLoadElectricalPowerOutput) {
  return setDouble(openstudio::Generator_MicroTurbineFields::MaximumFullLoadElectricalPowerOutput, maximumFullLoadElectricalPowerOutput);
}

void GeneratorMicroTurbine_Impl::resetMaximumFullLoadElectricalPowerOutput() {
  OS_ASSERT(setString(openstudio::Generator_MicroTurbineFields::MaximumFullLoadElectricalPowerOutput, ""));
}

double GeneratorMicroTurbine_Impl::referenceElectricalEfficiencyUsingLowerHeatingValue() const {
  const auto value = getDouble(openstudio::Generator_MicroTurbineFields::ReferenceElectricalEfficiencyUsingLowerHeatingValue, true);
  OS_ASSERT(value);
  return *value;
}

bool GeneratorMicroTurbine_Impl::setReferenceElectricalEfficiencyUsingLowerHeatingValue(double referenceElectricalEfficiencyUsingLowerHeatingValue) {
  return setDouble(openstudio::Generator_MicroTurbineFields::ReferenceElectricalEfficiencyUsingLowerHeatingValue,
                   referenceElectricalEfficiencyUsingLowerHeatingValue);
}

double GeneratorMicroTurbine_Impl::referenceCombustionAirInletTemperature() const {
  if (auto value = getDouble(openstudio::Generator_MicroTurbineFields::ReferenceCombustionAirInletTemperature, false)) {
    return *value;
  }
  return 15.0;
}

bool GeneratorMicroTurbine_Impl::isReferenceCombustionAirInletTemperatureDefaulted() const {
  return isEmpty(openstudio::Generator_MicroTurbineFields::ReferenceCombustionAirInletTemperature);
}

bool GeneratorMicroTurbine_Impl::setReferenceCombustionAirInletTemperature(double referenceCombustionAirInletTemperature) {
  const bool result = setDouble(openstudio::Generator_MicroTurbineFields::ReferenceCombustionAirInletTemperature,
                                referenceCombustionAirInletTemperature);
  OS_ASSERT(result);
  return result;
}

void GeneratorMicroTurbine_Impl::resetReferenceCombustionAirInletTemperature() {
  OS_ASSERT(setString(openstudio::Generator_MicroTurbineFields::ReferenceCombustionAirInletTemperature, ""));
}

double GeneratorMicroTurbine_Impl::referenceCombustionAirInletHumidityRatio() const {
  if (auto value = getDouble(openstudio::Generator_MicroTurbineFields::ReferenceCombustionAirInletHumidityRatio, false)) {
    return *value;
  }
  return 0.00638;
}

bool GeneratorMicroTurbine_Impl::isReferenceCombustionAirInletHumidityRatioDefaulted() const {
  return isEmpty(openstudio::Generator_MicroTurbineFields::ReferenceCombustionAirInletHumidityRatio);
}

bool GeneratorMicroTurbine_Impl::setReferenceCombustionAirInletHumidityRatio(double referenceCombustionAirInletHumidityRatio) {
  return setDouble(openstudio::Generator_MicroTurbineFields::ReferenceCombustionAirInletHumidityRatio,
                   referenceCombustionAirInletHumidityRatio);
}

void GeneratorMicroTurbine_Impl::resetReferenceCombustionAirInletHumidityRatio() {
  OS_ASSERT(setString(openstudio::Generator_MicroTurbineFields::ReferenceCombustionAirInletHumidityRatio, ""));
}

double GeneratorMicroTurbine_Impl::referenceElevation() const {
  if (auto value = getDouble(openstudio::Generator_MicroTurbineFields::ReferenceElevation, false)) {
    return *value;
  }
  return 0.0;
}

bool GeneratorMicroTurbine_Impl::isReferenceElevationDefaulted() const {
  return isEmpty(openstudio::Generator_MicroTurbineFields::ReferenceElevation);
}

bool GeneratorMicroTurbine_Impl::setReferenceElevation(double referenceElevation) {
  return setDouble(openstudio::Generator_MicroTurbineFields::ReferenceElevation, referenceElevation);
}

void GeneratorMicroTurbine_Impl::resetReferenceElevation() {
  OS_ASSERT(setString(openstudio::Generator_MicroTurbineFields::ReferenceElevation, ""));
}

std::string GeneratorMicroTurbine_Impl::fuelType() const {
  if (auto value = getString(openstudio::Generator_MicroTurbineFields::FuelType, false)) {
    if (!value->empty()) {
      return *value;
    }
  }
  return "NaturalGas";
}

bool GeneratorMicroTurbine_Impl::isFuelTypeDefaulted() const {
  return isEmpty(openstudio::Generator_MicroTurbineFields::FuelType);
}

bool GeneratorMicroTurbine_Impl::setFuelType(const std::string& fuelType) {
  return setString(openstudio::Generator_MicroTurbineFields::FuelType, fuelType);
}

void GeneratorMicroTurbine_Impl::resetFuelType() {
  OS_ASSERT(setString(openstudio::Generator_MicroTurbineFields::FuelType, ""));
}

double GeneratorMicroTurbine_Impl::fuelHigherHeatingValue() const {
  if (auto value = getDouble(openstudio::Generator_MicroTurbineFields::FuelHigherHeatingValue, false)) {
    return *value;
  }
  return 50000.0;
}

bool GeneratorMicroTurbine_Impl::isFuelHigherHeatingValueDefaulted() const {
  return isEmpty(openstudio::Generator_MicroTurbineFields::FuelHigherHeatingValue);
}

bool GeneratorMicroTurbine_Impl::setFuelHigherHeatingValue(double fuelHigherHeatingValue) {
  return setDouble(openstudio::Generator_MicroTurbineFields::FuelHigherHeatingValue, fuelHigherHeatingValue);
}

void GeneratorMicroTurbine_Impl::resetFuelHigherHeatingValue() {
  OS_ASSERT(setString(openstudio::Generator_MicroTurbineFields::FuelHigherHeatingValue, ""));
}

double GeneratorMicroTurbine_Impl::fuelLowerHeatingValue() const {
  if (auto value = getDouble(openstudio::Generator_MicroTurbineFields::FuelLowerHeatingValue, false)) {
    return *value;
  }
  return 45450.0;
}

bool GeneratorMicroTurbine_Impl::isFuelLowerHeatingValueDefaulted() const {
  return isEmpty(openstudio::Generator_MicroTurbineFields::FuelLowerHeatingValue);
}

bool GeneratorMicroTurbine_Impl::setFuelLowerHeatingValue(double fuelLowerHeatingValue) {
  return setDouble(openstudio::Generator_MicroTurbineFields::FuelLowerHeatingValue, fuelLowerHeatingValue);
}

void GeneratorMicroTurbine_Impl::resetFuelLowerHeatingValue() {
  OS_ASSERT(setString(openstudio::Generator_MicroTurbineFields::FuelLowerHeatingValue, ""));
}

double GeneratorMicroTurbine_Impl::standbyPower() const {
  if (auto value = getDouble(openstudio::Generator_MicroTurbineFields::StandbyPower, false)) {
    return *value;
  }
  return 0.0;
}

bool GeneratorMicroTurbine_Impl::isStandbyPowerDefaulted() const {
  return isEmpty(openstudio::Generator_MicroTurbineFields::StandbyPower);
}

bool GeneratorMicroTurbine_Impl::setStandbyPower(double standbyPower) {
  return setDouble(openstudio::Generator_MicroTurbineFields::StandbyPower, standbyPower);
}

void GeneratorMicroTurbine_Impl::resetStandbyPower() {
  OS_ASSERT(setString(openstudio::Generator_MicroTurbineFields::StandbyPower, ""));
}

double GeneratorMicroTurbine_Impl::ancillaryPower() const {
  if (auto value = getDouble(openstudio::Generator_MicroTurbineFields::AncillaryPower, false)) {
    return *value;
  }
  return 0.0;
}

bool GeneratorMicroTurbine_Impl::isAncillaryPowerDefaulted() const {
  return isEmpty(openstudio::Generator_MicroTurbineFields::AncillaryPower);
}

bool GeneratorMicroTurbine_Impl::setAncillaryPower(double ancillaryPower) {
  return setDouble(openstudio::Generator_MicroTurbineFields::AncillaryPower, ancillaryPower);
}

void GeneratorMicroTurbine_Impl::resetAncillaryPower() {
  OS_ASSERT(setString(openstudio::Generator_MicroTurbineFields::AncillaryPower, ""));
}

boost::optional<double> GeneratorMicroTurbine_Impl::referenceExhaustAirMassFlowRate() const {
  return getDouble(openstudio::Generator_MicroTurbineFields::ReferenceExhaustAirMassFlowRate, true);
}

bool GeneratorMicroTurbine_Impl::setReferenceExhaustAirMassFlowRate(double referenceExhaustAirMassFlowRate) {
  return setDouble(openstudio::Generator_MicroTurbineFields::ReferenceExhaustAirMassFlowRate, referenceExhaustAirMassFlowRate);
}

void GeneratorMicroTurbine_Impl::resetReferenceExhaustAirMassFlowRate() {
  OS_ASSERT(setString(openstudio::Generator_MicroTurbineFields::ReferenceExhaustAirMassFlowRate, ""));
}

boost::optional<double> GeneratorMicroTurbine_Impl::nominalExhaustAirOutletTemperature() const {
  return getDouble(openstudio::Generator_MicroTurbineFields::NominalExhaustAirOutletTemperature, true);
}

bool GeneratorMicroTurbine_Impl::setNominalExhaustAirOutletTemperature(double nominalExhaustAirOutletTemperature) {
  const bool result =
    setDouble(openstudio::Generator_MicroTurbineFields::NominalExhaustAirOutletTemperature, nominalExhaustAirOutletTemperature);
  OS_ASSERT(result);
  return result;
}

void GeneratorMicroTurbine_Impl::resetNominalExhaustAirOutletTemperature() {
  OS_ASSERT(setString(openstudio::Generator_MicroTurbineFields::NominalExhaustAirOutletTemperature, ""));
}

std::vector<std::string> GeneratorMicroTurbine_Impl::validFuelTypeValues() const {
  return openstudio::epmodel::GeneratorMicroTurbine::validFuelTypeValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
