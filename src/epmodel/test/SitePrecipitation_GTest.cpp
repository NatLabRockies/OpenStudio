/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/SitePrecipitation.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SitePrecipitation_DefaultConstructor) {
  Model model;
  SitePrecipitation object(model);
  EXPECT_EQ(SitePrecipitation::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, SitePrecipitation_ScalarAccessors_RoundTrip) {
  Model model;
  SitePrecipitation object(model);

  EXPECT_FALSE(object.precipitationModelType());
  const auto precipitationModelTypeValues = SitePrecipitation::precipitationModelTypeValues();
  ASSERT_FALSE(precipitationModelTypeValues.empty());
  EXPECT_TRUE(object.setPrecipitationModelType(precipitationModelTypeValues.front()));
  ASSERT_TRUE(object.precipitationModelType());
  EXPECT_EQ(precipitationModelTypeValues.front(), object.precipitationModelType().get());
  object.resetPrecipitationModelType();
  if (object.precipitationModelType()) {
    EXPECT_TRUE(object.precipitationModelType()->empty());
  }

  EXPECT_FALSE(object.designLevelforTotalAnnualPrecipitation());
  EXPECT_TRUE(object.setDesignLevelforTotalAnnualPrecipitation(0.75));
  ASSERT_TRUE(object.designLevelforTotalAnnualPrecipitation());
  EXPECT_DOUBLE_EQ(0.75, object.designLevelforTotalAnnualPrecipitation().get());
  object.resetDesignLevelforTotalAnnualPrecipitation();
  EXPECT_FALSE(object.designLevelforTotalAnnualPrecipitation());

  EXPECT_FALSE(object.averageTotalAnnualPrecipitation());
  EXPECT_TRUE(object.setAverageTotalAnnualPrecipitation(1.25));
  ASSERT_TRUE(object.averageTotalAnnualPrecipitation());
  EXPECT_DOUBLE_EQ(1.25, object.averageTotalAnnualPrecipitation().get());
  EXPECT_FALSE(object.setAverageTotalAnnualPrecipitation(-0.1));
  object.resetAverageTotalAnnualPrecipitation();
  EXPECT_FALSE(object.averageTotalAnnualPrecipitation());
}
