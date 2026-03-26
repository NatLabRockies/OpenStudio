/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HEATPUMPWATERTOWATEREQUATIONFITCOOLING_IMPL_HPP
#define EPMODEL_HEATPUMPWATERTOWATEREQUATIONFITCOOLING_IMPL_HPP

#include "WaterToWaterComponent/WaterToWaterComponent_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API HeatPumpWaterToWaterEquationFitCooling_Impl : public WaterToWaterComponent_Impl
    {
     public:
      using WaterToWaterComponent_Impl::WaterToWaterComponent_Impl;
      virtual ~HeatPumpWaterToWaterEquationFitCooling_Impl() override = default;

      unsigned supplyInletPort() const override;
      unsigned supplyOutletPort() const override;
      unsigned demandInletPort() const override;
      unsigned demandOutletPort() const override;

      // Reference load-side flow rate
      boost::optional<double> referenceLoadSideFlowRate() const;
      bool isReferenceLoadSideFlowRateAutosized() const;
      bool setReferenceLoadSideFlowRate(double referenceLoadSideFlowRate);
      void autosizeReferenceLoadSideFlowRate();
      boost::optional<double> autosizedReferenceLoadSideFlowRate() const;

      // Rated load-side flow rate
      double ratedLoadSideFlowRate() const;
      bool setRatedLoadSideFlowRate(double ratedLoadSideFlowRate);

      // Reference source-side flow rate
      boost::optional<double> referenceSourceSideFlowRate() const;
      bool isReferenceSourceSideFlowRateAutosized() const;
      bool setReferenceSourceSideFlowRate(double referenceSourceSideFlowRate);
      void autosizeReferenceSourceSideFlowRate();
      boost::optional<double> autosizedReferenceSourceSideFlowRate() const;

      // Rated source-side flow rate
      double ratedSourceSideFlowRate() const;
      bool setRatedSourceSideFlowRate(double ratedSourceSideFlowRate);

      // Rated cooling capacity
      boost::optional<double> ratedCoolingCapacity() const;
      bool isRatedCoolingCapacityAutosized() const;
      bool setRatedCoolingCapacity(double ratedCoolingCapacity);
      void autosizeRatedCoolingCapacity();
      boost::optional<double> autosizedRatedCoolingCapacity() const;

      // Rated cooling power consumption
      boost::optional<double> ratedCoolingPowerConsumption() const;
      bool isRatedCoolingPowerConsumptionAutosized() const;
      bool setRatedCoolingPowerConsumption(double ratedCoolingPowerConsumption);
      void autosizeRatedCoolingPowerConsumption();
      boost::optional<double> autosizedRatedCoolingPowerConsumption() const;

      // Performance knobs
      double referenceCoefficientofPerformance() const;
      bool setReferenceCoefficientofPerformance(double referenceCoefficientofPerformance);

      double sizingFactor() const;
      bool setSizingFactor(double sizingFactor);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
