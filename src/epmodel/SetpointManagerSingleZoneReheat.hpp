/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGERSINGLEZONEREHEAT_HPP
#define EPMODEL_SETPOINTMANAGERSINGLEZONEREHEAT_HPP

#include "EPModelAPI.hpp"
#include "SetpointManager.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;
class ThermalZone;

namespace detail {
class SetpointManagerSingleZoneReheat_Impl;
}

class EPMODEL_API SetpointManagerSingleZoneReheat : public SetpointManager
{
 public:
  explicit SetpointManagerSingleZoneReheat(const Model& model);

  virtual ~SetpointManagerSingleZoneReheat() override = default;
  SetpointManagerSingleZoneReheat(const SetpointManagerSingleZoneReheat& other) = default;
  SetpointManagerSingleZoneReheat(SetpointManagerSingleZoneReheat&& other) = default;
  SetpointManagerSingleZoneReheat& operator=(const SetpointManagerSingleZoneReheat&) = default;
  SetpointManagerSingleZoneReheat& operator=(SetpointManagerSingleZoneReheat&&) = default;

  static IddObjectType iddObjectType();

  double minimumSupplyAirTemperature() const;
  double maximumSupplyAirTemperature() const;
  boost::optional<ThermalZone> controlZone() const;

 protected:
  using ImplType = detail::SetpointManagerSingleZoneReheat_Impl;

  friend class Model;

  explicit SetpointManagerSingleZoneReheat(std::shared_ptr<detail::SetpointManagerSingleZoneReheat_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
