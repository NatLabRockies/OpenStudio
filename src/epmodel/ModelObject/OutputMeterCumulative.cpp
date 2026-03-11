/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "OutputMeterCumulative.hpp"
#include "OutputMeterCumulative_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/Output_Meter_Cumulative_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

OutputMeterCumulative::OutputMeterCumulative(const Model& model) : ModelObject(OutputMeterCumulative::iddObjectType(), model) {}

OutputMeterCumulative::OutputMeterCumulative(std::shared_ptr<detail::OutputMeterCumulative_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType OutputMeterCumulative::iddObjectType() {
  return IddObjectType::Output_Meter_Cumulative;
}

std::vector<std::string> OutputMeterCumulative::reportingFrequencyValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Output_Meter_CumulativeFields::ReportingFrequency);
}

std::string OutputMeterCumulative::keyName() const {
  return getImpl<detail::OutputMeterCumulative_Impl>()->keyName();
}

std::string OutputMeterCumulative::reportingFrequency() const {
  return getImpl<detail::OutputMeterCumulative_Impl>()->reportingFrequency();
}

bool OutputMeterCumulative::isReportingFrequencyDefaulted() const {
  return getImpl<detail::OutputMeterCumulative_Impl>()->isReportingFrequencyDefaulted();
}

bool OutputMeterCumulative::setKeyName(const std::string& keyName) {
  return getImpl<detail::OutputMeterCumulative_Impl>()->setKeyName(keyName);
}

bool OutputMeterCumulative::setReportingFrequency(const std::string& reportingFrequency) {
  return getImpl<detail::OutputMeterCumulative_Impl>()->setReportingFrequency(reportingFrequency);
}

void OutputMeterCumulative::resetReportingFrequency() {
  getImpl<detail::OutputMeterCumulative_Impl>()->resetReportingFrequency();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string OutputMeterCumulative_Impl::keyName() const {
  const auto value = getString(openstudio::Output_Meter_CumulativeFields::KeyName, true);
  OS_ASSERT(value);
  return *value;
}

std::string OutputMeterCumulative_Impl::reportingFrequency() const {
  const auto value = getString(openstudio::Output_Meter_CumulativeFields::ReportingFrequency, true);
  OS_ASSERT(value);
  return *value;
}

bool OutputMeterCumulative_Impl::isReportingFrequencyDefaulted() const {
  return isEmpty(openstudio::Output_Meter_CumulativeFields::ReportingFrequency);
}

bool OutputMeterCumulative_Impl::setKeyName(const std::string& keyName) {
  return setString(openstudio::Output_Meter_CumulativeFields::KeyName, keyName);
}

bool OutputMeterCumulative_Impl::setReportingFrequency(const std::string& reportingFrequency) {
  return setString(openstudio::Output_Meter_CumulativeFields::ReportingFrequency, reportingFrequency);
}

void OutputMeterCumulative_Impl::resetReportingFrequency() {
  OS_ASSERT(setString(openstudio::Output_Meter_CumulativeFields::ReportingFrequency, ""));
}

std::vector<std::string> OutputMeterCumulative_Impl::reportingFrequencyValues() const {
  return openstudio::epmodel::OutputMeterCumulative::reportingFrequencyValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
