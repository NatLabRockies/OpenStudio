/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

// Template definitions for ModelObject_Impl::getOrCreateTarget.
// Included at the bottom of Model.hpp so that openstudio::epmodel::Model is
// complete when the bodies are parsed (required by Clang two-phase lookup).
// Do NOT include this file directly — include Model.hpp instead.

#ifndef EPMODEL_MODELOBJECT_IMPL_INL
#define EPMODEL_MODELOBJECT_IMPL_INL

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {
  namespace detail {

    template <typename T>
    T ModelObject_Impl::getOrCreateTarget(unsigned fieldIndex) {
      if (auto target = getTarget(fieldIndex)) {
        if (auto typed = target->template optionalCast<T>()) {
          return *typed;
        }
      }

      auto name = getString(fieldIndex);
      if (name && !name->empty()) {
        if (auto obj = workspace().getObjectByTypeAndName(T::iddObjectType(), *name)) {
          if (auto typed = obj->template optionalCast<T>()) {
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
      setPointer(fieldIndex, created.handle(), false);
      return created;
    }

    template <typename T>
    T ModelObject_Impl::getOrCreateTarget(unsigned fieldIndex, const std::string& preferredName) {
      if (auto target = getTarget(fieldIndex)) {
        if (auto typed = target->template optionalCast<T>()) {
          return *typed;
        }
      }

      if (!preferredName.empty()) {
        if (auto obj = workspace().getObjectByTypeAndName(T::iddObjectType(), preferredName)) {
          if (auto typed = obj->template optionalCast<T>()) {
            setPointer(fieldIndex, typed->handle(), false);
            return *typed;
          }
        }
      }

      auto name = getString(fieldIndex);
      if (name && !name->empty()) {
        if (auto obj = workspace().getObjectByTypeAndName(T::iddObjectType(), *name)) {
          if (auto typed = obj->template optionalCast<T>()) {
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
      setPointer(fieldIndex, created.handle(), false);
      return created;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
