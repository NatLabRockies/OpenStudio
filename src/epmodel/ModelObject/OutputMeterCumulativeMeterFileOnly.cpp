/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "OutputMeterCumulativeMeterFileOnly.hpp"
#include "OutputMeterCumulativeMeterFileOnly_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/Output_Meter_Cumulative_MeterFileOnly_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

OutputMeterCumulativeMeterFileOnly::OutputMeterCumulativeMeterFileOnly(const Model& model)
  : ModelObject(OutputMeterCumulativeMeterFileOnly::iddObjectType(), model) {}

OutputMeterCumulativeMeterFileOnly::OutputMeterCumulativeMeterFileOnly(
  std::shared_ptr<detail::OutputMeterCumulativeMeterFileOnly_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType OutputMeterCumulativeMeterFileOnly::iddObjectType() {
  return IddObjectType::Output_Meter_Cumulative_MeterFileOnly;
}

std::vector<std::string> OutputMeterCumulativeMeterFileOnly::reportingFrequencyValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::Output_Meter_Cumulative_MeterFileOnlyFields::ReportingFrequency);
}

std::string OutputMeterCumulativeMeterFileOnly::keyName() const {
  return getImpl<detail::OutputMeterCumulativeMeterFileOnly_Impl>()->keyName();
}

std::string OutputMeterCumulativeMeterFileOnly::reportingFrequency() const {
  return getImpl<detail::OutputMeterCumulativeMeterFileOnly_Impl>()->reportingFrequency();
}

bool OutputMeterCumulativeMeterFileOnly::isReportingFrequencyDefaulted() const {
  return getImpl<detail::OutputMeterCumulativeMeterFileOnly_Impl>()->isReportingFrequencyDefaulted();
}

bool OutputMeterCumulativeMeterFileOnly::setKeyName(const std::string& keyName) {
  return getImpl<detail::OutputMeterCumulativeMeterFileOnly_Impl>()->setKeyName(keyName);
}

bool OutputMeterCumulativeMeterFileOnly::setReportingFrequency(const std::string& reportingFrequency) {
  return getImpl<detail::OutputMeterCumulativeMeterFileOnly_Impl>()->setReportingFrequency(reportingFrequency);
}

void OutputMeterCumulativeMeterFileOnly::resetReportingFrequency() {
  getImpl<detail::OutputMeterCumulativeMeterFileOnly_Impl>()->resetReportingFrequency();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string OutputMeterCumulativeMeterFileOnly_Impl::keyName() const {
  const auto value = getString(openstudio::Output_Meter_Cumulative_MeterFileOnlyFields::KeyName, true);
  OS_ASSERT(value);
  return *value;
}

std::string OutputMeterCumulativeMeterFileOnly_Impl::reportingFrequency() const {
  const auto value = getString(openstudio::Output_Meter_Cumulative_MeterFileOnlyFields::ReportingFrequency, true);
  OS_ASSERT(value);
  return *value;
}

bool OutputMeterCumulativeMeterFileOnly_Impl::isReportingFrequencyDefaulted() const {
  return isEmpty(openstudio::Output_Meter_Cumulative_MeterFileOnlyFields::ReportingFrequency);
}

bool OutputMeterCumulativeMeterFileOnly_Impl::setKeyName(const std::string& keyName) {
  return setString(openstudio::Output_Meter_Cumulative_MeterFileOnlyFields::KeyName, keyName);
}

bool OutputMeterCumulativeMeterFileOnly_Impl::setReportingFrequency(const std::string& reportingFrequency) {
  return setString(openstudio::Output_Meter_Cumulative_MeterFileOnlyFields::ReportingFrequency, reportingFrequency);
}

void OutputMeterCumulativeMeterFileOnly_Impl::resetReportingFrequency() {
  OS_ASSERT(setString(openstudio::Output_Meter_Cumulative_MeterFileOnlyFields::ReportingFrequency, ""));
}

std::vector<std::string> OutputMeterCumulativeMeterFileOnly_Impl::reportingFrequencyValues() const {
  return openstudio::epmodel::OutputMeterCumulativeMeterFileOnly::reportingFrequencyValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
