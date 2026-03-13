/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HEATPUMPWATERTOWATEREQUATIONFITHEATING_IMPL_HPP
#define EPMODEL_HEATPUMPWATERTOWATEREQUATIONFITHEATING_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API HeatPumpWaterToWaterEquationFitHeating_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~HeatPumpWaterToWaterEquationFitHeating_Impl() override = default;

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

      double referenceCoefficientofPerformance() const;
      bool setReferenceCoefficientofPerformance(double referenceCoefficientofPerformance);

      double sizingFactor() const;
      bool setSizingFactor(double sizingFactor);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
