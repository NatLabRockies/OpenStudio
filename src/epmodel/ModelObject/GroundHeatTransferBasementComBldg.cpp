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

  bool GroundHeatTransferBasementComBldg::isJanuaryaveragetemperatureDefaulted() const {
    return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->isJanuaryaveragetemperatureDefaulted();
  }

  bool GroundHeatTransferBasementComBldg::setJanuaryaveragetemperature(double januaryaveragetemperature) {
    return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->setJanuaryaveragetemperature(januaryaveragetemperature);
  }

  void GroundHeatTransferBasementComBldg::resetJanuaryaveragetemperature() {
    getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->resetJanuaryaveragetemperature();
  }

  double GroundHeatTransferBasementComBldg::februaryaveragetemperature() const {
    return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->februaryaveragetemperature();
  }

  bool GroundHeatTransferBasementComBldg::isFebruaryaveragetemperatureDefaulted() const {
    return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->isFebruaryaveragetemperatureDefaulted();
  }

  bool GroundHeatTransferBasementComBldg::setFebruaryaveragetemperature(double februaryaveragetemperature) {
    return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->setFebruaryaveragetemperature(februaryaveragetemperature);
  }

  void GroundHeatTransferBasementComBldg::resetFebruaryaveragetemperature() {
    getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->resetFebruaryaveragetemperature();
  }

  double GroundHeatTransferBasementComBldg::marchaveragetemperature() const {
    return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->marchaveragetemperature();
  }

  bool GroundHeatTransferBasementComBldg::isMarchaveragetemperatureDefaulted() const {
    return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->isMarchaveragetemperatureDefaulted();
  }

  bool GroundHeatTransferBasementComBldg::setMarchaveragetemperature(double marchaveragetemperature) {
    return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->setMarchaveragetemperature(marchaveragetemperature);
  }

  void GroundHeatTransferBasementComBldg::resetMarchaveragetemperature() {
    getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->resetMarchaveragetemperature();
  }

  double GroundHeatTransferBasementComBldg::aprilaveragetemperature() const {
    return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->aprilaveragetemperature();
  }

  bool GroundHeatTransferBasementComBldg::isAprilaveragetemperatureDefaulted() const {
    return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->isAprilaveragetemperatureDefaulted();
  }

  bool GroundHeatTransferBasementComBldg::setAprilaveragetemperature(double aprilaveragetemperature) {
    return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->setAprilaveragetemperature(aprilaveragetemperature);
  }

  void GroundHeatTransferBasementComBldg::resetAprilaveragetemperature() {
    getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->resetAprilaveragetemperature();
  }

  double GroundHeatTransferBasementComBldg::mayaveragetemperature() const {
    return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->mayaveragetemperature();
  }

  bool GroundHeatTransferBasementComBldg::isMayaveragetemperatureDefaulted() const {
    return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->isMayaveragetemperatureDefaulted();
  }

  bool GroundHeatTransferBasementComBldg::setMayaveragetemperature(double mayaveragetemperature) {
    return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->setMayaveragetemperature(mayaveragetemperature);
  }

  void GroundHeatTransferBasementComBldg::resetMayaveragetemperature() {
    getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->resetMayaveragetemperature();
  }

  double GroundHeatTransferBasementComBldg::juneaveragetemperature() const {
    return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->juneaveragetemperature();
  }

  bool GroundHeatTransferBasementComBldg::isJuneaveragetemperatureDefaulted() const {
    return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->isJuneaveragetemperatureDefaulted();
  }

  bool GroundHeatTransferBasementComBldg::setJuneaveragetemperature(double juneaveragetemperature) {
    return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->setJuneaveragetemperature(juneaveragetemperature);
  }

  void GroundHeatTransferBasementComBldg::resetJuneaveragetemperature() {
    getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->resetJuneaveragetemperature();
  }

  double GroundHeatTransferBasementComBldg::julyaveragetemperature() const {
    return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->julyaveragetemperature();
  }

  bool GroundHeatTransferBasementComBldg::isJulyaveragetemperatureDefaulted() const {
    return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->isJulyaveragetemperatureDefaulted();
  }

  bool GroundHeatTransferBasementComBldg::setJulyaveragetemperature(double julyaveragetemperature) {
    return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->setJulyaveragetemperature(julyaveragetemperature);
  }

  void GroundHeatTransferBasementComBldg::resetJulyaveragetemperature() {
    getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->resetJulyaveragetemperature();
  }

  double GroundHeatTransferBasementComBldg::augustaveragetemperature() const {
    return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->augustaveragetemperature();
  }

  bool GroundHeatTransferBasementComBldg::isAugustaveragetemperatureDefaulted() const {
    return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->isAugustaveragetemperatureDefaulted();
  }

  bool GroundHeatTransferBasementComBldg::setAugustaveragetemperature(double augustaveragetemperature) {
    return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->setAugustaveragetemperature(augustaveragetemperature);
  }

  void GroundHeatTransferBasementComBldg::resetAugustaveragetemperature() {
    getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->resetAugustaveragetemperature();
  }

  double GroundHeatTransferBasementComBldg::septemberaveragetemperature() const {
    return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->septemberaveragetemperature();
  }

  bool GroundHeatTransferBasementComBldg::isSeptemberaveragetemperatureDefaulted() const {
    return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->isSeptemberaveragetemperatureDefaulted();
  }

  bool GroundHeatTransferBasementComBldg::setSeptemberaveragetemperature(double septemberaveragetemperature) {
    return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->setSeptemberaveragetemperature(septemberaveragetemperature);
  }

  void GroundHeatTransferBasementComBldg::resetSeptemberaveragetemperature() {
    getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->resetSeptemberaveragetemperature();
  }

  double GroundHeatTransferBasementComBldg::octoberaveragetemperature() const {
    return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->octoberaveragetemperature();
  }

  bool GroundHeatTransferBasementComBldg::isOctoberaveragetemperatureDefaulted() const {
    return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->isOctoberaveragetemperatureDefaulted();
  }

  bool GroundHeatTransferBasementComBldg::setOctoberaveragetemperature(double octoberaveragetemperature) {
    return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->setOctoberaveragetemperature(octoberaveragetemperature);
  }

  void GroundHeatTransferBasementComBldg::resetOctoberaveragetemperature() {
    getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->resetOctoberaveragetemperature();
  }

  double GroundHeatTransferBasementComBldg::novemberaveragetemperature() const {
    return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->novemberaveragetemperature();
  }

  bool GroundHeatTransferBasementComBldg::isNovemberaveragetemperatureDefaulted() const {
    return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->isNovemberaveragetemperatureDefaulted();
  }

  bool GroundHeatTransferBasementComBldg::setNovemberaveragetemperature(double novemberaveragetemperature) {
    return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->setNovemberaveragetemperature(novemberaveragetemperature);
  }

  void GroundHeatTransferBasementComBldg::resetNovemberaveragetemperature() {
    getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->resetNovemberaveragetemperature();
  }

  double GroundHeatTransferBasementComBldg::decemberaveragetemperature() const {
    return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->decemberaveragetemperature();
  }

  bool GroundHeatTransferBasementComBldg::isDecemberaveragetemperatureDefaulted() const {
    return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->isDecemberaveragetemperatureDefaulted();
  }

  bool GroundHeatTransferBasementComBldg::setDecemberaveragetemperature(double decemberaveragetemperature) {
    return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->setDecemberaveragetemperature(decemberaveragetemperature);
  }

  void GroundHeatTransferBasementComBldg::resetDecemberaveragetemperature() {
    getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->resetDecemberaveragetemperature();
  }

  double GroundHeatTransferBasementComBldg::dailyvariationsinewaveamplitude() const {
    return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->dailyvariationsinewaveamplitude();
  }

  bool GroundHeatTransferBasementComBldg::isDailyvariationsinewaveamplitudeDefaulted() const {
    return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->isDailyvariationsinewaveamplitudeDefaulted();
  }

  bool GroundHeatTransferBasementComBldg::setDailyvariationsinewaveamplitude(double dailyvariationsinewaveamplitude) {
    return getImpl<detail::GroundHeatTransferBasementComBldg_Impl>()->setDailyvariationsinewaveamplitude(dailyvariationsinewaveamplitude);
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

    bool GroundHeatTransferBasementComBldg_Impl::isJanuaryaveragetemperatureDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Januaryaveragetemperature);
    }

    bool GroundHeatTransferBasementComBldg_Impl::setJanuaryaveragetemperature(double januaryaveragetemperature) {
      const bool result = setDouble(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Januaryaveragetemperature, januaryaveragetemperature);
      OS_ASSERT(result);
      return result;
    }

    void GroundHeatTransferBasementComBldg_Impl::resetJanuaryaveragetemperature() {
      OS_ASSERT(setString(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Januaryaveragetemperature, ""));
    }

    double GroundHeatTransferBasementComBldg_Impl::februaryaveragetemperature() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Februaryaveragetemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferBasementComBldg_Impl::isFebruaryaveragetemperatureDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Februaryaveragetemperature);
    }

    bool GroundHeatTransferBasementComBldg_Impl::setFebruaryaveragetemperature(double februaryaveragetemperature) {
      const bool result = setDouble(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Februaryaveragetemperature, februaryaveragetemperature);
      OS_ASSERT(result);
      return result;
    }

    void GroundHeatTransferBasementComBldg_Impl::resetFebruaryaveragetemperature() {
      OS_ASSERT(setString(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Februaryaveragetemperature, ""));
    }

    double GroundHeatTransferBasementComBldg_Impl::marchaveragetemperature() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Marchaveragetemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferBasementComBldg_Impl::isMarchaveragetemperatureDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Marchaveragetemperature);
    }

    bool GroundHeatTransferBasementComBldg_Impl::setMarchaveragetemperature(double marchaveragetemperature) {
      const bool result = setDouble(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Marchaveragetemperature, marchaveragetemperature);
      OS_ASSERT(result);
      return result;
    }

    void GroundHeatTransferBasementComBldg_Impl::resetMarchaveragetemperature() {
      OS_ASSERT(setString(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Marchaveragetemperature, ""));
    }

    double GroundHeatTransferBasementComBldg_Impl::aprilaveragetemperature() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Aprilaveragetemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferBasementComBldg_Impl::isAprilaveragetemperatureDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Aprilaveragetemperature);
    }

    bool GroundHeatTransferBasementComBldg_Impl::setAprilaveragetemperature(double aprilaveragetemperature) {
      const bool result = setDouble(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Aprilaveragetemperature, aprilaveragetemperature);
      OS_ASSERT(result);
      return result;
    }

    void GroundHeatTransferBasementComBldg_Impl::resetAprilaveragetemperature() {
      OS_ASSERT(setString(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Aprilaveragetemperature, ""));
    }

    double GroundHeatTransferBasementComBldg_Impl::mayaveragetemperature() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Mayaveragetemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferBasementComBldg_Impl::isMayaveragetemperatureDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Mayaveragetemperature);
    }

    bool GroundHeatTransferBasementComBldg_Impl::setMayaveragetemperature(double mayaveragetemperature) {
      const bool result = setDouble(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Mayaveragetemperature, mayaveragetemperature);
      OS_ASSERT(result);
      return result;
    }

    void GroundHeatTransferBasementComBldg_Impl::resetMayaveragetemperature() {
      OS_ASSERT(setString(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Mayaveragetemperature, ""));
    }

    double GroundHeatTransferBasementComBldg_Impl::juneaveragetemperature() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Juneaveragetemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferBasementComBldg_Impl::isJuneaveragetemperatureDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Juneaveragetemperature);
    }

    bool GroundHeatTransferBasementComBldg_Impl::setJuneaveragetemperature(double juneaveragetemperature) {
      const bool result = setDouble(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Juneaveragetemperature, juneaveragetemperature);
      OS_ASSERT(result);
      return result;
    }

    void GroundHeatTransferBasementComBldg_Impl::resetJuneaveragetemperature() {
      OS_ASSERT(setString(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Juneaveragetemperature, ""));
    }

    double GroundHeatTransferBasementComBldg_Impl::julyaveragetemperature() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Julyaveragetemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferBasementComBldg_Impl::isJulyaveragetemperatureDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Julyaveragetemperature);
    }

    bool GroundHeatTransferBasementComBldg_Impl::setJulyaveragetemperature(double julyaveragetemperature) {
      const bool result = setDouble(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Julyaveragetemperature, julyaveragetemperature);
      OS_ASSERT(result);
      return result;
    }

    void GroundHeatTransferBasementComBldg_Impl::resetJulyaveragetemperature() {
      OS_ASSERT(setString(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Julyaveragetemperature, ""));
    }

    double GroundHeatTransferBasementComBldg_Impl::augustaveragetemperature() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Augustaveragetemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferBasementComBldg_Impl::isAugustaveragetemperatureDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Augustaveragetemperature);
    }

    bool GroundHeatTransferBasementComBldg_Impl::setAugustaveragetemperature(double augustaveragetemperature) {
      const bool result = setDouble(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Augustaveragetemperature, augustaveragetemperature);
      OS_ASSERT(result);
      return result;
    }

    void GroundHeatTransferBasementComBldg_Impl::resetAugustaveragetemperature() {
      OS_ASSERT(setString(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Augustaveragetemperature, ""));
    }

    double GroundHeatTransferBasementComBldg_Impl::septemberaveragetemperature() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Septemberaveragetemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferBasementComBldg_Impl::isSeptemberaveragetemperatureDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Septemberaveragetemperature);
    }

    bool GroundHeatTransferBasementComBldg_Impl::setSeptemberaveragetemperature(double septemberaveragetemperature) {
      const bool result = setDouble(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Septemberaveragetemperature, septemberaveragetemperature);
      OS_ASSERT(result);
      return result;
    }

    void GroundHeatTransferBasementComBldg_Impl::resetSeptemberaveragetemperature() {
      OS_ASSERT(setString(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Septemberaveragetemperature, ""));
    }

    double GroundHeatTransferBasementComBldg_Impl::octoberaveragetemperature() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Octoberaveragetemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferBasementComBldg_Impl::isOctoberaveragetemperatureDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Octoberaveragetemperature);
    }

    bool GroundHeatTransferBasementComBldg_Impl::setOctoberaveragetemperature(double octoberaveragetemperature) {
      const bool result = setDouble(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Octoberaveragetemperature, octoberaveragetemperature);
      OS_ASSERT(result);
      return result;
    }

    void GroundHeatTransferBasementComBldg_Impl::resetOctoberaveragetemperature() {
      OS_ASSERT(setString(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Octoberaveragetemperature, ""));
    }

    double GroundHeatTransferBasementComBldg_Impl::novemberaveragetemperature() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Novemberaveragetemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferBasementComBldg_Impl::isNovemberaveragetemperatureDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Novemberaveragetemperature);
    }

    bool GroundHeatTransferBasementComBldg_Impl::setNovemberaveragetemperature(double novemberaveragetemperature) {
      const bool result = setDouble(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Novemberaveragetemperature, novemberaveragetemperature);
      OS_ASSERT(result);
      return result;
    }

    void GroundHeatTransferBasementComBldg_Impl::resetNovemberaveragetemperature() {
      OS_ASSERT(setString(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Novemberaveragetemperature, ""));
    }

    double GroundHeatTransferBasementComBldg_Impl::decemberaveragetemperature() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Decemberaveragetemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferBasementComBldg_Impl::isDecemberaveragetemperatureDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Decemberaveragetemperature);
    }

    bool GroundHeatTransferBasementComBldg_Impl::setDecemberaveragetemperature(double decemberaveragetemperature) {
      const bool result = setDouble(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Decemberaveragetemperature, decemberaveragetemperature);
      OS_ASSERT(result);
      return result;
    }

    void GroundHeatTransferBasementComBldg_Impl::resetDecemberaveragetemperature() {
      OS_ASSERT(setString(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Decemberaveragetemperature, ""));
    }

    double GroundHeatTransferBasementComBldg_Impl::dailyvariationsinewaveamplitude() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Dailyvariationsinewaveamplitude, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferBasementComBldg_Impl::isDailyvariationsinewaveamplitudeDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Dailyvariationsinewaveamplitude);
    }

    bool GroundHeatTransferBasementComBldg_Impl::setDailyvariationsinewaveamplitude(double dailyvariationsinewaveamplitude) {
      const bool result =
        setDouble(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Dailyvariationsinewaveamplitude, dailyvariationsinewaveamplitude);
      OS_ASSERT(result);
      return result;
    }

    void GroundHeatTransferBasementComBldg_Impl::resetDailyvariationsinewaveamplitude() {
      OS_ASSERT(setString(openstudio::GroundHeatTransfer_Basement_ComBldgFields::Dailyvariationsinewaveamplitude, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
