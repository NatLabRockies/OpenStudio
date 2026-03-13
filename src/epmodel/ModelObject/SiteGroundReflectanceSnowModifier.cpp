/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include "SiteGroundReflectanceSnowModifier.hpp"
#include "SiteGroundReflectanceSnowModifier_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Site_GroundReflectance_SnowModifier_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  SiteGroundReflectanceSnowModifier::SiteGroundReflectanceSnowModifier(const Model& model)
    : ModelObject(SiteGroundReflectanceSnowModifier::iddObjectType(), model) {}

  SiteGroundReflectanceSnowModifier::SiteGroundReflectanceSnowModifier(std::shared_ptr<detail::SiteGroundReflectanceSnowModifier_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType SiteGroundReflectanceSnowModifier::iddObjectType() {
    return IddObjectType::Site_GroundReflectance_SnowModifier;
  }

  double SiteGroundReflectanceSnowModifier::groundReflectedSolarModifier() const {
    return getImpl<detail::SiteGroundReflectanceSnowModifier_Impl>()->groundReflectedSolarModifier();
  }

  bool SiteGroundReflectanceSnowModifier::isGroundReflectedSolarModifierDefaulted() const {
    return getImpl<detail::SiteGroundReflectanceSnowModifier_Impl>()->isGroundReflectedSolarModifierDefaulted();
  }

  bool SiteGroundReflectanceSnowModifier::setGroundReflectedSolarModifier(double groundReflectedSolarModifier) {
    return getImpl<detail::SiteGroundReflectanceSnowModifier_Impl>()->setGroundReflectedSolarModifier(groundReflectedSolarModifier);
  }

  void SiteGroundReflectanceSnowModifier::resetGroundReflectedSolarModifier() {
    getImpl<detail::SiteGroundReflectanceSnowModifier_Impl>()->resetGroundReflectedSolarModifier();
  }

  double SiteGroundReflectanceSnowModifier::daylightingGroundReflectedSolarModifier() const {
    return getImpl<detail::SiteGroundReflectanceSnowModifier_Impl>()->daylightingGroundReflectedSolarModifier();
  }

  bool SiteGroundReflectanceSnowModifier::isDaylightingGroundReflectedSolarModifierDefaulted() const {
    return getImpl<detail::SiteGroundReflectanceSnowModifier_Impl>()->isDaylightingGroundReflectedSolarModifierDefaulted();
  }

  bool SiteGroundReflectanceSnowModifier::setDaylightingGroundReflectedSolarModifier(double daylightingGroundReflectedSolarModifier) {
    return getImpl<detail::SiteGroundReflectanceSnowModifier_Impl>()->setDaylightingGroundReflectedSolarModifier(
      daylightingGroundReflectedSolarModifier);
  }

  void SiteGroundReflectanceSnowModifier::resetDaylightingGroundReflectedSolarModifier() {
    getImpl<detail::SiteGroundReflectanceSnowModifier_Impl>()->resetDaylightingGroundReflectedSolarModifier();
  }

  namespace detail {

    double SiteGroundReflectanceSnowModifier_Impl::groundReflectedSolarModifier() const {
      const auto value = getDouble(openstudio::Site_GroundReflectance_SnowModifierFields::GroundReflectedSolarModifier, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SiteGroundReflectanceSnowModifier_Impl::isGroundReflectedSolarModifierDefaulted() const {
      return isEmpty(openstudio::Site_GroundReflectance_SnowModifierFields::GroundReflectedSolarModifier);
    }

    bool SiteGroundReflectanceSnowModifier_Impl::setGroundReflectedSolarModifier(double groundReflectedSolarModifier) {
      return setDouble(openstudio::Site_GroundReflectance_SnowModifierFields::GroundReflectedSolarModifier, groundReflectedSolarModifier);
    }

    void SiteGroundReflectanceSnowModifier_Impl::resetGroundReflectedSolarModifier() {
      OS_ASSERT(setString(openstudio::Site_GroundReflectance_SnowModifierFields::GroundReflectedSolarModifier, ""));
    }

    double SiteGroundReflectanceSnowModifier_Impl::daylightingGroundReflectedSolarModifier() const {
      const auto value = getDouble(openstudio::Site_GroundReflectance_SnowModifierFields::DaylightingGroundReflectedSolarModifier, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SiteGroundReflectanceSnowModifier_Impl::isDaylightingGroundReflectedSolarModifierDefaulted() const {
      return isEmpty(openstudio::Site_GroundReflectance_SnowModifierFields::DaylightingGroundReflectedSolarModifier);
    }

    bool SiteGroundReflectanceSnowModifier_Impl::setDaylightingGroundReflectedSolarModifier(double daylightingGroundReflectedSolarModifier) {
      return setDouble(openstudio::Site_GroundReflectance_SnowModifierFields::DaylightingGroundReflectedSolarModifier,
                       daylightingGroundReflectedSolarModifier);
    }

    void SiteGroundReflectanceSnowModifier_Impl::resetDaylightingGroundReflectedSolarModifier() {
      OS_ASSERT(setString(openstudio::Site_GroundReflectance_SnowModifierFields::DaylightingGroundReflectedSolarModifier, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
