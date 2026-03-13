/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Curve/TableLookup.hpp"
#include "../ResourceObject/TableIndependentVariable.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, TableLookup_DefaultConstructor) {
  Model model;
  TableLookup tableLookup(model);

  EXPECT_EQ(TableLookup::iddObjectType(), tableLookup.iddObject().type());
  EXPECT_EQ("None", tableLookup.normalizationMethod());
  EXPECT_DOUBLE_EQ(1.0, tableLookup.normalizationDivisor());
  EXPECT_FALSE(tableLookup.minimumOutput());
  EXPECT_FALSE(tableLookup.maximumOutput());
  EXPECT_EQ("Dimensionless", tableLookup.outputUnitType());
  EXPECT_TRUE(tableLookup.outputValues().empty());
  EXPECT_TRUE(tableLookup.independentVariables().empty());
}

TEST_F(EPModelFixture, TableLookup_ScalarAndRelationshipParity) {
  Model model;
  TableLookup tableLookup(model);
  TableIndependentVariable independentVariable(model);

  EXPECT_TRUE(tableLookup.setNormalizationMethod("DivisorOnly"));
  EXPECT_EQ("DivisorOnly", tableLookup.normalizationMethod());

  EXPECT_FALSE(tableLookup.setNormalizationDivisor(0.0));
  EXPECT_TRUE(tableLookup.setNormalizationDivisor(2.5));
  EXPECT_DOUBLE_EQ(2.5, tableLookup.normalizationDivisor());

  EXPECT_TRUE(tableLookup.setMinimumOutput(1.2));
  ASSERT_TRUE(tableLookup.minimumOutput());
  EXPECT_DOUBLE_EQ(1.2, tableLookup.minimumOutput().get());

  EXPECT_TRUE(tableLookup.setMaximumOutput(3.4));
  ASSERT_TRUE(tableLookup.maximumOutput());
  EXPECT_DOUBLE_EQ(3.4, tableLookup.maximumOutput().get());

  EXPECT_TRUE(tableLookup.setOutputUnitType("Capacity"));
  EXPECT_EQ("Capacity", tableLookup.outputUnitType());

  EXPECT_TRUE(tableLookup.addOutputValue(10.0));
  EXPECT_TRUE(tableLookup.addOutputValue(20.0));
  EXPECT_EQ(2u, tableLookup.numberofOutputValues());
  EXPECT_EQ(std::vector<double>({10.0, 20.0}), tableLookup.outputValues());
  EXPECT_TRUE(tableLookup.removeOutputValue(0));
  EXPECT_EQ(std::vector<double>({20.0}), tableLookup.outputValues());
  EXPECT_TRUE(tableLookup.setOutputValues({1.0, 2.0, 3.0}));
  EXPECT_EQ(std::vector<double>({1.0, 2.0, 3.0}), tableLookup.outputValues());

  EXPECT_TRUE(tableLookup.addIndependentVariable(independentVariable));
  EXPECT_FALSE(tableLookup.addIndependentVariable(independentVariable));
  ASSERT_EQ(1u, tableLookup.independentVariables().size());
  EXPECT_EQ(independentVariable.handle(), tableLookup.independentVariables()[0].handle());
  ASSERT_EQ(1u, independentVariable.tableLookups().size());
  EXPECT_EQ(tableLookup.handle(), independentVariable.tableLookups()[0].handle());

  EXPECT_TRUE(tableLookup.removeIndependentVariable(independentVariable));
  EXPECT_TRUE(tableLookup.independentVariables().empty());
  EXPECT_TRUE(independentVariable.tableLookups().empty());

  tableLookup.removeAllOutputValues();
  EXPECT_TRUE(tableLookup.outputValues().empty());

  tableLookup.resetMinimumOutput();
  EXPECT_FALSE(tableLookup.minimumOutput());

  tableLookup.resetMaximumOutput();
  EXPECT_FALSE(tableLookup.maximumOutput());
}
