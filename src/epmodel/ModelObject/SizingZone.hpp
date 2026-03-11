/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SIZINGZONE_HPP
#define EPMODEL_SIZINGZONE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include "../utilities/idd/IddEnums.hpp"

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;
class ThermalZone;

namespace detail {
class SizingZone_Impl;
}

class EPMODEL_API SizingZone : public ModelObject
{
 public:
  explicit SizingZone(const Model& model, const ThermalZone& thermalZone);

  virtual ~SizingZone() override = default;
  SizingZone(const SizingZone& other) = default;
  SizingZone(SizingZone&& other) = default;
  SizingZone& operator=(const SizingZone&) = default;
  SizingZone& operator=(SizingZone&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> coolingDesignAirFlowMethodValues();
  static std::vector<std::string> heatingDesignAirFlowMethodValues();
  static std::vector<std::string> zoneCoolingDesignSupplyAirTemperatureInputMethodValues();
  static std::vector<std::string> zoneHeatingDesignSupplyAirTemperatureInputMethodValues();
  static std::vector<std::string> zoneLoadSizingMethodValues();
  static std::vector<std::string> zoneLatentCoolingDesignSupplyAirHumidityRatioInputMethodValues();
  static std::vector<std::string> zoneLatentHeatingDesignSupplyAirHumidityRatioInputMethodValues();
  static std::vector<std::string> validSizingOptionValues();
  static std::vector<std::string> heatingCoilSizingMethodValues();

  ThermalZone thermalZone() const;

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model SizingZone scalar accessor names/signatures for model-counterpart parity.
  // - Field Mapping: Most scalar accessors map directly to EnergyPlus Sizing:Zone fields (same semantic names).
  // - Field Mapping: sizingOption maps to EnergyPlus Sizing:Zone field Type of Space Sum to Use.
  // - Field Mapping: DSZAD API delegates through Sizing:Zone.Design Specification Zone Air Distribution Object Name
  //   to DesignSpecification:ZoneAirDistribution scalar fields.
  // - ForwardTranslator Evidence: ForwardTranslateSizingZone maps DSZAD values through a linked
  //   DesignSpecification:ZoneAirDistribution object and otherwise writes Sizing:Zone scalars directly.
  // - TODO(parity): Add non-scalar relationship fields (schedules/targets) in a dedicated relationship pass.
  std::string zoneCoolingDesignSupplyAirTemperatureInputMethod() const;
  double zoneCoolingDesignSupplyAirTemperature() const;
  double zoneCoolingDesignSupplyAirTemperatureDifference() const;

  std::string zoneHeatingDesignSupplyAirTemperatureInputMethod() const;
  double zoneHeatingDesignSupplyAirTemperature() const;
  double zoneHeatingDesignSupplyAirTemperatureDifference() const;

  double zoneCoolingDesignSupplyAirHumidityRatio() const;
  double zoneHeatingDesignSupplyAirHumidityRatio() const;

  boost::optional<double> zoneHeatingSizingFactor() const;
  boost::optional<double> zoneCoolingSizingFactor() const;

  std::string coolingDesignAirFlowMethod() const;
  bool isCoolingDesignAirFlowMethodDefaulted() const;

  double coolingDesignAirFlowRate() const;
  bool isCoolingDesignAirFlowRateDefaulted() const;

  double coolingMinimumAirFlowperZoneFloorArea() const;
  bool isCoolingMinimumAirFlowperZoneFloorAreaDefaulted() const;

  double coolingMinimumAirFlow() const;
  bool isCoolingMinimumAirFlowDefaulted() const;

  double coolingMinimumAirFlowFraction() const;
  bool isCoolingMinimumAirFlowFractionDefaulted() const;

  std::string heatingDesignAirFlowMethod() const;
  bool isHeatingDesignAirFlowMethodDefaulted() const;

  double heatingDesignAirFlowRate() const;
  bool isHeatingDesignAirFlowRateDefaulted() const;

  double heatingMaximumAirFlowperZoneFloorArea() const;
  bool isHeatingMaximumAirFlowperZoneFloorAreaDefaulted() const;

  double heatingMaximumAirFlow() const;
  bool isHeatingMaximumAirFlowDefaulted() const;

  double heatingMaximumAirFlowFraction() const;
  bool isHeatingMaximumAirFlowFractionDefaulted() const;

  bool accountforDedicatedOutdoorAirSystem() const;
  std::string dedicatedOutdoorAirSystemControlStrategy() const;

  boost::optional<double> dedicatedOutdoorAirLowSetpointTemperatureforDesign() const;
  bool isDedicatedOutdoorAirLowSetpointTemperatureforDesignAutosized() const;

  boost::optional<double> dedicatedOutdoorAirHighSetpointTemperatureforDesign() const;
  bool isDedicatedOutdoorAirHighSetpointTemperatureforDesignAutosized() const;

  std::string zoneLoadSizingMethod() const;

  std::string zoneLatentCoolingDesignSupplyAirHumidityRatioInputMethod() const;
  boost::optional<double> zoneDehumidificationDesignSupplyAirHumidityRatio() const;
  double zoneCoolingDesignSupplyAirHumidityRatioDifference() const;

  std::string zoneLatentHeatingDesignSupplyAirHumidityRatioInputMethod() const;
  boost::optional<double> zoneHumidificationDesignSupplyAirHumidityRatio() const;
  double zoneHumidificationDesignSupplyAirHumidityRatioDifference() const;

  double designZoneAirDistributionEffectivenessinCoolingMode() const;
  bool isDesignZoneAirDistributionEffectivenessinCoolingModeDefaulted() const;

  double designZoneAirDistributionEffectivenessinHeatingMode() const;
  bool isDesignZoneAirDistributionEffectivenessinHeatingModeDefaulted() const;

  double designZoneSecondaryRecirculationFraction() const;
  bool isDesignZoneSecondaryRecirculationFractionDefaulted() const;

  double designMinimumZoneVentilationEfficiency() const;
  bool isDesignMinimumZoneVentilationEfficiencyDefaulted() const;

  std::string sizingOption() const;
  std::string heatingCoilSizingMethod() const;
  double maximumHeatingCapacityToCoolingLoadSizingRatio() const;

  bool setZoneCoolingDesignSupplyAirTemperatureInputMethod(const std::string& value);
  bool setZoneCoolingDesignSupplyAirTemperature(double zoneCoolingDesignSupplyAirTemperature);
  bool setZoneCoolingDesignSupplyAirTemperatureDifference(double value);

  bool setZoneHeatingDesignSupplyAirTemperatureInputMethod(const std::string& value);
  bool setZoneHeatingDesignSupplyAirTemperature(double zoneHeatingDesignSupplyAirTemperature);
  bool setZoneHeatingDesignSupplyAirTemperatureDifference(double value);

  bool setZoneCoolingDesignSupplyAirHumidityRatio(double zoneCoolingDesignSupplyAirHumidityRatio);
  bool setZoneHeatingDesignSupplyAirHumidityRatio(double zoneHeatingDesignSupplyAirHumidityRatio);

  bool setZoneHeatingSizingFactor(double zoneHeatingSizingFactor);
  void resetZoneHeatingSizingFactor();

  bool setZoneCoolingSizingFactor(double zoneCoolingSizingFactor);
  void resetZoneCoolingSizingFactor();

  bool setCoolingDesignAirFlowMethod(const std::string& coolingDesignAirFlowMethod);
  void resetCoolingDesignAirFlowMethod();

  bool setCoolingDesignAirFlowRate(double coolingDesignAirFlowRate);
  void resetCoolingDesignAirFlowRate();

  bool setCoolingMinimumAirFlowperZoneFloorArea(double coolingMinimumAirFlowperZoneFloorArea);
  void resetCoolingMinimumAirFlowperZoneFloorArea();

  bool setCoolingMinimumAirFlow(double coolingMinimumAirFlow);
  void resetCoolingMinimumAirFlow();

  bool setCoolingMinimumAirFlowFraction(double coolingMinimumAirFlowFraction);
  void resetCoolingMinimumAirFlowFraction();

  bool setHeatingDesignAirFlowMethod(const std::string& heatingDesignAirFlowMethod);
  void resetHeatingDesignAirFlowMethod();

  bool setHeatingDesignAirFlowRate(double heatingDesignAirFlowRate);
  void resetHeatingDesignAirFlowRate();

  bool setHeatingMaximumAirFlowperZoneFloorArea(double heatingMaximumAirFlowperZoneFloorArea);
  void resetHeatingMaximumAirFlowperZoneFloorArea();

  bool setHeatingMaximumAirFlow(double heatingMaximumAirFlow);
  void resetHeatingMaximumAirFlow();

  bool setHeatingMaximumAirFlowFraction(double heatingMaximumAirFlowFraction);
  void resetHeatingMaximumAirFlowFraction();

  bool setAccountforDedicatedOutdoorAirSystem(bool accountforDedicatedOutdoorAirSystem);
  bool setDedicatedOutdoorAirSystemControlStrategy(const std::string& dedicatedOutdoorAirSystemControlStrategy);

  bool setDedicatedOutdoorAirLowSetpointTemperatureforDesign(double dedicatedOutdoorAirLowSetpointTemperatureforDesign);
  void autosizeDedicatedOutdoorAirLowSetpointTemperatureforDesign();

  bool setDedicatedOutdoorAirHighSetpointTemperatureforDesign(double dedicatedOutdoorAirHighSetpointTemperatureforDesign);
  void autosizeDedicatedOutdoorAirHighSetpointTemperatureforDesign();

  bool setZoneLoadSizingMethod(const std::string& zoneLoadSizingMethod);

  bool setZoneLatentCoolingDesignSupplyAirHumidityRatioInputMethod(const std::string& zoneLatentCoolingDesignSupplyAirHumidityRatioInputMethod);

  bool setZoneDehumidificationDesignSupplyAirHumidityRatio(double zoneDehumidificationDesignSupplyAirHumidityRatio);
  void resetZoneDehumidificationDesignSupplyAirHumidityRatio();

  bool setZoneCoolingDesignSupplyAirHumidityRatioDifference(double zoneCoolingDesignSupplyAirHumidityRatioDifference);

  bool setZoneLatentHeatingDesignSupplyAirHumidityRatioInputMethod(const std::string& zoneLatentHeatingDesignSupplyAirHumidityRatioInputMethod);

  bool setZoneHumidificationDesignSupplyAirHumidityRatio(double zoneHumidificationDesignSupplyAirHumidityRatio);
  void resetZoneHumidificationDesignSupplyAirHumidityRatio();

  bool setZoneHumidificationDesignSupplyAirHumidityRatioDifference(double zoneHumidificationDesignSupplyAirHumidityRatioDifference);

  bool setDesignZoneAirDistributionEffectivenessinCoolingMode(double designZoneAirDistributionEffectivenessinCoolingMode);
  void resetDesignZoneAirDistributionEffectivenessinCoolingMode();

  bool setDesignZoneAirDistributionEffectivenessinHeatingMode(double designZoneAirDistributionEffectivenessinHeatingMode);
  void resetDesignZoneAirDistributionEffectivenessinHeatingMode();

  bool setDesignZoneSecondaryRecirculationFraction(double designZoneSecondaryRecirculationFraction);
  void resetDesignZoneSecondaryRecirculationFraction();

  bool setDesignMinimumZoneVentilationEfficiency(double designMinimumZoneVentilationEfficiency);
  void resetDesignMinimumZoneVentilationEfficiency();

  bool setSizingOption(const std::string& sizingOption);
  bool setHeatingCoilSizingMethod(const std::string& heatingCoilSizingMethod);
  bool setMaximumHeatingCapacityToCoolingLoadSizingRatio(double maximumHeatingCapacityToCoolingLoadSizingRatio);

 protected:
  using ImplType = detail::SizingZone_Impl;

  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;
  friend class openstudio::epmodel::Model;

  explicit SizingZone(std::shared_ptr<detail::SizingZone_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
