/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "OutputDaylightFactors.hpp"
#include "OutputDaylightFactors_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/Output_DaylightFactors_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

OutputDaylightFactors::OutputDaylightFactors(const Model& model) : ModelObject(OutputDaylightFactors::iddObjectType(), model) {}

OutputDaylightFactors::OutputDaylightFactors(std::shared_ptr<detail::OutputDaylightFactors_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType OutputDaylightFactors::iddObjectType() {
  return IddObjectType::Output_DaylightFactors;
}

std::vector<std::string> OutputDaylightFactors::reportingDaysValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Output_DaylightFactorsFields::ReportingDays);
}

std::string OutputDaylightFactors::reportingDays() const {
  return getImpl<detail::OutputDaylightFactors_Impl>()->reportingDays();
}

bool OutputDaylightFactors::setReportingDays(const std::string& reportingDays) {
  return getImpl<detail::OutputDaylightFactors_Impl>()->setReportingDays(reportingDays);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string OutputDaylightFactors_Impl::reportingDays() const {
  const auto value = getString(openstudio::Output_DaylightFactorsFields::ReportingDays, true);
  OS_ASSERT(value);
  return *value;
}

bool OutputDaylightFactors_Impl::setReportingDays(const std::string& reportingDays) {
  return setString(openstudio::Output_DaylightFactorsFields::ReportingDays, reportingDays);
}

std::vector<std::string> OutputDaylightFactors_Impl::reportingDaysValues() const {
  return openstudio::epmodel::OutputDaylightFactors::reportingDaysValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
