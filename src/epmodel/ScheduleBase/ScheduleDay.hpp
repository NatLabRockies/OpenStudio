/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SCHEDULEDAY_HPP
#define EPMODEL_SCHEDULEDAY_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class ScheduleDay_Impl;
}

class EPMODEL_API ScheduleDay : public ModelObject
{
 public:
  explicit ScheduleDay(const Model& model);

  virtual ~ScheduleDay() override = default;
  ScheduleDay(const ScheduleDay& other) = default;
  ScheduleDay(ScheduleDay&& other) = default;
  ScheduleDay& operator=(const ScheduleDay&) = default;
  ScheduleDay& operator=(ScheduleDay&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> interpolatetoTimestepValues();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model::ScheduleDay scalar accessor names/signatures where mappable in epmodel.
  // - Field Mapping: interpolatetoTimestep/setInterpolatetoTimestep map to EnergyPlus Schedule:Day:Interval
  //   field Interpolate to Timestep.
  // - Field Mapping: Schedule Type Limits Name is an object-list relationship field and is intentionally excluded.
  // - Field Mapping: Time and Value Until Time live in extensible groups and are intentionally excluded from scalar accessors.
  // - ForwardTranslator evidence: ForwardTranslateScheduleDay.cpp writes modelObject.interpolatetoTimestep() to
  //   Schedule_Day_IntervalFields::InterpolatetoTimestep.
  // - TODO(parity): Add schedule day extensible APIs (times/values/addValue/removeValue) and relationship APIs incrementally.
  std::string interpolatetoTimestep() const;
  bool isInterpolatetoTimestepDefaulted() const;
  bool setInterpolatetoTimestep(const std::string& interpolatetoTimestep);
  void resetInterpolatetoTimestep();

 protected:
  using ImplType = detail::ScheduleDay_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit ScheduleDay(std::shared_ptr<detail::ScheduleDay_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
