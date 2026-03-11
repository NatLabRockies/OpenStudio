/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HVACTEMPLATEZONECONSTANTVOLUME_HPP
#define EPMODEL_HVACTEMPLATEZONECONSTANTVOLUME_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class HVACTemplateZoneConstantVolume_Impl;
}

class EPMODEL_API HVACTemplateZoneConstantVolume : public ModelObject
{
 public:
  explicit HVACTemplateZoneConstantVolume(const Model& model);

  virtual ~HVACTemplateZoneConstantVolume() override = default;
  HVACTemplateZoneConstantVolume(const HVACTemplateZoneConstantVolume& other) = default;
  HVACTemplateZoneConstantVolume(HVACTemplateZoneConstantVolume&& other) = default;
  HVACTemplateZoneConstantVolume& operator=(const HVACTemplateZoneConstantVolume&) = default;
  HVACTemplateZoneConstantVolume& operator=(HVACTemplateZoneConstantVolume&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> outdoorAirMethodValues();
  static std::vector<std::string> reheatCoilTypeValues();
  static std::vector<std::string> baseboardHeatingTypeValues();
  static std::vector<std::string> zoneCoolingDesignSupplyAirTemperatureInputMethodValues();
  static std::vector<std::string> zoneHeatingDesignSupplyAirTemperatureInputMethodValues();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived class/accessor naming.
  // - Field Mapping: Scalar APIs map directly to HVACTemplate:Zone:ConstantVolume non-name, non-link scalar fields.
  // - Field Mapping: Zone/System/Thermostat/Schedule/Plenum/DesignSpecification name fields are object-list relationship
  //   fields and are intentionally excluded from scalar-only scaffold.
  // - TODO(parity): Revisit only if a future parity pass introduces relationship/object-link APIs.
  boost::optional<double> supplyAirMaximumFlowRate() const;
  boost::optional<double> zoneHeatingSizingFactor() const;
  boost::optional<double> zoneCoolingSizingFactor() const;
  std::string outdoorAirMethod() const;
  double outdoorAirFlowRateperPerson() const;
  double outdoorAirFlowRateperZoneFloorArea() const;
  double outdoorAirFlowRateperZone() const;
  std::string reheatCoilType() const;
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
  bool isOutdoorAirMethodDefaulted() const;
  bool isOutdoorAirFlowRateperPersonDefaulted() const;
  bool isOutdoorAirFlowRateperZoneFloorAreaDefaulted() const;
  bool isOutdoorAirFlowRateperZoneDefaulted() const;
  bool isReheatCoilTypeDefaulted() const;
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
  bool setOutdoorAirMethod(const std::string& outdoorAirMethod);
  bool setOutdoorAirFlowRateperPerson(double outdoorAirFlowRateperPerson);
  bool setOutdoorAirFlowRateperZoneFloorArea(double outdoorAirFlowRateperZoneFloorArea);
  bool setOutdoorAirFlowRateperZone(double outdoorAirFlowRateperZone);
  bool setReheatCoilType(const std::string& reheatCoilType);
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
  void resetOutdoorAirMethod();
  void resetOutdoorAirFlowRateperPerson();
  void resetOutdoorAirFlowRateperZoneFloorArea();
  void resetOutdoorAirFlowRateperZone();
  void resetReheatCoilType();
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

 protected:
  using ImplType = detail::HVACTemplateZoneConstantVolume_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit HVACTemplateZoneConstantVolume(std::shared_ptr<detail::HVACTemplateZoneConstantVolume_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
