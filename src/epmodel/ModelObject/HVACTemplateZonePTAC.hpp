/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HVACTEMPLATEZONEPTAC_HPP
#define EPMODEL_HVACTEMPLATEZONEPTAC_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class HVACTemplateZonePTAC_Impl;
}

class EPMODEL_API HVACTemplateZonePTAC : public ModelObject
{
 public:
  explicit HVACTemplateZonePTAC(const Model& model);

  virtual ~HVACTemplateZonePTAC() override = default;
  HVACTemplateZonePTAC(const HVACTemplateZonePTAC& other) = default;
  HVACTemplateZonePTAC(HVACTemplateZonePTAC&& other) = default;
  HVACTemplateZonePTAC& operator=(const HVACTemplateZonePTAC&) = default;
  HVACTemplateZonePTAC& operator=(HVACTemplateZonePTAC&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> outdoorAirMethodValues();
  static std::vector<std::string> supplyFanPlacementValues();
  static std::vector<std::string> coolingCoilTypeValues();
  static std::vector<std::string> heatingCoilTypeValues();
  static std::vector<std::string> zoneCoolingDesignSupplyAirTemperatureInputMethodValues();
  static std::vector<std::string> zoneHeatingDesignSupplyAirTemperatureInputMethodValues();
  static std::vector<std::string> baseboardHeatingTypeValues();
  static std::vector<std::string> capacityControlMethodValues();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived class/accessor naming.
  // - Field Mapping: Scalar APIs map directly to HVACTemplate:Zone:PTAC non-name, non-link scalar fields.
  // - Field Mapping: Zone/Thermostat/Schedule/DOAS/DesignSpecification name fields are object-list relationship fields
  //   and are intentionally excluded from this scalar-only scaffold.
  // - TODO(parity): Revisit only if a future parity pass introduces relationship/object-link APIs.
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
  double coolingCoilGrossRatedCoolingCOP() const;
  std::string heatingCoilType() const;
  boost::optional<double> heatingCoilCapacity() const;
  double gasHeatingCoilEfficiency() const;
  double gasHeatingCoilParasiticElectricLoad() const;
  std::string zoneCoolingDesignSupplyAirTemperatureInputMethod() const;
  double zoneCoolingDesignSupplyAirTemperature() const;
  double zoneCoolingDesignSupplyAirTemperatureDifference() const;
  std::string zoneHeatingDesignSupplyAirTemperatureInputMethod() const;
  double zoneHeatingDesignSupplyAirTemperature() const;
  double zoneHeatingDesignSupplyAirTemperatureDifference() const;
  std::string baseboardHeatingType() const;
  boost::optional<double> baseboardHeatingCapacity() const;
  std::string capacityControlMethod() const;

  bool isCoolingSupplyAirFlowRateDefaulted() const;
  bool isCoolingSupplyAirFlowRateAutosized() const;
  bool isHeatingSupplyAirFlowRateDefaulted() const;
  bool isHeatingSupplyAirFlowRateAutosized() const;
  bool isNoLoadSupplyAirFlowRateDefaulted() const;
  bool isNoLoadSupplyAirFlowRateAutosized() const;
  bool isZoneHeatingSizingFactorDefaulted() const;
  bool isZoneCoolingSizingFactorDefaulted() const;
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
  bool isCoolingCoilGrossRatedTotalCapacityAutosized() const;
  bool isCoolingCoilGrossRatedSensibleHeatRatioDefaulted() const;
  bool isCoolingCoilGrossRatedSensibleHeatRatioAutosized() const;
  bool isCoolingCoilGrossRatedCoolingCOPDefaulted() const;
  bool isHeatingCoilTypeDefaulted() const;
  bool isHeatingCoilCapacityDefaulted() const;
  bool isHeatingCoilCapacityAutosized() const;
  bool isGasHeatingCoilEfficiencyDefaulted() const;
  bool isGasHeatingCoilParasiticElectricLoadDefaulted() const;
  bool isZoneCoolingDesignSupplyAirTemperatureInputMethodDefaulted() const;
  bool isZoneCoolingDesignSupplyAirTemperatureDefaulted() const;
  bool isZoneCoolingDesignSupplyAirTemperatureDifferenceDefaulted() const;
  bool isZoneHeatingDesignSupplyAirTemperatureInputMethodDefaulted() const;
  bool isZoneHeatingDesignSupplyAirTemperatureDefaulted() const;
  bool isZoneHeatingDesignSupplyAirTemperatureDifferenceDefaulted() const;
  bool isBaseboardHeatingTypeDefaulted() const;
  bool isBaseboardHeatingCapacityDefaulted() const;
  bool isBaseboardHeatingCapacityAutosized() const;
  bool isCapacityControlMethodDefaulted() const;

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
  bool setCoolingCoilGrossRatedCoolingCOP(double coolingCoilGrossRatedCoolingCOP);
  bool setHeatingCoilType(const std::string& heatingCoilType);
  bool setHeatingCoilCapacity(double heatingCoilCapacity);
  bool setGasHeatingCoilEfficiency(double gasHeatingCoilEfficiency);
  bool setGasHeatingCoilParasiticElectricLoad(double gasHeatingCoilParasiticElectricLoad);
  bool setZoneCoolingDesignSupplyAirTemperatureInputMethod(const std::string& zoneCoolingDesignSupplyAirTemperatureInputMethod);
  bool setZoneCoolingDesignSupplyAirTemperature(double zoneCoolingDesignSupplyAirTemperature);
  bool setZoneCoolingDesignSupplyAirTemperatureDifference(double zoneCoolingDesignSupplyAirTemperatureDifference);
  bool setZoneHeatingDesignSupplyAirTemperatureInputMethod(const std::string& zoneHeatingDesignSupplyAirTemperatureInputMethod);
  bool setZoneHeatingDesignSupplyAirTemperature(double zoneHeatingDesignSupplyAirTemperature);
  bool setZoneHeatingDesignSupplyAirTemperatureDifference(double zoneHeatingDesignSupplyAirTemperatureDifference);
  bool setBaseboardHeatingType(const std::string& baseboardHeatingType);
  bool setBaseboardHeatingCapacity(double baseboardHeatingCapacity);
  bool setCapacityControlMethod(const std::string& capacityControlMethod);

  void resetCoolingSupplyAirFlowRate();
  void autosizeCoolingSupplyAirFlowRate();
  void resetHeatingSupplyAirFlowRate();
  void autosizeHeatingSupplyAirFlowRate();
  void resetNoLoadSupplyAirFlowRate();
  void autosizeNoLoadSupplyAirFlowRate();
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
  void autosizeCoolingCoilGrossRatedTotalCapacity();
  void resetCoolingCoilGrossRatedSensibleHeatRatio();
  void autosizeCoolingCoilGrossRatedSensibleHeatRatio();
  void resetCoolingCoilGrossRatedCoolingCOP();
  void resetHeatingCoilType();
  void resetHeatingCoilCapacity();
  void autosizeHeatingCoilCapacity();
  void resetGasHeatingCoilEfficiency();
  void resetGasHeatingCoilParasiticElectricLoad();
  void resetZoneCoolingDesignSupplyAirTemperatureInputMethod();
  void resetZoneCoolingDesignSupplyAirTemperature();
  void resetZoneCoolingDesignSupplyAirTemperatureDifference();
  void resetZoneHeatingDesignSupplyAirTemperatureInputMethod();
  void resetZoneHeatingDesignSupplyAirTemperature();
  void resetZoneHeatingDesignSupplyAirTemperatureDifference();
  void resetBaseboardHeatingType();
  void resetBaseboardHeatingCapacity();
  void autosizeBaseboardHeatingCapacity();
  void resetCapacityControlMethod();

 protected:
  using ImplType = detail::HVACTemplateZonePTAC_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit HVACTemplateZonePTAC(std::shared_ptr<detail::HVACTemplateZonePTAC_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
