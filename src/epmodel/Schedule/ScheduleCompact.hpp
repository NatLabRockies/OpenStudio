/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SCHEDULECOMPACT_HPP
#define EPMODEL_SCHEDULECOMPACT_HPP

#include "EPModelAPI.hpp"
#include "Schedule/Schedule.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ScheduleCompact_Impl;
  }

  class EPMODEL_API ScheduleCompact : public Schedule
  {
   public:
    explicit ScheduleCompact(const Model& model);
    ScheduleCompact(const Model& model, double constantValue);

    virtual ~ScheduleCompact() override = default;
    ScheduleCompact(const ScheduleCompact& other) = default;
    ScheduleCompact(ScheduleCompact&& other) = default;
    ScheduleCompact& operator=(const ScheduleCompact&) = default;
    ScheduleCompact& operator=(ScheduleCompact&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model::ScheduleCompact scalar API names/signatures where mappable in epmodel.
    // - Field Mapping: setToConstantValue/isConstantValue/constantValue map to Schedule:Compact extensible rows
    //   ("Through: 12/31", "For: AllDays", "Until: 24:00", <numeric value>).
    // - Field Mapping: scheduleTypeLimits is relationship-like (Schedule Type Limits Name object-list target) and excluded.
    // - ForwardTranslator evidence: ForwardTranslateScheduleCompact.cpp forwards/extensible group schedule data directly.
    // - TODO(parity): Add non-scalar schedule data editing APIs incrementally without changing preserved scalar signatures.
    /** @name Constant value scalar accessors */
    //@{
    bool setToConstantValue(double value);
    bool isConstantValue() const;
    boost::optional<double> constantValue() const;
    //@}

   protected:
    using ImplType = detail::ScheduleCompact_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ScheduleCompact(std::shared_ptr<detail::ScheduleCompact_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
