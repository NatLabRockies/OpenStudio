/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ModelObject.hpp"
#include "ModelObject_Impl.hpp"
#include "Model.hpp"
#include "Model_Impl.hpp"
#include "Node.hpp"

#include "../../utilities/idf/IdfObject.hpp"
#include "../../utilities/idf/WorkspaceObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  ModelObject::ModelObject(IddObjectType type, const Model& model, bool fastName, bool isTransient)
    : WorkspaceObject(model.getImpl<detail::Model_Impl>()->createObject(IdfObject(type, fastName), false, isTransient)) {
    auto modelImpl = model.getImpl<detail::Model_Impl>();
    openstudio::detail::WorkspaceObject_ImplPtrVector impls;
    impls.push_back(openstudio::IdfObject::getImpl<openstudio::detail::WorkspaceObject_Impl>());
    modelImpl->addObjects(impls, openstudio::UHPointerVector(), openstudio::HUPointerVector(), false, false, false);
  }

  ModelObject::ModelObject(std::shared_ptr<ImplType> impl) : WorkspaceObject(std::move(impl)) {}

  std::shared_ptr<ModelObject::ImplType> ModelObject::getImpl() const {
    return openstudio::IdfObject::getImpl<detail::ModelObject_Impl>();
  }

  Model ModelObject::model() const {
    return getImpl<detail::ModelObject_Impl>()->model();
  }

  ModelObject ModelObject::create(IddObjectType type, const Model& model, bool fastName) {
    return ModelObject(type, model, fastName);
  }

  bool ModelObject::operator<(const ModelObject& right) const {
    return (getImpl<detail::ModelObject_Impl>()) < (right.getImpl<detail::ModelObject_Impl>());
  }

  bool ModelObject::operator==(const ModelObject& other) const {
    return (handle() == other.handle());
  }

  bool ModelObject::operator!=(const ModelObject& other) const {
    return (handle() != other.handle());
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    ModelObject_Impl::ModelObject_Impl(const openstudio::IdfObject& idfObject, Model_Impl* model, bool keepHandle)
      : openstudio::detail::WorkspaceObject_Impl(idfObject, model, keepHandle) {}

    ModelObject_Impl::ModelObject_Impl(const openstudio::detail::WorkspaceObject_Impl& other, Model_Impl* model, bool keepHandle)
      : openstudio::detail::WorkspaceObject_Impl(other, model, keepHandle) {}

    openstudio::epmodel::Model ModelObject_Impl::model() const {
      return workspace().cast<Model>();
    }

    void ModelObject_Impl::canonicalize(LoadContext& context) {
      if (context.visited.contains(handle())) {
        return;
      }
      context.visited.insert(handle());
      doCanonicalize(context);
    }

    void ModelObject_Impl::doCanonicalize(LoadContext&) {}

    openstudio::epmodel::Node ModelObject_Impl::getOrCreateNodeTarget(unsigned fieldIndex) {
      if (auto target = getTarget(fieldIndex)) {
        if (auto node = target->optionalCast<openstudio::epmodel::Node>()) {
          return *node;
        }
      }

      auto name = getString(fieldIndex);
      openstudio::epmodel::Node node = model().getOrCreateTransientByNameOrCreate<openstudio::epmodel::Node>(name);
      if (!setString(fieldIndex, node.nameString())) {
        LOG_FREE_AND_THROW("openstudio.epmodel.ModelObject",
                           "Failed to set node target name for field index " << fieldIndex << ".");
      }
      setPointer(fieldIndex, node.handle(), false);
      return node;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
