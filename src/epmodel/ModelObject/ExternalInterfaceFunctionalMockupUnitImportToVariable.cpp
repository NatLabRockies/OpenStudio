/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ExternalInterfaceFunctionalMockupUnitImportToVariable.hpp"
#include "ExternalInterfaceFunctionalMockupUnitImportToVariable_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/ExternalInterface_FunctionalMockupUnitImport_To_Variable_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  ExternalInterfaceFunctionalMockupUnitImportToVariable::ExternalInterfaceFunctionalMockupUnitImportToVariable(const Model& model)
    : ModelObject(ExternalInterfaceFunctionalMockupUnitImportToVariable::iddObjectType(), model) {}

  ExternalInterfaceFunctionalMockupUnitImportToVariable::ExternalInterfaceFunctionalMockupUnitImportToVariable(
    std::shared_ptr<detail::ExternalInterfaceFunctionalMockupUnitImportToVariable_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType ExternalInterfaceFunctionalMockupUnitImportToVariable::iddObjectType() {
    return IddObjectType::ExternalInterface_FunctionalMockupUnitImport_To_Variable;
  }

  std::string ExternalInterfaceFunctionalMockupUnitImportToVariable::fMUInstanceName() const {
    return getImpl<detail::ExternalInterfaceFunctionalMockupUnitImportToVariable_Impl>()->fMUInstanceName();
  }

  bool ExternalInterfaceFunctionalMockupUnitImportToVariable::setFMUInstanceName(const std::string& fMUInstanceName) {
    return getImpl<detail::ExternalInterfaceFunctionalMockupUnitImportToVariable_Impl>()->setFMUInstanceName(fMUInstanceName);
  }

  std::string ExternalInterfaceFunctionalMockupUnitImportToVariable::fMUVariableName() const {
    return getImpl<detail::ExternalInterfaceFunctionalMockupUnitImportToVariable_Impl>()->fMUVariableName();
  }

  bool ExternalInterfaceFunctionalMockupUnitImportToVariable::setFMUVariableName(const std::string& fMUVariableName) {
    return getImpl<detail::ExternalInterfaceFunctionalMockupUnitImportToVariable_Impl>()->setFMUVariableName(fMUVariableName);
  }

  double ExternalInterfaceFunctionalMockupUnitImportToVariable::initialValue() const {
    return getImpl<detail::ExternalInterfaceFunctionalMockupUnitImportToVariable_Impl>()->initialValue();
  }

  bool ExternalInterfaceFunctionalMockupUnitImportToVariable::setInitialValue(double initialValue) {
    return getImpl<detail::ExternalInterfaceFunctionalMockupUnitImportToVariable_Impl>()->setInitialValue(initialValue);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string ExternalInterfaceFunctionalMockupUnitImportToVariable_Impl::fMUInstanceName() const {
      const auto value = getString(openstudio::ExternalInterface_FunctionalMockupUnitImport_To_VariableFields::FMUInstanceName, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ExternalInterfaceFunctionalMockupUnitImportToVariable_Impl::setFMUInstanceName(const std::string& fMUInstanceName) {
      const bool result = setString(openstudio::ExternalInterface_FunctionalMockupUnitImport_To_VariableFields::FMUInstanceName, fMUInstanceName);
      OS_ASSERT(result);
      return result;
    }

    std::string ExternalInterfaceFunctionalMockupUnitImportToVariable_Impl::fMUVariableName() const {
      const auto value = getString(openstudio::ExternalInterface_FunctionalMockupUnitImport_To_VariableFields::FMUVariableName, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ExternalInterfaceFunctionalMockupUnitImportToVariable_Impl::setFMUVariableName(const std::string& fMUVariableName) {
      const bool result = setString(openstudio::ExternalInterface_FunctionalMockupUnitImport_To_VariableFields::FMUVariableName, fMUVariableName);
      OS_ASSERT(result);
      return result;
    }

    double ExternalInterfaceFunctionalMockupUnitImportToVariable_Impl::initialValue() const {
      const auto value = getDouble(openstudio::ExternalInterface_FunctionalMockupUnitImport_To_VariableFields::InitialValue, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ExternalInterfaceFunctionalMockupUnitImportToVariable_Impl::setInitialValue(double initialValue) {
      const bool result = setDouble(openstudio::ExternalInterface_FunctionalMockupUnitImport_To_VariableFields::InitialValue, initialValue);
      OS_ASSERT(result);
      return result;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
