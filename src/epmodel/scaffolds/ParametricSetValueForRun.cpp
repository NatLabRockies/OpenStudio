/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "scaffolds/ParametricSetValueForRun.hpp"
#include "scaffolds/ParametricSetValueForRun_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

ParametricSetValueForRun::ParametricSetValueForRun(const Model& model) : ModelObject(ParametricSetValueForRun::iddObjectType(), model) {}

ParametricSetValueForRun::ParametricSetValueForRun(std::shared_ptr<detail::ParametricSetValueForRun_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType ParametricSetValueForRun::iddObjectType() {
  return IddObjectType::Parametric_SetValueForRun;
}

}  // namespace epmodel
}  // namespace openstudio
