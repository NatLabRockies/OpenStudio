/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ScheduleDayList.hpp"
#include "ScheduleDayList_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/Schedule_Day_List_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  ScheduleDayList::ScheduleDayList(const Model& model) : ModelObject(ScheduleDayList::iddObjectType(), model) {}

  ScheduleDayList::ScheduleDayList(std::shared_ptr<detail::ScheduleDayList_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType ScheduleDayList::iddObjectType() {
    return IddObjectType::Schedule_Day_List;
  }

  std::vector<std::string> ScheduleDayList::interpolatetoTimestepValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Schedule_Day_ListFields::InterpolatetoTimestep);
  }

  std::string ScheduleDayList::interpolatetoTimestep() const {
    return getImpl<detail::ScheduleDayList_Impl>()->interpolatetoTimestep();
  }

  bool ScheduleDayList::isInterpolatetoTimestepDefaulted() const {
    return getImpl<detail::ScheduleDayList_Impl>()->isInterpolatetoTimestepDefaulted();
  }

  bool ScheduleDayList::setInterpolatetoTimestep(const std::string& interpolatetoTimestep) {
    return getImpl<detail::ScheduleDayList_Impl>()->setInterpolatetoTimestep(interpolatetoTimestep);
  }

  void ScheduleDayList::resetInterpolatetoTimestep() {
    getImpl<detail::ScheduleDayList_Impl>()->resetInterpolatetoTimestep();
  }

  boost::optional<int> ScheduleDayList::minutesperItem() const {
    return getImpl<detail::ScheduleDayList_Impl>()->minutesperItem();
  }

  bool ScheduleDayList::setMinutesperItem(int minutesperItem) {
    return getImpl<detail::ScheduleDayList_Impl>()->setMinutesperItem(minutesperItem);
  }

  void ScheduleDayList::resetMinutesperItem() {
    getImpl<detail::ScheduleDayList_Impl>()->resetMinutesperItem();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string ScheduleDayList_Impl::interpolatetoTimestep() const {
      const auto value = getString(openstudio::Schedule_Day_ListFields::InterpolatetoTimestep, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ScheduleDayList_Impl::isInterpolatetoTimestepDefaulted() const {
      return isEmpty(openstudio::Schedule_Day_ListFields::InterpolatetoTimestep);
    }

    bool ScheduleDayList_Impl::setInterpolatetoTimestep(const std::string& interpolatetoTimestep) {
      return setString(openstudio::Schedule_Day_ListFields::InterpolatetoTimestep, interpolatetoTimestep);
    }

    void ScheduleDayList_Impl::resetInterpolatetoTimestep() {
      OS_ASSERT(setString(openstudio::Schedule_Day_ListFields::InterpolatetoTimestep, ""));
    }

    boost::optional<int> ScheduleDayList_Impl::minutesperItem() const {
      return getInt(openstudio::Schedule_Day_ListFields::MinutesperItem, true);
    }

    bool ScheduleDayList_Impl::setMinutesperItem(int minutesperItem) {
      return setInt(openstudio::Schedule_Day_ListFields::MinutesperItem, minutesperItem);
    }

    void ScheduleDayList_Impl::resetMinutesperItem() {
      OS_ASSERT(setString(openstudio::Schedule_Day_ListFields::MinutesperItem, ""));
    }

    std::vector<std::string> ScheduleDayList_Impl::interpolatetoTimestepValues() const {
      return openstudio::epmodel::ScheduleDayList::interpolatetoTimestepValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
