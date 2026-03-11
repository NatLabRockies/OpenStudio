/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_MODEL_IMPL_HPP
#define EPMODEL_MODEL_IMPL_HPP

#include "EPModelAPI.hpp"

#include "../utilities/core/Logger.hpp"
#include "../utilities/idf/Workspace_Impl.hpp"

#include <functional>
#include <map>
#include <memory>
#include <vector>

namespace openstudio {

class IdfFile;
class IdfObject;

namespace epmodel {

  class Model;

  namespace detail {

    class EPMODEL_API Model_Impl : public openstudio::detail::Workspace_Impl
    {
     public:
      Model_Impl();
      Model_Impl(const IdfFile& idfFile);
      Model_Impl(const openstudio::detail::Workspace_Impl& workspace, bool keepHandles = false);
      Model_Impl(const Model_Impl& other, bool keepHandles = false);
      Model_Impl(const Model_Impl& other, const std::vector<Handle>& hs, bool keepHandles = false, StrictnessLevel level = StrictnessLevel::Draft);

      virtual ~Model_Impl() override = default;

      virtual std::shared_ptr<openstudio::detail::WorkspaceObject_Impl> createObject(const IdfObject& object, bool keepHandle) override;
      virtual std::shared_ptr<openstudio::detail::WorkspaceObject_Impl> createObject(const IdfObject& object, bool keepHandle,
                                                                                     bool isTransient) override;
      virtual std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>
        createObject(const std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>& originalObjectImplPtr, bool keepHandle) override;

      openstudio::epmodel::Model model() const;

      using CopyConstructorFunction = std::function<std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
        Model_Impl*, const std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>&, bool)>;
      using CopyConstructorMap = std::map<IddObjectType, CopyConstructorFunction>;

      using NewConstructorFunction = std::function<std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(Model_Impl*, const IdfObject&, bool)>;
      using NewConstructorMap = std::map<IddObjectType, NewConstructorFunction>;

      struct ModelObjectCreator
      {
        explicit ModelObjectCreator();

        std::shared_ptr<openstudio::detail::WorkspaceObject_Impl> getNew(Model_Impl* model, const IdfObject& obj, bool keepHandle) const;
        std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>
          getCopy(Model_Impl* model, const std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>& obj, bool keepHandle) const;

        CopyConstructorMap m_copyMap;
        NewConstructorMap m_newMap;
      };

      static const ModelObjectCreator modelObjectCreator;

      REGISTER_LOGGER("openstudio.epmodel.Model");
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
