/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ParentObject/Site.hpp"

#include <algorithm>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, Site_DefaultConstructor) {
  Model model;
  Site site(model);
  EXPECT_EQ(Site::iddObjectType(), site.iddObject().type());
}

TEST_F(EPModelFixture, Site_ScalarAccessors_RoundTrip) {
  Model model;
  Site site(model);

  const double defaultLatitude = site.latitude();
  EXPECT_TRUE(site.isLatitudeDefaulted());
  EXPECT_TRUE(site.setLatitude(39.7392));
  EXPECT_FALSE(site.isLatitudeDefaulted());
  EXPECT_DOUBLE_EQ(39.7392, site.latitude());
  site.resetLatitude();
  EXPECT_TRUE(site.isLatitudeDefaulted());
  EXPECT_DOUBLE_EQ(defaultLatitude, site.latitude());

  const double defaultLongitude = site.longitude();
  EXPECT_TRUE(site.isLongitudeDefaulted());
  EXPECT_TRUE(site.setLongitude(-104.9903));
  EXPECT_FALSE(site.isLongitudeDefaulted());
  EXPECT_DOUBLE_EQ(-104.9903, site.longitude());
  site.resetLongitude();
  EXPECT_TRUE(site.isLongitudeDefaulted());
  EXPECT_DOUBLE_EQ(defaultLongitude, site.longitude());

  const double defaultTimeZone = site.timeZone();
  EXPECT_TRUE(site.isTimeZoneDefaulted());
  EXPECT_TRUE(site.setTimeZone(-7.0));
  EXPECT_FALSE(site.isTimeZoneDefaulted());
  EXPECT_DOUBLE_EQ(-7.0, site.timeZone());
  site.resetTimeZone();
  EXPECT_TRUE(site.isTimeZoneDefaulted());
  EXPECT_DOUBLE_EQ(defaultTimeZone, site.timeZone());

  const double defaultElevation = site.elevation();
  EXPECT_TRUE(site.isElevationDefaulted());
  EXPECT_TRUE(site.setElevation(1609.3));
  EXPECT_FALSE(site.isElevationDefaulted());
  EXPECT_DOUBLE_EQ(1609.3, site.elevation());
  site.resetElevation();
  EXPECT_TRUE(site.isElevationDefaulted());
  EXPECT_DOUBLE_EQ(defaultElevation, site.elevation());

  const bool defaultKeepSiteLocationInformation = site.keepSiteLocationInformation();
  EXPECT_TRUE(site.isKeepSiteLocationInformationDefaulted());
  EXPECT_TRUE(site.setKeepSiteLocationInformation(!defaultKeepSiteLocationInformation));
  EXPECT_FALSE(site.isKeepSiteLocationInformationDefaulted());
  EXPECT_EQ(!defaultKeepSiteLocationInformation, site.keepSiteLocationInformation());
  site.resetKeepSiteLocationInformation();
  EXPECT_TRUE(site.isKeepSiteLocationInformationDefaulted());
  EXPECT_EQ(defaultKeepSiteLocationInformation, site.keepSiteLocationInformation());

  const auto terrainValues = Site::validTerrainValues();
  ASSERT_FALSE(terrainValues.empty());
  EXPECT_TRUE(std::find(terrainValues.begin(), terrainValues.end(), site.terrain()) != terrainValues.end());

  EXPECT_TRUE(site.isTerrainDefaulted());
  const auto selectedTerrain = (terrainValues.front() == site.terrain() && terrainValues.size() > 1) ? terrainValues[1] : terrainValues.front();
  EXPECT_TRUE(site.setTerrain(selectedTerrain));
  EXPECT_FALSE(site.isTerrainDefaulted());
  EXPECT_EQ(selectedTerrain, site.terrain());
  site.resetTerrain();
  EXPECT_TRUE(site.isTerrainDefaulted());
}
