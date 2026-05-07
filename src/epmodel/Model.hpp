/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_MODEL_HPP
#define EPMODEL_MODEL_HPP

#include "EPModelAPI.hpp"
#include "Model_Impl.hpp"
#include "EPModelConcepts.hpp"
#include "StraightComponent/Node_Impl.hpp"

#include "../utilities/idf/Workspace.hpp"
#include "../utilities/idf/IdfObject.hpp"
#include "../utilities/idf/WorkspaceObject_Impl.hpp"
#include "../utilities/core/Compare.hpp"
#include "../utilities/core/Logger.hpp"

#include <string>
#include <set>
#include <vector>

namespace openstudio {
class IdfFile;
class SqlFile;

namespace epmodel {

  class Schedule;

  enum class SanitizationPolicy
  {
    None,
    ReportOnly,
    Repair,
  };

  struct EPMODEL_API SanitizationReport
  {
    unsigned infoCount{0};
    unsigned warningCount{0};
    unsigned errorCount{0};
    std::vector<std::string> messages;

    void log() const;
  };

  namespace detail {
    class Model_Impl;

    struct LoadContext
    {
      openstudio::epmodel::Model& model;
      SanitizationPolicy policy;
      SanitizationReport report;
      std::set<openstudio::Handle> visited;

      bool repairEnabled() const {
        return policy == SanitizationPolicy::Repair;
      }
    };

    void addLoadInfo(LoadContext& ctx, const std::string& message);
    void addLoadWarning(LoadContext& ctx, const std::string& message);
    void addLoadError(LoadContext& ctx, const std::string& message);
  }  // namespace detail

  class EPMODEL_API Model : public openstudio::Workspace
  {
   public:
    Model();
    explicit Model(const openstudio::IdfFile& idfFile);
    explicit Model(const openstudio::Workspace& workspace);
    Model clone(bool keepHandles = false) const;
    static boost::optional<Model> load(const openstudio::path& idfPath);
    Schedule alwaysOnDiscreteSchedule() const;
    std::string alwaysOnDiscreteScheduleName() const;
    Schedule alwaysOnContinuousSchedule() const;
    std::string alwaysOnContinuousScheduleName() const;
    SanitizationReport canonicalize(SanitizationPolicy policy = SanitizationPolicy::Repair);
    boost::optional<SqlFile> sqlFile() const;
    bool setSqlFile(const SqlFile& sqlFile);
    bool resetSqlFile();

    virtual ~Model() override = default;
    Model(const Model& other) = default;
    Model(Model&& other) = default;
    Model& operator=(const Model&) = default;
    Model& operator=(Model&&) = default;

    template <TransientModelObject T>
    T getOrCreateTransientByName(const std::string& name) const {
      if (name.empty()) {
        LOG_FREE_AND_THROW("openstudio.epmodel.Model", "Transient model objects require a non-empty name.");
      }

      auto objects = this->getObjectsByType(T::iddObjectType());
      for (const auto& wo : objects) {
        if (auto existingName = wo.name()) {
          if (openstudio::istringEqual(*existingName, name)) {
            if (auto impl = wo.template getImpl<typename T::ImplType>()) {
              return T(std::move(impl));
            }
          }
        }
      }

      auto modelImpl = getImpl<detail::Model_Impl>();
      openstudio::IdfObject idfObject(T::iddObjectType());
      auto actualName = idfObject.setName(name);
      if (!actualName || !openstudio::istringEqual(*actualName, name)) {
        LOG_FREE_AND_THROW("openstudio.epmodel.Model", "Failed to assign transient model object name '" << name << "'.");
      }

      auto impl = modelImpl->createObject(idfObject, false, true);
      openstudio::detail::WorkspaceObject_ImplPtrVector impls;
      impls.push_back(impl);
      modelImpl->addObjects(impls, false);

      auto typedImpl = std::dynamic_pointer_cast<typename T::ImplType>(impl);
      if (!typedImpl) {
        LOG_FREE_AND_THROW("openstudio.epmodel.Model", "Failed to create transient model object of requested type.");
      }
      return T(std::move(typedImpl));
    }

    /// Returns a transient model object by name, generating a name when missing.
    template <TransientModelObject T>
    T getOrCreateTransientByNameOrCreate(const boost::optional<std::string>& name) const {
      if (name && !name->empty()) {
        return getOrCreateTransientByName<T>(*name);
      }

      const auto generatedName = nextName(T::iddObjectType(), true);
      LOG_FREE(Warn, "openstudio.epmodel.Model", "Transient model object name missing; generated '" << generatedName << "'.");
      return getOrCreateTransientByName<T>(generatedName);
    }

    /// Returns a single model object of type T by handle, if it exists.
    template <AnyModelObject T>
    boost::optional<T> getModelObject(const Handle& handle) const {
      if (auto wo = this->getObject(handle)) {
        return wo->optionalCast<T>();
      }
      return boost::none;
    }

    // -------------------------------------------------------------------------
    //  Get a single model object by name
    // -------------------------------------------------------------------------

    /// Returns a model object of type T by exact name, if it exists.
    template <AnyModelObject T>
    boost::optional<T> getModelObjectByName(const std::string& name) const {
      std::vector<WorkspaceObject> objects = this->getObjectsByName(name, true);
      for (const auto& wo : objects) {
        std::shared_ptr<typename T::ImplType> p = wo.getImpl<typename T::ImplType>();
        if (p) {
          return T(std::move(p));
        }
      }
      return boost::none;
    }

    /// Returns a concrete model object of type T by exact name, if it exists.
    template <ConcreteModelObject T>
    boost::optional<T> getConcreteModelObjectByName(const std::string& name) const {
      if (auto object = this->getObjectByTypeAndName(T::iddObjectType(), name)) {
        if (auto p = object->template getImpl<typename T::ImplType>()) {
          return T(std::move(p));
        }
      }
      return boost::none;
    }

    // -------------------------------------------------------------------------
    //  Get model objects by type
    // -------------------------------------------------------------------------

    template <AnyModelObject T>
    std::vector<T> getModelObjects(bool sorted = false) const {
      std::vector<T> result;
      std::vector<WorkspaceObject> objects = this->objects(sorted);
      result.reserve(objects.size());
      for (const auto& wo : objects) {
        std::shared_ptr<typename T::ImplType> p = wo.getImpl<typename T::ImplType>();
        if (p) {
          result.push_back(T(std::move(p)));
        }
      }
      return result;
    }

    /// Returns all model objects of type T using T::iddObjectType() to speed up the search.
    /// This only works for concrete model objects.
    template <ConcreteModelObject T>
    std::vector<T> getConcreteModelObjects(bool sorted = false) const {
      std::vector<T> result;
      std::vector<WorkspaceObject> objects = this->getObjectsByType(T::iddObjectType());
      if (sorted) {
        objects = this->sort(objects);  // Call Workspace::sort
      }
      result.reserve(objects.size());
      for (const auto& wo : objects) {
        std::shared_ptr<typename T::ImplType> p = wo.getImpl<typename T::ImplType>();
        if (p) {
          result.push_back(T(std::move(p)));
        }
      }
      return result;
    }

    // -------------------------------------------------------------------------
    // Get model objects by name matching
    // -------------------------------------------------------------------------

    /** Returns all \link ModelObject ModelObjects \endlink of type T with given name. This method can
     *  be used with T as a concrete type (e.g. Zone) or as an abstract class (e.g. ParentObject).
     *
     *  \todo Use of this template method requires knowledge of the size of the implementation object.
     *  Therefore, to use model.getModelObjectsByName<Zone>("Zone1") the user must include both
     *  Zone.hpp and Zone_Impl.hpp. It may be better to instantiate each version of this template
     *  method to avoid exposing the implementation objects, this is an open question. */
    template <AnyModelObject T>
    std::vector<T> getModelObjectsByName(const std::string& name, bool exactMatch = true) const {
      std::vector<T> result;
      std::vector<WorkspaceObject> objects = this->getObjectsByName(name, exactMatch);
      result.reserve(objects.size());
      for (auto& wo : objects) {
        std::shared_ptr<typename T::ImplType> p = wo.getImpl<typename T::ImplType>();
        if (p) {
          result.push_back(T(p));
        }
      }
      return result;
    }

    template <ConcreteModelObject T>
    std::vector<T> getConcreteModelObjectsByName(const std::string& name, bool exactMatch = false) const {
      std::vector<T> result;
      if (exactMatch) {
        // Call the singular version directly
        if (auto object = this->getConcreteModelObjectByName<T>(name)) {
          result.push_back(*object);
        }
        return result;
      }
      std::vector<WorkspaceObject> objects = this->getObjectsByTypeAndName(T::iddObjectType(), name);
      result.reserve(objects.size());
      for (auto& wo : objects) {
        std::shared_ptr<typename T::ImplType> p = wo.getImpl<typename T::ImplType>();
        if (p) {
          result.push_back(T(p));
        }
      }
      return result;
    }

    // -------------------------------------------------------------------------
    // Get Unique Model Objects
    // -------------------------------------------------------------------------

    /** Returns the unique ModelObject of type T, creates a one if none are found.
     *
     *  \todo Use of this template method requires knowledge of the size of the implementation object.
     *  Therefore, to use model.getUniqueModelObject<Facility>() the user must include both
     *  Facility.hpp and Facility_Impl.hpp. It may be better to instantiate each version of this
     *  template method to avoid exposing the implementation objects, this is an open question.
     *
     *  Note that template specilizations are provided below for objects were there is a
     *  performance gain to be had by caching the unique model object
     *  eg: getUniqueModelObject<YearDescription>() */
    template <UniqueModelObject T>
    T getUniqueModelObject() {
      // NOTE: all UniqueModelObjects are Concrete. Call getObjectsByType to avoid returning a huge vector
      std::vector<WorkspaceObject> objects = this->getObjectsByType(T::iddObjectType());
      // std::vector<WorkspaceObject> objects = this->allObjects();
      for (const auto& wo : objects) {
        std::shared_ptr<typename T::ImplType> p = wo.getImpl<typename T::ImplType>();
        if (p) {
          return T(std::move(p));
        }
      }
      return T(*this);  // make a new T
    }

    /** Returns the unique ModelObject of type T if it is found.
     *
     *  \todo Use of this template method requires knowledge of the size of the implementation object.
     *  Therefore, to use model.getOptionalUniqueModelObject<Facility>() the user must include both
     *  Facility.hpp and Facility_Impl.hpp.  It may be better to instantiate each version of this
     *  template method to avoid exposing the implementation objects, this is an open question. */
    template <UniqueModelObject T>
    boost::optional<T> getOptionalUniqueModelObject() const {
      boost::optional<T> result;
      // NOTE: all UniqueModelObjects are Concrete. Call getObjectsByType to avoid returning a huge vector
      std::vector<WorkspaceObject> objects = this->getObjectsByType(T::iddObjectType());
      // std::vector<WorkspaceObject> objects = this->allObjects();
      for (const auto& wo : objects) {
        std::shared_ptr<typename T::ImplType> p = wo.getImpl<typename T::ImplType>();
        if (p) {
          result = T(std::move(p));
          break;
        }
      }
      return result;
    }

   protected:
    using ImplType = detail::Model_Impl;

    friend class openstudio::IdfObject;
    friend class ModelObject;
    friend class detail::ModelObject_Impl;
    friend class openstudio::Workspace;
    friend class detail::Model_Impl;

    Model(std::shared_ptr<openstudio::epmodel::detail::Model_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
