/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HEATPUMPWATERTOWATEREQUATIONFITCOOLING_IMPL_HPP
#define EPMODEL_HEATPUMPWATERTOWATEREQUATIONFITCOOLING_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API HeatPumpWaterToWaterEquationFitCooling_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~HeatPumpWaterToWaterEquationFitCooling_Impl() override = default;

  boost::optional<double> referenceLoadSideFlowRate() const;
  double ratedLoadSideFlowRate() const;
  bool isReferenceLoadSideFlowRateAutosized() const;

  boost::optional<double> referenceSourceSideFlowRate() const;
  double ratedSourceSideFlowRate() const;
  bool isReferenceSourceSideFlowRateAutosized() const;

  boost::optional<double> ratedCoolingCapacity() const;
  bool isRatedCoolingCapacityAutosized() const;

  boost::optional<double> ratedCoolingPowerConsumption() const;
  bool isRatedCoolingPowerConsumptionAutosized() const;

  double referenceCoefficientofPerformance() const;
  double sizingFactor() const;

  bool setReferenceLoadSideFlowRate(double referenceLoadSideFlowRate);
  bool setRatedLoadSideFlowRate(double ratedLoadSideFlowRate);
  void autosizeReferenceLoadSideFlowRate();

  bool setReferenceSourceSideFlowRate(double referenceSourceSideFlowRate);
  bool setRatedSourceSideFlowRate(double ratedSourceSideFlowRate);
  void autosizeReferenceSourceSideFlowRate();

  bool setRatedCoolingCapacity(double ratedCoolingCapacity);
  void autosizeRatedCoolingCapacity();

  bool setRatedCoolingPowerConsumption(double ratedCoolingPowerConsumption);
  void autosizeRatedCoolingPowerConsumption();

  bool setReferenceCoefficientofPerformance(double referenceCoefficientofPerformance);
  bool setSizingFactor(double sizingFactor);

  boost::optional<double> autosizedReferenceLoadSideFlowRate() const;
  boost::optional<double> autosizedReferenceSourceSideFlowRate() const;
  boost::optional<double> autosizedRatedCoolingCapacity() const;
  boost::optional<double> autosizedRatedCoolingPowerConsumption() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
