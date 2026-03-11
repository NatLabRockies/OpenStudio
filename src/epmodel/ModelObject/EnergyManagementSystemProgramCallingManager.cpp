/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "EnergyManagementSystemProgramCallingManager.hpp"
#include "EnergyManagementSystemProgramCallingManager_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/EnergyManagementSystem_ProgramCallingManager_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

EnergyManagementSystemProgramCallingManager::EnergyManagementSystemProgramCallingManager(const Model& model)
  : ModelObject(EnergyManagementSystemProgramCallingManager::iddObjectType(), model) {
  OS_ASSERT(getImpl<detail::EnergyManagementSystemProgramCallingManager_Impl>());

  // Mirror model-side constructor default.
  setCallingPoint("BeginNewEnvironment");
}

EnergyManagementSystemProgramCallingManager::EnergyManagementSystemProgramCallingManager(
  std::shared_ptr<detail::EnergyManagementSystemProgramCallingManager_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType EnergyManagementSystemProgramCallingManager::iddObjectType() {
  return IddObjectType::EnergyManagementSystem_ProgramCallingManager;
}

std::vector<std::string> EnergyManagementSystemProgramCallingManager::validCallingPointValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::EnergyManagementSystem_ProgramCallingManagerFields::EnergyPlusModelCallingPoint);
}

std::string EnergyManagementSystemProgramCallingManager::callingPoint() const {
  return getImpl<detail::EnergyManagementSystemProgramCallingManager_Impl>()->callingPoint();
}

bool EnergyManagementSystemProgramCallingManager::setCallingPoint(const std::string& callingPoint) {
  return getImpl<detail::EnergyManagementSystemProgramCallingManager_Impl>()->setCallingPoint(callingPoint);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string EnergyManagementSystemProgramCallingManager_Impl::callingPoint() const {
  const auto value = getString(openstudio::EnergyManagementSystem_ProgramCallingManagerFields::EnergyPlusModelCallingPoint, true);
  OS_ASSERT(value);
  return *value;
}

bool EnergyManagementSystemProgramCallingManager_Impl::setCallingPoint(const std::string& callingPoint) {
  return setString(openstudio::EnergyManagementSystem_ProgramCallingManagerFields::EnergyPlusModelCallingPoint, callingPoint);
}

std::vector<std::string> EnergyManagementSystemProgramCallingManager_Impl::validCallingPointValues() const {
  return openstudio::epmodel::EnergyManagementSystemProgramCallingManager::validCallingPointValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
