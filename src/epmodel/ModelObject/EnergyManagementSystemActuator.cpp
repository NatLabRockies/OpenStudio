/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "EnergyManagementSystemActuator.hpp"
#include "EnergyManagementSystemActuator_Impl.hpp"

#include "Model.hpp"
#include "ModelObject_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/EnergyManagementSystem_Actuator_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  namespace {

    // The EnergyPlus actuator schema still stores "Actuated Component Unique Name"
    // as a plain string, so this file needs a small local helper to turn an exact
    // name match back into a generic ModelObject without adding a broader public
    // factory just for this case.
    class RehydratedModelObject : public ModelObject
    {
     public:
      explicit RehydratedModelObject(std::shared_ptr<detail::ModelObject_Impl> impl) : ModelObject(std::move(impl)) {}
    };

    boost::optional<ModelObject> modelObjectByExactName(const Model& model, const std::string& name) {
      for (const auto& object : model.getObjectsByName(name, true, true)) {
        if (auto impl = object.getImpl<detail::ModelObject_Impl>()) {
          return RehydratedModelObject(std::move(impl));
        }
      }
      return boost::none;
    }

  }  // namespace

  EnergyManagementSystemActuator::EnergyManagementSystemActuator(const ModelObject& actuatedComponent, const std::string& actuatedComponentType,
                                                                 const std::string& actuatedComponentControlType)
    : ModelObject(EnergyManagementSystemActuator::iddObjectType(), actuatedComponent.model()) {
    OS_ASSERT(getImpl<detail::EnergyManagementSystemActuator_Impl>());
    const bool ok = setActuatedComponent(actuatedComponent) && setActuatedComponentType(actuatedComponentType)
                    && setActuatedComponentControlType(actuatedComponentControlType);
    OS_ASSERT(ok);
  }

  EnergyManagementSystemActuator::EnergyManagementSystemActuator(const Model& model)
    : ModelObject(EnergyManagementSystemActuator::iddObjectType(), model) {}

  EnergyManagementSystemActuator::EnergyManagementSystemActuator(std::shared_ptr<detail::EnergyManagementSystemActuator_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType EnergyManagementSystemActuator::iddObjectType() {
    return IddObjectType::EnergyManagementSystem_Actuator;
  }

  boost::optional<ModelObject> EnergyManagementSystemActuator::actuatedComponent() const {
    return getImpl<detail::EnergyManagementSystemActuator_Impl>()->actuatedComponent();
  }

  bool EnergyManagementSystemActuator::setActuatedComponent(const ModelObject& actuatedComponent) {
    return getImpl<detail::EnergyManagementSystemActuator_Impl>()->setActuatedComponent(actuatedComponent);
  }

  std::string EnergyManagementSystemActuator::actuatedComponentControlType() const {
    return getImpl<detail::EnergyManagementSystemActuator_Impl>()->actuatedComponentControlType();
  }

  bool EnergyManagementSystemActuator::setActuatedComponentControlType(const std::string& actuatedComponentControlType) {
    return getImpl<detail::EnergyManagementSystemActuator_Impl>()->setActuatedComponentControlType(actuatedComponentControlType);
  }

  std::string EnergyManagementSystemActuator::actuatedComponentType() const {
    return getImpl<detail::EnergyManagementSystemActuator_Impl>()->actuatedComponentType();
  }

  bool EnergyManagementSystemActuator::setActuatedComponentType(const std::string& actuatedComponentType) {
    return getImpl<detail::EnergyManagementSystemActuator_Impl>()->setActuatedComponentType(actuatedComponentType);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<ModelObject> EnergyManagementSystemActuator_Impl::actuatedComponent() const {
      const auto value = getString(openstudio::EnergyManagementSystem_ActuatorFields::ActuatedComponentUniqueName, true);
      if (!value) {
        return boost::none;
      }
      return modelObjectByExactName(model(), *value);
    }

    bool EnergyManagementSystemActuator_Impl::setActuatedComponent(const ModelObject& actuatedComponent) {
      return setString(openstudio::EnergyManagementSystem_ActuatorFields::ActuatedComponentUniqueName, actuatedComponent.nameString());
    }

    std::string EnergyManagementSystemActuator_Impl::actuatedComponentControlType() const {
      const auto value = getString(openstudio::EnergyManagementSystem_ActuatorFields::ActuatedComponentControlType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool EnergyManagementSystemActuator_Impl::setActuatedComponentControlType(const std::string& actuatedComponentControlType) {
      const bool result = setString(openstudio::EnergyManagementSystem_ActuatorFields::ActuatedComponentControlType, actuatedComponentControlType);
      OS_ASSERT(result);
      return result;
    }

    std::string EnergyManagementSystemActuator_Impl::actuatedComponentType() const {
      const auto value = getString(openstudio::EnergyManagementSystem_ActuatorFields::ActuatedComponentType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool EnergyManagementSystemActuator_Impl::setActuatedComponentType(const std::string& actuatedComponentType) {
      const bool result = setString(openstudio::EnergyManagementSystem_ActuatorFields::ActuatedComponentType, actuatedComponentType);
      OS_ASSERT(result);
      return result;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
