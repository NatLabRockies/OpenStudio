/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_MODEL_HPP
#define EPMODEL_MODEL_HPP

#include "EPModelAPI.hpp"
#include "Model_Impl.hpp"
#include "StraightComponent/Node_Impl.hpp"

#include "../utilities/idf/Workspace.hpp"
#include "../utilities/idf/IdfObject.hpp"
#include "../utilities/idf/WorkspaceObject_Impl.hpp"
#include "../utilities/core/Compare.hpp"
#include "../utilities/core/Logger.hpp"

#include <type_traits>
#include <string>
#include <set>
#include <vector>

namespace openstudio {
class IdfFile;

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

    template <typename T>
    struct is_transient_factory_type : std::false_type
    {
    };
  }  // namespace detail

  class Node;
  class CoilHeatingLowTempRadiantConstFlow;
  class CoilHeatingWaterBaseboard;
  class CoilHeatingWaterBaseboardRadiant;
  class CoilCoolingLowTempRadiantConstFlow;
  class CoilHeatingLowTempRadiantVarFlow;
  class CoilCoolingLowTempRadiantVarFlow;
  class CoilCoolingWaterPanelRadiant;
  class CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData;

class EPMODEL_API Model
  : public openstudio::Workspace
{
 public:
 Model();
  explicit Model(const openstudio::IdfFile& idfFile);
  explicit Model(const openstudio::Workspace& workspace);
  static boost::optional<Model> load(const openstudio::path& idfPath);
  Schedule alwaysOnDiscreteSchedule() const;
  std::string alwaysOnDiscreteScheduleName() const;
  SanitizationReport canonicalize(SanitizationPolicy policy = SanitizationPolicy::Repair);

  virtual ~Model() override = default;
  Model(const Model& other) = default;
  Model(Model&& other) = default;
  Model& operator=(const Model&) = default;
  Model& operator=(Model&&) = default;

  template <typename T>
  T getOrCreateTransientByName(const std::string& name) const {
    static_assert(detail::is_transient_factory_type<T>::value,
                  "getOrCreateTransientByName is only permitted for transient factory types.");

    if (name.empty()) {
      LOG_FREE_AND_THROW("openstudio.epmodel.Model", "Transient model objects require a non-empty name.");
    }

    auto objects = this->getObjectsByType(T::iddObjectType(), true);
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
  template <typename T>
  T getOrCreateTransientByNameOrCreate(const boost::optional<std::string>& name) const {
    static_assert(detail::is_transient_factory_type<T>::value,
                  "getOrCreateTransientByNameOrCreate is only permitted for transient factory types.");

    if (name && !name->empty()) {
      return getOrCreateTransientByName<T>(*name);
    }

    const auto generatedName = nextName(T::iddObjectType(), true);
    LOG_FREE(Warn, "openstudio.epmodel.Model",
             "Transient model object name missing; generated '" << generatedName << "'.");
    return getOrCreateTransientByName<T>(generatedName);
  }

  template <typename T>
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

  /// Returns a model object of type T by exact name, if it exists.
  template <typename T>
  boost::optional<T> getModelObjectByName(const std::string& name) const {
    std::vector<WorkspaceObject> objects = this->getObjectsByName(name, true, true);
    for (const auto& wo : objects) {
      std::shared_ptr<typename T::ImplType> p = wo.getImpl<typename T::ImplType>();
      if (p) {
        return T(std::move(p));
      }
    }
    return boost::none;
  }

  /// Returns a concrete model object of type T by exact name, if it exists.
  template <typename T>
  boost::optional<T> getConcreteModelObjectByName(const std::string& name) const {
    if (auto object = this->getObjectByTypeAndName(T::iddObjectType(), name)) {
      if (auto p = object->template getImpl<typename T::ImplType>()) {
        return T(std::move(p));
      }
    }
    return boost::none;
  }

  /// Returns a single model object of type T by handle, if it exists.
  template <typename T>
  boost::optional<T> getModelObject(const Handle& handle) const {
    if (auto wo = this->getObject(handle)) {
      return wo->optionalCast<T>();
    }
    return boost::none;
  }

  /// Returns all model objects of type T using T::iddObjectType() to speed up the search.
  /// This only works for concrete model objects.
  template <typename T>
  std::vector<T> getConcreteModelObjects(bool includeTransient = false) const {
    std::vector<T> result;
    std::vector<WorkspaceObject> objects = this->getObjectsByType(T::iddObjectType(), includeTransient);
    result.reserve(objects.size());
    for (const auto& wo : objects) {
      std::shared_ptr<typename T::ImplType> p = wo.getImpl<typename T::ImplType>();
      if (p) {
        result.push_back(T(std::move(p)));
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

namespace detail {
  template <>
  struct is_transient_factory_type<openstudio::epmodel::Node> : std::true_type
  {
  };

  template <>
  struct is_transient_factory_type<openstudio::epmodel::CoilHeatingLowTempRadiantConstFlow> : std::true_type
  {
  };

  template <>
  struct is_transient_factory_type<openstudio::epmodel::CoilHeatingWaterBaseboard> : std::true_type
  {
  };

  template <>
  struct is_transient_factory_type<openstudio::epmodel::CoilHeatingWaterBaseboardRadiant> : std::true_type
  {
  };

  template <>
  struct is_transient_factory_type<openstudio::epmodel::CoilCoolingLowTempRadiantConstFlow> : std::true_type
  {
  };

  template <>
  struct is_transient_factory_type<openstudio::epmodel::CoilHeatingLowTempRadiantVarFlow> : std::true_type
  {
  };

  template <>
  struct is_transient_factory_type<openstudio::epmodel::CoilCoolingLowTempRadiantVarFlow> : std::true_type
  {
  };

  template <>
  struct is_transient_factory_type<openstudio::epmodel::CoilCoolingWaterPanelRadiant> : std::true_type
  {
  };

  template <>
  struct is_transient_factory_type<openstudio::epmodel::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData> : std::true_type
  {
  };
}  // namespace detail

}  // namespace epmodel
}  // namespace openstudio

#endif
