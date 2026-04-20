/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "OutputControlSurfaceColorScheme.hpp"
#include "OutputControlSurfaceColorScheme_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

OutputControlSurfaceColorScheme::OutputControlSurfaceColorScheme(const Model& model)
  : ModelObject(OutputControlSurfaceColorScheme::iddObjectType(), model) {}

OutputControlSurfaceColorScheme::OutputControlSurfaceColorScheme(std::shared_ptr<detail::OutputControlSurfaceColorScheme_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType OutputControlSurfaceColorScheme::iddObjectType() {
  return IddObjectType::OutputControl_SurfaceColorScheme;
}

}  // namespace epmodel
}  // namespace openstudio
