/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HVACTEMPLATEZONEVRF_IMPL_HPP
#define EPMODEL_HVACTEMPLATEZONEVRF_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API HVACTemplateZoneVRF_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~HVACTemplateZoneVRF_Impl() override = default;

  boost::optional<double> zoneHeatingSizingFactor() const;
  boost::optional<double> zoneCoolingSizingFactor() const;
  double ratedTotalHeatingCapacitySizingRatio() const;
  boost::optional<double> coolingSupplyAirFlowRate() const;
  boost::optional<double> noCoolingSupplyAirFlowRate() const;
  boost::optional<double> heatingSupplyAirFlowRate() const;
  boost::optional<double> noHeatingSupplyAirFlowRate() const;
  boost::optional<double> coolingOutdoorAirFlowRate() const;
  boost::optional<double> heatingOutdoorAirFlowRate() const;
  boost::optional<double> noLoadOutdoorAirFlowRate() const;
  std::string outdoorAirMethod() const;
  double outdoorAirFlowRateperPerson() const;
  double outdoorAirFlowRateperZoneFloorArea() const;
  double outdoorAirFlowRateperZone() const;
  std::string supplyAirFanplacement() const;
  double supplyFanTotalEfficiency() const;
  double supplyFanDeltaPressure() const;
  double supplyFanMotorEfficiency() const;
  std::string coolingCoilType() const;
  boost::optional<double> coolingCoilGrossRatedTotalCapacity() const;
  boost::optional<double> coolingCoilGrossRatedSensibleHeatRatio() const;
  std::string heatPumpHeatingCoilType() const;
  boost::optional<double> heatPumpHeatingCoilGrossRatedCapacity() const;
  double zoneTerminalUnitOnParasiticElectricEnergyUse() const;
  double zoneTerminalUnitOffParasiticElectricEnergyUse() const;
  std::string zoneCoolingDesignSupplyAirTemperatureInputMethod() const;
  double zoneCoolingDesignSupplyAirTemperature() const;
  double zoneCoolingDesignSupplyAirTemperatureDifference() const;
  std::string zoneHeatingDesignSupplyAirTemperatureInputMethod() const;
  double zoneHeatingDesignSupplyAirTemperature() const;
  double zoneHeatingDesignSupplyAirTemperatureDifference() const;
  std::string baseboardHeatingType() const;
  boost::optional<double> baseboardHeatingCapacity() const;

  bool isRatedTotalHeatingCapacitySizingRatioDefaulted() const;
  bool isCoolingSupplyAirFlowRateDefaulted() const;
  bool isCoolingSupplyAirFlowRateAutosized() const;
  bool isNoCoolingSupplyAirFlowRateDefaulted() const;
  bool isNoCoolingSupplyAirFlowRateAutosized() const;
  bool isHeatingSupplyAirFlowRateDefaulted() const;
  bool isHeatingSupplyAirFlowRateAutosized() const;
  bool isNoHeatingSupplyAirFlowRateDefaulted() const;
  bool isNoHeatingSupplyAirFlowRateAutosized() const;
  bool isCoolingOutdoorAirFlowRateDefaulted() const;
  bool isCoolingOutdoorAirFlowRateAutosized() const;
  bool isHeatingOutdoorAirFlowRateDefaulted() const;
  bool isHeatingOutdoorAirFlowRateAutosized() const;
  bool isNoLoadOutdoorAirFlowRateDefaulted() const;
  bool isNoLoadOutdoorAirFlowRateAutosized() const;
  bool isOutdoorAirMethodDefaulted() const;
  bool isOutdoorAirFlowRateperPersonDefaulted() const;
  bool isOutdoorAirFlowRateperZoneFloorAreaDefaulted() const;
  bool isOutdoorAirFlowRateperZoneDefaulted() const;
  bool isSupplyAirFanplacementDefaulted() const;
  bool isSupplyFanTotalEfficiencyDefaulted() const;
  bool isSupplyFanDeltaPressureDefaulted() const;
  bool isSupplyFanMotorEfficiencyDefaulted() const;
  bool isCoolingCoilTypeDefaulted() const;
  bool isCoolingCoilGrossRatedTotalCapacityDefaulted() const;
  bool isCoolingCoilGrossRatedTotalCapacityAutosized() const;
  bool isCoolingCoilGrossRatedSensibleHeatRatioDefaulted() const;
  bool isCoolingCoilGrossRatedSensibleHeatRatioAutosized() const;
  bool isHeatPumpHeatingCoilTypeDefaulted() const;
  bool isHeatPumpHeatingCoilGrossRatedCapacityDefaulted() const;
  bool isHeatPumpHeatingCoilGrossRatedCapacityAutosized() const;
  bool isZoneTerminalUnitOnParasiticElectricEnergyUseDefaulted() const;
  bool isZoneTerminalUnitOffParasiticElectricEnergyUseDefaulted() const;
  bool isZoneCoolingDesignSupplyAirTemperatureInputMethodDefaulted() const;
  bool isZoneCoolingDesignSupplyAirTemperatureDefaulted() const;
  bool isZoneCoolingDesignSupplyAirTemperatureDifferenceDefaulted() const;
  bool isZoneHeatingDesignSupplyAirTemperatureInputMethodDefaulted() const;
  bool isZoneHeatingDesignSupplyAirTemperatureDefaulted() const;
  bool isZoneHeatingDesignSupplyAirTemperatureDifferenceDefaulted() const;
  bool isBaseboardHeatingTypeDefaulted() const;
  bool isBaseboardHeatingCapacityDefaulted() const;
  bool isBaseboardHeatingCapacityAutosized() const;

  bool setZoneHeatingSizingFactor(double zoneHeatingSizingFactor);
  bool setZoneCoolingSizingFactor(double zoneCoolingSizingFactor);
  bool setRatedTotalHeatingCapacitySizingRatio(double ratedTotalHeatingCapacitySizingRatio);
  bool setCoolingSupplyAirFlowRate(double coolingSupplyAirFlowRate);
  bool setNoCoolingSupplyAirFlowRate(double noCoolingSupplyAirFlowRate);
  bool setHeatingSupplyAirFlowRate(double heatingSupplyAirFlowRate);
  bool setNoHeatingSupplyAirFlowRate(double noHeatingSupplyAirFlowRate);
  bool setCoolingOutdoorAirFlowRate(double coolingOutdoorAirFlowRate);
  bool setHeatingOutdoorAirFlowRate(double heatingOutdoorAirFlowRate);
  bool setNoLoadOutdoorAirFlowRate(double noLoadOutdoorAirFlowRate);
  bool setOutdoorAirMethod(const std::string& outdoorAirMethod);
  bool setOutdoorAirFlowRateperPerson(double outdoorAirFlowRateperPerson);
  bool setOutdoorAirFlowRateperZoneFloorArea(double outdoorAirFlowRateperZoneFloorArea);
  bool setOutdoorAirFlowRateperZone(double outdoorAirFlowRateperZone);
  bool setSupplyAirFanplacement(const std::string& supplyAirFanplacement);
  bool setSupplyFanTotalEfficiency(double supplyFanTotalEfficiency);
  bool setSupplyFanDeltaPressure(double supplyFanDeltaPressure);
  bool setSupplyFanMotorEfficiency(double supplyFanMotorEfficiency);
  bool setCoolingCoilType(const std::string& coolingCoilType);
  bool setCoolingCoilGrossRatedTotalCapacity(double coolingCoilGrossRatedTotalCapacity);
  bool setCoolingCoilGrossRatedSensibleHeatRatio(double coolingCoilGrossRatedSensibleHeatRatio);
  bool setHeatPumpHeatingCoilType(const std::string& heatPumpHeatingCoilType);
  bool setHeatPumpHeatingCoilGrossRatedCapacity(double heatPumpHeatingCoilGrossRatedCapacity);
  bool setZoneTerminalUnitOnParasiticElectricEnergyUse(double zoneTerminalUnitOnParasiticElectricEnergyUse);
  bool setZoneTerminalUnitOffParasiticElectricEnergyUse(double zoneTerminalUnitOffParasiticElectricEnergyUse);
  bool setZoneCoolingDesignSupplyAirTemperatureInputMethod(const std::string& zoneCoolingDesignSupplyAirTemperatureInputMethod);
  bool setZoneCoolingDesignSupplyAirTemperature(double zoneCoolingDesignSupplyAirTemperature);
  bool setZoneCoolingDesignSupplyAirTemperatureDifference(double zoneCoolingDesignSupplyAirTemperatureDifference);
  bool setZoneHeatingDesignSupplyAirTemperatureInputMethod(const std::string& zoneHeatingDesignSupplyAirTemperatureInputMethod);
  bool setZoneHeatingDesignSupplyAirTemperature(double zoneHeatingDesignSupplyAirTemperature);
  bool setZoneHeatingDesignSupplyAirTemperatureDifference(double zoneHeatingDesignSupplyAirTemperatureDifference);
  bool setBaseboardHeatingType(const std::string& baseboardHeatingType);
  bool setBaseboardHeatingCapacity(double baseboardHeatingCapacity);

  void resetZoneHeatingSizingFactor();
  void resetZoneCoolingSizingFactor();
  void resetRatedTotalHeatingCapacitySizingRatio();
  void resetCoolingSupplyAirFlowRate();
  void autosizeCoolingSupplyAirFlowRate();
  void resetNoCoolingSupplyAirFlowRate();
  void autosizeNoCoolingSupplyAirFlowRate();
  void resetHeatingSupplyAirFlowRate();
  void autosizeHeatingSupplyAirFlowRate();
  void resetNoHeatingSupplyAirFlowRate();
  void autosizeNoHeatingSupplyAirFlowRate();
  void resetCoolingOutdoorAirFlowRate();
  void autosizeCoolingOutdoorAirFlowRate();
  void resetHeatingOutdoorAirFlowRate();
  void autosizeHeatingOutdoorAirFlowRate();
  void resetNoLoadOutdoorAirFlowRate();
  void autosizeNoLoadOutdoorAirFlowRate();
  void resetOutdoorAirMethod();
  void resetOutdoorAirFlowRateperPerson();
  void resetOutdoorAirFlowRateperZoneFloorArea();
  void resetOutdoorAirFlowRateperZone();
  void resetSupplyAirFanplacement();
  void resetSupplyFanTotalEfficiency();
  void resetSupplyFanDeltaPressure();
  void resetSupplyFanMotorEfficiency();
  void resetCoolingCoilType();
  void resetCoolingCoilGrossRatedTotalCapacity();
  void autosizeCoolingCoilGrossRatedTotalCapacity();
  void resetCoolingCoilGrossRatedSensibleHeatRatio();
  void autosizeCoolingCoilGrossRatedSensibleHeatRatio();
  void resetHeatPumpHeatingCoilType();
  void resetHeatPumpHeatingCoilGrossRatedCapacity();
  void autosizeHeatPumpHeatingCoilGrossRatedCapacity();
  void resetZoneTerminalUnitOnParasiticElectricEnergyUse();
  void resetZoneTerminalUnitOffParasiticElectricEnergyUse();
  void resetZoneCoolingDesignSupplyAirTemperatureInputMethod();
  void resetZoneCoolingDesignSupplyAirTemperature();
  void resetZoneCoolingDesignSupplyAirTemperatureDifference();
  void resetZoneHeatingDesignSupplyAirTemperatureInputMethod();
  void resetZoneHeatingDesignSupplyAirTemperature();
  void resetZoneHeatingDesignSupplyAirTemperatureDifference();
  void resetBaseboardHeatingType();
  void resetBaseboardHeatingCapacity();
  void autosizeBaseboardHeatingCapacity();

  std::vector<std::string> outdoorAirMethodValues() const;
  std::vector<std::string> supplyAirFanplacementValues() const;
  std::vector<std::string> coolingCoilTypeValues() const;
  std::vector<std::string> heatPumpHeatingCoilTypeValues() const;
  std::vector<std::string> zoneCoolingDesignSupplyAirTemperatureInputMethodValues() const;
  std::vector<std::string> zoneHeatingDesignSupplyAirTemperatureInputMethodValues() const;
  std::vector<std::string> baseboardHeatingTypeValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
