/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"

#include "Model.hpp"
#include "ResourceObject/ScheduleTypeLimits.hpp"
#include "ResourceObject/ScheduleTypeLimits_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Schedule_Compact_FieldEnums.hxx>
#include <utilities/idd/Schedule_Constant_FieldEnums.hxx>
#include <utilities/idd/Schedule_File_FieldEnums.hxx>
#include <utilities/idd/Schedule_Year_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

Schedule::Schedule(IddObjectType type, const Model& model) : ModelObject(type, model) {
  OS_ASSERT(getImpl<detail::Schedule_Impl>());
}

Schedule::Schedule(std::shared_ptr<detail::Schedule_Impl> impl) : ModelObject(std::move(impl)) {
  OS_ASSERT(getImpl<detail::Schedule_Impl>());
}

boost::optional<ScheduleTypeLimits> Schedule::scheduleTypeLimits() const {
  return getImpl<detail::Schedule_Impl>()->scheduleTypeLimits();
}

bool Schedule::setScheduleTypeLimits(const ScheduleTypeLimits& scheduleTypeLimits) {
  return getImpl<detail::Schedule_Impl>()->setScheduleTypeLimits(scheduleTypeLimits);
}

bool Schedule::resetScheduleTypeLimits() {
  return getImpl<detail::Schedule_Impl>()->resetScheduleTypeLimits();
}

namespace detail {

boost::optional<unsigned> Schedule_Impl::scheduleTypeLimitsFieldIndex() const {
  switch (iddObject().type().value()) {
    case IddObjectType::Schedule_Constant:
      return openstudio::Schedule_ConstantFields::ScheduleTypeLimitsName;
    case IddObjectType::Schedule_Compact:
      return openstudio::Schedule_CompactFields::ScheduleTypeLimitsName;
    case IddObjectType::Schedule_Year:
      return openstudio::Schedule_YearFields::ScheduleTypeLimitsName;
    case IddObjectType::Schedule_File:
      return openstudio::Schedule_FileFields::ScheduleTypeLimitsName;
    default:
      return boost::none;
  }
}

boost::optional<openstudio::epmodel::ScheduleTypeLimits> Schedule_Impl::scheduleTypeLimits() const {
  const auto fieldIndex = scheduleTypeLimitsFieldIndex();
  if (!fieldIndex) {
    return boost::none;
  }

  return getObject<openstudio::epmodel::ModelObject>().getModelObjectTarget<openstudio::epmodel::ScheduleTypeLimits>(*fieldIndex);
}

bool Schedule_Impl::setScheduleTypeLimits(const openstudio::epmodel::ScheduleTypeLimits& scheduleTypeLimits) {
  const auto fieldIndex = scheduleTypeLimitsFieldIndex();
  if (!fieldIndex || (scheduleTypeLimits.model() != model())) {
    return false;
  }

  return setPointer(*fieldIndex, scheduleTypeLimits.handle(), false);
}

bool Schedule_Impl::resetScheduleTypeLimits() {
  const auto fieldIndex = scheduleTypeLimitsFieldIndex();
  if (!fieldIndex) {
    return false;
  }

  return setString(*fieldIndex, "", false);
}

}  // namespace detail

}  // namespace epmodel
}  // namespace openstudio
