/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Curve/TableLookup.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, TableLookup_DefaultConstructor) {
  Model model;
  TableLookup tableLookup(model);
  EXPECT_EQ(TableLookup::iddObjectType(), tableLookup.iddObject().type());
}

TEST_F(EPModelFixture, TableLookup_ScalarAccessors_RoundTrip) {
  Model model;
  TableLookup tableLookup(model);

  EXPECT_TRUE(tableLookup.setNormalizationMethod("DivisorOnly"));
  EXPECT_EQ("DivisorOnly", tableLookup.normalizationMethod());

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

  EXPECT_TRUE(tableLookup.setExternalFileColumnNumber(7));
  ASSERT_TRUE(tableLookup.externalFileColumnNumber());
  EXPECT_EQ(7, tableLookup.externalFileColumnNumber().get());

  EXPECT_TRUE(tableLookup.setExternalFileStartingRowNumber(9));
  ASSERT_TRUE(tableLookup.externalFileStartingRowNumber());
  EXPECT_EQ(9, tableLookup.externalFileStartingRowNumber().get());

  tableLookup.resetMinimumOutput();
  EXPECT_FALSE(tableLookup.minimumOutput());

  tableLookup.resetMaximumOutput();
  EXPECT_FALSE(tableLookup.maximumOutput());

  tableLookup.resetExternalFileColumnNumber();
  EXPECT_FALSE(tableLookup.externalFileColumnNumber());

  tableLookup.resetExternalFileStartingRowNumber();
  EXPECT_FALSE(tableLookup.externalFileStartingRowNumber());
}
