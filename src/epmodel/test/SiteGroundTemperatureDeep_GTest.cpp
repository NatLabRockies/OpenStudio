/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/SiteGroundTemperatureDeep.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SiteGroundTemperatureDeep_DefaultConstructor) {
  Model model;
  SiteGroundTemperatureDeep object(model);
  EXPECT_EQ(SiteGroundTemperatureDeep::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, SiteGroundTemperatureDeep_ScalarAccessors_RoundTrip) {
  Model model;
  SiteGroundTemperatureDeep object(model);

  EXPECT_TRUE(object.isJanuaryDeepGroundTemperatureDefaulted());
  EXPECT_DOUBLE_EQ(16.0, object.januaryDeepGroundTemperature());
  EXPECT_TRUE(object.setJanuaryDeepGroundTemperature(10.0));
  EXPECT_DOUBLE_EQ(10.0, object.januaryDeepGroundTemperature());
  EXPECT_FALSE(object.isJanuaryDeepGroundTemperatureDefaulted());
  object.resetJanuaryDeepGroundTemperature();
  EXPECT_TRUE(object.isJanuaryDeepGroundTemperatureDefaulted());

  EXPECT_TRUE(object.isFebruaryDeepGroundTemperatureDefaulted());
  EXPECT_DOUBLE_EQ(16.0, object.februaryDeepGroundTemperature());
  EXPECT_TRUE(object.setFebruaryDeepGroundTemperature(11.0));
  EXPECT_DOUBLE_EQ(11.0, object.februaryDeepGroundTemperature());
  EXPECT_FALSE(object.isFebruaryDeepGroundTemperatureDefaulted());
  object.resetFebruaryDeepGroundTemperature();
  EXPECT_TRUE(object.isFebruaryDeepGroundTemperatureDefaulted());

  EXPECT_TRUE(object.isMarchDeepGroundTemperatureDefaulted());
  EXPECT_DOUBLE_EQ(16.0, object.marchDeepGroundTemperature());
  EXPECT_TRUE(object.setMarchDeepGroundTemperature(12.0));
  EXPECT_DOUBLE_EQ(12.0, object.marchDeepGroundTemperature());
  EXPECT_FALSE(object.isMarchDeepGroundTemperatureDefaulted());
  object.resetMarchDeepGroundTemperature();
  EXPECT_TRUE(object.isMarchDeepGroundTemperatureDefaulted());

  EXPECT_TRUE(object.isAprilDeepGroundTemperatureDefaulted());
  EXPECT_DOUBLE_EQ(16.0, object.aprilDeepGroundTemperature());
  EXPECT_TRUE(object.setAprilDeepGroundTemperature(13.0));
  EXPECT_DOUBLE_EQ(13.0, object.aprilDeepGroundTemperature());
  EXPECT_FALSE(object.isAprilDeepGroundTemperatureDefaulted());
  object.resetAprilDeepGroundTemperature();
  EXPECT_TRUE(object.isAprilDeepGroundTemperatureDefaulted());

  EXPECT_TRUE(object.isMayDeepGroundTemperatureDefaulted());
  EXPECT_DOUBLE_EQ(16.0, object.mayDeepGroundTemperature());
  EXPECT_TRUE(object.setMayDeepGroundTemperature(14.0));
  EXPECT_DOUBLE_EQ(14.0, object.mayDeepGroundTemperature());
  EXPECT_FALSE(object.isMayDeepGroundTemperatureDefaulted());
  object.resetMayDeepGroundTemperature();
  EXPECT_TRUE(object.isMayDeepGroundTemperatureDefaulted());

  EXPECT_TRUE(object.isJuneDeepGroundTemperatureDefaulted());
  EXPECT_DOUBLE_EQ(16.0, object.juneDeepGroundTemperature());
  EXPECT_TRUE(object.setJuneDeepGroundTemperature(15.0));
  EXPECT_DOUBLE_EQ(15.0, object.juneDeepGroundTemperature());
  EXPECT_FALSE(object.isJuneDeepGroundTemperatureDefaulted());
  object.resetJuneDeepGroundTemperature();
  EXPECT_TRUE(object.isJuneDeepGroundTemperatureDefaulted());

  EXPECT_TRUE(object.isJulyDeepGroundTemperatureDefaulted());
  EXPECT_DOUBLE_EQ(16.0, object.julyDeepGroundTemperature());
  EXPECT_TRUE(object.setJulyDeepGroundTemperature(16.0));
  EXPECT_DOUBLE_EQ(16.0, object.julyDeepGroundTemperature());
  EXPECT_FALSE(object.isJulyDeepGroundTemperatureDefaulted());
  object.resetJulyDeepGroundTemperature();
  EXPECT_TRUE(object.isJulyDeepGroundTemperatureDefaulted());

  EXPECT_TRUE(object.isAugustDeepGroundTemperatureDefaulted());
  EXPECT_DOUBLE_EQ(16.0, object.augustDeepGroundTemperature());
  EXPECT_TRUE(object.setAugustDeepGroundTemperature(17.0));
  EXPECT_DOUBLE_EQ(17.0, object.augustDeepGroundTemperature());
  EXPECT_FALSE(object.isAugustDeepGroundTemperatureDefaulted());
  object.resetAugustDeepGroundTemperature();
  EXPECT_TRUE(object.isAugustDeepGroundTemperatureDefaulted());

  EXPECT_TRUE(object.isSeptemberDeepGroundTemperatureDefaulted());
  EXPECT_DOUBLE_EQ(16.0, object.septemberDeepGroundTemperature());
  EXPECT_TRUE(object.setSeptemberDeepGroundTemperature(18.0));
  EXPECT_DOUBLE_EQ(18.0, object.septemberDeepGroundTemperature());
  EXPECT_FALSE(object.isSeptemberDeepGroundTemperatureDefaulted());
  object.resetSeptemberDeepGroundTemperature();
  EXPECT_TRUE(object.isSeptemberDeepGroundTemperatureDefaulted());

  EXPECT_TRUE(object.isOctoberDeepGroundTemperatureDefaulted());
  EXPECT_DOUBLE_EQ(16.0, object.octoberDeepGroundTemperature());
  EXPECT_TRUE(object.setOctoberDeepGroundTemperature(19.0));
  EXPECT_DOUBLE_EQ(19.0, object.octoberDeepGroundTemperature());
  EXPECT_FALSE(object.isOctoberDeepGroundTemperatureDefaulted());
  object.resetOctoberDeepGroundTemperature();
  EXPECT_TRUE(object.isOctoberDeepGroundTemperatureDefaulted());

  EXPECT_TRUE(object.isNovemberDeepGroundTemperatureDefaulted());
  EXPECT_DOUBLE_EQ(16.0, object.novemberDeepGroundTemperature());
  EXPECT_TRUE(object.setNovemberDeepGroundTemperature(20.0));
  EXPECT_DOUBLE_EQ(20.0, object.novemberDeepGroundTemperature());
  EXPECT_FALSE(object.isNovemberDeepGroundTemperatureDefaulted());
  object.resetNovemberDeepGroundTemperature();
  EXPECT_TRUE(object.isNovemberDeepGroundTemperatureDefaulted());

  EXPECT_TRUE(object.isDecemberDeepGroundTemperatureDefaulted());
  EXPECT_TRUE(object.setDecemberDeepGroundTemperature(21.0));
  EXPECT_DOUBLE_EQ(21.0, object.decemberDeepGroundTemperature());
  EXPECT_FALSE(object.isDecemberDeepGroundTemperatureDefaulted());
  object.resetDecemberDeepGroundTemperature();
  EXPECT_TRUE(object.isDecemberDeepGroundTemperatureDefaulted());
}
