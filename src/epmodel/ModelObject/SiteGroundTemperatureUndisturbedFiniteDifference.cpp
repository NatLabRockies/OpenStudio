/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SiteGroundTemperatureUndisturbedFiniteDifference.hpp"
#include "SiteGroundTemperatureUndisturbedFiniteDifference_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Site_GroundTemperature_Undisturbed_FiniteDifference_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

SiteGroundTemperatureUndisturbedFiniteDifference::SiteGroundTemperatureUndisturbedFiniteDifference(const Model& model)
  : ModelObject(SiteGroundTemperatureUndisturbedFiniteDifference::iddObjectType(), model) {
  OS_ASSERT(getImpl<detail::SiteGroundTemperatureUndisturbedFiniteDifference_Impl>());

  bool ok = true;
  ok = setSoilThermalConductivity(1.08);  // E+ docs
  OS_ASSERT(ok);
  ok = setSoilDensity(962.0);  // E+ docs
  OS_ASSERT(ok);
  ok = setSoilSpecificHeat(2576.0);  // E+ docs
  OS_ASSERT(ok);
}

SiteGroundTemperatureUndisturbedFiniteDifference::SiteGroundTemperatureUndisturbedFiniteDifference(
  std::shared_ptr<detail::SiteGroundTemperatureUndisturbedFiniteDifference_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType SiteGroundTemperatureUndisturbedFiniteDifference::iddObjectType() {
  return IddObjectType::Site_GroundTemperature_Undisturbed_FiniteDifference;
}

double SiteGroundTemperatureUndisturbedFiniteDifference::soilThermalConductivity() const {
  return getImpl<detail::SiteGroundTemperatureUndisturbedFiniteDifference_Impl>()->soilThermalConductivity();
}

double SiteGroundTemperatureUndisturbedFiniteDifference::soilDensity() const {
  return getImpl<detail::SiteGroundTemperatureUndisturbedFiniteDifference_Impl>()->soilDensity();
}

double SiteGroundTemperatureUndisturbedFiniteDifference::soilSpecificHeat() const {
  return getImpl<detail::SiteGroundTemperatureUndisturbedFiniteDifference_Impl>()->soilSpecificHeat();
}

double SiteGroundTemperatureUndisturbedFiniteDifference::soilMoistureContentVolumeFraction() const {
  return getImpl<detail::SiteGroundTemperatureUndisturbedFiniteDifference_Impl>()->soilMoistureContentVolumeFraction();
}

bool SiteGroundTemperatureUndisturbedFiniteDifference::isSoilMoistureContentVolumeFractionDefaulted() const {
  return getImpl<detail::SiteGroundTemperatureUndisturbedFiniteDifference_Impl>()->isSoilMoistureContentVolumeFractionDefaulted();
}

double SiteGroundTemperatureUndisturbedFiniteDifference::soilMoistureContentVolumeFractionatSaturation() const {
  return getImpl<detail::SiteGroundTemperatureUndisturbedFiniteDifference_Impl>()->soilMoistureContentVolumeFractionatSaturation();
}

bool SiteGroundTemperatureUndisturbedFiniteDifference::isSoilMoistureContentVolumeFractionatSaturationDefaulted() const {
  return getImpl<detail::SiteGroundTemperatureUndisturbedFiniteDifference_Impl>()->isSoilMoistureContentVolumeFractionatSaturationDefaulted();
}

double SiteGroundTemperatureUndisturbedFiniteDifference::evapotranspirationGroundCoverParameter() const {
  return getImpl<detail::SiteGroundTemperatureUndisturbedFiniteDifference_Impl>()->evapotranspirationGroundCoverParameter();
}

bool SiteGroundTemperatureUndisturbedFiniteDifference::isEvapotranspirationGroundCoverParameterDefaulted() const {
  return getImpl<detail::SiteGroundTemperatureUndisturbedFiniteDifference_Impl>()->isEvapotranspirationGroundCoverParameterDefaulted();
}

bool SiteGroundTemperatureUndisturbedFiniteDifference::setSoilThermalConductivity(double soilThermalConductivity) {
  return getImpl<detail::SiteGroundTemperatureUndisturbedFiniteDifference_Impl>()->setSoilThermalConductivity(soilThermalConductivity);
}

bool SiteGroundTemperatureUndisturbedFiniteDifference::setSoilDensity(double soilDensity) {
  return getImpl<detail::SiteGroundTemperatureUndisturbedFiniteDifference_Impl>()->setSoilDensity(soilDensity);
}

bool SiteGroundTemperatureUndisturbedFiniteDifference::setSoilSpecificHeat(double soilSpecificHeat) {
  return getImpl<detail::SiteGroundTemperatureUndisturbedFiniteDifference_Impl>()->setSoilSpecificHeat(soilSpecificHeat);
}

bool SiteGroundTemperatureUndisturbedFiniteDifference::setSoilMoistureContentVolumeFraction(double soilMoistureContentVolumeFraction) {
  return getImpl<detail::SiteGroundTemperatureUndisturbedFiniteDifference_Impl>()->setSoilMoistureContentVolumeFraction(
    soilMoistureContentVolumeFraction);
}

bool SiteGroundTemperatureUndisturbedFiniteDifference::setSoilMoistureContentVolumeFractionatSaturation(
  double soilMoistureContentVolumeFractionatSaturation) {
  return getImpl<detail::SiteGroundTemperatureUndisturbedFiniteDifference_Impl>()->setSoilMoistureContentVolumeFractionatSaturation(
    soilMoistureContentVolumeFractionatSaturation);
}

bool SiteGroundTemperatureUndisturbedFiniteDifference::setEvapotranspirationGroundCoverParameter(
  double evapotranspirationGroundCoverParameter) {
  return getImpl<detail::SiteGroundTemperatureUndisturbedFiniteDifference_Impl>()->setEvapotranspirationGroundCoverParameter(
    evapotranspirationGroundCoverParameter);
}

void SiteGroundTemperatureUndisturbedFiniteDifference::resetSoilMoistureContentVolumeFraction() {
  getImpl<detail::SiteGroundTemperatureUndisturbedFiniteDifference_Impl>()->resetSoilMoistureContentVolumeFraction();
}

void SiteGroundTemperatureUndisturbedFiniteDifference::resetSoilMoistureContentVolumeFractionatSaturation() {
  getImpl<detail::SiteGroundTemperatureUndisturbedFiniteDifference_Impl>()->resetSoilMoistureContentVolumeFractionatSaturation();
}

void SiteGroundTemperatureUndisturbedFiniteDifference::resetEvapotranspirationGroundCoverParameter() {
  getImpl<detail::SiteGroundTemperatureUndisturbedFiniteDifference_Impl>()->resetEvapotranspirationGroundCoverParameter();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

double SiteGroundTemperatureUndisturbedFiniteDifference_Impl::soilThermalConductivity() const {
  const auto value = getDouble(openstudio::Site_GroundTemperature_Undisturbed_FiniteDifferenceFields::SoilThermalConductivity, true);
  OS_ASSERT(value);
  return *value;
}

double SiteGroundTemperatureUndisturbedFiniteDifference_Impl::soilDensity() const {
  const auto value = getDouble(openstudio::Site_GroundTemperature_Undisturbed_FiniteDifferenceFields::SoilDensity, true);
  OS_ASSERT(value);
  return *value;
}

double SiteGroundTemperatureUndisturbedFiniteDifference_Impl::soilSpecificHeat() const {
  const auto value = getDouble(openstudio::Site_GroundTemperature_Undisturbed_FiniteDifferenceFields::SoilSpecificHeat, true);
  OS_ASSERT(value);
  return *value;
}

double SiteGroundTemperatureUndisturbedFiniteDifference_Impl::soilMoistureContentVolumeFraction() const {
  const auto value = getDouble(openstudio::Site_GroundTemperature_Undisturbed_FiniteDifferenceFields::SoilMoistureContentVolumeFraction, true);
  OS_ASSERT(value);
  return *value;
}

bool SiteGroundTemperatureUndisturbedFiniteDifference_Impl::isSoilMoistureContentVolumeFractionDefaulted() const {
  return isEmpty(openstudio::Site_GroundTemperature_Undisturbed_FiniteDifferenceFields::SoilMoistureContentVolumeFraction);
}

double SiteGroundTemperatureUndisturbedFiniteDifference_Impl::soilMoistureContentVolumeFractionatSaturation() const {
  const auto value =
    getDouble(openstudio::Site_GroundTemperature_Undisturbed_FiniteDifferenceFields::SoilMoistureContentVolumeFractionatSaturation, true);
  OS_ASSERT(value);
  return *value;
}

bool SiteGroundTemperatureUndisturbedFiniteDifference_Impl::isSoilMoistureContentVolumeFractionatSaturationDefaulted() const {
  return isEmpty(openstudio::Site_GroundTemperature_Undisturbed_FiniteDifferenceFields::SoilMoistureContentVolumeFractionatSaturation);
}

double SiteGroundTemperatureUndisturbedFiniteDifference_Impl::evapotranspirationGroundCoverParameter() const {
  const auto value =
    getDouble(openstudio::Site_GroundTemperature_Undisturbed_FiniteDifferenceFields::EvapotranspirationGroundCoverParameter, true);
  OS_ASSERT(value);
  return *value;
}

bool SiteGroundTemperatureUndisturbedFiniteDifference_Impl::isEvapotranspirationGroundCoverParameterDefaulted() const {
  return isEmpty(openstudio::Site_GroundTemperature_Undisturbed_FiniteDifferenceFields::EvapotranspirationGroundCoverParameter);
}

bool SiteGroundTemperatureUndisturbedFiniteDifference_Impl::setSoilThermalConductivity(double soilThermalConductivity) {
  const bool result = setDouble(openstudio::Site_GroundTemperature_Undisturbed_FiniteDifferenceFields::SoilThermalConductivity,
                                soilThermalConductivity);
  OS_ASSERT(result);
  return result;
}

bool SiteGroundTemperatureUndisturbedFiniteDifference_Impl::setSoilDensity(double soilDensity) {
  const bool result = setDouble(openstudio::Site_GroundTemperature_Undisturbed_FiniteDifferenceFields::SoilDensity, soilDensity);
  OS_ASSERT(result);
  return result;
}

bool SiteGroundTemperatureUndisturbedFiniteDifference_Impl::setSoilSpecificHeat(double soilSpecificHeat) {
  const bool result = setDouble(openstudio::Site_GroundTemperature_Undisturbed_FiniteDifferenceFields::SoilSpecificHeat, soilSpecificHeat);
  OS_ASSERT(result);
  return result;
}

bool SiteGroundTemperatureUndisturbedFiniteDifference_Impl::setSoilMoistureContentVolumeFraction(double soilMoistureContentVolumeFraction) {
  const bool result = setDouble(openstudio::Site_GroundTemperature_Undisturbed_FiniteDifferenceFields::SoilMoistureContentVolumeFraction,
                                soilMoistureContentVolumeFraction);
  OS_ASSERT(result);
  return result;
}

bool SiteGroundTemperatureUndisturbedFiniteDifference_Impl::setSoilMoistureContentVolumeFractionatSaturation(
  double soilMoistureContentVolumeFractionatSaturation) {
  const bool result = setDouble(
    openstudio::Site_GroundTemperature_Undisturbed_FiniteDifferenceFields::SoilMoistureContentVolumeFractionatSaturation,
    soilMoistureContentVolumeFractionatSaturation);
  OS_ASSERT(result);
  return result;
}

bool SiteGroundTemperatureUndisturbedFiniteDifference_Impl::setEvapotranspirationGroundCoverParameter(
  double evapotranspirationGroundCoverParameter) {
  const bool result = setDouble(openstudio::Site_GroundTemperature_Undisturbed_FiniteDifferenceFields::EvapotranspirationGroundCoverParameter,
                                evapotranspirationGroundCoverParameter);
  OS_ASSERT(result);
  return result;
}

void SiteGroundTemperatureUndisturbedFiniteDifference_Impl::resetSoilMoistureContentVolumeFraction() {
  OS_ASSERT(setString(openstudio::Site_GroundTemperature_Undisturbed_FiniteDifferenceFields::SoilMoistureContentVolumeFraction, ""));
}

void SiteGroundTemperatureUndisturbedFiniteDifference_Impl::resetSoilMoistureContentVolumeFractionatSaturation() {
  OS_ASSERT(setString(openstudio::Site_GroundTemperature_Undisturbed_FiniteDifferenceFields::SoilMoistureContentVolumeFractionatSaturation, ""));
}

void SiteGroundTemperatureUndisturbedFiniteDifference_Impl::resetEvapotranspirationGroundCoverParameter() {
  OS_ASSERT(setString(openstudio::Site_GroundTemperature_Undisturbed_FiniteDifferenceFields::EvapotranspirationGroundCoverParameter, ""));
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
