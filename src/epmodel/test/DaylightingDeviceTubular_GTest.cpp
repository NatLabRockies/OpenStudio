/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/DaylightingDeviceTubular.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, DaylightingDeviceTubular_DefaultConstructor) {
  Model model;
  DaylightingDeviceTubular tubular(model);
  EXPECT_EQ(DaylightingDeviceTubular::iddObjectType(), tubular.iddObject().type());

  EXPECT_DOUBLE_EQ(0.3556, tubular.diameter());
  EXPECT_DOUBLE_EQ(1.4, tubular.totalLength());
  EXPECT_DOUBLE_EQ(0.28, tubular.effectiveThermalResistance());
  EXPECT_TRUE(tubular.isEffectiveThermalResistanceDefaulted());
}

TEST_F(EPModelFixture, DaylightingDeviceTubular_ScalarAccessors_RoundTrip) {
  Model model;
  DaylightingDeviceTubular tubular(model);

  EXPECT_TRUE(tubular.setDiameter(0.75));
  EXPECT_TRUE(tubular.setTotalLength(2.1));
  EXPECT_TRUE(tubular.setEffectiveThermalResistance(0.4));

  EXPECT_DOUBLE_EQ(0.75, tubular.diameter());
  EXPECT_DOUBLE_EQ(2.1, tubular.totalLength());
  EXPECT_DOUBLE_EQ(0.4, tubular.effectiveThermalResistance());
  EXPECT_FALSE(tubular.isEffectiveThermalResistanceDefaulted());

  tubular.resetEffectiveThermalResistance();
  EXPECT_TRUE(tubular.isEffectiveThermalResistanceDefaulted());
  EXPECT_DOUBLE_EQ(0.28, tubular.effectiveThermalResistance());
}
