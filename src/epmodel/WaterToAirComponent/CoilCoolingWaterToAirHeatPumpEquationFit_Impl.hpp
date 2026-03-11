/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILCOOLINGWATERTOAIRHEATPUMPEQUATIONFIT_IMPL_HPP
#define EPMODEL_COILCOOLINGWATERTOAIRHEATPUMPEQUATIONFIT_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API CoilCoolingWaterToAirHeatPumpEquationFit_Impl : public ModelObject_Impl
{
 public:
  // Scalar-only scaffold: relationship-like fields are intentionally excluded for this cycle.
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~CoilCoolingWaterToAirHeatPumpEquationFit_Impl() override = default;

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
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
