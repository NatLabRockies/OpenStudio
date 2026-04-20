/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "scaffolds/ParametricRunControl.hpp"
#include "scaffolds/ParametricRunControl_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

ParametricRunControl::ParametricRunControl(const Model& model) : ModelObject(ParametricRunControl::iddObjectType(), model) {}

ParametricRunControl::ParametricRunControl(std::shared_ptr<detail::ParametricRunControl_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType ParametricRunControl::iddObjectType() {
  return IddObjectType::Parametric_RunControl;
}

}  // namespace epmodel
}  // namespace openstudio
