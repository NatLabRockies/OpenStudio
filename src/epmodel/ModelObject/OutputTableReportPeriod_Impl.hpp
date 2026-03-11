/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_OUTPUTTABLEREPORTPERIOD_IMPL_HPP
#define EPMODEL_OUTPUTTABLEREPORTPERIOD_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API OutputTableReportPeriod_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~OutputTableReportPeriod_Impl() override = default;

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

  std::vector<std::string> reportNameValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
