/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_THERMOSTATSETPOINTTHERMALCOMFORTFANGERSINGLEHEATING_IMPL_HPP
#define EPMODEL_THERMOSTATSETPOINTTHERMALCOMFORTFANGERSINGLEHEATING_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ThermostatSetpointThermalComfortFangerSingleHeating_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ThermostatSetpointThermalComfortFangerSingleHeating_Impl() override = default;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
