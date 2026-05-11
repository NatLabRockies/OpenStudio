/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ConstructionBase/ConstructionBase.hpp"
#include "ConstructionBase/ConstructionBase_Impl.hpp"

namespace openstudio {
namespace epmodel {

  ConstructionBase::ConstructionBase(IddObjectType type, const Model& model) : ResourceObject(type, model) {}

  ConstructionBase::ConstructionBase(std::shared_ptr<detail::ConstructionBase_Impl> impl) : ResourceObject(std::move(impl)) {}

}  // namespace epmodel
}  // namespace openstudio
