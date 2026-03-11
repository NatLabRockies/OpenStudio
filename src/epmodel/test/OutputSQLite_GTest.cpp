/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"

#include "../ModelObject/OutputSQLite.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, OutputSQLite_DefaultConstructor) {
  Model model;
  OutputSQLite outputSQLite(model);

  EXPECT_EQ(OutputSQLite::iddObjectType(), outputSQLite.iddObject().type());
  EXPECT_EQ("SimpleAndTabular", outputSQLite.optionType());
  EXPECT_EQ("UseOutputControlTableStyle", outputSQLite.unitConversionforTabularData());
}

TEST_F(EPModelFixture, OutputSQLite_ScalarAccessors_RoundTrip) {
  Model model;
  OutputSQLite outputSQLite(model);

  EXPECT_FALSE(OutputSQLite::optionTypeValues().empty());
  EXPECT_FALSE(OutputSQLite::unitConversionforTabularDataValues().empty());

  EXPECT_TRUE(outputSQLite.setOptionType("Simple"));
  EXPECT_EQ("Simple", outputSQLite.optionType());

  EXPECT_TRUE(outputSQLite.setUnitConversionforTabularData("None"));
  EXPECT_EQ("None", outputSQLite.unitConversionforTabularData());

  EXPECT_FALSE(outputSQLite.setOptionType("BadOptionType"));
  EXPECT_EQ("Simple", outputSQLite.optionType());

  EXPECT_FALSE(outputSQLite.setUnitConversionforTabularData("BadUnitConversion"));
  EXPECT_EQ("None", outputSQLite.unitConversionforTabularData());
}
