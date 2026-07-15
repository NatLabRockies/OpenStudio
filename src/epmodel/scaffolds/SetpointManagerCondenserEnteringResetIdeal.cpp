/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SetpointManagerCondenserEnteringResetIdeal.hpp"
#include "SetpointManagerCondenserEnteringResetIdeal_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/SetpointManager_CondenserEnteringReset_Ideal_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  SetpointManagerCondenserEnteringResetIdeal::SetpointManagerCondenserEnteringResetIdeal(const Model& model)
    : ModelObject(SetpointManagerCondenserEnteringResetIdeal::iddObjectType(), model) {}

  SetpointManagerCondenserEnteringResetIdeal::SetpointManagerCondenserEnteringResetIdeal(
    std::shared_ptr<detail::SetpointManagerCondenserEnteringResetIdeal_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType SetpointManagerCondenserEnteringResetIdeal::iddObjectType() {
    return IddObjectType::SetpointManager_CondenserEnteringReset_Ideal;
  }

  std::vector<std::string> SetpointManagerCondenserEnteringResetIdeal::controlVariableValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::SetpointManager_CondenserEnteringReset_IdealFields::ControlVariable);
  }

  std::string SetpointManagerCondenserEnteringResetIdeal::controlVariable() const {
    return getImpl<detail::SetpointManagerCondenserEnteringResetIdeal_Impl>()->controlVariable();
  }

  bool SetpointManagerCondenserEnteringResetIdeal::isControlVariableDefaulted() const {
    return getImpl<detail::SetpointManagerCondenserEnteringResetIdeal_Impl>()->isControlVariableDefaulted();
  }

  bool SetpointManagerCondenserEnteringResetIdeal::setControlVariable(const std::string& controlVariable) {
    return getImpl<detail::SetpointManagerCondenserEnteringResetIdeal_Impl>()->setControlVariable(controlVariable);
  }

  void SetpointManagerCondenserEnteringResetIdeal::resetControlVariable() {
    getImpl<detail::SetpointManagerCondenserEnteringResetIdeal_Impl>()->resetControlVariable();
  }

  double SetpointManagerCondenserEnteringResetIdeal::minimumLift() const {
    return getImpl<detail::SetpointManagerCondenserEnteringResetIdeal_Impl>()->minimumLift();
  }

  bool SetpointManagerCondenserEnteringResetIdeal::isMinimumLiftDefaulted() const {
    return getImpl<detail::SetpointManagerCondenserEnteringResetIdeal_Impl>()->isMinimumLiftDefaulted();
  }

  bool SetpointManagerCondenserEnteringResetIdeal::setMinimumLift(double minimumLift) {
    return getImpl<detail::SetpointManagerCondenserEnteringResetIdeal_Impl>()->setMinimumLift(minimumLift);
  }

  void SetpointManagerCondenserEnteringResetIdeal::resetMinimumLift() {
    getImpl<detail::SetpointManagerCondenserEnteringResetIdeal_Impl>()->resetMinimumLift();
  }

  double SetpointManagerCondenserEnteringResetIdeal::maximumCondenserEnteringWaterTemperature() const {
    return getImpl<detail::SetpointManagerCondenserEnteringResetIdeal_Impl>()->maximumCondenserEnteringWaterTemperature();
  }

  bool SetpointManagerCondenserEnteringResetIdeal::isMaximumCondenserEnteringWaterTemperatureDefaulted() const {
    return getImpl<detail::SetpointManagerCondenserEnteringResetIdeal_Impl>()->isMaximumCondenserEnteringWaterTemperatureDefaulted();
  }

  bool SetpointManagerCondenserEnteringResetIdeal::setMaximumCondenserEnteringWaterTemperature(double maximumCondenserEnteringWaterTemperature) {
    return getImpl<detail::SetpointManagerCondenserEnteringResetIdeal_Impl>()->setMaximumCondenserEnteringWaterTemperature(
      maximumCondenserEnteringWaterTemperature);
  }

  void SetpointManagerCondenserEnteringResetIdeal::resetMaximumCondenserEnteringWaterTemperature() {
    getImpl<detail::SetpointManagerCondenserEnteringResetIdeal_Impl>()->resetMaximumCondenserEnteringWaterTemperature();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string SetpointManagerCondenserEnteringResetIdeal_Impl::controlVariable() const {
      const auto value = getString(openstudio::SetpointManager_CondenserEnteringReset_IdealFields::ControlVariable, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SetpointManagerCondenserEnteringResetIdeal_Impl::isControlVariableDefaulted() const {
      return isEmpty(openstudio::SetpointManager_CondenserEnteringReset_IdealFields::ControlVariable);
    }

    bool SetpointManagerCondenserEnteringResetIdeal_Impl::setControlVariable(const std::string& controlVariable) {
      return setString(openstudio::SetpointManager_CondenserEnteringReset_IdealFields::ControlVariable, controlVariable);
    }

    void SetpointManagerCondenserEnteringResetIdeal_Impl::resetControlVariable() {
      OS_ASSERT(setString(openstudio::SetpointManager_CondenserEnteringReset_IdealFields::ControlVariable, ""));
    }

    double SetpointManagerCondenserEnteringResetIdeal_Impl::minimumLift() const {
      const auto value = getDouble(openstudio::SetpointManager_CondenserEnteringReset_IdealFields::MinimumLift, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SetpointManagerCondenserEnteringResetIdeal_Impl::isMinimumLiftDefaulted() const {
      return isEmpty(openstudio::SetpointManager_CondenserEnteringReset_IdealFields::MinimumLift);
    }

    bool SetpointManagerCondenserEnteringResetIdeal_Impl::setMinimumLift(double minimumLift) {
      const bool result = setDouble(openstudio::SetpointManager_CondenserEnteringReset_IdealFields::MinimumLift, minimumLift);
      OS_ASSERT(result);
      return result;
    }

    void SetpointManagerCondenserEnteringResetIdeal_Impl::resetMinimumLift() {
      OS_ASSERT(setString(openstudio::SetpointManager_CondenserEnteringReset_IdealFields::MinimumLift, ""));
    }

    double SetpointManagerCondenserEnteringResetIdeal_Impl::maximumCondenserEnteringWaterTemperature() const {
      const auto value = getDouble(openstudio::SetpointManager_CondenserEnteringReset_IdealFields::MaximumCondenserEnteringWaterTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SetpointManagerCondenserEnteringResetIdeal_Impl::isMaximumCondenserEnteringWaterTemperatureDefaulted() const {
      return isEmpty(openstudio::SetpointManager_CondenserEnteringReset_IdealFields::MaximumCondenserEnteringWaterTemperature);
    }

    bool
      SetpointManagerCondenserEnteringResetIdeal_Impl::setMaximumCondenserEnteringWaterTemperature(double maximumCondenserEnteringWaterTemperature) {
      const bool result = setDouble(openstudio::SetpointManager_CondenserEnteringReset_IdealFields::MaximumCondenserEnteringWaterTemperature,
                                    maximumCondenserEnteringWaterTemperature);
      OS_ASSERT(result);
      return result;
    }

    void SetpointManagerCondenserEnteringResetIdeal_Impl::resetMaximumCondenserEnteringWaterTemperature() {
      OS_ASSERT(setString(openstudio::SetpointManager_CondenserEnteringReset_IdealFields::MaximumCondenserEnteringWaterTemperature, ""));
    }

    std::vector<std::string> SetpointManagerCondenserEnteringResetIdeal_Impl::controlVariableValues() const {
      return SetpointManagerCondenserEnteringResetIdeal::controlVariableValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
