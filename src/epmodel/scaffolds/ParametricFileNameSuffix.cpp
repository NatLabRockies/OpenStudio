/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "scaffolds/ParametricFileNameSuffix.hpp"
#include "scaffolds/ParametricFileNameSuffix_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

ParametricFileNameSuffix::ParametricFileNameSuffix(const Model& model) : ModelObject(ParametricFileNameSuffix::iddObjectType(), model) {}

ParametricFileNameSuffix::ParametricFileNameSuffix(std::shared_ptr<detail::ParametricFileNameSuffix_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType ParametricFileNameSuffix::iddObjectType() {
  return IddObjectType::Parametric_FileNameSuffix;
}

}  // namespace epmodel
}  // namespace openstudio
