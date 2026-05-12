/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Glazing/Glazing.hpp"
#include "Glazing/Glazing_Impl.hpp"

namespace openstudio {
namespace epmodel {

  Glazing::Glazing(IddObjectType type, const Model& model) : FenestrationMaterial(type, model) {}

  Glazing::Glazing(std::shared_ptr<detail::Glazing_Impl> impl) : FenestrationMaterial(std::move(impl)) {}

}  // namespace epmodel
}  // namespace openstudio
