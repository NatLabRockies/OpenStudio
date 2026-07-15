/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HVACTEMPLATETHERMOSTAT_IMPL_HPP
#define EPMODEL_HVACTEMPLATETHERMOSTAT_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API HVACTemplateThermostat_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~HVACTemplateThermostat_Impl() override = default;

      boost::optional<double> constantHeatingSetpoint() const;
      bool setConstantHeatingSetpoint(double constantHeatingSetpoint);
      void resetConstantHeatingSetpoint();

      boost::optional<double> constantCoolingSetpoint() const;
      bool setConstantCoolingSetpoint(double constantCoolingSetpoint);
      void resetConstantCoolingSetpoint();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
