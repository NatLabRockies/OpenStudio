/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_EVAPORATIVECOOLERINDIRECTRESEARCHSPECIAL_HPP
#define EPMODEL_EVAPORATIVECOOLERINDIRECTRESEARCHSPECIAL_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <boost/optional.hpp>

#include <memory>
#include <string>

namespace openstudio {
namespace epmodel {

  class Model;
  class Schedule;
  class Curve;

  namespace detail {
    class EvaporativeCoolerIndirectResearchSpecial_Impl;
  }

  class EPMODEL_API EvaporativeCoolerIndirectResearchSpecial : public StraightComponent
  {
   public:
    explicit EvaporativeCoolerIndirectResearchSpecial(const Model& model);

    virtual ~EvaporativeCoolerIndirectResearchSpecial() override = default;
    EvaporativeCoolerIndirectResearchSpecial(const EvaporativeCoolerIndirectResearchSpecial& other) = default;
    EvaporativeCoolerIndirectResearchSpecial(EvaporativeCoolerIndirectResearchSpecial&& other) = default;
    EvaporativeCoolerIndirectResearchSpecial& operator=(const EvaporativeCoolerIndirectResearchSpecial&) = default;
    EvaporativeCoolerIndirectResearchSpecial& operator=(EvaporativeCoolerIndirectResearchSpecial&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - Status: Near Parity. The canonical indirect-research-special wrapper surface and placement behavior are present, with only the EnergyPlus-only
    //   secondary-fan pair storage gap and autosized-value lookup still documented.
    // - Canonical Counterpart: openstudio::model::EvaporativeCoolerIndirectResearchSpecial.
    // - Implemented Parity: Availability schedule, curve relationships, scalar field accessors, and `addToNode(...)` now follow the canonical
    //   indirect-research evaporative-cooler behavior, including outlet-sensor propagation on supply-side and OA-system placement.
    // - Documented Delta: EnergyPlus persists only `Secondary Air Fan Sizing Specific Power`, so wrappers rebuilt only from bare persisted storage must
    //   reconstruct the legacy `secondaryFanTotalEfficiency()` / `secondaryFanDeltaPressure()` pair from that single value; and
    //   `autosizedRecirculatingWaterPumpPowerConsumption()` / `autosizedSecondaryFanFlowRate()` / `autosizedSecondaryAirFanDesignPower()` /
    //   `autosizedPrimaryDesignAirFlowRate()` still return none because epmodel does not yet resolve autosized sizing results from SQL output.
    // - Field/Storage Mapping: These accessors map directly to EnergyPlus `EvaporativeCooler:Indirect:ResearchSpecial` fields and object-list targets.
    // - Evidence: `src/model/EvaporativeCoolerIndirectResearchSpecial.hpp`, `src/model/EvaporativeCoolerIndirectResearchSpecial.cpp`, and `src/energyplus/ForwardTranslator/ForwardTranslateEvaporativeCoolerIndirectResearchSpecial.cpp`.
    // - Remaining Parity Work: Replace the current reconstructed secondary-fan pair fallback with shared infrastructure that can preserve the canonical
    //   total-efficiency and delta-pressure values across all EnergyPlus-backed rematerialization paths.

    boost::optional<Schedule> availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);
    void resetAvailabilitySchedule();

    double coolerMaximumEffectiveness() const;
    bool setCoolerMaximumEffectiveness(double coolerMaximumEffectiveness);

    boost::optional<double> recirculatingWaterPumpPowerConsumption() const;
    bool isRecirculatingWaterPumpPowerConsumptionAutosized() const;
    bool setRecirculatingWaterPumpPowerConsumption(double recirculatingWaterPumpPowerConsumption);
    void autosizeRecirculatingWaterPumpPowerConsumption();
    boost::optional<double> autosizedRecirculatingWaterPumpPowerConsumption() const;

    boost::optional<double> secondaryFanFlowRate() const;
    bool isSecondaryFanFlowRateAutosized() const;
    bool setSecondaryFanFlowRate(double secondaryFanFlowRate);
    void resetSecondaryFanFlowRate();
    void autosizeSecondaryFanFlowRate();
    boost::optional<double> autosizedSecondaryFanFlowRate() const;

    double secondaryFanTotalEfficiency() const;
    bool setSecondaryFanTotalEfficiency(double secondaryFanTotalEfficiency);

    double secondaryFanDeltaPressure() const;
    bool setSecondaryFanDeltaPressure(double secondaryFanDeltaPressure);

    double dewpointEffectivenessFactor() const;
    bool setDewpointEffectivenessFactor(double dewpointEffectivenessFactor);

    boost::optional<double> driftLossFraction() const;
    bool setDriftLossFraction(double driftLossFraction);
    void resetDriftLossFraction();

    boost::optional<double> blowdownConcentrationRatio() const;
    bool setBlowdownConcentrationRatio(double blowdownConcentrationRatio);
    void resetBlowdownConcentrationRatio();

    boost::optional<Curve> wetbulbEffectivenessFlowRatioModifierCurve() const;
    bool setWetbulbEffectivenessFlowRatioModifierCurve(const Curve& curve);
    void resetWetbulbEffectivenessFlowRatioModifierCurve();

    boost::optional<double> coolerDrybulbDesignEffectiveness() const;
    bool setCoolerDrybulbDesignEffectiveness(double coolerDrybulbDesignEffectiveness);
    void resetCoolerDrybulbDesignEffectiveness();

    boost::optional<Curve> drybulbEffectivenessFlowRatioModifierCurve() const;
    bool setDrybulbEffectivenessFlowRatioModifierCurve(const Curve& curve);
    void resetDrybulbEffectivenessFlowRatioModifierCurve();

    double waterPumpPowerSizingFactor() const;
    bool setWaterPumpPowerSizingFactor(double waterPumpPowerSizingFactor);

    boost::optional<Curve> waterPumpPowerModifierCurve() const;
    bool setWaterPumpPowerModifierCurve(const Curve& curve);
    void resetWaterPumpPowerModifierCurve();

    double secondaryAirFlowScalingFactor() const;
    bool setSecondaryAirFlowScalingFactor(double secondaryAirFlowScalingFactor);

    boost::optional<double> secondaryAirFanDesignPower() const;
    bool isSecondaryAirFanDesignPowerAutosized() const;
    bool setSecondaryAirFanDesignPower(double secondaryAirFanDesignPower);
    void autosizeSecondaryAirFanDesignPower();
    boost::optional<double> autosizedSecondaryAirFanDesignPower() const;

    boost::optional<Curve> secondaryAirFanPowerModifierCurve() const;
    bool setSecondaryAirFanPowerModifierCurve(const Curve& curve);
    void resetSecondaryAirFanPowerModifierCurve();

    boost::optional<double> primaryDesignAirFlowRate() const;
    bool isPrimaryDesignAirFlowRateAutosized() const;
    bool setPrimaryDesignAirFlowRate(double primaryDesignAirFlowRate);
    void resetPrimaryDesignAirFlowRate();
    void autosizePrimaryDesignAirFlowRate();
    boost::optional<double> autosizedPrimaryDesignAirFlowRate() const;

   protected:
    using ImplType = detail::EvaporativeCoolerIndirectResearchSpecial_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit EvaporativeCoolerIndirectResearchSpecial(std::shared_ptr<detail::EvaporativeCoolerIndirectResearchSpecial_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
