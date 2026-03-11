/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SiteGroundTemperatureUndisturbedXing.hpp"
#include "SiteGroundTemperatureUndisturbedXing_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Site_GroundTemperature_Undisturbed_Xing_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

SiteGroundTemperatureUndisturbedXing::SiteGroundTemperatureUndisturbedXing(const Model& model)
  : ModelObject(SiteGroundTemperatureUndisturbedXing::iddObjectType(), model) {
  OS_ASSERT(getImpl<detail::SiteGroundTemperatureUndisturbedXing_Impl>());

  bool ok = true;
  ok = setSoilThermalConductivity(1.08);  // E+ docs
  OS_ASSERT(ok);
  ok = setSoilDensity(962.0);  // E+ docs
  OS_ASSERT(ok);
  ok = setSoilSpecificHeat(2576.0);  // E+ docs
  OS_ASSERT(ok);
  ok = setAverageSoilSurfaceTemperature(11.1);  // E+ docs
  OS_ASSERT(ok);
  ok = setSoilSurfaceTemperatureAmplitude1(13.4);  // E+ docs
  OS_ASSERT(ok);
  ok = setSoilSurfaceTemperatureAmplitude2(0.7);  // E+ docs
  OS_ASSERT(ok);
  ok = setPhaseShiftofTemperatureAmplitude1(25.0);  // E+ docs
  OS_ASSERT(ok);
  ok = setPhaseShiftofTemperatureAmplitude2(30.0);  // E+ docs
  OS_ASSERT(ok);
}

SiteGroundTemperatureUndisturbedXing::SiteGroundTemperatureUndisturbedXing(
  std::shared_ptr<detail::SiteGroundTemperatureUndisturbedXing_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType SiteGroundTemperatureUndisturbedXing::iddObjectType() {
  return IddObjectType::Site_GroundTemperature_Undisturbed_Xing;
}

double SiteGroundTemperatureUndisturbedXing::soilThermalConductivity() const {
  return getImpl<detail::SiteGroundTemperatureUndisturbedXing_Impl>()->soilThermalConductivity();
}

double SiteGroundTemperatureUndisturbedXing::soilDensity() const {
  return getImpl<detail::SiteGroundTemperatureUndisturbedXing_Impl>()->soilDensity();
}

double SiteGroundTemperatureUndisturbedXing::soilSpecificHeat() const {
  return getImpl<detail::SiteGroundTemperatureUndisturbedXing_Impl>()->soilSpecificHeat();
}

double SiteGroundTemperatureUndisturbedXing::averageSoilSurfaceTemperature() const {
  return getImpl<detail::SiteGroundTemperatureUndisturbedXing_Impl>()->averageSoilSurfaceTemperature();
}

double SiteGroundTemperatureUndisturbedXing::soilSurfaceTemperatureAmplitude1() const {
  return getImpl<detail::SiteGroundTemperatureUndisturbedXing_Impl>()->soilSurfaceTemperatureAmplitude1();
}

double SiteGroundTemperatureUndisturbedXing::soilSurfaceTemperatureAmplitude2() const {
  return getImpl<detail::SiteGroundTemperatureUndisturbedXing_Impl>()->soilSurfaceTemperatureAmplitude2();
}

double SiteGroundTemperatureUndisturbedXing::phaseShiftofTemperatureAmplitude1() const {
  return getImpl<detail::SiteGroundTemperatureUndisturbedXing_Impl>()->phaseShiftofTemperatureAmplitude1();
}

double SiteGroundTemperatureUndisturbedXing::phaseShiftofTemperatureAmplitude2() const {
  return getImpl<detail::SiteGroundTemperatureUndisturbedXing_Impl>()->phaseShiftofTemperatureAmplitude2();
}

bool SiteGroundTemperatureUndisturbedXing::setSoilThermalConductivity(double soilThermalConductivity) {
  return getImpl<detail::SiteGroundTemperatureUndisturbedXing_Impl>()->setSoilThermalConductivity(soilThermalConductivity);
}

bool SiteGroundTemperatureUndisturbedXing::setSoilDensity(double soilDensity) {
  return getImpl<detail::SiteGroundTemperatureUndisturbedXing_Impl>()->setSoilDensity(soilDensity);
}

bool SiteGroundTemperatureUndisturbedXing::setSoilSpecificHeat(double soilSpecificHeat) {
  return getImpl<detail::SiteGroundTemperatureUndisturbedXing_Impl>()->setSoilSpecificHeat(soilSpecificHeat);
}

bool SiteGroundTemperatureUndisturbedXing::setAverageSoilSurfaceTemperature(double averageSoilSurfaceTemperature) {
  return getImpl<detail::SiteGroundTemperatureUndisturbedXing_Impl>()->setAverageSoilSurfaceTemperature(averageSoilSurfaceTemperature);
}

bool SiteGroundTemperatureUndisturbedXing::setSoilSurfaceTemperatureAmplitude1(double soilSurfaceTemperatureAmplitude1) {
  return getImpl<detail::SiteGroundTemperatureUndisturbedXing_Impl>()->setSoilSurfaceTemperatureAmplitude1(soilSurfaceTemperatureAmplitude1);
}

bool SiteGroundTemperatureUndisturbedXing::setSoilSurfaceTemperatureAmplitude2(double soilSurfaceTemperatureAmplitude2) {
  return getImpl<detail::SiteGroundTemperatureUndisturbedXing_Impl>()->setSoilSurfaceTemperatureAmplitude2(soilSurfaceTemperatureAmplitude2);
}

bool SiteGroundTemperatureUndisturbedXing::setPhaseShiftofTemperatureAmplitude1(double phaseShiftofTemperatureAmplitude1) {
  return getImpl<detail::SiteGroundTemperatureUndisturbedXing_Impl>()->setPhaseShiftofTemperatureAmplitude1(
    phaseShiftofTemperatureAmplitude1);
}

bool SiteGroundTemperatureUndisturbedXing::setPhaseShiftofTemperatureAmplitude2(double phaseShiftofTemperatureAmplitude2) {
  return getImpl<detail::SiteGroundTemperatureUndisturbedXing_Impl>()->setPhaseShiftofTemperatureAmplitude2(
    phaseShiftofTemperatureAmplitude2);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

// Schema alignment implementation notes:
// - Accessor names/signatures are preserved from openstudio::model counterpart API.
// - Scalar field mapping is one-to-one with Site_GroundTemperature_Undisturbed_XingFields.
// - Required getters enforce strictness via asserted presence.
double SiteGroundTemperatureUndisturbedXing_Impl::soilThermalConductivity() const {
  const auto value = getDouble(openstudio::Site_GroundTemperature_Undisturbed_XingFields::SoilThermalConductivity, true);
  OS_ASSERT(value);
  return *value;
}

double SiteGroundTemperatureUndisturbedXing_Impl::soilDensity() const {
  const auto value = getDouble(openstudio::Site_GroundTemperature_Undisturbed_XingFields::SoilDensity, true);
  OS_ASSERT(value);
  return *value;
}

double SiteGroundTemperatureUndisturbedXing_Impl::soilSpecificHeat() const {
  const auto value = getDouble(openstudio::Site_GroundTemperature_Undisturbed_XingFields::SoilSpecificHeat, true);
  OS_ASSERT(value);
  return *value;
}

double SiteGroundTemperatureUndisturbedXing_Impl::averageSoilSurfaceTemperature() const {
  const auto value = getDouble(openstudio::Site_GroundTemperature_Undisturbed_XingFields::AverageSoilSurfaceTemperature, true);
  OS_ASSERT(value);
  return *value;
}

double SiteGroundTemperatureUndisturbedXing_Impl::soilSurfaceTemperatureAmplitude1() const {
  const auto value = getDouble(openstudio::Site_GroundTemperature_Undisturbed_XingFields::SoilSurfaceTemperatureAmplitude1, true);
  OS_ASSERT(value);
  return *value;
}

double SiteGroundTemperatureUndisturbedXing_Impl::soilSurfaceTemperatureAmplitude2() const {
  const auto value = getDouble(openstudio::Site_GroundTemperature_Undisturbed_XingFields::SoilSurfaceTemperatureAmplitude2, true);
  OS_ASSERT(value);
  return *value;
}

double SiteGroundTemperatureUndisturbedXing_Impl::phaseShiftofTemperatureAmplitude1() const {
  const auto value = getDouble(openstudio::Site_GroundTemperature_Undisturbed_XingFields::PhaseShiftofTemperatureAmplitude1, true);
  OS_ASSERT(value);
  return *value;
}

double SiteGroundTemperatureUndisturbedXing_Impl::phaseShiftofTemperatureAmplitude2() const {
  const auto value = getDouble(openstudio::Site_GroundTemperature_Undisturbed_XingFields::PhaseShiftofTemperatureAmplitude2, true);
  OS_ASSERT(value);
  return *value;
}

bool SiteGroundTemperatureUndisturbedXing_Impl::setSoilThermalConductivity(double soilThermalConductivity) {
  const bool result = setDouble(openstudio::Site_GroundTemperature_Undisturbed_XingFields::SoilThermalConductivity, soilThermalConductivity);
  OS_ASSERT(result);
  return result;
}

bool SiteGroundTemperatureUndisturbedXing_Impl::setSoilDensity(double soilDensity) {
  const bool result = setDouble(openstudio::Site_GroundTemperature_Undisturbed_XingFields::SoilDensity, soilDensity);
  OS_ASSERT(result);
  return result;
}

bool SiteGroundTemperatureUndisturbedXing_Impl::setSoilSpecificHeat(double soilSpecificHeat) {
  const bool result = setDouble(openstudio::Site_GroundTemperature_Undisturbed_XingFields::SoilSpecificHeat, soilSpecificHeat);
  OS_ASSERT(result);
  return result;
}

bool SiteGroundTemperatureUndisturbedXing_Impl::setAverageSoilSurfaceTemperature(double averageSoilSurfaceTemperature) {
  const bool result =
    setDouble(openstudio::Site_GroundTemperature_Undisturbed_XingFields::AverageSoilSurfaceTemperature, averageSoilSurfaceTemperature);
  OS_ASSERT(result);
  return result;
}

bool SiteGroundTemperatureUndisturbedXing_Impl::setSoilSurfaceTemperatureAmplitude1(double soilSurfaceTemperatureAmplitude1) {
  const bool result = setDouble(openstudio::Site_GroundTemperature_Undisturbed_XingFields::SoilSurfaceTemperatureAmplitude1,
                                soilSurfaceTemperatureAmplitude1);
  OS_ASSERT(result);
  return result;
}

bool SiteGroundTemperatureUndisturbedXing_Impl::setSoilSurfaceTemperatureAmplitude2(double soilSurfaceTemperatureAmplitude2) {
  const bool result = setDouble(openstudio::Site_GroundTemperature_Undisturbed_XingFields::SoilSurfaceTemperatureAmplitude2,
                                soilSurfaceTemperatureAmplitude2);
  OS_ASSERT(result);
  return result;
}

bool SiteGroundTemperatureUndisturbedXing_Impl::setPhaseShiftofTemperatureAmplitude1(double phaseShiftofTemperatureAmplitude1) {
  const bool result = setDouble(openstudio::Site_GroundTemperature_Undisturbed_XingFields::PhaseShiftofTemperatureAmplitude1,
                                phaseShiftofTemperatureAmplitude1);
  OS_ASSERT(result);
  return result;
}

bool SiteGroundTemperatureUndisturbedXing_Impl::setPhaseShiftofTemperatureAmplitude2(double phaseShiftofTemperatureAmplitude2) {
  const bool result = setDouble(openstudio::Site_GroundTemperature_Undisturbed_XingFields::PhaseShiftofTemperatureAmplitude2,
                                phaseShiftofTemperatureAmplitude2);
  OS_ASSERT(result);
  return result;
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
