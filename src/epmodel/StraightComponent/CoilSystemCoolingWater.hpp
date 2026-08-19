/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILSYSTEMCOOLINGWATER_HPP
#define EPMODEL_COILSYSTEMCOOLINGWATER_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class Schedule;
  class HVACComponent;
  class Node;

  namespace detail {
    class CoilSystemCoolingWater_Impl;
  }

  /** \brief Represents a water-coil cooling system.
   *
   * \par EnergyPlus object
   * \epobject{group-heating-and-cooling-coils.html#coilsystemcoolingwater,CoilSystem:Cooling:Water}.
   *
   * \par Important behavior
   * Referenced child coils and the supported contained air path are stored through the EnergyPlus object-list fields.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::CoilSystemCoolingWater</code>. <b>Added:</b> EPModel exposes <code>addToNode()</code>. The Model-only <code>assignEnergyPlusIDDDefaults()</code> helper is not exposed. Broader containing-component, clone/remove, and higher-level air-node convenience methods remain unavailable.
   * \par Known limitations
   * Use the supported compound-parent workflows for loop placement.
   */
  class EPMODEL_API CoilSystemCoolingWater : public StraightComponent
  {
   public:
    explicit CoilSystemCoolingWater(const Model& model);
    explicit CoilSystemCoolingWater(const Model& model, const HVACComponent& coolingCoil);

    virtual ~CoilSystemCoolingWater() override = default;
    CoilSystemCoolingWater(const CoilSystemCoolingWater& other) = default;
    CoilSystemCoolingWater(CoilSystemCoolingWater&& other) = default;
    CoilSystemCoolingWater& operator=(const CoilSystemCoolingWater&) = default;
    CoilSystemCoolingWater& operator=(CoilSystemCoolingWater&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> dehumidificationControlTypeValues();

    bool addToNode(Node& node);

    Schedule availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);

    HVACComponent coolingCoil() const;
    bool setCoolingCoil(const HVACComponent& coolingCoil);

    std::string dehumidificationControlType() const;
    bool setDehumidificationControlType(const std::string& dehumidificationControlType);

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

   protected:
    using ImplType = detail::CoilSystemCoolingWater_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CoilSystemCoolingWater(std::shared_ptr<detail::CoilSystemCoolingWater_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
