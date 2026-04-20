/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HVACTEMPLATESYSTEMUNITARYSYSTEM_HPP
#define EPMODEL_HVACTEMPLATESYSTEMUNITARYSYSTEM_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class HVACTemplateSystemUnitarySystem_Impl;
  }

  class EPMODEL_API HVACTemplateSystemUnitarySystem : public ModelObject
  {
   public:
    explicit HVACTemplateSystemUnitarySystem(const Model& model);

    virtual ~HVACTemplateSystemUnitarySystem() override = default;
    HVACTemplateSystemUnitarySystem(const HVACTemplateSystemUnitarySystem& other) = default;
    HVACTemplateSystemUnitarySystem(HVACTemplateSystemUnitarySystem&& other) = default;
    HVACTemplateSystemUnitarySystem& operator=(const HVACTemplateSystemUnitarySystem&) = default;
    HVACTemplateSystemUnitarySystem& operator=(HVACTemplateSystemUnitarySystem&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> controlTypeValues();
    static std::vector<std::string> supplyFanPlacementValues();
    static std::vector<std::string> coolingCoilTypeValues();
    static std::vector<std::string> heatingCoilTypeValues();
    static std::vector<std::string> heatPumpDefrostStrategyValues();
    static std::vector<std::string> heatPumpDefrostControlValues();
    static std::vector<std::string> supplementalHeatingorReheatCoilTypeValues();
    static std::vector<std::string> economizerTypeValues();
    static std::vector<std::string> economizerLockoutValues();
    static std::vector<std::string> heatRecoveryTypeValues();
    static std::vector<std::string> heatRecoveryHeatExchangerTypeValues();
    static std::vector<std::string> heatRecoveryFrostControlTypeValues();
    static std::vector<std::string> dehumidificationControlTypeValues();
    static std::vector<std::string> humidifierTypeValues();
    static std::vector<std::string> sizingOptionValues();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: Scalar APIs map directly to HVACTemplate:System:UnitarySystem non-name, non-link scalar fields.
    // - Field Mapping: Schedule/zone/plenum object-list fields are relationship-like and excluded from scalar accessors.
    // - TODO(parity): Add relationship/object-link APIs in a later parity pass.

    std::string controlType() const;
    bool setControlType(const std::string& controlType);
    void resetControlType();
    bool isControlTypeDefaulted() const;

    boost::optional<double> coolingSupplyAirFlowRate() const;
    bool setCoolingSupplyAirFlowRate(double coolingSupplyAirFlowRate);
    void resetCoolingSupplyAirFlowRate();
    bool isCoolingSupplyAirFlowRateDefaulted() const;
    bool isCoolingSupplyAirFlowRateAutosized() const;
    void autosizeCoolingSupplyAirFlowRate();

    boost::optional<double> heatingSupplyAirFlowRate() const;
    bool setHeatingSupplyAirFlowRate(double heatingSupplyAirFlowRate);
    void resetHeatingSupplyAirFlowRate();
    bool isHeatingSupplyAirFlowRateDefaulted() const;
    bool isHeatingSupplyAirFlowRateAutosized() const;
    void autosizeHeatingSupplyAirFlowRate();

    boost::optional<double> noLoadSupplyAirFlowRate() const;
    bool setNoLoadSupplyAirFlowRate(double noLoadSupplyAirFlowRate);
    void resetNoLoadSupplyAirFlowRate();
    bool isNoLoadSupplyAirFlowRateDefaulted() const;
    bool isNoLoadSupplyAirFlowRateAutosized() const;
    void autosizeNoLoadSupplyAirFlowRate();

    std::string supplyFanPlacement() const;
    bool setSupplyFanPlacement(const std::string& supplyFanPlacement);
    void resetSupplyFanPlacement();
    bool isSupplyFanPlacementDefaulted() const;

    double supplyFanTotalEfficiency() const;
    bool setSupplyFanTotalEfficiency(double supplyFanTotalEfficiency);
    void resetSupplyFanTotalEfficiency();
    bool isSupplyFanTotalEfficiencyDefaulted() const;

    double supplyFanDeltaPressure() const;
    bool setSupplyFanDeltaPressure(double supplyFanDeltaPressure);
    void resetSupplyFanDeltaPressure();
    bool isSupplyFanDeltaPressureDefaulted() const;

    double supplyFanMotorEfficiency() const;
    bool setSupplyFanMotorEfficiency(double supplyFanMotorEfficiency);
    void resetSupplyFanMotorEfficiency();
    bool isSupplyFanMotorEfficiencyDefaulted() const;

    double supplyFanMotorinAirStreamFraction() const;
    bool setSupplyFanMotorinAirStreamFraction(double supplyFanMotorinAirStreamFraction);
    void resetSupplyFanMotorinAirStreamFraction();
    bool isSupplyFanMotorinAirStreamFractionDefaulted() const;

    std::string coolingCoilType() const;
    bool setCoolingCoilType(const std::string& coolingCoilType);
    void resetCoolingCoilType();
    bool isCoolingCoilTypeDefaulted() const;

    int numberofSpeedsforCooling() const;
    bool setNumberofSpeedsforCooling(int numberofSpeedsforCooling);
    void resetNumberofSpeedsforCooling();
    bool isNumberofSpeedsforCoolingDefaulted() const;

    double coolingDesignSupplyAirTemperature() const;
    bool setCoolingDesignSupplyAirTemperature(double coolingDesignSupplyAirTemperature);
    void resetCoolingDesignSupplyAirTemperature();
    bool isCoolingDesignSupplyAirTemperatureDefaulted() const;

    boost::optional<double> dXCoolingCoilGrossRatedTotalCapacity() const;
    bool setDXCoolingCoilGrossRatedTotalCapacity(double dXCoolingCoilGrossRatedTotalCapacity);
    void resetDXCoolingCoilGrossRatedTotalCapacity();
    bool isDXCoolingCoilGrossRatedTotalCapacityDefaulted() const;
    bool isDXCoolingCoilGrossRatedTotalCapacityAutosized() const;
    void autosizeDXCoolingCoilGrossRatedTotalCapacity();

    boost::optional<double> dXCoolingCoilGrossRatedSensibleHeatRatio() const;
    bool setDXCoolingCoilGrossRatedSensibleHeatRatio(double dXCoolingCoilGrossRatedSensibleHeatRatio);
    void resetDXCoolingCoilGrossRatedSensibleHeatRatio();
    bool isDXCoolingCoilGrossRatedSensibleHeatRatioDefaulted() const;
    bool isDXCoolingCoilGrossRatedSensibleHeatRatioAutosized() const;
    void autosizeDXCoolingCoilGrossRatedSensibleHeatRatio();

    double dXCoolingCoilGrossRatedCOP() const;
    bool setDXCoolingCoilGrossRatedCOP(double dXCoolingCoilGrossRatedCOP);
    void resetDXCoolingCoilGrossRatedCOP();
    bool isDXCoolingCoilGrossRatedCOPDefaulted() const;

    std::string heatingCoilType() const;
    bool setHeatingCoilType(const std::string& heatingCoilType);
    void resetHeatingCoilType();
    bool isHeatingCoilTypeDefaulted() const;

    int numberofSpeedsorStagesforHeating() const;
    bool setNumberofSpeedsorStagesforHeating(int numberofSpeedsorStagesforHeating);
    void resetNumberofSpeedsorStagesforHeating();
    bool isNumberofSpeedsorStagesforHeatingDefaulted() const;

    double heatingDesignSupplyAirTemperature() const;
    bool setHeatingDesignSupplyAirTemperature(double heatingDesignSupplyAirTemperature);
    void resetHeatingDesignSupplyAirTemperature();
    bool isHeatingDesignSupplyAirTemperatureDefaulted() const;

    boost::optional<double> heatingCoilGrossRatedCapacity() const;
    bool setHeatingCoilGrossRatedCapacity(double heatingCoilGrossRatedCapacity);
    void resetHeatingCoilGrossRatedCapacity();
    bool isHeatingCoilGrossRatedCapacityDefaulted() const;
    bool isHeatingCoilGrossRatedCapacityAutosized() const;
    void autosizeHeatingCoilGrossRatedCapacity();

    double gasHeatingCoilEfficiency() const;
    bool setGasHeatingCoilEfficiency(double gasHeatingCoilEfficiency);
    void resetGasHeatingCoilEfficiency();
    bool isGasHeatingCoilEfficiencyDefaulted() const;

    double gasHeatingCoilParasiticElectricLoad() const;
    bool setGasHeatingCoilParasiticElectricLoad(double gasHeatingCoilParasiticElectricLoad);
    void resetGasHeatingCoilParasiticElectricLoad();
    bool isGasHeatingCoilParasiticElectricLoadDefaulted() const;

    double heatPumpHeatingCoilGrossRatedCOP() const;
    bool setHeatPumpHeatingCoilGrossRatedCOP(double heatPumpHeatingCoilGrossRatedCOP);
    void resetHeatPumpHeatingCoilGrossRatedCOP();
    bool isHeatPumpHeatingCoilGrossRatedCOPDefaulted() const;

    double heatPumpHeatingMinimumOutdoorDryBulbTemperature() const;
    bool setHeatPumpHeatingMinimumOutdoorDryBulbTemperature(double heatPumpHeatingMinimumOutdoorDryBulbTemperature);
    void resetHeatPumpHeatingMinimumOutdoorDryBulbTemperature();
    bool isHeatPumpHeatingMinimumOutdoorDryBulbTemperatureDefaulted() const;

    double heatPumpDefrostMaximumOutdoorDryBulbTemperature() const;
    bool setHeatPumpDefrostMaximumOutdoorDryBulbTemperature(double heatPumpDefrostMaximumOutdoorDryBulbTemperature);
    void resetHeatPumpDefrostMaximumOutdoorDryBulbTemperature();
    bool isHeatPumpDefrostMaximumOutdoorDryBulbTemperatureDefaulted() const;

    std::string heatPumpDefrostStrategy() const;
    bool setHeatPumpDefrostStrategy(const std::string& heatPumpDefrostStrategy);
    void resetHeatPumpDefrostStrategy();
    bool isHeatPumpDefrostStrategyDefaulted() const;

    std::string heatPumpDefrostControl() const;
    bool setHeatPumpDefrostControl(const std::string& heatPumpDefrostControl);
    void resetHeatPumpDefrostControl();
    bool isHeatPumpDefrostControlDefaulted() const;

    double heatPumpDefrostTimePeriodFraction() const;
    bool setHeatPumpDefrostTimePeriodFraction(double heatPumpDefrostTimePeriodFraction);
    void resetHeatPumpDefrostTimePeriodFraction();
    bool isHeatPumpDefrostTimePeriodFractionDefaulted() const;

    std::string supplementalHeatingorReheatCoilType() const;
    bool setSupplementalHeatingorReheatCoilType(const std::string& supplementalHeatingorReheatCoilType);
    void resetSupplementalHeatingorReheatCoilType();
    bool isSupplementalHeatingorReheatCoilTypeDefaulted() const;

    boost::optional<double> supplementalHeatingorReheatCoilCapacity() const;
    bool setSupplementalHeatingorReheatCoilCapacity(double supplementalHeatingorReheatCoilCapacity);
    void resetSupplementalHeatingorReheatCoilCapacity();
    bool isSupplementalHeatingorReheatCoilCapacityDefaulted() const;
    bool isSupplementalHeatingorReheatCoilCapacityAutosized() const;
    void autosizeSupplementalHeatingorReheatCoilCapacity();

    double supplementalHeatingorReheatCoilMaximumOutdoorDryBulbTemperature() const;
    bool setSupplementalHeatingorReheatCoilMaximumOutdoorDryBulbTemperature(double supplementalHeatingorReheatCoilMaximumOutdoorDryBulbTemperature);
    void resetSupplementalHeatingorReheatCoilMaximumOutdoorDryBulbTemperature();
    bool isSupplementalHeatingorReheatCoilMaximumOutdoorDryBulbTemperatureDefaulted() const;

    double supplementalGasHeatingorReheatCoilEfficiency() const;
    bool setSupplementalGasHeatingorReheatCoilEfficiency(double supplementalGasHeatingorReheatCoilEfficiency);
    void resetSupplementalGasHeatingorReheatCoilEfficiency();
    bool isSupplementalGasHeatingorReheatCoilEfficiencyDefaulted() const;

    double supplementalGasHeatingorReheatCoilParasiticElectricLoad() const;
    bool setSupplementalGasHeatingorReheatCoilParasiticElectricLoad(double supplementalGasHeatingorReheatCoilParasiticElectricLoad);
    void resetSupplementalGasHeatingorReheatCoilParasiticElectricLoad();
    bool isSupplementalGasHeatingorReheatCoilParasiticElectricLoadDefaulted() const;

    boost::optional<double> maximumOutdoorAirFlowRate() const;
    bool setMaximumOutdoorAirFlowRate(double maximumOutdoorAirFlowRate);
    void resetMaximumOutdoorAirFlowRate();
    bool isMaximumOutdoorAirFlowRateDefaulted() const;
    bool isMaximumOutdoorAirFlowRateAutosized() const;
    void autosizeMaximumOutdoorAirFlowRate();

    boost::optional<double> minimumOutdoorAirFlowRate() const;
    bool setMinimumOutdoorAirFlowRate(double minimumOutdoorAirFlowRate);
    void resetMinimumOutdoorAirFlowRate();
    bool isMinimumOutdoorAirFlowRateDefaulted() const;
    bool isMinimumOutdoorAirFlowRateAutosized() const;
    void autosizeMinimumOutdoorAirFlowRate();

    std::string economizerType() const;
    bool setEconomizerType(const std::string& economizerType);
    void resetEconomizerType();
    bool isEconomizerTypeDefaulted() const;

    std::string economizerLockout() const;
    bool setEconomizerLockout(const std::string& economizerLockout);
    void resetEconomizerLockout();
    bool isEconomizerLockoutDefaulted() const;

    boost::optional<double> economizerMaximumLimitDryBulbTemperature() const;
    bool setEconomizerMaximumLimitDryBulbTemperature(double economizerMaximumLimitDryBulbTemperature);
    void resetEconomizerMaximumLimitDryBulbTemperature();
    bool isEconomizerMaximumLimitDryBulbTemperatureDefaulted() const;

    boost::optional<double> economizerMaximumLimitEnthalpy() const;
    bool setEconomizerMaximumLimitEnthalpy(double economizerMaximumLimitEnthalpy);
    void resetEconomizerMaximumLimitEnthalpy();
    bool isEconomizerMaximumLimitEnthalpyDefaulted() const;

    boost::optional<double> economizerMaximumLimitDewpointTemperature() const;
    bool setEconomizerMaximumLimitDewpointTemperature(double economizerMaximumLimitDewpointTemperature);
    void resetEconomizerMaximumLimitDewpointTemperature();
    bool isEconomizerMaximumLimitDewpointTemperatureDefaulted() const;

    boost::optional<double> economizerMinimumLimitDryBulbTemperature() const;
    bool setEconomizerMinimumLimitDryBulbTemperature(double economizerMinimumLimitDryBulbTemperature);
    void resetEconomizerMinimumLimitDryBulbTemperature();
    bool isEconomizerMinimumLimitDryBulbTemperatureDefaulted() const;

    std::string heatRecoveryType() const;
    bool setHeatRecoveryType(const std::string& heatRecoveryType);
    void resetHeatRecoveryType();
    bool isHeatRecoveryTypeDefaulted() const;

    double sensibleHeatRecoveryEffectiveness() const;
    bool setSensibleHeatRecoveryEffectiveness(double sensibleHeatRecoveryEffectiveness);
    void resetSensibleHeatRecoveryEffectiveness();
    bool isSensibleHeatRecoveryEffectivenessDefaulted() const;

    double latentHeatRecoveryEffectiveness() const;
    bool setLatentHeatRecoveryEffectiveness(double latentHeatRecoveryEffectiveness);
    void resetLatentHeatRecoveryEffectiveness();
    bool isLatentHeatRecoveryEffectivenessDefaulted() const;

    std::string heatRecoveryHeatExchangerType() const;
    bool setHeatRecoveryHeatExchangerType(const std::string& heatRecoveryHeatExchangerType);
    void resetHeatRecoveryHeatExchangerType();
    bool isHeatRecoveryHeatExchangerTypeDefaulted() const;

    std::string heatRecoveryFrostControlType() const;
    bool setHeatRecoveryFrostControlType(const std::string& heatRecoveryFrostControlType);
    void resetHeatRecoveryFrostControlType();
    bool isHeatRecoveryFrostControlTypeDefaulted() const;

    std::string dehumidificationControlType() const;
    bool setDehumidificationControlType(const std::string& dehumidificationControlType);
    void resetDehumidificationControlType();
    bool isDehumidificationControlTypeDefaulted() const;

    double dehumidificationRelativeHumiditySetpoint() const;
    bool setDehumidificationRelativeHumiditySetpoint(double dehumidificationRelativeHumiditySetpoint);
    void resetDehumidificationRelativeHumiditySetpoint();
    bool isDehumidificationRelativeHumiditySetpointDefaulted() const;

    std::string humidifierType() const;
    bool setHumidifierType(const std::string& humidifierType);
    void resetHumidifierType();
    bool isHumidifierTypeDefaulted() const;

    double humidifierRatedCapacity() const;
    bool setHumidifierRatedCapacity(double humidifierRatedCapacity);
    void resetHumidifierRatedCapacity();
    bool isHumidifierRatedCapacityDefaulted() const;

    boost::optional<double> humidifierRatedElectricPower() const;
    bool setHumidifierRatedElectricPower(double humidifierRatedElectricPower);
    void resetHumidifierRatedElectricPower();
    bool isHumidifierRatedElectricPowerDefaulted() const;
    bool isHumidifierRatedElectricPowerAutosized() const;
    void autosizeHumidifierRatedElectricPower();

    double humidifierRelativeHumiditySetpoint() const;
    bool setHumidifierRelativeHumiditySetpoint(double humidifierRelativeHumiditySetpoint);
    void resetHumidifierRelativeHumiditySetpoint();
    bool isHumidifierRelativeHumiditySetpointDefaulted() const;

    std::string sizingOption() const;
    bool setSizingOption(const std::string& sizingOption);
    void resetSizingOption();
    bool isSizingOptionDefaulted() const;

    bool returnFan() const;
    bool setReturnFan(bool returnFan);
    void resetReturnFan();
    bool isReturnFanDefaulted() const;

    double returnFanTotalEfficiency() const;
    bool setReturnFanTotalEfficiency(double returnFanTotalEfficiency);
    void resetReturnFanTotalEfficiency();
    bool isReturnFanTotalEfficiencyDefaulted() const;

    double returnFanDeltaPressure() const;
    bool setReturnFanDeltaPressure(double returnFanDeltaPressure);
    void resetReturnFanDeltaPressure();
    bool isReturnFanDeltaPressureDefaulted() const;

    double returnFanMotorEfficiency() const;
    bool setReturnFanMotorEfficiency(double returnFanMotorEfficiency);
    void resetReturnFanMotorEfficiency();
    bool isReturnFanMotorEfficiencyDefaulted() const;

    double returnFanMotorinAirStreamFraction() const;
    bool setReturnFanMotorinAirStreamFraction(double returnFanMotorinAirStreamFraction);
    void resetReturnFanMotorinAirStreamFraction();
    bool isReturnFanMotorinAirStreamFractionDefaulted() const;

   protected:
    using ImplType = detail::HVACTemplateSystemUnitarySystem_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit HVACTemplateSystemUnitarySystem(std::shared_ptr<detail::HVACTemplateSystemUnitarySystem_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
