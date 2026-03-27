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
    // - Status: Scalar Parity. The canonical direct-research evaporative-cooler scalar surface is present, while schedule, node, and curve helpers remain out of scope.
    // - Canonical Counterpart: openstudio::model::EvaporativeCoolerDirectResearchSpecial.
    // - Implemented Parity: The preserved scalar API covers the cooler effectiveness, pump power, flow, drift/blowdown, sizing, and operating-temperature fields with matching default/autosize behavior.
    // - Documented Delta: Availability-schedule, node-link, sensor-node, and curve-name helpers remain intentionally excluded from this scalar pass.
    // - Field/Storage Mapping: These accessors map directly to EnergyPlus `EvaporativeCooler:Direct:ResearchSpecial` scalar fields used by the forward translator.
    // - Evidence: `src/model/EvaporativeCoolerDirectResearchSpecial.hpp` and `src/energyplus/ForwardTranslator/ForwardTranslateEvaporativeCoolerDirectResearchSpecial.cpp`.
    // - Remaining Parity Work: Add the omitted relationship helpers without changing the preserved scalar signatures.
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

    double driftLossFraction() const;
    bool setDriftLossFraction(double value);

    double blowdownConcentrationRatio() const;
    bool setBlowdownConcentrationRatio(double value);

    double waterPumpPowerSizingFactor() const;
    bool setWaterPumpPowerSizingFactor(double waterPumpPowerSizingFactor);

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
