/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILSYSTEMCOOLINGWATER_IMPL_HPP
#define EPMODEL_COILSYSTEMCOOLINGWATER_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {
namespace detail {

class EPMODEL_API CoilSystemCoolingWater_Impl : public StraightComponent_Impl
{
 public:
  using StraightComponent_Impl::StraightComponent_Impl;
  virtual ~CoilSystemCoolingWater_Impl() override = default;

  unsigned inletPort() const override;
  unsigned outletPort() const override;

  std::string dehumidificationControlType() const;
  bool runonSensibleLoad() const;
  bool runonLatentLoad() const;
  double minimumAirToWaterTemperatureOffset() const;
  bool economizerLockout() const;
  double minimumWaterLoopTemperatureForHeatRecovery() const;

  bool setDehumidificationControlType(const std::string& dehumidificationControlType);
  bool setRunonSensibleLoad(bool runonSensibleLoad);
  bool setRunonLatentLoad(bool runonLatentLoad);
  bool setMinimumAirToWaterTemperatureOffset(double minimumAirToWaterTemperatureOffset);
  bool setEconomizerLockout(bool economizerLockout);
  bool setMinimumWaterLoopTemperatureForHeatRecovery(double minimumWaterLoopTemperatureForHeatRecovery);

  std::vector<std::string> dehumidificationControlTypeValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
