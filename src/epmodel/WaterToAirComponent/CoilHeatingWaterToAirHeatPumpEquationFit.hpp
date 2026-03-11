/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILHEATINGWATERTOAIRHEATPUMPEQUATIONFIT_HPP
#define EPMODEL_COILHEATINGWATERTOAIRHEATPUMPEQUATIONFIT_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class CoilHeatingWaterToAirHeatPumpEquationFit_Impl;
}

class EPMODEL_API CoilHeatingWaterToAirHeatPumpEquationFit : public ModelObject
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
  // - API: Preserves openstudio::model scalar accessor names/signatures for model-counterpart compatibility.
  // - Field Mapping: ratedHeatingCapacity maps to E+ GrossRatedHeatingCapacity.
  // - Field Mapping: ratedHeatingCoefficientofPerformance maps to E+ GrossRatedHeatingCOP.
  // - Field Mapping: relationship-like fields (availability schedule, node names, and curve references) are intentionally excluded.
  // - ForwardTranslator evidence: ForwardTranslateCoilHeatingWaterToAirHeatPumpEquationFit.cpp writes these exact scalar fields and autosize semantics.
  // - TODO(parity): Add relationship field APIs when epmodel relationship scaffolding is enabled.
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
