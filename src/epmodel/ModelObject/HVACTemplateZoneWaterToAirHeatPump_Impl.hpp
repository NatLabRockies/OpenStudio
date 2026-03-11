/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HVACTEMPLATEZONEWATERTOAIRHEATPUMP_IMPL_HPP
#define EPMODEL_HVACTEMPLATEZONEWATERTOAIRHEATPUMP_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API HVACTemplateZoneWaterToAirHeatPump_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~HVACTemplateZoneWaterToAirHeatPump_Impl() override = default;

  boost::optional<double> coolingSupplyAirFlowRate() const;
  boost::optional<double> heatingSupplyAirFlowRate() const;
  boost::optional<double> noLoadSupplyAirFlowRate() const;
  boost::optional<double> zoneHeatingSizingFactor() const;
  boost::optional<double> zoneCoolingSizingFactor() const;
  std::string outdoorAirMethod() const;
  double outdoorAirFlowRateperPerson() const;
  double outdoorAirFlowRateperZoneFloorArea() const;
  double outdoorAirFlowRateperZone() const;
  std::string supplyFanPlacement() const;
  double supplyFanTotalEfficiency() const;
  double supplyFanDeltaPressure() const;
  double supplyFanMotorEfficiency() const;
  std::string coolingCoilType() const;
  boost::optional<double> coolingCoilGrossRatedTotalCapacity() const;
  boost::optional<double> coolingCoilGrossRatedSensibleHeatRatio() const;
  double coolingCoilGrossRatedCOP() const;
  std::string heatPumpHeatingCoilType() const;
  boost::optional<double> heatPumpHeatingCoilGrossRatedCapacity() const;
  double heatPumpHeatingCoilGrossRatedCOP() const;
  boost::optional<double> supplementalHeatingCoilCapacity() const;
  double maximumCyclingRate() const;
  double latentCapacityTimeConstant() const;
  double heatPumpFanDelayTime() const;
  std::string supplementalHeatingCoilType() const;
  std::string zoneCoolingDesignSupplyAirTemperatureInputMethod() const;
  double zoneCoolingDesignSupplyAirTemperature() const;
  double zoneCoolingDesignSupplyAirTemperatureDifference() const;
  std::string zoneHeatingDesignSupplyAirTemperatureInputMethod() const;
  double zoneHeatingDesignSupplyAirTemperature() const;
  double zoneHeatingDesignSupplyAirTemperatureDifference() const;
  std::string heatPumpCoilWaterFlowMode() const;
  std::string baseboardHeatingType() const;
  boost::optional<double> baseboardHeatingCapacity() const;

  bool isCoolingSupplyAirFlowRateDefaulted() const;
  bool isHeatingSupplyAirFlowRateDefaulted() const;
  bool isOutdoorAirMethodDefaulted() const;
  bool isOutdoorAirFlowRateperPersonDefaulted() const;
  bool isOutdoorAirFlowRateperZoneFloorAreaDefaulted() const;
  bool isOutdoorAirFlowRateperZoneDefaulted() const;
  bool isSupplyFanPlacementDefaulted() const;
  bool isSupplyFanTotalEfficiencyDefaulted() const;
  bool isSupplyFanDeltaPressureDefaulted() const;
  bool isSupplyFanMotorEfficiencyDefaulted() const;
  bool isCoolingCoilTypeDefaulted() const;
  bool isCoolingCoilGrossRatedTotalCapacityDefaulted() const;
  bool isCoolingCoilGrossRatedSensibleHeatRatioDefaulted() const;
  bool isCoolingCoilGrossRatedCOPDefaulted() const;
  bool isHeatPumpHeatingCoilTypeDefaulted() const;
  bool isHeatPumpHeatingCoilGrossRatedCapacityDefaulted() const;
  bool isHeatPumpHeatingCoilGrossRatedCOPDefaulted() const;
  bool isSupplementalHeatingCoilCapacityDefaulted() const;
  bool isMaximumCyclingRateDefaulted() const;
  bool isLatentCapacityTimeConstantDefaulted() const;
  bool isHeatPumpFanDelayTimeDefaulted() const;
  bool isSupplementalHeatingCoilTypeDefaulted() const;
  bool isZoneCoolingDesignSupplyAirTemperatureInputMethodDefaulted() const;
  bool isZoneCoolingDesignSupplyAirTemperatureDefaulted() const;
  bool isZoneCoolingDesignSupplyAirTemperatureDifferenceDefaulted() const;
  bool isZoneHeatingDesignSupplyAirTemperatureInputMethodDefaulted() const;
  bool isZoneHeatingDesignSupplyAirTemperatureDefaulted() const;
  bool isZoneHeatingDesignSupplyAirTemperatureDifferenceDefaulted() const;
  bool isHeatPumpCoilWaterFlowModeDefaulted() const;
  bool isBaseboardHeatingTypeDefaulted() const;
  bool isBaseboardHeatingCapacityDefaulted() const;
  bool isCoolingSupplyAirFlowRateAutosized() const;
  bool isHeatingSupplyAirFlowRateAutosized() const;
  bool isNoLoadSupplyAirFlowRateAutosized() const;
  bool isCoolingCoilGrossRatedTotalCapacityAutosized() const;
  bool isCoolingCoilGrossRatedSensibleHeatRatioAutosized() const;
  bool isHeatPumpHeatingCoilGrossRatedCapacityAutosized() const;
  bool isSupplementalHeatingCoilCapacityAutosized() const;
  bool isBaseboardHeatingCapacityAutosized() const;

  bool setCoolingSupplyAirFlowRate(double coolingSupplyAirFlowRate);
  bool setHeatingSupplyAirFlowRate(double heatingSupplyAirFlowRate);
  bool setNoLoadSupplyAirFlowRate(double noLoadSupplyAirFlowRate);
  bool setZoneHeatingSizingFactor(double zoneHeatingSizingFactor);
  bool setZoneCoolingSizingFactor(double zoneCoolingSizingFactor);
  bool setOutdoorAirMethod(const std::string& outdoorAirMethod);
  bool setOutdoorAirFlowRateperPerson(double outdoorAirFlowRateperPerson);
  bool setOutdoorAirFlowRateperZoneFloorArea(double outdoorAirFlowRateperZoneFloorArea);
  bool setOutdoorAirFlowRateperZone(double outdoorAirFlowRateperZone);
  bool setSupplyFanPlacement(const std::string& supplyFanPlacement);
  bool setSupplyFanTotalEfficiency(double supplyFanTotalEfficiency);
  bool setSupplyFanDeltaPressure(double supplyFanDeltaPressure);
  bool setSupplyFanMotorEfficiency(double supplyFanMotorEfficiency);
  bool setCoolingCoilType(const std::string& coolingCoilType);
  bool setCoolingCoilGrossRatedTotalCapacity(double coolingCoilGrossRatedTotalCapacity);
  bool setCoolingCoilGrossRatedSensibleHeatRatio(double coolingCoilGrossRatedSensibleHeatRatio);
  bool setCoolingCoilGrossRatedCOP(double coolingCoilGrossRatedCOP);
  bool setHeatPumpHeatingCoilType(const std::string& heatPumpHeatingCoilType);
  bool setHeatPumpHeatingCoilGrossRatedCapacity(double heatPumpHeatingCoilGrossRatedCapacity);
  bool setHeatPumpHeatingCoilGrossRatedCOP(double heatPumpHeatingCoilGrossRatedCOP);
  bool setSupplementalHeatingCoilCapacity(double supplementalHeatingCoilCapacity);
  bool setMaximumCyclingRate(double maximumCyclingRate);
  bool setLatentCapacityTimeConstant(double latentCapacityTimeConstant);
  bool setHeatPumpFanDelayTime(double heatPumpFanDelayTime);
  bool setSupplementalHeatingCoilType(const std::string& supplementalHeatingCoilType);
  bool setZoneCoolingDesignSupplyAirTemperatureInputMethod(const std::string& zoneCoolingDesignSupplyAirTemperatureInputMethod);
  bool setZoneCoolingDesignSupplyAirTemperature(double zoneCoolingDesignSupplyAirTemperature);
  bool setZoneCoolingDesignSupplyAirTemperatureDifference(double zoneCoolingDesignSupplyAirTemperatureDifference);
  bool setZoneHeatingDesignSupplyAirTemperatureInputMethod(const std::string& zoneHeatingDesignSupplyAirTemperatureInputMethod);
  bool setZoneHeatingDesignSupplyAirTemperature(double zoneHeatingDesignSupplyAirTemperature);
  bool setZoneHeatingDesignSupplyAirTemperatureDifference(double zoneHeatingDesignSupplyAirTemperatureDifference);
  bool setHeatPumpCoilWaterFlowMode(const std::string& heatPumpCoilWaterFlowMode);
  bool setBaseboardHeatingType(const std::string& baseboardHeatingType);
  bool setBaseboardHeatingCapacity(double baseboardHeatingCapacity);

  void resetCoolingSupplyAirFlowRate();
  void resetHeatingSupplyAirFlowRate();
  void resetNoLoadSupplyAirFlowRate();
  void resetZoneHeatingSizingFactor();
  void resetZoneCoolingSizingFactor();
  void resetOutdoorAirMethod();
  void resetOutdoorAirFlowRateperPerson();
  void resetOutdoorAirFlowRateperZoneFloorArea();
  void resetOutdoorAirFlowRateperZone();
  void resetSupplyFanPlacement();
  void resetSupplyFanTotalEfficiency();
  void resetSupplyFanDeltaPressure();
  void resetSupplyFanMotorEfficiency();
  void resetCoolingCoilType();
  void resetCoolingCoilGrossRatedTotalCapacity();
  void resetCoolingCoilGrossRatedSensibleHeatRatio();
  void resetCoolingCoilGrossRatedCOP();
  void resetHeatPumpHeatingCoilType();
  void resetHeatPumpHeatingCoilGrossRatedCapacity();
  void resetHeatPumpHeatingCoilGrossRatedCOP();
  void resetSupplementalHeatingCoilCapacity();
  void resetMaximumCyclingRate();
  void resetLatentCapacityTimeConstant();
  void resetHeatPumpFanDelayTime();
  void resetSupplementalHeatingCoilType();
  void resetZoneCoolingDesignSupplyAirTemperatureInputMethod();
  void resetZoneCoolingDesignSupplyAirTemperature();
  void resetZoneCoolingDesignSupplyAirTemperatureDifference();
  void resetZoneHeatingDesignSupplyAirTemperatureInputMethod();
  void resetZoneHeatingDesignSupplyAirTemperature();
  void resetZoneHeatingDesignSupplyAirTemperatureDifference();
  void resetHeatPumpCoilWaterFlowMode();
  void resetBaseboardHeatingType();
  void resetBaseboardHeatingCapacity();
  void autosizeCoolingSupplyAirFlowRate();
  void autosizeHeatingSupplyAirFlowRate();
  void autosizeNoLoadSupplyAirFlowRate();
  void autosizeCoolingCoilGrossRatedTotalCapacity();
  void autosizeCoolingCoilGrossRatedSensibleHeatRatio();
  void autosizeHeatPumpHeatingCoilGrossRatedCapacity();
  void autosizeSupplementalHeatingCoilCapacity();
  void autosizeBaseboardHeatingCapacity();

  std::vector<std::string> outdoorAirMethodValues() const;
  std::vector<std::string> supplyFanPlacementValues() const;
  std::vector<std::string> coolingCoilTypeValues() const;
  std::vector<std::string> heatPumpHeatingCoilTypeValues() const;
  std::vector<std::string> supplementalHeatingCoilTypeValues() const;
  std::vector<std::string> zoneCoolingDesignSupplyAirTemperatureInputMethodValues() const;
  std::vector<std::string> zoneHeatingDesignSupplyAirTemperatureInputMethodValues() const;
  std::vector<std::string> heatPumpCoilWaterFlowModeValues() const;
  std::vector<std::string> baseboardHeatingTypeValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif