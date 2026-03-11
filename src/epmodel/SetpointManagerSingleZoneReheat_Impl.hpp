/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGERSINGLEZONEREHEAT_IMPL_HPP
#define EPMODEL_SETPOINTMANAGERSINGLEZONEREHEAT_IMPL_HPP

#include "SetpointManager_Impl.hpp"

namespace openstudio {
namespace epmodel {
class Node;
class ThermalZone;
namespace detail {

class EPMODEL_API SetpointManagerSingleZoneReheat_Impl : public SetpointManager_Impl
{
 public:
  using SetpointManager_Impl::SetpointManager_Impl;
  virtual ~SetpointManagerSingleZoneReheat_Impl() override = default;

  bool addToNode(Node& node) override;
  bool setControlZone(const ThermalZone& thermalZone);

 protected:
  unsigned setpointNodeFieldIndex() const override;
  unsigned controlVariableFieldIndex() const override;

  void doCanonicalize(LoadContext& context) override;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
