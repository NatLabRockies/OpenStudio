/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ScheduleConstant.hpp"
#include "ScheduleConstant_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Schedule_Constant_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  ScheduleConstant::ScheduleConstant(const Model& model) : Schedule(ScheduleConstant::iddObjectType(), model) {
    OS_ASSERT(setValue(0.0));
  }

  ScheduleConstant::ScheduleConstant(std::shared_ptr<detail::ScheduleConstant_Impl> impl) : Schedule(std::move(impl)) {}

  IddObjectType ScheduleConstant::iddObjectType() {
    return IddObjectType::Schedule_Constant;
  }

  double ScheduleConstant::value() const {
    return getImpl<detail::ScheduleConstant_Impl>()->value();
  }

  bool ScheduleConstant::setValue(double value) {
    return getImpl<detail::ScheduleConstant_Impl>()->setValue(value);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<unsigned> ScheduleConstant_Impl::scheduleTypeLimitsFieldIndex() const {
      return openstudio::Schedule_ConstantFields::ScheduleTypeLimitsName;
    }

    double ScheduleConstant_Impl::value() const {
      const auto value = getDouble(openstudio::Schedule_ConstantFields::HourlyValue, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ScheduleConstant_Impl::setValue(double value) {
      const bool result = setDouble(openstudio::Schedule_ConstantFields::HourlyValue, value);
      OS_ASSERT(result);
      return result;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
