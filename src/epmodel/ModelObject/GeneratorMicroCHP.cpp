/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "GeneratorMicroCHP.hpp"
#include "GeneratorMicroCHP_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

GeneratorMicroCHP::GeneratorMicroCHP(const Model& model) : ModelObject(GeneratorMicroCHP::iddObjectType(), model) {}

GeneratorMicroCHP::GeneratorMicroCHP(std::shared_ptr<detail::GeneratorMicroCHP_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType GeneratorMicroCHP::iddObjectType() {
  return IddObjectType::Generator_MicroCHP;
}

}  // namespace epmodel
}  // namespace openstudio
