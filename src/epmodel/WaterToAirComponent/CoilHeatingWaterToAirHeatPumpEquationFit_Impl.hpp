/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILHEATINGWATERTOAIRHEATPUMPEQUATIONFIT_IMPL_HPP
#define EPMODEL_COILHEATINGWATERTOAIRHEATPUMPEQUATIONFIT_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API CoilHeatingWaterToAirHeatPumpEquationFit_Impl : public ModelObject_Impl
{
 public:
  // Scalar-only scaffold: relationship-like fields are intentionally excluded for this cycle.
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~CoilHeatingWaterToAirHeatPumpEquationFit_Impl() override = default;

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
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
