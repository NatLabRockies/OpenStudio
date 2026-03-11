/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "OutputControlReportingTolerances.hpp"
#include "OutputControlReportingTolerances_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/OutputControl_ReportingTolerances_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

OutputControlReportingTolerances::OutputControlReportingTolerances(const Model& model)
  : ModelObject(OutputControlReportingTolerances::iddObjectType(), model) {}

OutputControlReportingTolerances::OutputControlReportingTolerances(
  std::shared_ptr<detail::OutputControlReportingTolerances_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType OutputControlReportingTolerances::iddObjectType() {
  return IddObjectType::OutputControl_ReportingTolerances;
}

double OutputControlReportingTolerances::toleranceforTimeHeatingSetpointNotMet() const {
  return getImpl<detail::OutputControlReportingTolerances_Impl>()->toleranceforTimeHeatingSetpointNotMet();
}

bool OutputControlReportingTolerances::isToleranceforTimeHeatingSetpointNotMetDefaulted() const {
  return getImpl<detail::OutputControlReportingTolerances_Impl>()->isToleranceforTimeHeatingSetpointNotMetDefaulted();
}

double OutputControlReportingTolerances::toleranceforTimeCoolingSetpointNotMet() const {
  return getImpl<detail::OutputControlReportingTolerances_Impl>()->toleranceforTimeCoolingSetpointNotMet();
}

bool OutputControlReportingTolerances::isToleranceforTimeCoolingSetpointNotMetDefaulted() const {
  return getImpl<detail::OutputControlReportingTolerances_Impl>()->isToleranceforTimeCoolingSetpointNotMetDefaulted();
}

bool OutputControlReportingTolerances::setToleranceforTimeHeatingSetpointNotMet(double toleranceforTimeHeatingSetpointNotMet) {
  return getImpl<detail::OutputControlReportingTolerances_Impl>()->setToleranceforTimeHeatingSetpointNotMet(
    toleranceforTimeHeatingSetpointNotMet);
}

void OutputControlReportingTolerances::resetToleranceforTimeHeatingSetpointNotMet() {
  getImpl<detail::OutputControlReportingTolerances_Impl>()->resetToleranceforTimeHeatingSetpointNotMet();
}

bool OutputControlReportingTolerances::setToleranceforTimeCoolingSetpointNotMet(double toleranceforTimeCoolingSetpointNotMet) {
  return getImpl<detail::OutputControlReportingTolerances_Impl>()->setToleranceforTimeCoolingSetpointNotMet(
    toleranceforTimeCoolingSetpointNotMet);
}

void OutputControlReportingTolerances::resetToleranceforTimeCoolingSetpointNotMet() {
  getImpl<detail::OutputControlReportingTolerances_Impl>()->resetToleranceforTimeCoolingSetpointNotMet();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

double OutputControlReportingTolerances_Impl::toleranceforTimeHeatingSetpointNotMet() const {
  const auto value = getDouble(openstudio::OutputControl_ReportingTolerancesFields::ToleranceforTimeHeatingSetpointNotMet, true);
  OS_ASSERT(value);
  return *value;
}

bool OutputControlReportingTolerances_Impl::isToleranceforTimeHeatingSetpointNotMetDefaulted() const {
  return isEmpty(openstudio::OutputControl_ReportingTolerancesFields::ToleranceforTimeHeatingSetpointNotMet);
}

double OutputControlReportingTolerances_Impl::toleranceforTimeCoolingSetpointNotMet() const {
  const auto value = getDouble(openstudio::OutputControl_ReportingTolerancesFields::ToleranceforTimeCoolingSetpointNotMet, true);
  OS_ASSERT(value);
  return *value;
}

bool OutputControlReportingTolerances_Impl::isToleranceforTimeCoolingSetpointNotMetDefaulted() const {
  return isEmpty(openstudio::OutputControl_ReportingTolerancesFields::ToleranceforTimeCoolingSetpointNotMet);
}

bool OutputControlReportingTolerances_Impl::setToleranceforTimeHeatingSetpointNotMet(double toleranceforTimeHeatingSetpointNotMet) {
  const bool result =
    setDouble(openstudio::OutputControl_ReportingTolerancesFields::ToleranceforTimeHeatingSetpointNotMet,
              toleranceforTimeHeatingSetpointNotMet);
  OS_ASSERT(result);
  return result;
}

void OutputControlReportingTolerances_Impl::resetToleranceforTimeHeatingSetpointNotMet() {
  const bool result = setString(openstudio::OutputControl_ReportingTolerancesFields::ToleranceforTimeHeatingSetpointNotMet, "");
  OS_ASSERT(result);
}

bool OutputControlReportingTolerances_Impl::setToleranceforTimeCoolingSetpointNotMet(double toleranceforTimeCoolingSetpointNotMet) {
  const bool result =
    setDouble(openstudio::OutputControl_ReportingTolerancesFields::ToleranceforTimeCoolingSetpointNotMet,
              toleranceforTimeCoolingSetpointNotMet);
  OS_ASSERT(result);
  return result;
}

void OutputControlReportingTolerances_Impl::resetToleranceforTimeCoolingSetpointNotMet() {
  const bool result = setString(openstudio::OutputControl_ReportingTolerancesFields::ToleranceforTimeCoolingSetpointNotMet, "");
  OS_ASSERT(result);
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
