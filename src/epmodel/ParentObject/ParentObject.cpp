/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ParentObject/ParentObject.hpp"
#include "ParentObject/ParentObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  ParentObject::ParentObject(IddObjectType type, const Model& model, bool fastName, bool isTransient)
    : ModelObject(type, model, fastName, isTransient) {}

  ParentObject::ParentObject(std::shared_ptr<ImplType> impl) : ModelObject(std::move(impl)) {}

  std::vector<ModelObject> ParentObject::children() const {
    return {};
  }

}  // namespace epmodel
}  // namespace openstudio
