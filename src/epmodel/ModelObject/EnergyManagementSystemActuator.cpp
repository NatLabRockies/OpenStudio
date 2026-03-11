/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "EnergyManagementSystemActuator.hpp"
#include "EnergyManagementSystemActuator_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/EnergyManagementSystem_Actuator_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

EnergyManagementSystemActuator::EnergyManagementSystemActuator(const Model& model)
  : ModelObject(EnergyManagementSystemActuator::iddObjectType(), model) {}

EnergyManagementSystemActuator::EnergyManagementSystemActuator(std::shared_ptr<detail::EnergyManagementSystemActuator_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType EnergyManagementSystemActuator::iddObjectType() {
  return IddObjectType::EnergyManagementSystem_Actuator;
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
