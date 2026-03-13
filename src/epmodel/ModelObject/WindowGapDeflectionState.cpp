/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "WindowGapDeflectionState.hpp"
#include "WindowGapDeflectionState_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/WindowGap_DeflectionState_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  WindowGapDeflectionState::WindowGapDeflectionState(const Model& model) : ModelObject(WindowGapDeflectionState::iddObjectType(), model) {
    // Keep default scalar values populated for strict getters.
    OS_ASSERT(setDeflectedThickness(0.0));
    OS_ASSERT(setInitialTemperature(25.0));
    OS_ASSERT(setInitialPressure(101325.0));
  }

  WindowGapDeflectionState::WindowGapDeflectionState(std::shared_ptr<detail::WindowGapDeflectionState_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType WindowGapDeflectionState::iddObjectType() {
    return IddObjectType::WindowGap_DeflectionState;
  }

  double WindowGapDeflectionState::deflectedThickness() const {
    return getImpl<detail::WindowGapDeflectionState_Impl>()->deflectedThickness();
  }

  bool WindowGapDeflectionState::setDeflectedThickness(double deflectedThickness) {
    return getImpl<detail::WindowGapDeflectionState_Impl>()->setDeflectedThickness(deflectedThickness);
  }

  namespace detail {

    double WindowGapDeflectionState_Impl::deflectedThickness() const {
      const auto value = getDouble(openstudio::WindowGap_DeflectionStateFields::DeflectedThickness, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowGapDeflectionState_Impl::setDeflectedThickness(double deflectedThickness) {
      return setDouble(openstudio::WindowGap_DeflectionStateFields::DeflectedThickness, deflectedThickness);
    }

  }  // namespace detail

  double WindowGapDeflectionState::initialTemperature() const {
    return getImpl<detail::WindowGapDeflectionState_Impl>()->initialTemperature();
  }

  bool WindowGapDeflectionState::setInitialTemperature(double initialTemperature) {
    return getImpl<detail::WindowGapDeflectionState_Impl>()->setInitialTemperature(initialTemperature);
  }

  namespace detail {

    double WindowGapDeflectionState_Impl::initialTemperature() const {
      const auto value = getDouble(openstudio::WindowGap_DeflectionStateFields::InitialTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowGapDeflectionState_Impl::setInitialTemperature(double initialTemperature) {
      return setDouble(openstudio::WindowGap_DeflectionStateFields::InitialTemperature, initialTemperature);
    }

  }  // namespace detail

  double WindowGapDeflectionState::initialPressure() const {
    return getImpl<detail::WindowGapDeflectionState_Impl>()->initialPressure();
  }

  bool WindowGapDeflectionState::setInitialPressure(double initialPressure) {
    return getImpl<detail::WindowGapDeflectionState_Impl>()->setInitialPressure(initialPressure);
  }

  namespace detail {

    double WindowGapDeflectionState_Impl::initialPressure() const {
      const auto value = getDouble(openstudio::WindowGap_DeflectionStateFields::InitialPressure, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowGapDeflectionState_Impl::setInitialPressure(double initialPressure) {
      return setDouble(openstudio::WindowGap_DeflectionStateFields::InitialPressure, initialPressure);
    }

  }  // namespace detail

}  // namespace epmodel
}  // namespace openstudio
