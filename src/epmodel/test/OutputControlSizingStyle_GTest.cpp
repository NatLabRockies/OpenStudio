/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"

#include "../scaffolds/OutputControlSizingStyle.hpp"

#include <algorithm>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, OutputControlSizingStyle_DefaultConstructor) {
  Model model;
  OutputControlSizingStyle object(model);

  EXPECT_EQ(OutputControlSizingStyle::iddObjectType(), object.iddObject().type());
  EXPECT_EQ("Comma", object.columnSeparator());
}

TEST_F(EPModelFixture, OutputControlSizingStyle_ScalarAccessors_RoundTrip) {
  Model model;
  OutputControlSizingStyle object(model);

  const auto values = OutputControlSizingStyle::columnSeparatorValues();
  EXPECT_NE(values.end(), std::find(values.begin(), values.end(), "Comma"));
  EXPECT_NE(values.end(), std::find(values.begin(), values.end(), "Tab"));
  EXPECT_NE(values.end(), std::find(values.begin(), values.end(), "Fixed"));

  EXPECT_FALSE(object.setColumnSeparator("bad value"));

  EXPECT_TRUE(object.setColumnSeparator("Tab"));
  EXPECT_EQ("Tab", object.columnSeparator());

  EXPECT_TRUE(object.setColumnSeparator("Fixed"));
  EXPECT_EQ("Fixed", object.columnSeparator());
}
