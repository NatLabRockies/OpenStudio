/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SCHEDULEYEAR_HPP
#define EPMODEL_SCHEDULEYEAR_HPP

#include "EPModelAPI.hpp"
#include "Schedule/Schedule.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ScheduleYear_Impl;
  }

  class EPMODEL_API ScheduleYear : public Schedule
  {
   public:
    explicit ScheduleYear(const Model& model);

    virtual ~ScheduleYear() override = default;
    ScheduleYear(const ScheduleYear& other) = default;
    ScheduleYear(ScheduleYear&& other) = default;
    ScheduleYear& operator=(const ScheduleYear&) = default;
    ScheduleYear& operator=(ScheduleYear&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - Status: Scalar Parity. The typed wrapper now preserves the literal EnergyPlus object identity for `Schedule:Year`, but the canonical `ScheduleYear` relationship APIs are still missing.
    // - Canonical Counterpart: openstudio::model::ScheduleYear.
    // - Implemented Parity: Inherited scalar accessors remain available, including Name and Schedule Type Limits linkage.
    // - Documented Delta: Week/date relationship APIs are not yet exposed, and canonical `ScheduleRuleset` remains separate future work.
    // - Field/Storage Mapping: The wrapper maps directly to EnergyPlus `Schedule:Year`; extensible WeekSchedule/Start/End groups remain outside the current scalar scaffold.
    // - Evidence: `src/model/ScheduleYear.hpp` defines the canonical `ScheduleYear` wrapper while EnergyPlus persists the underlying object as `Schedule:Year`.
    // - Remaining Parity Work: Add the `ScheduleYear` week/date relationship APIs. Decide separately how epmodel should model canonical `ScheduleRuleset`.

   protected:
    using ImplType = detail::ScheduleYear_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ScheduleYear(std::shared_ptr<detail::ScheduleYear_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
