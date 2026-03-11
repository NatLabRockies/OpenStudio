/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/GroundHeatTransferBasementComBldg.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, GroundHeatTransferBasementComBldg_DefaultConstructor) {
  Model model;
  GroundHeatTransferBasementComBldg object(model);
  EXPECT_EQ(GroundHeatTransferBasementComBldg::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, GroundHeatTransferBasementComBldg_ScalarAccessors_RoundTrip) {
  Model model;
  GroundHeatTransferBasementComBldg object(model);

  EXPECT_TRUE(object.isJanuaryaveragetemperatureDefaulted());
  EXPECT_TRUE(object.isFebruaryaveragetemperatureDefaulted());
  EXPECT_TRUE(object.isMarchaveragetemperatureDefaulted());
  EXPECT_TRUE(object.isAprilaveragetemperatureDefaulted());
  EXPECT_TRUE(object.isMayaveragetemperatureDefaulted());
  EXPECT_TRUE(object.isJuneaveragetemperatureDefaulted());
  EXPECT_TRUE(object.isJulyaveragetemperatureDefaulted());
  EXPECT_TRUE(object.isAugustaveragetemperatureDefaulted());
  EXPECT_TRUE(object.isSeptemberaveragetemperatureDefaulted());
  EXPECT_TRUE(object.isOctoberaveragetemperatureDefaulted());
  EXPECT_TRUE(object.isNovemberaveragetemperatureDefaulted());
  EXPECT_TRUE(object.isDecemberaveragetemperatureDefaulted());
  EXPECT_TRUE(object.isDailyvariationsinewaveamplitudeDefaulted());

  EXPECT_TRUE(object.setJanuaryaveragetemperature(20.1));
  EXPECT_TRUE(object.setFebruaryaveragetemperature(20.2));
  EXPECT_TRUE(object.setMarchaveragetemperature(20.3));
  EXPECT_TRUE(object.setAprilaveragetemperature(20.4));
  EXPECT_TRUE(object.setMayaveragetemperature(20.5));
  EXPECT_TRUE(object.setJuneaveragetemperature(20.6));
  EXPECT_TRUE(object.setJulyaveragetemperature(20.7));
  EXPECT_TRUE(object.setAugustaveragetemperature(20.8));
  EXPECT_TRUE(object.setSeptemberaveragetemperature(20.9));
  EXPECT_TRUE(object.setOctoberaveragetemperature(21.0));
  EXPECT_TRUE(object.setNovemberaveragetemperature(21.1));
  EXPECT_TRUE(object.setDecemberaveragetemperature(21.2));
  EXPECT_TRUE(object.setDailyvariationsinewaveamplitude(2.3));

  EXPECT_DOUBLE_EQ(20.1, object.januaryaveragetemperature());
  EXPECT_DOUBLE_EQ(20.2, object.februaryaveragetemperature());
  EXPECT_DOUBLE_EQ(20.3, object.marchaveragetemperature());
  EXPECT_DOUBLE_EQ(20.4, object.aprilaveragetemperature());
  EXPECT_DOUBLE_EQ(20.5, object.mayaveragetemperature());
  EXPECT_DOUBLE_EQ(20.6, object.juneaveragetemperature());
  EXPECT_DOUBLE_EQ(20.7, object.julyaveragetemperature());
  EXPECT_DOUBLE_EQ(20.8, object.augustaveragetemperature());
  EXPECT_DOUBLE_EQ(20.9, object.septemberaveragetemperature());
  EXPECT_DOUBLE_EQ(21.0, object.octoberaveragetemperature());
  EXPECT_DOUBLE_EQ(21.1, object.novemberaveragetemperature());
  EXPECT_DOUBLE_EQ(21.2, object.decemberaveragetemperature());
  EXPECT_DOUBLE_EQ(2.3, object.dailyvariationsinewaveamplitude());

  EXPECT_FALSE(object.isDailyvariationsinewaveamplitudeDefaulted());
  object.resetDailyvariationsinewaveamplitude();
  EXPECT_TRUE(object.isDailyvariationsinewaveamplitudeDefaulted());
}
