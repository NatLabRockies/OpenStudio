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
