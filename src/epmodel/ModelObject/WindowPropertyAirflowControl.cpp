/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include "WindowPropertyAirflowControl.hpp"
#include "WindowPropertyAirflowControl_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/WindowProperty_AirflowControl_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  WindowPropertyAirflowControl::WindowPropertyAirflowControl(const Model& model)
    : ModelObject(WindowPropertyAirflowControl::iddObjectType(), model) {}

  WindowPropertyAirflowControl::WindowPropertyAirflowControl(std::shared_ptr<detail::WindowPropertyAirflowControl_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType WindowPropertyAirflowControl::iddObjectType() {
    return IddObjectType::WindowProperty_AirflowControl;
  }

  std::vector<std::string> WindowPropertyAirflowControl::airflowSourceValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::WindowProperty_AirflowControlFields::AirflowSource);
  }

  std::vector<std::string> WindowPropertyAirflowControl::airflowDestinationValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::WindowProperty_AirflowControlFields::AirflowDestination);
  }

  std::vector<std::string> WindowPropertyAirflowControl::airflowControlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::WindowProperty_AirflowControlFields::AirflowControlType);
  }

  std::string WindowPropertyAirflowControl::airflowSource() const {
    return getImpl<detail::WindowPropertyAirflowControl_Impl>()->airflowSource();
  }

  bool WindowPropertyAirflowControl::isAirflowSourceDefaulted() const {
    return getImpl<detail::WindowPropertyAirflowControl_Impl>()->isAirflowSourceDefaulted();
  }

  bool WindowPropertyAirflowControl::setAirflowSource(const std::string& airflowSource) {
    return getImpl<detail::WindowPropertyAirflowControl_Impl>()->setAirflowSource(airflowSource);
  }

  void WindowPropertyAirflowControl::resetAirflowSource() {
    getImpl<detail::WindowPropertyAirflowControl_Impl>()->resetAirflowSource();
  }

  std::string WindowPropertyAirflowControl::airflowDestination() const {
    return getImpl<detail::WindowPropertyAirflowControl_Impl>()->airflowDestination();
  }

  bool WindowPropertyAirflowControl::isAirflowDestinationDefaulted() const {
    return getImpl<detail::WindowPropertyAirflowControl_Impl>()->isAirflowDestinationDefaulted();
  }

  bool WindowPropertyAirflowControl::setAirflowDestination(const std::string& airflowDestination) {
    return getImpl<detail::WindowPropertyAirflowControl_Impl>()->setAirflowDestination(airflowDestination);
  }

  void WindowPropertyAirflowControl::resetAirflowDestination() {
    getImpl<detail::WindowPropertyAirflowControl_Impl>()->resetAirflowDestination();
  }

  double WindowPropertyAirflowControl::maximumFlowRate() const {
    return getImpl<detail::WindowPropertyAirflowControl_Impl>()->maximumFlowRate();
  }

  bool WindowPropertyAirflowControl::isMaximumFlowRateDefaulted() const {
    return getImpl<detail::WindowPropertyAirflowControl_Impl>()->isMaximumFlowRateDefaulted();
  }

  bool WindowPropertyAirflowControl::setMaximumFlowRate(double maximumFlowRate) {
    return getImpl<detail::WindowPropertyAirflowControl_Impl>()->setMaximumFlowRate(maximumFlowRate);
  }

  void WindowPropertyAirflowControl::resetMaximumFlowRate() {
    getImpl<detail::WindowPropertyAirflowControl_Impl>()->resetMaximumFlowRate();
  }

  std::string WindowPropertyAirflowControl::airflowControlType() const {
    return getImpl<detail::WindowPropertyAirflowControl_Impl>()->airflowControlType();
  }

  bool WindowPropertyAirflowControl::isAirflowControlTypeDefaulted() const {
    return getImpl<detail::WindowPropertyAirflowControl_Impl>()->isAirflowControlTypeDefaulted();
  }

  bool WindowPropertyAirflowControl::setAirflowControlType(const std::string& airflowControlType) {
    return getImpl<detail::WindowPropertyAirflowControl_Impl>()->setAirflowControlType(airflowControlType);
  }

  void WindowPropertyAirflowControl::resetAirflowControlType() {
    getImpl<detail::WindowPropertyAirflowControl_Impl>()->resetAirflowControlType();
  }

  bool WindowPropertyAirflowControl::airflowIsScheduled() const {
    return getImpl<detail::WindowPropertyAirflowControl_Impl>()->airflowIsScheduled();
  }

  bool WindowPropertyAirflowControl::isAirflowIsScheduledDefaulted() const {
    return getImpl<detail::WindowPropertyAirflowControl_Impl>()->isAirflowIsScheduledDefaulted();
  }

  bool WindowPropertyAirflowControl::setAirflowIsScheduled(bool airflowIsScheduled) {
    return getImpl<detail::WindowPropertyAirflowControl_Impl>()->setAirflowIsScheduled(airflowIsScheduled);
  }

  void WindowPropertyAirflowControl::resetAirflowIsScheduled() {
    getImpl<detail::WindowPropertyAirflowControl_Impl>()->resetAirflowIsScheduled();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string WindowPropertyAirflowControl_Impl::airflowSource() const {
      const auto value = getString(openstudio::WindowProperty_AirflowControlFields::AirflowSource, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowPropertyAirflowControl_Impl::isAirflowSourceDefaulted() const {
      return isEmpty(openstudio::WindowProperty_AirflowControlFields::AirflowSource);
    }

    bool WindowPropertyAirflowControl_Impl::setAirflowSource(const std::string& airflowSource) {
      return setString(openstudio::WindowProperty_AirflowControlFields::AirflowSource, airflowSource);
    }

    void WindowPropertyAirflowControl_Impl::resetAirflowSource() {
      OS_ASSERT(setString(openstudio::WindowProperty_AirflowControlFields::AirflowSource, ""));
    }

    std::string WindowPropertyAirflowControl_Impl::airflowDestination() const {
      const auto value = getString(openstudio::WindowProperty_AirflowControlFields::AirflowDestination, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowPropertyAirflowControl_Impl::isAirflowDestinationDefaulted() const {
      return isEmpty(openstudio::WindowProperty_AirflowControlFields::AirflowDestination);
    }

    bool WindowPropertyAirflowControl_Impl::setAirflowDestination(const std::string& airflowDestination) {
      return setString(openstudio::WindowProperty_AirflowControlFields::AirflowDestination, airflowDestination);
    }

    void WindowPropertyAirflowControl_Impl::resetAirflowDestination() {
      OS_ASSERT(setString(openstudio::WindowProperty_AirflowControlFields::AirflowDestination, ""));
    }

    double WindowPropertyAirflowControl_Impl::maximumFlowRate() const {
      const auto value = getDouble(openstudio::WindowProperty_AirflowControlFields::MaximumFlowRate, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowPropertyAirflowControl_Impl::isMaximumFlowRateDefaulted() const {
      return isEmpty(openstudio::WindowProperty_AirflowControlFields::MaximumFlowRate);
    }

    bool WindowPropertyAirflowControl_Impl::setMaximumFlowRate(double maximumFlowRate) {
      const bool result = setDouble(openstudio::WindowProperty_AirflowControlFields::MaximumFlowRate, maximumFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void WindowPropertyAirflowControl_Impl::resetMaximumFlowRate() {
      OS_ASSERT(setString(openstudio::WindowProperty_AirflowControlFields::MaximumFlowRate, ""));
    }

    std::string WindowPropertyAirflowControl_Impl::airflowControlType() const {
      const auto value = getString(openstudio::WindowProperty_AirflowControlFields::AirflowControlType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowPropertyAirflowControl_Impl::isAirflowControlTypeDefaulted() const {
      return isEmpty(openstudio::WindowProperty_AirflowControlFields::AirflowControlType);
    }

    bool WindowPropertyAirflowControl_Impl::setAirflowControlType(const std::string& airflowControlType) {
      return setString(openstudio::WindowProperty_AirflowControlFields::AirflowControlType, airflowControlType);
    }

    void WindowPropertyAirflowControl_Impl::resetAirflowControlType() {
      OS_ASSERT(setString(openstudio::WindowProperty_AirflowControlFields::AirflowControlType, ""));
    }

    namespace {

      bool getBooleanFieldValue(const ModelObject_Impl& impl, int fieldIndex) {
        const auto value = impl.getString(fieldIndex, true);
        OS_ASSERT(value);
        return openstudio::istringEqual(*value, "yes");
      }

      bool setBooleanFieldValue(ModelObject_Impl& impl, int fieldIndex, bool value) {
        return impl.setString(fieldIndex, value ? "Yes" : "No");
      }

    }  // namespace

    bool WindowPropertyAirflowControl_Impl::airflowIsScheduled() const {
      return getBooleanFieldValue(*this, openstudio::WindowProperty_AirflowControlFields::AirflowIsScheduled);
    }

    bool WindowPropertyAirflowControl_Impl::isAirflowIsScheduledDefaulted() const {
      return isEmpty(openstudio::WindowProperty_AirflowControlFields::AirflowIsScheduled);
    }

    bool WindowPropertyAirflowControl_Impl::setAirflowIsScheduled(bool airflowIsScheduled) {
      const bool result = setBooleanFieldValue(*this, openstudio::WindowProperty_AirflowControlFields::AirflowIsScheduled, airflowIsScheduled);
      OS_ASSERT(result);
      return result;
    }

    void WindowPropertyAirflowControl_Impl::resetAirflowIsScheduled() {
      OS_ASSERT(setString(openstudio::WindowProperty_AirflowControlFields::AirflowIsScheduled, ""));
    }

    std::vector<std::string> WindowPropertyAirflowControl_Impl::airflowSourceValues() const {
      return openstudio::epmodel::WindowPropertyAirflowControl::airflowSourceValues();
    }

    std::vector<std::string> WindowPropertyAirflowControl_Impl::airflowDestinationValues() const {
      return openstudio::epmodel::WindowPropertyAirflowControl::airflowDestinationValues();
    }

    std::vector<std::string> WindowPropertyAirflowControl_Impl::airflowControlTypeValues() const {
      return openstudio::epmodel::WindowPropertyAirflowControl::airflowControlTypeValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
