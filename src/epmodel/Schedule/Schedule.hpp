/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SCHEDULE_HPP
#define EPMODEL_SCHEDULE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"
#include "ResourceObject/ScheduleTypeLimits.hpp"

#include <boost/optional.hpp>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class Schedule_Impl;
  }

  class EPMODEL_API Schedule : public ModelObject
  {
   public:
    virtual ~Schedule() override = default;
    Schedule(const Schedule& other) = default;
    Schedule(Schedule&& other) = default;
    Schedule& operator=(const Schedule&) = default;
    Schedule& operator=(Schedule&&) = default;

    boost::optional<ScheduleTypeLimits> scheduleTypeLimits() const;
    bool setScheduleTypeLimits(const ScheduleTypeLimits& scheduleTypeLimits);
    bool resetScheduleTypeLimits();

   protected:
    using ImplType = detail::Schedule_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit Schedule(std::shared_ptr<detail::Schedule_Impl> impl);
    Schedule(IddObjectType type, const Model& model);
  };

  using OptionalSchedule = boost::optional<Schedule>;
  using ScheduleVector = std::vector<Schedule>;

}  // namespace epmodel
}  // namespace openstudio

#endif
