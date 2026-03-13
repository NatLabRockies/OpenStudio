/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_RESOURCEOBJECT_HPP
#define EPMODEL_RESOURCEOBJECT_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
  class ResourceObject_Impl;
}

class EPMODEL_API ResourceObject : public ModelObject
{
 public:
  virtual ~ResourceObject() override = default;
  ResourceObject(const ResourceObject& other) = default;
  ResourceObject(ResourceObject&& other) = default;
  ResourceObject& operator=(const ResourceObject&) = default;
  ResourceObject& operator=(ResourceObject&&) = default;

 protected:
  using ImplType = detail::ResourceObject_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  ResourceObject(IddObjectType type, const Model& model, bool fastName = false, bool isTransient = false);
  explicit ResourceObject(std::shared_ptr<ImplType> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
