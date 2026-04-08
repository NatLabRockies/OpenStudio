/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACFOURPIPEFANCOIL_HPP
#define EPMODEL_ZONEHVACFOURPIPEFANCOIL_HPP

#include "EPModelAPI.hpp"
#include "ZoneHVACComponent.hpp"

#include <boost/optional.hpp>
#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class HVACComponent;
  class Node;
  class Schedule;

  namespace detail {
    class ZoneHVACFourPipeFanCoil_Impl;
  }

  class EPMODEL_API ZoneHVACFourPipeFanCoil : public ZoneHVACComponent
  {
   public:
    explicit ZoneHVACFourPipeFanCoil(const Model& model);

    virtual ~ZoneHVACFourPipeFanCoil() override = default;
    ZoneHVACFourPipeFanCoil(const ZoneHVACFourPipeFanCoil& other) = default;
    ZoneHVACFourPipeFanCoil(ZoneHVACFourPipeFanCoil&& other) = default;
    ZoneHVACFourPipeFanCoil& operator=(const ZoneHVACFourPipeFanCoil&) = default;
    ZoneHVACFourPipeFanCoil& operator=(ZoneHVACFourPipeFanCoil&&) = default;

    static IddObjectType iddObjectType();
    static std::vector<std::string> capacityControlMethodValues();
    static std::vector<std::string> outdoorAirMixerObjectTypeValues();

    // Schema Alignment Notes:
    // - Status: Partial Parity. The core scalar fields and contained equipment links are present, and the contained fan/coil air path is now kept
    //   consistent through parent-owned epmodel nodes, but broader fan-coil parity remains incomplete.
    // - Canonical Counterpart: openstudio::model::ZoneHVACFourPipeFanCoil.
    // - Implemented Parity: `capacityControlMethod`, supply-air flow scalars, hot/cold water flow scalars, convergence tolerances, supply-air
    //   temperature limits, and the fan/coil child accessors preserve the canonical wrapper behavior. The contained supply fan, cooling coil,
    //   and heating coil now share a parent-owned air path with direct access to the meaningful fan-outlet and cooling-coil-outlet roles on
    //   the compound.
    // - Documented Delta: `fanOutletNode()` and `coolingCoilOutletNode()` are exposed as additive conveniences so callers can inspect and
    //   rename the meaningful node roles owned by the compound, even when those roles alias each other or the parent outlet in a valid
    //   configuration. Outdoor-air mixer linkage remains string-backed, so the OA-mixer-only node roles are still outside the public wrapper
    //   for now.
    // - Field/Storage Mapping: The component's fan, heating/cooling coils, and schedule links are modeled explicitly rather than flattened into
    //   scalar references, and the contained air-path nodes are synchronized through transient Node objects.
    // - Evidence: `src/model/ZoneHVACFourPipeFanCoil.hpp`, `src/model/ZoneHVACFourPipeFanCoil.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateZoneHVACFourPipeFanCoil.cpp`, and `src/epmodel/test/ZoneHVACFourPipeFanCoil_GTest.cpp`.
    // - Remaining Parity Work: Add any remaining canonical fan-coil relationship conveniences only if the model wrapper still exposes them as
    //   public API.

    Schedule availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);

    std::string capacityControlMethod() const;
    bool setCapacityControlMethod(const std::string& capacityControlMethod);

    boost::optional<double> maximumSupplyAirFlowRate() const;
    bool isMaximumSupplyAirFlowRateAutosized() const;
    bool setMaximumSupplyAirFlowRate(double maximumSupplyAirFlowRate);
    void autosizeMaximumSupplyAirFlowRate();

    double lowSpeedSupplyAirFlowRatio() const;
    bool isLowSpeedSupplyAirFlowRatioDefaulted() const;
    bool setLowSpeedSupplyAirFlowRatio(double lowSpeedSupplyAirFlowRatio);
    void resetLowSpeedSupplyAirFlowRatio();

    double mediumSpeedSupplyAirFlowRatio() const;
    bool isMediumSpeedSupplyAirFlowRatioDefaulted() const;
    bool setMediumSpeedSupplyAirFlowRatio(double mediumSpeedSupplyAirFlowRatio);
    void resetMediumSpeedSupplyAirFlowRatio();

    boost::optional<double> maximumOutdoorAirFlowRate() const;
    bool isMaximumOutdoorAirFlowRateAutosized() const;
    bool setMaximumOutdoorAirFlowRate(double maximumOutdoorAirFlowRate);
    void autosizeMaximumOutdoorAirFlowRate();

    std::string outdoorAirMixerObjectType() const;
    bool setOutdoorAirMixerObjectType(const std::string& outdoorAirMixerObjectType);

    boost::optional<Schedule> outdoorAirSchedule() const;
    bool setOutdoorAirSchedule(Schedule& schedule);
    void resetOutdoorAirSchedule();

    HVACComponent supplyAirFan() const;
    HVACComponent coolingCoil() const;
    HVACComponent heatingCoil() const;
    boost::optional<Node> fanOutletNode() const;
    boost::optional<Node> coolingCoilOutletNode() const;

    bool setSupplyAirFan(const HVACComponent& fan);
    bool setCoolingCoil(const HVACComponent& coolingCoil);
    bool setHeatingCoil(const HVACComponent& heatingCoil);

    boost::optional<Schedule> supplyAirFanOperatingModeSchedule() const;
    bool setSupplyAirFanOperatingModeSchedule(Schedule& schedule);
    void resetSupplyAirFanOperatingModeSchedule();

    boost::optional<double> maximumColdWaterFlowRate() const;
    bool isMaximumColdWaterFlowRateAutosized() const;
    bool setMaximumColdWaterFlowRate(double maximumColdWaterFlowRate);
    void autosizeMaximumColdWaterFlowRate();

    double minimumColdWaterFlowRate() const;
    bool isMinimumColdWaterFlowRateDefaulted() const;
    bool setMinimumColdWaterFlowRate(double minimumColdWaterFlowRate);
    void resetMinimumColdWaterFlowRate();

    double coolingConvergenceTolerance() const;
    bool isCoolingConvergenceToleranceDefaulted() const;
    bool setCoolingConvergenceTolerance(double coolingConvergenceTolerance);
    void resetCoolingConvergenceTolerance();

    boost::optional<double> maximumHotWaterFlowRate() const;
    bool isMaximumHotWaterFlowRateAutosized() const;
    bool setMaximumHotWaterFlowRate(double maximumHotWaterFlowRate);
    void autosizeMaximumHotWaterFlowRate();

    double minimumHotWaterFlowRate() const;
    bool isMinimumHotWaterFlowRateDefaulted() const;
    bool setMinimumHotWaterFlowRate(double minimumHotWaterFlowRate);
    void resetMinimumHotWaterFlowRate();

    double heatingConvergenceTolerance() const;
    bool isHeatingConvergenceToleranceDefaulted() const;
    bool setHeatingConvergenceTolerance(double heatingConvergenceTolerance);
    void resetHeatingConvergenceTolerance();

    boost::optional<double> minimumSupplyAirTemperatureInCoolingMode() const;
    bool isMinimumSupplyAirTemperatureInCoolingModeAutosized() const;
    bool setMinimumSupplyAirTemperatureInCoolingMode(double minimumSupplyAirTemperatureInCoolingMode);
    void autosizeMinimumSupplyAirTemperatureInCoolingMode();

    boost::optional<double> maximumSupplyAirTemperatureInHeatingMode() const;
    bool isMaximumSupplyAirTemperatureInHeatingModeAutosized() const;
    bool setMaximumSupplyAirTemperatureInHeatingMode(double maximumSupplyAirTemperatureInHeatingMode);
    void autosizeMaximumSupplyAirTemperatureInHeatingMode();

   protected:
    using ImplType = detail::ZoneHVACFourPipeFanCoil_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ZoneHVACFourPipeFanCoil(std::shared_ptr<detail::ZoneHVACFourPipeFanCoil_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_ZONEHVACFOURPIPEFANCOIL_HPP
