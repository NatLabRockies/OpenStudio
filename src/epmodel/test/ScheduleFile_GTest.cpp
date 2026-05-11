/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ScheduleInterval/ScheduleFile.hpp"

#include "../../utilities/data/TimeSeries.hpp"

using namespace openstudio;
using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ScheduleFile_DefaultConstructor) {
  Model model;
  ScheduleFile schedule(model);
  EXPECT_EQ(ScheduleFile::iddObjectType(), schedule.iddObject().type());

  EXPECT_EQ(1, schedule.columnNumber());
  EXPECT_EQ(0, schedule.rowstoSkipatTop());
}

/* TEST_F(EPModelFixture, ScheduleFileAltCtor) {
  Model model;
  // EXPECT_EQ(0u, model.getConcreteModelObjects<ExternalFile>().size());
  EXPECT_EQ(0u, model.getConcreteModelObjects<ScheduleFile>().size());

  path p = resourcesPath() / toPath("model/schedulefile.csv");
  EXPECT_TRUE(exists(p));

  path expectedDestDir;
  std::vector<path> absoluteFilePaths = model.workflowJSON().absoluteFilePaths();
  if (absoluteFilePaths.empty()) {
    expectedDestDir = model.workflowJSON().absoluteRootDir();
  } else {
    expectedDestDir = absoluteFilePaths[0];
  }

  if (exists(expectedDestDir)) {
    removeDirectory(expectedDestDir);
  }
  ASSERT_FALSE(exists(expectedDestDir));

  ScheduleFile schedule(model, openstudio::toString(p));
  EXPECT_EQ(1u, model.getConcreteModelObjects<ScheduleFile>().size());
  // EXPECT_EQ(1u, model.getConcreteModelObjects<ExternalFile>().size());
  ExternalFile externalfile = schedule.externalFile();
  EXPECT_EQ(1u, externalfile.scheduleFiles().size());
  EXPECT_EQ(openstudio::toString(p), externalfile.fileName());
  //EXPECT_TRUE(externalfile.isColumnSeparatorDefaulted());
  EXPECT_FALSE(equivalent(expectedDestDir / externalfile.fileName(), externalfile.filePath()));
  EXPECT_TRUE(exists(externalfile.filePath()));
  EXPECT_EQ(p, externalfile.filePath());
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
  EXPECT_EQ(1u, model.getConcreteModelObjects<ExternalFile>().size());
  ExternalFile externalfile2 = schedule2.externalFile();
  EXPECT_EQ(2u, externalfile.scheduleFiles().size());
  EXPECT_EQ(externalfile.handle(), externalfile2.handle());
  EXPECT_TRUE(schedule2.isNumberofHoursofDataDefaulted());
  EXPECT_EQ(1, schedule2.columnNumber());
  schedule2.setColumnNumber(2);
  EXPECT_EQ(2, schedule2.columnNumber());
  EXPECT_EQ(0, schedule2.rowstoSkipatTop());
  schedule2.setRowstoSkipatTop(1);
  EXPECT_EQ(1, schedule2.rowstoSkipatTop());
} */

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

  EXPECT_TRUE(schedule.minutesperItem());
  EXPECT_EQ("60", schedule.minutesperItem().get());
  EXPECT_TRUE(schedule.setMinutesperItem(15));
  ASSERT_TRUE(schedule.minutesperItem());
  EXPECT_EQ("15", schedule.minutesperItem().get());
  EXPECT_TRUE(schedule.setMinutesperItem("30"));
  ASSERT_TRUE(schedule.minutesperItem());
  EXPECT_EQ("30", schedule.minutesperItem().get());
  EXPECT_FALSE(schedule.setMinutesperItem("BAD"));
  schedule.resetMinutesperItem();
  EXPECT_TRUE(schedule.isMinutesperItemDefaulted());
  ASSERT_TRUE(schedule.minutesperItem());
  EXPECT_EQ("60", schedule.minutesperItem().get());

  EXPECT_TRUE(schedule.adjustScheduleforDaylightSavings());
  EXPECT_TRUE(schedule.setAdjustScheduleforDaylightSavings(false));
  EXPECT_FALSE(schedule.adjustScheduleforDaylightSavings());
  schedule.resetAdjustScheduleforDaylightSavings();
  EXPECT_TRUE(schedule.adjustScheduleforDaylightSavings());
}

TEST_F(EPModelFixture, ScheduleFile_fromTimeSeries_intervalLengthYes) {
  Model model;

  Date startDate(MonthOfYear::Jan, 1);
  Time intervalLength(0, 0, 60);
  Vector values(8760);
  for (unsigned i = 0; i < values.size(); ++i) {
    values[i] = i % 24;
  }

  TimeSeries timeSeries(startDate, intervalLength, values, "");

  boost::optional<ScheduleFile> schedule = ScheduleFile::fromTimeSeries(timeSeries, model);
  ASSERT_TRUE(schedule);
  //EXPECT_EQ("", schedule->fileName());
  EXPECT_EQ(1, schedule->columnNumber());
  EXPECT_EQ(0, schedule->rowstoSkipatTop());
  ASSERT_TRUE(schedule->numberofHoursofData());
  EXPECT_EQ(8760, schedule->numberofHoursofData().get());
  EXPECT_EQ("Comma", schedule->columnSeparator());
  EXPECT_TRUE(schedule->interpolatetoTimestep());
  ASSERT_TRUE(schedule->minutesperItem());
  EXPECT_EQ("60", schedule->minutesperItem().get());
  EXPECT_TRUE(schedule->adjustScheduleforDaylightSavings());
}

TEST_F(EPModelFixture, ScheduleFile_fromTimeSeries_intervalLengthNo) {
  Model model;

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
}