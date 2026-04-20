/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "RoomAirNode.hpp"
#include "RoomAirNode_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/RoomAir_Node_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  RoomAirNode::RoomAirNode(const Model& model) : ModelObject(RoomAirNode::iddObjectType(), model) {}

  RoomAirNode::RoomAirNode(std::shared_ptr<detail::RoomAirNode_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType RoomAirNode::iddObjectType() {
    return IddObjectType::RoomAir_Node;
  }

  std::vector<std::string> RoomAirNode::nodeTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::RoomAir_NodeFields::NodeType);
  }

  std::string RoomAirNode::nodeType() const {
    return getImpl<detail::RoomAirNode_Impl>()->nodeType();
  }

  bool RoomAirNode::setNodeType(const std::string& nodeType) {
    return getImpl<detail::RoomAirNode_Impl>()->setNodeType(nodeType);
  }

  double RoomAirNode::heightOfNodalControlVolumeCenter() const {
    return getImpl<detail::RoomAirNode_Impl>()->heightOfNodalControlVolumeCenter();
  }

  bool RoomAirNode::setHeightOfNodalControlVolumeCenter(double heightOfNodalControlVolumeCenter) {
    return getImpl<detail::RoomAirNode_Impl>()->setHeightOfNodalControlVolumeCenter(heightOfNodalControlVolumeCenter);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string RoomAirNode_Impl::nodeType() const {
      const auto value = getString(openstudio::RoomAir_NodeFields::NodeType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RoomAirNode_Impl::setNodeType(const std::string& nodeType) {
      return setString(openstudio::RoomAir_NodeFields::NodeType, nodeType);
    }

    double RoomAirNode_Impl::heightOfNodalControlVolumeCenter() const {
      const auto value = getDouble(openstudio::RoomAir_NodeFields::HeightofNodalControlVolumeCenter, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RoomAirNode_Impl::setHeightOfNodalControlVolumeCenter(double heightOfNodalControlVolumeCenter) {
      return setDouble(openstudio::RoomAir_NodeFields::HeightofNodalControlVolumeCenter, heightOfNodalControlVolumeCenter);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
