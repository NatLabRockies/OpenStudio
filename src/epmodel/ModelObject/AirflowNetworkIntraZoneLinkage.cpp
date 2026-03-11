/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AirflowNetworkIntraZoneLinkage.hpp"
#include "AirflowNetworkIntraZoneLinkage_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

AirflowNetworkIntraZoneLinkage::AirflowNetworkIntraZoneLinkage(const Model& model)
  : ModelObject(AirflowNetworkIntraZoneLinkage::iddObjectType(), model) {}

AirflowNetworkIntraZoneLinkage::AirflowNetworkIntraZoneLinkage(std::shared_ptr<detail::AirflowNetworkIntraZoneLinkage_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType AirflowNetworkIntraZoneLinkage::iddObjectType() {
  return IddObjectType::AirflowNetwork_IntraZone_Linkage;
}

}  // namespace epmodel
}  // namespace openstudio
