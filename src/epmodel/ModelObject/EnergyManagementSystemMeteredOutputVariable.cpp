/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "EnergyManagementSystemMeteredOutputVariable.hpp"
#include "EnergyManagementSystemMeteredOutputVariable_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/EnergyManagementSystem_MeteredOutputVariable_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

#include <stdexcept>

namespace openstudio {
namespace epmodel {

EnergyManagementSystemMeteredOutputVariable::EnergyManagementSystemMeteredOutputVariable(const Model& model, const std::string& eMSVariableName)
  : ModelObject(EnergyManagementSystemMeteredOutputVariable::iddObjectType(), model) {
  OS_ASSERT(getImpl<detail::EnergyManagementSystemMeteredOutputVariable_Impl>());
  const bool ok = setEMSVariableName(eMSVariableName);
  if (!ok) {
    remove();
    throw std::runtime_error("Unable to set EnergyManagementSystemMeteredOutputVariable EMS Variable Name to '" + eMSVariableName + "'.");
  }

  // Mirror model-side constructor defaults.
  setUpdateFrequency("SystemTimestep");
  setResourceType("Electricity");
  setGroupType("Building");
  setEndUseCategory("Fans");
}

EnergyManagementSystemMeteredOutputVariable::EnergyManagementSystemMeteredOutputVariable(
  std::shared_ptr<detail::EnergyManagementSystemMeteredOutputVariable_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType EnergyManagementSystemMeteredOutputVariable::iddObjectType() {
  return IddObjectType::EnergyManagementSystem_MeteredOutputVariable;
}

std::vector<std::string> EnergyManagementSystemMeteredOutputVariable::updateFrequencyValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::EnergyManagementSystem_MeteredOutputVariableFields::UpdateFrequency);
}

std::vector<std::string> EnergyManagementSystemMeteredOutputVariable::resourceTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::EnergyManagementSystem_MeteredOutputVariableFields::ResourceType);
}

std::vector<std::string> EnergyManagementSystemMeteredOutputVariable::groupTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::EnergyManagementSystem_MeteredOutputVariableFields::GroupType);
}

std::vector<std::string> EnergyManagementSystemMeteredOutputVariable::endUseCategoryValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::EnergyManagementSystem_MeteredOutputVariableFields::EndUseCategory);
}

std::string EnergyManagementSystemMeteredOutputVariable::emsVariableName() const {
  return getImpl<detail::EnergyManagementSystemMeteredOutputVariable_Impl>()->emsVariableName();
}

bool EnergyManagementSystemMeteredOutputVariable::setEMSVariableName(const std::string& eMSVariableName) {
  return getImpl<detail::EnergyManagementSystemMeteredOutputVariable_Impl>()->setEMSVariableName(eMSVariableName);
}

std::string EnergyManagementSystemMeteredOutputVariable::updateFrequency() const {
  return getImpl<detail::EnergyManagementSystemMeteredOutputVariable_Impl>()->updateFrequency();
}

bool EnergyManagementSystemMeteredOutputVariable::setUpdateFrequency(const std::string& updateFrequency) {
  return getImpl<detail::EnergyManagementSystemMeteredOutputVariable_Impl>()->setUpdateFrequency(updateFrequency);
}

std::string EnergyManagementSystemMeteredOutputVariable::resourceType() const {
  return getImpl<detail::EnergyManagementSystemMeteredOutputVariable_Impl>()->resourceType();
}

bool EnergyManagementSystemMeteredOutputVariable::setResourceType(const std::string& resourceType) {
  return getImpl<detail::EnergyManagementSystemMeteredOutputVariable_Impl>()->setResourceType(resourceType);
}

std::string EnergyManagementSystemMeteredOutputVariable::groupType() const {
  return getImpl<detail::EnergyManagementSystemMeteredOutputVariable_Impl>()->groupType();
}

bool EnergyManagementSystemMeteredOutputVariable::setGroupType(const std::string& groupType) {
  return getImpl<detail::EnergyManagementSystemMeteredOutputVariable_Impl>()->setGroupType(groupType);
}

std::string EnergyManagementSystemMeteredOutputVariable::endUseCategory() const {
  return getImpl<detail::EnergyManagementSystemMeteredOutputVariable_Impl>()->endUseCategory();
}

bool EnergyManagementSystemMeteredOutputVariable::setEndUseCategory(const std::string& endUseCategory) {
  return getImpl<detail::EnergyManagementSystemMeteredOutputVariable_Impl>()->setEndUseCategory(endUseCategory);
}

std::string EnergyManagementSystemMeteredOutputVariable::endUseSubcategory() const {
  return getImpl<detail::EnergyManagementSystemMeteredOutputVariable_Impl>()->endUseSubcategory();
}

bool EnergyManagementSystemMeteredOutputVariable::setEndUseSubcategory(const std::string& endUseSubcategory) {
  return getImpl<detail::EnergyManagementSystemMeteredOutputVariable_Impl>()->setEndUseSubcategory(endUseSubcategory);
}

void EnergyManagementSystemMeteredOutputVariable::resetEndUseSubcategory() {
  getImpl<detail::EnergyManagementSystemMeteredOutputVariable_Impl>()->resetEndUseSubcategory();
}

std::string EnergyManagementSystemMeteredOutputVariable::units() const {
  return getImpl<detail::EnergyManagementSystemMeteredOutputVariable_Impl>()->units();
}

bool EnergyManagementSystemMeteredOutputVariable::setUnits(const std::string& units) {
  return getImpl<detail::EnergyManagementSystemMeteredOutputVariable_Impl>()->setUnits(units);
}

void EnergyManagementSystemMeteredOutputVariable::resetUnits() {
  getImpl<detail::EnergyManagementSystemMeteredOutputVariable_Impl>()->resetUnits();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string EnergyManagementSystemMeteredOutputVariable_Impl::emsVariableName() const {
  const auto value = getString(openstudio::EnergyManagementSystem_MeteredOutputVariableFields::EMSVariableName, true);
  OS_ASSERT(value);
  return *value;
}

bool EnergyManagementSystemMeteredOutputVariable_Impl::setEMSVariableName(const std::string& eMSVariableName) {
  return setString(openstudio::EnergyManagementSystem_MeteredOutputVariableFields::EMSVariableName, eMSVariableName);
}

std::string EnergyManagementSystemMeteredOutputVariable_Impl::updateFrequency() const {
  const auto value = getString(openstudio::EnergyManagementSystem_MeteredOutputVariableFields::UpdateFrequency, true);
  OS_ASSERT(value);
  return *value;
}

bool EnergyManagementSystemMeteredOutputVariable_Impl::setUpdateFrequency(const std::string& updateFrequency) {
  return setString(openstudio::EnergyManagementSystem_MeteredOutputVariableFields::UpdateFrequency, updateFrequency);
}

std::string EnergyManagementSystemMeteredOutputVariable_Impl::resourceType() const {
  const auto value = getString(openstudio::EnergyManagementSystem_MeteredOutputVariableFields::ResourceType, true);
  OS_ASSERT(value);
  return *value;
}

bool EnergyManagementSystemMeteredOutputVariable_Impl::setResourceType(const std::string& resourceType) {
  return setString(openstudio::EnergyManagementSystem_MeteredOutputVariableFields::ResourceType, resourceType);
}

std::string EnergyManagementSystemMeteredOutputVariable_Impl::groupType() const {
  const auto value = getString(openstudio::EnergyManagementSystem_MeteredOutputVariableFields::GroupType, true);
  OS_ASSERT(value);
  return *value;
}

bool EnergyManagementSystemMeteredOutputVariable_Impl::setGroupType(const std::string& groupType) {
  return setString(openstudio::EnergyManagementSystem_MeteredOutputVariableFields::GroupType, groupType);
}

std::string EnergyManagementSystemMeteredOutputVariable_Impl::endUseCategory() const {
  const auto value = getString(openstudio::EnergyManagementSystem_MeteredOutputVariableFields::EndUseCategory, true);
  OS_ASSERT(value);
  return *value;
}

bool EnergyManagementSystemMeteredOutputVariable_Impl::setEndUseCategory(const std::string& endUseCategory) {
  return setString(openstudio::EnergyManagementSystem_MeteredOutputVariableFields::EndUseCategory, endUseCategory);
}

std::string EnergyManagementSystemMeteredOutputVariable_Impl::endUseSubcategory() const {
  const auto value = getString(openstudio::EnergyManagementSystem_MeteredOutputVariableFields::EndUseSubcategory, true);
  if (value) {
    return *value;
  }
  return "";
}

bool EnergyManagementSystemMeteredOutputVariable_Impl::setEndUseSubcategory(const std::string& endUseSubcategory) {
  return setString(openstudio::EnergyManagementSystem_MeteredOutputVariableFields::EndUseSubcategory, endUseSubcategory);
}

void EnergyManagementSystemMeteredOutputVariable_Impl::resetEndUseSubcategory() {
  const bool result = setString(openstudio::EnergyManagementSystem_MeteredOutputVariableFields::EndUseSubcategory, "");
  OS_ASSERT(result);
}

std::string EnergyManagementSystemMeteredOutputVariable_Impl::units() const {
  const auto value = getString(openstudio::EnergyManagementSystem_MeteredOutputVariableFields::Units, true);
  if (value) {
    return *value;
  }
  return "";
}

bool EnergyManagementSystemMeteredOutputVariable_Impl::setUnits(const std::string& units) {
  return setString(openstudio::EnergyManagementSystem_MeteredOutputVariableFields::Units, units);
}

void EnergyManagementSystemMeteredOutputVariable_Impl::resetUnits() {
  const bool result = setString(openstudio::EnergyManagementSystem_MeteredOutputVariableFields::Units, "");
  OS_ASSERT(result);
}

std::vector<std::string> EnergyManagementSystemMeteredOutputVariable_Impl::updateFrequencyValues() const {
  return openstudio::epmodel::EnergyManagementSystemMeteredOutputVariable::updateFrequencyValues();
}

std::vector<std::string> EnergyManagementSystemMeteredOutputVariable_Impl::resourceTypeValues() const {
  return openstudio::epmodel::EnergyManagementSystemMeteredOutputVariable::resourceTypeValues();
}

std::vector<std::string> EnergyManagementSystemMeteredOutputVariable_Impl::groupTypeValues() const {
  return openstudio::epmodel::EnergyManagementSystemMeteredOutputVariable::groupTypeValues();
}

std::vector<std::string> EnergyManagementSystemMeteredOutputVariable_Impl::endUseCategoryValues() const {
  return openstudio::epmodel::EnergyManagementSystemMeteredOutputVariable::endUseCategoryValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
