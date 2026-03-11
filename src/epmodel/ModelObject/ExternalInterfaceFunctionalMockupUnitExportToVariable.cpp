/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ExternalInterfaceFunctionalMockupUnitExportToVariable.hpp"
#include "ExternalInterfaceFunctionalMockupUnitExportToVariable_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/ExternalInterface_FunctionalMockupUnitExport_To_Variable_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

ExternalInterfaceFunctionalMockupUnitExportToVariable::ExternalInterfaceFunctionalMockupUnitExportToVariable(
  const Model& model, const std::string& fMUVariableName, double initialValue)
  : ModelObject(ExternalInterfaceFunctionalMockupUnitExportToVariable::iddObjectType(), model) {
  OS_ASSERT(setFMUVariableName(fMUVariableName));
  OS_ASSERT(setInitialValue(initialValue));
}

ExternalInterfaceFunctionalMockupUnitExportToVariable::ExternalInterfaceFunctionalMockupUnitExportToVariable(
  std::shared_ptr<detail::ExternalInterfaceFunctionalMockupUnitExportToVariable_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType ExternalInterfaceFunctionalMockupUnitExportToVariable::iddObjectType() {
  return IddObjectType::ExternalInterface_FunctionalMockupUnitExport_To_Variable;
}

std::string ExternalInterfaceFunctionalMockupUnitExportToVariable::fMUVariableName() const {
  return getImpl<detail::ExternalInterfaceFunctionalMockupUnitExportToVariable_Impl>()->fMUVariableName();
}

bool ExternalInterfaceFunctionalMockupUnitExportToVariable::setFMUVariableName(const std::string& fMUVariableName) {
  return getImpl<detail::ExternalInterfaceFunctionalMockupUnitExportToVariable_Impl>()->setFMUVariableName(fMUVariableName);
}

double ExternalInterfaceFunctionalMockupUnitExportToVariable::initialValue() const {
  return getImpl<detail::ExternalInterfaceFunctionalMockupUnitExportToVariable_Impl>()->initialValue();
}

bool ExternalInterfaceFunctionalMockupUnitExportToVariable::setInitialValue(double initialValue) {
  return getImpl<detail::ExternalInterfaceFunctionalMockupUnitExportToVariable_Impl>()->setInitialValue(initialValue);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string ExternalInterfaceFunctionalMockupUnitExportToVariable_Impl::fMUVariableName() const {
  const auto value = getString(openstudio::ExternalInterface_FunctionalMockupUnitExport_To_VariableFields::FMUVariableName, true);
  OS_ASSERT(value);
  return *value;
}

bool ExternalInterfaceFunctionalMockupUnitExportToVariable_Impl::setFMUVariableName(const std::string& fMUVariableName) {
  const bool result = setString(openstudio::ExternalInterface_FunctionalMockupUnitExport_To_VariableFields::FMUVariableName, fMUVariableName);
  OS_ASSERT(result);
  return result;
}

double ExternalInterfaceFunctionalMockupUnitExportToVariable_Impl::initialValue() const {
  const auto value = getDouble(openstudio::ExternalInterface_FunctionalMockupUnitExport_To_VariableFields::InitialValue, true);
  OS_ASSERT(value);
  return *value;
}

bool ExternalInterfaceFunctionalMockupUnitExportToVariable_Impl::setInitialValue(double initialValue) {
  const bool result = setDouble(openstudio::ExternalInterface_FunctionalMockupUnitExport_To_VariableFields::InitialValue, initialValue);
  OS_ASSERT(result);
  return result;
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
