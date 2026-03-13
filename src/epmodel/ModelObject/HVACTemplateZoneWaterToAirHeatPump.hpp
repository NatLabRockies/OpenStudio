/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HVACTEMPLATEZONEWATERTOAIRHEATPUMP_HPP
#define EPMODEL_HVACTEMPLATEZONEWATERTOAIRHEATPUMP_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class HVACTemplateZoneWaterToAirHeatPump_Impl;
  }

  class EPMODEL_API HVACTemplateZoneWaterToAirHeatPump : public ModelObject
  {
   public:
    explicit HVACTemplateZoneWaterToAirHeatPump(const Model& model);

    virtual ~HVACTemplateZoneWaterToAirHeatPump() override = default;
    HVACTemplateZoneWaterToAirHeatPump(const HVACTemplateZoneWaterToAirHeatPump& other) = default;
    HVACTemplateZoneWaterToAirHeatPump(HVACTemplateZoneWaterToAirHeatPump&& other) = default;
    HVACTemplateZoneWaterToAirHeatPump& operator=(const HVACTemplateZoneWaterToAirHeatPump&) = default;
    HVACTemplateZoneWaterToAirHeatPump& operator=(HVACTemplateZoneWaterToAirHeatPump&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> outdoorAirMethodValues();
    static std::vector<std::string> supplyFanPlacementValues();
    static std::vector<std::string> coolingCoilTypeValues();
    static std::vector<std::string> heatPumpHeatingCoilTypeValues();
    static std::vector<std::string> supplementalHeatingCoilTypeValues();
    static std::vector<std::string> zoneCoolingDesignSupplyAirTemperatureInputMethodValues();
    static std::vector<std::string> zoneHeatingDesignSupplyAirTemperatureInputMethodValues();
    static std::vector<std::string> heatPumpCoilWaterFlowModeValues();
    static std::vector<std::string> baseboardHeatingTypeValues();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: Scalar APIs map directly to HVACTemplate:Zone:WaterToAirHeatPump non-name, non-link scalar fields.
    // - Field Mapping: Zone/Thermostat/Schedule/DOAS/DesignSpecification name fields are object-list relationship fields
    //   and are intentionally excluded from this scalar-only scaffold.
    // - TODO(parity): Revisit only if a future parity pass introduces relationship/object-link APIs.
    /** @name Field accessors */
    //@{

    boost::optional<double> coolingSupplyAirFlowRate() const;
    bool isCoolingSupplyAirFlowRateDefaulted() const;
    bool isCoolingSupplyAirFlowRateAutosized() const;
    bool setCoolingSupplyAirFlowRate(double coolingSupplyAirFlowRate);
    void resetCoolingSupplyAirFlowRate();
    void autosizeCoolingSupplyAirFlowRate();

    boost::optional<double> heatingSupplyAirFlowRate() const;
    bool isHeatingSupplyAirFlowRateDefaulted() const;
    bool isHeatingSupplyAirFlowRateAutosized() const;
    bool setHeatingSupplyAirFlowRate(double heatingSupplyAirFlowRate);
    void resetHeatingSupplyAirFlowRate();
    void autosizeHeatingSupplyAirFlowRate();

    boost::optional<double> noLoadSupplyAirFlowRate() const;
    bool isNoLoadSupplyAirFlowRateAutosized() const;
    bool setNoLoadSupplyAirFlowRate(double noLoadSupplyAirFlowRate);
    void resetNoLoadSupplyAirFlowRate();
    void autosizeNoLoadSupplyAirFlowRate();

    boost::optional<double> zoneHeatingSizingFactor() const;
    bool setZoneHeatingSizingFactor(double zoneHeatingSizingFactor);
    void resetZoneHeatingSizingFactor();

    boost::optional<double> zoneCoolingSizingFactor() const;
    bool setZoneCoolingSizingFactor(double zoneCoolingSizingFactor);
    void resetZoneCoolingSizingFactor();

    std::string outdoorAirMethod() const;
    bool isOutdoorAirMethodDefaulted() const;
    bool setOutdoorAirMethod(const std::string& outdoorAirMethod);
    void resetOutdoorAirMethod();

    double outdoorAirFlowRateperPerson() const;
    bool isOutdoorAirFlowRateperPersonDefaulted() const;
    bool setOutdoorAirFlowRateperPerson(double outdoorAirFlowRateperPerson);
    void resetOutdoorAirFlowRateperPerson();

    double outdoorAirFlowRateperZoneFloorArea() const;
    bool isOutdoorAirFlowRateperZoneFloorAreaDefaulted() const;
    bool setOutdoorAirFlowRateperZoneFloorArea(double outdoorAirFlowRateperZoneFloorArea);
    void resetOutdoorAirFlowRateperZoneFloorArea();

    double outdoorAirFlowRateperZone() const;
    bool isOutdoorAirFlowRateperZoneDefaulted() const;
    bool setOutdoorAirFlowRateperZone(double outdoorAirFlowRateperZone);
    void resetOutdoorAirFlowRateperZone();

    std::string supplyFanPlacement() const;
    bool isSupplyFanPlacementDefaulted() const;
    bool setSupplyFanPlacement(const std::string& supplyFanPlacement);
    void resetSupplyFanPlacement();

    double supplyFanTotalEfficiency() const;
    bool isSupplyFanTotalEfficiencyDefaulted() const;
    bool setSupplyFanTotalEfficiency(double supplyFanTotalEfficiency);
    void resetSupplyFanTotalEfficiency();

    double supplyFanDeltaPressure() const;
    bool isSupplyFanDeltaPressureDefaulted() const;
    bool setSupplyFanDeltaPressure(double supplyFanDeltaPressure);
    void resetSupplyFanDeltaPressure();

    double supplyFanMotorEfficiency() const;
    bool isSupplyFanMotorEfficiencyDefaulted() const;
    bool setSupplyFanMotorEfficiency(double supplyFanMotorEfficiency);
    void resetSupplyFanMotorEfficiency();

    std::string coolingCoilType() const;
    bool isCoolingCoilTypeDefaulted() const;
    bool setCoolingCoilType(const std::string& coolingCoilType);
    void resetCoolingCoilType();

    boost::optional<double> coolingCoilGrossRatedTotalCapacity() const;
    bool isCoolingCoilGrossRatedTotalCapacityDefaulted() const;
    bool isCoolingCoilGrossRatedTotalCapacityAutosized() const;
    bool setCoolingCoilGrossRatedTotalCapacity(double coolingCoilGrossRatedTotalCapacity);
    void resetCoolingCoilGrossRatedTotalCapacity();
    void autosizeCoolingCoilGrossRatedTotalCapacity();

    boost::optional<double> coolingCoilGrossRatedSensibleHeatRatio() const;
    bool isCoolingCoilGrossRatedSensibleHeatRatioDefaulted() const;
    bool isCoolingCoilGrossRatedSensibleHeatRatioAutosized() const;
    bool setCoolingCoilGrossRatedSensibleHeatRatio(double coolingCoilGrossRatedSensibleHeatRatio);
    void resetCoolingCoilGrossRatedSensibleHeatRatio();
    void autosizeCoolingCoilGrossRatedSensibleHeatRatio();

    double coolingCoilGrossRatedCOP() const;
    bool isCoolingCoilGrossRatedCOPDefaulted() const;
    bool setCoolingCoilGrossRatedCOP(double coolingCoilGrossRatedCOP);
    void resetCoolingCoilGrossRatedCOP();

    std::string heatPumpHeatingCoilType() const;
    bool isHeatPumpHeatingCoilTypeDefaulted() const;
    bool setHeatPumpHeatingCoilType(const std::string& heatPumpHeatingCoilType);
    void resetHeatPumpHeatingCoilType();

    boost::optional<double> heatPumpHeatingCoilGrossRatedCapacity() const;
    bool isHeatPumpHeatingCoilGrossRatedCapacityDefaulted() const;
    bool isHeatPumpHeatingCoilGrossRatedCapacityAutosized() const;
    bool setHeatPumpHeatingCoilGrossRatedCapacity(double heatPumpHeatingCoilGrossRatedCapacity);
    void resetHeatPumpHeatingCoilGrossRatedCapacity();
    void autosizeHeatPumpHeatingCoilGrossRatedCapacity();

    double heatPumpHeatingCoilGrossRatedCOP() const;
    bool isHeatPumpHeatingCoilGrossRatedCOPDefaulted() const;
    bool setHeatPumpHeatingCoilGrossRatedCOP(double heatPumpHeatingCoilGrossRatedCOP);
    void resetHeatPumpHeatingCoilGrossRatedCOP();

    boost::optional<double> supplementalHeatingCoilCapacity() const;
    bool isSupplementalHeatingCoilCapacityDefaulted() const;
    bool isSupplementalHeatingCoilCapacityAutosized() const;
    bool setSupplementalHeatingCoilCapacity(double supplementalHeatingCoilCapacity);
    void resetSupplementalHeatingCoilCapacity();
    void autosizeSupplementalHeatingCoilCapacity();

    double maximumCyclingRate() const;
    bool isMaximumCyclingRateDefaulted() const;
    bool setMaximumCyclingRate(double maximumCyclingRate);
    void resetMaximumCyclingRate();

    double latentCapacityTimeConstant() const;
    bool isLatentCapacityTimeConstantDefaulted() const;
    bool setLatentCapacityTimeConstant(double latentCapacityTimeConstant);
    void resetLatentCapacityTimeConstant();

    double heatPumpFanDelayTime() const;
    bool isHeatPumpFanDelayTimeDefaulted() const;
    bool setHeatPumpFanDelayTime(double heatPumpFanDelayTime);
    void resetHeatPumpFanDelayTime();

    std::string supplementalHeatingCoilType() const;
    bool isSupplementalHeatingCoilTypeDefaulted() const;
    bool setSupplementalHeatingCoilType(const std::string& supplementalHeatingCoilType);
    void resetSupplementalHeatingCoilType();

    std::string zoneCoolingDesignSupplyAirTemperatureInputMethod() const;
    bool isZoneCoolingDesignSupplyAirTemperatureInputMethodDefaulted() const;
    bool setZoneCoolingDesignSupplyAirTemperatureInputMethod(const std::string& zoneCoolingDesignSupplyAirTemperatureInputMethod);
    void resetZoneCoolingDesignSupplyAirTemperatureInputMethod();

    double zoneCoolingDesignSupplyAirTemperature() const;
    bool isZoneCoolingDesignSupplyAirTemperatureDefaulted() const;
    bool setZoneCoolingDesignSupplyAirTemperature(double zoneCoolingDesignSupplyAirTemperature);
    void resetZoneCoolingDesignSupplyAirTemperature();

    double zoneCoolingDesignSupplyAirTemperatureDifference() const;
    bool isZoneCoolingDesignSupplyAirTemperatureDifferenceDefaulted() const;
    bool setZoneCoolingDesignSupplyAirTemperatureDifference(double zoneCoolingDesignSupplyAirTemperatureDifference);
    void resetZoneCoolingDesignSupplyAirTemperatureDifference();

    std::string zoneHeatingDesignSupplyAirTemperatureInputMethod() const;
    bool isZoneHeatingDesignSupplyAirTemperatureInputMethodDefaulted() const;
    bool setZoneHeatingDesignSupplyAirTemperatureInputMethod(const std::string& zoneHeatingDesignSupplyAirTemperatureInputMethod);
    void resetZoneHeatingDesignSupplyAirTemperatureInputMethod();

    double zoneHeatingDesignSupplyAirTemperature() const;
    bool isZoneHeatingDesignSupplyAirTemperatureDefaulted() const;
    bool setZoneHeatingDesignSupplyAirTemperature(double zoneHeatingDesignSupplyAirTemperature);
    void resetZoneHeatingDesignSupplyAirTemperature();

    double zoneHeatingDesignSupplyAirTemperatureDifference() const;
    bool isZoneHeatingDesignSupplyAirTemperatureDifferenceDefaulted() const;
    bool setZoneHeatingDesignSupplyAirTemperatureDifference(double zoneHeatingDesignSupplyAirTemperatureDifference);
    void resetZoneHeatingDesignSupplyAirTemperatureDifference();

    std::string heatPumpCoilWaterFlowMode() const;
    bool isHeatPumpCoilWaterFlowModeDefaulted() const;
    bool setHeatPumpCoilWaterFlowMode(const std::string& heatPumpCoilWaterFlowMode);
    void resetHeatPumpCoilWaterFlowMode();

    std::string baseboardHeatingType() const;
    bool isBaseboardHeatingTypeDefaulted() const;
    bool setBaseboardHeatingType(const std::string& baseboardHeatingType);
    void resetBaseboardHeatingType();

    boost::optional<double> baseboardHeatingCapacity() const;
    bool isBaseboardHeatingCapacityDefaulted() const;
    bool isBaseboardHeatingCapacityAutosized() const;
    bool setBaseboardHeatingCapacity(double baseboardHeatingCapacity);
    void resetBaseboardHeatingCapacity();
    void autosizeBaseboardHeatingCapacity();

    //@}

   protected:
    using ImplType = detail::HVACTemplateZoneWaterToAirHeatPump_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit HVACTemplateZoneWaterToAirHeatPump(std::shared_ptr<detail::HVACTemplateZoneWaterToAirHeatPump_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
