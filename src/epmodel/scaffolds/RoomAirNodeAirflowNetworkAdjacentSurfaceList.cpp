/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "RoomAirNodeAirflowNetworkAdjacentSurfaceList.hpp"
#include "RoomAirNodeAirflowNetworkAdjacentSurfaceList_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  RoomAirNodeAirflowNetworkAdjacentSurfaceList::RoomAirNodeAirflowNetworkAdjacentSurfaceList(const Model& model)
    : ModelObject(RoomAirNodeAirflowNetworkAdjacentSurfaceList::iddObjectType(), model) {}

  RoomAirNodeAirflowNetworkAdjacentSurfaceList::RoomAirNodeAirflowNetworkAdjacentSurfaceList(
    std::shared_ptr<detail::RoomAirNodeAirflowNetworkAdjacentSurfaceList_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType RoomAirNodeAirflowNetworkAdjacentSurfaceList::iddObjectType() {
    return IddObjectType::RoomAir_Node_AirflowNetwork_AdjacentSurfaceList;
  }

}  // namespace epmodel
}  // namespace openstudio
