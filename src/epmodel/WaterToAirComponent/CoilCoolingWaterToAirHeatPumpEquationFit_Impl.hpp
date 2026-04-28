/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILCOOLINGWATERTOAIRHEATPUMPEQUATIONFIT_IMPL_HPP
#define EPMODEL_COILCOOLINGWATERTOAIRHEATPUMPEQUATIONFIT_IMPL_HPP

#include "WaterToAirComponent_Impl.hpp"

namespace openstudio {
namespace epmodel {

class Curve;
class Model;
class ModelObject;
class Schedule;
class AirflowNetworkDistributionComponentCoil;

namespace detail {

class EPMODEL_API CoilCoolingWaterToAirHeatPumpEquationFit_Impl : public WaterToAirComponent_Impl
{
 public:
  using WaterToAirComponent_Impl::WaterToAirComponent_Impl;
  virtual ~CoilCoolingWaterToAirHeatPumpEquationFit_Impl() override = default;

  unsigned airInletPort() const override;
  unsigned airOutletPort() const override;
  unsigned waterInletPort() const override;
  unsigned waterOutletPort() const override;

  Schedule availabilitySchedule() const;
  bool setAvailabilitySchedule(Schedule& schedule);

  boost::optional<double> ratedAirFlowRate() const;
  bool isRatedAirFlowRateDefaulted() const;
  bool isRatedAirFlowRateAutosized() const;
  bool setRatedAirFlowRate(double ratedAirFlowRate);
  void resetRatedAirFlowRate();
  void autosizeRatedAirFlowRate();
  boost::optional<double> autosizedRatedAirFlowRate() const;

  boost::optional<double> ratedWaterFlowRate() const;
  bool isRatedWaterFlowRateDefaulted() const;
  bool isRatedWaterFlowRateAutosized() const;
  bool setRatedWaterFlowRate(double ratedWaterFlowRate);
  void resetRatedWaterFlowRate();
  void autosizeRatedWaterFlowRate();
  boost::optional<double> autosizedRatedWaterFlowRate() const;

  boost::optional<double> ratedTotalCoolingCapacity() const;
  bool isRatedTotalCoolingCapacityDefaulted() const;
  bool isRatedTotalCoolingCapacityAutosized() const;
  bool setRatedTotalCoolingCapacity(double ratedTotalCoolingCapacity);
  void resetRatedTotalCoolingCapacity();
  void autosizeRatedTotalCoolingCapacity();
  boost::optional<double> autosizedRatedTotalCoolingCapacity() const;

  boost::optional<double> ratedSensibleCoolingCapacity() const;
  bool isRatedSensibleCoolingCapacityDefaulted() const;
  bool isRatedSensibleCoolingCapacityAutosized() const;
  bool setRatedSensibleCoolingCapacity(double ratedSensibleCoolingCapacity);
  void resetRatedSensibleCoolingCapacity();
  void autosizeRatedSensibleCoolingCapacity();
  boost::optional<double> autosizedRatedSensibleCoolingCapacity() const;

  double ratedCoolingCoefficientofPerformance() const;
  bool isRatedCoolingCoefficientofPerformanceDefaulted() const;
  bool setRatedCoolingCoefficientofPerformance(double ratedCoolingCoefficientofPerformance);

  double ratedEnteringWaterTemperature() const;
  bool setRatedEnteringWaterTemperature(double ratedEnteringWaterTemperature);

  double ratedEnteringAirDryBulbTemperature() const;
  bool setRatedEnteringAirDryBulbTemperature(double ratedEnteringAirDryBulbTemperature);

  double ratedEnteringAirWetBulbTemperature() const;
  bool setRatedEnteringAirWetBulbTemperature(double ratedEnteringAirWetBulbTemperature);

  Curve totalCoolingCapacityCurve() const;
  bool setTotalCoolingCapacityCurve(const Curve& totalCoolingCapacityCurve);

  Curve sensibleCoolingCapacityCurve() const;
  bool setSensibleCoolingCapacityCurve(const Curve& sensibleCoolingCapacityCurve);

  Curve coolingPowerConsumptionCurve() const;
  bool setCoolingPowerConsumptionCurve(const Curve& coolingPowerConsumptionCurve);

  Curve partLoadFractionCorrelationCurve() const;
  bool setPartLoadFractionCorrelationCurve(const Curve& partLoadFractionCorrelationCurve);

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

  std::vector<ModelObject> children() const override;

  AirflowNetworkDistributionComponentCoil getAirflowNetworkEquivalentDuct(double length, double diameter);
  boost::optional<AirflowNetworkDistributionComponentCoil> airflowNetworkEquivalentDuct() const;

  void setConstructorSharedDefaults(const Model& model);
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
