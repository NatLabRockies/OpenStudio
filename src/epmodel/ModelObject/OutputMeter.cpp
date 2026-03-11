/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "OutputMeter.hpp"
#include "OutputMeter_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/Output_Meter_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

OutputMeter::OutputMeter(const Model& model) : ModelObject(OutputMeter::iddObjectType(), model) {}

OutputMeter::OutputMeter(std::shared_ptr<detail::OutputMeter_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType OutputMeter::iddObjectType() {
  return IddObjectType::Output_Meter;
}

std::vector<std::string> OutputMeter::reportingFrequencyValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Output_MeterFields::ReportingFrequency);
}

std::string OutputMeter::keyName() const {
  return getImpl<detail::OutputMeter_Impl>()->keyName();
}

std::string OutputMeter::reportingFrequency() const {
  return getImpl<detail::OutputMeter_Impl>()->reportingFrequency();
}

bool OutputMeter::isReportingFrequencyDefaulted() const {
  return getImpl<detail::OutputMeter_Impl>()->isReportingFrequencyDefaulted();
}

bool OutputMeter::setKeyName(const std::string& keyName) {
  return getImpl<detail::OutputMeter_Impl>()->setKeyName(keyName);
}

bool OutputMeter::setReportingFrequency(const std::string& reportingFrequency) {
  return getImpl<detail::OutputMeter_Impl>()->setReportingFrequency(reportingFrequency);
}

void OutputMeter::resetReportingFrequency() {
  getImpl<detail::OutputMeter_Impl>()->resetReportingFrequency();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string OutputMeter_Impl::keyName() const {
  const auto value = getString(openstudio::Output_MeterFields::KeyName, true);
  OS_ASSERT(value);
  return *value;
}

std::string OutputMeter_Impl::reportingFrequency() const {
  const auto value = getString(openstudio::Output_MeterFields::ReportingFrequency, true);
  OS_ASSERT(value);
  return *value;
}

bool OutputMeter_Impl::isReportingFrequencyDefaulted() const {
  return isEmpty(openstudio::Output_MeterFields::ReportingFrequency);
}

bool OutputMeter_Impl::setKeyName(const std::string& keyName) {
  return setString(openstudio::Output_MeterFields::KeyName, keyName);
}

bool OutputMeter_Impl::setReportingFrequency(const std::string& reportingFrequency) {
  return setString(openstudio::Output_MeterFields::ReportingFrequency, reportingFrequency);
}

void OutputMeter_Impl::resetReportingFrequency() {
  OS_ASSERT(setString(openstudio::Output_MeterFields::ReportingFrequency, ""));
}

std::vector<std::string> OutputMeter_Impl::reportingFrequencyValues() const {
  return openstudio::epmodel::OutputMeter::reportingFrequencyValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
