/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRFLOWNETWORKDISTRIBUTIONNODE_IMPL_HPP
#define EPMODEL_AIRFLOWNETWORKDISTRIBUTIONNODE_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API AirflowNetworkDistributionNode_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~AirflowNetworkDistributionNode_Impl() override = default;

  std::string componentObjectTypeorNodeType() const;
  bool isComponentObjectTypeorNodeTypeDefaulted() const;
  bool setComponentObjectTypeorNodeType(const std::string& componentObjectTypeorNodeType);
  void resetComponentObjectTypeorNodeType();

  double nodeHeight() const;
  bool isNodeHeightDefaulted() const;
  bool setNodeHeight(double nodeHeight);
  void resetNodeHeight();

  std::vector<std::string> componentObjectTypeorNodeTypeValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
