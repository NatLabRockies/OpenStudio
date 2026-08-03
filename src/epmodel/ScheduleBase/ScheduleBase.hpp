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

  /** ScheduleBase is a ResourceObject that serves as a base class for Schedule and ScheduleDay,
   *  that is, objects with ScheduleTypeLimits. This class provides getters and setters for
   *  ScheduleTypeLimits. Note that while users can explicitly set their own ScheduleTypeLimits,
   *  we recommend using the \link ScheduleTypeRegistry ScheduleTypeRegistry\endlink and
   *  related non-member functions, or letting user \link ModelObject ModelObjects\endlink set
   *  this field, instead. */
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

    /** Returns true if scheduleTypeLimits is compatible with this object and is actually set.
     *  The operation will fail if the Schedule or ScheduleDay is in use in a way that restricts
     *  the allowable ScheduleTypeLimits and the new value (scheduleTypeLimits) is incompatible
     *  with that use. For instance, if a Schedule is used with a Lights object, then only
     *  properly configured fractional ScheduleTypeLimits will succeed. ScheduleDay objects used
     *  in a ScheduleRuleset or a ScheduleRule are restricted to use ScheduleTypeLimits compatible
     *  with those of their (ScheduleRuleset or ScheduleRule) parent. */
    bool setScheduleTypeLimits(const ScheduleTypeLimits& scheduleTypeLimits);

    /** Returns true if the scheduleTypeLimits() of this object is successfully cleared. Will fail
     *  if this object is being used by an object that expects it to have a ScheduleTypeLimits. */
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
