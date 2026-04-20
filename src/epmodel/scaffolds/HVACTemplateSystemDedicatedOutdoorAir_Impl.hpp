/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HVACTEMPLATESYSTEMDEDICATEDOUTDOORAIR_IMPL_HPP
#define EPMODEL_HVACTEMPLATESYSTEMDEDICATEDOUTDOORAIR_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API HVACTemplateSystemDedicatedOutdoorAir_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~HVACTemplateSystemDedicatedOutdoorAir_Impl() override = default;

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

      std::vector<std::string> airOutletTypeValues() const;
      std::vector<std::string> supplyFanPlacementValues() const;
      std::vector<std::string> coolingCoilTypeValues() const;
      std::vector<std::string> coolingCoilSetpointControlTypeValues() const;
      std::vector<std::string> heatingCoilTypeValues() const;
      std::vector<std::string> heatingCoilSetpointControlTypeValues() const;
      std::vector<std::string> heatRecoveryTypeValues() const;
      std::vector<std::string> heatRecoveryHeatExchangerTypeValues() const;
      std::vector<std::string> heatRecoveryFrostControlTypeValues() const;
      std::vector<std::string> dehumidificationControlTypeValues() const;
      std::vector<std::string> humidifierTypeValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
