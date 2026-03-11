/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "HVACTemplatePlantChillerObjectReference.hpp"
#include "HVACTemplatePlantChillerObjectReference_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/HVACTemplate_Plant_Chiller_ObjectReference_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

HVACTemplatePlantChillerObjectReference::HVACTemplatePlantChillerObjectReference(const Model& model)
  : ModelObject(HVACTemplatePlantChillerObjectReference::iddObjectType(), model) {}

HVACTemplatePlantChillerObjectReference::HVACTemplatePlantChillerObjectReference(
  std::shared_ptr<detail::HVACTemplatePlantChillerObjectReference_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType HVACTemplatePlantChillerObjectReference::iddObjectType() {
  return IddObjectType::HVACTemplate_Plant_Chiller_ObjectReference;
}

std::vector<std::string> HVACTemplatePlantChillerObjectReference::chillerObjectTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::HVACTemplate_Plant_Chiller_ObjectReferenceFields::ChillerObjectType);
}

std::string HVACTemplatePlantChillerObjectReference::chillerObjectType() const {
  return getImpl<detail::HVACTemplatePlantChillerObjectReference_Impl>()->chillerObjectType();
}

boost::optional<double> HVACTemplatePlantChillerObjectReference::priority() const {
  return getImpl<detail::HVACTemplatePlantChillerObjectReference_Impl>()->priority();
}

bool HVACTemplatePlantChillerObjectReference::isChillerObjectTypeDefaulted() const {
  return getImpl<detail::HVACTemplatePlantChillerObjectReference_Impl>()->isChillerObjectTypeDefaulted();
}

bool HVACTemplatePlantChillerObjectReference::setChillerObjectType(const std::string& chillerObjectType) {
  return getImpl<detail::HVACTemplatePlantChillerObjectReference_Impl>()->setChillerObjectType(chillerObjectType);
}

bool HVACTemplatePlantChillerObjectReference::setPriority(double priority) {
  return getImpl<detail::HVACTemplatePlantChillerObjectReference_Impl>()->setPriority(priority);
}

void HVACTemplatePlantChillerObjectReference::resetChillerObjectType() {
  getImpl<detail::HVACTemplatePlantChillerObjectReference_Impl>()->resetChillerObjectType();
}

void HVACTemplatePlantChillerObjectReference::resetPriority() {
  getImpl<detail::HVACTemplatePlantChillerObjectReference_Impl>()->resetPriority();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string HVACTemplatePlantChillerObjectReference_Impl::chillerObjectType() const {
  auto value = getString(openstudio::HVACTemplate_Plant_Chiller_ObjectReferenceFields::ChillerObjectType, true);
  OS_ASSERT(value);
  return *value;
}

boost::optional<double> HVACTemplatePlantChillerObjectReference_Impl::priority() const {
  return getDouble(openstudio::HVACTemplate_Plant_Chiller_ObjectReferenceFields::Priority, true);
}

bool HVACTemplatePlantChillerObjectReference_Impl::isChillerObjectTypeDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Plant_Chiller_ObjectReferenceFields::ChillerObjectType);
}

bool HVACTemplatePlantChillerObjectReference_Impl::setChillerObjectType(const std::string& chillerObjectType) {
  return setString(openstudio::HVACTemplate_Plant_Chiller_ObjectReferenceFields::ChillerObjectType, chillerObjectType);
}

bool HVACTemplatePlantChillerObjectReference_Impl::setPriority(double priority) {
  const bool result = setDouble(openstudio::HVACTemplate_Plant_Chiller_ObjectReferenceFields::Priority, priority);
  OS_ASSERT(result);
  return result;
}

void HVACTemplatePlantChillerObjectReference_Impl::resetChillerObjectType() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Plant_Chiller_ObjectReferenceFields::ChillerObjectType, ""));
}

void HVACTemplatePlantChillerObjectReference_Impl::resetPriority() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Plant_Chiller_ObjectReferenceFields::Priority, ""));
}

std::vector<std::string> HVACTemplatePlantChillerObjectReference_Impl::chillerObjectTypeValues() const {
  return openstudio::epmodel::HVACTemplatePlantChillerObjectReference::chillerObjectTypeValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
