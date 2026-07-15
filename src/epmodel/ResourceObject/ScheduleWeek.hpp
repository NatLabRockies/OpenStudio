/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SCHEDULEWEEK_HPP
#define EPMODEL_SCHEDULEWEEK_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ScheduleWeek_Impl;
  }

  class EPMODEL_API ScheduleWeek : public ModelObject
  {
   public:
    explicit ScheduleWeek(const Model& model);

    virtual ~ScheduleWeek() override = default;
    ScheduleWeek(const ScheduleWeek& other) = default;
    ScheduleWeek(ScheduleWeek&& other) = default;
    ScheduleWeek& operator=(const ScheduleWeek&) = default;
    ScheduleWeek& operator=(ScheduleWeek&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Preserves openstudio::model counterpart naming (`ScheduleWeek`).
    // - Field Mapping: Relationship fields (Sunday..CustomDay2 schedule day links) map to EnergyPlus Schedule:Week:Daily targets and are excluded from scalar scaffold APIs.
    // - ForwardTranslator evidence: `ForwardTranslateScheduleWeek.cpp` maps counterpart schedule-day APIs to Schedule_Week_DailyFields::*Schedule_DayName fields.
    // - Field Mapping: Name remains available through inherited ModelObject scalar accessors.
    // - TODO(parity): Add non-scalar schedule-day relationship methods in a dedicated parity pass.

   protected:
    using ImplType = detail::ScheduleWeek_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ScheduleWeek(std::shared_ptr<detail::ScheduleWeek_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
