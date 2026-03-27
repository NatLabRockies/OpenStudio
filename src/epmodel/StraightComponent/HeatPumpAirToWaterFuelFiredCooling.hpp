/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HEATPUMPAIRTOWATERFUELFIREDCOOLING_HPP
#define EPMODEL_HEATPUMPAIRTOWATERFUELFIREDCOOLING_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class HeatPumpAirToWaterFuelFiredCooling_Impl;
}

class EPMODEL_API HeatPumpAirToWaterFuelFiredCooling : public StraightComponent
{
 public:
  explicit HeatPumpAirToWaterFuelFiredCooling(const Model& model);

  virtual ~HeatPumpAirToWaterFuelFiredCooling() override = default;
  HeatPumpAirToWaterFuelFiredCooling(const HeatPumpAirToWaterFuelFiredCooling& other) = default;
  HeatPumpAirToWaterFuelFiredCooling(HeatPumpAirToWaterFuelFiredCooling&& other) = default;
  HeatPumpAirToWaterFuelFiredCooling& operator=(const HeatPumpAirToWaterFuelFiredCooling&) = default;
  HeatPumpAirToWaterFuelFiredCooling& operator=(HeatPumpAirToWaterFuelFiredCooling&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> fuelTypeValues();
  static std::vector<std::string> flowModeValues();
  static std::vector<std::string> outdoorAirTemperatureCurveInputVariableValues();
  static std::vector<std::string> waterTemperatureCurveInputVariableValues();

  // Schema Alignment Notes:
  // - Status: Scalar Parity. The canonical fuel-fired cooling heat-pump scalar surface is present, while companion and relationship helpers remain out of scope.
  // - Canonical Counterpart: openstudio::model::HeatPumpAirToWaterFuelFiredCooling.
  // - Implemented Parity: The preserved scalar API matches the fuel, capacity, COP, flow, sizing, temperature, and power accessors with matching autosize/default behavior.
  // - Documented Delta: Companion-heat-pump, node/object-reference, and curve/object target-link helpers remain intentionally excluded from this scalar pass.
  // - Field/Storage Mapping: These accessors map directly to EnergyPlus `HeatPump:AirToWater:FuelFired:Cooling` scalar fields used by the forward translator.
  // - Evidence: `src/model/HeatPumpAirToWaterFuelFiredCooling.hpp`, `src/model/HeatPumpAirToWaterFuelFiredCooling.cpp`, and `src/energyplus/ForwardTranslator/ForwardTranslateHeatPumpAirToWaterFuelFiredCooling.cpp`.
  // - Remaining Parity Work: Add the omitted relationship helpers without changing the preserved scalar signatures.
  std::string fuelType() const;
  bool setFuelType(const std::string& fuelType);

  std::string endUseSubcategory() const;
  bool isEndUseSubcategoryDefaulted() const;
  bool setEndUseSubcategory(const std::string& endUseSubcategory);
  void resetEndUseSubcategory();

  boost::optional<double> nominalCoolingCapacity() const;
  bool isNominalCoolingCapacityAutosized() const;
  boost::optional<double> autosizedNominalCoolingCapacity();
  bool setNominalCoolingCapacity(double nominalCoolingCapacity);
  void resetNominalCoolingCapacity();
  void autosizeNominalCoolingCapacity();

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

  double nominalAuxiliaryElectricPower() const;
  bool setNominalAuxiliaryElectricPower(double nominalAuxiliaryElectricPower);

  double standbyElectricPower() const;
  bool setStandbyElectricPower(double standbyElectricPower);

  double minimumUnloadingRatio() const;
  bool setMinimumUnloadingRatio(double minimumUnloadingRatio);

 protected:
  using ImplType = detail::HeatPumpAirToWaterFuelFiredCooling_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit HeatPumpAirToWaterFuelFiredCooling(std::shared_ptr<detail::HeatPumpAirToWaterFuelFiredCooling_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
