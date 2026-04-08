/***********************************************************************************************************************  
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.  
*  See also https://openstudio.net/license  
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACPACKAGEDTERMINALHEATPUMP_HPP
#define EPMODEL_ZONEHVACPACKAGEDTERMINALHEATPUMP_HPP

#include "EPModelAPI.hpp"
#include "ZoneHVACComponent.hpp"

#include <utilities/idd/ZoneHVAC_PackagedTerminalHeatPump_FieldEnums.hxx>

#include <boost/optional.hpp>
#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class HVACComponent;
  class ModelObject;
  class Node;
  class Schedule;

  namespace detail {
    class ZoneHVACPackagedTerminalHeatPump_Impl;
  }

  class EPMODEL_API ZoneHVACPackagedTerminalHeatPump : public ZoneHVACComponent
  {
   public:
    explicit ZoneHVACPackagedTerminalHeatPump(const Model& model);

    virtual ~ZoneHVACPackagedTerminalHeatPump() override = default;
    ZoneHVACPackagedTerminalHeatPump(const ZoneHVACPackagedTerminalHeatPump& other) = default;
    ZoneHVACPackagedTerminalHeatPump(ZoneHVACPackagedTerminalHeatPump&& other) = default;
    ZoneHVACPackagedTerminalHeatPump& operator=(const ZoneHVACPackagedTerminalHeatPump&) = default;
    ZoneHVACPackagedTerminalHeatPump& operator=(ZoneHVACPackagedTerminalHeatPump&&) = default;

    static IddObjectType iddObjectType();
    static std::vector<std::string> fanPlacementValues();
    static std::vector<std::string> validFanPlacementValues();

    // Schema Alignment Notes:
    // - Status: Partial Parity. The flow and control scalars are aligned, and the contained fan/coil air path is now kept consistent through
    //   parent-owned epmodel nodes, but broader heat-pump parity remains incomplete.
    // - Canonical Counterpart: openstudio::model::ZoneHVACPackagedTerminalHeatPump.
    // - Implemented Parity: Supply-air and outdoor-air flow scalars, convergence tolerances, supplemental-heater limits, `fanPlacement`, and
    //   the contained fan/coil child accessors preserve the canonical wrapper behavior. The contained supply fan, cooling coil, heating coil,
    //   and supplemental heating coil now share a parent-owned air path, with direct access to the meaningful fan-outlet,
    //   cooling-coil-outlet, and heating-coil-outlet roles on the compound.
    // - Documented Delta: `fanOutletNode()`, `coolingCoilOutletNode()`, and `heatingCoilOutletNode()` are exposed as additive conveniences so
    //   callers can inspect and rename the meaningful node roles owned by the compound, even when those roles alias each other or the parent
    //   outlet in a valid configuration. Outdoor-air mixer references and OA-mixer-only node roles remain outside the public wrapper.
    // - Field/Storage Mapping: Scalar values live directly on the EnergyPlus object while schedules and contained equipment are modeled
    //   explicitly through child-object state and transient epmodel nodes.
    // - Evidence: `src/model/ZoneHVACPackagedTerminalHeatPump.hpp`, `src/model/ZoneHVACPackagedTerminalHeatPump.cpp`,
    //   `src/energyplus/ForwardTranslator/ForwardTranslateZoneHVACPackagedTerminalHeatPump.cpp`, and
    //   `src/epmodel/test/ZoneHVACPackagedTerminalHeatPump_GTest.cpp`.
    // - Remaining Parity Work: Add any remaining canonical heat-pump relationship conveniences only if the model wrapper still exposes them as
    //   public API.

    unsigned inletPort() const;
    unsigned outletPort() const;

    std::vector<ModelObject> children() const;

    Schedule availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);

    boost::optional<double> supplyAirFlowRateDuringCoolingOperation() const;
    bool isSupplyAirFlowRateDuringCoolingOperationAutosized() const;
    bool setSupplyAirFlowRateDuringCoolingOperation(double supplyAirFlowRateDuringCoolingOperation);
    void autosizeSupplyAirFlowRateDuringCoolingOperation();

    boost::optional<double> supplyAirFlowRateDuringHeatingOperation() const;
    bool isSupplyAirFlowRateDuringHeatingOperationAutosized() const;
    bool setSupplyAirFlowRateDuringHeatingOperation(double supplyAirFlowRateDuringHeatingOperation);
    void autosizeSupplyAirFlowRateDuringHeatingOperation();

    boost::optional<double> supplyAirFlowRateWhenNoCoolingorHeatingisNeeded() const;
    bool isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const;
    bool setSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded(double supplyAirFlowRateWhenNoCoolingorHeatingisNeeded);
    void resetSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
    void autosizeSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();

    bool noLoadSupplyAirFlowRateControlSetToLowSpeed() const;
    bool setNoLoadSupplyAirFlowRateControlSetToLowSpeed(bool noLoadSupplyAirFlowRateControlSetToLowSpeed);

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

    double heatingConvergenceTolerance() const;
    bool isHeatingConvergenceToleranceDefaulted() const;
    bool setHeatingConvergenceTolerance(double heatingConvergenceTolerance);
    void resetHeatingConvergenceTolerance();

    double minimumOutdoorDryBulbTemperatureforCompressorOperation() const;
    bool isMinimumOutdoorDryBulbTemperatureforCompressorOperationDefaulted() const;
    bool setMinimumOutdoorDryBulbTemperatureforCompressorOperation(double minimumOutdoorDryBulbTemperatureforCompressorOperation);
    void resetMinimumOutdoorDryBulbTemperatureforCompressorOperation();

    double coolingConvergenceTolerance() const;
    bool isCoolingConvergenceToleranceDefaulted() const;
    bool setCoolingConvergenceTolerance(double coolingConvergenceTolerance);
    void resetCoolingConvergenceTolerance();

    boost::optional<double> maximumSupplyAirTemperaturefromSupplementalHeater() const;
    bool isMaximumSupplyAirTemperaturefromSupplementalHeaterAutosized() const;
    bool setMaximumSupplyAirTemperaturefromSupplementalHeater(double maximumSupplyAirTemperaturefromSupplementalHeater);
    void autosizeMaximumSupplyAirTemperaturefromSupplementalHeater();

    double maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation() const;
    bool isMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperationDefaulted() const;
    bool setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(double maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation);
    void resetMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation();

    std::string fanPlacement() const;
    bool isFanPlacementDefaulted() const;
    bool setFanPlacement(const std::string& fanPlacement);
    void resetFanPlacement();

    HVACComponent supplyAirFan() const;
    bool setSupplyAirFan(const HVACComponent& supplyAirFan);

    Schedule supplyAirFanOperatingModeSchedule() const;
    bool setSupplyAirFanOperatingModeSchedule(Schedule& schedule);

    HVACComponent heatingCoil() const;
    bool setHeatingCoil(const HVACComponent& heatingCoil);

    HVACComponent coolingCoil() const;
    bool setCoolingCoil(const HVACComponent& coolingCoil);

    HVACComponent supplementalHeatingCoil() const;
    bool setSupplementalHeatingCoil(const HVACComponent& supplementalHeatingCoil);

    boost::optional<Node> fanOutletNode() const;
    boost::optional<Node> coolingCoilOutletNode() const;
    boost::optional<Node> heatingCoilOutletNode() const;

    double dXHeatingCoilSizingRatio() const;
    bool setDXHeatingCoilSizingRatio(double dXHeatingCoilSizingRatio);

   protected:
    using ImplType = detail::ZoneHVACPackagedTerminalHeatPump_Impl;

    explicit ZoneHVACPackagedTerminalHeatPump(std::shared_ptr<detail::ZoneHVACPackagedTerminalHeatPump_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
