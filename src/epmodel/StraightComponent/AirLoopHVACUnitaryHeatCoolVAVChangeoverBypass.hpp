/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRLOOPHVACUNITARYHEATCOOLVAVCHANGEOVERBYPASS_HPP
#define EPMODEL_AIRLOOPHVACUNITARYHEATCOOLVAVCHANGEOVERBYPASS_HPP

#include "EPModelAPI.hpp"
#include "Mixer/Mixer.hpp"
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

  /**
   * \brief Changeover-bypass VAV unitary system with a supply fan, heating coil, cooling coil, and internal bypass path.
   *
   * \par EnergyPlus object
   * Encapsulates \epobject{group-unitary-equipment.html#airloophvacunitaryheatcoolvavchangeoverbypass,AirLoopHVAC:UnitaryHeatCool:VAVChangeoverBypass}.
   *
   * \par Important behavior
   * The fan and coils are maintained as a parent-owned serial path. `addToNode` connects the unitary to an air-loop
   * supply path and exposes the fan, cooling-coil, and heating-coil outlet nodes. The optional bypass return can be
   * connected to a zone mixer or return plenum.
   *
   * \par OpenStudio Model API
   * Counterpart: `openstudio::model::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass`. The epmodel API covers the
   * unitary scalar controls, schedules, child relationships, and insertion path, plus internal outlet-node helpers.
   * EPModel also exposes direct internal outlet-node and plenum/mixer navigation for the supported serial path.
   *
   * \par Known limitations
   * Return-plenum zone-assignment conveniences and broader local-topology insertion paths are not exposed.
   */
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

    unsigned plenumorMixerAirPort() const;
    Node plenumorMixerNode() const;
    boost::optional<Mixer> plenumorMixer() const;
    bool setPlenumorMixer(const Mixer& returnPathComponent);
    void resetPlenumorMixer();

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
