/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTOAIRCOMPONENT_IMPL_HPP
#define EPMODEL_AIRTOAIRCOMPONENT_IMPL_HPP

#include "HVACComponent/HVACComponent_Impl.hpp"

namespace openstudio {
namespace epmodel {

class ModelObject;
class Node;
class AirLoopHVACOutdoorAirSystem;

namespace detail {

class EPMODEL_API AirToAirComponent_Impl : public HVACComponent_Impl
{
 public:
  using HVACComponent_Impl::HVACComponent_Impl;
  virtual ~AirToAirComponent_Impl() override = default;

  virtual unsigned primaryAirInletPort() const;
  virtual unsigned primaryAirOutletPort() const;
  virtual unsigned secondaryAirInletPort() const;
  virtual unsigned secondaryAirOutletPort() const;

  boost::optional<ModelObject> primaryAirInletModelObject() const;
  boost::optional<ModelObject> primaryAirOutletModelObject() const;
  boost::optional<ModelObject> secondaryAirInletModelObject() const;
  boost::optional<ModelObject> secondaryAirOutletModelObject() const;

  bool addToNode(Node& node) override;
  void disconnect() override;
  std::vector<IdfObject> remove() override;
  void doCanonicalize(LoadContext& context) override;

 private:
  bool addToOutdoorAirSystem(AirLoopHVACOutdoorAirSystem& oaSystem, Node& node);
  bool removeFromOutdoorAirSystem(AirLoopHVACOutdoorAirSystem& oaSystem);
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
