/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILSYSTEMINTEGRATEDHEATPUMPAIRSOURCE_IMPL_HPP
#define EPMODEL_COILSYSTEMINTEGRATEDHEATPUMPAIRSOURCE_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

namespace openstudio {
namespace epmodel {
namespace detail {

class EPMODEL_API CoilSystemIntegratedHeatPumpAirSource_Impl : public StraightComponent_Impl
{
 public:
  using StraightComponent_Impl::StraightComponent_Impl;
  virtual ~CoilSystemIntegratedHeatPumpAirSource_Impl() override = default;

  unsigned inletPort() const override;
  unsigned outletPort() const override;

  double indoorTemperatureLimitForSCWHMode() const;
  bool setIndoorTemperatureLimitForSCWHMode(double indoorTemperatureLimitForSCWHMode);

  double ambientTemperatureLimitForSCWHMode() const;
  bool setAmbientTemperatureLimitForSCWHMode(double ambientTemperatureLimitForSCWHMode);

  double indoorTemperatureAboveWhichWHHasHigherPriority() const;
  bool setIndoorTemperatureAboveWhichWHHasHigherPriority(double indoorTemperatureAboveWhichWHHasHigherPriority);

  double ambientTemperatureAboveWhichWHHasHigherPriority() const;
  bool setAmbientTemperatureAboveWhichWHHasHigherPriority(double ambientTemperatureAboveWhichWHHasHigherPriority);

  int flagtoIndicateLoadControlInSCWHMode() const;
  bool setFlagtoIndicateLoadControlInSCWHMode(int flagtoIndicateLoadControlInSCWHMode);

  int minimumSpeedLevelForSCWHMode() const;
  bool setMinimumSpeedLevelForSCWHMode(int minimumSpeedLevelForSCWHMode);

  double maximumWaterFlowVolumeBeforeSwitchingfromSCDWHtoSCWHMode() const;
  bool setMaximumWaterFlowVolumeBeforeSwitchingfromSCDWHtoSCWHMode(double maximumWaterFlowVolumeBeforeSwitchingfromSCDWHtoSCWHMode);

  int minimumSpeedLevelForSCDWHMode() const;
  bool setMinimumSpeedLevelForSCDWHMode(int minimumSpeedLevelForSCDWHMode);

  double maximumRunningTimeBeforeAllowingElectricResistanceHeatUseDuringSHDWHMode() const;
  bool setMaximumRunningTimeBeforeAllowingElectricResistanceHeatUseDuringSHDWHMode(
    double maximumRunningTimeBeforeAllowingElectricResistanceHeatUseDuringSHDWHMode);

  int minimumSpeedLevelForSHDWHMode() const;
  bool setMinimumSpeedLevelForSHDWHMode(int minimumSpeedLevelForSHDWHMode);
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
