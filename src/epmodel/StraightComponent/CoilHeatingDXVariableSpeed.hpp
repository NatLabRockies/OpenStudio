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

namespace detail {
class CoilHeatingDXVariableSpeed_Impl;
}

class EPMODEL_API CoilHeatingDXVariableSpeed : public StraightComponent
{
 public:
  explicit CoilHeatingDXVariableSpeed(const Model& model);

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
  // - Status: Scalar Parity. The canonical scalar heating DX surface is largely present, while schedule, curve, speed-data, and node-link helpers remain out of scope.
  // - Canonical Counterpart: openstudio::model::CoilHeatingDXVariableSpeed.
  // - Implemented Parity: The speed-level heating-capacity, airflow, defrost, crankcase-heater, and resistive-defrost helpers preserve the canonical naming and autosize behavior.
  // - Documented Delta: Availability schedule, curves, speed-data lists, and node-link helpers from canonical `openstudio::model::CoilHeatingDXVariableSpeed` are not exposed yet.
  // - Field/Storage Mapping: Preserved scalars map directly to EnergyPlus `Coil:Heating:DX:VariableSpeed` fields.
  // - Evidence: `src/model/CoilHeatingDXVariableSpeed.hpp`, `src/energyplus/ForwardTranslator/ForwardTranslateCoilHeatingDXVariableSpeed.cpp`, and `src/epmodel/test/CoilHeatingDXVariableSpeed_GTest.cpp`.
  // - Remaining Parity Work: Add the omitted schedule, curve, speed-data, and relationship helpers without changing the preserved scalar signatures.
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

  double minimumOutdoorDryBulbTemperatureforCompressorOperation() const;
  bool setMinimumOutdoorDryBulbTemperatureforCompressorOperation(double minimumOutdoorDryBulbTemperatureforCompressorOperation);

  boost::optional<double> outdoorDryBulbTemperaturetoTurnOnCompressor() const;
  bool setOutdoorDryBulbTemperaturetoTurnOnCompressor(double outdoorDryBulbTemperaturetoTurnOnCompressor);
  void resetOutdoorDryBulbTemperaturetoTurnOnCompressor();

  double maximumOutdoorDryBulbTemperatureforDefrostOperation() const;
  bool setMaximumOutdoorDryBulbTemperatureforDefrostOperation(double maximumOutdoorDryBulbTemperatureforDefrostOperation);

  double crankcaseHeaterCapacity() const;
  bool setCrankcaseHeaterCapacity(double crankcaseHeaterCapacity);

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
