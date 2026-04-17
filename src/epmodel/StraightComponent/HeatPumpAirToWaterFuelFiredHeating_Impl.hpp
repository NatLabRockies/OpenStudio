/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HEATPUMPAIRTOWATERFUELFIREDHEATING_IMPL_HPP
#define EPMODEL_HEATPUMPAIRTOWATERFUELFIREDHEATING_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

class Curve;
class HeatPumpAirToWaterFuelFiredCooling;
class Node;

namespace detail {

class EPMODEL_API HeatPumpAirToWaterFuelFiredHeating_Impl : public StraightComponent_Impl
{
 public:
  using StraightComponent_Impl::StraightComponent_Impl;
  virtual ~HeatPumpAirToWaterFuelFiredHeating_Impl() override = default;

  unsigned inletPort() const override;
  unsigned outletPort() const override;
  bool addToNode(Node& node) override;

  boost::optional<HeatPumpAirToWaterFuelFiredCooling> companionCoolingHeatPump() const;
  bool setCompanionCoolingHeatPump(const HeatPumpAirToWaterFuelFiredCooling& heatPumpAirToWaterFuelFiredCooling);
  void resetCompanionCoolingHeatPump();

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

  Curve normalizedCapacityFunctionofTemperatureCurve() const;
  bool setNormalizedCapacityFunctionofTemperatureCurve(const Curve& normalizedCapacityFunctionofTemperatureCurve);

  Curve fuelEnergyInputRatioFunctionofTemperatureCurve() const;
  bool setFuelEnergyInputRatioFunctionofTemperatureCurve(const Curve& fuelEnergyInputRatioFunctionofTemperatureCurve);

  Curve fuelEnergyInputRatioFunctionofPLRCurve() const;
  bool setFuelEnergyInputRatioFunctionofPLRCurve(const Curve& fuelEnergyInputRatioFunctionofPLRCurve);

  double minimumPartLoadRatio() const;
  bool setMinimumPartLoadRatio(double minimumPartLoadRatio);

  double maximumPartLoadRatio() const;
  bool setMaximumPartLoadRatio(double maximumPartLoadRatio);

  std::string defrostControlType() const;
  bool setDefrostControlType(const std::string& defrostControlType);

  double defrostOperationTimeFraction() const;
  bool setDefrostOperationTimeFraction(double defrostOperationTimeFraction);

  boost::optional<Curve> fuelEnergyInputRatioDefrostAdjustmentCurve() const;
  bool setFuelEnergyInputRatioDefrostAdjustmentCurve(const Curve& fuelEnergyInputRatioDefrostAdjustmentCurve);
  void resetFuelEnergyInputRatioDefrostAdjustmentCurve();

  double resistiveDefrostHeaterCapacity() const;
  bool setResistiveDefrostHeaterCapacity(double resistiveDefrostHeaterCapacity);

  double maximumOutdoorDrybulbTemperatureforDefrostOperation() const;
  bool setMaximumOutdoorDrybulbTemperatureforDefrostOperation(double maximumOutdoorDrybulbTemperatureforDefrostOperation);

  boost::optional<Curve> cyclingRatioFactorCurve() const;
  bool setCyclingRatioFactorCurve(const Curve& cyclingRatioFactorCurve);
  void resetCyclingRatioFactorCurve();

  double nominalAuxiliaryElectricPower() const;
  bool setNominalAuxiliaryElectricPower(double nominalAuxiliaryElectricPower);

  boost::optional<Curve> auxiliaryElectricEnergyInputRatioFunctionofTemperatureCurve() const;
  bool setAuxiliaryElectricEnergyInputRatioFunctionofTemperatureCurve(const Curve& auxiliaryElectricEnergyInputRatioFunctionofTemperatureCurve);
  void resetAuxiliaryElectricEnergyInputRatioFunctionofTemperatureCurve();

  boost::optional<Curve> auxiliaryElectricEnergyInputRatioFunctionofPLRCurve() const;
  bool setAuxiliaryElectricEnergyInputRatioFunctionofPLRCurve(const Curve& auxiliaryElectricEnergyInputRatioFunctionofPLRCurve);
  void resetAuxiliaryElectricEnergyInputRatioFunctionofPLRCurve();

  double standbyElectricPower() const;
  bool setStandbyElectricPower(double standbyElectricPower);

  double minimumUnloadingRatio() const;
  bool setMinimumUnloadingRatio(double minimumUnloadingRatio);

  std::vector<std::string> fuelTypeValues() const;
  std::vector<std::string> flowModeValues() const;
  std::vector<std::string> outdoorAirTemperatureCurveInputVariableValues() const;
  std::vector<std::string> waterTemperatureCurveInputVariableValues() const;
  std::vector<std::string> defrostControlTypeValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
