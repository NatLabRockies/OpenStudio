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
  class HVACComponent;
  class Node;
  class ModelObject;
  class Schedule;
  namespace detail {

    class EPMODEL_API CoilSystemCoolingWater_Impl : public StraightComponent_Impl
    {
     public:
      using StraightComponent_Impl::StraightComponent_Impl;
      virtual ~CoilSystemCoolingWater_Impl() override = default;

      unsigned inletPort() const override;
      unsigned outletPort() const override;

      bool addToNode(Node& node) override;
      std::vector<ModelObject> children() const override;
      std::vector<IdfObject> remove() override;

      Schedule availabilitySchedule() const;
      bool setAvailabilitySchedule(Schedule& schedule);

      HVACComponent coolingCoil() const;
      bool setCoolingCoil(const HVACComponent& coolingCoil);

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

      boost::optional<HVACComponent> companionCoilUsedForHeatRecovery() const;
      bool setCompanionCoilUsedForHeatRecovery(const HVACComponent& companionCoilUsedForHeatRecovery);
      void resetCompanionCoilUsedForHeatRecovery();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
