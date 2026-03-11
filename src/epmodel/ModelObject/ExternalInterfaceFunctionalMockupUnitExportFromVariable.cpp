/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ExternalInterfaceFunctionalMockupUnitExportFromVariable.hpp"
#include "ExternalInterfaceFunctionalMockupUnitExportFromVariable_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/ExternalInterface_FunctionalMockupUnitExport_From_Variable_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

#include <stdexcept>

namespace openstudio {
namespace epmodel {

ExternalInterfaceFunctionalMockupUnitExportFromVariable::ExternalInterfaceFunctionalMockupUnitExportFromVariable(
  const Model& model, const std::string& outputVariableIndexKeyName, const std::string& outputVariableName, const std::string& fMUVariableName)
  : ModelObject(ExternalInterfaceFunctionalMockupUnitExportFromVariable::iddObjectType(), model) {
  OS_ASSERT(setOutputVariableIndexKeyName(outputVariableIndexKeyName));
  const bool ok = setOutputVariableName(outputVariableName);
  if (!ok) {
    remove();
    throw std::runtime_error("Unable to set Output Variable Name for ExternalInterfaceFunctionalMockupUnitExportFromVariable.");
  }
  OS_ASSERT(setFMUVariableName(fMUVariableName));
}

ExternalInterfaceFunctionalMockupUnitExportFromVariable::ExternalInterfaceFunctionalMockupUnitExportFromVariable(
  std::shared_ptr<detail::ExternalInterfaceFunctionalMockupUnitExportFromVariable_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType ExternalInterfaceFunctionalMockupUnitExportFromVariable::iddObjectType() {
  return IddObjectType::ExternalInterface_FunctionalMockupUnitExport_From_Variable;
}

std::string ExternalInterfaceFunctionalMockupUnitExportFromVariable::outputVariableIndexKeyName() const {
  return getImpl<detail::ExternalInterfaceFunctionalMockupUnitExportFromVariable_Impl>()->outputVariableIndexKeyName();
}

bool ExternalInterfaceFunctionalMockupUnitExportFromVariable::setOutputVariableIndexKeyName(const std::string& outputVariableIndexKeyName) {
  return getImpl<detail::ExternalInterfaceFunctionalMockupUnitExportFromVariable_Impl>()->setOutputVariableIndexKeyName(outputVariableIndexKeyName);
}

std::string ExternalInterfaceFunctionalMockupUnitExportFromVariable::outputVariableName() const {
  return getImpl<detail::ExternalInterfaceFunctionalMockupUnitExportFromVariable_Impl>()->outputVariableName();
}

bool ExternalInterfaceFunctionalMockupUnitExportFromVariable::setOutputVariableName(const std::string& outputVariableName) {
  return getImpl<detail::ExternalInterfaceFunctionalMockupUnitExportFromVariable_Impl>()->setOutputVariableName(outputVariableName);
}

std::string ExternalInterfaceFunctionalMockupUnitExportFromVariable::fMUVariableName() const {
  return getImpl<detail::ExternalInterfaceFunctionalMockupUnitExportFromVariable_Impl>()->fMUVariableName();
}

bool ExternalInterfaceFunctionalMockupUnitExportFromVariable::setFMUVariableName(const std::string& fMUVariableName) {
  return getImpl<detail::ExternalInterfaceFunctionalMockupUnitExportFromVariable_Impl>()->setFMUVariableName(fMUVariableName);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string ExternalInterfaceFunctionalMockupUnitExportFromVariable_Impl::outputVariableIndexKeyName() const {
  const auto value = getString(openstudio::ExternalInterface_FunctionalMockupUnitExport_From_VariableFields::Output_VariableIndexKeyName, true);
  OS_ASSERT(value);
  return *value;
}

bool ExternalInterfaceFunctionalMockupUnitExportFromVariable_Impl::setOutputVariableIndexKeyName(const std::string& outputVariableIndexKeyName) {
  const bool result = setString(openstudio::ExternalInterface_FunctionalMockupUnitExport_From_VariableFields::Output_VariableIndexKeyName,
                                outputVariableIndexKeyName);
  OS_ASSERT(result);
  return result;
}

std::string ExternalInterfaceFunctionalMockupUnitExportFromVariable_Impl::outputVariableName() const {
  const auto value = getString(openstudio::ExternalInterface_FunctionalMockupUnitExport_From_VariableFields::Output_VariableName, true);
  OS_ASSERT(value);
  return *value;
}

bool ExternalInterfaceFunctionalMockupUnitExportFromVariable_Impl::setOutputVariableName(const std::string& outputVariableName) {
  return setString(openstudio::ExternalInterface_FunctionalMockupUnitExport_From_VariableFields::Output_VariableName, outputVariableName);
}

std::string ExternalInterfaceFunctionalMockupUnitExportFromVariable_Impl::fMUVariableName() const {
  const auto value = getString(openstudio::ExternalInterface_FunctionalMockupUnitExport_From_VariableFields::FMUVariableName, true);
  OS_ASSERT(value);
  return *value;
}

bool ExternalInterfaceFunctionalMockupUnitExportFromVariable_Impl::setFMUVariableName(const std::string& fMUVariableName) {
  const bool result = setString(openstudio::ExternalInterface_FunctionalMockupUnitExport_From_VariableFields::FMUVariableName, fMUVariableName);
  OS_ASSERT(result);
  return result;
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
