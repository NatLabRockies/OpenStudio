/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SIZINGZONE_IMPL_HPP
#define EPMODEL_SIZINGZONE_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

class ThermalZone;
class ModelObject;
class DesignSpecificationOutdoorAir;
class DesignSpecificationOutdoorAirSpaceList;

namespace detail {

class EPMODEL_API SizingZone_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~SizingZone_Impl() override = default;

  boost::optional<openstudio::epmodel::ThermalZone> optionalThermalZone() const;
  openstudio::epmodel::ThermalZone thermalZone() const;

  boost::optional<openstudio::epmodel::DesignSpecificationOutdoorAirSpaceList> designSpecificationOutdoorAirSpaceList() const;
  bool setDesignSpecificationOutdoorAirSpaceList(
    const openstudio::epmodel::DesignSpecificationOutdoorAirSpaceList& designSpecificationOutdoorAirSpaceList);

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

  std::vector<std::string> coolingDesignAirFlowMethodValues() const;
  std::vector<std::string> heatingDesignAirFlowMethodValues() const;
  std::vector<std::string> zoneCoolingDesignSupplyAirTemperatureInputMethodValues() const;
  std::vector<std::string> zoneHeatingDesignSupplyAirTemperatureInputMethodValues() const;
  std::vector<std::string> zoneLoadSizingMethodValues() const;
  std::vector<std::string> zoneLatentCoolingDesignSupplyAirHumidityRatioInputMethodValues() const;
  std::vector<std::string> zoneLatentHeatingDesignSupplyAirHumidityRatioInputMethodValues() const;
  std::vector<std::string> validSizingOptionValues() const;
  std::vector<std::string> heatingCoilSizingMethodValues() const;

  void doCanonicalize(LoadContext& context) override;

 private:
  boost::optional<openstudio::epmodel::ModelObject> designSpecificationZoneAirDistribution() const;
  boost::optional<openstudio::epmodel::ModelObject> getOrCreateDesignSpecificationZoneAirDistribution();
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
