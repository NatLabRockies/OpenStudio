/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HVACTEMPLATESYSTEMPACKAGEDVAV_HPP
#define EPMODEL_HVACTEMPLATESYSTEMPACKAGEDVAV_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class HVACTemplateSystemPackagedVAV_Impl;
  }

  class EPMODEL_API HVACTemplateSystemPackagedVAV : public ModelObject
  {
   public:
    explicit HVACTemplateSystemPackagedVAV(const Model& model);

    virtual ~HVACTemplateSystemPackagedVAV() override = default;
    HVACTemplateSystemPackagedVAV(const HVACTemplateSystemPackagedVAV& other) = default;
    HVACTemplateSystemPackagedVAV(HVACTemplateSystemPackagedVAV&& other) = default;
    HVACTemplateSystemPackagedVAV& operator=(const HVACTemplateSystemPackagedVAV&) = default;
    HVACTemplateSystemPackagedVAV& operator=(HVACTemplateSystemPackagedVAV&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> supplyFanPlacementValues();
    static std::vector<std::string> coolingCoilTypeValues();
    static std::vector<std::string> heatingCoilTypeValues();
    static std::vector<std::string> minimumOutdoorAirControlTypeValues();
    static std::vector<std::string> economizerTypeValues();
    static std::vector<std::string> economizerLockoutValues();
    static std::vector<std::string> supplyFanPartLoadPowerCoefficientsValues();
    static std::vector<std::string> nightCycleControlValues();
    static std::vector<std::string> heatRecoveryTypeValues();
    static std::vector<std::string> coolingCoilSetpointResetTypeValues();
    static std::vector<std::string> heatingCoilSetpointResetTypeValues();
    static std::vector<std::string> dehumidificationControlTypeValues();
    static std::vector<std::string> humidifierTypeValues();
    static std::vector<std::string> sizingOptionValues();
    static std::vector<std::string> returnFanPartLoadPowerCoefficientsValues();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: Scalar APIs map directly to HVACTemplate:System:PackagedVAV non-name, non-link scalar fields.
    // - Field Mapping: Schedule/plenum/control-zone object-list fields are relationship-like and excluded from scalar accessors.
    // - TODO(parity): Add relationship/object-link APIs in a later parity pass.
    /** @name Field accessors */
    //@{

    // Supply fan maximum flow rate
    boost::optional<double> supplyFanMaximumFlowRate() const;
    bool isSupplyFanMaximumFlowRateDefaulted() const;
    bool isSupplyFanMaximumFlowRateAutosized() const;
    bool setSupplyFanMaximumFlowRate(double supplyFanMaximumFlowRate);
    void resetSupplyFanMaximumFlowRate();
    void autosizeSupplyFanMaximumFlowRate();

    // Supply fan minimum flow rate
    boost::optional<double> supplyFanMinimumFlowRate() const;
    bool isSupplyFanMinimumFlowRateDefaulted() const;
    bool isSupplyFanMinimumFlowRateAutosized() const;
    bool setSupplyFanMinimumFlowRate(double supplyFanMinimumFlowRate);
    void resetSupplyFanMinimumFlowRate();
    void autosizeSupplyFanMinimumFlowRate();

    // Supply fan placement
    std::string supplyFanPlacement() const;
    bool isSupplyFanPlacementDefaulted() const;
    bool setSupplyFanPlacement(const std::string& supplyFanPlacement);
    void resetSupplyFanPlacement();

    // Supply fan total efficiency
    double supplyFanTotalEfficiency() const;
    bool isSupplyFanTotalEfficiencyDefaulted() const;
    bool setSupplyFanTotalEfficiency(double supplyFanTotalEfficiency);
    void resetSupplyFanTotalEfficiency();

    // Supply fan delta pressure
    double supplyFanDeltaPressure() const;
    bool isSupplyFanDeltaPressureDefaulted() const;
    bool setSupplyFanDeltaPressure(double supplyFanDeltaPressure);
    void resetSupplyFanDeltaPressure();

    // Supply fan motor efficiency
    double supplyFanMotorEfficiency() const;
    bool isSupplyFanMotorEfficiencyDefaulted() const;
    bool setSupplyFanMotorEfficiency(double supplyFanMotorEfficiency);
    void resetSupplyFanMotorEfficiency();

    // Supply fan motor in air stream fraction
    double supplyFanMotorinAirStreamFraction() const;
    bool isSupplyFanMotorinAirStreamFractionDefaulted() const;
    bool setSupplyFanMotorinAirStreamFraction(double supplyFanMotorinAirStreamFraction);
    void resetSupplyFanMotorinAirStreamFraction();

    // Cooling coil type
    std::string coolingCoilType() const;
    bool isCoolingCoilTypeDefaulted() const;
    bool setCoolingCoilType(const std::string& coolingCoilType);
    void resetCoolingCoilType();

    // Cooling coil design setpoint
    double coolingCoilDesignSetpoint() const;
    bool isCoolingCoilDesignSetpointDefaulted() const;
    bool setCoolingCoilDesignSetpoint(double coolingCoilDesignSetpoint);
    void resetCoolingCoilDesignSetpoint();

    // Cooling coil gross rated total capacity
    boost::optional<double> coolingCoilGrossRatedTotalCapacity() const;
    bool isCoolingCoilGrossRatedTotalCapacityDefaulted() const;
    bool isCoolingCoilGrossRatedTotalCapacityAutosized() const;
    bool setCoolingCoilGrossRatedTotalCapacity(double coolingCoilGrossRatedTotalCapacity);
    void resetCoolingCoilGrossRatedTotalCapacity();
    void autosizeCoolingCoilGrossRatedTotalCapacity();

    // Cooling coil gross rated sensible heat ratio
    boost::optional<double> coolingCoilGrossRatedSensibleHeatRatio() const;
    bool isCoolingCoilGrossRatedSensibleHeatRatioDefaulted() const;
    bool isCoolingCoilGrossRatedSensibleHeatRatioAutosized() const;
    bool setCoolingCoilGrossRatedSensibleHeatRatio(double coolingCoilGrossRatedSensibleHeatRatio);
    void resetCoolingCoilGrossRatedSensibleHeatRatio();
    void autosizeCoolingCoilGrossRatedSensibleHeatRatio();

    // Cooling coil gross rated COP
    double coolingCoilGrossRatedCOP() const;
    bool isCoolingCoilGrossRatedCOPDefaulted() const;
    bool setCoolingCoilGrossRatedCOP(double coolingCoilGrossRatedCOP);
    void resetCoolingCoilGrossRatedCOP();

    // Heating coil type
    std::string heatingCoilType() const;
    bool isHeatingCoilTypeDefaulted() const;
    bool setHeatingCoilType(const std::string& heatingCoilType);
    void resetHeatingCoilType();

    // Heating coil design setpoint
    double heatingCoilDesignSetpoint() const;
    bool isHeatingCoilDesignSetpointDefaulted() const;
    bool setHeatingCoilDesignSetpoint(double heatingCoilDesignSetpoint);
    void resetHeatingCoilDesignSetpoint();

    // Heating coil capacity
    boost::optional<double> heatingCoilCapacity() const;
    bool isHeatingCoilCapacityDefaulted() const;
    bool isHeatingCoilCapacityAutosized() const;
    bool setHeatingCoilCapacity(double heatingCoilCapacity);
    void resetHeatingCoilCapacity();
    void autosizeHeatingCoilCapacity();

    // Gas heating coil efficiency
    double gasHeatingCoilEfficiency() const;
    bool isGasHeatingCoilEfficiencyDefaulted() const;
    bool setGasHeatingCoilEfficiency(double gasHeatingCoilEfficiency);
    void resetGasHeatingCoilEfficiency();

    // Gas heating coil parasitic electric load
    double gasHeatingCoilParasiticElectricLoad() const;
    bool isGasHeatingCoilParasiticElectricLoadDefaulted() const;
    bool setGasHeatingCoilParasiticElectricLoad(double gasHeatingCoilParasiticElectricLoad);
    void resetGasHeatingCoilParasiticElectricLoad();

    // Maximum outdoor air flow rate
    boost::optional<double> maximumOutdoorAirFlowRate() const;
    bool isMaximumOutdoorAirFlowRateDefaulted() const;
    bool isMaximumOutdoorAirFlowRateAutosized() const;
    bool setMaximumOutdoorAirFlowRate(double maximumOutdoorAirFlowRate);
    void resetMaximumOutdoorAirFlowRate();
    void autosizeMaximumOutdoorAirFlowRate();

    // Minimum outdoor air flow rate
    boost::optional<double> minimumOutdoorAirFlowRate() const;
    bool isMinimumOutdoorAirFlowRateDefaulted() const;
    bool isMinimumOutdoorAirFlowRateAutosized() const;
    bool setMinimumOutdoorAirFlowRate(double minimumOutdoorAirFlowRate);
    void resetMinimumOutdoorAirFlowRate();
    void autosizeMinimumOutdoorAirFlowRate();

    // Minimum outdoor air control type
    std::string minimumOutdoorAirControlType() const;
    bool isMinimumOutdoorAirControlTypeDefaulted() const;
    bool setMinimumOutdoorAirControlType(const std::string& minimumOutdoorAirControlType);
    void resetMinimumOutdoorAirControlType();

    // Economizer type
    std::string economizerType() const;
    bool isEconomizerTypeDefaulted() const;
    bool setEconomizerType(const std::string& economizerType);
    void resetEconomizerType();

    // Economizer lockout
    std::string economizerLockout() const;
    bool isEconomizerLockoutDefaulted() const;
    bool setEconomizerLockout(const std::string& economizerLockout);
    void resetEconomizerLockout();

    // Economizer maximum limit dry-bulb temperature
    boost::optional<double> economizerMaximumLimitDryBulbTemperature() const;
    bool isEconomizerMaximumLimitDryBulbTemperatureDefaulted() const;
    bool setEconomizerMaximumLimitDryBulbTemperature(double economizerMaximumLimitDryBulbTemperature);
    void resetEconomizerMaximumLimitDryBulbTemperature();

    // Economizer maximum limit enthalpy
    boost::optional<double> economizerMaximumLimitEnthalpy() const;
    bool isEconomizerMaximumLimitEnthalpyDefaulted() const;
    bool setEconomizerMaximumLimitEnthalpy(double economizerMaximumLimitEnthalpy);
    void resetEconomizerMaximumLimitEnthalpy();

    // Economizer maximum limit dewpoint temperature
    boost::optional<double> economizerMaximumLimitDewpointTemperature() const;
    bool isEconomizerMaximumLimitDewpointTemperatureDefaulted() const;
    bool setEconomizerMaximumLimitDewpointTemperature(double economizerMaximumLimitDewpointTemperature);
    void resetEconomizerMaximumLimitDewpointTemperature();

    // Economizer minimum limit dry-bulb temperature
    boost::optional<double> economizerMinimumLimitDryBulbTemperature() const;
    bool isEconomizerMinimumLimitDryBulbTemperatureDefaulted() const;
    bool setEconomizerMinimumLimitDryBulbTemperature(double economizerMinimumLimitDryBulbTemperature);
    void resetEconomizerMinimumLimitDryBulbTemperature();

    // Supply fan part load power coefficients
    std::string supplyFanPartLoadPowerCoefficients() const;
    bool isSupplyFanPartLoadPowerCoefficientsDefaulted() const;
    bool setSupplyFanPartLoadPowerCoefficients(const std::string& supplyFanPartLoadPowerCoefficients);
    void resetSupplyFanPartLoadPowerCoefficients();

    // Night cycle control
    std::string nightCycleControl() const;
    bool isNightCycleControlDefaulted() const;
    bool setNightCycleControl(const std::string& nightCycleControl);
    void resetNightCycleControl();

    // Heat recovery type
    std::string heatRecoveryType() const;
    bool isHeatRecoveryTypeDefaulted() const;
    bool setHeatRecoveryType(const std::string& heatRecoveryType);
    void resetHeatRecoveryType();

    // Sensible heat recovery effectiveness
    double sensibleHeatRecoveryEffectiveness() const;
    bool isSensibleHeatRecoveryEffectivenessDefaulted() const;
    bool setSensibleHeatRecoveryEffectiveness(double sensibleHeatRecoveryEffectiveness);
    void resetSensibleHeatRecoveryEffectiveness();

    // Latent heat recovery effectiveness
    double latentHeatRecoveryEffectiveness() const;
    bool isLatentHeatRecoveryEffectivenessDefaulted() const;
    bool setLatentHeatRecoveryEffectiveness(double latentHeatRecoveryEffectiveness);
    void resetLatentHeatRecoveryEffectiveness();

    // Cooling coil setpoint reset type
    std::string coolingCoilSetpointResetType() const;
    bool isCoolingCoilSetpointResetTypeDefaulted() const;
    bool setCoolingCoilSetpointResetType(const std::string& coolingCoilSetpointResetType);
    void resetCoolingCoilSetpointResetType();

    // Heating coil setpoint reset type
    std::string heatingCoilSetpointResetType() const;
    bool isHeatingCoilSetpointResetTypeDefaulted() const;
    bool setHeatingCoilSetpointResetType(const std::string& heatingCoilSetpointResetType);
    void resetHeatingCoilSetpointResetType();

    // Dehumidification control type
    std::string dehumidificationControlType() const;
    bool isDehumidificationControlTypeDefaulted() const;
    bool setDehumidificationControlType(const std::string& dehumidificationControlType);
    void resetDehumidificationControlType();

    // Dehumidification setpoint
    double dehumidificationSetpoint() const;
    bool isDehumidificationSetpointDefaulted() const;
    bool setDehumidificationSetpoint(double dehumidificationSetpoint);
    void resetDehumidificationSetpoint();

    // Humidifier type
    std::string humidifierType() const;
    bool isHumidifierTypeDefaulted() const;
    bool setHumidifierType(const std::string& humidifierType);
    void resetHumidifierType();

    // Humidifier rated capacity
    double humidifierRatedCapacity() const;
    bool isHumidifierRatedCapacityDefaulted() const;
    bool setHumidifierRatedCapacity(double humidifierRatedCapacity);
    void resetHumidifierRatedCapacity();

    // Humidifier rated electric power
    boost::optional<double> humidifierRatedElectricPower() const;
    bool isHumidifierRatedElectricPowerDefaulted() const;
    bool isHumidifierRatedElectricPowerAutosized() const;
    bool setHumidifierRatedElectricPower(double humidifierRatedElectricPower);
    void resetHumidifierRatedElectricPower();
    void autosizeHumidifierRatedElectricPower();

    // Humidifier setpoint
    double humidifierSetpoint() const;
    bool isHumidifierSetpointDefaulted() const;
    bool setHumidifierSetpoint(double humidifierSetpoint);
    void resetHumidifierSetpoint();

    // Sizing option
    std::string sizingOption() const;
    bool isSizingOptionDefaulted() const;
    bool setSizingOption(const std::string& sizingOption);
    void resetSizingOption();

    // Return fan
    bool returnFan() const;
    bool isReturnFanDefaulted() const;
    bool setReturnFan(bool returnFan);
    void resetReturnFan();

    // Return fan total efficiency
    double returnFanTotalEfficiency() const;
    bool isReturnFanTotalEfficiencyDefaulted() const;
    bool setReturnFanTotalEfficiency(double returnFanTotalEfficiency);
    void resetReturnFanTotalEfficiency();

    // Return fan delta pressure
    double returnFanDeltaPressure() const;
    bool isReturnFanDeltaPressureDefaulted() const;
    bool setReturnFanDeltaPressure(double returnFanDeltaPressure);
    void resetReturnFanDeltaPressure();

    // Return fan motor efficiency
    double returnFanMotorEfficiency() const;
    bool isReturnFanMotorEfficiencyDefaulted() const;
    bool setReturnFanMotorEfficiency(double returnFanMotorEfficiency);
    void resetReturnFanMotorEfficiency();

    // Return fan motor in air stream fraction
    double returnFanMotorinAirStreamFraction() const;
    bool isReturnFanMotorinAirStreamFractionDefaulted() const;
    bool setReturnFanMotorinAirStreamFraction(double returnFanMotorinAirStreamFraction);
    void resetReturnFanMotorinAirStreamFraction();

    // Return fan part load power coefficients
    std::string returnFanPartLoadPowerCoefficients() const;
    bool isReturnFanPartLoadPowerCoefficientsDefaulted() const;
    bool setReturnFanPartLoadPowerCoefficients(const std::string& returnFanPartLoadPowerCoefficients);
    void resetReturnFanPartLoadPowerCoefficients();

    //@}

   protected:
    using ImplType = detail::HVACTemplateSystemPackagedVAV_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit HVACTemplateSystemPackagedVAV(std::shared_ptr<detail::HVACTemplateSystemPackagedVAV_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
