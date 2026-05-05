/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AvailabilityManager/AvailabilityManagerOptimumStart.hpp"
#include "AvailabilityManager/AvailabilityManagerOptimumStart_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/AvailabilityManager_OptimumStart_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  AvailabilityManagerOptimumStart::AvailabilityManagerOptimumStart(const Model& model)
    : ModelObject(AvailabilityManagerOptimumStart::iddObjectType(), model) {
    setControlType("MaximumofZoneList");
    setMaximumValueforOptimumStartTime(6.0);
    setControlAlgorithm("AdaptiveTemperatureGradient");
    setConstantTemperatureGradientduringCooling(3.0);
    setConstantTemperatureGradientduringHeating(3.0);
    setInitialTemperatureGradientduringCooling(2.0);
    setInitialTemperatureGradientduringHeating(2.0);
    setConstantStartTime(2.0);
    setNumberofPreviousDays(3);
  }

  AvailabilityManagerOptimumStart::AvailabilityManagerOptimumStart(std::shared_ptr<detail::AvailabilityManagerOptimumStart_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType AvailabilityManagerOptimumStart::iddObjectType() {
    return IddObjectType::AvailabilityManager_OptimumStart;
  }

  std::vector<std::string> AvailabilityManagerOptimumStart::controlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::AvailabilityManager_OptimumStartFields::ControlType);
  }

  std::vector<std::string> AvailabilityManagerOptimumStart::controlAlgorithmValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::AvailabilityManager_OptimumStartFields::ControlAlgorithm);
  }

  std::string AvailabilityManagerOptimumStart::controlType() const {
    return getImpl<detail::AvailabilityManagerOptimumStart_Impl>()->controlType();
  }

  bool AvailabilityManagerOptimumStart::setControlType(const std::string& controlType) {
    return getImpl<detail::AvailabilityManagerOptimumStart_Impl>()->setControlType(controlType);
  }

  double AvailabilityManagerOptimumStart::maximumValueforOptimumStartTime() const {
    return getImpl<detail::AvailabilityManagerOptimumStart_Impl>()->maximumValueforOptimumStartTime();
  }

  bool AvailabilityManagerOptimumStart::setMaximumValueforOptimumStartTime(double maximumValueforOptimumStartTime) {
    return getImpl<detail::AvailabilityManagerOptimumStart_Impl>()->setMaximumValueforOptimumStartTime(maximumValueforOptimumStartTime);
  }

  std::string AvailabilityManagerOptimumStart::controlAlgorithm() const {
    return getImpl<detail::AvailabilityManagerOptimumStart_Impl>()->controlAlgorithm();
  }

  bool AvailabilityManagerOptimumStart::setControlAlgorithm(const std::string& controlAlgorithm) {
    return getImpl<detail::AvailabilityManagerOptimumStart_Impl>()->setControlAlgorithm(controlAlgorithm);
  }

  double AvailabilityManagerOptimumStart::constantTemperatureGradientduringCooling() const {
    return getImpl<detail::AvailabilityManagerOptimumStart_Impl>()->constantTemperatureGradientduringCooling();
  }

  bool AvailabilityManagerOptimumStart::setConstantTemperatureGradientduringCooling(double constantTemperatureGradientduringCooling) {
    return getImpl<detail::AvailabilityManagerOptimumStart_Impl>()->setConstantTemperatureGradientduringCooling(
      constantTemperatureGradientduringCooling);
  }

  double AvailabilityManagerOptimumStart::constantTemperatureGradientduringHeating() const {
    return getImpl<detail::AvailabilityManagerOptimumStart_Impl>()->constantTemperatureGradientduringHeating();
  }

  bool AvailabilityManagerOptimumStart::setConstantTemperatureGradientduringHeating(double constantTemperatureGradientduringHeating) {
    return getImpl<detail::AvailabilityManagerOptimumStart_Impl>()->setConstantTemperatureGradientduringHeating(
      constantTemperatureGradientduringHeating);
  }

  double AvailabilityManagerOptimumStart::initialTemperatureGradientduringCooling() const {
    return getImpl<detail::AvailabilityManagerOptimumStart_Impl>()->initialTemperatureGradientduringCooling();
  }

  bool AvailabilityManagerOptimumStart::setInitialTemperatureGradientduringCooling(double initialTemperatureGradientduringCooling) {
    return getImpl<detail::AvailabilityManagerOptimumStart_Impl>()->setInitialTemperatureGradientduringCooling(
      initialTemperatureGradientduringCooling);
  }

  double AvailabilityManagerOptimumStart::initialTemperatureGradientduringHeating() const {
    return getImpl<detail::AvailabilityManagerOptimumStart_Impl>()->initialTemperatureGradientduringHeating();
  }

  bool AvailabilityManagerOptimumStart::setInitialTemperatureGradientduringHeating(double initialTemperatureGradientduringHeating) {
    return getImpl<detail::AvailabilityManagerOptimumStart_Impl>()->setInitialTemperatureGradientduringHeating(
      initialTemperatureGradientduringHeating);
  }

  double AvailabilityManagerOptimumStart::constantStartTime() const {
    return getImpl<detail::AvailabilityManagerOptimumStart_Impl>()->constantStartTime();
  }

  bool AvailabilityManagerOptimumStart::setConstantStartTime(double constantStartTime) {
    return getImpl<detail::AvailabilityManagerOptimumStart_Impl>()->setConstantStartTime(constantStartTime);
  }

  int AvailabilityManagerOptimumStart::numberofPreviousDays() const {
    return getImpl<detail::AvailabilityManagerOptimumStart_Impl>()->numberofPreviousDays();
  }

  bool AvailabilityManagerOptimumStart::setNumberofPreviousDays(int numberofPreviousDays) {
    return getImpl<detail::AvailabilityManagerOptimumStart_Impl>()->setNumberofPreviousDays(numberofPreviousDays);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string AvailabilityManagerOptimumStart_Impl::controlType() const {
      const auto value = getString(openstudio::AvailabilityManager_OptimumStartFields::ControlType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AvailabilityManagerOptimumStart_Impl::setControlType(const std::string& controlType) {
      return setString(openstudio::AvailabilityManager_OptimumStartFields::ControlType, controlType);
    }

    double AvailabilityManagerOptimumStart_Impl::maximumValueforOptimumStartTime() const {
      const auto value = getDouble(openstudio::AvailabilityManager_OptimumStartFields::MaximumValueforOptimumStartTime, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AvailabilityManagerOptimumStart_Impl::setMaximumValueforOptimumStartTime(double maximumValueforOptimumStartTime) {
      const bool result =
        setDouble(openstudio::AvailabilityManager_OptimumStartFields::MaximumValueforOptimumStartTime, maximumValueforOptimumStartTime);
      OS_ASSERT(result);
      return result;
    }

    std::string AvailabilityManagerOptimumStart_Impl::controlAlgorithm() const {
      const auto value = getString(openstudio::AvailabilityManager_OptimumStartFields::ControlAlgorithm, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AvailabilityManagerOptimumStart_Impl::setControlAlgorithm(const std::string& controlAlgorithm) {
      return setString(openstudio::AvailabilityManager_OptimumStartFields::ControlAlgorithm, controlAlgorithm);
    }

    double AvailabilityManagerOptimumStart_Impl::constantTemperatureGradientduringCooling() const {
      const auto value = getDouble(openstudio::AvailabilityManager_OptimumStartFields::ConstantTemperatureGradientduringCooling, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AvailabilityManagerOptimumStart_Impl::setConstantTemperatureGradientduringCooling(double constantTemperatureGradientduringCooling) {
      const bool result = setDouble(openstudio::AvailabilityManager_OptimumStartFields::ConstantTemperatureGradientduringCooling,
                                    constantTemperatureGradientduringCooling);
      OS_ASSERT(result);
      return result;
    }

    double AvailabilityManagerOptimumStart_Impl::constantTemperatureGradientduringHeating() const {
      const auto value = getDouble(openstudio::AvailabilityManager_OptimumStartFields::ConstantTemperatureGradientduringHeating, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AvailabilityManagerOptimumStart_Impl::setConstantTemperatureGradientduringHeating(double constantTemperatureGradientduringHeating) {
      const bool result = setDouble(openstudio::AvailabilityManager_OptimumStartFields::ConstantTemperatureGradientduringHeating,
                                    constantTemperatureGradientduringHeating);
      OS_ASSERT(result);
      return result;
    }

    double AvailabilityManagerOptimumStart_Impl::initialTemperatureGradientduringCooling() const {
      const auto value = getDouble(openstudio::AvailabilityManager_OptimumStartFields::InitialTemperatureGradientduringCooling, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AvailabilityManagerOptimumStart_Impl::setInitialTemperatureGradientduringCooling(double initialTemperatureGradientduringCooling) {
      const bool result = setDouble(openstudio::AvailabilityManager_OptimumStartFields::InitialTemperatureGradientduringCooling,
                                    initialTemperatureGradientduringCooling);
      OS_ASSERT(result);
      return result;
    }

    double AvailabilityManagerOptimumStart_Impl::initialTemperatureGradientduringHeating() const {
      const auto value = getDouble(openstudio::AvailabilityManager_OptimumStartFields::InitialTemperatureGradientduringHeating, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AvailabilityManagerOptimumStart_Impl::setInitialTemperatureGradientduringHeating(double initialTemperatureGradientduringHeating) {
      const bool result = setDouble(openstudio::AvailabilityManager_OptimumStartFields::InitialTemperatureGradientduringHeating,
                                    initialTemperatureGradientduringHeating);
      OS_ASSERT(result);
      return result;
    }

    double AvailabilityManagerOptimumStart_Impl::constantStartTime() const {
      const auto value = getDouble(openstudio::AvailabilityManager_OptimumStartFields::ConstantStartTime, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AvailabilityManagerOptimumStart_Impl::setConstantStartTime(double constantStartTime) {
      const bool result = setDouble(openstudio::AvailabilityManager_OptimumStartFields::ConstantStartTime, constantStartTime);
      OS_ASSERT(result);
      return result;
    }

    int AvailabilityManagerOptimumStart_Impl::numberofPreviousDays() const {
      const auto value = getInt(openstudio::AvailabilityManager_OptimumStartFields::NumberofPreviousDays, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AvailabilityManagerOptimumStart_Impl::setNumberofPreviousDays(int numberofPreviousDays) {
      return setInt(openstudio::AvailabilityManager_OptimumStartFields::NumberofPreviousDays, numberofPreviousDays);
    }

    std::vector<std::string> AvailabilityManagerOptimumStart_Impl::controlTypeValues() const {
      return openstudio::epmodel::AvailabilityManagerOptimumStart::controlTypeValues();
    }

    std::vector<std::string> AvailabilityManagerOptimumStart_Impl::controlAlgorithmValues() const {
      return openstudio::epmodel::AvailabilityManagerOptimumStart::controlAlgorithmValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
