/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILCOOLINGWATERTOAIRHEATPUMPVARIABLESPEEDEQUATIONFIT_IMPL_HPP
#define EPMODEL_COILCOOLINGWATERTOAIRHEATPUMPVARIABLESPEEDEQUATIONFIT_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl : public ModelObject_Impl
{
 public:
  // Scalar-only scaffold: relationship-like fields are intentionally excluded for this cycle.
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl() override = default;

  int nominalSpeedLevel() const;
  bool setNominalSpeedLevel(int nominalSpeedLevel);

  boost::optional<double> grossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel() const;
  bool isGrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevelAutosized() const;
  bool setGrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel(double grossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel);
  void autosizeGrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel();

  boost::optional<double> ratedAirFlowRateAtSelectedNominalSpeedLevel() const;
  bool isRatedAirFlowRateAtSelectedNominalSpeedLevelAutosized() const;
  bool setRatedAirFlowRateAtSelectedNominalSpeedLevel(double ratedAirFlowRateAtSelectedNominalSpeedLevel);
  void autosizeRatedAirFlowRateAtSelectedNominalSpeedLevel();

  boost::optional<double> ratedWaterFlowRateAtSelectedNominalSpeedLevel() const;
  bool isRatedWaterFlowRateAtSelectedNominalSpeedLevelAutosized() const;
  bool setRatedWaterFlowRateAtSelectedNominalSpeedLevel(double ratedWaterFlowRateAtSelectedNominalSpeedLevel);
  void autosizeRatedWaterFlowRateAtSelectedNominalSpeedLevel();

  double nominalTimeforCondensatetoBeginLeavingtheCoil() const;
  bool setNominalTimeforCondensatetoBeginLeavingtheCoil(double nominalTimeforCondensatetoBeginLeavingtheCoil);

  double initialMoistureEvaporationRateDividedbySteadyStateACLatentCapacity() const;
  bool setInitialMoistureEvaporationRateDividedbySteadyStateACLatentCapacity(
    double initialMoistureEvaporationRateDividedbySteadyStateACLatentCapacity);

  double maximumCyclingRate() const;
  bool setMaximumCyclingRate(double maximumCyclingRate);

  double latentCapacityTimeConstant() const;
  bool setLatentCapacityTimeConstant(double latentCapacityTimeConstant);

  double fanDelayTime() const;
  bool setFanDelayTime(double fanDelayTime);

  bool useHotGasReheat() const;
  bool setUseHotGasReheat(bool useHotGasReheat);
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
