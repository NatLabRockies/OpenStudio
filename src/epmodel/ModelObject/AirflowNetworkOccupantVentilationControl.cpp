/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AirflowNetworkOccupantVentilationControl.hpp"
#include "AirflowNetworkOccupantVentilationControl_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/AirflowNetwork_OccupantVentilationControl_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  AirflowNetworkOccupantVentilationControl::AirflowNetworkOccupantVentilationControl(const Model& model)
    : ModelObject(AirflowNetworkOccupantVentilationControl::iddObjectType(), model) {}

  AirflowNetworkOccupantVentilationControl::AirflowNetworkOccupantVentilationControl(
    std::shared_ptr<detail::AirflowNetworkOccupantVentilationControl_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType AirflowNetworkOccupantVentilationControl::iddObjectType() {
    return IddObjectType::AirflowNetwork_OccupantVentilationControl;
  }

  double AirflowNetworkOccupantVentilationControl::minimumOpeningTime() const {
    return getImpl<detail::AirflowNetworkOccupantVentilationControl_Impl>()->minimumOpeningTime();
  }

  bool AirflowNetworkOccupantVentilationControl::isMinimumOpeningTimeDefaulted() const {
    return getImpl<detail::AirflowNetworkOccupantVentilationControl_Impl>()->isMinimumOpeningTimeDefaulted();
  }

  bool AirflowNetworkOccupantVentilationControl::setMinimumOpeningTime(double minimumOpeningTime) {
    return getImpl<detail::AirflowNetworkOccupantVentilationControl_Impl>()->setMinimumOpeningTime(minimumOpeningTime);
  }

  void AirflowNetworkOccupantVentilationControl::resetMinimumOpeningTime() {
    getImpl<detail::AirflowNetworkOccupantVentilationControl_Impl>()->resetMinimumOpeningTime();
  }

  double AirflowNetworkOccupantVentilationControl::minimumClosingTime() const {
    return getImpl<detail::AirflowNetworkOccupantVentilationControl_Impl>()->minimumClosingTime();
  }

  bool AirflowNetworkOccupantVentilationControl::isMinimumClosingTimeDefaulted() const {
    return getImpl<detail::AirflowNetworkOccupantVentilationControl_Impl>()->isMinimumClosingTimeDefaulted();
  }

  bool AirflowNetworkOccupantVentilationControl::setMinimumClosingTime(double minimumClosingTime) {
    return getImpl<detail::AirflowNetworkOccupantVentilationControl_Impl>()->setMinimumClosingTime(minimumClosingTime);
  }

  void AirflowNetworkOccupantVentilationControl::resetMinimumClosingTime() {
    getImpl<detail::AirflowNetworkOccupantVentilationControl_Impl>()->resetMinimumClosingTime();
  }

  double AirflowNetworkOccupantVentilationControl::thermalComfortTemperatureBoundaryPoint() const {
    return getImpl<detail::AirflowNetworkOccupantVentilationControl_Impl>()->thermalComfortTemperatureBoundaryPoint();
  }

  bool AirflowNetworkOccupantVentilationControl::isThermalComfortTemperatureBoundaryPointDefaulted() const {
    return getImpl<detail::AirflowNetworkOccupantVentilationControl_Impl>()->isThermalComfortTemperatureBoundaryPointDefaulted();
  }

  bool AirflowNetworkOccupantVentilationControl::setThermalComfortTemperatureBoundaryPoint(double thermalComfortTemperatureBoundaryPoint) {
    return getImpl<detail::AirflowNetworkOccupantVentilationControl_Impl>()->setThermalComfortTemperatureBoundaryPoint(
      thermalComfortTemperatureBoundaryPoint);
  }

  void AirflowNetworkOccupantVentilationControl::resetThermalComfortTemperatureBoundaryPoint() {
    getImpl<detail::AirflowNetworkOccupantVentilationControl_Impl>()->resetThermalComfortTemperatureBoundaryPoint();
  }

  double AirflowNetworkOccupantVentilationControl::maximumPredictedPercentageofDissatisfiedThreshold() const {
    return getImpl<detail::AirflowNetworkOccupantVentilationControl_Impl>()->maximumPredictedPercentageofDissatisfiedThreshold();
  }

  bool AirflowNetworkOccupantVentilationControl::isMaximumPredictedPercentageofDissatisfiedThresholdDefaulted() const {
    return getImpl<detail::AirflowNetworkOccupantVentilationControl_Impl>()->isMaximumPredictedPercentageofDissatisfiedThresholdDefaulted();
  }

  bool AirflowNetworkOccupantVentilationControl::setMaximumPredictedPercentageofDissatisfiedThreshold(
    double maximumPredictedPercentageofDissatisfiedThreshold) {
    return getImpl<detail::AirflowNetworkOccupantVentilationControl_Impl>()->setMaximumPredictedPercentageofDissatisfiedThreshold(
      maximumPredictedPercentageofDissatisfiedThreshold);
  }

  void AirflowNetworkOccupantVentilationControl::resetMaximumPredictedPercentageofDissatisfiedThreshold() {
    getImpl<detail::AirflowNetworkOccupantVentilationControl_Impl>()->resetMaximumPredictedPercentageofDissatisfiedThreshold();
  }

  bool AirflowNetworkOccupantVentilationControl::occupancyCheck() const {
    return getImpl<detail::AirflowNetworkOccupantVentilationControl_Impl>()->occupancyCheck();
  }

  bool AirflowNetworkOccupantVentilationControl::isOccupancyCheckDefaulted() const {
    return getImpl<detail::AirflowNetworkOccupantVentilationControl_Impl>()->isOccupancyCheckDefaulted();
  }

  void AirflowNetworkOccupantVentilationControl::setOccupancyCheck(bool occupancyCheck) {
    getImpl<detail::AirflowNetworkOccupantVentilationControl_Impl>()->setOccupancyCheck(occupancyCheck);
  }

  void AirflowNetworkOccupantVentilationControl::resetOccupancyCheck() {
    getImpl<detail::AirflowNetworkOccupantVentilationControl_Impl>()->resetOccupancyCheck();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double AirflowNetworkOccupantVentilationControl_Impl::minimumOpeningTime() const {
      const auto value = getDouble(openstudio::AirflowNetwork_OccupantVentilationControlFields::MinimumOpeningTime, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirflowNetworkOccupantVentilationControl_Impl::isMinimumOpeningTimeDefaulted() const {
      return isEmpty(openstudio::AirflowNetwork_OccupantVentilationControlFields::MinimumOpeningTime);
    }

    bool AirflowNetworkOccupantVentilationControl_Impl::setMinimumOpeningTime(double minimumOpeningTime) {
      return setDouble(openstudio::AirflowNetwork_OccupantVentilationControlFields::MinimumOpeningTime, minimumOpeningTime);
    }

    void AirflowNetworkOccupantVentilationControl_Impl::resetMinimumOpeningTime() {
      OS_ASSERT(setString(openstudio::AirflowNetwork_OccupantVentilationControlFields::MinimumOpeningTime, ""));
    }

    double AirflowNetworkOccupantVentilationControl_Impl::minimumClosingTime() const {
      const auto value = getDouble(openstudio::AirflowNetwork_OccupantVentilationControlFields::MinimumClosingTime, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirflowNetworkOccupantVentilationControl_Impl::isMinimumClosingTimeDefaulted() const {
      return isEmpty(openstudio::AirflowNetwork_OccupantVentilationControlFields::MinimumClosingTime);
    }

    bool AirflowNetworkOccupantVentilationControl_Impl::setMinimumClosingTime(double minimumClosingTime) {
      return setDouble(openstudio::AirflowNetwork_OccupantVentilationControlFields::MinimumClosingTime, minimumClosingTime);
    }

    void AirflowNetworkOccupantVentilationControl_Impl::resetMinimumClosingTime() {
      OS_ASSERT(setString(openstudio::AirflowNetwork_OccupantVentilationControlFields::MinimumClosingTime, ""));
    }

    double AirflowNetworkOccupantVentilationControl_Impl::thermalComfortTemperatureBoundaryPoint() const {
      const auto value = getDouble(openstudio::AirflowNetwork_OccupantVentilationControlFields::ThermalComfortTemperatureBoundaryPoint, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirflowNetworkOccupantVentilationControl_Impl::isThermalComfortTemperatureBoundaryPointDefaulted() const {
      return isEmpty(openstudio::AirflowNetwork_OccupantVentilationControlFields::ThermalComfortTemperatureBoundaryPoint);
    }

    bool AirflowNetworkOccupantVentilationControl_Impl::setThermalComfortTemperatureBoundaryPoint(double thermalComfortTemperatureBoundaryPoint) {
      return setDouble(openstudio::AirflowNetwork_OccupantVentilationControlFields::ThermalComfortTemperatureBoundaryPoint,
                       thermalComfortTemperatureBoundaryPoint);
    }

    void AirflowNetworkOccupantVentilationControl_Impl::resetThermalComfortTemperatureBoundaryPoint() {
      OS_ASSERT(setString(openstudio::AirflowNetwork_OccupantVentilationControlFields::ThermalComfortTemperatureBoundaryPoint, ""));
    }

    double AirflowNetworkOccupantVentilationControl_Impl::maximumPredictedPercentageofDissatisfiedThreshold() const {
      const auto value = getDouble(openstudio::AirflowNetwork_OccupantVentilationControlFields::MaximumThresholdforPersonsDissatisfiedPPD, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirflowNetworkOccupantVentilationControl_Impl::isMaximumPredictedPercentageofDissatisfiedThresholdDefaulted() const {
      return isEmpty(openstudio::AirflowNetwork_OccupantVentilationControlFields::MaximumThresholdforPersonsDissatisfiedPPD);
    }

    bool AirflowNetworkOccupantVentilationControl_Impl::setMaximumPredictedPercentageofDissatisfiedThreshold(
      double maximumPredictedPercentageofDissatisfiedThreshold) {
      return setDouble(openstudio::AirflowNetwork_OccupantVentilationControlFields::MaximumThresholdforPersonsDissatisfiedPPD,
                       maximumPredictedPercentageofDissatisfiedThreshold);
    }

    void AirflowNetworkOccupantVentilationControl_Impl::resetMaximumPredictedPercentageofDissatisfiedThreshold() {
      OS_ASSERT(setString(openstudio::AirflowNetwork_OccupantVentilationControlFields::MaximumThresholdforPersonsDissatisfiedPPD, ""));
    }

    bool AirflowNetworkOccupantVentilationControl_Impl::occupancyCheck() const {
      const auto value = getString(openstudio::AirflowNetwork_OccupantVentilationControlFields::OccupancyCheck, true);
      OS_ASSERT(value);
      return openstudio::istringEqual(*value, "Yes");
    }

    bool AirflowNetworkOccupantVentilationControl_Impl::isOccupancyCheckDefaulted() const {
      return isEmpty(openstudio::AirflowNetwork_OccupantVentilationControlFields::OccupancyCheck);
    }

    void AirflowNetworkOccupantVentilationControl_Impl::setOccupancyCheck(bool occupancyCheck) {
      const bool result = setString(openstudio::AirflowNetwork_OccupantVentilationControlFields::OccupancyCheck, occupancyCheck ? "Yes" : "No");
      OS_ASSERT(result);
    }

    void AirflowNetworkOccupantVentilationControl_Impl::resetOccupancyCheck() {
      OS_ASSERT(setString(openstudio::AirflowNetwork_OccupantVentilationControlFields::OccupancyCheck, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
