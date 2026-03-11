/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/SkyTemperature.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SkyTemperature_DefaultConstructor) {
  Model model;
  SkyTemperature skyTemperature(model);
  EXPECT_EQ(SkyTemperature::iddObjectType(), skyTemperature.iddObject().type());
}

TEST_F(EPModelFixture, SkyTemperature_ScalarAccessors_RoundTrip) {
  Model model;
  SkyTemperature skyTemperature(model);

  EXPECT_TRUE(skyTemperature.isCalculationTypeDefaulted());
  EXPECT_TRUE(skyTemperature.setCalculationType("BerdahlMartin"));
  EXPECT_EQ("BerdahlMartin", skyTemperature.calculationType());
  EXPECT_FALSE(skyTemperature.isCalculationTypeDefaulted());
  skyTemperature.resetCalculationType();
  EXPECT_TRUE(skyTemperature.isCalculationTypeDefaulted());

  EXPECT_TRUE(skyTemperature.isUseWeatherFileHorizontalIRDefaulted());
  EXPECT_TRUE(skyTemperature.useWeatherFileHorizontalIR());
  EXPECT_TRUE(skyTemperature.setUseWeatherFileHorizontalIR(false));
  EXPECT_FALSE(skyTemperature.useWeatherFileHorizontalIR());
  EXPECT_FALSE(skyTemperature.isUseWeatherFileHorizontalIRDefaulted());
  skyTemperature.resetUseWeatherFileHorizontalIR();
  EXPECT_TRUE(skyTemperature.useWeatherFileHorizontalIR());
  EXPECT_TRUE(skyTemperature.isUseWeatherFileHorizontalIRDefaulted());
}
