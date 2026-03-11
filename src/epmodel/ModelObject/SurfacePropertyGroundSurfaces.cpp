/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SurfacePropertyGroundSurfaces.hpp"
#include "SurfacePropertyGroundSurfaces_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  SurfacePropertyGroundSurfaces::SurfacePropertyGroundSurfaces(const Model& model)
    : ModelObject(SurfacePropertyGroundSurfaces::iddObjectType(), model) {}

  SurfacePropertyGroundSurfaces::SurfacePropertyGroundSurfaces(std::shared_ptr<detail::SurfacePropertyGroundSurfaces_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType SurfacePropertyGroundSurfaces::iddObjectType() {
    return IddObjectType::SurfaceProperty_GroundSurfaces;
  }

}  // namespace epmodel
}  // namespace openstudio
