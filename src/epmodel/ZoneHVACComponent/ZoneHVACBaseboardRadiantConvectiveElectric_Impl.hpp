/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACBASEBOARDRADIANTCONVECTIVEELECTRIC_IMPL_HPP
#define EPMODEL_ZONEHVACBASEBOARDRADIANTCONVECTIVEELECTRIC_IMPL_HPP

#include "ZoneHVACComponent/ZoneHVACComponent_Impl.hpp"

#include <string>

namespace openstudio {
namespace epmodel {

  class Schedule;

  namespace detail {

    class EPMODEL_API ZoneHVACBaseboardRadiantConvectiveElectric_Impl : public ZoneHVACComponent_Impl
    {
     public:
      using ZoneHVACComponent_Impl::ZoneHVACComponent_Impl;
      virtual ~ZoneHVACBaseboardRadiantConvectiveElectric_Impl() override = default;

      Schedule availabilitySchedule() const;
      bool setAvailabilitySchedule(Schedule& schedule);

      std::string heatingDesignCapacityMethod() const;
      bool setHeatingDesignCapacityMethod(const std::string& heatingDesignCapacityMethod);

      boost::optional<double> heatingDesignCapacity() const;
      bool isHeatingDesignCapacityAutosized() const;
      bool setHeatingDesignCapacity(double heatingDesignCapacity);
      void autosizeHeatingDesignCapacity();
      boost::optional<double> autosizedHeatingDesignCapacity() const;

      double heatingDesignCapacityPerFloorArea() const;
      bool setHeatingDesignCapacityPerFloorArea(double heatingDesignCapacityPerFloorArea);

      double fractionofAutosizedHeatingDesignCapacity() const;
      bool setFractionofAutosizedHeatingDesignCapacity(double fractionofAutosizedHeatingDesignCapacity);

      double efficiency() const;
      bool setEfficiency(double efficiency);

      double fractionRadiant() const;
      bool setFractionRadiant(double fractionRadiant);

      double fractionofRadiantEnergyIncidentonPeople() const;
      bool setFractionofRadiantEnergyIncidentonPeople(double fractionofRadiantEnergyIncidentonPeople);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
