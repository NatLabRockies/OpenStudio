/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"

#include "../ModelObject/OutputControlIlluminanceMapStyle.hpp"

#include <algorithm>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, OutputControlIlluminanceMapStyle_DefaultConstructor) {
  Model model;
  OutputControlIlluminanceMapStyle object(model);

  EXPECT_EQ(OutputControlIlluminanceMapStyle::iddObjectType(), object.iddObject().type());
  EXPECT_TRUE(object.isColumnSeparatorDefaulted());
  EXPECT_EQ("Comma", object.columnSeparator());
}

TEST_F(EPModelFixture, OutputControlIlluminanceMapStyle_ScalarAccessors_RoundTrip) {
  Model model;
  OutputControlIlluminanceMapStyle object(model);

  const auto values = OutputControlIlluminanceMapStyle::columnSeparatorValues();
  EXPECT_NE(values.end(), std::find(values.begin(), values.end(), "Comma"));
  EXPECT_NE(values.end(), std::find(values.begin(), values.end(), "Tab"));
  EXPECT_NE(values.end(), std::find(values.begin(), values.end(), "Fixed"));

  EXPECT_FALSE(object.setColumnSeparator("bad value"));
  EXPECT_TRUE(object.setColumnSeparator("Tab"));
  EXPECT_FALSE(object.isColumnSeparatorDefaulted());
  EXPECT_EQ("Tab", object.columnSeparator());

  object.resetColumnSeparator();
  EXPECT_TRUE(object.isColumnSeparatorDefaulted());
  EXPECT_EQ("Comma", object.columnSeparator());
}
