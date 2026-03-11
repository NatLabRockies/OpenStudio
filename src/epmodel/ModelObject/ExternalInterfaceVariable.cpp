/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ExternalInterfaceVariable.hpp"
#include "ExternalInterfaceVariable_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/ExternalInterface_Variable_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

ExternalInterfaceVariable::ExternalInterfaceVariable(const Model& model, const std::string& variableName, double initialValue)
  : ModelObject(ExternalInterfaceVariable::iddObjectType(), model) {
  const bool ok = setName(variableName).has_value();
  OS_ASSERT(ok);
  OS_ASSERT(variableName == nameString());
  OS_ASSERT(setInitialValue(initialValue));
}

ExternalInterfaceVariable::ExternalInterfaceVariable(std::shared_ptr<detail::ExternalInterfaceVariable_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType ExternalInterfaceVariable::iddObjectType() {
  return IddObjectType::ExternalInterface_Variable;
}

double ExternalInterfaceVariable::initialValue() const {
  return getImpl<detail::ExternalInterfaceVariable_Impl>()->initialValue();
}

bool ExternalInterfaceVariable::setInitialValue(double initialValue) {
  return getImpl<detail::ExternalInterfaceVariable_Impl>()->setInitialValue(initialValue);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

double ExternalInterfaceVariable_Impl::initialValue() const {
  const auto value = getDouble(openstudio::ExternalInterface_VariableFields::InitialValue, true);
  OS_ASSERT(value);
  return *value;
}

bool ExternalInterfaceVariable_Impl::setInitialValue(double initialValue) {
  const bool result = setDouble(openstudio::ExternalInterface_VariableFields::InitialValue, initialValue);
  OS_ASSERT(result);
  return result;
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
