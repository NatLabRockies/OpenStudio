/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_MODELOBJECT_HPP
#define EPMODEL_MODELOBJECT_HPP

#include "EPModelAPI.hpp"
#include "../EPModelConcepts.hpp"

#include "../../utilities/idd/IddEnums.hpp"
#include "../../utilities/idf/WorkspaceObject.hpp"

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

    template <AnyModelObject T>
    boost::optional<T> getModelObjectTarget(unsigned index) const {
      boost::optional<T> result;
      auto candidate = getTarget(index);
      if (candidate) {
        result = candidate->template optionalCast<T>();
      }
      return result;
    }

    template <AnyModelObject T>
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

    /** Get all objects of type T that point to this object. This method is preferred over the
     *  WorkspaceObject equivalent, as its use does not require knowledge of the IddObjectType. */
    template <AnyModelObject T>
    std::vector<T> getModelObjectSources() const {
      std::vector<T> result;
      std::vector<WorkspaceObject> wos = sources();
      result.reserve(wos.size());
      for (const WorkspaceObject& wo : wos) {
        boost::optional<T> oSource = wo.optionalCast<T>();
        if (oSource) {
          result.emplace_back(*oSource);
        }
      }
      return result;
    }

    /** Get all objects of type T that point to this object. Preferred usage (do not use with
     *  abstract classes):
     *
     *  \code
     *  PeopleVector myZonesPeople = zone.getModelObjectSources<People>(People::iddObjectType());
     *  \endcode
     **/
    template <AnyModelObject T>
    std::vector<T> getModelObjectSources(IddObjectType iddObjectType) const {
      std::vector<T> result;
      std::vector<WorkspaceObject> wos = getSources(iddObjectType);
      result.reserve(wos.size());
      for (const WorkspaceObject& wo : wos) {
        // assume iddObjectType is valid for T
        result.emplace_back(wo.cast<T>());
      }
      return result;
    }

    bool operator<(const ModelObject& right) const;
    bool operator==(const ModelObject& other) const;
    bool operator!=(const ModelObject& other) const;

    boost::optional<double> getAutosizedValue(const std::string& valueName, const std::string& units) const;

   protected:
    using ImplType = detail::ModelObject_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::IdfExtensibleGroup;
    friend class openstudio::detail::IdfObject_Impl;
    friend class detail::ModelObject_Impl;

    explicit ModelObject(IddObjectType type, const Model& model, bool fastName = false, bool isTransient = false);
    explicit ModelObject(std::shared_ptr<ImplType> impl);
  };

  using OptionalModelObject = boost::optional<ModelObject>;

}  // namespace epmodel
}  // namespace openstudio

#endif
