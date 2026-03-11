/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_OUTPUTTABLEREPORTPERIOD_HPP
#define EPMODEL_OUTPUTTABLEREPORTPERIOD_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class OutputTableReportPeriod_Impl;
}

class EPMODEL_API OutputTableReportPeriod : public ModelObject
{
 public:
  explicit OutputTableReportPeriod(const Model& model);

  virtual ~OutputTableReportPeriod() override = default;
  OutputTableReportPeriod(const OutputTableReportPeriod& other) = default;
  OutputTableReportPeriod(OutputTableReportPeriod&& other) = default;
  OutputTableReportPeriod& operator=(const OutputTableReportPeriod&) = default;
  OutputTableReportPeriod& operator=(OutputTableReportPeriod&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> reportNameValues();

  // Schema Alignment Notes:
  // - API: This no-counterpart epmodel type uses IDD-derived class/accessor naming.
  // - Field Mapping: reportName, begin/end year, begin/end month, begin/end day, and begin/end hour map directly to E+ Output:Table:ReportPeriod scalar fields.
  // - Field Mapping: Name is available through base ModelObject name accessors and is not duplicated here.
  boost::optional<std::string> reportName() const;

  boost::optional<int> beginYear() const;

  int beginMonth() const;

  int beginDayofMonth() const;

  int beginHourofDay() const;

  boost::optional<int> endYear() const;

  int endMonth() const;

  int endDayofMonth() const;

  int endHourofDay() const;

  bool setReportName(const std::string& reportName);
  void resetReportName();

  bool setBeginYear(int beginYear);
  void resetBeginYear();

  bool setBeginMonth(int beginMonth);

  bool setBeginDayofMonth(int beginDayofMonth);

  bool setBeginHourofDay(int beginHourofDay);

  bool setEndYear(int endYear);
  void resetEndYear();

  bool setEndMonth(int endMonth);

  bool setEndDayofMonth(int endDayofMonth);

  bool setEndHourofDay(int endHourofDay);

 protected:
  using ImplType = detail::OutputTableReportPeriod_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit OutputTableReportPeriod(std::shared_ptr<detail::OutputTableReportPeriod_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
