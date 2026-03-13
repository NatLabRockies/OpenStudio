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
      bool setReportName(const std::string& reportName);
      void resetReportName();

      boost::optional<int> beginYear() const;
      bool setBeginYear(int beginYear);
      void resetBeginYear();

      int beginMonth() const;
      bool setBeginMonth(int beginMonth);

      int beginDayofMonth() const;
      bool setBeginDayofMonth(int beginDayofMonth);

      int beginHourofDay() const;
      bool setBeginHourofDay(int beginHourofDay);

      boost::optional<int> endYear() const;
      bool setEndYear(int endYear);
      void resetEndYear();

      int endMonth() const;
      bool setEndMonth(int endMonth);

      int endDayofMonth() const;
      bool setEndDayofMonth(int endDayofMonth);

      int endHourofDay() const;
      bool setEndHourofDay(int endHourofDay);

      std::vector<std::string> reportNameValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
