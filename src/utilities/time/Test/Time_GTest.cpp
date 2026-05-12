/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "../Time.hpp"

#include <string>

using namespace std;
using namespace boost;
using namespace openstudio;

int numberOfSeconds(int days, int hours, int minutes, int seconds) {
  return 24 * 60 * 60 * days + 60 * 60 * hours + 60 * minutes + seconds;
}

double numberOfDays(int days, int hours, int minutes, int seconds) {
  return days + 1.0 / (24.0) * hours + 1.0 / (24.0 * 60.0) * minutes + 1.0 / (24.0 * 60.0 * 60.0) * seconds;
}

TEST(Time, FracDaysConstructor) {
  Time testTime(0.0);
  EXPECT_EQ(testTime.totalSeconds(), 0);

  testTime = Time(0.5);
  EXPECT_EQ(testTime.totalSeconds(), 60 * 60 * 12);

  testTime = Time(1.0);
  EXPECT_EQ(testTime.totalSeconds(), 60 * 60 * 24);
}

TEST(Time, MixedConstructor) {
  EXPECT_EQ(Time(0, 1, 0, 0), Time(0, 0, 60, 0));
  EXPECT_EQ(Time(0, -1, 0, 0), Time(0, 0, -60, 0));
  EXPECT_EQ(Time(0, 1, 30, 0), Time(0, 0, 90, 0));
  EXPECT_EQ(Time(0, -1, -30, 0), Time(0, 0, -90, 0));
  EXPECT_EQ(Time(0, 1, 0, 0), Time(0, 1, 1, -60));
  EXPECT_EQ(Time(0, 1, 0, 0), Time(0, 1, -1, 60));
  EXPECT_EQ(Time(0, 0, 59, 0), Time(0, 1, -1, 0));
  EXPECT_EQ(Time(0, 1, 30, 0), Time(1.5 / 24.0));
  EXPECT_EQ(Time(0, -1, -30, 0), Time(-1.5 / 24.0));
}

TEST(Time, StringConstructor) {
  Time time(0, 0, 0, 0);

  std::stringstream ss;
  ss << time;
  Time time2(ss.str());

  EXPECT_TRUE(time == time2) << ss.str() << ", " << time << " != " << time2;

  time = Time(0, 4, 0, 0);

  ss.str("");
  ss << time;
  time2 = Time(ss.str());

  EXPECT_TRUE(time == time2) << ss.str() << ", " << time << " != " << time2;

  time = Time(4, 4, 0, 0);

  ss.str("");
  ss << time;
  time2 = Time(ss.str());

  EXPECT_TRUE(time == time2) << ss.str() << ", " << time << " != " << time2;
}

TEST(Time, TMConstructor) {
  time_t t = time(nullptr);
  tm* lt = localtime(&t);
  Time zt(*lt);

  EXPECT_EQ(zt.hours(), lt->tm_hour);
  EXPECT_EQ(zt.minutes(), lt->tm_min);
  EXPECT_EQ(zt.seconds(), lt->tm_sec);
}

TEST(Time, DaysHoursMinutesSecondsConstructor) {
  Time testTime(0, 0, 0, 0);
  EXPECT_DOUBLE_EQ(testTime.totalDays(), 0.0 / (24 * 60 * 60));
  EXPECT_DOUBLE_EQ(testTime.totalHours(), 0.0 / (60 * 60));
  EXPECT_DOUBLE_EQ(testTime.totalMinutes(), 0.0 / 60);
  EXPECT_EQ(testTime.totalSeconds(), 0);
  EXPECT_EQ(testTime.days(), 0);
  EXPECT_EQ(testTime.hours(), 0);
  EXPECT_EQ(testTime.minutes(), 0);
  EXPECT_EQ(testTime.seconds(), 0);

  testTime = Time(0, 0, 0, 1);
  EXPECT_DOUBLE_EQ(testTime.totalDays(), 1.0 / (24 * 60 * 60));
  EXPECT_DOUBLE_EQ(testTime.totalHours(), 1.0 / (60 * 60));
  EXPECT_DOUBLE_EQ(testTime.totalMinutes(), 1.0 / 60);
  EXPECT_EQ(testTime.totalSeconds(), 1);
  EXPECT_EQ(testTime.days(), 0);
  EXPECT_EQ(testTime.hours(), 0);
  EXPECT_EQ(testTime.minutes(), 0);
  EXPECT_EQ(testTime.seconds(), 1);

  testTime = Time(0, 0, 1, 0);
  EXPECT_DOUBLE_EQ(testTime.totalDays(), 1.0 / (24 * 60));
  EXPECT_DOUBLE_EQ(testTime.totalHours(), 1.0 / (60));
  EXPECT_DOUBLE_EQ(testTime.totalMinutes(), 1.0);
  EXPECT_EQ(testTime.totalSeconds(), 60);
  EXPECT_EQ(testTime.days(), 0);
  EXPECT_EQ(testTime.hours(), 0);
  EXPECT_EQ(testTime.minutes(), 1);
  EXPECT_EQ(testTime.seconds(), 0);

  testTime = Time(0, 1, 0, 0);
  EXPECT_DOUBLE_EQ(testTime.totalDays(), 1.0 / 24);
  EXPECT_DOUBLE_EQ(testTime.totalHours(), 1.0);
  EXPECT_DOUBLE_EQ(testTime.totalMinutes(), 60.0);
  EXPECT_EQ(testTime.totalSeconds(), 60 * 60);
  EXPECT_EQ(testTime.days(), 0);
  EXPECT_EQ(testTime.hours(), 1);
  EXPECT_EQ(testTime.minutes(), 0);
  EXPECT_EQ(testTime.seconds(), 0);

  testTime = Time(1, 0, 0, 0);
  EXPECT_DOUBLE_EQ(testTime.totalDays(), 1.0);
  EXPECT_DOUBLE_EQ(testTime.totalHours(), 24.0);
  EXPECT_DOUBLE_EQ(testTime.totalMinutes(), 24.0 * 60.0);
  EXPECT_EQ(testTime.totalSeconds(), 24.0 * 60 * 60);
  EXPECT_EQ(testTime.days(), 1);
  EXPECT_EQ(testTime.hours(), 0);
  EXPECT_EQ(testTime.minutes(), 0);
  EXPECT_EQ(testTime.seconds(), 0);

  testTime = Time(1, 1, 1, 1);
  EXPECT_DOUBLE_EQ(testTime.totalDays(), 1.0 + 1.0 / 24 + 1.0 / (24 * 60) + 1.0 / (24 * 60 * 60));
  EXPECT_DOUBLE_EQ(testTime.totalHours(), 24 + 1.0 + 1.0 / 60 + 1.0 / (60 * 60));
  EXPECT_DOUBLE_EQ(testTime.totalMinutes(), 24 * 60 + 60 + 1 + 1.0 / 60);
  EXPECT_EQ(testTime.totalSeconds(), 24 * 60 * 60 + 60 * 60 + 60 + 1);
  EXPECT_EQ(testTime.days(), 1);
  EXPECT_EQ(testTime.hours(), 1);
  EXPECT_EQ(testTime.minutes(), 1);
  EXPECT_EQ(testTime.seconds(), 1);
}

TEST(Time, FromUntilString_ValidFormats) {
  // All prefix variants accepted by EnergyPlus: "Until:", "Until ", "until:", "until ", no prefix.
  // Two-digit and single-digit hours.
  struct TC
  {
    const char* input;
    int h;
    int m;
  };
  constexpr std::array cases{
    TC{"Until: 12:00", 12, 0}, TC{"until: 12:01", 12, 1}, TC{"Until 12:02", 12, 2}, TC{"until 12:03", 12, 3}, TC{"12:04", 12, 4},
    TC{"Until:12:05", 12, 5},  TC{"until:12:06", 12, 6},  TC{"Until12:07", 12, 7},  TC{"until12:08", 12, 8},  TC{"Until: 1:00", 1, 0},
    TC{"until: 1:01", 1, 1},   TC{"Until 1:02", 1, 2},    TC{"until 1:03", 1, 3},   TC{"1:04", 1, 4},         TC{"Until:1:05", 1, 5},
    TC{"until:1:06", 1, 6},    TC{"Until1:07", 1, 7},     TC{"until1:08", 1, 8},
  };

  for (const auto& [input, h, m] : cases) {
    const Time t = Time::fromUntilString(input);
    EXPECT_EQ(t.days(), 0) << "Input: " << input;
    EXPECT_EQ(t.hours(), h) << "Input: " << input;
    EXPECT_EQ(t.minutes(), m) << "Input: " << input;
  }
}

TEST(Time, FromUntilString_SpecialTimes) {
  // 24:00 — canonical end-of-day for E+ schedules
  EXPECT_EQ(Time::fromUntilString("Until: 24:00").totalSeconds(), 24 * 60 * 60);

  // 00:00 — valid Time (zero), though invalid as a schedule "Until" value in E+
  EXPECT_EQ(Time::fromUntilString("Until: 00:00").totalSeconds(), 0);

  // Single-digit hour and minute without zero-padding
  const Time t = Time::fromUntilString("Until: 6:05");
  EXPECT_EQ(t.hours(), 6);
  EXPECT_EQ(t.minutes(), 5);
}

TEST(Time, FromUntilString_WeirdCases) {
  // "HH:MM:SS" — the parser finds the first colon, so seconds are silently ignored
  // and the string is parsed as HH:MM.
  {
    const Time t = Time::fromUntilString("Until: 23:56:00");
    EXPECT_EQ(t.hours(), 23);
    EXPECT_EQ(t.minutes(), 56);
  }

  // "24:01" — over 24 h, produces a valid Time but is invalid for E+ schedule use
  {
    const Time t = Time::fromUntilString("Until: 24:01");
    EXPECT_EQ(t.totalSeconds(), (24 * 60 + 1) * 60);
  }
}

TEST(Time, FromUntilString_Invalid) {
  EXPECT_THROW(Time::fromUntilString(""), std::exception);
  EXPECT_THROW(Time::fromUntilString("Until:"), std::exception);         // nothing after prefix
  EXPECT_THROW(Time::fromUntilString("garbage"), std::exception);        // no colon at all
  EXPECT_THROW(Time::fromUntilString("abc:def"), std::exception);        // non-numeric HH/MM
  EXPECT_THROW(Time::fromUntilString("Until: abc:00"), std::exception);  // non-numeric HH
}

TEST(Time, ToUntilString) {
  EXPECT_EQ(Time(0, 12, 0).toUntilString(), "Until: 12:00");
  EXPECT_EQ(Time(0, 1, 5).toUntilString(), "Until: 01:05");  // zero-padded
  EXPECT_EQ(Time(0, 0, 0).toUntilString(), "Until: 00:00");
  EXPECT_EQ(Time(0, 24, 0).toUntilString(), "Until: 24:00");  // end-of-day
  EXPECT_EQ(Time(0, 6, 30).toUntilString(), "Until: 06:30");
}

TEST(Time, UntilString_RoundTrip) {
  for (const Time& t : {Time(0, 1, 0), Time(0, 6, 15), Time(0, 12, 30), Time(0, 23, 59), Time(0, 24, 0)}) {
    const std::string s = t.toUntilString();
    EXPECT_EQ(Time::fromUntilString(s), t) << "Round-trip failed for: " << s;
  }
}
