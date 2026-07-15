/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AirflowNetworkDistributionComponentFan.hpp"
#include "AirflowNetworkDistributionComponentFan_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  AirflowNetworkDistributionComponentFan::AirflowNetworkDistributionComponentFan(const Model& model)
    : ModelObject(AirflowNetworkDistributionComponentFan::iddObjectType(), model) {}

  AirflowNetworkDistributionComponentFan::AirflowNetworkDistributionComponentFan(
    std::shared_ptr<detail::AirflowNetworkDistributionComponentFan_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType AirflowNetworkDistributionComponentFan::iddObjectType() {
    return IddObjectType::AirflowNetwork_Distribution_Component_Fan;
  }

}  // namespace epmodel
}  // namespace openstudio
