/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILHEATINGDXVARIABLEREFRIGERANTFLOWFLUIDTEMPERATURECONTROL_IMPL_HPP
#define EPMODEL_COILHEATINGDXVARIABLEREFRIGERANTFLOWFLUIDTEMPERATURECONTROL_IMPL_HPP

#include "HVACComponent_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_Impl : public HVACComponent_Impl
    {
     public:
      using HVACComponent_Impl::HVACComponent_Impl;
      virtual ~CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_Impl() override = default;

      boost::optional<double> ratedTotalHeatingCapacity() const;
      bool setRatedTotalHeatingCapacity(double ratedTotalHeatingCapacity);
      bool isRatedTotalHeatingCapacityAutosized() const;
      void autosizeRatedTotalHeatingCapacity();

      double indoorUnitReferenceSubcooling() const;
      bool setIndoorUnitReferenceSubcooling(double indoorUnitReferenceSubcooling);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
