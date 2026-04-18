/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILHEATINGWATERTOAIRHEATPUMPEQUATIONFIT_IMPL_HPP
#define EPMODEL_COILHEATINGWATERTOAIRHEATPUMPEQUATIONFIT_IMPL_HPP

#include "WaterToAirComponent_Impl.hpp"

namespace openstudio {
namespace epmodel {

class Curve;
class Model;
class ModelObject;
class Schedule;
class AirflowNetworkDistributionComponentCoil;

namespace detail {

class EPMODEL_API CoilHeatingWaterToAirHeatPumpEquationFit_Impl : public WaterToAirComponent_Impl
{
 public:
  using WaterToAirComponent_Impl::WaterToAirComponent_Impl;
  virtual ~CoilHeatingWaterToAirHeatPumpEquationFit_Impl() override = default;

  unsigned airInletPort() const override;
  unsigned airOutletPort() const override;
  unsigned waterInletPort() const override;
  unsigned waterOutletPort() const override;

  Schedule availabilitySchedule() const;
  bool setAvailabilitySchedule(Schedule& schedule);

  boost::optional<double> ratedAirFlowRate() const;
  bool isRatedAirFlowRateDefaulted() const;
  bool isRatedAirFlowRateAutosized() const;
  bool setRatedAirFlowRate(boost::optional<double> ratedAirFlowRate);
  bool setRatedAirFlowRate(double ratedAirFlowRate);
  void resetRatedAirFlowRate();
  void autosizeRatedAirFlowRate();
  boost::optional<double> autosizedRatedAirFlowRate() const;

  boost::optional<double> ratedWaterFlowRate() const;
  bool isRatedWaterFlowRateDefaulted() const;
  bool isRatedWaterFlowRateAutosized() const;
  bool setRatedWaterFlowRate(boost::optional<double> ratedWaterFlowRate);
  bool setRatedWaterFlowRate(double ratedWaterFlowRate);
  void resetRatedWaterFlowRate();
  void autosizeRatedWaterFlowRate();
  boost::optional<double> autosizedRatedWaterFlowRate() const;

  boost::optional<double> ratedHeatingCapacity() const;
  bool isRatedHeatingCapacityDefaulted() const;
  bool isRatedHeatingCapacityAutosized() const;
  bool setRatedHeatingCapacity(boost::optional<double> ratedHeatingCapacity);
  bool setRatedHeatingCapacity(double ratedHeatingCapacity);
  void resetRatedHeatingCapacity();
  void autosizeRatedHeatingCapacity();
  boost::optional<double> autosizedRatedHeatingCapacity() const;

  double ratedHeatingCoefficientofPerformance() const;
  bool isRatedHeatingCoefficientofPerformanceDefaulted() const;
  bool setRatedHeatingCoefficientofPerformance(double ratedHeatingCoefficientofPerformance);
  void resetRatedHeatingCoefficientofPerformance();

  double ratedEnteringWaterTemperature() const;
  bool setRatedEnteringWaterTemperature(double ratedEnteringWaterTemperature);

  double ratedEnteringAirDryBulbTemperature() const;
  bool setRatedEnteringAirDryBulbTemperature(double ratedEnteringAirDryBulbTemperature);

  Curve heatingCapacityCurve() const;
  bool setHeatingCapacityCurve(const Curve& heatingCapacityCurve);

  Curve heatingPowerConsumptionCurve() const;
  bool setHeatingPowerConsumptionCurve(const Curve& heatingPowerConsumptionCurve);

  Curve partLoadFractionCorrelationCurve() const;
  bool setPartLoadFractionCorrelationCurve(const Curve& partLoadFractionCorrelationCurve);

  double ratioofRatedHeatingCapacitytoRatedCoolingCapacity() const;
  bool setRatioofRatedHeatingCapacitytoRatedCoolingCapacity(double ratioofRatedHeatingCapacitytoRatedCoolingCapacity);

  std::vector<ModelObject> children() const override;

  AirflowNetworkDistributionComponentCoil getAirflowNetworkEquivalentDuct(double length, double diameter);
  boost::optional<AirflowNetworkDistributionComponentCoil> airflowNetworkEquivalentDuct() const;

  void setConstructorSharedDefaults(const Model& model);
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
