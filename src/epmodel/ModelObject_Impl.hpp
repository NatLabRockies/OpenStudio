/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_MODELOBJECT_IMPL_HPP
#define EPMODEL_MODELOBJECT_IMPL_HPP

#include "EPModelAPI.hpp"

#include "../utilities/idf/Workspace.hpp"
#include "../utilities/idf/WorkspaceObject.hpp"
#include "../utilities/idf/WorkspaceObject_Impl.hpp"
#include "../utilities/core/Logger.hpp"
#include <boost/optional.hpp>
namespace openstudio {
class IdfObject;
namespace epmodel {

class Model;
class Node;

namespace detail {
  class Model_Impl;
  struct LoadContext;

class EPMODEL_API ModelObject_Impl : public openstudio::detail::WorkspaceObject_Impl
{
 public:
  ModelObject_Impl(const openstudio::IdfObject& idfObject, Model_Impl* model, bool keepHandle);
  ModelObject_Impl(const openstudio::detail::WorkspaceObject_Impl& other, Model_Impl* model, bool keepHandle);
  virtual ~ModelObject_Impl() override = default;

  openstudio::epmodel::Model model() const;
  void canonicalize(LoadContext& context);

 protected:
  template <typename T>
  T getOrCreateTarget(unsigned fieldIndex) {
    if (auto target = getTarget(fieldIndex)) {
      if (auto typed = target->template optionalCast<T>()) {
        return *typed;
      }
    }

    auto name = getString(fieldIndex);
    if (name && !name->empty()) {
      if (auto obj = workspace().getObjectByTypeAndName(T::iddObjectType(), *name, true)) {
        if (auto typed = obj->template optionalCast<T>()) {
          if (!setString(fieldIndex, typed->nameString())) {
            LOG_FREE_AND_THROW("openstudio.epmodel.ModelObject",
                               "Failed to set field index " << fieldIndex << " to target '" << typed->nameString() << "'.");
          }
          setPointer(fieldIndex, typed->handle(), false);
          return *typed;
        }
      }
    }

    T created(model());
    if (name && !name->empty()) {
      if (!created.setName(*name)) {
        LOG_FREE(Warn, "openstudio.epmodel.ModelObject",
                 "Failed to apply existing name '" << *name << "' to newly created target at field index " << fieldIndex << ".");
      }
    }
    if (!setString(fieldIndex, created.nameString())) {
      LOG_FREE_AND_THROW("openstudio.epmodel.ModelObject",
                         "Failed to set field index " << fieldIndex << " to target '" << created.nameString() << "'.");
    }
    setPointer(fieldIndex, created.handle(), false);
    return created;
  }

  template <typename T>
  T getOrCreateTarget(unsigned fieldIndex, const std::string& preferredName) {
    if (auto target = getTarget(fieldIndex)) {
      if (auto typed = target->template optionalCast<T>()) {
        return *typed;
      }
    }

    if (!preferredName.empty()) {
      if (auto obj = workspace().getObjectByTypeAndName(T::iddObjectType(), preferredName, true)) {
        if (auto typed = obj->template optionalCast<T>()) {
          if (!setString(fieldIndex, typed->nameString())) {
            LOG_FREE_AND_THROW("openstudio.epmodel.ModelObject",
                               "Failed to set field index " << fieldIndex << " to target '" << typed->nameString() << "'.");
          }
          setPointer(fieldIndex, typed->handle(), false);
          return *typed;
        }
      }
    }

    auto name = getString(fieldIndex);
    if (name && !name->empty()) {
      if (auto obj = workspace().getObjectByTypeAndName(T::iddObjectType(), *name, true)) {
        if (auto typed = obj->template optionalCast<T>()) {
          if (!setString(fieldIndex, typed->nameString())) {
            LOG_FREE_AND_THROW("openstudio.epmodel.ModelObject",
                               "Failed to set field index " << fieldIndex << " to target '" << typed->nameString() << "'.");
          }
          setPointer(fieldIndex, typed->handle(), false);
          return *typed;
        }
      }
    }

    T created(model());
    if (!preferredName.empty()) {
      if (!created.setName(preferredName)) {
        LOG_FREE(Warn, "openstudio.epmodel.ModelObject",
                 "Failed to apply preferred name '" << preferredName << "' to newly created target at field index " << fieldIndex << ".");
      }
    } else if (name && !name->empty()) {
      if (!created.setName(*name)) {
        LOG_FREE(Warn, "openstudio.epmodel.ModelObject",
                 "Failed to apply existing name '" << *name << "' to newly created target at field index " << fieldIndex << ".");
      }
    }
    if (!setString(fieldIndex, created.nameString())) {
      LOG_FREE_AND_THROW("openstudio.epmodel.ModelObject",
                         "Failed to set field index " << fieldIndex << " to target '" << created.nameString() << "'.");
    }
    setPointer(fieldIndex, created.handle(), false);
    return created;
  }
  openstudio::epmodel::Node getOrCreateNodeTarget(unsigned fieldIndex);

  virtual void doCanonicalize(LoadContext& context);
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
