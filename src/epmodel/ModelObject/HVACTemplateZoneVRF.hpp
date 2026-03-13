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
    boost::optional<double> zoneHeatingSizingFactor() const;
    bool setZoneHeatingSizingFactor(double zoneHeatingSizingFactor);
    void resetZoneHeatingSizingFactor();

    boost::optional<double> zoneCoolingSizingFactor() const;
    bool setZoneCoolingSizingFactor(double zoneCoolingSizingFactor);
    void resetZoneCoolingSizingFactor();

    double ratedTotalHeatingCapacitySizingRatio() const;
    bool isRatedTotalHeatingCapacitySizingRatioDefaulted() const;
    bool setRatedTotalHeatingCapacitySizingRatio(double ratedTotalHeatingCapacitySizingRatio);
    void resetRatedTotalHeatingCapacitySizingRatio();

    boost::optional<double> coolingSupplyAirFlowRate() const;
    bool isCoolingSupplyAirFlowRateDefaulted() const;
    bool isCoolingSupplyAirFlowRateAutosized() const;
    bool setCoolingSupplyAirFlowRate(double coolingSupplyAirFlowRate);
    void resetCoolingSupplyAirFlowRate();
    void autosizeCoolingSupplyAirFlowRate();

    boost::optional<double> noCoolingSupplyAirFlowRate() const;
    bool isNoCoolingSupplyAirFlowRateDefaulted() const;
    bool isNoCoolingSupplyAirFlowRateAutosized() const;
    bool setNoCoolingSupplyAirFlowRate(double noCoolingSupplyAirFlowRate);
    void resetNoCoolingSupplyAirFlowRate();
    void autosizeNoCoolingSupplyAirFlowRate();

    boost::optional<double> heatingSupplyAirFlowRate() const;
    bool isHeatingSupplyAirFlowRateDefaulted() const;
    bool isHeatingSupplyAirFlowRateAutosized() const;
    bool setHeatingSupplyAirFlowRate(double heatingSupplyAirFlowRate);
    void resetHeatingSupplyAirFlowRate();
    void autosizeHeatingSupplyAirFlowRate();

    boost::optional<double> noHeatingSupplyAirFlowRate() const;
    bool isNoHeatingSupplyAirFlowRateDefaulted() const;
    bool isNoHeatingSupplyAirFlowRateAutosized() const;
    bool setNoHeatingSupplyAirFlowRate(double noHeatingSupplyAirFlowRate);
    void resetNoHeatingSupplyAirFlowRate();
    void autosizeNoHeatingSupplyAirFlowRate();

    boost::optional<double> coolingOutdoorAirFlowRate() const;
    bool isCoolingOutdoorAirFlowRateDefaulted() const;
    bool isCoolingOutdoorAirFlowRateAutosized() const;
    bool setCoolingOutdoorAirFlowRate(double coolingOutdoorAirFlowRate);
    void resetCoolingOutdoorAirFlowRate();
    void autosizeCoolingOutdoorAirFlowRate();

    boost::optional<double> heatingOutdoorAirFlowRate() const;
    bool isHeatingOutdoorAirFlowRateDefaulted() const;
    bool isHeatingOutdoorAirFlowRateAutosized() const;
    bool setHeatingOutdoorAirFlowRate(double heatingOutdoorAirFlowRate);
    void resetHeatingOutdoorAirFlowRate();
    void autosizeHeatingOutdoorAirFlowRate();

    boost::optional<double> noLoadOutdoorAirFlowRate() const;
    bool isNoLoadOutdoorAirFlowRateDefaulted() const;
    bool isNoLoadOutdoorAirFlowRateAutosized() const;
    bool setNoLoadOutdoorAirFlowRate(double noLoadOutdoorAirFlowRate);
    void resetNoLoadOutdoorAirFlowRate();
    void autosizeNoLoadOutdoorAirFlowRate();

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

    std::string supplyAirFanplacement() const;
    bool isSupplyAirFanplacementDefaulted() const;
    bool setSupplyAirFanplacement(const std::string& supplyAirFanplacement);
    void resetSupplyAirFanplacement();

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

    double zoneTerminalUnitOnParasiticElectricEnergyUse() const;
    bool isZoneTerminalUnitOnParasiticElectricEnergyUseDefaulted() const;
    bool setZoneTerminalUnitOnParasiticElectricEnergyUse(double zoneTerminalUnitOnParasiticElectricEnergyUse);
    void resetZoneTerminalUnitOnParasiticElectricEnergyUse();

    double zoneTerminalUnitOffParasiticElectricEnergyUse() const;
    bool isZoneTerminalUnitOffParasiticElectricEnergyUseDefaulted() const;
    bool setZoneTerminalUnitOffParasiticElectricEnergyUse(double zoneTerminalUnitOffParasiticElectricEnergyUse);
    void resetZoneTerminalUnitOffParasiticElectricEnergyUse();

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
