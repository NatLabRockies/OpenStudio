/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SetpointManagerReturnTemperatureChilledWater.hpp"
#include "SetpointManagerReturnTemperatureChilledWater_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/SetpointManager_ReturnTemperature_ChilledWater_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  SetpointManagerReturnTemperatureChilledWater::SetpointManagerReturnTemperatureChilledWater(const Model& model)
    : ModelObject(SetpointManagerReturnTemperatureChilledWater::iddObjectType(), model) {}

  SetpointManagerReturnTemperatureChilledWater::SetpointManagerReturnTemperatureChilledWater(
    std::shared_ptr<detail::SetpointManagerReturnTemperatureChilledWater_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType SetpointManagerReturnTemperatureChilledWater::iddObjectType() {
    return IddObjectType::SetpointManager_ReturnTemperature_ChilledWater;
  }

  std::vector<std::string> SetpointManagerReturnTemperatureChilledWater::returnTemperatureSetpointInputTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::SetpointManager_ReturnTemperature_ChilledWaterFields::ReturnTemperatureSetpointInputType);
  }

  double SetpointManagerReturnTemperatureChilledWater::minimumSupplyTemperatureSetpoint() const {
    return getImpl<detail::SetpointManagerReturnTemperatureChilledWater_Impl>()->minimumSupplyTemperatureSetpoint();
  }

  bool SetpointManagerReturnTemperatureChilledWater::isMinimumSupplyTemperatureSetpointDefaulted() const {
    return getImpl<detail::SetpointManagerReturnTemperatureChilledWater_Impl>()->isMinimumSupplyTemperatureSetpointDefaulted();
  }

  bool SetpointManagerReturnTemperatureChilledWater::setMinimumSupplyTemperatureSetpoint(double minimumSupplyTemperatureSetpoint) {
    return getImpl<detail::SetpointManagerReturnTemperatureChilledWater_Impl>()->setMinimumSupplyTemperatureSetpoint(
      minimumSupplyTemperatureSetpoint);
  }

  void SetpointManagerReturnTemperatureChilledWater::resetMinimumSupplyTemperatureSetpoint() {
    getImpl<detail::SetpointManagerReturnTemperatureChilledWater_Impl>()->resetMinimumSupplyTemperatureSetpoint();
  }

  double SetpointManagerReturnTemperatureChilledWater::maximumSupplyTemperatureSetpoint() const {
    return getImpl<detail::SetpointManagerReturnTemperatureChilledWater_Impl>()->maximumSupplyTemperatureSetpoint();
  }

  bool SetpointManagerReturnTemperatureChilledWater::isMaximumSupplyTemperatureSetpointDefaulted() const {
    return getImpl<detail::SetpointManagerReturnTemperatureChilledWater_Impl>()->isMaximumSupplyTemperatureSetpointDefaulted();
  }

  bool SetpointManagerReturnTemperatureChilledWater::setMaximumSupplyTemperatureSetpoint(double maximumSupplyTemperatureSetpoint) {
    return getImpl<detail::SetpointManagerReturnTemperatureChilledWater_Impl>()->setMaximumSupplyTemperatureSetpoint(
      maximumSupplyTemperatureSetpoint);
  }

  void SetpointManagerReturnTemperatureChilledWater::resetMaximumSupplyTemperatureSetpoint() {
    getImpl<detail::SetpointManagerReturnTemperatureChilledWater_Impl>()->resetMaximumSupplyTemperatureSetpoint();
  }

  std::string SetpointManagerReturnTemperatureChilledWater::returnTemperatureSetpointInputType() const {
    return getImpl<detail::SetpointManagerReturnTemperatureChilledWater_Impl>()->returnTemperatureSetpointInputType();
  }

  bool SetpointManagerReturnTemperatureChilledWater::setReturnTemperatureSetpointInputType(const std::string& returnTemperatureSetpointInputType) {
    return getImpl<detail::SetpointManagerReturnTemperatureChilledWater_Impl>()->setReturnTemperatureSetpointInputType(
      returnTemperatureSetpointInputType);
  }

  double SetpointManagerReturnTemperatureChilledWater::returnTemperatureSetpointConstantValue() const {
    return getImpl<detail::SetpointManagerReturnTemperatureChilledWater_Impl>()->returnTemperatureSetpointConstantValue();
  }

  bool SetpointManagerReturnTemperatureChilledWater::isReturnTemperatureSetpointConstantValueDefaulted() const {
    return getImpl<detail::SetpointManagerReturnTemperatureChilledWater_Impl>()->isReturnTemperatureSetpointConstantValueDefaulted();
  }

  bool SetpointManagerReturnTemperatureChilledWater::setReturnTemperatureSetpointConstantValue(double returnTemperatureSetpointConstantValue) {
    return getImpl<detail::SetpointManagerReturnTemperatureChilledWater_Impl>()->setReturnTemperatureSetpointConstantValue(
      returnTemperatureSetpointConstantValue);
  }

  void SetpointManagerReturnTemperatureChilledWater::resetReturnTemperatureSetpointConstantValue() {
    getImpl<detail::SetpointManagerReturnTemperatureChilledWater_Impl>()->resetReturnTemperatureSetpointConstantValue();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double SetpointManagerReturnTemperatureChilledWater_Impl::minimumSupplyTemperatureSetpoint() const {
      const auto value = getDouble(openstudio::SetpointManager_ReturnTemperature_ChilledWaterFields::MinimumSupplyTemperatureSetpoint, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SetpointManagerReturnTemperatureChilledWater_Impl::isMinimumSupplyTemperatureSetpointDefaulted() const {
      return isEmpty(openstudio::SetpointManager_ReturnTemperature_ChilledWaterFields::MinimumSupplyTemperatureSetpoint);
    }

    bool SetpointManagerReturnTemperatureChilledWater_Impl::setMinimumSupplyTemperatureSetpoint(double minimumSupplyTemperatureSetpoint) {
      const bool result = setDouble(openstudio::SetpointManager_ReturnTemperature_ChilledWaterFields::MinimumSupplyTemperatureSetpoint,
                                    minimumSupplyTemperatureSetpoint);
      OS_ASSERT(result);
      return result;
    }

    void SetpointManagerReturnTemperatureChilledWater_Impl::resetMinimumSupplyTemperatureSetpoint() {
      OS_ASSERT(setString(openstudio::SetpointManager_ReturnTemperature_ChilledWaterFields::MinimumSupplyTemperatureSetpoint, ""));
    }

    double SetpointManagerReturnTemperatureChilledWater_Impl::maximumSupplyTemperatureSetpoint() const {
      const auto value = getDouble(openstudio::SetpointManager_ReturnTemperature_ChilledWaterFields::MaximumSupplyTemperatureSetpoint, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SetpointManagerReturnTemperatureChilledWater_Impl::isMaximumSupplyTemperatureSetpointDefaulted() const {
      return isEmpty(openstudio::SetpointManager_ReturnTemperature_ChilledWaterFields::MaximumSupplyTemperatureSetpoint);
    }

    bool SetpointManagerReturnTemperatureChilledWater_Impl::setMaximumSupplyTemperatureSetpoint(double maximumSupplyTemperatureSetpoint) {
      const bool result = setDouble(openstudio::SetpointManager_ReturnTemperature_ChilledWaterFields::MaximumSupplyTemperatureSetpoint,
                                    maximumSupplyTemperatureSetpoint);
      OS_ASSERT(result);
      return result;
    }

    void SetpointManagerReturnTemperatureChilledWater_Impl::resetMaximumSupplyTemperatureSetpoint() {
      OS_ASSERT(setString(openstudio::SetpointManager_ReturnTemperature_ChilledWaterFields::MaximumSupplyTemperatureSetpoint, ""));
    }

    std::string SetpointManagerReturnTemperatureChilledWater_Impl::returnTemperatureSetpointInputType() const {
      const auto value = getString(openstudio::SetpointManager_ReturnTemperature_ChilledWaterFields::ReturnTemperatureSetpointInputType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SetpointManagerReturnTemperatureChilledWater_Impl::setReturnTemperatureSetpointInputType(
      const std::string& returnTemperatureSetpointInputType) {
      return setString(openstudio::SetpointManager_ReturnTemperature_ChilledWaterFields::ReturnTemperatureSetpointInputType,
                       returnTemperatureSetpointInputType);
    }

    double SetpointManagerReturnTemperatureChilledWater_Impl::returnTemperatureSetpointConstantValue() const {
      const auto value = getDouble(openstudio::SetpointManager_ReturnTemperature_ChilledWaterFields::ReturnTemperatureSetpointConstantValue, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SetpointManagerReturnTemperatureChilledWater_Impl::isReturnTemperatureSetpointConstantValueDefaulted() const {
      return isEmpty(openstudio::SetpointManager_ReturnTemperature_ChilledWaterFields::ReturnTemperatureSetpointConstantValue);
    }

    bool SetpointManagerReturnTemperatureChilledWater_Impl::setReturnTemperatureSetpointConstantValue(double returnTemperatureSetpointConstantValue) {
      const bool result = setDouble(openstudio::SetpointManager_ReturnTemperature_ChilledWaterFields::ReturnTemperatureSetpointConstantValue,
                                    returnTemperatureSetpointConstantValue);
      OS_ASSERT(result);
      return result;
    }

    void SetpointManagerReturnTemperatureChilledWater_Impl::resetReturnTemperatureSetpointConstantValue() {
      OS_ASSERT(setString(openstudio::SetpointManager_ReturnTemperature_ChilledWaterFields::ReturnTemperatureSetpointConstantValue, ""));
    }

    std::vector<std::string> SetpointManagerReturnTemperatureChilledWater_Impl::returnTemperatureSetpointInputTypeValues() const {
      return SetpointManagerReturnTemperatureChilledWater::returnTemperatureSetpointInputTypeValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
