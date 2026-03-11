/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/SurfacePropertyConvectionCoefficientsMultipleSurface.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SurfacePropertyConvectionCoefficientsMultipleSurface_DefaultConstructor) {
  Model model;
  SurfacePropertyConvectionCoefficientsMultipleSurface sp(model);
  EXPECT_EQ(SurfacePropertyConvectionCoefficientsMultipleSurface::iddObjectType(), sp.iddObject().type());
}

TEST_F(EPModelFixture, SurfacePropertyConvectionCoefficientsMultipleSurface_ScalarAccessors_RoundTrip) {
  Model model;
  SurfacePropertyConvectionCoefficientsMultipleSurface sp(model);

  EXPECT_TRUE(sp.setSurfaceType("AllExteriorSurfaces"));
  ASSERT_TRUE(sp.surfaceType());
  EXPECT_EQ("AllExteriorSurfaces", sp.surfaceType().get());
  sp.resetSurfaceType();
  ASSERT_TRUE(sp.surfaceType());
  EXPECT_TRUE(sp.surfaceType()->empty());

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

TEST_F(EPModelFixture, SurfacePropertyConvectionCoefficientsMultipleSurface_ChoiceValues) {
  auto surfTypeValues = SurfacePropertyConvectionCoefficientsMultipleSurface::surfaceTypeValues();
  EXPECT_FALSE(surfTypeValues.empty());

  auto loc1Values = SurfacePropertyConvectionCoefficientsMultipleSurface::convectionCoefficient1LocationValues();
  EXPECT_FALSE(loc1Values.empty());

  auto type1Values = SurfacePropertyConvectionCoefficientsMultipleSurface::convectionCoefficient1TypeValues();
  EXPECT_FALSE(type1Values.empty());

  auto loc2Values = SurfacePropertyConvectionCoefficientsMultipleSurface::convectionCoefficient2LocationValues();
  EXPECT_FALSE(loc2Values.empty());

  auto type2Values = SurfacePropertyConvectionCoefficientsMultipleSurface::convectionCoefficient2TypeValues();
  EXPECT_FALSE(type2Values.empty());
}
