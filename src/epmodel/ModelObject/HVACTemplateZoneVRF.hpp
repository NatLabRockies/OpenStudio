/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HVACTEMPLATEZONEVRF_HPP
#define EPMODEL_HVACTEMPLATEZONEVRF_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class HVACTemplateZoneVRF_Impl;
}

class EPMODEL_API HVACTemplateZoneVRF : public ModelObject
{
 public:
  explicit HVACTemplateZoneVRF(const Model& model);

  virtual ~HVACTemplateZoneVRF() override = default;
  HVACTemplateZoneVRF(const HVACTemplateZoneVRF& other) = default;
  HVACTemplateZoneVRF(HVACTemplateZoneVRF&& other) = default;
  HVACTemplateZoneVRF& operator=(const HVACTemplateZoneVRF&) = default;
  HVACTemplateZoneVRF& operator=(HVACTemplateZoneVRF&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> outdoorAirMethodValues();
  static std::vector<std::string> supplyAirFanplacementValues();
  static std::vector<std::string> coolingCoilTypeValues();
  static std::vector<std::string> heatPumpHeatingCoilTypeValues();
  static std::vector<std::string> zoneCoolingDesignSupplyAirTemperatureInputMethodValues();
  static std::vector<std::string> zoneHeatingDesignSupplyAirTemperatureInputMethodValues();
  static std::vector<std::string> baseboardHeatingTypeValues();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived class/accessor naming.
  // - Field Mapping: Scalar APIs map directly to HVACTemplate:Zone:VRF non-name, non-link scalar fields.
  // - Field Mapping: Zone/System/Thermostat/Schedule/DOAS/DesignSpecification name fields are object-list
  //   relationship fields and are intentionally excluded from this scalar-only scaffold.
  // - TODO(parity): Revisit only if a future parity pass introduces relationship/object-link APIs.
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

 protected:
  using ImplType = detail::HVACTemplateZoneVRF_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit HVACTemplateZoneVRF(std::shared_ptr<detail::HVACTemplateZoneVRF_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
