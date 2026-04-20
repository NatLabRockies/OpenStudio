/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "WindowGapSupportPillar.hpp"
#include "WindowGapSupportPillar_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/WindowGap_SupportPillar_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  WindowGapSupportPillar::WindowGapSupportPillar(const Model& model) : ModelObject(WindowGapSupportPillar::iddObjectType(), model) {}

  WindowGapSupportPillar::WindowGapSupportPillar(std::shared_ptr<detail::WindowGapSupportPillar_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType WindowGapSupportPillar::iddObjectType() {
    return IddObjectType::WindowGap_SupportPillar;
  }

  double WindowGapSupportPillar::spacing() const {
    return getImpl<detail::WindowGapSupportPillar_Impl>()->spacing();
  }

  bool WindowGapSupportPillar::isSpacingDefaulted() const {
    return getImpl<detail::WindowGapSupportPillar_Impl>()->isSpacingDefaulted();
  }

  bool WindowGapSupportPillar::setSpacing(double spacing) {
    return getImpl<detail::WindowGapSupportPillar_Impl>()->setSpacing(spacing);
  }

  void WindowGapSupportPillar::resetSpacing() {
    getImpl<detail::WindowGapSupportPillar_Impl>()->resetSpacing();
  }

  double WindowGapSupportPillar::radius() const {
    return getImpl<detail::WindowGapSupportPillar_Impl>()->radius();
  }

  bool WindowGapSupportPillar::isRadiusDefaulted() const {
    return getImpl<detail::WindowGapSupportPillar_Impl>()->isRadiusDefaulted();
  }

  bool WindowGapSupportPillar::setRadius(double radius) {
    return getImpl<detail::WindowGapSupportPillar_Impl>()->setRadius(radius);
  }

  void WindowGapSupportPillar::resetRadius() {
    getImpl<detail::WindowGapSupportPillar_Impl>()->resetRadius();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double WindowGapSupportPillar_Impl::spacing() const {
      const auto value = getDouble(openstudio::WindowGap_SupportPillarFields::Spacing, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowGapSupportPillar_Impl::isSpacingDefaulted() const {
      return isEmpty(openstudio::WindowGap_SupportPillarFields::Spacing);
    }

    bool WindowGapSupportPillar_Impl::setSpacing(double spacing) {
      const bool result = setDouble(openstudio::WindowGap_SupportPillarFields::Spacing, spacing);
      OS_ASSERT(result);
      return result;
    }

    void WindowGapSupportPillar_Impl::resetSpacing() {
      OS_ASSERT(setString(openstudio::WindowGap_SupportPillarFields::Spacing, ""));
    }

    double WindowGapSupportPillar_Impl::radius() const {
      const auto value = getDouble(openstudio::WindowGap_SupportPillarFields::Radius, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowGapSupportPillar_Impl::isRadiusDefaulted() const {
      return isEmpty(openstudio::WindowGap_SupportPillarFields::Radius);
    }

    bool WindowGapSupportPillar_Impl::setRadius(double radius) {
      const bool result = setDouble(openstudio::WindowGap_SupportPillarFields::Radius, radius);
      OS_ASSERT(result);
      return result;
    }

    void WindowGapSupportPillar_Impl::resetRadius() {
      OS_ASSERT(setString(openstudio::WindowGap_SupportPillarFields::Radius, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
