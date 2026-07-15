/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ResourceObject/ResourceObject.hpp"
#include "ResourceObject/ResourceObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  ResourceObject::ResourceObject(IddObjectType type, const Model& model, bool fastName, bool isTransient)
    : ModelObject(type, model, fastName, isTransient) {}

  ResourceObject::ResourceObject(std::shared_ptr<ImplType> impl) : ModelObject(std::static_pointer_cast<detail::ModelObject_Impl>(std::move(impl))) {}

}  // namespace epmodel
}  // namespace openstudio
