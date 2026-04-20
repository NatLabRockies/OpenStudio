/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/ShadingPropertyReflectance.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ShadingPropertyReflectance_DefaultConstructor) {
  Model model;
  ShadingPropertyReflectance shadingPropertyReflectance(model);
  EXPECT_EQ(ShadingPropertyReflectance::iddObjectType(), shadingPropertyReflectance.iddObject().type());
}

TEST_F(EPModelFixture, ShadingPropertyReflectance_ScalarAccessors_RoundTrip) {
  Model model;
  ShadingPropertyReflectance shadingPropertyReflectance(model);

  EXPECT_TRUE(shadingPropertyReflectance.isDiffuseSolarReflectanceofUnglazedPartofShadingSurfaceDefaulted());
  EXPECT_TRUE(shadingPropertyReflectance.isDiffuseVisibleReflectanceofUnglazedPartofShadingSurfaceDefaulted());
  EXPECT_TRUE(shadingPropertyReflectance.isFractionofShadingSurfaceThatIsGlazedDefaulted());

  EXPECT_DOUBLE_EQ(0.2, shadingPropertyReflectance.diffuseSolarReflectanceofUnglazedPartofShadingSurface());
  EXPECT_DOUBLE_EQ(0.2, shadingPropertyReflectance.diffuseVisibleReflectanceofUnglazedPartofShadingSurface());
  EXPECT_DOUBLE_EQ(0.0, shadingPropertyReflectance.fractionofShadingSurfaceThatIsGlazed());

  EXPECT_TRUE(shadingPropertyReflectance.setDiffuseSolarReflectanceofUnglazedPartofShadingSurface(0.6));
  EXPECT_FALSE(shadingPropertyReflectance.isDiffuseSolarReflectanceofUnglazedPartofShadingSurfaceDefaulted());
  EXPECT_DOUBLE_EQ(0.6, shadingPropertyReflectance.diffuseSolarReflectanceofUnglazedPartofShadingSurface());

  EXPECT_TRUE(shadingPropertyReflectance.setDiffuseVisibleReflectanceofUnglazedPartofShadingSurface(0.7));
  EXPECT_FALSE(shadingPropertyReflectance.isDiffuseVisibleReflectanceofUnglazedPartofShadingSurfaceDefaulted());
  EXPECT_DOUBLE_EQ(0.7, shadingPropertyReflectance.diffuseVisibleReflectanceofUnglazedPartofShadingSurface());

  EXPECT_TRUE(shadingPropertyReflectance.setFractionofShadingSurfaceThatIsGlazed(0.3));
  EXPECT_FALSE(shadingPropertyReflectance.isFractionofShadingSurfaceThatIsGlazedDefaulted());
  EXPECT_DOUBLE_EQ(0.3, shadingPropertyReflectance.fractionofShadingSurfaceThatIsGlazed());

  EXPECT_FALSE(shadingPropertyReflectance.setFractionofShadingSurfaceThatIsGlazed(1.5));
  EXPECT_DOUBLE_EQ(0.3, shadingPropertyReflectance.fractionofShadingSurfaceThatIsGlazed());

  shadingPropertyReflectance.resetDiffuseSolarReflectanceofUnglazedPartofShadingSurface();
  shadingPropertyReflectance.resetDiffuseVisibleReflectanceofUnglazedPartofShadingSurface();
  shadingPropertyReflectance.resetFractionofShadingSurfaceThatIsGlazed();

  EXPECT_TRUE(shadingPropertyReflectance.isDiffuseSolarReflectanceofUnglazedPartofShadingSurfaceDefaulted());
  EXPECT_TRUE(shadingPropertyReflectance.isDiffuseVisibleReflectanceofUnglazedPartofShadingSurfaceDefaulted());
  EXPECT_TRUE(shadingPropertyReflectance.isFractionofShadingSurfaceThatIsGlazedDefaulted());

  EXPECT_DOUBLE_EQ(0.2, shadingPropertyReflectance.diffuseSolarReflectanceofUnglazedPartofShadingSurface());
  EXPECT_DOUBLE_EQ(0.2, shadingPropertyReflectance.diffuseVisibleReflectanceofUnglazedPartofShadingSurface());
  EXPECT_DOUBLE_EQ(0.0, shadingPropertyReflectance.fractionofShadingSurfaceThatIsGlazed());
}
