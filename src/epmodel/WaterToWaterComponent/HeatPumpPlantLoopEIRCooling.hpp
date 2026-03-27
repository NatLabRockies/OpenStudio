/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HEATPUMPPLANTLOOPEIRCOOLING_HPP
#define EPMODEL_HEATPUMPPLANTLOOPEIRCOOLING_HPP

#include "EPModelAPI.hpp"
#include "WaterToWaterComponent/WaterToWaterComponent.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
  class HeatPumpPlantLoopEIRCooling_Impl;
}

class EPMODEL_API HeatPumpPlantLoopEIRCooling : public WaterToWaterComponent
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
  // - Status: Scalar Parity. The plant-loop heat-pump cooling scalars are aligned, while companion-object and loop-link behavior remains excluded.
  // - Canonical Counterpart: openstudio::model::HeatPumpPlantLoopEIRCooling.
  // - Implemented Parity: Scalar accessors for condenser type, flow rates, heat-recovery flow, reference capacity, COP, sizing, control, and temperature limits preserve the canonical model API shape.
  // - Documented Delta: Companion-object, curve, and node/link APIs are intentionally excluded in this pass.
  // - Field/Storage Mapping: Scalar wrappers target EnergyPlus `HeatPump:PlantLoop:EIR:Cooling` fields directly, including autosized flow/capacity behavior.
  // - Evidence: `src/model/HeatPumpPlantLoopEIRCooling.hpp`, `src/model/HeatPumpPlantLoopEIRCooling.cpp`, and `src/energyplus/ForwardTranslator/ForwardTranslateHeatPumpPlantLoopEIRCooling.cpp`.
  // - Remaining Parity Work: Add the excluded loop-coupling and companion-object APIs only if the family moves beyond scalar parity.
  std::string condenserType() const;
  bool setCondenserType(const std::string& condenserType);

  boost::optional<double> loadSideReferenceFlowRate() const;
  bool isLoadSideReferenceFlowRateAutosized() const;
  bool setLoadSideReferenceFlowRate(double loadSideReferenceFlowRate);
  void autosizeLoadSideReferenceFlowRate();
  boost::optional<double> autosizedLoadSideReferenceFlowRate() const;

  boost::optional<double> sourceSideReferenceFlowRate() const;
  bool isSourceSideReferenceFlowRateAutosized() const;
  bool setSourceSideReferenceFlowRate(double sourceSideReferenceFlowRate);
  void autosizeSourceSideReferenceFlowRate();
  boost::optional<double> autosizedSourceSideReferenceFlowRate() const;

  boost::optional<double> heatRecoveryReferenceFlowRate() const;
  bool isHeatRecoveryReferenceFlowRateAutosized() const;
  bool setHeatRecoveryReferenceFlowRate(double heatRecoveryReferenceFlowRate);
  void autosizeHeatRecoveryReferenceFlowRate();
  boost::optional<double> autosizedHeatRecoveryReferenceFlowRate() const;

  boost::optional<double> referenceCapacity() const;
  bool isReferenceCapacityAutosized() const;
  bool setReferenceCapacity(double referenceCapacity);
  void autosizeReferenceCapacity();
  boost::optional<double> autosizedReferenceCapacity() const;

  double referenceCoefficientofPerformance() const;
  bool setReferenceCoefficientofPerformance(double referenceCoefficientofPerformance);

  double sizingFactor() const;
  bool setSizingFactor(double sizingFactor);

  std::string controlType() const;
  bool setControlType(const std::string& controlType);

  std::string flowMode() const;
  bool setFlowMode(const std::string& flowMode);

  double minimumPartLoadRatio() const;
  bool setMinimumPartLoadRatio(double minimumPartLoadRatio);

  double minimumSourceInletTemperature() const;
  bool setMinimumSourceInletTemperature(double minimumSourceInletTemperature);

  double maximumSourceInletTemperature() const;
  bool setMaximumSourceInletTemperature(double maximumSourceInletTemperature);

  double maximumHeatRecoveryOutletTemperature() const;
  bool setMaximumHeatRecoveryOutletTemperature(double maximumHeatRecoveryOutletTemperature);

  double thermosiphonMinimumTemperatureDifference() const;
  bool setThermosiphonMinimumTemperatureDifference(double thermosiphonMinimumTemperatureDifference);

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
