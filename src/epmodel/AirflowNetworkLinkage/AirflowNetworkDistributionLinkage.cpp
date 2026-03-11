/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AirflowNetworkLinkage/AirflowNetworkDistributionLinkage.hpp"
#include "AirflowNetworkLinkage/AirflowNetworkDistributionLinkage_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

AirflowNetworkDistributionLinkage::AirflowNetworkDistributionLinkage(const Model& model)
  : ModelObject(AirflowNetworkDistributionLinkage::iddObjectType(), model) {}

AirflowNetworkDistributionLinkage::AirflowNetworkDistributionLinkage(std::shared_ptr<detail::AirflowNetworkDistributionLinkage_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType AirflowNetworkDistributionLinkage::iddObjectType() {
  return IddObjectType::AirflowNetwork_Distribution_Linkage;
}

}  // namespace epmodel
}  // namespace openstudio
