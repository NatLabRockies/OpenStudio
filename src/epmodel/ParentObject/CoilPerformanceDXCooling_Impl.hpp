/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILPERFORMANCEDXCOOLING_IMPL_HPP
#define EPMODEL_COILPERFORMANCEDXCOOLING_IMPL_HPP

#include "ParentObject/ParentObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API CoilPerformanceDXCooling_Impl : public ParentObject_Impl
{
 public:
  using ParentObject_Impl::ParentObject_Impl;
  virtual ~CoilPerformanceDXCooling_Impl() override = default;

  boost::optional<double> grossRatedTotalCoolingCapacity() const;
  bool isGrossRatedTotalCoolingCapacityAutosized() const;
  bool setGrossRatedTotalCoolingCapacity(double grossRatedTotalCoolingCapacity);
  void autosizeGrossRatedTotalCoolingCapacity();

  boost::optional<double> grossRatedSensibleHeatRatio() const;
  bool isGrossRatedSensibleHeatRatioAutosized() const;
  bool setGrossRatedSensibleHeatRatio(double grossRatedSensibleHeatRatio);
  void autosizeGrossRatedSensibleHeatRatio();

  double grossRatedCoolingCOP() const;
  bool setGrossRatedCoolingCOP(double grossRatedCoolingCOP);

  boost::optional<double> ratedAirFlowRate() const;
  bool isRatedAirFlowRateAutosized() const;
  bool setRatedAirFlowRate(double ratedAirFlowRate);
  void autosizeRatedAirFlowRate();

  double fractionofAirFlowBypassedAroundCoil() const;
  bool setFractionofAirFlowBypassedAroundCoil(double fractionofAirFlowBypassedAroundCoil);

  double nominalTimeforCondensateRemovaltoBegin() const;
  bool setNominalTimeforCondensateRemovaltoBegin(double nominalTimeforCondensateRemovaltoBegin);

  double ratioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity() const;
  bool setRatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity(
    double ratioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity);

  double maximumCyclingRate() const;
  bool setMaximumCyclingRate(double maximumCyclingRate);

  double latentCapacityTimeConstant() const;
  bool setLatentCapacityTimeConstant(double latentCapacityTimeConstant);

  std::string condenserType() const;
  bool setCondenserType(const std::string& condenserType);

  double evaporativeCondenserEffectiveness() const;
  bool setEvaporativeCondenserEffectiveness(double evaporativeCondenserEffectiveness);

  boost::optional<double> evaporativeCondenserAirFlowRate() const;
  bool isEvaporativeCondenserAirFlowRateAutosized() const;
  bool setEvaporativeCondenserAirFlowRate(double evaporativeCondenserAirFlowRate);
  void autosizeEvaporativeCondenserAirFlowRate();

  boost::optional<double> evaporativeCondenserPumpRatedPowerConsumption() const;
  bool isEvaporativeCondenserPumpRatedPowerConsumptionAutosized() const;
  bool setEvaporativeCondenserPumpRatedPowerConsumption(double evaporativeCondenserPumpRatedPowerConsumption);
  void autosizeEvaporativeCondenserPumpRatedPowerConsumption();

  std::vector<std::string> condenserTypeValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
