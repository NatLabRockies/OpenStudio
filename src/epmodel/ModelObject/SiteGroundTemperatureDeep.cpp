/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SiteGroundTemperatureDeep.hpp"
#include "SiteGroundTemperatureDeep_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Site_GroundTemperature_Deep_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  SiteGroundTemperatureDeep::SiteGroundTemperatureDeep(const Model& model) : ModelObject(SiteGroundTemperatureDeep::iddObjectType(), model) {}

  SiteGroundTemperatureDeep::SiteGroundTemperatureDeep(std::shared_ptr<detail::SiteGroundTemperatureDeep_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType SiteGroundTemperatureDeep::iddObjectType() {
    return IddObjectType::Site_GroundTemperature_Deep;
  }

  double SiteGroundTemperatureDeep::januaryDeepGroundTemperature() const {
    return getImpl<detail::SiteGroundTemperatureDeep_Impl>()->januaryDeepGroundTemperature();
  }

  bool SiteGroundTemperatureDeep::isJanuaryDeepGroundTemperatureDefaulted() const {
    return getImpl<detail::SiteGroundTemperatureDeep_Impl>()->isJanuaryDeepGroundTemperatureDefaulted();
  }

  bool SiteGroundTemperatureDeep::setJanuaryDeepGroundTemperature(double januaryDeepGroundTemperature) {
    return getImpl<detail::SiteGroundTemperatureDeep_Impl>()->setJanuaryDeepGroundTemperature(januaryDeepGroundTemperature);
  }

  void SiteGroundTemperatureDeep::resetJanuaryDeepGroundTemperature() {
    getImpl<detail::SiteGroundTemperatureDeep_Impl>()->resetJanuaryDeepGroundTemperature();
  }

  double SiteGroundTemperatureDeep::februaryDeepGroundTemperature() const {
    return getImpl<detail::SiteGroundTemperatureDeep_Impl>()->februaryDeepGroundTemperature();
  }

  bool SiteGroundTemperatureDeep::isFebruaryDeepGroundTemperatureDefaulted() const {
    return getImpl<detail::SiteGroundTemperatureDeep_Impl>()->isFebruaryDeepGroundTemperatureDefaulted();
  }

  bool SiteGroundTemperatureDeep::setFebruaryDeepGroundTemperature(double februaryDeepGroundTemperature) {
    return getImpl<detail::SiteGroundTemperatureDeep_Impl>()->setFebruaryDeepGroundTemperature(februaryDeepGroundTemperature);
  }

  void SiteGroundTemperatureDeep::resetFebruaryDeepGroundTemperature() {
    getImpl<detail::SiteGroundTemperatureDeep_Impl>()->resetFebruaryDeepGroundTemperature();
  }

  double SiteGroundTemperatureDeep::marchDeepGroundTemperature() const {
    return getImpl<detail::SiteGroundTemperatureDeep_Impl>()->marchDeepGroundTemperature();
  }

  bool SiteGroundTemperatureDeep::isMarchDeepGroundTemperatureDefaulted() const {
    return getImpl<detail::SiteGroundTemperatureDeep_Impl>()->isMarchDeepGroundTemperatureDefaulted();
  }

  bool SiteGroundTemperatureDeep::setMarchDeepGroundTemperature(double marchDeepGroundTemperature) {
    return getImpl<detail::SiteGroundTemperatureDeep_Impl>()->setMarchDeepGroundTemperature(marchDeepGroundTemperature);
  }

  void SiteGroundTemperatureDeep::resetMarchDeepGroundTemperature() {
    getImpl<detail::SiteGroundTemperatureDeep_Impl>()->resetMarchDeepGroundTemperature();
  }

  double SiteGroundTemperatureDeep::aprilDeepGroundTemperature() const {
    return getImpl<detail::SiteGroundTemperatureDeep_Impl>()->aprilDeepGroundTemperature();
  }

  bool SiteGroundTemperatureDeep::isAprilDeepGroundTemperatureDefaulted() const {
    return getImpl<detail::SiteGroundTemperatureDeep_Impl>()->isAprilDeepGroundTemperatureDefaulted();
  }

  bool SiteGroundTemperatureDeep::setAprilDeepGroundTemperature(double aprilDeepGroundTemperature) {
    return getImpl<detail::SiteGroundTemperatureDeep_Impl>()->setAprilDeepGroundTemperature(aprilDeepGroundTemperature);
  }

  void SiteGroundTemperatureDeep::resetAprilDeepGroundTemperature() {
    getImpl<detail::SiteGroundTemperatureDeep_Impl>()->resetAprilDeepGroundTemperature();
  }

  double SiteGroundTemperatureDeep::mayDeepGroundTemperature() const {
    return getImpl<detail::SiteGroundTemperatureDeep_Impl>()->mayDeepGroundTemperature();
  }

  bool SiteGroundTemperatureDeep::isMayDeepGroundTemperatureDefaulted() const {
    return getImpl<detail::SiteGroundTemperatureDeep_Impl>()->isMayDeepGroundTemperatureDefaulted();
  }

  bool SiteGroundTemperatureDeep::setMayDeepGroundTemperature(double mayDeepGroundTemperature) {
    return getImpl<detail::SiteGroundTemperatureDeep_Impl>()->setMayDeepGroundTemperature(mayDeepGroundTemperature);
  }

  void SiteGroundTemperatureDeep::resetMayDeepGroundTemperature() {
    getImpl<detail::SiteGroundTemperatureDeep_Impl>()->resetMayDeepGroundTemperature();
  }

  double SiteGroundTemperatureDeep::juneDeepGroundTemperature() const {
    return getImpl<detail::SiteGroundTemperatureDeep_Impl>()->juneDeepGroundTemperature();
  }

  bool SiteGroundTemperatureDeep::isJuneDeepGroundTemperatureDefaulted() const {
    return getImpl<detail::SiteGroundTemperatureDeep_Impl>()->isJuneDeepGroundTemperatureDefaulted();
  }

  bool SiteGroundTemperatureDeep::setJuneDeepGroundTemperature(double juneDeepGroundTemperature) {
    return getImpl<detail::SiteGroundTemperatureDeep_Impl>()->setJuneDeepGroundTemperature(juneDeepGroundTemperature);
  }

  void SiteGroundTemperatureDeep::resetJuneDeepGroundTemperature() {
    getImpl<detail::SiteGroundTemperatureDeep_Impl>()->resetJuneDeepGroundTemperature();
  }

  double SiteGroundTemperatureDeep::julyDeepGroundTemperature() const {
    return getImpl<detail::SiteGroundTemperatureDeep_Impl>()->julyDeepGroundTemperature();
  }

  bool SiteGroundTemperatureDeep::isJulyDeepGroundTemperatureDefaulted() const {
    return getImpl<detail::SiteGroundTemperatureDeep_Impl>()->isJulyDeepGroundTemperatureDefaulted();
  }

  bool SiteGroundTemperatureDeep::setJulyDeepGroundTemperature(double julyDeepGroundTemperature) {
    return getImpl<detail::SiteGroundTemperatureDeep_Impl>()->setJulyDeepGroundTemperature(julyDeepGroundTemperature);
  }

  void SiteGroundTemperatureDeep::resetJulyDeepGroundTemperature() {
    getImpl<detail::SiteGroundTemperatureDeep_Impl>()->resetJulyDeepGroundTemperature();
  }

  double SiteGroundTemperatureDeep::augustDeepGroundTemperature() const {
    return getImpl<detail::SiteGroundTemperatureDeep_Impl>()->augustDeepGroundTemperature();
  }

  bool SiteGroundTemperatureDeep::isAugustDeepGroundTemperatureDefaulted() const {
    return getImpl<detail::SiteGroundTemperatureDeep_Impl>()->isAugustDeepGroundTemperatureDefaulted();
  }

  bool SiteGroundTemperatureDeep::setAugustDeepGroundTemperature(double augustDeepGroundTemperature) {
    return getImpl<detail::SiteGroundTemperatureDeep_Impl>()->setAugustDeepGroundTemperature(augustDeepGroundTemperature);
  }

  void SiteGroundTemperatureDeep::resetAugustDeepGroundTemperature() {
    getImpl<detail::SiteGroundTemperatureDeep_Impl>()->resetAugustDeepGroundTemperature();
  }

  double SiteGroundTemperatureDeep::septemberDeepGroundTemperature() const {
    return getImpl<detail::SiteGroundTemperatureDeep_Impl>()->septemberDeepGroundTemperature();
  }

  bool SiteGroundTemperatureDeep::isSeptemberDeepGroundTemperatureDefaulted() const {
    return getImpl<detail::SiteGroundTemperatureDeep_Impl>()->isSeptemberDeepGroundTemperatureDefaulted();
  }

  bool SiteGroundTemperatureDeep::setSeptemberDeepGroundTemperature(double septemberDeepGroundTemperature) {
    return getImpl<detail::SiteGroundTemperatureDeep_Impl>()->setSeptemberDeepGroundTemperature(septemberDeepGroundTemperature);
  }

  void SiteGroundTemperatureDeep::resetSeptemberDeepGroundTemperature() {
    getImpl<detail::SiteGroundTemperatureDeep_Impl>()->resetSeptemberDeepGroundTemperature();
  }

  double SiteGroundTemperatureDeep::octoberDeepGroundTemperature() const {
    return getImpl<detail::SiteGroundTemperatureDeep_Impl>()->octoberDeepGroundTemperature();
  }

  bool SiteGroundTemperatureDeep::isOctoberDeepGroundTemperatureDefaulted() const {
    return getImpl<detail::SiteGroundTemperatureDeep_Impl>()->isOctoberDeepGroundTemperatureDefaulted();
  }

  bool SiteGroundTemperatureDeep::setOctoberDeepGroundTemperature(double octoberDeepGroundTemperature) {
    return getImpl<detail::SiteGroundTemperatureDeep_Impl>()->setOctoberDeepGroundTemperature(octoberDeepGroundTemperature);
  }

  void SiteGroundTemperatureDeep::resetOctoberDeepGroundTemperature() {
    getImpl<detail::SiteGroundTemperatureDeep_Impl>()->resetOctoberDeepGroundTemperature();
  }

  double SiteGroundTemperatureDeep::novemberDeepGroundTemperature() const {
    return getImpl<detail::SiteGroundTemperatureDeep_Impl>()->novemberDeepGroundTemperature();
  }

  bool SiteGroundTemperatureDeep::isNovemberDeepGroundTemperatureDefaulted() const {
    return getImpl<detail::SiteGroundTemperatureDeep_Impl>()->isNovemberDeepGroundTemperatureDefaulted();
  }

  bool SiteGroundTemperatureDeep::setNovemberDeepGroundTemperature(double novemberDeepGroundTemperature) {
    return getImpl<detail::SiteGroundTemperatureDeep_Impl>()->setNovemberDeepGroundTemperature(novemberDeepGroundTemperature);
  }

  void SiteGroundTemperatureDeep::resetNovemberDeepGroundTemperature() {
    getImpl<detail::SiteGroundTemperatureDeep_Impl>()->resetNovemberDeepGroundTemperature();
  }

  double SiteGroundTemperatureDeep::decemberDeepGroundTemperature() const {
    return getImpl<detail::SiteGroundTemperatureDeep_Impl>()->decemberDeepGroundTemperature();
  }

  bool SiteGroundTemperatureDeep::isDecemberDeepGroundTemperatureDefaulted() const {
    return getImpl<detail::SiteGroundTemperatureDeep_Impl>()->isDecemberDeepGroundTemperatureDefaulted();
  }

  bool SiteGroundTemperatureDeep::setDecemberDeepGroundTemperature(double decemberDeepGroundTemperature) {
    return getImpl<detail::SiteGroundTemperatureDeep_Impl>()->setDecemberDeepGroundTemperature(decemberDeepGroundTemperature);
  }

  void SiteGroundTemperatureDeep::resetDecemberDeepGroundTemperature() {
    getImpl<detail::SiteGroundTemperatureDeep_Impl>()->resetDecemberDeepGroundTemperature();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double SiteGroundTemperatureDeep_Impl::januaryDeepGroundTemperature() const {
      auto value = getDouble(openstudio::Site_GroundTemperature_DeepFields::JanuaryDeepGroundTemperature, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool SiteGroundTemperatureDeep_Impl::isJanuaryDeepGroundTemperatureDefaulted() const {
      return isEmpty(openstudio::Site_GroundTemperature_DeepFields::JanuaryDeepGroundTemperature);
    }

    bool SiteGroundTemperatureDeep_Impl::setJanuaryDeepGroundTemperature(double januaryDeepGroundTemperature) {
      const bool result = setDouble(openstudio::Site_GroundTemperature_DeepFields::JanuaryDeepGroundTemperature, januaryDeepGroundTemperature);
      OS_ASSERT(result);
      return result;
    }

    void SiteGroundTemperatureDeep_Impl::resetJanuaryDeepGroundTemperature() {
      const bool result = setString(openstudio::Site_GroundTemperature_DeepFields::JanuaryDeepGroundTemperature, "");
      OS_ASSERT(result);
    }

    double SiteGroundTemperatureDeep_Impl::februaryDeepGroundTemperature() const {
      auto value = getDouble(openstudio::Site_GroundTemperature_DeepFields::FebruaryDeepGroundTemperature, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool SiteGroundTemperatureDeep_Impl::isFebruaryDeepGroundTemperatureDefaulted() const {
      return isEmpty(openstudio::Site_GroundTemperature_DeepFields::FebruaryDeepGroundTemperature);
    }

    bool SiteGroundTemperatureDeep_Impl::setFebruaryDeepGroundTemperature(double februaryDeepGroundTemperature) {
      const bool result = setDouble(openstudio::Site_GroundTemperature_DeepFields::FebruaryDeepGroundTemperature, februaryDeepGroundTemperature);
      OS_ASSERT(result);
      return result;
    }

    void SiteGroundTemperatureDeep_Impl::resetFebruaryDeepGroundTemperature() {
      const bool result = setString(openstudio::Site_GroundTemperature_DeepFields::FebruaryDeepGroundTemperature, "");
      OS_ASSERT(result);
    }

    double SiteGroundTemperatureDeep_Impl::marchDeepGroundTemperature() const {
      auto value = getDouble(openstudio::Site_GroundTemperature_DeepFields::MarchDeepGroundTemperature, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool SiteGroundTemperatureDeep_Impl::isMarchDeepGroundTemperatureDefaulted() const {
      return isEmpty(openstudio::Site_GroundTemperature_DeepFields::MarchDeepGroundTemperature);
    }

    bool SiteGroundTemperatureDeep_Impl::setMarchDeepGroundTemperature(double marchDeepGroundTemperature) {
      const bool result = setDouble(openstudio::Site_GroundTemperature_DeepFields::MarchDeepGroundTemperature, marchDeepGroundTemperature);
      OS_ASSERT(result);
      return result;
    }

    void SiteGroundTemperatureDeep_Impl::resetMarchDeepGroundTemperature() {
      const bool result = setString(openstudio::Site_GroundTemperature_DeepFields::MarchDeepGroundTemperature, "");
      OS_ASSERT(result);
    }

    double SiteGroundTemperatureDeep_Impl::aprilDeepGroundTemperature() const {
      auto value = getDouble(openstudio::Site_GroundTemperature_DeepFields::AprilDeepGroundTemperature, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool SiteGroundTemperatureDeep_Impl::isAprilDeepGroundTemperatureDefaulted() const {
      return isEmpty(openstudio::Site_GroundTemperature_DeepFields::AprilDeepGroundTemperature);
    }

    bool SiteGroundTemperatureDeep_Impl::setAprilDeepGroundTemperature(double aprilDeepGroundTemperature) {
      const bool result = setDouble(openstudio::Site_GroundTemperature_DeepFields::AprilDeepGroundTemperature, aprilDeepGroundTemperature);
      OS_ASSERT(result);
      return result;
    }

    void SiteGroundTemperatureDeep_Impl::resetAprilDeepGroundTemperature() {
      const bool result = setString(openstudio::Site_GroundTemperature_DeepFields::AprilDeepGroundTemperature, "");
      OS_ASSERT(result);
    }

    double SiteGroundTemperatureDeep_Impl::mayDeepGroundTemperature() const {
      auto value = getDouble(openstudio::Site_GroundTemperature_DeepFields::MayDeepGroundTemperature, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool SiteGroundTemperatureDeep_Impl::isMayDeepGroundTemperatureDefaulted() const {
      return isEmpty(openstudio::Site_GroundTemperature_DeepFields::MayDeepGroundTemperature);
    }

    bool SiteGroundTemperatureDeep_Impl::setMayDeepGroundTemperature(double mayDeepGroundTemperature) {
      const bool result = setDouble(openstudio::Site_GroundTemperature_DeepFields::MayDeepGroundTemperature, mayDeepGroundTemperature);
      OS_ASSERT(result);
      return result;
    }

    void SiteGroundTemperatureDeep_Impl::resetMayDeepGroundTemperature() {
      const bool result = setString(openstudio::Site_GroundTemperature_DeepFields::MayDeepGroundTemperature, "");
      OS_ASSERT(result);
    }

    double SiteGroundTemperatureDeep_Impl::juneDeepGroundTemperature() const {
      auto value = getDouble(openstudio::Site_GroundTemperature_DeepFields::JuneDeepGroundTemperature, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool SiteGroundTemperatureDeep_Impl::isJuneDeepGroundTemperatureDefaulted() const {
      return isEmpty(openstudio::Site_GroundTemperature_DeepFields::JuneDeepGroundTemperature);
    }

    bool SiteGroundTemperatureDeep_Impl::setJuneDeepGroundTemperature(double juneDeepGroundTemperature) {
      const bool result = setDouble(openstudio::Site_GroundTemperature_DeepFields::JuneDeepGroundTemperature, juneDeepGroundTemperature);
      OS_ASSERT(result);
      return result;
    }

    void SiteGroundTemperatureDeep_Impl::resetJuneDeepGroundTemperature() {
      const bool result = setString(openstudio::Site_GroundTemperature_DeepFields::JuneDeepGroundTemperature, "");
      OS_ASSERT(result);
    }

    double SiteGroundTemperatureDeep_Impl::julyDeepGroundTemperature() const {
      auto value = getDouble(openstudio::Site_GroundTemperature_DeepFields::JulyDeepGroundTemperature, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool SiteGroundTemperatureDeep_Impl::isJulyDeepGroundTemperatureDefaulted() const {
      return isEmpty(openstudio::Site_GroundTemperature_DeepFields::JulyDeepGroundTemperature);
    }

    bool SiteGroundTemperatureDeep_Impl::setJulyDeepGroundTemperature(double julyDeepGroundTemperature) {
      const bool result = setDouble(openstudio::Site_GroundTemperature_DeepFields::JulyDeepGroundTemperature, julyDeepGroundTemperature);
      OS_ASSERT(result);
      return result;
    }

    void SiteGroundTemperatureDeep_Impl::resetJulyDeepGroundTemperature() {
      const bool result = setString(openstudio::Site_GroundTemperature_DeepFields::JulyDeepGroundTemperature, "");
      OS_ASSERT(result);
    }

    double SiteGroundTemperatureDeep_Impl::augustDeepGroundTemperature() const {
      auto value = getDouble(openstudio::Site_GroundTemperature_DeepFields::AugustDeepGroundTemperature, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool SiteGroundTemperatureDeep_Impl::isAugustDeepGroundTemperatureDefaulted() const {
      return isEmpty(openstudio::Site_GroundTemperature_DeepFields::AugustDeepGroundTemperature);
    }

    bool SiteGroundTemperatureDeep_Impl::setAugustDeepGroundTemperature(double augustDeepGroundTemperature) {
      const bool result = setDouble(openstudio::Site_GroundTemperature_DeepFields::AugustDeepGroundTemperature, augustDeepGroundTemperature);
      OS_ASSERT(result);
      return result;
    }

    void SiteGroundTemperatureDeep_Impl::resetAugustDeepGroundTemperature() {
      const bool result = setString(openstudio::Site_GroundTemperature_DeepFields::AugustDeepGroundTemperature, "");
      OS_ASSERT(result);
    }

    double SiteGroundTemperatureDeep_Impl::septemberDeepGroundTemperature() const {
      auto value = getDouble(openstudio::Site_GroundTemperature_DeepFields::SeptemberDeepGroundTemperature, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool SiteGroundTemperatureDeep_Impl::isSeptemberDeepGroundTemperatureDefaulted() const {
      return isEmpty(openstudio::Site_GroundTemperature_DeepFields::SeptemberDeepGroundTemperature);
    }

    bool SiteGroundTemperatureDeep_Impl::setSeptemberDeepGroundTemperature(double septemberDeepGroundTemperature) {
      const bool result = setDouble(openstudio::Site_GroundTemperature_DeepFields::SeptemberDeepGroundTemperature, septemberDeepGroundTemperature);
      OS_ASSERT(result);
      return result;
    }

    void SiteGroundTemperatureDeep_Impl::resetSeptemberDeepGroundTemperature() {
      const bool result = setString(openstudio::Site_GroundTemperature_DeepFields::SeptemberDeepGroundTemperature, "");
      OS_ASSERT(result);
    }

    double SiteGroundTemperatureDeep_Impl::octoberDeepGroundTemperature() const {
      auto value = getDouble(openstudio::Site_GroundTemperature_DeepFields::OctoberDeepGroundTemperature, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool SiteGroundTemperatureDeep_Impl::isOctoberDeepGroundTemperatureDefaulted() const {
      return isEmpty(openstudio::Site_GroundTemperature_DeepFields::OctoberDeepGroundTemperature);
    }

    bool SiteGroundTemperatureDeep_Impl::setOctoberDeepGroundTemperature(double octoberDeepGroundTemperature) {
      const bool result = setDouble(openstudio::Site_GroundTemperature_DeepFields::OctoberDeepGroundTemperature, octoberDeepGroundTemperature);
      OS_ASSERT(result);
      return result;
    }

    void SiteGroundTemperatureDeep_Impl::resetOctoberDeepGroundTemperature() {
      const bool result = setString(openstudio::Site_GroundTemperature_DeepFields::OctoberDeepGroundTemperature, "");
      OS_ASSERT(result);
    }

    double SiteGroundTemperatureDeep_Impl::novemberDeepGroundTemperature() const {
      auto value = getDouble(openstudio::Site_GroundTemperature_DeepFields::NovemberDeepGroundTemperature, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool SiteGroundTemperatureDeep_Impl::isNovemberDeepGroundTemperatureDefaulted() const {
      return isEmpty(openstudio::Site_GroundTemperature_DeepFields::NovemberDeepGroundTemperature);
    }

    bool SiteGroundTemperatureDeep_Impl::setNovemberDeepGroundTemperature(double novemberDeepGroundTemperature) {
      const bool result = setDouble(openstudio::Site_GroundTemperature_DeepFields::NovemberDeepGroundTemperature, novemberDeepGroundTemperature);
      OS_ASSERT(result);
      return result;
    }

    void SiteGroundTemperatureDeep_Impl::resetNovemberDeepGroundTemperature() {
      const bool result = setString(openstudio::Site_GroundTemperature_DeepFields::NovemberDeepGroundTemperature, "");
      OS_ASSERT(result);
    }

    double SiteGroundTemperatureDeep_Impl::decemberDeepGroundTemperature() const {
      auto value = getDouble(openstudio::Site_GroundTemperature_DeepFields::DecemberDeepGroundTemperature, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool SiteGroundTemperatureDeep_Impl::isDecemberDeepGroundTemperatureDefaulted() const {
      return isEmpty(openstudio::Site_GroundTemperature_DeepFields::DecemberDeepGroundTemperature);
    }

    bool SiteGroundTemperatureDeep_Impl::setDecemberDeepGroundTemperature(double decemberDeepGroundTemperature) {
      const bool result = setDouble(openstudio::Site_GroundTemperature_DeepFields::DecemberDeepGroundTemperature, decemberDeepGroundTemperature);
      OS_ASSERT(result);
      return result;
    }

    void SiteGroundTemperatureDeep_Impl::resetDecemberDeepGroundTemperature() {
      const bool result = setString(openstudio::Site_GroundTemperature_DeepFields::DecemberDeepGroundTemperature, "");
      OS_ASSERT(result);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
