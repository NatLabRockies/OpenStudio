/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILCOOLINGDXVARIABLESPEED_HPP
#define EPMODEL_COILCOOLINGDXVARIABLESPEED_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;
class Node;
class Schedule;
class Curve;

namespace detail {
class CoilCoolingDXVariableSpeed_Impl;
}

class EPMODEL_API CoilCoolingDXVariableSpeed : public StraightComponent
{
 public:
  explicit CoilCoolingDXVariableSpeed(const Model& model);
  explicit CoilCoolingDXVariableSpeed(const Model& model, const Curve& partLoadFraction);

  virtual ~CoilCoolingDXVariableSpeed() override = default;
  CoilCoolingDXVariableSpeed(const CoilCoolingDXVariableSpeed& other) = default;
  CoilCoolingDXVariableSpeed(CoilCoolingDXVariableSpeed&& other) = default;
  CoilCoolingDXVariableSpeed& operator=(const CoilCoolingDXVariableSpeed&) = default;
  CoilCoolingDXVariableSpeed& operator=(CoilCoolingDXVariableSpeed&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> condenserTypeValues();

  bool addToNode(Node& node);

  // Schema Alignment Notes:
  // - Status: Partial Parity. Required availability / PLF-curve behavior, optional basin / crankcase relationships, bounded child traversal,
  //   and the current epmodel supply-side air-loop insertion path are present, while the canonical speed-data family and broader OA / DOAS topology
  //   remain out of scope.
  // - Canonical Counterpart: openstudio::model::CoilCoolingDXVariableSpeed.
  // - Implemented Parity: The speed-level capacity, airflow, compressor, condenser, and evaporative-condenser helpers preserve the canonical naming and
  //   autosize behavior; the required availability schedule, constructor-with-part-load-fraction curve, and energy-part-load-fraction curve are now
  //   preserved; and optional basin-heater and crankcase-heater relationship helpers are exposed for the current bounded slice.
  // - Documented Delta: Canonical variable-speed stage-data / speed-list parity remains deferred because epmodel does not yet expose the
  //   `CoilCoolingDXVariableSpeedSpeedData` family or its owning list surface.
  // - Field/Storage Mapping: Preserved scalars map directly to EnergyPlus `Coil:Cooling:DX:VariableSpeed` fields.
  // - Evidence: `src/model/CoilCoolingDXVariableSpeed.hpp`, `src/energyplus/ForwardTranslator/ForwardTranslateCoilCoolingDXVariableSpeed.cpp`, and `src/epmodel/test/CoilCoolingDXVariableSpeed_GTest.cpp`.
  // - Remaining Parity Work: Add canonical speed-data / speed-list parity once epmodel has a viable representation for the `SpeedData` family, and widen
  //   topology acceptance only where the current epmodel air-loop graph can prove it.
  Schedule availabilitySchedule() const;
  bool setAvailabilitySchedule(Schedule& schedule);

  int nominalSpeedLevel() const;
  bool setNominalSpeedLevel(int nominalSpeedLevel);

  boost::optional<double> grossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel() const;
  bool setGrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel(double grossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel);
  bool isGrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevelAutosized() const;
  void autosizeGrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel();

  boost::optional<double> ratedAirFlowRateAtSelectedNominalSpeedLevel() const;
  bool setRatedAirFlowRateAtSelectedNominalSpeedLevel(double ratedAirFlowRateAtSelectedNominalSpeedLevel);
  bool isRatedAirFlowRateAtSelectedNominalSpeedLevelAutosized() const;
  void autosizeRatedAirFlowRateAtSelectedNominalSpeedLevel();

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

  Curve energyPartLoadFractionCurve() const;
  bool setEnergyPartLoadFractionCurve(const Curve& curve);

  std::string condenserType() const;
  bool setCondenserType(const std::string& condenserType);

  boost::optional<double> evaporativeCondenserPumpRatedPowerConsumption() const;
  bool setEvaporativeCondenserPumpRatedPowerConsumption(double evaporativeCondenserPumpRatedPowerConsumption);
  bool isEvaporativeCondenserPumpRatedPowerConsumptionAutosized() const;
  void autosizeEvaporativeCondenserPumpRatedPowerConsumption();

  double crankcaseHeaterCapacity() const;
  bool setCrankcaseHeaterCapacity(double crankcaseHeaterCapacity);

  boost::optional<Curve> crankcaseHeaterCapacityFunctionofTemperatureCurve() const;
  bool setCrankcaseHeaterCapacityFunctionofTemperatureCurve(const Curve& curve);
  void resetCrankcaseHeaterCapacityFunctionofTemperatureCurve();

  double maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation() const;
  bool setMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation(double maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation);

  double basinHeaterCapacity() const;
  bool setBasinHeaterCapacity(double basinHeaterCapacity);

  double basinHeaterSetpointTemperature() const;
  bool setBasinHeaterSetpointTemperature(double basinHeaterSetpointTemperature);

  boost::optional<Schedule> basinHeaterOperatingSchedule() const;
  bool setBasinHeaterOperatingSchedule(Schedule& schedule);
  void resetBasinHeaterOperatingSchedule();

  double minimumOutdoorDryBulbTemperatureforCompressorOperation() const;
  bool setMinimumOutdoorDryBulbTemperatureforCompressorOperation(double minimumOutdoorDryBulbTemperatureforCompressorOperation);

 protected:
  using ImplType = detail::CoilCoolingDXVariableSpeed_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit CoilCoolingDXVariableSpeed(std::shared_ptr<detail::CoilCoolingDXVariableSpeed_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
