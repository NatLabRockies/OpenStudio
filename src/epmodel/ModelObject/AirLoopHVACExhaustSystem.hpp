/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRLOOPHVACEXHAUSTSYSTEM_HPP
#define EPMODEL_AIRLOOPHVACEXHAUSTSYSTEM_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <boost/optional.hpp>
#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class AirLoopHVACZoneMixer;
  class FanComponentModel;
  class FanSystemModel;
  class HVACComponent;
  class Model;
  class ThermalZone;
  class ZoneHVACExhaustControl;

  namespace detail {
    class AirLoopHVACExhaustSystem_Impl;
  }

  /** \brief Represents a central exhaust system serving one or more thermal zones.
   *
   * \par EnergyPlus object
   * \epobject{group-air-path.html#airloophvacexhaustsystem,AirLoopHVAC:ExhaustSystem}, together with its required
   * \epobject{group-air-path.html#airloophvaczonemixer,AirLoopHVAC:ZoneMixer} and central fan.
   *
   * \par Important behavior
   * The fan constructors accept an unconnected
   * <code>Fan:SystemModel</code> or <code>Fan:ComponentModel</code> and create
   * the mixer and connecting nodes needed to route exhaust to that fan.
   * <code>addZone()</code> registers the zone exhaust inlet, adds the control's
   * outlet to the mixer, and returns a <code>ZoneHVACExhaustControl</code>.
   * <code>zoneHVACExhaustControls()</code> reports controls in the order of
   * the mixer inlets. Removing a system or one of its controls removes the
   * topology owned by the system and disconnects, but does not remove, the
   * caller-provided fan.
   *
   * \par OpenStudio Model API
   * OpenStudio Model has no public wrapper for
   * <code>AirLoopHVAC:ExhaustSystem</code>. This wrapper is new to the EPModel
   * API.
   *
   * \par Known limitations
   * A zone can be added only when its exhaust-node registration can be
   * maintained exclusively; shared <code>NodeList</code> registrations are
   * rejected. The fan constructors also reject fans from another model or
   * fans that are already connected. A system created with the model-only
   * constructor has no automatically created fan or mixer and must be wired
   * before it can add zones.
   */
  class EPMODEL_API AirLoopHVACExhaustSystem : public ModelObject
  {
   public:
    explicit AirLoopHVACExhaustSystem(const Model& model);
    AirLoopHVACExhaustSystem(const Model& model, FanSystemModel& fan);
    AirLoopHVACExhaustSystem(const Model& model, FanComponentModel& fan);

    virtual ~AirLoopHVACExhaustSystem() override = default;
    AirLoopHVACExhaustSystem(const AirLoopHVACExhaustSystem& other) = default;
    AirLoopHVACExhaustSystem(AirLoopHVACExhaustSystem&& other) = default;
    AirLoopHVACExhaustSystem& operator=(const AirLoopHVACExhaustSystem&) = default;
    AirLoopHVACExhaustSystem& operator=(AirLoopHVACExhaustSystem&&) = default;

    static IddObjectType iddObjectType();

    boost::optional<AirLoopHVACZoneMixer> zoneMixer() const;
    boost::optional<HVACComponent> fan() const;
    std::vector<ZoneHVACExhaustControl> zoneHVACExhaustControls() const;
    boost::optional<ZoneHVACExhaustControl> addZone(ThermalZone& thermalZone);
    bool removeZoneHVACExhaustControl(ZoneHVACExhaustControl& control);

   protected:
    using ImplType = detail::AirLoopHVACExhaustSystem_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirLoopHVACExhaustSystem(std::shared_ptr<detail::AirLoopHVACExhaustSystem_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
