/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../StraightComponent/SwimmingPoolIndoor.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SwimmingPoolIndoor_DefaultConstructor) {
  Model model;
  SwimmingPoolIndoor pool(model);
  EXPECT_EQ(SwimmingPoolIndoor::iddObjectType(), pool.iddObject().type());
  EXPECT_FALSE(pool.nameString().empty());
}

TEST_F(EPModelFixture, SwimmingPoolIndoor_ScalarAccessors_RoundTrip) {
  Model model;
  SwimmingPoolIndoor pool(model);

  EXPECT_TRUE(pool.setAverageDepth(1.75));
  EXPECT_DOUBLE_EQ(1.75, pool.averageDepth());

  EXPECT_TRUE(pool.setCoverEvaporationFactor(0.3));
  EXPECT_DOUBLE_EQ(0.3, pool.coverEvaporationFactor());
  EXPECT_FALSE(pool.isCoverEvaporationFactorDefaulted());
  pool.resetCoverEvaporationFactor();
  EXPECT_TRUE(pool.isCoverEvaporationFactorDefaulted());

  EXPECT_TRUE(pool.setCoverConvectionFactor(0.4));
  EXPECT_DOUBLE_EQ(0.4, pool.coverConvectionFactor());
  EXPECT_FALSE(pool.isCoverConvectionFactorDefaulted());
  pool.resetCoverConvectionFactor();
  EXPECT_TRUE(pool.isCoverConvectionFactorDefaulted());

  EXPECT_TRUE(pool.setCoverShortWavelengthRadiationFactor(0.1));
  EXPECT_DOUBLE_EQ(0.1, pool.coverShortWavelengthRadiationFactor());
  EXPECT_FALSE(pool.isCoverShortWavelengthRadiationFactorDefaulted());
  pool.resetCoverShortWavelengthRadiationFactor();
  EXPECT_TRUE(pool.isCoverShortWavelengthRadiationFactorDefaulted());

  EXPECT_TRUE(pool.setCoverLongWavelengthRadiationFactor(0.2));
  EXPECT_DOUBLE_EQ(0.2, pool.coverLongWavelengthRadiationFactor());
  EXPECT_FALSE(pool.isCoverLongWavelengthRadiationFactorDefaulted());
  pool.resetCoverLongWavelengthRadiationFactor();
  EXPECT_TRUE(pool.isCoverLongWavelengthRadiationFactorDefaulted());

  EXPECT_FALSE(pool.poolHeatingSystemMaximumWaterFlowRate());
  EXPECT_TRUE(pool.setPoolHeatingSystemMaximumWaterFlowRate(0.12));
  ASSERT_TRUE(pool.poolHeatingSystemMaximumWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.12, pool.poolHeatingSystemMaximumWaterFlowRate().get());
  pool.resetPoolHeatingSystemMaximumWaterFlowRate();
  EXPECT_FALSE(pool.poolHeatingSystemMaximumWaterFlowRate());

  EXPECT_FALSE(pool.poolMiscellaneousEquipmentPower());
  EXPECT_TRUE(pool.setPoolMiscellaneousEquipmentPower(123.0));
  ASSERT_TRUE(pool.poolMiscellaneousEquipmentPower());
  EXPECT_DOUBLE_EQ(123.0, pool.poolMiscellaneousEquipmentPower().get());
  pool.resetPoolMiscellaneousEquipmentPower();
  EXPECT_FALSE(pool.poolMiscellaneousEquipmentPower());

  EXPECT_TRUE(pool.setMaximumNumberofPeople(25.0));
  EXPECT_DOUBLE_EQ(25.0, pool.maximumNumberofPeople());
}
