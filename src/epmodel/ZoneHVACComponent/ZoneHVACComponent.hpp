/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACCOMPONENT_HPP
#define EPMODEL_ZONEHVACCOMPONENT_HPP

#include "EPModelAPI.hpp"
#include "HVACComponent/HVACComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class AirLoopHVACReturnPlenum;
  class AirLoopHVAC;
  class Model;
  class Node;
  class ThermalZone;

  namespace detail {
    class ZoneHVACComponent_Impl;
  }

  // ZoneHVACComponent is the shared base for equipment that conditions a single
  // zone. The public surface mirrors model::ZoneHVACComponent even though epmodel
  // stores the underlying EnergyPlus zone equipment topology through
  // ZoneHVAC:EquipmentConnections and ZoneHVAC:EquipmentList objects.
  class EPMODEL_API ZoneHVACComponent : public HVACComponent
  {
   public:
    virtual ~ZoneHVACComponent() override = default;
    ZoneHVACComponent(const ZoneHVACComponent& other) = default;
    ZoneHVACComponent(ZoneHVACComponent&& other) = default;
    ZoneHVACComponent& operator=(const ZoneHVACComponent&) = default;
    ZoneHVACComponent& operator=(ZoneHVACComponent&&) = default;

    // Schema Alignment Notes:
    // - Status: Partial Parity. The shared zone-equipment topology contract is present, but the canonical base convenience surface is still somewhat broader than epmodel's wrapper.
    // - Canonical Counterpart: openstudio::model::ZoneHVACComponent.
    // - Implemented Parity: Inlet/outlet port and node accessors, `thermalZone`, `addToThermalZone`, `removeFromThermalZone`, return-plenum wiring, `addToNode`, `airLoopHVAC`, `removeFromAirLoopHVAC`, and air-side model-object traversal preserve the canonical zone-equipment topology contract.
    // - Documented Delta: The epmodel base stays focused on zone-equipment attachment and loop plumbing; additional convenience remains on derived wrappers or is still omitted while relationship coverage matures.
    // - Field/Storage Mapping: Public zone-equipment behavior is resolved through EnergyPlus `ZoneHVAC:EquipmentConnections` and `ZoneHVAC:EquipmentList` storage instead of OpenStudio-side connection objects.
    // - Evidence: `src/model/ZoneHVACComponent.hpp` and `src/model/ZoneHVACComponent.cpp` define the canonical shared topology behavior exercised by the concrete zone-equipment wrappers.
    // - Remaining Parity Work: Add any missing shared zone-equipment convenience only if it is needed across multiple derived wrappers after the family normalization pass.
    unsigned inletPort() const;
    boost::optional<Node> inletNode() const;

    unsigned outletPort() const;
    boost::optional<Node> outletNode() const;

    virtual boost::optional<ThermalZone> thermalZone() const;

    bool addToThermalZone(ThermalZone& thermalZone);
    void removeFromThermalZone();

    bool setReturnPlenum(const ThermalZone& plenumZone);
    void removeReturnPlenum();
    boost::optional<AirLoopHVACReturnPlenum> returnPlenum() const;

    bool addToNode(Node& node);
    boost::optional<AirLoopHVAC> airLoopHVAC() const;
    bool removeFromAirLoopHVAC();

    boost::optional<ModelObject> airInletModelObject() const;
    boost::optional<ModelObject> airOutletModelObject() const;

   protected:
    using ImplType = detail::ZoneHVACComponent_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ZoneHVACComponent(std::shared_ptr<detail::ZoneHVACComponent_Impl> impl);
    ZoneHVACComponent(IddObjectType type, const Model& model);
  };

  using OptionalZoneHVACComponent = boost::optional<ZoneHVACComponent>;

}  // namespace epmodel
}  // namespace openstudio

#endif
