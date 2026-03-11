/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HEATPUMPPLANTLOOPEIRCOOLING_HPP
#define EPMODEL_HEATPUMPPLANTLOOPEIRCOOLING_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class HeatPumpPlantLoopEIRCooling_Impl;
}

class EPMODEL_API HeatPumpPlantLoopEIRCooling : public ModelObject
{
 public:
  explicit HeatPumpPlantLoopEIRCooling(const Model& model);

  virtual ~HeatPumpPlantLoopEIRCooling() override = default;
  HeatPumpPlantLoopEIRCooling(const HeatPumpPlantLoopEIRCooling& other) = default;
  HeatPumpPlantLoopEIRCooling(HeatPumpPlantLoopEIRCooling&& other) = default;
  HeatPumpPlantLoopEIRCooling& operator=(const HeatPumpPlantLoopEIRCooling&) = default;
  HeatPumpPlantLoopEIRCooling& operator=(HeatPumpPlantLoopEIRCooling&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> validCondenserTypeValues();
  static std::vector<std::string> condenserTypeValues();

  // Schema Alignment Notes:
  // - API: Preserves openstudio::model scalar accessor names/signatures for this model-counterpart class.
  // - Field Mapping: Preserved scalar APIs map directly to E+ HeatPump:PlantLoop:EIR:Cooling scalar fields.
  // - Field Mapping: Relationship-like fields (companion object, curves, node/link targets) are intentionally excluded.
  // - Field Mapping: ForwardTranslator evidence confirms direct mapping and Autosize string behavior for flow/capacity fields.
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

  std::string controlType() const;
  std::string flowMode() const;

  double minimumPartLoadRatio() const;
  double minimumSourceInletTemperature() const;
  double maximumSourceInletTemperature() const;

  double maximumHeatRecoveryOutletTemperature() const;
  double thermosiphonMinimumTemperatureDifference() const;

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

  bool setControlType(const std::string& controlType);
  bool setFlowMode(const std::string& flowMode);

  bool setMinimumPartLoadRatio(double minimumPartLoadRatio);
  bool setMinimumSourceInletTemperature(double minimumSourceInletTemperature);
  bool setMaximumSourceInletTemperature(double maximumSourceInletTemperature);

  bool setMaximumHeatRecoveryOutletTemperature(double maximumHeatRecoveryOutletTemperature);
  bool setThermosiphonMinimumTemperatureDifference(double thermosiphonMinimumTemperatureDifference);

  boost::optional<double> autosizedLoadSideReferenceFlowRate() const;
  boost::optional<double> autosizedSourceSideReferenceFlowRate() const;
  boost::optional<double> autosizedHeatRecoveryReferenceFlowRate() const;
  boost::optional<double> autosizedReferenceCapacity() const;

 protected:
  using ImplType = detail::HeatPumpPlantLoopEIRCooling_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit HeatPumpPlantLoopEIRCooling(std::shared_ptr<detail::HeatPumpPlantLoopEIRCooling_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
