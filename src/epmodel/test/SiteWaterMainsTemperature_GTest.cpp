/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/SiteWaterMainsTemperature.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SiteWaterMainsTemperature_DefaultConstructor) {
  Model model;
  SiteWaterMainsTemperature object(model);
  EXPECT_EQ(SiteWaterMainsTemperature::iddObjectType(), object.iddObject().type());
  EXPECT_EQ("CorrelationFromWeatherFile", object.calculationMethod());
  EXPECT_DOUBLE_EQ(1.0, object.temperatureMultiplier());
  EXPECT_DOUBLE_EQ(0.0, object.temperatureOffset());
}

TEST_F(EPModelFixture, SiteWaterMainsTemperature_ScalarAccessors_RoundTrip) {
  Model model;
  SiteWaterMainsTemperature object(model);

  const auto calculationMethodValues = SiteWaterMainsTemperature::calculationMethodValues();
  ASSERT_FALSE(calculationMethodValues.empty());
  EXPECT_EQ(calculationMethodValues, SiteWaterMainsTemperature::validCalculationMethodValues());
  EXPECT_TRUE(object.setCalculationMethod("Schedule"));
  EXPECT_EQ("Schedule", object.calculationMethod());

  EXPECT_FALSE(object.annualAverageOutdoorAirTemperature());
  EXPECT_TRUE(object.setAnnualAverageOutdoorAirTemperature(10.0));
  ASSERT_TRUE(object.annualAverageOutdoorAirTemperature());
  EXPECT_DOUBLE_EQ(10.0, object.annualAverageOutdoorAirTemperature().get());
  EXPECT_EQ("Correlation", object.calculationMethod());
  object.resetAnnualAverageOutdoorAirTemperature();
  EXPECT_FALSE(object.annualAverageOutdoorAirTemperature());

  EXPECT_FALSE(object.maximumDifferenceInMonthlyAverageOutdoorAirTemperatures());
  EXPECT_TRUE(object.setMaximumDifferenceInMonthlyAverageOutdoorAirTemperatures(11.0));
  ASSERT_TRUE(object.maximumDifferenceInMonthlyAverageOutdoorAirTemperatures());
  EXPECT_DOUBLE_EQ(11.0, object.maximumDifferenceInMonthlyAverageOutdoorAirTemperatures().get());
  EXPECT_FALSE(object.setMaximumDifferenceInMonthlyAverageOutdoorAirTemperatures(-0.1));
  object.resetMaximumDifferenceInMonthlyAverageOutdoorAirTemperatures();
  EXPECT_FALSE(object.maximumDifferenceInMonthlyAverageOutdoorAirTemperatures());

  EXPECT_TRUE(object.setTemperatureMultiplier(1.2));
  EXPECT_DOUBLE_EQ(1.2, object.temperatureMultiplier());
  EXPECT_FALSE(object.setTemperatureMultiplier(-0.1));

  EXPECT_TRUE(object.setTemperatureOffset(-1.5));
  EXPECT_DOUBLE_EQ(-1.5, object.temperatureOffset());
}
