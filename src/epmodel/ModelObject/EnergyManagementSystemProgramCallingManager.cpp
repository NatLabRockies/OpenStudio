/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "EnergyManagementSystemProgramCallingManager.hpp"
#include "EnergyManagementSystemProgramCallingManager_Impl.hpp"

#include "EnergyManagementSystemProgram.hpp"
#include "EnergyManagementSystemProgram_Impl.hpp"
#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/EnergyManagementSystem_ProgramCallingManager_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>

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

std::vector<EnergyManagementSystemProgram> EnergyManagementSystemProgramCallingManager::programs() const {
  return getImpl<detail::EnergyManagementSystemProgramCallingManager_Impl>()->programs();
}

boost::optional<EnergyManagementSystemProgram> EnergyManagementSystemProgramCallingManager::getProgram(unsigned index) const {
  return getImpl<detail::EnergyManagementSystemProgramCallingManager_Impl>()->getProgram(index);
}

bool EnergyManagementSystemProgramCallingManager::eraseProgram(unsigned index) {
  return getImpl<detail::EnergyManagementSystemProgramCallingManager_Impl>()->eraseProgram(index);
}

void EnergyManagementSystemProgramCallingManager::erasePrograms() {
  getImpl<detail::EnergyManagementSystemProgramCallingManager_Impl>()->erasePrograms();
}

bool EnergyManagementSystemProgramCallingManager::addProgram(const EnergyManagementSystemProgram& program) {
  return getImpl<detail::EnergyManagementSystemProgramCallingManager_Impl>()->addProgram(program);
}

bool EnergyManagementSystemProgramCallingManager::setProgram(const EnergyManagementSystemProgram& program, unsigned index) {
  return getImpl<detail::EnergyManagementSystemProgramCallingManager_Impl>()->setProgram(program, index);
}

bool EnergyManagementSystemProgramCallingManager::setPrograms(const std::vector<EnergyManagementSystemProgram>& programs) {
  return getImpl<detail::EnergyManagementSystemProgramCallingManager_Impl>()->setPrograms(programs);
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

std::vector<EnergyManagementSystemProgram> EnergyManagementSystemProgramCallingManager_Impl::programs() const {
  std::vector<EnergyManagementSystemProgram> result;
  for (const auto& group : getObject<ModelObject>().extensibleGroups()) {
    auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
    if (!workspaceGroup) {
      continue;
    }
    if (auto program = workspaceGroup->getTarget(openstudio::EnergyManagementSystem_ProgramCallingManagerExtensibleFields::ProgramName)) {
      if (auto typedProgram = program->optionalCast<EnergyManagementSystemProgram>()) {
        result.push_back(*typedProgram);
      }
    }
  }
  return result;
}

boost::optional<EnergyManagementSystemProgram> EnergyManagementSystemProgramCallingManager_Impl::getProgram(unsigned index) const {
  const auto groups = getObject<ModelObject>().extensibleGroups();
  if (index >= groups.size()) {
    return boost::none;
  }
  auto workspaceGroup = groups[index].optionalCast<openstudio::WorkspaceExtensibleGroup>();
  if (!workspaceGroup) {
    return boost::none;
  }
  auto target = workspaceGroup->getTarget(openstudio::EnergyManagementSystem_ProgramCallingManagerExtensibleFields::ProgramName);
  if (!target) {
    return boost::none;
  }
  return target->optionalCast<EnergyManagementSystemProgram>();
}

bool EnergyManagementSystemProgramCallingManager_Impl::eraseProgram(unsigned index) {
  const auto groups = getObject<ModelObject>().extensibleGroups();
  if (index >= groups.size()) {
    return false;
  }
  getObject<ModelObject>().eraseExtensibleGroup(index);
  return true;
}

void EnergyManagementSystemProgramCallingManager_Impl::erasePrograms() {
  getObject<ModelObject>().clearExtensibleGroups();
}

bool EnergyManagementSystemProgramCallingManager_Impl::addProgram(const EnergyManagementSystemProgram& program) {
  auto group = getObject<ModelObject>().pushExtensibleGroup().cast<openstudio::WorkspaceExtensibleGroup>();
  if (!group.setPointer(openstudio::EnergyManagementSystem_ProgramCallingManagerExtensibleFields::ProgramName, program.handle())) {
    getObject<ModelObject>().eraseExtensibleGroup(group.groupIndex());
    return false;
  }
  return true;
}

bool EnergyManagementSystemProgramCallingManager_Impl::setProgram(const EnergyManagementSystemProgram& program, unsigned index) {
  const auto groups = getObject<ModelObject>().extensibleGroups();
  if (index >= groups.size()) {
    return false;
  }
  auto workspaceGroup = groups[index].cast<openstudio::WorkspaceExtensibleGroup>();
  return workspaceGroup.setPointer(openstudio::EnergyManagementSystem_ProgramCallingManagerExtensibleFields::ProgramName, program.handle());
}

bool EnergyManagementSystemProgramCallingManager_Impl::setPrograms(const std::vector<EnergyManagementSystemProgram>& programs) {
  erasePrograms();
  for (const auto& program : programs) {
    if (!addProgram(program)) {
      return false;
    }
  }
  return true;
}

std::vector<std::string> EnergyManagementSystemProgramCallingManager_Impl::validCallingPointValues() const {
  return openstudio::epmodel::EnergyManagementSystemProgramCallingManager::validCallingPointValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
