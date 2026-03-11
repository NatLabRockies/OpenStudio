/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ResourceObject/TableIndependentVariable.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, TableIndependentVariable_DefaultConstructor) {
  Model model;
  TableIndependentVariable tableIndependentVariable(model);
  EXPECT_EQ(TableIndependentVariable::iddObjectType(), tableIndependentVariable.iddObject().type());
}

TEST_F(EPModelFixture, TableIndependentVariable_ScalarAccessors_RoundTrip) {
  Model model;
  TableIndependentVariable tableIndependentVariable(model);

  EXPECT_TRUE(tableIndependentVariable.setInterpolationMethod("Cubic"));
  EXPECT_EQ("Cubic", tableIndependentVariable.interpolationMethod());
  EXPECT_FALSE(tableIndependentVariable.isInterpolationMethodDefaulted());

  EXPECT_TRUE(tableIndependentVariable.setExtrapolationMethod("Linear"));
  EXPECT_EQ("Linear", tableIndependentVariable.extrapolationMethod());
  EXPECT_FALSE(tableIndependentVariable.isExtrapolationMethodDefaulted());

  EXPECT_TRUE(tableIndependentVariable.setMinimumValue(10.0));
  ASSERT_TRUE(tableIndependentVariable.minimumValue());
  EXPECT_DOUBLE_EQ(10.0, tableIndependentVariable.minimumValue().get());

  EXPECT_TRUE(tableIndependentVariable.setMaximumValue(20.0));
  ASSERT_TRUE(tableIndependentVariable.maximumValue());
  EXPECT_DOUBLE_EQ(20.0, tableIndependentVariable.maximumValue().get());

  EXPECT_TRUE(tableIndependentVariable.setNormalizationReferenceValue(5.0));
  ASSERT_TRUE(tableIndependentVariable.normalizationReferenceValue());
  EXPECT_DOUBLE_EQ(5.0, tableIndependentVariable.normalizationReferenceValue().get());

  EXPECT_TRUE(tableIndependentVariable.setUnitType("Temperature"));
  EXPECT_EQ("Temperature", tableIndependentVariable.unitType());
  EXPECT_FALSE(tableIndependentVariable.isUnitTypeDefaulted());

  EXPECT_TRUE(tableIndependentVariable.setExternalFileName("table.csv"));
  ASSERT_TRUE(tableIndependentVariable.externalFileName());
  EXPECT_EQ("table.csv", tableIndependentVariable.externalFileName().get());

  EXPECT_TRUE(tableIndependentVariable.setExternalFileColumnNumber(2));
  ASSERT_TRUE(tableIndependentVariable.externalFileColumnNumber());
  EXPECT_EQ(2, tableIndependentVariable.externalFileColumnNumber().get());

  EXPECT_TRUE(tableIndependentVariable.setExternalFileStartingRowNumber(5));
  ASSERT_TRUE(tableIndependentVariable.externalFileStartingRowNumber());
  EXPECT_EQ(5, tableIndependentVariable.externalFileStartingRowNumber().get());

  tableIndependentVariable.resetInterpolationMethod();
  EXPECT_TRUE(tableIndependentVariable.isInterpolationMethodDefaulted());

  tableIndependentVariable.resetExtrapolationMethod();
  EXPECT_TRUE(tableIndependentVariable.isExtrapolationMethodDefaulted());

  tableIndependentVariable.resetMinimumValue();
  EXPECT_FALSE(tableIndependentVariable.minimumValue());

  tableIndependentVariable.resetMaximumValue();
  EXPECT_FALSE(tableIndependentVariable.maximumValue());

  tableIndependentVariable.resetNormalizationReferenceValue();
  EXPECT_FALSE(tableIndependentVariable.normalizationReferenceValue());

  tableIndependentVariable.resetUnitType();
  EXPECT_TRUE(tableIndependentVariable.isUnitTypeDefaulted());

  tableIndependentVariable.resetExternalFileName();
  EXPECT_FALSE(tableIndependentVariable.externalFileName());

  tableIndependentVariable.resetExternalFileColumnNumber();
  EXPECT_FALSE(tableIndependentVariable.externalFileColumnNumber());

  tableIndependentVariable.resetExternalFileStartingRowNumber();
  EXPECT_FALSE(tableIndependentVariable.externalFileStartingRowNumber());
}
