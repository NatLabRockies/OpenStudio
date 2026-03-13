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
      bool setZoneCoolingDesignSupplyAirTemperatureInputMethod(const std::string& value);

      double zoneCoolingDesignSupplyAirTemperature() const;
      bool setZoneCoolingDesignSupplyAirTemperature(double zoneCoolingDesignSupplyAirTemperature);

      double zoneCoolingDesignSupplyAirTemperatureDifference() const;
      bool setZoneCoolingDesignSupplyAirTemperatureDifference(double value);

      std::string zoneHeatingDesignSupplyAirTemperatureInputMethod() const;
      bool setZoneHeatingDesignSupplyAirTemperatureInputMethod(const std::string& value);

      double zoneHeatingDesignSupplyAirTemperature() const;
      bool setZoneHeatingDesignSupplyAirTemperature(double zoneHeatingDesignSupplyAirTemperature);

      double zoneHeatingDesignSupplyAirTemperatureDifference() const;
      bool setZoneHeatingDesignSupplyAirTemperatureDifference(double value);

      double zoneCoolingDesignSupplyAirHumidityRatio() const;
      bool setZoneCoolingDesignSupplyAirHumidityRatio(double zoneCoolingDesignSupplyAirHumidityRatio);

      double zoneHeatingDesignSupplyAirHumidityRatio() const;
      bool setZoneHeatingDesignSupplyAirHumidityRatio(double zoneHeatingDesignSupplyAirHumidityRatio);

      boost::optional<double> zoneHeatingSizingFactor() const;
      bool setZoneHeatingSizingFactor(double zoneHeatingSizingFactor);
      void resetZoneHeatingSizingFactor();

      boost::optional<double> zoneCoolingSizingFactor() const;
      bool setZoneCoolingSizingFactor(double zoneCoolingSizingFactor);
      void resetZoneCoolingSizingFactor();

      std::string coolingDesignAirFlowMethod() const;
      bool isCoolingDesignAirFlowMethodDefaulted() const;
      bool setCoolingDesignAirFlowMethod(const std::string& coolingDesignAirFlowMethod);
      void resetCoolingDesignAirFlowMethod();

      double coolingDesignAirFlowRate() const;
      bool isCoolingDesignAirFlowRateDefaulted() const;
      bool setCoolingDesignAirFlowRate(double coolingDesignAirFlowRate);
      void resetCoolingDesignAirFlowRate();

      double coolingMinimumAirFlowperZoneFloorArea() const;
      bool isCoolingMinimumAirFlowperZoneFloorAreaDefaulted() const;
      bool setCoolingMinimumAirFlowperZoneFloorArea(double coolingMinimumAirFlowperZoneFloorArea);
      void resetCoolingMinimumAirFlowperZoneFloorArea();

      double coolingMinimumAirFlow() const;
      bool isCoolingMinimumAirFlowDefaulted() const;
      bool setCoolingMinimumAirFlow(double coolingMinimumAirFlow);
      void resetCoolingMinimumAirFlow();

      double coolingMinimumAirFlowFraction() const;
      bool isCoolingMinimumAirFlowFractionDefaulted() const;
      bool setCoolingMinimumAirFlowFraction(double coolingMinimumAirFlowFraction);
      void resetCoolingMinimumAirFlowFraction();

      std::string heatingDesignAirFlowMethod() const;
      bool isHeatingDesignAirFlowMethodDefaulted() const;
      bool setHeatingDesignAirFlowMethod(const std::string& heatingDesignAirFlowMethod);
      void resetHeatingDesignAirFlowMethod();

      double heatingDesignAirFlowRate() const;
      bool isHeatingDesignAirFlowRateDefaulted() const;
      bool setHeatingDesignAirFlowRate(double heatingDesignAirFlowRate);
      void resetHeatingDesignAirFlowRate();

      double heatingMaximumAirFlowperZoneFloorArea() const;
      bool isHeatingMaximumAirFlowperZoneFloorAreaDefaulted() const;
      bool setHeatingMaximumAirFlowperZoneFloorArea(double heatingMaximumAirFlowperZoneFloorArea);
      void resetHeatingMaximumAirFlowperZoneFloorArea();

      double heatingMaximumAirFlow() const;
      bool isHeatingMaximumAirFlowDefaulted() const;
      bool setHeatingMaximumAirFlow(double heatingMaximumAirFlow);
      void resetHeatingMaximumAirFlow();

      double heatingMaximumAirFlowFraction() const;
      bool isHeatingMaximumAirFlowFractionDefaulted() const;
      bool setHeatingMaximumAirFlowFraction(double heatingMaximumAirFlowFraction);
      void resetHeatingMaximumAirFlowFraction();

      bool accountforDedicatedOutdoorAirSystem() const;
      bool setAccountforDedicatedOutdoorAirSystem(bool accountforDedicatedOutdoorAirSystem);

      std::string dedicatedOutdoorAirSystemControlStrategy() const;
      bool setDedicatedOutdoorAirSystemControlStrategy(const std::string& dedicatedOutdoorAirSystemControlStrategy);

      boost::optional<double> dedicatedOutdoorAirLowSetpointTemperatureforDesign() const;
      bool isDedicatedOutdoorAirLowSetpointTemperatureforDesignAutosized() const;
      bool setDedicatedOutdoorAirLowSetpointTemperatureforDesign(double dedicatedOutdoorAirLowSetpointTemperatureforDesign);
      void autosizeDedicatedOutdoorAirLowSetpointTemperatureforDesign();

      boost::optional<double> dedicatedOutdoorAirHighSetpointTemperatureforDesign() const;
      bool isDedicatedOutdoorAirHighSetpointTemperatureforDesignAutosized() const;
      bool setDedicatedOutdoorAirHighSetpointTemperatureforDesign(double dedicatedOutdoorAirHighSetpointTemperatureforDesign);
      void autosizeDedicatedOutdoorAirHighSetpointTemperatureforDesign();

      std::string zoneLoadSizingMethod() const;
      bool setZoneLoadSizingMethod(const std::string& zoneLoadSizingMethod);

      std::string zoneLatentCoolingDesignSupplyAirHumidityRatioInputMethod() const;
      bool setZoneLatentCoolingDesignSupplyAirHumidityRatioInputMethod(const std::string& zoneLatentCoolingDesignSupplyAirHumidityRatioInputMethod);

      boost::optional<double> zoneDehumidificationDesignSupplyAirHumidityRatio() const;
      bool setZoneDehumidificationDesignSupplyAirHumidityRatio(double zoneDehumidificationDesignSupplyAirHumidityRatio);
      void resetZoneDehumidificationDesignSupplyAirHumidityRatio();

      double zoneCoolingDesignSupplyAirHumidityRatioDifference() const;
      bool setZoneCoolingDesignSupplyAirHumidityRatioDifference(double zoneCoolingDesignSupplyAirHumidityRatioDifference);

      std::string zoneLatentHeatingDesignSupplyAirHumidityRatioInputMethod() const;
      bool setZoneLatentHeatingDesignSupplyAirHumidityRatioInputMethod(const std::string& zoneLatentHeatingDesignSupplyAirHumidityRatioInputMethod);

      boost::optional<double> zoneHumidificationDesignSupplyAirHumidityRatio() const;
      bool setZoneHumidificationDesignSupplyAirHumidityRatio(double zoneHumidificationDesignSupplyAirHumidityRatio);
      void resetZoneHumidificationDesignSupplyAirHumidityRatio();

      double zoneHumidificationDesignSupplyAirHumidityRatioDifference() const;
      bool setZoneHumidificationDesignSupplyAirHumidityRatioDifference(double zoneHumidificationDesignSupplyAirHumidityRatioDifference);

      double designZoneAirDistributionEffectivenessinCoolingMode() const;
      bool isDesignZoneAirDistributionEffectivenessinCoolingModeDefaulted() const;
      bool setDesignZoneAirDistributionEffectivenessinCoolingMode(double designZoneAirDistributionEffectivenessinCoolingMode);
      void resetDesignZoneAirDistributionEffectivenessinCoolingMode();

      double designZoneAirDistributionEffectivenessinHeatingMode() const;
      bool isDesignZoneAirDistributionEffectivenessinHeatingModeDefaulted() const;
      bool setDesignZoneAirDistributionEffectivenessinHeatingMode(double designZoneAirDistributionEffectivenessinHeatingMode);
      void resetDesignZoneAirDistributionEffectivenessinHeatingMode();

      double designZoneSecondaryRecirculationFraction() const;
      bool isDesignZoneSecondaryRecirculationFractionDefaulted() const;
      bool setDesignZoneSecondaryRecirculationFraction(double designZoneSecondaryRecirculationFraction);
      void resetDesignZoneSecondaryRecirculationFraction();

      double designMinimumZoneVentilationEfficiency() const;
      bool isDesignMinimumZoneVentilationEfficiencyDefaulted() const;
      bool setDesignMinimumZoneVentilationEfficiency(double designMinimumZoneVentilationEfficiency);
      void resetDesignMinimumZoneVentilationEfficiency();

      std::string sizingOption() const;
      bool setSizingOption(const std::string& sizingOption);

      std::string heatingCoilSizingMethod() const;
      bool setHeatingCoilSizingMethod(const std::string& heatingCoilSizingMethod);

      double maximumHeatingCapacityToCoolingLoadSizingRatio() const;
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
