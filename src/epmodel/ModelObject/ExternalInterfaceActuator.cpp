/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ExternalInterfaceActuator.hpp"
#include "ExternalInterfaceActuator_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/ExternalInterface_Actuator_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

ExternalInterfaceActuator::ExternalInterfaceActuator(const Model& model) : ModelObject(ExternalInterfaceActuator::iddObjectType(), model) {}

ExternalInterfaceActuator::ExternalInterfaceActuator(std::shared_ptr<detail::ExternalInterfaceActuator_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType ExternalInterfaceActuator::iddObjectType() {
  return IddObjectType::ExternalInterface_Actuator;
}

std::string ExternalInterfaceActuator::actuatedComponentControlType() const {
  return getImpl<detail::ExternalInterfaceActuator_Impl>()->actuatedComponentControlType();
}

bool ExternalInterfaceActuator::setActuatedComponentControlType(const std::string& actuatedComponentControlType) {
  return getImpl<detail::ExternalInterfaceActuator_Impl>()->setActuatedComponentControlType(actuatedComponentControlType);
}

std::string ExternalInterfaceActuator::actuatedComponentType() const {
  return getImpl<detail::ExternalInterfaceActuator_Impl>()->actuatedComponentType();
}

bool ExternalInterfaceActuator::setActuatedComponentType(const std::string& actuatedComponentType) {
  return getImpl<detail::ExternalInterfaceActuator_Impl>()->setActuatedComponentType(actuatedComponentType);
}

boost::optional<double> ExternalInterfaceActuator::optionalInitialValue() const {
  return getImpl<detail::ExternalInterfaceActuator_Impl>()->optionalInitialValue();
}

bool ExternalInterfaceActuator::setOptionalInitialValue(double optionalInitialValue) {
  return getImpl<detail::ExternalInterfaceActuator_Impl>()->setOptionalInitialValue(optionalInitialValue);
}

void ExternalInterfaceActuator::resetOptionalInitialValue() {
  getImpl<detail::ExternalInterfaceActuator_Impl>()->resetOptionalInitialValue();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string ExternalInterfaceActuator_Impl::actuatedComponentControlType() const {
  const auto value = getString(openstudio::ExternalInterface_ActuatorFields::ActuatedComponentControlType, true);
  OS_ASSERT(value);
  return *value;
}

bool ExternalInterfaceActuator_Impl::setActuatedComponentControlType(const std::string& actuatedComponentControlType) {
  const bool result = setString(openstudio::ExternalInterface_ActuatorFields::ActuatedComponentControlType, actuatedComponentControlType);
  OS_ASSERT(result);
  return result;
}

std::string ExternalInterfaceActuator_Impl::actuatedComponentType() const {
  const auto value = getString(openstudio::ExternalInterface_ActuatorFields::ActuatedComponentType, true);
  OS_ASSERT(value);
  return *value;
}

bool ExternalInterfaceActuator_Impl::setActuatedComponentType(const std::string& actuatedComponentType) {
  const bool result = setString(openstudio::ExternalInterface_ActuatorFields::ActuatedComponentType, actuatedComponentType);
  OS_ASSERT(result);
  return result;
}

boost::optional<double> ExternalInterfaceActuator_Impl::optionalInitialValue() const {
  return getDouble(openstudio::ExternalInterface_ActuatorFields::OptionalInitialValue, true);
}

bool ExternalInterfaceActuator_Impl::setOptionalInitialValue(double optionalInitialValue) {
  const bool result = setDouble(openstudio::ExternalInterface_ActuatorFields::OptionalInitialValue, optionalInitialValue);
  OS_ASSERT(result);
  return result;
}

void ExternalInterfaceActuator_Impl::resetOptionalInitialValue() {
  const bool result = setString(openstudio::ExternalInterface_ActuatorFields::OptionalInitialValue, "");
  OS_ASSERT(result);
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
