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
  class Node;
  namespace detail {

    class EPMODEL_API CoilSystemCoolingWater_Impl : public StraightComponent_Impl
    {
     public:
      using StraightComponent_Impl::StraightComponent_Impl;
      virtual ~CoilSystemCoolingWater_Impl() override = default;

      unsigned inletPort() const override;
      unsigned outletPort() const override;

      bool addToNode(Node& node) override;

      std::string dehumidificationControlType() const;
      bool setDehumidificationControlType(const std::string& dehumidificationControlType);
      std::vector<std::string> dehumidificationControlTypeValues() const;

      bool runonSensibleLoad() const;
      bool setRunonSensibleLoad(bool runonSensibleLoad);

      bool runonLatentLoad() const;
      bool setRunonLatentLoad(bool runonLatentLoad);

      double minimumAirToWaterTemperatureOffset() const;
      bool setMinimumAirToWaterTemperatureOffset(double minimumAirToWaterTemperatureOffset);

      bool economizerLockout() const;
      bool setEconomizerLockout(bool economizerLockout);

      double minimumWaterLoopTemperatureForHeatRecovery() const;
      bool setMinimumWaterLoopTemperatureForHeatRecovery(double minimumWaterLoopTemperatureForHeatRecovery);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
