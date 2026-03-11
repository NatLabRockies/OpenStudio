/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../StraightComponent/FanComponentModel.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, FanComponentModel_DefaultConstructor) {
  Model model;
  FanComponentModel fan(model);
  EXPECT_EQ(FanComponentModel::iddObjectType(), fan.iddObject().type());
  EXPECT_FALSE(fan.nameString().empty());
}

TEST_F(EPModelFixture, FanComponentModel_ScalarAccessors_RoundTrip) {
  Model model;
  FanComponentModel fan(model);

  EXPECT_TRUE(fan.setMaximumFlowRate(1.25));
  ASSERT_TRUE(fan.maximumFlowRate());
  EXPECT_DOUBLE_EQ(1.25, fan.maximumFlowRate().get());
  EXPECT_FALSE(fan.isMaximumFlowRateAutosized());
  fan.autosizeMaximumFlowRate();
  EXPECT_TRUE(fan.isMaximumFlowRateAutosized());

  EXPECT_TRUE(fan.setMinimumFlowRate(0.40));
  ASSERT_TRUE(fan.minimumFlowRate());
  EXPECT_DOUBLE_EQ(0.40, fan.minimumFlowRate().get());
  fan.autosizeMinimumFlowRate();
  EXPECT_TRUE(fan.isMinimumFlowRateAutosized());

  EXPECT_TRUE(fan.setFanWheelDiameter(0.5));
  EXPECT_DOUBLE_EQ(0.5, fan.fanWheelDiameter());

  EXPECT_TRUE(fan.setMaximumFanStaticEfficiency(0.72));
  EXPECT_DOUBLE_EQ(0.72, fan.maximumFanStaticEfficiency());

  EXPECT_TRUE(fan.setMaximumMotorOutputPower(1750.0));
  ASSERT_TRUE(fan.maximumMotorOutputPower());
  EXPECT_DOUBLE_EQ(1750.0, fan.maximumMotorOutputPower().get());
  fan.autosizeMaximumMotorOutputPower();
  EXPECT_TRUE(fan.isMaximumMotorOutputPowerAutosized());

  auto vfdTypes = FanComponentModel::vFDEfficiencyTypeValues();
  ASSERT_FALSE(vfdTypes.empty());
  EXPECT_TRUE(fan.setVFDEfficiencyType(vfdTypes.front()));
  EXPECT_EQ(vfdTypes.front(), fan.vFDEfficiencyType());

  EXPECT_TRUE(fan.setEndUseSubcategory("Fans"));
  EXPECT_EQ("Fans", fan.endUseSubcategory());
}
