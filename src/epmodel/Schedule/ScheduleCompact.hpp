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

  /** \brief Represents a compact schedule made from EnergyPlus extensible rows.
   *
   * \par EnergyPlus object
   * \epobject{group-schedules.html#schedulecompact,Schedule:Compact}
   *
   * \par Important behavior
   * <code>setToConstantValue()</code> replaces all extensible rows with the
   * EnergyPlus sequence <code>Through: 12/31</code>, <code>For: AllDays</code>,
   * <code>Until: 24:00</code>, and the supplied value. The constant-value
   * queries return a value when there are four rows and the final row contains
   * a numeric value; they do not validate the text labels in the first rows.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::ScheduleCompact</code>. No known public API
   * differences.
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
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
