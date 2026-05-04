/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/SiteGroundTemperatureShallow.hpp"
#include "../ModelObject/SiteGroundTemperatureShallow_Impl.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SiteGroundTemperatureShallow_DefaultConstructor) {
  Model model;
  auto object = model.getUniqueModelObject<SiteGroundTemperatureShallow>();
  EXPECT_EQ(SiteGroundTemperatureShallow::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, SiteGroundTemperatureShallow_ScalarAccessors_RoundTrip) {
  Model model;
  auto object = model.getUniqueModelObject<SiteGroundTemperatureShallow>();

  EXPECT_TRUE(object.isJanuarySurfaceGroundTemperatureDefaulted());
  EXPECT_TRUE(object.setJanuarySurfaceGroundTemperature(10.0));
  EXPECT_DOUBLE_EQ(10.0, object.januarySurfaceGroundTemperature());
  EXPECT_FALSE(object.isJanuarySurfaceGroundTemperatureDefaulted());
  object.resetJanuarySurfaceGroundTemperature();
  EXPECT_TRUE(object.isJanuarySurfaceGroundTemperatureDefaulted());

  EXPECT_TRUE(object.isFebruarySurfaceGroundTemperatureDefaulted());
  EXPECT_TRUE(object.setFebruarySurfaceGroundTemperature(11.0));
  EXPECT_DOUBLE_EQ(11.0, object.februarySurfaceGroundTemperature());
  EXPECT_FALSE(object.isFebruarySurfaceGroundTemperatureDefaulted());
  object.resetFebruarySurfaceGroundTemperature();
  EXPECT_TRUE(object.isFebruarySurfaceGroundTemperatureDefaulted());

  EXPECT_TRUE(object.isMarchSurfaceGroundTemperatureDefaulted());
  EXPECT_TRUE(object.setMarchSurfaceGroundTemperature(12.0));
  EXPECT_DOUBLE_EQ(12.0, object.marchSurfaceGroundTemperature());
  EXPECT_FALSE(object.isMarchSurfaceGroundTemperatureDefaulted());
  object.resetMarchSurfaceGroundTemperature();
  EXPECT_TRUE(object.isMarchSurfaceGroundTemperatureDefaulted());

  EXPECT_TRUE(object.isAprilSurfaceGroundTemperatureDefaulted());
  EXPECT_TRUE(object.setAprilSurfaceGroundTemperature(13.0));
  EXPECT_DOUBLE_EQ(13.0, object.aprilSurfaceGroundTemperature());
  EXPECT_FALSE(object.isAprilSurfaceGroundTemperatureDefaulted());
  object.resetAprilSurfaceGroundTemperature();
  EXPECT_TRUE(object.isAprilSurfaceGroundTemperatureDefaulted());

  EXPECT_TRUE(object.isMaySurfaceGroundTemperatureDefaulted());
  EXPECT_TRUE(object.setMaySurfaceGroundTemperature(14.0));
  EXPECT_DOUBLE_EQ(14.0, object.maySurfaceGroundTemperature());
  EXPECT_FALSE(object.isMaySurfaceGroundTemperatureDefaulted());
  object.resetMaySurfaceGroundTemperature();
  EXPECT_TRUE(object.isMaySurfaceGroundTemperatureDefaulted());

  EXPECT_TRUE(object.isJuneSurfaceGroundTemperatureDefaulted());
  EXPECT_TRUE(object.setJuneSurfaceGroundTemperature(15.0));
  EXPECT_DOUBLE_EQ(15.0, object.juneSurfaceGroundTemperature());
  EXPECT_FALSE(object.isJuneSurfaceGroundTemperatureDefaulted());
  object.resetJuneSurfaceGroundTemperature();
  EXPECT_TRUE(object.isJuneSurfaceGroundTemperatureDefaulted());

  EXPECT_TRUE(object.isJulySurfaceGroundTemperatureDefaulted());
  EXPECT_TRUE(object.setJulySurfaceGroundTemperature(16.0));
  EXPECT_DOUBLE_EQ(16.0, object.julySurfaceGroundTemperature());
  EXPECT_FALSE(object.isJulySurfaceGroundTemperatureDefaulted());
  object.resetJulySurfaceGroundTemperature();
  EXPECT_TRUE(object.isJulySurfaceGroundTemperatureDefaulted());

  EXPECT_TRUE(object.isAugustSurfaceGroundTemperatureDefaulted());
  EXPECT_TRUE(object.setAugustSurfaceGroundTemperature(17.0));
  EXPECT_DOUBLE_EQ(17.0, object.augustSurfaceGroundTemperature());
  EXPECT_FALSE(object.isAugustSurfaceGroundTemperatureDefaulted());
  object.resetAugustSurfaceGroundTemperature();
  EXPECT_TRUE(object.isAugustSurfaceGroundTemperatureDefaulted());

  EXPECT_TRUE(object.isSeptemberSurfaceGroundTemperatureDefaulted());
  EXPECT_TRUE(object.setSeptemberSurfaceGroundTemperature(18.0));
  EXPECT_DOUBLE_EQ(18.0, object.septemberSurfaceGroundTemperature());
  EXPECT_FALSE(object.isSeptemberSurfaceGroundTemperatureDefaulted());
  object.resetSeptemberSurfaceGroundTemperature();
  EXPECT_TRUE(object.isSeptemberSurfaceGroundTemperatureDefaulted());

  EXPECT_TRUE(object.isOctoberSurfaceGroundTemperatureDefaulted());
  EXPECT_TRUE(object.setOctoberSurfaceGroundTemperature(19.0));
  EXPECT_DOUBLE_EQ(19.0, object.octoberSurfaceGroundTemperature());
  EXPECT_FALSE(object.isOctoberSurfaceGroundTemperatureDefaulted());
  object.resetOctoberSurfaceGroundTemperature();
  EXPECT_TRUE(object.isOctoberSurfaceGroundTemperatureDefaulted());

  EXPECT_TRUE(object.isNovemberSurfaceGroundTemperatureDefaulted());
  EXPECT_TRUE(object.setNovemberSurfaceGroundTemperature(20.0));
  EXPECT_DOUBLE_EQ(20.0, object.novemberSurfaceGroundTemperature());
  EXPECT_FALSE(object.isNovemberSurfaceGroundTemperatureDefaulted());
  object.resetNovemberSurfaceGroundTemperature();
  EXPECT_TRUE(object.isNovemberSurfaceGroundTemperatureDefaulted());

  EXPECT_TRUE(object.isDecemberSurfaceGroundTemperatureDefaulted());
  EXPECT_TRUE(object.setDecemberSurfaceGroundTemperature(21.0));
  EXPECT_DOUBLE_EQ(21.0, object.decemberSurfaceGroundTemperature());
  EXPECT_FALSE(object.isDecemberSurfaceGroundTemperatureDefaulted());
  object.resetDecemberSurfaceGroundTemperature();
  EXPECT_TRUE(object.isDecemberSurfaceGroundTemperatureDefaulted());
}
