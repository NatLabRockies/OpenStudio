/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ParametricLogic.hpp"
#include "ParametricLogic_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  ParametricLogic::ParametricLogic(const Model& model) : ModelObject(ParametricLogic::iddObjectType(), model) {}

  ParametricLogic::ParametricLogic(std::shared_ptr<detail::ParametricLogic_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType ParametricLogic::iddObjectType() {
    return IddObjectType::Parametric_Logic;
  }

}  // namespace epmodel
}  // namespace openstudio
