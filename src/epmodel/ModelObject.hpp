/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_MODELOBJECT_HPP
#define EPMODEL_MODELOBJECT_HPP

#include "EPModelAPI.hpp"

#include "../utilities/idd/IddEnums.hpp"
#include "../utilities/idf/WorkspaceObject.hpp"

#include <boost/optional.hpp>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
  class ModelObject_Impl;
}

class EPMODEL_API ModelObject : public openstudio::WorkspaceObject
{
 public:
  virtual ~ModelObject() override = default;
  ModelObject(const ModelObject& other) = default;
  ModelObject(ModelObject&& other) = default;
  ModelObject& operator=(const ModelObject&) = default;
  ModelObject& operator=(ModelObject&&) = default;

  Model model() const;
  static ModelObject create(IddObjectType type, const Model& model, bool fastName = false);
  using openstudio::IdfObject::getImpl;

  template <typename T>
  boost::optional<T> getModelObjectTarget(unsigned index) const {
    boost::optional<T> result;
    auto candidate = getTarget(index);
    if (candidate) {
      result = candidate->template optionalCast<T>();
    }
    return result;
  }

  template <typename T>
  std::vector<T> getModelObjectTargets() const {
    std::vector<T> result;
    auto wos = targets();
    result.reserve(wos.size());
    for (const auto& wo : wos) {
      auto target = wo.template optionalCast<T>();
      if (target) {
        result.emplace_back(*target);
      }
    }
    return result;
  }

  bool operator<(const ModelObject& right) const;
  bool operator==(const ModelObject& other) const;
  bool operator!=(const ModelObject& other) const;

 protected:
  using ImplType = detail::ModelObject_Impl;

  friend class openstudio::IdfObject;
  friend class openstudio::IdfExtensibleGroup;
  friend class openstudio::detail::IdfObject_Impl;
  friend class detail::ModelObject_Impl;

  explicit ModelObject(IddObjectType type, const Model& model, bool fastName = false, bool isTransient = false);
  explicit ModelObject(std::shared_ptr<ImplType> impl);
  std::shared_ptr<ImplType> getImpl() const;
};

using OptionalModelObject = boost::optional<ModelObject>;

}  // namespace epmodel
}  // namespace openstudio

#endif
