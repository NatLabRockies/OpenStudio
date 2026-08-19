/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILHEATINGWATERTOAIRHEATPUMPVARIABLESPEEDEQUATIONFIT_HPP
#define EPMODEL_COILHEATINGWATERTOAIRHEATPUMPVARIABLESPEEDEQUATIONFIT_HPP

#include "EPModelAPI.hpp"
#include "WaterToAirComponent.hpp"

#include <utilities/core/Deprecated.hpp>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class Schedule;
  class Curve;
  class CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData;
  class AirflowNetworkDistributionComponentCoil;

  namespace detail {
    class CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl;
  }

  /** \brief Represents a variable-speed water-to-air heating heat-pump coil.
   *
   * \par EnergyPlus object
   * \epobject{group-heating-and-cooling-coils.html#coilheatingwatertoairheatpumpvariablespeedequationfit,Coil:Heating:WaterToAirHeatPump:VariableSpeedEquationFit}
   *
   * \par Important behavior
   * Speed-data wrappers are transient views backed by the coil's EnergyPlus
   * extensible speed rows: attached wrappers write the parent row, while
   * detached wrappers retain their own values until attached. Autosized-value
   * queries do not read SQL sizing results and return no value.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit</code>.
   *
   * - <b>Changed:</b> The airflow-network equivalent-duct methods use
   *   <code>AirflowNetworkDistributionComponentCoil</code> instead of
   *   Model's <code>AirflowNetworkEquivalentDuct</code>.
   * - <b>Changed:</b> Autosized-value queries remain API-compatible but return
   *   no value because EPModel does not read SQL sizing results.
   *
   * \par Known limitations
   * Speed rows are persisted on the parent coil; they are not independent
   * EnergyPlus objects that can be saved separately.
   */
  class EPMODEL_API CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit : public WaterToAirComponent
  {
   public:
    explicit CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit(const Model& model);
    CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit(const Model& model, const Curve& partLoadFraction);

    virtual ~CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit() override = default;
    CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit(const CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit& other) = default;
    CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit(CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit&& other) = default;
    CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit& operator=(const CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit&) = default;
    CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit& operator=(CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit&&) = default;

    static IddObjectType iddObjectType();

    Schedule availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);

    int nominalSpeedLevel() const;
    bool setNominalSpeedLevel(int nominalSpeedLevel);

    boost::optional<double> ratedHeatingCapacityAtSelectedNominalSpeedLevel() const;
    bool setRatedHeatingCapacityAtSelectedNominalSpeedLevel(double ratedHeatingCapacityAtSelectedNominalSpeedLevel);
    bool isRatedHeatingCapacityAtSelectedNominalSpeedLevelAutosized() const;
    void autosizeRatedHeatingCapacityAtSelectedNominalSpeedLevel();
    boost::optional<double> autosizedRatedHeatingCapacityAtSelectedNominalSpeedLevel() const;

    boost::optional<double> ratedAirFlowRateAtSelectedNominalSpeedLevel() const;
    bool setRatedAirFlowRateAtSelectedNominalSpeedLevel(double ratedAirFlowRateAtSelectedNominalSpeedLevel);
    bool isRatedAirFlowRateAtSelectedNominalSpeedLevelAutosized() const;
    void autosizeRatedAirFlowRateAtSelectedNominalSpeedLevel();
    boost::optional<double> autosizedRatedAirFlowRateAtSelectedNominalSpeedLevel() const;

    boost::optional<double> ratedWaterFlowRateAtSelectedNominalSpeedLevel() const;
    bool setRatedWaterFlowRateAtSelectedNominalSpeedLevel(double ratedWaterFlowRateAtSelectedNominalSpeedLevel);
    bool isRatedWaterFlowRateAtSelectedNominalSpeedLevelAutosized() const;
    void autosizeRatedWaterFlowRateAtSelectedNominalSpeedLevel();
    boost::optional<double> autosizedRatedWaterFlowRateAtSelectedNominalSpeedLevel() const;

    Curve energyPartLoadFractionCurve() const;
    bool setEnergyPartLoadFractionCurve(const Curve& curve);

    std::vector<CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData> speeds() const;
    bool addSpeed(const CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData& speed);
    void removeSpeed(const CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData& speed);
    void removeAllSpeeds();

    AirflowNetworkDistributionComponentCoil getAirflowNetworkEquivalentDuct(double length, double diameter);
    boost::optional<AirflowNetworkDistributionComponentCoil> airflowNetworkEquivalentDuct() const;

    std::vector<ModelObject> children() const;

   protected:
    using ImplType = detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit(
      std::shared_ptr<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
