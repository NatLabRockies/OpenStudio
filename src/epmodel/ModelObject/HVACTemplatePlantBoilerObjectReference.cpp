/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "HVACTemplatePlantBoilerObjectReference.hpp"
#include "HVACTemplatePlantBoilerObjectReference_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/HVACTemplate_Plant_Boiler_ObjectReference_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

HVACTemplatePlantBoilerObjectReference::HVACTemplatePlantBoilerObjectReference(const Model& model)
  : ModelObject(HVACTemplatePlantBoilerObjectReference::iddObjectType(), model) {}

HVACTemplatePlantBoilerObjectReference::HVACTemplatePlantBoilerObjectReference(
  std::shared_ptr<detail::HVACTemplatePlantBoilerObjectReference_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType HVACTemplatePlantBoilerObjectReference::iddObjectType() {
  return IddObjectType::HVACTemplate_Plant_Boiler_ObjectReference;
}

std::vector<std::string> HVACTemplatePlantBoilerObjectReference::boilerObjectTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::HVACTemplate_Plant_Boiler_ObjectReferenceFields::BoilerObjectType);
}

std::vector<std::string> HVACTemplatePlantBoilerObjectReference::templatePlantLoopTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::HVACTemplate_Plant_Boiler_ObjectReferenceFields::TemplatePlantLoopType);
}

std::string HVACTemplatePlantBoilerObjectReference::boilerObjectType() const {
  return getImpl<detail::HVACTemplatePlantBoilerObjectReference_Impl>()->boilerObjectType();
}

boost::optional<double> HVACTemplatePlantBoilerObjectReference::priority() const {
  return getImpl<detail::HVACTemplatePlantBoilerObjectReference_Impl>()->priority();
}

boost::optional<std::string> HVACTemplatePlantBoilerObjectReference::templatePlantLoopType() const {
  return getImpl<detail::HVACTemplatePlantBoilerObjectReference_Impl>()->templatePlantLoopType();
}

bool HVACTemplatePlantBoilerObjectReference::isBoilerObjectTypeDefaulted() const {
  return getImpl<detail::HVACTemplatePlantBoilerObjectReference_Impl>()->isBoilerObjectTypeDefaulted();
}

bool HVACTemplatePlantBoilerObjectReference::setBoilerObjectType(const std::string& boilerObjectType) {
  return getImpl<detail::HVACTemplatePlantBoilerObjectReference_Impl>()->setBoilerObjectType(boilerObjectType);
}

bool HVACTemplatePlantBoilerObjectReference::setPriority(double priority) {
  return getImpl<detail::HVACTemplatePlantBoilerObjectReference_Impl>()->setPriority(priority);
}

bool HVACTemplatePlantBoilerObjectReference::setTemplatePlantLoopType(const std::string& templatePlantLoopType) {
  return getImpl<detail::HVACTemplatePlantBoilerObjectReference_Impl>()->setTemplatePlantLoopType(templatePlantLoopType);
}

void HVACTemplatePlantBoilerObjectReference::resetBoilerObjectType() {
  getImpl<detail::HVACTemplatePlantBoilerObjectReference_Impl>()->resetBoilerObjectType();
}

void HVACTemplatePlantBoilerObjectReference::resetPriority() {
  getImpl<detail::HVACTemplatePlantBoilerObjectReference_Impl>()->resetPriority();
}

void HVACTemplatePlantBoilerObjectReference::resetTemplatePlantLoopType() {
  getImpl<detail::HVACTemplatePlantBoilerObjectReference_Impl>()->resetTemplatePlantLoopType();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string HVACTemplatePlantBoilerObjectReference_Impl::boilerObjectType() const {
  auto value = getString(openstudio::HVACTemplate_Plant_Boiler_ObjectReferenceFields::BoilerObjectType, true);
  OS_ASSERT(value);
  return *value;
}

boost::optional<double> HVACTemplatePlantBoilerObjectReference_Impl::priority() const {
  return getDouble(openstudio::HVACTemplate_Plant_Boiler_ObjectReferenceFields::Priority, true);
}

boost::optional<std::string> HVACTemplatePlantBoilerObjectReference_Impl::templatePlantLoopType() const {
  return getString(openstudio::HVACTemplate_Plant_Boiler_ObjectReferenceFields::TemplatePlantLoopType, true);
}

bool HVACTemplatePlantBoilerObjectReference_Impl::isBoilerObjectTypeDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Plant_Boiler_ObjectReferenceFields::BoilerObjectType);
}

bool HVACTemplatePlantBoilerObjectReference_Impl::setBoilerObjectType(const std::string& boilerObjectType) {
  return setString(openstudio::HVACTemplate_Plant_Boiler_ObjectReferenceFields::BoilerObjectType, boilerObjectType);
}

bool HVACTemplatePlantBoilerObjectReference_Impl::setPriority(double priority) {
  const bool result = setDouble(openstudio::HVACTemplate_Plant_Boiler_ObjectReferenceFields::Priority, priority);
  OS_ASSERT(result);
  return result;
}

bool HVACTemplatePlantBoilerObjectReference_Impl::setTemplatePlantLoopType(const std::string& templatePlantLoopType) {
  return setString(openstudio::HVACTemplate_Plant_Boiler_ObjectReferenceFields::TemplatePlantLoopType, templatePlantLoopType);
}

void HVACTemplatePlantBoilerObjectReference_Impl::resetBoilerObjectType() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Plant_Boiler_ObjectReferenceFields::BoilerObjectType, ""));
}

void HVACTemplatePlantBoilerObjectReference_Impl::resetPriority() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Plant_Boiler_ObjectReferenceFields::Priority, ""));
}

void HVACTemplatePlantBoilerObjectReference_Impl::resetTemplatePlantLoopType() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Plant_Boiler_ObjectReferenceFields::TemplatePlantLoopType, ""));
}

std::vector<std::string> HVACTemplatePlantBoilerObjectReference_Impl::boilerObjectTypeValues() const {
  return openstudio::epmodel::HVACTemplatePlantBoilerObjectReference::boilerObjectTypeValues();
}

std::vector<std::string> HVACTemplatePlantBoilerObjectReference_Impl::templatePlantLoopTypeValues() const {
  return openstudio::epmodel::HVACTemplatePlantBoilerObjectReference::templatePlantLoopTypeValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
