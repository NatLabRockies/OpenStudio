/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONECONTROLCONTAMINANTCONTROLLER_IMPL_HPP
#define EPMODEL_ZONECONTROLCONTAMINANTCONTROLLER_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  class Schedule;
  class ThermalZone;

  namespace detail {

    class EPMODEL_API ZoneControlContaminantController_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ZoneControlContaminantController_Impl() override = default;

      boost::optional<openstudio::epmodel::ThermalZone> controlledZone() const;

      boost::optional<openstudio::epmodel::Schedule> carbonDioxideControlAvailabilitySchedule() const;
      bool setCarbonDioxideControlAvailabilitySchedule(openstudio::epmodel::Schedule& schedule);
      void resetCarbonDioxideControlAvailabilitySchedule();

      boost::optional<openstudio::epmodel::Schedule> carbonDioxideSetpointSchedule() const;
      bool setCarbonDioxideSetpointSchedule(openstudio::epmodel::Schedule& schedule);
      void resetCarbonDioxideSetpointSchedule();

      boost::optional<openstudio::epmodel::Schedule> minimumCarbonDioxideConcentrationSchedule() const;
      bool setMinimumCarbonDioxideConcentrationSchedule(openstudio::epmodel::Schedule& schedule);
      void resetMinimumCarbonDioxideConcentrationSchedule();

      boost::optional<openstudio::epmodel::Schedule> genericContaminantControlAvailabilitySchedule() const;
      bool setGenericContaminantControlAvailabilitySchedule(openstudio::epmodel::Schedule& schedule);
      void resetGenericContaminantControlAvailabilitySchedule();

      boost::optional<openstudio::epmodel::Schedule> genericContaminantSetpointSchedule() const;
      bool setGenericContaminantSetpointSchedule(openstudio::epmodel::Schedule& schedule);
      void resetGenericContaminantSetpointSchedule();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
