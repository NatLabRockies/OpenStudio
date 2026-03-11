/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HVACTEMPLATEZONEVAVFANPOWERED_HPP
#define EPMODEL_HVACTEMPLATEZONEVAVFANPOWERED_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class HVACTemplateZoneVAVFanPowered_Impl;
}

class EPMODEL_API HVACTemplateZoneVAVFanPowered : public ModelObject
{
 public:
  explicit HVACTemplateZoneVAVFanPowered(const Model& model);

  virtual ~HVACTemplateZoneVAVFanPowered() override = default;
  HVACTemplateZoneVAVFanPowered(const HVACTemplateZoneVAVFanPowered& other) = default;
  HVACTemplateZoneVAVFanPowered(HVACTemplateZoneVAVFanPowered&& other) = default;
  HVACTemplateZoneVAVFanPowered& operator=(const HVACTemplateZoneVAVFanPowered&) = default;
  HVACTemplateZoneVAVFanPowered& operator=(HVACTemplateZoneVAVFanPowered&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> flowTypeValues();
  static std::vector<std::string> outdoorAirMethodValues();
  static std::vector<std::string> reheatCoilTypeValues();
  static std::vector<std::string> baseboardHeatingTypeValues();
  static std::vector<std::string> zoneCoolingDesignSupplyAirTemperatureInputMethodValues();
  static std::vector<std::string> zoneHeatingDesignSupplyAirTemperatureInputMethodValues();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived class/accessor naming.
  // - Field Mapping: Scalar APIs map directly to HVACTemplate:Zone:VAV:FanPowered non-name, non-link scalar fields.
  // - Field Mapping: Zone/System/Thermostat/Schedule/Plenum/DesignSpecification name fields are object-list relationship
  //   fields and are intentionally excluded from scalar-only scaffold.
  // - TODO(parity): Revisit only if a future parity pass introduces relationship/object-link APIs.
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

 protected:
  using ImplType = detail::HVACTemplateZoneVAVFanPowered_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit HVACTemplateZoneVAVFanPowered(std::shared_ptr<detail::HVACTemplateZoneVAVFanPowered_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
