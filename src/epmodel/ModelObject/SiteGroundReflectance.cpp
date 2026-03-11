/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include "SiteGroundReflectance.hpp"
#include "SiteGroundReflectance_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Site_GroundReflectance_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  SiteGroundReflectance::SiteGroundReflectance(const Model& model) : ModelObject(SiteGroundReflectance::iddObjectType(), model) {}

  SiteGroundReflectance::SiteGroundReflectance(std::shared_ptr<detail::SiteGroundReflectance_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType SiteGroundReflectance::iddObjectType() {
    return IddObjectType::Site_GroundReflectance;
  }

  double SiteGroundReflectance::januaryGroundReflectance() const {
    return getImpl<detail::SiteGroundReflectance_Impl>()->januaryGroundReflectance();
  }

  bool SiteGroundReflectance::isJanuaryGroundReflectanceDefaulted() const {
    return getImpl<detail::SiteGroundReflectance_Impl>()->isJanuaryGroundReflectanceDefaulted();
  }

  double SiteGroundReflectance::februaryGroundReflectance() const {
    return getImpl<detail::SiteGroundReflectance_Impl>()->februaryGroundReflectance();
  }

  bool SiteGroundReflectance::isFebruaryGroundReflectanceDefaulted() const {
    return getImpl<detail::SiteGroundReflectance_Impl>()->isFebruaryGroundReflectanceDefaulted();
  }

  double SiteGroundReflectance::marchGroundReflectance() const {
    return getImpl<detail::SiteGroundReflectance_Impl>()->marchGroundReflectance();
  }

  bool SiteGroundReflectance::isMarchGroundReflectanceDefaulted() const {
    return getImpl<detail::SiteGroundReflectance_Impl>()->isMarchGroundReflectanceDefaulted();
  }

  double SiteGroundReflectance::aprilGroundReflectance() const {
    return getImpl<detail::SiteGroundReflectance_Impl>()->aprilGroundReflectance();
  }

  bool SiteGroundReflectance::isAprilGroundReflectanceDefaulted() const {
    return getImpl<detail::SiteGroundReflectance_Impl>()->isAprilGroundReflectanceDefaulted();
  }

  double SiteGroundReflectance::mayGroundReflectance() const {
    return getImpl<detail::SiteGroundReflectance_Impl>()->mayGroundReflectance();
  }

  bool SiteGroundReflectance::isMayGroundReflectanceDefaulted() const {
    return getImpl<detail::SiteGroundReflectance_Impl>()->isMayGroundReflectanceDefaulted();
  }

  double SiteGroundReflectance::juneGroundReflectance() const {
    return getImpl<detail::SiteGroundReflectance_Impl>()->juneGroundReflectance();
  }

  bool SiteGroundReflectance::isJuneGroundReflectanceDefaulted() const {
    return getImpl<detail::SiteGroundReflectance_Impl>()->isJuneGroundReflectanceDefaulted();
  }

  double SiteGroundReflectance::julyGroundReflectance() const {
    return getImpl<detail::SiteGroundReflectance_Impl>()->julyGroundReflectance();
  }

  bool SiteGroundReflectance::isJulyGroundReflectanceDefaulted() const {
    return getImpl<detail::SiteGroundReflectance_Impl>()->isJulyGroundReflectanceDefaulted();
  }

  double SiteGroundReflectance::augustGroundReflectance() const {
    return getImpl<detail::SiteGroundReflectance_Impl>()->augustGroundReflectance();
  }

  bool SiteGroundReflectance::isAugustGroundReflectanceDefaulted() const {
    return getImpl<detail::SiteGroundReflectance_Impl>()->isAugustGroundReflectanceDefaulted();
  }

  double SiteGroundReflectance::septemberGroundReflectance() const {
    return getImpl<detail::SiteGroundReflectance_Impl>()->septemberGroundReflectance();
  }

  bool SiteGroundReflectance::isSeptemberGroundReflectanceDefaulted() const {
    return getImpl<detail::SiteGroundReflectance_Impl>()->isSeptemberGroundReflectanceDefaulted();
  }

  double SiteGroundReflectance::octoberGroundReflectance() const {
    return getImpl<detail::SiteGroundReflectance_Impl>()->octoberGroundReflectance();
  }

  bool SiteGroundReflectance::isOctoberGroundReflectanceDefaulted() const {
    return getImpl<detail::SiteGroundReflectance_Impl>()->isOctoberGroundReflectanceDefaulted();
  }

  double SiteGroundReflectance::novemberGroundReflectance() const {
    return getImpl<detail::SiteGroundReflectance_Impl>()->novemberGroundReflectance();
  }

  bool SiteGroundReflectance::isNovemberGroundReflectanceDefaulted() const {
    return getImpl<detail::SiteGroundReflectance_Impl>()->isNovemberGroundReflectanceDefaulted();
  }

  double SiteGroundReflectance::decemberGroundReflectance() const {
    return getImpl<detail::SiteGroundReflectance_Impl>()->decemberGroundReflectance();
  }

  bool SiteGroundReflectance::isDecemberGroundReflectanceDefaulted() const {
    return getImpl<detail::SiteGroundReflectance_Impl>()->isDecemberGroundReflectanceDefaulted();
  }

  bool SiteGroundReflectance::setJanuaryGroundReflectance(double januaryGroundReflectance) {
    return getImpl<detail::SiteGroundReflectance_Impl>()->setJanuaryGroundReflectance(januaryGroundReflectance);
  }

  void SiteGroundReflectance::resetJanuaryGroundReflectance() {
    getImpl<detail::SiteGroundReflectance_Impl>()->resetJanuaryGroundReflectance();
  }

  bool SiteGroundReflectance::setFebruaryGroundReflectance(double februaryGroundReflectance) {
    return getImpl<detail::SiteGroundReflectance_Impl>()->setFebruaryGroundReflectance(februaryGroundReflectance);
  }

  void SiteGroundReflectance::resetFebruaryGroundReflectance() {
    getImpl<detail::SiteGroundReflectance_Impl>()->resetFebruaryGroundReflectance();
  }

  bool SiteGroundReflectance::setMarchGroundReflectance(double marchGroundReflectance) {
    return getImpl<detail::SiteGroundReflectance_Impl>()->setMarchGroundReflectance(marchGroundReflectance);
  }

  void SiteGroundReflectance::resetMarchGroundReflectance() {
    getImpl<detail::SiteGroundReflectance_Impl>()->resetMarchGroundReflectance();
  }

  bool SiteGroundReflectance::setAprilGroundReflectance(double aprilGroundReflectance) {
    return getImpl<detail::SiteGroundReflectance_Impl>()->setAprilGroundReflectance(aprilGroundReflectance);
  }

  void SiteGroundReflectance::resetAprilGroundReflectance() {
    getImpl<detail::SiteGroundReflectance_Impl>()->resetAprilGroundReflectance();
  }

  bool SiteGroundReflectance::setMayGroundReflectance(double mayGroundReflectance) {
    return getImpl<detail::SiteGroundReflectance_Impl>()->setMayGroundReflectance(mayGroundReflectance);
  }

  void SiteGroundReflectance::resetMayGroundReflectance() {
    getImpl<detail::SiteGroundReflectance_Impl>()->resetMayGroundReflectance();
  }

  bool SiteGroundReflectance::setJuneGroundReflectance(double juneGroundReflectance) {
    return getImpl<detail::SiteGroundReflectance_Impl>()->setJuneGroundReflectance(juneGroundReflectance);
  }

  void SiteGroundReflectance::resetJuneGroundReflectance() {
    getImpl<detail::SiteGroundReflectance_Impl>()->resetJuneGroundReflectance();
  }

  bool SiteGroundReflectance::setJulyGroundReflectance(double julyGroundReflectance) {
    return getImpl<detail::SiteGroundReflectance_Impl>()->setJulyGroundReflectance(julyGroundReflectance);
  }

  void SiteGroundReflectance::resetJulyGroundReflectance() {
    getImpl<detail::SiteGroundReflectance_Impl>()->resetJulyGroundReflectance();
  }

  bool SiteGroundReflectance::setAugustGroundReflectance(double augustGroundReflectance) {
    return getImpl<detail::SiteGroundReflectance_Impl>()->setAugustGroundReflectance(augustGroundReflectance);
  }

  void SiteGroundReflectance::resetAugustGroundReflectance() {
    getImpl<detail::SiteGroundReflectance_Impl>()->resetAugustGroundReflectance();
  }

  bool SiteGroundReflectance::setSeptemberGroundReflectance(double septemberGroundReflectance) {
    return getImpl<detail::SiteGroundReflectance_Impl>()->setSeptemberGroundReflectance(septemberGroundReflectance);
  }

  void SiteGroundReflectance::resetSeptemberGroundReflectance() {
    getImpl<detail::SiteGroundReflectance_Impl>()->resetSeptemberGroundReflectance();
  }

  bool SiteGroundReflectance::setOctoberGroundReflectance(double octoberGroundReflectance) {
    return getImpl<detail::SiteGroundReflectance_Impl>()->setOctoberGroundReflectance(octoberGroundReflectance);
  }

  void SiteGroundReflectance::resetOctoberGroundReflectance() {
    getImpl<detail::SiteGroundReflectance_Impl>()->resetOctoberGroundReflectance();
  }

  bool SiteGroundReflectance::setNovemberGroundReflectance(double novemberGroundReflectance) {
    return getImpl<detail::SiteGroundReflectance_Impl>()->setNovemberGroundReflectance(novemberGroundReflectance);
  }

  void SiteGroundReflectance::resetNovemberGroundReflectance() {
    getImpl<detail::SiteGroundReflectance_Impl>()->resetNovemberGroundReflectance();
  }

  bool SiteGroundReflectance::setDecemberGroundReflectance(double decemberGroundReflectance) {
    return getImpl<detail::SiteGroundReflectance_Impl>()->setDecemberGroundReflectance(decemberGroundReflectance);
  }

  void SiteGroundReflectance::resetDecemberGroundReflectance() {
    getImpl<detail::SiteGroundReflectance_Impl>()->resetDecemberGroundReflectance();
  }

  namespace detail {

    double SiteGroundReflectance_Impl::januaryGroundReflectance() const {
      const auto value = getDouble(openstudio::Site_GroundReflectanceFields::JanuaryGroundReflectance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SiteGroundReflectance_Impl::isJanuaryGroundReflectanceDefaulted() const {
      return isEmpty(openstudio::Site_GroundReflectanceFields::JanuaryGroundReflectance);
    }

    bool SiteGroundReflectance_Impl::setJanuaryGroundReflectance(double januaryGroundReflectance) {
      return setDouble(openstudio::Site_GroundReflectanceFields::JanuaryGroundReflectance, januaryGroundReflectance);
    }

    void SiteGroundReflectance_Impl::resetJanuaryGroundReflectance() {
      OS_ASSERT(setString(openstudio::Site_GroundReflectanceFields::JanuaryGroundReflectance, ""));
    }

    double SiteGroundReflectance_Impl::februaryGroundReflectance() const {
      const auto value = getDouble(openstudio::Site_GroundReflectanceFields::FebruaryGroundReflectance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SiteGroundReflectance_Impl::isFebruaryGroundReflectanceDefaulted() const {
      return isEmpty(openstudio::Site_GroundReflectanceFields::FebruaryGroundReflectance);
    }

    bool SiteGroundReflectance_Impl::setFebruaryGroundReflectance(double februaryGroundReflectance) {
      return setDouble(openstudio::Site_GroundReflectanceFields::FebruaryGroundReflectance, februaryGroundReflectance);
    }

    void SiteGroundReflectance_Impl::resetFebruaryGroundReflectance() {
      OS_ASSERT(setString(openstudio::Site_GroundReflectanceFields::FebruaryGroundReflectance, ""));
    }

    double SiteGroundReflectance_Impl::marchGroundReflectance() const {
      const auto value = getDouble(openstudio::Site_GroundReflectanceFields::MarchGroundReflectance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SiteGroundReflectance_Impl::isMarchGroundReflectanceDefaulted() const {
      return isEmpty(openstudio::Site_GroundReflectanceFields::MarchGroundReflectance);
    }

    bool SiteGroundReflectance_Impl::setMarchGroundReflectance(double marchGroundReflectance) {
      return setDouble(openstudio::Site_GroundReflectanceFields::MarchGroundReflectance, marchGroundReflectance);
    }

    void SiteGroundReflectance_Impl::resetMarchGroundReflectance() {
      OS_ASSERT(setString(openstudio::Site_GroundReflectanceFields::MarchGroundReflectance, ""));
    }

    double SiteGroundReflectance_Impl::aprilGroundReflectance() const {
      const auto value = getDouble(openstudio::Site_GroundReflectanceFields::AprilGroundReflectance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SiteGroundReflectance_Impl::isAprilGroundReflectanceDefaulted() const {
      return isEmpty(openstudio::Site_GroundReflectanceFields::AprilGroundReflectance);
    }

    bool SiteGroundReflectance_Impl::setAprilGroundReflectance(double aprilGroundReflectance) {
      return setDouble(openstudio::Site_GroundReflectanceFields::AprilGroundReflectance, aprilGroundReflectance);
    }

    void SiteGroundReflectance_Impl::resetAprilGroundReflectance() {
      OS_ASSERT(setString(openstudio::Site_GroundReflectanceFields::AprilGroundReflectance, ""));
    }

    double SiteGroundReflectance_Impl::mayGroundReflectance() const {
      const auto value = getDouble(openstudio::Site_GroundReflectanceFields::MayGroundReflectance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SiteGroundReflectance_Impl::isMayGroundReflectanceDefaulted() const {
      return isEmpty(openstudio::Site_GroundReflectanceFields::MayGroundReflectance);
    }

    bool SiteGroundReflectance_Impl::setMayGroundReflectance(double mayGroundReflectance) {
      return setDouble(openstudio::Site_GroundReflectanceFields::MayGroundReflectance, mayGroundReflectance);
    }

    void SiteGroundReflectance_Impl::resetMayGroundReflectance() {
      OS_ASSERT(setString(openstudio::Site_GroundReflectanceFields::MayGroundReflectance, ""));
    }

    double SiteGroundReflectance_Impl::juneGroundReflectance() const {
      const auto value = getDouble(openstudio::Site_GroundReflectanceFields::JuneGroundReflectance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SiteGroundReflectance_Impl::isJuneGroundReflectanceDefaulted() const {
      return isEmpty(openstudio::Site_GroundReflectanceFields::JuneGroundReflectance);
    }

    bool SiteGroundReflectance_Impl::setJuneGroundReflectance(double juneGroundReflectance) {
      return setDouble(openstudio::Site_GroundReflectanceFields::JuneGroundReflectance, juneGroundReflectance);
    }

    void SiteGroundReflectance_Impl::resetJuneGroundReflectance() {
      OS_ASSERT(setString(openstudio::Site_GroundReflectanceFields::JuneGroundReflectance, ""));
    }

    double SiteGroundReflectance_Impl::julyGroundReflectance() const {
      const auto value = getDouble(openstudio::Site_GroundReflectanceFields::JulyGroundReflectance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SiteGroundReflectance_Impl::isJulyGroundReflectanceDefaulted() const {
      return isEmpty(openstudio::Site_GroundReflectanceFields::JulyGroundReflectance);
    }

    bool SiteGroundReflectance_Impl::setJulyGroundReflectance(double julyGroundReflectance) {
      return setDouble(openstudio::Site_GroundReflectanceFields::JulyGroundReflectance, julyGroundReflectance);
    }

    void SiteGroundReflectance_Impl::resetJulyGroundReflectance() {
      OS_ASSERT(setString(openstudio::Site_GroundReflectanceFields::JulyGroundReflectance, ""));
    }

    double SiteGroundReflectance_Impl::augustGroundReflectance() const {
      const auto value = getDouble(openstudio::Site_GroundReflectanceFields::AugustGroundReflectance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SiteGroundReflectance_Impl::isAugustGroundReflectanceDefaulted() const {
      return isEmpty(openstudio::Site_GroundReflectanceFields::AugustGroundReflectance);
    }

    bool SiteGroundReflectance_Impl::setAugustGroundReflectance(double augustGroundReflectance) {
      return setDouble(openstudio::Site_GroundReflectanceFields::AugustGroundReflectance, augustGroundReflectance);
    }

    void SiteGroundReflectance_Impl::resetAugustGroundReflectance() {
      OS_ASSERT(setString(openstudio::Site_GroundReflectanceFields::AugustGroundReflectance, ""));
    }

    double SiteGroundReflectance_Impl::septemberGroundReflectance() const {
      const auto value = getDouble(openstudio::Site_GroundReflectanceFields::SeptemberGroundReflectance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SiteGroundReflectance_Impl::isSeptemberGroundReflectanceDefaulted() const {
      return isEmpty(openstudio::Site_GroundReflectanceFields::SeptemberGroundReflectance);
    }

    bool SiteGroundReflectance_Impl::setSeptemberGroundReflectance(double septemberGroundReflectance) {
      return setDouble(openstudio::Site_GroundReflectanceFields::SeptemberGroundReflectance, septemberGroundReflectance);
    }

    void SiteGroundReflectance_Impl::resetSeptemberGroundReflectance() {
      OS_ASSERT(setString(openstudio::Site_GroundReflectanceFields::SeptemberGroundReflectance, ""));
    }

    double SiteGroundReflectance_Impl::octoberGroundReflectance() const {
      const auto value = getDouble(openstudio::Site_GroundReflectanceFields::OctoberGroundReflectance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SiteGroundReflectance_Impl::isOctoberGroundReflectanceDefaulted() const {
      return isEmpty(openstudio::Site_GroundReflectanceFields::OctoberGroundReflectance);
    }

    bool SiteGroundReflectance_Impl::setOctoberGroundReflectance(double octoberGroundReflectance) {
      return setDouble(openstudio::Site_GroundReflectanceFields::OctoberGroundReflectance, octoberGroundReflectance);
    }

    void SiteGroundReflectance_Impl::resetOctoberGroundReflectance() {
      OS_ASSERT(setString(openstudio::Site_GroundReflectanceFields::OctoberGroundReflectance, ""));
    }

    double SiteGroundReflectance_Impl::novemberGroundReflectance() const {
      const auto value = getDouble(openstudio::Site_GroundReflectanceFields::NovemberGroundReflectance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SiteGroundReflectance_Impl::isNovemberGroundReflectanceDefaulted() const {
      return isEmpty(openstudio::Site_GroundReflectanceFields::NovemberGroundReflectance);
    }

    bool SiteGroundReflectance_Impl::setNovemberGroundReflectance(double novemberGroundReflectance) {
      return setDouble(openstudio::Site_GroundReflectanceFields::NovemberGroundReflectance, novemberGroundReflectance);
    }

    void SiteGroundReflectance_Impl::resetNovemberGroundReflectance() {
      OS_ASSERT(setString(openstudio::Site_GroundReflectanceFields::NovemberGroundReflectance, ""));
    }

    double SiteGroundReflectance_Impl::decemberGroundReflectance() const {
      const auto value = getDouble(openstudio::Site_GroundReflectanceFields::DecemberGroundReflectance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SiteGroundReflectance_Impl::isDecemberGroundReflectanceDefaulted() const {
      return isEmpty(openstudio::Site_GroundReflectanceFields::DecemberGroundReflectance);
    }

    bool SiteGroundReflectance_Impl::setDecemberGroundReflectance(double decemberGroundReflectance) {
      return setDouble(openstudio::Site_GroundReflectanceFields::DecemberGroundReflectance, decemberGroundReflectance);
    }

    void SiteGroundReflectance_Impl::resetDecemberGroundReflectance() {
      OS_ASSERT(setString(openstudio::Site_GroundReflectanceFields::DecemberGroundReflectance, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
