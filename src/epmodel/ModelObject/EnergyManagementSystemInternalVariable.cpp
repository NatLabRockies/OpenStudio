/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "EnergyManagementSystemInternalVariable.hpp"
#include "EnergyManagementSystemInternalVariable_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/EnergyManagementSystem_InternalVariable_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

#include <stdexcept>

namespace openstudio {
namespace epmodel {

EnergyManagementSystemInternalVariable::EnergyManagementSystemInternalVariable(const Model& model, const std::string& internalDataType)
  : ModelObject(EnergyManagementSystemInternalVariable::iddObjectType(), model) {
  OS_ASSERT(getImpl<detail::EnergyManagementSystemInternalVariable_Impl>());
  bool ok = setInternalDataType(internalDataType);
  if (!ok) {
    remove();
    throw std::runtime_error("Unable to set EnergyManagementSystemInternalVariable Internal Data Type to '" + internalDataType + "'.");
  }
}

EnergyManagementSystemInternalVariable::EnergyManagementSystemInternalVariable(
  std::shared_ptr<detail::EnergyManagementSystemInternalVariable_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType EnergyManagementSystemInternalVariable::iddObjectType() {
  return IddObjectType::EnergyManagementSystem_InternalVariable;
}

std::string EnergyManagementSystemInternalVariable::internalDataIndexKeyName() const {
  return getImpl<detail::EnergyManagementSystemInternalVariable_Impl>()->internalDataIndexKeyName();
}

bool EnergyManagementSystemInternalVariable::setInternalDataIndexKeyName(const std::string& internalDataIndexKeyName) {
  return getImpl<detail::EnergyManagementSystemInternalVariable_Impl>()->setInternalDataIndexKeyName(internalDataIndexKeyName);
}

void EnergyManagementSystemInternalVariable::resetInternalDataIndexKeyName() {
  getImpl<detail::EnergyManagementSystemInternalVariable_Impl>()->resetInternalDataIndexKeyName();
}

std::string EnergyManagementSystemInternalVariable::internalDataType() const {
  return getImpl<detail::EnergyManagementSystemInternalVariable_Impl>()->internalDataType();
}

bool EnergyManagementSystemInternalVariable::setInternalDataType(const std::string& internalDataType) {
  return getImpl<detail::EnergyManagementSystemInternalVariable_Impl>()->setInternalDataType(internalDataType);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string EnergyManagementSystemInternalVariable_Impl::internalDataIndexKeyName() const {
  const auto value = getString(openstudio::EnergyManagementSystem_InternalVariableFields::InternalDataIndexKeyName, true);
  if (value) {
    return *value;
  }
  return "";
}

bool EnergyManagementSystemInternalVariable_Impl::setInternalDataIndexKeyName(const std::string& internalDataIndexKeyName) {
  const bool result = setString(openstudio::EnergyManagementSystem_InternalVariableFields::InternalDataIndexKeyName, internalDataIndexKeyName);
  OS_ASSERT(result);
  return result;
}

void EnergyManagementSystemInternalVariable_Impl::resetInternalDataIndexKeyName() {
  const bool result = setString(openstudio::EnergyManagementSystem_InternalVariableFields::InternalDataIndexKeyName, "");
  OS_ASSERT(result);
}

std::string EnergyManagementSystemInternalVariable_Impl::internalDataType() const {
  const auto value = getString(openstudio::EnergyManagementSystem_InternalVariableFields::InternalDataType, true);
  OS_ASSERT(value);
  return *value;
}

bool EnergyManagementSystemInternalVariable_Impl::setInternalDataType(const std::string& internalDataType) {
  const bool result = setString(openstudio::EnergyManagementSystem_InternalVariableFields::InternalDataType, internalDataType);
  OS_ASSERT(result);
  return result;
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
