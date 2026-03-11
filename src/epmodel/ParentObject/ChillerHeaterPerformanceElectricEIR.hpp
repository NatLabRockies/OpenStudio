/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CHILLERHEATERPERFORMANCEELECTRICEIR_HPP
#define EPMODEL_CHILLERHEATERPERFORMANCEELECTRICEIR_HPP

#include "EPModelAPI.hpp"
#include "ParentObject/ParentObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class ChillerHeaterPerformanceElectricEIR_Impl;
}

class EPMODEL_API ChillerHeaterPerformanceElectricEIR : public ParentObject
{
 public:
  explicit ChillerHeaterPerformanceElectricEIR(const Model& model);

  virtual ~ChillerHeaterPerformanceElectricEIR() override = default;
  ChillerHeaterPerformanceElectricEIR(const ChillerHeaterPerformanceElectricEIR& other) = default;
  ChillerHeaterPerformanceElectricEIR(ChillerHeaterPerformanceElectricEIR&& other) = default;
  ChillerHeaterPerformanceElectricEIR& operator=(const ChillerHeaterPerformanceElectricEIR&) = default;
  ChillerHeaterPerformanceElectricEIR& operator=(ChillerHeaterPerformanceElectricEIR&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> chilledWaterFlowModeTypeValues();
  static std::vector<std::string> condenserTypeValues();
  static std::vector<std::string> coolingModeTemperatureCurveCondenserWaterIndependentVariableValues();
  static std::vector<std::string> heatingModeTemperatureCurveCondenserWaterIndependentVariableValues();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model::ChillerHeaterPerformanceElectricEIR scalar API names/signatures for counterpart compatibility.
  // - Field Mapping: Preserved scalar APIs map directly to EnergyPlus ChillerHeaterPerformance:Electric:EIR scalar fields.
  // - Field Mapping: Curve-name relationship fields are intentionally excluded from this scalar-only scaffold.
  // - ForwardTranslator evidence: translateChillerHeaterPerformanceElectricEIR writes autosize and scalar values directly to matching fields.
  // - TODO(parity): Add excluded relationship/reverse-lookup APIs in a dedicated parity pass.
  boost::optional<double> referenceCoolingModeEvaporatorCapacity() const;
  bool isReferenceCoolingModeEvaporatorCapacityAutosized() const;
  bool setReferenceCoolingModeEvaporatorCapacity(double referenceCoolingModeEvaporatorCapacity);
  void autosizeReferenceCoolingModeEvaporatorCapacity();

  double referenceCoolingModeCOP() const;
  bool setReferenceCoolingModeCOP(double referenceCoolingModeCOP);

  double referenceCoolingModeLeavingChilledWaterTemperature() const;
  bool setReferenceCoolingModeLeavingChilledWaterTemperature(double referenceCoolingModeLeavingChilledWaterTemperature);

  double referenceCoolingModeEnteringCondenserFluidTemperature() const;
  bool setReferenceCoolingModeEnteringCondenserFluidTemperature(double referenceCoolingModeEnteringCondenserFluidTemperature);

  double referenceCoolingModeLeavingCondenserWaterTemperature() const;
  bool setReferenceCoolingModeLeavingCondenserWaterTemperature(double referenceCoolingModeLeavingCondenserWaterTemperature);

  double referenceHeatingModeCoolingCapacityRatio() const;
  bool setReferenceHeatingModeCoolingCapacityRatio(double referenceHeatingModeCoolingCapacityRatio);

  double referenceHeatingModeCoolingPowerInputRatio() const;
  bool setReferenceHeatingModeCoolingPowerInputRatio(double referenceHeatingModeCoolingPowerInputRatio);

  double referenceHeatingModeLeavingChilledWaterTemperature() const;
  bool setReferenceHeatingModeLeavingChilledWaterTemperature(double referenceHeatingModeLeavingChilledWaterTemperature);

  double referenceHeatingModeLeavingCondenserWaterTemperature() const;
  bool setReferenceHeatingModeLeavingCondenserWaterTemperature(double referenceHeatingModeLeavingCondenserWaterTemperature);

  double referenceHeatingModeEnteringCondenserFluidTemperature() const;
  bool setReferenceHeatingModeEnteringCondenserFluidTemperature(double referenceHeatingModeEnteringCondenserFluidTemperature);

  double heatingModeEnteringChilledWaterTemperatureLowLimit() const;
  bool setHeatingModeEnteringChilledWaterTemperatureLowLimit(double heatingModeEnteringChilledWaterTemperatureLowLimit);

  std::string chilledWaterFlowModeType() const;
  bool setChilledWaterFlowModeType(const std::string& chilledWaterFlowModeType);

  boost::optional<double> designChilledWaterFlowRate() const;
  bool isDesignChilledWaterFlowRateAutosized() const;
  bool setDesignChilledWaterFlowRate(double designChilledWaterFlowRate);
  void resetDesignChilledWaterFlowRate();
  void autosizeDesignChilledWaterFlowRate();

  boost::optional<double> designCondenserWaterFlowRate() const;
  bool isDesignCondenserWaterFlowRateAutosized() const;
  bool setDesignCondenserWaterFlowRate(double designCondenserWaterFlowRate);
  void resetDesignCondenserWaterFlowRate();
  void autosizeDesignCondenserWaterFlowRate();

  double designHotWaterFlowRate() const;
  bool setDesignHotWaterFlowRate(double designHotWaterFlowRate);

  double compressorMotorEfficiency() const;
  bool setCompressorMotorEfficiency(double compressorMotorEfficiency);

  std::string condenserType() const;
  bool setCondenserType(const std::string& condenserType);

  std::string coolingModeTemperatureCurveCondenserWaterIndependentVariable() const;
  bool setCoolingModeTemperatureCurveCondenserWaterIndependentVariable(
    const std::string& coolingModeTemperatureCurveCondenserWaterIndependentVariable);

  double coolingModeCoolingCapacityOptimumPartLoadRatio() const;
  bool setCoolingModeCoolingCapacityOptimumPartLoadRatio(double coolingModeCoolingCapacityOptimumPartLoadRatio);

  std::string heatingModeTemperatureCurveCondenserWaterIndependentVariable() const;
  bool setHeatingModeTemperatureCurveCondenserWaterIndependentVariable(
    const std::string& heatingModeTemperatureCurveCondenserWaterIndependentVariable);

  double heatingModeCoolingCapacityOptimumPartLoadRatio() const;
  bool setHeatingModeCoolingCapacityOptimumPartLoadRatio(double heatingModeCoolingCapacityOptimumPartLoadRatio);

  double sizingFactor() const;
  bool setSizingFactor(double sizingFactor);

 protected:
  using ImplType = detail::ChillerHeaterPerformanceElectricEIR_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit ChillerHeaterPerformanceElectricEIR(std::shared_ptr<detail::ChillerHeaterPerformanceElectricEIR_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
