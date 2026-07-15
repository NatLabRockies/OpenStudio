/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ExternalInterfaceFunctionalMockupUnitImportFromVariable.hpp"
#include "ExternalInterfaceFunctionalMockupUnitImportFromVariable_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/ExternalInterface_FunctionalMockupUnitImport_From_Variable_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

#include <stdexcept>

namespace openstudio {
namespace epmodel {

  ExternalInterfaceFunctionalMockupUnitImportFromVariable::ExternalInterfaceFunctionalMockupUnitImportFromVariable(
    const Model& model, const std::string& outputVariableIndexKeyName, const std::string& outputVariableName, const std::string& fMUInstanceName,
    const std::string& fMUVariableName)
    : ModelObject(ExternalInterfaceFunctionalMockupUnitImportFromVariable::iddObjectType(), model) {
    OS_ASSERT(setOutputVariableIndexKeyName(outputVariableIndexKeyName));
    const bool ok = setOutputVariableName(outputVariableName);
    if (!ok) {
      remove();
      throw std::runtime_error("Unable to set Output Variable Name for ExternalInterfaceFunctionalMockupUnitImportFromVariable.");
    }
    OS_ASSERT(setFMUInstanceName(fMUInstanceName));
    OS_ASSERT(setFMUVariableName(fMUVariableName));
  }

  ExternalInterfaceFunctionalMockupUnitImportFromVariable::ExternalInterfaceFunctionalMockupUnitImportFromVariable(
    std::shared_ptr<detail::ExternalInterfaceFunctionalMockupUnitImportFromVariable_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType ExternalInterfaceFunctionalMockupUnitImportFromVariable::iddObjectType() {
    return IddObjectType::ExternalInterface_FunctionalMockupUnitImport_From_Variable;
  }

  std::string ExternalInterfaceFunctionalMockupUnitImportFromVariable::outputVariableIndexKeyName() const {
    return getImpl<detail::ExternalInterfaceFunctionalMockupUnitImportFromVariable_Impl>()->outputVariableIndexKeyName();
  }

  bool ExternalInterfaceFunctionalMockupUnitImportFromVariable::setOutputVariableIndexKeyName(const std::string& outputVariableIndexKeyName) {
    return getImpl<detail::ExternalInterfaceFunctionalMockupUnitImportFromVariable_Impl>()->setOutputVariableIndexKeyName(outputVariableIndexKeyName);
  }

  std::string ExternalInterfaceFunctionalMockupUnitImportFromVariable::outputVariableName() const {
    return getImpl<detail::ExternalInterfaceFunctionalMockupUnitImportFromVariable_Impl>()->outputVariableName();
  }

  bool ExternalInterfaceFunctionalMockupUnitImportFromVariable::setOutputVariableName(const std::string& outputVariableName) {
    return getImpl<detail::ExternalInterfaceFunctionalMockupUnitImportFromVariable_Impl>()->setOutputVariableName(outputVariableName);
  }

  std::string ExternalInterfaceFunctionalMockupUnitImportFromVariable::fMUInstanceName() const {
    return getImpl<detail::ExternalInterfaceFunctionalMockupUnitImportFromVariable_Impl>()->fMUInstanceName();
  }

  bool ExternalInterfaceFunctionalMockupUnitImportFromVariable::setFMUInstanceName(const std::string& fMUInstanceName) {
    return getImpl<detail::ExternalInterfaceFunctionalMockupUnitImportFromVariable_Impl>()->setFMUInstanceName(fMUInstanceName);
  }

  std::string ExternalInterfaceFunctionalMockupUnitImportFromVariable::fMUVariableName() const {
    return getImpl<detail::ExternalInterfaceFunctionalMockupUnitImportFromVariable_Impl>()->fMUVariableName();
  }

  bool ExternalInterfaceFunctionalMockupUnitImportFromVariable::setFMUVariableName(const std::string& fMUVariableName) {
    return getImpl<detail::ExternalInterfaceFunctionalMockupUnitImportFromVariable_Impl>()->setFMUVariableName(fMUVariableName);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string ExternalInterfaceFunctionalMockupUnitImportFromVariable_Impl::outputVariableIndexKeyName() const {
      const auto value = getString(openstudio::ExternalInterface_FunctionalMockupUnitImport_From_VariableFields::Output_VariableIndexKeyName, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ExternalInterfaceFunctionalMockupUnitImportFromVariable_Impl::setOutputVariableIndexKeyName(const std::string& outputVariableIndexKeyName) {
      const bool result = setString(openstudio::ExternalInterface_FunctionalMockupUnitImport_From_VariableFields::Output_VariableIndexKeyName,
                                    outputVariableIndexKeyName);
      OS_ASSERT(result);
      return result;
    }

    std::string ExternalInterfaceFunctionalMockupUnitImportFromVariable_Impl::outputVariableName() const {
      const auto value = getString(openstudio::ExternalInterface_FunctionalMockupUnitImport_From_VariableFields::Output_VariableName, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ExternalInterfaceFunctionalMockupUnitImportFromVariable_Impl::setOutputVariableName(const std::string& outputVariableName) {
      return setString(openstudio::ExternalInterface_FunctionalMockupUnitImport_From_VariableFields::Output_VariableName, outputVariableName);
    }

    std::string ExternalInterfaceFunctionalMockupUnitImportFromVariable_Impl::fMUInstanceName() const {
      const auto value = getString(openstudio::ExternalInterface_FunctionalMockupUnitImport_From_VariableFields::FMUInstanceName, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ExternalInterfaceFunctionalMockupUnitImportFromVariable_Impl::setFMUInstanceName(const std::string& fMUInstanceName) {
      const bool result = setString(openstudio::ExternalInterface_FunctionalMockupUnitImport_From_VariableFields::FMUInstanceName, fMUInstanceName);
      OS_ASSERT(result);
      return result;
    }

    std::string ExternalInterfaceFunctionalMockupUnitImportFromVariable_Impl::fMUVariableName() const {
      const auto value = getString(openstudio::ExternalInterface_FunctionalMockupUnitImport_From_VariableFields::FMUVariableName, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ExternalInterfaceFunctionalMockupUnitImportFromVariable_Impl::setFMUVariableName(const std::string& fMUVariableName) {
      const bool result = setString(openstudio::ExternalInterface_FunctionalMockupUnitImport_From_VariableFields::FMUVariableName, fMUVariableName);
      OS_ASSERT(result);
      return result;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
