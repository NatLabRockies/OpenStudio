/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HEATPUMPAIRTOWATERFUELFIREDCOOLING_IMPL_HPP
#define EPMODEL_HEATPUMPAIRTOWATERFUELFIREDCOOLING_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API HeatPumpAirToWaterFuelFiredCooling_Impl : public StraightComponent_Impl
{
 public:
  using StraightComponent_Impl::StraightComponent_Impl;
  virtual ~HeatPumpAirToWaterFuelFiredCooling_Impl() override = default;

  // Schema Alignment Notes:
  // - API: selected inventory row idd_type is OutdoorAir:Node, but Impl methods intentionally target
  //   HeatPump_AirToWater_FuelFired_CoolingFields to preserve openstudio::model scalar API parity.
  unsigned inletPort() const override;
  unsigned outletPort() const override;

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

  std::vector<std::string> fuelTypeValues() const;
  std::vector<std::string> flowModeValues() const;
  std::vector<std::string> outdoorAirTemperatureCurveInputVariableValues() const;
  std::vector<std::string> waterTemperatureCurveInputVariableValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
