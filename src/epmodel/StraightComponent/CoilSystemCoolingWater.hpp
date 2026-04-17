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

    // Schema Alignment Notes:
    // - Status: Partial Parity. The canonical schedule, cooling-coil, companion-coil, constructor-default, and current insertion-path helpers are
    //   now present, while broader model-owned topology conveniences remain out of scope.
    // - Canonical Counterpart: openstudio::model::CoilSystemCoolingWater.
    // - Implemented Parity: The default constructors, `availabilitySchedule`, `coolingCoil`, `companionCoilUsedForHeatRecovery`, their
    //   relationship setters/reset, the main scalar controls, child traversal, and the current supply-side plus outboard-OA `addToNode(...)`
    //   paths preserve the bounded canonical slice.
    // - Documented Delta: Broader containing-component, clone/remove, and higher-level air-node convenience behavior from canonical
    //   `openstudio::model::CoilSystemCoolingWater` are not exposed yet.
    // - Field/Storage Mapping: Preserved schedule and coil relationships map directly to EnergyPlus `CoilSystem:Cooling:Water` object-list
    //   fields, while the implemented scalars map directly to the remaining control fields.
    // - Evidence: `src/model/CoilSystemCoolingWater.hpp`, `src/energyplus/ForwardTranslator/ForwardTranslateCoilSystemCoolingWater.cpp`, and `src/epmodel/test/CoilSystemCoolingWater_GTest.cpp`.
    // - Remaining Parity Work: Add the remaining containing-component, clone/remove, and higher-level air-node conveniences without changing the
    //   preserved relationship signatures.
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
