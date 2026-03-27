/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILHEATINGWATERTOAIRHEATPUMPEQUATIONFIT_HPP
#define EPMODEL_COILHEATINGWATERTOAIRHEATPUMPEQUATIONFIT_HPP

#include "EPModelAPI.hpp"
#include "WaterToAirComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class CoilHeatingWaterToAirHeatPumpEquationFit_Impl;
}

class EPMODEL_API CoilHeatingWaterToAirHeatPumpEquationFit : public WaterToAirComponent
{
 public:
  explicit CoilHeatingWaterToAirHeatPumpEquationFit(const Model& model);

  virtual ~CoilHeatingWaterToAirHeatPumpEquationFit() override = default;
  CoilHeatingWaterToAirHeatPumpEquationFit(const CoilHeatingWaterToAirHeatPumpEquationFit& other) = default;
  CoilHeatingWaterToAirHeatPumpEquationFit(CoilHeatingWaterToAirHeatPumpEquationFit&& other) = default;
  CoilHeatingWaterToAirHeatPumpEquationFit& operator=(const CoilHeatingWaterToAirHeatPumpEquationFit&) = default;
  CoilHeatingWaterToAirHeatPumpEquationFit& operator=(CoilHeatingWaterToAirHeatPumpEquationFit&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - Status: Scalar Parity. The scalar fit fields and autosize semantics are aligned, while the curve/schedule/duct surface remains intentionally omitted.
  // - Canonical Counterpart: openstudio::model::CoilHeatingWaterToAirHeatPumpEquationFit.
  // - Implemented Parity: `ratedAirFlowRate`, `ratedWaterFlowRate`, `ratedHeatingCapacity`, `ratedHeatingCoefficientofPerformance`, `ratedEnteringWaterTemperature`, `ratedEnteringAirDryBulbTemperature`, `ratioofRatedHeatingCapacitytoRatedCoolingCapacity`, and the autosize/reset helpers preserve the canonical scalar contract.
  // - Documented Delta: Availability schedule, curve objects, and equivalent-duct helpers are not exposed here even though the canonical model type owns them.
  // - Field/Storage Mapping: Scalar fit fields map directly to the corresponding EnergyPlus `Coil:Heating:WaterToAirHeatPump:EquationFit` fields.
  // - Evidence: `src/model/CoilHeatingWaterToAirHeatPumpEquationFit.hpp`, `src/model/CoilHeatingWaterToAirHeatPumpEquationFit.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateCoilHeatingWaterToAirHeatPumpEquationFit.cpp`, and `src/epmodel/test/CoilHeatingWaterToAirHeatPumpEquationFit_GTest.cpp`.
  // - Remaining Parity Work: Add the omitted curve, schedule, and helper APIs only if the family moves beyond scalar parity.
  boost::optional<double> ratedAirFlowRate() const;
  bool isRatedAirFlowRateDefaulted() const;
  bool isRatedAirFlowRateAutosized() const;
  bool setRatedAirFlowRate(boost::optional<double> ratedAirFlowRate);
  bool setRatedAirFlowRate(double ratedAirFlowRate);
  void resetRatedAirFlowRate();
  void autosizeRatedAirFlowRate();

  boost::optional<double> ratedWaterFlowRate() const;
  bool isRatedWaterFlowRateDefaulted() const;
  bool isRatedWaterFlowRateAutosized() const;
  bool setRatedWaterFlowRate(boost::optional<double> ratedWaterFlowRate);
  bool setRatedWaterFlowRate(double ratedWaterFlowRate);
  void resetRatedWaterFlowRate();
  void autosizeRatedWaterFlowRate();

  boost::optional<double> ratedHeatingCapacity() const;
  bool isRatedHeatingCapacityDefaulted() const;
  bool isRatedHeatingCapacityAutosized() const;
  bool setRatedHeatingCapacity(boost::optional<double> ratedHeatingCapacity);
  bool setRatedHeatingCapacity(double ratedHeatingCapacity);
  void resetRatedHeatingCapacity();
  void autosizeRatedHeatingCapacity();

  double ratedHeatingCoefficientofPerformance() const;
  bool isRatedHeatingCoefficientofPerformanceDefaulted() const;
  bool setRatedHeatingCoefficientofPerformance(double ratedHeatingCoefficientofPerformance);
  void resetRatedHeatingCoefficientofPerformance();

  double ratedEnteringWaterTemperature() const;
  bool setRatedEnteringWaterTemperature(double ratedEnteringWaterTemperature);

  double ratedEnteringAirDryBulbTemperature() const;
  bool setRatedEnteringAirDryBulbTemperature(double ratedEnteringAirDryBulbTemperature);

  double ratioofRatedHeatingCapacitytoRatedCoolingCapacity() const;
  bool setRatioofRatedHeatingCapacitytoRatedCoolingCapacity(double ratioofRatedHeatingCapacitytoRatedCoolingCapacity);

 protected:
  using ImplType = detail::CoilHeatingWaterToAirHeatPumpEquationFit_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit CoilHeatingWaterToAirHeatPumpEquationFit(std::shared_ptr<detail::CoilHeatingWaterToAirHeatPumpEquationFit_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
