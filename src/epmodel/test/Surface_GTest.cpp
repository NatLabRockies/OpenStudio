/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../PlanarSurface/Surface.hpp"
#include "../PlanarSurface/Surface_Impl.hpp"
#include "../PlanarSurfaceGroup/Space.hpp"
#include "../PlanarSurfaceGroup/Space_Impl.hpp"
#include "../PlanarSurface/SubSurface.hpp"
#include "../PlanarSurface/SubSurface_Impl.hpp"
#include "../LayeredConstruction/Construction.hpp"
#include "../LayeredConstruction/Construction_Impl.hpp"
#include "../OpaqueMaterial/StandardOpaqueMaterial.hpp"
#include "../OpaqueMaterial/StandardOpaqueMaterial_Impl.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, Surface_DefaultConstructor) {
  Model model;
  Surface surface({{0, 0, 1}, {0, 0, 0}, {1, 0, 0}, {1, 0, 1}}, model);
  EXPECT_EQ(Surface::iddObjectType(), surface.iddObject().type());
  EXPECT_FALSE(surface.nameString().empty());
}

TEST_F(EPModelFixture, Surface_ScalarAccessors_RoundTrip) {
  Model model;
  Surface surface({{0, 0, 1}, {0, 0, 0}, {1, 0, 0}, {1, 0, 1}}, model);

  EXPECT_TRUE(surface.setSurfaceType("Wall"));
  EXPECT_EQ("Wall", surface.surfaceType());

  EXPECT_TRUE(surface.setOutsideBoundaryCondition("Outdoors"));
  EXPECT_EQ("Outdoors", surface.outsideBoundaryCondition());

  EXPECT_TRUE(surface.setSunExposure("NoSun"));
  EXPECT_EQ("NoSun", surface.sunExposure());
  EXPECT_FALSE(surface.isSunExposureDefaulted());
  surface.resetSunExposure();
  EXPECT_TRUE(surface.isSunExposureDefaulted());

  EXPECT_TRUE(surface.setWindExposure("NoWind"));
  EXPECT_EQ("NoWind", surface.windExposure());
  EXPECT_FALSE(surface.isWindExposureDefaulted());
  surface.resetWindExposure();
  EXPECT_TRUE(surface.isWindExposureDefaulted());

  EXPECT_TRUE(surface.setViewFactortoGround(0.42));
  ASSERT_TRUE(surface.viewFactortoGround());
  EXPECT_DOUBLE_EQ(0.42, *surface.viewFactortoGround());
  EXPECT_FALSE(surface.isViewFactortoGroundAutocalculated());
  surface.autocalculateViewFactortoGround();
  EXPECT_TRUE(surface.isViewFactortoGroundAutocalculated());
  surface.resetViewFactortoGround();
  EXPECT_TRUE(surface.isViewFactortoGroundDefaulted());

  EXPECT_TRUE(surface.setNumberofVertices(4));
  EXPECT_EQ(4u, surface.numberofVertices());
  EXPECT_FALSE(surface.isNumberofVerticesAutocalculated());
  surface.autocalculateNumberofVertices();
  EXPECT_TRUE(surface.isNumberofVerticesAutocalculated());
  surface.resetNumberofVertices();
  EXPECT_TRUE(surface.isNumberofVerticesDefaulted());
}

TEST_F(EPModelFixture, Surface_CreateAdjacentSurface_AlreadyAdjacent) {
  Model model;
  Space space1(model);
  Space space2(model);
  Space space3(model);

  Surface surface({{0, 10, 3}, {0, 10, 0}, {0, 0, 0}, {0, 0, 3}}, model);
  ASSERT_TRUE(surface.setSpace(space1));

  auto adjacentSurface_ = surface.createAdjacentSurface(space2);
  ASSERT_TRUE(adjacentSurface_);
  ASSERT_TRUE(surface.adjacentSurface());
  EXPECT_EQ(*adjacentSurface_, *surface.adjacentSurface());
  EXPECT_EQ(2, model.getConcreteModelObjects<Surface>().size());

  // Already has an adjacent Surface: nothing is created and the existing match is kept
  EXPECT_FALSE(surface.createAdjacentSurface(space3));
  EXPECT_EQ(2, model.getConcreteModelObjects<Surface>().size());
  ASSERT_TRUE(surface.adjacentSurface());
  EXPECT_EQ(*adjacentSurface_, *surface.adjacentSurface());
  ASSERT_TRUE(adjacentSurface_->adjacentSurface());
  EXPECT_EQ(surface, *adjacentSurface_->adjacentSurface());
  EXPECT_EQ("Surface", adjacentSurface_->outsideBoundaryCondition());

  // Same from the other side
  EXPECT_FALSE(adjacentSurface_->createAdjacentSurface(space3));
  EXPECT_EQ(2, model.getConcreteModelObjects<Surface>().size());
}

TEST_F(EPModelFixture, Surface_CreateAdjacentSurface_Construction) {
  Model model;
  Space space1(model);
  Space space2(model);
  Space space3(model);

  StandardOpaqueMaterial outer(model);
  StandardOpaqueMaterial inner(model);
  Construction asymmetric(model);
  EXPECT_TRUE(asymmetric.setName("Asymmetric"));
  EXPECT_TRUE(asymmetric.setLayers({outer, inner}));
  Construction symmetric(model);
  EXPECT_TRUE(symmetric.setLayers({outer, inner, outer}));

  Surface surface1({{0, 10, 3}, {0, 10, 0}, {0, 0, 0}, {0, 0, 3}}, model);
  ASSERT_TRUE(surface1.setSpace(space1));
  ASSERT_TRUE(surface1.setConstruction(asymmetric));
  SubSurface subSurface1({{0, 9, 2}, {0, 9, 1}, {0, 1, 1}, {0, 1, 2}}, model);
  ASSERT_TRUE(subSurface1.setSurface(surface1));
  ASSERT_TRUE(subSurface1.setConstruction(symmetric));

  // A named asymmetric construction is reversed, a symmetric one is kept
  auto surface2_ = surface1.createAdjacentSurface(space2);
  ASSERT_TRUE(surface2_);
  EXPECT_FALSE(surface2_->isConstructionDefaulted());
  ASSERT_TRUE(surface2_->construction());
  EXPECT_EQ("Asymmetric Reversed", surface2_->construction()->nameString());
  EXPECT_TRUE(asymmetric.reverseEqualLayers(surface2_->construction()->cast<Construction>()));
  ASSERT_EQ(1, surface2_->subSurfaces().size());
  auto subSurface2 = surface2_->subSurfaces().front();
  EXPECT_FALSE(subSurface2.isConstructionDefaulted());
  ASSERT_TRUE(subSurface2.construction());
  EXPECT_EQ(symmetric, *subSurface2.construction());
  EXPECT_EQ(3, model.getConcreteModelObjects<Construction>().size());

  // The existing reversed construction is reused
  Surface surface3({{0, 10, 3}, {0, 10, 0}, {0, 0, 0}, {0, 0, 3}}, model);
  ASSERT_TRUE(surface3.setSpace(space1));
  ASSERT_TRUE(surface3.setConstruction(asymmetric));
  auto surface4_ = surface3.createAdjacentSurface(space3);
  ASSERT_TRUE(surface4_);
  ASSERT_TRUE(surface4_->construction());
  EXPECT_EQ(*surface2_->construction(), *surface4_->construction());
  EXPECT_EQ(3, model.getConcreteModelObjects<Construction>().size());

  // A defaulted construction stays defaulted on the other side
  Surface surface5({{0, 10, 3}, {0, 10, 0}, {0, 0, 0}, {0, 0, 3}}, model);
  ASSERT_TRUE(surface5.setSpace(space1));
  SubSurface subSurface5({{0, 9, 2}, {0, 9, 1}, {0, 1, 1}, {0, 1, 2}}, model);
  ASSERT_TRUE(subSurface5.setSurface(surface5));
  auto surface6_ = surface5.createAdjacentSurface(space3);
  ASSERT_TRUE(surface6_);
  EXPECT_TRUE(surface6_->isConstructionDefaulted());
  ASSERT_EQ(1, surface6_->subSurfaces().size());
  EXPECT_TRUE(surface6_->subSurfaces().front().isConstructionDefaulted());
  EXPECT_EQ(3, model.getConcreteModelObjects<Construction>().size());
}
