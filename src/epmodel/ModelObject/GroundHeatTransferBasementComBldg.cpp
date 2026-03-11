/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "GroundHeatTransferBasementComBldg.hpp"
#include "GroundHeatTransferBasementComBldg_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/GroundHeatTransfer_Basement_ComBldg_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

GroundHeatTransferBasementComBldg::GroundHeatTransferBasementComBldg(const Model& model)
  : ModelObject(GroundHeatTransferBasementComBldg::iddObjectType(), model) {}

GroundHeatTransferBasementComBldg::GroundHeatTransferBasementComBldg(std::shared_ptr<detail::GroundHeatTransferBasementComBldg_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType GroundHeatTransferBasementComBldg::iddObjectType() {
  return IddObjectType::GroundHeatTransfer_Basement_ComBldg;
}

double GroundHeatTransferBasementComBldg::januaryaveragetemperature() const {
  return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->januaryaveragetemperature();
}

double GroundHeatTransferBasementComBldg::februaryaveragetemperature() const {
  return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->februaryaveragetemperature();
}

double GroundHeatTransferBasementComBldg::marchaveragetemperature() const {
  return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->marchaveragetemperature();
}

double GroundHeatTransferBasementComBldg::aprilaveragetemperature() const {
  return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->aprilaveragetemperature();
}

double GroundHeatTransferBasementComBldg::mayaveragetemperature() const {
  return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->mayaveragetemperature();
}

double GroundHeatTransferBasementComBldg::juneaveragetemperature() const {
  return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->juneaveragetemperature();
}

double GroundHeatTransferBasementComBldg::julyaveragetemperature() const {
  return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->julyaveragetemperature();
}

double GroundHeatTransferBasementComBldg::augustaveragetemperature() const {
  return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->augustaveragetemperature();
}

double GroundHeatTransferBasementComBldg::septemberaveragetemperature() const {
  return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->septemberaveragetemperature();
}

double GroundHeatTransferBasementComBldg::octoberaveragetemperature() const {
  return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->octoberaveragetemperature();
}

double GroundHeatTransferBasementComBldg::novemberaveragetemperature() const {
  return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->novemberaveragetemperature();
}

double GroundHeatTransferBasementComBldg::decemberaveragetemperature() const {
  return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->decemberaveragetemperature();
}

double GroundHeatTransferBasementComBldg::dailyvariationsinewaveamplitude() const {
  return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->dailyvariationsinewaveamplitude();
}

bool GroundHeatTransferBasementComBldg::isJanuaryaveragetemperatureDefaulted() const {
  return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->isJanuaryaveragetemperatureDefaulted();
}

bool GroundHeatTransferBasementComBldg::isFebruaryaveragetemperatureDefaulted() const {
  return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->isFebruaryaveragetemperatureDefaulted();
}

bool GroundHeatTransferBasementComBldg::isMarchaveragetemperatureDefaulted() const {
  return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->isMarchaveragetemperatureDefaulted();
}

bool GroundHeatTransferBasementComBldg::isAprilaveragetemperatureDefaulted() const {
  return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->isAprilaveragetemperatureDefaulted();
}

bool GroundHeatTransferBasementComBldg::isMayaveragetemperatureDefaulted() const {
  return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->isMayaveragetemperatureDefaulted();
}

bool GroundHeatTransferBasementComBldg::isJuneaveragetemperatureDefaulted() const {
  return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->isJuneaveragetemperatureDefaulted();
}

bool GroundHeatTransferBasementComBldg::isJulyaveragetemperatureDefaulted() const {
  return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->isJulyaveragetemperatureDefaulted();
}

bool GroundHeatTransferBasementComBldg::isAugustaveragetemperatureDefaulted() const {
  return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->isAugustaveragetemperatureDefaulted();
}

bool GroundHeatTransferBasementComBldg::isSeptemberaveragetemperatureDefaulted() const {
  return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->isSeptemberaveragetemperatureDefaulted();
}

bool GroundHeatTransferBasementComBldg::isOctoberaveragetemperatureDefaulted() const {
  return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->isOctoberaveragetemperatureDefaulted();
}

bool GroundHeatTransferBasementComBldg::isNovemberaveragetemperatureDefaulted() const {
  return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->isNovemberaveragetemperatureDefaulted();
}

bool GroundHeatTransferBasementComBldg::isDecemberaveragetemperatureDefaulted() const {
  return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->isDecemberaveragetemperatureDefaulted();
}

bool GroundHeatTransferBasementComBldg::isDailyvariationsinewaveamplitudeDefaulted() const {
  return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->isDailyvariationsinewaveamplitudeDefaulted();
}

bool GroundHeatTransferBasementComBldg::setJanuaryaveragetemperature(double januaryaveragetemperature) {
  return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->setJanuaryaveragetemperature(januaryaveragetemperature);
}

bool GroundHeatTransferBasementComBldg::setFebruaryaveragetemperature(double februaryaveragetemperature) {
  return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->setFebruaryaveragetemperature(februaryaveragetemperature);
}

bool GroundHeatTransferBasementComBldg::setMarchaveragetemperature(double marchaveragetemperature) {
  return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->setMarchaveragetemperature(marchaveragetemperature);
}

bool GroundHeatTransferBasementComBldg::setAprilaveragetemperature(double aprilaveragetemperature) {
  return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->setAprilaveragetemperature(aprilaveragetemperature);
}

bool GroundHeatTransferBasementComBldg::setMayaveragetemperature(double mayaveragetemperature) {
  return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->setMayaveragetemperature(mayaveragetemperature);
}

bool GroundHeatTransferBasementComBldg::setJuneaveragetemperature(double juneaveragetemperature) {
  return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->setJuneaveragetemperature(juneaveragetemperature);
}

bool GroundHeatTransferBasementComBldg::setJulyaveragetemperature(double julyaveragetemperature) {
  return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->setJulyaveragetemperature(julyaveragetemperature);
}

bool GroundHeatTransferBasementComBldg::setAugustaveragetemperature(double augustaveragetemperature) {
  return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->setAugustaveragetemperature(augustaveragetemperature);
}

bool GroundHeatTransferBasementComBldg::setSeptemberaveragetemperature(double septemberaveragetemperature) {
  return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->setSeptemberaveragetemperature(septemberaveragetemperature);
}

bool GroundHeatTransferBasementComBldg::setOctoberaveragetemperature(double octoberaveragetemperature) {
  return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->setOctoberaveragetemperature(octoberaveragetemperature);
}

bool GroundHeatTransferBasementComBldg::setNovemberaveragetemperature(double novemberaveragetemperature) {
  return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->setNovemberaveragetemperature(novemberaveragetemperature);
}

bool GroundHeatTransferBasementComBldg::setDecemberaveragetemperature(double decemberaveragetemperature) {
  return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->setDecemberaveragetemperature(decemberaveragetemperature);
}

bool GroundHeatTransferBasementComBldg::setDailyvariationsinewaveamplitude(double dailyvariationsinewaveamplitude) {
  return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->setDailyvariationsinewaveamplitude(dailyvariationsinewaveamplitude);
}

void GroundHeatTransferBasementComBldg::resetJanuaryaveragetemperature() {
  getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->resetJanuaryaveragetemperature();
}

void GroundHeatTransferBasementComBldg::resetFebruaryaveragetemperature() {
  getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->resetFebruaryaveragetemperature();
}

void GroundHeatTransferBasementComBldg::resetMarchaveragetemperature() {
  getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->resetMarchaveragetemperature();
}

void GroundHeatTransferBasementComBldg::resetAprilaveragetemperature() {
  getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->resetAprilaveragetemperature();
}

void GroundHeatTransferBasementComBldg::resetMayaveragetemperature() {
  getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->resetMayaveragetemperature();
}

void GroundHeatTransferBasementComBldg::resetJuneaveragetemperature() {
  getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->resetJuneaveragetemperature();
}

void GroundHeatTransferBasementComBldg::resetJulyaveragetemperature() {
  getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->resetJulyaveragetemperature();
}

void GroundHeatTransferBasementComBldg::resetAugustaveragetemperature() {
  getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->resetAugustaveragetemperature();
}

void GroundHeatTransferBasementComBldg::resetSeptemberaveragetemperature() {
  getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->resetSeptemberaveragetemperature();
}

void GroundHeatTransferBasementComBldg::resetOctoberaveragetemperature() {
  getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->resetOctoberaveragetemperature();
}

void GroundHeatTransferBasementComBldg::resetNovemberaveragetemperature() {
  getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->resetNovemberaveragetemperature();
}

void GroundHeatTransferBasementComBldg::resetDecemberaveragetemperature() {
  getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->resetDecemberaveragetemperature();
}

void GroundHeatTransferBasementComBldg::resetDailyvariationsinewaveamplitude() {
  getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->resetDailyvariationsinewaveamplitude();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

double GroundHeatTransferBasementComBldg_Impl::januaryaveragetemperature() const {
  const auto value = getDouble(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Januaryaveragetemperature, true);
  OS_ASSERT(value);
  return *value;
}

double GroundHeatTransferBasementComBldg_Impl::februaryaveragetemperature() const {
  const auto value = getDouble(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Februaryaveragetemperature, true);
  OS_ASSERT(value);
  return *value;
}

double GroundHeatTransferBasementComBldg_Impl::marchaveragetemperature() const {
  const auto value = getDouble(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Marchaveragetemperature, true);
  OS_ASSERT(value);
  return *value;
}

double GroundHeatTransferBasementComBldg_Impl::aprilaveragetemperature() const {
  const auto value = getDouble(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Aprilaveragetemperature, true);
  OS_ASSERT(value);
  return *value;
}

double GroundHeatTransferBasementComBldg_Impl::mayaveragetemperature() const {
  const auto value = getDouble(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Mayaveragetemperature, true);
  OS_ASSERT(value);
  return *value;
}

double GroundHeatTransferBasementComBldg_Impl::juneaveragetemperature() const {
  const auto value = getDouble(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Juneaveragetemperature, true);
  OS_ASSERT(value);
  return *value;
}

double GroundHeatTransferBasementComBldg_Impl::julyaveragetemperature() const {
  const auto value = getDouble(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Julyaveragetemperature, true);
  OS_ASSERT(value);
  return *value;
}

double GroundHeatTransferBasementComBldg_Impl::augustaveragetemperature() const {
  const auto value = getDouble(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Augustaveragetemperature, true);
  OS_ASSERT(value);
  return *value;
}

double GroundHeatTransferBasementComBldg_Impl::septemberaveragetemperature() const {
  const auto value = getDouble(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Septemberaveragetemperature, true);
  OS_ASSERT(value);
  return *value;
}

double GroundHeatTransferBasementComBldg_Impl::octoberaveragetemperature() const {
  const auto value = getDouble(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Octoberaveragetemperature, true);
  OS_ASSERT(value);
  return *value;
}

double GroundHeatTransferBasementComBldg_Impl::novemberaveragetemperature() const {
  const auto value = getDouble(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Novemberaveragetemperature, true);
  OS_ASSERT(value);
  return *value;
}

double GroundHeatTransferBasementComBldg_Impl::decemberaveragetemperature() const {
  const auto value = getDouble(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Decemberaveragetemperature, true);
  OS_ASSERT(value);
  return *value;
}

double GroundHeatTransferBasementComBldg_Impl::dailyvariationsinewaveamplitude() const {
  const auto value = getDouble(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Dailyvariationsinewaveamplitude, true);
  OS_ASSERT(value);
  return *value;
}

bool GroundHeatTransferBasementComBldg_Impl::isJanuaryaveragetemperatureDefaulted() const {
  return isEmpty(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Januaryaveragetemperature);
}

bool GroundHeatTransferBasementComBldg_Impl::isFebruaryaveragetemperatureDefaulted() const {
  return isEmpty(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Februaryaveragetemperature);
}

bool GroundHeatTransferBasementComBldg_Impl::isMarchaveragetemperatureDefaulted() const {
  return isEmpty(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Marchaveragetemperature);
}

bool GroundHeatTransferBasementComBldg_Impl::isAprilaveragetemperatureDefaulted() const {
  return isEmpty(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Aprilaveragetemperature);
}

bool GroundHeatTransferBasementComBldg_Impl::isMayaveragetemperatureDefaulted() const {
  return isEmpty(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Mayaveragetemperature);
}

bool GroundHeatTransferBasementComBldg_Impl::isJuneaveragetemperatureDefaulted() const {
  return isEmpty(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Juneaveragetemperature);
}

bool GroundHeatTransferBasementComBldg_Impl::isJulyaveragetemperatureDefaulted() const {
  return isEmpty(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Julyaveragetemperature);
}

bool GroundHeatTransferBasementComBldg_Impl::isAugustaveragetemperatureDefaulted() const {
  return isEmpty(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Augustaveragetemperature);
}

bool GroundHeatTransferBasementComBldg_Impl::isSeptemberaveragetemperatureDefaulted() const {
  return isEmpty(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Septemberaveragetemperature);
}

bool GroundHeatTransferBasementComBldg_Impl::isOctoberaveragetemperatureDefaulted() const {
  return isEmpty(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Octoberaveragetemperature);
}

bool GroundHeatTransferBasementComBldg_Impl::isNovemberaveragetemperatureDefaulted() const {
  return isEmpty(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Novemberaveragetemperature);
}

bool GroundHeatTransferBasementComBldg_Impl::isDecemberaveragetemperatureDefaulted() const {
  return isEmpty(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Decemberaveragetemperature);
}

bool GroundHeatTransferBasementComBldg_Impl::isDailyvariationsinewaveamplitudeDefaulted() const {
  return isEmpty(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Dailyvariationsinewaveamplitude);
}

bool GroundHeatTransferBasementComBldg_Impl::setJanuaryaveragetemperature(double januaryaveragetemperature) {
  const bool result = setDouble(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Januaryaveragetemperature, januaryaveragetemperature);
  OS_ASSERT(result);
  return result;
}

bool GroundHeatTransferBasementComBldg_Impl::setFebruaryaveragetemperature(double februaryaveragetemperature) {
  const bool result =
    setDouble(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Februaryaveragetemperature, februaryaveragetemperature);
  OS_ASSERT(result);
  return result;
}

bool GroundHeatTransferBasementComBldg_Impl::setMarchaveragetemperature(double marchaveragetemperature) {
  const bool result = setDouble(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Marchaveragetemperature, marchaveragetemperature);
  OS_ASSERT(result);
  return result;
}

bool GroundHeatTransferBasementComBldg_Impl::setAprilaveragetemperature(double aprilaveragetemperature) {
  const bool result = setDouble(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Aprilaveragetemperature, aprilaveragetemperature);
  OS_ASSERT(result);
  return result;
}

bool GroundHeatTransferBasementComBldg_Impl::setMayaveragetemperature(double mayaveragetemperature) {
  const bool result = setDouble(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Mayaveragetemperature, mayaveragetemperature);
  OS_ASSERT(result);
  return result;
}

bool GroundHeatTransferBasementComBldg_Impl::setJuneaveragetemperature(double juneaveragetemperature) {
  const bool result = setDouble(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Juneaveragetemperature, juneaveragetemperature);
  OS_ASSERT(result);
  return result;
}

bool GroundHeatTransferBasementComBldg_Impl::setJulyaveragetemperature(double julyaveragetemperature) {
  const bool result = setDouble(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Julyaveragetemperature, julyaveragetemperature);
  OS_ASSERT(result);
  return result;
}

bool GroundHeatTransferBasementComBldg_Impl::setAugustaveragetemperature(double augustaveragetemperature) {
  const bool result = setDouble(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Augustaveragetemperature, augustaveragetemperature);
  OS_ASSERT(result);
  return result;
}

bool GroundHeatTransferBasementComBldg_Impl::setSeptemberaveragetemperature(double septemberaveragetemperature) {
  const bool result =
    setDouble(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Septemberaveragetemperature, septemberaveragetemperature);
  OS_ASSERT(result);
  return result;
}

bool GroundHeatTransferBasementComBldg_Impl::setOctoberaveragetemperature(double octoberaveragetemperature) {
  const bool result = setDouble(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Octoberaveragetemperature, octoberaveragetemperature);
  OS_ASSERT(result);
  return result;
}

bool GroundHeatTransferBasementComBldg_Impl::setNovemberaveragetemperature(double novemberaveragetemperature) {
  const bool result =
    setDouble(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Novemberaveragetemperature, novemberaveragetemperature);
  OS_ASSERT(result);
  return result;
}

bool GroundHeatTransferBasementComBldg_Impl::setDecemberaveragetemperature(double decemberaveragetemperature) {
  const bool result =
    setDouble(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Decemberaveragetemperature, decemberaveragetemperature);
  OS_ASSERT(result);
  return result;
}

bool GroundHeatTransferBasementComBldg_Impl::setDailyvariationsinewaveamplitude(double dailyvariationsinewaveamplitude) {
  const bool result = setDouble(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Dailyvariationsinewaveamplitude, dailyvariationsinewaveamplitude);
  OS_ASSERT(result);
  return result;
}

void GroundHeatTransferBasementComBldg_Impl::resetJanuaryaveragetemperature() {
  OS_ASSERT(setString(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Januaryaveragetemperature, ""));
}

void GroundHeatTransferBasementComBldg_Impl::resetFebruaryaveragetemperature() {
  OS_ASSERT(setString(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Februaryaveragetemperature, ""));
}

void GroundHeatTransferBasementComBldg_Impl::resetMarchaveragetemperature() {
  OS_ASSERT(setString(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Marchaveragetemperature, ""));
}

void GroundHeatTransferBasementComBldg_Impl::resetAprilaveragetemperature() {
  OS_ASSERT(setString(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Aprilaveragetemperature, ""));
}

void GroundHeatTransferBasementComBldg_Impl::resetMayaveragetemperature() {
  OS_ASSERT(setString(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Mayaveragetemperature, ""));
}

void GroundHeatTransferBasementComBldg_Impl::resetJuneaveragetemperature() {
  OS_ASSERT(setString(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Juneaveragetemperature, ""));
}

void GroundHeatTransferBasementComBldg_Impl::resetJulyaveragetemperature() {
  OS_ASSERT(setString(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Julyaveragetemperature, ""));
}

void GroundHeatTransferBasementComBldg_Impl::resetAugustaveragetemperature() {
  OS_ASSERT(setString(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Augustaveragetemperature, ""));
}

void GroundHeatTransferBasementComBldg_Impl::resetSeptemberaveragetemperature() {
  OS_ASSERT(setString(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Septemberaveragetemperature, ""));
}

void GroundHeatTransferBasementComBldg_Impl::resetOctoberaveragetemperature() {
  OS_ASSERT(setString(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Octoberaveragetemperature, ""));
}

void GroundHeatTransferBasementComBldg_Impl::resetNovemberaveragetemperature() {
  OS_ASSERT(setString(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Novemberaveragetemperature, ""));
}

void GroundHeatTransferBasementComBldg_Impl::resetDecemberaveragetemperature() {
  OS_ASSERT(setString(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Decemberaveragetemperature, ""));
}

void GroundHeatTransferBasementComBldg_Impl::resetDailyvariationsinewaveamplitude() {
  OS_ASSERT(setString(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Dailyvariationsinewaveamplitude, ""));
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
