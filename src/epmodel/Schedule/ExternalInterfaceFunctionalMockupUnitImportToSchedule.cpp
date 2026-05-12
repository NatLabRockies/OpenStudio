/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ExternalInterfaceFunctionalMockupUnitImportToSchedule.hpp"
#include "ExternalInterfaceFunctionalMockupUnitImportToSchedule_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/ExternalInterface_FunctionalMockupUnitImport_To_Schedule_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  ExternalInterfaceFunctionalMockupUnitImportToSchedule::ExternalInterfaceFunctionalMockupUnitImportToSchedule(const Model& model)
    : Schedule(ExternalInterfaceFunctionalMockupUnitImportToSchedule::iddObjectType(), model) {}

  ExternalInterfaceFunctionalMockupUnitImportToSchedule::ExternalInterfaceFunctionalMockupUnitImportToSchedule(
    std::shared_ptr<detail::ExternalInterfaceFunctionalMockupUnitImportToSchedule_Impl> impl)
    : Schedule(std::move(impl)) {}

  IddObjectType ExternalInterfaceFunctionalMockupUnitImportToSchedule::iddObjectType() {
    return IddObjectType::ExternalInterface_FunctionalMockupUnitImport_To_Schedule;
  }

  // FMU instance name
  std::string ExternalInterfaceFunctionalMockupUnitImportToSchedule::fMUInstanceName() const {
    return getImpl<detail::ExternalInterfaceFunctionalMockupUnitImportToSchedule_Impl>()->fMUInstanceName();
  }

  bool ExternalInterfaceFunctionalMockupUnitImportToSchedule::setFMUInstanceName(const std::string& fMUInstanceName) {
    return getImpl<detail::ExternalInterfaceFunctionalMockupUnitImportToSchedule_Impl>()->setFMUInstanceName(fMUInstanceName);
  }

  // FMU variable name
  std::string ExternalInterfaceFunctionalMockupUnitImportToSchedule::fMUVariableName() const {
    return getImpl<detail::ExternalInterfaceFunctionalMockupUnitImportToSchedule_Impl>()->fMUVariableName();
  }

  bool ExternalInterfaceFunctionalMockupUnitImportToSchedule::setFMUVariableName(const std::string& fMUVariableName) {
    return getImpl<detail::ExternalInterfaceFunctionalMockupUnitImportToSchedule_Impl>()->setFMUVariableName(fMUVariableName);
  }

  // Initial value
  double ExternalInterfaceFunctionalMockupUnitImportToSchedule::initialValue() const {
    return getImpl<detail::ExternalInterfaceFunctionalMockupUnitImportToSchedule_Impl>()->initialValue();
  }

  bool ExternalInterfaceFunctionalMockupUnitImportToSchedule::setInitialValue(double initialValue) {
    return getImpl<detail::ExternalInterfaceFunctionalMockupUnitImportToSchedule_Impl>()->setInitialValue(initialValue);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<unsigned> ExternalInterfaceFunctionalMockupUnitImportToSchedule_Impl::scheduleTypeLimitsFieldIndex() const {
      return openstudio::ExternalInterface_FunctionalMockupUnitImport_To_ScheduleFields::ScheduleTypeLimitsNames;
    }

    // FMU instance name
    std::string ExternalInterfaceFunctionalMockupUnitImportToSchedule_Impl::fMUInstanceName() const {
      const auto value = getString(openstudio::ExternalInterface_FunctionalMockupUnitImport_To_ScheduleFields::FMUInstanceName, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ExternalInterfaceFunctionalMockupUnitImportToSchedule_Impl::setFMUInstanceName(const std::string& fMUInstanceName) {
      const bool result = setString(openstudio::ExternalInterface_FunctionalMockupUnitImport_To_ScheduleFields::FMUInstanceName, fMUInstanceName);
      OS_ASSERT(result);
      return result;
    }

    // FMU variable name
    std::string ExternalInterfaceFunctionalMockupUnitImportToSchedule_Impl::fMUVariableName() const {
      const auto value = getString(openstudio::ExternalInterface_FunctionalMockupUnitImport_To_ScheduleFields::FMUVariableName, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ExternalInterfaceFunctionalMockupUnitImportToSchedule_Impl::setFMUVariableName(const std::string& fMUVariableName) {
      const bool result = setString(openstudio::ExternalInterface_FunctionalMockupUnitImport_To_ScheduleFields::FMUVariableName, fMUVariableName);
      OS_ASSERT(result);
      return result;
    }

    // Initial value
    double ExternalInterfaceFunctionalMockupUnitImportToSchedule_Impl::initialValue() const {
      const auto value = getDouble(openstudio::ExternalInterface_FunctionalMockupUnitImport_To_ScheduleFields::InitialValue, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ExternalInterfaceFunctionalMockupUnitImportToSchedule_Impl::setInitialValue(double initialValue) {
      const bool result = setDouble(openstudio::ExternalInterface_FunctionalMockupUnitImport_To_ScheduleFields::InitialValue, initialValue);
      OS_ASSERT(result);
      return result;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
