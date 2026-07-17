/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ScheduleInterval/ScheduleFile.hpp"
#include "ScheduleInterval/ScheduleFile_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/Schedule_File_FieldEnums.hxx>
#include <utilities/core/DeprecatedHelpers.hpp>
#include <utilities/core/Logger.hpp>

#include "../utilities/data/TimeSeries.hpp"

namespace openstudio {
namespace epmodel {

  // ScheduleFile(const ExternalFile& externalfile, int column = 1, int rowsToSkip = 0) : Schedule(ScheduleFile::iddObjectType(), model) {}

  ScheduleFile::ScheduleFile(const Model& model, int column, int rowsToSkip) : Schedule(ScheduleFile::iddObjectType(), model) {
    // Mirror preserved counterpart constructor behavior for required scalar fields.
    bool ok = true;
    ok &= setColumnNumber(column);
    ok &= setRowstoSkipatTop(rowsToSkip);
    OS_ASSERT(ok);
  }

  ScheduleFile::ScheduleFile(const Model& model, const openstudio::path& filePath, int column, int rowsToSkip, bool translateFileWithRelativePath)
    : Schedule(ScheduleFile::iddObjectType(), model) {

    openstudio::path p;
    if (!exists(filePath)) {
      this->remove();
      LOG_FREE_AND_THROW("openstudio.epmodel.ScheduleFile", "Cannot find file \"" << toString(filePath) << "\" for " << briefDescription());
    } else {
      if (translateFileWithRelativePath) {
        p = filePath;
      } else {
        // make the path correct for this system
        p = system_complete(filePath);
      }
    }

    bool ok = true;
    ok &= getImpl<detail::ScheduleFile_Impl>()->setFileName(toString(p));
    ok &= setColumnNumber(column);
    ok &= setRowstoSkipatTop(rowsToSkip);
    OS_ASSERT(ok);
  }

  ScheduleFile::ScheduleFile(std::shared_ptr<detail::ScheduleFile_Impl> impl) : Schedule(std::move(impl)) {}

  IddObjectType ScheduleFile::iddObjectType() {
    return IddObjectType::Schedule_File;
  }

  std::vector<std::string> ScheduleFile::columnSeparatorValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Schedule_FileFields::ColumnSeparator);
  }

  std::vector<std::string> ScheduleFile::minutesperItemValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Schedule_FileFields::MinutesperItem);
  }

  // std::string ScheduleFile::fileName() const {
  //   return getImpl<detail::ScheduleFile_Impl>()->fileName();
  // }

  // bool ScheduleFile::setFileName(std::string fileName) {
  //   return getImpl<detail::ScheduleFile_Impl>()->setFileName(fileName);
  // }

  int ScheduleFile::columnNumber() const {
    return getImpl<detail::ScheduleFile_Impl>()->columnNumber();
  }

  bool ScheduleFile::setColumnNumber(int columnNumber) {
    return getImpl<detail::ScheduleFile_Impl>()->setColumnNumber(columnNumber);
  }

  int ScheduleFile::rowstoSkipatTop() const {
    return getImpl<detail::ScheduleFile_Impl>()->rowstoSkipatTop();
  }

  bool ScheduleFile::setRowstoSkipatTop(int rowstoSkipatTop) {
    return getImpl<detail::ScheduleFile_Impl>()->setRowstoSkipatTop(rowstoSkipatTop);
  }

  boost::optional<int> ScheduleFile::numberofHoursofData() const {
    return getImpl<detail::ScheduleFile_Impl>()->numberofHoursofData();
  }

  bool ScheduleFile::isNumberofHoursofDataDefaulted() const {
    return getImpl<detail::ScheduleFile_Impl>()->isNumberofHoursofDataDefaulted();
  }

  bool ScheduleFile::setNumberofHoursofData(int numberofHours) {
    return getImpl<detail::ScheduleFile_Impl>()->setNumberofHoursofData(numberofHours);
  }

  std::string ScheduleFile::columnSeparator() const {
    return getImpl<detail::ScheduleFile_Impl>()->columnSeparator();
  }

  bool ScheduleFile::isColumnSeparatorDefaulted() const {
    return getImpl<detail::ScheduleFile_Impl>()->isColumnSeparatorDefaulted();
  }

  bool ScheduleFile::setColumnSeparator(const std::string& columnSeparator) {
    return getImpl<detail::ScheduleFile_Impl>()->setColumnSeparator(columnSeparator);
  }

  void ScheduleFile::resetColumnSeparator() {
    getImpl<detail::ScheduleFile_Impl>()->resetColumnSeparator();
  }

  bool ScheduleFile::interpolatetoTimestep() const {
    return getImpl<detail::ScheduleFile_Impl>()->interpolatetoTimestep();
  }

  bool ScheduleFile::isInterpolatetoTimestepDefaulted() const {
    return getImpl<detail::ScheduleFile_Impl>()->isInterpolatetoTimestepDefaulted();
  }

  bool ScheduleFile::setInterpolatetoTimestep(bool interpolatetoTimestep) {
    return getImpl<detail::ScheduleFile_Impl>()->setInterpolatetoTimestep(interpolatetoTimestep);
  }

  void ScheduleFile::resetInterpolatetoTimestep() {
    getImpl<detail::ScheduleFile_Impl>()->resetInterpolatetoTimestep();
  }

  boost::optional<std::string> ScheduleFile::minutesperItem() const {
    return getImpl<detail::ScheduleFile_Impl>()->minutesperItem();
  }

  bool ScheduleFile::isMinutesperItemDefaulted() const {
    return getImpl<detail::ScheduleFile_Impl>()->isMinutesperItemDefaulted();
  }

  bool ScheduleFile::setMinutesperItem(const std::string& minutesperItem) {
    try {
      return getImpl<detail::ScheduleFile_Impl>()->setMinutesperItem(std::stoi(minutesperItem));
    } catch (const std::exception&) {
      return false;
    }
  }

  bool ScheduleFile::setMinutesperItem(int minutesperItem) {
    return getImpl<detail::ScheduleFile_Impl>()->setMinutesperItem(minutesperItem);
  }

  void ScheduleFile::resetMinutesperItem() {
    getImpl<detail::ScheduleFile_Impl>()->resetMinutesperItem();
  }

  bool ScheduleFile::adjustScheduleforDaylightSavings() const {
    return getImpl<detail::ScheduleFile_Impl>()->adjustScheduleforDaylightSavings();
  }

  bool ScheduleFile::isAdjustScheduleforDaylightSavingsDefaulted() const {
    return getImpl<detail::ScheduleFile_Impl>()->isAdjustScheduleforDaylightSavingsDefaulted();
  }

  bool ScheduleFile::setAdjustScheduleforDaylightSavings(bool adjustScheduleforDaylightSavings) {
    return getImpl<detail::ScheduleFile_Impl>()->setAdjustScheduleforDaylightSavings(adjustScheduleforDaylightSavings);
  }

  void ScheduleFile::resetAdjustScheduleforDaylightSavings() {
    getImpl<detail::ScheduleFile_Impl>()->resetAdjustScheduleforDaylightSavings();
  }

  boost::optional<CSVFile> ScheduleFile::csvFile() const {
    return getImpl<detail::ScheduleFile_Impl>()->csvFile();
  }

  bool ScheduleFile::translateFileWithRelativePath() const {
    DEPRECATED_AT_MSG(4, 0, 0, "Schedule:File is no longer 'translated'.");
    return false;
  }
  
  bool ScheduleFile::isTranslateFileWithRelativePathDefaulted() const {
    DEPRECATED_AT_MSG(4, 0, 0, "Schedule:File is no longer 'translated'.");
    return false;
  }
  
  bool ScheduleFile::setTranslateFileWithRelativePath(bool translateFileWithRelativePath) {
    DEPRECATED_AT_MSG(4, 0, 0, "Schedule:File is no longer 'translated'.");
    return false;
  }
  
  void ScheduleFile::resetTranslateFileWithRelativePath() {
    DEPRECATED_AT_MSG(4, 0, 0, "Schedule:File is no longer 'translated'.");
  }
  
  openstudio::path ScheduleFile::translatedFilePath() const {
    return getImpl<epmodel::detail::ScheduleFile_Impl>()->translatedFilePath();
  }

  boost::optional<ScheduleFile> ScheduleFile::fromTimeSeries(const openstudio::TimeSeries& timeSeries, Model& model) {
    boost::optional<ScheduleFile> result;

    boost::optional<openstudio::Time> intervalTime = timeSeries.intervalLength();
    if (intervalTime) {
      result = ScheduleFile(model, 2); // FT ScheduleFixedInterval wrote the dateTimes to file
      const std::string name = result->nameString();
      openstudio::path filePath = toPath(name + ".csv");

      CSVFile csvFile;
      csvFile.addColumn(timeSeries.dateTimes());
      csvFile.addColumn(timeSeries.values());
      csvFile.saveAs(filePath);

      openstudio::path p;
      if (!exists(filePath)) {
        result->remove();
        // LOG_AND_THROW("Cannot find file \"" << toString(filePath) << "\" for " << briefDescription());
      } else {
        // make the path correct for this system
        p = system_complete(filePath);
      }

      bool ok = true;
      ok &= result->getImpl<detail::ScheduleFile_Impl>()->setFileName(toString(p));
      ok &= result->getImpl<detail::ScheduleFile_Impl>()->setTimeSeries(timeSeries);
      OS_ASSERT(ok);
    } else {
      LOG_FREE(Warn, "openstudio.epmodel.ScheduleFile", "Timeseries does not have an interval length defined, but ScheduleVariableInterval is deprecated");
    }

    return result;
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    bool ScheduleFile_Impl::setTimeSeries(const openstudio::TimeSeries& timeSeries) {
      boost::optional<openstudio::Time> intervalTime = timeSeries.intervalLength();
      if (!intervalTime) {
        return false;
      }

      auto intervalLengthAsInteger = [](const double value) -> int {
        double integralPart = 0.0;
        if (std::modf(value, &integralPart) == 0.0) {
          // The intervalLength is actually an int, not a double
          return static_cast<int>(integralPart);
        }
        return -1;
      };

      // check the interval
      const double intervalLengthDouble = intervalTime->totalMinutes();
      const int intervalLength = intervalLengthAsInteger(intervalLengthDouble);
      if (intervalLength < 0) {
        return false;
      }

      bool ok = true;
      ok &= this->setMinutesperItem(intervalLength);
      // Do we actually need the following? They aren't required in the IDD.
      //ok &= this->setNumberofHoursofData(8760);
      //ok &= this->setColumnSeparator("Comma");
      //ok &= this->setInterpolatetoTimestep(true);
      //ok &= this->setAdjustScheduleforDaylightSavings(true);
      return true;
    }

    std::string ScheduleFile_Impl::fileName() const {
      const auto value = getString(openstudio::Schedule_FileFields::FileName, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ScheduleFile_Impl::setFileName(std::string fileName) {
      const bool result = setString(openstudio::Schedule_FileFields::FileName, fileName);
      OS_ASSERT(result);
      return result;
    }

    int ScheduleFile_Impl::columnNumber() const {
      const auto value = getInt(openstudio::Schedule_FileFields::ColumnNumber, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ScheduleFile_Impl::setColumnNumber(int columnNumber) {
      return setInt(openstudio::Schedule_FileFields::ColumnNumber, columnNumber);
    }

    int ScheduleFile_Impl::rowstoSkipatTop() const {
      const auto value = getInt(openstudio::Schedule_FileFields::RowstoSkipatTop, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ScheduleFile_Impl::setRowstoSkipatTop(int rowstoSkipatTop) {
      return setInt(openstudio::Schedule_FileFields::RowstoSkipatTop, rowstoSkipatTop);
    }

    boost::optional<int> ScheduleFile_Impl::numberofHoursofData() const {
      return getInt(openstudio::Schedule_FileFields::NumberofHoursofData, true);
    }

    bool ScheduleFile_Impl::isNumberofHoursofDataDefaulted() const {
      return isEmpty(openstudio::Schedule_FileFields::NumberofHoursofData);
    }

    bool ScheduleFile_Impl::setNumberofHoursofData(int numberofHours) {
      return setInt(openstudio::Schedule_FileFields::NumberofHoursofData, numberofHours);
    }

    std::string ScheduleFile_Impl::columnSeparator() const {
      const auto value = getString(openstudio::Schedule_FileFields::ColumnSeparator, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ScheduleFile_Impl::isColumnSeparatorDefaulted() const {
      return isEmpty(openstudio::Schedule_FileFields::ColumnSeparator);
    }

    bool ScheduleFile_Impl::setColumnSeparator(const std::string& columnSeparator) {
      return setString(openstudio::Schedule_FileFields::ColumnSeparator, columnSeparator);
    }

    void ScheduleFile_Impl::resetColumnSeparator() {
      OS_ASSERT(setString(openstudio::Schedule_FileFields::ColumnSeparator, ""));
    }

    bool ScheduleFile_Impl::interpolatetoTimestep() const {
      const auto value = getString(openstudio::Schedule_FileFields::InterpolatetoTimestep, true);
      OS_ASSERT(value);
      return openstudio::istringEqual(*value, "Yes");
    }

    bool ScheduleFile_Impl::isInterpolatetoTimestepDefaulted() const {
      return isEmpty(openstudio::Schedule_FileFields::InterpolatetoTimestep);
    }

    bool ScheduleFile_Impl::setInterpolatetoTimestep(bool interpolatetoTimestep) {
      const bool result = setString(openstudio::Schedule_FileFields::InterpolatetoTimestep, interpolatetoTimestep ? "Yes" : "No");
      OS_ASSERT(result);
      return result;
    }

    void ScheduleFile_Impl::resetInterpolatetoTimestep() {
      OS_ASSERT(setString(openstudio::Schedule_FileFields::InterpolatetoTimestep, ""));
    }

    boost::optional<std::string> ScheduleFile_Impl::minutesperItem() const {
      const auto value = getInt(openstudio::Schedule_FileFields::MinutesperItem, true);
      OS_ASSERT(value);
      return std::to_string(*value);
    }

    bool ScheduleFile_Impl::isMinutesperItemDefaulted() const {
      return isEmpty(openstudio::Schedule_FileFields::MinutesperItem);
    }

    bool ScheduleFile_Impl::setMinutesperItem(int minutesperItem) {
      return setInt(openstudio::Schedule_FileFields::MinutesperItem, minutesperItem);
    }

    void ScheduleFile_Impl::resetMinutesperItem() {
      OS_ASSERT(setString(openstudio::Schedule_FileFields::MinutesperItem, ""));
    }

    bool ScheduleFile_Impl::adjustScheduleforDaylightSavings() const {
      const auto value = getString(openstudio::Schedule_FileFields::AdjustScheduleforDaylightSavings, true);
      OS_ASSERT(value);
      return openstudio::istringEqual(*value, "Yes");
    }

    bool ScheduleFile_Impl::isAdjustScheduleforDaylightSavingsDefaulted() const {
      return isEmpty(openstudio::Schedule_FileFields::AdjustScheduleforDaylightSavings);
    }

    bool ScheduleFile_Impl::setAdjustScheduleforDaylightSavings(bool adjustScheduleforDaylightSavings) {
      const bool result =
        setString(openstudio::Schedule_FileFields::AdjustScheduleforDaylightSavings, adjustScheduleforDaylightSavings ? "Yes" : "No");
      OS_ASSERT(result);
      return result;
    }

    void ScheduleFile_Impl::resetAdjustScheduleforDaylightSavings() {
      OS_ASSERT(setString(openstudio::Schedule_FileFields::AdjustScheduleforDaylightSavings, ""));
    }

    boost::optional<CSVFile> ScheduleFile_Impl::csvFile() const {
      boost::optional<CSVFile> csvFile;
      csvFile = CSVFile::load(this->fileName());
      return csvFile;
    }

    openstudio::path ScheduleFile_Impl::translatedFilePath() const {
      openstudio::path filePath = this->fileName();
      if (!exists(filePath)) {
        LOG_FREE(Warn, "openstudio.epmodel.ScheduleFile", "Cannot find file \"" << filePath << "\"");
      }
      return filePath;
    }

    std::vector<std::string> ScheduleFile_Impl::columnSeparatorValues() const {
      return openstudio::epmodel::ScheduleFile::columnSeparatorValues();
    }

    std::vector<std::string> ScheduleFile_Impl::minutesperItemValues() const {
      return openstudio::epmodel::ScheduleFile::minutesperItemValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
