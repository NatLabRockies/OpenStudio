/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HEATPUMPWATERTOWATEREQUATIONFITCOOLING_HPP
#define EPMODEL_HEATPUMPWATERTOWATEREQUATIONFITCOOLING_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class HeatPumpWaterToWaterEquationFitCooling_Impl;
}

class EPMODEL_API HeatPumpWaterToWaterEquationFitCooling : public ModelObject
{
 public:
  explicit HeatPumpWaterToWaterEquationFitCooling(const Model& model);

  virtual ~HeatPumpWaterToWaterEquationFitCooling() override = default;
  HeatPumpWaterToWaterEquationFitCooling(const HeatPumpWaterToWaterEquationFitCooling& other) = default;
  HeatPumpWaterToWaterEquationFitCooling(HeatPumpWaterToWaterEquationFitCooling&& other) = default;
  HeatPumpWaterToWaterEquationFitCooling& operator=(const HeatPumpWaterToWaterEquationFitCooling&) = default;
  HeatPumpWaterToWaterEquationFitCooling& operator=(HeatPumpWaterToWaterEquationFitCooling&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: Preserves existing openstudio::model scalar accessor names/signatures, including legacy rated/reference aliases.
  // - Field Mapping: ratedCoolingCapacity/ratedCoolingPowerConsumption map to E+ Reference Cooling fields per ForwardTranslator behavior.
  // - Field Mapping: Relationship-like fields (nodes, curves, companion heat pump) are intentionally excluded in this scalar-only scaffold.
  // - TODO(parity): Add non-scalar curve/companion APIs and WaterToWater component behavior in a dedicated parity pass.
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

 protected:
  using ImplType = detail::HeatPumpWaterToWaterEquationFitCooling_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit HeatPumpWaterToWaterEquationFitCooling(std::shared_ptr<detail::HeatPumpWaterToWaterEquationFitCooling_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
