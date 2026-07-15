/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AVAILABILITYMANAGERSCHEDULEDON_IMPL_HPP
#define EPMODEL_AVAILABILITYMANAGERSCHEDULEDON_IMPL_HPP

#include "AvailabilityManager/AvailabilityManager_Impl.hpp"

namespace openstudio {
namespace epmodel {

  class Schedule;

  namespace detail {

    class EPMODEL_API AvailabilityManagerScheduledOn_Impl : public AvailabilityManager_Impl
    {
     public:
      using AvailabilityManager_Impl::AvailabilityManager_Impl;
      virtual ~AvailabilityManagerScheduledOn_Impl() override = default;

      openstudio::epmodel::Schedule schedule() const;
      bool setSchedule(openstudio::epmodel::Schedule& schedule);
      void doCanonicalize(LoadContext& context) override;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
