/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRFLOWNETWORKDISTRIBUTIONNODE_HPP
#define EPMODEL_AIRFLOWNETWORKDISTRIBUTIONNODE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class AirflowNetworkDistributionNode_Impl;
}

class EPMODEL_API AirflowNetworkDistributionNode : public ModelObject
{
 public:
  explicit AirflowNetworkDistributionNode(const Model& model);

  virtual ~AirflowNetworkDistributionNode() override = default;
  AirflowNetworkDistributionNode(const AirflowNetworkDistributionNode& other) = default;
  AirflowNetworkDistributionNode(AirflowNetworkDistributionNode&& other) = default;
  AirflowNetworkDistributionNode& operator=(const AirflowNetworkDistributionNode&) = default;
  AirflowNetworkDistributionNode& operator=(AirflowNetworkDistributionNode&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> componentObjectTypeorNodeTypeValues();

  // Schema Alignment Notes:
  // - API: This no-counterpart epmodel type uses IDD-derived class/accessor naming.
  // - Field Mapping: componentObjectTypeorNodeType and nodeHeight map directly to EnergyPlus
  //   AirflowNetwork:Distribution:Node scalar fields.
  // - Field Mapping: Component Name or Node Name is a relationship-like target-link field and is
  //   intentionally excluded from scalar accessors.
  // - ForwardTranslator evidence: translateAirflowNetworkDistributionNode writes
  //   Component Object Type or Node Type and Node Height directly.
  // - TODO(parity): Add relationship APIs after scalar scaffold saturation.
  std::string componentObjectTypeorNodeType() const;
  bool isComponentObjectTypeorNodeTypeDefaulted() const;
  bool setComponentObjectTypeorNodeType(const std::string& componentObjectTypeorNodeType);
  void resetComponentObjectTypeorNodeType();

  double nodeHeight() const;
  bool isNodeHeightDefaulted() const;
  bool setNodeHeight(double nodeHeight);
  void resetNodeHeight();

 protected:
  using ImplType = detail::AirflowNetworkDistributionNode_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit AirflowNetworkDistributionNode(std::shared_ptr<detail::AirflowNetworkDistributionNode_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
