/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../StraightComponent/SolarCollectorIntegralCollectorStorage.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SolarCollectorIntegralCollectorStorage_DefaultConstructor) {
  Model model;
  SolarCollectorIntegralCollectorStorage object(model);
  EXPECT_EQ(SolarCollectorIntegralCollectorStorage::iddObjectType(), object.iddObject().type());
  EXPECT_FALSE(object.nameString().empty());
}

TEST_F(EPModelFixture, SolarCollectorIntegralCollectorStorage_ScalarAccessors_RoundTrip) {
  Model model;
  SolarCollectorIntegralCollectorStorage object(model);

  const auto boundaryValues = SolarCollectorIntegralCollectorStorage::bottomSurfaceBoundaryConditionsTypeValues();
  EXPECT_FALSE(boundaryValues.empty());
  EXPECT_EQ("AmbientAir", object.bottomSurfaceBoundaryConditionsType());
  EXPECT_TRUE(object.isBottomSurfaceBoundaryConditionsTypeDefaulted());

  EXPECT_FALSE(object.maximumFlowRate());

  EXPECT_TRUE(object.setMaximumFlowRate(0.00234));
  ASSERT_TRUE(object.maximumFlowRate());
  EXPECT_DOUBLE_EQ(0.00234, object.maximumFlowRate().get());

  object.resetMaximumFlowRate();
  EXPECT_FALSE(object.maximumFlowRate());
}
