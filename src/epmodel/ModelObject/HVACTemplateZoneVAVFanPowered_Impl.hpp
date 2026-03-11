/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HVACTEMPLATEZONEVAVFANPOWERED_IMPL_HPP
#define EPMODEL_HVACTEMPLATEZONEVAVFANPOWERED_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API HVACTemplateZoneVAVFanPowered_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~HVACTemplateZoneVAVFanPowered_Impl() override = default;

  boost::optional<double> primarySupplyAirMaximumFlowRate() const;
  boost::optional<double> zoneHeatingSizingFactor() const;
  boost::optional<double> zoneCoolingSizingFactor() const;
  boost::optional<double> primarySupplyAirMinimumFlowFraction() const;
  boost::optional<double> secondarySupplyAirMaximumFlowRate() const;
  std::string flowType() const;
  boost::optional<double> parallelFanOnFlowFraction() const;
  std::string outdoorAirMethod() const;
  double outdoorAirFlowRateperPerson() const;
  double outdoorAirFlowRateperZoneFloorArea() const;
  double outdoorAirFlowRateperZone() const;
  std::string reheatCoilType() const;
  double fanTotalEfficiency() const;
  double fanDeltaPressure() const;
  double fanMotorEfficiency() const;
  std::string baseboardHeatingType() const;
  boost::optional<double> baseboardHeatingCapacity() const;
  std::string zoneCoolingDesignSupplyAirTemperatureInputMethod() const;
  double zoneCoolingDesignSupplyAirTemperature() const;
  double zoneCoolingDesignSupplyAirTemperatureDifference() const;
  std::string zoneHeatingDesignSupplyAirTemperatureInputMethod() const;
  double zoneHeatingDesignSupplyAirTemperature() const;
  double zoneHeatingDesignSupplyAirTemperatureDifference() const;

  bool isPrimarySupplyAirMaximumFlowRateDefaulted() const;
  bool isPrimarySupplyAirMaximumFlowRateAutosized() const;
  bool isZoneHeatingSizingFactorDefaulted() const;
  bool isZoneCoolingSizingFactorDefaulted() const;
  bool isPrimarySupplyAirMinimumFlowFractionDefaulted() const;
  bool isPrimarySupplyAirMinimumFlowFractionAutosized() const;
  bool isSecondarySupplyAirMaximumFlowRateDefaulted() const;
  bool isSecondarySupplyAirMaximumFlowRateAutosized() const;
  bool isFlowTypeDefaulted() const;
  bool isParallelFanOnFlowFractionDefaulted() const;
  bool isParallelFanOnFlowFractionAutosized() const;
  bool isOutdoorAirMethodDefaulted() const;
  bool isOutdoorAirFlowRateperPersonDefaulted() const;
  bool isOutdoorAirFlowRateperZoneFloorAreaDefaulted() const;
  bool isOutdoorAirFlowRateperZoneDefaulted() const;
  bool isReheatCoilTypeDefaulted() const;
  bool isFanTotalEfficiencyDefaulted() const;
  bool isFanDeltaPressureDefaulted() const;
  bool isFanMotorEfficiencyDefaulted() const;
  bool isBaseboardHeatingTypeDefaulted() const;
  bool isBaseboardHeatingCapacityDefaulted() const;
  bool isBaseboardHeatingCapacityAutosized() const;
  bool isZoneCoolingDesignSupplyAirTemperatureInputMethodDefaulted() const;
  bool isZoneCoolingDesignSupplyAirTemperatureDefaulted() const;
  bool isZoneCoolingDesignSupplyAirTemperatureDifferenceDefaulted() const;
  bool isZoneHeatingDesignSupplyAirTemperatureInputMethodDefaulted() const;
  bool isZoneHeatingDesignSupplyAirTemperatureDefaulted() const;
  bool isZoneHeatingDesignSupplyAirTemperatureDifferenceDefaulted() const;

  bool setPrimarySupplyAirMaximumFlowRate(double primarySupplyAirMaximumFlowRate);
  bool setZoneHeatingSizingFactor(double zoneHeatingSizingFactor);
  bool setZoneCoolingSizingFactor(double zoneCoolingSizingFactor);
  bool setPrimarySupplyAirMinimumFlowFraction(double primarySupplyAirMinimumFlowFraction);
  bool setSecondarySupplyAirMaximumFlowRate(double secondarySupplyAirMaximumFlowRate);
  bool setFlowType(const std::string& flowType);
  bool setParallelFanOnFlowFraction(double parallelFanOnFlowFraction);
  bool setOutdoorAirMethod(const std::string& outdoorAirMethod);
  bool setOutdoorAirFlowRateperPerson(double outdoorAirFlowRateperPerson);
  bool setOutdoorAirFlowRateperZoneFloorArea(double outdoorAirFlowRateperZoneFloorArea);
  bool setOutdoorAirFlowRateperZone(double outdoorAirFlowRateperZone);
  bool setReheatCoilType(const std::string& reheatCoilType);
  bool setFanTotalEfficiency(double fanTotalEfficiency);
  bool setFanDeltaPressure(double fanDeltaPressure);
  bool setFanMotorEfficiency(double fanMotorEfficiency);
  bool setBaseboardHeatingType(const std::string& baseboardHeatingType);
  bool setBaseboardHeatingCapacity(double baseboardHeatingCapacity);
  bool setZoneCoolingDesignSupplyAirTemperatureInputMethod(const std::string& zoneCoolingDesignSupplyAirTemperatureInputMethod);
  bool setZoneCoolingDesignSupplyAirTemperature(double zoneCoolingDesignSupplyAirTemperature);
  bool setZoneCoolingDesignSupplyAirTemperatureDifference(double zoneCoolingDesignSupplyAirTemperatureDifference);
  bool setZoneHeatingDesignSupplyAirTemperatureInputMethod(const std::string& zoneHeatingDesignSupplyAirTemperatureInputMethod);
  bool setZoneHeatingDesignSupplyAirTemperature(double zoneHeatingDesignSupplyAirTemperature);
  bool setZoneHeatingDesignSupplyAirTemperatureDifference(double zoneHeatingDesignSupplyAirTemperatureDifference);

  void resetPrimarySupplyAirMaximumFlowRate();
  void autosizePrimarySupplyAirMaximumFlowRate();
  void resetZoneHeatingSizingFactor();
  void resetZoneCoolingSizingFactor();
  void resetPrimarySupplyAirMinimumFlowFraction();
  void autosizePrimarySupplyAirMinimumFlowFraction();
  void resetSecondarySupplyAirMaximumFlowRate();
  void autosizeSecondarySupplyAirMaximumFlowRate();
  void resetFlowType();
  void resetParallelFanOnFlowFraction();
  void autosizeParallelFanOnFlowFraction();
  void resetOutdoorAirMethod();
  void resetOutdoorAirFlowRateperPerson();
  void resetOutdoorAirFlowRateperZoneFloorArea();
  void resetOutdoorAirFlowRateperZone();
  void resetReheatCoilType();
  void resetFanTotalEfficiency();
  void resetFanDeltaPressure();
  void resetFanMotorEfficiency();
  void resetBaseboardHeatingType();
  void resetBaseboardHeatingCapacity();
  void autosizeBaseboardHeatingCapacity();
  void resetZoneCoolingDesignSupplyAirTemperatureInputMethod();
  void resetZoneCoolingDesignSupplyAirTemperature();
  void resetZoneCoolingDesignSupplyAirTemperatureDifference();
  void resetZoneHeatingDesignSupplyAirTemperatureInputMethod();
  void resetZoneHeatingDesignSupplyAirTemperature();
  void resetZoneHeatingDesignSupplyAirTemperatureDifference();

  std::vector<std::string> flowTypeValues() const;
  std::vector<std::string> outdoorAirMethodValues() const;
  std::vector<std::string> reheatCoilTypeValues() const;
  std::vector<std::string> baseboardHeatingTypeValues() const;
  std::vector<std::string> zoneCoolingDesignSupplyAirTemperatureInputMethodValues() const;
  std::vector<std::string> zoneHeatingDesignSupplyAirTemperatureInputMethodValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
