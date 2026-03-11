/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CHILLERHEATERABSORPTIONDIRECTFIRED_HPP
#define EPMODEL_CHILLERHEATERABSORPTIONDIRECTFIRED_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class ChillerHeaterAbsorptionDirectFired_Impl;
}

class EPMODEL_API ChillerHeaterAbsorptionDirectFired : public ModelObject
{
 public:
  explicit ChillerHeaterAbsorptionDirectFired(const Model& model);

  virtual ~ChillerHeaterAbsorptionDirectFired() override = default;
  ChillerHeaterAbsorptionDirectFired(const ChillerHeaterAbsorptionDirectFired& other) = default;
  ChillerHeaterAbsorptionDirectFired(ChillerHeaterAbsorptionDirectFired&& other) = default;
  ChillerHeaterAbsorptionDirectFired& operator=(const ChillerHeaterAbsorptionDirectFired&) = default;
  ChillerHeaterAbsorptionDirectFired& operator=(ChillerHeaterAbsorptionDirectFired&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> temperatureCurveInputVariableValues();
  static std::vector<std::string> condenserTypeValues();
  static std::vector<std::string> fuelTypeValues();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived scalar accessor names.
  // - Field Mapping: Scalar APIs map directly to EnergyPlus ChillerHeater:Absorption:DirectFired fields.
  // - Field Mapping: Relationship fields (node/object-list references) are excluded from this scalar-only scaffold.
  // - TODO(parity): Add excluded relationship APIs in a dedicated relationship pass.
  boost::optional<double> nominalCoolingCapacity() const;
  bool isNominalCoolingCapacityDefaulted() const;
  bool isNominalCoolingCapacityAutosized() const;
  bool setNominalCoolingCapacity(double nominalCoolingCapacity);
  void resetNominalCoolingCapacity();
  void autosizeNominalCoolingCapacity();

  double heatingtoCoolingCapacityRatio() const;
  bool isHeatingtoCoolingCapacityRatioDefaulted() const;
  bool setHeatingtoCoolingCapacityRatio(double heatingtoCoolingCapacityRatio);
  void resetHeatingtoCoolingCapacityRatio();

  double fuelInputtoCoolingOutputRatio() const;
  bool isFuelInputtoCoolingOutputRatioDefaulted() const;
  bool setFuelInputtoCoolingOutputRatio(double fuelInputtoCoolingOutputRatio);
  void resetFuelInputtoCoolingOutputRatio();

  double fuelInputtoHeatingOutputRatio() const;
  bool isFuelInputtoHeatingOutputRatioDefaulted() const;
  bool setFuelInputtoHeatingOutputRatio(double fuelInputtoHeatingOutputRatio);
  void resetFuelInputtoHeatingOutputRatio();

  double electricInputtoCoolingOutputRatio() const;
  bool isElectricInputtoCoolingOutputRatioDefaulted() const;
  bool setElectricInputtoCoolingOutputRatio(double electricInputtoCoolingOutputRatio);
  void resetElectricInputtoCoolingOutputRatio();

  double electricInputtoHeatingOutputRatio() const;
  bool isElectricInputtoHeatingOutputRatioDefaulted() const;
  bool setElectricInputtoHeatingOutputRatio(double electricInputtoHeatingOutputRatio);
  void resetElectricInputtoHeatingOutputRatio();

  double minimumPartLoadRatio() const;
  bool isMinimumPartLoadRatioDefaulted() const;
  bool setMinimumPartLoadRatio(double minimumPartLoadRatio);
  void resetMinimumPartLoadRatio();

  double maximumPartLoadRatio() const;
  bool isMaximumPartLoadRatioDefaulted() const;
  bool setMaximumPartLoadRatio(double maximumPartLoadRatio);
  void resetMaximumPartLoadRatio();

  double optimumPartLoadRatio() const;
  bool isOptimumPartLoadRatioDefaulted() const;
  bool setOptimumPartLoadRatio(double optimumPartLoadRatio);
  void resetOptimumPartLoadRatio();

  double designEnteringCondenserWaterTemperature() const;
  bool isDesignEnteringCondenserWaterTemperatureDefaulted() const;
  bool setDesignEnteringCondenserWaterTemperature(double designEnteringCondenserWaterTemperature);
  void resetDesignEnteringCondenserWaterTemperature();

  double designLeavingChilledWaterTemperature() const;
  bool isDesignLeavingChilledWaterTemperatureDefaulted() const;
  bool setDesignLeavingChilledWaterTemperature(double designLeavingChilledWaterTemperature);
  void resetDesignLeavingChilledWaterTemperature();

  boost::optional<double> designChilledWaterFlowRate() const;
  bool isDesignChilledWaterFlowRateDefaulted() const;
  bool isDesignChilledWaterFlowRateAutosized() const;
  bool setDesignChilledWaterFlowRate(double designChilledWaterFlowRate);
  void resetDesignChilledWaterFlowRate();
  void autosizeDesignChilledWaterFlowRate();

  boost::optional<double> designCondenserWaterFlowRate() const;
  bool isDesignCondenserWaterFlowRateDefaulted() const;
  bool isDesignCondenserWaterFlowRateAutosized() const;
  bool setDesignCondenserWaterFlowRate(double designCondenserWaterFlowRate);
  void resetDesignCondenserWaterFlowRate();
  void autosizeDesignCondenserWaterFlowRate();

  boost::optional<double> designHotWaterFlowRate() const;
  bool isDesignHotWaterFlowRateDefaulted() const;
  bool isDesignHotWaterFlowRateAutosized() const;
  bool setDesignHotWaterFlowRate(double designHotWaterFlowRate);
  void resetDesignHotWaterFlowRate();
  void autosizeDesignHotWaterFlowRate();

  std::string temperatureCurveInputVariable() const;
  bool isTemperatureCurveInputVariableDefaulted() const;
  bool setTemperatureCurveInputVariable(const std::string& temperatureCurveInputVariable);
  void resetTemperatureCurveInputVariable();

  std::string condenserType() const;
  bool isCondenserTypeDefaulted() const;
  bool setCondenserType(const std::string& condenserType);
  void resetCondenserType();

  double chilledWaterTemperatureLowerLimit() const;
  bool isChilledWaterTemperatureLowerLimitDefaulted() const;
  bool setChilledWaterTemperatureLowerLimit(double chilledWaterTemperatureLowerLimit);
  void resetChilledWaterTemperatureLowerLimit();

  double fuelHigherHeatingValue() const;
  bool isFuelHigherHeatingValueDefaulted() const;
  bool setFuelHigherHeatingValue(double fuelHigherHeatingValue);
  void resetFuelHigherHeatingValue();

  std::string fuelType() const;
  bool isFuelTypeDefaulted() const;
  bool setFuelType(const std::string& fuelType);
  void resetFuelType();

  double sizingFactor() const;
  bool isSizingFactorDefaulted() const;
  bool setSizingFactor(double sizingFactor);
  void resetSizingFactor();

 protected:
  using ImplType = detail::ChillerHeaterAbsorptionDirectFired_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit ChillerHeaterAbsorptionDirectFired(std::shared_ptr<detail::ChillerHeaterAbsorptionDirectFired_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
