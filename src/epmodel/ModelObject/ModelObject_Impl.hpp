/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_MODELOBJECT_IMPL_HPP
#define EPMODEL_MODELOBJECT_IMPL_HPP

#include "EPModelAPI.hpp"

#include "../../utilities/idf/Workspace.hpp"
#include "../../utilities/idf/WorkspaceObject.hpp"
#include "../../utilities/idf/WorkspaceObject_Impl.hpp"
#include "../../utilities/core/Logger.hpp"
#include <boost/optional.hpp>
#include <string>
namespace openstudio {
class IdfObject;
namespace epmodel {

  class Model;
  class Node;
  class Schedule;

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

      // Node field helpers follow one simple rule: if we hand a Node back to
      // a caller, it must already be linked to this object. That keeps later
      // Node renames tracked by the owning field instead of drifting away as
      // an unlinked transient object.
      //
      // `resolvedNodeTarget` is the read path for a NodeType field that
      // already has persisted meaning. If the pointer is missing but the
      // field still names a Node, this method materializes the pointer before
      // returning. If the field is blank, or the link cannot be established,
      // it returns none.
      //
      // `resolvedOrCreatedNodeTarget` is the stronger form used by owner
      // maintenance and canonicalization. It first preserves any existing
      // field meaning. Only when the field is blank does it create or reuse a
      // Node with the caller's suggested name and link it immediately.
      boost::optional<openstudio::epmodel::Node> resolvedNodeTarget(unsigned fieldIndex) const;
      openstudio::epmodel::Node resolvedOrCreatedNodeTarget(unsigned fieldIndex, const std::string& suggestedName);
      boost::optional<double> getAutosizedValue(const std::string& valueName, const std::string& units,
                                                std::string overrideCompType = "") const;
      boost::optional<double> getAutosizedValueFromInitializationSummary(const std::string& valueName,
                                                                         const std::string& units) const;
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
      T getOrCreateTarget(unsigned fieldIndex, const std::string& preferredName) {
        if (auto target = getTarget(fieldIndex)) {
          if (auto typed = target->template optionalCast<T>()) {
            return *typed;
          }
        }

        if (!preferredName.empty()) {
          if (auto obj = workspace().getObjectByTypeAndName(T::iddObjectType(), preferredName, true)) {
            if (auto typed = obj->template optionalCast<T>()) {
              setPointer(fieldIndex, typed->handle(), false);
              return *typed;
            }
          }
        }

        auto name = getString(fieldIndex);
        if (name && !name->empty()) {
          if (auto obj = workspace().getObjectByTypeAndName(T::iddObjectType(), *name, true)) {
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
      bool setSchedule(unsigned fieldIndex, const std::string& className, const std::string& scheduleDisplayName,
                       openstudio::epmodel::Schedule& schedule);

      virtual void doCanonicalize(LoadContext& context);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
