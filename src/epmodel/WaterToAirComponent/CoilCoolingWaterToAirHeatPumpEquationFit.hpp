/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILCOOLINGWATERTOAIRHEATPUMPEQUATIONFIT_HPP
#define EPMODEL_COILCOOLINGWATERTOAIRHEATPUMPEQUATIONFIT_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class CoilCoolingWaterToAirHeatPumpEquationFit_Impl;
}

class EPMODEL_API CoilCoolingWaterToAirHeatPumpEquationFit : public ModelObject
{
 public:
  explicit CoilCoolingWaterToAirHeatPumpEquationFit(const Model& model);

  virtual ~CoilCoolingWaterToAirHeatPumpEquationFit() override = default;
  CoilCoolingWaterToAirHeatPumpEquationFit(const CoilCoolingWaterToAirHeatPumpEquationFit& other) = default;
  CoilCoolingWaterToAirHeatPumpEquationFit(CoilCoolingWaterToAirHeatPumpEquationFit&& other) = default;
  CoilCoolingWaterToAirHeatPumpEquationFit& operator=(const CoilCoolingWaterToAirHeatPumpEquationFit&) = default;
  CoilCoolingWaterToAirHeatPumpEquationFit& operator=(CoilCoolingWaterToAirHeatPumpEquationFit&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: Preserves openstudio::model scalar accessor names/signatures for model-counterpart compatibility.
  // - Field Mapping: ratedTotalCoolingCapacity/ratedSensibleCoolingCapacity/ratedCoolingCoefficientofPerformance map to E+ GrossRated* fields.
  // - Field Mapping: relationship-like fields (availability schedule, node names, and curve references) are intentionally excluded in this scalar scaffold phase.
  // - ForwardTranslator evidence: ForwardTranslateCoilCoolingWaterToAirHeatPumpEquationFit.cpp writes these exact scalar fields and autosize semantics.
  // - TODO(parity): Add relationship field APIs when epmodel relationship scaffolding is enabled.
  boost::optional<double> ratedAirFlowRate() const;
  bool isRatedAirFlowRateDefaulted() const;
  bool isRatedAirFlowRateAutosized() const;
  bool setRatedAirFlowRate(double ratedAirFlowRate);
  void resetRatedAirFlowRate();
  void autosizeRatedAirFlowRate();

  boost::optional<double> ratedWaterFlowRate() const;
  bool isRatedWaterFlowRateDefaulted() const;
  bool isRatedWaterFlowRateAutosized() const;
  bool setRatedWaterFlowRate(double ratedWaterFlowRate);
  void resetRatedWaterFlowRate();
  void autosizeRatedWaterFlowRate();

  boost::optional<double> ratedTotalCoolingCapacity() const;
  bool isRatedTotalCoolingCapacityDefaulted() const;
  bool isRatedTotalCoolingCapacityAutosized() const;
  bool setRatedTotalCoolingCapacity(double ratedTotalCoolingCapacity);
  void resetRatedTotalCoolingCapacity();
  void autosizeRatedTotalCoolingCapacity();

  boost::optional<double> ratedSensibleCoolingCapacity() const;
  bool isRatedSensibleCoolingCapacityDefaulted() const;
  bool isRatedSensibleCoolingCapacityAutosized() const;
  bool setRatedSensibleCoolingCapacity(double ratedSensibleCoolingCapacity);
  void resetRatedSensibleCoolingCapacity();
  void autosizeRatedSensibleCoolingCapacity();

  double ratedCoolingCoefficientofPerformance() const;
  bool isRatedCoolingCoefficientofPerformanceDefaulted() const;
  bool setRatedCoolingCoefficientofPerformance(double ratedCoolingCoefficientofPerformance);

  double ratedEnteringWaterTemperature() const;
  bool setRatedEnteringWaterTemperature(double ratedEnteringAirDryBulbTemperature);

  double ratedEnteringAirDryBulbTemperature() const;
  bool setRatedEnteringAirDryBulbTemperature(double ratedEnteringAirDryBulbTemperature);

  double ratedEnteringAirWetBulbTemperature() const;
  bool setRatedEnteringAirWetBulbTemperature(double ratedEnteringAirWetBulbTemperature);

  double nominalTimeforCondensateRemovaltoBegin() const;
  bool isNominalTimeforCondensateRemovaltoBeginDefaulted() const;
  bool setNominalTimeforCondensateRemovaltoBegin(double nominalTimeforCondensateRemovaltoBegin);
  void resetNominalTimeforCondensateRemovaltoBegin();

  double ratioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity() const;
  bool isRatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacityDefaulted() const;
  bool setRatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity(
    double ratioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity);
  void resetRatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity();

  double maximumCyclingRate() const;
  bool setMaximumCyclingRate(double maximumCyclingRate);

  double latentCapacityTimeConstant() const;
  bool setLatentCapacityTimeConstant(double latentCapacityTimeConstant);

  double fanDelayTime() const;
  bool setFanDelayTime(double fanDelayTime);

 protected:
  using ImplType = detail::CoilCoolingWaterToAirHeatPumpEquationFit_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit CoilCoolingWaterToAirHeatPumpEquationFit(std::shared_ptr<detail::CoilCoolingWaterToAirHeatPumpEquationFit_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
