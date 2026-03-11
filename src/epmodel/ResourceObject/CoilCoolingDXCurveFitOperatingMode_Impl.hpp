/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILCOOLINGDXCURVEFITOPERATINGMODE_IMPL_HPP
#define EPMODEL_COILCOOLINGDXCURVEFITOPERATINGMODE_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API CoilCoolingDXCurveFitOperatingMode_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~CoilCoolingDXCurveFitOperatingMode_Impl() override = default;

  boost::optional<double> ratedGrossTotalCoolingCapacity() const;
  bool isRatedGrossTotalCoolingCapacityAutosized() const;

  boost::optional<double> ratedEvaporatorAirFlowRate() const;
  bool isRatedEvaporatorAirFlowRateAutosized() const;

  boost::optional<double> ratedCondenserAirFlowRate() const;
  bool isRatedCondenserAirFlowRateAutosized() const;

  double maximumCyclingRate() const;

  double ratioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity() const;

  double latentCapacityTimeConstant() const;

  double nominalTimeforCondensateRemovaltoBegin() const;

  bool applyLatentDegradationtoSpeedsGreaterthan1() const;

  std::string condenserType() const;

  boost::optional<double> nominalEvaporativeCondenserPumpPower() const;
  bool isNominalEvaporativeCondenserPumpPowerAutosized() const;

  unsigned nominalSpeedNumber() const;
  bool isNominalSpeedNumberDefaulted() const;

  bool setRatedGrossTotalCoolingCapacity(double ratedGrossTotalCoolingCapacity);
  void autosizeRatedGrossTotalCoolingCapacity();

  bool setRatedEvaporatorAirFlowRate(double ratedEvaporatorAirFlowRate);
  void autosizeRatedEvaporatorAirFlowRate();

  bool setRatedCondenserAirFlowRate(double ratedCondenserAirFlowRate);
  void autosizeRatedCondenserAirFlowRate();

  bool setMaximumCyclingRate(double maximumCyclingRate);

  bool setRatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity(
    double ratioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity);

  bool setLatentCapacityTimeConstant(double latentCapacityTimeConstant);

  bool setNominalTimeforCondensateRemovaltoBegin(double nominalTimeforCondensateRemovaltoBegin);

  bool setApplyLatentDegradationtoSpeedsGreaterthan1(bool applyLatentDegradationtoSpeedsGreaterthan1);

  bool setCondenserType(const std::string& condenserType);

  bool setNominalEvaporativeCondenserPumpPower(double nominalEvaporativeCondenserPumpPower);
  void autosizeNominalEvaporativeCondenserPumpPower();

  bool setNominalSpeedNumber(unsigned nominalSpeedNumber);
  void resetNominalSpeedNumber();

  std::vector<std::string> condenserTypeValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
