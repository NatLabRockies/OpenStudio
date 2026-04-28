/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILSYSTEMINTEGRATEDHEATPUMPAIRSOURCE_IMPL_HPP
#define EPMODEL_COILSYSTEMINTEGRATEDHEATPUMPAIRSOURCE_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {
  class HVACComponent;
  class Node;
  class StraightComponent;
namespace detail {

class EPMODEL_API CoilSystemIntegratedHeatPumpAirSource_Impl : public StraightComponent_Impl
{
 public:
  using StraightComponent_Impl::StraightComponent_Impl;
  virtual ~CoilSystemIntegratedHeatPumpAirSource_Impl() override = default;

  unsigned inletPort() const override;
  unsigned outletPort() const override;
  bool addToNode(Node& node) override;

  StraightComponent spaceCoolingCoil() const;
  boost::optional<StraightComponent> optionalSpaceCoolingCoil() const;
  StraightComponent spaceHeatingCoil() const;
  boost::optional<StraightComponent> optionalSpaceHeatingCoil() const;
  HVACComponent dedicatedWaterHeatingCoil() const;
  boost::optional<HVACComponent> optionalDedicatedWaterHeatingCoil() const;
  HVACComponent scwhCoil() const;
  boost::optional<HVACComponent> optionalScwhCoil() const;
  StraightComponent scdwhCoolingCoil() const;
  boost::optional<StraightComponent> optionalScdwhCoolingCoil() const;
  HVACComponent scdwhWaterHeatingCoil() const;
  boost::optional<HVACComponent> optionalScdwhWaterHeatingCoil() const;
  StraightComponent shdwhHeatingCoil() const;
  boost::optional<StraightComponent> optionalShdwhHeatingCoil() const;
  HVACComponent shdwhWaterHeatingCoil() const;
  boost::optional<HVACComponent> optionalShdwhWaterHeatingCoil() const;

  bool setSpaceCoolingCoil(const StraightComponent& spaceCoolingCoil);
  bool setSpaceHeatingCoil(const StraightComponent& spaceHeatingCoil);
  bool setDedicatedWaterHeatingCoil(const HVACComponent& dedicatedWaterHeatingCoil);
  bool setSCWHCoil(const HVACComponent& scwhCoil);
  bool setSCDWHCoolingCoil(const StraightComponent& scdwhCoolingCoil);
  bool setSCDWHWaterHeatingCoil(const HVACComponent& scdwhWaterHeatingCoil);
  bool setSHDWHHeatingCoil(const StraightComponent& shdwhHeatingCoil);
  bool setSHDWHWaterHeatingCoil(const HVACComponent& shdwhWaterHeatingCoil);

  std::vector<ModelObject> children() const override;

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
