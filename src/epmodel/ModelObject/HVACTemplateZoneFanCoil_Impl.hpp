/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HVACTEMPLATEZONEFANCOIL_IMPL_HPP
#define EPMODEL_HVACTEMPLATEZONEFANCOIL_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API HVACTemplateZoneFanCoil_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~HVACTemplateZoneFanCoil_Impl() override = default;

  boost::optional<double> supplyAirMaximumFlowRate() const;
  boost::optional<double> zoneHeatingSizingFactor() const;
  boost::optional<double> zoneCoolingSizingFactor() const;
  std::string outdoorAirMethod() const;
  double outdoorAirFlowRateperPerson() const;
  double outdoorAirFlowRateperZoneFloorArea() const;
  double outdoorAirFlowRateperZone() const;
  double supplyFanTotalEfficiency() const;
  double supplyFanDeltaPressure() const;
  double supplyFanMotorEfficiency() const;
  double supplyFanMotorinAirStreamFraction() const;
  std::string coolingCoilType() const;
  double coolingCoilDesignSetpoint() const;
  std::string heatingCoilType() const;
  double heatingCoilDesignSetpoint() const;
  std::string zoneCoolingDesignSupplyAirTemperatureInputMethod() const;
  double zoneCoolingDesignSupplyAirTemperatureDifference() const;
  std::string zoneHeatingDesignSupplyAirTemperatureInputMethod() const;
  double zoneHeatingDesignSupplyAirTemperatureDifference() const;
  boost::optional<std::string> capacityControlMethod() const;
  double lowSpeedSupplyAirFlowRatio() const;
  double mediumSpeedSupplyAirFlowRatio() const;
  std::string baseboardHeatingType() const;
  boost::optional<double> baseboardHeatingCapacity() const;

  bool isSupplyAirMaximumFlowRateDefaulted() const;
  bool isSupplyAirMaximumFlowRateAutosized() const;
  bool isOutdoorAirMethodDefaulted() const;
  bool isOutdoorAirFlowRateperPersonDefaulted() const;
  bool isOutdoorAirFlowRateperZoneFloorAreaDefaulted() const;
  bool isOutdoorAirFlowRateperZoneDefaulted() const;
  bool isSupplyFanTotalEfficiencyDefaulted() const;
  bool isSupplyFanDeltaPressureDefaulted() const;
  bool isSupplyFanMotorEfficiencyDefaulted() const;
  bool isSupplyFanMotorinAirStreamFractionDefaulted() const;
  bool isCoolingCoilTypeDefaulted() const;
  bool isCoolingCoilDesignSetpointDefaulted() const;
  bool isHeatingCoilTypeDefaulted() const;
  bool isHeatingCoilDesignSetpointDefaulted() const;
  bool isZoneCoolingDesignSupplyAirTemperatureInputMethodDefaulted() const;
  bool isZoneCoolingDesignSupplyAirTemperatureDifferenceDefaulted() const;
  bool isZoneHeatingDesignSupplyAirTemperatureInputMethodDefaulted() const;
  bool isZoneHeatingDesignSupplyAirTemperatureDifferenceDefaulted() const;
  bool isLowSpeedSupplyAirFlowRatioDefaulted() const;
  bool isMediumSpeedSupplyAirFlowRatioDefaulted() const;
  bool isBaseboardHeatingTypeDefaulted() const;
  bool isBaseboardHeatingCapacityDefaulted() const;
  bool isBaseboardHeatingCapacityAutosized() const;

  bool setSupplyAirMaximumFlowRate(double supplyAirMaximumFlowRate);
  bool setZoneHeatingSizingFactor(double zoneHeatingSizingFactor);
  bool setZoneCoolingSizingFactor(double zoneCoolingSizingFactor);
  bool setOutdoorAirMethod(const std::string& outdoorAirMethod);
  bool setOutdoorAirFlowRateperPerson(double outdoorAirFlowRateperPerson);
  bool setOutdoorAirFlowRateperZoneFloorArea(double outdoorAirFlowRateperZoneFloorArea);
  bool setOutdoorAirFlowRateperZone(double outdoorAirFlowRateperZone);
  bool setSupplyFanTotalEfficiency(double supplyFanTotalEfficiency);
  bool setSupplyFanDeltaPressure(double supplyFanDeltaPressure);
  bool setSupplyFanMotorEfficiency(double supplyFanMotorEfficiency);
  bool setSupplyFanMotorinAirStreamFraction(double supplyFanMotorinAirStreamFraction);
  bool setCoolingCoilType(const std::string& coolingCoilType);
  bool setCoolingCoilDesignSetpoint(double coolingCoilDesignSetpoint);
  bool setHeatingCoilType(const std::string& heatingCoilType);
  bool setHeatingCoilDesignSetpoint(double heatingCoilDesignSetpoint);
  bool setZoneCoolingDesignSupplyAirTemperatureInputMethod(const std::string& zoneCoolingDesignSupplyAirTemperatureInputMethod);
  bool setZoneCoolingDesignSupplyAirTemperatureDifference(double zoneCoolingDesignSupplyAirTemperatureDifference);
  bool setZoneHeatingDesignSupplyAirTemperatureInputMethod(const std::string& zoneHeatingDesignSupplyAirTemperatureInputMethod);
  bool setZoneHeatingDesignSupplyAirTemperatureDifference(double zoneHeatingDesignSupplyAirTemperatureDifference);
  bool setCapacityControlMethod(const std::string& capacityControlMethod);
  bool setLowSpeedSupplyAirFlowRatio(double lowSpeedSupplyAirFlowRatio);
  bool setMediumSpeedSupplyAirFlowRatio(double mediumSpeedSupplyAirFlowRatio);
  bool setBaseboardHeatingType(const std::string& baseboardHeatingType);
  bool setBaseboardHeatingCapacity(double baseboardHeatingCapacity);

  void resetSupplyAirMaximumFlowRate();
  void autosizeSupplyAirMaximumFlowRate();
  void resetZoneHeatingSizingFactor();
  void resetZoneCoolingSizingFactor();
  void resetOutdoorAirMethod();
  void resetOutdoorAirFlowRateperPerson();
  void resetOutdoorAirFlowRateperZoneFloorArea();
  void resetOutdoorAirFlowRateperZone();
  void resetSupplyFanTotalEfficiency();
  void resetSupplyFanDeltaPressure();
  void resetSupplyFanMotorEfficiency();
  void resetSupplyFanMotorinAirStreamFraction();
  void resetCoolingCoilType();
  void resetCoolingCoilDesignSetpoint();
  void resetHeatingCoilType();
  void resetHeatingCoilDesignSetpoint();
  void resetZoneCoolingDesignSupplyAirTemperatureInputMethod();
  void resetZoneCoolingDesignSupplyAirTemperatureDifference();
  void resetZoneHeatingDesignSupplyAirTemperatureInputMethod();
  void resetZoneHeatingDesignSupplyAirTemperatureDifference();
  void resetCapacityControlMethod();
  void resetLowSpeedSupplyAirFlowRatio();
  void resetMediumSpeedSupplyAirFlowRatio();
  void resetBaseboardHeatingType();
  void resetBaseboardHeatingCapacity();
  void autosizeBaseboardHeatingCapacity();

  std::vector<std::string> outdoorAirMethodValues() const;
  std::vector<std::string> coolingCoilTypeValues() const;
  std::vector<std::string> heatingCoilTypeValues() const;
  std::vector<std::string> zoneCoolingDesignSupplyAirTemperatureInputMethodValues() const;
  std::vector<std::string> zoneHeatingDesignSupplyAirTemperatureInputMethodValues() const;
  std::vector<std::string> capacityControlMethodValues() const;
  std::vector<std::string> baseboardHeatingTypeValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
