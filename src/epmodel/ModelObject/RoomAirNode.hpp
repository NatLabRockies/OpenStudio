/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ROOMAIRNODE_HPP
#define EPMODEL_ROOMAIRNODE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class RoomAirNode_Impl;
  }

  class EPMODEL_API RoomAirNode : public ModelObject
  {
   public:
    explicit RoomAirNode(const Model& model);

    virtual ~RoomAirNode() override = default;
    RoomAirNode(const RoomAirNode& other) = default;
    RoomAirNode(RoomAirNode&& other) = default;
    RoomAirNode& operator=(const RoomAirNode&) = default;
    RoomAirNode& operator=(RoomAirNode&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> nodeTypeValues();

    // Schema Alignment Notes:
    // - API: RoomAir:Node is a no-counterpart type so the class name and accessors mirror the IDD.
    // - Field Mapping: nodeType maps directly to the RoomAir:Node Node Type choice and heightOfNodalControlVolumeCenter
    //   maps directly to Height of Nodal Control Volume Center.
    // - Field Mapping: Zone Name and Surface Name object-list references are relationship-like and intentionally
    //   excluded from this scalar-only pass.
    // - TODO(parity): Add relationship helpers for zone/surface connections once scalar saturation is complete.
    std::string nodeType() const;
    bool setNodeType(const std::string& nodeType);

    double heightOfNodalControlVolumeCenter() const;
    bool setHeightOfNodalControlVolumeCenter(double heightOfNodalControlVolumeCenter);

   protected:
    using ImplType = detail::RoomAirNode_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit RoomAirNode(std::shared_ptr<detail::RoomAirNode_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
