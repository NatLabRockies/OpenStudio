/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "EnergyManagementSystemOutputVariable.hpp"
#include "EnergyManagementSystemOutputVariable_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/EnergyManagementSystem_OutputVariable_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

#include <stdexcept>

namespace openstudio {
namespace epmodel {

EnergyManagementSystemOutputVariable::EnergyManagementSystemOutputVariable(const Model& model, const std::string& eMSVariableName)
  : ModelObject(EnergyManagementSystemOutputVariable::iddObjectType(), model) {
  OS_ASSERT(getImpl<detail::EnergyManagementSystemOutputVariable_Impl>());
  const bool ok = setEMSVariableName(eMSVariableName);
  if (!ok) {
    remove();
    throw std::runtime_error("Unable to set EnergyManagementSystemOutputVariable EMS Variable Name to '" + eMSVariableName + "'.");
  }

  // Mirror model-side constructor defaults.
  setUpdateFrequency("ZoneTimestep");
  setTypeOfDataInVariable("Averaged");
}

EnergyManagementSystemOutputVariable::EnergyManagementSystemOutputVariable(
  std::shared_ptr<detail::EnergyManagementSystemOutputVariable_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType EnergyManagementSystemOutputVariable::iddObjectType() {
  return IddObjectType::EnergyManagementSystem_OutputVariable;
}

std::vector<std::string> EnergyManagementSystemOutputVariable::typeOfDataInVariableValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::EnergyManagementSystem_OutputVariableFields::TypeofDatainVariable);
}

std::vector<std::string> EnergyManagementSystemOutputVariable::updateFrequencyValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::EnergyManagementSystem_OutputVariableFields::UpdateFrequency);
}

std::string EnergyManagementSystemOutputVariable::emsVariableName() const {
  return getImpl<detail::EnergyManagementSystemOutputVariable_Impl>()->emsVariableName();
}

bool EnergyManagementSystemOutputVariable::setEMSVariableName(const std::string& eMSVariableName) {
  return getImpl<detail::EnergyManagementSystemOutputVariable_Impl>()->setEMSVariableName(eMSVariableName);
}

std::string EnergyManagementSystemOutputVariable::typeOfDataInVariable() const {
  return getImpl<detail::EnergyManagementSystemOutputVariable_Impl>()->typeOfDataInVariable();
}

bool EnergyManagementSystemOutputVariable::setTypeOfDataInVariable(const std::string& typeofDatainVariable) {
  return getImpl<detail::EnergyManagementSystemOutputVariable_Impl>()->setTypeOfDataInVariable(typeofDatainVariable);
}

std::string EnergyManagementSystemOutputVariable::updateFrequency() const {
  return getImpl<detail::EnergyManagementSystemOutputVariable_Impl>()->updateFrequency();
}

bool EnergyManagementSystemOutputVariable::setUpdateFrequency(const std::string& updateFrequency) {
  return getImpl<detail::EnergyManagementSystemOutputVariable_Impl>()->setUpdateFrequency(updateFrequency);
}

std::string EnergyManagementSystemOutputVariable::units() const {
  return getImpl<detail::EnergyManagementSystemOutputVariable_Impl>()->units();
}

bool EnergyManagementSystemOutputVariable::setUnits(const std::string& units) {
  return getImpl<detail::EnergyManagementSystemOutputVariable_Impl>()->setUnits(units);
}

void EnergyManagementSystemOutputVariable::resetUnits() {
  getImpl<detail::EnergyManagementSystemOutputVariable_Impl>()->resetUnits();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string EnergyManagementSystemOutputVariable_Impl::emsVariableName() const {
  const auto value = getString(openstudio::EnergyManagementSystem_OutputVariableFields::EMSVariableName, true);
  OS_ASSERT(value);
  return *value;
}

bool EnergyManagementSystemOutputVariable_Impl::setEMSVariableName(const std::string& eMSVariableName) {
  const bool result = setString(openstudio::EnergyManagementSystem_OutputVariableFields::EMSVariableName, eMSVariableName);
  OS_ASSERT(result);
  return result;
}

std::string EnergyManagementSystemOutputVariable_Impl::typeOfDataInVariable() const {
  const auto value = getString(openstudio::EnergyManagementSystem_OutputVariableFields::TypeofDatainVariable, true);
  OS_ASSERT(value);
  return *value;
}

bool EnergyManagementSystemOutputVariable_Impl::setTypeOfDataInVariable(const std::string& typeofDatainVariable) {
  return setString(openstudio::EnergyManagementSystem_OutputVariableFields::TypeofDatainVariable, typeofDatainVariable);
}

std::string EnergyManagementSystemOutputVariable_Impl::updateFrequency() const {
  const auto value = getString(openstudio::EnergyManagementSystem_OutputVariableFields::UpdateFrequency, true);
  OS_ASSERT(value);
  return *value;
}

bool EnergyManagementSystemOutputVariable_Impl::setUpdateFrequency(const std::string& updateFrequency) {
  return setString(openstudio::EnergyManagementSystem_OutputVariableFields::UpdateFrequency, updateFrequency);
}

std::string EnergyManagementSystemOutputVariable_Impl::units() const {
  const auto value = getString(openstudio::EnergyManagementSystem_OutputVariableFields::Units, true);
  if (value) {
    return *value;
  }
  return "";
}

bool EnergyManagementSystemOutputVariable_Impl::setUnits(const std::string& units) {
  const bool result = setString(openstudio::EnergyManagementSystem_OutputVariableFields::Units, units);
  OS_ASSERT(result);
  return result;
}

void EnergyManagementSystemOutputVariable_Impl::resetUnits() {
  const bool result = setString(openstudio::EnergyManagementSystem_OutputVariableFields::Units, "");
  OS_ASSERT(result);
}

std::vector<std::string> EnergyManagementSystemOutputVariable_Impl::typeOfDataInVariableValues() const {
  return openstudio::epmodel::EnergyManagementSystemOutputVariable::typeOfDataInVariableValues();
}

std::vector<std::string> EnergyManagementSystemOutputVariable_Impl::updateFrequencyValues() const {
  return openstudio::epmodel::EnergyManagementSystemOutputVariable::updateFrequencyValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
