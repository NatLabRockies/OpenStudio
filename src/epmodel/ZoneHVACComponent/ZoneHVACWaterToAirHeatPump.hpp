/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACWATERTOAIRHEATPUMP_HPP
#define EPMODEL_ZONEHVACWATERTOAIRHEATPUMP_HPP

#include "EPModelAPI.hpp"
#include "ZoneHVACComponent.hpp"

#include <memory>
#include <string>
#include <vector>

namespace boost {
template <typename T>
class optional;
}

namespace openstudio {
namespace epmodel {

  class Model;
  class HVACComponent;
  class ModelObject;
  class Node;
  class Schedule;

  namespace detail {
    class ZoneHVACWaterToAirHeatPump_Impl;
  }

  class EPMODEL_API ZoneHVACWaterToAirHeatPump : public ZoneHVACComponent
  {
   public:
    explicit ZoneHVACWaterToAirHeatPump(const Model& model);

    virtual ~ZoneHVACWaterToAirHeatPump() override = default;
    ZoneHVACWaterToAirHeatPump(const ZoneHVACWaterToAirHeatPump& other) = default;
    ZoneHVACWaterToAirHeatPump(ZoneHVACWaterToAirHeatPump&& other) = default;
    ZoneHVACWaterToAirHeatPump& operator=(const ZoneHVACWaterToAirHeatPump&) = default;
    ZoneHVACWaterToAirHeatPump& operator=(ZoneHVACWaterToAirHeatPump&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> fanPlacementValues();
    static std::vector<std::string> heatPumpCoilWaterFlowModeValues();

    // Schema Alignment Notes:
    // - Status: Partial Parity. The scalar water-to-air heat-pump fields are aligned, and the contained fan/coil air path is now kept
    //   consistent through parent-owned epmodel nodes, but broader water-to-air heat-pump parity remains incomplete.
    // - Canonical Counterpart: openstudio::model::ZoneHVACWaterToAirHeatPump.
    // - Implemented Parity: The supply-air, outdoor-air, supplemental-heater, and DX sizing scalar groups map directly to the EnergyPlus
    //   object. The contained supply fan, cooling coil, heating coil, and supplemental heating coil now share a parent-owned air path with
    //   direct access to the meaningful fan-outlet, cooling-coil-outlet, and heating-coil-outlet roles on the compound.
    // - Documented Delta: These node accessors are additive conveniences so callers can inspect and rename the internal node roles owned by
    //   the compound, even when some roles alias each other or the parent outlet in a valid configuration. Outdoor-air-mixer-only node roles
    //   still remain outside the public wrapper because they do not have parent-backed field storage on this object.
    // - Field/Storage Mapping: Scalar values live directly on the EnergyPlus object while fan and coil topology is represented through
    //   explicit child-object state and transient epmodel nodes.
    // - Evidence: `src/model/ZoneHVACWaterToAirHeatPump.hpp`, `src/model/ZoneHVACWaterToAirHeatPump.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateZoneHVACWaterToAirHeatPump.cpp`, and `src/epmodel/test/ZoneHVACWaterToAirHeatPump_GTest.cpp`.
    // - Remaining Parity Work: Add any remaining canonical relationship conveniences only if the model wrapper still exposes them as public API.

    Schedule availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);

    /** @name Scalar field accessors */
    //@{

    boost::optional<double> supplyAirFlowRateDuringCoolingOperation() const;
    bool isSupplyAirFlowRateDuringCoolingOperationAutosized() const;
    boost::optional<double> autosizedSupplyAirFlowRateDuringCoolingOperation() const;
    bool setSupplyAirFlowRateDuringCoolingOperation(boost::optional<double> supplyAirFlowRateDuringCoolingOperation);
    bool setSupplyAirFlowRateDuringCoolingOperation(double supplyAirFlowRateDuringCoolingOperation);
    void resetSupplyAirFlowRateDuringCoolingOperation();
    void autosizeSupplyAirFlowRateDuringCoolingOperation();

    boost::optional<double> supplyAirFlowRateDuringHeatingOperation() const;
    bool isSupplyAirFlowRateDuringHeatingOperationAutosized() const;
    boost::optional<double> autosizedSupplyAirFlowRateDuringHeatingOperation() const;
    bool setSupplyAirFlowRateDuringHeatingOperation(boost::optional<double> supplyAirFlowRateDuringHeatingOperation);
    bool setSupplyAirFlowRateDuringHeatingOperation(double supplyAirFlowRateDuringHeatingOperation);
    void resetSupplyAirFlowRateDuringHeatingOperation();
    void autosizeSupplyAirFlowRateDuringHeatingOperation();

    boost::optional<double> supplyAirFlowRateWhenNoCoolingorHeatingisNeeded() const;
    bool isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const;
    boost::optional<double> autosizedSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded() const;
    bool setSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded(boost::optional<double> supplyAirFlowRateWhenNoCoolingorHeatingisNeeded);
    bool setSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded(double supplyAirFlowRateWhenNoCoolingorHeatingisNeeded);
    void resetSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
    void autosizeSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();

    bool noLoadSupplyAirFlowRateControlSetToLowSpeed() const;
    bool setNoLoadSupplyAirFlowRateControlSetToLowSpeed(bool noLoadSupplyAirFlowRateControlSetToLowSpeed);

    boost::optional<double> outdoorAirFlowRateDuringCoolingOperation() const;
    bool isOutdoorAirFlowRateDuringCoolingOperationAutosized() const;
    boost::optional<double> autosizedOutdoorAirFlowRateDuringCoolingOperation() const;
    bool setOutdoorAirFlowRateDuringCoolingOperation(boost::optional<double> outdoorAirFlowRateDuringCoolingOperation);
    bool setOutdoorAirFlowRateDuringCoolingOperation(double outdoorAirFlowRateDuringCoolingOperation);
    void resetOutdoorAirFlowRateDuringCoolingOperation();
    void autosizeOutdoorAirFlowRateDuringCoolingOperation();

    boost::optional<double> outdoorAirFlowRateDuringHeatingOperation() const;
    bool isOutdoorAirFlowRateDuringHeatingOperationAutosized() const;
    boost::optional<double> autosizedOutdoorAirFlowRateDuringHeatingOperation() const;
    bool setOutdoorAirFlowRateDuringHeatingOperation(boost::optional<double> outdoorAirFlowRateDuringHeatingOperation);
    bool setOutdoorAirFlowRateDuringHeatingOperation(double outdoorAirFlowRateDuringHeatingOperation);
    void resetOutdoorAirFlowRateDuringHeatingOperation();
    void autosizeOutdoorAirFlowRateDuringHeatingOperation();

    boost::optional<double> outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() const;
    bool isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const;
    boost::optional<double> autosizedOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() const;
    bool setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(boost::optional<double> outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded);
    bool setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(double outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded);
    void resetOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
    void autosizeOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();

    boost::optional<double> maximumSupplyAirTemperaturefromSupplementalHeater() const;
    bool isMaximumSupplyAirTemperaturefromSupplementalHeaterAutosized() const;
    boost::optional<double> autosizedMaximumSupplyAirTemperaturefromSupplementalHeater() const;
    bool setMaximumSupplyAirTemperaturefromSupplementalHeater(boost::optional<double> maximumSupplyAirTemperaturefromSupplementalHeater);
    bool setMaximumSupplyAirTemperaturefromSupplementalHeater(double maximumSupplyAirTemperaturefromSupplementalHeater);
    void resetMaximumSupplyAirTemperaturefromSupplementalHeater();
    void autosizeMaximumSupplyAirTemperaturefromSupplementalHeater();

    double maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation() const;
    bool isMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperationDefaulted() const;
    bool setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(
      boost::optional<double> maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation);
    bool setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(double maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation);
    void resetMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation();

    std::string fanPlacement() const;
    bool isFanPlacementDefaulted() const;
    bool setFanPlacement(const std::string& fanPlacement);
    void resetFanPlacement();

    std::string heatPumpCoilWaterFlowMode() const;
    bool isHeatPumpCoilWaterFlowModeDefaulted() const;
    bool setHeatPumpCoilWaterFlowMode(const std::string& heatPumpCoilWaterFlowMode);
    void resetHeatPumpCoilWaterFlowMode();

    boost::optional<Schedule> supplyAirFanOperatingModeSchedule() const;
    bool setSupplyAirFanOperatingModeSchedule(Schedule& schedule);
    void resetSupplyAirFanOperatingModeSchedule();

    HVACComponent supplyAirFan() const;
    bool setSupplyAirFan(const HVACComponent& supplyAirFan);

    HVACComponent heatingCoil() const;
    bool setHeatingCoil(const HVACComponent& heatingCoil);

    HVACComponent coolingCoil() const;
    bool setCoolingCoil(const HVACComponent& coolingCoil);

    HVACComponent supplementalHeatingCoil() const;
    bool setSupplementalHeatingCoil(const HVACComponent& supplementalHeatingCoil);

    boost::optional<Node> fanOutletNode() const;
    boost::optional<Node> coolingCoilOutletNode() const;
    boost::optional<Node> heatingCoilOutletNode() const;

    std::vector<ModelObject> children() const;

    double dXHeatingCoilSizingRatio() const;
    bool setDXHeatingCoilSizingRatio(double dXHeatingCoilSizingRatio);
    //@}

   protected:
    using ImplType = detail::ZoneHVACWaterToAirHeatPump_Impl;

    explicit ZoneHVACWaterToAirHeatPump(std::shared_ptr<detail::ZoneHVACWaterToAirHeatPump_Impl> impl);

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
