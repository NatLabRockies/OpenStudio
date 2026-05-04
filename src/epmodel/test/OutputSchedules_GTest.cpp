/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/OutputSchedules.hpp"
#include "../ModelObject/OutputSchedules_Impl.hpp"

#include <utilities/core/StringHelpers.hpp>

#include <algorithm>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, OutputSchedules_DefaultConstructor) {
  Model model;
  auto outputSchedules = model.getUniqueModelObject<OutputSchedules>();

  EXPECT_EQ(OutputSchedules::iddObjectType(), outputSchedules.iddObject().type());
  EXPECT_TRUE(openstudio::istringEqual("Hourly", outputSchedules.keyField()));
}

TEST_F(EPModelFixture, OutputSchedules_ScalarAccessors_RoundTrip) {
  Model model;
  auto outputSchedules = model.getUniqueModelObject<OutputSchedules>();

  const auto keyFieldValues = OutputSchedules::keyFieldValues();
  EXPECT_NE(keyFieldValues.end(), std::find(keyFieldValues.begin(), keyFieldValues.end(), "Hourly"));
  EXPECT_NE(keyFieldValues.end(), std::find(keyFieldValues.begin(), keyFieldValues.end(), "Timestep"));

  const auto validKeyFieldValues = OutputSchedules::validKeyFieldValues();
  EXPECT_EQ(keyFieldValues, validKeyFieldValues);

  EXPECT_TRUE(outputSchedules.setKeyField("Timestep"));
  EXPECT_TRUE(openstudio::istringEqual("Timestep", outputSchedules.keyField()));

  EXPECT_FALSE(outputSchedules.setKeyField("Invalid"));
  EXPECT_TRUE(openstudio::istringEqual("Timestep", outputSchedules.keyField()));
}
