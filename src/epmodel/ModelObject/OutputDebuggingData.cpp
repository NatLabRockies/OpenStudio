/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ModelObject/OutputDebuggingData.hpp"
#include "ModelObject/OutputDebuggingData_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Output_DebuggingData_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  OutputDebuggingData::OutputDebuggingData(const Model& model) : ModelObject(OutputDebuggingData::iddObjectType(), model) {
    const bool ok = setReportDebuggingData(false);
    OS_ASSERT(ok);
    const bool ok2 = setReportDuringWarmup(false);
    OS_ASSERT(ok2);
  }

  OutputDebuggingData::OutputDebuggingData(std::shared_ptr<detail::OutputDebuggingData_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType OutputDebuggingData::iddObjectType() {
    return IddObjectType::Output_DebuggingData;
  }

  bool OutputDebuggingData::reportDebuggingData() const {
    return getImpl<detail::OutputDebuggingData_Impl>()->reportDebuggingData();
  }

  bool OutputDebuggingData::setReportDebuggingData(bool reportDebuggingData) {
    return getImpl<detail::OutputDebuggingData_Impl>()->setReportDebuggingData(reportDebuggingData);
  }

  bool OutputDebuggingData::reportDuringWarmup() const {
    return getImpl<detail::OutputDebuggingData_Impl>()->reportDuringWarmup();
  }

  bool OutputDebuggingData::setReportDuringWarmup(bool reportDuringWarmup) {
    return getImpl<detail::OutputDebuggingData_Impl>()->setReportDuringWarmup(reportDuringWarmup);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    bool OutputDebuggingData_Impl::reportDebuggingData() const {
      if (const auto value = getString(openstudio::Output_DebuggingDataFields::ReportDebuggingData, true)) {
        return openstudio::istringEqual(*value, "Yes") || openstudio::istringEqual(*value, "True");
      }
      return false;
    }

    bool OutputDebuggingData_Impl::setReportDebuggingData(bool reportDebuggingData) {
      return setString(openstudio::Output_DebuggingDataFields::ReportDebuggingData, reportDebuggingData ? "Yes" : "No");
    }

    bool OutputDebuggingData_Impl::reportDuringWarmup() const {
      if (const auto value = getString(openstudio::Output_DebuggingDataFields::ReportDuringWarmup, true)) {
        return openstudio::istringEqual(*value, "Yes") || openstudio::istringEqual(*value, "True");
      }
      return false;
    }

    bool OutputDebuggingData_Impl::setReportDuringWarmup(bool reportDuringWarmup) {
      return setString(openstudio::Output_DebuggingDataFields::ReportDuringWarmup, reportDuringWarmup ? "Yes" : "No");
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
