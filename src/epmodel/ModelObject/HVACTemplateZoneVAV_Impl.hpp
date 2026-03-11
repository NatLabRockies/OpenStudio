/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HVACTEMPLATEZONEVAV_IMPL_HPP
#define EPMODEL_HVACTEMPLATEZONEVAV_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API HVACTemplateZoneVAV_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~HVACTemplateZoneVAV_Impl() override = default;

  boost::optional<double> supplyAirMaximumFlowRate() const;
  boost::optional<double> zoneHeatingSizingFactor() const;
  boost::optional<double> zoneCoolingSizingFactor() const;
  std::string zoneMinimumAirFlowInputMethod() const;
  double constantMinimumAirFlowFraction() const;
  boost::optional<double> fixedMinimumAirFlowRate() const;
  std::string outdoorAirMethod() const;
  double outdoorAirFlowRateperPerson() const;
  double outdoorAirFlowRateperZoneFloorArea() const;
  double outdoorAirFlowRateperZone() const;
  std::string reheatCoilType() const;
  std::string damperHeatingAction() const;
  boost::optional<double> maximumFlowperZoneFloorAreaDuringReheat() const;
  boost::optional<double> maximumFlowFractionDuringReheat() const;
  boost::optional<double> maximumReheatAirTemperature() const;
  std::string baseboardHeatingType() const;
  boost::optional<double> baseboardHeatingCapacity() const;
  std::string zoneCoolingDesignSupplyAirTemperatureInputMethod() const;
  double zoneCoolingDesignSupplyAirTemperature() const;
  double zoneCoolingDesignSupplyAirTemperatureDifference() const;
  std::string zoneHeatingDesignSupplyAirTemperatureInputMethod() const;
  double zoneHeatingDesignSupplyAirTemperature() const;
  double zoneHeatingDesignSupplyAirTemperatureDifference() const;

  bool isSupplyAirMaximumFlowRateDefaulted() const;
  bool isSupplyAirMaximumFlowRateAutosized() const;
  bool isZoneMinimumAirFlowInputMethodDefaulted() const;
  bool isConstantMinimumAirFlowFractionDefaulted() const;
  bool isFixedMinimumAirFlowRateDefaulted() const;
  bool isOutdoorAirMethodDefaulted() const;
  bool isOutdoorAirFlowRateperPersonDefaulted() const;
  bool isOutdoorAirFlowRateperZoneFloorAreaDefaulted() const;
  bool isOutdoorAirFlowRateperZoneDefaulted() const;
  bool isReheatCoilTypeDefaulted() const;
  bool isDamperHeatingActionDefaulted() const;
  bool isMaximumFlowperZoneFloorAreaDuringReheatDefaulted() const;
  bool isMaximumFlowperZoneFloorAreaDuringReheatAutocalculated() const;
  bool isMaximumFlowFractionDuringReheatDefaulted() const;
  bool isMaximumFlowFractionDuringReheatAutocalculated() const;
  bool isMaximumReheatAirTemperatureDefaulted() const;
  bool isBaseboardHeatingTypeDefaulted() const;
  bool isBaseboardHeatingCapacityDefaulted() const;
  bool isBaseboardHeatingCapacityAutosized() const;
  bool isZoneCoolingDesignSupplyAirTemperatureInputMethodDefaulted() const;
  bool isZoneCoolingDesignSupplyAirTemperatureDefaulted() const;
  bool isZoneCoolingDesignSupplyAirTemperatureDifferenceDefaulted() const;
  bool isZoneHeatingDesignSupplyAirTemperatureInputMethodDefaulted() const;
  bool isZoneHeatingDesignSupplyAirTemperatureDefaulted() const;
  bool isZoneHeatingDesignSupplyAirTemperatureDifferenceDefaulted() const;

  bool setSupplyAirMaximumFlowRate(double supplyAirMaximumFlowRate);
  bool setZoneHeatingSizingFactor(double zoneHeatingSizingFactor);
  bool setZoneCoolingSizingFactor(double zoneCoolingSizingFactor);
  bool setZoneMinimumAirFlowInputMethod(const std::string& zoneMinimumAirFlowInputMethod);
  bool setConstantMinimumAirFlowFraction(double constantMinimumAirFlowFraction);
  bool setFixedMinimumAirFlowRate(double fixedMinimumAirFlowRate);
  bool setOutdoorAirMethod(const std::string& outdoorAirMethod);
  bool setOutdoorAirFlowRateperPerson(double outdoorAirFlowRateperPerson);
  bool setOutdoorAirFlowRateperZoneFloorArea(double outdoorAirFlowRateperZoneFloorArea);
  bool setOutdoorAirFlowRateperZone(double outdoorAirFlowRateperZone);
  bool setReheatCoilType(const std::string& reheatCoilType);
  bool setDamperHeatingAction(const std::string& damperHeatingAction);
  bool setMaximumFlowperZoneFloorAreaDuringReheat(double maximumFlowperZoneFloorAreaDuringReheat);
  bool setMaximumFlowFractionDuringReheat(double maximumFlowFractionDuringReheat);
  bool setMaximumReheatAirTemperature(double maximumReheatAirTemperature);
  bool setBaseboardHeatingType(const std::string& baseboardHeatingType);
  bool setBaseboardHeatingCapacity(double baseboardHeatingCapacity);
  bool setZoneCoolingDesignSupplyAirTemperatureInputMethod(const std::string& zoneCoolingDesignSupplyAirTemperatureInputMethod);
  bool setZoneCoolingDesignSupplyAirTemperature(double zoneCoolingDesignSupplyAirTemperature);
  bool setZoneCoolingDesignSupplyAirTemperatureDifference(double zoneCoolingDesignSupplyAirTemperatureDifference);
  bool setZoneHeatingDesignSupplyAirTemperatureInputMethod(const std::string& zoneHeatingDesignSupplyAirTemperatureInputMethod);
  bool setZoneHeatingDesignSupplyAirTemperature(double zoneHeatingDesignSupplyAirTemperature);
  bool setZoneHeatingDesignSupplyAirTemperatureDifference(double zoneHeatingDesignSupplyAirTemperatureDifference);

  void resetSupplyAirMaximumFlowRate();
  void autosizeSupplyAirMaximumFlowRate();
  void resetZoneHeatingSizingFactor();
  void resetZoneCoolingSizingFactor();
  void resetZoneMinimumAirFlowInputMethod();
  void resetConstantMinimumAirFlowFraction();
  void resetFixedMinimumAirFlowRate();
  void resetOutdoorAirMethod();
  void resetOutdoorAirFlowRateperPerson();
  void resetOutdoorAirFlowRateperZoneFloorArea();
  void resetOutdoorAirFlowRateperZone();
  void resetReheatCoilType();
  void resetDamperHeatingAction();
  void resetMaximumFlowperZoneFloorAreaDuringReheat();
  void autocalculateMaximumFlowperZoneFloorAreaDuringReheat();
  void resetMaximumFlowFractionDuringReheat();
  void autocalculateMaximumFlowFractionDuringReheat();
  void resetMaximumReheatAirTemperature();
  void resetBaseboardHeatingType();
  void resetBaseboardHeatingCapacity();
  void autosizeBaseboardHeatingCapacity();
  void resetZoneCoolingDesignSupplyAirTemperatureInputMethod();
  void resetZoneCoolingDesignSupplyAirTemperature();
  void resetZoneCoolingDesignSupplyAirTemperatureDifference();
  void resetZoneHeatingDesignSupplyAirTemperatureInputMethod();
  void resetZoneHeatingDesignSupplyAirTemperature();
  void resetZoneHeatingDesignSupplyAirTemperatureDifference();

  std::vector<std::string> zoneMinimumAirFlowInputMethodValues() const;
  std::vector<std::string> outdoorAirMethodValues() const;
  std::vector<std::string> reheatCoilTypeValues() const;
  std::vector<std::string> damperHeatingActionValues() const;
  std::vector<std::string> baseboardHeatingTypeValues() const;
  std::vector<std::string> zoneCoolingDesignSupplyAirTemperatureInputMethodValues() const;
  std::vector<std::string> zoneHeatingDesignSupplyAirTemperatureInputMethodValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
