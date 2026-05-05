/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SiteGroundTemperatureShallow.hpp"
#include "SiteGroundTemperatureShallow_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Site_GroundTemperature_Shallow_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  SiteGroundTemperatureShallow::SiteGroundTemperatureShallow(const Model& model)
    : ModelObject(SiteGroundTemperatureShallow::iddObjectType(), model) {}

  SiteGroundTemperatureShallow::SiteGroundTemperatureShallow(std::shared_ptr<detail::SiteGroundTemperatureShallow_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType SiteGroundTemperatureShallow::iddObjectType() {
    return IddObjectType::Site_GroundTemperature_Shallow;
  }

  double SiteGroundTemperatureShallow::januarySurfaceGroundTemperature() const {
    return getImpl<detail::SiteGroundTemperatureShallow_Impl>()->januarySurfaceGroundTemperature();
  }

  bool SiteGroundTemperatureShallow::isJanuarySurfaceGroundTemperatureDefaulted() const {
    return getImpl<detail::SiteGroundTemperatureShallow_Impl>()->isJanuarySurfaceGroundTemperatureDefaulted();
  }

  bool SiteGroundTemperatureShallow::setJanuarySurfaceGroundTemperature(double januarySurfaceGroundTemperature) {
    return getImpl<detail::SiteGroundTemperatureShallow_Impl>()->setJanuarySurfaceGroundTemperature(januarySurfaceGroundTemperature);
  }

  void SiteGroundTemperatureShallow::resetJanuarySurfaceGroundTemperature() {
    getImpl<detail::SiteGroundTemperatureShallow_Impl>()->resetJanuarySurfaceGroundTemperature();
  }

  namespace detail {

    // Schema alignment implementation notes:
    // - Month accessors map one-to-one to Site_GroundTemperature_ShallowFields enum values.
    // - Getter strictness + setter bool-return-with-assert follow generator parity for required scalar APIs.

    double SiteGroundTemperatureShallow_Impl::januarySurfaceGroundTemperature() const {
      const auto value = getDouble(openstudio::Site_GroundTemperature_ShallowFields::JanuarySurfaceGroundTemperature, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool SiteGroundTemperatureShallow_Impl::isJanuarySurfaceGroundTemperatureDefaulted() const {
      return isEmpty(openstudio::Site_GroundTemperature_ShallowFields::JanuarySurfaceGroundTemperature);
    }

    bool SiteGroundTemperatureShallow_Impl::setJanuarySurfaceGroundTemperature(double januarySurfaceGroundTemperature) {
      const bool result =
        setDouble(openstudio::Site_GroundTemperature_ShallowFields::JanuarySurfaceGroundTemperature, januarySurfaceGroundTemperature);
      OS_ASSERT(result);
      return result;
    }

    void SiteGroundTemperatureShallow_Impl::resetJanuarySurfaceGroundTemperature() {
      const bool result = setString(openstudio::Site_GroundTemperature_ShallowFields::JanuarySurfaceGroundTemperature, "");
      OS_ASSERT(result);
    }

  }  // namespace detail

  double SiteGroundTemperatureShallow::februarySurfaceGroundTemperature() const {
    return getImpl<detail::SiteGroundTemperatureShallow_Impl>()->februarySurfaceGroundTemperature();
  }

  bool SiteGroundTemperatureShallow::isFebruarySurfaceGroundTemperatureDefaulted() const {
    return getImpl<detail::SiteGroundTemperatureShallow_Impl>()->isFebruarySurfaceGroundTemperatureDefaulted();
  }

  bool SiteGroundTemperatureShallow::setFebruarySurfaceGroundTemperature(double februarySurfaceGroundTemperature) {
    return getImpl<detail::SiteGroundTemperatureShallow_Impl>()->setFebruarySurfaceGroundTemperature(februarySurfaceGroundTemperature);
  }

  void SiteGroundTemperatureShallow::resetFebruarySurfaceGroundTemperature() {
    getImpl<detail::SiteGroundTemperatureShallow_Impl>()->resetFebruarySurfaceGroundTemperature();
  }

  namespace detail {

    double SiteGroundTemperatureShallow_Impl::februarySurfaceGroundTemperature() const {
      const auto value = getDouble(openstudio::Site_GroundTemperature_ShallowFields::FebruarySurfaceGroundTemperature, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool SiteGroundTemperatureShallow_Impl::isFebruarySurfaceGroundTemperatureDefaulted() const {
      return isEmpty(openstudio::Site_GroundTemperature_ShallowFields::FebruarySurfaceGroundTemperature);
    }

    bool SiteGroundTemperatureShallow_Impl::setFebruarySurfaceGroundTemperature(double februarySurfaceGroundTemperature) {
      const bool result =
        setDouble(openstudio::Site_GroundTemperature_ShallowFields::FebruarySurfaceGroundTemperature, februarySurfaceGroundTemperature);
      OS_ASSERT(result);
      return result;
    }

    void SiteGroundTemperatureShallow_Impl::resetFebruarySurfaceGroundTemperature() {
      const bool result = setString(openstudio::Site_GroundTemperature_ShallowFields::FebruarySurfaceGroundTemperature, "");
      OS_ASSERT(result);
    }

  }  // namespace detail

  double SiteGroundTemperatureShallow::marchSurfaceGroundTemperature() const {
    return getImpl<detail::SiteGroundTemperatureShallow_Impl>()->marchSurfaceGroundTemperature();
  }

  bool SiteGroundTemperatureShallow::isMarchSurfaceGroundTemperatureDefaulted() const {
    return getImpl<detail::SiteGroundTemperatureShallow_Impl>()->isMarchSurfaceGroundTemperatureDefaulted();
  }

  bool SiteGroundTemperatureShallow::setMarchSurfaceGroundTemperature(double marchSurfaceGroundTemperature) {
    return getImpl<detail::SiteGroundTemperatureShallow_Impl>()->setMarchSurfaceGroundTemperature(marchSurfaceGroundTemperature);
  }

  void SiteGroundTemperatureShallow::resetMarchSurfaceGroundTemperature() {
    getImpl<detail::SiteGroundTemperatureShallow_Impl>()->resetMarchSurfaceGroundTemperature();
  }

  namespace detail {

    double SiteGroundTemperatureShallow_Impl::marchSurfaceGroundTemperature() const {
      const auto value = getDouble(openstudio::Site_GroundTemperature_ShallowFields::MarchSurfaceGroundTemperature, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool SiteGroundTemperatureShallow_Impl::isMarchSurfaceGroundTemperatureDefaulted() const {
      return isEmpty(openstudio::Site_GroundTemperature_ShallowFields::MarchSurfaceGroundTemperature);
    }

    bool SiteGroundTemperatureShallow_Impl::setMarchSurfaceGroundTemperature(double marchSurfaceGroundTemperature) {
      const bool result = setDouble(openstudio::Site_GroundTemperature_ShallowFields::MarchSurfaceGroundTemperature, marchSurfaceGroundTemperature);
      OS_ASSERT(result);
      return result;
    }

    void SiteGroundTemperatureShallow_Impl::resetMarchSurfaceGroundTemperature() {
      const bool result = setString(openstudio::Site_GroundTemperature_ShallowFields::MarchSurfaceGroundTemperature, "");
      OS_ASSERT(result);
    }

  }  // namespace detail

  double SiteGroundTemperatureShallow::aprilSurfaceGroundTemperature() const {
    return getImpl<detail::SiteGroundTemperatureShallow_Impl>()->aprilSurfaceGroundTemperature();
  }

  bool SiteGroundTemperatureShallow::isAprilSurfaceGroundTemperatureDefaulted() const {
    return getImpl<detail::SiteGroundTemperatureShallow_Impl>()->isAprilSurfaceGroundTemperatureDefaulted();
  }

  bool SiteGroundTemperatureShallow::setAprilSurfaceGroundTemperature(double aprilSurfaceGroundTemperature) {
    return getImpl<detail::SiteGroundTemperatureShallow_Impl>()->setAprilSurfaceGroundTemperature(aprilSurfaceGroundTemperature);
  }

  void SiteGroundTemperatureShallow::resetAprilSurfaceGroundTemperature() {
    getImpl<detail::SiteGroundTemperatureShallow_Impl>()->resetAprilSurfaceGroundTemperature();
  }

  namespace detail {

    double SiteGroundTemperatureShallow_Impl::aprilSurfaceGroundTemperature() const {
      const auto value = getDouble(openstudio::Site_GroundTemperature_ShallowFields::AprilSurfaceGroundTemperature, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool SiteGroundTemperatureShallow_Impl::isAprilSurfaceGroundTemperatureDefaulted() const {
      return isEmpty(openstudio::Site_GroundTemperature_ShallowFields::AprilSurfaceGroundTemperature);
    }

    bool SiteGroundTemperatureShallow_Impl::setAprilSurfaceGroundTemperature(double aprilSurfaceGroundTemperature) {
      const bool result = setDouble(openstudio::Site_GroundTemperature_ShallowFields::AprilSurfaceGroundTemperature, aprilSurfaceGroundTemperature);
      OS_ASSERT(result);
      return result;
    }

    void SiteGroundTemperatureShallow_Impl::resetAprilSurfaceGroundTemperature() {
      const bool result = setString(openstudio::Site_GroundTemperature_ShallowFields::AprilSurfaceGroundTemperature, "");
      OS_ASSERT(result);
    }

  }  // namespace detail

  double SiteGroundTemperatureShallow::maySurfaceGroundTemperature() const {
    return getImpl<detail::SiteGroundTemperatureShallow_Impl>()->maySurfaceGroundTemperature();
  }

  bool SiteGroundTemperatureShallow::isMaySurfaceGroundTemperatureDefaulted() const {
    return getImpl<detail::SiteGroundTemperatureShallow_Impl>()->isMaySurfaceGroundTemperatureDefaulted();
  }

  bool SiteGroundTemperatureShallow::setMaySurfaceGroundTemperature(double maySurfaceGroundTemperature) {
    return getImpl<detail::SiteGroundTemperatureShallow_Impl>()->setMaySurfaceGroundTemperature(maySurfaceGroundTemperature);
  }

  void SiteGroundTemperatureShallow::resetMaySurfaceGroundTemperature() {
    getImpl<detail::SiteGroundTemperatureShallow_Impl>()->resetMaySurfaceGroundTemperature();
  }

  namespace detail {

    double SiteGroundTemperatureShallow_Impl::maySurfaceGroundTemperature() const {
      const auto value = getDouble(openstudio::Site_GroundTemperature_ShallowFields::MaySurfaceGroundTemperature, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool SiteGroundTemperatureShallow_Impl::isMaySurfaceGroundTemperatureDefaulted() const {
      return isEmpty(openstudio::Site_GroundTemperature_ShallowFields::MaySurfaceGroundTemperature);
    }

    bool SiteGroundTemperatureShallow_Impl::setMaySurfaceGroundTemperature(double maySurfaceGroundTemperature) {
      const bool result = setDouble(openstudio::Site_GroundTemperature_ShallowFields::MaySurfaceGroundTemperature, maySurfaceGroundTemperature);
      OS_ASSERT(result);
      return result;
    }

    void SiteGroundTemperatureShallow_Impl::resetMaySurfaceGroundTemperature() {
      const bool result = setString(openstudio::Site_GroundTemperature_ShallowFields::MaySurfaceGroundTemperature, "");
      OS_ASSERT(result);
    }

  }  // namespace detail

  double SiteGroundTemperatureShallow::juneSurfaceGroundTemperature() const {
    return getImpl<detail::SiteGroundTemperatureShallow_Impl>()->juneSurfaceGroundTemperature();
  }

  bool SiteGroundTemperatureShallow::isJuneSurfaceGroundTemperatureDefaulted() const {
    return getImpl<detail::SiteGroundTemperatureShallow_Impl>()->isJuneSurfaceGroundTemperatureDefaulted();
  }

  bool SiteGroundTemperatureShallow::setJuneSurfaceGroundTemperature(double juneSurfaceGroundTemperature) {
    return getImpl<detail::SiteGroundTemperatureShallow_Impl>()->setJuneSurfaceGroundTemperature(juneSurfaceGroundTemperature);
  }

  void SiteGroundTemperatureShallow::resetJuneSurfaceGroundTemperature() {
    getImpl<detail::SiteGroundTemperatureShallow_Impl>()->resetJuneSurfaceGroundTemperature();
  }

  namespace detail {

    double SiteGroundTemperatureShallow_Impl::juneSurfaceGroundTemperature() const {
      const auto value = getDouble(openstudio::Site_GroundTemperature_ShallowFields::JuneSurfaceGroundTemperature, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool SiteGroundTemperatureShallow_Impl::isJuneSurfaceGroundTemperatureDefaulted() const {
      return isEmpty(openstudio::Site_GroundTemperature_ShallowFields::JuneSurfaceGroundTemperature);
    }

    bool SiteGroundTemperatureShallow_Impl::setJuneSurfaceGroundTemperature(double juneSurfaceGroundTemperature) {
      const bool result = setDouble(openstudio::Site_GroundTemperature_ShallowFields::JuneSurfaceGroundTemperature, juneSurfaceGroundTemperature);
      OS_ASSERT(result);
      return result;
    }

    void SiteGroundTemperatureShallow_Impl::resetJuneSurfaceGroundTemperature() {
      const bool result = setString(openstudio::Site_GroundTemperature_ShallowFields::JuneSurfaceGroundTemperature, "");
      OS_ASSERT(result);
    }

  }  // namespace detail

  double SiteGroundTemperatureShallow::julySurfaceGroundTemperature() const {
    return getImpl<detail::SiteGroundTemperatureShallow_Impl>()->julySurfaceGroundTemperature();
  }

  bool SiteGroundTemperatureShallow::isJulySurfaceGroundTemperatureDefaulted() const {
    return getImpl<detail::SiteGroundTemperatureShallow_Impl>()->isJulySurfaceGroundTemperatureDefaulted();
  }

  bool SiteGroundTemperatureShallow::setJulySurfaceGroundTemperature(double julySurfaceGroundTemperature) {
    return getImpl<detail::SiteGroundTemperatureShallow_Impl>()->setJulySurfaceGroundTemperature(julySurfaceGroundTemperature);
  }

  void SiteGroundTemperatureShallow::resetJulySurfaceGroundTemperature() {
    getImpl<detail::SiteGroundTemperatureShallow_Impl>()->resetJulySurfaceGroundTemperature();
  }

  namespace detail {

    double SiteGroundTemperatureShallow_Impl::julySurfaceGroundTemperature() const {
      const auto value = getDouble(openstudio::Site_GroundTemperature_ShallowFields::JulySurfaceGroundTemperature, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool SiteGroundTemperatureShallow_Impl::isJulySurfaceGroundTemperatureDefaulted() const {
      return isEmpty(openstudio::Site_GroundTemperature_ShallowFields::JulySurfaceGroundTemperature);
    }

    bool SiteGroundTemperatureShallow_Impl::setJulySurfaceGroundTemperature(double julySurfaceGroundTemperature) {
      const bool result = setDouble(openstudio::Site_GroundTemperature_ShallowFields::JulySurfaceGroundTemperature, julySurfaceGroundTemperature);
      OS_ASSERT(result);
      return result;
    }

    void SiteGroundTemperatureShallow_Impl::resetJulySurfaceGroundTemperature() {
      const bool result = setString(openstudio::Site_GroundTemperature_ShallowFields::JulySurfaceGroundTemperature, "");
      OS_ASSERT(result);
    }

  }  // namespace detail

  double SiteGroundTemperatureShallow::augustSurfaceGroundTemperature() const {
    return getImpl<detail::SiteGroundTemperatureShallow_Impl>()->augustSurfaceGroundTemperature();
  }

  bool SiteGroundTemperatureShallow::isAugustSurfaceGroundTemperatureDefaulted() const {
    return getImpl<detail::SiteGroundTemperatureShallow_Impl>()->isAugustSurfaceGroundTemperatureDefaulted();
  }

  bool SiteGroundTemperatureShallow::setAugustSurfaceGroundTemperature(double augustSurfaceGroundTemperature) {
    return getImpl<detail::SiteGroundTemperatureShallow_Impl>()->setAugustSurfaceGroundTemperature(augustSurfaceGroundTemperature);
  }

  void SiteGroundTemperatureShallow::resetAugustSurfaceGroundTemperature() {
    getImpl<detail::SiteGroundTemperatureShallow_Impl>()->resetAugustSurfaceGroundTemperature();
  }

  namespace detail {

    double SiteGroundTemperatureShallow_Impl::augustSurfaceGroundTemperature() const {
      const auto value = getDouble(openstudio::Site_GroundTemperature_ShallowFields::AugustSurfaceGroundTemperature, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool SiteGroundTemperatureShallow_Impl::isAugustSurfaceGroundTemperatureDefaulted() const {
      return isEmpty(openstudio::Site_GroundTemperature_ShallowFields::AugustSurfaceGroundTemperature);
    }

    bool SiteGroundTemperatureShallow_Impl::setAugustSurfaceGroundTemperature(double augustSurfaceGroundTemperature) {
      const bool result = setDouble(openstudio::Site_GroundTemperature_ShallowFields::AugustSurfaceGroundTemperature, augustSurfaceGroundTemperature);
      OS_ASSERT(result);
      return result;
    }

    void SiteGroundTemperatureShallow_Impl::resetAugustSurfaceGroundTemperature() {
      const bool result = setString(openstudio::Site_GroundTemperature_ShallowFields::AugustSurfaceGroundTemperature, "");
      OS_ASSERT(result);
    }

  }  // namespace detail

  double SiteGroundTemperatureShallow::septemberSurfaceGroundTemperature() const {
    return getImpl<detail::SiteGroundTemperatureShallow_Impl>()->septemberSurfaceGroundTemperature();
  }

  bool SiteGroundTemperatureShallow::isSeptemberSurfaceGroundTemperatureDefaulted() const {
    return getImpl<detail::SiteGroundTemperatureShallow_Impl>()->isSeptemberSurfaceGroundTemperatureDefaulted();
  }

  bool SiteGroundTemperatureShallow::setSeptemberSurfaceGroundTemperature(double septemberSurfaceGroundTemperature) {
    return getImpl<detail::SiteGroundTemperatureShallow_Impl>()->setSeptemberSurfaceGroundTemperature(septemberSurfaceGroundTemperature);
  }

  void SiteGroundTemperatureShallow::resetSeptemberSurfaceGroundTemperature() {
    getImpl<detail::SiteGroundTemperatureShallow_Impl>()->resetSeptemberSurfaceGroundTemperature();
  }

  namespace detail {

    double SiteGroundTemperatureShallow_Impl::septemberSurfaceGroundTemperature() const {
      const auto value = getDouble(openstudio::Site_GroundTemperature_ShallowFields::SeptemberSurfaceGroundTemperature, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool SiteGroundTemperatureShallow_Impl::isSeptemberSurfaceGroundTemperatureDefaulted() const {
      return isEmpty(openstudio::Site_GroundTemperature_ShallowFields::SeptemberSurfaceGroundTemperature);
    }

    bool SiteGroundTemperatureShallow_Impl::setSeptemberSurfaceGroundTemperature(double septemberSurfaceGroundTemperature) {
      const bool result =
        setDouble(openstudio::Site_GroundTemperature_ShallowFields::SeptemberSurfaceGroundTemperature, septemberSurfaceGroundTemperature);
      OS_ASSERT(result);
      return result;
    }

    void SiteGroundTemperatureShallow_Impl::resetSeptemberSurfaceGroundTemperature() {
      const bool result = setString(openstudio::Site_GroundTemperature_ShallowFields::SeptemberSurfaceGroundTemperature, "");
      OS_ASSERT(result);
    }

  }  // namespace detail

  double SiteGroundTemperatureShallow::octoberSurfaceGroundTemperature() const {
    return getImpl<detail::SiteGroundTemperatureShallow_Impl>()->octoberSurfaceGroundTemperature();
  }

  bool SiteGroundTemperatureShallow::isOctoberSurfaceGroundTemperatureDefaulted() const {
    return getImpl<detail::SiteGroundTemperatureShallow_Impl>()->isOctoberSurfaceGroundTemperatureDefaulted();
  }

  bool SiteGroundTemperatureShallow::setOctoberSurfaceGroundTemperature(double octoberSurfaceGroundTemperature) {
    return getImpl<detail::SiteGroundTemperatureShallow_Impl>()->setOctoberSurfaceGroundTemperature(octoberSurfaceGroundTemperature);
  }

  void SiteGroundTemperatureShallow::resetOctoberSurfaceGroundTemperature() {
    getImpl<detail::SiteGroundTemperatureShallow_Impl>()->resetOctoberSurfaceGroundTemperature();
  }

  namespace detail {

    double SiteGroundTemperatureShallow_Impl::octoberSurfaceGroundTemperature() const {
      const auto value = getDouble(openstudio::Site_GroundTemperature_ShallowFields::OctoberSurfaceGroundTemperature, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool SiteGroundTemperatureShallow_Impl::isOctoberSurfaceGroundTemperatureDefaulted() const {
      return isEmpty(openstudio::Site_GroundTemperature_ShallowFields::OctoberSurfaceGroundTemperature);
    }

    bool SiteGroundTemperatureShallow_Impl::setOctoberSurfaceGroundTemperature(double octoberSurfaceGroundTemperature) {
      const bool result =
        setDouble(openstudio::Site_GroundTemperature_ShallowFields::OctoberSurfaceGroundTemperature, octoberSurfaceGroundTemperature);
      OS_ASSERT(result);
      return result;
    }

    void SiteGroundTemperatureShallow_Impl::resetOctoberSurfaceGroundTemperature() {
      const bool result = setString(openstudio::Site_GroundTemperature_ShallowFields::OctoberSurfaceGroundTemperature, "");
      OS_ASSERT(result);
    }

  }  // namespace detail

  double SiteGroundTemperatureShallow::novemberSurfaceGroundTemperature() const {
    return getImpl<detail::SiteGroundTemperatureShallow_Impl>()->novemberSurfaceGroundTemperature();
  }

  bool SiteGroundTemperatureShallow::isNovemberSurfaceGroundTemperatureDefaulted() const {
    return getImpl<detail::SiteGroundTemperatureShallow_Impl>()->isNovemberSurfaceGroundTemperatureDefaulted();
  }

  bool SiteGroundTemperatureShallow::setNovemberSurfaceGroundTemperature(double novemberSurfaceGroundTemperature) {
    return getImpl<detail::SiteGroundTemperatureShallow_Impl>()->setNovemberSurfaceGroundTemperature(novemberSurfaceGroundTemperature);
  }

  void SiteGroundTemperatureShallow::resetNovemberSurfaceGroundTemperature() {
    getImpl<detail::SiteGroundTemperatureShallow_Impl>()->resetNovemberSurfaceGroundTemperature();
  }

  namespace detail {

    double SiteGroundTemperatureShallow_Impl::novemberSurfaceGroundTemperature() const {
      const auto value = getDouble(openstudio::Site_GroundTemperature_ShallowFields::NovemberSurfaceGroundTemperature, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool SiteGroundTemperatureShallow_Impl::isNovemberSurfaceGroundTemperatureDefaulted() const {
      return isEmpty(openstudio::Site_GroundTemperature_ShallowFields::NovemberSurfaceGroundTemperature);
    }

    bool SiteGroundTemperatureShallow_Impl::setNovemberSurfaceGroundTemperature(double novemberSurfaceGroundTemperature) {
      const bool result =
        setDouble(openstudio::Site_GroundTemperature_ShallowFields::NovemberSurfaceGroundTemperature, novemberSurfaceGroundTemperature);
      OS_ASSERT(result);
      return result;
    }

    void SiteGroundTemperatureShallow_Impl::resetNovemberSurfaceGroundTemperature() {
      const bool result = setString(openstudio::Site_GroundTemperature_ShallowFields::NovemberSurfaceGroundTemperature, "");
      OS_ASSERT(result);
    }

  }  // namespace detail

  double SiteGroundTemperatureShallow::decemberSurfaceGroundTemperature() const {
    return getImpl<detail::SiteGroundTemperatureShallow_Impl>()->decemberSurfaceGroundTemperature();
  }

  bool SiteGroundTemperatureShallow::isDecemberSurfaceGroundTemperatureDefaulted() const {
    return getImpl<detail::SiteGroundTemperatureShallow_Impl>()->isDecemberSurfaceGroundTemperatureDefaulted();
  }

  bool SiteGroundTemperatureShallow::setDecemberSurfaceGroundTemperature(double decemberSurfaceGroundTemperature) {
    return getImpl<detail::SiteGroundTemperatureShallow_Impl>()->setDecemberSurfaceGroundTemperature(decemberSurfaceGroundTemperature);
  }

  void SiteGroundTemperatureShallow::resetDecemberSurfaceGroundTemperature() {
    getImpl<detail::SiteGroundTemperatureShallow_Impl>()->resetDecemberSurfaceGroundTemperature();
  }

  namespace detail {

    double SiteGroundTemperatureShallow_Impl::decemberSurfaceGroundTemperature() const {
      const auto value = getDouble(openstudio::Site_GroundTemperature_ShallowFields::DecemberSurfaceGroundTemperature, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool SiteGroundTemperatureShallow_Impl::isDecemberSurfaceGroundTemperatureDefaulted() const {
      return isEmpty(openstudio::Site_GroundTemperature_ShallowFields::DecemberSurfaceGroundTemperature);
    }

    bool SiteGroundTemperatureShallow_Impl::setDecemberSurfaceGroundTemperature(double decemberSurfaceGroundTemperature) {
      const bool result =
        setDouble(openstudio::Site_GroundTemperature_ShallowFields::DecemberSurfaceGroundTemperature, decemberSurfaceGroundTemperature);
      OS_ASSERT(result);
      return result;
    }

    void SiteGroundTemperatureShallow_Impl::resetDecemberSurfaceGroundTemperature() {
      const bool result = setString(openstudio::Site_GroundTemperature_ShallowFields::DecemberSurfaceGroundTemperature, "");
      OS_ASSERT(result);
    }

  }  // namespace detail

}  // namespace epmodel
}  // namespace openstudio
