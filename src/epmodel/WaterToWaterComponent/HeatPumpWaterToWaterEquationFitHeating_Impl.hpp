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
  double ratedLoadSideFlowRate() const;
  bool isReferenceLoadSideFlowRateAutosized() const;

  boost::optional<double> referenceSourceSideFlowRate() const;
  double ratedSourceSideFlowRate() const;
  bool isReferenceSourceSideFlowRateAutosized() const;

  boost::optional<double> ratedHeatingCapacity() const;
  bool isRatedHeatingCapacityAutosized() const;

  boost::optional<double> ratedHeatingPowerConsumption() const;
  bool isRatedHeatingPowerConsumptionAutosized() const;

  double referenceCoefficientofPerformance() const;
  double sizingFactor() const;

  bool setReferenceLoadSideFlowRate(double referenceLoadSideFlowRate);
  bool setRatedLoadSideFlowRate(double ratedLoadSideFlowRate);
  void autosizeReferenceLoadSideFlowRate();

  bool setReferenceSourceSideFlowRate(double referenceSourceSideFlowRate);
  bool setRatedSourceSideFlowRate(double ratedSourceSideFlowRate);
  void autosizeReferenceSourceSideFlowRate();

  bool setRatedHeatingCapacity(double ratedHeatingCapacity);
  void autosizeRatedHeatingCapacity();

  bool setRatedHeatingPowerConsumption(double ratedHeatingPowerConsumption);
  void autosizeRatedHeatingPowerConsumption();

  bool setReferenceCoefficientofPerformance(double referenceCoefficientofPerformance);
  bool setSizingFactor(double sizingFactor);

  boost::optional<double> autosizedReferenceLoadSideFlowRate() const;
  boost::optional<double> autosizedReferenceSourceSideFlowRate() const;
  boost::optional<double> autosizedRatedHeatingCapacity() const;
  boost::optional<double> autosizedRatedHeatingPowerConsumption() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
