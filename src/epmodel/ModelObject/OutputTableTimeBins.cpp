/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "OutputTableTimeBins.hpp"
#include "OutputTableTimeBins_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/Output_Table_TimeBins_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

OutputTableTimeBins::OutputTableTimeBins(const Model& model) : ModelObject(OutputTableTimeBins::iddObjectType(), model) {}

OutputTableTimeBins::OutputTableTimeBins(std::shared_ptr<detail::OutputTableTimeBins_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType OutputTableTimeBins::iddObjectType() {
  return IddObjectType::Output_Table_TimeBins;
}

std::vector<std::string> OutputTableTimeBins::variableTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Output_Table_TimeBinsFields::VariableType);
}

std::string OutputTableTimeBins::keyValue() const {
  return getImpl<detail::OutputTableTimeBins_Impl>()->keyValue();
}

bool OutputTableTimeBins::isKeyValueDefaulted() const {
  return getImpl<detail::OutputTableTimeBins_Impl>()->isKeyValueDefaulted();
}

std::string OutputTableTimeBins::variableName() const {
  return getImpl<detail::OutputTableTimeBins_Impl>()->variableName();
}

boost::optional<double> OutputTableTimeBins::intervalStart() const {
  return getImpl<detail::OutputTableTimeBins_Impl>()->intervalStart();
}

boost::optional<double> OutputTableTimeBins::intervalSize() const {
  return getImpl<detail::OutputTableTimeBins_Impl>()->intervalSize();
}

boost::optional<int> OutputTableTimeBins::intervalCount() const {
  return getImpl<detail::OutputTableTimeBins_Impl>()->intervalCount();
}

boost::optional<std::string> OutputTableTimeBins::variableType() const {
  return getImpl<detail::OutputTableTimeBins_Impl>()->variableType();
}

bool OutputTableTimeBins::setKeyValue(const std::string& keyValue) {
  return getImpl<detail::OutputTableTimeBins_Impl>()->setKeyValue(keyValue);
}

void OutputTableTimeBins::resetKeyValue() {
  getImpl<detail::OutputTableTimeBins_Impl>()->resetKeyValue();
}

bool OutputTableTimeBins::setVariableName(const std::string& variableName) {
  return getImpl<detail::OutputTableTimeBins_Impl>()->setVariableName(variableName);
}

bool OutputTableTimeBins::setIntervalStart(double intervalStart) {
  return getImpl<detail::OutputTableTimeBins_Impl>()->setIntervalStart(intervalStart);
}

void OutputTableTimeBins::resetIntervalStart() {
  getImpl<detail::OutputTableTimeBins_Impl>()->resetIntervalStart();
}

bool OutputTableTimeBins::setIntervalSize(double intervalSize) {
  return getImpl<detail::OutputTableTimeBins_Impl>()->setIntervalSize(intervalSize);
}

void OutputTableTimeBins::resetIntervalSize() {
  getImpl<detail::OutputTableTimeBins_Impl>()->resetIntervalSize();
}

bool OutputTableTimeBins::setIntervalCount(int intervalCount) {
  return getImpl<detail::OutputTableTimeBins_Impl>()->setIntervalCount(intervalCount);
}

void OutputTableTimeBins::resetIntervalCount() {
  getImpl<detail::OutputTableTimeBins_Impl>()->resetIntervalCount();
}

bool OutputTableTimeBins::setVariableType(const std::string& variableType) {
  return getImpl<detail::OutputTableTimeBins_Impl>()->setVariableType(variableType);
}

void OutputTableTimeBins::resetVariableType() {
  getImpl<detail::OutputTableTimeBins_Impl>()->resetVariableType();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string OutputTableTimeBins_Impl::keyValue() const {
  const auto value = getString(openstudio::Output_Table_TimeBinsFields::KeyValue, true);
  OS_ASSERT(value);
  return *value;
}

bool OutputTableTimeBins_Impl::isKeyValueDefaulted() const {
  return isEmpty(openstudio::Output_Table_TimeBinsFields::KeyValue);
}

std::string OutputTableTimeBins_Impl::variableName() const {
  const auto value = getString(openstudio::Output_Table_TimeBinsFields::VariableName, true);
  OS_ASSERT(value);
  return *value;
}

boost::optional<double> OutputTableTimeBins_Impl::intervalStart() const {
  return getDouble(openstudio::Output_Table_TimeBinsFields::IntervalStart, true);
}

boost::optional<double> OutputTableTimeBins_Impl::intervalSize() const {
  return getDouble(openstudio::Output_Table_TimeBinsFields::IntervalSize, true);
}

boost::optional<int> OutputTableTimeBins_Impl::intervalCount() const {
  return getInt(openstudio::Output_Table_TimeBinsFields::IntervalCount, true);
}

boost::optional<std::string> OutputTableTimeBins_Impl::variableType() const {
  return getString(openstudio::Output_Table_TimeBinsFields::VariableType, true);
}

bool OutputTableTimeBins_Impl::setKeyValue(const std::string& keyValue) {
  const bool result = setString(openstudio::Output_Table_TimeBinsFields::KeyValue, keyValue);
  OS_ASSERT(result);
  return result;
}

void OutputTableTimeBins_Impl::resetKeyValue() {
  const bool result = setString(openstudio::Output_Table_TimeBinsFields::KeyValue, "");
  OS_ASSERT(result);
}

bool OutputTableTimeBins_Impl::setVariableName(const std::string& variableName) {
  return setString(openstudio::Output_Table_TimeBinsFields::VariableName, variableName);
}

bool OutputTableTimeBins_Impl::setIntervalStart(double intervalStart) {
  const bool result = setDouble(openstudio::Output_Table_TimeBinsFields::IntervalStart, intervalStart);
  OS_ASSERT(result);
  return result;
}

void OutputTableTimeBins_Impl::resetIntervalStart() {
  const bool result = setString(openstudio::Output_Table_TimeBinsFields::IntervalStart, "");
  OS_ASSERT(result);
}

bool OutputTableTimeBins_Impl::setIntervalSize(double intervalSize) {
  const bool result = setDouble(openstudio::Output_Table_TimeBinsFields::IntervalSize, intervalSize);
  OS_ASSERT(result);
  return result;
}

void OutputTableTimeBins_Impl::resetIntervalSize() {
  const bool result = setString(openstudio::Output_Table_TimeBinsFields::IntervalSize, "");
  OS_ASSERT(result);
}

bool OutputTableTimeBins_Impl::setIntervalCount(int intervalCount) {
  return setInt(openstudio::Output_Table_TimeBinsFields::IntervalCount, intervalCount);
}

void OutputTableTimeBins_Impl::resetIntervalCount() {
  const bool result = setString(openstudio::Output_Table_TimeBinsFields::IntervalCount, "");
  OS_ASSERT(result);
}

bool OutputTableTimeBins_Impl::setVariableType(const std::string& variableType) {
  return setString(openstudio::Output_Table_TimeBinsFields::VariableType, variableType);
}

void OutputTableTimeBins_Impl::resetVariableType() {
  const bool result = setString(openstudio::Output_Table_TimeBinsFields::VariableType, "");
  OS_ASSERT(result);
}

std::vector<std::string> OutputTableTimeBins_Impl::variableTypeValues() const {
  return openstudio::epmodel::OutputTableTimeBins::variableTypeValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
