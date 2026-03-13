/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "RunPeriodControlDaylightSavingTime.hpp"
#include "RunPeriodControlDaylightSavingTime_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/RunPeriodControl_DaylightSavingTime_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  RunPeriodControlDaylightSavingTime::RunPeriodControlDaylightSavingTime(const Model& model)
    : ModelObject(RunPeriodControlDaylightSavingTime::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::RunPeriodControlDaylightSavingTime_Impl>());
    OS_ASSERT(setStartDate("2nd Sunday in March"));
    OS_ASSERT(setEndDate("1st Sunday in November"));
  }

  RunPeriodControlDaylightSavingTime::RunPeriodControlDaylightSavingTime(std::shared_ptr<detail::RunPeriodControlDaylightSavingTime_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType RunPeriodControlDaylightSavingTime::iddObjectType() {
    return IddObjectType::RunPeriodControl_DaylightSavingTime;
  }

  std::string RunPeriodControlDaylightSavingTime::startDate() const {
    return getImpl<detail::RunPeriodControlDaylightSavingTime_Impl>()->startDate();
  }

  bool RunPeriodControlDaylightSavingTime::setStartDate(const std::string& startDate) {
    return getImpl<detail::RunPeriodControlDaylightSavingTime_Impl>()->setStartDate(startDate);
  }

  std::string RunPeriodControlDaylightSavingTime::endDate() const {
    return getImpl<detail::RunPeriodControlDaylightSavingTime_Impl>()->endDate();
  }

  bool RunPeriodControlDaylightSavingTime::setEndDate(const std::string& endDate) {
    return getImpl<detail::RunPeriodControlDaylightSavingTime_Impl>()->setEndDate(endDate);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string RunPeriodControlDaylightSavingTime_Impl::startDate() const {
      const auto value = getString(openstudio::RunPeriodControl_DaylightSavingTimeFields::StartDate, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RunPeriodControlDaylightSavingTime_Impl::setStartDate(const std::string& startDate) {
      const bool result = setString(openstudio::RunPeriodControl_DaylightSavingTimeFields::StartDate, startDate);
      OS_ASSERT(result);
      return result;
    }

    std::string RunPeriodControlDaylightSavingTime_Impl::endDate() const {
      const auto value = getString(openstudio::RunPeriodControl_DaylightSavingTimeFields::EndDate, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RunPeriodControlDaylightSavingTime_Impl::setEndDate(const std::string& endDate) {
      const bool result = setString(openstudio::RunPeriodControl_DaylightSavingTimeFields::EndDate, endDate);
      OS_ASSERT(result);
      return result;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
