/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include "SurfacePropertySolarIncidentInside.hpp"
#include "SurfacePropertySolarIncidentInside_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  SurfacePropertySolarIncidentInside::SurfacePropertySolarIncidentInside(const Model& model)
    : ModelObject(SurfacePropertySolarIncidentInside::iddObjectType(), model) {}

  SurfacePropertySolarIncidentInside::SurfacePropertySolarIncidentInside(std::shared_ptr<detail::SurfacePropertySolarIncidentInside_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType SurfacePropertySolarIncidentInside::iddObjectType() {
    return IddObjectType::SurfaceProperty_SolarIncidentInside;
  }

}  // namespace epmodel
}  // namespace openstudio
