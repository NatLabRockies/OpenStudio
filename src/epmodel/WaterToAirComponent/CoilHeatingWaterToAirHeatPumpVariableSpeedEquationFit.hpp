/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILHEATINGWATERTOAIRHEATPUMPVARIABLESPEEDEQUATIONFIT_HPP
#define EPMODEL_COILHEATINGWATERTOAIRHEATPUMPVARIABLESPEEDEQUATIONFIT_HPP

#include "EPModelAPI.hpp"
#include "WaterToAirComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl;
}

class EPMODEL_API CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit : public WaterToAirComponent
{
 public:
  explicit CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit(const Model& model);

  virtual ~CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit() override = default;
  CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit(const CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit& other) = default;
  CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit(CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit&& other) = default;
  CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit& operator=(const CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit&) = default;
  CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit& operator=(CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: Preserves openstudio::model scalar accessor names/signatures for model-counterpart compatibility.
  // - Field Mapping: ratedHeatingCapacityAtSelectedNominalSpeedLevel maps to E+ RatedHeatingCapacityAtSelectedNominalSpeedLevel.
  // - Field Mapping: relationship-like fields (availability schedule, node names, speed data/extensibles, and curve references) are excluded.
  // - ForwardTranslator evidence: ForwardTranslateCoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit.cpp writes these scalar fields and autosize semantics.
  // - TODO(parity): Add relationship APIs when epmodel relationship scaffolding is enabled.
  int nominalSpeedLevel() const;
  bool setNominalSpeedLevel(int nominalSpeedLevel);

  boost::optional<double> ratedHeatingCapacityAtSelectedNominalSpeedLevel() const;
  bool setRatedHeatingCapacityAtSelectedNominalSpeedLevel(double ratedHeatingCapacityAtSelectedNominalSpeedLevel);
  bool isRatedHeatingCapacityAtSelectedNominalSpeedLevelAutosized() const;
  void autosizeRatedHeatingCapacityAtSelectedNominalSpeedLevel();

  boost::optional<double> ratedAirFlowRateAtSelectedNominalSpeedLevel() const;
  bool setRatedAirFlowRateAtSelectedNominalSpeedLevel(double ratedAirFlowRateAtSelectedNominalSpeedLevel);
  bool isRatedAirFlowRateAtSelectedNominalSpeedLevelAutosized() const;
  void autosizeRatedAirFlowRateAtSelectedNominalSpeedLevel();

  boost::optional<double> ratedWaterFlowRateAtSelectedNominalSpeedLevel() const;
  bool setRatedWaterFlowRateAtSelectedNominalSpeedLevel(double ratedWaterFlowRateAtSelectedNominalSpeedLevel);
  bool isRatedWaterFlowRateAtSelectedNominalSpeedLevelAutosized() const;
  void autosizeRatedWaterFlowRateAtSelectedNominalSpeedLevel();

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
