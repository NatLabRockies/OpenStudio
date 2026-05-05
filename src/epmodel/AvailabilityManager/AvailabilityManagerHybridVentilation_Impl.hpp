/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AVAILABILITYMANAGERHYBRIDVENTILATION_IMPL_HPP
#define EPMODEL_AVAILABILITYMANAGERHYBRIDVENTILATION_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API AvailabilityManagerHybridVentilation_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~AvailabilityManagerHybridVentilation_Impl() override = default;

      bool useWeatherFileRainIndicators() const;
      bool setUseWeatherFileRainIndicators(bool useWeatherFileRainIndicators);

      double maximumWindSpeed() const;
      bool setMaximumWindSpeed(double maximumWindSpeed);

      double minimumOutdoorTemperature() const;
      bool setMinimumOutdoorTemperature(double minimumOutdoorTemperature);

      double maximumOutdoorTemperature() const;
      bool setMaximumOutdoorTemperature(double maximumOutdoorTemperature);

      double minimumOutdoorEnthalpy() const;
      bool setMinimumOutdoorEnthalpy(double minimumOutdoorEnthalpy);

      double maximumOutdoorEnthalpy() const;
      bool setMaximumOutdoorEnthalpy(double maximumOutdoorEnthalpy);

      double minimumOutdoorDewpoint() const;
      bool setMinimumOutdoorDewpoint(double minimumOutdoorDewpoint);

      double maximumOutdoorDewpoint() const;
      bool setMaximumOutdoorDewpoint(double maximumOutdoorDewpoint);

      double minimumHVACOperationTime() const;
      bool setMinimumHVACOperationTime(double minimumHVACOperationTime);

      double minimumVentilationTime() const;
      bool setMinimumVentilationTime(double minimumVentilationTime);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
