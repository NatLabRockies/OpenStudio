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
    // - API: Preserve openstudio::model::EvaporativeCoolerIndirectResearchSpecial scalar accessor names/signatures.
    // - Field Mapping: coolerMaximumEffectiveness -> E+ Cooler Wetbulb Design Effectiveness.
    // - Field Mapping: recirculatingWaterPumpPowerConsumption -> E+ Recirculating Water Pump Design Power.
    // - Field Mapping: secondaryFanFlowRate -> E+ Secondary Air Design Flow Rate.
    // - Field Mapping: legacy secondaryFanTotalEfficiency and secondaryFanDeltaPressure APIs both delegate to
    //   E+ Secondary Air Fan Sizing Specific Power to preserve counterpart signatures while this scalar-only pass
    //   omits non-scalar parity behavior.
    // - Field Mapping: coolerDrybulbDesignEffectiveness, waterPumpPowerSizingFactor, secondaryAirFlowScalingFactor,
    //   secondaryAirFanDesignPower, primaryDesignAirFlowRate, dewpointEffectivenessFactor, driftLossFraction, and
    //   blowdownConcentrationRatio map directly to current E+ scalar fields.
    // - Field Mapping: availability schedule, node-name, relief-air node, storage tank, and curve-name fields are
    //   relationship-like and excluded from this scalar-only scaffold.
    // - TODO(parity): Revisit secondary-fan dual-API mapping if richer non-scalar parity storage is introduced.

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

    boost::optional<double> coolerDrybulbDesignEffectiveness() const;
    bool setCoolerDrybulbDesignEffectiveness(double coolerDrybulbDesignEffectiveness);
    void resetCoolerDrybulbDesignEffectiveness();

    double waterPumpPowerSizingFactor() const;
    bool setWaterPumpPowerSizingFactor(double waterPumpPowerSizingFactor);

    double secondaryAirFlowScalingFactor() const;
    bool setSecondaryAirFlowScalingFactor(double secondaryAirFlowScalingFactor);

    boost::optional<double> secondaryAirFanDesignPower() const;
    bool isSecondaryAirFanDesignPowerAutosized() const;
    bool setSecondaryAirFanDesignPower(double secondaryAirFanDesignPower);
    void autosizeSecondaryAirFanDesignPower();
    boost::optional<double> autosizedSecondaryAirFanDesignPower() const;

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
