/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "OutputTableReportPeriod.hpp"
#include "OutputTableReportPeriod_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/Output_Table_ReportPeriod_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  OutputTableReportPeriod::OutputTableReportPeriod(const Model& model) : ModelObject(OutputTableReportPeriod::iddObjectType(), model) {}

  OutputTableReportPeriod::OutputTableReportPeriod(std::shared_ptr<detail::OutputTableReportPeriod_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType OutputTableReportPeriod::iddObjectType() {
    return IddObjectType::Output_Table_ReportPeriod;
  }

  std::vector<std::string> OutputTableReportPeriod::reportNameValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Output_Table_ReportPeriodFields::ReportName);
  }

  boost::optional<std::string> OutputTableReportPeriod::reportName() const {
    return getImpl<detail::OutputTableReportPeriod_Impl>()->reportName();
  }

  bool OutputTableReportPeriod::setReportName(const std::string& reportName) {
    return getImpl<detail::OutputTableReportPeriod_Impl>()->setReportName(reportName);
  }

  void OutputTableReportPeriod::resetReportName() {
    getImpl<detail::OutputTableReportPeriod_Impl>()->resetReportName();
  }

  boost::optional<int> OutputTableReportPeriod::beginYear() const {
    return getImpl<detail::OutputTableReportPeriod_Impl>()->beginYear();
  }

  bool OutputTableReportPeriod::setBeginYear(int beginYear) {
    return getImpl<detail::OutputTableReportPeriod_Impl>()->setBeginYear(beginYear);
  }

  void OutputTableReportPeriod::resetBeginYear() {
    getImpl<detail::OutputTableReportPeriod_Impl>()->resetBeginYear();
  }

  int OutputTableReportPeriod::beginMonth() const {
    return getImpl<detail::OutputTableReportPeriod_Impl>()->beginMonth();
  }

  bool OutputTableReportPeriod::setBeginMonth(int beginMonth) {
    return getImpl<detail::OutputTableReportPeriod_Impl>()->setBeginMonth(beginMonth);
  }

  int OutputTableReportPeriod::beginDayofMonth() const {
    return getImpl<detail::OutputTableReportPeriod_Impl>()->beginDayofMonth();
  }

  bool OutputTableReportPeriod::setBeginDayofMonth(int beginDayofMonth) {
    return getImpl<detail::OutputTableReportPeriod_Impl>()->setBeginDayofMonth(beginDayofMonth);
  }

  int OutputTableReportPeriod::beginHourofDay() const {
    return getImpl<detail::OutputTableReportPeriod_Impl>()->beginHourofDay();
  }

  bool OutputTableReportPeriod::setBeginHourofDay(int beginHourofDay) {
    return getImpl<detail::OutputTableReportPeriod_Impl>()->setBeginHourofDay(beginHourofDay);
  }

  boost::optional<int> OutputTableReportPeriod::endYear() const {
    return getImpl<detail::OutputTableReportPeriod_Impl>()->endYear();
  }

  bool OutputTableReportPeriod::setEndYear(int endYear) {
    return getImpl<detail::OutputTableReportPeriod_Impl>()->setEndYear(endYear);
  }

  void OutputTableReportPeriod::resetEndYear() {
    getImpl<detail::OutputTableReportPeriod_Impl>()->resetEndYear();
  }

  int OutputTableReportPeriod::endMonth() const {
    return getImpl<detail::OutputTableReportPeriod_Impl>()->endMonth();
  }

  bool OutputTableReportPeriod::setEndMonth(int endMonth) {
    return getImpl<detail::OutputTableReportPeriod_Impl>()->setEndMonth(endMonth);
  }

  int OutputTableReportPeriod::endDayofMonth() const {
    return getImpl<detail::OutputTableReportPeriod_Impl>()->endDayofMonth();
  }

  bool OutputTableReportPeriod::setEndDayofMonth(int endDayofMonth) {
    return getImpl<detail::OutputTableReportPeriod_Impl>()->setEndDayofMonth(endDayofMonth);
  }

  int OutputTableReportPeriod::endHourofDay() const {
    return getImpl<detail::OutputTableReportPeriod_Impl>()->endHourofDay();
  }

  bool OutputTableReportPeriod::setEndHourofDay(int endHourofDay) {
    return getImpl<detail::OutputTableReportPeriod_Impl>()->setEndHourofDay(endHourofDay);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<std::string> OutputTableReportPeriod_Impl::reportName() const {
      if (isEmpty(openstudio::Output_Table_ReportPeriodFields::ReportName)) {
        return boost::none;
      }
      return getString(openstudio::Output_Table_ReportPeriodFields::ReportName, true);
    }

    bool OutputTableReportPeriod_Impl::setReportName(const std::string& reportName) {
      return setString(openstudio::Output_Table_ReportPeriodFields::ReportName, reportName);
    }

    void OutputTableReportPeriod_Impl::resetReportName() {
      const bool result = setString(openstudio::Output_Table_ReportPeriodFields::ReportName, "");
      OS_ASSERT(result);
    }

    boost::optional<int> OutputTableReportPeriod_Impl::beginYear() const {
      return getInt(openstudio::Output_Table_ReportPeriodFields::BeginYear, true);
    }

    bool OutputTableReportPeriod_Impl::setBeginYear(int beginYear) {
      return setInt(openstudio::Output_Table_ReportPeriodFields::BeginYear, beginYear);
    }

    void OutputTableReportPeriod_Impl::resetBeginYear() {
      const bool result = setString(openstudio::Output_Table_ReportPeriodFields::BeginYear, "");
      OS_ASSERT(result);
    }

    int OutputTableReportPeriod_Impl::beginMonth() const {
      const auto value = getInt(openstudio::Output_Table_ReportPeriodFields::BeginMonth, true);
      OS_ASSERT(value);
      return *value;
    }

    bool OutputTableReportPeriod_Impl::setBeginMonth(int beginMonth) {
      return setInt(openstudio::Output_Table_ReportPeriodFields::BeginMonth, beginMonth);
    }

    int OutputTableReportPeriod_Impl::beginDayofMonth() const {
      const auto value = getInt(openstudio::Output_Table_ReportPeriodFields::BeginDayofMonth, true);
      OS_ASSERT(value);
      return *value;
    }

    bool OutputTableReportPeriod_Impl::setBeginDayofMonth(int beginDayofMonth) {
      return setInt(openstudio::Output_Table_ReportPeriodFields::BeginDayofMonth, beginDayofMonth);
    }

    int OutputTableReportPeriod_Impl::beginHourofDay() const {
      const auto value = getInt(openstudio::Output_Table_ReportPeriodFields::BeginHourofDay, true);
      OS_ASSERT(value);
      return *value;
    }

    bool OutputTableReportPeriod_Impl::setBeginHourofDay(int beginHourofDay) {
      return setInt(openstudio::Output_Table_ReportPeriodFields::BeginHourofDay, beginHourofDay);
    }

    boost::optional<int> OutputTableReportPeriod_Impl::endYear() const {
      return getInt(openstudio::Output_Table_ReportPeriodFields::EndYear, true);
    }

    bool OutputTableReportPeriod_Impl::setEndYear(int endYear) {
      return setInt(openstudio::Output_Table_ReportPeriodFields::EndYear, endYear);
    }

    void OutputTableReportPeriod_Impl::resetEndYear() {
      const bool result = setString(openstudio::Output_Table_ReportPeriodFields::EndYear, "");
      OS_ASSERT(result);
    }

    int OutputTableReportPeriod_Impl::endMonth() const {
      const auto value = getInt(openstudio::Output_Table_ReportPeriodFields::EndMonth, true);
      OS_ASSERT(value);
      return *value;
    }

    bool OutputTableReportPeriod_Impl::setEndMonth(int endMonth) {
      return setInt(openstudio::Output_Table_ReportPeriodFields::EndMonth, endMonth);
    }

    int OutputTableReportPeriod_Impl::endDayofMonth() const {
      const auto value = getInt(openstudio::Output_Table_ReportPeriodFields::EndDayofMonth, true);
      OS_ASSERT(value);
      return *value;
    }

    bool OutputTableReportPeriod_Impl::setEndDayofMonth(int endDayofMonth) {
      return setInt(openstudio::Output_Table_ReportPeriodFields::EndDayofMonth, endDayofMonth);
    }

    int OutputTableReportPeriod_Impl::endHourofDay() const {
      const auto value = getInt(openstudio::Output_Table_ReportPeriodFields::EndHourofDay, true);
      OS_ASSERT(value);
      return *value;
    }

    bool OutputTableReportPeriod_Impl::setEndHourofDay(int endHourofDay) {
      return setInt(openstudio::Output_Table_ReportPeriodFields::EndHourofDay, endHourofDay);
    }

    std::vector<std::string> OutputTableReportPeriod_Impl::reportNameValues() const {
      return openstudio::epmodel::OutputTableReportPeriod::reportNameValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
