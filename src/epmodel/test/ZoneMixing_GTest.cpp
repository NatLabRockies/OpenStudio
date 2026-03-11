/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/ZoneMixing.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneMixing_DefaultConstructor) {
  Model model;
  ZoneMixing mixing(model);

  EXPECT_EQ(ZoneMixing::iddObjectType(), mixing.iddObject().type());
  ASSERT_TRUE(mixing.designFlowRate());
  EXPECT_DOUBLE_EQ(0.0, *mixing.designFlowRate());
  EXPECT_EQ("Flow/Zone", mixing.designFlowRateCalculationMethod());
  EXPECT_FALSE(mixing.flowRateperFloorArea());
  EXPECT_FALSE(mixing.flowRateperPerson());
  EXPECT_FALSE(mixing.airChangesperHour());
  EXPECT_FALSE(mixing.deltaTemperature());
}

TEST_F(EPModelFixture, ZoneMixing_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneMixing mixing(model);

  ASSERT_TRUE(mixing.setFlowRateperFloorArea(1.2));
  ASSERT_TRUE(mixing.flowRateperFloorArea());
  EXPECT_DOUBLE_EQ(1.2, *mixing.flowRateperFloorArea());
  EXPECT_EQ("Flow/Area", mixing.designFlowRateCalculationMethod());

  ASSERT_TRUE(mixing.setFlowRateperPerson(2.3));
  ASSERT_TRUE(mixing.flowRateperPerson());
  EXPECT_DOUBLE_EQ(2.3, *mixing.flowRateperPerson());
  EXPECT_EQ("Flow/Person", mixing.designFlowRateCalculationMethod());

  ASSERT_TRUE(mixing.setAirChangesperHour(3.4));
  ASSERT_TRUE(mixing.airChangesperHour());
  EXPECT_DOUBLE_EQ(3.4, *mixing.airChangesperHour());
  EXPECT_EQ("AirChanges/Hour", mixing.designFlowRateCalculationMethod());

  ASSERT_TRUE(mixing.setDesignFlowRate(4.5));
  ASSERT_TRUE(mixing.designFlowRate());
  EXPECT_DOUBLE_EQ(4.5, *mixing.designFlowRate());
  EXPECT_EQ("Flow/Zone", mixing.designFlowRateCalculationMethod());
  EXPECT_FALSE(mixing.flowRateperFloorArea());
  EXPECT_FALSE(mixing.flowRateperPerson());
  EXPECT_FALSE(mixing.airChangesperHour());

  ASSERT_TRUE(mixing.setDeltaTemperature(1.6));
  ASSERT_TRUE(mixing.deltaTemperature());
  EXPECT_DOUBLE_EQ(1.6, *mixing.deltaTemperature());

  mixing.resetDeltaTemperature();
  EXPECT_FALSE(mixing.deltaTemperature());
}
