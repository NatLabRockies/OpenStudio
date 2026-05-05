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

    // Cooling and heating supply air temperature
    std::string zoneCoolingDesignSupplyAirTemperatureInputMethod() const;
    double zoneCoolingDesignSupplyAirTemperature() const;
    double zoneCoolingDesignSupplyAirTemperatureDifference() const;
    bool setZoneCoolingDesignSupplyAirTemperatureInputMethod(const std::string& value);
    bool setZoneCoolingDesignSupplyAirTemperature(double zoneCoolingDesignSupplyAirTemperature);
    bool setZoneCoolingDesignSupplyAirTemperatureDifference(double value);

    std::string zoneHeatingDesignSupplyAirTemperatureInputMethod() const;
    double zoneHeatingDesignSupplyAirTemperature() const;
    double zoneHeatingDesignSupplyAirTemperatureDifference() const;
    bool setZoneHeatingDesignSupplyAirTemperatureInputMethod(const std::string& value);
    bool setZoneHeatingDesignSupplyAirTemperature(double zoneHeatingDesignSupplyAirTemperature);
    bool setZoneHeatingDesignSupplyAirTemperatureDifference(double value);

    // Cooling and heating supply air humidity ratios
    double zoneCoolingDesignSupplyAirHumidityRatio() const;
    bool setZoneCoolingDesignSupplyAirHumidityRatio(double zoneCoolingDesignSupplyAirHumidityRatio);
    double zoneHeatingDesignSupplyAirHumidityRatio() const;
    bool setZoneHeatingDesignSupplyAirHumidityRatio(double zoneHeatingDesignSupplyAirHumidityRatio);

    // Sizing factors
    boost::optional<double> zoneHeatingSizingFactor() const;
    bool setZoneHeatingSizingFactor(double zoneHeatingSizingFactor);
    void resetZoneHeatingSizingFactor();

    boost::optional<double> zoneCoolingSizingFactor() const;
    bool setZoneCoolingSizingFactor(double zoneCoolingSizingFactor);
    void resetZoneCoolingSizingFactor();

    // Cooling design air flow
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

    // Heating design air flow
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

    // Dedicated outdoor air system
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

    // Zone load sizing
    std::string zoneLoadSizingMethod() const;
    bool setZoneLoadSizingMethod(const std::string& zoneLoadSizingMethod);

    std::string zoneLatentCoolingDesignSupplyAirHumidityRatioInputMethod() const;
    bool setZoneLatentCoolingDesignSupplyAirHumidityRatioInputMethod(const std::string& zoneLatentCoolingDesignSupplyAirHumidityRatioInputMethod);
    boost::optional<double> zoneDehumidificationDesignSupplyAirHumidityRatio() const;
    double zoneCoolingDesignSupplyAirHumidityRatioDifference() const;
    bool setZoneDehumidificationDesignSupplyAirHumidityRatio(double zoneDehumidificationDesignSupplyAirHumidityRatio);
    void resetZoneDehumidificationDesignSupplyAirHumidityRatio();
    bool setZoneCoolingDesignSupplyAirHumidityRatioDifference(double zoneCoolingDesignSupplyAirHumidityRatioDifference);

    std::string zoneLatentHeatingDesignSupplyAirHumidityRatioInputMethod() const;
    bool setZoneLatentHeatingDesignSupplyAirHumidityRatioInputMethod(const std::string& zoneLatentHeatingDesignSupplyAirHumidityRatioInputMethod);
    boost::optional<double> zoneHumidificationDesignSupplyAirHumidityRatio() const;
    double zoneHumidificationDesignSupplyAirHumidityRatioDifference() const;
    bool setZoneHumidificationDesignSupplyAirHumidityRatio(double zoneHumidificationDesignSupplyAirHumidityRatio);
    void resetZoneHumidificationDesignSupplyAirHumidityRatio();
    bool setZoneHumidificationDesignSupplyAirHumidityRatioDifference(double zoneHumidificationDesignSupplyAirHumidityRatioDifference);

    // Design distribution effectiveness and ventilation
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

    // Other sizing options
    std::string sizingOption() const;
    bool setSizingOption(const std::string& sizingOption);

    std::string heatingCoilSizingMethod() const;
    bool setHeatingCoilSizingMethod(const std::string& heatingCoilSizingMethod);

    double maximumHeatingCapacityToCoolingLoadSizingRatio() const;
    bool setMaximumHeatingCapacityToCoolingLoadSizingRatio(double maximumHeatingCapacityToCoolingLoadSizingRatio);

   protected:
    using ImplType = detail::SizingZone_Impl;

    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;
    friend class Model;

    explicit SizingZone(std::shared_ptr<detail::SizingZone_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
