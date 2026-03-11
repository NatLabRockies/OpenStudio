/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/ZoneCrossMixing.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneCrossMixing_DefaultConstructor) {
  Model model;
  ZoneCrossMixing mixing(model);

  EXPECT_EQ(ZoneCrossMixing::iddObjectType(), mixing.iddObject().type());
  EXPECT_EQ("Flow/Zone", mixing.designFlowRateCalculationMethod());
  EXPECT_TRUE(mixing.isDesignFlowRateCalculationMethodDefaulted());
  EXPECT_DOUBLE_EQ(0.0, mixing.deltaTemperature());
  EXPECT_TRUE(mixing.isDeltaTemperatureDefaulted());
  EXPECT_FALSE(mixing.designFlowRate());
  EXPECT_FALSE(mixing.flowRateperFloorArea());
  EXPECT_FALSE(mixing.flowRateperPerson());
  EXPECT_FALSE(mixing.airChangesperHour());
}

TEST_F(EPModelFixture, ZoneCrossMixing_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneCrossMixing mixing(model);

  EXPECT_TRUE(mixing.setDesignFlowRate(0.45));
  EXPECT_TRUE(mixing.setFlowRateperFloorArea(0.001));
  EXPECT_TRUE(mixing.setFlowRateperPerson(0.0035));
  EXPECT_TRUE(mixing.setAirChangesperHour(2.75));
  EXPECT_TRUE(mixing.setDeltaTemperature(4.5));
  EXPECT_TRUE(mixing.setDesignFlowRateCalculationMethod("Flow/Area"));

  EXPECT_TRUE(mixing.designFlowRate());
  EXPECT_DOUBLE_EQ(0.45, *mixing.designFlowRate());
  EXPECT_TRUE(mixing.flowRateperFloorArea());
  EXPECT_DOUBLE_EQ(0.001, *mixing.flowRateperFloorArea());
  EXPECT_TRUE(mixing.flowRateperPerson());
  EXPECT_DOUBLE_EQ(0.0035, *mixing.flowRateperPerson());
  EXPECT_TRUE(mixing.airChangesperHour());
  EXPECT_DOUBLE_EQ(2.75, *mixing.airChangesperHour());
  EXPECT_DOUBLE_EQ(4.5, mixing.deltaTemperature());
  EXPECT_FALSE(mixing.isDeltaTemperatureDefaulted());
  EXPECT_EQ("Flow/Area", mixing.designFlowRateCalculationMethod());
  EXPECT_FALSE(mixing.isDesignFlowRateCalculationMethodDefaulted());

  mixing.resetDeltaTemperature();
  EXPECT_TRUE(mixing.isDeltaTemperatureDefaulted());
  EXPECT_DOUBLE_EQ(0.0, mixing.deltaTemperature());

  mixing.resetDesignFlowRateCalculationMethod();
  EXPECT_TRUE(mixing.isDesignFlowRateCalculationMethodDefaulted());
  EXPECT_EQ("Flow/Zone", mixing.designFlowRateCalculationMethod());
}
