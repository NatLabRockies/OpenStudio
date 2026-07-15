/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACEVAPORATIVECOOLERUNIT_HPP
#define EPMODEL_ZONEHVACEVAPORATIVECOOLERUNIT_HPP

#include "EPModelAPI.hpp"
#include "ZoneHVACComponent.hpp"

#include <boost/optional.hpp>

#include <memory>
#include <string>
#include <vector>

namespace boost {
template <typename T>
class optional;
}

namespace openstudio {
namespace epmodel {

  class HVACComponent;
  class Model;
  class ModelObject;
  class Node;
  class Schedule;

  namespace detail {
    struct LoadContext;
    class ZoneHVACEvaporativeCoolerUnit_Impl;
  }  // namespace detail

  class EPMODEL_API ZoneHVACEvaporativeCoolerUnit : public ZoneHVACComponent
  {
   public:
    explicit ZoneHVACEvaporativeCoolerUnit(const Model& model);

    virtual ~ZoneHVACEvaporativeCoolerUnit() override = default;
    ZoneHVACEvaporativeCoolerUnit(const ZoneHVACEvaporativeCoolerUnit& other) = default;
    ZoneHVACEvaporativeCoolerUnit(ZoneHVACEvaporativeCoolerUnit&& other) = default;
    ZoneHVACEvaporativeCoolerUnit& operator=(const ZoneHVACEvaporativeCoolerUnit&) = default;
    ZoneHVACEvaporativeCoolerUnit& operator=(ZoneHVACEvaporativeCoolerUnit&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - Status: Partial Parity. The scalar fan/control fields are aligned, and the contained fan/cooler air path is now kept consistent
    //   through parent-owned epmodel nodes, but broader evaporative-cooler-unit parity remains incomplete.
    // - Canonical Counterpart: openstudio::model::ZoneHVACEvaporativeCoolerUnit.
    // - Implemented Parity: `availabilitySchedule`, `supplyAirFan`, `firstEvaporativeCooler`, optional `secondEvaporativeCooler`,
    //   `designSupplyAirFlowRate`, `fanPlacement`, `coolerUnitControlMethod`, throttling-range, cooling-load threshold, and shutoff humidity
    //   map directly to the EnergyPlus object. The contained fan and evaporative coolers now share a parent-owned air path with direct access
    //   to the meaningful outdoor-air, fan-outlet, and first-cooler-outlet roles on the compound.
    // - Documented Delta: `outdoorAirNode()`, `fanOutletNode()`, `firstEvaporativeCoolerOutletNode()`, and
    //   `secondEvaporativeCoolerOutletNode()` are exposed as additive conveniences so callers can inspect and rename the owned node roles even
    //   when those roles alias each other or the parent outlet in a valid configuration.
    // - Field/Storage Mapping: Scalar fields live directly on the EnergyPlus object while schedules and contained equipment are modeled
    //   explicitly through child-object state and transient epmodel nodes.
    // - Evidence: `src/model/ZoneHVACEvaporativeCoolerUnit.hpp`, `src/model/ZoneHVACEvaporativeCoolerUnit.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateZoneHVACEvaporativeCoolerUnit.cpp`, and `src/epmodel/test/ZoneHVACEvaporativeCoolerUnit_GTest.cpp`.
    // - Remaining Parity Work: Add any remaining public relationship helpers only if the canonical wrapper still exposes them directly.
    static std::vector<std::string> fanPlacementValues();
    static std::vector<std::string> coolerUnitControlMethodValues();

    unsigned inletPort() const;
    unsigned outletPort() const;

    Schedule availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);

    HVACComponent supplyAirFan() const;
    bool setSupplyAirFan(const HVACComponent& hvacComponent);

    boost::optional<double> designSupplyAirFlowRate() const;
    bool isDesignSupplyAirFlowRateAutosized() const;
    bool setDesignSupplyAirFlowRate(double designSupplyAirFlowRate);
    void autosizeDesignSupplyAirFlowRate();

    std::string fanPlacement() const;
    bool setFanPlacement(const std::string& fanPlacement);

    std::string coolerUnitControlMethod() const;
    bool setCoolerUnitControlMethod(const std::string& coolerUnitControlMethod);

    double throttlingRangeTemperatureDifference() const;
    bool setThrottlingRangeTemperatureDifference(double throttlingRangeTemperatureDifference);

    double coolingLoadControlThresholdHeatTransferRate() const;
    bool setCoolingLoadControlThresholdHeatTransferRate(double coolingLoadControlThresholdHeatTransferRate);

    HVACComponent firstEvaporativeCooler() const;
    bool setFirstEvaporativeCooler(const HVACComponent& hvacComponent);

    boost::optional<HVACComponent> secondEvaporativeCooler() const;
    bool setSecondEvaporativeCooler(const HVACComponent& hvacComponent);
    void resetSecondEvaporativeCooler();

    double shutOffRelativeHumidity() const;
    bool setShutOffRelativeHumidity(double shutOffRelativeHumidity);

    boost::optional<Node> outdoorAirNode() const;
    boost::optional<Node> fanOutletNode() const;
    boost::optional<Node> firstEvaporativeCoolerOutletNode() const;
    boost::optional<Node> secondEvaporativeCoolerOutletNode() const;

    std::vector<ModelObject> children() const;

   protected:
    using ImplType = detail::ZoneHVACEvaporativeCoolerUnit_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ZoneHVACEvaporativeCoolerUnit(std::shared_ptr<detail::ZoneHVACEvaporativeCoolerUnit_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
