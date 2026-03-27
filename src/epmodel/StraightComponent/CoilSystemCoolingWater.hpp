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
  class Node;

  namespace detail {
    class CoilSystemCoolingWater_Impl;
  }

  class EPMODEL_API CoilSystemCoolingWater : public StraightComponent
  {
   public:
    explicit CoilSystemCoolingWater(const Model& model);

    virtual ~CoilSystemCoolingWater() override = default;
    CoilSystemCoolingWater(const CoilSystemCoolingWater& other) = default;
    CoilSystemCoolingWater(CoilSystemCoolingWater&& other) = default;
    CoilSystemCoolingWater& operator=(const CoilSystemCoolingWater&) = default;
    CoilSystemCoolingWater& operator=(CoilSystemCoolingWater&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> dehumidificationControlTypeValues();

    bool addToNode(Node& node);

    // Schema Alignment Notes:
    // - Status: Partial Parity. The control and performance scalars are present, but coil, companion, schedule, and node-link helpers remain model-owned.
    // - Canonical Counterpart: openstudio::model::CoilSystemCoolingWater.
    // - Implemented Parity: `dehumidificationControlType`, run-on loads, temperature offset, economizer lockout, and heat-recovery limit preserve the canonical scalar API.
    // - Documented Delta: Availability schedule, cooling-coil object/name, companion-coil, and air-node helpers from canonical `openstudio::model::CoilSystemCoolingWater` are not exposed yet.
    // - Field/Storage Mapping: Preserved scalars map directly to EnergyPlus `CoilSystem:Cooling:Water` fields.
    // - Evidence: `src/model/CoilSystemCoolingWater.hpp`, `src/energyplus/ForwardTranslator/ForwardTranslateCoilSystemCoolingWater.cpp`, and `src/epmodel/test/CoilSystemCoolingWater_GTest.cpp`.
    // - Remaining Parity Work: Add the omitted schedule, coil-link, companion-coil, and node-link helpers without changing the preserved scalar signatures.
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
