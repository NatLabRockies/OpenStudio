/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "RoomAirNodeAirflowNetworkInternalGains.hpp"
#include "RoomAirNodeAirflowNetworkInternalGains_Impl.hpp"

#include "Model.hpp"

namespace openstudio {
namespace epmodel {

  RoomAirNodeAirflowNetworkInternalGains::RoomAirNodeAirflowNetworkInternalGains(const Model& model)
    : ModelObject(RoomAirNodeAirflowNetworkInternalGains::iddObjectType(), model) {}

  RoomAirNodeAirflowNetworkInternalGains::RoomAirNodeAirflowNetworkInternalGains(
    std::shared_ptr<detail::RoomAirNodeAirflowNetworkInternalGains_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType RoomAirNodeAirflowNetworkInternalGains::iddObjectType() {
    return IddObjectType::RoomAir_Node_AirflowNetwork_InternalGains;
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
