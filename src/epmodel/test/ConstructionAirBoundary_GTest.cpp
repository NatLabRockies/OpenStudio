/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ConstructionBase/ConstructionAirBoundary.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ConstructionAirBoundary_DefaultConstructor) {
  Model model;
  ConstructionAirBoundary object(model);
  EXPECT_EQ(ConstructionAirBoundary::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, ConstructionAirBoundary_ScalarAccessors_RoundTrip) {
  Model model;
  ConstructionAirBoundary object(model);

  EXPECT_EQ("GroupedZones", object.solarAndDaylightingMethod());
  EXPECT_TRUE(object.isSolarAndDaylightingMethodDefaulted());
  EXPECT_FALSE(object.setSolarAndDaylightingMethod("AnyValue"));

  EXPECT_EQ("GroupedZones", object.radiantExchangeMethod());
  EXPECT_TRUE(object.isRadiantExchangeMethodDefaulted());
  EXPECT_FALSE(object.setRadiantExchangeMethod("AnyValue"));

  EXPECT_TRUE(object.setAirExchangeMethod("SimpleMixing"));
  EXPECT_EQ("SimpleMixing", object.airExchangeMethod());
  EXPECT_FALSE(object.isAirExchangeMethodDefaulted());
  object.resetAirExchangeMethod();
  EXPECT_TRUE(object.isAirExchangeMethodDefaulted());

  EXPECT_TRUE(object.setSimpleMixingAirChangesPerHour(0.35));
  EXPECT_DOUBLE_EQ(0.35, object.simpleMixingAirChangesPerHour());
  EXPECT_FALSE(object.isSimpleMixingAirChangesPerHourDefaulted());
  object.resetSimpleMixingAirChangesPerHour();
  EXPECT_TRUE(object.isSimpleMixingAirChangesPerHourDefaulted());
}
