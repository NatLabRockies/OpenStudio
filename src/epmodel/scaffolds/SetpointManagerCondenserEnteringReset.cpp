/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SetpointManagerCondenserEnteringReset.hpp"
#include "SetpointManagerCondenserEnteringReset_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/SetpointManager_CondenserEnteringReset_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  SetpointManagerCondenserEnteringReset::SetpointManagerCondenserEnteringReset(const Model& model)
    : ModelObject(SetpointManagerCondenserEnteringReset::iddObjectType(), model) {}

  SetpointManagerCondenserEnteringReset::SetpointManagerCondenserEnteringReset(
    std::shared_ptr<detail::SetpointManagerCondenserEnteringReset_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType SetpointManagerCondenserEnteringReset::iddObjectType() {
    return IddObjectType::SetpointManager_CondenserEnteringReset;
  }

  std::vector<std::string> SetpointManagerCondenserEnteringReset::controlVariableValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::SetpointManager_CondenserEnteringResetFields::ControlVariable);
  }

  std::string SetpointManagerCondenserEnteringReset::controlVariable() const {
    return getImpl<detail::SetpointManagerCondenserEnteringReset_Impl>()->controlVariable();
  }

  bool SetpointManagerCondenserEnteringReset::isControlVariableDefaulted() const {
    return getImpl<detail::SetpointManagerCondenserEnteringReset_Impl>()->isControlVariableDefaulted();
  }

  bool SetpointManagerCondenserEnteringReset::setControlVariable(const std::string& controlVariable) {
    return getImpl<detail::SetpointManagerCondenserEnteringReset_Impl>()->setControlVariable(controlVariable);
  }

  void SetpointManagerCondenserEnteringReset::resetControlVariable() {
    getImpl<detail::SetpointManagerCondenserEnteringReset_Impl>()->resetControlVariable();
  }

  double SetpointManagerCondenserEnteringReset::minimumLift() const {
    return getImpl<detail::SetpointManagerCondenserEnteringReset_Impl>()->minimumLift();
  }

  bool SetpointManagerCondenserEnteringReset::isMinimumLiftDefaulted() const {
    return getImpl<detail::SetpointManagerCondenserEnteringReset_Impl>()->isMinimumLiftDefaulted();
  }

  bool SetpointManagerCondenserEnteringReset::setMinimumLift(double minimumLift) {
    return getImpl<detail::SetpointManagerCondenserEnteringReset_Impl>()->setMinimumLift(minimumLift);
  }

  void SetpointManagerCondenserEnteringReset::resetMinimumLift() {
    getImpl<detail::SetpointManagerCondenserEnteringReset_Impl>()->resetMinimumLift();
  }

  double SetpointManagerCondenserEnteringReset::maximumCondenserEnteringWaterTemperature() const {
    return getImpl<detail::SetpointManagerCondenserEnteringReset_Impl>()->maximumCondenserEnteringWaterTemperature();
  }

  bool SetpointManagerCondenserEnteringReset::isMaximumCondenserEnteringWaterTemperatureDefaulted() const {
    return getImpl<detail::SetpointManagerCondenserEnteringReset_Impl>()->isMaximumCondenserEnteringWaterTemperatureDefaulted();
  }

  bool SetpointManagerCondenserEnteringReset::setMaximumCondenserEnteringWaterTemperature(double maximumCondenserEnteringWaterTemperature) {
    return getImpl<detail::SetpointManagerCondenserEnteringReset_Impl>()->setMaximumCondenserEnteringWaterTemperature(
      maximumCondenserEnteringWaterTemperature);
  }

  void SetpointManagerCondenserEnteringReset::resetMaximumCondenserEnteringWaterTemperature() {
    getImpl<detail::SetpointManagerCondenserEnteringReset_Impl>()->resetMaximumCondenserEnteringWaterTemperature();
  }

  double SetpointManagerCondenserEnteringReset::coolingTowerDesignInletAirWetBulbTemperature() const {
    return getImpl<detail::SetpointManagerCondenserEnteringReset_Impl>()->coolingTowerDesignInletAirWetBulbTemperature();
  }

  bool SetpointManagerCondenserEnteringReset::isCoolingTowerDesignInletAirWetBulbTemperatureDefaulted() const {
    return getImpl<detail::SetpointManagerCondenserEnteringReset_Impl>()->isCoolingTowerDesignInletAirWetBulbTemperatureDefaulted();
  }

  bool SetpointManagerCondenserEnteringReset::setCoolingTowerDesignInletAirWetBulbTemperature(double coolingTowerDesignInletAirWetBulbTemperature) {
    return getImpl<detail::SetpointManagerCondenserEnteringReset_Impl>()->setCoolingTowerDesignInletAirWetBulbTemperature(
      coolingTowerDesignInletAirWetBulbTemperature);
  }

  void SetpointManagerCondenserEnteringReset::resetCoolingTowerDesignInletAirWetBulbTemperature() {
    getImpl<detail::SetpointManagerCondenserEnteringReset_Impl>()->resetCoolingTowerDesignInletAirWetBulbTemperature();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string SetpointManagerCondenserEnteringReset_Impl::controlVariable() const {
      const auto value = getString(openstudio::SetpointManager_CondenserEnteringResetFields::ControlVariable, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SetpointManagerCondenserEnteringReset_Impl::isControlVariableDefaulted() const {
      return isEmpty(openstudio::SetpointManager_CondenserEnteringResetFields::ControlVariable);
    }

    bool SetpointManagerCondenserEnteringReset_Impl::setControlVariable(const std::string& controlVariable) {
      return setString(openstudio::SetpointManager_CondenserEnteringResetFields::ControlVariable, controlVariable);
    }

    void SetpointManagerCondenserEnteringReset_Impl::resetControlVariable() {
      OS_ASSERT(setString(openstudio::SetpointManager_CondenserEnteringResetFields::ControlVariable, ""));
    }

    double SetpointManagerCondenserEnteringReset_Impl::minimumLift() const {
      const auto value = getDouble(openstudio::SetpointManager_CondenserEnteringResetFields::MinimumLift, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SetpointManagerCondenserEnteringReset_Impl::isMinimumLiftDefaulted() const {
      return isEmpty(openstudio::SetpointManager_CondenserEnteringResetFields::MinimumLift);
    }

    bool SetpointManagerCondenserEnteringReset_Impl::setMinimumLift(double minimumLift) {
      const bool result = setDouble(openstudio::SetpointManager_CondenserEnteringResetFields::MinimumLift, minimumLift);
      OS_ASSERT(result);
      return result;
    }

    void SetpointManagerCondenserEnteringReset_Impl::resetMinimumLift() {
      OS_ASSERT(setString(openstudio::SetpointManager_CondenserEnteringResetFields::MinimumLift, ""));
    }

    double SetpointManagerCondenserEnteringReset_Impl::maximumCondenserEnteringWaterTemperature() const {
      const auto value = getDouble(openstudio::SetpointManager_CondenserEnteringResetFields::MaximumCondenserEnteringWaterTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SetpointManagerCondenserEnteringReset_Impl::isMaximumCondenserEnteringWaterTemperatureDefaulted() const {
      return isEmpty(openstudio::SetpointManager_CondenserEnteringResetFields::MaximumCondenserEnteringWaterTemperature);
    }

    bool SetpointManagerCondenserEnteringReset_Impl::setMaximumCondenserEnteringWaterTemperature(double maximumCondenserEnteringWaterTemperature) {
      const bool result = setDouble(openstudio::SetpointManager_CondenserEnteringResetFields::MaximumCondenserEnteringWaterTemperature,
                                    maximumCondenserEnteringWaterTemperature);
      OS_ASSERT(result);
      return result;
    }

    void SetpointManagerCondenserEnteringReset_Impl::resetMaximumCondenserEnteringWaterTemperature() {
      OS_ASSERT(setString(openstudio::SetpointManager_CondenserEnteringResetFields::MaximumCondenserEnteringWaterTemperature, ""));
    }

    double SetpointManagerCondenserEnteringReset_Impl::coolingTowerDesignInletAirWetBulbTemperature() const {
      const auto value = getDouble(openstudio::SetpointManager_CondenserEnteringResetFields::CoolingTowerDesignInletAirWetBulbTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SetpointManagerCondenserEnteringReset_Impl::isCoolingTowerDesignInletAirWetBulbTemperatureDefaulted() const {
      return isEmpty(openstudio::SetpointManager_CondenserEnteringResetFields::CoolingTowerDesignInletAirWetBulbTemperature);
    }

    bool SetpointManagerCondenserEnteringReset_Impl::setCoolingTowerDesignInletAirWetBulbTemperature(
      double coolingTowerDesignInletAirWetBulbTemperature) {
      const bool result = setDouble(openstudio::SetpointManager_CondenserEnteringResetFields::CoolingTowerDesignInletAirWetBulbTemperature,
                                    coolingTowerDesignInletAirWetBulbTemperature);
      OS_ASSERT(result);
      return result;
    }

    void SetpointManagerCondenserEnteringReset_Impl::resetCoolingTowerDesignInletAirWetBulbTemperature() {
      OS_ASSERT(setString(openstudio::SetpointManager_CondenserEnteringResetFields::CoolingTowerDesignInletAirWetBulbTemperature, ""));
    }

    std::vector<std::string> SetpointManagerCondenserEnteringReset_Impl::controlVariableValues() const {
      return SetpointManagerCondenserEnteringReset::controlVariableValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
