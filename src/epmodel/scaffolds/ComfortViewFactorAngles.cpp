/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ComfortViewFactorAngles.hpp"
#include "ComfortViewFactorAngles_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

ComfortViewFactorAngles::ComfortViewFactorAngles(const Model& model) : ModelObject(ComfortViewFactorAngles::iddObjectType(), model) {}

ComfortViewFactorAngles::ComfortViewFactorAngles(std::shared_ptr<detail::ComfortViewFactorAngles_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType ComfortViewFactorAngles::iddObjectType() {
  return IddObjectType::ComfortViewFactorAngles;
}

}  // namespace epmodel
}  // namespace openstudio
