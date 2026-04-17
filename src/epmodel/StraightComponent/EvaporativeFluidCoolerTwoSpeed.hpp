/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_EVAPORATIVEFLUIDCOOLERTWOSPEED_HPP
#define EPMODEL_EVAPORATIVEFLUIDCOOLERTWOSPEED_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <boost/optional.hpp>

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class EvaporativeFluidCoolerTwoSpeed_Impl;
  }

  class EPMODEL_API EvaporativeFluidCoolerTwoSpeed : public StraightComponent
  {
   public:
    explicit EvaporativeFluidCoolerTwoSpeed(const Model& model);

    virtual ~EvaporativeFluidCoolerTwoSpeed() override = default;
    EvaporativeFluidCoolerTwoSpeed(const EvaporativeFluidCoolerTwoSpeed& other) = default;
    EvaporativeFluidCoolerTwoSpeed(EvaporativeFluidCoolerTwoSpeed&& other) = default;
    EvaporativeFluidCoolerTwoSpeed& operator=(const EvaporativeFluidCoolerTwoSpeed&) = default;
    EvaporativeFluidCoolerTwoSpeed& operator=(EvaporativeFluidCoolerTwoSpeed&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> performanceInputMethodValues();
    static std::vector<std::string> evaporationLossModeValues();
    static std::vector<std::string> blowdownCalculationModeValues();

    // Schema Alignment Notes:
    // - Status: Parity with documented deltas. The canonical scalar surface and plant-supply placement rule are present, while the outdoor-air and
    //   blowdown schedule relationship helpers plus the legacy storage-tank placeholder remain out of scope.
    // - Canonical Counterpart: openstudio::model::EvaporativeFluidCoolerTwoSpeed.
    // - Implemented Parity: The preserved API matches the canonical high/low speed flow, fan power, sizing-factor, spray-water, performance, and
    //   capacity accessors with matching autosize/default behavior, and inherited `addToNode(...)` now follows the canonical plant-supply-only
    //   insertion contract.
    // - Documented Delta: The public wrapper still omits `outdoorAirInletNodeName()`, `blowdownMakeupWaterUsageSchedule()`, their mutators, and the
    //   legacy storage-tank helper.
    // - Field/Storage Mapping: These accessors map directly to EnergyPlus `EvaporativeFluidCooler:TwoSpeed` scalar fields used by the forward translator.
    // - Evidence: `src/model/EvaporativeFluidCoolerTwoSpeed.hpp`, `src/model/EvaporativeFluidCoolerTwoSpeed.cpp`, and
    //   `src/energyplus/ForwardTranslator/ForwardTranslateEvaporativeFluidCoolerTwoSpeed.cpp`.
    // - Remaining Parity Work: Add the omitted relationship helpers without changing the preserved scalar signatures.

    // High fan speed air flow rate
    boost::optional<double> highFanSpeedAirFlowRate() const;
    bool isHighFanSpeedAirFlowRateAutosized() const;
    bool setHighFanSpeedAirFlowRate(double highFanSpeedAirFlowRate);
    void autosizeHighFanSpeedAirFlowRate();
    boost::optional<double> autosizedHighFanSpeedAirFlowRate() const;

    // High fan speed fan power
    boost::optional<double> highFanSpeedFanPower() const;
    bool isHighFanSpeedFanPowerAutosized() const;
    bool setHighFanSpeedFanPower(double highFanSpeedFanPower);
    void autosizeHighFanSpeedFanPower();
    boost::optional<double> autosizedHighFanSpeedFanPower() const;

    // Low fan speed air flow rate
    boost::optional<double> lowFanSpeedAirFlowRate() const;
    bool isLowFanSpeedAirFlowRateAutosized() const;
    bool setLowFanSpeedAirFlowRate(double lowFanSpeedAirFlowRate);
    void autosizeLowFanSpeedAirFlowRate();
    boost::optional<double> autosizedLowFanSpeedAirFlowRate() const;

    // Low fan speed air flow rate sizing factor
    double lowFanSpeedAirFlowRateSizingFactor() const;
    bool setLowFanSpeedAirFlowRateSizingFactor(double lowFanSpeedAirFlowRateSizingFactor);

    // Low fan speed fan power
    boost::optional<double> lowFanSpeedFanPower() const;
    bool isLowFanSpeedFanPowerAutosized() const;
    bool setLowFanSpeedFanPower(double lowFanSpeedFanPower);
    void autosizeLowFanSpeedFanPower();
    boost::optional<double> autosizedLowFanSpeedFanPower() const;

    // Low fan speed fan power sizing factor
    double lowFanSpeedFanPowerSizingFactor() const;
    bool setLowFanSpeedFanPowerSizingFactor(double lowFanSpeedFanPowerSizingFactor);

    // Design spray water flow rate
    double designSprayWaterFlowRate() const;
    bool setDesignSprayWaterFlowRate(double designSprayWaterFlowRate);

    // Performance input method
    std::string performanceInputMethod() const;
    bool setPerformanceInputMethod(const std::string& performanceInputMethod);

    // Heat rejection capacity / nominal capacity sizing ratio
    double heatRejectionCapacityandNominalCapacitySizingRatio() const;
    bool setHeatRejectionCapacityandNominalCapacitySizingRatio(double heatRejectionCapacityandNominalCapacitySizingRatio);

    // High speed standard design capacity
    boost::optional<double> highSpeedStandardDesignCapacity() const;
    bool setHighSpeedStandardDesignCapacity(double highSpeedStandardDesignCapacity);
    void resetHighSpeedStandardDesignCapacity();

    // Low speed standard design capacity
    boost::optional<double> lowSpeedStandardDesignCapacity() const;
    bool isLowSpeedStandardDesignCapacityAutosized() const;
    bool setLowSpeedStandardDesignCapacity(double lowSpeedStandardDesignCapacity);
    void resetLowSpeedStandardDesignCapacity();
    void autosizeLowSpeedStandardDesignCapacity();
    boost::optional<double> autosizedLowSpeedStandardDesignCapacity() const;

    // Low speed standard capacity sizing factor
    double lowSpeedStandardCapacitySizingFactor() const;
    bool setLowSpeedStandardCapacitySizingFactor(double lowSpeedStandardCapacitySizingFactor);

    // High fan speed U-factor times area value
    boost::optional<double> highFanSpeedUfactorTimesAreaValue() const;
    bool isHighFanSpeedUfactorTimesAreaValueAutosized() const;
    bool setHighFanSpeedUfactorTimesAreaValue(double highFanSpeedUfactorTimesAreaValue);
    void resetHighFanSpeedUfactorTimesAreaValue();
    void autosizeHighFanSpeedUfactorTimesAreaValue();
    boost::optional<double> autosizedHighFanSpeedUfactorTimesAreaValue() const;

    // Low fan speed U-factor times area value
    boost::optional<double> lowFanSpeedUfactorTimesAreaValue() const;
    bool isLowFanSpeedUfactorTimesAreaValueAutosized() const;
    bool setLowFanSpeedUfactorTimesAreaValue(double lowFanSpeedUfactorTimesAreaValue);
    void resetLowFanSpeedUfactorTimesAreaValue();
    void autosizeLowFanSpeedUfactorTimesAreaValue();
    boost::optional<double> autosizedLowFanSpeedUfactorTimesAreaValue() const;

    // Low fan speed U-factor times area sizing factor
    double lowFanSpeedUFactorTimesAreaSizingFactor() const;
    bool setLowFanSpeedUFactorTimesAreaSizingFactor(double lowFanSpeedUFactorTimesAreaSizingFactor);

    // Design water flow rate
    boost::optional<double> designWaterFlowRate() const;
    bool isDesignWaterFlowRateAutosized() const;
    bool setDesignWaterFlowRate(double designWaterFlowRate);
    void resetDesignWaterFlowRate();
    void autosizeDesignWaterFlowRate();
    boost::optional<double> autosizedDesignWaterFlowRate() const;

    // High speed user-specified design capacity
    boost::optional<double> highSpeedUserSpecifiedDesignCapacity() const;
    bool setHighSpeedUserSpecifiedDesignCapacity(double highSpeedUserSpecifiedDesignCapacity);
    void resetHighSpeedUserSpecifiedDesignCapacity();

    // Low speed user-specified design capacity
    boost::optional<double> lowSpeedUserSpecifiedDesignCapacity() const;
    bool isLowSpeedUserSpecifiedDesignCapacityAutosized() const;
    bool setLowSpeedUserSpecifiedDesignCapacity(double lowSpeedUserSpecifiedDesignCapacity);
    void resetLowSpeedUserSpecifiedDesignCapacity();
    void autosizeLowSpeedUserSpecifiedDesignCapacity();
    boost::optional<double> autosizedLowSpeedUserSpecifiedDesignCapacity() const;

    // Low speed user-specified design capacity sizing factor
    double lowSpeedUserSpecifiedDesignCapacitySizingFactor() const;
    bool setLowSpeedUserSpecifiedDesignCapacitySizingFactor(double lowSpeedUserSpecifiedDesignCapacitySizingFactor);

    // Design entering water temperature
    boost::optional<double> designEnteringWaterTemperature() const;
    bool isDesignEnteringWaterTemperatureAutosized() const;
    bool setDesignEnteringWaterTemperature(double designEnteringWaterTemperature);
    void autosizeDesignEnteringWaterTemperature();
    boost::optional<double> autosizedDesignEnteringWaterTemperature() const;

    // Design entering air temperature
    double designEnteringAirTemperature() const;
    bool setDesignEnteringAirTemperature(double designEnteringAirTemperature);

    // Design entering air wetbulb temperature
    double designEnteringAirWetbulbTemperature() const;
    bool setDesignEnteringAirWetbulbTemperature(double designEnteringAirWetbulbTemperature);

    // High speed sizing factor
    double highSpeedSizingFactor() const;
    bool setHighSpeedSizingFactor(double highSpeedSizingFactor);

    // Evaporation loss mode
    std::string evaporationLossMode() const;
    bool setEvaporationLossMode(const std::string& evaporationLossMode);

    // Evaporation loss factor
    boost::optional<double> evaporationLossFactor() const;
    bool setEvaporationLossFactor(double evaporationLossFactor);
    void resetEvaporationLossFactor();

    // Drift loss percent
    double driftLossPercent() const;
    bool setDriftLossPercent(double driftLossPercent);

    // Blowdown calculation mode
    std::string blowdownCalculationMode() const;
    bool setBlowdownCalculationMode(const std::string& blowdownCalculationMode);

    // Blowdown concentration ratio
    double blowdownConcentrationRatio() const;
    bool setBlowdownConcentrationRatio(double blowdownConcentrationRatio);

   protected:
    using ImplType = detail::EvaporativeFluidCoolerTwoSpeed_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit EvaporativeFluidCoolerTwoSpeed(std::shared_ptr<detail::EvaporativeFluidCoolerTwoSpeed_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
