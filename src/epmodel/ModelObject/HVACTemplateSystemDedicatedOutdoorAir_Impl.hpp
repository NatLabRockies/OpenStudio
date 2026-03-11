/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HVACTEMPLATESYSTEMDEDICATEDOUTDOORAIR_IMPL_HPP
#define EPMODEL_HVACTEMPLATESYSTEMDEDICATEDOUTDOORAIR_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API HVACTemplateSystemDedicatedOutdoorAir_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~HVACTemplateSystemDedicatedOutdoorAir_Impl() override = default;

  std::string airOutletType() const;
  boost::optional<double> supplyFanFlowRate() const;
  double supplyFanTotalEfficiency() const;
  double supplyFanDeltaPressure() const;
  double supplyFanMotorEfficiency() const;
  double supplyFanMotorinAirStreamFraction() const;
  std::string supplyFanPlacement() const;
  std::string coolingCoilType() const;
  std::string coolingCoilSetpointControlType() const;
  double coolingCoilDesignSetpoint() const;
  double coolingCoilSetpointatOutdoorDryBulbLow() const;
  double coolingCoilResetOutdoorDryBulbLow() const;
  double coolingCoilSetpointatOutdoorDryBulbHigh() const;
  double coolingCoilResetOutdoorDryBulbHigh() const;
  boost::optional<double> dXCoolingCoilGrossRatedTotalCapacity() const;
  boost::optional<double> dXCoolingCoilGrossRatedSensibleHeatRatio() const;
  double dXCoolingCoilGrossRatedCOP() const;
  std::string heatingCoilType() const;
  std::string heatingCoilSetpointControlType() const;
  double heatingCoilDesignSetpoint() const;
  double heatingCoilSetpointatOutdoorDryBulbLow() const;
  double heatingCoilResetOutdoorDryBulbLow() const;
  double heatingCoilSetpointatOutdoorDryBulbHigh() const;
  double heatingCoilResetOutdoorDryBulbHigh() const;
  double gasHeatingCoilEfficiency() const;
  double gasHeatingCoilParasiticElectricLoad() const;
  std::string heatRecoveryType() const;
  double heatRecoverySensibleEffectiveness() const;
  double heatRecoveryLatentEffectiveness() const;
  std::string heatRecoveryHeatExchangerType() const;
  std::string heatRecoveryFrostControlType() const;
  std::string dehumidificationControlType() const;
  double dehumidificationSetpoint() const;
  std::string humidifierType() const;
  double humidifierRatedCapacity() const;
  boost::optional<double> humidifierRatedElectricPower() const;
  double humidifierConstantSetpoint() const;

  bool isAirOutletTypeDefaulted() const;
  bool isSupplyFanFlowRateDefaulted() const;
  bool isSupplyFanTotalEfficiencyDefaulted() const;
  bool isSupplyFanDeltaPressureDefaulted() const;
  bool isSupplyFanMotorEfficiencyDefaulted() const;
  bool isSupplyFanMotorinAirStreamFractionDefaulted() const;
  bool isSupplyFanPlacementDefaulted() const;
  bool isCoolingCoilTypeDefaulted() const;
  bool isCoolingCoilSetpointControlTypeDefaulted() const;
  bool isCoolingCoilDesignSetpointDefaulted() const;
  bool isCoolingCoilSetpointatOutdoorDryBulbLowDefaulted() const;
  bool isCoolingCoilResetOutdoorDryBulbLowDefaulted() const;
  bool isCoolingCoilSetpointatOutdoorDryBulbHighDefaulted() const;
  bool isCoolingCoilResetOutdoorDryBulbHighDefaulted() const;
  bool isDXCoolingCoilGrossRatedTotalCapacityDefaulted() const;
  bool isDXCoolingCoilGrossRatedSensibleHeatRatioDefaulted() const;
  bool isDXCoolingCoilGrossRatedCOPDefaulted() const;
  bool isHeatingCoilTypeDefaulted() const;
  bool isHeatingCoilSetpointControlTypeDefaulted() const;
  bool isHeatingCoilDesignSetpointDefaulted() const;
  bool isHeatingCoilSetpointatOutdoorDryBulbLowDefaulted() const;
  bool isHeatingCoilResetOutdoorDryBulbLowDefaulted() const;
  bool isHeatingCoilSetpointatOutdoorDryBulbHighDefaulted() const;
  bool isHeatingCoilResetOutdoorDryBulbHighDefaulted() const;
  bool isGasHeatingCoilEfficiencyDefaulted() const;
  bool isGasHeatingCoilParasiticElectricLoadDefaulted() const;
  bool isHeatRecoveryTypeDefaulted() const;
  bool isHeatRecoverySensibleEffectivenessDefaulted() const;
  bool isHeatRecoveryLatentEffectivenessDefaulted() const;
  bool isHeatRecoveryHeatExchangerTypeDefaulted() const;
  bool isHeatRecoveryFrostControlTypeDefaulted() const;
  bool isDehumidificationControlTypeDefaulted() const;
  bool isDehumidificationSetpointDefaulted() const;
  bool isHumidifierTypeDefaulted() const;
  bool isHumidifierRatedCapacityDefaulted() const;
  bool isHumidifierRatedElectricPowerDefaulted() const;
  bool isHumidifierConstantSetpointDefaulted() const;
  bool isSupplyFanFlowRateAutosized() const;
  bool isDXCoolingCoilGrossRatedTotalCapacityAutosized() const;
  bool isDXCoolingCoilGrossRatedSensibleHeatRatioAutosized() const;
  bool isHumidifierRatedElectricPowerAutosized() const;

  bool setAirOutletType(const std::string& airOutletType);
  bool setSupplyFanFlowRate(double supplyFanFlowRate);
  bool setSupplyFanTotalEfficiency(double supplyFanTotalEfficiency);
  bool setSupplyFanDeltaPressure(double supplyFanDeltaPressure);
  bool setSupplyFanMotorEfficiency(double supplyFanMotorEfficiency);
  bool setSupplyFanMotorinAirStreamFraction(double supplyFanMotorinAirStreamFraction);
  bool setSupplyFanPlacement(const std::string& supplyFanPlacement);
  bool setCoolingCoilType(const std::string& coolingCoilType);
  bool setCoolingCoilSetpointControlType(const std::string& coolingCoilSetpointControlType);
  bool setCoolingCoilDesignSetpoint(double coolingCoilDesignSetpoint);
  bool setCoolingCoilSetpointatOutdoorDryBulbLow(double coolingCoilSetpointatOutdoorDryBulbLow);
  bool setCoolingCoilResetOutdoorDryBulbLow(double coolingCoilResetOutdoorDryBulbLow);
  bool setCoolingCoilSetpointatOutdoorDryBulbHigh(double coolingCoilSetpointatOutdoorDryBulbHigh);
  bool setCoolingCoilResetOutdoorDryBulbHigh(double coolingCoilResetOutdoorDryBulbHigh);
  bool setDXCoolingCoilGrossRatedTotalCapacity(double dXCoolingCoilGrossRatedTotalCapacity);
  bool setDXCoolingCoilGrossRatedSensibleHeatRatio(double dXCoolingCoilGrossRatedSensibleHeatRatio);
  bool setDXCoolingCoilGrossRatedCOP(double dXCoolingCoilGrossRatedCOP);
  bool setHeatingCoilType(const std::string& heatingCoilType);
  bool setHeatingCoilSetpointControlType(const std::string& heatingCoilSetpointControlType);
  bool setHeatingCoilDesignSetpoint(double heatingCoilDesignSetpoint);
  bool setHeatingCoilSetpointatOutdoorDryBulbLow(double heatingCoilSetpointatOutdoorDryBulbLow);
  bool setHeatingCoilResetOutdoorDryBulbLow(double heatingCoilResetOutdoorDryBulbLow);
  bool setHeatingCoilSetpointatOutdoorDryBulbHigh(double heatingCoilSetpointatOutdoorDryBulbHigh);
  bool setHeatingCoilResetOutdoorDryBulbHigh(double heatingCoilResetOutdoorDryBulbHigh);
  bool setGasHeatingCoilEfficiency(double gasHeatingCoilEfficiency);
  bool setGasHeatingCoilParasiticElectricLoad(double gasHeatingCoilParasiticElectricLoad);
  bool setHeatRecoveryType(const std::string& heatRecoveryType);
  bool setHeatRecoverySensibleEffectiveness(double heatRecoverySensibleEffectiveness);
  bool setHeatRecoveryLatentEffectiveness(double heatRecoveryLatentEffectiveness);
  bool setHeatRecoveryHeatExchangerType(const std::string& heatRecoveryHeatExchangerType);
  bool setHeatRecoveryFrostControlType(const std::string& heatRecoveryFrostControlType);
  bool setDehumidificationControlType(const std::string& dehumidificationControlType);
  bool setDehumidificationSetpoint(double dehumidificationSetpoint);
  bool setHumidifierType(const std::string& humidifierType);
  bool setHumidifierRatedCapacity(double humidifierRatedCapacity);
  bool setHumidifierRatedElectricPower(double humidifierRatedElectricPower);
  bool setHumidifierConstantSetpoint(double humidifierConstantSetpoint);

  void resetAirOutletType();
  void resetSupplyFanFlowRate();
  void resetSupplyFanTotalEfficiency();
  void resetSupplyFanDeltaPressure();
  void resetSupplyFanMotorEfficiency();
  void resetSupplyFanMotorinAirStreamFraction();
  void resetSupplyFanPlacement();
  void resetCoolingCoilType();
  void resetCoolingCoilSetpointControlType();
  void resetCoolingCoilDesignSetpoint();
  void resetCoolingCoilSetpointatOutdoorDryBulbLow();
  void resetCoolingCoilResetOutdoorDryBulbLow();
  void resetCoolingCoilSetpointatOutdoorDryBulbHigh();
  void resetCoolingCoilResetOutdoorDryBulbHigh();
  void resetDXCoolingCoilGrossRatedTotalCapacity();
  void resetDXCoolingCoilGrossRatedSensibleHeatRatio();
  void resetDXCoolingCoilGrossRatedCOP();
  void resetHeatingCoilType();
  void resetHeatingCoilSetpointControlType();
  void resetHeatingCoilDesignSetpoint();
  void resetHeatingCoilSetpointatOutdoorDryBulbLow();
  void resetHeatingCoilResetOutdoorDryBulbLow();
  void resetHeatingCoilSetpointatOutdoorDryBulbHigh();
  void resetHeatingCoilResetOutdoorDryBulbHigh();
  void resetGasHeatingCoilEfficiency();
  void resetGasHeatingCoilParasiticElectricLoad();
  void resetHeatRecoveryType();
  void resetHeatRecoverySensibleEffectiveness();
  void resetHeatRecoveryLatentEffectiveness();
  void resetHeatRecoveryHeatExchangerType();
  void resetHeatRecoveryFrostControlType();
  void resetDehumidificationControlType();
  void resetDehumidificationSetpoint();
  void resetHumidifierType();
  void resetHumidifierRatedCapacity();
  void resetHumidifierRatedElectricPower();
  void resetHumidifierConstantSetpoint();
  void autosizeSupplyFanFlowRate();
  void autosizeDXCoolingCoilGrossRatedTotalCapacity();
  void autosizeDXCoolingCoilGrossRatedSensibleHeatRatio();
  void autosizeHumidifierRatedElectricPower();

  std::vector<std::string> airOutletTypeValues() const;
  std::vector<std::string> supplyFanPlacementValues() const;
  std::vector<std::string> coolingCoilTypeValues() const;
  std::vector<std::string> coolingCoilSetpointControlTypeValues() const;
  std::vector<std::string> heatingCoilTypeValues() const;
  std::vector<std::string> heatingCoilSetpointControlTypeValues() const;
  std::vector<std::string> heatRecoveryTypeValues() const;
  std::vector<std::string> heatRecoveryHeatExchangerTypeValues() const;
  std::vector<std::string> heatRecoveryFrostControlTypeValues() const;
  std::vector<std::string> dehumidificationControlTypeValues() const;
  std::vector<std::string> humidifierTypeValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
