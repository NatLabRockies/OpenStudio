/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PLANTCOMPONENTTEMPERATURESOURCE_IMPL_HPP
#define EPMODEL_PLANTCOMPONENTTEMPERATURESOURCE_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Schedule;

  namespace detail {

    class EPMODEL_API PlantComponentTemperatureSource_Impl : public StraightComponent_Impl
    {
     public:
      using StraightComponent_Impl::StraightComponent_Impl;
      virtual ~PlantComponentTemperatureSource_Impl() override = default;

      unsigned inletPort() const override;
      unsigned outletPort() const override;

      boost::optional<double> designVolumeFlowRate() const;
      bool isDesignVolumeFlowRateAutosized() const;
      bool setDesignVolumeFlowRate(double designVolumeFlowRate);
      void autosizeDesignVolumeFlowRate();
      boost::optional<double> autosizedDesignVolumeFlowRate() const;

      std::string temperatureSpecificationType() const;
      bool setTemperatureSpecificationType(const std::string& temperatureSpecificationType);
      std::vector<std::string> temperatureSpecificationTypeValues() const;

      boost::optional<double> sourceTemperature() const;
      bool setSourceTemperature(double sourceTemperature);
      void resetSourceTemperature();

      boost::optional<Schedule> sourceTemperatureSchedule() const;
      bool setSourceTemperatureSchedule(Schedule& schedule);
      void resetSourceTemperatureSchedule();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
