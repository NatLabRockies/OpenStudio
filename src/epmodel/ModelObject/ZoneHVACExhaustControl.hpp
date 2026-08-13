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

    // Schema Alignment Notes:
    // - Status: Partial Parity. This EnergyPlus-only flow-control object exposes its persisted state and read-only topology relationships.
    // - Canonical Counterpart: None. `ZoneHVAC:ExhaustControl` has no same-name openstudio::model wrapper.
    // - Implemented Parity: Direct scalar fields, schedule targets, zone and node targets, unique central-exhaust-system reverse ownership, and owner-controlled add/remove lifecycle are available without exposing relationship mutators on the control.
    // - Documented Delta: Zone registration, central mixer routing, and private-node cleanup are intentionally mutated only through `AirLoopHVACExhaustSystem`; the control itself exposes read-only topology relationships.
    // - Field/Storage Mapping: Zone, inlet/outlet nodes, optional supply node or NodeList, and schedules map directly to their EnergyPlus relationship fields; central-system ownership is derived from the control outlet's unique zone-mixer inlet membership.
    // - Evidence: `resources/energyplus/ProposedEnergy+.idd`, `src/epmodel/test/ZoneHVACExhaustControl_GTest.cpp`, and `resources/Examples/compact_osw/epmodel_central_exhaust_small_office_idf.osw`.
    // - Remaining Parity Work: Characterize movement or malformed-import repair only when a representative workflow requires them.
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
