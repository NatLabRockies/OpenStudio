/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONECONTROLTHERMOSTATTHERMALCOMFORT_IMPL_HPP
#define EPMODEL_ZONECONTROLTHERMOSTATTHERMALCOMFORT_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ZoneControlThermostatThermalComfort_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ZoneControlThermostatThermalComfort_Impl() override = default;

      std::string averagingMethod() const;
      bool setAveragingMethod(const std::string& averagingMethod);
      bool isAveragingMethodDefaulted() const;
      void resetAveragingMethod();

      boost::optional<double> minimumDryBulbTemperatureSetpoint() const;
      bool setMinimumDryBulbTemperatureSetpoint(double minimumDryBulbTemperatureSetpoint);
      bool isMinimumDryBulbTemperatureSetpointDefaulted() const;
      void resetMinimumDryBulbTemperatureSetpoint();

      boost::optional<double> maximumDryBulbTemperatureSetpoint() const;
      bool setMaximumDryBulbTemperatureSetpoint(double maximumDryBulbTemperatureSetpoint);
      bool isMaximumDryBulbTemperatureSetpointDefaulted() const;
      void resetMaximumDryBulbTemperatureSetpoint();

      std::vector<std::string> averagingMethodValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
