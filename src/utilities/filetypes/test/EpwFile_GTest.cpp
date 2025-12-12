/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>
#include "../EpwFile.hpp"
#include "../../time/Time.hpp"
#include "../../time/Date.hpp"
#include "../../core/Checksum.hpp"

#include <resources.hxx>

#include <array>

using namespace openstudio;

TEST(Filetypes, EpwFile) {
  // LOCATION,Climate Zone 1,CA,USA,CTZRV2,725945,40.80,-124.20,-8.0,13.0
  // DESIGN CONDITIONS,1,Climate Design Data 2009 ASHRAE Handbook,,Heating,12,-0.6,0.6,-4.1,2.7,5.3,-2.2,3.2,3.8,11.1,12.3,9.7,11.3,2,90,Cooling,8,6.5,21.6,15.2,19.9,15.1,18.7,14.6,16.8,19.5,16.1,18.6,15.5,17.6,4.3,320,15.9,11.4,17.5,15.1,10.8,16.8,14.4,10.3,16.2,47.3,19.8,45,18.5,43.3,17.6,1804,Extremes,9,8.2,7.4,20.8,-2.5,28.3,1.7,2.2,-3.7,29.8,-4.6,31.1,-5.6,32.3,-6.8,33.9
  // TYPICAL/EXTREME PERIODS,6,Summer - Week Nearest Max Temperature For Period,Extreme,7/ 8,7/14,Summer - Week Nearest Average Temperature For Period,Typical,8/12,8/18,Winter - Week Nearest Min Temperature For Period,Extreme,1/15,1/21,Winter - Week Nearest Average Temperature For Period,Typical,1/22,1/28,Autumn - Week Nearest Average Temperature For Period,Typical,11/26,12/ 2,Spring - Week Nearest Average Temperature For Period,Typical,5/27,6/ 2
  // GROUND TEMPERATURES,3,.5,,,,9.66,10.10,10.96,11.78,13.32,14.13,14.35,13.94,12.99,11.81,10.64,9.87,2,,,,10.27,10.38,10.87,11.41,12.60,13.35,13.73,13.65,13.10,12.29,11.37,10.64,4,,,,10.90,10.82,11.04,11.35,12.13,12.72,13.10,13.19,12.95,12.47,11.85,11.28
  // HOLIDAYS/DAYLIGHT SAVINGS,No,0,0,0
  // COMMENTS 1,California Climate Zone 01 Version 2;
  // COMMENTS 2, -- Ground temps produced with a standard soil diffusivity of 2.3225760E-03 {m**2/day}
  // DATA PERIODS,1,1,Data,Sunday, 1/ 1,12/31
  path p = resourcesPath() / toPath("utilities/Filetypes/USA_CO_Golden-NREL.724666_TMY3.epw");
  EpwFile epwFile(p);
  EXPECT_EQ(p, epwFile.path());
  EXPECT_EQ("BDF687C1", epwFile.checksum());
  EXPECT_EQ(openstudio::checksum(epwFile.path()), epwFile.checksum());
  EXPECT_EQ("Denver Centennial  Golden   Nr", epwFile.city());
  EXPECT_EQ("CO", epwFile.stateProvinceRegion());
  EXPECT_EQ("USA", epwFile.country());
  EXPECT_EQ("TMY3", epwFile.dataSource());
  EXPECT_EQ("724666", epwFile.wmoNumber());
  EXPECT_EQ(39.74, epwFile.latitude());
  EXPECT_EQ(-105.18, epwFile.longitude());
  EXPECT_EQ(-7, epwFile.timeZone());
  EXPECT_EQ(1829, epwFile.elevation());
  EXPECT_EQ(Time(0, 1, 0, 0), epwFile.timeStep());
  EXPECT_EQ(DayOfWeek(DayOfWeek::Sunday), epwFile.startDayOfWeek());
  EXPECT_EQ(Date(MonthOfYear::Jan, 1), epwFile.startDate());
  EXPECT_EQ(Date(MonthOfYear::Dec, 31), epwFile.endDate());
  EXPECT_FALSE(epwFile.isActual());
}

TEST(Filetypes, EpwFile_Data) {
  path p = resourcesPath() / toPath("utilities/Filetypes/USA_CO_Golden-NREL.724666_TMY3.epw");
  EpwFile epwFile(p);
  EXPECT_EQ(p, epwFile.path());
  EXPECT_EQ("BDF687C1", epwFile.checksum());
  EXPECT_EQ(openstudio::checksum(epwFile.path()), epwFile.checksum());
  EXPECT_EQ("Denver Centennial  Golden   Nr", epwFile.city());
  EXPECT_EQ("CO", epwFile.stateProvinceRegion());
  EXPECT_EQ("USA", epwFile.country());
  EXPECT_EQ("TMY3", epwFile.dataSource());
  EXPECT_EQ("724666", epwFile.wmoNumber());
  EXPECT_EQ(39.74, epwFile.latitude());
  EXPECT_EQ(-105.18, epwFile.longitude());
  EXPECT_EQ(-7, epwFile.timeZone());
  EXPECT_EQ(1829, epwFile.elevation());
  EXPECT_EQ(Time(0, 1, 0, 0), epwFile.timeStep());
  EXPECT_EQ(DayOfWeek(DayOfWeek::Sunday), epwFile.startDayOfWeek());
  EXPECT_EQ(Date(MonthOfYear::Jan, 1), epwFile.startDate());
  EXPECT_EQ(Date(MonthOfYear::Dec, 31), epwFile.endDate());
  // Up to here, everything should be the same as the first test. Now ask for the data
  std::vector<EpwDataPoint> data = epwFile.data();
  EXPECT_EQ(8760, data.size());
  // The last data point should be for the last hour 12/31/1996, with a dry bulb temp of 4C and pressure 81100
  // Gets reported as "1997-Jan-01 00:00:00"
  openstudio::DateTime dateTime = data[8759].dateTime();
  EXPECT_EQ(1, dateTime.date().monthOfYear().value());
  EXPECT_EQ(1, dateTime.date().dayOfMonth());
  EXPECT_EQ(1997, dateTime.date().year());
  EXPECT_EQ(0, dateTime.time().hours());
  EXPECT_EQ(0, dateTime.time().minutes());
  EXPECT_EQ(0, dateTime.time().seconds());
  EXPECT_EQ(4.0, data[8759].dryBulbTemperature().get());
  EXPECT_EQ(81100, data[8759].atmosphericStationPressure().get());
  // Try out the alternate access functions, dew point temperature should be -1C
  EXPECT_EQ(-1.0, data[8759].getFieldByName("Dew Point Temperature").get());
  EXPECT_EQ(-1.0, data[8759].getField(EpwDataField("Dew Point Temperature")).get());
  // The last data point should not have a liquid precipitation depth
  EXPECT_FALSE(data[8759].getFieldByName("Liquid Precipitation Depth"));
  // Get the data as strings
  std::vector<std::string> epwStrings = data[8759].toEpwStrings();
  ASSERT_EQ(35, epwStrings.size());
  std::vector<std::string> known = {"1996", "12",       "31",    "24",        "0",  "?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9*9",
                                    "4.0",  "-1.0",     "69",    "81100",     "0",  "0",
                                    "294",  "0.000000", "0",     "0",         "0",  "0",
                                    "0",    "0",        "130",   "6.200000",  "9",  "9",
                                    "48.3", "7500",     "9",     "999999999", "60", "0.0310",
                                    "0",    "88",       "0.210", "999",       "99"};
  for (unsigned i = 0; i < 35; i++) {
    EXPECT_EQ(known[i], epwStrings[i]);
  }
  // Get a time series
  boost::optional<openstudio::TimeSeries> series = epwFile.getTimeSeries("Wind Speed");
  ASSERT_TRUE(series);
  ASSERT_EQ(8760, series->values().size());
  DateTimeVector seriesTimes = series->dateTimes();
  ASSERT_EQ(8760, seriesTimes.size());
  // Check the times in the data and the time series
  DateTime current(Date(1, 1, 1999), Time(0, 1));  // Use 1999 to avoid leap years
  Time delta(0, 1);
  for (unsigned i = 0; i < 8760; i++) {
    // This is a lot more complicated that it probably should be to avoid the year being a problem
    DateTime datatime = data[i].dateTime();
    EXPECT_EQ(datatime.date().monthOfYear(), current.date().monthOfYear());
    EXPECT_EQ(datatime.date().dayOfMonth(), current.date().dayOfMonth());
    EXPECT_EQ(datatime.time().hours(), current.time().hours());
    EXPECT_EQ(datatime.time().minutes(), current.time().minutes());
    DateTime seriestime = seriesTimes[i];
    EXPECT_EQ(seriestime.date().monthOfYear(), current.date().monthOfYear());
    EXPECT_EQ(seriestime.date().dayOfMonth(), current.date().dayOfMonth());
    EXPECT_EQ(seriestime.time().hours(), current.time().hours());
    EXPECT_EQ(seriestime.time().minutes(), current.time().minutes());
    current += delta;
  }
  // We should redo the original tests because we have reparsed the entire file
  EXPECT_EQ(p, epwFile.path());
  EXPECT_EQ("BDF687C1", epwFile.checksum());
  EXPECT_EQ(openstudio::checksum(epwFile.path()), epwFile.checksum());
  EXPECT_EQ("Denver Centennial  Golden   Nr", epwFile.city());
  EXPECT_EQ("CO", epwFile.stateProvinceRegion());
  EXPECT_EQ("USA", epwFile.country());
  EXPECT_EQ("TMY3", epwFile.dataSource());
  EXPECT_EQ("724666", epwFile.wmoNumber());
  EXPECT_EQ(39.74, epwFile.latitude());
  EXPECT_EQ(-105.18, epwFile.longitude());
  EXPECT_EQ(-7, epwFile.timeZone());
  EXPECT_EQ(1829, epwFile.elevation());
  EXPECT_EQ(Time(0, 1, 0, 0), epwFile.timeStep());
  EXPECT_EQ(DayOfWeek(DayOfWeek::Sunday), epwFile.startDayOfWeek());
  EXPECT_EQ(Date(MonthOfYear::Jan, 1), epwFile.startDate());
  EXPECT_EQ(Date(MonthOfYear::Dec, 31), epwFile.endDate());
  EXPECT_FALSE(epwFile.isActual());
}

TEST(Filetypes, EpwFile_Design) {
  path p = resourcesPath() / toPath("utilities/Filetypes/USA_CO_Golden-NREL.724666_TMY3.epw");
  EpwFile epwFile(p);
  EXPECT_EQ(p, epwFile.path());
  EXPECT_EQ("BDF687C1", epwFile.checksum());
  EXPECT_EQ(openstudio::checksum(epwFile.path()), epwFile.checksum());
  EXPECT_EQ("Denver Centennial  Golden   Nr", epwFile.city());
  EXPECT_EQ("CO", epwFile.stateProvinceRegion());
  EXPECT_EQ("USA", epwFile.country());
  EXPECT_EQ("TMY3", epwFile.dataSource());
  EXPECT_EQ("724666", epwFile.wmoNumber());
  EXPECT_EQ(39.74, epwFile.latitude());
  EXPECT_EQ(-105.18, epwFile.longitude());
  EXPECT_EQ(-7, epwFile.timeZone());
  EXPECT_EQ(1829, epwFile.elevation());
  EXPECT_EQ(Time(0, 1, 0, 0), epwFile.timeStep());
  EXPECT_EQ(DayOfWeek(DayOfWeek::Sunday), epwFile.startDayOfWeek());
  EXPECT_EQ(Date(MonthOfYear::Jan, 1), epwFile.startDate());
  EXPECT_EQ(Date(MonthOfYear::Dec, 31), epwFile.endDate());
  // Up to here, everything should be the same as the first test. Now ask for the design conditions
  std::vector<EpwDesignCondition> designs = epwFile.designConditions();
  EXPECT_EQ(1, designs.size());
  EXPECT_EQ("Climate Design Data 2009 ASHRAE Handbook", designs[0].titleOfDesignCondition());
  EXPECT_EQ(12, designs[0].heatingColdestMonth().get());
  EXPECT_EQ(-18.8, designs[0].heatingDryBulb99pt6().get());
  EXPECT_EQ(-18.8, designs[0].getFieldByName("Heating Dry Bulb Temperature 99.6%").get());
  EXPECT_EQ(-18.8, designs[0].getField(EpwDesignField("Heating Dry Bulb Temperature 99.6%")).get());
  EXPECT_EQ("C", designs[0].getUnitsByName("Heating Dry Bulb Temperature 99.6%").get());
  EXPECT_EQ("C", designs[0].getUnits(EpwDesignField("Heating Dry Bulb Temperature 99.6%")));
  EXPECT_EQ(-15.5, designs[0].heatingDryBulb99().get());
  EXPECT_EQ(-21.6, designs[0].heatingHumidificationDewPoint99pt6().get());
  EXPECT_EQ(0.7, designs[0].heatingHumidificationHumidityRatio99pt6().get());
  EXPECT_EQ(-10.9, designs[0].heatingHumidificationMeanCoincidentDryBulb99pt6().get());
  EXPECT_EQ(-18.8, designs[0].heatingHumidificationDewPoint99().get());
  EXPECT_EQ(0.9, designs[0].heatingHumidificationHumidityRatio99().get());
  EXPECT_EQ(-7.5, designs[0].heatingHumidificationMeanCoincidentDryBulb99().get());
  EXPECT_EQ(12.2, designs[0].heatingColdestMonthWindSpeed0pt4().get());
  EXPECT_EQ(3.9, designs[0].heatingColdestMonthMeanCoincidentDryBulb0pt4().get());
  EXPECT_EQ(10.9, designs[0].heatingColdestMonthWindSpeed1().get());
  EXPECT_EQ(3.8, designs[0].heatingColdestMonthMeanCoincidentDryBulb1().get());
  EXPECT_EQ(3.0, designs[0].heatingMeanCoincidentWindSpeed99pt6().get());
  EXPECT_EQ(340, designs[0].heatingPrevailingCoincidentWindDirection99pt6().get());
  EXPECT_EQ(7, designs[0].coolingHottestMonth().get());
  EXPECT_EQ(15.2, designs[0].coolingDryBulbRange().get());
  EXPECT_EQ(33.0, designs[0].coolingDryBulb0pt4().get());
  EXPECT_EQ(15.7, designs[0].coolingMeanCoincidentWetBulb0pt4().get());
  EXPECT_EQ(32.0, designs[0].coolingDryBulb1().get());
  EXPECT_EQ(15.5, designs[0].coolingMeanCoincidentWetBulb1().get());
  EXPECT_EQ(30.2, designs[0].coolingDryBulb2().get());
  EXPECT_EQ(15.3, designs[0].coolingMeanCoincidentWetBulb2().get());
  EXPECT_EQ(18.4, designs[0].coolingEvaporationWetBulb0pt4().get());
  EXPECT_EQ(27.3, designs[0].coolingEvaporationMeanCoincidentDryBulb0pt4().get());
  EXPECT_EQ(17.5, designs[0].coolingEvaporationWetBulb1().get());
  EXPECT_EQ(26.4, designs[0].coolingEvaporationMeanCoincidentDryBulb1().get());
  EXPECT_EQ(16.8, designs[0].coolingEvaporationWetBulb2().get());
  EXPECT_EQ(25.6, designs[0].coolingEvaporationMeanCoincidentDryBulb2().get());
  EXPECT_EQ(4.9, designs[0].coolingMeanCoincidentWindSpeed0pt4().get());
  EXPECT_EQ(0, designs[0].coolingPrevailingCoincidentWindDirection0pt4().get());
  EXPECT_EQ(16.1, designs[0].coolingDehumidificationDewPoint0pt4().get());
  EXPECT_EQ(14.3, designs[0].coolingDehumidificationHumidityRatio0pt4().get());
  EXPECT_EQ(20.2, designs[0].coolingDehumidificationMeanCoincidentDryBulb0pt4().get());
  EXPECT_EQ(14.9, designs[0].coolingDehumidificationDewPoint1().get());
  EXPECT_EQ(13.2, designs[0].coolingDehumidificationHumidityRatio1().get());
  EXPECT_EQ(19.9, designs[0].coolingDehumidificationMeanCoincidentDryBulb1().get());
  EXPECT_EQ(13.9, designs[0].coolingDehumidificationDewPoint2().get());
  EXPECT_EQ(12.3, designs[0].coolingDehumidificationHumidityRatio2().get());
  EXPECT_EQ(19.6, designs[0].coolingDehumidificationMeanCoincidentDryBulb2().get());
  EXPECT_EQ(59.7, designs[0].coolingEnthalpy0pt4().get());
  EXPECT_EQ(27.3, designs[0].coolingEnthalpyMeanCoincidentDryBulb0pt4().get());
  EXPECT_EQ(56.6, designs[0].coolingEnthalpy1().get());
  EXPECT_EQ(26.6, designs[0].coolingEnthalpyMeanCoincidentDryBulb1().get());
  EXPECT_EQ(54.0, designs[0].coolingEnthalpy2().get());
  EXPECT_EQ(25.7, designs[0].coolingEnthalpyMeanCoincidentDryBulb2().get());
  EXPECT_EQ(760, designs[0].coolingHours8To4AndDryBulb12pt8To20pt6().get());
  EXPECT_EQ(11.1, designs[0].extremeWindSpeed1().get());
  EXPECT_EQ(9.5, designs[0].extremeWindSpeed2pt5().get());
  EXPECT_EQ(8.4, designs[0].extremeWindSpeed5().get());
  EXPECT_EQ(22.9, designs[0].extremeMaxWetBulb().get());
  EXPECT_EQ(-22.9, designs[0].extremeMeanMinDryBulb().get());
  EXPECT_EQ(36.1, designs[0].extremeMeanMaxDryBulb().get());
  EXPECT_EQ(3.8, designs[0].extremeStdDevMinDryBulb().get());
  EXPECT_EQ(1.2, designs[0].extremeStdDevMaxDryBulb().get());
  EXPECT_EQ(-25.7, designs[0].extremeN5YearsMinDryBulb().get());
  EXPECT_EQ(37.0, designs[0].extremeN5YearsMaxDryBulb().get());
  EXPECT_EQ(-27.9, designs[0].extremeN10YearsMinDryBulb().get());
  EXPECT_EQ(37.7, designs[0].extremeN10YearsMaxDryBulb().get());
  EXPECT_EQ(-30.1, designs[0].extremeN20YearsMinDryBulb().get());
  EXPECT_EQ(38.3, designs[0].extremeN20YearsMaxDryBulb().get());
  EXPECT_EQ(-32.8, designs[0].extremeN50YearsMinDryBulb().get());
  EXPECT_EQ(39.2, designs[0].extremeN50YearsMaxDryBulb().get());
}

TEST(Filetypes, EpwFile_Ground) {
  path p = resourcesPath() / toPath("utilities/Filetypes/USA_CO_Golden-NREL.724666_TMY3.epw");
  EpwFile epwFile(p);
  EXPECT_EQ(p, epwFile.path());
  EXPECT_EQ("BDF687C1", epwFile.checksum());
  EXPECT_EQ(openstudio::checksum(epwFile.path()), epwFile.checksum());
  EXPECT_EQ("Denver Centennial  Golden   Nr", epwFile.city());
  EXPECT_EQ("CO", epwFile.stateProvinceRegion());
  EXPECT_EQ("USA", epwFile.country());
  EXPECT_EQ("TMY3", epwFile.dataSource());
  EXPECT_EQ("724666", epwFile.wmoNumber());
  EXPECT_EQ(39.74, epwFile.latitude());
  EXPECT_EQ(-105.18, epwFile.longitude());
  EXPECT_EQ(-7, epwFile.timeZone());
  EXPECT_EQ(1829, epwFile.elevation());
  EXPECT_EQ(Time(0, 1, 0, 0), epwFile.timeStep());
  EXPECT_EQ(DayOfWeek(DayOfWeek::Sunday), epwFile.startDayOfWeek());
  EXPECT_EQ(Date(MonthOfYear::Jan, 1), epwFile.startDate());
  EXPECT_EQ(Date(MonthOfYear::Dec, 31), epwFile.endDate());
  // Up to here, everything should be the same as the first test. Now ask for the design conditions

  constexpr std::array<std::array<double, 16>, 3> expected_depth_values{{
    {0.5, -9999, -9999, -9999, -0.6, 1.34, 5.12, 8.69, 15.46, 19.02, 20.0, 18.2, 14.02, 8.83, 3.71, 0.32},
    {2.0, -9999, -9999, -9999, 2.08, 2.55, 4.7, 7.1, 12.3, 15.62, 17.28, 16.91, 14.53, 10.94, 6.9, 3.72},
    {4.0, -9999, -9999, -9999, 4.84, 4.51, 5.45, 6.81, 10.25, 12.82, 14.49, 14.9, 13.86, 11.74, 9.0, 6.53},
  }};

  std::vector<EpwGroundTemperatureDepth> depths = epwFile.groundTemperatureDepths();
  ASSERT_EQ(3, depths.size());
  for (size_t i = 0; i < depths.size(); ++i) {
    const auto& depth = depths.at(i);
    const auto& expected_values = expected_depth_values.at(i);

    EXPECT_DOUBLE_EQ(expected_values.at(0), depth.groundTemperatureDepth());
    if (expected_values.at(1) < 0) {
      EXPECT_FALSE(depth.soilConductivity());
    } else {
      ASSERT_TRUE(depth.soilConductivity());
      EXPECT_DOUBLE_EQ(expected_values.at(1), depth.soilConductivity().get());
    }
    if (expected_values.at(2) < 0) {
      EXPECT_FALSE(depth.soilDensity());
    } else {
      ASSERT_TRUE(depth.soilDensity());
      EXPECT_DOUBLE_EQ(expected_values.at(2), depth.soilDensity().get());
    }
    if (expected_values.at(3) < 0) {
      EXPECT_FALSE(depth.soilSpecificHeat());
    } else {
      ASSERT_TRUE(depth.soilSpecificHeat());
      EXPECT_DOUBLE_EQ(expected_values.at(3), depth.soilSpecificHeat().get());
    }
    EXPECT_DOUBLE_EQ(expected_values.at(4), depth.janGroundTemperature());
    EXPECT_DOUBLE_EQ(expected_values.at(5), depth.febGroundTemperature());
    EXPECT_DOUBLE_EQ(expected_values.at(6), depth.marGroundTemperature());
    EXPECT_DOUBLE_EQ(expected_values.at(7), depth.aprGroundTemperature());
    EXPECT_DOUBLE_EQ(expected_values.at(8), depth.mayGroundTemperature());
    EXPECT_DOUBLE_EQ(expected_values.at(9), depth.junGroundTemperature());
    EXPECT_DOUBLE_EQ(expected_values.at(10), depth.julGroundTemperature());
    EXPECT_DOUBLE_EQ(expected_values.at(11), depth.augGroundTemperature());
    EXPECT_DOUBLE_EQ(expected_values.at(12), depth.sepGroundTemperature());
    EXPECT_DOUBLE_EQ(expected_values.at(13), depth.octGroundTemperature());
    EXPECT_DOUBLE_EQ(expected_values.at(14), depth.novGroundTemperature());
    EXPECT_DOUBLE_EQ(expected_values.at(15), depth.decGroundTemperature());
  }
}

TEST(Filetypes, EpwFile_Design_DoubleRead) {
  path p = resourcesPath() / toPath("utilities/Filetypes/USA_CO_Golden-NREL.724666_TMY3.epw");
  EpwFile epwFile(p);
  EXPECT_EQ(p, epwFile.path());
  EXPECT_EQ("BDF687C1", epwFile.checksum());
  EXPECT_EQ(openstudio::checksum(epwFile.path()), epwFile.checksum());
  EXPECT_EQ("Denver Centennial  Golden   Nr", epwFile.city());
  EXPECT_EQ("CO", epwFile.stateProvinceRegion());
  EXPECT_EQ("USA", epwFile.country());
  EXPECT_EQ("TMY3", epwFile.dataSource());
  EXPECT_EQ("724666", epwFile.wmoNumber());
  EXPECT_EQ(39.74, epwFile.latitude());
  EXPECT_EQ(-105.18, epwFile.longitude());
  EXPECT_EQ(-7, epwFile.timeZone());
  EXPECT_EQ(1829, epwFile.elevation());
  EXPECT_EQ(Time(0, 1, 0, 0), epwFile.timeStep());
  EXPECT_EQ(DayOfWeek(DayOfWeek::Sunday), epwFile.startDayOfWeek());
  EXPECT_EQ(Date(MonthOfYear::Jan, 1), epwFile.startDate());
  EXPECT_EQ(Date(MonthOfYear::Dec, 31), epwFile.endDate());
  // Ask for data
  std::vector<EpwDataPoint> data = epwFile.data();
  EXPECT_EQ(8760, data.size());
  // The last data point should be for the last hour 12/31/1996, with a dry bulb temp of 4C and pressure 81100
  openstudio::DateTime dateTime = data[8759].dateTime();
  EXPECT_EQ(1, dateTime.date().monthOfYear().value());
  EXPECT_EQ(1, dateTime.date().dayOfMonth());
  EXPECT_EQ(1997, dateTime.date().year());
  EXPECT_EQ(0, dateTime.time().hours());
  EXPECT_EQ(0, dateTime.time().minutes());
  EXPECT_EQ(0, dateTime.time().seconds());
  EXPECT_EQ(4.0, data[8759].dryBulbTemperature().get());
  EXPECT_EQ(81100, data[8759].atmosphericStationPressure().get());
  // Try out the alternate access functions, dew point temperature should be -1C
  EXPECT_EQ(-1.0, data[8759].getFieldByName("Dew Point Temperature").get());
  EXPECT_EQ(-1.0, data[8759].getField(EpwDataField("Dew Point Temperature")).get());
  // The last data point should not have a liquid precipitation depth
  EXPECT_FALSE(data[8759].getFieldByName("Liquid Precipitation Depth"));
  // Ask for the design conditions
  std::vector<EpwDesignCondition> designs = epwFile.designConditions();
  EXPECT_EQ(1, designs.size());
  EXPECT_EQ("Climate Design Data 2009 ASHRAE Handbook", designs[0].titleOfDesignCondition());
  EXPECT_EQ(12, designs[0].heatingColdestMonth().get());
  EXPECT_EQ(-18.8, designs[0].heatingDryBulb99pt6().get());
  EXPECT_EQ(-18.8, designs[0].getFieldByName("Heating Dry Bulb Temperature 99.6%").get());
  EXPECT_EQ(-18.8, designs[0].getField(EpwDesignField("Heating Dry Bulb Temperature 99.6%")).get());
  EXPECT_EQ("C", designs[0].getUnitsByName("Heating Dry Bulb Temperature 99.6%").get());
  EXPECT_EQ("C", designs[0].getUnits(EpwDesignField("Heating Dry Bulb Temperature 99.6%")));
  ASSERT_TRUE(designs[0].heatingDryBulb99().get());
  EXPECT_EQ(-15.5, designs[0].heatingDryBulb99().get());
  EXPECT_EQ(-21.6, designs[0].heatingHumidificationDewPoint99pt6().get());
  EXPECT_EQ(0.7, designs[0].heatingHumidificationHumidityRatio99pt6().get());
  EXPECT_EQ(-10.9, designs[0].heatingHumidificationMeanCoincidentDryBulb99pt6().get());
  EXPECT_EQ(-18.8, designs[0].heatingHumidificationDewPoint99().get());
  EXPECT_EQ(0.9, designs[0].heatingHumidificationHumidityRatio99().get());
  EXPECT_EQ(-7.5, designs[0].heatingHumidificationMeanCoincidentDryBulb99().get());
  EXPECT_EQ(12.2, designs[0].heatingColdestMonthWindSpeed0pt4().get());
  EXPECT_EQ(3.9, designs[0].heatingColdestMonthMeanCoincidentDryBulb0pt4().get());
  EXPECT_EQ(10.9, designs[0].heatingColdestMonthWindSpeed1().get());
  EXPECT_EQ(3.8, designs[0].heatingColdestMonthMeanCoincidentDryBulb1().get());
  EXPECT_EQ(3.0, designs[0].heatingMeanCoincidentWindSpeed99pt6().get());
  EXPECT_EQ(340, designs[0].heatingPrevailingCoincidentWindDirection99pt6().get());
  EXPECT_EQ(7, designs[0].coolingHottestMonth().get());
  EXPECT_EQ(15.2, designs[0].coolingDryBulbRange().get());
  EXPECT_EQ(33.0, designs[0].coolingDryBulb0pt4().get());
  EXPECT_EQ(15.7, designs[0].coolingMeanCoincidentWetBulb0pt4().get());
  EXPECT_EQ(32.0, designs[0].coolingDryBulb1().get());
  EXPECT_EQ(15.5, designs[0].coolingMeanCoincidentWetBulb1().get());
  EXPECT_EQ(30.2, designs[0].coolingDryBulb2().get());
  EXPECT_EQ(15.3, designs[0].coolingMeanCoincidentWetBulb2().get());
  EXPECT_EQ(18.4, designs[0].coolingEvaporationWetBulb0pt4().get());
  EXPECT_EQ(27.3, designs[0].coolingEvaporationMeanCoincidentDryBulb0pt4().get());
  EXPECT_EQ(17.5, designs[0].coolingEvaporationWetBulb1().get());
  EXPECT_EQ(26.4, designs[0].coolingEvaporationMeanCoincidentDryBulb1().get());
  EXPECT_EQ(16.8, designs[0].coolingEvaporationWetBulb2().get());
  EXPECT_EQ(25.6, designs[0].coolingEvaporationMeanCoincidentDryBulb2().get());
  EXPECT_EQ(4.9, designs[0].coolingMeanCoincidentWindSpeed0pt4().get());
  EXPECT_EQ(0, designs[0].coolingPrevailingCoincidentWindDirection0pt4().get());
  EXPECT_EQ(16.1, designs[0].coolingDehumidificationDewPoint0pt4().get());
  EXPECT_EQ(14.3, designs[0].coolingDehumidificationHumidityRatio0pt4().get());
  EXPECT_EQ(20.2, designs[0].coolingDehumidificationMeanCoincidentDryBulb0pt4().get());
  EXPECT_EQ(14.9, designs[0].coolingDehumidificationDewPoint1().get());
  EXPECT_EQ(13.2, designs[0].coolingDehumidificationHumidityRatio1().get());
  EXPECT_EQ(19.9, designs[0].coolingDehumidificationMeanCoincidentDryBulb1().get());
  EXPECT_EQ(13.9, designs[0].coolingDehumidificationDewPoint2().get());
  EXPECT_EQ(12.3, designs[0].coolingDehumidificationHumidityRatio2().get());
  EXPECT_EQ(19.6, designs[0].coolingDehumidificationMeanCoincidentDryBulb2().get());
  EXPECT_EQ(59.7, designs[0].coolingEnthalpy0pt4().get());
  EXPECT_EQ(27.3, designs[0].coolingEnthalpyMeanCoincidentDryBulb0pt4().get());
  EXPECT_EQ(56.6, designs[0].coolingEnthalpy1().get());
  EXPECT_EQ(26.6, designs[0].coolingEnthalpyMeanCoincidentDryBulb1().get());
  EXPECT_EQ(54.0, designs[0].coolingEnthalpy2().get());
  EXPECT_EQ(25.7, designs[0].coolingEnthalpyMeanCoincidentDryBulb2().get());
  EXPECT_EQ(760, designs[0].coolingHours8To4AndDryBulb12pt8To20pt6().get());
  EXPECT_EQ(11.1, designs[0].extremeWindSpeed1().get());
  EXPECT_EQ(9.5, designs[0].extremeWindSpeed2pt5().get());
  EXPECT_EQ(8.4, designs[0].extremeWindSpeed5().get());
  EXPECT_EQ(22.9, designs[0].extremeMaxWetBulb().get());
  EXPECT_EQ(-22.9, designs[0].extremeMeanMinDryBulb().get());
  EXPECT_EQ(36.1, designs[0].extremeMeanMaxDryBulb().get());
  EXPECT_EQ(3.8, designs[0].extremeStdDevMinDryBulb().get());
  EXPECT_EQ(1.2, designs[0].extremeStdDevMaxDryBulb().get());
  EXPECT_EQ(-25.7, designs[0].extremeN5YearsMinDryBulb().get());
  EXPECT_EQ(37.0, designs[0].extremeN5YearsMaxDryBulb().get());
  EXPECT_EQ(-27.9, designs[0].extremeN10YearsMinDryBulb().get());
  EXPECT_EQ(37.7, designs[0].extremeN10YearsMaxDryBulb().get());
  EXPECT_EQ(-30.1, designs[0].extremeN20YearsMinDryBulb().get());
  EXPECT_EQ(38.3, designs[0].extremeN20YearsMaxDryBulb().get());
  EXPECT_EQ(-32.8, designs[0].extremeN50YearsMinDryBulb().get());
  EXPECT_EQ(39.2, designs[0].extremeN50YearsMaxDryBulb().get());
  // Check that the data is the right size
  data = epwFile.data();
  EXPECT_EQ(8760, data.size());
}

TEST(Filetypes, EpwFile_Data_DoubleRead) {
  path p = resourcesPath() / toPath("utilities/Filetypes/USA_CO_Golden-NREL.724666_TMY3.epw");
  EpwFile epwFile(p);
  EXPECT_EQ(p, epwFile.path());
  EXPECT_EQ("BDF687C1", epwFile.checksum());
  EXPECT_EQ(openstudio::checksum(epwFile.path()), epwFile.checksum());
  EXPECT_EQ("Denver Centennial  Golden   Nr", epwFile.city());
  EXPECT_EQ("CO", epwFile.stateProvinceRegion());
  EXPECT_EQ("USA", epwFile.country());
  EXPECT_EQ("TMY3", epwFile.dataSource());
  EXPECT_EQ("724666", epwFile.wmoNumber());
  EXPECT_EQ(39.74, epwFile.latitude());
  EXPECT_EQ(-105.18, epwFile.longitude());
  EXPECT_EQ(-7, epwFile.timeZone());
  EXPECT_EQ(1829, epwFile.elevation());
  EXPECT_EQ(Time(0, 1, 0, 0), epwFile.timeStep());
  EXPECT_EQ(DayOfWeek(DayOfWeek::Sunday), epwFile.startDayOfWeek());
  EXPECT_EQ(Date(MonthOfYear::Jan, 1), epwFile.startDate());
  EXPECT_EQ(Date(MonthOfYear::Dec, 31), epwFile.endDate());
  // Ask for the design conditions
  std::vector<EpwDesignCondition> designs = epwFile.designConditions();
  EXPECT_EQ(1, designs.size());
  EXPECT_EQ("Climate Design Data 2009 ASHRAE Handbook", designs[0].titleOfDesignCondition());
  EXPECT_EQ(12, designs[0].heatingColdestMonth().get());
  EXPECT_EQ(-18.8, designs[0].heatingDryBulb99pt6().get());
  EXPECT_EQ(-18.8, designs[0].getFieldByName("Heating Dry Bulb Temperature 99.6%").get());
  EXPECT_EQ(-18.8, designs[0].getField(EpwDesignField("Heating Dry Bulb Temperature 99.6%")).get());
  EXPECT_EQ("C", designs[0].getUnitsByName("Heating Dry Bulb Temperature 99.6%").get());
  EXPECT_EQ("C", designs[0].getUnits(EpwDesignField("Heating Dry Bulb Temperature 99.6%")));
  ASSERT_TRUE(designs[0].heatingDryBulb99().get());
  EXPECT_EQ(-15.5, designs[0].heatingDryBulb99().get());
  EXPECT_EQ(-21.6, designs[0].heatingHumidificationDewPoint99pt6().get());
  EXPECT_EQ(0.7, designs[0].heatingHumidificationHumidityRatio99pt6().get());
  EXPECT_EQ(-10.9, designs[0].heatingHumidificationMeanCoincidentDryBulb99pt6().get());
  EXPECT_EQ(-18.8, designs[0].heatingHumidificationDewPoint99().get());
  EXPECT_EQ(0.9, designs[0].heatingHumidificationHumidityRatio99().get());
  EXPECT_EQ(-7.5, designs[0].heatingHumidificationMeanCoincidentDryBulb99().get());
  EXPECT_EQ(12.2, designs[0].heatingColdestMonthWindSpeed0pt4().get());
  EXPECT_EQ(3.9, designs[0].heatingColdestMonthMeanCoincidentDryBulb0pt4().get());
  EXPECT_EQ(10.9, designs[0].heatingColdestMonthWindSpeed1().get());
  EXPECT_EQ(3.8, designs[0].heatingColdestMonthMeanCoincidentDryBulb1().get());
  EXPECT_EQ(3.0, designs[0].heatingMeanCoincidentWindSpeed99pt6().get());
  EXPECT_EQ(340, designs[0].heatingPrevailingCoincidentWindDirection99pt6().get());
  EXPECT_EQ(7, designs[0].coolingHottestMonth().get());
  EXPECT_EQ(15.2, designs[0].coolingDryBulbRange().get());
  EXPECT_EQ(33.0, designs[0].coolingDryBulb0pt4().get());
  EXPECT_EQ(15.7, designs[0].coolingMeanCoincidentWetBulb0pt4().get());
  EXPECT_EQ(32.0, designs[0].coolingDryBulb1().get());
  EXPECT_EQ(15.5, designs[0].coolingMeanCoincidentWetBulb1().get());
  EXPECT_EQ(30.2, designs[0].coolingDryBulb2().get());
  EXPECT_EQ(15.3, designs[0].coolingMeanCoincidentWetBulb2().get());
  EXPECT_EQ(18.4, designs[0].coolingEvaporationWetBulb0pt4().get());
  EXPECT_EQ(27.3, designs[0].coolingEvaporationMeanCoincidentDryBulb0pt4().get());
  EXPECT_EQ(17.5, designs[0].coolingEvaporationWetBulb1().get());
  EXPECT_EQ(26.4, designs[0].coolingEvaporationMeanCoincidentDryBulb1().get());
  EXPECT_EQ(16.8, designs[0].coolingEvaporationWetBulb2().get());
  EXPECT_EQ(25.6, designs[0].coolingEvaporationMeanCoincidentDryBulb2().get());
  EXPECT_EQ(4.9, designs[0].coolingMeanCoincidentWindSpeed0pt4().get());
  EXPECT_EQ(0, designs[0].coolingPrevailingCoincidentWindDirection0pt4().get());
  EXPECT_EQ(16.1, designs[0].coolingDehumidificationDewPoint0pt4().get());
  EXPECT_EQ(14.3, designs[0].coolingDehumidificationHumidityRatio0pt4().get());
  EXPECT_EQ(20.2, designs[0].coolingDehumidificationMeanCoincidentDryBulb0pt4().get());
  EXPECT_EQ(14.9, designs[0].coolingDehumidificationDewPoint1().get());
  EXPECT_EQ(13.2, designs[0].coolingDehumidificationHumidityRatio1().get());
  EXPECT_EQ(19.9, designs[0].coolingDehumidificationMeanCoincidentDryBulb1().get());
  EXPECT_EQ(13.9, designs[0].coolingDehumidificationDewPoint2().get());
  EXPECT_EQ(12.3, designs[0].coolingDehumidificationHumidityRatio2().get());
  EXPECT_EQ(19.6, designs[0].coolingDehumidificationMeanCoincidentDryBulb2().get());
  EXPECT_EQ(59.7, designs[0].coolingEnthalpy0pt4().get());
  EXPECT_EQ(27.3, designs[0].coolingEnthalpyMeanCoincidentDryBulb0pt4().get());
  EXPECT_EQ(56.6, designs[0].coolingEnthalpy1().get());
  EXPECT_EQ(26.6, designs[0].coolingEnthalpyMeanCoincidentDryBulb1().get());
  EXPECT_EQ(54.0, designs[0].coolingEnthalpy2().get());
  EXPECT_EQ(25.7, designs[0].coolingEnthalpyMeanCoincidentDryBulb2().get());
  EXPECT_EQ(760, designs[0].coolingHours8To4AndDryBulb12pt8To20pt6().get());
  EXPECT_EQ(11.1, designs[0].extremeWindSpeed1().get());
  EXPECT_EQ(9.5, designs[0].extremeWindSpeed2pt5().get());
  EXPECT_EQ(8.4, designs[0].extremeWindSpeed5().get());
  EXPECT_EQ(22.9, designs[0].extremeMaxWetBulb().get());
  EXPECT_EQ(-22.9, designs[0].extremeMeanMinDryBulb().get());
  EXPECT_EQ(36.1, designs[0].extremeMeanMaxDryBulb().get());
  EXPECT_EQ(3.8, designs[0].extremeStdDevMinDryBulb().get());
  EXPECT_EQ(1.2, designs[0].extremeStdDevMaxDryBulb().get());
  EXPECT_EQ(-25.7, designs[0].extremeN5YearsMinDryBulb().get());
  EXPECT_EQ(37.0, designs[0].extremeN5YearsMaxDryBulb().get());
  EXPECT_EQ(-27.9, designs[0].extremeN10YearsMinDryBulb().get());
  EXPECT_EQ(37.7, designs[0].extremeN10YearsMaxDryBulb().get());
  EXPECT_EQ(-30.1, designs[0].extremeN20YearsMinDryBulb().get());
  EXPECT_EQ(38.3, designs[0].extremeN20YearsMaxDryBulb().get());
  EXPECT_EQ(-32.8, designs[0].extremeN50YearsMinDryBulb().get());
  EXPECT_EQ(39.2, designs[0].extremeN50YearsMaxDryBulb().get());
  // Ask for data
  std::vector<EpwDataPoint> data = epwFile.data();
  EXPECT_EQ(8760, data.size());
  // The last data point should be for the last hour 12/31/1996, with a dry bulb temp of 4C and pressure 81100
  openstudio::DateTime dateTime = data[8759].dateTime();
  EXPECT_EQ(1, dateTime.date().monthOfYear().value());
  EXPECT_EQ(1, dateTime.date().dayOfMonth());
  EXPECT_EQ(1997, dateTime.date().year());
  EXPECT_EQ(0, dateTime.time().hours());
  EXPECT_EQ(0, dateTime.time().minutes());
  EXPECT_EQ(0, dateTime.time().seconds());
  EXPECT_EQ(4.0, data[8759].dryBulbTemperature().get());
  EXPECT_EQ(81100, data[8759].atmosphericStationPressure().get());
  // Try out the alternate access functions, dew point temperature should be -1C
  EXPECT_EQ(-1.0, data[8759].getFieldByName("Dew Point Temperature").get());
  EXPECT_EQ(-1.0, data[8759].getField(EpwDataField("Dew Point Temperature")).get());
  // The last data point should not have a liquid precipitation depth
  EXPECT_FALSE(data[8759].getFieldByName("Liquid Precipitation Depth"));
  // Check that the design data is the right size
  designs = epwFile.designConditions();
  EXPECT_EQ(1, designs.size());
}

TEST(Filetypes, EpwFile_NoDesign) {
  path p = resourcesPath() / toPath("utilities/Filetypes/leapday-test.epw");
  EpwFile epwFile(p);
  EXPECT_EQ(p, epwFile.path());
  // Ask for data
  std::vector<EpwDataPoint> data = epwFile.data();
  EXPECT_EQ(8784, data.size());
  // Ask for the design conditions, but there aren't any
  std::vector<EpwDesignCondition> designs = epwFile.designConditions();
  EXPECT_EQ(0, designs.size());
  data = epwFile.data();
  EXPECT_EQ(8784, data.size());
}

TEST(Filetypes, EpwFile_IncompleteDesign) {
  path p = resourcesPath() / toPath("utilities/Filetypes/USA_CO_Golden-NREL.724666_TMY3_IncompleteDesign.epw");
  EpwFile epwFile(p);
  EXPECT_EQ(p, epwFile.path());
  EXPECT_EQ("ECC55BA2", epwFile.checksum());
  EXPECT_EQ(openstudio::checksum(epwFile.path()), epwFile.checksum());
  EXPECT_EQ("Denver Centennial  Golden   Nr", epwFile.city());
  EXPECT_EQ("CO", epwFile.stateProvinceRegion());
  EXPECT_EQ("USA", epwFile.country());
  EXPECT_EQ("TMY3", epwFile.dataSource());
  EXPECT_EQ("724666", epwFile.wmoNumber());
  EXPECT_EQ(39.74, epwFile.latitude());
  EXPECT_EQ(-105.18, epwFile.longitude());
  EXPECT_EQ(-7, epwFile.timeZone());
  EXPECT_EQ(1829, epwFile.elevation());
  EXPECT_EQ(Time(0, 1, 0, 0), epwFile.timeStep());
  EXPECT_EQ(DayOfWeek(DayOfWeek::Sunday), epwFile.startDayOfWeek());
  EXPECT_EQ(Date(MonthOfYear::Jan, 1), epwFile.startDate());
  EXPECT_EQ(Date(MonthOfYear::Dec, 31), epwFile.endDate());
  // Up to here, everything should be the same as the first test. Now ask for the design conditions
  std::vector<EpwDesignCondition> designs = epwFile.designConditions();
  EXPECT_EQ(1, designs.size());
  EXPECT_EQ("Climate Design Data 2013 ASHRAE Handbook", designs[0].titleOfDesignCondition());
  EXPECT_FALSE(designs[0].heatingColdestMonth());
  EXPECT_FALSE(designs[0].heatingDryBulb99pt6());
  EXPECT_FALSE(designs[0].getFieldByName("Heating Dry Bulb Temperature 99.6%"));
  EXPECT_FALSE(designs[0].getField(EpwDesignField("Heating Dry Bulb Temperature 99.6%")));
  EXPECT_EQ("C", designs[0].getUnitsByName("Heating Dry Bulb Temperature 99.6%").get());
  EXPECT_EQ("C", designs[0].getUnits(EpwDesignField("Heating Dry Bulb Temperature 99.6%")));
  EXPECT_FALSE(designs[0].heatingDryBulb99());
  EXPECT_FALSE(designs[0].heatingHumidificationDewPoint99pt6());
  EXPECT_FALSE(designs[0].heatingHumidificationHumidityRatio99pt6());
  EXPECT_FALSE(designs[0].heatingHumidificationMeanCoincidentDryBulb99pt6());
  EXPECT_FALSE(designs[0].heatingHumidificationDewPoint99());
  EXPECT_FALSE(designs[0].heatingHumidificationHumidityRatio99());
  EXPECT_FALSE(designs[0].heatingHumidificationMeanCoincidentDryBulb99());
  EXPECT_FALSE(designs[0].heatingColdestMonthWindSpeed0pt4());
  EXPECT_FALSE(designs[0].heatingColdestMonthMeanCoincidentDryBulb0pt4());
  ASSERT_TRUE(designs[0].heatingColdestMonthWindSpeed1());
  EXPECT_EQ(13.4, designs[0].heatingColdestMonthWindSpeed1().get());
  EXPECT_FALSE(designs[0].heatingColdestMonthMeanCoincidentDryBulb1());
  EXPECT_FALSE(designs[0].heatingMeanCoincidentWindSpeed99pt6());
  EXPECT_FALSE(designs[0].heatingPrevailingCoincidentWindDirection99pt6());
  EXPECT_FALSE(designs[0].coolingHottestMonth());
  ASSERT_TRUE(designs[0].coolingDryBulbRange());
  EXPECT_EQ(9.8, designs[0].coolingDryBulbRange().get());
  EXPECT_FALSE(designs[0].coolingDryBulb0pt4());
  EXPECT_FALSE(designs[0].coolingMeanCoincidentWetBulb0pt4());
  ASSERT_TRUE(designs[0].coolingDryBulb1());
  EXPECT_EQ(28.0, designs[0].coolingDryBulb1().get());
  ASSERT_TRUE(designs[0].coolingMeanCoincidentWetBulb1());
  EXPECT_EQ(19.5, designs[0].coolingMeanCoincidentWetBulb1().get());
  EXPECT_FALSE(designs[0].coolingDryBulb2());
  EXPECT_FALSE(designs[0].coolingMeanCoincidentWetBulb2());
  EXPECT_FALSE(designs[0].coolingEvaporationWetBulb0pt4());
  EXPECT_FALSE(designs[0].coolingEvaporationMeanCoincidentDryBulb0pt4());
  EXPECT_FALSE(designs[0].coolingEvaporationWetBulb1());
  EXPECT_FALSE(designs[0].coolingEvaporationMeanCoincidentDryBulb1());
  EXPECT_FALSE(designs[0].coolingEvaporationWetBulb2());
  EXPECT_FALSE(designs[0].coolingEvaporationMeanCoincidentDryBulb2());
  ASSERT_TRUE(designs[0].coolingMeanCoincidentWindSpeed0pt4());
  EXPECT_EQ(5.5, designs[0].coolingMeanCoincidentWindSpeed0pt4().get());
  EXPECT_FALSE(designs[0].coolingPrevailingCoincidentWindDirection0pt4());
  EXPECT_FALSE(designs[0].coolingDehumidificationDewPoint0pt4());
  EXPECT_FALSE(designs[0].coolingDehumidificationHumidityRatio0pt4());
  EXPECT_FALSE(designs[0].coolingDehumidificationMeanCoincidentDryBulb0pt4());
  EXPECT_FALSE(designs[0].coolingDehumidificationDewPoint1());
  EXPECT_FALSE(designs[0].coolingDehumidificationHumidityRatio1());
  EXPECT_FALSE(designs[0].coolingDehumidificationMeanCoincidentDryBulb1());
  ASSERT_TRUE(designs[0].coolingDehumidificationDewPoint2());
  EXPECT_EQ(17.7, designs[0].coolingDehumidificationDewPoint2().get());
  EXPECT_FALSE(designs[0].coolingDehumidificationHumidityRatio2());
  ASSERT_TRUE(designs[0].coolingDehumidificationMeanCoincidentDryBulb2());
  EXPECT_EQ(23.2, designs[0].coolingDehumidificationMeanCoincidentDryBulb2().get());
  EXPECT_FALSE(designs[0].coolingEnthalpy0pt4());
  EXPECT_FALSE(designs[0].coolingEnthalpyMeanCoincidentDryBulb0pt4());
  EXPECT_FALSE(designs[0].coolingEnthalpy1());
  EXPECT_FALSE(designs[0].coolingEnthalpyMeanCoincidentDryBulb1());
  EXPECT_FALSE(designs[0].coolingEnthalpy2());
  EXPECT_FALSE(designs[0].coolingEnthalpyMeanCoincidentDryBulb2());
  EXPECT_FALSE(designs[0].coolingHours8To4AndDryBulb12pt8To20pt6());
  EXPECT_FALSE(designs[0].extremeWindSpeed1());
  EXPECT_FALSE(designs[0].extremeWindSpeed2pt5());
  EXPECT_FALSE(designs[0].extremeWindSpeed5());
  EXPECT_FALSE(designs[0].extremeMaxWetBulb());
  EXPECT_FALSE(designs[0].extremeMeanMinDryBulb());
  EXPECT_FALSE(designs[0].extremeMeanMaxDryBulb());
  EXPECT_FALSE(designs[0].extremeStdDevMinDryBulb());
  EXPECT_FALSE(designs[0].extremeStdDevMaxDryBulb());
  EXPECT_FALSE(designs[0].extremeN5YearsMinDryBulb());
  EXPECT_FALSE(designs[0].extremeN5YearsMaxDryBulb());
  EXPECT_FALSE(designs[0].extremeN10YearsMinDryBulb());
  EXPECT_FALSE(designs[0].extremeN10YearsMaxDryBulb());
  EXPECT_FALSE(designs[0].extremeN20YearsMinDryBulb());
  EXPECT_FALSE(designs[0].extremeN20YearsMaxDryBulb());
  EXPECT_FALSE(designs[0].extremeN50YearsMinDryBulb());
  EXPECT_FALSE(designs[0].extremeN50YearsMaxDryBulb());
}

TEST(Filetypes, EpwFile_LeapTimeSeries) {
  path p = resourcesPath() / toPath("utilities/Filetypes/leapday-test.epw");
  EpwFile epwFile(p);
  EXPECT_EQ(p, epwFile.path());
  // Ask for data
  std::vector<EpwDataPoint> data = epwFile.data();
  EXPECT_EQ(8784, data.size());
  // Ask for the design conditions, but there aren't any
  std::vector<EpwDesignCondition> designs = epwFile.designConditions();
  EXPECT_EQ(0, designs.size());
  data = epwFile.data();
  EXPECT_EQ(8784, data.size());

  EXPECT_TRUE(epwFile.isActual());

  boost::optional<int> _epwDataPointBaseYear = data[0].date().baseYear();
  ASSERT_TRUE(_epwDataPointBaseYear);
  EXPECT_EQ(2012, _epwDataPointBaseYear.get());

  boost::optional<TimeSeries> _t;
  ASSERT_NO_THROW(_t = epwFile.getTimeSeries("Dry Bulb Temperature"));
  ASSERT_TRUE(_t);
  // isActual is true, so it should be a timeSeries with the actual year
  boost::optional<int> _timeSeriesBaseYear = _t->firstReportDateTime().date().baseYear();
  ASSERT_TRUE(_timeSeriesBaseYear);
  EXPECT_EQ(2012, _timeSeriesBaseYear.get());
}

TEST(Filetypes, EpwFile_LeapTimeSeries_AMYNoLeapDay) {
  // Tests for #5214

  path p = resourcesPath() / toPath("utilities/Filetypes/leapday-test-noleapday.epw");
  EpwFile epwFile(p);
  boost::optional<TimeSeries> _t;
  ASSERT_NO_THROW(_t = epwFile.getTimeSeries("Dry Bulb Temperature"));
  ASSERT_TRUE(_t);
  // even though this is AMY, the lack of Feb 29 causes it to be TMY (i.e., successive datapoints greater than 1 day)
  boost::optional<int> _timeSeriesBaseYear = _t->firstReportDateTime().date().baseYear();
  EXPECT_FALSE(_timeSeriesBaseYear);
}

TEST(Filetypes, EpwFile_LeapTimeSeries_TMYLeapFebNoLeapDay) {
  // Tests for #5214

  path p = resourcesPath() / toPath("utilities/Filetypes/USA_CO_Golden-NREL.724666_TMY3-noleapday.epw");
  EpwFile epwFile(p);
  boost::optional<TimeSeries> _t;
  ASSERT_NO_THROW(_t = epwFile.getTimeSeries("Dry Bulb Temperature"));
  ASSERT_TRUE(_t);
  boost::optional<int> _timeSeriesBaseYear = _t->firstReportDateTime().date().baseYear();
  EXPECT_FALSE(_timeSeriesBaseYear);
}

TEST(Filetypes, EpwFile_LeapTimeSeries_TMYLeapFebLeapDay) {
  // Tests for #5214

  path p = resourcesPath() / toPath("utilities/Filetypes/USA_CO_Golden-NREL.724666_TMY3-leapday.epw");
  EpwFile epwFile(p);
  // [utilities.time.Date] <2> Bad Date: year = 2009, month = Feb(2), day = 29.
  EXPECT_ANY_THROW(epwFile.getTimeSeries("Dry Bulb Temperature"));
}

TEST(Filetypes, EpwFile_NonActualTimeSeries) {
  path p = resourcesPath() / toPath("utilities/Filetypes/USA_CO_Golden-NREL.724666_TMY3.epw");
  EpwFile epwFile(p);
  EXPECT_EQ(p, epwFile.path());
  // Ask for data
  std::vector<EpwDataPoint> data = epwFile.data();
  EXPECT_EQ(8760, data.size());

  EXPECT_FALSE(epwFile.isActual());

  // It should have a baseYear as a DataPoint
  boost::optional<int> _epwDataPointBaseYear = data[0].date().baseYear();
  ASSERT_TRUE(_epwDataPointBaseYear);
  EXPECT_EQ(1999, _epwDataPointBaseYear.get());

  boost::optional<TimeSeries> _t;
  ASSERT_NO_THROW(_t = epwFile.getTimeSeries("Dry Bulb Temperature"));
  ASSERT_TRUE(_t);
  // But it shouldn't when getting a TimeSeries, since it's a TMY file
  boost::optional<int> _timeSeriesBaseYear = _t->firstReportDateTime().date().baseYear();
  EXPECT_FALSE(_timeSeriesBaseYear);
}

TEST(Filetypes, EpwFile_International_Data) {
  path p = resourcesPath() / toPath("utilities/Filetypes/CHN_Guangdong.Shaoguan.590820_CSWD.epw");
  EpwFile epwFile(p, true);
  EXPECT_EQ(p, epwFile.path());
  EXPECT_EQ("B68C068B", epwFile.checksum());
  EXPECT_EQ("Shaoguan", epwFile.city());
  EXPECT_EQ("Guangdong", epwFile.stateProvinceRegion());
  EXPECT_EQ("CHN", epwFile.country());
  EXPECT_EQ("CSWD", epwFile.dataSource());
  EXPECT_EQ("590820", epwFile.wmoNumber());
  EXPECT_EQ(24.68, epwFile.latitude());
  EXPECT_EQ(113.6, epwFile.longitude());
  EXPECT_EQ(8, epwFile.timeZone());
  EXPECT_EQ(61, epwFile.elevation());
  EXPECT_EQ(Time(0, 1, 0, 0), epwFile.timeStep());
  EXPECT_EQ(DayOfWeek(DayOfWeek::Sunday), epwFile.startDayOfWeek());
  EXPECT_EQ(Date(MonthOfYear::Jan, 1), epwFile.startDate());
  EXPECT_EQ(Date(MonthOfYear::Dec, 31), epwFile.endDate());
  // Up to here, everything should be the same as the first test. Now ask for the data
  std::vector<EpwDataPoint> data = epwFile.data();
  EXPECT_EQ(8760, data.size());
  // The last data point check
  EXPECT_EQ(14.7, data[8759].dryBulbTemperature().get());
  EXPECT_EQ(101100, data[8759].atmosphericStationPressure().get());
  // Try out the alternate access functions, dew point temperature should be -1C
  EXPECT_EQ(11.7, data[8759].getFieldByName("Dew Point Temperature").get());
  EXPECT_EQ(11.7, data[8759].getField(EpwDataField("Dew Point Temperature")).get());
  // The last data point should not have a liquid precipitation depth
  EXPECT_FALSE(data[8759].getFieldByName("Liquid Precipitation Depth"));
  // Get a time series
  boost::optional<openstudio::TimeSeries> series = epwFile.getTimeSeries("Wind Speed");
  ASSERT_TRUE(series);
  ASSERT_EQ(8760, series->values().size());
  DateTimeVector seriesTimes = series->dateTimes();
  ASSERT_EQ(8760, seriesTimes.size());
  // Check the times in the data and the time series
  DateTime current(Date(1, 1, 1999), Time(0, 1));  // Use 1999 to avoid leap years
  Time delta(0, 1);
  for (unsigned i = 0; i < 8760; i++) {
    // This is a lot more complicated that it probably should be to avoid the year being a problem
    DateTime datatime = data[i].dateTime();
    EXPECT_EQ(datatime.date().monthOfYear(), current.date().monthOfYear());
    EXPECT_EQ(datatime.date().dayOfMonth(), current.date().dayOfMonth());
    EXPECT_EQ(datatime.time().hours(), current.time().hours());
    EXPECT_EQ(datatime.time().minutes(), current.time().minutes());
    DateTime seriestime = seriesTimes[i];
    EXPECT_EQ(seriestime.date().monthOfYear(), current.date().monthOfYear());
    EXPECT_EQ(seriestime.date().dayOfMonth(), current.date().dayOfMonth());
    EXPECT_EQ(seriestime.time().hours(), current.time().hours());
    EXPECT_EQ(seriestime.time().minutes(), current.time().minutes());
    current += delta;
  }
  // No need to redo the original tests here since the data should have been loaded in the constructor
}

TEST(Filetypes, EpwFile_IWEC_Data) {
  path p = resourcesPath() / toPath("utilities/Filetypes/TUN_Tunis.607150_IWEC.epw");
  EpwFile epwFile(p, true);
  EXPECT_EQ(p, epwFile.path());
  EXPECT_EQ("FEAB878E", epwFile.checksum());
  EXPECT_EQ("TUNIS", epwFile.city());
  EXPECT_EQ("-", epwFile.stateProvinceRegion());
  EXPECT_EQ("TUN", epwFile.country());
  EXPECT_EQ("IWEC Data", epwFile.dataSource());
  EXPECT_EQ("607150", epwFile.wmoNumber());
  EXPECT_EQ(36.83, epwFile.latitude());
  EXPECT_EQ(10.23, epwFile.longitude());
  EXPECT_EQ(1, epwFile.timeZone());
  EXPECT_EQ(4, epwFile.elevation());
  EXPECT_EQ(Time(0, 1, 0, 0), epwFile.timeStep());
  EXPECT_EQ(DayOfWeek(DayOfWeek::Sunday), epwFile.startDayOfWeek());
  EXPECT_EQ(Date(MonthOfYear::Jan, 1), epwFile.startDate());
  EXPECT_EQ(Date(MonthOfYear::Dec, 31), epwFile.endDate());
  // Up to here, everything should be the same as the first test. Now ask for the data
  std::vector<EpwDataPoint> data = epwFile.data();
  EXPECT_EQ(8760, data.size());
  // The last data point check
  EXPECT_EQ(11.3, data[8759].dryBulbTemperature().get());
  EXPECT_EQ(102400, data[8759].atmosphericStationPressure().get());
  // Try out the alternate access functions
  EXPECT_EQ(9.8, data[8759].getFieldByName("Dew Point Temperature").get());
  EXPECT_EQ(9.8, data[8759].getField(EpwDataField("Dew Point Temperature")).get());
  // Get a time series
  boost::optional<openstudio::TimeSeries> series = epwFile.getTimeSeries("Wind Speed");
  ASSERT_TRUE(series);
  ASSERT_EQ(8760, series->values().size());
  DateTimeVector seriesTimes = series->dateTimes();
  ASSERT_EQ(8760, seriesTimes.size());
  // Check the times in the data and the time series
  DateTime current(Date(1, 1, 1999), Time(0, 1));  // Use 1999 to avoid leap years
  Time delta(0, 1);
  for (unsigned i = 0; i < 8760; i++) {
    // This is a lot more complicated that it probably should be to avoid the year being a problem
    DateTime datatime = data[i].dateTime();
    EXPECT_EQ(datatime.date().monthOfYear(), current.date().monthOfYear());
    EXPECT_EQ(datatime.date().dayOfMonth(), current.date().dayOfMonth());
    EXPECT_EQ(datatime.time().hours(), current.time().hours());
    EXPECT_EQ(datatime.time().minutes(), current.time().minutes());
    DateTime seriestime = seriesTimes[i];
    EXPECT_EQ(seriestime.date().monthOfYear(), current.date().monthOfYear());
    EXPECT_EQ(seriestime.date().dayOfMonth(), current.date().dayOfMonth());
    EXPECT_EQ(seriestime.time().hours(), current.time().hours());
    EXPECT_EQ(seriestime.time().minutes(), current.time().minutes());
    current += delta;
  }
  // No need to redo the original tests here since the data should have been loaded in the constructor
}

TEST(Filetypes, EpwFile_TMY) {
  path p = resourcesPath() / toPath("utilities/Filetypes/USA_CO_Golden-NREL.724666_TMY3.epw");
  EpwFile epwFile(p);
  EXPECT_EQ(p, epwFile.path());
  EXPECT_EQ("BDF687C1", epwFile.checksum());
  EXPECT_EQ("Denver Centennial  Golden   Nr", epwFile.city());
  EXPECT_EQ("CO", epwFile.stateProvinceRegion());
  EXPECT_EQ("USA", epwFile.country());
  EXPECT_EQ("TMY3", epwFile.dataSource());
  EXPECT_EQ("724666", epwFile.wmoNumber());
  EXPECT_EQ(39.74, epwFile.latitude());
  EXPECT_EQ(-105.18, epwFile.longitude());
  EXPECT_EQ(-7, epwFile.timeZone());
  EXPECT_EQ(1829, epwFile.elevation());
  EXPECT_EQ(Time(0, 1, 0, 0), epwFile.timeStep());
  EXPECT_EQ(DayOfWeek(DayOfWeek::Sunday), epwFile.startDayOfWeek());
  EXPECT_FALSE(epwFile.startDateActualYear());
  EXPECT_FALSE(epwFile.endDateActualYear());
  EXPECT_EQ(Date(MonthOfYear::Jan, 1), epwFile.startDate());
  EXPECT_EQ(Date(MonthOfYear::Dec, 31), epwFile.endDate());
  EXPECT_EQ(365, (epwFile.endDate() - epwFile.startDate()).totalDays() + 1);
  EXPECT_FALSE(epwFile.isActual());
}

TEST(Filetypes, EpwFile_Wrap_TMY) {
  path p = resourcesPath() / toPath("utilities/Filetypes/USA_CO_Golden-NREL.wrap.epw");
  // Wrap around years not supported for TMY data, EPW file
  EXPECT_ANY_THROW(EpwFile{p});
}

TEST(Filetypes, EpwFile_AMY) {
  path p = resourcesPath() / toPath("utilities/Filetypes/USA_CO_Golden-NREL.amy");
  EpwFile epwFile(p);
  EXPECT_EQ(p, epwFile.path());
  EXPECT_EQ("521A957C", epwFile.checksum());
  EXPECT_EQ("Denver Centennial  Golden   Nr", epwFile.city());
  EXPECT_EQ("CO", epwFile.stateProvinceRegion());
  EXPECT_EQ("USA", epwFile.country());
  EXPECT_EQ("TMY3", epwFile.dataSource());
  EXPECT_EQ("724666", epwFile.wmoNumber());
  EXPECT_EQ(39.74, epwFile.latitude());
  EXPECT_EQ(-105.18, epwFile.longitude());
  EXPECT_EQ(-7, epwFile.timeZone());
  EXPECT_EQ(1829, epwFile.elevation());
  EXPECT_EQ(Time(0, 1, 0, 0), epwFile.timeStep());
  EXPECT_EQ(DayOfWeek(DayOfWeek::Friday), epwFile.startDayOfWeek());
  ASSERT_TRUE(epwFile.startDateActualYear());
  EXPECT_EQ(1999, epwFile.startDateActualYear().get());
  ASSERT_TRUE(epwFile.endDateActualYear());
  EXPECT_EQ(1999, epwFile.endDateActualYear().get());
  EXPECT_EQ(Date(MonthOfYear::Jan, 1, 1999), epwFile.startDate());
  EXPECT_EQ(Date(MonthOfYear::Dec, 31, 1999), epwFile.endDate());
  EXPECT_EQ(365, (epwFile.endDate() - epwFile.startDate()).totalDays() + 1);
  EXPECT_TRUE(epwFile.isActual());
}

TEST(Filetypes, EpwFile_Wrap_AMY) {
  path p = resourcesPath() / toPath("utilities/Filetypes/USA_CO_Golden-NREL.wrap.amy");
  EpwFile epwFile(p);
  EXPECT_EQ(p, epwFile.path());
  EXPECT_EQ("8F74A20B", epwFile.checksum());
  EXPECT_EQ("Denver Centennial  Golden   Nr", epwFile.city());
  EXPECT_EQ("CO", epwFile.stateProvinceRegion());
  EXPECT_EQ("USA", epwFile.country());
  EXPECT_EQ("TMY3", epwFile.dataSource());
  EXPECT_EQ("724666", epwFile.wmoNumber());
  EXPECT_EQ(39.74, epwFile.latitude());
  EXPECT_EQ(-105.18, epwFile.longitude());
  EXPECT_EQ(-7, epwFile.timeZone());
  EXPECT_EQ(1829, epwFile.elevation());
  EXPECT_EQ(Time(0, 1, 0, 0), epwFile.timeStep());
  EXPECT_EQ(DayOfWeek(DayOfWeek::Saturday), epwFile.startDayOfWeek());
  ASSERT_TRUE(epwFile.startDateActualYear());
  EXPECT_EQ(1999, epwFile.startDateActualYear().get());
  ASSERT_TRUE(epwFile.endDateActualYear());
  EXPECT_EQ(2000, epwFile.endDateActualYear().get());
  EXPECT_EQ(Date(MonthOfYear::Apr, 10, 1999), epwFile.startDate());
  EXPECT_EQ(Date(MonthOfYear::Apr, 8, 2000), epwFile.endDate());  // 2000 is a leap year
  EXPECT_EQ(365, (epwFile.endDate() - epwFile.startDate()).totalDays() + 1);
  EXPECT_TRUE(epwFile.isActual());
}

TEST(Filetypes, EpwFile_DataPoint) {
  // Check that we can read all timeseries wind speed values, even if they are extreme
  path p = resourcesPath() / toPath("utilities/Filetypes/USA_CT_New.Haven-Tweed.AP.725045_TMY3.epw");
  EpwFile epwFile(p);
  EXPECT_EQ(p, epwFile.path());
  for (const EpwDataPoint& dataPoint : epwFile.data()) {
    EXPECT_TRUE(dataPoint.windSpeed());
    //EXPECT_NO_THROW(dataPoint.windSpeed().get());
  }
}

TEST(Filetypes, EpwFile_parseDataPeriods) {

  // I would construct an empty EpwFile to call parseDataPeriods but I can't since it's a private Ctor, and the method itself is private...

  // DATA PERIODS,1,1,Data,Sunday, 1/ 1,1/1 => no year
  // DATA PERIODS has no year. The file is also treated as TMY since both years present in records are not the same, so m_startDateActualYear isn't
  // set in parse
  std::string epwFileStringNoYear = R"(LOCATION,Denver Centennial  Golden   Nr,CO,USA,TMY3,724666,39.74,-105.18,-7.0,1829.0
DESIGN CONDITIONS,1,Climate Design Data 2009 ASHRAE Handbook,,Heating,12,-18.8,-15.5,-21.6,0.7,-10.9,-18.8,0.9,-7.5,12.2,3.9,10.9,3.8,3,340,Cooling,7,15.2,33,15.7,32,15.5,30.2,15.3,18.4,27.3,17.5,26.4,16.8,25.6,4.9,0,16.1,14.3,20.2,14.9,13.2,19.9,13.9,12.3,19.6,59.7,27.3,56.6,26.6,54,25.7,760,Extremes,11.1,9.5,8.4,22.9,-22.9,36.1,3.8,1.2,-25.7,37,-27.9,37.7,-30.1,38.3,-32.8,39.2
TYPICAL/EXTREME PERIODS,6,Summer - Week Nearest Max Temperature For Period,Extreme,7/ 6,7/12,Summer - Week Nearest Average Temperature For Period,Typical,7/27,8/ 2,Winter - Week Nearest Min Temperature For Period,Extreme,12/15,12/21,Winter - Week Nearest Average Temperature For Period,Typical,12/ 1,12/ 7,Autumn - Week Nearest Average Temperature For Period,Typical,10/20,10/26,Spring - Week Nearest Average Temperature For Period,Typical,4/26,5/ 2
GROUND TEMPERATURES,3,.5,,,,-0.60,1.34,5.12,8.69,15.46,19.02,20.00,18.20,14.02,8.83,3.71,0.32,2,,,,2.08,2.55,4.70,7.10,12.30,15.62,17.28,16.91,14.53,10.94,6.90,3.72,4,,,,4.84,4.51,5.45,6.81,10.25,12.82,14.49,14.90,13.86,11.74,9.00,6.53
HOLIDAYS/DAYLIGHT SAVINGS,No,0,0,0
COMMENTS 1,Custom/User Format -- WMO#724666; NREL TMY Data Set (2008); Period of Record 1973-2005 (Generally)
COMMENTS 2, -- Ground temps produced with a standard soil diffusivity of 2.3225760E-03 {m**2/day}
DATA PERIODS,1,1,Data,Sunday, 1/ 1,1/1
1999,1,1,1,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9*9,-3.0,-4.0,92,80600,0,0,257,0,0,0,0,0,0,0,0,0.0,9,8,16.1,3300,9,999999999,89,0.0310,0,88,0.330,999.0,99.0
2005,1,1,2,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9*9,-3.0,-6.0,77,80600,0,0,261,0,0,0,0,0,0,0,170,2.1,10,9,16.1,3000,9,999999999,89,0.0310,0,88,0.330,999.0,99.0
1999,1,1,3,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9*9,-4.0,-7.0,77,80700,0,0,251,0,0,0,0,0,0,0,250,1.5,9,8,16.1,3000,9,999999999,89,0.0310,0,88,0.330,999.0,99.0
1999,1,1,4,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9*9,-2.0,-5.0,78,80700,0,0,273,0,0,0,0,0,0,0,330,1.5,10,10,16.1,2700,9,999999999,89,0.0310,0,88,0.330,999.0,99.0
1999,1,1,5,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9?9?9,-2.0,-4.0,85,80800,0,0,274,0,0,0,0,0,0,0,240,3.6,10,10,12.9,1080,9,999999999,100,0.0310,0,88,0.330,0.0,1.0
1999,1,1,6,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9*9,-1.0,-2.0,92,80900,0,0,280,0,0,0,0,0,0,0,0,0.0,10,10,1.2,150,9,999999999,89,0.0310,0,88,0.330,999.0,99.0
1999,1,1,7,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9*9,-1.0,-1.0,100,81000,0,0,281,0,0,0,0,0,0,0,270,2.6,10,10,1.6,480,9,999999999,89,0.0310,0,88,0.330,999.0,99.0
1999,1,1,8,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9?9?9,-1.0,-1.0,100,81100,41,861,281,4,119,2,906,6725,559,79,260,2.1,10,10,1.6,480,9,999999999,89,0.0310,0,88,0.330,0.0,1.0
1999,1,1,9,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9*9,0.0,-1.0,92,81300,242,1415,272,178,480,95,17449,32960,11774,1860,240,2.6,9,8,6.4,1500,9,999999999,89,0.0310,0,88,0.330,999.0,99.0
1999,1,1,10,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9*9,2.0,-1.0,80,81500,429,1415,294,49,0,49,5871,0,5871,2108,280,2.6,10,10,16.1,1500,9,999999999,89,0.0310,0,88,0.330,999.0,99.0
1999,1,1,11,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9?9?9,2.0,-1.0,80,81500,563,1415,294,431,654,169,44097,62425,19149,3410,10,4.6,10,10,16.1,1500,9,999999999,89,0.0310,0,88,0.330,0.0,6.0
1999,1,1,12,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9*9,1.0,-2.0,79,81500,635,1415,275,326,296,193,34655,30037,21116,4256,10,7.2,8,8,16.1,1500,9,999999999,80,0.0310,0,88,0.330,999.0,99.0
1999,1,1,13,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9*9,3.0,-3.0,63,81600,640,1415,296,255,96,212,28023,9483,23716,5980,360,6.2,10,10,16.1,810,9,999999999,80,0.0310,0,88,0.330,999.0,99.0
1999,1,1,14,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9?9?9,2.0,-4.0,62,81600,577,1415,291,160,12,155,18096,900,17727,5938,20,7.2,10,10,16.1,960,9,999999999,80,0.0310,0,88,0.330,0.0,1.0
1999,1,1,15,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9?9?9,1.0,-4.0,67,81700,452,1415,287,59,0,59,7007,0,7007,2516,20,7.2,10,10,12.9,840,9,999999999,80,0.0310,0,88,0.330,0.0,1.0
1999,1,1,16,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9?9?9,1.0,-4.0,67,81700,272,1415,287,51,0,51,5821,0,5821,1885,360,5.1,10,10,16.1,1020,9,999999999,80,0.0310,0,88,0.330,0.0,1.0
1999,1,1,17,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9*9?9?9?9*9*9?9*9*9,0.0,-3.9,72,81700,62,1073,283,18,170,12,2390,7964,1886,227,10,5.4,10,10,16.1,885,9,999999999,80,0.0310,0,88,0.330,999.0,99.0
1999,1,1,18,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9?9?9,-1.0,-4.0,78,81800,0,0,278,0,0,0,0,0,0,0,10,5.7,10,10,12.9,750,9,999999999,80,0.0310,0,88,0.330,0.0,1.0
1999,1,1,19,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9*9,-2.0,-6.0,71,81800,0,0,272,0,0,0,0,0,0,0,360,5.1,10,10,14.5,750,9,999999999,69,0.0310,0,88,0.330,999.0,99.0
1999,1,1,20,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9?9?9,-4.0,-8.0,71,81800,0,0,262,0,0,0,0,0,0,0,20,8.2,10,10,14.5,480,9,999999999,69,0.0310,0,88,0.330,0.0,1.0
1999,1,1,21,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9?9?9,-5.0,-7.0,84,81800,0,0,260,0,0,0,0,0,0,0,10,5.1,10,10,2.8,330,9,999999999,69,0.0310,0,88,0.330,0.0,1.0
1999,1,1,22,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9?9?9,-6.0,-6.0,100,81800,0,0,257,0,0,0,0,0,0,0,10,3.6,10,10,1.2,210,9,999999999,69,0.0310,0,88,0.330,0.0,1.0
1999,1,1,23,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9*9,-7.0,-9.0,84,81800,0,0,250,0,0,0,0,0,0,0,30,6.7,10,10,1.2,150,9,999999999,69,0.0310,0,88,0.330,999.0,99.0
1999,1,1,24,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9*9,-7.0,-9.0,84,81700,0,0,250,0,0,0,0,0,0,0,30,6.7,10,10,1.2,150,9,999999999,69,0.0310,0,88,0.330,999.0,99.0
)";

  boost::optional<EpwFile> _epwFile = EpwFile::loadFromString(epwFileStringNoYear);
  ASSERT_TRUE(_epwFile);
  EXPECT_FALSE(_epwFile->startDateActualYear());

  // DATA PERIODS,1,1,Data,Sunday, 1/ 1/2012,1/1/2012 => includes the year
  std::string epwFileStringWithYear = R"(LOCATION,Denver Centennial  Golden   Nr,CO,USA,TMY3,724666,39.74,-105.18,-7.0,1829.0
DESIGN CONDITIONS,1,Climate Design Data 2009 ASHRAE Handbook,,Heating,12,-18.8,-15.5,-21.6,0.7,-10.9,-18.8,0.9,-7.5,12.2,3.9,10.9,3.8,3,340,Cooling,7,15.2,33,15.7,32,15.5,30.2,15.3,18.4,27.3,17.5,26.4,16.8,25.6,4.9,0,16.1,14.3,20.2,14.9,13.2,19.9,13.9,12.3,19.6,59.7,27.3,56.6,26.6,54,25.7,760,Extremes,11.1,9.5,8.4,22.9,-22.9,36.1,3.8,1.2,-25.7,37,-27.9,37.7,-30.1,38.3,-32.8,39.2
TYPICAL/EXTREME PERIODS,6,Summer - Week Nearest Max Temperature For Period,Extreme,7/ 6,7/12,Summer - Week Nearest Average Temperature For Period,Typical,7/27,8/ 2,Winter - Week Nearest Min Temperature For Period,Extreme,12/15,12/21,Winter - Week Nearest Average Temperature For Period,Typical,12/ 1,12/ 7,Autumn - Week Nearest Average Temperature For Period,Typical,10/20,10/26,Spring - Week Nearest Average Temperature For Period,Typical,4/26,5/ 2
GROUND TEMPERATURES,3,.5,,,,-0.60,1.34,5.12,8.69,15.46,19.02,20.00,18.20,14.02,8.83,3.71,0.32,2,,,,2.08,2.55,4.70,7.10,12.30,15.62,17.28,16.91,14.53,10.94,6.90,3.72,4,,,,4.84,4.51,5.45,6.81,10.25,12.82,14.49,14.90,13.86,11.74,9.00,6.53
HOLIDAYS/DAYLIGHT SAVINGS,No,0,0,0
COMMENTS 1,Custom/User Format -- WMO#724666; NREL TMY Data Set (2008); Period of Record 1973-2005 (Generally)
COMMENTS 2, -- Ground temps produced with a standard soil diffusivity of 2.3225760E-03 {m**2/day}
DATA PERIODS,1,1,Data,Sunday, 1/ 1/2012,1/1/2012
1999,1,1,1,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9*9,-3.0,-4.0,92,80600,0,0,257,0,0,0,0,0,0,0,0,0.0,9,8,16.1,3300,9,999999999,89,0.0310,0,88,0.330,999.0,99.0
2005,1,1,2,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9*9,-3.0,-6.0,77,80600,0,0,261,0,0,0,0,0,0,0,170,2.1,10,9,16.1,3000,9,999999999,89,0.0310,0,88,0.330,999.0,99.0
1999,1,1,3,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9*9,-4.0,-7.0,77,80700,0,0,251,0,0,0,0,0,0,0,250,1.5,9,8,16.1,3000,9,999999999,89,0.0310,0,88,0.330,999.0,99.0
1999,1,1,4,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9*9,-2.0,-5.0,78,80700,0,0,273,0,0,0,0,0,0,0,330,1.5,10,10,16.1,2700,9,999999999,89,0.0310,0,88,0.330,999.0,99.0
1999,1,1,5,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9?9?9,-2.0,-4.0,85,80800,0,0,274,0,0,0,0,0,0,0,240,3.6,10,10,12.9,1080,9,999999999,100,0.0310,0,88,0.330,0.0,1.0
1999,1,1,6,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9*9,-1.0,-2.0,92,80900,0,0,280,0,0,0,0,0,0,0,0,0.0,10,10,1.2,150,9,999999999,89,0.0310,0,88,0.330,999.0,99.0
1999,1,1,7,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9*9,-1.0,-1.0,100,81000,0,0,281,0,0,0,0,0,0,0,270,2.6,10,10,1.6,480,9,999999999,89,0.0310,0,88,0.330,999.0,99.0
1999,1,1,8,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9?9?9,-1.0,-1.0,100,81100,41,861,281,4,119,2,906,6725,559,79,260,2.1,10,10,1.6,480,9,999999999,89,0.0310,0,88,0.330,0.0,1.0
1999,1,1,9,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9*9,0.0,-1.0,92,81300,242,1415,272,178,480,95,17449,32960,11774,1860,240,2.6,9,8,6.4,1500,9,999999999,89,0.0310,0,88,0.330,999.0,99.0
1999,1,1,10,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9*9,2.0,-1.0,80,81500,429,1415,294,49,0,49,5871,0,5871,2108,280,2.6,10,10,16.1,1500,9,999999999,89,0.0310,0,88,0.330,999.0,99.0
1999,1,1,11,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9?9?9,2.0,-1.0,80,81500,563,1415,294,431,654,169,44097,62425,19149,3410,10,4.6,10,10,16.1,1500,9,999999999,89,0.0310,0,88,0.330,0.0,6.0
1999,1,1,12,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9*9,1.0,-2.0,79,81500,635,1415,275,326,296,193,34655,30037,21116,4256,10,7.2,8,8,16.1,1500,9,999999999,80,0.0310,0,88,0.330,999.0,99.0
1999,1,1,13,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9*9,3.0,-3.0,63,81600,640,1415,296,255,96,212,28023,9483,23716,5980,360,6.2,10,10,16.1,810,9,999999999,80,0.0310,0,88,0.330,999.0,99.0
1999,1,1,14,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9?9?9,2.0,-4.0,62,81600,577,1415,291,160,12,155,18096,900,17727,5938,20,7.2,10,10,16.1,960,9,999999999,80,0.0310,0,88,0.330,0.0,1.0
1999,1,1,15,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9?9?9,1.0,-4.0,67,81700,452,1415,287,59,0,59,7007,0,7007,2516,20,7.2,10,10,12.9,840,9,999999999,80,0.0310,0,88,0.330,0.0,1.0
1999,1,1,16,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9?9?9,1.0,-4.0,67,81700,272,1415,287,51,0,51,5821,0,5821,1885,360,5.1,10,10,16.1,1020,9,999999999,80,0.0310,0,88,0.330,0.0,1.0
1999,1,1,17,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9*9?9?9?9*9*9?9*9*9,0.0,-3.9,72,81700,62,1073,283,18,170,12,2390,7964,1886,227,10,5.4,10,10,16.1,885,9,999999999,80,0.0310,0,88,0.330,999.0,99.0
1999,1,1,18,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9?9?9,-1.0,-4.0,78,81800,0,0,278,0,0,0,0,0,0,0,10,5.7,10,10,12.9,750,9,999999999,80,0.0310,0,88,0.330,0.0,1.0
1999,1,1,19,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9*9,-2.0,-6.0,71,81800,0,0,272,0,0,0,0,0,0,0,360,5.1,10,10,14.5,750,9,999999999,69,0.0310,0,88,0.330,999.0,99.0
1999,1,1,20,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9?9?9,-4.0,-8.0,71,81800,0,0,262,0,0,0,0,0,0,0,20,8.2,10,10,14.5,480,9,999999999,69,0.0310,0,88,0.330,0.0,1.0
1999,1,1,21,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9?9?9,-5.0,-7.0,84,81800,0,0,260,0,0,0,0,0,0,0,10,5.1,10,10,2.8,330,9,999999999,69,0.0310,0,88,0.330,0.0,1.0
1999,1,1,22,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9?9?9,-6.0,-6.0,100,81800,0,0,257,0,0,0,0,0,0,0,10,3.6,10,10,1.2,210,9,999999999,69,0.0310,0,88,0.330,0.0,1.0
1999,1,1,23,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9*9,-7.0,-9.0,84,81800,0,0,250,0,0,0,0,0,0,0,30,6.7,10,10,1.2,150,9,999999999,69,0.0310,0,88,0.330,999.0,99.0
1999,1,1,24,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9*9,-7.0,-9.0,84,81700,0,0,250,0,0,0,0,0,0,0,30,6.7,10,10,1.2,150,9,999999999,69,0.0310,0,88,0.330,999.0,99.0
)";

  // parseDataPeriods should have set m_startDateActualYear
  _epwFile = EpwFile::loadFromString(epwFileStringWithYear);
  ASSERT_TRUE(_epwFile);
  ASSERT_TRUE(_epwFile->startDateActualYear());
  EXPECT_EQ(2012, _epwFile->startDateActualYear().get());
}

TEST(Filetypes, EpwFile_parseHolidaysDaylightSavings) {

  // I would construct an empty EpwFile to call parseDataPeriods but I can't since it's a private Ctor, and the method itself is private...

  // Typical: nothing included (that's the case for ALL weather files on EnergyPlus.net)
  // HOLIDAYS/DAYLIGHT SAVINGS,No,0,0,0
  std::string epwFileStringNoHolidaysDaylightSavings = R"(LOCATION,Denver Centennial  Golden   Nr,CO,USA,TMY3,724666,39.74,-105.18,-7.0,1829.0
DESIGN CONDITIONS,1,Climate Design Data 2009 ASHRAE Handbook,,Heating,12,-18.8,-15.5,-21.6,0.7,-10.9,-18.8,0.9,-7.5,12.2,3.9,10.9,3.8,3,340,Cooling,7,15.2,33,15.7,32,15.5,30.2,15.3,18.4,27.3,17.5,26.4,16.8,25.6,4.9,0,16.1,14.3,20.2,14.9,13.2,19.9,13.9,12.3,19.6,59.7,27.3,56.6,26.6,54,25.7,760,Extremes,11.1,9.5,8.4,22.9,-22.9,36.1,3.8,1.2,-25.7,37,-27.9,37.7,-30.1,38.3,-32.8,39.2
TYPICAL/EXTREME PERIODS,6,Summer - Week Nearest Max Temperature For Period,Extreme,7/ 6,7/12,Summer - Week Nearest Average Temperature For Period,Typical,7/27,8/ 2,Winter - Week Nearest Min Temperature For Period,Extreme,12/15,12/21,Winter - Week Nearest Average Temperature For Period,Typical,12/ 1,12/ 7,Autumn - Week Nearest Average Temperature For Period,Typical,10/20,10/26,Spring - Week Nearest Average Temperature For Period,Typical,4/26,5/ 2
GROUND TEMPERATURES,3,.5,,,,-0.60,1.34,5.12,8.69,15.46,19.02,20.00,18.20,14.02,8.83,3.71,0.32,2,,,,2.08,2.55,4.70,7.10,12.30,15.62,17.28,16.91,14.53,10.94,6.90,3.72,4,,,,4.84,4.51,5.45,6.81,10.25,12.82,14.49,14.90,13.86,11.74,9.00,6.53
HOLIDAYS/DAYLIGHT SAVINGS,No,0,0,0
COMMENTS 1,Custom/User Format -- WMO#724666; NREL TMY Data Set (2008); Period of Record 1973-2005 (Generally)
COMMENTS 2, -- Ground temps produced with a standard soil diffusivity of 2.3225760E-03 {m**2/day}
DATA PERIODS,1,1,Data,Sunday, 1/ 1,1/1
1999,1,1,1,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9*9,-3.0,-4.0,92,80600,0,0,257,0,0,0,0,0,0,0,0,0.0,9,8,16.1,3300,9,999999999,89,0.0310,0,88,0.330,999.0,99.0
2005,1,1,2,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9*9,-3.0,-6.0,77,80600,0,0,261,0,0,0,0,0,0,0,170,2.1,10,9,16.1,3000,9,999999999,89,0.0310,0,88,0.330,999.0,99.0
1999,1,1,3,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9*9,-4.0,-7.0,77,80700,0,0,251,0,0,0,0,0,0,0,250,1.5,9,8,16.1,3000,9,999999999,89,0.0310,0,88,0.330,999.0,99.0
1999,1,1,4,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9*9,-2.0,-5.0,78,80700,0,0,273,0,0,0,0,0,0,0,330,1.5,10,10,16.1,2700,9,999999999,89,0.0310,0,88,0.330,999.0,99.0
1999,1,1,5,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9?9?9,-2.0,-4.0,85,80800,0,0,274,0,0,0,0,0,0,0,240,3.6,10,10,12.9,1080,9,999999999,100,0.0310,0,88,0.330,0.0,1.0
1999,1,1,6,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9*9,-1.0,-2.0,92,80900,0,0,280,0,0,0,0,0,0,0,0,0.0,10,10,1.2,150,9,999999999,89,0.0310,0,88,0.330,999.0,99.0
1999,1,1,7,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9*9,-1.0,-1.0,100,81000,0,0,281,0,0,0,0,0,0,0,270,2.6,10,10,1.6,480,9,999999999,89,0.0310,0,88,0.330,999.0,99.0
1999,1,1,8,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9?9?9,-1.0,-1.0,100,81100,41,861,281,4,119,2,906,6725,559,79,260,2.1,10,10,1.6,480,9,999999999,89,0.0310,0,88,0.330,0.0,1.0
1999,1,1,9,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9*9,0.0,-1.0,92,81300,242,1415,272,178,480,95,17449,32960,11774,1860,240,2.6,9,8,6.4,1500,9,999999999,89,0.0310,0,88,0.330,999.0,99.0
1999,1,1,10,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9*9,2.0,-1.0,80,81500,429,1415,294,49,0,49,5871,0,5871,2108,280,2.6,10,10,16.1,1500,9,999999999,89,0.0310,0,88,0.330,999.0,99.0
1999,1,1,11,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9?9?9,2.0,-1.0,80,81500,563,1415,294,431,654,169,44097,62425,19149,3410,10,4.6,10,10,16.1,1500,9,999999999,89,0.0310,0,88,0.330,0.0,6.0
1999,1,1,12,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9*9,1.0,-2.0,79,81500,635,1415,275,326,296,193,34655,30037,21116,4256,10,7.2,8,8,16.1,1500,9,999999999,80,0.0310,0,88,0.330,999.0,99.0
1999,1,1,13,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9*9,3.0,-3.0,63,81600,640,1415,296,255,96,212,28023,9483,23716,5980,360,6.2,10,10,16.1,810,9,999999999,80,0.0310,0,88,0.330,999.0,99.0
1999,1,1,14,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9?9?9,2.0,-4.0,62,81600,577,1415,291,160,12,155,18096,900,17727,5938,20,7.2,10,10,16.1,960,9,999999999,80,0.0310,0,88,0.330,0.0,1.0
1999,1,1,15,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9?9?9,1.0,-4.0,67,81700,452,1415,287,59,0,59,7007,0,7007,2516,20,7.2,10,10,12.9,840,9,999999999,80,0.0310,0,88,0.330,0.0,1.0
1999,1,1,16,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9?9?9,1.0,-4.0,67,81700,272,1415,287,51,0,51,5821,0,5821,1885,360,5.1,10,10,16.1,1020,9,999999999,80,0.0310,0,88,0.330,0.0,1.0
1999,1,1,17,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9*9?9?9?9*9*9?9*9*9,0.0,-3.9,72,81700,62,1073,283,18,170,12,2390,7964,1886,227,10,5.4,10,10,16.1,885,9,999999999,80,0.0310,0,88,0.330,999.0,99.0
1999,1,1,18,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9?9?9,-1.0,-4.0,78,81800,0,0,278,0,0,0,0,0,0,0,10,5.7,10,10,12.9,750,9,999999999,80,0.0310,0,88,0.330,0.0,1.0
1999,1,1,19,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9*9,-2.0,-6.0,71,81800,0,0,272,0,0,0,0,0,0,0,360,5.1,10,10,14.5,750,9,999999999,69,0.0310,0,88,0.330,999.0,99.0
1999,1,1,20,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9?9?9,-4.0,-8.0,71,81800,0,0,262,0,0,0,0,0,0,0,20,8.2,10,10,14.5,480,9,999999999,69,0.0310,0,88,0.330,0.0,1.0
1999,1,1,21,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9?9?9,-5.0,-7.0,84,81800,0,0,260,0,0,0,0,0,0,0,10,5.1,10,10,2.8,330,9,999999999,69,0.0310,0,88,0.330,0.0,1.0
1999,1,1,22,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9?9?9,-6.0,-6.0,100,81800,0,0,257,0,0,0,0,0,0,0,10,3.6,10,10,1.2,210,9,999999999,69,0.0310,0,88,0.330,0.0,1.0
1999,1,1,23,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9*9,-7.0,-9.0,84,81800,0,0,250,0,0,0,0,0,0,0,30,6.7,10,10,1.2,150,9,999999999,69,0.0310,0,88,0.330,999.0,99.0
1999,1,1,24,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9*9,-7.0,-9.0,84,81700,0,0,250,0,0,0,0,0,0,0,30,6.7,10,10,1.2,150,9,999999999,69,0.0310,0,88,0.330,999.0,99.0
)";

  boost::optional<EpwFile> _epwFile = EpwFile::loadFromString(epwFileStringNoHolidaysDaylightSavings);
  ASSERT_TRUE(_epwFile);
  EXPECT_FALSE(_epwFile->daylightSavingStartDate());
  EXPECT_FALSE(_epwFile->daylightSavingEndDate());
  std::vector<EpwHoliday> holidays = _epwFile->holidays();
  EXPECT_TRUE(holidays.empty());

  // Taken from NREL/EnergyPlus: weather/Drycold_blast.epw
  // HOLIDAYS/DAYLIGHT SAVINGS,No, 4/29,10/28,9,Hol:001, 1/ 1,Hol:002, 2/19,Hol:003, 5/28,Hol:004, 7/ 4,Hol:005, 9/ 3,Hol:006,10/ 8,Hol:007,11/12,Hol:008,11/22,Hol:009,12/25
  std::string epwFileStringWithHolidaysDaylightSavings = R"(LOCATION,Denver Centennial  Golden   Nr,CO,USA,TMY3,724666,39.74,-105.18,-7.0,1829.0
DESIGN CONDITIONS,1,Climate Design Data 2009 ASHRAE Handbook,,Heating,12,-18.8,-15.5,-21.6,0.7,-10.9,-18.8,0.9,-7.5,12.2,3.9,10.9,3.8,3,340,Cooling,7,15.2,33,15.7,32,15.5,30.2,15.3,18.4,27.3,17.5,26.4,16.8,25.6,4.9,0,16.1,14.3,20.2,14.9,13.2,19.9,13.9,12.3,19.6,59.7,27.3,56.6,26.6,54,25.7,760,Extremes,11.1,9.5,8.4,22.9,-22.9,36.1,3.8,1.2,-25.7,37,-27.9,37.7,-30.1,38.3,-32.8,39.2
TYPICAL/EXTREME PERIODS,6,Summer - Week Nearest Max Temperature For Period,Extreme,7/ 6,7/12,Summer - Week Nearest Average Temperature For Period,Typical,7/27,8/ 2,Winter - Week Nearest Min Temperature For Period,Extreme,12/15,12/21,Winter - Week Nearest Average Temperature For Period,Typical,12/ 1,12/ 7,Autumn - Week Nearest Average Temperature For Period,Typical,10/20,10/26,Spring - Week Nearest Average Temperature For Period,Typical,4/26,5/ 2
GROUND TEMPERATURES,3,.5,,,,-0.60,1.34,5.12,8.69,15.46,19.02,20.00,18.20,14.02,8.83,3.71,0.32,2,,,,2.08,2.55,4.70,7.10,12.30,15.62,17.28,16.91,14.53,10.94,6.90,3.72,4,,,,4.84,4.51,5.45,6.81,10.25,12.82,14.49,14.90,13.86,11.74,9.00,6.53
HOLIDAYS/DAYLIGHT SAVINGS,No, 4/29,10/28,9,Hol:001, 1/ 1,Hol:002, 2/19,Hol:003, 5/28,Hol:004, 7/ 4,Hol:005, 9/ 3,Hol:006,10/ 8,Hol:007,11/12,Hol:008,11/22,Hol:009,12/25
COMMENTS 1,Custom/User Format -- WMO#724666; NREL TMY Data Set (2008); Period of Record 1973-2005 (Generally)
COMMENTS 2, -- Ground temps produced with a standard soil diffusivity of 2.3225760E-03 {m**2/day}
DATA PERIODS,1,1,Data,Sunday, 1/ 1,1/1
1999,1,1,1,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9*9,-3.0,-4.0,92,80600,0,0,257,0,0,0,0,0,0,0,0,0.0,9,8,16.1,3300,9,999999999,89,0.0310,0,88,0.330,999.0,99.0
2005,1,1,2,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9*9,-3.0,-6.0,77,80600,0,0,261,0,0,0,0,0,0,0,170,2.1,10,9,16.1,3000,9,999999999,89,0.0310,0,88,0.330,999.0,99.0
1999,1,1,3,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9*9,-4.0,-7.0,77,80700,0,0,251,0,0,0,0,0,0,0,250,1.5,9,8,16.1,3000,9,999999999,89,0.0310,0,88,0.330,999.0,99.0
1999,1,1,4,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9*9,-2.0,-5.0,78,80700,0,0,273,0,0,0,0,0,0,0,330,1.5,10,10,16.1,2700,9,999999999,89,0.0310,0,88,0.330,999.0,99.0
1999,1,1,5,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9?9?9,-2.0,-4.0,85,80800,0,0,274,0,0,0,0,0,0,0,240,3.6,10,10,12.9,1080,9,999999999,100,0.0310,0,88,0.330,0.0,1.0
1999,1,1,6,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9*9,-1.0,-2.0,92,80900,0,0,280,0,0,0,0,0,0,0,0,0.0,10,10,1.2,150,9,999999999,89,0.0310,0,88,0.330,999.0,99.0
1999,1,1,7,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9*9,-1.0,-1.0,100,81000,0,0,281,0,0,0,0,0,0,0,270,2.6,10,10,1.6,480,9,999999999,89,0.0310,0,88,0.330,999.0,99.0
1999,1,1,8,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9?9?9,-1.0,-1.0,100,81100,41,861,281,4,119,2,906,6725,559,79,260,2.1,10,10,1.6,480,9,999999999,89,0.0310,0,88,0.330,0.0,1.0
1999,1,1,9,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9*9,0.0,-1.0,92,81300,242,1415,272,178,480,95,17449,32960,11774,1860,240,2.6,9,8,6.4,1500,9,999999999,89,0.0310,0,88,0.330,999.0,99.0
1999,1,1,10,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9*9,2.0,-1.0,80,81500,429,1415,294,49,0,49,5871,0,5871,2108,280,2.6,10,10,16.1,1500,9,999999999,89,0.0310,0,88,0.330,999.0,99.0
1999,1,1,11,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9?9?9,2.0,-1.0,80,81500,563,1415,294,431,654,169,44097,62425,19149,3410,10,4.6,10,10,16.1,1500,9,999999999,89,0.0310,0,88,0.330,0.0,6.0
1999,1,1,12,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9*9,1.0,-2.0,79,81500,635,1415,275,326,296,193,34655,30037,21116,4256,10,7.2,8,8,16.1,1500,9,999999999,80,0.0310,0,88,0.330,999.0,99.0
1999,1,1,13,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9*9,3.0,-3.0,63,81600,640,1415,296,255,96,212,28023,9483,23716,5980,360,6.2,10,10,16.1,810,9,999999999,80,0.0310,0,88,0.330,999.0,99.0
1999,1,1,14,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9?9?9,2.0,-4.0,62,81600,577,1415,291,160,12,155,18096,900,17727,5938,20,7.2,10,10,16.1,960,9,999999999,80,0.0310,0,88,0.330,0.0,1.0
1999,1,1,15,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9?9?9,1.0,-4.0,67,81700,452,1415,287,59,0,59,7007,0,7007,2516,20,7.2,10,10,12.9,840,9,999999999,80,0.0310,0,88,0.330,0.0,1.0
1999,1,1,16,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9?9?9,1.0,-4.0,67,81700,272,1415,287,51,0,51,5821,0,5821,1885,360,5.1,10,10,16.1,1020,9,999999999,80,0.0310,0,88,0.330,0.0,1.0
1999,1,1,17,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9*9?9?9?9*9*9?9*9*9,0.0,-3.9,72,81700,62,1073,283,18,170,12,2390,7964,1886,227,10,5.4,10,10,16.1,885,9,999999999,80,0.0310,0,88,0.330,999.0,99.0
1999,1,1,18,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9?9?9,-1.0,-4.0,78,81800,0,0,278,0,0,0,0,0,0,0,10,5.7,10,10,12.9,750,9,999999999,80,0.0310,0,88,0.330,0.0,1.0
1999,1,1,19,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9*9,-2.0,-6.0,71,81800,0,0,272,0,0,0,0,0,0,0,360,5.1,10,10,14.5,750,9,999999999,69,0.0310,0,88,0.330,999.0,99.0
1999,1,1,20,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9?9?9,-4.0,-8.0,71,81800,0,0,262,0,0,0,0,0,0,0,20,8.2,10,10,14.5,480,9,999999999,69,0.0310,0,88,0.330,0.0,1.0
1999,1,1,21,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9?9?9,-5.0,-7.0,84,81800,0,0,260,0,0,0,0,0,0,0,10,5.1,10,10,2.8,330,9,999999999,69,0.0310,0,88,0.330,0.0,1.0
1999,1,1,22,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9?9?9,-6.0,-6.0,100,81800,0,0,257,0,0,0,0,0,0,0,10,3.6,10,10,1.2,210,9,999999999,69,0.0310,0,88,0.330,0.0,1.0
1999,1,1,23,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9*9,-7.0,-9.0,84,81800,0,0,250,0,0,0,0,0,0,0,30,6.7,10,10,1.2,150,9,999999999,69,0.0310,0,88,0.330,999.0,99.0
1999,1,1,24,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9*9,-7.0,-9.0,84,81700,0,0,250,0,0,0,0,0,0,0,30,6.7,10,10,1.2,150,9,999999999,69,0.0310,0,88,0.330,999.0,99.0
)";

  _epwFile = EpwFile::loadFromString(epwFileStringWithHolidaysDaylightSavings);
  ASSERT_TRUE(_epwFile);
  // Daylight: 4/29,10/28
  ASSERT_TRUE(_epwFile->daylightSavingStartDate());
  Date expectedStartDate(openstudio::monthOfYear(4), 29);
  EXPECT_EQ(expectedStartDate, _epwFile->daylightSavingStartDate().get());
  ASSERT_TRUE(_epwFile->daylightSavingEndDate());
  Date expectedEndDate(openstudio::monthOfYear(10), 28);
  EXPECT_EQ(expectedEndDate, _epwFile->daylightSavingEndDate().get());

  holidays = _epwFile->holidays();
  EXPECT_FALSE(holidays.empty());
  EXPECT_EQ(9u, holidays.size());

  std::vector<std::pair<std::string, std::string>> expectedResult = {
    {"Hol:001", "1/ 1"},  {"Hol:002", "2/19"},  {"Hol:003", "5/28"},  {"Hol:004", "7/ 4"},  {"Hol:005", "9/ 3"},
    {"Hol:006", "10/ 8"}, {"Hol:007", "11/12"}, {"Hol:008", "11/22"}, {"Hol:009", "12/25"},
  };

  int i = 0;
  for (const EpwHoliday& holiday : holidays) {
    EXPECT_EQ(expectedResult[i].first, holiday.holidayName());
    EXPECT_EQ(expectedResult[i].second, holiday.holidayDateString());
    ++i;
  }
}

TEST(Filetypes, EpwDesignCondition_HoF_2009) {

  const std::string line = "Climate Design Data 2009 ASHRAE Handbook,,"
                           "Heating,12,-18.8,-15.5,-21.6,0.7,-10.9,-18.8,0.9,-7.5,12.2,3.9,10.9,3.8,3,340,"
                           "Cooling,7,15.2,33,15.7,32,15.5,30.2,15.3,18.4,27.3,17.5,26.4,16.8,25.6,4.9,0,16.1,14.3,20.2,14.9,13.2,19.9,13.9,12.3,"
                           "19.6,59.7,27.3,56.6,26.6,54,25.7,760,"
                           "Extremes,11.1,9.5,8.4,22.9,-22.9,36.1,3.8,1.2,-25.7,37,-27.9,37.7,-30.1,38.3,-32.8,39.2";
  auto dc_ = EpwDesignCondition::fromDesignConditionsString(line);
  ASSERT_TRUE(dc_);
  const auto dc = std::move(*dc_);

  EXPECT_EQ(dc.ashraeHoFVersion(), ASHRAEHoFVintage::ASHRAE_2009);

  EXPECT_EQ("Climate Design Data 2009 ASHRAE Handbook", dc.titleOfDesignCondition());
  EXPECT_EQ(12, dc.heatingColdestMonth().get());
  EXPECT_EQ(-18.8, dc.heatingDryBulb99pt6().get());
  EXPECT_EQ(-18.8, dc.getFieldByName("Heating Dry Bulb Temperature 99.6%").get());
  EXPECT_EQ(-18.8, dc.getField(EpwDesignField("Heating Dry Bulb Temperature 99.6%")).get());
  EXPECT_EQ("C", dc.getUnitsByName("Heating Dry Bulb Temperature 99.6%").get());
  EXPECT_EQ("C", dc.getUnits(EpwDesignField("Heating Dry Bulb Temperature 99.6%")));
  EXPECT_EQ(-15.5, dc.heatingDryBulb99().get());
  EXPECT_EQ(-21.6, dc.heatingHumidificationDewPoint99pt6().get());
  EXPECT_EQ(0.7, dc.heatingHumidificationHumidityRatio99pt6().get());
  EXPECT_EQ(-10.9, dc.heatingHumidificationMeanCoincidentDryBulb99pt6().get());
  EXPECT_EQ(-18.8, dc.heatingHumidificationDewPoint99().get());
  EXPECT_EQ(0.9, dc.heatingHumidificationHumidityRatio99().get());
  EXPECT_EQ(-7.5, dc.heatingHumidificationMeanCoincidentDryBulb99().get());
  EXPECT_EQ(12.2, dc.heatingColdestMonthWindSpeed0pt4().get());
  EXPECT_EQ(3.9, dc.heatingColdestMonthMeanCoincidentDryBulb0pt4().get());
  EXPECT_EQ(10.9, dc.heatingColdestMonthWindSpeed1().get());
  EXPECT_EQ(3.8, dc.heatingColdestMonthMeanCoincidentDryBulb1().get());
  EXPECT_EQ(3.0, dc.heatingMeanCoincidentWindSpeed99pt6().get());
  EXPECT_EQ(340, dc.heatingPrevailingCoincidentWindDirection99pt6().get());
  EXPECT_FALSE(dc.heatingWindShelterFactor());

  EXPECT_EQ(7, dc.coolingHottestMonth().get());
  EXPECT_EQ(15.2, dc.coolingDryBulbRange().get());
  EXPECT_EQ(33.0, dc.coolingDryBulb0pt4().get());
  EXPECT_EQ(15.7, dc.coolingMeanCoincidentWetBulb0pt4().get());
  EXPECT_EQ(32.0, dc.coolingDryBulb1().get());
  EXPECT_EQ(15.5, dc.coolingMeanCoincidentWetBulb1().get());
  EXPECT_EQ(30.2, dc.coolingDryBulb2().get());
  EXPECT_EQ(15.3, dc.coolingMeanCoincidentWetBulb2().get());
  EXPECT_EQ(18.4, dc.coolingEvaporationWetBulb0pt4().get());
  EXPECT_EQ(27.3, dc.coolingEvaporationMeanCoincidentDryBulb0pt4().get());
  EXPECT_EQ(17.5, dc.coolingEvaporationWetBulb1().get());
  EXPECT_EQ(26.4, dc.coolingEvaporationMeanCoincidentDryBulb1().get());
  EXPECT_EQ(16.8, dc.coolingEvaporationWetBulb2().get());
  EXPECT_EQ(25.6, dc.coolingEvaporationMeanCoincidentDryBulb2().get());
  EXPECT_EQ(4.9, dc.coolingMeanCoincidentWindSpeed0pt4().get());
  EXPECT_EQ(0, dc.coolingPrevailingCoincidentWindDirection0pt4().get());
  EXPECT_EQ(16.1, dc.coolingDehumidificationDewPoint0pt4().get());
  EXPECT_EQ(14.3, dc.coolingDehumidificationHumidityRatio0pt4().get());
  EXPECT_EQ(20.2, dc.coolingDehumidificationMeanCoincidentDryBulb0pt4().get());
  EXPECT_EQ(14.9, dc.coolingDehumidificationDewPoint1().get());
  EXPECT_EQ(13.2, dc.coolingDehumidificationHumidityRatio1().get());
  EXPECT_EQ(19.9, dc.coolingDehumidificationMeanCoincidentDryBulb1().get());
  EXPECT_EQ(13.9, dc.coolingDehumidificationDewPoint2().get());
  EXPECT_EQ(12.3, dc.coolingDehumidificationHumidityRatio2().get());
  EXPECT_EQ(19.6, dc.coolingDehumidificationMeanCoincidentDryBulb2().get());
  EXPECT_EQ(59.7, dc.coolingEnthalpy0pt4().get());
  EXPECT_EQ(27.3, dc.coolingEnthalpyMeanCoincidentDryBulb0pt4().get());
  EXPECT_EQ(56.6, dc.coolingEnthalpy1().get());
  EXPECT_EQ(26.6, dc.coolingEnthalpyMeanCoincidentDryBulb1().get());
  EXPECT_EQ(54.0, dc.coolingEnthalpy2().get());
  EXPECT_EQ(25.7, dc.coolingEnthalpyMeanCoincidentDryBulb2().get());

  ASSERT_TRUE(dc.coolingHours8To4AndDryBulb12pt8To20pt6());
  EXPECT_EQ(760, dc.coolingHours8To4AndDryBulb12pt8To20pt6().get());

  EXPECT_EQ(11.1, dc.extremeWindSpeed1().get());
  EXPECT_EQ(9.5, dc.extremeWindSpeed2pt5().get());
  EXPECT_EQ(8.4, dc.extremeWindSpeed5().get());

  ASSERT_TRUE(dc.coolingExtremeMaxWetBulb());
  EXPECT_EQ(22.9, dc.coolingExtremeMaxWetBulb().get());
  ASSERT_TRUE(dc.extremeMaxWetBulb());
  EXPECT_EQ(22.9, dc.extremeMaxWetBulb().get());

  EXPECT_EQ(-22.9, dc.extremeMeanMinDryBulb().get());
  EXPECT_EQ(36.1, dc.extremeMeanMaxDryBulb().get());
  EXPECT_EQ(3.8, dc.extremeStdDevMinDryBulb().get());
  EXPECT_EQ(1.2, dc.extremeStdDevMaxDryBulb().get());
  EXPECT_EQ(-25.7, dc.extremeN5YearsMinDryBulb().get());
  EXPECT_EQ(37.0, dc.extremeN5YearsMaxDryBulb().get());
  EXPECT_EQ(-27.9, dc.extremeN10YearsMinDryBulb().get());
  EXPECT_EQ(37.7, dc.extremeN10YearsMaxDryBulb().get());
  EXPECT_EQ(-30.1, dc.extremeN20YearsMinDryBulb().get());
  EXPECT_EQ(38.3, dc.extremeN20YearsMaxDryBulb().get());
  EXPECT_EQ(-32.8, dc.extremeN50YearsMinDryBulb().get());
  EXPECT_EQ(39.2, dc.extremeN50YearsMaxDryBulb().get());
}

TEST(Filetypes, EpwDesignCondition_HoF_2009_Heuristics) {

  const std::string line = "This title does not include the version,,"
                           "Heating,12,-18.8,-15.5,-21.6,0.7,-10.9,-18.8,0.9,-7.5,12.2,3.9,10.9,3.8,3,340,"
                           "Cooling,7,15.2,33,15.7,32,15.5,30.2,15.3,18.4,27.3,17.5,26.4,16.8,25.6,4.9,0,16.1,14.3,20.2,14.9,13.2,19.9,13.9,12.3,"
                           "19.6,59.7,27.3,56.6,26.6,54,25.7,760,"
                           "Extremes,11.1,9.5,8.4,22.9,-22.9,36.1,3.8,1.2,-25.7,37,-27.9,37.7,-30.1,38.3,-32.8,39.2";
  auto dc_ = EpwDesignCondition::fromDesignConditionsString(line);
  ASSERT_TRUE(dc_);
  const auto dc = std::move(*dc_);

  EXPECT_EQ(dc.ashraeHoFVersion(), ASHRAEHoFVintage::ASHRAE_2009);

  EXPECT_EQ("This title does not include the version", dc.titleOfDesignCondition());
  EXPECT_EQ(12, dc.heatingColdestMonth().get());
  EXPECT_EQ(-18.8, dc.heatingDryBulb99pt6().get());
  EXPECT_EQ(-18.8, dc.getFieldByName("Heating Dry Bulb Temperature 99.6%").get());
  EXPECT_EQ(-18.8, dc.getField(EpwDesignField("Heating Dry Bulb Temperature 99.6%")).get());
  EXPECT_EQ("C", dc.getUnitsByName("Heating Dry Bulb Temperature 99.6%").get());
  EXPECT_EQ("C", dc.getUnits(EpwDesignField("Heating Dry Bulb Temperature 99.6%")));
  EXPECT_EQ(-15.5, dc.heatingDryBulb99().get());
  EXPECT_EQ(-21.6, dc.heatingHumidificationDewPoint99pt6().get());
  EXPECT_EQ(0.7, dc.heatingHumidificationHumidityRatio99pt6().get());
  EXPECT_EQ(-10.9, dc.heatingHumidificationMeanCoincidentDryBulb99pt6().get());
  EXPECT_EQ(-18.8, dc.heatingHumidificationDewPoint99().get());
  EXPECT_EQ(0.9, dc.heatingHumidificationHumidityRatio99().get());
  EXPECT_EQ(-7.5, dc.heatingHumidificationMeanCoincidentDryBulb99().get());
  EXPECT_EQ(12.2, dc.heatingColdestMonthWindSpeed0pt4().get());
  EXPECT_EQ(3.9, dc.heatingColdestMonthMeanCoincidentDryBulb0pt4().get());
  EXPECT_EQ(10.9, dc.heatingColdestMonthWindSpeed1().get());
  EXPECT_EQ(3.8, dc.heatingColdestMonthMeanCoincidentDryBulb1().get());
  EXPECT_EQ(3.0, dc.heatingMeanCoincidentWindSpeed99pt6().get());
  EXPECT_EQ(340, dc.heatingPrevailingCoincidentWindDirection99pt6().get());
  EXPECT_FALSE(dc.heatingWindShelterFactor());

  EXPECT_EQ(7, dc.coolingHottestMonth().get());
  EXPECT_EQ(15.2, dc.coolingDryBulbRange().get());
  EXPECT_EQ(33.0, dc.coolingDryBulb0pt4().get());
  EXPECT_EQ(15.7, dc.coolingMeanCoincidentWetBulb0pt4().get());
  EXPECT_EQ(32.0, dc.coolingDryBulb1().get());
  EXPECT_EQ(15.5, dc.coolingMeanCoincidentWetBulb1().get());
  EXPECT_EQ(30.2, dc.coolingDryBulb2().get());
  EXPECT_EQ(15.3, dc.coolingMeanCoincidentWetBulb2().get());
  EXPECT_EQ(18.4, dc.coolingEvaporationWetBulb0pt4().get());
  EXPECT_EQ(27.3, dc.coolingEvaporationMeanCoincidentDryBulb0pt4().get());
  EXPECT_EQ(17.5, dc.coolingEvaporationWetBulb1().get());
  EXPECT_EQ(26.4, dc.coolingEvaporationMeanCoincidentDryBulb1().get());
  EXPECT_EQ(16.8, dc.coolingEvaporationWetBulb2().get());
  EXPECT_EQ(25.6, dc.coolingEvaporationMeanCoincidentDryBulb2().get());
  EXPECT_EQ(4.9, dc.coolingMeanCoincidentWindSpeed0pt4().get());
  EXPECT_EQ(0, dc.coolingPrevailingCoincidentWindDirection0pt4().get());
  EXPECT_EQ(16.1, dc.coolingDehumidificationDewPoint0pt4().get());
  EXPECT_EQ(14.3, dc.coolingDehumidificationHumidityRatio0pt4().get());
  EXPECT_EQ(20.2, dc.coolingDehumidificationMeanCoincidentDryBulb0pt4().get());
  EXPECT_EQ(14.9, dc.coolingDehumidificationDewPoint1().get());
  EXPECT_EQ(13.2, dc.coolingDehumidificationHumidityRatio1().get());
  EXPECT_EQ(19.9, dc.coolingDehumidificationMeanCoincidentDryBulb1().get());
  EXPECT_EQ(13.9, dc.coolingDehumidificationDewPoint2().get());
  EXPECT_EQ(12.3, dc.coolingDehumidificationHumidityRatio2().get());
  EXPECT_EQ(19.6, dc.coolingDehumidificationMeanCoincidentDryBulb2().get());
  EXPECT_EQ(59.7, dc.coolingEnthalpy0pt4().get());
  EXPECT_EQ(27.3, dc.coolingEnthalpyMeanCoincidentDryBulb0pt4().get());
  EXPECT_EQ(56.6, dc.coolingEnthalpy1().get());
  EXPECT_EQ(26.6, dc.coolingEnthalpyMeanCoincidentDryBulb1().get());
  EXPECT_EQ(54.0, dc.coolingEnthalpy2().get());
  EXPECT_EQ(25.7, dc.coolingEnthalpyMeanCoincidentDryBulb2().get());

  ASSERT_TRUE(dc.coolingHours8To4AndDryBulb12pt8To20pt6());
  EXPECT_EQ(760, dc.coolingHours8To4AndDryBulb12pt8To20pt6().get());

  EXPECT_EQ(11.1, dc.extremeWindSpeed1().get());
  EXPECT_EQ(9.5, dc.extremeWindSpeed2pt5().get());
  EXPECT_EQ(8.4, dc.extremeWindSpeed5().get());

  ASSERT_TRUE(dc.coolingExtremeMaxWetBulb());
  EXPECT_EQ(22.9, dc.coolingExtremeMaxWetBulb().get());
  ASSERT_TRUE(dc.extremeMaxWetBulb());
  EXPECT_EQ(22.9, dc.extremeMaxWetBulb().get());

  EXPECT_EQ(-22.9, dc.extremeMeanMinDryBulb().get());
  EXPECT_EQ(36.1, dc.extremeMeanMaxDryBulb().get());
  EXPECT_EQ(3.8, dc.extremeStdDevMinDryBulb().get());
  EXPECT_EQ(1.2, dc.extremeStdDevMaxDryBulb().get());
  EXPECT_EQ(-25.7, dc.extremeN5YearsMinDryBulb().get());
  EXPECT_EQ(37.0, dc.extremeN5YearsMaxDryBulb().get());
  EXPECT_EQ(-27.9, dc.extremeN10YearsMinDryBulb().get());
  EXPECT_EQ(37.7, dc.extremeN10YearsMaxDryBulb().get());
  EXPECT_EQ(-30.1, dc.extremeN20YearsMinDryBulb().get());
  EXPECT_EQ(38.3, dc.extremeN20YearsMaxDryBulb().get());
  EXPECT_EQ(-32.8, dc.extremeN50YearsMinDryBulb().get());
  EXPECT_EQ(39.2, dc.extremeN50YearsMaxDryBulb().get());
}

TEST(Filetypes, EpwDesignCondition_HoF_2021) {

  const std::string line = "2021 ASHRAE Handbook -- Fundamentals - Chapter 14 Climatic Design Information,,"
                           "Heating,12,-18.8,-15.5,-21.6,0.7,-10.9,-18.8,0.9,-7.5,12.2,3.9,10.9,3.8,3,340,0.635,"
                           "Cooling,7,15.2,33,15.7,32,15.5,30.2,15.3,18.4,27.3,17.5,26.4,16.8,25.6,4.9,0,16.1,14.3,20.2,14.9,13.2,19.9,13.9,12.3,"
                           "19.6,59.7,27.3,56.6,26.6,54,25.7,22.9,"
                           "Extremes,11.1,9.5,8.4,-22.9,36.1,3.8,1.2,-25.7,37,-27.9,37.7,-30.1,38.3,-32.8,39.2";
  auto dc_ = EpwDesignCondition::fromDesignConditionsString(line);
  ASSERT_TRUE(dc_);
  const auto dc = std::move(*dc_);

  EXPECT_EQ(dc.ashraeHoFVersion(), ASHRAEHoFVintage::ASHRAE_2021);

  EXPECT_EQ("2021 ASHRAE Handbook -- Fundamentals - Chapter 14 Climatic Design Information", dc.titleOfDesignCondition());
  EXPECT_EQ(12, dc.heatingColdestMonth().get());
  EXPECT_EQ(-18.8, dc.heatingDryBulb99pt6().get());
  EXPECT_EQ(-18.8, dc.getFieldByName("Heating Dry Bulb Temperature 99.6%").get());
  EXPECT_EQ(-18.8, dc.getField(EpwDesignField("Heating Dry Bulb Temperature 99.6%")).get());
  EXPECT_EQ("C", dc.getUnitsByName("Heating Dry Bulb Temperature 99.6%").get());
  EXPECT_EQ("C", dc.getUnits(EpwDesignField("Heating Dry Bulb Temperature 99.6%")));
  EXPECT_EQ(-15.5, dc.heatingDryBulb99().get());
  EXPECT_EQ(-21.6, dc.heatingHumidificationDewPoint99pt6().get());
  EXPECT_EQ(0.7, dc.heatingHumidificationHumidityRatio99pt6().get());
  EXPECT_EQ(-10.9, dc.heatingHumidificationMeanCoincidentDryBulb99pt6().get());
  EXPECT_EQ(-18.8, dc.heatingHumidificationDewPoint99().get());
  EXPECT_EQ(0.9, dc.heatingHumidificationHumidityRatio99().get());
  EXPECT_EQ(-7.5, dc.heatingHumidificationMeanCoincidentDryBulb99().get());
  EXPECT_EQ(12.2, dc.heatingColdestMonthWindSpeed0pt4().get());
  EXPECT_EQ(3.9, dc.heatingColdestMonthMeanCoincidentDryBulb0pt4().get());
  EXPECT_EQ(10.9, dc.heatingColdestMonthWindSpeed1().get());
  EXPECT_EQ(3.8, dc.heatingColdestMonthMeanCoincidentDryBulb1().get());
  EXPECT_EQ(3.0, dc.heatingMeanCoincidentWindSpeed99pt6().get());
  EXPECT_EQ(340, dc.heatingPrevailingCoincidentWindDirection99pt6().get());
  ASSERT_TRUE(dc.heatingWindShelterFactor());
  EXPECT_EQ(0.635, dc.heatingWindShelterFactor().get());

  EXPECT_EQ(7, dc.coolingHottestMonth().get());
  EXPECT_EQ(15.2, dc.coolingDryBulbRange().get());
  EXPECT_EQ(33.0, dc.coolingDryBulb0pt4().get());
  EXPECT_EQ(15.7, dc.coolingMeanCoincidentWetBulb0pt4().get());
  EXPECT_EQ(32.0, dc.coolingDryBulb1().get());
  EXPECT_EQ(15.5, dc.coolingMeanCoincidentWetBulb1().get());
  EXPECT_EQ(30.2, dc.coolingDryBulb2().get());
  EXPECT_EQ(15.3, dc.coolingMeanCoincidentWetBulb2().get());
  EXPECT_EQ(18.4, dc.coolingEvaporationWetBulb0pt4().get());
  EXPECT_EQ(27.3, dc.coolingEvaporationMeanCoincidentDryBulb0pt4().get());
  EXPECT_EQ(17.5, dc.coolingEvaporationWetBulb1().get());
  EXPECT_EQ(26.4, dc.coolingEvaporationMeanCoincidentDryBulb1().get());
  EXPECT_EQ(16.8, dc.coolingEvaporationWetBulb2().get());
  EXPECT_EQ(25.6, dc.coolingEvaporationMeanCoincidentDryBulb2().get());
  EXPECT_EQ(4.9, dc.coolingMeanCoincidentWindSpeed0pt4().get());
  EXPECT_EQ(0, dc.coolingPrevailingCoincidentWindDirection0pt4().get());
  EXPECT_EQ(16.1, dc.coolingDehumidificationDewPoint0pt4().get());
  EXPECT_EQ(14.3, dc.coolingDehumidificationHumidityRatio0pt4().get());
  EXPECT_EQ(20.2, dc.coolingDehumidificationMeanCoincidentDryBulb0pt4().get());
  EXPECT_EQ(14.9, dc.coolingDehumidificationDewPoint1().get());
  EXPECT_EQ(13.2, dc.coolingDehumidificationHumidityRatio1().get());
  EXPECT_EQ(19.9, dc.coolingDehumidificationMeanCoincidentDryBulb1().get());
  EXPECT_EQ(13.9, dc.coolingDehumidificationDewPoint2().get());
  EXPECT_EQ(12.3, dc.coolingDehumidificationHumidityRatio2().get());
  EXPECT_EQ(19.6, dc.coolingDehumidificationMeanCoincidentDryBulb2().get());
  EXPECT_EQ(59.7, dc.coolingEnthalpy0pt4().get());
  EXPECT_EQ(27.3, dc.coolingEnthalpyMeanCoincidentDryBulb0pt4().get());
  EXPECT_EQ(56.6, dc.coolingEnthalpy1().get());
  EXPECT_EQ(26.6, dc.coolingEnthalpyMeanCoincidentDryBulb1().get());
  EXPECT_EQ(54.0, dc.coolingEnthalpy2().get());
  EXPECT_EQ(25.7, dc.coolingEnthalpyMeanCoincidentDryBulb2().get());

  EXPECT_FALSE(dc.coolingHours8To4AndDryBulb12pt8To20pt6());

  EXPECT_EQ(11.1, dc.extremeWindSpeed1().get());
  EXPECT_EQ(9.5, dc.extremeWindSpeed2pt5().get());
  EXPECT_EQ(8.4, dc.extremeWindSpeed5().get());

  ASSERT_TRUE(dc.coolingExtremeMaxWetBulb());
  EXPECT_EQ(22.9, dc.coolingExtremeMaxWetBulb().get());
  ASSERT_TRUE(dc.extremeMaxWetBulb());
  EXPECT_EQ(22.9, dc.extremeMaxWetBulb().get());

  EXPECT_EQ(-22.9, dc.extremeMeanMinDryBulb().get());
  EXPECT_EQ(36.1, dc.extremeMeanMaxDryBulb().get());
  EXPECT_EQ(3.8, dc.extremeStdDevMinDryBulb().get());
  EXPECT_EQ(1.2, dc.extremeStdDevMaxDryBulb().get());
  EXPECT_EQ(-25.7, dc.extremeN5YearsMinDryBulb().get());
  EXPECT_EQ(37.0, dc.extremeN5YearsMaxDryBulb().get());
  EXPECT_EQ(-27.9, dc.extremeN10YearsMinDryBulb().get());
  EXPECT_EQ(37.7, dc.extremeN10YearsMaxDryBulb().get());
  EXPECT_EQ(-30.1, dc.extremeN20YearsMinDryBulb().get());
  EXPECT_EQ(38.3, dc.extremeN20YearsMaxDryBulb().get());
  EXPECT_EQ(-32.8, dc.extremeN50YearsMinDryBulb().get());
  EXPECT_EQ(39.2, dc.extremeN50YearsMaxDryBulb().get());
}

TEST(Filetypes, EpwDesignCondition_HoF_2021_Heuristics) {

  const std::string line = "This title does not include the version,,"
                           "Heating,12,-18.8,-15.5,-21.6,0.7,-10.9,-18.8,0.9,-7.5,12.2,3.9,10.9,3.8,3,340,0.635,"
                           "Cooling,7,15.2,33,15.7,32,15.5,30.2,15.3,18.4,27.3,17.5,26.4,16.8,25.6,4.9,0,16.1,14.3,20.2,14.9,13.2,19.9,13.9,12.3,"
                           "19.6,59.7,27.3,56.6,26.6,54,25.7,22.9,"
                           "Extremes,11.1,9.5,8.4,-22.9,36.1,3.8,1.2,-25.7,37,-27.9,37.7,-30.1,38.3,-32.8,39.2";
  auto dc_ = EpwDesignCondition::fromDesignConditionsString(line);
  ASSERT_TRUE(dc_);
  const auto dc = std::move(*dc_);

  EXPECT_EQ(dc.ashraeHoFVersion(), ASHRAEHoFVintage::ASHRAE_2021);

  EXPECT_EQ("This title does not include the version", dc.titleOfDesignCondition());
  EXPECT_EQ(12, dc.heatingColdestMonth().get());
  EXPECT_EQ(-18.8, dc.heatingDryBulb99pt6().get());
  EXPECT_EQ(-18.8, dc.getFieldByName("Heating Dry Bulb Temperature 99.6%").get());
  EXPECT_EQ(-18.8, dc.getField(EpwDesignField("Heating Dry Bulb Temperature 99.6%")).get());
  EXPECT_EQ("C", dc.getUnitsByName("Heating Dry Bulb Temperature 99.6%").get());
  EXPECT_EQ("C", dc.getUnits(EpwDesignField("Heating Dry Bulb Temperature 99.6%")));
  EXPECT_EQ(-15.5, dc.heatingDryBulb99().get());
  EXPECT_EQ(-21.6, dc.heatingHumidificationDewPoint99pt6().get());
  EXPECT_EQ(0.7, dc.heatingHumidificationHumidityRatio99pt6().get());
  EXPECT_EQ(-10.9, dc.heatingHumidificationMeanCoincidentDryBulb99pt6().get());
  EXPECT_EQ(-18.8, dc.heatingHumidificationDewPoint99().get());
  EXPECT_EQ(0.9, dc.heatingHumidificationHumidityRatio99().get());
  EXPECT_EQ(-7.5, dc.heatingHumidificationMeanCoincidentDryBulb99().get());
  EXPECT_EQ(12.2, dc.heatingColdestMonthWindSpeed0pt4().get());
  EXPECT_EQ(3.9, dc.heatingColdestMonthMeanCoincidentDryBulb0pt4().get());
  EXPECT_EQ(10.9, dc.heatingColdestMonthWindSpeed1().get());
  EXPECT_EQ(3.8, dc.heatingColdestMonthMeanCoincidentDryBulb1().get());
  EXPECT_EQ(3.0, dc.heatingMeanCoincidentWindSpeed99pt6().get());
  EXPECT_EQ(340, dc.heatingPrevailingCoincidentWindDirection99pt6().get());
  ASSERT_TRUE(dc.heatingWindShelterFactor());
  EXPECT_EQ(0.635, dc.heatingWindShelterFactor().get());

  EXPECT_EQ(7, dc.coolingHottestMonth().get());
  EXPECT_EQ(15.2, dc.coolingDryBulbRange().get());
  EXPECT_EQ(33.0, dc.coolingDryBulb0pt4().get());
  EXPECT_EQ(15.7, dc.coolingMeanCoincidentWetBulb0pt4().get());
  EXPECT_EQ(32.0, dc.coolingDryBulb1().get());
  EXPECT_EQ(15.5, dc.coolingMeanCoincidentWetBulb1().get());
  EXPECT_EQ(30.2, dc.coolingDryBulb2().get());
  EXPECT_EQ(15.3, dc.coolingMeanCoincidentWetBulb2().get());
  EXPECT_EQ(18.4, dc.coolingEvaporationWetBulb0pt4().get());
  EXPECT_EQ(27.3, dc.coolingEvaporationMeanCoincidentDryBulb0pt4().get());
  EXPECT_EQ(17.5, dc.coolingEvaporationWetBulb1().get());
  EXPECT_EQ(26.4, dc.coolingEvaporationMeanCoincidentDryBulb1().get());
  EXPECT_EQ(16.8, dc.coolingEvaporationWetBulb2().get());
  EXPECT_EQ(25.6, dc.coolingEvaporationMeanCoincidentDryBulb2().get());
  EXPECT_EQ(4.9, dc.coolingMeanCoincidentWindSpeed0pt4().get());
  EXPECT_EQ(0, dc.coolingPrevailingCoincidentWindDirection0pt4().get());
  EXPECT_EQ(16.1, dc.coolingDehumidificationDewPoint0pt4().get());
  EXPECT_EQ(14.3, dc.coolingDehumidificationHumidityRatio0pt4().get());
  EXPECT_EQ(20.2, dc.coolingDehumidificationMeanCoincidentDryBulb0pt4().get());
  EXPECT_EQ(14.9, dc.coolingDehumidificationDewPoint1().get());
  EXPECT_EQ(13.2, dc.coolingDehumidificationHumidityRatio1().get());
  EXPECT_EQ(19.9, dc.coolingDehumidificationMeanCoincidentDryBulb1().get());
  EXPECT_EQ(13.9, dc.coolingDehumidificationDewPoint2().get());
  EXPECT_EQ(12.3, dc.coolingDehumidificationHumidityRatio2().get());
  EXPECT_EQ(19.6, dc.coolingDehumidificationMeanCoincidentDryBulb2().get());
  EXPECT_EQ(59.7, dc.coolingEnthalpy0pt4().get());
  EXPECT_EQ(27.3, dc.coolingEnthalpyMeanCoincidentDryBulb0pt4().get());
  EXPECT_EQ(56.6, dc.coolingEnthalpy1().get());
  EXPECT_EQ(26.6, dc.coolingEnthalpyMeanCoincidentDryBulb1().get());
  EXPECT_EQ(54.0, dc.coolingEnthalpy2().get());
  EXPECT_EQ(25.7, dc.coolingEnthalpyMeanCoincidentDryBulb2().get());

  EXPECT_FALSE(dc.coolingHours8To4AndDryBulb12pt8To20pt6());

  EXPECT_EQ(11.1, dc.extremeWindSpeed1().get());
  EXPECT_EQ(9.5, dc.extremeWindSpeed2pt5().get());
  EXPECT_EQ(8.4, dc.extremeWindSpeed5().get());

  ASSERT_TRUE(dc.coolingExtremeMaxWetBulb());
  EXPECT_EQ(22.9, dc.coolingExtremeMaxWetBulb().get());
  ASSERT_TRUE(dc.extremeMaxWetBulb());
  EXPECT_EQ(22.9, dc.extremeMaxWetBulb().get());

  EXPECT_EQ(-22.9, dc.extremeMeanMinDryBulb().get());
  EXPECT_EQ(36.1, dc.extremeMeanMaxDryBulb().get());
  EXPECT_EQ(3.8, dc.extremeStdDevMinDryBulb().get());
  EXPECT_EQ(1.2, dc.extremeStdDevMaxDryBulb().get());
  EXPECT_EQ(-25.7, dc.extremeN5YearsMinDryBulb().get());
  EXPECT_EQ(37.0, dc.extremeN5YearsMaxDryBulb().get());
  EXPECT_EQ(-27.9, dc.extremeN10YearsMinDryBulb().get());
  EXPECT_EQ(37.7, dc.extremeN10YearsMaxDryBulb().get());
  EXPECT_EQ(-30.1, dc.extremeN20YearsMinDryBulb().get());
  EXPECT_EQ(38.3, dc.extremeN20YearsMaxDryBulb().get());
  EXPECT_EQ(-32.8, dc.extremeN50YearsMinDryBulb().get());
  EXPECT_EQ(39.2, dc.extremeN50YearsMaxDryBulb().get());
}

TEST(Filetypes, EpwDesignCondition_HoF_2021_Heuristics_OverrideVersion) {

  const std::string line = "This title includes the 2009 version when it's not actually it,,"
                           "Heating,12,-18.8,-15.5,-21.6,0.7,-10.9,-18.8,0.9,-7.5,12.2,3.9,10.9,3.8,3,340,0.635,"
                           "Cooling,7,15.2,33,15.7,32,15.5,30.2,15.3,18.4,27.3,17.5,26.4,16.8,25.6,4.9,0,16.1,14.3,20.2,14.9,13.2,19.9,13.9,12.3,"
                           "19.6,59.7,27.3,56.6,26.6,54,25.7,22.9,"
                           "Extremes,11.1,9.5,8.4,-22.9,36.1,3.8,1.2,-25.7,37,-27.9,37.7,-30.1,38.3,-32.8,39.2";
  auto dc_ = EpwDesignCondition::fromDesignConditionsString(line);
  ASSERT_TRUE(dc_);
  const auto dc = std::move(*dc_);

  EXPECT_EQ(dc.ashraeHoFVersion(), ASHRAEHoFVintage::ASHRAE_2021);

  EXPECT_EQ("This title includes the 2009 version when it's not actually it", dc.titleOfDesignCondition());
  EXPECT_EQ(12, dc.heatingColdestMonth().get());
  EXPECT_EQ(-18.8, dc.heatingDryBulb99pt6().get());
  EXPECT_EQ(-18.8, dc.getFieldByName("Heating Dry Bulb Temperature 99.6%").get());
  EXPECT_EQ(-18.8, dc.getField(EpwDesignField("Heating Dry Bulb Temperature 99.6%")).get());
  EXPECT_EQ("C", dc.getUnitsByName("Heating Dry Bulb Temperature 99.6%").get());
  EXPECT_EQ("C", dc.getUnits(EpwDesignField("Heating Dry Bulb Temperature 99.6%")));
  EXPECT_EQ(-15.5, dc.heatingDryBulb99().get());
  EXPECT_EQ(-21.6, dc.heatingHumidificationDewPoint99pt6().get());
  EXPECT_EQ(0.7, dc.heatingHumidificationHumidityRatio99pt6().get());
  EXPECT_EQ(-10.9, dc.heatingHumidificationMeanCoincidentDryBulb99pt6().get());
  EXPECT_EQ(-18.8, dc.heatingHumidificationDewPoint99().get());
  EXPECT_EQ(0.9, dc.heatingHumidificationHumidityRatio99().get());
  EXPECT_EQ(-7.5, dc.heatingHumidificationMeanCoincidentDryBulb99().get());
  EXPECT_EQ(12.2, dc.heatingColdestMonthWindSpeed0pt4().get());
  EXPECT_EQ(3.9, dc.heatingColdestMonthMeanCoincidentDryBulb0pt4().get());
  EXPECT_EQ(10.9, dc.heatingColdestMonthWindSpeed1().get());
  EXPECT_EQ(3.8, dc.heatingColdestMonthMeanCoincidentDryBulb1().get());
  EXPECT_EQ(3.0, dc.heatingMeanCoincidentWindSpeed99pt6().get());
  EXPECT_EQ(340, dc.heatingPrevailingCoincidentWindDirection99pt6().get());
  ASSERT_TRUE(dc.heatingWindShelterFactor());
  EXPECT_EQ(0.635, dc.heatingWindShelterFactor().get());

  EXPECT_EQ(7, dc.coolingHottestMonth().get());
  EXPECT_EQ(15.2, dc.coolingDryBulbRange().get());
  EXPECT_EQ(33.0, dc.coolingDryBulb0pt4().get());
  EXPECT_EQ(15.7, dc.coolingMeanCoincidentWetBulb0pt4().get());
  EXPECT_EQ(32.0, dc.coolingDryBulb1().get());
  EXPECT_EQ(15.5, dc.coolingMeanCoincidentWetBulb1().get());
  EXPECT_EQ(30.2, dc.coolingDryBulb2().get());
  EXPECT_EQ(15.3, dc.coolingMeanCoincidentWetBulb2().get());
  EXPECT_EQ(18.4, dc.coolingEvaporationWetBulb0pt4().get());
  EXPECT_EQ(27.3, dc.coolingEvaporationMeanCoincidentDryBulb0pt4().get());
  EXPECT_EQ(17.5, dc.coolingEvaporationWetBulb1().get());
  EXPECT_EQ(26.4, dc.coolingEvaporationMeanCoincidentDryBulb1().get());
  EXPECT_EQ(16.8, dc.coolingEvaporationWetBulb2().get());
  EXPECT_EQ(25.6, dc.coolingEvaporationMeanCoincidentDryBulb2().get());
  EXPECT_EQ(4.9, dc.coolingMeanCoincidentWindSpeed0pt4().get());
  EXPECT_EQ(0, dc.coolingPrevailingCoincidentWindDirection0pt4().get());
  EXPECT_EQ(16.1, dc.coolingDehumidificationDewPoint0pt4().get());
  EXPECT_EQ(14.3, dc.coolingDehumidificationHumidityRatio0pt4().get());
  EXPECT_EQ(20.2, dc.coolingDehumidificationMeanCoincidentDryBulb0pt4().get());
  EXPECT_EQ(14.9, dc.coolingDehumidificationDewPoint1().get());
  EXPECT_EQ(13.2, dc.coolingDehumidificationHumidityRatio1().get());
  EXPECT_EQ(19.9, dc.coolingDehumidificationMeanCoincidentDryBulb1().get());
  EXPECT_EQ(13.9, dc.coolingDehumidificationDewPoint2().get());
  EXPECT_EQ(12.3, dc.coolingDehumidificationHumidityRatio2().get());
  EXPECT_EQ(19.6, dc.coolingDehumidificationMeanCoincidentDryBulb2().get());
  EXPECT_EQ(59.7, dc.coolingEnthalpy0pt4().get());
  EXPECT_EQ(27.3, dc.coolingEnthalpyMeanCoincidentDryBulb0pt4().get());
  EXPECT_EQ(56.6, dc.coolingEnthalpy1().get());
  EXPECT_EQ(26.6, dc.coolingEnthalpyMeanCoincidentDryBulb1().get());
  EXPECT_EQ(54.0, dc.coolingEnthalpy2().get());
  EXPECT_EQ(25.7, dc.coolingEnthalpyMeanCoincidentDryBulb2().get());

  EXPECT_FALSE(dc.coolingHours8To4AndDryBulb12pt8To20pt6());

  EXPECT_EQ(11.1, dc.extremeWindSpeed1().get());
  EXPECT_EQ(9.5, dc.extremeWindSpeed2pt5().get());
  EXPECT_EQ(8.4, dc.extremeWindSpeed5().get());

  ASSERT_TRUE(dc.coolingExtremeMaxWetBulb());
  EXPECT_EQ(22.9, dc.coolingExtremeMaxWetBulb().get());
  ASSERT_TRUE(dc.extremeMaxWetBulb());
  EXPECT_EQ(22.9, dc.extremeMaxWetBulb().get());

  EXPECT_EQ(-22.9, dc.extremeMeanMinDryBulb().get());
  EXPECT_EQ(36.1, dc.extremeMeanMaxDryBulb().get());
  EXPECT_EQ(3.8, dc.extremeStdDevMinDryBulb().get());
  EXPECT_EQ(1.2, dc.extremeStdDevMaxDryBulb().get());
  EXPECT_EQ(-25.7, dc.extremeN5YearsMinDryBulb().get());
  EXPECT_EQ(37.0, dc.extremeN5YearsMaxDryBulb().get());
  EXPECT_EQ(-27.9, dc.extremeN10YearsMinDryBulb().get());
  EXPECT_EQ(37.7, dc.extremeN10YearsMaxDryBulb().get());
  EXPECT_EQ(-30.1, dc.extremeN20YearsMinDryBulb().get());
  EXPECT_EQ(38.3, dc.extremeN20YearsMaxDryBulb().get());
  EXPECT_EQ(-32.8, dc.extremeN50YearsMinDryBulb().get());
  EXPECT_EQ(39.2, dc.extremeN50YearsMaxDryBulb().get());
}

TEST(Filetypes, EpwDesignCondition_WrongNumberOfSubFields_TooManyTotal) {
  const std::string line = "This 2021 version has too many fields total,,"
                           "Heating,12,-18.8,-15.5,-21.6,0.7,-10.9,-18.8,0.9,-7.5,12.2,3.9,10.9,3.8,3,340,0.635,0.936,"
                           "Cooling,7,15.2,33,15.7,32,15.5,30.2,15.3,18.4,27.3,17.5,26.4,16.8,25.6,4.9,0,16.1,14.3,20.2,14.9,13.2,19.9,13.9,12.3,"
                           "19.6,59.7,27.3,56.6,26.6,54,25.7,22.9,"
                           "Extremes,11.1,9.5,8.4,-22.9,36.1,3.8,1.2,-25.7,37,-27.9,37.7,-30.1,38.3,-32.8,39.2";
  auto dc_ = EpwDesignCondition::fromDesignConditionsString(line);
  EXPECT_FALSE(dc_);
}

TEST(Filetypes, EpwDesignCondition_WrongNumberOfSubFields_UnbalancedFields) {
  const std::string line = "This 2021 version has one too many fields in heating and one too few in extremes,,"
                           "Heating,12,-18.8,-15.5,-21.6,0.7,-10.9,-18.8,0.9,-7.5,12.2,3.9,10.9,3.8,3,340,0.635,0.936,"
                           "Cooling,7,15.2,33,15.7,32,15.5,30.2,15.3,18.4,27.3,17.5,26.4,16.8,25.6,4.9,0,16.1,14.3,20.2,14.9,13.2,19.9,13.9,12.3,"
                           "19.6,59.7,27.3,56.6,26.6,54,25.7,22.9,"
                           "Extremes,11.1,9.5,8.4,-22.9,36.1,3.8,1.2,-25.7,37,-27.9,37.7,-30.1,38.3,-32.8";
  auto dc_ = EpwDesignCondition::fromDesignConditionsString(line);
  EXPECT_FALSE(dc_);
}

TEST(Filetypes, EpwDesignCondition_WrongNumberOfSubFields_UnbalancedFields2) {
  const std::string line = "This 2021 version has one too many fields in cooling and one too few in heating,,"
                           "Heating,12,-18.8,-15.5,-21.6,0.7,-10.9,-18.8,0.9,-7.5,12.2,3.9,10.9,3.8,3,340,"
                           "Cooling,7,15.2,33,15.7,32,15.5,30.2,15.3,18.4,27.3,17.5,26.4,16.8,25.6,4.9,0,16.1,14.3,20.2,14.9,13.2,19.9,13.9,12.3,"
                           "19.6,59.7,27.3,56.6,26.6,54,25.7,22.9,700,"
                           "Extremes,11.1,9.5,8.4,-22.9,36.1,3.8,1.2,-25.7,37,-27.9,37.7,-30.1,38.3,-32.8,39.2";
  auto dc_ = EpwDesignCondition::fromDesignConditionsString(line);
  EXPECT_FALSE(dc_);
}

TEST(Filetypes, EpwFile_EpwDesignCondition_TMYx) {

  // USA_CO_Denver.Intl.AP.725650_TMYx.2009-2023.epw

  const std::string epwFileContent = R"(LOCATION,Denver.Intl.AP,CO,USA,SRC-TMYx,725650,39.83300,-104.6580,-7.0,1650.2
DESIGN CONDITIONS,1,2021 ASHRAE Handbook -- Fundamentals - Chapter 14 Climatic Design Information,,Heating,12,-17.9,-14.6,-22.0,0.6,-11.2,-19.6,0.8,-6.5,13.3,5.7,11.8,2.7,3.4,230,0.635,Cooling,7,15.3,34.9,15.5,33.5,15.4,32.0,15.3,18.2,27.2,17.6,27.0,16.9,26.4,4.2,20,15.9,13.8,20.1,15.0,13.0,19.9,14.1,12.3,19.7,58.3,26.9,55.8,26.8,53.8,26.3,20.7,Extremes,12.1,10.6,8.9,-23.5,37.4,3.1,1.1,-25.8,38.2,-27.6,38.9,-29.3,39.5,-31.6,40.3
TYPICAL/EXTREME PERIODS,6,Summer - Week Nearest Max Temperature For Period,Extreme,7/13,7/19,Summer - Week Nearest Average Temperature For Period,Typical,6/ 8,6/14,Winter - Week Nearest Min Temperature For Period,Extreme,2/ 3,2/ 9,Winter - Week Nearest Average Temperature For Period,Typical,1/ 6,1/12,Autumn - Week Nearest Average Temperature For Period,Typical,10/ 6,10/12,Spring - Week Nearest Average Temperature For Period,Typical,4/ 5,4/11
GROUND TEMPERATURES,3,.5,,,,4.30,0.24,-0.87,0.09,5.58,11.73,17.52,21.71,22.93,20.96,16.22,10.25,2,,,,7.96,4.15,2.33,2.27,5.17,9.38,13.90,17.78,19.79,19.41,16.74,12.63,4,,,,10.35,7.39,5.57,5.01,6.08,8.53,11.58,14.57,16.57,17.05,15.91,13.50
HOLIDAYS/DAYLIGHT SAVINGS,No,0,0,0
COMMENTS 1,"NCEI ISD/ERA5 - #years=[15] Period of Record=2009-2023; Jan=2022; Feb=2014; Mar=2014; Apr=2018; May=2017; Jun=2017; Jul=2019; Aug=2015; Sep=2018; Oct=2014; Nov=2017; Dec=2018"
COMMENTS 2,"Downloaded from Climate.Onebuilding.org -- Ground temps represent undisturbed earth temperatures - calculated from this weather data."
DATA PERIODS,1,1,Data,Sunday,1/ 1,1/1
2022,1,1,1,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9,-13.30,-15.00,86,81916,0,0,264,0,0,0,0,0,0,0,70,5.10,10,10,2012.0,914,0,999099999,2,0.0850,2,88,0.460,0.2,0.0
2022,1,1,2,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9,-13.90,-16.10,82,81876,0,0,264,0,0,0,0,0,0,0,90,5.10,10,10,2012.0,1036,0,999099999,2,0.0850,2,88,0.470,0.2,0.0
2022,1,1,3,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9,-13.90,-16.10,82,81597,0,0,259,0,0,0,0,0,0,0,90,5.70,10,10,2000.0,223,0,999099999,2,0.0850,2,88,0.480,0.1,0.0
2022,1,1,4,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9,-15.00,-17.00,83,81803,0,0,261,0,0,0,0,0,0,0,60,2.60,10,10,2012.0,823,0,999099999,2,0.0850,2,88,0.370,0.1,0.0
2022,1,1,5,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9,-16.10,-18.30,81,81730,0,0,256,0,0,0,0,0,0,0,60,3.10,10,10,2012.0,2438,0,999099999,1,0.0850,2,88,0.380,0.1,0.0
2022,1,1,6,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9*9?9*9*9?9*9,-16.70,-18.30,86,81573,0,0,255,0,0,0,0,0,0,0,60,3.10,10,10,2012.0,201,0,999099999,1,0.0850,2,88,0.390,0.1,0.0
2022,1,1,7,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9,-16.70,-18.90,81,81690,0,0,251,0,0,0,0,0,0,0,60,3.60,10,10,3219.0,823,0,999099999,1,0.0850,3,88,0.390,0.1,0.0
2022,1,1,8,0,?9?9?9?9E0?9?9?9*9*9?9?9?9?9?9?9?9?9*9*9?9*9,-17.20,-19.40,81,81656,137,800,253,0,0,0,0,0,0,0,70,2.60,8,8,1207.0,396,0,999099999,1,0.0850,3,88,0.400,0.2,0.0
2022,1,1,9,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9,-17.20,-19.40,81,81918,345,1415,252,23,1,23,5129,386,5129,2340,110,2.10,10,10,1600.0,212,0,999099999,1,0.0850,3,88,0.410,0.2,0.0
2022,1,1,10,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9,-16.10,-18.90,77,81730,505,1415,250,62,8,60,10947,2612,10140,4335,70,1.50,10,10,2012.0,1006,0,999099999,1,0.0850,3,88,0.420,0.3,0.0
2022,1,1,11,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9,-15.00,-18.00,76,81803,607,1415,250,124,42,108,17552,4023,16347,6800,20,2.10,10,10,2414.0,792,0,999099999,1,0.0850,4,88,0.440,0.2,0.0
2022,1,1,12,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9,-15.00,-17.80,77,82324,643,1415,249,180,36,166,22848,2807,22384,9914,20,2.10,10,10,2400.0,214,0,999099999,1,0.0850,4,88,0.470,0.2,0.0
2022,1,1,13,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9,-14.40,-17.20,77,81843,611,1415,248,228,21,219,28428,7017,25889,11729,320,3.10,10,10,4828.0,945,0,999099999,2,0.0850,4,88,0.500,0.3,0.0
2022,1,1,14,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9*9?9*9*9?9*9,-13.90,-16.70,77,81876,514,1415,242,270,112,224,31118,19196,24758,13430,260,3.10,9,9,4828.0,1006,0,999099999,2,0.0850,4,88,0.510,0.2,0.0
2022,1,1,15,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9*9?9*9*9?9*9,-13.30,-16.70,73,82429,357,1415,234,262,252,174,26333,30503,19536,14094,290,2.60,5,5,4828.0,424,0,999099999,2,0.0850,4,88,0.510,0.0,0.0
2022,1,1,16,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9*9?9*9*9?9*9,-13.90,-17.20,74,82502,152,1415,218,188,330,106,15789,26276,10770,10037,250,1.50,9,9,4828.0,6706,0,999099999,2,0.0850,4,88,0.500,0.0,0.0
2022,1,1,17,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9*9?9*9*9?9*9,-14.40,-17.80,73,82550,0,894,198,78,0,40,5562,8978,3104,3442,200,1.50,5,5,4828.0,77777,0,999099999,1,0.0850,4,88,0.500,0.0,0.0
2022,1,1,18,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9*9?9*9*9?9*9,-14.40,-17.80,73,82550,0,0,177,12,0,6,648,0,300,105,200,1.50,0,0,4828.0,77777,9,999999999,1,0.0850,4,88,0.500,0.0,0.0
2022,1,1,19,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9*9?9*9*9?9*9,-22.20,-23.90,85,82280,0,0,171,0,0,0,0,0,0,0,180,4.60,0,0,4828.0,77777,9,999999999,1,0.0850,4,88,0.500,0.0,0.0
2022,1,1,20,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9*9?9*9*9?9*9,-20.00,-21.70,85,82410,0,0,169,0,0,0,0,0,0,0,190,5.10,0,0,4828.0,77777,9,999999999,1,0.0850,4,88,0.500,0.0,0.0
2022,1,1,21,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9*9?9*9*9?9*9,-20.00,-21.70,85,82410,0,0,168,0,0,0,0,0,0,0,190,5.10,0,0,4828.0,77777,9,999999999,1,0.0850,4,88,0.490,0.0,0.0
2022,1,1,22,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9*9?9*9*9?9*9,-19.40,-22.20,76,82452,0,0,167,0,0,0,0,0,0,0,160,5.10,0,0,4828.0,77777,9,999999999,1,0.0850,4,88,0.490,0.0,0.0
2022,1,1,23,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9*9?9*9*9?9*9,-13.90,-18.30,66,82712,0,0,164,0,0,0,0,0,0,0,210,6.70,0,0,4828.0,77777,9,999999999,1,0.0850,4,88,0.490,0.0,0.0
2022,1,1,24,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9*9?9*9*9?9*9,-13.90,-18.30,66,82712,0,0,163,0,0,0,0,0,0,0,210,6.70,0,0,4828.0,77777,9,999999999,1,0.0850,8,88,0.490,0.0,0.0
)";

  boost::optional<EpwFile> epwFile_ = EpwFile::loadFromString(epwFileContent);
  ASSERT_TRUE(epwFile_);
  auto epwFile = std::move(*epwFile_);

  // Up to here, everything should be the same as the first test. Now ask for the design conditions
  std::vector<EpwDesignCondition> designs = epwFile.designConditions();
  EXPECT_EQ(1, designs.size());
  const auto& dc = designs.front();

  EXPECT_EQ(dc.ashraeHoFVersion(), ASHRAEHoFVintage::ASHRAE_2021);

  EXPECT_EQ("2021 ASHRAE Handbook -- Fundamentals - Chapter 14 Climatic Design Information", dc.titleOfDesignCondition());

  // Heating,12,-17.9,-14.6,-22.0,0.6,-11.2,-19.6,0.8,-6.5,13.3,5.7,11.8,2.7,3.4,230,0.635
  EXPECT_EQ(12, dc.heatingColdestMonth().get());
  EXPECT_EQ(-17.9, dc.heatingDryBulb99pt6().get());
  EXPECT_EQ(-17.9, dc.getFieldByName("Heating Dry Bulb Temperature 99.6%").get());
  EXPECT_EQ(-17.9, dc.getField(EpwDesignField("Heating Dry Bulb Temperature 99.6%")).get());
  EXPECT_EQ("C", dc.getUnitsByName("Heating Dry Bulb Temperature 99.6%").get());
  EXPECT_EQ("C", dc.getUnits(EpwDesignField("Heating Dry Bulb Temperature 99.6%")));
  EXPECT_EQ(-14.6, dc.heatingDryBulb99().get());
  EXPECT_EQ(-22.0, dc.heatingHumidificationDewPoint99pt6().get());
  EXPECT_EQ(0.6, dc.heatingHumidificationHumidityRatio99pt6().get());
  EXPECT_EQ(-11.2, dc.heatingHumidificationMeanCoincidentDryBulb99pt6().get());
  EXPECT_EQ(-19.6, dc.heatingHumidificationDewPoint99().get());
  EXPECT_EQ(0.8, dc.heatingHumidificationHumidityRatio99().get());
  EXPECT_EQ(-6.5, dc.heatingHumidificationMeanCoincidentDryBulb99().get());
  EXPECT_EQ(13.3, dc.heatingColdestMonthWindSpeed0pt4().get());
  EXPECT_EQ(5.7, dc.heatingColdestMonthMeanCoincidentDryBulb0pt4().get());
  EXPECT_EQ(11.8, dc.heatingColdestMonthWindSpeed1().get());
  EXPECT_EQ(2.7, dc.heatingColdestMonthMeanCoincidentDryBulb1().get());
  EXPECT_EQ(3.4, dc.heatingMeanCoincidentWindSpeed99pt6().get());
  EXPECT_EQ(230, dc.heatingPrevailingCoincidentWindDirection99pt6().get());
  ASSERT_TRUE(dc.heatingWindShelterFactor());
  EXPECT_EQ(0.635, dc.heatingWindShelterFactor().get());

  // Cooling,7,15.3,34.9,15.5,33.5,15.4,32.0,15.3,18.2,27.2,17.6,27.0,16.9,26.4,4.2,20,15.9,13.8,20.1,15.0,13.0,19.9,14.1,12.3,19.7,58.3,26.9,55.8,26.8,53.8,26.3,20.7
  EXPECT_EQ(7, dc.coolingHottestMonth().get());
  EXPECT_EQ(15.3, dc.coolingDryBulbRange().get());
  EXPECT_EQ(34.9, dc.coolingDryBulb0pt4().get());
  EXPECT_EQ(15.5, dc.coolingMeanCoincidentWetBulb0pt4().get());
  EXPECT_EQ(33.5, dc.coolingDryBulb1().get());
  EXPECT_EQ(15.4, dc.coolingMeanCoincidentWetBulb1().get());
  EXPECT_EQ(32.0, dc.coolingDryBulb2().get());
  EXPECT_EQ(15.3, dc.coolingMeanCoincidentWetBulb2().get());
  EXPECT_EQ(18.2, dc.coolingEvaporationWetBulb0pt4().get());
  EXPECT_EQ(27.2, dc.coolingEvaporationMeanCoincidentDryBulb0pt4().get());
  EXPECT_EQ(17.6, dc.coolingEvaporationWetBulb1().get());
  EXPECT_EQ(27.0, dc.coolingEvaporationMeanCoincidentDryBulb1().get());
  EXPECT_EQ(16.9, dc.coolingEvaporationWetBulb2().get());
  EXPECT_EQ(26.4, dc.coolingEvaporationMeanCoincidentDryBulb2().get());
  EXPECT_EQ(4.2, dc.coolingMeanCoincidentWindSpeed0pt4().get());
  EXPECT_EQ(20, dc.coolingPrevailingCoincidentWindDirection0pt4().get());
  EXPECT_EQ(15.9, dc.coolingDehumidificationDewPoint0pt4().get());
  EXPECT_EQ(13.8, dc.coolingDehumidificationHumidityRatio0pt4().get());
  EXPECT_EQ(20.1, dc.coolingDehumidificationMeanCoincidentDryBulb0pt4().get());
  EXPECT_EQ(15.0, dc.coolingDehumidificationDewPoint1().get());
  EXPECT_EQ(13.0, dc.coolingDehumidificationHumidityRatio1().get());
  EXPECT_EQ(19.9, dc.coolingDehumidificationMeanCoincidentDryBulb1().get());
  EXPECT_EQ(14.1, dc.coolingDehumidificationDewPoint2().get());
  EXPECT_EQ(12.3, dc.coolingDehumidificationHumidityRatio2().get());
  EXPECT_EQ(19.7, dc.coolingDehumidificationMeanCoincidentDryBulb2().get());
  EXPECT_EQ(58.3, dc.coolingEnthalpy0pt4().get());
  EXPECT_EQ(26.9, dc.coolingEnthalpyMeanCoincidentDryBulb0pt4().get());
  EXPECT_EQ(55.8, dc.coolingEnthalpy1().get());
  EXPECT_EQ(26.8, dc.coolingEnthalpyMeanCoincidentDryBulb1().get());
  EXPECT_EQ(53.8, dc.coolingEnthalpy2().get());
  EXPECT_EQ(26.3, dc.coolingEnthalpyMeanCoincidentDryBulb2().get());

  EXPECT_FALSE(dc.coolingHours8To4AndDryBulb12pt8To20pt6());

  ASSERT_TRUE(dc.coolingExtremeMaxWetBulb());
  EXPECT_EQ(20.7, dc.coolingExtremeMaxWetBulb().get());

  // Extremes,12.1,10.6,8.9,-23.5,37.4,3.1,1.1,-25.8,38.2,-27.6,38.9,-29.3,39.5,-31.6,40.3
  EXPECT_EQ(12.1, dc.extremeWindSpeed1().get());
  EXPECT_EQ(10.6, dc.extremeWindSpeed2pt5().get());
  EXPECT_EQ(8.9, dc.extremeWindSpeed5().get());
  ASSERT_TRUE(dc.extremeMaxWetBulb());
  EXPECT_EQ(20.7, dc.extremeMaxWetBulb().get());
  EXPECT_EQ(-23.5, dc.extremeMeanMinDryBulb().get());
  EXPECT_EQ(37.4, dc.extremeMeanMaxDryBulb().get());
  EXPECT_EQ(3.1, dc.extremeStdDevMinDryBulb().get());
  EXPECT_EQ(1.1, dc.extremeStdDevMaxDryBulb().get());
  EXPECT_EQ(-25.8, dc.extremeN5YearsMinDryBulb().get());
  EXPECT_EQ(38.2, dc.extremeN5YearsMaxDryBulb().get());
  EXPECT_EQ(-27.6, dc.extremeN10YearsMinDryBulb().get());
  EXPECT_EQ(38.9, dc.extremeN10YearsMaxDryBulb().get());
  EXPECT_EQ(-29.3, dc.extremeN20YearsMinDryBulb().get());
  EXPECT_EQ(39.5, dc.extremeN20YearsMaxDryBulb().get());
  EXPECT_EQ(-31.6, dc.extremeN50YearsMinDryBulb().get());
  EXPECT_EQ(40.3, dc.extremeN50YearsMaxDryBulb().get());
}

TEST(Filetypes, EpwFile_EpwDesignCondition_TMYx_HoF_2017) {

  // I have never seen a TMYx file with 2017 HoF design conditions, but let's test it anyway
  // The (cooling) Extreme Max Wet Bulb is the last field of the Cooling (and not in Extreme) but there is no Wind Shelter Factor in Heating

  const std::string epwFileContent = R"(LOCATION,Denver.Intl.AP,CO,USA,SRC-TMYx,725650,39.83300,-104.6580,-7.0,1650.2
DESIGN CONDITIONS,1,2017 ASHRAE Handbook -- Fundamentals - Chapter 14 Climatic Design Information,,Heating,12,-17.9,-14.6,-22.0,0.6,-11.2,-19.6,0.8,-6.5,13.3,5.7,11.8,2.7,3.4,230,Cooling,7,15.3,34.9,15.5,33.5,15.4,32.0,15.3,18.2,27.2,17.6,27.0,16.9,26.4,4.2,20,15.9,13.8,20.1,15.0,13.0,19.9,14.1,12.3,19.7,58.3,26.9,55.8,26.8,53.8,26.3,20.7,Extremes,12.1,10.6,8.9,-23.5,37.4,3.1,1.1,-25.8,38.2,-27.6,38.9,-29.3,39.5,-31.6,40.3
TYPICAL/EXTREME PERIODS,6,Summer - Week Nearest Max Temperature For Period,Extreme,7/13,7/19,Summer - Week Nearest Average Temperature For Period,Typical,6/ 8,6/14,Winter - Week Nearest Min Temperature For Period,Extreme,2/ 3,2/ 9,Winter - Week Nearest Average Temperature For Period,Typical,1/ 6,1/12,Autumn - Week Nearest Average Temperature For Period,Typical,10/ 6,10/12,Spring - Week Nearest Average Temperature For Period,Typical,4/ 5,4/11
GROUND TEMPERATURES,3,.5,,,,4.30,0.24,-0.87,0.09,5.58,11.73,17.52,21.71,22.93,20.96,16.22,10.25,2,,,,7.96,4.15,2.33,2.27,5.17,9.38,13.90,17.78,19.79,19.41,16.74,12.63,4,,,,10.35,7.39,5.57,5.01,6.08,8.53,11.58,14.57,16.57,17.05,15.91,13.50
HOLIDAYS/DAYLIGHT SAVINGS,No,0,0,0
COMMENTS 1,"NCEI ISD/ERA5 - #years=[15] Period of Record=2009-2023; Jan=2022; Feb=2014; Mar=2014; Apr=2018; May=2017; Jun=2017; Jul=2019; Aug=2015; Sep=2018; Oct=2014; Nov=2017; Dec=2018"
COMMENTS 2,"Downloaded from Climate.Onebuilding.org -- Ground temps represent undisturbed earth temperatures - calculated from this weather data."
DATA PERIODS,1,1,Data,Sunday,1/ 1,1/1
2022,1,1,1,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9,-13.30,-15.00,86,81916,0,0,264,0,0,0,0,0,0,0,70,5.10,10,10,2012.0,914,0,999099999,2,0.0850,2,88,0.460,0.2,0.0
2022,1,1,2,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9,-13.90,-16.10,82,81876,0,0,264,0,0,0,0,0,0,0,90,5.10,10,10,2012.0,1036,0,999099999,2,0.0850,2,88,0.470,0.2,0.0
2022,1,1,3,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9,-13.90,-16.10,82,81597,0,0,259,0,0,0,0,0,0,0,90,5.70,10,10,2000.0,223,0,999099999,2,0.0850,2,88,0.480,0.1,0.0
2022,1,1,4,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9,-15.00,-17.00,83,81803,0,0,261,0,0,0,0,0,0,0,60,2.60,10,10,2012.0,823,0,999099999,2,0.0850,2,88,0.370,0.1,0.0
2022,1,1,5,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9,-16.10,-18.30,81,81730,0,0,256,0,0,0,0,0,0,0,60,3.10,10,10,2012.0,2438,0,999099999,1,0.0850,2,88,0.380,0.1,0.0
2022,1,1,6,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9*9?9*9*9?9*9,-16.70,-18.30,86,81573,0,0,255,0,0,0,0,0,0,0,60,3.10,10,10,2012.0,201,0,999099999,1,0.0850,2,88,0.390,0.1,0.0
2022,1,1,7,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9,-16.70,-18.90,81,81690,0,0,251,0,0,0,0,0,0,0,60,3.60,10,10,3219.0,823,0,999099999,1,0.0850,3,88,0.390,0.1,0.0
2022,1,1,8,0,?9?9?9?9E0?9?9?9*9*9?9?9?9?9?9?9?9?9*9*9?9*9,-17.20,-19.40,81,81656,137,800,253,0,0,0,0,0,0,0,70,2.60,8,8,1207.0,396,0,999099999,1,0.0850,3,88,0.400,0.2,0.0
2022,1,1,9,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9,-17.20,-19.40,81,81918,345,1415,252,23,1,23,5129,386,5129,2340,110,2.10,10,10,1600.0,212,0,999099999,1,0.0850,3,88,0.410,0.2,0.0
2022,1,1,10,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9,-16.10,-18.90,77,81730,505,1415,250,62,8,60,10947,2612,10140,4335,70,1.50,10,10,2012.0,1006,0,999099999,1,0.0850,3,88,0.420,0.3,0.0
2022,1,1,11,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9,-15.00,-18.00,76,81803,607,1415,250,124,42,108,17552,4023,16347,6800,20,2.10,10,10,2414.0,792,0,999099999,1,0.0850,4,88,0.440,0.2,0.0
2022,1,1,12,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9,-15.00,-17.80,77,82324,643,1415,249,180,36,166,22848,2807,22384,9914,20,2.10,10,10,2400.0,214,0,999099999,1,0.0850,4,88,0.470,0.2,0.0
2022,1,1,13,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9?9?9*9*9?9*9,-14.40,-17.20,77,81843,611,1415,248,228,21,219,28428,7017,25889,11729,320,3.10,10,10,4828.0,945,0,999099999,2,0.0850,4,88,0.500,0.3,0.0
2022,1,1,14,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9*9?9*9*9?9*9,-13.90,-16.70,77,81876,514,1415,242,270,112,224,31118,19196,24758,13430,260,3.10,9,9,4828.0,1006,0,999099999,2,0.0850,4,88,0.510,0.2,0.0
2022,1,1,15,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9*9?9*9*9?9*9,-13.30,-16.70,73,82429,357,1415,234,262,252,174,26333,30503,19536,14094,290,2.60,5,5,4828.0,424,0,999099999,2,0.0850,4,88,0.510,0.0,0.0
2022,1,1,16,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9*9?9*9*9?9*9,-13.90,-17.20,74,82502,152,1415,218,188,330,106,15789,26276,10770,10037,250,1.50,9,9,4828.0,6706,0,999099999,2,0.0850,4,88,0.500,0.0,0.0
2022,1,1,17,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9*9?9*9*9?9*9,-14.40,-17.80,73,82550,0,894,198,78,0,40,5562,8978,3104,3442,200,1.50,5,5,4828.0,77777,0,999099999,1,0.0850,4,88,0.500,0.0,0.0
2022,1,1,18,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9*9?9*9*9?9*9,-14.40,-17.80,73,82550,0,0,177,12,0,6,648,0,300,105,200,1.50,0,0,4828.0,77777,9,999999999,1,0.0850,4,88,0.500,0.0,0.0
2022,1,1,19,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9*9?9*9*9?9*9,-22.20,-23.90,85,82280,0,0,171,0,0,0,0,0,0,0,180,4.60,0,0,4828.0,77777,9,999999999,1,0.0850,4,88,0.500,0.0,0.0
2022,1,1,20,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9*9?9*9*9?9*9,-20.00,-21.70,85,82410,0,0,169,0,0,0,0,0,0,0,190,5.10,0,0,4828.0,77777,9,999999999,1,0.0850,4,88,0.500,0.0,0.0
2022,1,1,21,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9*9?9*9*9?9*9,-20.00,-21.70,85,82410,0,0,168,0,0,0,0,0,0,0,190,5.10,0,0,4828.0,77777,9,999999999,1,0.0850,4,88,0.490,0.0,0.0
2022,1,1,22,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9*9?9*9*9?9*9,-19.40,-22.20,76,82452,0,0,167,0,0,0,0,0,0,0,160,5.10,0,0,4828.0,77777,9,999999999,1,0.0850,4,88,0.490,0.0,0.0
2022,1,1,23,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9*9?9*9*9?9*9,-13.90,-18.30,66,82712,0,0,164,0,0,0,0,0,0,0,210,6.70,0,0,4828.0,77777,9,999999999,1,0.0850,4,88,0.490,0.0,0.0
2022,1,1,24,0,?9?9?9?9E0?9?9?9?9?9?9?9?9?9?9?9*9?9*9*9?9*9,-13.90,-18.30,66,82712,0,0,163,0,0,0,0,0,0,0,210,6.70,0,0,4828.0,77777,9,999999999,1,0.0850,8,88,0.490,0.0,0.0
)";

  boost::optional<EpwFile> epwFile_ = EpwFile::loadFromString(epwFileContent);
  ASSERT_TRUE(epwFile_);
  auto epwFile = std::move(*epwFile_);

  // Up to here, everything should be the same as the first test. Now ask for the design conditions
  std::vector<EpwDesignCondition> designs = epwFile.designConditions();
  EXPECT_EQ(1, designs.size());
  const auto& dc = designs.front();

  EXPECT_EQ(dc.ashraeHoFVersion(), ASHRAEHoFVintage::ASHRAE_2017);

  EXPECT_EQ("2017 ASHRAE Handbook -- Fundamentals - Chapter 14 Climatic Design Information", dc.titleOfDesignCondition());

  // Heating,12,-17.9,-14.6,-22.0,0.6,-11.2,-19.6,0.8,-6.5,13.3,5.7,11.8,2.7,3.4,230,0.635
  EXPECT_EQ(12, dc.heatingColdestMonth().get());
  EXPECT_EQ(-17.9, dc.heatingDryBulb99pt6().get());
  EXPECT_EQ(-17.9, dc.getFieldByName("Heating Dry Bulb Temperature 99.6%").get());
  EXPECT_EQ(-17.9, dc.getField(EpwDesignField("Heating Dry Bulb Temperature 99.6%")).get());
  EXPECT_EQ("C", dc.getUnitsByName("Heating Dry Bulb Temperature 99.6%").get());
  EXPECT_EQ("C", dc.getUnits(EpwDesignField("Heating Dry Bulb Temperature 99.6%")));
  EXPECT_EQ(-14.6, dc.heatingDryBulb99().get());
  EXPECT_EQ(-22.0, dc.heatingHumidificationDewPoint99pt6().get());
  EXPECT_EQ(0.6, dc.heatingHumidificationHumidityRatio99pt6().get());
  EXPECT_EQ(-11.2, dc.heatingHumidificationMeanCoincidentDryBulb99pt6().get());
  EXPECT_EQ(-19.6, dc.heatingHumidificationDewPoint99().get());
  EXPECT_EQ(0.8, dc.heatingHumidificationHumidityRatio99().get());
  EXPECT_EQ(-6.5, dc.heatingHumidificationMeanCoincidentDryBulb99().get());
  EXPECT_EQ(13.3, dc.heatingColdestMonthWindSpeed0pt4().get());
  EXPECT_EQ(5.7, dc.heatingColdestMonthMeanCoincidentDryBulb0pt4().get());
  EXPECT_EQ(11.8, dc.heatingColdestMonthWindSpeed1().get());
  EXPECT_EQ(2.7, dc.heatingColdestMonthMeanCoincidentDryBulb1().get());
  EXPECT_EQ(3.4, dc.heatingMeanCoincidentWindSpeed99pt6().get());
  EXPECT_EQ(230, dc.heatingPrevailingCoincidentWindDirection99pt6().get());
  EXPECT_FALSE(dc.heatingWindShelterFactor());

  // Cooling,7,15.3,34.9,15.5,33.5,15.4,32.0,15.3,18.2,27.2,17.6,27.0,16.9,26.4,4.2,20,15.9,13.8,20.1,15.0,13.0,19.9,14.1,12.3,19.7,58.3,26.9,55.8,26.8,53.8,26.3,20.7
  EXPECT_EQ(7, dc.coolingHottestMonth().get());
  EXPECT_EQ(15.3, dc.coolingDryBulbRange().get());
  EXPECT_EQ(34.9, dc.coolingDryBulb0pt4().get());
  EXPECT_EQ(15.5, dc.coolingMeanCoincidentWetBulb0pt4().get());
  EXPECT_EQ(33.5, dc.coolingDryBulb1().get());
  EXPECT_EQ(15.4, dc.coolingMeanCoincidentWetBulb1().get());
  EXPECT_EQ(32.0, dc.coolingDryBulb2().get());
  EXPECT_EQ(15.3, dc.coolingMeanCoincidentWetBulb2().get());
  EXPECT_EQ(18.2, dc.coolingEvaporationWetBulb0pt4().get());
  EXPECT_EQ(27.2, dc.coolingEvaporationMeanCoincidentDryBulb0pt4().get());
  EXPECT_EQ(17.6, dc.coolingEvaporationWetBulb1().get());
  EXPECT_EQ(27.0, dc.coolingEvaporationMeanCoincidentDryBulb1().get());
  EXPECT_EQ(16.9, dc.coolingEvaporationWetBulb2().get());
  EXPECT_EQ(26.4, dc.coolingEvaporationMeanCoincidentDryBulb2().get());
  EXPECT_EQ(4.2, dc.coolingMeanCoincidentWindSpeed0pt4().get());
  EXPECT_EQ(20, dc.coolingPrevailingCoincidentWindDirection0pt4().get());
  EXPECT_EQ(15.9, dc.coolingDehumidificationDewPoint0pt4().get());
  EXPECT_EQ(13.8, dc.coolingDehumidificationHumidityRatio0pt4().get());
  EXPECT_EQ(20.1, dc.coolingDehumidificationMeanCoincidentDryBulb0pt4().get());
  EXPECT_EQ(15.0, dc.coolingDehumidificationDewPoint1().get());
  EXPECT_EQ(13.0, dc.coolingDehumidificationHumidityRatio1().get());
  EXPECT_EQ(19.9, dc.coolingDehumidificationMeanCoincidentDryBulb1().get());
  EXPECT_EQ(14.1, dc.coolingDehumidificationDewPoint2().get());
  EXPECT_EQ(12.3, dc.coolingDehumidificationHumidityRatio2().get());
  EXPECT_EQ(19.7, dc.coolingDehumidificationMeanCoincidentDryBulb2().get());
  EXPECT_EQ(58.3, dc.coolingEnthalpy0pt4().get());
  EXPECT_EQ(26.9, dc.coolingEnthalpyMeanCoincidentDryBulb0pt4().get());
  EXPECT_EQ(55.8, dc.coolingEnthalpy1().get());
  EXPECT_EQ(26.8, dc.coolingEnthalpyMeanCoincidentDryBulb1().get());
  EXPECT_EQ(53.8, dc.coolingEnthalpy2().get());
  EXPECT_EQ(26.3, dc.coolingEnthalpyMeanCoincidentDryBulb2().get());

  EXPECT_FALSE(dc.coolingHours8To4AndDryBulb12pt8To20pt6());

  ASSERT_TRUE(dc.coolingExtremeMaxWetBulb());
  EXPECT_EQ(20.7, dc.coolingExtremeMaxWetBulb().get());

  // Extremes,12.1,10.6,8.9,-23.5,37.4,3.1,1.1,-25.8,38.2,-27.6,38.9,-29.3,39.5,-31.6,40.3
  EXPECT_EQ(12.1, dc.extremeWindSpeed1().get());
  EXPECT_EQ(10.6, dc.extremeWindSpeed2pt5().get());
  EXPECT_EQ(8.9, dc.extremeWindSpeed5().get());
  ASSERT_TRUE(dc.extremeMaxWetBulb());
  EXPECT_EQ(20.7, dc.extremeMaxWetBulb().get());
  EXPECT_EQ(-23.5, dc.extremeMeanMinDryBulb().get());
  EXPECT_EQ(37.4, dc.extremeMeanMaxDryBulb().get());
  EXPECT_EQ(3.1, dc.extremeStdDevMinDryBulb().get());
  EXPECT_EQ(1.1, dc.extremeStdDevMaxDryBulb().get());
  EXPECT_EQ(-25.8, dc.extremeN5YearsMinDryBulb().get());
  EXPECT_EQ(38.2, dc.extremeN5YearsMaxDryBulb().get());
  EXPECT_EQ(-27.6, dc.extremeN10YearsMinDryBulb().get());
  EXPECT_EQ(38.9, dc.extremeN10YearsMaxDryBulb().get());
  EXPECT_EQ(-29.3, dc.extremeN20YearsMinDryBulb().get());
  EXPECT_EQ(39.5, dc.extremeN20YearsMaxDryBulb().get());
  EXPECT_EQ(-31.6, dc.extremeN50YearsMinDryBulb().get());
  EXPECT_EQ(40.3, dc.extremeN50YearsMaxDryBulb().get());
}
