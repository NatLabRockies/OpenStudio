/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/FaultModelHumidistatOffset.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, FaultModelHumidistatOffset_DefaultConstructor) {
  Model model;
  FaultModelHumidistatOffset fault(model);
  EXPECT_EQ(FaultModelHumidistatOffset::iddObjectType(), fault.iddObject().type());

  const auto values = FaultModelHumidistatOffset::humidistatOffsetTypeValues();
  EXPECT_FALSE(values.empty());

  EXPECT_TRUE(fault.isHumidistatOffsetTypeDefaulted());
  EXPECT_EQ("ThermostatOffsetIndependent", fault.humidistatOffsetType());

  EXPECT_TRUE(fault.isReferenceHumidistatOffsetDefaulted());
  EXPECT_DOUBLE_EQ(5.0, fault.referenceHumidistatOffset());
}

TEST_F(EPModelFixture, FaultModelHumidistatOffset_ScalarAccessors_RoundTrip) {
  Model model;
  FaultModelHumidistatOffset fault(model);

  EXPECT_TRUE(fault.setHumidistatOffsetType("ThermostatOffsetDependent"));
  EXPECT_FALSE(fault.isHumidistatOffsetTypeDefaulted());
  EXPECT_EQ("ThermostatOffsetDependent", fault.humidistatOffsetType());
  EXPECT_FALSE(fault.setHumidistatOffsetType("InvalidHumidistatOffsetType"));
  EXPECT_EQ("ThermostatOffsetDependent", fault.humidistatOffsetType());
  fault.resetHumidistatOffsetType();
  EXPECT_TRUE(fault.isHumidistatOffsetTypeDefaulted());
  EXPECT_EQ("ThermostatOffsetIndependent", fault.humidistatOffsetType());

  EXPECT_TRUE(fault.setReferenceHumidistatOffset(8.0));
  EXPECT_FALSE(fault.isReferenceHumidistatOffsetDefaulted());
  EXPECT_DOUBLE_EQ(8.0, fault.referenceHumidistatOffset());
  EXPECT_FALSE(fault.setReferenceHumidistatOffset(25.0));
  EXPECT_DOUBLE_EQ(8.0, fault.referenceHumidistatOffset());
  fault.resetReferenceHumidistatOffset();
  EXPECT_TRUE(fault.isReferenceHumidistatOffsetDefaulted());
  EXPECT_DOUBLE_EQ(5.0, fault.referenceHumidistatOffset());
}
