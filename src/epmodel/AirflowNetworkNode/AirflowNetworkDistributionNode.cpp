/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AirflowNetworkNode/AirflowNetworkDistributionNode.hpp"
#include "AirflowNetworkNode/AirflowNetworkDistributionNode_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/AirflowNetwork_Distribution_Node_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  AirflowNetworkDistributionNode::AirflowNetworkDistributionNode(const Model& model)
    : ModelObject(AirflowNetworkDistributionNode::iddObjectType(), model) {}

  AirflowNetworkDistributionNode::AirflowNetworkDistributionNode(std::shared_ptr<detail::AirflowNetworkDistributionNode_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType AirflowNetworkDistributionNode::iddObjectType() {
    return IddObjectType::AirflowNetwork_Distribution_Node;
  }

  std::vector<std::string> AirflowNetworkDistributionNode::componentObjectTypeorNodeTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::AirflowNetwork_Distribution_NodeFields::ComponentObjectTypeorNodeType);
  }

  std::string AirflowNetworkDistributionNode::componentObjectTypeorNodeType() const {
    return getImpl<detail::AirflowNetworkDistributionNode_Impl>()->componentObjectTypeorNodeType();
  }

  bool AirflowNetworkDistributionNode::isComponentObjectTypeorNodeTypeDefaulted() const {
    return getImpl<detail::AirflowNetworkDistributionNode_Impl>()->isComponentObjectTypeorNodeTypeDefaulted();
  }

  bool AirflowNetworkDistributionNode::setComponentObjectTypeorNodeType(const std::string& componentObjectTypeorNodeType) {
    return getImpl<detail::AirflowNetworkDistributionNode_Impl>()->setComponentObjectTypeorNodeType(componentObjectTypeorNodeType);
  }

  void AirflowNetworkDistributionNode::resetComponentObjectTypeorNodeType() {
    getImpl<detail::AirflowNetworkDistributionNode_Impl>()->resetComponentObjectTypeorNodeType();
  }

  double AirflowNetworkDistributionNode::nodeHeight() const {
    return getImpl<detail::AirflowNetworkDistributionNode_Impl>()->nodeHeight();
  }

  bool AirflowNetworkDistributionNode::isNodeHeightDefaulted() const {
    return getImpl<detail::AirflowNetworkDistributionNode_Impl>()->isNodeHeightDefaulted();
  }

  bool AirflowNetworkDistributionNode::setNodeHeight(double nodeHeight) {
    return getImpl<detail::AirflowNetworkDistributionNode_Impl>()->setNodeHeight(nodeHeight);
  }

  void AirflowNetworkDistributionNode::resetNodeHeight() {
    getImpl<detail::AirflowNetworkDistributionNode_Impl>()->resetNodeHeight();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string AirflowNetworkDistributionNode_Impl::componentObjectTypeorNodeType() const {
      const auto value = getString(openstudio::AirflowNetwork_Distribution_NodeFields::ComponentObjectTypeorNodeType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirflowNetworkDistributionNode_Impl::isComponentObjectTypeorNodeTypeDefaulted() const {
      return isEmpty(openstudio::AirflowNetwork_Distribution_NodeFields::ComponentObjectTypeorNodeType);
    }

    bool AirflowNetworkDistributionNode_Impl::setComponentObjectTypeorNodeType(const std::string& componentObjectTypeorNodeType) {
      return setString(openstudio::AirflowNetwork_Distribution_NodeFields::ComponentObjectTypeorNodeType, componentObjectTypeorNodeType);
    }

    void AirflowNetworkDistributionNode_Impl::resetComponentObjectTypeorNodeType() {
      OS_ASSERT(setString(openstudio::AirflowNetwork_Distribution_NodeFields::ComponentObjectTypeorNodeType, ""));
    }

    double AirflowNetworkDistributionNode_Impl::nodeHeight() const {
      const auto value = getDouble(openstudio::AirflowNetwork_Distribution_NodeFields::NodeHeight, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirflowNetworkDistributionNode_Impl::isNodeHeightDefaulted() const {
      return isEmpty(openstudio::AirflowNetwork_Distribution_NodeFields::NodeHeight);
    }

    bool AirflowNetworkDistributionNode_Impl::setNodeHeight(double nodeHeight) {
      return setDouble(openstudio::AirflowNetwork_Distribution_NodeFields::NodeHeight, nodeHeight);
    }

    void AirflowNetworkDistributionNode_Impl::resetNodeHeight() {
      OS_ASSERT(setString(openstudio::AirflowNetwork_Distribution_NodeFields::NodeHeight, ""));
    }

    std::vector<std::string> AirflowNetworkDistributionNode_Impl::componentObjectTypeorNodeTypeValues() const {
      return openstudio::epmodel::AirflowNetworkDistributionNode::componentObjectTypeorNodeTypeValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
