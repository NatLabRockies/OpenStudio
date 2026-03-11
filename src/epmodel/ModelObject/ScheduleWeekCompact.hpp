/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SCHEDULEWEEKCOMPACT_HPP
#define EPMODEL_SCHEDULEWEEKCOMPACT_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class ScheduleWeekCompact_Impl;
}

class EPMODEL_API ScheduleWeekCompact : public ModelObject
{
 public:
  explicit ScheduleWeekCompact(const Model& model);

  virtual ~ScheduleWeekCompact() override = default;
  ScheduleWeekCompact(const ScheduleWeekCompact& other) = default;
  ScheduleWeekCompact(ScheduleWeekCompact&& other) = default;
  ScheduleWeekCompact& operator=(const ScheduleWeekCompact&) = default;
  ScheduleWeekCompact& operator=(ScheduleWeekCompact&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: This no-counterpart type keeps IDD-derived class/API naming.
  // - Field Mapping: Name remains available through base ModelObject scalar API.
  // - Field Mapping: Day Type List / Schedule Day Name extensible fields are relationship-like links and excluded from scalar accessors.
  // - TODO(parity): Add typed extensible relationship APIs incrementally after scalar saturation.

 protected:
  using ImplType = detail::ScheduleWeekCompact_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit ScheduleWeekCompact(std::shared_ptr<detail::ScheduleWeekCompact_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
