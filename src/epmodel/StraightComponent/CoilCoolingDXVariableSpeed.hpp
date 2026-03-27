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

namespace detail {
class CoilCoolingDXVariableSpeed_Impl;
}

class EPMODEL_API CoilCoolingDXVariableSpeed : public StraightComponent
{
 public:
  explicit CoilCoolingDXVariableSpeed(const Model& model);

  virtual ~CoilCoolingDXVariableSpeed() override = default;
  CoilCoolingDXVariableSpeed(const CoilCoolingDXVariableSpeed& other) = default;
  CoilCoolingDXVariableSpeed(CoilCoolingDXVariableSpeed&& other) = default;
  CoilCoolingDXVariableSpeed& operator=(const CoilCoolingDXVariableSpeed&) = default;
  CoilCoolingDXVariableSpeed& operator=(CoilCoolingDXVariableSpeed&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> condenserTypeValues();

  bool addToNode(Node& node);

  // Schema Alignment Notes:
  // - Status: Scalar Parity. The canonical scalar variable-speed DX surface is largely present, while schedule, curve, speed-list, and relationship helpers remain out of scope.
  // - Canonical Counterpart: openstudio::model::CoilCoolingDXVariableSpeed.
  // - Implemented Parity: The speed-level capacity, airflow, compressor, condenser, and evaporative-condenser helpers preserve the canonical naming and autosize behavior.
  // - Documented Delta: Availability schedule, curves, speed-list data, and node-link helpers from canonical `openstudio::model::CoilCoolingDXVariableSpeed` are not exposed yet.
  // - Field/Storage Mapping: Preserved scalars map directly to EnergyPlus `Coil:Cooling:DX:VariableSpeed` fields.
  // - Evidence: `src/model/CoilCoolingDXVariableSpeed.hpp`, `src/energyplus/ForwardTranslator/ForwardTranslateCoilCoolingDXVariableSpeed.cpp`, and `src/epmodel/test/CoilCoolingDXVariableSpeed_GTest.cpp`.
  // - Remaining Parity Work: Add the omitted schedule, curve, speed-list, and relationship helpers without changing the preserved scalar signatures.
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

  std::string condenserType() const;
  bool setCondenserType(const std::string& condenserType);

  boost::optional<double> evaporativeCondenserPumpRatedPowerConsumption() const;
  bool setEvaporativeCondenserPumpRatedPowerConsumption(double evaporativeCondenserPumpRatedPowerConsumption);
  bool isEvaporativeCondenserPumpRatedPowerConsumptionAutosized() const;
  void autosizeEvaporativeCondenserPumpRatedPowerConsumption();

  double crankcaseHeaterCapacity() const;
  bool setCrankcaseHeaterCapacity(double crankcaseHeaterCapacity);

  double maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation() const;
  bool setMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation(double maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation);

  double basinHeaterCapacity() const;
  bool setBasinHeaterCapacity(double basinHeaterCapacity);

  double basinHeaterSetpointTemperature() const;
  bool setBasinHeaterSetpointTemperature(double basinHeaterSetpointTemperature);

  double minimumOutdoorDryBulbTemperatureforCompressorOperation() const;
  bool setMinimumOutdoorDryBulbTemperatureforCompressorOperation(double minimumOutdoorDryBulbTemperatureforCompressorOperation);

 protected:
  using ImplType = detail::CoilCoolingDXVariableSpeed_Impl;

  friend class Model;

  explicit CoilCoolingDXVariableSpeed(std::shared_ptr<detail::CoilCoolingDXVariableSpeed_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
