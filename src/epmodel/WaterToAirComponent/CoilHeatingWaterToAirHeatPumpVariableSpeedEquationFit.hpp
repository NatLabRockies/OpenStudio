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

  // Schema Alignment Notes:
  // - Status: Parity with documented deltas.
  // - Canonical Counterpart: openstudio::model::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit.
  // - Implemented Parity: The canonical availability schedule, part-load curve, scalar speed-level fields, and speed-data child APIs are
  //   exposed here. epmodel preserves the canonical speed-data children as transient ParentObject wrappers: detached transient wrappers
  //   hold their own OpenStudio-style fields until added to a parent coil, while attached transient wrappers read and write a specific
  //   EnergyPlus extensible speed row on the parent object.
  // - Documented Delta: The autosized query methods are API-preserving stubs for now: they return `none` until epmodel grows the
  //   SQL-backed autosized result lookup used by the canonical model layer.
  // - Documented Delta: The canonical equivalent-duct helper surface is exposed here through epmodel's
  //   `AirflowNetworkDistributionComponentCoil`, which is the EnergyPlus-side surrogate written by the model-layer
  //   `AirflowNetworkEquivalentDuct` translator path for coils.
  // - Field/Storage Mapping: Scalar fields map directly to the corresponding EnergyPlus
  //   `Coil:Heating:WaterToAirHeatPump:VariableSpeedEquationFit` fields. The canonical speed-data children are backed by the parent's real
  //   EnergyPlus extensible speed rows, not by separate persisted EnergyPlus objects.
  // - Evidence: `src/model/CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit.hpp`, `src/model/CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateCoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit.cpp`, and `src/epmodel/test/CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_GTest.cpp`.
  // - Remaining Parity Work: Add SQL-backed autosized result lookup if epmodel needs canonical autosized-value parity.
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
