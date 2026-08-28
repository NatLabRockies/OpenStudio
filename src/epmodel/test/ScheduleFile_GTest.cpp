/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ScheduleInterval/ScheduleFile.hpp"
#include "../ScheduleInterval/ScheduleFile_Impl.hpp"

#include "../../utilities/data/TimeSeries.hpp"
#include "../../utilities/core/StringStreamLogSink.hpp"

using namespace openstudio;
using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ScheduleFile_DefaultConstructor) {
  Model model;
  ScheduleFile schedule(model);
  EXPECT_EQ(ScheduleFile::iddObjectType(), schedule.iddObject().type());

  EXPECT_EQ(1, schedule.columnNumber());
  EXPECT_EQ(0, schedule.rowstoSkipatTop());
}

TEST_F(EPModelFixture, ScheduleFile_ScalarAccessors_RoundTrip) {
  Model model;
  ScheduleFile schedule(model);

  EXPECT_TRUE(schedule.setColumnNumber(2));
  EXPECT_EQ(2, schedule.columnNumber());

  EXPECT_TRUE(schedule.setRowstoSkipatTop(3));
  EXPECT_EQ(3, schedule.rowstoSkipatTop());

  EXPECT_TRUE(schedule.setNumberofHoursofData(8760));
  ASSERT_TRUE(schedule.numberofHoursofData());
  EXPECT_EQ(8760, schedule.numberofHoursofData().get());
  EXPECT_FALSE(schedule.isNumberofHoursofDataDefaulted());

  EXPECT_TRUE(schedule.setColumnSeparator("Tab"));
  EXPECT_EQ("Tab", schedule.columnSeparator());
  EXPECT_FALSE(schedule.isColumnSeparatorDefaulted());
  schedule.resetColumnSeparator();
  EXPECT_TRUE(schedule.isColumnSeparatorDefaulted());
  EXPECT_EQ("Comma", schedule.columnSeparator());

  EXPECT_FALSE(schedule.interpolatetoTimestep());
  EXPECT_TRUE(schedule.setInterpolatetoTimestep(true));
  EXPECT_TRUE(schedule.interpolatetoTimestep());
  schedule.resetInterpolatetoTimestep();
  EXPECT_FALSE(schedule.interpolatetoTimestep());

  EXPECT_EQ(60, schedule.minutesperItem());
  EXPECT_TRUE(schedule.setMinutesperItem(15));
  EXPECT_EQ(15, schedule.minutesperItem());
  EXPECT_TRUE(schedule.setMinutesperItem("30"));
  EXPECT_EQ(30, schedule.minutesperItem());
  EXPECT_FALSE(schedule.setMinutesperItem("BAD"));
  schedule.resetMinutesperItem();
  EXPECT_TRUE(schedule.isMinutesperItemDefaulted());
  EXPECT_EQ(60, schedule.minutesperItem());

  EXPECT_TRUE(schedule.adjustScheduleforDaylightSavings());
  EXPECT_TRUE(schedule.setAdjustScheduleforDaylightSavings(false));
  EXPECT_FALSE(schedule.adjustScheduleforDaylightSavings());
  schedule.resetAdjustScheduleforDaylightSavings();
  EXPECT_TRUE(schedule.adjustScheduleforDaylightSavings());

  boost::optional<CSVFile> csvFile = schedule.csvFile();
  EXPECT_FALSE(csvFile);
}

TEST_F(EPModelFixture, ScheduleFile_AltCtor) {
  Model model;
  // EXPECT_EQ(0u, model.getConcreteModelObjects<ExternalFile>().size());
  EXPECT_EQ(0u, model.getConcreteModelObjects<ScheduleFile>().size());

  path p = resourcesPath() / toPath("model/schedulefile.csv");
  EXPECT_TRUE(exists(p));

/*   path expectedDestDir;
  std::vector<path> absoluteFilePaths = model.workflowJSON().absoluteFilePaths();
  if (absoluteFilePaths.empty()) {
    expectedDestDir = model.workflowJSON().absoluteRootDir();
  } else {
    expectedDestDir = absoluteFilePaths[0];
  }

  if (exists(expectedDestDir)) {
    removeDirectory(expectedDestDir);
  }
  ASSERT_FALSE(exists(expectedDestDir)); */

  ScheduleFile schedule(model, openstudio::toString(p));
  EXPECT_EQ(1u, model.getConcreteModelObjects<ScheduleFile>().size());
/*   EXPECT_EQ(1u, model.getConcreteModelObjects<ExternalFile>().size());
  ExternalFile externalfile = schedule.externalFile();
  EXPECT_EQ(1u, externalfile.scheduleFiles().size());
  EXPECT_EQ(openstudio::toString(p), externalfile.fileName());
  EXPECT_TRUE(externalfile.isColumnSeparatorDefaulted());
  EXPECT_FALSE(equivalent(expectedDestDir / externalfile.fileName(), externalfile.filePath()));
  EXPECT_TRUE(exists(externalfile.filePath()));
  EXPECT_EQ(p, externalfile.filePath()); */
  EXPECT_TRUE(schedule.isNumberofHoursofDataDefaulted());
  EXPECT_EQ(1, schedule.columnNumber());
  schedule.setColumnNumber(1);
  EXPECT_EQ(1, schedule.columnNumber());
  EXPECT_EQ(0, schedule.rowstoSkipatTop());
  schedule.setRowstoSkipatTop(1);
  EXPECT_EQ(1, schedule.rowstoSkipatTop());

  EXPECT_EQ("Comma", schedule.columnSeparator());
  EXPECT_TRUE(schedule.isColumnSeparatorDefaulted());
  EXPECT_TRUE(schedule.setColumnSeparator("Tab"));
  EXPECT_EQ("Tab", schedule.columnSeparator());

  ScheduleFile schedule2(model, openstudio::toString(p));
  EXPECT_EQ(2u, model.getConcreteModelObjects<ScheduleFile>().size());
/*   EXPECT_EQ(1u, model.getConcreteModelObjects<ExternalFile>().size());
  ExternalFile externalfile2 = schedule2.externalFile();
  EXPECT_EQ(2u, externalfile.scheduleFiles().size());
  EXPECT_EQ(externalfile.handle(), externalfile2.handle()); */
  EXPECT_TRUE(schedule2.isNumberofHoursofDataDefaulted());
  EXPECT_EQ(1, schedule2.columnNumber());
  schedule2.setColumnNumber(2);
  EXPECT_EQ(2, schedule2.columnNumber());
  EXPECT_EQ(0, schedule2.rowstoSkipatTop());
  schedule2.setRowstoSkipatTop(1);
  EXPECT_EQ(1, schedule2.rowstoSkipatTop());

  openstudio::path filePath = schedule2.getImpl<epmodel::detail::ScheduleFile_Impl>()->fileName();
  ASSERT_TRUE(exists(filePath));
  EXPECT_EQ("schedulefile.csv", filePath.filename());

  schedule2.remove();
  EXPECT_EQ(1u, model.getConcreteModelObjects<ScheduleFile>().size());
}

TEST_F(EPModelFixture, ScheduleFile_ExtraSettersGetters) {
  Model model;

  path p = toPath("resources/model/schedulefile.csv"); // relative path
  EXPECT_TRUE(exists(p));

  bool translateFileWithRelativePath = false;
  ScheduleFile schedule(model, openstudio::toString(p), 1, 0, translateFileWithRelativePath);

  boost::optional<CSVFile> csvFile = schedule.csvFile();
  ASSERT_TRUE(csvFile);
  EXPECT_EQ(3u, csvFile->numColumns());
  EXPECT_EQ(8761u, csvFile->numRows());
  EXPECT_FALSE(schedule.translateFileWithRelativePath());
  EXPECT_FALSE(schedule.isTranslateFileWithRelativePathDefaulted());
  EXPECT_FALSE(schedule.setTranslateFileWithRelativePath(true));
  schedule.resetTranslateFileWithRelativePath();
  openstudio::path filePath = schedule.getImpl<epmodel::detail::ScheduleFile_Impl>()->fileName();
  ASSERT_TRUE(exists(filePath));
  EXPECT_NE(p, filePath);
  EXPECT_NE(p, schedule.translatedFilePath());

  translateFileWithRelativePath = true;
  ScheduleFile schedule2(model, openstudio::toString(p), 1, 0, translateFileWithRelativePath);

  boost::optional<CSVFile> csvFile2 = schedule2.csvFile();
  ASSERT_TRUE(csvFile2);
  EXPECT_EQ(3u, csvFile2->numColumns());
  EXPECT_EQ(8761u, csvFile2->numRows());
  EXPECT_FALSE(schedule2.translateFileWithRelativePath());
  EXPECT_FALSE(schedule2.isTranslateFileWithRelativePathDefaulted());
  EXPECT_FALSE(schedule2.setTranslateFileWithRelativePath(true));
  schedule2.resetTranslateFileWithRelativePath();
  openstudio::path filePath2 = schedule2.getImpl<epmodel::detail::ScheduleFile_Impl>()->fileName();
  ASSERT_TRUE(exists(filePath2));
  EXPECT_EQ(p, filePath2);
  EXPECT_EQ(p, schedule2.translatedFilePath());
}

TEST_F(EPModelFixture, ScheduleFile_CheckCannotFindFile) {
  Model model;

  StringStreamLogSink sink;
  sink.setLogLevel(Warn);

  path p = resourcesPath() / toPath("model/schedulefile2.csv");
  EXPECT_FALSE(exists(p));
  EXPECT_THROW(ScheduleFile(model, openstudio::toString(p)), openstudio::Exception);
  EXPECT_EQ(1, sink.logMessages().size());
  EXPECT_EQ("openstudio.epmodel.ScheduleFile", sink.logMessages().front().logChannel());
  EXPECT_TRUE(sink.logMessages().front().logMessage().find("Cannot find file") != std::string::npos);
  EXPECT_TRUE(sink.logMessages().front().logMessage().find("resources/model/schedulefile2.csv\" for Object of type 'Schedule:File' and named 'Schedule File 1'") != std::string::npos);

  path p2 = resourcesPath() / toPath("model/schedulefile.csv");
  EXPECT_TRUE(exists(p2));
  ScheduleFile schedule(model, openstudio::toString(p2));
  EXPECT_TRUE(schedule.getImpl<epmodel::detail::ScheduleFile_Impl>()->setFileName(toString(p)));

  StringStreamLogSink sink2;
  sink2.setLogLevel(Warn);

  EXPECT_EQ(p, schedule.translatedFilePath());
  EXPECT_EQ(1, sink2.logMessages().size());
  EXPECT_EQ("openstudio.epmodel.ScheduleFile", sink2.logMessages().front().logChannel());
  EXPECT_TRUE(sink2.logMessages().front().logMessage().find("Cannot find file") != std::string::npos);
  EXPECT_TRUE(sink2.logMessages().front().logMessage().find("resources/model/schedulefile2.csv\"") != std::string::npos);
}

TEST_F(EPModelFixture, ScheduleFile_fromTimeSeries_intervalLengthYes) {
  Model model;

  // hourly
  Date startDate(MonthOfYear::Jan, 1);
  Time intervalLength(0, 0, 60);
  Vector values(8760);
  for (unsigned i = 0; i < values.size(); ++i) {
    values[i] = i % 24;
  }

  TimeSeries timeSeries(startDate, intervalLength, values, "");

  boost::optional<ScheduleFile> schedule = ScheduleFile::fromTimeSeries(timeSeries, model);
  ASSERT_TRUE(schedule);
  openstudio::path filePath = schedule->getImpl<epmodel::detail::ScheduleFile_Impl>()->fileName();
  ASSERT_TRUE(exists(filePath));
  EXPECT_EQ("Schedule File 1.csv", filePath.filename());
  EXPECT_EQ(2, schedule->columnNumber());
  EXPECT_EQ(0, schedule->rowstoSkipatTop());
  ASSERT_TRUE(schedule->numberofHoursofData());
  EXPECT_EQ(8760, schedule->numberofHoursofData().get());
  EXPECT_EQ("Comma", schedule->columnSeparator());
  EXPECT_FALSE(schedule->interpolatetoTimestep());
  EXPECT_EQ(60, schedule->minutesperItem());
  EXPECT_TRUE(schedule->adjustScheduleforDaylightSavings());

  // 15-minutely
  Time intervalLength2(0, 0, 15);
  Vector values2(4 * 8760);
  for (unsigned i = 0; i < values2.size(); ++i) {
    values2[i] = i % 24;
  }

  TimeSeries timeSeries2(startDate, intervalLength2, values2, "");

  boost::optional<ScheduleFile> schedule2 = ScheduleFile::fromTimeSeries(timeSeries2, model);
  ASSERT_TRUE(schedule2);
  openstudio::path filePath2 = schedule2->getImpl<epmodel::detail::ScheduleFile_Impl>()->fileName();
  ASSERT_TRUE(exists(filePath2));
  EXPECT_EQ("Schedule File 2.csv", filePath2.filename());
  EXPECT_EQ(2, schedule2->columnNumber());
  EXPECT_EQ(0, schedule2->rowstoSkipatTop());
  ASSERT_TRUE(schedule2->numberofHoursofData());
  EXPECT_EQ(8760, schedule2->numberofHoursofData().get());
  EXPECT_EQ("Comma", schedule2->columnSeparator());
  EXPECT_FALSE(schedule2->interpolatetoTimestep());
  ASSERT_TRUE(schedule2->minutesperItem());
  EXPECT_EQ(15, schedule2->minutesperItem());
  EXPECT_TRUE(schedule2->adjustScheduleforDaylightSavings());
}

TEST_F(EPModelFixture, ScheduleFile_fromTimeSeries_intervalLengthNo) {
  Model model;

  StringStreamLogSink sink;
  sink.setLogLevel(Warn);

  Date startDate(MonthOfYear::Jan, 1);
  Time intervalLength(0, 0, 60);
  std::vector<DateTime> dateTimes;
  Vector values(8760);
  for (unsigned i = 0; i < values.size(); ++i) {
    dateTimes.push_back(DateTime(startDate, intervalLength * (i + 1)));
    values[i] = i % 24;
  }

  TimeSeries timeSeries(dateTimes, values, "");

  boost::optional<ScheduleFile> schedule = ScheduleFile::fromTimeSeries(timeSeries, model);
  ASSERT_FALSE(schedule);
  EXPECT_EQ(1, sink.logMessages().size());
  EXPECT_EQ("openstudio.epmodel.ScheduleFile", sink.logMessages().front().logChannel());
  EXPECT_EQ("Timeseries does not have an interval length defined, but ScheduleVariableInterval is deprecated", sink.logMessages().front().logMessage());
}

TEST_F(EPModelFixture, ScheduleFile_timeSeries) {
  Model model;

  StringStreamLogSink sink;
  sink.setLogLevel(Warn);

  ScheduleFile schedule(model);
  EXPECT_EQ(0, sink.logMessages().size());

  EXPECT_EQ("", schedule.fileName());
  EXPECT_EQ(0, sink.logMessages().size());
  boost::optional<CSVFile> csvFile = schedule.csvFile();
  EXPECT_FALSE(csvFile);
  EXPECT_EQ(1, sink.logMessages().size());
  EXPECT_EQ("openstudio.CSVFile", sink.logMessages()[0].logChannel());
  EXPECT_EQ("Path '' is not a CSVFile file", sink.logMessages()[0].logMessage());
  EXPECT_THROW(schedule.timeSeries(), openstudio::Exception);
  EXPECT_EQ(3, sink.logMessages().size());
  EXPECT_EQ("openstudio.CSVFile", sink.logMessages()[1].logChannel());
  EXPECT_EQ("Path '' is not a CSVFile file", sink.logMessages()[1].logMessage());
  EXPECT_EQ("openstudio.epmodel.ScheduleFile", sink.logMessages()[2].logChannel());
  EXPECT_EQ("Did not set File Name for Object of type 'Schedule:File' and named 'Schedule File 1'", sink.logMessages()[2].logMessage());

  path p = resourcesPath() / toPath("model/schedulefile.csv");
  EXPECT_TRUE(exists(p));

  int columnNumber = 1;
  const int rowsToSkip = 1;
  ScheduleFile schedule2(model, openstudio::toString(p), columnNumber, rowsToSkip);
  openstudio::TimeSeries timeSeries;
  boost::optional<openstudio::Time> intervalTime;
  double intervalLengthDouble;
  DateTimeVector dateTimes;
  DateTime firstReportDateTime;
  DateTime firstDateTime;
  DateTime secondDateTime;
  DateTime lastDateTime;

  timeSeries = schedule2.timeSeries();
  intervalTime = timeSeries.intervalLength();
  ASSERT_TRUE(intervalTime);
  intervalLengthDouble = intervalTime->totalMinutes();
  EXPECT_EQ(intervalLengthDouble, schedule2.minutesperItem());
  dateTimes = timeSeries.dateTimes();
  EXPECT_EQ(8760, dateTimes.size());
  EXPECT_EQ(8760, timeSeries.values().size());
  firstReportDateTime = DateTime(Date(MonthOfYear::Jan, 1), openstudio::Time(0, 0, schedule2.minutesperItem()));
  EXPECT_EQ(firstReportDateTime, timeSeries.firstReportDateTime());
  firstDateTime = DateTime(Date(MonthOfYear::Jan, 1), openstudio::Time(0, 0, schedule2.minutesperItem()));
  EXPECT_EQ(firstDateTime, dateTimes[0]);
  secondDateTime = firstDateTime + openstudio::Time(0, 0, schedule2.minutesperItem());
  EXPECT_EQ(secondDateTime, dateTimes[1]);
  lastDateTime = DateTime(Date(MonthOfYear::Dec, 31), openstudio::Time(0, 24));
  EXPECT_EQ(lastDateTime, dateTimes.back());
  EXPECT_EQ(1, timeSeries.values(0));
  EXPECT_EQ(8760, timeSeries.values(8759));

  columnNumber = 2;
  schedule2.setColumnNumber(columnNumber);
  timeSeries = schedule2.timeSeries();
  intervalTime = timeSeries.intervalLength();
  ASSERT_TRUE(intervalTime);
  intervalLengthDouble = intervalTime->totalMinutes();
  EXPECT_EQ(intervalLengthDouble, schedule2.minutesperItem());
  dateTimes = timeSeries.dateTimes();
  EXPECT_EQ(8760, dateTimes.size());
  EXPECT_EQ(8760, timeSeries.values().size());
  firstReportDateTime = DateTime(Date(MonthOfYear::Jan, 1), openstudio::Time(0, 0, schedule2.minutesperItem()));
  EXPECT_EQ(firstReportDateTime, timeSeries.firstReportDateTime());
  firstDateTime = DateTime(Date(MonthOfYear::Jan, 1), openstudio::Time(0, 0, schedule2.minutesperItem()));
  EXPECT_EQ(firstDateTime, dateTimes[0]);
  secondDateTime = firstDateTime + openstudio::Time(0, 0, schedule2.minutesperItem());
  EXPECT_EQ(secondDateTime, dateTimes[1]);
  lastDateTime = DateTime(Date(MonthOfYear::Dec, 31), openstudio::Time(0, 24));
  EXPECT_EQ(lastDateTime, dateTimes.back());
  EXPECT_EQ(8759, timeSeries.values(0));
  EXPECT_EQ(0, timeSeries.values(8759));

  StringStreamLogSink sink2;
  sink2.setLogLevel(Warn);

  columnNumber = 3;
  schedule2.setColumnNumber(columnNumber);
  schedule2.setMinutesperItem(15); // this trips the error checking
  timeSeries = schedule2.timeSeries();
  intervalTime = timeSeries.intervalLength();
  ASSERT_TRUE(intervalTime);
  intervalLengthDouble = intervalTime->totalMinutes();
  EXPECT_EQ(intervalLengthDouble, schedule2.minutesperItem());
  dateTimes = timeSeries.dateTimes();
  EXPECT_EQ(8760, dateTimes.size());
  EXPECT_EQ(8760, timeSeries.values().size());
  firstReportDateTime = DateTime(Date(MonthOfYear::Jan, 1), openstudio::Time(0, 0, schedule2.minutesperItem()));
  EXPECT_EQ(firstReportDateTime, timeSeries.firstReportDateTime());
  firstDateTime = DateTime(Date(MonthOfYear::Jan, 1), openstudio::Time(0, 0, schedule2.minutesperItem()));
  EXPECT_EQ(firstDateTime, dateTimes[0]);
  secondDateTime = firstDateTime + openstudio::Time(0, 0, schedule2.minutesperItem());
  EXPECT_EQ(secondDateTime, dateTimes[1]);
  lastDateTime = DateTime(Date(MonthOfYear::Apr, 2), openstudio::Time(0, 6));
  EXPECT_EQ(lastDateTime, dateTimes.back());
  EXPECT_EQ(0.207618, timeSeries.values(0));
  EXPECT_EQ(0.62146, timeSeries.values(8759));

  EXPECT_EQ(1, sink2.logMessages().size());
  EXPECT_EQ("openstudio.epmodel.ScheduleFile", sink2.logMessages().front().logChannel());
  EXPECT_TRUE(sink2.logMessages().front().logMessage().find("With 15 minutes per item, last date time is 2009-Apr-02 06:00:00") != std::string::npos);
  EXPECT_TRUE(sink2.logMessages().front().logMessage().find("resources/model/schedulefile.csv referenced by Object of type 'Schedule:File' and named 'Schedule File 2'") != std::string::npos);

  // TODO: try setting a leap year
}
