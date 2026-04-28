/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILCOOLINGDXVARIABLEREFRIGERANTFLOWFLUIDTEMPERATURECONTROL_IMPL_HPP
#define EPMODEL_COILCOOLINGDXVARIABLEREFRIGERANTFLOWFLUIDTEMPERATURECONTROL_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl_Impl : public StraightComponent_Impl
    {
     public:
      using StraightComponent_Impl::StraightComponent_Impl;
      virtual ~CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl_Impl() override = default;

      unsigned inletPort() const override;
      unsigned outletPort() const override;
      bool addToNode(Node& node) override;

      Schedule availabilitySchedule() const;
      bool setAvailabilitySchedule(Schedule& schedule);

      boost::optional<double> ratedTotalCoolingCapacity() const;
      bool setRatedTotalCoolingCapacity(double ratedTotalCoolingCapacity);
      bool isRatedTotalCoolingCapacityAutosized() const;
      void autosizeRatedTotalCoolingCapacity();

      boost::optional<double> ratedSensibleHeatRatio() const;
      bool setRatedSensibleHeatRatio(double ratedSensibleHeatRatio);
      bool isRatedSensibleHeatRatioAutosized() const;
      void autosizeRatedSensibleHeatRatio();

      double indoorUnitReferenceSuperheating() const;
      bool setIndoorUnitReferenceSuperheating(double indoorUnitReferenceSuperheating);

      Curve indoorUnitEvaporatingTemperatureFunctionofSuperheatingCurve() const;
      bool setIndoorUnitEvaporatingTemperatureFunctionofSuperheatingCurve(const Curve& curve);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
