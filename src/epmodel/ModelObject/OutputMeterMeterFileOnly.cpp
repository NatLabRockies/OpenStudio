/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "OutputMeterMeterFileOnly.hpp"
#include "OutputMeterMeterFileOnly_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/Output_Meter_MeterFileOnly_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

OutputMeterMeterFileOnly::OutputMeterMeterFileOnly(const Model& model)
  : ModelObject(OutputMeterMeterFileOnly::iddObjectType(), model) {}

OutputMeterMeterFileOnly::OutputMeterMeterFileOnly(std::shared_ptr<detail::OutputMeterMeterFileOnly_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType OutputMeterMeterFileOnly::iddObjectType() {
  return IddObjectType::Output_Meter_MeterFileOnly;
}

std::vector<std::string> OutputMeterMeterFileOnly::reportingFrequencyValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::Output_Meter_MeterFileOnlyFields::ReportingFrequency);
}

std::string OutputMeterMeterFileOnly::keyName() const {
  return getImpl<detail::OutputMeterMeterFileOnly_Impl>()->keyName();
}

std::string OutputMeterMeterFileOnly::reportingFrequency() const {
  return getImpl<detail::OutputMeterMeterFileOnly_Impl>()->reportingFrequency();
}

bool OutputMeterMeterFileOnly::isReportingFrequencyDefaulted() const {
  return getImpl<detail::OutputMeterMeterFileOnly_Impl>()->isReportingFrequencyDefaulted();
}

bool OutputMeterMeterFileOnly::setKeyName(const std::string& keyName) {
  return getImpl<detail::OutputMeterMeterFileOnly_Impl>()->setKeyName(keyName);
}

bool OutputMeterMeterFileOnly::setReportingFrequency(const std::string& reportingFrequency) {
  return getImpl<detail::OutputMeterMeterFileOnly_Impl>()->setReportingFrequency(reportingFrequency);
}

void OutputMeterMeterFileOnly::resetReportingFrequency() {
  getImpl<detail::OutputMeterMeterFileOnly_Impl>()->resetReportingFrequency();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string OutputMeterMeterFileOnly_Impl::keyName() const {
  const auto value = getString(openstudio::Output_Meter_MeterFileOnlyFields::KeyName, true);
  OS_ASSERT(value);
  return *value;
}

std::string OutputMeterMeterFileOnly_Impl::reportingFrequency() const {
  const auto value = getString(openstudio::Output_Meter_MeterFileOnlyFields::ReportingFrequency, true);
  OS_ASSERT(value);
  return *value;
}

bool OutputMeterMeterFileOnly_Impl::isReportingFrequencyDefaulted() const {
  return isEmpty(openstudio::Output_Meter_MeterFileOnlyFields::ReportingFrequency);
}

bool OutputMeterMeterFileOnly_Impl::setKeyName(const std::string& keyName) {
  return setString(openstudio::Output_Meter_MeterFileOnlyFields::KeyName, keyName);
}

bool OutputMeterMeterFileOnly_Impl::setReportingFrequency(const std::string& reportingFrequency) {
  return setString(openstudio::Output_Meter_MeterFileOnlyFields::ReportingFrequency, reportingFrequency);
}

void OutputMeterMeterFileOnly_Impl::resetReportingFrequency() {
  OS_ASSERT(setString(openstudio::Output_Meter_MeterFileOnlyFields::ReportingFrequency, ""));
}

std::vector<std::string> OutputMeterMeterFileOnly_Impl::reportingFrequencyValues() const {
  return openstudio::epmodel::OutputMeterMeterFileOnly::reportingFrequencyValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
