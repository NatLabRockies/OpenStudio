/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HVACTEMPLATESYSTEMUNITARYHEATPUMPAIRTOAIR_HPP
#define EPMODEL_HVACTEMPLATESYSTEMUNITARYHEATPUMPAIRTOAIR_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class HVACTemplateSystemUnitaryHeatPumpAirToAir_Impl;
}

class EPMODEL_API HVACTemplateSystemUnitaryHeatPumpAirToAir : public ModelObject
{
 public:
  explicit HVACTemplateSystemUnitaryHeatPumpAirToAir(const Model& model);

  virtual ~HVACTemplateSystemUnitaryHeatPumpAirToAir() override = default;
  HVACTemplateSystemUnitaryHeatPumpAirToAir(const HVACTemplateSystemUnitaryHeatPumpAirToAir& other) = default;
  HVACTemplateSystemUnitaryHeatPumpAirToAir(HVACTemplateSystemUnitaryHeatPumpAirToAir&& other) = default;
  HVACTemplateSystemUnitaryHeatPumpAirToAir& operator=(const HVACTemplateSystemUnitaryHeatPumpAirToAir&) = default;
  HVACTemplateSystemUnitaryHeatPumpAirToAir& operator=(HVACTemplateSystemUnitaryHeatPumpAirToAir&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> supplyFanPlacementValues();
  static std::vector<std::string> coolingCoilTypeValues();
  static std::vector<std::string> heatPumpHeatingCoilTypeValues();
  static std::vector<std::string> heatPumpDefrostStrategyValues();
  static std::vector<std::string> heatPumpDefrostControlValues();
  static std::vector<std::string> supplementalHeatingCoilTypeValues();
  static std::vector<std::string> economizerTypeValues();
  static std::vector<std::string> economizerLockoutValues();
  static std::vector<std::string> nightCycleControlValues();
  static std::vector<std::string> heatRecoveryTypeValues();
  static std::vector<std::string> humidifierTypeValues();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived class/accessor naming.
  // - Field Mapping: Scalar APIs map directly to HVACTemplate:System:UnitaryHeatPump:AirToAir non-name, non-link scalar fields.
  // - Field Mapping: Schedule/zone/plenum object-list fields are relationship-like and excluded from scalar accessors.
  // - TODO(parity): Add relationship/object-link APIs in a later parity pass.
  boost::optional<double> coolingSupplyAirFlowRate() const;
  boost::optional<double> heatingSupplyAirFlowRate() const;
  boost::optional<double> noLoadSupplyAirFlowRate() const;
  std::string supplyFanPlacement() const;
  double supplyFanTotalEfficiency() const;
  double supplyFanDeltaPressure() const;
  double supplyFanMotorEfficiency() const;
  double supplyFanMotorinAirStreamFraction() const;
  std::string coolingCoilType() const;
  double coolingDesignSupplyAirTemperature() const;
  boost::optional<double> coolingCoilGrossRatedTotalCapacity() const;
  boost::optional<double> coolingCoilGrossRatedSensibleHeatRatio() const;
  double coolingCoilGrossRatedCOP() const;
  std::string heatPumpHeatingCoilType() const;
  double heatingDesignSupplyAirTemperature() const;
  boost::optional<double> heatPumpHeatingCoilGrossRatedCapacity() const;
  double heatPumpHeatingCoilRatedCOP() const;
  double heatPumpHeatingMinimumOutdoorDryBulbTemperature() const;
  double heatPumpDefrostMaximumOutdoorDryBulbTemperature() const;
  std::string heatPumpDefrostStrategy() const;
  std::string heatPumpDefrostControl() const;
  double heatPumpDefrostTimePeriodFraction() const;
  std::string supplementalHeatingCoilType() const;
  boost::optional<double> supplementalHeatingCoilCapacity() const;
  double supplementalHeatingCoilMaximumOutdoorDryBulbTemperature() const;
  double supplementalGasHeatingCoilEfficiency() const;
  double supplementalGasHeatingCoilParasiticElectricLoad() const;
  boost::optional<double> maximumOutdoorAirFlowRate() const;
  boost::optional<double> minimumOutdoorAirFlowRate() const;
  std::string economizerType() const;
  std::string economizerLockout() const;
  boost::optional<double> economizerMaximumLimitDryBulbTemperature() const;
  boost::optional<double> economizerMaximumLimitEnthalpy() const;
  boost::optional<double> economizerMaximumLimitDewpointTemperature() const;
  boost::optional<double> economizerMinimumLimitDryBulbTemperature() const;
  std::string nightCycleControl() const;
  std::string heatRecoveryType() const;
  double sensibleHeatRecoveryEffectiveness() const;
  double latentHeatRecoveryEffectiveness() const;
  std::string humidifierType() const;
  double humidifierRatedCapacity() const;
  boost::optional<double> humidifierRatedElectricPower() const;
  double humidifierSetpoint() const;
  bool returnFan() const;
  double returnFanTotalEfficiency() const;
  double returnFanDeltaPressure() const;
  double returnFanMotorEfficiency() const;
  double returnFanMotorinAirStreamFraction() const;

  bool isCoolingSupplyAirFlowRateDefaulted() const;
  bool isHeatingSupplyAirFlowRateDefaulted() const;
  bool isNoLoadSupplyAirFlowRateDefaulted() const;
  bool isSupplyFanPlacementDefaulted() const;
  bool isSupplyFanTotalEfficiencyDefaulted() const;
  bool isSupplyFanDeltaPressureDefaulted() const;
  bool isSupplyFanMotorEfficiencyDefaulted() const;
  bool isSupplyFanMotorinAirStreamFractionDefaulted() const;
  bool isCoolingCoilTypeDefaulted() const;
  bool isCoolingDesignSupplyAirTemperatureDefaulted() const;
  bool isCoolingCoilGrossRatedTotalCapacityDefaulted() const;
  bool isCoolingCoilGrossRatedSensibleHeatRatioDefaulted() const;
  bool isCoolingCoilGrossRatedCOPDefaulted() const;
  bool isHeatPumpHeatingCoilTypeDefaulted() const;
  bool isHeatingDesignSupplyAirTemperatureDefaulted() const;
  bool isHeatPumpHeatingCoilGrossRatedCapacityDefaulted() const;
  bool isHeatPumpHeatingCoilRatedCOPDefaulted() const;
  bool isHeatPumpHeatingMinimumOutdoorDryBulbTemperatureDefaulted() const;
  bool isHeatPumpDefrostMaximumOutdoorDryBulbTemperatureDefaulted() const;
  bool isHeatPumpDefrostStrategyDefaulted() const;
  bool isHeatPumpDefrostControlDefaulted() const;
  bool isHeatPumpDefrostTimePeriodFractionDefaulted() const;
  bool isSupplementalHeatingCoilTypeDefaulted() const;
  bool isSupplementalHeatingCoilCapacityDefaulted() const;
  bool isSupplementalHeatingCoilMaximumOutdoorDryBulbTemperatureDefaulted() const;
  bool isSupplementalGasHeatingCoilEfficiencyDefaulted() const;
  bool isSupplementalGasHeatingCoilParasiticElectricLoadDefaulted() const;
  bool isMaximumOutdoorAirFlowRateDefaulted() const;
  bool isMinimumOutdoorAirFlowRateDefaulted() const;
  bool isEconomizerTypeDefaulted() const;
  bool isEconomizerLockoutDefaulted() const;
  bool isNightCycleControlDefaulted() const;
  bool isHeatRecoveryTypeDefaulted() const;
  bool isSensibleHeatRecoveryEffectivenessDefaulted() const;
  bool isLatentHeatRecoveryEffectivenessDefaulted() const;
  bool isHumidifierTypeDefaulted() const;
  bool isHumidifierRatedCapacityDefaulted() const;
  bool isHumidifierRatedElectricPowerDefaulted() const;
  bool isHumidifierSetpointDefaulted() const;
  bool isReturnFanDefaulted() const;
  bool isReturnFanTotalEfficiencyDefaulted() const;
  bool isReturnFanDeltaPressureDefaulted() const;
  bool isReturnFanMotorEfficiencyDefaulted() const;
  bool isReturnFanMotorinAirStreamFractionDefaulted() const;

  bool isCoolingSupplyAirFlowRateAutosized() const;
  bool isHeatingSupplyAirFlowRateAutosized() const;
  bool isNoLoadSupplyAirFlowRateAutosized() const;
  bool isCoolingCoilGrossRatedTotalCapacityAutosized() const;
  bool isCoolingCoilGrossRatedSensibleHeatRatioAutosized() const;
  bool isHeatPumpHeatingCoilGrossRatedCapacityAutosized() const;
  bool isSupplementalHeatingCoilCapacityAutosized() const;
  bool isMaximumOutdoorAirFlowRateAutosized() const;
  bool isMinimumOutdoorAirFlowRateAutosized() const;
  bool isHumidifierRatedElectricPowerAutosized() const;

  bool setCoolingSupplyAirFlowRate(double coolingSupplyAirFlowRate);
  bool setHeatingSupplyAirFlowRate(double heatingSupplyAirFlowRate);
  bool setNoLoadSupplyAirFlowRate(double noLoadSupplyAirFlowRate);
  bool setSupplyFanPlacement(const std::string& supplyFanPlacement);
  bool setSupplyFanTotalEfficiency(double supplyFanTotalEfficiency);
  bool setSupplyFanDeltaPressure(double supplyFanDeltaPressure);
  bool setSupplyFanMotorEfficiency(double supplyFanMotorEfficiency);
  bool setSupplyFanMotorinAirStreamFraction(double supplyFanMotorinAirStreamFraction);
  bool setCoolingCoilType(const std::string& coolingCoilType);
  bool setCoolingDesignSupplyAirTemperature(double coolingDesignSupplyAirTemperature);
  bool setCoolingCoilGrossRatedTotalCapacity(double coolingCoilGrossRatedTotalCapacity);
  bool setCoolingCoilGrossRatedSensibleHeatRatio(double coolingCoilGrossRatedSensibleHeatRatio);
  bool setCoolingCoilGrossRatedCOP(double coolingCoilGrossRatedCOP);
  bool setHeatPumpHeatingCoilType(const std::string& heatPumpHeatingCoilType);
  bool setHeatingDesignSupplyAirTemperature(double heatingDesignSupplyAirTemperature);
  bool setHeatPumpHeatingCoilGrossRatedCapacity(double heatPumpHeatingCoilGrossRatedCapacity);
  bool setHeatPumpHeatingCoilRatedCOP(double heatPumpHeatingCoilRatedCOP);
  bool setHeatPumpHeatingMinimumOutdoorDryBulbTemperature(double heatPumpHeatingMinimumOutdoorDryBulbTemperature);
  bool setHeatPumpDefrostMaximumOutdoorDryBulbTemperature(double heatPumpDefrostMaximumOutdoorDryBulbTemperature);
  bool setHeatPumpDefrostStrategy(const std::string& heatPumpDefrostStrategy);
  bool setHeatPumpDefrostControl(const std::string& heatPumpDefrostControl);
  bool setHeatPumpDefrostTimePeriodFraction(double heatPumpDefrostTimePeriodFraction);
  bool setSupplementalHeatingCoilType(const std::string& supplementalHeatingCoilType);
  bool setSupplementalHeatingCoilCapacity(double supplementalHeatingCoilCapacity);
  bool setSupplementalHeatingCoilMaximumOutdoorDryBulbTemperature(double supplementalHeatingCoilMaximumOutdoorDryBulbTemperature);
  bool setSupplementalGasHeatingCoilEfficiency(double supplementalGasHeatingCoilEfficiency);
  bool setSupplementalGasHeatingCoilParasiticElectricLoad(double supplementalGasHeatingCoilParasiticElectricLoad);
  bool setMaximumOutdoorAirFlowRate(double maximumOutdoorAirFlowRate);
  bool setMinimumOutdoorAirFlowRate(double minimumOutdoorAirFlowRate);
  bool setEconomizerType(const std::string& economizerType);
  bool setEconomizerLockout(const std::string& economizerLockout);
  bool setEconomizerMaximumLimitDryBulbTemperature(double economizerMaximumLimitDryBulbTemperature);
  bool setEconomizerMaximumLimitEnthalpy(double economizerMaximumLimitEnthalpy);
  bool setEconomizerMaximumLimitDewpointTemperature(double economizerMaximumLimitDewpointTemperature);
  bool setEconomizerMinimumLimitDryBulbTemperature(double economizerMinimumLimitDryBulbTemperature);
  bool setNightCycleControl(const std::string& nightCycleControl);
  bool setHeatRecoveryType(const std::string& heatRecoveryType);
  bool setSensibleHeatRecoveryEffectiveness(double sensibleHeatRecoveryEffectiveness);
  bool setLatentHeatRecoveryEffectiveness(double latentHeatRecoveryEffectiveness);
  bool setHumidifierType(const std::string& humidifierType);
  bool setHumidifierRatedCapacity(double humidifierRatedCapacity);
  bool setHumidifierRatedElectricPower(double humidifierRatedElectricPower);
  bool setHumidifierSetpoint(double humidifierSetpoint);
  bool setReturnFan(bool returnFan);
  bool setReturnFanTotalEfficiency(double returnFanTotalEfficiency);
  bool setReturnFanDeltaPressure(double returnFanDeltaPressure);
  bool setReturnFanMotorEfficiency(double returnFanMotorEfficiency);
  bool setReturnFanMotorinAirStreamFraction(double returnFanMotorinAirStreamFraction);

  void resetCoolingSupplyAirFlowRate();
  void resetHeatingSupplyAirFlowRate();
  void resetNoLoadSupplyAirFlowRate();
  void resetSupplyFanPlacement();
  void resetSupplyFanTotalEfficiency();
  void resetSupplyFanDeltaPressure();
  void resetSupplyFanMotorEfficiency();
  void resetSupplyFanMotorinAirStreamFraction();
  void resetCoolingCoilType();
  void resetCoolingDesignSupplyAirTemperature();
  void resetCoolingCoilGrossRatedTotalCapacity();
  void resetCoolingCoilGrossRatedSensibleHeatRatio();
  void resetCoolingCoilGrossRatedCOP();
  void resetHeatPumpHeatingCoilType();
  void resetHeatingDesignSupplyAirTemperature();
  void resetHeatPumpHeatingCoilGrossRatedCapacity();
  void resetHeatPumpHeatingCoilRatedCOP();
  void resetHeatPumpHeatingMinimumOutdoorDryBulbTemperature();
  void resetHeatPumpDefrostMaximumOutdoorDryBulbTemperature();
  void resetHeatPumpDefrostStrategy();
  void resetHeatPumpDefrostControl();
  void resetHeatPumpDefrostTimePeriodFraction();
  void resetSupplementalHeatingCoilType();
  void resetSupplementalHeatingCoilCapacity();
  void resetSupplementalHeatingCoilMaximumOutdoorDryBulbTemperature();
  void resetSupplementalGasHeatingCoilEfficiency();
  void resetSupplementalGasHeatingCoilParasiticElectricLoad();
  void resetMaximumOutdoorAirFlowRate();
  void resetMinimumOutdoorAirFlowRate();
  void resetEconomizerType();
  void resetEconomizerLockout();
  void resetEconomizerMaximumLimitDryBulbTemperature();
  void resetEconomizerMaximumLimitEnthalpy();
  void resetEconomizerMaximumLimitDewpointTemperature();
  void resetEconomizerMinimumLimitDryBulbTemperature();
  void resetNightCycleControl();
  void resetHeatRecoveryType();
  void resetSensibleHeatRecoveryEffectiveness();
  void resetLatentHeatRecoveryEffectiveness();
  void resetHumidifierType();
  void resetHumidifierRatedCapacity();
  void resetHumidifierRatedElectricPower();
  void resetHumidifierSetpoint();
  void resetReturnFan();
  void resetReturnFanTotalEfficiency();
  void resetReturnFanDeltaPressure();
  void resetReturnFanMotorEfficiency();
  void resetReturnFanMotorinAirStreamFraction();

  void autosizeCoolingSupplyAirFlowRate();
  void autosizeHeatingSupplyAirFlowRate();
  void autosizeNoLoadSupplyAirFlowRate();
  void autosizeCoolingCoilGrossRatedTotalCapacity();
  void autosizeCoolingCoilGrossRatedSensibleHeatRatio();
  void autosizeHeatPumpHeatingCoilGrossRatedCapacity();
  void autosizeSupplementalHeatingCoilCapacity();
  void autosizeMaximumOutdoorAirFlowRate();
  void autosizeMinimumOutdoorAirFlowRate();
  void autosizeHumidifierRatedElectricPower();

 protected:
  using ImplType = detail::HVACTemplateSystemUnitaryHeatPumpAirToAir_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit HVACTemplateSystemUnitaryHeatPumpAirToAir(std::shared_ptr<detail::HVACTemplateSystemUnitaryHeatPumpAirToAir_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
