/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACCOMPONENT_IMPL_HPP
#define EPMODEL_ZONEHVACCOMPONENT_IMPL_HPP

#include "HVACComponent/HVACComponent_Impl.hpp"

namespace openstudio {
namespace epmodel {

class AirLoopHVACReturnPlenum;
class HVACComponent;
class ModelObject;
class Node;
class ThermalZone;

namespace detail {

// Compound zone HVAC owners like UnitVentilator and FourPipeFanCoil need one
// shared way to treat StraightComponent and WaterToAirComponent children as a
// single serial air path. Keep that type dispatch private here instead of
// spreading it through each owner implementation.
EPMODEL_API bool isContainedAirPathComponent(const HVACComponent& component);
EPMODEL_API unsigned containedAirInletPort(const HVACComponent& component);
EPMODEL_API unsigned containedAirOutletPort(const HVACComponent& component);
EPMODEL_API boost::optional<ModelObject> containedAirOutletModelObject(const HVACComponent& component);

class EPMODEL_API ZoneHVACComponent_Impl : public HVACComponent_Impl
{
 public:
  using HVACComponent_Impl::HVACComponent_Impl;
  virtual ~ZoneHVACComponent_Impl() override = default;

  // The public ZoneHVACComponent API always exposes inlet/outlet ports, but a
  // number of zone devices are equipment-list-only in practice. Those types can
  // inherit the default zero-port behavior until they need a concrete override.
  virtual unsigned inletPort() const;
  virtual unsigned outletPort() const;

  virtual boost::optional<Node> inletNode() const;
  virtual boost::optional<Node> outletNode() const;

  virtual boost::optional<ThermalZone> thermalZone() const;

  virtual bool addToThermalZone(ThermalZone& thermalZone);
  virtual void removeFromThermalZone();

  std::vector<IdfObject> remove() override;

  bool addToNode(Node& node) override;
  boost::optional<AirLoopHVAC> airLoopHVAC() const override;
  bool removeFromAirLoopHVAC();

  boost::optional<ModelObject> airInletModelObject() const;
  boost::optional<ModelObject> airOutletModelObject() const;

  bool setReturnPlenum(const ThermalZone& plenumZone);
  void removeReturnPlenum();
  boost::optional<AirLoopHVACReturnPlenum> returnPlenum() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
