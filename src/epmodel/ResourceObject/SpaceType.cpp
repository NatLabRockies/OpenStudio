/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ResourceObject/SpaceType.hpp"
#include "ResourceObject/SpaceType_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  SpaceType::SpaceType(const Model& model) : ModelObject(SpaceType::iddObjectType(), model) {}

  SpaceType::SpaceType(std::shared_ptr<detail::SpaceType_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType SpaceType::iddObjectType() {
    return IddObjectType::SpaceList;
  }

}  // namespace epmodel
}  // namespace openstudio
