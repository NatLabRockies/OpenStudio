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
  // - Status: Scalar Parity. The scalar speed-level fields are aligned, while the extensible speed-data surface remains intentionally omitted.
  // - Canonical Counterpart: openstudio::model::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit.
  // - Implemented Parity: `nominalSpeedLevel`, `ratedHeatingCapacityAtSelectedNominalSpeedLevel`, `ratedAirFlowRateAtSelectedNominalSpeedLevel`, `ratedWaterFlowRateAtSelectedNominalSpeedLevel`, and the autosize helpers preserve the canonical scalar contract.
  // - Documented Delta: Availability schedule, part-load curve, and speed-data extensible objects are not exposed here even though the canonical model type owns them.
  // - Field/Storage Mapping: Scalar fields map directly to the corresponding EnergyPlus `Coil:Heating:WaterToAirHeatPump:VariableSpeedEquationFit` fields.
  // - Evidence: `src/model/CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit.hpp`, `src/model/CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateCoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit.cpp`, and `src/epmodel/test/CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_GTest.cpp`.
  // - Remaining Parity Work: Add the omitted curve, schedule, and extensible speed-data APIs only if the family moves beyond scalar parity.
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
