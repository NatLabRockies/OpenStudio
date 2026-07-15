/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HVACTEMPLATESYSTEMDEDICATEDOUTDOORAIR_HPP
#define EPMODEL_HVACTEMPLATESYSTEMDEDICATEDOUTDOORAIR_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class HVACTemplateSystemDedicatedOutdoorAir_Impl;
  }

  class EPMODEL_API HVACTemplateSystemDedicatedOutdoorAir : public ModelObject
  {
   public:
    explicit HVACTemplateSystemDedicatedOutdoorAir(const Model& model);

    virtual ~HVACTemplateSystemDedicatedOutdoorAir() override = default;
    HVACTemplateSystemDedicatedOutdoorAir(const HVACTemplateSystemDedicatedOutdoorAir& other) = default;
    HVACTemplateSystemDedicatedOutdoorAir(HVACTemplateSystemDedicatedOutdoorAir&& other) = default;
    HVACTemplateSystemDedicatedOutdoorAir& operator=(const HVACTemplateSystemDedicatedOutdoorAir&) = default;
    HVACTemplateSystemDedicatedOutdoorAir& operator=(HVACTemplateSystemDedicatedOutdoorAir&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> airOutletTypeValues();
    static std::vector<std::string> supplyFanPlacementValues();
    static std::vector<std::string> coolingCoilTypeValues();
    static std::vector<std::string> coolingCoilSetpointControlTypeValues();
    static std::vector<std::string> heatingCoilTypeValues();
    static std::vector<std::string> heatingCoilSetpointControlTypeValues();
    static std::vector<std::string> heatRecoveryTypeValues();
    static std::vector<std::string> heatRecoveryHeatExchangerTypeValues();
    static std::vector<std::string> heatRecoveryFrostControlTypeValues();
    static std::vector<std::string> dehumidificationControlTypeValues();
    static std::vector<std::string> humidifierTypeValues();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: Scalar APIs map directly to HVACTemplate:System:DedicatedOutdoorAir non-name, non-link scalar fields.
    // - Field Mapping: Schedule name fields are relationship-like object-list links and excluded from scalar accessors.
    // - TODO(parity): Add relationship/object-link APIs in a later parity pass.

    std::string airOutletType() const;
    bool isAirOutletTypeDefaulted() const;
    bool setAirOutletType(const std::string& airOutletType);
    void resetAirOutletType();

    boost::optional<double> supplyFanFlowRate() const;
    bool isSupplyFanFlowRateDefaulted() const;
    bool isSupplyFanFlowRateAutosized() const;
    bool setSupplyFanFlowRate(double supplyFanFlowRate);
    void resetSupplyFanFlowRate();
    void autosizeSupplyFanFlowRate();

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

    std::string supplyFanPlacement() const;
    bool isSupplyFanPlacementDefaulted() const;
    bool setSupplyFanPlacement(const std::string& supplyFanPlacement);
    void resetSupplyFanPlacement();

    std::string coolingCoilType() const;
    bool isCoolingCoilTypeDefaulted() const;
    bool setCoolingCoilType(const std::string& coolingCoilType);
    void resetCoolingCoilType();

    std::string coolingCoilSetpointControlType() const;
    bool isCoolingCoilSetpointControlTypeDefaulted() const;
    bool setCoolingCoilSetpointControlType(const std::string& coolingCoilSetpointControlType);
    void resetCoolingCoilSetpointControlType();

    double coolingCoilDesignSetpoint() const;
    bool isCoolingCoilDesignSetpointDefaulted() const;
    bool setCoolingCoilDesignSetpoint(double coolingCoilDesignSetpoint);
    void resetCoolingCoilDesignSetpoint();

    double coolingCoilSetpointatOutdoorDryBulbLow() const;
    bool isCoolingCoilSetpointatOutdoorDryBulbLowDefaulted() const;
    bool setCoolingCoilSetpointatOutdoorDryBulbLow(double coolingCoilSetpointatOutdoorDryBulbLow);
    void resetCoolingCoilSetpointatOutdoorDryBulbLow();

    double coolingCoilResetOutdoorDryBulbLow() const;
    bool isCoolingCoilResetOutdoorDryBulbLowDefaulted() const;
    bool setCoolingCoilResetOutdoorDryBulbLow(double coolingCoilResetOutdoorDryBulbLow);
    void resetCoolingCoilResetOutdoorDryBulbLow();

    double coolingCoilSetpointatOutdoorDryBulbHigh() const;
    bool isCoolingCoilSetpointatOutdoorDryBulbHighDefaulted() const;
    bool setCoolingCoilSetpointatOutdoorDryBulbHigh(double coolingCoilSetpointatOutdoorDryBulbHigh);
    void resetCoolingCoilSetpointatOutdoorDryBulbHigh();

    double coolingCoilResetOutdoorDryBulbHigh() const;
    bool isCoolingCoilResetOutdoorDryBulbHighDefaulted() const;
    bool setCoolingCoilResetOutdoorDryBulbHigh(double coolingCoilResetOutdoorDryBulbHigh);
    void resetCoolingCoilResetOutdoorDryBulbHigh();

    boost::optional<double> dXCoolingCoilGrossRatedTotalCapacity() const;
    bool isDXCoolingCoilGrossRatedTotalCapacityDefaulted() const;
    bool isDXCoolingCoilGrossRatedTotalCapacityAutosized() const;
    bool setDXCoolingCoilGrossRatedTotalCapacity(double dXCoolingCoilGrossRatedTotalCapacity);
    void resetDXCoolingCoilGrossRatedTotalCapacity();
    void autosizeDXCoolingCoilGrossRatedTotalCapacity();

    boost::optional<double> dXCoolingCoilGrossRatedSensibleHeatRatio() const;
    bool isDXCoolingCoilGrossRatedSensibleHeatRatioDefaulted() const;
    bool isDXCoolingCoilGrossRatedSensibleHeatRatioAutosized() const;
    bool setDXCoolingCoilGrossRatedSensibleHeatRatio(double dXCoolingCoilGrossRatedSensibleHeatRatio);
    void resetDXCoolingCoilGrossRatedSensibleHeatRatio();
    void autosizeDXCoolingCoilGrossRatedSensibleHeatRatio();

    double dXCoolingCoilGrossRatedCOP() const;
    bool isDXCoolingCoilGrossRatedCOPDefaulted() const;
    bool setDXCoolingCoilGrossRatedCOP(double dXCoolingCoilGrossRatedCOP);
    void resetDXCoolingCoilGrossRatedCOP();

    std::string heatingCoilType() const;
    bool isHeatingCoilTypeDefaulted() const;
    bool setHeatingCoilType(const std::string& heatingCoilType);
    void resetHeatingCoilType();

    std::string heatingCoilSetpointControlType() const;
    bool isHeatingCoilSetpointControlTypeDefaulted() const;
    bool setHeatingCoilSetpointControlType(const std::string& heatingCoilSetpointControlType);
    void resetHeatingCoilSetpointControlType();

    double heatingCoilDesignSetpoint() const;
    bool isHeatingCoilDesignSetpointDefaulted() const;
    bool setHeatingCoilDesignSetpoint(double heatingCoilDesignSetpoint);
    void resetHeatingCoilDesignSetpoint();

    double heatingCoilSetpointatOutdoorDryBulbLow() const;
    bool isHeatingCoilSetpointatOutdoorDryBulbLowDefaulted() const;
    bool setHeatingCoilSetpointatOutdoorDryBulbLow(double heatingCoilSetpointatOutdoorDryBulbLow);
    void resetHeatingCoilSetpointatOutdoorDryBulbLow();

    double heatingCoilResetOutdoorDryBulbLow() const;
    bool isHeatingCoilResetOutdoorDryBulbLowDefaulted() const;
    bool setHeatingCoilResetOutdoorDryBulbLow(double heatingCoilResetOutdoorDryBulbLow);
    void resetHeatingCoilResetOutdoorDryBulbLow();

    double heatingCoilSetpointatOutdoorDryBulbHigh() const;
    bool isHeatingCoilSetpointatOutdoorDryBulbHighDefaulted() const;
    bool setHeatingCoilSetpointatOutdoorDryBulbHigh(double heatingCoilSetpointatOutdoorDryBulbHigh);
    void resetHeatingCoilSetpointatOutdoorDryBulbHigh();

    double heatingCoilResetOutdoorDryBulbHigh() const;
    bool isHeatingCoilResetOutdoorDryBulbHighDefaulted() const;
    bool setHeatingCoilResetOutdoorDryBulbHigh(double heatingCoilResetOutdoorDryBulbHigh);
    void resetHeatingCoilResetOutdoorDryBulbHigh();

    double gasHeatingCoilEfficiency() const;
    bool isGasHeatingCoilEfficiencyDefaulted() const;
    bool setGasHeatingCoilEfficiency(double gasHeatingCoilEfficiency);
    void resetGasHeatingCoilEfficiency();

    double gasHeatingCoilParasiticElectricLoad() const;
    bool isGasHeatingCoilParasiticElectricLoadDefaulted() const;
    bool setGasHeatingCoilParasiticElectricLoad(double gasHeatingCoilParasiticElectricLoad);
    void resetGasHeatingCoilParasiticElectricLoad();

    std::string heatRecoveryType() const;
    bool isHeatRecoveryTypeDefaulted() const;
    bool setHeatRecoveryType(const std::string& heatRecoveryType);
    void resetHeatRecoveryType();

    double heatRecoverySensibleEffectiveness() const;
    bool isHeatRecoverySensibleEffectivenessDefaulted() const;
    bool setHeatRecoverySensibleEffectiveness(double heatRecoverySensibleEffectiveness);
    void resetHeatRecoverySensibleEffectiveness();

    double heatRecoveryLatentEffectiveness() const;
    bool isHeatRecoveryLatentEffectivenessDefaulted() const;
    bool setHeatRecoveryLatentEffectiveness(double heatRecoveryLatentEffectiveness);
    void resetHeatRecoveryLatentEffectiveness();

    std::string heatRecoveryHeatExchangerType() const;
    bool isHeatRecoveryHeatExchangerTypeDefaulted() const;
    bool setHeatRecoveryHeatExchangerType(const std::string& heatRecoveryHeatExchangerType);
    void resetHeatRecoveryHeatExchangerType();

    std::string heatRecoveryFrostControlType() const;
    bool isHeatRecoveryFrostControlTypeDefaulted() const;
    bool setHeatRecoveryFrostControlType(const std::string& heatRecoveryFrostControlType);
    void resetHeatRecoveryFrostControlType();

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

    double humidifierConstantSetpoint() const;
    bool isHumidifierConstantSetpointDefaulted() const;
    bool setHumidifierConstantSetpoint(double humidifierConstantSetpoint);
    void resetHumidifierConstantSetpoint();

   protected:
    using ImplType = detail::HVACTemplateSystemDedicatedOutdoorAir_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit HVACTemplateSystemDedicatedOutdoorAir(std::shared_ptr<detail::HVACTemplateSystemDedicatedOutdoorAir_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
