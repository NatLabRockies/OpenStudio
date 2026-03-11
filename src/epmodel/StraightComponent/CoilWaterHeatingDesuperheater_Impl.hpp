/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILWATERHEATINGDESUPERHEATER_IMPL_HPP
#define EPMODEL_COILWATERHEATINGDESUPERHEATER_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

namespace openstudio {
namespace epmodel {
namespace detail {

class EPMODEL_API CoilWaterHeatingDesuperheater_Impl : public StraightComponent_Impl
{
 public:
  using StraightComponent_Impl::StraightComponent_Impl;
  virtual ~CoilWaterHeatingDesuperheater_Impl() override = default;

  unsigned inletPort() const override;
  unsigned outletPort() const override;

  double deadBandTemperatureDifference() const;
  bool isDeadBandTemperatureDifferenceDefaulted() const;

  boost::optional<double> ratedHeatReclaimRecoveryEfficiency() const;

  double ratedInletWaterTemperature() const;
  double ratedOutdoorAirTemperature() const;
  double maximumInletWaterTemperatureforHeatReclaim() const;

  double waterFlowRate() const;

  double waterPumpPower() const;
  bool isWaterPumpPowerDefaulted() const;

  double fractionofPumpHeattoWater() const;
  bool isFractionofPumpHeattoWaterDefaulted() const;

  double onCycleParasiticElectricLoad() const;
  bool isOnCycleParasiticElectricLoadDefaulted() const;

  double offCycleParasiticElectricLoad() const;
  bool isOffCycleParasiticElectricLoadDefaulted() const;

  bool setDeadBandTemperatureDifference(double deadBandTemperatureDifference);
  void resetDeadBandTemperatureDifference();

  bool setRatedHeatReclaimRecoveryEfficiency(double ratedHeatReclaimRecoveryEfficiency);
  void resetRatedHeatReclaimRecoveryEfficiency();

  bool setRatedInletWaterTemperature(double ratedInletWaterTemperature);
  bool setRatedOutdoorAirTemperature(double ratedOutdoorAirTemperature);
  bool setMaximumInletWaterTemperatureforHeatReclaim(double maximumInletWaterTemperatureforHeatReclaim);

  bool setWaterFlowRate(double waterFlowRate);

  bool setWaterPumpPower(double waterPumpPower);
  void resetWaterPumpPower();

  bool setFractionofPumpHeattoWater(double fractionofPumpHeattoWater);
  void resetFractionofPumpHeattoWater();

  bool setOnCycleParasiticElectricLoad(double onCycleParasiticElectricLoad);
  void resetOnCycleParasiticElectricLoad();

  bool setOffCycleParasiticElectricLoad(double offCycleParasiticElectricLoad);
  void resetOffCycleParasiticElectricLoad();
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
