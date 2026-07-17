/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SCHEDULEFILE_IMPL_HPP
#define EPMODEL_SCHEDULEFILE_IMPL_HPP

#include "Schedule/Schedule_Impl.hpp"
#include "../utilities/filetypes/CSVFile.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {
  namespace detail {

    class EPMODEL_API ScheduleFile_Impl : public Schedule_Impl
    {
     public:
      using Schedule_Impl::Schedule_Impl;
      virtual ~ScheduleFile_Impl() override = default;

      std::string fileName() const;
      bool setFileName(std::string fileName);

      int columnNumber() const;
      bool setColumnNumber(int columnNumber);

      int rowstoSkipatTop() const;
      bool setRowstoSkipatTop(int rowstoSkipatTop);

      boost::optional<int> numberofHoursofData() const;
      bool isNumberofHoursofDataDefaulted() const;
      bool setNumberofHoursofData(int numberofHours);

      std::string columnSeparator() const;
      bool isColumnSeparatorDefaulted() const;
      bool setColumnSeparator(const std::string& columnSeparator);
      void resetColumnSeparator();

      bool interpolatetoTimestep() const;
      bool isInterpolatetoTimestepDefaulted() const;
      bool setInterpolatetoTimestep(bool interpolatetoTimestep);
      void resetInterpolatetoTimestep();

      boost::optional<std::string> minutesperItem() const;
      bool isMinutesperItemDefaulted() const;
      bool setMinutesperItem(int minutesperItem);
      void resetMinutesperItem();

      bool adjustScheduleforDaylightSavings() const;
      bool isAdjustScheduleforDaylightSavingsDefaulted() const;
      bool setAdjustScheduleforDaylightSavings(bool adjustScheduleforDaylightSavings);
      void resetAdjustScheduleforDaylightSavings();

      // openstudio::TimeSeries timeSeries() const;
      bool setTimeSeries(const openstudio::TimeSeries& timeSeries);

      // Extra setters/getters
      boost::optional<CSVFile> csvFile() const;
      // bool translateFileWithRelativePath() const;
      // bool isTranslateFileWithRelativePathDefaulted() const;
      // void ensureNoLeapDays();
      // bool setTranslateFileWithRelativePath(bool translateFileWithRelativePath);
      // void resetTranslateFileWithRelativePath();
      openstudio::path translatedFilePath() const;

      std::vector<std::string> columnSeparatorValues() const;
      std::vector<std::string> minutesperItemValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
