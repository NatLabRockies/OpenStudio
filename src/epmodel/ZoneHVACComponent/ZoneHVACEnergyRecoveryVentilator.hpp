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
  }  // namespace detail

/** \brief An energy-recovery ventilator serving a thermal zone.
 *
 * \par EnergyPlus object
 * \epobject{group-zone-forced-air-units.html#zonehvacenergyrecoveryventilator,ZoneHVAC:EnergyRecoveryVentilator}
 *
 * \par Important behavior
 * The heat exchanger and supply/exhaust fans share a parent-owned dual-path topology; EPModel exposes outdoor-air, supply-fan-inlet, exhaust-fan-inlet, and relief-air node roles.
 *
 * \par OpenStudio Model API
 * The corresponding OpenStudio Model class is <code>openstudio::model::ZoneHVACEnergyRecoveryVentilator</code>.
 * EPModel adds the explicit fan-inlet, outdoor-air, exhaust, and relief node
 * accessors; Model additionally exposes autosized supply/exhaust flow queries.
 *
 * \par Known limitations
 * Availability-manager relationships and SQL-backed autosized flow results are not exposed.
 */
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
