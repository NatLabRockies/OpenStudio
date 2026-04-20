/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"

#include "../scaffolds/OutputVariableDictionary.hpp"

#include <algorithm>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, OutputVariableDictionary_DefaultConstructor) {
  Model model;
  OutputVariableDictionary outputVariableDictionary(model);

  EXPECT_EQ(OutputVariableDictionary::iddObjectType(), outputVariableDictionary.iddObject().type());
  EXPECT_TRUE(outputVariableDictionary.isKeyFieldDefaulted());
  EXPECT_EQ("regular", outputVariableDictionary.keyField());
  EXPECT_FALSE(outputVariableDictionary.sortOption());

  const auto keyFieldValues = OutputVariableDictionary::keyFieldValues();
  EXPECT_NE(keyFieldValues.end(), std::find(keyFieldValues.begin(), keyFieldValues.end(), "IDF"));
  EXPECT_NE(keyFieldValues.end(), std::find(keyFieldValues.begin(), keyFieldValues.end(), "regular"));

  const auto sortOptionValues = OutputVariableDictionary::sortOptionValues();
  EXPECT_NE(sortOptionValues.end(), std::find(sortOptionValues.begin(), sortOptionValues.end(), "Name"));
  EXPECT_NE(sortOptionValues.end(), std::find(sortOptionValues.begin(), sortOptionValues.end(), "Unsorted"));
}

TEST_F(EPModelFixture, OutputVariableDictionary_ScalarAccessors_RoundTrip) {
  Model model;
  OutputVariableDictionary outputVariableDictionary(model);

  EXPECT_TRUE(outputVariableDictionary.setKeyField("IDF"));
  EXPECT_FALSE(outputVariableDictionary.isKeyFieldDefaulted());
  EXPECT_EQ("IDF", outputVariableDictionary.keyField());

  EXPECT_TRUE(outputVariableDictionary.setSortOption("Unsorted"));
  ASSERT_TRUE(outputVariableDictionary.sortOption());
  EXPECT_EQ("Unsorted", outputVariableDictionary.sortOption().get());

  EXPECT_FALSE(outputVariableDictionary.setKeyField("BadEnum"));
  EXPECT_EQ("IDF", outputVariableDictionary.keyField());

  EXPECT_FALSE(outputVariableDictionary.setSortOption("BadEnum"));
  ASSERT_TRUE(outputVariableDictionary.sortOption());
  EXPECT_EQ("Unsorted", outputVariableDictionary.sortOption().get());

  outputVariableDictionary.resetKeyField();
  outputVariableDictionary.resetSortOption();

  EXPECT_TRUE(outputVariableDictionary.isKeyFieldDefaulted());
  EXPECT_EQ("regular", outputVariableDictionary.keyField());
  const auto resetSortOption = outputVariableDictionary.sortOption();
  if (resetSortOption) {
    EXPECT_TRUE(resetSortOption->empty());
  }
}
