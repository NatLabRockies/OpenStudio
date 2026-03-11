/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HEATPUMPAIRTOWATERFUELFIREDHEATING_HPP
#define EPMODEL_HEATPUMPAIRTOWATERFUELFIREDHEATING_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class HeatPumpAirToWaterFuelFiredHeating_Impl;
}

class EPMODEL_API HeatPumpAirToWaterFuelFiredHeating : public StraightComponent
{
 public:
  explicit HeatPumpAirToWaterFuelFiredHeating(const Model& model);

  virtual ~HeatPumpAirToWaterFuelFiredHeating() override = default;
  HeatPumpAirToWaterFuelFiredHeating(const HeatPumpAirToWaterFuelFiredHeating& other) = default;
  HeatPumpAirToWaterFuelFiredHeating(HeatPumpAirToWaterFuelFiredHeating&& other) = default;
  HeatPumpAirToWaterFuelFiredHeating& operator=(const HeatPumpAirToWaterFuelFiredHeating&) = default;
  HeatPumpAirToWaterFuelFiredHeating& operator=(HeatPumpAirToWaterFuelFiredHeating&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> fuelTypeValues();
  static std::vector<std::string> flowModeValues();
  static std::vector<std::string> outdoorAirTemperatureCurveInputVariableValues();
  static std::vector<std::string> waterTemperatureCurveInputVariableValues();
  static std::vector<std::string> defrostControlTypeValues();

  // Schema Alignment Notes:
  // - API: Preserves openstudio::model::HeatPumpAirToWaterFuelFiredHeating scalar accessor names/signatures.
  // - Field Mapping: scalar methods map directly to E+ HeatPump:AirToWater:FuelFired:Heating fields with matching concepts.
  // - Field Mapping: companion heat pump, node/object references, and curve/object target-link fields are intentionally excluded.
  // - ForwardTranslator evidence: ForwardTranslateHeatPumpAirToWaterFuelFiredHeating.cpp writes these scalar APIs to the same E+ fields.
  // - TODO(parity): add relationship/object-list APIs incrementally without changing scalar signatures.
  std::string fuelType() const;
  bool setFuelType(const std::string& fuelType);

  std::string endUseSubcategory() const;
  bool isEndUseSubcategoryDefaulted() const;
  bool setEndUseSubcategory(const std::string& endUseSubcategory);
  void resetEndUseSubcategory();

  boost::optional<double> nominalHeatingCapacity() const;
  bool isNominalHeatingCapacityAutosized() const;
  boost::optional<double> autosizedNominalHeatingCapacity();
  bool setNominalHeatingCapacity(double nominalHeatingCapacity);
  void resetNominalHeatingCapacity();
  void autosizeNominalHeatingCapacity();

  double nominalCOP() const;
  bool setNominalCOP(double nominalCOP);

  boost::optional<double> designFlowRate() const;
  bool isDesignFlowRateAutosized() const;
  boost::optional<double> autosizedDesignFlowRate();
  bool setDesignFlowRate(double designFlowRate);
  void resetDesignFlowRate();
  void autosizeDesignFlowRate();

  double designSupplyTemperature() const;
  bool setDesignSupplyTemperature(double designSupplyTemperature);

  boost::optional<double> designTemperatureLift() const;
  bool isDesignTemperatureLiftAutosized() const;
  boost::optional<double> autosizedDesignTemperatureLift();
  bool setDesignTemperatureLift(double designTemperatureLift);
  void autosizeDesignTemperatureLift();

  double sizingFactor() const;
  bool setSizingFactor(double sizingFactor);

  std::string flowMode() const;
  bool setFlowMode(const std::string& flowMode);

  std::string outdoorAirTemperatureCurveInputVariable() const;
  bool setOutdoorAirTemperatureCurveInputVariable(const std::string& outdoorAirTemperatureCurveInputVariable);

  std::string waterTemperatureCurveInputVariable() const;
  bool setWaterTemperatureCurveInputVariable(const std::string& waterTemperatureCurveInputVariable);

  double minimumPartLoadRatio() const;
  bool setMinimumPartLoadRatio(double minimumPartLoadRatio);

  double maximumPartLoadRatio() const;
  bool setMaximumPartLoadRatio(double maximumPartLoadRatio);

  std::string defrostControlType() const;
  bool setDefrostControlType(const std::string& defrostControlType);

  double defrostOperationTimeFraction() const;
  bool setDefrostOperationTimeFraction(double defrostOperationTimeFraction);

  double resistiveDefrostHeaterCapacity() const;
  bool setResistiveDefrostHeaterCapacity(double resistiveDefrostHeaterCapacity);

  double maximumOutdoorDrybulbTemperatureforDefrostOperation() const;
  bool setMaximumOutdoorDrybulbTemperatureforDefrostOperation(double maximumOutdoorDrybulbTemperatureforDefrostOperation);

  double nominalAuxiliaryElectricPower() const;
  bool setNominalAuxiliaryElectricPower(double nominalAuxiliaryElectricPower);

  double standbyElectricPower() const;
  bool setStandbyElectricPower(double standbyElectricPower);

  double minimumUnloadingRatio() const;
  bool setMinimumUnloadingRatio(double minimumUnloadingRatio);

 protected:
  using ImplType = detail::HeatPumpAirToWaterFuelFiredHeating_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit HeatPumpAirToWaterFuelFiredHeating(std::shared_ptr<detail::HeatPumpAirToWaterFuelFiredHeating_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
