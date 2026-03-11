/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/CoilDXASHRAE205Performance.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilDXASHRAE205Performance_DefaultConstructor) {
  Model model;
  CoilDXASHRAE205Performance coil(model);
  EXPECT_EQ(CoilDXASHRAE205Performance::iddObjectType(), coil.iddObject().type());
}

TEST_F(EPModelFixture, CoilDXASHRAE205Performance_ScalarAccessors_RoundTrip) {
  Model model;
  CoilDXASHRAE205Performance coil(model);

  EXPECT_TRUE(coil.setRepresentationFileName("rs0004-representation.cbor"));
  EXPECT_EQ("rs0004-representation.cbor", coil.representationFileName());

  EXPECT_TRUE(coil.isPerformanceInterpolationMethodDefaulted());
  EXPECT_EQ("Linear", coil.performanceInterpolationMethod());
  EXPECT_TRUE(coil.setPerformanceInterpolationMethod("Cubic"));
  EXPECT_EQ("Cubic", coil.performanceInterpolationMethod());
  EXPECT_FALSE(coil.isPerformanceInterpolationMethodDefaulted());
  coil.resetPerformanceInterpolationMethod();
  EXPECT_TRUE(coil.isPerformanceInterpolationMethodDefaulted());
  EXPECT_EQ("Linear", coil.performanceInterpolationMethod());

  EXPECT_TRUE(coil.isRatedTotalCoolingCapacityAutosized());
  EXPECT_TRUE(coil.setRatedTotalCoolingCapacity(12000.0));
  ASSERT_TRUE(coil.ratedTotalCoolingCapacity());
  EXPECT_DOUBLE_EQ(12000.0, coil.ratedTotalCoolingCapacity().get());
  EXPECT_FALSE(coil.isRatedTotalCoolingCapacityAutosized());
  coil.autosizeRatedTotalCoolingCapacity();
  EXPECT_TRUE(coil.isRatedTotalCoolingCapacityAutosized());
  coil.resetRatedTotalCoolingCapacity();
  EXPECT_FALSE(coil.ratedTotalCoolingCapacity());
  EXPECT_TRUE(coil.isRatedTotalCoolingCapacityAutosized());

  EXPECT_TRUE(coil.isRatedSteadyStateHeatingCapacityAutosized());
  EXPECT_TRUE(coil.setRatedSteadyStateHeatingCapacity(15000.0));
  ASSERT_TRUE(coil.ratedSteadyStateHeatingCapacity());
  EXPECT_DOUBLE_EQ(15000.0, coil.ratedSteadyStateHeatingCapacity().get());
  EXPECT_FALSE(coil.isRatedSteadyStateHeatingCapacityAutosized());
  coil.autosizeRatedSteadyStateHeatingCapacity();
  EXPECT_TRUE(coil.isRatedSteadyStateHeatingCapacityAutosized());
  coil.resetRatedSteadyStateHeatingCapacity();
  EXPECT_FALSE(coil.ratedSteadyStateHeatingCapacity());
  EXPECT_TRUE(coil.isRatedSteadyStateHeatingCapacityAutosized());
}
