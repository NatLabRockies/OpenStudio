/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ExternalInterfaceFunctionalMockupUnitExportToActuator.hpp"
#include "ExternalInterfaceFunctionalMockupUnitExportToActuator_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/ExternalInterface_FunctionalMockupUnitExport_To_Actuator_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

ExternalInterfaceFunctionalMockupUnitExportToActuator::ExternalInterfaceFunctionalMockupUnitExportToActuator(const Model& model)
  : ModelObject(ExternalInterfaceFunctionalMockupUnitExportToActuator::iddObjectType(), model) {}

ExternalInterfaceFunctionalMockupUnitExportToActuator::ExternalInterfaceFunctionalMockupUnitExportToActuator(
  std::shared_ptr<detail::ExternalInterfaceFunctionalMockupUnitExportToActuator_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType ExternalInterfaceFunctionalMockupUnitExportToActuator::iddObjectType() {
  return IddObjectType::ExternalInterface_FunctionalMockupUnitExport_To_Actuator;
}

std::string ExternalInterfaceFunctionalMockupUnitExportToActuator::actuatedComponentType() const {
  return getImpl<detail::ExternalInterfaceFunctionalMockupUnitExportToActuator_Impl>()->actuatedComponentType();
}

bool ExternalInterfaceFunctionalMockupUnitExportToActuator::setActuatedComponentType(const std::string& actuatedComponentType) {
  return getImpl<detail::ExternalInterfaceFunctionalMockupUnitExportToActuator_Impl>()->setActuatedComponentType(actuatedComponentType);
}

std::string ExternalInterfaceFunctionalMockupUnitExportToActuator::actuatedComponentControlType() const {
  return getImpl<detail::ExternalInterfaceFunctionalMockupUnitExportToActuator_Impl>()->actuatedComponentControlType();
}

bool ExternalInterfaceFunctionalMockupUnitExportToActuator::setActuatedComponentControlType(const std::string& actuatedComponentControlType) {
  return getImpl<detail::ExternalInterfaceFunctionalMockupUnitExportToActuator_Impl>()->setActuatedComponentControlType(
    actuatedComponentControlType);
}

std::string ExternalInterfaceFunctionalMockupUnitExportToActuator::fMUVariableName() const {
  return getImpl<detail::ExternalInterfaceFunctionalMockupUnitExportToActuator_Impl>()->fMUVariableName();
}

bool ExternalInterfaceFunctionalMockupUnitExportToActuator::setFMUVariableName(const std::string& fMUVariableName) {
  return getImpl<detail::ExternalInterfaceFunctionalMockupUnitExportToActuator_Impl>()->setFMUVariableName(fMUVariableName);
}

boost::optional<double> ExternalInterfaceFunctionalMockupUnitExportToActuator::initialValue() const {
  return getImpl<detail::ExternalInterfaceFunctionalMockupUnitExportToActuator_Impl>()->initialValue();
}

bool ExternalInterfaceFunctionalMockupUnitExportToActuator::setInitialValue(double initialValue) {
  return getImpl<detail::ExternalInterfaceFunctionalMockupUnitExportToActuator_Impl>()->setInitialValue(initialValue);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string ExternalInterfaceFunctionalMockupUnitExportToActuator_Impl::actuatedComponentType() const {
  const auto value = getString(openstudio::ExternalInterface_FunctionalMockupUnitExport_To_ActuatorFields::ActuatedComponentType, true);
  OS_ASSERT(value);
  return *value;
}

bool ExternalInterfaceFunctionalMockupUnitExportToActuator_Impl::setActuatedComponentType(const std::string& actuatedComponentType) {
  const bool result = setString(openstudio::ExternalInterface_FunctionalMockupUnitExport_To_ActuatorFields::ActuatedComponentType,
                                actuatedComponentType);
  OS_ASSERT(result);
  return result;
}

std::string ExternalInterfaceFunctionalMockupUnitExportToActuator_Impl::actuatedComponentControlType() const {
  const auto value =
    getString(openstudio::ExternalInterface_FunctionalMockupUnitExport_To_ActuatorFields::ActuatedComponentControlType, true);
  OS_ASSERT(value);
  return *value;
}

bool ExternalInterfaceFunctionalMockupUnitExportToActuator_Impl::setActuatedComponentControlType(
  const std::string& actuatedComponentControlType) {
  const bool result = setString(openstudio::ExternalInterface_FunctionalMockupUnitExport_To_ActuatorFields::ActuatedComponentControlType,
                                actuatedComponentControlType);
  OS_ASSERT(result);
  return result;
}

std::string ExternalInterfaceFunctionalMockupUnitExportToActuator_Impl::fMUVariableName() const {
  const auto value = getString(openstudio::ExternalInterface_FunctionalMockupUnitExport_To_ActuatorFields::FMUVariableName, true);
  OS_ASSERT(value);
  return *value;
}

bool ExternalInterfaceFunctionalMockupUnitExportToActuator_Impl::setFMUVariableName(const std::string& fMUVariableName) {
  const bool result = setString(openstudio::ExternalInterface_FunctionalMockupUnitExport_To_ActuatorFields::FMUVariableName, fMUVariableName);
  OS_ASSERT(result);
  return result;
}

boost::optional<double> ExternalInterfaceFunctionalMockupUnitExportToActuator_Impl::initialValue() const {
  return getDouble(openstudio::ExternalInterface_FunctionalMockupUnitExport_To_ActuatorFields::InitialValue, true);
}

bool ExternalInterfaceFunctionalMockupUnitExportToActuator_Impl::setInitialValue(double initialValue) {
  const bool result = setDouble(openstudio::ExternalInterface_FunctionalMockupUnitExport_To_ActuatorFields::InitialValue, initialValue);
  OS_ASSERT(result);
  return result;
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
