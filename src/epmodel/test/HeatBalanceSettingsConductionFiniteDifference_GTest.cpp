/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/HeatBalanceSettingsConductionFiniteDifference.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, HeatBalanceSettingsConductionFiniteDifference_DefaultConstructor) {
  Model model;
  HeatBalanceSettingsConductionFiniteDifference object(model);

  EXPECT_EQ(HeatBalanceSettingsConductionFiniteDifference::iddObjectType(), object.iddObject().type());

  EXPECT_TRUE(object.isDifferenceSchemeDefaulted());
  EXPECT_EQ("FullyImplicitFirstOrder", object.differenceScheme());
  EXPECT_TRUE(object.isSpaceDiscretizationConstantDefaulted());
  EXPECT_DOUBLE_EQ(3.0, object.spaceDiscretizationConstant());
  EXPECT_TRUE(object.isRelaxationFactorDefaulted());
  EXPECT_DOUBLE_EQ(1.0, object.relaxationFactor());
  EXPECT_TRUE(object.isInsideFaceSurfaceTemperatureConvergenceCriteriaDefaulted());
  EXPECT_DOUBLE_EQ(0.002, object.insideFaceSurfaceTemperatureConvergenceCriteria());
}

TEST_F(EPModelFixture, HeatBalanceSettingsConductionFiniteDifference_ScalarAccessors_RoundTrip) {
  Model model;
  HeatBalanceSettingsConductionFiniteDifference object(model);

  EXPECT_TRUE(object.setDifferenceScheme("CrankNicholsonSecondOrder"));
  EXPECT_EQ("CrankNicholsonSecondOrder", object.differenceScheme());
  EXPECT_FALSE(object.isDifferenceSchemeDefaulted());
  object.resetDifferenceScheme();
  EXPECT_TRUE(object.isDifferenceSchemeDefaulted());
  EXPECT_EQ("FullyImplicitFirstOrder", object.differenceScheme());

  EXPECT_TRUE(object.setSpaceDiscretizationConstant(2.5));
  EXPECT_DOUBLE_EQ(2.5, object.spaceDiscretizationConstant());
  EXPECT_FALSE(object.isSpaceDiscretizationConstantDefaulted());
  object.resetSpaceDiscretizationConstant();
  EXPECT_TRUE(object.isSpaceDiscretizationConstantDefaulted());
  EXPECT_DOUBLE_EQ(3.0, object.spaceDiscretizationConstant());

  EXPECT_TRUE(object.setRelaxationFactor(0.5));
  EXPECT_DOUBLE_EQ(0.5, object.relaxationFactor());
  EXPECT_FALSE(object.isRelaxationFactorDefaulted());
  EXPECT_FALSE(object.setRelaxationFactor(0.0));
  object.resetRelaxationFactor();
  EXPECT_TRUE(object.isRelaxationFactorDefaulted());
  EXPECT_DOUBLE_EQ(1.0, object.relaxationFactor());

  EXPECT_TRUE(object.setInsideFaceSurfaceTemperatureConvergenceCriteria(0.005));
  EXPECT_DOUBLE_EQ(0.005, object.insideFaceSurfaceTemperatureConvergenceCriteria());
  EXPECT_FALSE(object.isInsideFaceSurfaceTemperatureConvergenceCriteriaDefaulted());
  EXPECT_FALSE(object.setInsideFaceSurfaceTemperatureConvergenceCriteria(0.02));
  object.resetInsideFaceSurfaceTemperatureConvergenceCriteria();
  EXPECT_TRUE(object.isInsideFaceSurfaceTemperatureConvergenceCriteriaDefaulted());
  EXPECT_DOUBLE_EQ(0.002, object.insideFaceSurfaceTemperatureConvergenceCriteria());

  const auto values = HeatBalanceSettingsConductionFiniteDifference::differenceSchemeValues();
  EXPECT_GE(values.size(), 1u);
}
