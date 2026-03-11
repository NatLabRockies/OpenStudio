/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "HVACTemplatePlantTowerObjectReference.hpp"
#include "HVACTemplatePlantTowerObjectReference_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/HVACTemplate_Plant_Tower_ObjectReference_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

HVACTemplatePlantTowerObjectReference::HVACTemplatePlantTowerObjectReference(const Model& model)
  : ModelObject(HVACTemplatePlantTowerObjectReference::iddObjectType(), model) {}

HVACTemplatePlantTowerObjectReference::HVACTemplatePlantTowerObjectReference(
  std::shared_ptr<detail::HVACTemplatePlantTowerObjectReference_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType HVACTemplatePlantTowerObjectReference::iddObjectType() {
  return IddObjectType::HVACTemplate_Plant_Tower_ObjectReference;
}

std::vector<std::string> HVACTemplatePlantTowerObjectReference::coolingTowerObjectTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::HVACTemplate_Plant_Tower_ObjectReferenceFields::CoolingTowerObjectType);
}

std::vector<std::string> HVACTemplatePlantTowerObjectReference::templatePlantLoopTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::HVACTemplate_Plant_Tower_ObjectReferenceFields::TemplatePlantLoopType);
}

std::string HVACTemplatePlantTowerObjectReference::coolingTowerObjectType() const {
  return getImpl<detail::HVACTemplatePlantTowerObjectReference_Impl>()->coolingTowerObjectType();
}

boost::optional<double> HVACTemplatePlantTowerObjectReference::priority() const {
  return getImpl<detail::HVACTemplatePlantTowerObjectReference_Impl>()->priority();
}

boost::optional<std::string> HVACTemplatePlantTowerObjectReference::templatePlantLoopType() const {
  return getImpl<detail::HVACTemplatePlantTowerObjectReference_Impl>()->templatePlantLoopType();
}

bool HVACTemplatePlantTowerObjectReference::isCoolingTowerObjectTypeDefaulted() const {
  return getImpl<detail::HVACTemplatePlantTowerObjectReference_Impl>()->isCoolingTowerObjectTypeDefaulted();
}

bool HVACTemplatePlantTowerObjectReference::setCoolingTowerObjectType(const std::string& coolingTowerObjectType) {
  return getImpl<detail::HVACTemplatePlantTowerObjectReference_Impl>()->setCoolingTowerObjectType(coolingTowerObjectType);
}

bool HVACTemplatePlantTowerObjectReference::setPriority(double priority) {
  return getImpl<detail::HVACTemplatePlantTowerObjectReference_Impl>()->setPriority(priority);
}

bool HVACTemplatePlantTowerObjectReference::setTemplatePlantLoopType(const std::string& templatePlantLoopType) {
  return getImpl<detail::HVACTemplatePlantTowerObjectReference_Impl>()->setTemplatePlantLoopType(templatePlantLoopType);
}

void HVACTemplatePlantTowerObjectReference::resetCoolingTowerObjectType() {
  getImpl<detail::HVACTemplatePlantTowerObjectReference_Impl>()->resetCoolingTowerObjectType();
}

void HVACTemplatePlantTowerObjectReference::resetPriority() {
  getImpl<detail::HVACTemplatePlantTowerObjectReference_Impl>()->resetPriority();
}

void HVACTemplatePlantTowerObjectReference::resetTemplatePlantLoopType() {
  getImpl<detail::HVACTemplatePlantTowerObjectReference_Impl>()->resetTemplatePlantLoopType();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string HVACTemplatePlantTowerObjectReference_Impl::coolingTowerObjectType() const {
  auto value = getString(openstudio::HVACTemplate_Plant_Tower_ObjectReferenceFields::CoolingTowerObjectType, true);
  OS_ASSERT(value);
  return *value;
}

boost::optional<double> HVACTemplatePlantTowerObjectReference_Impl::priority() const {
  return getDouble(openstudio::HVACTemplate_Plant_Tower_ObjectReferenceFields::Priority, true);
}

boost::optional<std::string> HVACTemplatePlantTowerObjectReference_Impl::templatePlantLoopType() const {
  return getString(openstudio::HVACTemplate_Plant_Tower_ObjectReferenceFields::TemplatePlantLoopType, true);
}

bool HVACTemplatePlantTowerObjectReference_Impl::isCoolingTowerObjectTypeDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Plant_Tower_ObjectReferenceFields::CoolingTowerObjectType);
}

bool HVACTemplatePlantTowerObjectReference_Impl::setCoolingTowerObjectType(const std::string& coolingTowerObjectType) {
  return setString(openstudio::HVACTemplate_Plant_Tower_ObjectReferenceFields::CoolingTowerObjectType, coolingTowerObjectType);
}

bool HVACTemplatePlantTowerObjectReference_Impl::setPriority(double priority) {
  const bool result = setDouble(openstudio::HVACTemplate_Plant_Tower_ObjectReferenceFields::Priority, priority);
  OS_ASSERT(result);
  return result;
}

bool HVACTemplatePlantTowerObjectReference_Impl::setTemplatePlantLoopType(const std::string& templatePlantLoopType) {
  return setString(openstudio::HVACTemplate_Plant_Tower_ObjectReferenceFields::TemplatePlantLoopType, templatePlantLoopType);
}

void HVACTemplatePlantTowerObjectReference_Impl::resetCoolingTowerObjectType() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Plant_Tower_ObjectReferenceFields::CoolingTowerObjectType, ""));
}

void HVACTemplatePlantTowerObjectReference_Impl::resetPriority() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Plant_Tower_ObjectReferenceFields::Priority, ""));
}

void HVACTemplatePlantTowerObjectReference_Impl::resetTemplatePlantLoopType() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Plant_Tower_ObjectReferenceFields::TemplatePlantLoopType, ""));
}

std::vector<std::string> HVACTemplatePlantTowerObjectReference_Impl::coolingTowerObjectTypeValues() const {
  return openstudio::epmodel::HVACTemplatePlantTowerObjectReference::coolingTowerObjectTypeValues();
}

std::vector<std::string> HVACTemplatePlantTowerObjectReference_Impl::templatePlantLoopTypeValues() const {
  return openstudio::epmodel::HVACTemplatePlantTowerObjectReference::templatePlantLoopTypeValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
