/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include "SiteGroundTemperatureBuildingSurface.hpp"
#include "SiteGroundTemperatureBuildingSurface_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Site_GroundTemperature_BuildingSurface_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  SiteGroundTemperatureBuildingSurface::SiteGroundTemperatureBuildingSurface(const Model& model)
    : ModelObject(SiteGroundTemperatureBuildingSurface::iddObjectType(), model) {}

  SiteGroundTemperatureBuildingSurface::SiteGroundTemperatureBuildingSurface(std::shared_ptr<detail::SiteGroundTemperatureBuildingSurface_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType SiteGroundTemperatureBuildingSurface::iddObjectType() {
    return IddObjectType::Site_GroundTemperature_BuildingSurface;
  }

  double SiteGroundTemperatureBuildingSurface::januaryGroundTemperature() const {
    return getImpl<detail::SiteGroundTemperatureBuildingSurface_Impl>()->januaryGroundTemperature();
  }

  bool SiteGroundTemperatureBuildingSurface::isJanuaryGroundTemperatureDefaulted() const {
    return getImpl<detail::SiteGroundTemperatureBuildingSurface_Impl>()->isJanuaryGroundTemperatureDefaulted();
  }

  bool SiteGroundTemperatureBuildingSurface::setJanuaryGroundTemperature(double januaryGroundTemperature) {
    return getImpl<detail::SiteGroundTemperatureBuildingSurface_Impl>()->setJanuaryGroundTemperature(januaryGroundTemperature);
  }

  void SiteGroundTemperatureBuildingSurface::resetJanuaryGroundTemperature() {
    getImpl<detail::SiteGroundTemperatureBuildingSurface_Impl>()->resetJanuaryGroundTemperature();
  }

  double SiteGroundTemperatureBuildingSurface::februaryGroundTemperature() const {
    return getImpl<detail::SiteGroundTemperatureBuildingSurface_Impl>()->februaryGroundTemperature();
  }

  bool SiteGroundTemperatureBuildingSurface::isFebruaryGroundTemperatureDefaulted() const {
    return getImpl<detail::SiteGroundTemperatureBuildingSurface_Impl>()->isFebruaryGroundTemperatureDefaulted();
  }

  bool SiteGroundTemperatureBuildingSurface::setFebruaryGroundTemperature(double februaryGroundTemperature) {
    return getImpl<detail::SiteGroundTemperatureBuildingSurface_Impl>()->setFebruaryGroundTemperature(februaryGroundTemperature);
  }

  void SiteGroundTemperatureBuildingSurface::resetFebruaryGroundTemperature() {
    getImpl<detail::SiteGroundTemperatureBuildingSurface_Impl>()->resetFebruaryGroundTemperature();
  }

  double SiteGroundTemperatureBuildingSurface::marchGroundTemperature() const {
    return getImpl<detail::SiteGroundTemperatureBuildingSurface_Impl>()->marchGroundTemperature();
  }

  bool SiteGroundTemperatureBuildingSurface::isMarchGroundTemperatureDefaulted() const {
    return getImpl<detail::SiteGroundTemperatureBuildingSurface_Impl>()->isMarchGroundTemperatureDefaulted();
  }

  bool SiteGroundTemperatureBuildingSurface::setMarchGroundTemperature(double marchGroundTemperature) {
    return getImpl<detail::SiteGroundTemperatureBuildingSurface_Impl>()->setMarchGroundTemperature(marchGroundTemperature);
  }

  void SiteGroundTemperatureBuildingSurface::resetMarchGroundTemperature() {
    getImpl<detail::SiteGroundTemperatureBuildingSurface_Impl>()->resetMarchGroundTemperature();
  }

  double SiteGroundTemperatureBuildingSurface::aprilGroundTemperature() const {
    return getImpl<detail::SiteGroundTemperatureBuildingSurface_Impl>()->aprilGroundTemperature();
  }

  bool SiteGroundTemperatureBuildingSurface::isAprilGroundTemperatureDefaulted() const {
    return getImpl<detail::SiteGroundTemperatureBuildingSurface_Impl>()->isAprilGroundTemperatureDefaulted();
  }

  bool SiteGroundTemperatureBuildingSurface::setAprilGroundTemperature(double aprilGroundTemperature) {
    return getImpl<detail::SiteGroundTemperatureBuildingSurface_Impl>()->setAprilGroundTemperature(aprilGroundTemperature);
  }

  void SiteGroundTemperatureBuildingSurface::resetAprilGroundTemperature() {
    getImpl<detail::SiteGroundTemperatureBuildingSurface_Impl>()->resetAprilGroundTemperature();
  }

  double SiteGroundTemperatureBuildingSurface::mayGroundTemperature() const {
    return getImpl<detail::SiteGroundTemperatureBuildingSurface_Impl>()->mayGroundTemperature();
  }

  bool SiteGroundTemperatureBuildingSurface::isMayGroundTemperatureDefaulted() const {
    return getImpl<detail::SiteGroundTemperatureBuildingSurface_Impl>()->isMayGroundTemperatureDefaulted();
  }

  bool SiteGroundTemperatureBuildingSurface::setMayGroundTemperature(double mayGroundTemperature) {
    return getImpl<detail::SiteGroundTemperatureBuildingSurface_Impl>()->setMayGroundTemperature(mayGroundTemperature);
  }

  void SiteGroundTemperatureBuildingSurface::resetMayGroundTemperature() {
    getImpl<detail::SiteGroundTemperatureBuildingSurface_Impl>()->resetMayGroundTemperature();
  }

  double SiteGroundTemperatureBuildingSurface::juneGroundTemperature() const {
    return getImpl<detail::SiteGroundTemperatureBuildingSurface_Impl>()->juneGroundTemperature();
  }

  bool SiteGroundTemperatureBuildingSurface::isJuneGroundTemperatureDefaulted() const {
    return getImpl<detail::SiteGroundTemperatureBuildingSurface_Impl>()->isJuneGroundTemperatureDefaulted();
  }

  bool SiteGroundTemperatureBuildingSurface::setJuneGroundTemperature(double juneGroundTemperature) {
    return getImpl<detail::SiteGroundTemperatureBuildingSurface_Impl>()->setJuneGroundTemperature(juneGroundTemperature);
  }

  void SiteGroundTemperatureBuildingSurface::resetJuneGroundTemperature() {
    getImpl<detail::SiteGroundTemperatureBuildingSurface_Impl>()->resetJuneGroundTemperature();
  }

  double SiteGroundTemperatureBuildingSurface::julyGroundTemperature() const {
    return getImpl<detail::SiteGroundTemperatureBuildingSurface_Impl>()->julyGroundTemperature();
  }

  bool SiteGroundTemperatureBuildingSurface::isJulyGroundTemperatureDefaulted() const {
    return getImpl<detail::SiteGroundTemperatureBuildingSurface_Impl>()->isJulyGroundTemperatureDefaulted();
  }

  bool SiteGroundTemperatureBuildingSurface::setJulyGroundTemperature(double julyGroundTemperature) {
    return getImpl<detail::SiteGroundTemperatureBuildingSurface_Impl>()->setJulyGroundTemperature(julyGroundTemperature);
  }

  void SiteGroundTemperatureBuildingSurface::resetJulyGroundTemperature() {
    getImpl<detail::SiteGroundTemperatureBuildingSurface_Impl>()->resetJulyGroundTemperature();
  }

  double SiteGroundTemperatureBuildingSurface::augustGroundTemperature() const {
    return getImpl<detail::SiteGroundTemperatureBuildingSurface_Impl>()->augustGroundTemperature();
  }

  bool SiteGroundTemperatureBuildingSurface::isAugustGroundTemperatureDefaulted() const {
    return getImpl<detail::SiteGroundTemperatureBuildingSurface_Impl>()->isAugustGroundTemperatureDefaulted();
  }

  bool SiteGroundTemperatureBuildingSurface::setAugustGroundTemperature(double augustGroundTemperature) {
    return getImpl<detail::SiteGroundTemperatureBuildingSurface_Impl>()->setAugustGroundTemperature(augustGroundTemperature);
  }

  void SiteGroundTemperatureBuildingSurface::resetAugustGroundTemperature() {
    getImpl<detail::SiteGroundTemperatureBuildingSurface_Impl>()->resetAugustGroundTemperature();
  }

  double SiteGroundTemperatureBuildingSurface::septemberGroundTemperature() const {
    return getImpl<detail::SiteGroundTemperatureBuildingSurface_Impl>()->septemberGroundTemperature();
  }

  bool SiteGroundTemperatureBuildingSurface::isSeptemberGroundTemperatureDefaulted() const {
    return getImpl<detail::SiteGroundTemperatureBuildingSurface_Impl>()->isSeptemberGroundTemperatureDefaulted();
  }

  bool SiteGroundTemperatureBuildingSurface::setSeptemberGroundTemperature(double septemberGroundTemperature) {
    return getImpl<detail::SiteGroundTemperatureBuildingSurface_Impl>()->setSeptemberGroundTemperature(septemberGroundTemperature);
  }

  void SiteGroundTemperatureBuildingSurface::resetSeptemberGroundTemperature() {
    getImpl<detail::SiteGroundTemperatureBuildingSurface_Impl>()->resetSeptemberGroundTemperature();
  }

  double SiteGroundTemperatureBuildingSurface::octoberGroundTemperature() const {
    return getImpl<detail::SiteGroundTemperatureBuildingSurface_Impl>()->octoberGroundTemperature();
  }

  bool SiteGroundTemperatureBuildingSurface::isOctoberGroundTemperatureDefaulted() const {
    return getImpl<detail::SiteGroundTemperatureBuildingSurface_Impl>()->isOctoberGroundTemperatureDefaulted();
  }

  bool SiteGroundTemperatureBuildingSurface::setOctoberGroundTemperature(double octoberGroundTemperature) {
    return getImpl<detail::SiteGroundTemperatureBuildingSurface_Impl>()->setOctoberGroundTemperature(octoberGroundTemperature);
  }

  void SiteGroundTemperatureBuildingSurface::resetOctoberGroundTemperature() {
    getImpl<detail::SiteGroundTemperatureBuildingSurface_Impl>()->resetOctoberGroundTemperature();
  }

  double SiteGroundTemperatureBuildingSurface::novemberGroundTemperature() const {
    return getImpl<detail::SiteGroundTemperatureBuildingSurface_Impl>()->novemberGroundTemperature();
  }

  bool SiteGroundTemperatureBuildingSurface::isNovemberGroundTemperatureDefaulted() const {
    return getImpl<detail::SiteGroundTemperatureBuildingSurface_Impl>()->isNovemberGroundTemperatureDefaulted();
  }

  bool SiteGroundTemperatureBuildingSurface::setNovemberGroundTemperature(double novemberGroundTemperature) {
    return getImpl<detail::SiteGroundTemperatureBuildingSurface_Impl>()->setNovemberGroundTemperature(novemberGroundTemperature);
  }

  void SiteGroundTemperatureBuildingSurface::resetNovemberGroundTemperature() {
    getImpl<detail::SiteGroundTemperatureBuildingSurface_Impl>()->resetNovemberGroundTemperature();
  }

  double SiteGroundTemperatureBuildingSurface::decemberGroundTemperature() const {
    return getImpl<detail::SiteGroundTemperatureBuildingSurface_Impl>()->decemberGroundTemperature();
  }

  bool SiteGroundTemperatureBuildingSurface::isDecemberGroundTemperatureDefaulted() const {
    return getImpl<detail::SiteGroundTemperatureBuildingSurface_Impl>()->isDecemberGroundTemperatureDefaulted();
  }

  bool SiteGroundTemperatureBuildingSurface::setDecemberGroundTemperature(double decemberGroundTemperature) {
    return getImpl<detail::SiteGroundTemperatureBuildingSurface_Impl>()->setDecemberGroundTemperature(decemberGroundTemperature);
  }

  void SiteGroundTemperatureBuildingSurface::resetDecemberGroundTemperature() {
    getImpl<detail::SiteGroundTemperatureBuildingSurface_Impl>()->resetDecemberGroundTemperature();
  }

  namespace detail {

    double SiteGroundTemperatureBuildingSurface_Impl::januaryGroundTemperature() const {
      const auto value = getDouble(openstudio::Site_GroundTemperature_BuildingSurfaceFields::JanuaryGroundTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SiteGroundTemperatureBuildingSurface_Impl::isJanuaryGroundTemperatureDefaulted() const {
      return isEmpty(openstudio::Site_GroundTemperature_BuildingSurfaceFields::JanuaryGroundTemperature);
    }

    bool SiteGroundTemperatureBuildingSurface_Impl::setJanuaryGroundTemperature(double januaryGroundTemperature) {
      return setDouble(openstudio::Site_GroundTemperature_BuildingSurfaceFields::JanuaryGroundTemperature, januaryGroundTemperature);
    }

    void SiteGroundTemperatureBuildingSurface_Impl::resetJanuaryGroundTemperature() {
      OS_ASSERT(setString(openstudio::Site_GroundTemperature_BuildingSurfaceFields::JanuaryGroundTemperature, ""));
    }

    double SiteGroundTemperatureBuildingSurface_Impl::februaryGroundTemperature() const {
      const auto value = getDouble(openstudio::Site_GroundTemperature_BuildingSurfaceFields::FebruaryGroundTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SiteGroundTemperatureBuildingSurface_Impl::isFebruaryGroundTemperatureDefaulted() const {
      return isEmpty(openstudio::Site_GroundTemperature_BuildingSurfaceFields::FebruaryGroundTemperature);
    }

    bool SiteGroundTemperatureBuildingSurface_Impl::setFebruaryGroundTemperature(double februaryGroundTemperature) {
      return setDouble(openstudio::Site_GroundTemperature_BuildingSurfaceFields::FebruaryGroundTemperature, februaryGroundTemperature);
    }

    void SiteGroundTemperatureBuildingSurface_Impl::resetFebruaryGroundTemperature() {
      OS_ASSERT(setString(openstudio::Site_GroundTemperature_BuildingSurfaceFields::FebruaryGroundTemperature, ""));
    }

    double SiteGroundTemperatureBuildingSurface_Impl::marchGroundTemperature() const {
      const auto value = getDouble(openstudio::Site_GroundTemperature_BuildingSurfaceFields::MarchGroundTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SiteGroundTemperatureBuildingSurface_Impl::isMarchGroundTemperatureDefaulted() const {
      return isEmpty(openstudio::Site_GroundTemperature_BuildingSurfaceFields::MarchGroundTemperature);
    }

    bool SiteGroundTemperatureBuildingSurface_Impl::setMarchGroundTemperature(double marchGroundTemperature) {
      return setDouble(openstudio::Site_GroundTemperature_BuildingSurfaceFields::MarchGroundTemperature, marchGroundTemperature);
    }

    void SiteGroundTemperatureBuildingSurface_Impl::resetMarchGroundTemperature() {
      OS_ASSERT(setString(openstudio::Site_GroundTemperature_BuildingSurfaceFields::MarchGroundTemperature, ""));
    }

    double SiteGroundTemperatureBuildingSurface_Impl::aprilGroundTemperature() const {
      const auto value = getDouble(openstudio::Site_GroundTemperature_BuildingSurfaceFields::AprilGroundTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SiteGroundTemperatureBuildingSurface_Impl::isAprilGroundTemperatureDefaulted() const {
      return isEmpty(openstudio::Site_GroundTemperature_BuildingSurfaceFields::AprilGroundTemperature);
    }

    bool SiteGroundTemperatureBuildingSurface_Impl::setAprilGroundTemperature(double aprilGroundTemperature) {
      return setDouble(openstudio::Site_GroundTemperature_BuildingSurfaceFields::AprilGroundTemperature, aprilGroundTemperature);
    }

    void SiteGroundTemperatureBuildingSurface_Impl::resetAprilGroundTemperature() {
      OS_ASSERT(setString(openstudio::Site_GroundTemperature_BuildingSurfaceFields::AprilGroundTemperature, ""));
    }

    double SiteGroundTemperatureBuildingSurface_Impl::mayGroundTemperature() const {
      const auto value = getDouble(openstudio::Site_GroundTemperature_BuildingSurfaceFields::MayGroundTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SiteGroundTemperatureBuildingSurface_Impl::isMayGroundTemperatureDefaulted() const {
      return isEmpty(openstudio::Site_GroundTemperature_BuildingSurfaceFields::MayGroundTemperature);
    }

    bool SiteGroundTemperatureBuildingSurface_Impl::setMayGroundTemperature(double mayGroundTemperature) {
      return setDouble(openstudio::Site_GroundTemperature_BuildingSurfaceFields::MayGroundTemperature, mayGroundTemperature);
    }

    void SiteGroundTemperatureBuildingSurface_Impl::resetMayGroundTemperature() {
      OS_ASSERT(setString(openstudio::Site_GroundTemperature_BuildingSurfaceFields::MayGroundTemperature, ""));
    }

    double SiteGroundTemperatureBuildingSurface_Impl::juneGroundTemperature() const {
      const auto value = getDouble(openstudio::Site_GroundTemperature_BuildingSurfaceFields::JuneGroundTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SiteGroundTemperatureBuildingSurface_Impl::isJuneGroundTemperatureDefaulted() const {
      return isEmpty(openstudio::Site_GroundTemperature_BuildingSurfaceFields::JuneGroundTemperature);
    }

    bool SiteGroundTemperatureBuildingSurface_Impl::setJuneGroundTemperature(double juneGroundTemperature) {
      return setDouble(openstudio::Site_GroundTemperature_BuildingSurfaceFields::JuneGroundTemperature, juneGroundTemperature);
    }

    void SiteGroundTemperatureBuildingSurface_Impl::resetJuneGroundTemperature() {
      OS_ASSERT(setString(openstudio::Site_GroundTemperature_BuildingSurfaceFields::JuneGroundTemperature, ""));
    }

    double SiteGroundTemperatureBuildingSurface_Impl::julyGroundTemperature() const {
      const auto value = getDouble(openstudio::Site_GroundTemperature_BuildingSurfaceFields::JulyGroundTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SiteGroundTemperatureBuildingSurface_Impl::isJulyGroundTemperatureDefaulted() const {
      return isEmpty(openstudio::Site_GroundTemperature_BuildingSurfaceFields::JulyGroundTemperature);
    }

    bool SiteGroundTemperatureBuildingSurface_Impl::setJulyGroundTemperature(double julyGroundTemperature) {
      return setDouble(openstudio::Site_GroundTemperature_BuildingSurfaceFields::JulyGroundTemperature, julyGroundTemperature);
    }

    void SiteGroundTemperatureBuildingSurface_Impl::resetJulyGroundTemperature() {
      OS_ASSERT(setString(openstudio::Site_GroundTemperature_BuildingSurfaceFields::JulyGroundTemperature, ""));
    }

    double SiteGroundTemperatureBuildingSurface_Impl::augustGroundTemperature() const {
      const auto value = getDouble(openstudio::Site_GroundTemperature_BuildingSurfaceFields::AugustGroundTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SiteGroundTemperatureBuildingSurface_Impl::isAugustGroundTemperatureDefaulted() const {
      return isEmpty(openstudio::Site_GroundTemperature_BuildingSurfaceFields::AugustGroundTemperature);
    }

    bool SiteGroundTemperatureBuildingSurface_Impl::setAugustGroundTemperature(double augustGroundTemperature) {
      return setDouble(openstudio::Site_GroundTemperature_BuildingSurfaceFields::AugustGroundTemperature, augustGroundTemperature);
    }

    void SiteGroundTemperatureBuildingSurface_Impl::resetAugustGroundTemperature() {
      OS_ASSERT(setString(openstudio::Site_GroundTemperature_BuildingSurfaceFields::AugustGroundTemperature, ""));
    }

    double SiteGroundTemperatureBuildingSurface_Impl::septemberGroundTemperature() const {
      const auto value = getDouble(openstudio::Site_GroundTemperature_BuildingSurfaceFields::SeptemberGroundTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SiteGroundTemperatureBuildingSurface_Impl::isSeptemberGroundTemperatureDefaulted() const {
      return isEmpty(openstudio::Site_GroundTemperature_BuildingSurfaceFields::SeptemberGroundTemperature);
    }

    bool SiteGroundTemperatureBuildingSurface_Impl::setSeptemberGroundTemperature(double septemberGroundTemperature) {
      return setDouble(openstudio::Site_GroundTemperature_BuildingSurfaceFields::SeptemberGroundTemperature, septemberGroundTemperature);
    }

    void SiteGroundTemperatureBuildingSurface_Impl::resetSeptemberGroundTemperature() {
      OS_ASSERT(setString(openstudio::Site_GroundTemperature_BuildingSurfaceFields::SeptemberGroundTemperature, ""));
    }

    double SiteGroundTemperatureBuildingSurface_Impl::octoberGroundTemperature() const {
      const auto value = getDouble(openstudio::Site_GroundTemperature_BuildingSurfaceFields::OctoberGroundTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SiteGroundTemperatureBuildingSurface_Impl::isOctoberGroundTemperatureDefaulted() const {
      return isEmpty(openstudio::Site_GroundTemperature_BuildingSurfaceFields::OctoberGroundTemperature);
    }

    bool SiteGroundTemperatureBuildingSurface_Impl::setOctoberGroundTemperature(double octoberGroundTemperature) {
      return setDouble(openstudio::Site_GroundTemperature_BuildingSurfaceFields::OctoberGroundTemperature, octoberGroundTemperature);
    }

    void SiteGroundTemperatureBuildingSurface_Impl::resetOctoberGroundTemperature() {
      OS_ASSERT(setString(openstudio::Site_GroundTemperature_BuildingSurfaceFields::OctoberGroundTemperature, ""));
    }

    double SiteGroundTemperatureBuildingSurface_Impl::novemberGroundTemperature() const {
      const auto value = getDouble(openstudio::Site_GroundTemperature_BuildingSurfaceFields::NovemberGroundTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SiteGroundTemperatureBuildingSurface_Impl::isNovemberGroundTemperatureDefaulted() const {
      return isEmpty(openstudio::Site_GroundTemperature_BuildingSurfaceFields::NovemberGroundTemperature);
    }

    bool SiteGroundTemperatureBuildingSurface_Impl::setNovemberGroundTemperature(double novemberGroundTemperature) {
      return setDouble(openstudio::Site_GroundTemperature_BuildingSurfaceFields::NovemberGroundTemperature, novemberGroundTemperature);
    }

    void SiteGroundTemperatureBuildingSurface_Impl::resetNovemberGroundTemperature() {
      OS_ASSERT(setString(openstudio::Site_GroundTemperature_BuildingSurfaceFields::NovemberGroundTemperature, ""));
    }

    double SiteGroundTemperatureBuildingSurface_Impl::decemberGroundTemperature() const {
      const auto value = getDouble(openstudio::Site_GroundTemperature_BuildingSurfaceFields::DecemberGroundTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SiteGroundTemperatureBuildingSurface_Impl::isDecemberGroundTemperatureDefaulted() const {
      return isEmpty(openstudio::Site_GroundTemperature_BuildingSurfaceFields::DecemberGroundTemperature);
    }

    bool SiteGroundTemperatureBuildingSurface_Impl::setDecemberGroundTemperature(double decemberGroundTemperature) {
      return setDouble(openstudio::Site_GroundTemperature_BuildingSurfaceFields::DecemberGroundTemperature, decemberGroundTemperature);
    }

    void SiteGroundTemperatureBuildingSurface_Impl::resetDecemberGroundTemperature() {
      OS_ASSERT(setString(openstudio::Site_GroundTemperature_BuildingSurfaceFields::DecemberGroundTemperature, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
