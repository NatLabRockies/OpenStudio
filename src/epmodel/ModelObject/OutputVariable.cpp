/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "OutputVariable.hpp"
#include "OutputVariable_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/Output_Variable_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

OutputVariable::OutputVariable(const std::string& variableName, const Model& model) : ModelObject(OutputVariable::iddObjectType(), model) {
  OS_ASSERT(getImpl<detail::OutputVariable_Impl>());
  const bool ok = setVariableName(variableName);
  OS_ASSERT(ok);
}

OutputVariable::OutputVariable(std::shared_ptr<detail::OutputVariable_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType OutputVariable::iddObjectType() {
  return IddObjectType::Output_Variable;
}

std::vector<std::string> OutputVariable::reportingFrequencyValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Output_VariableFields::ReportingFrequency);
}

std::string OutputVariable::keyValue() const {
  return getImpl<detail::OutputVariable_Impl>()->keyValue();
}

bool OutputVariable::isKeyValueDefaulted() const {
  return getImpl<detail::OutputVariable_Impl>()->isKeyValueDefaulted();
}

std::string OutputVariable::variableName() const {
  return getImpl<detail::OutputVariable_Impl>()->variableName();
}

std::string OutputVariable::reportingFrequency() const {
  return getImpl<detail::OutputVariable_Impl>()->reportingFrequency();
}

bool OutputVariable::isReportingFrequencyDefaulted() const {
  return getImpl<detail::OutputVariable_Impl>()->isReportingFrequencyDefaulted();
}

bool OutputVariable::setKeyValue(const std::string& keyValue) {
  return getImpl<detail::OutputVariable_Impl>()->setKeyValue(keyValue);
}

void OutputVariable::resetKeyValue() {
  getImpl<detail::OutputVariable_Impl>()->resetKeyValue();
}

bool OutputVariable::setVariableName(const std::string& variableName) {
  return getImpl<detail::OutputVariable_Impl>()->setVariableName(variableName);
}

bool OutputVariable::setReportingFrequency(const std::string& reportingFrequency) {
  return getImpl<detail::OutputVariable_Impl>()->setReportingFrequency(reportingFrequency);
}

void OutputVariable::resetReportingFrequency() {
  getImpl<detail::OutputVariable_Impl>()->resetReportingFrequency();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string OutputVariable_Impl::keyValue() const {
  const auto value = getString(openstudio::Output_VariableFields::KeyValue, true);
  OS_ASSERT(value);
  return *value;
}

bool OutputVariable_Impl::isKeyValueDefaulted() const {
  return isEmpty(openstudio::Output_VariableFields::KeyValue);
}

std::string OutputVariable_Impl::variableName() const {
  const auto value = getString(openstudio::Output_VariableFields::VariableName, true);
  OS_ASSERT(value);
  return *value;
}

std::string OutputVariable_Impl::reportingFrequency() const {
  const auto value = getString(openstudio::Output_VariableFields::ReportingFrequency, true);
  OS_ASSERT(value);
  return *value;
}

bool OutputVariable_Impl::isReportingFrequencyDefaulted() const {
  return isEmpty(openstudio::Output_VariableFields::ReportingFrequency);
}

bool OutputVariable_Impl::setKeyValue(const std::string& keyValue) {
  const bool result = setString(openstudio::Output_VariableFields::KeyValue, keyValue);
  OS_ASSERT(result);
  return result;
}

void OutputVariable_Impl::resetKeyValue() {
  const bool result = setString(openstudio::Output_VariableFields::KeyValue, "");
  OS_ASSERT(result);
}

bool OutputVariable_Impl::setVariableName(const std::string& variableName) {
  const bool result = setString(openstudio::Output_VariableFields::VariableName, variableName);
  OS_ASSERT(result);
  return result;
}

bool OutputVariable_Impl::setReportingFrequency(const std::string& reportingFrequency) {
  return setString(openstudio::Output_VariableFields::ReportingFrequency, reportingFrequency);
}

void OutputVariable_Impl::resetReportingFrequency() {
  const bool result = setString(openstudio::Output_VariableFields::ReportingFrequency, "");
  OS_ASSERT(result);
}

std::vector<std::string> OutputVariable_Impl::reportingFrequencyValues() const {
  return openstudio::epmodel::OutputVariable::reportingFrequencyValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
