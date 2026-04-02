/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ScheduleCompact.hpp"
#include "ScheduleCompact_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idf/IdfExtensibleGroup.hpp>

#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  ScheduleCompact::ScheduleCompact(const Model& model) : Schedule(ScheduleCompact::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::ScheduleCompact_Impl>());
  }

  ScheduleCompact::ScheduleCompact(const Model& model, double constantValue) : Schedule(ScheduleCompact::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::ScheduleCompact_Impl>());
    OS_ASSERT(setToConstantValue(constantValue));
  }

  ScheduleCompact::ScheduleCompact(std::shared_ptr<detail::ScheduleCompact_Impl> impl) : Schedule(std::move(impl)) {}

  IddObjectType ScheduleCompact::iddObjectType() {
    return IddObjectType::Schedule_Compact;
  }

  // Constant value scalar accessors
  bool ScheduleCompact::setToConstantValue(double value) {
    return getImpl<detail::ScheduleCompact_Impl>()->setToConstantValue(value);
  }

  bool ScheduleCompact::isConstantValue() const {
    return getImpl<detail::ScheduleCompact_Impl>()->isConstantValue();
  }

  boost::optional<double> ScheduleCompact::constantValue() const {
    return getImpl<detail::ScheduleCompact_Impl>()->constantValue();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    bool ScheduleCompact_Impl::setToConstantValue(double value) {
      auto scheduleCompact = getObject<openstudio::epmodel::ScheduleCompact>();
      scheduleCompact.clearExtensibleGroups();

      std::vector<std::string> fields(1);

      fields[0] = "Through: 12/31";
      OS_ASSERT(!scheduleCompact.pushExtensibleGroup(fields).empty());

      fields[0] = "For: AllDays";
      OS_ASSERT(!scheduleCompact.pushExtensibleGroup(fields).empty());

      fields[0] = "Until: 24:00";
      OS_ASSERT(!scheduleCompact.pushExtensibleGroup(fields).empty());

      fields[0] = "";
      auto valueGroup = scheduleCompact.pushExtensibleGroup(fields);
      OS_ASSERT(!valueGroup.empty());

      const bool result = valueGroup.setDouble(0u, value);
      OS_ASSERT(result);
      return result;
    }

    bool ScheduleCompact_Impl::isConstantValue() const {
      auto scheduleCompact = getObject<openstudio::epmodel::ScheduleCompact>();
      const auto scheduleData = scheduleCompact.extensibleGroups();
      if (scheduleData.size() != 4u) {
        return false;
      }
      return scheduleData[3].getDouble(0u).has_value();
    }

    boost::optional<double> ScheduleCompact_Impl::constantValue() const {
      auto scheduleCompact = getObject<openstudio::epmodel::ScheduleCompact>();
      const auto scheduleData = scheduleCompact.extensibleGroups();
      if (scheduleData.size() != 4u) {
        return boost::none;
      }
      return scheduleData[3].getDouble(0u);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
