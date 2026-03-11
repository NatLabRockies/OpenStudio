/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SiteGroundTemperatureUndisturbedKusudaAchenbach.hpp"
#include "SiteGroundTemperatureUndisturbedKusudaAchenbach_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Site_GroundTemperature_Undisturbed_KusudaAchenbach_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

SiteGroundTemperatureUndisturbedKusudaAchenbach::SiteGroundTemperatureUndisturbedKusudaAchenbach(const Model& model)
  : ModelObject(SiteGroundTemperatureUndisturbedKusudaAchenbach::iddObjectType(), model) {
  OS_ASSERT(getImpl<detail::SiteGroundTemperatureUndisturbedKusudaAchenbach_Impl>());

  bool ok = true;
  ok = setSoilThermalConductivity(1.08);  // E+ docs
  OS_ASSERT(ok);
  ok = setSoilDensity(962.0);  // E+ docs
  OS_ASSERT(ok);
  ok = setSoilSpecificHeat(2576.0);  // E+ docs
  OS_ASSERT(ok);
  ok = setAverageSoilSurfaceTemperature(15.5);
  OS_ASSERT(ok);
  ok = setAverageAmplitudeofSurfaceTemperature(12.8);
  OS_ASSERT(ok);
  ok = setPhaseShiftofMinimumSurfaceTemperature(17.3);
  OS_ASSERT(ok);
}

SiteGroundTemperatureUndisturbedKusudaAchenbach::SiteGroundTemperatureUndisturbedKusudaAchenbach(
  std::shared_ptr<detail::SiteGroundTemperatureUndisturbedKusudaAchenbach_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType SiteGroundTemperatureUndisturbedKusudaAchenbach::iddObjectType() {
  return IddObjectType::Site_GroundTemperature_Undisturbed_KusudaAchenbach;
}

double SiteGroundTemperatureUndisturbedKusudaAchenbach::soilThermalConductivity() const {
  return getImpl<detail::SiteGroundTemperatureUndisturbedKusudaAchenbach_Impl>()->soilThermalConductivity();
}

double SiteGroundTemperatureUndisturbedKusudaAchenbach::soilDensity() const {
  return getImpl<detail::SiteGroundTemperatureUndisturbedKusudaAchenbach_Impl>()->soilDensity();
}

double SiteGroundTemperatureUndisturbedKusudaAchenbach::soilSpecificHeat() const {
  return getImpl<detail::SiteGroundTemperatureUndisturbedKusudaAchenbach_Impl>()->soilSpecificHeat();
}

boost::optional<double> SiteGroundTemperatureUndisturbedKusudaAchenbach::averageSoilSurfaceTemperature() const {
  return getImpl<detail::SiteGroundTemperatureUndisturbedKusudaAchenbach_Impl>()->averageSoilSurfaceTemperature();
}

boost::optional<double> SiteGroundTemperatureUndisturbedKusudaAchenbach::averageAmplitudeofSurfaceTemperature() const {
  return getImpl<detail::SiteGroundTemperatureUndisturbedKusudaAchenbach_Impl>()->averageAmplitudeofSurfaceTemperature();
}

boost::optional<double> SiteGroundTemperatureUndisturbedKusudaAchenbach::phaseShiftofMinimumSurfaceTemperature() const {
  return getImpl<detail::SiteGroundTemperatureUndisturbedKusudaAchenbach_Impl>()->phaseShiftofMinimumSurfaceTemperature();
}

bool SiteGroundTemperatureUndisturbedKusudaAchenbach::setSoilThermalConductivity(double soilThermalConductivity) {
  return getImpl<detail::SiteGroundTemperatureUndisturbedKusudaAchenbach_Impl>()->setSoilThermalConductivity(soilThermalConductivity);
}

bool SiteGroundTemperatureUndisturbedKusudaAchenbach::setSoilDensity(double soilDensity) {
  return getImpl<detail::SiteGroundTemperatureUndisturbedKusudaAchenbach_Impl>()->setSoilDensity(soilDensity);
}

bool SiteGroundTemperatureUndisturbedKusudaAchenbach::setSoilSpecificHeat(double soilSpecificHeat) {
  return getImpl<detail::SiteGroundTemperatureUndisturbedKusudaAchenbach_Impl>()->setSoilSpecificHeat(soilSpecificHeat);
}

bool SiteGroundTemperatureUndisturbedKusudaAchenbach::setAverageSoilSurfaceTemperature(double averageSoilSurfaceTemperature) {
  return getImpl<detail::SiteGroundTemperatureUndisturbedKusudaAchenbach_Impl>()->setAverageSoilSurfaceTemperature(averageSoilSurfaceTemperature);
}

void SiteGroundTemperatureUndisturbedKusudaAchenbach::resetAverageSoilSurfaceTemperature() {
  getImpl<detail::SiteGroundTemperatureUndisturbedKusudaAchenbach_Impl>()->resetAverageSoilSurfaceTemperature();
}

bool SiteGroundTemperatureUndisturbedKusudaAchenbach::setAverageAmplitudeofSurfaceTemperature(double averageAmplitudeofSurfaceTemperature) {
  return getImpl<detail::SiteGroundTemperatureUndisturbedKusudaAchenbach_Impl>()->setAverageAmplitudeofSurfaceTemperature(
    averageAmplitudeofSurfaceTemperature);
}

void SiteGroundTemperatureUndisturbedKusudaAchenbach::resetAverageAmplitudeofSurfaceTemperature() {
  getImpl<detail::SiteGroundTemperatureUndisturbedKusudaAchenbach_Impl>()->resetAverageAmplitudeofSurfaceTemperature();
}

bool SiteGroundTemperatureUndisturbedKusudaAchenbach::setPhaseShiftofMinimumSurfaceTemperature(double phaseShiftofMinimumSurfaceTemperature) {
  return getImpl<detail::SiteGroundTemperatureUndisturbedKusudaAchenbach_Impl>()->setPhaseShiftofMinimumSurfaceTemperature(
    phaseShiftofMinimumSurfaceTemperature);
}

void SiteGroundTemperatureUndisturbedKusudaAchenbach::resetPhaseShiftofMinimumSurfaceTemperature() {
  getImpl<detail::SiteGroundTemperatureUndisturbedKusudaAchenbach_Impl>()->resetPhaseShiftofMinimumSurfaceTemperature();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

// Schema alignment implementation notes:
// - Accessor names follow openstudio::model counterpart API.
// - Field mapping is one-to-one with Site_GroundTemperature_Undisturbed_KusudaAchenbachFields values.
// - Required getters enforce strictness via asserted presence.
double SiteGroundTemperatureUndisturbedKusudaAchenbach_Impl::soilThermalConductivity() const {
  const auto value = getDouble(openstudio::Site_GroundTemperature_Undisturbed_KusudaAchenbachFields::SoilThermalConductivity, true);
  OS_ASSERT(value);
  return *value;
}

double SiteGroundTemperatureUndisturbedKusudaAchenbach_Impl::soilDensity() const {
  const auto value = getDouble(openstudio::Site_GroundTemperature_Undisturbed_KusudaAchenbachFields::SoilDensity, true);
  OS_ASSERT(value);
  return *value;
}

double SiteGroundTemperatureUndisturbedKusudaAchenbach_Impl::soilSpecificHeat() const {
  const auto value = getDouble(openstudio::Site_GroundTemperature_Undisturbed_KusudaAchenbachFields::SoilSpecificHeat, true);
  OS_ASSERT(value);
  return *value;
}

boost::optional<double> SiteGroundTemperatureUndisturbedKusudaAchenbach_Impl::averageSoilSurfaceTemperature() const {
  return getDouble(openstudio::Site_GroundTemperature_Undisturbed_KusudaAchenbachFields::AverageSoilSurfaceTemperature, true);
}

boost::optional<double> SiteGroundTemperatureUndisturbedKusudaAchenbach_Impl::averageAmplitudeofSurfaceTemperature() const {
  return getDouble(openstudio::Site_GroundTemperature_Undisturbed_KusudaAchenbachFields::AverageAmplitudeofSurfaceTemperature, true);
}

boost::optional<double> SiteGroundTemperatureUndisturbedKusudaAchenbach_Impl::phaseShiftofMinimumSurfaceTemperature() const {
  return getDouble(openstudio::Site_GroundTemperature_Undisturbed_KusudaAchenbachFields::PhaseShiftofMinimumSurfaceTemperature, true);
}

bool SiteGroundTemperatureUndisturbedKusudaAchenbach_Impl::setSoilThermalConductivity(double soilThermalConductivity) {
  const bool result =
    setDouble(openstudio::Site_GroundTemperature_Undisturbed_KusudaAchenbachFields::SoilThermalConductivity, soilThermalConductivity);
  OS_ASSERT(result);
  return result;
}

bool SiteGroundTemperatureUndisturbedKusudaAchenbach_Impl::setSoilDensity(double soilDensity) {
  const bool result = setDouble(openstudio::Site_GroundTemperature_Undisturbed_KusudaAchenbachFields::SoilDensity, soilDensity);
  OS_ASSERT(result);
  return result;
}

bool SiteGroundTemperatureUndisturbedKusudaAchenbach_Impl::setSoilSpecificHeat(double soilSpecificHeat) {
  const bool result = setDouble(openstudio::Site_GroundTemperature_Undisturbed_KusudaAchenbachFields::SoilSpecificHeat, soilSpecificHeat);
  OS_ASSERT(result);
  return result;
}

bool SiteGroundTemperatureUndisturbedKusudaAchenbach_Impl::setAverageSoilSurfaceTemperature(double averageSoilSurfaceTemperature) {
  const bool result = setDouble(openstudio::Site_GroundTemperature_Undisturbed_KusudaAchenbachFields::AverageSoilSurfaceTemperature,
                                averageSoilSurfaceTemperature);
  OS_ASSERT(result);
  return result;
}

void SiteGroundTemperatureUndisturbedKusudaAchenbach_Impl::resetAverageSoilSurfaceTemperature() {
  OS_ASSERT(setString(openstudio::Site_GroundTemperature_Undisturbed_KusudaAchenbachFields::AverageSoilSurfaceTemperature, ""));
}

bool SiteGroundTemperatureUndisturbedKusudaAchenbach_Impl::setAverageAmplitudeofSurfaceTemperature(
  double averageAmplitudeofSurfaceTemperature) {
  const bool result = setDouble(openstudio::Site_GroundTemperature_Undisturbed_KusudaAchenbachFields::AverageAmplitudeofSurfaceTemperature,
                                averageAmplitudeofSurfaceTemperature);
  OS_ASSERT(result);
  return result;
}

void SiteGroundTemperatureUndisturbedKusudaAchenbach_Impl::resetAverageAmplitudeofSurfaceTemperature() {
  OS_ASSERT(setString(openstudio::Site_GroundTemperature_Undisturbed_KusudaAchenbachFields::AverageAmplitudeofSurfaceTemperature, ""));
}

bool SiteGroundTemperatureUndisturbedKusudaAchenbach_Impl::setPhaseShiftofMinimumSurfaceTemperature(
  double phaseShiftofMinimumSurfaceTemperature) {
  const bool result = setDouble(openstudio::Site_GroundTemperature_Undisturbed_KusudaAchenbachFields::PhaseShiftofMinimumSurfaceTemperature,
                                phaseShiftofMinimumSurfaceTemperature);
  OS_ASSERT(result);
  return result;
}

void SiteGroundTemperatureUndisturbedKusudaAchenbach_Impl::resetPhaseShiftofMinimumSurfaceTemperature() {
  OS_ASSERT(setString(openstudio::Site_GroundTemperature_Undisturbed_KusudaAchenbachFields::PhaseShiftofMinimumSurfaceTemperature, ""));
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
