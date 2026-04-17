/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILHEATINGDXVARIABLESPEED_HPP
#define EPMODEL_COILHEATINGDXVARIABLESPEED_HPP

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
class CoilHeatingDXVariableSpeed_Impl;
}

class EPMODEL_API CoilHeatingDXVariableSpeed : public StraightComponent
{
 public:
  explicit CoilHeatingDXVariableSpeed(const Model& model);
  explicit CoilHeatingDXVariableSpeed(const Model& model, const Curve& partLoadFraction);

  virtual ~CoilHeatingDXVariableSpeed() override = default;
  CoilHeatingDXVariableSpeed(const CoilHeatingDXVariableSpeed& other) = default;
  CoilHeatingDXVariableSpeed(CoilHeatingDXVariableSpeed&& other) = default;
  CoilHeatingDXVariableSpeed& operator=(const CoilHeatingDXVariableSpeed&) = default;
  CoilHeatingDXVariableSpeed& operator=(CoilHeatingDXVariableSpeed&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> defrostStrategyValues();
  static std::vector<std::string> defrostControlValues();

  bool addToNode(Node& node);

  // Schema Alignment Notes:
  // - Status: Partial Parity. Required availability / PLF-curve behavior, optional defrost / crankcase relationships, bounded child traversal,
  //   and the current epmodel supply-side air-loop insertion path are present, while the canonical speed-data family and broader OA / DOAS topology
  //   remain out of scope.
  // - Canonical Counterpart: openstudio::model::CoilHeatingDXVariableSpeed.
  // - Implemented Parity: The speed-level heating-capacity, airflow, defrost, crankcase-heater, and resistive-defrost helpers preserve the canonical
  //   naming and autosize behavior; the required availability schedule, constructor-with-part-load-fraction curve, and energy-part-load-fraction curve
  //   are now preserved; and optional defrost-EIR and crankcase-heater relationship helpers are exposed for the current bounded slice.
  // - Documented Delta: Canonical variable-speed speed-data / speed-list parity remains deferred because epmodel does not yet expose the
  //   `CoilHeatingDXVariableSpeedSpeedData` family or its owning list surface.
  // - Field/Storage Mapping: Preserved scalars and the bounded relationship slice map directly to EnergyPlus `Coil:Heating:DX:VariableSpeed` fields.
  // - Evidence: `src/model/CoilHeatingDXVariableSpeed.hpp`, `src/energyplus/ForwardTranslator/ForwardTranslateCoilHeatingDXVariableSpeed.cpp`, and `src/epmodel/test/CoilHeatingDXVariableSpeed_GTest.cpp`.
  // - Remaining Parity Work: Add canonical speed-data / speed-list parity once epmodel has a viable representation for the `SpeedData` family, and widen
  //   topology acceptance only where the current epmodel air-loop graph can prove it.
  Schedule availabilitySchedule() const;
  bool setAvailabilitySchedule(Schedule& schedule);

  int nominalSpeedLevel() const;
  bool setNominalSpeedLevel(int nominalSpeedLevel);

  boost::optional<double> ratedHeatingCapacityAtSelectedNominalSpeedLevel() const;
  bool isRatedHeatingCapacityAtSelectedNominalSpeedLevelAutosized() const;
  bool setRatedHeatingCapacityAtSelectedNominalSpeedLevel(double ratedHeatingCapacityAtSelectedNominalSpeedLevel);
  void autosizeRatedHeatingCapacityAtSelectedNominalSpeedLevel();

  boost::optional<double> ratedAirFlowRateAtSelectedNominalSpeedLevel() const;
  bool isRatedAirFlowRateAtSelectedNominalSpeedLevelAutosized() const;
  bool setRatedAirFlowRateAtSelectedNominalSpeedLevel(double ratedAirFlowRateAtSelectedNominalSpeedLevel);
  void autosizeRatedAirFlowRateAtSelectedNominalSpeedLevel();

  Curve energyPartLoadFractionCurve() const;
  bool setEnergyPartLoadFractionCurve(const Curve& curve);

  boost::optional<Curve> defrostEnergyInputRatioFunctionofTemperatureCurve() const;
  bool setDefrostEnergyInputRatioFunctionofTemperatureCurve(const Curve& curve);
  void resetDefrostEnergyInputRatioFunctionofTemperatureCurve();

  double minimumOutdoorDryBulbTemperatureforCompressorOperation() const;
  bool setMinimumOutdoorDryBulbTemperatureforCompressorOperation(double minimumOutdoorDryBulbTemperatureforCompressorOperation);

  boost::optional<double> outdoorDryBulbTemperaturetoTurnOnCompressor() const;
  bool setOutdoorDryBulbTemperaturetoTurnOnCompressor(double outdoorDryBulbTemperaturetoTurnOnCompressor);
  void resetOutdoorDryBulbTemperaturetoTurnOnCompressor();

  double maximumOutdoorDryBulbTemperatureforDefrostOperation() const;
  bool setMaximumOutdoorDryBulbTemperatureforDefrostOperation(double maximumOutdoorDryBulbTemperatureforDefrostOperation);

  double crankcaseHeaterCapacity() const;
  bool setCrankcaseHeaterCapacity(double crankcaseHeaterCapacity);

  boost::optional<Curve> crankcaseHeaterCapacityFunctionofTemperatureCurve() const;
  bool setCrankcaseHeaterCapacityFunctionofTemperatureCurve(const Curve& curve);
  void resetCrankcaseHeaterCapacityFunctionofTemperatureCurve();

  double maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation() const;
  bool setMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation(double maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation);

  std::string defrostStrategy() const;
  bool setDefrostStrategy(const std::string& defrostStrategy);

  std::string defrostControl() const;
  bool setDefrostControl(const std::string& defrostControl);

  double defrostTimePeriodFraction() const;
  bool setDefrostTimePeriodFraction(double defrostTimePeriodFraction);

  boost::optional<double> resistiveDefrostHeaterCapacity() const;
  bool isResistiveDefrostHeaterCapacityAutosized() const;
  bool setResistiveDefrostHeaterCapacity(double resistiveDefrostHeaterCapacity);
  void autosizeResistiveDefrostHeaterCapacity();

 protected:
  using ImplType = detail::CoilHeatingDXVariableSpeed_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit CoilHeatingDXVariableSpeed(std::shared_ptr<detail::CoilHeatingDXVariableSpeed_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
