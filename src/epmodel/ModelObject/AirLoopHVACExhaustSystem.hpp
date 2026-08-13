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

    // Schema Alignment Notes:
    // - Status: Partial Parity. This EnergyPlus-only owner exposes its required persisted relationships and a bounded owning lifecycle.
    // - Canonical Counterpart: None. `AirLoopHVAC:ExhaustSystem` has no same-name openstudio::model wrapper.
    // - Implemented Parity: Typed constructors directly wire a supported central fan behind an owned zone mixer; `addZone` and control removal keep ordered mixer rows, zone exhaust-node registration, private nodes, persistence, and reverse ownership coherent. The required relationships remain available as read-only typed views.
    // - Documented Delta: The schema/import Model constructor remains topology-incomplete by design. The owning lifecycle retains and disconnects the caller-provided fan when the system is removed, and it does not expose independent mixer, fan, or node setters.
    // - Field/Storage Mapping: `Zone Mixer Name` targets `AirLoopHVAC:ZoneMixer`; `Fan Object Type` discriminates the `Fan Name` target between `Fan:SystemModel` and `Fan:ComponentModel`.
    // - Evidence: `resources/energyplus/ProposedEnergy+.idd`, `src/epmodel/test/AirLoopHVACExhaustSystem_GTest.cpp`, and `resources/Examples/compact_osw/epmodel_central_exhaust_small_office_idf.osw`.
    // - Remaining Parity Work: Broaden malformed-import canonicalization only from observed cases.
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
