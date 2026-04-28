/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_EVAPORATIVECOOLERDIRECTRESEARCHSPECIAL_HPP
#define EPMODEL_EVAPORATIVECOOLERDIRECTRESEARCHSPECIAL_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;
  class Schedule;
  class Node;
  class Curve;

  namespace detail {
    class EvaporativeCoolerDirectResearchSpecial_Impl;
  }

  class EPMODEL_API EvaporativeCoolerDirectResearchSpecial : public StraightComponent
  {
   public:
    explicit EvaporativeCoolerDirectResearchSpecial(const Model& model);

    virtual ~EvaporativeCoolerDirectResearchSpecial() override = default;
    EvaporativeCoolerDirectResearchSpecial(const EvaporativeCoolerDirectResearchSpecial& other) = default;
    EvaporativeCoolerDirectResearchSpecial(EvaporativeCoolerDirectResearchSpecial&& other) = default;
    EvaporativeCoolerDirectResearchSpecial& operator=(const EvaporativeCoolerDirectResearchSpecial&) = default;
    EvaporativeCoolerDirectResearchSpecial& operator=(EvaporativeCoolerDirectResearchSpecial&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - Status: Parity with documented deltas. The canonical direct-research evaporative-cooler wrapper surface and placement behavior are present, with
    //   only epmodel-wide autosized-value lookup still deferred.
    // - Canonical Counterpart: openstudio::model::EvaporativeCoolerDirectResearchSpecial.
    // - Implemented Parity: Availability schedule, sensor-node/curve relationships, scalar field accessors, and `addToNode(...)` now follow the
    //   canonical direct-research evaporative-cooler behavior, including outlet-sensor propagation on supply-side and OA-system placement.
    // - Documented Delta: The constructor seeds `blowdownConcentrationRatio()` to the EnergyPlus minimum of `2.0` because the persisted schema does not
    //   accept the canonical model-side `0.0` placeholder; epmodel still exposes only the single-argument constructor and therefore defaults the required
    //   availability schedule to `Model::alwaysOnDiscreteSchedule()` instead of accepting the canonical `(Model, Schedule&)` constructor; and
    //   `autosizedRecirculatingWaterPumpPowerConsumption()` / `autosizedPrimaryAirDesignFlowRate()` still return none because epmodel does not yet resolve
    //   autosized sizing results from SQL output.
    // - Field/Storage Mapping: These accessors map directly to EnergyPlus `EvaporativeCooler:Direct:ResearchSpecial` fields and node/object-list targets.
    // - Evidence: `src/model/EvaporativeCoolerDirectResearchSpecial.hpp`, `src/model/EvaporativeCoolerDirectResearchSpecial.cpp`, and
    //   `src/energyplus/ForwardTranslator/ForwardTranslateEvaporativeCoolerDirectResearchSpecial.cpp`.
    // - Remaining Parity Work: Wire these autosized accessors to epmodel sizing-result lookup once that shared infrastructure exists.
    Schedule availabilitySchedule() const;
    Schedule availableSchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);
    bool setAvailableSchedule(Schedule& schedule);

    double coolerDesignEffectiveness() const;
    double coolerEffectiveness() const;
    bool setCoolerDesignEffectiveness(double value);
    bool setCoolerEffectiveness(double value);

    boost::optional<double> recirculatingWaterPumpPowerConsumption() const;
    bool setRecirculatingWaterPumpPowerConsumption(double value);
    void autosizeRecirculatingWaterPumpPowerConsumption();
    bool isRecirculatingWaterPumpPowerConsumptionAutosized() const;
    boost::optional<double> autosizedRecirculatingWaterPumpPowerConsumption() const;

    boost::optional<double> primaryAirDesignFlowRate() const;
    bool setPrimaryAirDesignFlowRate(double value);
    void autosizePrimaryAirDesignFlowRate();
    bool isPrimaryAirDesignFlowRateAutosized() const;
    boost::optional<double> autosizedPrimaryAirDesignFlowRate() const;

    boost::optional<Node> sensorNode() const;
    bool setSensorNode(const Node& node);

    double driftLossFraction() const;
    bool setDriftLossFraction(double value);

    double blowdownConcentrationRatio() const;
    bool setBlowdownConcentrationRatio(double value);

    boost::optional<Curve> effectivenessFlowRatioModifierCurve() const;
    bool setEffectivenessFlowRatioModifierCurve(const Curve& curve);
    void resetEffectivenessFlowRatioModifierCurve();

    double waterPumpPowerSizingFactor() const;
    bool setWaterPumpPowerSizingFactor(double waterPumpPowerSizingFactor);

    boost::optional<Curve> waterPumpPowerModifierCurve() const;
    bool setWaterPumpPowerModifierCurve(const Curve& curve);
    void resetWaterPumpPowerModifierCurve();

    double evaporativeOperationMinimumDrybulbTemperature() const;
    bool setEvaporativeOperationMinimumDrybulbTemperature(double evaporativeOperationMinimumDrybulbTemperature);

    double evaporativeOperationMaximumLimitWetbulbTemperature() const;
    bool setEvaporativeOperationMaximumLimitWetbulbTemperature(double evaporativeOperationMaximumLimitWetbulbTemperature);

    double evaporativeOperationMaximumLimitDrybulbTemperature() const;
    bool setEvaporativeOperationMaximumLimitDrybulbTemperature(double evaporativeOperationMaximumLimitDrybulbTemperature);

   protected:
    using ImplType = detail::EvaporativeCoolerDirectResearchSpecial_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit EvaporativeCoolerDirectResearchSpecial(std::shared_ptr<detail::EvaporativeCoolerDirectResearchSpecial_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
