/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILCOOLINGWATERTOAIRHEATPUMPVARIABLESPEEDEQUATIONFIT_HPP
#define EPMODEL_COILCOOLINGWATERTOAIRHEATPUMPVARIABLESPEEDEQUATIONFIT_HPP

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
  class CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData;
  class AirflowNetworkDistributionComponentCoil;

  namespace detail {
    class CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl;
  }

  /** \brief Represents a variable-speed water-to-air cooling heat-pump coil.
   *
   * \par EnergyPlus object
   * \epobject{group-heating-and-cooling-coils.html#coilcoolingwatertoairheatpumpvariablespeedequationfit,Coil:Cooling:WaterToAirHeatPump:VariableSpeedEquationFit}
   *
   * \par Important behavior
   * Speed-data wrappers are transient views backed by the coil's EnergyPlus
   * extensible speed rows: attached wrappers write the parent row, while
   * detached wrappers retain their own values until attached. Autosized-value
   * queries do not read SQL sizing results and return no value.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit</code>.
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
  class EPMODEL_API CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit : public WaterToAirComponent
  {
   public:
    explicit CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit(const Model& model);
    CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit(const Model& model, const Curve& partLoadFraction);

    virtual ~CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit() override = default;
    CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit(const CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit& other) = default;
    CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit(CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit&& other) = default;
    CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit& operator=(const CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit&) = default;
    CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit& operator=(CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit&&) = default;

    static IddObjectType iddObjectType();

    Schedule availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);

    int nominalSpeedLevel() const;
    bool setNominalSpeedLevel(int nominalSpeedLevel);

    boost::optional<double> grossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel() const;
    bool setGrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel(double grossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel);
    bool isGrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevelAutosized() const;
    void autosizeGrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel();
    boost::optional<double> autosizedGrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel() const;

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

    double nominalTimeforCondensatetoBeginLeavingtheCoil() const;
    bool setNominalTimeforCondensatetoBeginLeavingtheCoil(double nominalTimeforCondensatetoBeginLeavingtheCoil);

    double initialMoistureEvaporationRateDividedbySteadyStateACLatentCapacity() const;
    bool setInitialMoistureEvaporationRateDividedbySteadyStateACLatentCapacity(
      double initialMoistureEvaporationRateDividedbySteadyStateACLatentCapacity);

    double maximumCyclingRate() const;
    bool setMaximumCyclingRate(double maximumCyclingRate);

    double latentCapacityTimeConstant() const;
    bool setLatentCapacityTimeConstant(double latentCapacityTimeConstant);

    double fanDelayTime() const;
    bool setFanDelayTime(double fanDelayTime);

    bool useHotGasReheat() const;
    bool setUseHotGasReheat(bool useHotGasReheat);

    Curve energyPartLoadFractionCurve() const;
    bool setEnergyPartLoadFractionCurve(const Curve& curve);

    std::vector<CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData> speeds() const;
    bool addSpeed(const CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData& speed);
    void removeSpeed(const CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData& speed);
    void removeAllSpeeds();

    AirflowNetworkDistributionComponentCoil getAirflowNetworkEquivalentDuct(double length, double diameter);
    boost::optional<AirflowNetworkDistributionComponentCoil> airflowNetworkEquivalentDuct() const;

    std::vector<ModelObject> children() const;

   protected:
    using ImplType = detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit(
      std::shared_ptr<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
