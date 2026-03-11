/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include "SurfacePropertyLocalEnvironment.hpp"
#include "SurfacePropertyLocalEnvironment_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  SurfacePropertyLocalEnvironment::SurfacePropertyLocalEnvironment(const Model& model)
    : ModelObject(SurfacePropertyLocalEnvironment::iddObjectType(), model) {}

  SurfacePropertyLocalEnvironment::SurfacePropertyLocalEnvironment(std::shared_ptr<detail::SurfacePropertyLocalEnvironment_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType SurfacePropertyLocalEnvironment::iddObjectType() {
    return IddObjectType::SurfaceProperty_LocalEnvironment;
  }

}  // namespace epmodel
}  // namespace openstudio
