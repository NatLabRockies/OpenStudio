/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACENERGYRECOVERYVENTILATOR_HPP
#define EPMODEL_ZONEHVACENERGYRECOVERYVENTILATOR_HPP

#include "EPModelAPI.hpp"
#include "ZoneHVACComponent.hpp"

#include <boost/optional.hpp>
#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class HVACComponent;
  class ModelObject;
  class Node;
  class Schedule;
  class ZoneHVACEnergyRecoveryVentilatorController;

  namespace detail {
    struct LoadContext;
    class ZoneHVACEnergyRecoveryVentilator_Impl;
  }

  class EPMODEL_API ZoneHVACEnergyRecoveryVentilator : public ZoneHVACComponent
  {
   public:
    explicit ZoneHVACEnergyRecoveryVentilator(const Model& model);

    virtual ~ZoneHVACEnergyRecoveryVentilator() override = default;
    ZoneHVACEnergyRecoveryVentilator(const ZoneHVACEnergyRecoveryVentilator& other) = default;
    ZoneHVACEnergyRecoveryVentilator(ZoneHVACEnergyRecoveryVentilator&& other) = default;
    ZoneHVACEnergyRecoveryVentilator& operator=(const ZoneHVACEnergyRecoveryVentilator&) = default;
    ZoneHVACEnergyRecoveryVentilator& operator=(ZoneHVACEnergyRecoveryVentilator&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - Status: Partial Parity. The scalar ventilation fields are aligned, and the owned heat-exchanger/fan topology is now kept consistent
    //   through parent-owned epmodel nodes, but broader ERV parity remains incomplete.
    // - Canonical Counterpart: openstudio::model::ZoneHVACEnergyRecoveryVentilator.
    // - Implemented Parity: `availabilitySchedule`, `heatExchanger`, `supplyAirFan`, `exhaustAirFan`, optional `controller`,
    //   `supplyAirFlowRate`, `exhaustAirFlowRate`, `ventilationRateperUnitFloorArea`, `ventilationRateperOccupant`, and `children()`
    //   preserve the main canonical wrapper behavior. The owned heat exchanger and fans now share a parent-owned dual-path topology with
    //   direct access to the meaningful outdoor-air, supply-fan-inlet, exhaust-fan-inlet, and relief-air node roles on the compound.
    // - Documented Delta: The parent-level node conveniences are additive epmodel APIs. Availability-manager relationships still remain
    //   outside the public wrapper.
    // - Field/Storage Mapping: Scalar values are stored directly on the EnergyPlus object while the owned child equipment and node wiring are
    //   represented through explicit child-object state and transient epmodel nodes.
    // - Evidence: `src/model/ZoneHVACEnergyRecoveryVentilator.hpp`, `src/model/ZoneHVACEnergyRecoveryVentilator.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateZoneHVACEnergyRecoveryVentilator.cpp`, and `src/epmodel/test/ZoneHVACEnergyRecoveryVentilator_GTest.cpp`.
    // - Remaining Parity Work: Expose any remaining relationship helpers only if the canonical model surface still needs them as public
    //   epmodel APIs.

    Schedule availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);

    HVACComponent heatExchanger() const;
    bool setHeatExchanger(const HVACComponent& heatExchanger);

    boost::optional<double> supplyAirFlowRate() const;
    bool setSupplyAirFlowRate(double supplyAirFlowRate);
    bool isSupplyAirFlowRateAutosized() const;
    void autosizeSupplyAirFlowRate();

    boost::optional<double> exhaustAirFlowRate() const;
    bool setExhaustAirFlowRate(double exhaustAirFlowRate);
    bool isExhaustAirFlowRateAutosized() const;
    void autosizeExhaustAirFlowRate();

    HVACComponent supplyAirFan() const;
    bool setSupplyAirFan(const HVACComponent& supplyAirFan);

    HVACComponent exhaustAirFan() const;
    bool setExhaustAirFan(const HVACComponent& exhaustAirFan);

    boost::optional<ZoneHVACEnergyRecoveryVentilatorController> controller() const;
    bool setController(const ZoneHVACEnergyRecoveryVentilatorController& controller);
    void resetController();

    double ventilationRateperUnitFloorArea() const;
    bool setVentilationRateperUnitFloorArea(double ventilationRateperUnitFloorArea);

    double ventilationRateperOccupant() const;
    bool setVentilationRateperOccupant(double ventilationRateperOccupant);

    boost::optional<Node> outdoorAirNode() const;
    boost::optional<Node> supplyAirFanInletNode() const;
    boost::optional<Node> exhaustAirFanInletNode() const;
    boost::optional<Node> reliefAirNode() const;

    std::vector<ModelObject> children() const;

   protected:
    using ImplType = detail::ZoneHVACEnergyRecoveryVentilator_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ZoneHVACEnergyRecoveryVentilator(std::shared_ptr<detail::ZoneHVACEnergyRecoveryVentilator_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_ZONEHVACENERGYRECOVERYVENTILATOR_HPP
