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

  namespace detail {
    class AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl;
  }

  class EPMODEL_API AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass : public StraightComponent
  {
   public:
    explicit AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass(const Model& model);

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
    // - Status: Partial Parity. The core airflow and operating-mode scalars are aligned, but the canonical object-link and topology surface is still intentionally narrower.
    // - Canonical Counterpart: openstudio::model::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass.
    // - Implemented Parity: `systemAirFlowRateDuringCoolingOperation`, `systemAirFlowRateDuringHeatingOperation`, `systemAirFlowRateWhenNoCoolingorHeatingisNeeded`, `outdoorAirFlowRateDuringCoolingOperation`, `outdoorAirFlowRateDuringHeatingOperation`, `outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded`, `supplyAirFanPlacement`, `priorityControlMode`, `minimumOutletAirTemperatureDuringCoolingOperation`, `maximumOutletAirTemperatureDuringHeatingOperation`, `dehumidificationControlType`, and `minimumRuntimeBeforeOperatingModeChange` preserve the canonical scalar contract.
    // - Documented Delta: Availability schedule, fan/coil object references, node names, and plenum/mixer linkage fields are not exposed as public accessors yet.
    // - Field/Storage Mapping: The preserved scalars map directly to EnergyPlus unitary-system flow and control fields; the forward translator wires fan/coil/topology objects separately.
    // - Evidence: `src/model/AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass.hpp`, `src/model/AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateAirLoopHVACUnitaryHeatCoolVAVChangeoverBypass.cpp`, and `src/epmodel/test/AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_GTest.cpp`.
    // - Remaining Parity Work: Add the omitted schedule, coil, node, and plenum-link helpers once relationship parity is being filled in.
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

    std::string supplyAirFanPlacement() const;
    bool setSupplyAirFanPlacement(const std::string& supplyAirFanPlacement);

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
