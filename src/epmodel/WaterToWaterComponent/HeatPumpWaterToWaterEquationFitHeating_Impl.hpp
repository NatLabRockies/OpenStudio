/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HEATPUMPWATERTOWATEREQUATIONFITHEATING_IMPL_HPP
#define EPMODEL_HEATPUMPWATERTOWATEREQUATIONFITHEATING_IMPL_HPP

#include "WaterToWaterComponent/WaterToWaterComponent_Impl.hpp"

namespace openstudio {
namespace epmodel {

  class CurveQuadLinear;
  class HeatPumpWaterToWaterEquationFitCooling;

  namespace detail {

    class EPMODEL_API HeatPumpWaterToWaterEquationFitHeating_Impl : public WaterToWaterComponent_Impl
    {
     public:
      using WaterToWaterComponent_Impl::WaterToWaterComponent_Impl;
      virtual ~HeatPumpWaterToWaterEquationFitHeating_Impl() override = default;

      unsigned supplyInletPort() const override;
      unsigned supplyOutletPort() const override;
      unsigned demandInletPort() const override;
      unsigned demandOutletPort() const override;

      boost::optional<double> referenceLoadSideFlowRate() const;
      bool isReferenceLoadSideFlowRateAutosized() const;
      bool setReferenceLoadSideFlowRate(double referenceLoadSideFlowRate);
      void autosizeReferenceLoadSideFlowRate();
      boost::optional<double> autosizedReferenceLoadSideFlowRate() const;

      double ratedLoadSideFlowRate() const;
      bool setRatedLoadSideFlowRate(double ratedLoadSideFlowRate);

      boost::optional<double> referenceSourceSideFlowRate() const;
      bool isReferenceSourceSideFlowRateAutosized() const;
      bool setReferenceSourceSideFlowRate(double referenceSourceSideFlowRate);
      void autosizeReferenceSourceSideFlowRate();
      boost::optional<double> autosizedReferenceSourceSideFlowRate() const;

      double ratedSourceSideFlowRate() const;
      bool setRatedSourceSideFlowRate(double ratedSourceSideFlowRate);

      boost::optional<double> ratedHeatingCapacity() const;
      bool isRatedHeatingCapacityAutosized() const;
      bool setRatedHeatingCapacity(double ratedHeatingCapacity);
      void autosizeRatedHeatingCapacity();
      boost::optional<double> autosizedRatedHeatingCapacity() const;

      boost::optional<double> ratedHeatingPowerConsumption() const;
      bool isRatedHeatingPowerConsumptionAutosized() const;
      bool setRatedHeatingPowerConsumption(double ratedHeatingPowerConsumption);
      void autosizeRatedHeatingPowerConsumption();
      boost::optional<double> autosizedRatedHeatingPowerConsumption() const;

      CurveQuadLinear heatingCapacityCurve() const;
      bool setHeatingCapacityCurve(const CurveQuadLinear& heatingCapacityCurve);

      CurveQuadLinear heatingCompressorPowerCurve() const;
      bool setHeatingCompressorPowerCurve(const CurveQuadLinear& heatingCompressorPowerCurve);

      double referenceCoefficientofPerformance() const;
      bool setReferenceCoefficientofPerformance(double referenceCoefficientofPerformance);

      double sizingFactor() const;
      bool setSizingFactor(double sizingFactor);

      boost::optional<HeatPumpWaterToWaterEquationFitCooling> companionCoolingHeatPump() const;
      bool setCompanionCoolingHeatPump(const HeatPumpWaterToWaterEquationFitCooling& companionCoolingHeatPump);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
