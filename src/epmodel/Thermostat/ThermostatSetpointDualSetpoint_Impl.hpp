/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_THERMOSTAT_THERMOSTATSETPOINTDUALSETPOINT_IMPL_HPP
#define EPMODEL_THERMOSTAT_THERMOSTATSETPOINTDUALSETPOINT_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ThermostatSetpointDualSetpoint_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ThermostatSetpointDualSetpoint_Impl() override = default;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
