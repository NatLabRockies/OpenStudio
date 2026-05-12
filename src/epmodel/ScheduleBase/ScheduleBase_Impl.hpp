/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SCHEDULEBASE_IMPL_HPP
#define EPMODEL_SCHEDULEBASE_IMPL_HPP

#include "EPModelAPI.hpp"
#include "ResourceObject/ResourceObject_Impl.hpp"

#include <boost/optional.hpp>

namespace openstudio {
namespace epmodel {

  class ModelObject;
  class ScheduleTypeLimits;

  namespace detail {

    /** ScheduleBase_Impl is a ResourceObject_Impl that is the implementation class for ScheduleBase.*/
    class EPMODEL_API ScheduleBase_Impl : public ResourceObject_Impl
    {
     public:
      using ResourceObject_Impl::ResourceObject_Impl;
      virtual ~ScheduleBase_Impl() override = default;

      boost::optional<ScheduleTypeLimits> scheduleTypeLimits() const;
      bool setScheduleTypeLimits(const ScheduleTypeLimits& scheduleTypeLimits);
      bool resetScheduleTypeLimits();

      virtual std::vector<double> values() const = 0;

      // ensure that this object does not contain the date 2/29
      virtual void ensureNoLeapDays() = 0;

     protected:
      virtual boost::optional<unsigned> scheduleTypeLimitsFieldIndex() const = 0;

      virtual bool candidateIsCompatibleWithCurrentUse(const ScheduleTypeLimits& candidate) const = 0;

      virtual bool okToResetScheduleTypeLimits() const = 0;

      bool valuesAreWithinBounds() const;

     private:
      REGISTER_LOGGER("openstudio.epmodel.ScheduleBase");
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
