/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ElectricLoadCenterTransformer.hpp"
#include "ElectricLoadCenterTransformer_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/ElectricLoadCenter_Transformer_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

ElectricLoadCenterTransformer::ElectricLoadCenterTransformer(const Model& model)
  : ModelObject(ElectricLoadCenterTransformer::iddObjectType(), model) {}

ElectricLoadCenterTransformer::ElectricLoadCenterTransformer(std::shared_ptr<detail::ElectricLoadCenterTransformer_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType ElectricLoadCenterTransformer::iddObjectType() {
  return IddObjectType::ElectricLoadCenter_Transformer;
}

std::vector<std::string> ElectricLoadCenterTransformer::transformerUsageValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::ElectricLoadCenter_TransformerFields::TransformerUsage);
}

std::vector<std::string> ElectricLoadCenterTransformer::phaseValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::ElectricLoadCenter_TransformerFields::Phase);
}

std::vector<std::string> ElectricLoadCenterTransformer::conductorMaterialValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::ElectricLoadCenter_TransformerFields::ConductorMaterial);
}

std::vector<std::string> ElectricLoadCenterTransformer::performanceInputMethodValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::ElectricLoadCenter_TransformerFields::PerformanceInputMethod);
}

std::string ElectricLoadCenterTransformer::transformerUsage() const {
  return getImpl<detail::ElectricLoadCenterTransformer_Impl>()->transformerUsage();
}

bool ElectricLoadCenterTransformer::isTransformerUsageDefaulted() const {
  return getImpl<detail::ElectricLoadCenterTransformer_Impl>()->isTransformerUsageDefaulted();
}

bool ElectricLoadCenterTransformer::setTransformerUsage(const std::string& transformerUsage) {
  return getImpl<detail::ElectricLoadCenterTransformer_Impl>()->setTransformerUsage(transformerUsage);
}

void ElectricLoadCenterTransformer::resetTransformerUsage() {
  getImpl<detail::ElectricLoadCenterTransformer_Impl>()->resetTransformerUsage();
}

double ElectricLoadCenterTransformer::radiativeFraction() const {
  return getImpl<detail::ElectricLoadCenterTransformer_Impl>()->radiativeFraction();
}

bool ElectricLoadCenterTransformer::isRadiativeFractionDefaulted() const {
  return getImpl<detail::ElectricLoadCenterTransformer_Impl>()->isRadiativeFractionDefaulted();
}

bool ElectricLoadCenterTransformer::setRadiativeFraction(double radiativeFraction) {
  return getImpl<detail::ElectricLoadCenterTransformer_Impl>()->setRadiativeFraction(radiativeFraction);
}

void ElectricLoadCenterTransformer::resetRadiativeFraction() {
  getImpl<detail::ElectricLoadCenterTransformer_Impl>()->resetRadiativeFraction();
}

boost::optional<double> ElectricLoadCenterTransformer::ratedCapacity() const {
  return getImpl<detail::ElectricLoadCenterTransformer_Impl>()->ratedCapacity();
}

bool ElectricLoadCenterTransformer::setRatedCapacity(double ratedCapacity) {
  return getImpl<detail::ElectricLoadCenterTransformer_Impl>()->setRatedCapacity(ratedCapacity);
}

void ElectricLoadCenterTransformer::resetRatedCapacity() {
  getImpl<detail::ElectricLoadCenterTransformer_Impl>()->resetRatedCapacity();
}

std::string ElectricLoadCenterTransformer::phase() const {
  return getImpl<detail::ElectricLoadCenterTransformer_Impl>()->phase();
}

bool ElectricLoadCenterTransformer::isPhaseDefaulted() const {
  return getImpl<detail::ElectricLoadCenterTransformer_Impl>()->isPhaseDefaulted();
}

bool ElectricLoadCenterTransformer::setPhase(const std::string& phase) {
  return getImpl<detail::ElectricLoadCenterTransformer_Impl>()->setPhase(phase);
}

void ElectricLoadCenterTransformer::resetPhase() {
  getImpl<detail::ElectricLoadCenterTransformer_Impl>()->resetPhase();
}

std::string ElectricLoadCenterTransformer::conductorMaterial() const {
  return getImpl<detail::ElectricLoadCenterTransformer_Impl>()->conductorMaterial();
}

bool ElectricLoadCenterTransformer::isConductorMaterialDefaulted() const {
  return getImpl<detail::ElectricLoadCenterTransformer_Impl>()->isConductorMaterialDefaulted();
}

bool ElectricLoadCenterTransformer::setConductorMaterial(const std::string& conductorMaterial) {
  return getImpl<detail::ElectricLoadCenterTransformer_Impl>()->setConductorMaterial(conductorMaterial);
}

void ElectricLoadCenterTransformer::resetConductorMaterial() {
  getImpl<detail::ElectricLoadCenterTransformer_Impl>()->resetConductorMaterial();
}

double ElectricLoadCenterTransformer::fullLoadTemperatureRise() const {
  return getImpl<detail::ElectricLoadCenterTransformer_Impl>()->fullLoadTemperatureRise();
}

bool ElectricLoadCenterTransformer::isFullLoadTemperatureRiseDefaulted() const {
  return getImpl<detail::ElectricLoadCenterTransformer_Impl>()->isFullLoadTemperatureRiseDefaulted();
}

bool ElectricLoadCenterTransformer::setFullLoadTemperatureRise(double fullLoadTemperatureRise) {
  return getImpl<detail::ElectricLoadCenterTransformer_Impl>()->setFullLoadTemperatureRise(fullLoadTemperatureRise);
}

void ElectricLoadCenterTransformer::resetFullLoadTemperatureRise() {
  getImpl<detail::ElectricLoadCenterTransformer_Impl>()->resetFullLoadTemperatureRise();
}

double ElectricLoadCenterTransformer::fractionofEddyCurrentLosses() const {
  return getImpl<detail::ElectricLoadCenterTransformer_Impl>()->fractionofEddyCurrentLosses();
}

bool ElectricLoadCenterTransformer::isFractionofEddyCurrentLossesDefaulted() const {
  return getImpl<detail::ElectricLoadCenterTransformer_Impl>()->isFractionofEddyCurrentLossesDefaulted();
}

bool ElectricLoadCenterTransformer::setFractionofEddyCurrentLosses(double fractionofEddyCurrentLosses) {
  return getImpl<detail::ElectricLoadCenterTransformer_Impl>()->setFractionofEddyCurrentLosses(fractionofEddyCurrentLosses);
}

void ElectricLoadCenterTransformer::resetFractionofEddyCurrentLosses() {
  getImpl<detail::ElectricLoadCenterTransformer_Impl>()->resetFractionofEddyCurrentLosses();
}

std::string ElectricLoadCenterTransformer::performanceInputMethod() const {
  return getImpl<detail::ElectricLoadCenterTransformer_Impl>()->performanceInputMethod();
}

bool ElectricLoadCenterTransformer::isPerformanceInputMethodDefaulted() const {
  return getImpl<detail::ElectricLoadCenterTransformer_Impl>()->isPerformanceInputMethodDefaulted();
}

bool ElectricLoadCenterTransformer::setPerformanceInputMethod(const std::string& performanceInputMethod) {
  return getImpl<detail::ElectricLoadCenterTransformer_Impl>()->setPerformanceInputMethod(performanceInputMethod);
}

void ElectricLoadCenterTransformer::resetPerformanceInputMethod() {
  getImpl<detail::ElectricLoadCenterTransformer_Impl>()->resetPerformanceInputMethod();
}

boost::optional<double> ElectricLoadCenterTransformer::ratedNoLoadLoss() const {
  return getImpl<detail::ElectricLoadCenterTransformer_Impl>()->ratedNoLoadLoss();
}

bool ElectricLoadCenterTransformer::setRatedNoLoadLoss(double ratedNoLoadLoss) {
  return getImpl<detail::ElectricLoadCenterTransformer_Impl>()->setRatedNoLoadLoss(ratedNoLoadLoss);
}

void ElectricLoadCenterTransformer::resetRatedNoLoadLoss() {
  getImpl<detail::ElectricLoadCenterTransformer_Impl>()->resetRatedNoLoadLoss();
}

boost::optional<double> ElectricLoadCenterTransformer::ratedLoadLoss() const {
  return getImpl<detail::ElectricLoadCenterTransformer_Impl>()->ratedLoadLoss();
}

bool ElectricLoadCenterTransformer::setRatedLoadLoss(double ratedLoadLoss) {
  return getImpl<detail::ElectricLoadCenterTransformer_Impl>()->setRatedLoadLoss(ratedLoadLoss);
}

void ElectricLoadCenterTransformer::resetRatedLoadLoss() {
  getImpl<detail::ElectricLoadCenterTransformer_Impl>()->resetRatedLoadLoss();
}

double ElectricLoadCenterTransformer::nameplateEfficiency() const {
  return getImpl<detail::ElectricLoadCenterTransformer_Impl>()->nameplateEfficiency();
}

bool ElectricLoadCenterTransformer::isNameplateEfficiencyDefaulted() const {
  return getImpl<detail::ElectricLoadCenterTransformer_Impl>()->isNameplateEfficiencyDefaulted();
}

bool ElectricLoadCenterTransformer::setNameplateEfficiency(double nameplateEfficiency) {
  return getImpl<detail::ElectricLoadCenterTransformer_Impl>()->setNameplateEfficiency(nameplateEfficiency);
}

void ElectricLoadCenterTransformer::resetNameplateEfficiency() {
  getImpl<detail::ElectricLoadCenterTransformer_Impl>()->resetNameplateEfficiency();
}

double ElectricLoadCenterTransformer::perUnitLoadforNameplateEfficiency() const {
  return getImpl<detail::ElectricLoadCenterTransformer_Impl>()->perUnitLoadforNameplateEfficiency();
}

bool ElectricLoadCenterTransformer::isPerUnitLoadforNameplateEfficiencyDefaulted() const {
  return getImpl<detail::ElectricLoadCenterTransformer_Impl>()->isPerUnitLoadforNameplateEfficiencyDefaulted();
}

bool ElectricLoadCenterTransformer::setPerUnitLoadforNameplateEfficiency(double perUnitLoadforNameplateEfficiency) {
  return getImpl<detail::ElectricLoadCenterTransformer_Impl>()->setPerUnitLoadforNameplateEfficiency(perUnitLoadforNameplateEfficiency);
}

void ElectricLoadCenterTransformer::resetPerUnitLoadforNameplateEfficiency() {
  getImpl<detail::ElectricLoadCenterTransformer_Impl>()->resetPerUnitLoadforNameplateEfficiency();
}

double ElectricLoadCenterTransformer::referenceTemperatureforNameplateEfficiency() const {
  return getImpl<detail::ElectricLoadCenterTransformer_Impl>()->referenceTemperatureforNameplateEfficiency();
}

bool ElectricLoadCenterTransformer::isReferenceTemperatureforNameplateEfficiencyDefaulted() const {
  return getImpl<detail::ElectricLoadCenterTransformer_Impl>()->isReferenceTemperatureforNameplateEfficiencyDefaulted();
}

bool ElectricLoadCenterTransformer::setReferenceTemperatureforNameplateEfficiency(double referenceTemperatureforNameplateEfficiency) {
  return getImpl<detail::ElectricLoadCenterTransformer_Impl>()->setReferenceTemperatureforNameplateEfficiency(
    referenceTemperatureforNameplateEfficiency);
}

void ElectricLoadCenterTransformer::resetReferenceTemperatureforNameplateEfficiency() {
  getImpl<detail::ElectricLoadCenterTransformer_Impl>()->resetReferenceTemperatureforNameplateEfficiency();
}

boost::optional<double> ElectricLoadCenterTransformer::perUnitLoadforMaximumEfficiency() const {
  return getImpl<detail::ElectricLoadCenterTransformer_Impl>()->perUnitLoadforMaximumEfficiency();
}

bool ElectricLoadCenterTransformer::setPerUnitLoadforMaximumEfficiency(double perUnitLoadforMaximumEfficiency) {
  return getImpl<detail::ElectricLoadCenterTransformer_Impl>()->setPerUnitLoadforMaximumEfficiency(perUnitLoadforMaximumEfficiency);
}

void ElectricLoadCenterTransformer::resetPerUnitLoadforMaximumEfficiency() {
  getImpl<detail::ElectricLoadCenterTransformer_Impl>()->resetPerUnitLoadforMaximumEfficiency();
}

bool ElectricLoadCenterTransformer::considerTransformerLossforUtilityCost() const {
  return getImpl<detail::ElectricLoadCenterTransformer_Impl>()->considerTransformerLossforUtilityCost();
}

bool ElectricLoadCenterTransformer::isConsiderTransformerLossforUtilityCostDefaulted() const {
  return getImpl<detail::ElectricLoadCenterTransformer_Impl>()->isConsiderTransformerLossforUtilityCostDefaulted();
}

bool ElectricLoadCenterTransformer::setConsiderTransformerLossforUtilityCost(bool considerTransformerLossforUtilityCost) {
  return getImpl<detail::ElectricLoadCenterTransformer_Impl>()->setConsiderTransformerLossforUtilityCost(
    considerTransformerLossforUtilityCost);
}

void ElectricLoadCenterTransformer::resetConsiderTransformerLossforUtilityCost() {
  getImpl<detail::ElectricLoadCenterTransformer_Impl>()->resetConsiderTransformerLossforUtilityCost();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string ElectricLoadCenterTransformer_Impl::transformerUsage() const {
  const auto value = getString(openstudio::ElectricLoadCenter_TransformerFields::TransformerUsage, true);
  OS_ASSERT(value);
  return *value;
}

bool ElectricLoadCenterTransformer_Impl::isTransformerUsageDefaulted() const {
  return isEmpty(openstudio::ElectricLoadCenter_TransformerFields::TransformerUsage);
}

bool ElectricLoadCenterTransformer_Impl::setTransformerUsage(const std::string& transformerUsage) {
  return setString(openstudio::ElectricLoadCenter_TransformerFields::TransformerUsage, transformerUsage);
}

void ElectricLoadCenterTransformer_Impl::resetTransformerUsage() {
  OS_ASSERT(setString(openstudio::ElectricLoadCenter_TransformerFields::TransformerUsage, ""));
}

double ElectricLoadCenterTransformer_Impl::radiativeFraction() const {
  const auto value = getDouble(openstudio::ElectricLoadCenter_TransformerFields::RadiativeFraction, true);
  OS_ASSERT(value);
  return *value;
}

bool ElectricLoadCenterTransformer_Impl::isRadiativeFractionDefaulted() const {
  return isEmpty(openstudio::ElectricLoadCenter_TransformerFields::RadiativeFraction);
}

bool ElectricLoadCenterTransformer_Impl::setRadiativeFraction(double radiativeFraction) {
  const bool result = setDouble(openstudio::ElectricLoadCenter_TransformerFields::RadiativeFraction, radiativeFraction);
  OS_ASSERT(result);
  return result;
}

void ElectricLoadCenterTransformer_Impl::resetRadiativeFraction() {
  OS_ASSERT(setString(openstudio::ElectricLoadCenter_TransformerFields::RadiativeFraction, ""));
}

boost::optional<double> ElectricLoadCenterTransformer_Impl::ratedCapacity() const {
  return getDouble(openstudio::ElectricLoadCenter_TransformerFields::RatedCapacity, true);
}

bool ElectricLoadCenterTransformer_Impl::setRatedCapacity(double ratedCapacity) {
  const bool result = setDouble(openstudio::ElectricLoadCenter_TransformerFields::RatedCapacity, ratedCapacity);
  OS_ASSERT(result);
  return result;
}

void ElectricLoadCenterTransformer_Impl::resetRatedCapacity() {
  OS_ASSERT(setString(openstudio::ElectricLoadCenter_TransformerFields::RatedCapacity, ""));
}

std::string ElectricLoadCenterTransformer_Impl::phase() const {
  const auto value = getString(openstudio::ElectricLoadCenter_TransformerFields::Phase, true);
  OS_ASSERT(value);
  return *value;
}

bool ElectricLoadCenterTransformer_Impl::isPhaseDefaulted() const {
  return isEmpty(openstudio::ElectricLoadCenter_TransformerFields::Phase);
}

bool ElectricLoadCenterTransformer_Impl::setPhase(const std::string& phase) {
  return setString(openstudio::ElectricLoadCenter_TransformerFields::Phase, phase);
}

void ElectricLoadCenterTransformer_Impl::resetPhase() {
  OS_ASSERT(setString(openstudio::ElectricLoadCenter_TransformerFields::Phase, ""));
}

std::string ElectricLoadCenterTransformer_Impl::conductorMaterial() const {
  const auto value = getString(openstudio::ElectricLoadCenter_TransformerFields::ConductorMaterial, true);
  OS_ASSERT(value);
  return *value;
}

bool ElectricLoadCenterTransformer_Impl::isConductorMaterialDefaulted() const {
  return isEmpty(openstudio::ElectricLoadCenter_TransformerFields::ConductorMaterial);
}

bool ElectricLoadCenterTransformer_Impl::setConductorMaterial(const std::string& conductorMaterial) {
  return setString(openstudio::ElectricLoadCenter_TransformerFields::ConductorMaterial, conductorMaterial);
}

void ElectricLoadCenterTransformer_Impl::resetConductorMaterial() {
  OS_ASSERT(setString(openstudio::ElectricLoadCenter_TransformerFields::ConductorMaterial, ""));
}

double ElectricLoadCenterTransformer_Impl::fullLoadTemperatureRise() const {
  const auto value = getDouble(openstudio::ElectricLoadCenter_TransformerFields::FullLoadTemperatureRise, true);
  OS_ASSERT(value);
  return *value;
}

bool ElectricLoadCenterTransformer_Impl::isFullLoadTemperatureRiseDefaulted() const {
  return isEmpty(openstudio::ElectricLoadCenter_TransformerFields::FullLoadTemperatureRise);
}

bool ElectricLoadCenterTransformer_Impl::setFullLoadTemperatureRise(double fullLoadTemperatureRise) {
  const bool result = setDouble(openstudio::ElectricLoadCenter_TransformerFields::FullLoadTemperatureRise, fullLoadTemperatureRise);
  OS_ASSERT(result);
  return result;
}

void ElectricLoadCenterTransformer_Impl::resetFullLoadTemperatureRise() {
  OS_ASSERT(setString(openstudio::ElectricLoadCenter_TransformerFields::FullLoadTemperatureRise, ""));
}

double ElectricLoadCenterTransformer_Impl::fractionofEddyCurrentLosses() const {
  const auto value = getDouble(openstudio::ElectricLoadCenter_TransformerFields::FractionofEddyCurrentLosses, true);
  OS_ASSERT(value);
  return *value;
}

bool ElectricLoadCenterTransformer_Impl::isFractionofEddyCurrentLossesDefaulted() const {
  return isEmpty(openstudio::ElectricLoadCenter_TransformerFields::FractionofEddyCurrentLosses);
}

bool ElectricLoadCenterTransformer_Impl::setFractionofEddyCurrentLosses(double fractionofEddyCurrentLosses) {
  const bool result =
    setDouble(openstudio::ElectricLoadCenter_TransformerFields::FractionofEddyCurrentLosses, fractionofEddyCurrentLosses);
  OS_ASSERT(result);
  return result;
}

void ElectricLoadCenterTransformer_Impl::resetFractionofEddyCurrentLosses() {
  OS_ASSERT(setString(openstudio::ElectricLoadCenter_TransformerFields::FractionofEddyCurrentLosses, ""));
}

std::string ElectricLoadCenterTransformer_Impl::performanceInputMethod() const {
  const auto value = getString(openstudio::ElectricLoadCenter_TransformerFields::PerformanceInputMethod, true);
  OS_ASSERT(value);
  return *value;
}

bool ElectricLoadCenterTransformer_Impl::isPerformanceInputMethodDefaulted() const {
  return isEmpty(openstudio::ElectricLoadCenter_TransformerFields::PerformanceInputMethod);
}

bool ElectricLoadCenterTransformer_Impl::setPerformanceInputMethod(const std::string& performanceInputMethod) {
  return setString(openstudio::ElectricLoadCenter_TransformerFields::PerformanceInputMethod, performanceInputMethod);
}

void ElectricLoadCenterTransformer_Impl::resetPerformanceInputMethod() {
  OS_ASSERT(setString(openstudio::ElectricLoadCenter_TransformerFields::PerformanceInputMethod, ""));
}

boost::optional<double> ElectricLoadCenterTransformer_Impl::ratedNoLoadLoss() const {
  return getDouble(openstudio::ElectricLoadCenter_TransformerFields::RatedNoLoadLoss, true);
}

bool ElectricLoadCenterTransformer_Impl::setRatedNoLoadLoss(double ratedNoLoadLoss) {
  const bool result = setDouble(openstudio::ElectricLoadCenter_TransformerFields::RatedNoLoadLoss, ratedNoLoadLoss);
  OS_ASSERT(result);
  return result;
}

void ElectricLoadCenterTransformer_Impl::resetRatedNoLoadLoss() {
  OS_ASSERT(setString(openstudio::ElectricLoadCenter_TransformerFields::RatedNoLoadLoss, ""));
}

boost::optional<double> ElectricLoadCenterTransformer_Impl::ratedLoadLoss() const {
  return getDouble(openstudio::ElectricLoadCenter_TransformerFields::RatedLoadLoss, true);
}

bool ElectricLoadCenterTransformer_Impl::setRatedLoadLoss(double ratedLoadLoss) {
  const bool result = setDouble(openstudio::ElectricLoadCenter_TransformerFields::RatedLoadLoss, ratedLoadLoss);
  OS_ASSERT(result);
  return result;
}

void ElectricLoadCenterTransformer_Impl::resetRatedLoadLoss() {
  OS_ASSERT(setString(openstudio::ElectricLoadCenter_TransformerFields::RatedLoadLoss, ""));
}

double ElectricLoadCenterTransformer_Impl::nameplateEfficiency() const {
  const auto value = getDouble(openstudio::ElectricLoadCenter_TransformerFields::NameplateEfficiency, true);
  OS_ASSERT(value);
  return *value;
}

bool ElectricLoadCenterTransformer_Impl::isNameplateEfficiencyDefaulted() const {
  return isEmpty(openstudio::ElectricLoadCenter_TransformerFields::NameplateEfficiency);
}

bool ElectricLoadCenterTransformer_Impl::setNameplateEfficiency(double nameplateEfficiency) {
  const bool result = setDouble(openstudio::ElectricLoadCenter_TransformerFields::NameplateEfficiency, nameplateEfficiency);
  OS_ASSERT(result);
  return result;
}

void ElectricLoadCenterTransformer_Impl::resetNameplateEfficiency() {
  OS_ASSERT(setString(openstudio::ElectricLoadCenter_TransformerFields::NameplateEfficiency, ""));
}

double ElectricLoadCenterTransformer_Impl::perUnitLoadforNameplateEfficiency() const {
  const auto value = getDouble(openstudio::ElectricLoadCenter_TransformerFields::PerUnitLoadforNameplateEfficiency, true);
  OS_ASSERT(value);
  return *value;
}

bool ElectricLoadCenterTransformer_Impl::isPerUnitLoadforNameplateEfficiencyDefaulted() const {
  return isEmpty(openstudio::ElectricLoadCenter_TransformerFields::PerUnitLoadforNameplateEfficiency);
}

bool ElectricLoadCenterTransformer_Impl::setPerUnitLoadforNameplateEfficiency(double perUnitLoadforNameplateEfficiency) {
  const bool result = setDouble(openstudio::ElectricLoadCenter_TransformerFields::PerUnitLoadforNameplateEfficiency,
                                perUnitLoadforNameplateEfficiency);
  OS_ASSERT(result);
  return result;
}

void ElectricLoadCenterTransformer_Impl::resetPerUnitLoadforNameplateEfficiency() {
  OS_ASSERT(setString(openstudio::ElectricLoadCenter_TransformerFields::PerUnitLoadforNameplateEfficiency, ""));
}

double ElectricLoadCenterTransformer_Impl::referenceTemperatureforNameplateEfficiency() const {
  const auto value = getDouble(openstudio::ElectricLoadCenter_TransformerFields::ReferenceTemperatureforNameplateEfficiency, true);
  OS_ASSERT(value);
  return *value;
}

bool ElectricLoadCenterTransformer_Impl::isReferenceTemperatureforNameplateEfficiencyDefaulted() const {
  return isEmpty(openstudio::ElectricLoadCenter_TransformerFields::ReferenceTemperatureforNameplateEfficiency);
}

bool ElectricLoadCenterTransformer_Impl::setReferenceTemperatureforNameplateEfficiency(double referenceTemperatureforNameplateEfficiency) {
  const bool result = setDouble(openstudio::ElectricLoadCenter_TransformerFields::ReferenceTemperatureforNameplateEfficiency,
                                referenceTemperatureforNameplateEfficiency);
  OS_ASSERT(result);
  return result;
}

void ElectricLoadCenterTransformer_Impl::resetReferenceTemperatureforNameplateEfficiency() {
  OS_ASSERT(setString(openstudio::ElectricLoadCenter_TransformerFields::ReferenceTemperatureforNameplateEfficiency, ""));
}

boost::optional<double> ElectricLoadCenterTransformer_Impl::perUnitLoadforMaximumEfficiency() const {
  return getDouble(openstudio::ElectricLoadCenter_TransformerFields::PerUnitLoadforMaximumEfficiency, true);
}

bool ElectricLoadCenterTransformer_Impl::setPerUnitLoadforMaximumEfficiency(double perUnitLoadforMaximumEfficiency) {
  const bool result =
    setDouble(openstudio::ElectricLoadCenter_TransformerFields::PerUnitLoadforMaximumEfficiency, perUnitLoadforMaximumEfficiency);
  OS_ASSERT(result);
  return result;
}

void ElectricLoadCenterTransformer_Impl::resetPerUnitLoadforMaximumEfficiency() {
  OS_ASSERT(setString(openstudio::ElectricLoadCenter_TransformerFields::PerUnitLoadforMaximumEfficiency, ""));
}

bool ElectricLoadCenterTransformer_Impl::considerTransformerLossforUtilityCost() const {
  const auto value = getString(openstudio::ElectricLoadCenter_TransformerFields::ConsiderTransformerLossforUtilityCost, true);
  OS_ASSERT(value);
  return openstudio::istringEqual(*value, "yes");
}

bool ElectricLoadCenterTransformer_Impl::isConsiderTransformerLossforUtilityCostDefaulted() const {
  return isEmpty(openstudio::ElectricLoadCenter_TransformerFields::ConsiderTransformerLossforUtilityCost);
}

bool ElectricLoadCenterTransformer_Impl::setConsiderTransformerLossforUtilityCost(bool considerTransformerLossforUtilityCost) {
  const bool result = setString(openstudio::ElectricLoadCenter_TransformerFields::ConsiderTransformerLossforUtilityCost,
                                considerTransformerLossforUtilityCost ? "Yes" : "No");
  OS_ASSERT(result);
  return result;
}

void ElectricLoadCenterTransformer_Impl::resetConsiderTransformerLossforUtilityCost() {
  OS_ASSERT(setString(openstudio::ElectricLoadCenter_TransformerFields::ConsiderTransformerLossforUtilityCost, ""));
}

std::vector<std::string> ElectricLoadCenterTransformer_Impl::transformerUsageValues() const {
  return openstudio::epmodel::ElectricLoadCenterTransformer::transformerUsageValues();
}

std::vector<std::string> ElectricLoadCenterTransformer_Impl::phaseValues() const {
  return openstudio::epmodel::ElectricLoadCenterTransformer::phaseValues();
}

std::vector<std::string> ElectricLoadCenterTransformer_Impl::conductorMaterialValues() const {
  return openstudio::epmodel::ElectricLoadCenterTransformer::conductorMaterialValues();
}

std::vector<std::string> ElectricLoadCenterTransformer_Impl::performanceInputMethodValues() const {
  return openstudio::epmodel::ElectricLoadCenterTransformer::performanceInputMethodValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
