/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SiteGroundTemperatureFCfactorMethod.hpp"
#include "SiteGroundTemperatureFCfactorMethod_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Site_GroundTemperature_FCfactorMethod_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

SiteGroundTemperatureFCfactorMethod::SiteGroundTemperatureFCfactorMethod(const Model& model)
  : ModelObject(SiteGroundTemperatureFCfactorMethod::iddObjectType(), model) {}

SiteGroundTemperatureFCfactorMethod::SiteGroundTemperatureFCfactorMethod(std::shared_ptr<detail::SiteGroundTemperatureFCfactorMethod_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType SiteGroundTemperatureFCfactorMethod::iddObjectType() {
  return IddObjectType::Site_GroundTemperature_FCfactorMethod;
}

double SiteGroundTemperatureFCfactorMethod::januaryGroundTemperature() const {
  return getImpl<detail::SiteGroundTemperatureFCfactorMethod_Impl>()->januaryGroundTemperature();
}

bool SiteGroundTemperatureFCfactorMethod::isJanuaryGroundTemperatureDefaulted() const {
  return getImpl<detail::SiteGroundTemperatureFCfactorMethod_Impl>()->isJanuaryGroundTemperatureDefaulted();
}

bool SiteGroundTemperatureFCfactorMethod::setJanuaryGroundTemperature(double januaryGroundTemperature) {
  return getImpl<detail::SiteGroundTemperatureFCfactorMethod_Impl>()->setJanuaryGroundTemperature(januaryGroundTemperature);
}

void SiteGroundTemperatureFCfactorMethod::resetJanuaryGroundTemperature() {
  getImpl<detail::SiteGroundTemperatureFCfactorMethod_Impl>()->resetJanuaryGroundTemperature();
}

double SiteGroundTemperatureFCfactorMethod::februaryGroundTemperature() const {
  return getImpl<detail::SiteGroundTemperatureFCfactorMethod_Impl>()->februaryGroundTemperature();
}

bool SiteGroundTemperatureFCfactorMethod::isFebruaryGroundTemperatureDefaulted() const {
  return getImpl<detail::SiteGroundTemperatureFCfactorMethod_Impl>()->isFebruaryGroundTemperatureDefaulted();
}

bool SiteGroundTemperatureFCfactorMethod::setFebruaryGroundTemperature(double februaryGroundTemperature) {
  return getImpl<detail::SiteGroundTemperatureFCfactorMethod_Impl>()->setFebruaryGroundTemperature(februaryGroundTemperature);
}

void SiteGroundTemperatureFCfactorMethod::resetFebruaryGroundTemperature() {
  getImpl<detail::SiteGroundTemperatureFCfactorMethod_Impl>()->resetFebruaryGroundTemperature();
}

double SiteGroundTemperatureFCfactorMethod::marchGroundTemperature() const {
  return getImpl<detail::SiteGroundTemperatureFCfactorMethod_Impl>()->marchGroundTemperature();
}

bool SiteGroundTemperatureFCfactorMethod::isMarchGroundTemperatureDefaulted() const {
  return getImpl<detail::SiteGroundTemperatureFCfactorMethod_Impl>()->isMarchGroundTemperatureDefaulted();
}

bool SiteGroundTemperatureFCfactorMethod::setMarchGroundTemperature(double marchGroundTemperature) {
  return getImpl<detail::SiteGroundTemperatureFCfactorMethod_Impl>()->setMarchGroundTemperature(marchGroundTemperature);
}

void SiteGroundTemperatureFCfactorMethod::resetMarchGroundTemperature() {
  getImpl<detail::SiteGroundTemperatureFCfactorMethod_Impl>()->resetMarchGroundTemperature();
}

double SiteGroundTemperatureFCfactorMethod::aprilGroundTemperature() const {
  return getImpl<detail::SiteGroundTemperatureFCfactorMethod_Impl>()->aprilGroundTemperature();
}

bool SiteGroundTemperatureFCfactorMethod::isAprilGroundTemperatureDefaulted() const {
  return getImpl<detail::SiteGroundTemperatureFCfactorMethod_Impl>()->isAprilGroundTemperatureDefaulted();
}

bool SiteGroundTemperatureFCfactorMethod::setAprilGroundTemperature(double aprilGroundTemperature) {
  return getImpl<detail::SiteGroundTemperatureFCfactorMethod_Impl>()->setAprilGroundTemperature(aprilGroundTemperature);
}

void SiteGroundTemperatureFCfactorMethod::resetAprilGroundTemperature() {
  getImpl<detail::SiteGroundTemperatureFCfactorMethod_Impl>()->resetAprilGroundTemperature();
}

double SiteGroundTemperatureFCfactorMethod::mayGroundTemperature() const {
  return getImpl<detail::SiteGroundTemperatureFCfactorMethod_Impl>()->mayGroundTemperature();
}

bool SiteGroundTemperatureFCfactorMethod::isMayGroundTemperatureDefaulted() const {
  return getImpl<detail::SiteGroundTemperatureFCfactorMethod_Impl>()->isMayGroundTemperatureDefaulted();
}

bool SiteGroundTemperatureFCfactorMethod::setMayGroundTemperature(double mayGroundTemperature) {
  return getImpl<detail::SiteGroundTemperatureFCfactorMethod_Impl>()->setMayGroundTemperature(mayGroundTemperature);
}

void SiteGroundTemperatureFCfactorMethod::resetMayGroundTemperature() {
  getImpl<detail::SiteGroundTemperatureFCfactorMethod_Impl>()->resetMayGroundTemperature();
}

double SiteGroundTemperatureFCfactorMethod::juneGroundTemperature() const {
  return getImpl<detail::SiteGroundTemperatureFCfactorMethod_Impl>()->juneGroundTemperature();
}

bool SiteGroundTemperatureFCfactorMethod::isJuneGroundTemperatureDefaulted() const {
  return getImpl<detail::SiteGroundTemperatureFCfactorMethod_Impl>()->isJuneGroundTemperatureDefaulted();
}

bool SiteGroundTemperatureFCfactorMethod::setJuneGroundTemperature(double juneGroundTemperature) {
  return getImpl<detail::SiteGroundTemperatureFCfactorMethod_Impl>()->setJuneGroundTemperature(juneGroundTemperature);
}

void SiteGroundTemperatureFCfactorMethod::resetJuneGroundTemperature() {
  getImpl<detail::SiteGroundTemperatureFCfactorMethod_Impl>()->resetJuneGroundTemperature();
}

double SiteGroundTemperatureFCfactorMethod::julyGroundTemperature() const {
  return getImpl<detail::SiteGroundTemperatureFCfactorMethod_Impl>()->julyGroundTemperature();
}

bool SiteGroundTemperatureFCfactorMethod::isJulyGroundTemperatureDefaulted() const {
  return getImpl<detail::SiteGroundTemperatureFCfactorMethod_Impl>()->isJulyGroundTemperatureDefaulted();
}

bool SiteGroundTemperatureFCfactorMethod::setJulyGroundTemperature(double julyGroundTemperature) {
  return getImpl<detail::SiteGroundTemperatureFCfactorMethod_Impl>()->setJulyGroundTemperature(julyGroundTemperature);
}

void SiteGroundTemperatureFCfactorMethod::resetJulyGroundTemperature() {
  getImpl<detail::SiteGroundTemperatureFCfactorMethod_Impl>()->resetJulyGroundTemperature();
}

double SiteGroundTemperatureFCfactorMethod::augustGroundTemperature() const {
  return getImpl<detail::SiteGroundTemperatureFCfactorMethod_Impl>()->augustGroundTemperature();
}

bool SiteGroundTemperatureFCfactorMethod::isAugustGroundTemperatureDefaulted() const {
  return getImpl<detail::SiteGroundTemperatureFCfactorMethod_Impl>()->isAugustGroundTemperatureDefaulted();
}

bool SiteGroundTemperatureFCfactorMethod::setAugustGroundTemperature(double augustGroundTemperature) {
  return getImpl<detail::SiteGroundTemperatureFCfactorMethod_Impl>()->setAugustGroundTemperature(augustGroundTemperature);
}

void SiteGroundTemperatureFCfactorMethod::resetAugustGroundTemperature() {
  getImpl<detail::SiteGroundTemperatureFCfactorMethod_Impl>()->resetAugustGroundTemperature();
}

double SiteGroundTemperatureFCfactorMethod::septemberGroundTemperature() const {
  return getImpl<detail::SiteGroundTemperatureFCfactorMethod_Impl>()->septemberGroundTemperature();
}

bool SiteGroundTemperatureFCfactorMethod::isSeptemberGroundTemperatureDefaulted() const {
  return getImpl<detail::SiteGroundTemperatureFCfactorMethod_Impl>()->isSeptemberGroundTemperatureDefaulted();
}

bool SiteGroundTemperatureFCfactorMethod::setSeptemberGroundTemperature(double septemberGroundTemperature) {
  return getImpl<detail::SiteGroundTemperatureFCfactorMethod_Impl>()->setSeptemberGroundTemperature(septemberGroundTemperature);
}

void SiteGroundTemperatureFCfactorMethod::resetSeptemberGroundTemperature() {
  getImpl<detail::SiteGroundTemperatureFCfactorMethod_Impl>()->resetSeptemberGroundTemperature();
}

double SiteGroundTemperatureFCfactorMethod::octoberGroundTemperature() const {
  return getImpl<detail::SiteGroundTemperatureFCfactorMethod_Impl>()->octoberGroundTemperature();
}

bool SiteGroundTemperatureFCfactorMethod::isOctoberGroundTemperatureDefaulted() const {
  return getImpl<detail::SiteGroundTemperatureFCfactorMethod_Impl>()->isOctoberGroundTemperatureDefaulted();
}

bool SiteGroundTemperatureFCfactorMethod::setOctoberGroundTemperature(double octoberGroundTemperature) {
  return getImpl<detail::SiteGroundTemperatureFCfactorMethod_Impl>()->setOctoberGroundTemperature(octoberGroundTemperature);
}

void SiteGroundTemperatureFCfactorMethod::resetOctoberGroundTemperature() {
  getImpl<detail::SiteGroundTemperatureFCfactorMethod_Impl>()->resetOctoberGroundTemperature();
}

double SiteGroundTemperatureFCfactorMethod::novemberGroundTemperature() const {
  return getImpl<detail::SiteGroundTemperatureFCfactorMethod_Impl>()->novemberGroundTemperature();
}

bool SiteGroundTemperatureFCfactorMethod::isNovemberGroundTemperatureDefaulted() const {
  return getImpl<detail::SiteGroundTemperatureFCfactorMethod_Impl>()->isNovemberGroundTemperatureDefaulted();
}

bool SiteGroundTemperatureFCfactorMethod::setNovemberGroundTemperature(double novemberGroundTemperature) {
  return getImpl<detail::SiteGroundTemperatureFCfactorMethod_Impl>()->setNovemberGroundTemperature(novemberGroundTemperature);
}

void SiteGroundTemperatureFCfactorMethod::resetNovemberGroundTemperature() {
  getImpl<detail::SiteGroundTemperatureFCfactorMethod_Impl>()->resetNovemberGroundTemperature();
}

double SiteGroundTemperatureFCfactorMethod::decemberGroundTemperature() const {
  return getImpl<detail::SiteGroundTemperatureFCfactorMethod_Impl>()->decemberGroundTemperature();
}

bool SiteGroundTemperatureFCfactorMethod::isDecemberGroundTemperatureDefaulted() const {
  return getImpl<detail::SiteGroundTemperatureFCfactorMethod_Impl>()->isDecemberGroundTemperatureDefaulted();
}

bool SiteGroundTemperatureFCfactorMethod::setDecemberGroundTemperature(double decemberGroundTemperature) {
  return getImpl<detail::SiteGroundTemperatureFCfactorMethod_Impl>()->setDecemberGroundTemperature(decemberGroundTemperature);
}

void SiteGroundTemperatureFCfactorMethod::resetDecemberGroundTemperature() {
  getImpl<detail::SiteGroundTemperatureFCfactorMethod_Impl>()->resetDecemberGroundTemperature();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

// Ruby generator parity:
// - Required double getters assert presence.
// - Setters return bool and assert success for non-failable scalar fields.
// - Resets clear fields to allow IDD defaults.
double SiteGroundTemperatureFCfactorMethod_Impl::januaryGroundTemperature() const {
  const auto value = getDouble(openstudio::Site_GroundTemperature_FCfactorMethodFields::JanuaryGroundTemperature, true);
  OS_ASSERT(value);
  return value.get();
}

bool SiteGroundTemperatureFCfactorMethod_Impl::isJanuaryGroundTemperatureDefaulted() const {
  return isEmpty(openstudio::Site_GroundTemperature_FCfactorMethodFields::JanuaryGroundTemperature);
}

bool SiteGroundTemperatureFCfactorMethod_Impl::setJanuaryGroundTemperature(double januaryGroundTemperature) {
  const bool result = setDouble(openstudio::Site_GroundTemperature_FCfactorMethodFields::JanuaryGroundTemperature, januaryGroundTemperature);
  OS_ASSERT(result);
  return result;
}

void SiteGroundTemperatureFCfactorMethod_Impl::resetJanuaryGroundTemperature() {
  const bool result = setString(openstudio::Site_GroundTemperature_FCfactorMethodFields::JanuaryGroundTemperature, "");
  OS_ASSERT(result);
}

double SiteGroundTemperatureFCfactorMethod_Impl::februaryGroundTemperature() const {
  const auto value = getDouble(openstudio::Site_GroundTemperature_FCfactorMethodFields::FebruaryGroundTemperature, true);
  OS_ASSERT(value);
  return value.get();
}

bool SiteGroundTemperatureFCfactorMethod_Impl::isFebruaryGroundTemperatureDefaulted() const {
  return isEmpty(openstudio::Site_GroundTemperature_FCfactorMethodFields::FebruaryGroundTemperature);
}

bool SiteGroundTemperatureFCfactorMethod_Impl::setFebruaryGroundTemperature(double februaryGroundTemperature) {
  const bool result = setDouble(openstudio::Site_GroundTemperature_FCfactorMethodFields::FebruaryGroundTemperature, februaryGroundTemperature);
  OS_ASSERT(result);
  return result;
}

void SiteGroundTemperatureFCfactorMethod_Impl::resetFebruaryGroundTemperature() {
  const bool result = setString(openstudio::Site_GroundTemperature_FCfactorMethodFields::FebruaryGroundTemperature, "");
  OS_ASSERT(result);
}

double SiteGroundTemperatureFCfactorMethod_Impl::marchGroundTemperature() const {
  const auto value = getDouble(openstudio::Site_GroundTemperature_FCfactorMethodFields::MarchGroundTemperature, true);
  OS_ASSERT(value);
  return value.get();
}

bool SiteGroundTemperatureFCfactorMethod_Impl::isMarchGroundTemperatureDefaulted() const {
  return isEmpty(openstudio::Site_GroundTemperature_FCfactorMethodFields::MarchGroundTemperature);
}

bool SiteGroundTemperatureFCfactorMethod_Impl::setMarchGroundTemperature(double marchGroundTemperature) {
  const bool result = setDouble(openstudio::Site_GroundTemperature_FCfactorMethodFields::MarchGroundTemperature, marchGroundTemperature);
  OS_ASSERT(result);
  return result;
}

void SiteGroundTemperatureFCfactorMethod_Impl::resetMarchGroundTemperature() {
  const bool result = setString(openstudio::Site_GroundTemperature_FCfactorMethodFields::MarchGroundTemperature, "");
  OS_ASSERT(result);
}

double SiteGroundTemperatureFCfactorMethod_Impl::aprilGroundTemperature() const {
  const auto value = getDouble(openstudio::Site_GroundTemperature_FCfactorMethodFields::AprilGroundTemperature, true);
  OS_ASSERT(value);
  return value.get();
}

bool SiteGroundTemperatureFCfactorMethod_Impl::isAprilGroundTemperatureDefaulted() const {
  return isEmpty(openstudio::Site_GroundTemperature_FCfactorMethodFields::AprilGroundTemperature);
}

bool SiteGroundTemperatureFCfactorMethod_Impl::setAprilGroundTemperature(double aprilGroundTemperature) {
  const bool result = setDouble(openstudio::Site_GroundTemperature_FCfactorMethodFields::AprilGroundTemperature, aprilGroundTemperature);
  OS_ASSERT(result);
  return result;
}

void SiteGroundTemperatureFCfactorMethod_Impl::resetAprilGroundTemperature() {
  const bool result = setString(openstudio::Site_GroundTemperature_FCfactorMethodFields::AprilGroundTemperature, "");
  OS_ASSERT(result);
}

double SiteGroundTemperatureFCfactorMethod_Impl::mayGroundTemperature() const {
  const auto value = getDouble(openstudio::Site_GroundTemperature_FCfactorMethodFields::MayGroundTemperature, true);
  OS_ASSERT(value);
  return value.get();
}

bool SiteGroundTemperatureFCfactorMethod_Impl::isMayGroundTemperatureDefaulted() const {
  return isEmpty(openstudio::Site_GroundTemperature_FCfactorMethodFields::MayGroundTemperature);
}

bool SiteGroundTemperatureFCfactorMethod_Impl::setMayGroundTemperature(double mayGroundTemperature) {
  const bool result = setDouble(openstudio::Site_GroundTemperature_FCfactorMethodFields::MayGroundTemperature, mayGroundTemperature);
  OS_ASSERT(result);
  return result;
}

void SiteGroundTemperatureFCfactorMethod_Impl::resetMayGroundTemperature() {
  const bool result = setString(openstudio::Site_GroundTemperature_FCfactorMethodFields::MayGroundTemperature, "");
  OS_ASSERT(result);
}

double SiteGroundTemperatureFCfactorMethod_Impl::juneGroundTemperature() const {
  const auto value = getDouble(openstudio::Site_GroundTemperature_FCfactorMethodFields::JuneGroundTemperature, true);
  OS_ASSERT(value);
  return value.get();
}

bool SiteGroundTemperatureFCfactorMethod_Impl::isJuneGroundTemperatureDefaulted() const {
  return isEmpty(openstudio::Site_GroundTemperature_FCfactorMethodFields::JuneGroundTemperature);
}

bool SiteGroundTemperatureFCfactorMethod_Impl::setJuneGroundTemperature(double juneGroundTemperature) {
  const bool result = setDouble(openstudio::Site_GroundTemperature_FCfactorMethodFields::JuneGroundTemperature, juneGroundTemperature);
  OS_ASSERT(result);
  return result;
}

void SiteGroundTemperatureFCfactorMethod_Impl::resetJuneGroundTemperature() {
  const bool result = setString(openstudio::Site_GroundTemperature_FCfactorMethodFields::JuneGroundTemperature, "");
  OS_ASSERT(result);
}

double SiteGroundTemperatureFCfactorMethod_Impl::julyGroundTemperature() const {
  const auto value = getDouble(openstudio::Site_GroundTemperature_FCfactorMethodFields::JulyGroundTemperature, true);
  OS_ASSERT(value);
  return value.get();
}

bool SiteGroundTemperatureFCfactorMethod_Impl::isJulyGroundTemperatureDefaulted() const {
  return isEmpty(openstudio::Site_GroundTemperature_FCfactorMethodFields::JulyGroundTemperature);
}

bool SiteGroundTemperatureFCfactorMethod_Impl::setJulyGroundTemperature(double julyGroundTemperature) {
  const bool result = setDouble(openstudio::Site_GroundTemperature_FCfactorMethodFields::JulyGroundTemperature, julyGroundTemperature);
  OS_ASSERT(result);
  return result;
}

void SiteGroundTemperatureFCfactorMethod_Impl::resetJulyGroundTemperature() {
  const bool result = setString(openstudio::Site_GroundTemperature_FCfactorMethodFields::JulyGroundTemperature, "");
  OS_ASSERT(result);
}

double SiteGroundTemperatureFCfactorMethod_Impl::augustGroundTemperature() const {
  const auto value = getDouble(openstudio::Site_GroundTemperature_FCfactorMethodFields::AugustGroundTemperature, true);
  OS_ASSERT(value);
  return value.get();
}

bool SiteGroundTemperatureFCfactorMethod_Impl::isAugustGroundTemperatureDefaulted() const {
  return isEmpty(openstudio::Site_GroundTemperature_FCfactorMethodFields::AugustGroundTemperature);
}

bool SiteGroundTemperatureFCfactorMethod_Impl::setAugustGroundTemperature(double augustGroundTemperature) {
  const bool result = setDouble(openstudio::Site_GroundTemperature_FCfactorMethodFields::AugustGroundTemperature, augustGroundTemperature);
  OS_ASSERT(result);
  return result;
}

void SiteGroundTemperatureFCfactorMethod_Impl::resetAugustGroundTemperature() {
  const bool result = setString(openstudio::Site_GroundTemperature_FCfactorMethodFields::AugustGroundTemperature, "");
  OS_ASSERT(result);
}

double SiteGroundTemperatureFCfactorMethod_Impl::septemberGroundTemperature() const {
  const auto value = getDouble(openstudio::Site_GroundTemperature_FCfactorMethodFields::SeptemberGroundTemperature, true);
  OS_ASSERT(value);
  return value.get();
}

bool SiteGroundTemperatureFCfactorMethod_Impl::isSeptemberGroundTemperatureDefaulted() const {
  return isEmpty(openstudio::Site_GroundTemperature_FCfactorMethodFields::SeptemberGroundTemperature);
}

bool SiteGroundTemperatureFCfactorMethod_Impl::setSeptemberGroundTemperature(double septemberGroundTemperature) {
  const bool result = setDouble(openstudio::Site_GroundTemperature_FCfactorMethodFields::SeptemberGroundTemperature, septemberGroundTemperature);
  OS_ASSERT(result);
  return result;
}

void SiteGroundTemperatureFCfactorMethod_Impl::resetSeptemberGroundTemperature() {
  const bool result = setString(openstudio::Site_GroundTemperature_FCfactorMethodFields::SeptemberGroundTemperature, "");
  OS_ASSERT(result);
}

double SiteGroundTemperatureFCfactorMethod_Impl::octoberGroundTemperature() const {
  const auto value = getDouble(openstudio::Site_GroundTemperature_FCfactorMethodFields::OctoberGroundTemperature, true);
  OS_ASSERT(value);
  return value.get();
}

bool SiteGroundTemperatureFCfactorMethod_Impl::isOctoberGroundTemperatureDefaulted() const {
  return isEmpty(openstudio::Site_GroundTemperature_FCfactorMethodFields::OctoberGroundTemperature);
}

bool SiteGroundTemperatureFCfactorMethod_Impl::setOctoberGroundTemperature(double octoberGroundTemperature) {
  const bool result = setDouble(openstudio::Site_GroundTemperature_FCfactorMethodFields::OctoberGroundTemperature, octoberGroundTemperature);
  OS_ASSERT(result);
  return result;
}

void SiteGroundTemperatureFCfactorMethod_Impl::resetOctoberGroundTemperature() {
  const bool result = setString(openstudio::Site_GroundTemperature_FCfactorMethodFields::OctoberGroundTemperature, "");
  OS_ASSERT(result);
}

double SiteGroundTemperatureFCfactorMethod_Impl::novemberGroundTemperature() const {
  const auto value = getDouble(openstudio::Site_GroundTemperature_FCfactorMethodFields::NovemberGroundTemperature, true);
  OS_ASSERT(value);
  return value.get();
}

bool SiteGroundTemperatureFCfactorMethod_Impl::isNovemberGroundTemperatureDefaulted() const {
  return isEmpty(openstudio::Site_GroundTemperature_FCfactorMethodFields::NovemberGroundTemperature);
}

bool SiteGroundTemperatureFCfactorMethod_Impl::setNovemberGroundTemperature(double novemberGroundTemperature) {
  const bool result = setDouble(openstudio::Site_GroundTemperature_FCfactorMethodFields::NovemberGroundTemperature, novemberGroundTemperature);
  OS_ASSERT(result);
  return result;
}

void SiteGroundTemperatureFCfactorMethod_Impl::resetNovemberGroundTemperature() {
  const bool result = setString(openstudio::Site_GroundTemperature_FCfactorMethodFields::NovemberGroundTemperature, "");
  OS_ASSERT(result);
}

double SiteGroundTemperatureFCfactorMethod_Impl::decemberGroundTemperature() const {
  const auto value = getDouble(openstudio::Site_GroundTemperature_FCfactorMethodFields::DecemberGroundTemperature, true);
  OS_ASSERT(value);
  return value.get();
}

bool SiteGroundTemperatureFCfactorMethod_Impl::isDecemberGroundTemperatureDefaulted() const {
  return isEmpty(openstudio::Site_GroundTemperature_FCfactorMethodFields::DecemberGroundTemperature);
}

bool SiteGroundTemperatureFCfactorMethod_Impl::setDecemberGroundTemperature(double decemberGroundTemperature) {
  const bool result = setDouble(openstudio::Site_GroundTemperature_FCfactorMethodFields::DecemberGroundTemperature, decemberGroundTemperature);
  OS_ASSERT(result);
  return result;
}

void SiteGroundTemperatureFCfactorMethod_Impl::resetDecemberGroundTemperature() {
  const bool result = setString(openstudio::Site_GroundTemperature_FCfactorMethodFields::DecemberGroundTemperature, "");
  OS_ASSERT(result);
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
