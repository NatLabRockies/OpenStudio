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

    /** @name Field Accessors */
    //@{

    // Cooling supply air flow rate
    boost::optional<double> coolingSupplyAirFlowRate() const;
    bool isCoolingSupplyAirFlowRateDefaulted() const;
    bool isCoolingSupplyAirFlowRateAutosized() const;
    bool setCoolingSupplyAirFlowRate(double coolingSupplyAirFlowRate);
    void resetCoolingSupplyAirFlowRate();
    void autosizeCoolingSupplyAirFlowRate();

    // Heating supply air flow rate
    boost::optional<double> heatingSupplyAirFlowRate() const;
    bool isHeatingSupplyAirFlowRateDefaulted() const;
    bool isHeatingSupplyAirFlowRateAutosized() const;
    bool setHeatingSupplyAirFlowRate(double heatingSupplyAirFlowRate);
    void resetHeatingSupplyAirFlowRate();
    void autosizeHeatingSupplyAirFlowRate();

    // No-load supply air flow rate
    boost::optional<double> noLoadSupplyAirFlowRate() const;
    bool isNoLoadSupplyAirFlowRateDefaulted() const;
    bool isNoLoadSupplyAirFlowRateAutosized() const;
    bool setNoLoadSupplyAirFlowRate(double noLoadSupplyAirFlowRate);
    void resetNoLoadSupplyAirFlowRate();
    void autosizeNoLoadSupplyAirFlowRate();

    // Zone sizing factors
    boost::optional<double> zoneHeatingSizingFactor() const;
    bool isZoneHeatingSizingFactorDefaulted() const;
    bool setZoneHeatingSizingFactor(double zoneHeatingSizingFactor);
    void resetZoneHeatingSizingFactor();

    boost::optional<double> zoneCoolingSizingFactor() const;
    bool isZoneCoolingSizingFactorDefaulted() const;
    bool setZoneCoolingSizingFactor(double zoneCoolingSizingFactor);
    void resetZoneCoolingSizingFactor();

    // Outdoor air
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

    // Supply fan
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

    // Cooling coil
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

    double coolingCoilGrossRatedCoolingCOP() const;
    bool isCoolingCoilGrossRatedCoolingCOPDefaulted() const;
    bool setCoolingCoilGrossRatedCoolingCOP(double coolingCoilGrossRatedCoolingCOP);
    void resetCoolingCoilGrossRatedCoolingCOP();

    // Heating coil
    std::string heatingCoilType() const;
    bool isHeatingCoilTypeDefaulted() const;
    bool setHeatingCoilType(const std::string& heatingCoilType);
    void resetHeatingCoilType();

    boost::optional<double> heatingCoilCapacity() const;
    bool isHeatingCoilCapacityDefaulted() const;
    bool isHeatingCoilCapacityAutosized() const;
    bool setHeatingCoilCapacity(double heatingCoilCapacity);
    void resetHeatingCoilCapacity();
    void autosizeHeatingCoilCapacity();

    double gasHeatingCoilEfficiency() const;
    bool isGasHeatingCoilEfficiencyDefaulted() const;
    bool setGasHeatingCoilEfficiency(double gasHeatingCoilEfficiency);
    void resetGasHeatingCoilEfficiency();

    double gasHeatingCoilParasiticElectricLoad() const;
    bool isGasHeatingCoilParasiticElectricLoadDefaulted() const;
    bool setGasHeatingCoilParasiticElectricLoad(double gasHeatingCoilParasiticElectricLoad);
    void resetGasHeatingCoilParasiticElectricLoad();

    // Zone cooling design supply air temperature
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

    // Zone heating design supply air temperature
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

    // Baseboard heating
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

    // Capacity control
    std::string capacityControlMethod() const;
    bool isCapacityControlMethodDefaulted() const;
    bool setCapacityControlMethod(const std::string& capacityControlMethod);
    void resetCapacityControlMethod();

    //@}

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
