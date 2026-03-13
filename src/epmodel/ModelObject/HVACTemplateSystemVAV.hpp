/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HVACTEMPLATESYSTEMVAV_HPP
#define EPMODEL_HVACTEMPLATESYSTEMVAV_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class HVACTemplateSystemVAV_Impl;
  }

  class EPMODEL_API HVACTemplateSystemVAV : public ModelObject
  {
   public:
    explicit HVACTemplateSystemVAV(const Model& model);

    virtual ~HVACTemplateSystemVAV() override = default;
    HVACTemplateSystemVAV(const HVACTemplateSystemVAV& other) = default;
    HVACTemplateSystemVAV(HVACTemplateSystemVAV&& other) = default;
    HVACTemplateSystemVAV& operator=(const HVACTemplateSystemVAV&) = default;
    HVACTemplateSystemVAV& operator=(HVACTemplateSystemVAV&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> supplyFanPlacementValues();
    static std::vector<std::string> coolingCoilTypeValues();
    static std::vector<std::string> heatingCoilTypeValues();
    static std::vector<std::string> preheatCoilTypeValues();
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
    // - Field Mapping: Scalar APIs map directly to HVACTemplate:System:VAV non-name, non-link scalar fields.
    // - Field Mapping: Schedule/plenum/control-zone object-list fields are relationship-like and excluded from scalar accessors.
    // - TODO(parity): Add relationship/object-link APIs in a later parity pass.

    boost::optional<double> supplyFanMaximumFlowRate() const;
    bool isSupplyFanMaximumFlowRateDefaulted() const;
    bool isSupplyFanMaximumFlowRateAutosized() const;
    bool setSupplyFanMaximumFlowRate(double supplyFanMaximumFlowRate);
    void resetSupplyFanMaximumFlowRate();
    void autosizeSupplyFanMaximumFlowRate();

    boost::optional<double> supplyFanMinimumFlowRate() const;
    bool isSupplyFanMinimumFlowRateDefaulted() const;
    bool isSupplyFanMinimumFlowRateAutosized() const;
    bool setSupplyFanMinimumFlowRate(double supplyFanMinimumFlowRate);
    void resetSupplyFanMinimumFlowRate();
    void autosizeSupplyFanMinimumFlowRate();

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

    double supplyFanMotorinAirStreamFraction() const;
    bool isSupplyFanMotorinAirStreamFractionDefaulted() const;
    bool setSupplyFanMotorinAirStreamFraction(double supplyFanMotorinAirStreamFraction);
    void resetSupplyFanMotorinAirStreamFraction();

    std::string coolingCoilType() const;
    bool isCoolingCoilTypeDefaulted() const;
    bool setCoolingCoilType(const std::string& coolingCoilType);
    void resetCoolingCoilType();

    double coolingCoilDesignSetpoint() const;
    bool isCoolingCoilDesignSetpointDefaulted() const;
    bool setCoolingCoilDesignSetpoint(double coolingCoilDesignSetpoint);
    void resetCoolingCoilDesignSetpoint();

    std::string heatingCoilType() const;
    bool isHeatingCoilTypeDefaulted() const;
    bool setHeatingCoilType(const std::string& heatingCoilType);
    void resetHeatingCoilType();

    double heatingCoilDesignSetpoint() const;
    bool isHeatingCoilDesignSetpointDefaulted() const;
    bool setHeatingCoilDesignSetpoint(double heatingCoilDesignSetpoint);
    void resetHeatingCoilDesignSetpoint();

    double gasHeatingCoilEfficiency() const;
    bool isGasHeatingCoilEfficiencyDefaulted() const;
    bool setGasHeatingCoilEfficiency(double gasHeatingCoilEfficiency);
    void resetGasHeatingCoilEfficiency();

    double gasHeatingCoilParasiticElectricLoad() const;
    bool isGasHeatingCoilParasiticElectricLoadDefaulted() const;
    bool setGasHeatingCoilParasiticElectricLoad(double gasHeatingCoilParasiticElectricLoad);
    void resetGasHeatingCoilParasiticElectricLoad();

    std::string preheatCoilType() const;
    bool isPreheatCoilTypeDefaulted() const;
    bool setPreheatCoilType(const std::string& preheatCoilType);
    void resetPreheatCoilType();

    double preheatCoilDesignSetpoint() const;
    bool isPreheatCoilDesignSetpointDefaulted() const;
    bool setPreheatCoilDesignSetpoint(double preheatCoilDesignSetpoint);
    void resetPreheatCoilDesignSetpoint();

    double gasPreheatCoilEfficiency() const;
    bool isGasPreheatCoilEfficiencyDefaulted() const;
    bool setGasPreheatCoilEfficiency(double gasPreheatCoilEfficiency);
    void resetGasPreheatCoilEfficiency();

    double gasPreheatCoilParasiticElectricLoad() const;
    bool isGasPreheatCoilParasiticElectricLoadDefaulted() const;
    bool setGasPreheatCoilParasiticElectricLoad(double gasPreheatCoilParasiticElectricLoad);
    void resetGasPreheatCoilParasiticElectricLoad();

    boost::optional<double> maximumOutdoorAirFlowRate() const;
    bool isMaximumOutdoorAirFlowRateDefaulted() const;
    bool isMaximumOutdoorAirFlowRateAutosized() const;
    bool setMaximumOutdoorAirFlowRate(double maximumOutdoorAirFlowRate);
    void resetMaximumOutdoorAirFlowRate();
    void autosizeMaximumOutdoorAirFlowRate();

    boost::optional<double> minimumOutdoorAirFlowRate() const;
    bool isMinimumOutdoorAirFlowRateDefaulted() const;
    bool isMinimumOutdoorAirFlowRateAutosized() const;
    bool setMinimumOutdoorAirFlowRate(double minimumOutdoorAirFlowRate);
    void resetMinimumOutdoorAirFlowRate();
    void autosizeMinimumOutdoorAirFlowRate();

    std::string minimumOutdoorAirControlType() const;
    bool isMinimumOutdoorAirControlTypeDefaulted() const;
    bool setMinimumOutdoorAirControlType(const std::string& minimumOutdoorAirControlType);
    void resetMinimumOutdoorAirControlType();

    std::string economizerType() const;
    bool isEconomizerTypeDefaulted() const;
    bool setEconomizerType(const std::string& economizerType);
    void resetEconomizerType();

    std::string economizerLockout() const;
    bool isEconomizerLockoutDefaulted() const;
    bool setEconomizerLockout(const std::string& economizerLockout);
    void resetEconomizerLockout();

    boost::optional<double> economizerUpperTemperatureLimit() const;
    bool isEconomizerUpperTemperatureLimitDefaulted() const;
    bool setEconomizerUpperTemperatureLimit(double economizerUpperTemperatureLimit);
    void resetEconomizerUpperTemperatureLimit();

    boost::optional<double> economizerLowerTemperatureLimit() const;
    bool isEconomizerLowerTemperatureLimitDefaulted() const;
    bool setEconomizerLowerTemperatureLimit(double economizerLowerTemperatureLimit);
    void resetEconomizerLowerTemperatureLimit();

    boost::optional<double> economizerUpperEnthalpyLimit() const;
    bool isEconomizerUpperEnthalpyLimitDefaulted() const;
    bool setEconomizerUpperEnthalpyLimit(double economizerUpperEnthalpyLimit);
    void resetEconomizerUpperEnthalpyLimit();

    boost::optional<double> economizerMaximumLimitDewpointTemperature() const;
    bool isEconomizerMaximumLimitDewpointTemperatureDefaulted() const;
    bool setEconomizerMaximumLimitDewpointTemperature(double economizerMaximumLimitDewpointTemperature);
    void resetEconomizerMaximumLimitDewpointTemperature();

    std::string supplyFanPartLoadPowerCoefficients() const;
    bool isSupplyFanPartLoadPowerCoefficientsDefaulted() const;
    bool setSupplyFanPartLoadPowerCoefficients(const std::string& supplyFanPartLoadPowerCoefficients);
    void resetSupplyFanPartLoadPowerCoefficients();

    std::string nightCycleControl() const;
    bool isNightCycleControlDefaulted() const;
    bool setNightCycleControl(const std::string& nightCycleControl);
    void resetNightCycleControl();

    std::string heatRecoveryType() const;
    bool isHeatRecoveryTypeDefaulted() const;
    bool setHeatRecoveryType(const std::string& heatRecoveryType);
    void resetHeatRecoveryType();

    double sensibleHeatRecoveryEffectiveness() const;
    bool isSensibleHeatRecoveryEffectivenessDefaulted() const;
    bool setSensibleHeatRecoveryEffectiveness(double sensibleHeatRecoveryEffectiveness);
    void resetSensibleHeatRecoveryEffectiveness();

    double latentHeatRecoveryEffectiveness() const;
    bool isLatentHeatRecoveryEffectivenessDefaulted() const;
    bool setLatentHeatRecoveryEffectiveness(double latentHeatRecoveryEffectiveness);
    void resetLatentHeatRecoveryEffectiveness();

    std::string coolingCoilSetpointResetType() const;
    bool isCoolingCoilSetpointResetTypeDefaulted() const;
    bool setCoolingCoilSetpointResetType(const std::string& coolingCoilSetpointResetType);
    void resetCoolingCoilSetpointResetType();

    std::string heatingCoilSetpointResetType() const;
    bool isHeatingCoilSetpointResetTypeDefaulted() const;
    bool setHeatingCoilSetpointResetType(const std::string& heatingCoilSetpointResetType);
    void resetHeatingCoilSetpointResetType();

    std::string dehumidificationControlType() const;
    bool isDehumidificationControlTypeDefaulted() const;
    bool setDehumidificationControlType(const std::string& dehumidificationControlType);
    void resetDehumidificationControlType();

    double dehumidificationSetpoint() const;
    bool isDehumidificationSetpointDefaulted() const;
    bool setDehumidificationSetpoint(double dehumidificationSetpoint);
    void resetDehumidificationSetpoint();

    std::string humidifierType() const;
    bool isHumidifierTypeDefaulted() const;
    bool setHumidifierType(const std::string& humidifierType);
    void resetHumidifierType();

    double humidifierRatedCapacity() const;
    bool isHumidifierRatedCapacityDefaulted() const;
    bool setHumidifierRatedCapacity(double humidifierRatedCapacity);
    void resetHumidifierRatedCapacity();

    boost::optional<double> humidifierRatedElectricPower() const;
    bool isHumidifierRatedElectricPowerDefaulted() const;
    bool isHumidifierRatedElectricPowerAutosized() const;
    bool setHumidifierRatedElectricPower(double humidifierRatedElectricPower);
    void resetHumidifierRatedElectricPower();
    void autosizeHumidifierRatedElectricPower();

    double humidifierSetpoint() const;
    bool isHumidifierSetpointDefaulted() const;
    bool setHumidifierSetpoint(double humidifierSetpoint);
    void resetHumidifierSetpoint();

    std::string sizingOption() const;
    bool isSizingOptionDefaulted() const;
    bool setSizingOption(const std::string& sizingOption);
    void resetSizingOption();

    bool returnFan() const;
    bool isReturnFanDefaulted() const;
    bool setReturnFan(bool returnFan);
    void resetReturnFan();

    double returnFanTotalEfficiency() const;
    bool isReturnFanTotalEfficiencyDefaulted() const;
    bool setReturnFanTotalEfficiency(double returnFanTotalEfficiency);
    void resetReturnFanTotalEfficiency();

    double returnFanDeltaPressure() const;
    bool isReturnFanDeltaPressureDefaulted() const;
    bool setReturnFanDeltaPressure(double returnFanDeltaPressure);
    void resetReturnFanDeltaPressure();

    double returnFanMotorEfficiency() const;
    bool isReturnFanMotorEfficiencyDefaulted() const;
    bool setReturnFanMotorEfficiency(double returnFanMotorEfficiency);
    void resetReturnFanMotorEfficiency();

    double returnFanMotorinAirStreamFraction() const;
    bool isReturnFanMotorinAirStreamFractionDefaulted() const;
    bool setReturnFanMotorinAirStreamFraction(double returnFanMotorinAirStreamFraction);
    void resetReturnFanMotorinAirStreamFraction();

    std::string returnFanPartLoadPowerCoefficients() const;
    bool isReturnFanPartLoadPowerCoefficientsDefaulted() const;
    bool setReturnFanPartLoadPowerCoefficients(const std::string& returnFanPartLoadPowerCoefficients);
    void resetReturnFanPartLoadPowerCoefficients();

   protected:
    using ImplType = detail::HVACTemplateSystemVAV_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit HVACTemplateSystemVAV(std::shared_ptr<detail::HVACTemplateSystemVAV_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
