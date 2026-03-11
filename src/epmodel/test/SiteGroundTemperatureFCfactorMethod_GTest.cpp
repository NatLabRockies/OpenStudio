/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/SiteGroundTemperatureFCfactorMethod.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SiteGroundTemperatureFCfactorMethod_DefaultConstructor) {
  Model model;
  SiteGroundTemperatureFCfactorMethod object(model);
  EXPECT_EQ(SiteGroundTemperatureFCfactorMethod::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, SiteGroundTemperatureFCfactorMethod_ScalarAccessors_RoundTrip) {
  Model model;
  SiteGroundTemperatureFCfactorMethod object(model);

  EXPECT_TRUE(object.isJanuaryGroundTemperatureDefaulted());
  EXPECT_TRUE(object.setJanuaryGroundTemperature(10.0));
  EXPECT_DOUBLE_EQ(10.0, object.januaryGroundTemperature());
  EXPECT_FALSE(object.isJanuaryGroundTemperatureDefaulted());
  object.resetJanuaryGroundTemperature();
  EXPECT_TRUE(object.isJanuaryGroundTemperatureDefaulted());

  EXPECT_TRUE(object.isFebruaryGroundTemperatureDefaulted());
  EXPECT_TRUE(object.setFebruaryGroundTemperature(11.0));
  EXPECT_DOUBLE_EQ(11.0, object.februaryGroundTemperature());
  EXPECT_FALSE(object.isFebruaryGroundTemperatureDefaulted());
  object.resetFebruaryGroundTemperature();
  EXPECT_TRUE(object.isFebruaryGroundTemperatureDefaulted());

  EXPECT_TRUE(object.isMarchGroundTemperatureDefaulted());
  EXPECT_TRUE(object.setMarchGroundTemperature(12.0));
  EXPECT_DOUBLE_EQ(12.0, object.marchGroundTemperature());
  EXPECT_FALSE(object.isMarchGroundTemperatureDefaulted());
  object.resetMarchGroundTemperature();
  EXPECT_TRUE(object.isMarchGroundTemperatureDefaulted());

  EXPECT_TRUE(object.isAprilGroundTemperatureDefaulted());
  EXPECT_TRUE(object.setAprilGroundTemperature(13.0));
  EXPECT_DOUBLE_EQ(13.0, object.aprilGroundTemperature());
  EXPECT_FALSE(object.isAprilGroundTemperatureDefaulted());
  object.resetAprilGroundTemperature();
  EXPECT_TRUE(object.isAprilGroundTemperatureDefaulted());

  EXPECT_TRUE(object.isMayGroundTemperatureDefaulted());
  EXPECT_TRUE(object.setMayGroundTemperature(14.0));
  EXPECT_DOUBLE_EQ(14.0, object.mayGroundTemperature());
  EXPECT_FALSE(object.isMayGroundTemperatureDefaulted());
  object.resetMayGroundTemperature();
  EXPECT_TRUE(object.isMayGroundTemperatureDefaulted());

  EXPECT_TRUE(object.isJuneGroundTemperatureDefaulted());
  EXPECT_TRUE(object.setJuneGroundTemperature(15.0));
  EXPECT_DOUBLE_EQ(15.0, object.juneGroundTemperature());
  EXPECT_FALSE(object.isJuneGroundTemperatureDefaulted());
  object.resetJuneGroundTemperature();
  EXPECT_TRUE(object.isJuneGroundTemperatureDefaulted());

  EXPECT_TRUE(object.isJulyGroundTemperatureDefaulted());
  EXPECT_TRUE(object.setJulyGroundTemperature(16.0));
  EXPECT_DOUBLE_EQ(16.0, object.julyGroundTemperature());
  EXPECT_FALSE(object.isJulyGroundTemperatureDefaulted());
  object.resetJulyGroundTemperature();
  EXPECT_TRUE(object.isJulyGroundTemperatureDefaulted());

  EXPECT_TRUE(object.isAugustGroundTemperatureDefaulted());
  EXPECT_TRUE(object.setAugustGroundTemperature(17.0));
  EXPECT_DOUBLE_EQ(17.0, object.augustGroundTemperature());
  EXPECT_FALSE(object.isAugustGroundTemperatureDefaulted());
  object.resetAugustGroundTemperature();
  EXPECT_TRUE(object.isAugustGroundTemperatureDefaulted());

  EXPECT_TRUE(object.isSeptemberGroundTemperatureDefaulted());
  EXPECT_TRUE(object.setSeptemberGroundTemperature(18.0));
  EXPECT_DOUBLE_EQ(18.0, object.septemberGroundTemperature());
  EXPECT_FALSE(object.isSeptemberGroundTemperatureDefaulted());
  object.resetSeptemberGroundTemperature();
  EXPECT_TRUE(object.isSeptemberGroundTemperatureDefaulted());

  EXPECT_TRUE(object.isOctoberGroundTemperatureDefaulted());
  EXPECT_TRUE(object.setOctoberGroundTemperature(19.0));
  EXPECT_DOUBLE_EQ(19.0, object.octoberGroundTemperature());
  EXPECT_FALSE(object.isOctoberGroundTemperatureDefaulted());
  object.resetOctoberGroundTemperature();
  EXPECT_TRUE(object.isOctoberGroundTemperatureDefaulted());

  EXPECT_TRUE(object.isNovemberGroundTemperatureDefaulted());
  EXPECT_TRUE(object.setNovemberGroundTemperature(20.0));
  EXPECT_DOUBLE_EQ(20.0, object.novemberGroundTemperature());
  EXPECT_FALSE(object.isNovemberGroundTemperatureDefaulted());
  object.resetNovemberGroundTemperature();
  EXPECT_TRUE(object.isNovemberGroundTemperatureDefaulted());

  EXPECT_TRUE(object.isDecemberGroundTemperatureDefaulted());
  EXPECT_TRUE(object.setDecemberGroundTemperature(21.0));
  EXPECT_DOUBLE_EQ(21.0, object.decemberGroundTemperature());
  EXPECT_FALSE(object.isDecemberGroundTemperatureDefaulted());
  object.resetDecemberGroundTemperature();
  EXPECT_TRUE(object.isDecemberGroundTemperatureDefaulted());
}
