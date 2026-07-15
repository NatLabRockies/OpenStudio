/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGERRETURNTEMPERATURECHILLEDWATER_IMPL_HPP
#define EPMODEL_SETPOINTMANAGERRETURNTEMPERATURECHILLEDWATER_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API SetpointManagerReturnTemperatureChilledWater_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~SetpointManagerReturnTemperatureChilledWater_Impl() override = default;

      double minimumSupplyTemperatureSetpoint() const;
      bool isMinimumSupplyTemperatureSetpointDefaulted() const;
      bool setMinimumSupplyTemperatureSetpoint(double minimumSupplyTemperatureSetpoint);
      void resetMinimumSupplyTemperatureSetpoint();

      double maximumSupplyTemperatureSetpoint() const;
      bool isMaximumSupplyTemperatureSetpointDefaulted() const;
      bool setMaximumSupplyTemperatureSetpoint(double maximumSupplyTemperatureSetpoint);
      void resetMaximumSupplyTemperatureSetpoint();

      std::string returnTemperatureSetpointInputType() const;
      bool setReturnTemperatureSetpointInputType(const std::string& returnTemperatureSetpointInputType);

      double returnTemperatureSetpointConstantValue() const;
      bool isReturnTemperatureSetpointConstantValueDefaulted() const;
      bool setReturnTemperatureSetpointConstantValue(double returnTemperatureSetpointConstantValue);
      void resetReturnTemperatureSetpointConstantValue();

      std::vector<std::string> returnTemperatureSetpointInputTypeValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
