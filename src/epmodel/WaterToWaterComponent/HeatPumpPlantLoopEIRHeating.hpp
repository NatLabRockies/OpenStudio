/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HEATPUMPPLANTLOOPEIRHEATING_HPP
#define EPMODEL_HEATPUMPPLANTLOOPEIRHEATING_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class HeatPumpPlantLoopEIRHeating_Impl;
}

class EPMODEL_API HeatPumpPlantLoopEIRHeating : public ModelObject
{
 public:
  explicit HeatPumpPlantLoopEIRHeating(const Model& model);

  virtual ~HeatPumpPlantLoopEIRHeating() override = default;
  HeatPumpPlantLoopEIRHeating(const HeatPumpPlantLoopEIRHeating& other) = default;
  HeatPumpPlantLoopEIRHeating(HeatPumpPlantLoopEIRHeating&& other) = default;
  HeatPumpPlantLoopEIRHeating& operator=(const HeatPumpPlantLoopEIRHeating&) = default;
  HeatPumpPlantLoopEIRHeating& operator=(HeatPumpPlantLoopEIRHeating&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> validCondenserTypeValues();
  static std::vector<std::string> condenserTypeValues();

  // Schema Alignment Notes:
  // - API: Preserves openstudio::model scalar accessor names/signatures for this model-counterpart class.
  // - Field Mapping: Preserved scalar APIs map directly to E+ HeatPump:PlantLoop:EIR:Heating scalar fields.
  // - Field Mapping: Relationship-like fields (companion object, curves, node/link targets) are intentionally excluded.
  // - Field Mapping: ForwardTranslator evidence confirms direct scalar mapping and Autosize string behavior for flow/capacity fields.
  // - TODO(parity): Add excluded non-scalar APIs and loop-coupling behavior in a dedicated parity pass.
  std::string condenserType() const;

  boost::optional<double> loadSideReferenceFlowRate() const;
  bool isLoadSideReferenceFlowRateAutosized() const;

  boost::optional<double> sourceSideReferenceFlowRate() const;
  bool isSourceSideReferenceFlowRateAutosized() const;

  boost::optional<double> heatRecoveryReferenceFlowRate() const;
  bool isHeatRecoveryReferenceFlowRateAutosized() const;

  boost::optional<double> referenceCapacity() const;
  bool isReferenceCapacityAutosized() const;

  double referenceCoefficientofPerformance() const;
  double sizingFactor() const;

  double heatingToCoolingCapacitySizingRatio() const;
  std::string heatPumpSizingMethod() const;

  std::string controlType() const;
  std::string flowMode() const;

  double minimumPartLoadRatio() const;
  double minimumSourceInletTemperature() const;
  double maximumSourceInletTemperature() const;

  double maximumOutdoorDryBulbTemperatureForDefrostOperation() const;
  std::string heatPumpDefrostControl() const;
  double heatPumpDefrostTimePeriodFraction() const;

  double minimumHeatRecoveryOutletTemperature() const;

  bool setCondenserType(const std::string& condenserType);

  bool setLoadSideReferenceFlowRate(double loadSideReferenceFlowRate);
  void autosizeLoadSideReferenceFlowRate();

  bool setSourceSideReferenceFlowRate(double sourceSideReferenceFlowRate);
  void autosizeSourceSideReferenceFlowRate();

  bool setHeatRecoveryReferenceFlowRate(double heatRecoveryReferenceFlowRate);
  void autosizeHeatRecoveryReferenceFlowRate();

  bool setReferenceCapacity(double referenceCapacity);
  void autosizeReferenceCapacity();

  bool setReferenceCoefficientofPerformance(double referenceCoefficientofPerformance);
  bool setSizingFactor(double sizingFactor);

  bool setHeatingToCoolingCapacitySizingRatio(double heatingToCoolingCapacitySizingRatio);
  bool setHeatPumpSizingMethod(const std::string& heatPumpSizingMethod);

  bool setControlType(const std::string& controlType);
  bool setFlowMode(const std::string& flowMode);

  bool setMinimumPartLoadRatio(double minimumPartLoadRatio);
  bool setMinimumSourceInletTemperature(double minimumSourceInletTemperature);
  bool setMaximumSourceInletTemperature(double maximumSourceInletTemperature);

  bool setMaximumOutdoorDryBulbTemperatureForDefrostOperation(double maximumOutdoorDryBulbTemperatureForDefrostOperation);
  bool setHeatPumpDefrostControl(const std::string& heatPumpDefrostControl);
  bool setHeatPumpDefrostTimePeriodFraction(double heatPumpDefrostTimePeriodFraction);

  bool setMinimumHeatRecoveryOutletTemperature(double minimumHeatRecoveryOutletTemperature);

  boost::optional<double> autosizedLoadSideReferenceFlowRate() const;
  boost::optional<double> autosizedSourceSideReferenceFlowRate() const;
  boost::optional<double> autosizedHeatRecoveryReferenceFlowRate() const;
  boost::optional<double> autosizedReferenceCapacity() const;

 protected:
  using ImplType = detail::HeatPumpPlantLoopEIRHeating_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit HeatPumpPlantLoopEIRHeating(std::shared_ptr<detail::HeatPumpPlantLoopEIRHeating_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
