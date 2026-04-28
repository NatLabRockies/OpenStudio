/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ROOMAIRNODEAIRFLOWNETWORKADJACENTSURFACELIST_HPP
#define EPMODEL_ROOMAIRNODEAIRFLOWNETWORKADJACENTSURFACELIST_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class RoomAirNodeAirflowNetworkAdjacentSurfaceList_Impl;
  }

  class EPMODEL_API RoomAirNodeAirflowNetworkAdjacentSurfaceList : public ModelObject
  {
   public:
    explicit RoomAirNodeAirflowNetworkAdjacentSurfaceList(const Model& model);

    virtual ~RoomAirNodeAirflowNetworkAdjacentSurfaceList() override = default;
    RoomAirNodeAirflowNetworkAdjacentSurfaceList(const RoomAirNodeAirflowNetworkAdjacentSurfaceList& other) = default;
    RoomAirNodeAirflowNetworkAdjacentSurfaceList(RoomAirNodeAirflowNetworkAdjacentSurfaceList&& other) = default;
    RoomAirNodeAirflowNetworkAdjacentSurfaceList& operator=(const RoomAirNodeAirflowNetworkAdjacentSurfaceList&) = default;
    RoomAirNodeAirflowNetworkAdjacentSurfaceList& operator=(RoomAirNodeAirflowNetworkAdjacentSurfaceList&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: This type has no openstudio::model counterpart, so the class name and accessor surface naming mirror the
    //   IDD.
    // - Field Mapping: Name is still supplied via the ModelObject base scalar APIs, while the extensible Surface Name
    //   field is an object-list relationship (AllHeatTranSurfNames) and therefore excluded from this scalar-only pass.
    // - TODO(parity): Add typed helpers for the surface reference list once relationship scaffolding is in scope.

   protected:
    using ImplType = detail::RoomAirNodeAirflowNetworkAdjacentSurfaceList_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit RoomAirNodeAirflowNetworkAdjacentSurfaceList(std::shared_ptr<detail::RoomAirNodeAirflowNetworkAdjacentSurfaceList_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
