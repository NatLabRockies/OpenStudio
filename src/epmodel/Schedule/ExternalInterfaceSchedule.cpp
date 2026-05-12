/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ExternalInterfaceSchedule.hpp"
#include "ExternalInterfaceSchedule_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/ExternalInterface_Schedule_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  ExternalInterfaceSchedule::ExternalInterfaceSchedule(const Model& model, double initialValue)
    : Schedule(ExternalInterfaceSchedule::iddObjectType(), model) {
    OS_ASSERT(setInitialValue(initialValue));
  }

  ExternalInterfaceSchedule::ExternalInterfaceSchedule(const Model& model) : Schedule(ExternalInterfaceSchedule::iddObjectType(), model) {
    OS_ASSERT(setInitialValue(0.0));
  }

  ExternalInterfaceSchedule::ExternalInterfaceSchedule(std::shared_ptr<detail::ExternalInterfaceSchedule_Impl> impl) : Schedule(std::move(impl)) {}

  IddObjectType ExternalInterfaceSchedule::iddObjectType() {
    return IddObjectType::ExternalInterface_Schedule;
  }

  // Initial Value accessors
  double ExternalInterfaceSchedule::initialValue() const {
    return getImpl<detail::ExternalInterfaceSchedule_Impl>()->initialValue();
  }

  bool ExternalInterfaceSchedule::setInitialValue(double initialValue) {
    return getImpl<detail::ExternalInterfaceSchedule_Impl>()->setInitialValue(initialValue);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    unsigned ExternalInterfaceSchedule_Impl::scheduleTypeLimitsFieldIndex() const {
      return openstudio::ExternalInterface_ScheduleFields::ScheduleTypeLimitsName;
    }

    double ExternalInterfaceSchedule_Impl::initialValue() const {
      const auto value = getDouble(openstudio::ExternalInterface_ScheduleFields::InitialValue, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ExternalInterfaceSchedule_Impl::setInitialValue(double initialValue) {
      const bool result = setDouble(openstudio::ExternalInterface_ScheduleFields::InitialValue, initialValue);
      OS_ASSERT(result);
      return result;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
