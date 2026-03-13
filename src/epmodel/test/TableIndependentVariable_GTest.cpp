/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Curve/TableLookup.hpp"
#include "../ResourceObject/TableIndependentVariable.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, TableIndependentVariable_DefaultConstructor) {
  Model model;
  TableIndependentVariable tableIndependentVariable(model);

  EXPECT_EQ(TableIndependentVariable::iddObjectType(), tableIndependentVariable.iddObject().type());
  EXPECT_EQ("Linear", tableIndependentVariable.interpolationMethod());
  EXPECT_EQ("Constant", tableIndependentVariable.extrapolationMethod());
  EXPECT_EQ("Dimensionless", tableIndependentVariable.unitType());
  EXPECT_TRUE(tableIndependentVariable.values().empty());
}

TEST_F(EPModelFixture, TableIndependentVariable_ScalarAndValueParity) {
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

  EXPECT_TRUE(tableIndependentVariable.addValue(1.0));
  EXPECT_TRUE(tableIndependentVariable.addValue(2.0));
  EXPECT_EQ(2u, tableIndependentVariable.numberofValues());
  EXPECT_EQ(std::vector<double>({1.0, 2.0}), tableIndependentVariable.values());
  EXPECT_TRUE(tableIndependentVariable.removeValue(0));
  EXPECT_EQ(std::vector<double>({2.0}), tableIndependentVariable.values());
  EXPECT_TRUE(tableIndependentVariable.setValues({3.0, 4.0, 5.0}));
  EXPECT_EQ(std::vector<double>({3.0, 4.0, 5.0}), tableIndependentVariable.values());

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
}

TEST_F(EPModelFixture, TableIndependentVariable_ReverseLookupParity) {
  Model model;
  TableIndependentVariable independentVariable(model);
  TableLookup tableLookup(model);

  EXPECT_TRUE(independentVariable.tableLookups().empty());
  EXPECT_TRUE(tableLookup.addIndependentVariable(independentVariable));
  ASSERT_EQ(1u, independentVariable.tableLookups().size());
  EXPECT_EQ(tableLookup.handle(), independentVariable.tableLookups()[0].handle());
}
