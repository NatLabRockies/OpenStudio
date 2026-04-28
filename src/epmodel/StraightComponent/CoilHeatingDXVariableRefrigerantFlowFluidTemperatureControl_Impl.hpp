/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILHEATINGDXVARIABLEREFRIGERANTFLOWFLUIDTEMPERATURECONTROL_IMPL_HPP
#define EPMODEL_COILHEATINGDXVARIABLEREFRIGERANTFLOWFLUIDTEMPERATURECONTROL_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

namespace openstudio {
namespace epmodel {

  class Curve;
  class Schedule;

  namespace detail {

    class EPMODEL_API CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_Impl : public StraightComponent_Impl
    {
     public:
      using StraightComponent_Impl::StraightComponent_Impl;
      virtual ~CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_Impl() override = default;

      unsigned inletPort() const override;
      unsigned outletPort() const override;
      bool addToNode(Node& node) override;

      Schedule availabilitySchedule() const;
      bool setAvailabilitySchedule(Schedule& schedule);

      boost::optional<double> ratedTotalHeatingCapacity() const;
      bool setRatedTotalHeatingCapacity(double ratedTotalHeatingCapacity);
      bool isRatedTotalHeatingCapacityAutosized() const;
      void autosizeRatedTotalHeatingCapacity();

      double indoorUnitReferenceSubcooling() const;
      Curve indoorUnitCondensingTemperatureFunctionofSubcoolingCurve() const;
      bool setIndoorUnitReferenceSubcooling(double indoorUnitReferenceSubcooling);
      bool setIndoorUnitCondensingTemperatureFunctionofSubcoolingCurve(const Curve& curve);

      std::vector<ModelObject> children() const override;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
