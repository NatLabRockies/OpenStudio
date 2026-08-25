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

/** \brief An indirect evaporative cooler using the ResearchSpecial performance model.
 *
 * \par EnergyPlus object
 * \epobject{group-evaporative-coolers.html#evaporativecoolerindirectresearchspecial,EvaporativeCooler:Indirect:ResearchSpecial}
 *
 * \par Important behavior
 * EnergyPlus-only secondary-air inlet/outlet nodes and the outdoor-air declaration are maintained with the cooler.
 *
 * \par OpenStudio Model API
 * The corresponding OpenStudio Model type is <code>openstudio::model::EvaporativeCoolerIndirectResearchSpecial</code>.
 *
 * \par Known limitations
 * Secondary-fan efficiency and pressure are reconstructed from EnergyPlus specific power on reload; SQL-backed autosized result queries are unavailable.
 */
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
