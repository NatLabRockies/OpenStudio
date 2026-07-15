/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SiteVariableLocation.hpp"
#include "SiteVariableLocation_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  SiteVariableLocation::SiteVariableLocation(const Model& model) : ModelObject(SiteVariableLocation::iddObjectType(), model) {}

  SiteVariableLocation::SiteVariableLocation(std::shared_ptr<detail::SiteVariableLocation_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType SiteVariableLocation::iddObjectType() {
    return IddObjectType::Site_VariableLocation;
  }

}  // namespace epmodel
}  // namespace openstudio
