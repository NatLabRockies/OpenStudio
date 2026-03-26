/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILHEATINGWATERTOAIRHEATPUMPVARIABLESPEEDEQUATIONFIT_IMPL_HPP
#define EPMODEL_COILHEATINGWATERTOAIRHEATPUMPVARIABLESPEEDEQUATIONFIT_IMPL_HPP

#include "WaterToAirComponent_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl : public WaterToAirComponent_Impl
{
 public:
  using WaterToAirComponent_Impl::WaterToAirComponent_Impl;
  virtual ~CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl() override = default;

  unsigned airInletPort() const override;
  unsigned airOutletPort() const override;
  unsigned waterInletPort() const override;
  unsigned waterOutletPort() const override;

  int nominalSpeedLevel() const;
  bool setNominalSpeedLevel(int nominalSpeedLevel);

  boost::optional<double> ratedHeatingCapacityAtSelectedNominalSpeedLevel() const;
  bool setRatedHeatingCapacityAtSelectedNominalSpeedLevel(double ratedHeatingCapacityAtSelectedNominalSpeedLevel);
  bool isRatedHeatingCapacityAtSelectedNominalSpeedLevelAutosized() const;
  void autosizeRatedHeatingCapacityAtSelectedNominalSpeedLevel();

  boost::optional<double> ratedAirFlowRateAtSelectedNominalSpeedLevel() const;
  bool setRatedAirFlowRateAtSelectedNominalSpeedLevel(double ratedAirFlowRateAtSelectedNominalSpeedLevel);
  bool isRatedAirFlowRateAtSelectedNominalSpeedLevelAutosized() const;
  void autosizeRatedAirFlowRateAtSelectedNominalSpeedLevel();

  boost::optional<double> ratedWaterFlowRateAtSelectedNominalSpeedLevel() const;
  bool setRatedWaterFlowRateAtSelectedNominalSpeedLevel(double ratedWaterFlowRateAtSelectedNominalSpeedLevel);
  bool isRatedWaterFlowRateAtSelectedNominalSpeedLevelAutosized() const;
  void autosizeRatedWaterFlowRateAtSelectedNominalSpeedLevel();
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
