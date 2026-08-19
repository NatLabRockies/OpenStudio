/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVAC_EXHAUSTCONTROL_HPP
#define EPMODEL_ZONEHVAC_EXHAUSTCONTROL_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <boost/optional.hpp>
#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class AirLoopHVACExhaustSystem;
  class Model;
  class Node;
  class Schedule;
  class ThermalZone;

  namespace detail {
    class ZoneHVACExhaustControl_Impl;
  }

  /** \brief Represents controlled exhaust flow from a thermal zone to a central exhaust system.
   *
   * \par EnergyPlus object
   * \epobject{group-air-path.html#zonehvacexhaustcontrol,ZoneHVAC:ExhaustControl}
   *
   * \par Important behavior
   * A newly constructed control uses <code>Scheduled</code> flow control and
   * an autosized design exhaust flow rate. Its typed relationship methods
   * resolve the availability schedule, zone, inlet and outlet nodes, optional
   * supply node or node list, and exhaust schedules. Exhaust-system ownership
   * is derived from the outlet node's membership in an
   * <code>AirLoopHVAC:ZoneMixer</code>; zone registration, mixer routing, and
   * private-node cleanup are maintained by
   * <code>AirLoopHVACExhaustSystem</code>.
   *
   * \par OpenStudio Model API
   * OpenStudio Model has no public wrapper for
   * <code>ZoneHVAC:ExhaustControl</code>. This wrapper is new to the EPModel
   * API.
   *
   * \par Known limitations
   * Use <code>AirLoopHVACExhaustSystem::addZone()</code> to create and attach a
   * control when the zone is part of a central exhaust system. Standalone
   * removal is rejected when the control's inlet or outlet nodes have shared,
   * duplicate, or external claims that cannot be removed safely. Ownership
   * lookup also returns no system when an outlet is claimed by more than one
   * exhaust-system mixer.
   */
  class EPMODEL_API ZoneHVACExhaustControl : public ModelObject
  {
   public:
    explicit ZoneHVACExhaustControl(const Model& model);

    virtual ~ZoneHVACExhaustControl() override = default;
    ZoneHVACExhaustControl(const ZoneHVACExhaustControl& other) = default;
    ZoneHVACExhaustControl(ZoneHVACExhaustControl&& other) = default;
    ZoneHVACExhaustControl& operator=(const ZoneHVACExhaustControl&) = default;
    ZoneHVACExhaustControl& operator=(ZoneHVACExhaustControl&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> flowControlTypeValues();

    boost::optional<Schedule> availabilitySchedule() const;
    boost::optional<ThermalZone> thermalZone() const;
    boost::optional<Node> inletNode() const;
    boost::optional<Node> outletNode() const;

    std::string flowControlType() const;
    bool isFlowControlTypeDefaulted() const;
    bool setFlowControlType(const std::string& flowControlType);
    void resetFlowControlType();

    boost::optional<double> designExhaustFlowRate() const;
    bool isDesignExhaustFlowRateAutosized() const;
    bool setDesignExhaustFlowRate(double designExhaustFlowRate);
    void autosizeDesignExhaustFlowRate();
    void resetDesignExhaustFlowRate();

    boost::optional<Schedule> exhaustFlowFractionSchedule() const;
    boost::optional<ModelObject> supplyNodeorNodeList() const;
    boost::optional<Schedule> minimumZoneTemperatureLimitSchedule() const;
    boost::optional<Schedule> minimumExhaustFlowFractionSchedule() const;
    boost::optional<Schedule> balancedExhaustFractionSchedule() const;
    boost::optional<AirLoopHVACExhaustSystem> airLoopHVACExhaustSystem() const;

   protected:
    using ImplType = detail::ZoneHVACExhaustControl_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ZoneHVACExhaustControl(std::shared_ptr<detail::ZoneHVACExhaustControl_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
