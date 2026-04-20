/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "RoomAirSettingsAirflowNetwork.hpp"
#include "RoomAirSettingsAirflowNetwork_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

RoomAirSettingsAirflowNetwork::RoomAirSettingsAirflowNetwork(const Model& model)
  : ModelObject(RoomAirSettingsAirflowNetwork::iddObjectType(), model) {}

RoomAirSettingsAirflowNetwork::RoomAirSettingsAirflowNetwork(std::shared_ptr<detail::RoomAirSettingsAirflowNetwork_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType RoomAirSettingsAirflowNetwork::iddObjectType() {
  return IddObjectType::RoomAirSettings_AirflowNetwork;
}

}  // namespace epmodel
}  // namespace openstudio
