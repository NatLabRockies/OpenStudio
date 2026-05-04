/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"

#include "../ModelObject/OutputControlTableStyle.hpp"
#include "../ModelObject/OutputControlTableStyle_Impl.hpp"

#include <algorithm>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, OutputControlTableStyle_DefaultConstructor) {
  Model model;
  auto object = model.getUniqueModelObject<OutputControlTableStyle>();

  EXPECT_EQ(OutputControlTableStyle::iddObjectType(), object.iddObject().type());
  EXPECT_EQ("HTML", object.columnSeparator());
  EXPECT_EQ("None", object.unitConversion());
}

TEST_F(EPModelFixture, OutputControlTableStyle_ScalarAccessors_RoundTrip) {
  Model model;
  auto object = model.getUniqueModelObject<OutputControlTableStyle>();

  const auto columnSeparatorValues = OutputControlTableStyle::columnSeparatorValues();
  EXPECT_NE(columnSeparatorValues.end(), std::find(columnSeparatorValues.begin(), columnSeparatorValues.end(), "Tab"));
  EXPECT_NE(columnSeparatorValues.end(), std::find(columnSeparatorValues.begin(), columnSeparatorValues.end(), "Fixed"));

  const auto unitConversionValues = OutputControlTableStyle::unitConversionValues();
  EXPECT_NE(unitConversionValues.end(), std::find(unitConversionValues.begin(), unitConversionValues.end(), "JtoKWH"));
  EXPECT_NE(unitConversionValues.end(),
            std::find(unitConversionValues.begin(), unitConversionValues.end(), "InchPoundExceptElectricity"));

  EXPECT_FALSE(object.setColumnSeparator("bad value"));
  EXPECT_FALSE(object.setUnitConversion("bad value"));

  EXPECT_TRUE(object.setColumnSeparator("Tab"));
  EXPECT_TRUE(object.setUnitConversion("JtoKWH"));
  EXPECT_EQ("Tab", object.columnSeparator());
  EXPECT_EQ("JtoKWH", object.unitConversion());

  EXPECT_TRUE(object.setUnitConversion("InchPoundExceptElectricity"));
  EXPECT_EQ("InchPoundExceptElectricity", object.unitConversion());
}
