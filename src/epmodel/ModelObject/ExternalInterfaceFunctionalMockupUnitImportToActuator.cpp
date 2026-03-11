/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ExternalInterfaceFunctionalMockupUnitImportToActuator.hpp"
#include "ExternalInterfaceFunctionalMockupUnitImportToActuator_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/ExternalInterface_FunctionalMockupUnitImport_To_Actuator_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

ExternalInterfaceFunctionalMockupUnitImportToActuator::ExternalInterfaceFunctionalMockupUnitImportToActuator(const Model& model)
  : ModelObject(ExternalInterfaceFunctionalMockupUnitImportToActuator::iddObjectType(), model) {}

ExternalInterfaceFunctionalMockupUnitImportToActuator::ExternalInterfaceFunctionalMockupUnitImportToActuator(
  std::shared_ptr<detail::ExternalInterfaceFunctionalMockupUnitImportToActuator_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType ExternalInterfaceFunctionalMockupUnitImportToActuator::iddObjectType() {
  return IddObjectType::ExternalInterface_FunctionalMockupUnitImport_To_Actuator;
}

std::string ExternalInterfaceFunctionalMockupUnitImportToActuator::actuatedComponentType() const {
  return getImpl<detail::ExternalInterfaceFunctionalMockupUnitImportToActuator_Impl>()->actuatedComponentType();
}

bool ExternalInterfaceFunctionalMockupUnitImportToActuator::setActuatedComponentType(const std::string& actuatedComponentType) {
  return getImpl<detail::ExternalInterfaceFunctionalMockupUnitImportToActuator_Impl>()->setActuatedComponentType(actuatedComponentType);
}

std::string ExternalInterfaceFunctionalMockupUnitImportToActuator::actuatedComponentControlType() const {
  return getImpl<detail::ExternalInterfaceFunctionalMockupUnitImportToActuator_Impl>()->actuatedComponentControlType();
}

bool ExternalInterfaceFunctionalMockupUnitImportToActuator::setActuatedComponentControlType(const std::string& actuatedComponentControlType) {
  return getImpl<detail::ExternalInterfaceFunctionalMockupUnitImportToActuator_Impl>()->setActuatedComponentControlType(
    actuatedComponentControlType);
}

std::string ExternalInterfaceFunctionalMockupUnitImportToActuator::fMUInstanceName() const {
  return getImpl<detail::ExternalInterfaceFunctionalMockupUnitImportToActuator_Impl>()->fMUInstanceName();
}

bool ExternalInterfaceFunctionalMockupUnitImportToActuator::setFMUInstanceName(const std::string& fMUInstanceName) {
  return getImpl<detail::ExternalInterfaceFunctionalMockupUnitImportToActuator_Impl>()->setFMUInstanceName(fMUInstanceName);
}

std::string ExternalInterfaceFunctionalMockupUnitImportToActuator::fMUVariableName() const {
  return getImpl<detail::ExternalInterfaceFunctionalMockupUnitImportToActuator_Impl>()->fMUVariableName();
}

bool ExternalInterfaceFunctionalMockupUnitImportToActuator::setFMUVariableName(const std::string& fMUVariableName) {
  return getImpl<detail::ExternalInterfaceFunctionalMockupUnitImportToActuator_Impl>()->setFMUVariableName(fMUVariableName);
}

double ExternalInterfaceFunctionalMockupUnitImportToActuator::initialValue() const {
  return getImpl<detail::ExternalInterfaceFunctionalMockupUnitImportToActuator_Impl>()->initialValue();
}

bool ExternalInterfaceFunctionalMockupUnitImportToActuator::setInitialValue(double initialValue) {
  return getImpl<detail::ExternalInterfaceFunctionalMockupUnitImportToActuator_Impl>()->setInitialValue(initialValue);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string ExternalInterfaceFunctionalMockupUnitImportToActuator_Impl::actuatedComponentType() const {
  const auto value = getString(openstudio::ExternalInterface_FunctionalMockupUnitImport_To_ActuatorFields::ActuatedComponentType, true);
  OS_ASSERT(value);
  return *value;
}

bool ExternalInterfaceFunctionalMockupUnitImportToActuator_Impl::setActuatedComponentType(const std::string& actuatedComponentType) {
  const bool result = setString(openstudio::ExternalInterface_FunctionalMockupUnitImport_To_ActuatorFields::ActuatedComponentType,
                                actuatedComponentType);
  OS_ASSERT(result);
  return result;
}

std::string ExternalInterfaceFunctionalMockupUnitImportToActuator_Impl::actuatedComponentControlType() const {
  const auto value =
    getString(openstudio::ExternalInterface_FunctionalMockupUnitImport_To_ActuatorFields::ActuatedComponentControlType, true);
  OS_ASSERT(value);
  return *value;
}

bool ExternalInterfaceFunctionalMockupUnitImportToActuator_Impl::setActuatedComponentControlType(
  const std::string& actuatedComponentControlType) {
  const bool result = setString(openstudio::ExternalInterface_FunctionalMockupUnitImport_To_ActuatorFields::ActuatedComponentControlType,
                                actuatedComponentControlType);
  OS_ASSERT(result);
  return result;
}

std::string ExternalInterfaceFunctionalMockupUnitImportToActuator_Impl::fMUInstanceName() const {
  const auto value = getString(openstudio::ExternalInterface_FunctionalMockupUnitImport_To_ActuatorFields::FMUInstanceName, true);
  OS_ASSERT(value);
  return *value;
}

bool ExternalInterfaceFunctionalMockupUnitImportToActuator_Impl::setFMUInstanceName(const std::string& fMUInstanceName) {
  const bool result = setString(openstudio::ExternalInterface_FunctionalMockupUnitImport_To_ActuatorFields::FMUInstanceName, fMUInstanceName);
  OS_ASSERT(result);
  return result;
}

std::string ExternalInterfaceFunctionalMockupUnitImportToActuator_Impl::fMUVariableName() const {
  const auto value = getString(openstudio::ExternalInterface_FunctionalMockupUnitImport_To_ActuatorFields::FMUVariableName, true);
  OS_ASSERT(value);
  return *value;
}

bool ExternalInterfaceFunctionalMockupUnitImportToActuator_Impl::setFMUVariableName(const std::string& fMUVariableName) {
  const bool result = setString(openstudio::ExternalInterface_FunctionalMockupUnitImport_To_ActuatorFields::FMUVariableName, fMUVariableName);
  OS_ASSERT(result);
  return result;
}

double ExternalInterfaceFunctionalMockupUnitImportToActuator_Impl::initialValue() const {
  const auto value = getDouble(openstudio::ExternalInterface_FunctionalMockupUnitImport_To_ActuatorFields::InitialValue, true);
  OS_ASSERT(value);
  return *value;
}

bool ExternalInterfaceFunctionalMockupUnitImportToActuator_Impl::setInitialValue(double initialValue) {
  const bool result = setDouble(openstudio::ExternalInterface_FunctionalMockupUnitImport_To_ActuatorFields::InitialValue, initialValue);
  OS_ASSERT(result);
  return result;
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
