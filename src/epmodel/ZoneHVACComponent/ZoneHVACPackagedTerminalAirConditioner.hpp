/***********************************************************************************************************************  
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.  
*  See also https://openstudio.net/license  
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACPACKAGEDTERMINALAIRCONDITIONER_HPP
#define EPMODEL_ZONEHVACPACKAGEDTERMINALAIRCONDITIONER_HPP

#include "EPModelAPI.hpp"
#include "ZoneHVACComponent.hpp"

#include <utilities/idd/ZoneHVAC_PackagedTerminalAirConditioner_FieldEnums.hxx>
#include <boost/optional.hpp>
#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class Node;
  class ModelObject;
  class HVACComponent;
  class Schedule;

  namespace detail {
    class ZoneHVACPackagedTerminalAirConditioner_Impl;
  }

  class EPMODEL_API ZoneHVACPackagedTerminalAirConditioner : public ZoneHVACComponent
  {
   public:
    explicit ZoneHVACPackagedTerminalAirConditioner(const Model& model);

    virtual ~ZoneHVACPackagedTerminalAirConditioner() override = default;
    ZoneHVACPackagedTerminalAirConditioner(const ZoneHVACPackagedTerminalAirConditioner& other) = default;
    ZoneHVACPackagedTerminalAirConditioner(ZoneHVACPackagedTerminalAirConditioner&& other) = default;
    ZoneHVACPackagedTerminalAirConditioner& operator=(const ZoneHVACPackagedTerminalAirConditioner&) = default;
    ZoneHVACPackagedTerminalAirConditioner& operator=(ZoneHVACPackagedTerminalAirConditioner&&) = default;

    static IddObjectType iddObjectType();
    static std::vector<std::string> fanPlacementValues();
    static std::vector<std::string> validFanPlacementValues();

    // Schema Alignment Notes:
    // - Status: Partial Parity. The flow and fan-placement scalars are aligned, and the contained fan/coil air path is now kept consistent
    //   through parent-owned epmodel nodes, but broader PTAC parity remains incomplete.
    // - Canonical Counterpart: openstudio::model::ZoneHVACPackagedTerminalAirConditioner.
    // - Implemented Parity: Supply-air and outdoor-air flow scalars, `noLoadSupplyAirFlowRateControlSetToLowSpeed`, and `fanPlacement`
    //   map directly to the EnergyPlus object. The contained supply fan, cooling coil, and heating coil now share a parent-owned air path
    //   with direct access to the meaningful fan-outlet, cooling-coil-outlet, and heating-coil-outlet roles on the compound.
    // - Documented Delta: `fanOutletNode()`, `coolingCoilOutletNode()`, and `heatingCoilOutletNode()` are exposed as additive conveniences
    //   so callers can inspect and rename the meaningful node roles owned by the compound, even when those roles alias each other or the
    //   parent outlet in a valid configuration. Outdoor-air mixer references and OA-mixer-only node roles remain outside the public wrapper.
    // - Field/Storage Mapping: Scalar values live directly on the EnergyPlus object while schedules and contained equipment are modeled
    //   explicitly through child-object state and transient epmodel nodes.
    // - Evidence: `src/model/ZoneHVACPackagedTerminalAirConditioner.hpp`, `src/model/ZoneHVACPackagedTerminalAirConditioner.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateZoneHVACPackagedTerminalAirConditioner.cpp`, and `src/epmodel/test/ZoneHVACPackagedTerminalAirConditioner_GTest.cpp`.
    // - Remaining Parity Work: Outdoor-air mixer references and OA-mixer-only node roles are still intentionally omitted from the public
    //   wrapper. Add them later if we decide the wrapper should expose that part of the canonical PTAC surface directly.

    Schedule availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);

    boost::optional<double> supplyAirFlowRateDuringCoolingOperation() const;
    bool setSupplyAirFlowRateDuringCoolingOperation(double supplyAirFlowRateDuringCoolingOperation);
    bool isSupplyAirFlowRateDuringCoolingOperationAutosized() const;
    void autosizeSupplyAirFlowRateDuringCoolingOperation();

    boost::optional<double> supplyAirFlowRateDuringHeatingOperation() const;
    bool setSupplyAirFlowRateDuringHeatingOperation(double supplyAirFlowRateDuringHeatingOperation);
    bool isSupplyAirFlowRateDuringHeatingOperationAutosized() const;
    void autosizeSupplyAirFlowRateDuringHeatingOperation();

    boost::optional<double> supplyAirFlowRateWhenNoCoolingorHeatingisNeeded() const;
    bool setSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded(double supplyAirFlowRateWhenNoCoolingorHeatingisNeeded);
    void resetSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
    bool isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const;
    void autosizeSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();

    bool noLoadSupplyAirFlowRateControlSetToLowSpeed() const;
    bool setNoLoadSupplyAirFlowRateControlSetToLowSpeed(bool noLoadSupplyAirFlowRateControlSetToLowSpeed);

    boost::optional<double> outdoorAirFlowRateDuringCoolingOperation() const;
    bool setOutdoorAirFlowRateDuringCoolingOperation(double outdoorAirFlowRateDuringCoolingOperation);
    bool isOutdoorAirFlowRateDuringCoolingOperationAutosized() const;
    void autosizeOutdoorAirFlowRateDuringCoolingOperation();

    boost::optional<double> outdoorAirFlowRateDuringHeatingOperation() const;
    bool setOutdoorAirFlowRateDuringHeatingOperation(double outdoorAirFlowRateDuringHeatingOperation);
    bool isOutdoorAirFlowRateDuringHeatingOperationAutosized() const;
    void autosizeOutdoorAirFlowRateDuringHeatingOperation();

    boost::optional<double> outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() const;
    bool setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(double outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded);
    void resetOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
    bool isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const;
    void autosizeOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();

    std::string fanPlacement() const;
    bool isFanPlacementDefaulted() const;
    bool setFanPlacement(const std::string& fanPlacement);
    void resetFanPlacement();

    HVACComponent supplyAirFan() const;
    bool setSupplyAirFan(const HVACComponent& fan);

    Schedule supplyAirFanOperatingModeSchedule() const;
    bool setSupplyAirFanOperatingModeSchedule(Schedule& schedule);

    HVACComponent heatingCoil() const;
    bool setHeatingCoil(const HVACComponent& heatingCoil);

    HVACComponent coolingCoil() const;
    bool setCoolingCoil(const HVACComponent& coolingCoil);

    boost::optional<Node> fanOutletNode() const;
    boost::optional<Node> coolingCoilOutletNode() const;
    boost::optional<Node> heatingCoilOutletNode() const;

    std::vector<ModelObject> children() const;

   protected:
    using ImplType = detail::ZoneHVACPackagedTerminalAirConditioner_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ZoneHVACPackagedTerminalAirConditioner(std::shared_ptr<detail::ZoneHVACPackagedTerminalAirConditioner_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
