/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILHEATINGDXVARIABLEREFRIGERANTFLOWFLUIDTEMPERATURECONTROL_IMPL_HPP
#define EPMODEL_COILHEATINGDXVARIABLEREFRIGERANTFLOWFLUIDTEMPERATURECONTROL_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_Impl : public StraightComponent_Impl
    {
     public:
      using StraightComponent_Impl::StraightComponent_Impl;
      virtual ~CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_Impl() override = default;

      unsigned inletPort() const override;
      unsigned outletPort() const override;
      bool addToNode(Node& node) override;

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
