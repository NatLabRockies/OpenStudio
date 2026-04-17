/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILCOOLINGDXVARIABLEREFRIGERANTFLOW_IMPL_HPP
#define EPMODEL_COILCOOLINGDXVARIABLEREFRIGERANTFLOW_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

namespace openstudio {
namespace epmodel {

  class Curve;
  class Schedule;

  namespace detail {

    class EPMODEL_API CoilCoolingDXVariableRefrigerantFlow_Impl : public StraightComponent_Impl
    {
     public:
      using StraightComponent_Impl::StraightComponent_Impl;
      virtual ~CoilCoolingDXVariableRefrigerantFlow_Impl() override = default;

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

      boost::optional<double> ratedAirFlowRate() const;
      bool setRatedAirFlowRate(double ratedAirFlowRate);
      bool isRatedAirFlowRateAutosized() const;
      void autosizeRatedAirFlowRate();

      Curve coolingCapacityRatioModifierFunctionofTemperatureCurve() const;
      bool setCoolingCapacityRatioModifierFunctionofTemperatureCurve(const Curve& curve);

      Curve coolingCapacityModifierCurveFunctionofFlowFraction() const;
      bool setCoolingCapacityModifierCurveFunctionofFlowFraction(const Curve& curve);

      std::vector<ModelObject> children() const override;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
