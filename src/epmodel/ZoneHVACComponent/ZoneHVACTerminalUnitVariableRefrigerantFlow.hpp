/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACTERMINALUNITVARIABLEREFRIGERANTFLOW_HPP
#define EPMODEL_ZONEHVACTERMINALUNITVARIABLEREFRIGERANTFLOW_HPP

#include "EPModelAPI.hpp"
#include "ZoneHVACComponent.hpp"

#include <utilities/idd/ZoneHVAC_TerminalUnit_VariableRefrigerantFlow_FieldEnums.hxx>
#include <boost/optional.hpp>
#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class CoilCoolingDXVariableRefrigerantFlow;
  class CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl;
  class CoilHeatingDXVariableRefrigerantFlow;
  class CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl;
  class HVACComponent;
  class ModelObject;
  class Node;
  class OutdoorAirMixer;
  class Schedule;
  class ThermalZone;

  namespace detail {
    class ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl;
  }

/** \brief A variable-refrigerant-flow terminal unit serving a thermal zone.
 *
 * \par EnergyPlus object
 * \epobject{group-zone-forced-air-units.html#zonehvacterminalunitvariablerefrigerantflow,ZoneHVAC:TerminalUnit:VariableRefrigerantFlow}
 *
 * \par Important behavior
 * Contained fan and coils share a parent-owned air path, and a local outdoor-air mixer is an additive child convenience. Moving a live terminal between a main branch and outdoor-air stream requires removing its existing air-loop placement first.
 *
 * \par OpenStudio Model API
 * The corresponding OpenStudio Model class is <code>openstudio::model::ZoneHVACTerminalUnitVariableRefrigerantFlow</code>.
 * EPModel adds explicit boundary-node accessors, an outdoor-air mixer view,
 * and persisted-child traversal; Model instead exposes
 * <code>isFluidTemperatureControl()</code> and an autosized supplemental-heater
 * temperature query.
 *
 * \par Known limitations
 * A detached EPModel terminal retains materialized boundary nodes and its local mixer. Clone and sizing conveniences and the unselected relief-stream role are not fully aligned with Model.
 */
  class EPMODEL_API ZoneHVACTerminalUnitVariableRefrigerantFlow : public ZoneHVACComponent
  {
   public:
    explicit ZoneHVACTerminalUnitVariableRefrigerantFlow(const Model& model, bool isFluidTemperatureControl = false);
    explicit ZoneHVACTerminalUnitVariableRefrigerantFlow(const Model& model, const CoilCoolingDXVariableRefrigerantFlow& coolingCoil,
                                                         const CoilHeatingDXVariableRefrigerantFlow& heatingCoil, const HVACComponent& fan);
    explicit ZoneHVACTerminalUnitVariableRefrigerantFlow(const Model& model,
                                                         const CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl& coolingCoil,
                                                         const CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl& heatingCoil,
                                                         const HVACComponent& fan);

    virtual ~ZoneHVACTerminalUnitVariableRefrigerantFlow() override = default;
    ZoneHVACTerminalUnitVariableRefrigerantFlow(const ZoneHVACTerminalUnitVariableRefrigerantFlow& other) = default;
    ZoneHVACTerminalUnitVariableRefrigerantFlow(ZoneHVACTerminalUnitVariableRefrigerantFlow&& other) = default;
    ZoneHVACTerminalUnitVariableRefrigerantFlow& operator=(const ZoneHVACTerminalUnitVariableRefrigerantFlow&) = default;
    ZoneHVACTerminalUnitVariableRefrigerantFlow& operator=(ZoneHVACTerminalUnitVariableRefrigerantFlow&&) = default;

    static IddObjectType iddObjectType();
    static std::vector<std::string> supplyAirFanPlacementValues();


    Schedule terminalUnitAvailabilityschedule() const;
    bool setTerminalUnitAvailabilityschedule(Schedule& schedule);

    boost::optional<double> supplyAirFlowRateDuringCoolingOperation() const;
    bool isSupplyAirFlowRateDuringCoolingOperationAutosized() const;
    bool setSupplyAirFlowRateDuringCoolingOperation(double supplyAirFlowRateDuringCoolingOperation);
    void autosizeSupplyAirFlowRateDuringCoolingOperation();

    boost::optional<double> supplyAirFlowRateWhenNoCoolingisNeeded() const;
    bool isSupplyAirFlowRateWhenNoCoolingisNeededAutosized() const;
    bool setSupplyAirFlowRateWhenNoCoolingisNeeded(double supplyAirFlowRateWhenNoCoolingisNeeded);
    void resetSupplyAirFlowRateWhenNoCoolingisNeeded();
    void autosizeSupplyAirFlowRateWhenNoCoolingisNeeded();

    boost::optional<double> supplyAirFlowRateDuringHeatingOperation() const;
    bool isSupplyAirFlowRateDuringHeatingOperationAutosized() const;
    bool setSupplyAirFlowRateDuringHeatingOperation(double supplyAirFlowRateDuringHeatingOperation);
    void autosizeSupplyAirFlowRateDuringHeatingOperation();

    boost::optional<double> supplyAirFlowRateWhenNoHeatingisNeeded() const;
    bool isSupplyAirFlowRateWhenNoHeatingisNeededAutosized() const;
    bool setSupplyAirFlowRateWhenNoHeatingisNeeded(double supplyAirFlowRateWhenNoHeatingisNeeded);
    void resetSupplyAirFlowRateWhenNoHeatingisNeeded();
    void autosizeSupplyAirFlowRateWhenNoHeatingisNeeded();

    boost::optional<double> outdoorAirFlowRateDuringCoolingOperation() const;
    bool isOutdoorAirFlowRateDuringCoolingOperationAutosized() const;
    bool setOutdoorAirFlowRateDuringCoolingOperation(double outdoorAirFlowRateDuringCoolingOperation);
    void autosizeOutdoorAirFlowRateDuringCoolingOperation();

    boost::optional<double> outdoorAirFlowRateDuringHeatingOperation() const;
    bool isOutdoorAirFlowRateDuringHeatingOperationAutosized() const;
    bool setOutdoorAirFlowRateDuringHeatingOperation(double outdoorAirFlowRateDuringHeatingOperation);
    void autosizeOutdoorAirFlowRateDuringHeatingOperation();

    boost::optional<double> outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() const;
    bool isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const;
    bool setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(double outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded);
    void resetOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
    void autosizeOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();

    double zoneTerminalUnitOnParasiticElectricEnergyUse() const;
    bool setZoneTerminalUnitOnParasiticElectricEnergyUse(double zoneTerminalUnitOnParasiticElectricEnergyUse);

    double zoneTerminalUnitOffParasiticElectricEnergyUse() const;
    bool setZoneTerminalUnitOffParasiticElectricEnergyUse(double zoneTerminalUnitOffParasiticElectricEnergyUse);

    double ratedTotalHeatingCapacitySizingRatio() const;
    bool setRatedTotalHeatingCapacitySizingRatio(double ratedTotalHeatingCapacitySizingRatio);

    boost::optional<double> maximumSupplyAirTemperaturefromSupplementalHeater() const;
    bool isMaximumSupplyAirTemperaturefromSupplementalHeaterAutosized() const;
    bool setMaximumSupplyAirTemperaturefromSupplementalHeater(double maximumSupplyAirTemperaturefromSupplementalHeater);
    void autosizeMaximumSupplyAirTemperaturefromSupplementalHeater();

    double maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation() const;
    bool isMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperationDefaulted() const;
    bool setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(double maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation);
    void resetMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation();

    std::string supplyAirFanPlacement() const;
    bool isSupplyAirFanPlacementDefaulted() const;
    bool setSupplyAirFanPlacement(const std::string& supplyAirFanPlacement);
    void resetSupplyAirFanPlacement();

    HVACComponent supplyAirFan() const;
    bool setSupplyAirFan(const HVACComponent& fan);

    Schedule supplyAirFanOperatingModeSchedule() const;
    bool setSupplyAirFanOperatingModeSchedule(Schedule& schedule);

    boost::optional<HVACComponent> coolingCoil() const;
    bool setCoolingCoil(const HVACComponent& coil);

    boost::optional<HVACComponent> heatingCoil() const;
    bool setHeatingCoil(const HVACComponent& coil);

    boost::optional<HVACComponent> supplementalHeatingCoil() const;
    bool setSupplementalHeatingCoil(const HVACComponent& coil);
    void resetSupplementalHeatingCoil();

    boost::optional<Node> fanOutletNode() const;
    boost::optional<Node> coolingCoilOutletNode() const;
    boost::optional<Node> heatingCoilOutletNode() const;
    boost::optional<Node> mixedAirNode() const;
    boost::optional<Node> outdoorAirNode() const;
    boost::optional<Node> reliefAirNode() const;
    boost::optional<OutdoorAirMixer> outdoorAirMixer() const;

    boost::optional<ThermalZone> controllingZoneorThermostatLocation() const;
    bool setControllingZoneorThermostatLocation(const ThermalZone& thermalZone);
    void resetControllingZoneorThermostatLocation();

    boost::optional<HVACComponent> vrfSystem() const;

    std::vector<ModelObject> children() const;

    boost::optional<double> autosizedSupplyAirFlowRateDuringCoolingOperation() const;
    boost::optional<double> autosizedSupplyAirFlowRateWhenNoCoolingisNeeded() const;
    boost::optional<double> autosizedSupplyAirFlowRateDuringHeatingOperation() const;
    boost::optional<double> autosizedSupplyAirFlowRateWhenNoHeatingisNeeded() const;
    boost::optional<double> autosizedOutdoorAirFlowRateDuringCoolingOperation() const;
    boost::optional<double> autosizedOutdoorAirFlowRateDuringHeatingOperation() const;
    boost::optional<double> autosizedOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() const;

   protected:
    using ImplType = detail::ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ZoneHVACTerminalUnitVariableRefrigerantFlow(std::shared_ptr<detail::ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
