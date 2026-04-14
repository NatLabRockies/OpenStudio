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

  namespace detail {
    class CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl;
  }

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

    // Schema Alignment Notes:
    // - Status: Parity with documented deltas.
    // - Canonical Counterpart: openstudio::model::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit.
    // - Implemented Parity: The canonical availability schedule, part-load curve, scalar speed-level fields, autosized query helpers, and
    //   speed-data child APIs are exposed here. epmodel preserves the canonical speed-data children as transient ParentObject wrappers:
    //   detached transient wrappers hold their own OpenStudio-style fields until added to a parent coil, while attached transient wrappers
    //   read and write a specific EnergyPlus extensible speed row on the parent object.
    // - Documented Delta: `AirflowNetworkEquivalentDuct` parity is still deferred. High-level child traversal therefore returns the energy
    //   part-load curve and speed-data children, but not the canonical AirflowNetwork companion. The autosized query methods are also
    //   API-preserving stubs for now: they return `none` until epmodel grows the SQL-backed autosized result lookup used by the canonical
    //   model layer.
    // - Field/Storage Mapping: Scalar fields map directly to the corresponding EnergyPlus
    //   `Coil:Cooling:WaterToAirHeatPump:VariableSpeedEquationFit` fields. The canonical speed-data children are backed by the parent's real
    //   EnergyPlus extensible speed rows, not by separate persisted EnergyPlus objects.
    // - Evidence: `src/model/CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit.hpp`, `src/model/CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateCoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit.cpp`, and `src/epmodel/test/CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_GTest.cpp`.
    // - Remaining Parity Work: Add `AirflowNetworkEquivalentDuct` once that family is built out in epmodel.
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
