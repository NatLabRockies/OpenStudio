/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONECONTROLHUMIDISTAT_IMPL_HPP
#define EPMODEL_ZONECONTROLHUMIDISTAT_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  class Schedule;
  class ThermalZone;

  namespace detail {

    class EPMODEL_API ZoneControlHumidistat_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ZoneControlHumidistat_Impl() override = default;

      boost::optional<openstudio::epmodel::ThermalZone> controlledZone() const;

      boost::optional<openstudio::epmodel::Schedule> humidifyingRelativeHumiditySetpointSchedule() const;
      boost::optional<openstudio::epmodel::Schedule> dehumidifyingRelativeHumiditySetpointSchedule() const;

      bool setHumidifyingRelativeHumiditySetpointSchedule(openstudio::epmodel::Schedule& schedule);
      bool setDehumidifyingRelativeHumiditySetpointSchedule(openstudio::epmodel::Schedule& schedule);

      void resetHumidifyingRelativeHumiditySetpointSchedule();
      void resetDehumidifyingRelativeHumiditySetpointSchedule();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
