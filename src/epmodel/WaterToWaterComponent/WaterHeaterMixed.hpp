/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_WATERHEATERMIXED_HPP
#define EPMODEL_WATERHEATERMIXED_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <boost/optional.hpp>

#include <memory>
#include <string>
#include <vector>

namespace openstudio {

class FuelType;

namespace epmodel {

  class Model;

  namespace detail {

    class WaterHeaterMixed_Impl;

  }

  class EPMODEL_API WaterHeaterMixed : public ModelObject
  {
   public:
    explicit WaterHeaterMixed(const Model& model);

    virtual ~WaterHeaterMixed() override = default;
    WaterHeaterMixed(const WaterHeaterMixed& other) = default;
    WaterHeaterMixed(WaterHeaterMixed&& other) = default;
    WaterHeaterMixed& operator=(const WaterHeaterMixed&) = default;
    WaterHeaterMixed& operator=(WaterHeaterMixed&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> heaterControlTypeValues();
    static std::vector<std::string> heaterFuelTypeValues();
    static std::vector<std::string> offCycleParasiticFuelTypeValues();
    static std::vector<std::string> onCycleParasiticFuelTypeValues();
    static std::vector<std::string> ambientTemperatureIndicatorValues();
    static std::vector<std::string> sourceSideFlowControlModeValues();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model::WaterHeaterMixed scalar accessor names/signatures for counterpart parity.
    // - Field Mapping: Simple scalar methods map directly to the EnergyPlus WaterHeater:Mixed fields per ForwardTranslateWaterHeaterMixed.
    // - Field Mapping: Relationship-like schedule, curve, node, and plant references (Setpoint Temperature Schedule, PartLoadFactorCurve, ambient node/zone/schedule fields, node/link names) are excluded from this scalar-only scaffold.
    // - ForwardTranslator evidence: ForwardTranslateWaterHeaterMixed.cpp confirms these scalar mappings and the ThermalsZone->Zone token drift for AmbientTemperatureIndicator.
    // - TODO(parity): Add missing relationship/object references (schedules, nodes, PlantLoop wiring) in a later parity pass.

    // Tank volume
    boost::optional<double> tankVolume() const;
    bool isTankVolumeDefaulted() const;
    bool isTankVolumeAutosized() const;
    bool setTankVolume(double tankVolume);
    void resetTankVolume();
    void autosizeTankVolume();
    boost::optional<double> autosizedTankVolume() const;

    // Deadband difference
    double deadbandTemperatureDifference() const;
    bool isDeadbandTemperatureDifferenceDefaulted() const;
    bool setDeadbandTemperatureDifference(double deadbandTemperatureDifference);
    void resetDeadbandTemperatureDifference();

    // Maximum temperature limit
    boost::optional<double> maximumTemperatureLimit() const;
    bool setMaximumTemperatureLimit(double maximumTemperatureLimit);
    void resetMaximumTemperatureLimit();

    // Heater control type
    std::string heaterControlType() const;
    bool isHeaterControlTypeDefaulted() const;
    bool setHeaterControlType(const std::string& heaterControlType);
    void resetHeaterControlType();

    // Heater maximum capacity
    boost::optional<double> heaterMaximumCapacity() const;
    bool isHeaterMaximumCapacityAutosized() const;
    bool setHeaterMaximumCapacity(double heaterMaximumCapacity);
    void resetHeaterMaximumCapacity();
    void autosizeHeaterMaximumCapacity();
    boost::optional<double> autosizedHeaterMaximumCapacity() const;

    // Heater minimum capacity
    boost::optional<double> heaterMinimumCapacity() const;
    bool setHeaterMinimumCapacity(double heaterMinimumCapacity);
    void resetHeaterMinimumCapacity();

    // Heater ignition minimum flow
    double heaterIgnitionMinimumFlowRate() const;
    bool isHeaterIgnitionMinimumFlowRateDefaulted() const;
    bool setHeaterIgnitionMinimumFlowRate(double heaterIgnitionMinimumFlowRate);
    void resetHeaterIgnitionMinimumFlowRate();

    // Heater ignition delay
    double heaterIgnitionDelay() const;
    bool isHeaterIgnitionDelayDefaulted() const;
    bool setHeaterIgnitionDelay(double heaterIgnitionDelay);
    void resetHeaterIgnitionDelay();

    // Heater fuel type
    std::string heaterFuelType() const;
    bool setHeaterFuelType(const FuelType& heaterFuelType);
    bool setHeaterFuelType(const std::string& heaterFuelType);

    // Heater thermal efficiency
    boost::optional<double> heaterThermalEfficiency() const;
    bool setHeaterThermalEfficiency(double heaterThermalEfficiency);
    void resetHeaterThermalEfficiency();

    // Off-cycle parasitic fuel consumption
    double offCycleParasiticFuelConsumptionRate() const;
    bool isOffCycleParasiticFuelConsumptionRateDefaulted() const;
    bool setOffCycleParasiticFuelConsumptionRate(double offCycleParasiticFuelConsumptionRate);
    void resetOffCycleParasiticFuelConsumptionRate();

    // Off-cycle parasitic fuel type
    boost::optional<std::string> offCycleParasiticFuelType() const;
    bool setOffCycleParasiticFuelType(const FuelType& offCycleParasiticFuelType);
    bool setOffCycleParasiticFuelType(const std::string& offCycleParasiticFuelType);
    void resetOffCycleParasiticFuelType();

    // Off-cycle parasitic heat fraction
    double offCycleParasiticHeatFractiontoTank() const;
    bool isOffCycleParasiticHeatFractiontoTankDefaulted() const;
    bool setOffCycleParasiticHeatFractiontoTank(double offCycleParasiticHeatFractiontoTank);
    void resetOffCycleParasiticHeatFractiontoTank();

    // On-cycle parasitic fuel consumption
    double onCycleParasiticFuelConsumptionRate() const;
    bool isOnCycleParasiticFuelConsumptionRateDefaulted() const;
    bool setOnCycleParasiticFuelConsumptionRate(double onCycleParasiticFuelConsumptionRate);
    void resetOnCycleParasiticFuelConsumptionRate();

    // On-cycle parasitic fuel type
    boost::optional<std::string> onCycleParasiticFuelType() const;
    bool setOnCycleParasiticFuelType(const FuelType& onCycleParasiticFuelType);
    bool setOnCycleParasiticFuelType(const std::string& onCycleParasiticFuelType);
    void resetOnCycleParasiticFuelType();

    // On-cycle parasitic heat fraction
    double onCycleParasiticHeatFractiontoTank() const;
    bool isOnCycleParasiticHeatFractiontoTankDefaulted() const;
    bool setOnCycleParasiticHeatFractiontoTank(double onCycleParasiticHeatFractiontoTank);
    void resetOnCycleParasiticHeatFractiontoTank();

    // Ambient temperature indicator
    std::string ambientTemperatureIndicator() const;
    bool setAmbientTemperatureIndicator(const std::string& ambientTemperatureIndicator);

    // Off-cycle loss coefficient
    boost::optional<double> offCycleLossCoefficienttoAmbientTemperature() const;
    bool setOffCycleLossCoefficienttoAmbientTemperature(double offCycleLossCoefficienttoAmbientTemperature);
    void resetOffCycleLossCoefficienttoAmbientTemperature();

    // Off-cycle loss fraction to thermal zone
    double offCycleLossFractiontoThermalZone() const;
    bool isOffCycleLossFractiontoThermalZoneDefaulted() const;
    bool setOffCycleLossFractiontoThermalZone(double offCycleLossFractiontoThermalZone);
    void resetOffCycleLossFractiontoThermalZone();

    // On-cycle loss coefficient
    boost::optional<double> onCycleLossCoefficienttoAmbientTemperature() const;
    bool setOnCycleLossCoefficienttoAmbientTemperature(double onCycleLossCoefficienttoAmbientTemperature);
    void resetOnCycleLossCoefficienttoAmbientTemperature();

    // On-cycle loss fraction to thermal zone
    double onCycleLossFractiontoThermalZone() const;
    bool isOnCycleLossFractiontoThermalZoneDefaulted() const;
    bool setOnCycleLossFractiontoThermalZone(double onCycleLossFractiontoThermalZone);
    void resetOnCycleLossFractiontoThermalZone();

    // Peak use flow rate
    boost::optional<double> peakUseFlowRate() const;
    bool setPeakUseFlowRate(double peakUseFlowRate);
    void resetPeakUseFlowRate();

    // Use side effectiveness
    double useSideEffectiveness() const;
    bool isUseSideEffectivenessDefaulted() const;
    bool setUseSideEffectiveness(double useSideEffectiveness);
    void resetUseSideEffectiveness();

    // Source side effectiveness
    double sourceSideEffectiveness() const;
    bool isSourceSideEffectivenessDefaulted() const;
    bool setSourceSideEffectiveness(double sourceSideEffectiveness);
    void resetSourceSideEffectiveness();

    // Use side design flow rate
    boost::optional<double> useSideDesignFlowRate() const;
    bool isUseSideDesignFlowRateDefaulted() const;
    bool isUseSideDesignFlowRateAutosized() const;
    bool setUseSideDesignFlowRate(double useSideDesignFlowRate);
    void resetUseSideDesignFlowRate();
    void autosizeUseSideDesignFlowRate();
    boost::optional<double> autosizedUseSideDesignFlowRate() const;

    // Source side design flow rate
    boost::optional<double> sourceSideDesignFlowRate() const;
    bool isSourceSideDesignFlowRateDefaulted() const;
    bool isSourceSideDesignFlowRateAutosized() const;
    bool setSourceSideDesignFlowRate(double sourceSideDesignFlowRate);
    void resetSourceSideDesignFlowRate();
    void autosizeSourceSideDesignFlowRate();
    boost::optional<double> autosizedSourceSideDesignFlowRate() const;

    // Indirect water heating recovery time
    double indirectWaterHeatingRecoveryTime() const;
    bool isIndirectWaterHeatingRecoveryTimeDefaulted() const;
    bool setIndirectWaterHeatingRecoveryTime(double indirectWaterHeatingRecoveryTime);
    void resetIndirectWaterHeatingRecoveryTime();

    // Source side flow control mode
    std::string sourceSideFlowControlMode() const;
    bool setSourceSideFlowControlMode(const std::string& sourceSideFlowControlMode);

    // End-use subcategory
    std::string endUseSubcategory() const;
    bool setEndUseSubcategory(const std::string& endUseSubcategory);

   protected:
    using ImplType = detail::WaterHeaterMixed_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit WaterHeaterMixed(std::shared_ptr<detail::WaterHeaterMixed_Impl> impl);
  };

  using OptionalWaterHeaterMixed = boost::optional<WaterHeaterMixed>;

}  // namespace epmodel
}  // namespace openstudio

#endif
