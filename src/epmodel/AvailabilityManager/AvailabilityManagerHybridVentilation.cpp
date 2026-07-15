/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AvailabilityManager/AvailabilityManagerHybridVentilation.hpp"
#include "AvailabilityManager/AvailabilityManagerHybridVentilation_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/AvailabilityManager_HybridVentilation_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  AvailabilityManagerHybridVentilation::AvailabilityManagerHybridVentilation(const Model& model)
    : ModelObject(AvailabilityManagerHybridVentilation::iddObjectType(), model) {
    setUseWeatherFileRainIndicators(true);
    setMaximumWindSpeed(40.0);
    setMinimumOutdoorTemperature(20.0);
    setMaximumOutdoorTemperature(30.0);
    setMinimumOutdoorEnthalpy(20000.0);
    setMaximumOutdoorEnthalpy(30000.0);
    setMinimumOutdoorDewpoint(15.0);
    setMaximumOutdoorDewpoint(30.0);
    setMinimumHVACOperationTime(0.0);
    setMinimumVentilationTime(0.0);
  }

  AvailabilityManagerHybridVentilation::AvailabilityManagerHybridVentilation(std::shared_ptr<detail::AvailabilityManagerHybridVentilation_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType AvailabilityManagerHybridVentilation::iddObjectType() {
    return IddObjectType::AvailabilityManager_HybridVentilation;
  }

  bool AvailabilityManagerHybridVentilation::useWeatherFileRainIndicators() const {
    return getImpl<detail::AvailabilityManagerHybridVentilation_Impl>()->useWeatherFileRainIndicators();
  }

  bool AvailabilityManagerHybridVentilation::setUseWeatherFileRainIndicators(bool useWeatherFileRainIndicators) {
    return getImpl<detail::AvailabilityManagerHybridVentilation_Impl>()->setUseWeatherFileRainIndicators(useWeatherFileRainIndicators);
  }

  double AvailabilityManagerHybridVentilation::maximumWindSpeed() const {
    return getImpl<detail::AvailabilityManagerHybridVentilation_Impl>()->maximumWindSpeed();
  }

  bool AvailabilityManagerHybridVentilation::setMaximumWindSpeed(double maximumWindSpeed) {
    return getImpl<detail::AvailabilityManagerHybridVentilation_Impl>()->setMaximumWindSpeed(maximumWindSpeed);
  }

  double AvailabilityManagerHybridVentilation::minimumOutdoorTemperature() const {
    return getImpl<detail::AvailabilityManagerHybridVentilation_Impl>()->minimumOutdoorTemperature();
  }

  bool AvailabilityManagerHybridVentilation::setMinimumOutdoorTemperature(double minimumOutdoorTemperature) {
    return getImpl<detail::AvailabilityManagerHybridVentilation_Impl>()->setMinimumOutdoorTemperature(minimumOutdoorTemperature);
  }

  double AvailabilityManagerHybridVentilation::maximumOutdoorTemperature() const {
    return getImpl<detail::AvailabilityManagerHybridVentilation_Impl>()->maximumOutdoorTemperature();
  }

  bool AvailabilityManagerHybridVentilation::setMaximumOutdoorTemperature(double maximumOutdoorTemperature) {
    return getImpl<detail::AvailabilityManagerHybridVentilation_Impl>()->setMaximumOutdoorTemperature(maximumOutdoorTemperature);
  }

  double AvailabilityManagerHybridVentilation::minimumOutdoorEnthalpy() const {
    return getImpl<detail::AvailabilityManagerHybridVentilation_Impl>()->minimumOutdoorEnthalpy();
  }

  bool AvailabilityManagerHybridVentilation::setMinimumOutdoorEnthalpy(double minimumOutdoorEnthalpy) {
    return getImpl<detail::AvailabilityManagerHybridVentilation_Impl>()->setMinimumOutdoorEnthalpy(minimumOutdoorEnthalpy);
  }

  double AvailabilityManagerHybridVentilation::maximumOutdoorEnthalpy() const {
    return getImpl<detail::AvailabilityManagerHybridVentilation_Impl>()->maximumOutdoorEnthalpy();
  }

  bool AvailabilityManagerHybridVentilation::setMaximumOutdoorEnthalpy(double maximumOutdoorEnthalpy) {
    return getImpl<detail::AvailabilityManagerHybridVentilation_Impl>()->setMaximumOutdoorEnthalpy(maximumOutdoorEnthalpy);
  }

  double AvailabilityManagerHybridVentilation::minimumOutdoorDewpoint() const {
    return getImpl<detail::AvailabilityManagerHybridVentilation_Impl>()->minimumOutdoorDewpoint();
  }

  bool AvailabilityManagerHybridVentilation::setMinimumOutdoorDewpoint(double minimumOutdoorDewpoint) {
    return getImpl<detail::AvailabilityManagerHybridVentilation_Impl>()->setMinimumOutdoorDewpoint(minimumOutdoorDewpoint);
  }

  double AvailabilityManagerHybridVentilation::maximumOutdoorDewpoint() const {
    return getImpl<detail::AvailabilityManagerHybridVentilation_Impl>()->maximumOutdoorDewpoint();
  }

  bool AvailabilityManagerHybridVentilation::setMaximumOutdoorDewpoint(double maximumOutdoorDewpoint) {
    return getImpl<detail::AvailabilityManagerHybridVentilation_Impl>()->setMaximumOutdoorDewpoint(maximumOutdoorDewpoint);
  }

  double AvailabilityManagerHybridVentilation::minimumHVACOperationTime() const {
    return getImpl<detail::AvailabilityManagerHybridVentilation_Impl>()->minimumHVACOperationTime();
  }

  bool AvailabilityManagerHybridVentilation::setMinimumHVACOperationTime(double minimumHVACOperationTime) {
    return getImpl<detail::AvailabilityManagerHybridVentilation_Impl>()->setMinimumHVACOperationTime(minimumHVACOperationTime);
  }

  double AvailabilityManagerHybridVentilation::minimumVentilationTime() const {
    return getImpl<detail::AvailabilityManagerHybridVentilation_Impl>()->minimumVentilationTime();
  }

  bool AvailabilityManagerHybridVentilation::setMinimumVentilationTime(double minimumVentilationTime) {
    return getImpl<detail::AvailabilityManagerHybridVentilation_Impl>()->setMinimumVentilationTime(minimumVentilationTime);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    bool AvailabilityManagerHybridVentilation_Impl::useWeatherFileRainIndicators() const {
      const auto value = getString(openstudio::AvailabilityManager_HybridVentilationFields::UseWeatherFileRainIndicators, true);
      OS_ASSERT(value);
      return openstudio::istringEqual(*value, "Yes");
    }

    bool AvailabilityManagerHybridVentilation_Impl::setUseWeatherFileRainIndicators(bool useWeatherFileRainIndicators) {
      const bool result =
        setString(openstudio::AvailabilityManager_HybridVentilationFields::UseWeatherFileRainIndicators, useWeatherFileRainIndicators ? "Yes" : "No");
      OS_ASSERT(result);
      return result;
    }

    double AvailabilityManagerHybridVentilation_Impl::maximumWindSpeed() const {
      const auto value = getDouble(openstudio::AvailabilityManager_HybridVentilationFields::MaximumWindSpeed, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AvailabilityManagerHybridVentilation_Impl::setMaximumWindSpeed(double maximumWindSpeed) {
      const bool result = setDouble(openstudio::AvailabilityManager_HybridVentilationFields::MaximumWindSpeed, maximumWindSpeed);
      OS_ASSERT(result);
      return result;
    }

    double AvailabilityManagerHybridVentilation_Impl::minimumOutdoorTemperature() const {
      const auto value = getDouble(openstudio::AvailabilityManager_HybridVentilationFields::MinimumOutdoorTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AvailabilityManagerHybridVentilation_Impl::setMinimumOutdoorTemperature(double minimumOutdoorTemperature) {
      const bool result = setDouble(openstudio::AvailabilityManager_HybridVentilationFields::MinimumOutdoorTemperature, minimumOutdoorTemperature);
      OS_ASSERT(result);
      return result;
    }

    double AvailabilityManagerHybridVentilation_Impl::maximumOutdoorTemperature() const {
      const auto value = getDouble(openstudio::AvailabilityManager_HybridVentilationFields::MaximumOutdoorTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AvailabilityManagerHybridVentilation_Impl::setMaximumOutdoorTemperature(double maximumOutdoorTemperature) {
      const bool result = setDouble(openstudio::AvailabilityManager_HybridVentilationFields::MaximumOutdoorTemperature, maximumOutdoorTemperature);
      OS_ASSERT(result);
      return result;
    }

    double AvailabilityManagerHybridVentilation_Impl::minimumOutdoorEnthalpy() const {
      const auto value = getDouble(openstudio::AvailabilityManager_HybridVentilationFields::MinimumOutdoorEnthalpy, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AvailabilityManagerHybridVentilation_Impl::setMinimumOutdoorEnthalpy(double minimumOutdoorEnthalpy) {
      const bool result = setDouble(openstudio::AvailabilityManager_HybridVentilationFields::MinimumOutdoorEnthalpy, minimumOutdoorEnthalpy);
      OS_ASSERT(result);
      return result;
    }

    double AvailabilityManagerHybridVentilation_Impl::maximumOutdoorEnthalpy() const {
      const auto value = getDouble(openstudio::AvailabilityManager_HybridVentilationFields::MaximumOutdoorEnthalpy, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AvailabilityManagerHybridVentilation_Impl::setMaximumOutdoorEnthalpy(double maximumOutdoorEnthalpy) {
      const bool result = setDouble(openstudio::AvailabilityManager_HybridVentilationFields::MaximumOutdoorEnthalpy, maximumOutdoorEnthalpy);
      OS_ASSERT(result);
      return result;
    }

    double AvailabilityManagerHybridVentilation_Impl::minimumOutdoorDewpoint() const {
      const auto value = getDouble(openstudio::AvailabilityManager_HybridVentilationFields::MinimumOutdoorDewpoint, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AvailabilityManagerHybridVentilation_Impl::setMinimumOutdoorDewpoint(double minimumOutdoorDewpoint) {
      const bool result = setDouble(openstudio::AvailabilityManager_HybridVentilationFields::MinimumOutdoorDewpoint, minimumOutdoorDewpoint);
      OS_ASSERT(result);
      return result;
    }

    double AvailabilityManagerHybridVentilation_Impl::maximumOutdoorDewpoint() const {
      const auto value = getDouble(openstudio::AvailabilityManager_HybridVentilationFields::MaximumOutdoorDewpoint, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AvailabilityManagerHybridVentilation_Impl::setMaximumOutdoorDewpoint(double maximumOutdoorDewpoint) {
      const bool result = setDouble(openstudio::AvailabilityManager_HybridVentilationFields::MaximumOutdoorDewpoint, maximumOutdoorDewpoint);
      OS_ASSERT(result);
      return result;
    }

    double AvailabilityManagerHybridVentilation_Impl::minimumHVACOperationTime() const {
      const auto value = getDouble(openstudio::AvailabilityManager_HybridVentilationFields::MinimumHVACOperationTime, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AvailabilityManagerHybridVentilation_Impl::setMinimumHVACOperationTime(double minimumHVACOperationTime) {
      const bool result = setDouble(openstudio::AvailabilityManager_HybridVentilationFields::MinimumHVACOperationTime, minimumHVACOperationTime);
      OS_ASSERT(result);
      return result;
    }

    double AvailabilityManagerHybridVentilation_Impl::minimumVentilationTime() const {
      const auto value = getDouble(openstudio::AvailabilityManager_HybridVentilationFields::MinimumVentilationTime, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AvailabilityManagerHybridVentilation_Impl::setMinimumVentilationTime(double minimumVentilationTime) {
      const bool result = setDouble(openstudio::AvailabilityManager_HybridVentilationFields::MinimumVentilationTime, minimumVentilationTime);
      OS_ASSERT(result);
      return result;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
