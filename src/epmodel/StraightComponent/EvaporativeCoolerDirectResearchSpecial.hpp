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

/** \brief A direct evaporative cooler using the ResearchSpecial performance model.
 *
 * \par EnergyPlus object
 * \epobject{group-evaporative-coolers.html#evaporativecoolerdirectresearchspecial,EvaporativeCooler:Direct:ResearchSpecial}
 *
 * \par Important behavior
 * Outlet-sensor and node relationships are maintained when placed on a supply branch or outdoor-air system. The constructor seeds the required blowdown concentration ratio to 2.0 and uses the always-on discrete schedule.
 *
 * \par OpenStudio Model API
 * The corresponding OpenStudio Model type is <code>openstudio::model::EvaporativeCoolerDirectResearchSpecial</code>.
 *
 * \par Known limitations
 * The canonical schedule-taking constructor and SQL-backed autosized result queries are not available.
 */
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
