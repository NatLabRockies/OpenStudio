/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../LayeredConstruction/Construction.hpp"
#include "../LayeredConstruction/Construction_Impl.hpp"
#include "../OpaqueMaterial/StandardOpaqueMaterial.hpp"
#include "../OpaqueMaterial/StandardOpaqueMaterial_Impl.hpp"
#include "../ResourceObject/SurfaceConstructionAssignments.hpp"
#include "../ResourceObject/SurfaceConstructionAssignments_Impl.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SurfaceConstructionAssignments_GettersSetters) {
  Model m;
  SurfaceConstructionAssignments surfaceConstructionAssignments(m);

  surfaceConstructionAssignments.setName("My SurfaceConstructionAssignments");

  // Floor Construction Name: Optional Object
  EXPECT_FALSE(surfaceConstructionAssignments.floorConstruction());
  Construction floorConstruction(m);
  EXPECT_TRUE(surfaceConstructionAssignments.setFloorConstruction(floorConstruction));
  ASSERT_TRUE(surfaceConstructionAssignments.floorConstruction());
  EXPECT_EQ(floorConstruction, surfaceConstructionAssignments.floorConstruction().get());

  // Wall Construction Name: Optional Object
  EXPECT_FALSE(surfaceConstructionAssignments.wallConstruction());
  Construction wallConstruction(m);
  EXPECT_TRUE(surfaceConstructionAssignments.setWallConstruction(wallConstruction));
  ASSERT_TRUE(surfaceConstructionAssignments.wallConstruction());
  EXPECT_EQ(wallConstruction, surfaceConstructionAssignments.wallConstruction().get());

  // Roof Ceiling Construction Name: Optional Object
  EXPECT_FALSE(surfaceConstructionAssignments.roofCeilingConstruction());
  Construction roofCeilingConstruction(m);
  EXPECT_TRUE(surfaceConstructionAssignments.setRoofCeilingConstruction(roofCeilingConstruction));
  ASSERT_TRUE(surfaceConstructionAssignments.roofCeilingConstruction());
  EXPECT_EQ(roofCeilingConstruction, surfaceConstructionAssignments.roofCeilingConstruction().get());

  // Reset
  surfaceConstructionAssignments.resetFloorConstruction();
  EXPECT_FALSE(surfaceConstructionAssignments.floorConstruction());
  EXPECT_TRUE(surfaceConstructionAssignments.wallConstruction());
  EXPECT_TRUE(surfaceConstructionAssignments.roofCeilingConstruction());

  surfaceConstructionAssignments.resetWallConstruction();
  EXPECT_FALSE(surfaceConstructionAssignments.floorConstruction());
  EXPECT_FALSE(surfaceConstructionAssignments.wallConstruction());
  EXPECT_TRUE(surfaceConstructionAssignments.roofCeilingConstruction());

  surfaceConstructionAssignments.resetRoofCeilingConstruction();
  EXPECT_FALSE(surfaceConstructionAssignments.floorConstruction());
  EXPECT_FALSE(surfaceConstructionAssignments.wallConstruction());
  EXPECT_FALSE(surfaceConstructionAssignments.roofCeilingConstruction());
}

TEST_F(EPModelFixture, SurfaceConstructionAssignments_RemovingConstructionClearsSlot) {
  Model model;
  SurfaceConstructionAssignments assignments(model);
  Construction wall(model);
  ASSERT_TRUE(assignments.setWallConstruction(wall));

  EXPECT_FALSE(wall.remove().empty());
  EXPECT_FALSE(assignments.wallConstruction());
}

TEST_F(EPModelFixture, SurfaceConstructionAssignments_Merge) {
  Model model;
  SurfaceConstructionAssignments assignments(model);
  SurfaceConstructionAssignments other(model);
  Construction ownWall(model);
  Construction otherWall(model);
  Construction otherFloor(model);
  ASSERT_TRUE(assignments.setWallConstruction(ownWall));
  ASSERT_TRUE(other.setWallConstruction(otherWall));
  ASSERT_TRUE(other.setFloorConstruction(otherFloor));

  assignments.merge(other);

  // Empty slots are filled from other, set slots are kept.
  ASSERT_TRUE(assignments.wallConstruction());
  ASSERT_TRUE(assignments.floorConstruction());
  EXPECT_EQ(ownWall, *assignments.wallConstruction());
  EXPECT_EQ(otherFloor, *assignments.floorConstruction());
  EXPECT_FALSE(assignments.roofCeilingConstruction());

  // other is unchanged.
  ASSERT_TRUE(other.wallConstruction());
  EXPECT_EQ(otherWall, *other.wallConstruction());
  EXPECT_FALSE(other.roofCeilingConstruction());
}

TEST_F(EPModelFixture, SurfaceConstructionAssignments_Clone) {

  Model model;
  SurfaceConstructionAssignments assignments(model);

  auto constructionWithMaterial = [&model](const std::string& name) -> Construction {
    Construction construction(model);
    construction.setName(name);
    StandardOpaqueMaterial material(model);
    material.setName("Material " + name);
    EXPECT_TRUE(construction.setLayers({material}));
    return construction;
  };

  auto wallConstruction = constructionWithMaterial("Wall");
  auto floorConstruction = constructionWithMaterial("Floor");
  auto roofCeilingConstruction = constructionWithMaterial("RoofCeiling");
  ASSERT_TRUE(assignments.setWallConstruction(wallConstruction));
  ASSERT_TRUE(assignments.setFloorConstruction(floorConstruction));
  ASSERT_TRUE(assignments.setRoofCeilingConstruction(roofCeilingConstruction));

  EXPECT_EQ(1, model.getConcreteModelObjects<SurfaceConstructionAssignments>().size());
  EXPECT_EQ(3, model.getConcreteModelObjects<Construction>().size());
  EXPECT_EQ(3, model.getConcreteModelObjects<StandardOpaqueMaterial>().size());

  // TODO: Need to implement clone(Model&) and resources() for deep copy...
  // {
  //   // Clone in another model
  //   Model model2;
  //   auto clone = assignments.clone(model2).cast<SurfaceConstructionAssignments>();
  //   EXPECT_EQ(1, model2.getConcreteModelObjects<SurfaceConstructionAssignments>().size());
  //   EXPECT_EQ(3, model2.getConcreteModelObjects<Construction>().size());
  //   EXPECT_EQ(3, model2.getConcreteModelObjects<StandardOpaqueMaterial>().size());
  //   EXPECT_TRUE(clone.wallConstruction());
  //   EXPECT_TRUE(clone.floorConstruction());
  //   EXPECT_TRUE(clone.roofCeilingConstruction());
  // }

  auto clone_ = model.addObject(assignments.idfObject());
  ASSERT_TRUE(clone_);
  auto clone = clone_->cast<SurfaceConstructionAssignments>();
  EXPECT_EQ(2, model.getConcreteModelObjects<SurfaceConstructionAssignments>().size());
  EXPECT_EQ(3, model.getConcreteModelObjects<Construction>().size());
  EXPECT_EQ(3, model.getConcreteModelObjects<StandardOpaqueMaterial>().size());
  ASSERT_TRUE(clone.wallConstruction());
  EXPECT_EQ(wallConstruction, *clone.wallConstruction());
  ASSERT_TRUE(clone.floorConstruction());
  EXPECT_EQ(floorConstruction, *clone.floorConstruction());
  ASSERT_TRUE(clone.roofCeilingConstruction());
  EXPECT_EQ(roofCeilingConstruction, *clone.roofCeilingConstruction());
}
