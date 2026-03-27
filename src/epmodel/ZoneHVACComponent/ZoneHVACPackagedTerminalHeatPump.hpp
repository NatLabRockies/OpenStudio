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
    // - Status: Partial Parity. The scalar flow/control fields and child equipment links are present, but schedule, mixer, node, and capacity-control wiring remains relationship-driven.
    // - Canonical Counterpart: openstudio::model::ZoneHVACPackagedTerminalHeatPump.
    // - Implemented Parity: Supply-air and outdoor-air flow scalars, convergence tolerances, supplemental-heater limits, and `fanPlacement` map directly to the EnergyPlus object; contained fan and coil children are exposed explicitly.
    // - Documented Delta: Availability schedules, outdoor-air mixer links, node names, and capacity-control helpers remain outside the current public surface.
    // - Field/Storage Mapping: Scalar values live directly on the EnergyPlus object while the fan and coil topology is modeled through child-object state.
    // - Evidence: `src/model/ZoneHVACPackagedTerminalHeatPump.hpp`, `src/model/ZoneHVACPackagedTerminalHeatPump.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateZoneHVACPackagedTerminalHeatPump.cpp`, and `src/epmodel/test/ZoneHVACPackagedTerminalHeatPump_GTest.cpp`.
    // - Remaining Parity Work: Add the missing relationship helpers only if the canonical wrapper continues to expose them directly.

    unsigned inletPort() const;
    unsigned outletPort() const;

    std::vector<ModelObject> children() const;

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
    bool setSupplyAirFan(HVACComponent& supplyAirFan);

    HVACComponent heatingCoil() const;
    bool setHeatingCoil(HVACComponent& heatingCoil);

    HVACComponent coolingCoil() const;
    bool setCoolingCoil(HVACComponent& coolingCoil);

    HVACComponent supplementalHeatingCoil() const;
    bool setSupplementalHeatingCoil(HVACComponent& supplementalHeatingCoil);

    double dXHeatingCoilSizingRatio() const;
    bool setDXHeatingCoilSizingRatio(double dXHeatingCoilSizingRatio);

   protected:
    using ImplType = detail::ZoneHVACPackagedTerminalHeatPump_Impl;

    explicit ZoneHVACPackagedTerminalHeatPump(std::shared_ptr<detail::ZoneHVACPackagedTerminalHeatPump_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
