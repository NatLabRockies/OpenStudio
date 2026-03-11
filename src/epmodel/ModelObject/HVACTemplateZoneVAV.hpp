/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HVACTEMPLATEZONEVAV_HPP
#define EPMODEL_HVACTEMPLATEZONEVAV_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class HVACTemplateZoneVAV_Impl;
}

class EPMODEL_API HVACTemplateZoneVAV : public ModelObject
{
 public:
  explicit HVACTemplateZoneVAV(const Model& model);

  virtual ~HVACTemplateZoneVAV() override = default;
  HVACTemplateZoneVAV(const HVACTemplateZoneVAV& other) = default;
  HVACTemplateZoneVAV(HVACTemplateZoneVAV&& other) = default;
  HVACTemplateZoneVAV& operator=(const HVACTemplateZoneVAV&) = default;
  HVACTemplateZoneVAV& operator=(HVACTemplateZoneVAV&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> zoneMinimumAirFlowInputMethodValues();
  static std::vector<std::string> outdoorAirMethodValues();
  static std::vector<std::string> reheatCoilTypeValues();
  static std::vector<std::string> damperHeatingActionValues();
  static std::vector<std::string> baseboardHeatingTypeValues();
  static std::vector<std::string> zoneCoolingDesignSupplyAirTemperatureInputMethodValues();
  static std::vector<std::string> zoneHeatingDesignSupplyAirTemperatureInputMethodValues();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived class/accessor naming.
  // - Field Mapping: Scalar APIs map directly to HVACTemplate:Zone:VAV non-link scalar fields.
  // - Field Mapping: Zone/System/Thermostat/Schedule/Plenum/DesignSpecification object-list fields are relationship
  //   fields and are intentionally excluded from scalar-only scaffold.
  // - TODO(parity): Revisit only if a future parity pass introduces relationship/object-link APIs.
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

 protected:
  using ImplType = detail::HVACTemplateZoneVAV_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit HVACTemplateZoneVAV(std::shared_ptr<detail::HVACTemplateZoneVAV_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
