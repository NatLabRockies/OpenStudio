/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include "WindowMaterialGap.hpp"
#include "WindowMaterialGap_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/WindowMaterial_Gap_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  WindowMaterialGap::WindowMaterialGap(const Model& model) : ModelObject(WindowMaterialGap::iddObjectType(), model) {
    OS_ASSERT(setThickness(0.0127));
  }

  WindowMaterialGap::WindowMaterialGap(std::shared_ptr<detail::WindowMaterialGap_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType WindowMaterialGap::iddObjectType() {
    return IddObjectType::WindowMaterial_Gap;
  }

  double WindowMaterialGap::thickness() const {
    return getImpl<detail::WindowMaterialGap_Impl>()->thickness();
  }

  bool WindowMaterialGap::setThickness(double thickness) {
    return getImpl<detail::WindowMaterialGap_Impl>()->setThickness(thickness);
  }

  double WindowMaterialGap::pressure() const {
    return getImpl<detail::WindowMaterialGap_Impl>()->pressure();
  }

  bool WindowMaterialGap::isPressureDefaulted() const {
    return getImpl<detail::WindowMaterialGap_Impl>()->isPressureDefaulted();
  }

  bool WindowMaterialGap::setPressure(double pressure) {
    return getImpl<detail::WindowMaterialGap_Impl>()->setPressure(pressure);
  }

  void WindowMaterialGap::resetPressure() {
    getImpl<detail::WindowMaterialGap_Impl>()->resetPressure();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double WindowMaterialGap_Impl::thickness() const {
      const auto value = getDouble(openstudio::WindowMaterial_GapFields::Thickness, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowMaterialGap_Impl::setThickness(double thickness) {
      const bool result = setDouble(openstudio::WindowMaterial_GapFields::Thickness, thickness);
      OS_ASSERT(result);
      return result;
    }

    double WindowMaterialGap_Impl::pressure() const {
      const auto value = getDouble(openstudio::WindowMaterial_GapFields::Pressure, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowMaterialGap_Impl::isPressureDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_GapFields::Pressure);
    }

    bool WindowMaterialGap_Impl::setPressure(double pressure) {
      const bool result = setDouble(openstudio::WindowMaterial_GapFields::Pressure, pressure);
      OS_ASSERT(result);
      return result;
    }

    void WindowMaterialGap_Impl::resetPressure() {
      const bool result = setString(openstudio::WindowMaterial_GapFields::Pressure, "");
      OS_ASSERT(result);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
