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
    boost::optional<double> tankVolume() const;
    bool isTankVolumeDefaulted() const;
    bool isTankVolumeAutosized() const;

    double deadbandTemperatureDifference() const;
    bool isDeadbandTemperatureDifferenceDefaulted() const;

    boost::optional<double> maximumTemperatureLimit() const;

    std::string heaterControlType() const;
    bool isHeaterControlTypeDefaulted() const;

    boost::optional<double> heaterMaximumCapacity() const;
    bool isHeaterMaximumCapacityAutosized() const;

    boost::optional<double> heaterMinimumCapacity() const;

    double heaterIgnitionMinimumFlowRate() const;
    bool isHeaterIgnitionMinimumFlowRateDefaulted() const;

    double heaterIgnitionDelay() const;
    bool isHeaterIgnitionDelayDefaulted() const;

    std::string heaterFuelType() const;

    boost::optional<double> heaterThermalEfficiency() const;

    double offCycleParasiticFuelConsumptionRate() const;
    bool isOffCycleParasiticFuelConsumptionRateDefaulted() const;

    boost::optional<std::string> offCycleParasiticFuelType() const;

    double offCycleParasiticHeatFractiontoTank() const;
    bool isOffCycleParasiticHeatFractiontoTankDefaulted() const;

    double onCycleParasiticFuelConsumptionRate() const;
    bool isOnCycleParasiticFuelConsumptionRateDefaulted() const;

    boost::optional<std::string> onCycleParasiticFuelType() const;

    double onCycleParasiticHeatFractiontoTank() const;
    bool isOnCycleParasiticHeatFractiontoTankDefaulted() const;

    std::string ambientTemperatureIndicator() const;

    boost::optional<double> offCycleLossCoefficienttoAmbientTemperature() const;

    double offCycleLossFractiontoThermalZone() const;
    bool isOffCycleLossFractiontoThermalZoneDefaulted() const;

    boost::optional<double> onCycleLossCoefficienttoAmbientTemperature() const;

    double onCycleLossFractiontoThermalZone() const;
    bool isOnCycleLossFractiontoThermalZoneDefaulted() const;

    boost::optional<double> peakUseFlowRate() const;

    double useSideEffectiveness() const;
    bool isUseSideEffectivenessDefaulted() const;

    double sourceSideEffectiveness() const;
    bool isSourceSideEffectivenessDefaulted() const;

    boost::optional<double> useSideDesignFlowRate() const;
    bool isUseSideDesignFlowRateDefaulted() const;
    bool isUseSideDesignFlowRateAutosized() const;

    boost::optional<double> sourceSideDesignFlowRate() const;
    bool isSourceSideDesignFlowRateDefaulted() const;
    bool isSourceSideDesignFlowRateAutosized() const;

    double indirectWaterHeatingRecoveryTime() const;
    bool isIndirectWaterHeatingRecoveryTimeDefaulted() const;

    std::string sourceSideFlowControlMode() const;

    std::string endUseSubcategory() const;

    boost::optional<double> autosizedTankVolume() const;
    boost::optional<double> autosizedHeaterMaximumCapacity() const;
    boost::optional<double> autosizedUseSideDesignFlowRate() const;
    boost::optional<double> autosizedSourceSideDesignFlowRate() const;

    bool setTankVolume(double tankVolume);
    void resetTankVolume();
    void autosizeTankVolume();

    bool setDeadbandTemperatureDifference(double deadbandTemperatureDifference);
    void resetDeadbandTemperatureDifference();

    bool setMaximumTemperatureLimit(double maximumTemperatureLimit);
    void resetMaximumTemperatureLimit();

    bool setHeaterControlType(const std::string& heaterControlType);
    void resetHeaterControlType();

    bool setHeaterMaximumCapacity(double heaterMaximumCapacity);
    void resetHeaterMaximumCapacity();
    void autosizeHeaterMaximumCapacity();

    bool setHeaterMinimumCapacity(double heaterMinimumCapacity);
    void resetHeaterMinimumCapacity();

    bool setHeaterIgnitionMinimumFlowRate(double heaterIgnitionMinimumFlowRate);
    void resetHeaterIgnitionMinimumFlowRate();

    bool setHeaterIgnitionDelay(double heaterIgnitionDelay);
    void resetHeaterIgnitionDelay();

    bool setHeaterFuelType(const FuelType& heaterFuelType);
    bool setHeaterFuelType(const std::string& heaterFuelType);

    bool setHeaterThermalEfficiency(double heaterThermalEfficiency);
    void resetHeaterThermalEfficiency();

    bool setOffCycleParasiticFuelConsumptionRate(double offCycleParasiticFuelConsumptionRate);
    void resetOffCycleParasiticFuelConsumptionRate();

    bool setOffCycleParasiticFuelType(const FuelType& offCycleParasiticFuelType);
    bool setOffCycleParasiticFuelType(const std::string& offCycleParasiticFuelType);
    void resetOffCycleParasiticFuelType();

    bool setOffCycleParasiticHeatFractiontoTank(double offCycleParasiticHeatFractiontoTank);
    void resetOffCycleParasiticHeatFractiontoTank();

    bool setOnCycleParasiticFuelConsumptionRate(double onCycleParasiticFuelConsumptionRate);
    void resetOnCycleParasiticFuelConsumptionRate();

    bool setOnCycleParasiticFuelType(const FuelType& onCycleParasiticFuelType);
    bool setOnCycleParasiticFuelType(const std::string& onCycleParasiticFuelType);
    void resetOnCycleParasiticFuelType();

    bool setOnCycleParasiticHeatFractiontoTank(double onCycleParasiticHeatFractiontoTank);
    void resetOnCycleParasiticHeatFractiontoTank();

    bool setAmbientTemperatureIndicator(const std::string& ambientTemperatureIndicator);

    bool setOffCycleLossCoefficienttoAmbientTemperature(double offCycleLossCoefficienttoAmbientTemperature);
    void resetOffCycleLossCoefficienttoAmbientTemperature();

    bool setOffCycleLossFractiontoThermalZone(double offCycleLossFractiontoThermalZone);
    void resetOffCycleLossFractiontoThermalZone();

    bool setOnCycleLossCoefficienttoAmbientTemperature(double onCycleLossCoefficienttoAmbientTemperature);
    void resetOnCycleLossCoefficienttoAmbientTemperature();

    bool setOnCycleLossFractiontoThermalZone(double onCycleLossFractiontoThermalZone);
    void resetOnCycleLossFractiontoThermalZone();

    bool setPeakUseFlowRate(double peakUseFlowRate);
    void resetPeakUseFlowRate();

    bool setUseSideEffectiveness(double useSideEffectiveness);
    void resetUseSideEffectiveness();

    bool setSourceSideEffectiveness(double sourceSideEffectiveness);
    void resetSourceSideEffectiveness();

    bool setUseSideDesignFlowRate(double useSideDesignFlowRate);
    void resetUseSideDesignFlowRate();
    void autosizeUseSideDesignFlowRate();

    bool setSourceSideDesignFlowRate(double sourceSideDesignFlowRate);
    void resetSourceSideDesignFlowRate();
    void autosizeSourceSideDesignFlowRate();

    bool setIndirectWaterHeatingRecoveryTime(double indirectWaterHeatingRecoveryTime);
    void resetIndirectWaterHeatingRecoveryTime();

    bool setSourceSideFlowControlMode(const std::string& sourceSideFlowControlMode);

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
