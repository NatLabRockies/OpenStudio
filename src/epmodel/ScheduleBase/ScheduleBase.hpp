/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SCHEDULEBASE_HPP
#define EPMODEL_SCHEDULEBASE_HPP

#include "EPModelAPI.hpp"
#include "ResourceObject/ResourceObject.hpp"

#include <boost/optional.hpp>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;
  class ScheduleTypeLimits;

  namespace detail {
    class ScheduleBase_Impl;
  }

  /** \brief Provides the shared schedule type-limits relationship.
   *
   * \par EnergyPlus object
   * This class has no single EnergyPlus object. It is the base for schedule
   * objects that carry a <code>Schedule Type Limits Name</code> field,
   * including \epobject{group-schedules.html#scheduledayinterval,Schedule:Day:Interval} and concrete objects derived
   * from <code>Schedule</code>.
   *
   * \par Important behavior
   * <code>setScheduleTypeLimits()</code> accepts a limits object from the same
   * model and writes the object-list relationship. <code>ensureNoLeapDays()</code>
   * delegates to the concrete schedule type; interval-based schedule days have
   * no date fields to change.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::ScheduleBase</code>. EPModel provides the same
   * public methods. Its schedule-type-limits setter does not reproduce Model's
   * use-based compatibility checks; it checks model ownership and the IDD
   * relationship instead.
   *
   * \par Known limitations
   * EPModel does not validate schedule values against the selected limits when
   * the relationship is set.
   */
  class EPMODEL_API ScheduleBase : public ResourceObject
  {
   public:
    /** @name Constructors and Destructors */
    //@{
    virtual ~ScheduleBase() override = default;
    ScheduleBase(const ScheduleBase& other) = default;
    ScheduleBase(ScheduleBase&& other) = default;
    ScheduleBase& operator=(const ScheduleBase&) = default;
    ScheduleBase& operator=(ScheduleBase&&) = default;

    //@}
    /** @name Getters */
    //@{

    /** Returns the ScheduleTypeLimits of this object, if set. */
    boost::optional<ScheduleTypeLimits> scheduleTypeLimits() const;

    //@}
    /** @name Setters */
    //@{

    /** Returns true if the limits object belongs to this model and the relationship is set. */
    bool setScheduleTypeLimits(const ScheduleTypeLimits& scheduleTypeLimits);

    /** Returns true if the schedule type-limits relationship is cleared. */
    bool resetScheduleTypeLimits();

    // ensure that this object does not contain the date 2/29
    void ensureNoLeapDays();

   protected:
    /// @cond
    ScheduleBase(IddObjectType type, const Model& model);
    using ImplType = detail::ScheduleBase_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ScheduleBase(std::shared_ptr<detail::ScheduleBase_Impl> impl);
    /// @endcond
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
