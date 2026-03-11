/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/LifeCycleCostUseAdjustment.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, LifeCycleCostUseAdjustment_DefaultConstructor) {
  Model model;
  LifeCycleCostUseAdjustment lifeCycleCostUseAdjustment(model);

  EXPECT_EQ(LifeCycleCostUseAdjustment::iddObjectType(), lifeCycleCostUseAdjustment.iddObject().type());
}

TEST_F(EPModelFixture, LifeCycleCostUseAdjustment_ScalarAccessors_RoundTrip) {
  Model model;
  LifeCycleCostUseAdjustment lifeCycleCostUseAdjustment(model);

  const auto resources = LifeCycleCostUseAdjustment::resourceValues();
  EXPECT_FALSE(resources.empty());

  EXPECT_TRUE(lifeCycleCostUseAdjustment.setResource("Electricity"));
  EXPECT_EQ("Electricity", lifeCycleCostUseAdjustment.resource());

  EXPECT_FALSE(lifeCycleCostUseAdjustment.setResource("BadResource"));
  EXPECT_EQ("Electricity", lifeCycleCostUseAdjustment.resource());
}
