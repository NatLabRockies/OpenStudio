/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/SurfacePropertyConvectionCoefficients.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SurfacePropertyConvectionCoefficients_DefaultConstructor) {
  Model model;
  SurfacePropertyConvectionCoefficients sp(model);
  EXPECT_EQ(SurfacePropertyConvectionCoefficients::iddObjectType(), sp.iddObject().type());
}

TEST_F(EPModelFixture, SurfacePropertyConvectionCoefficients_ScalarAccessors_RoundTrip) {
  Model model;
  SurfacePropertyConvectionCoefficients sp(model);

  EXPECT_TRUE(sp.setConvectionCoefficient1Location("Outside"));
  ASSERT_TRUE(sp.convectionCoefficient1Location());
  EXPECT_EQ("Outside", sp.convectionCoefficient1Location().get());
  sp.resetConvectionCoefficient1Location();
  ASSERT_TRUE(sp.convectionCoefficient1Location());
  EXPECT_TRUE(sp.convectionCoefficient1Location()->empty());

  EXPECT_TRUE(sp.setConvectionCoefficient1Type("Value"));
  ASSERT_TRUE(sp.convectionCoefficient1Type());
  EXPECT_EQ("Value", sp.convectionCoefficient1Type().get());
  sp.resetConvectionCoefficient1Type();
  ASSERT_TRUE(sp.convectionCoefficient1Type());
  EXPECT_TRUE(sp.convectionCoefficient1Type()->empty());

  EXPECT_TRUE(sp.setConvectionCoefficient1(3.5));
  ASSERT_TRUE(sp.convectionCoefficient1());
  EXPECT_DOUBLE_EQ(3.5, sp.convectionCoefficient1().get());
  sp.resetConvectionCoefficient1();
  EXPECT_FALSE(sp.convectionCoefficient1());

  EXPECT_TRUE(sp.setConvectionCoefficient2Location("Inside"));
  ASSERT_TRUE(sp.convectionCoefficient2Location());
  EXPECT_EQ("Inside", sp.convectionCoefficient2Location().get());
  sp.resetConvectionCoefficient2Location();
  ASSERT_TRUE(sp.convectionCoefficient2Location());
  EXPECT_TRUE(sp.convectionCoefficient2Location()->empty());

  EXPECT_TRUE(sp.setConvectionCoefficient2Type("Schedule"));
  ASSERT_TRUE(sp.convectionCoefficient2Type());
  EXPECT_EQ("Schedule", sp.convectionCoefficient2Type().get());
  sp.resetConvectionCoefficient2Type();
  ASSERT_TRUE(sp.convectionCoefficient2Type());
  EXPECT_TRUE(sp.convectionCoefficient2Type()->empty());

  EXPECT_TRUE(sp.setConvectionCoefficient2(7.8));
  ASSERT_TRUE(sp.convectionCoefficient2());
  EXPECT_DOUBLE_EQ(7.8, sp.convectionCoefficient2().get());
  sp.resetConvectionCoefficient2();
  // N2 has an IDD default of 0.1, so after reset getDouble still returns a value
  ASSERT_TRUE(sp.convectionCoefficient2());
  EXPECT_DOUBLE_EQ(0.1, sp.convectionCoefficient2().get());
}

TEST_F(EPModelFixture, SurfacePropertyConvectionCoefficients_ChoiceValues) {
  auto loc1Values = SurfacePropertyConvectionCoefficients::convectionCoefficient1LocationValues();
  EXPECT_FALSE(loc1Values.empty());

  auto type1Values = SurfacePropertyConvectionCoefficients::convectionCoefficient1TypeValues();
  EXPECT_FALSE(type1Values.empty());

  auto loc2Values = SurfacePropertyConvectionCoefficients::convectionCoefficient2LocationValues();
  EXPECT_FALSE(loc2Values.empty());

  auto type2Values = SurfacePropertyConvectionCoefficients::convectionCoefficient2TypeValues();
  EXPECT_FALSE(type2Values.empty());
}
