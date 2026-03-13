/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AVAILABILITYMANAGERNIGHTCYCLE_IMPL_HPP
#define EPMODEL_AVAILABILITYMANAGERNIGHTCYCLE_IMPL_HPP

#include "AvailabilityManager/AvailabilityManager_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  class AirLoopHVAC;

  namespace detail {

    class EPMODEL_API AvailabilityManagerNightCycle_Impl : public AvailabilityManager_Impl
    {
     public:
      using AvailabilityManager_Impl::AvailabilityManager_Impl;
      virtual ~AvailabilityManagerNightCycle_Impl() override = default;

      std::vector<std::string> controlTypeValues() const;
      std::vector<std::string> cyclingRunTimeControlTypeValues() const;

      boost::optional<openstudio::epmodel::AirLoopHVAC> airLoopHVAC() const;

      std::string controlType() const;
      bool setControlType(const std::string& controlType);
      bool isControlTypeDefaulted() const;
      void resetControlType();

      double thermostatTolerance() const;
      bool setThermostatTolerance(double thermostatTolerance);
      bool isThermostatToleranceDefaulted() const;
      void resetThermostatTolerance();

      double cyclingRunTime() const;
      bool setCyclingRunTime(double cyclingRunTime);
      bool isCyclingRunTimeDefaulted() const;
      void resetCyclingRunTime();

      std::string cyclingRunTimeControlType() const;
      bool setCyclingRunTimeControlType(const std::string& cyclingRunTimeControlType);
      bool isCyclingRunTimeControlTypeDefaulted() const;
      void resetCyclingRunTimeControlType();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
