/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../SpaceLoadInstance/People.hpp"
#include <utilities/idd/People_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, People_DefaultConstructor) {
  Model model;
  People object(model);
  EXPECT_EQ(People::iddObjectType(), object.iddObject().type());
  EXPECT_FALSE(object.nameString().empty());
}

TEST_F(EPModelFixture, People_ScalarAccessors_RoundTrip) {
  Model model;
  People object(model);

  EXPECT_TRUE(object.setClothingInsulationCalculationMethod("CalculationMethodSchedule"));
  EXPECT_EQ("CalculationMethodSchedule", object.clothingInsulationCalculationMethod());

  EXPECT_TRUE(object.setColdStressTemperatureThreshold(12.5));
  EXPECT_DOUBLE_EQ(12.5, object.coldStressTemperatureThreshold());
  object.resetColdStressTemperatureThreshold();
  EXPECT_TRUE(object.isColdStressTemperatureThresholdDefaulted());

  EXPECT_TRUE(object.setHeatStressTemperatureThreshold(33.5));
  EXPECT_DOUBLE_EQ(33.5, object.heatStressTemperatureThreshold());
  object.resetHeatStressTemperatureThreshold();
  EXPECT_TRUE(object.isHeatStressTemperatureThresholdDefaulted());

  // Verify multiplier compatibility semantics on translated scalar person-density fields.
  EXPECT_TRUE(object.setString(openstudio::PeopleFields::NumberofPeopleCalculationMethod, "People"));
  EXPECT_TRUE(object.setDouble(openstudio::PeopleFields::NumberofPeople, 10.0));
  EXPECT_TRUE(object.setMultiplier(2.0));
  EXPECT_DOUBLE_EQ(20.0, object.getDouble(openstudio::PeopleFields::NumberofPeople, true).get());
}
