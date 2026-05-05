/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AirflowNetworkIntraZoneNode.hpp"
#include "AirflowNetworkIntraZoneNode_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/AirflowNetwork_IntraZone_Node_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  AirflowNetworkIntraZoneNode::AirflowNetworkIntraZoneNode(const Model& model) : ModelObject(AirflowNetworkIntraZoneNode::iddObjectType(), model) {}

  AirflowNetworkIntraZoneNode::AirflowNetworkIntraZoneNode(std::shared_ptr<detail::AirflowNetworkIntraZoneNode_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType AirflowNetworkIntraZoneNode::iddObjectType() {
    return IddObjectType::AirflowNetwork_IntraZone_Node;
  }

  double AirflowNetworkIntraZoneNode::nodeHeight() const {
    return getImpl<detail::AirflowNetworkIntraZoneNode_Impl>()->nodeHeight();
  }

  bool AirflowNetworkIntraZoneNode::isNodeHeightDefaulted() const {
    return getImpl<detail::AirflowNetworkIntraZoneNode_Impl>()->isNodeHeightDefaulted();
  }

  bool AirflowNetworkIntraZoneNode::setNodeHeight(double nodeHeight) {
    return getImpl<detail::AirflowNetworkIntraZoneNode_Impl>()->setNodeHeight(nodeHeight);
  }

  void AirflowNetworkIntraZoneNode::resetNodeHeight() {
    getImpl<detail::AirflowNetworkIntraZoneNode_Impl>()->resetNodeHeight();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double AirflowNetworkIntraZoneNode_Impl::nodeHeight() const {
      const auto value = getDouble(openstudio::AirflowNetwork_IntraZone_NodeFields::NodeHeight, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirflowNetworkIntraZoneNode_Impl::isNodeHeightDefaulted() const {
      return isEmpty(openstudio::AirflowNetwork_IntraZone_NodeFields::NodeHeight);
    }

    bool AirflowNetworkIntraZoneNode_Impl::setNodeHeight(double nodeHeight) {
      const bool result = setDouble(openstudio::AirflowNetwork_IntraZone_NodeFields::NodeHeight, nodeHeight);
      OS_ASSERT(result);
      return result;
    }

    void AirflowNetworkIntraZoneNode_Impl::resetNodeHeight() {
      OS_ASSERT(setString(openstudio::AirflowNetwork_IntraZone_NodeFields::NodeHeight, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
