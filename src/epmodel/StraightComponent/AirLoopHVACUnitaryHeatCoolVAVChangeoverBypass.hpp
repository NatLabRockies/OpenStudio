/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRLOOPHVACUNITARYHEATCOOLVAVCHANGEOVERBYPASS_HPP
#define EPMODEL_AIRLOOPHVACUNITARYHEATCOOLVAVCHANGEOVERBYPASS_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class Node;
  class HVACComponent;
  class ModelObject;
  class Schedule;

  namespace detail {
    class AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl;
  }

  class EPMODEL_API AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass : public StraightComponent
  {
   public:
    explicit AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass(const Model& model);
    AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass(const Model& model, const HVACComponent& fan, const HVACComponent& coolingCoil,
                                                  const HVACComponent& heatingCoil);

    virtual ~AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass() override = default;
    AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass(const AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass& other) = default;
    AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass(AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass&& other) = default;
    AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass& operator=(const AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass&) = default;
    AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass& operator=(AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> supplyAirFanPlacementValues();
    static std::vector<std::string> priorityControlModeValues();
    static std::vector<std::string> dehumidificationControlTypeValues();

    bool addToNode(Node& node);

    // Schema Alignment Notes:
    // - Status: Partial Parity. The core airflow/control scalars and direct object-link fields are aligned, and the owned internal air path is now maintained through parent-owned epmodel nodes.
    // - Canonical Counterpart: openstudio::model::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass.
    // - Implemented Parity: Availability schedule, outdoor-air-flow-rate multiplier schedule, supply fan,
    //   supply-air-fan operating mode schedule, heating coil, cooling coil, and the scalar airflow/control fields preserve the main
    //   canonical wrapper contract. The relationship constructor and child traversal now match the canonical wrapper's owned-component slice.
    //   The owned fan/cooling/heating chain also shares a stable parent-maintained air path, with direct
    //   access to the meaningful outlet node roles on the compound.
    // - Documented Delta: `fanOutletNode()`, `coolingCoilOutletNode()`, and `heatingCoilOutletNode()` are additive epmodel conveniences
    //   for the owned serial air path. Node names and plenum-or-mixer topology conveniences beyond that owned chain remain intentionally
    //   omitted.
    // - Field/Storage Mapping: Scalar values map directly to EnergyPlus unitary-system flow and control fields, while schedule, fan/coil,
    //   and internal-node relationships are explicit parent-owned object links in epmodel.
    // - Evidence: `src/model/AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass.hpp`, `src/model/AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateAirLoopHVACUnitaryHeatCoolVAVChangeoverBypass.cpp`, and `src/epmodel/test/AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_GTest.cpp`.
    // - Remaining Parity Work: Add the omitted node and plenum-link helpers only if the canonical wrapper still exposes them directly.
    boost::optional<Schedule> availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);
    void resetAvailabilitySchedule();

    boost::optional<double> systemAirFlowRateDuringCoolingOperation() const;
    bool setSystemAirFlowRateDuringCoolingOperation(double systemAirFlowRateDuringCoolingOperation);
    bool isSystemAirFlowRateDuringCoolingOperationAutosized() const;
    void autosizeSystemAirFlowRateDuringCoolingOperation();

    boost::optional<double> systemAirFlowRateDuringHeatingOperation() const;
    bool setSystemAirFlowRateDuringHeatingOperation(double systemAirFlowRateDuringHeatingOperation);
    bool isSystemAirFlowRateDuringHeatingOperationAutosized() const;
    void autosizeSystemAirFlowRateDuringHeatingOperation();

    boost::optional<double> systemAirFlowRateWhenNoCoolingorHeatingisNeeded() const;
    bool setSystemAirFlowRateWhenNoCoolingorHeatingisNeeded(double systemAirFlowRateWhenNoCoolingorHeatingisNeeded);
    bool isSystemAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const;
    void autosizeSystemAirFlowRateWhenNoCoolingorHeatingisNeeded();

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
    bool isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const;
    void autosizeOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();

    boost::optional<Schedule> outdoorAirFlowRateMultiplierSchedule() const;
    bool setOutdoorAirFlowRateMultiplierSchedule(Schedule& outdoorAirFlowRateMultiplierSchedule);
    void resetOutdoorAirFlowRateMultiplierSchedule();

    HVACComponent supplyAirFan() const;
    bool setSupplyAirFan(const HVACComponent& fansCVandOnOff);

    std::string supplyAirFanPlacement() const;
    bool setSupplyAirFanPlacement(const std::string& supplyAirFanPlacement);

    boost::optional<Schedule> supplyAirFanOperatingModeSchedule() const;
    bool setSupplyAirFanOperatingModeSchedule(Schedule& schedule);
    void resetSupplyAirFanOperatingModeSchedule();

    HVACComponent coolingCoil() const;
    bool setCoolingCoil(const HVACComponent& coolingCoilName);

    HVACComponent heatingCoil() const;
    bool setHeatingCoil(const HVACComponent& heatingCoilName);

    boost::optional<Node> fanOutletNode() const;
    boost::optional<Node> coolingCoilOutletNode() const;
    boost::optional<Node> heatingCoilOutletNode() const;

    std::string priorityControlMode() const;
    bool setPriorityControlMode(const std::string& priorityControlMode);

    double minimumOutletAirTemperatureDuringCoolingOperation() const;
    bool setMinimumOutletAirTemperatureDuringCoolingOperation(double minimumOutletAirTemperatureDuringCoolingOperation);

    double maximumOutletAirTemperatureDuringHeatingOperation() const;
    bool setMaximumOutletAirTemperatureDuringHeatingOperation(double maximumOutletAirTemperatureDuringHeatingOperation);

    std::string dehumidificationControlType() const;
    bool setDehumidificationControlType(const std::string& dehumidificationControlType);

    double minimumRuntimeBeforeOperatingModeChange() const;
    bool setMinimumRuntimeBeforeOperatingModeChange(double runtime);

   protected:
    using ImplType = detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass(std::shared_ptr<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
