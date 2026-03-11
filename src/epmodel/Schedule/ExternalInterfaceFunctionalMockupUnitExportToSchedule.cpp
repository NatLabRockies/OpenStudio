/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ExternalInterfaceFunctionalMockupUnitExportToSchedule.hpp"
#include "ExternalInterfaceFunctionalMockupUnitExportToSchedule_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/ExternalInterface_FunctionalMockupUnitExport_To_Schedule_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

ExternalInterfaceFunctionalMockupUnitExportToSchedule::ExternalInterfaceFunctionalMockupUnitExportToSchedule(
  const Model& model, const std::string& fMUVariableName)
  : ModelObject(ExternalInterfaceFunctionalMockupUnitExportToSchedule::iddObjectType(), model) {
  OS_ASSERT(setFMUVariableName(fMUVariableName));
}

ExternalInterfaceFunctionalMockupUnitExportToSchedule::ExternalInterfaceFunctionalMockupUnitExportToSchedule(
  const Model& model, const std::string& fMUVariableName, double initialValue)
  : ModelObject(ExternalInterfaceFunctionalMockupUnitExportToSchedule::iddObjectType(), model) {
  OS_ASSERT(setFMUVariableName(fMUVariableName));
  OS_ASSERT(setInitialValue(initialValue));
}

ExternalInterfaceFunctionalMockupUnitExportToSchedule::ExternalInterfaceFunctionalMockupUnitExportToSchedule(
  std::shared_ptr<detail::ExternalInterfaceFunctionalMockupUnitExportToSchedule_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType ExternalInterfaceFunctionalMockupUnitExportToSchedule::iddObjectType() {
  return IddObjectType::ExternalInterface_FunctionalMockupUnitExport_To_Schedule;
}

std::string ExternalInterfaceFunctionalMockupUnitExportToSchedule::fMUVariableName() const {
  return getImpl<detail::ExternalInterfaceFunctionalMockupUnitExportToSchedule_Impl>()->fMUVariableName();
}

bool ExternalInterfaceFunctionalMockupUnitExportToSchedule::setFMUVariableName(const std::string& fMUVariableName) {
  return getImpl<detail::ExternalInterfaceFunctionalMockupUnitExportToSchedule_Impl>()->setFMUVariableName(fMUVariableName);
}

boost::optional<double> ExternalInterfaceFunctionalMockupUnitExportToSchedule::initialValue() const {
  return getImpl<detail::ExternalInterfaceFunctionalMockupUnitExportToSchedule_Impl>()->initialValue();
}

bool ExternalInterfaceFunctionalMockupUnitExportToSchedule::setInitialValue(double initialValue) {
  return getImpl<detail::ExternalInterfaceFunctionalMockupUnitExportToSchedule_Impl>()->setInitialValue(initialValue);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string ExternalInterfaceFunctionalMockupUnitExportToSchedule_Impl::fMUVariableName() const {
  const auto value = getString(openstudio::ExternalInterface_FunctionalMockupUnitExport_To_ScheduleFields::FMUVariableName, true);
  OS_ASSERT(value);
  return *value;
}

bool ExternalInterfaceFunctionalMockupUnitExportToSchedule_Impl::setFMUVariableName(const std::string& fMUVariableName) {
  const bool result = setString(openstudio::ExternalInterface_FunctionalMockupUnitExport_To_ScheduleFields::FMUVariableName, fMUVariableName);
  OS_ASSERT(result);
  return result;
}

boost::optional<double> ExternalInterfaceFunctionalMockupUnitExportToSchedule_Impl::initialValue() const {
  return getDouble(openstudio::ExternalInterface_FunctionalMockupUnitExport_To_ScheduleFields::InitialValue, true);
}

bool ExternalInterfaceFunctionalMockupUnitExportToSchedule_Impl::setInitialValue(double initialValue) {
  const bool result = setDouble(openstudio::ExternalInterface_FunctionalMockupUnitExport_To_ScheduleFields::InitialValue, initialValue);
  OS_ASSERT(result);
  return result;
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
