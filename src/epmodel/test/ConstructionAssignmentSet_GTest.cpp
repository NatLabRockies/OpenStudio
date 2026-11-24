/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../LayeredConstruction/Construction.hpp"
#include "../LayeredConstruction/Construction_Impl.hpp"
#include "../ParentObject/Building.hpp"
#include "../ParentObject/Building_Impl.hpp"
#include "../PlanarSurfaceGroup/Space.hpp"
#include "../PlanarSurfaceGroup/Space_Impl.hpp"
#include "../ResourceObject/ConstructionAssignmentSet.hpp"
#include "../ResourceObject/ConstructionAssignmentSet_Impl.hpp"
#include "../ResourceObject/SubSurfaceConstructionAssignments.hpp"
#include "../ResourceObject/SubSurfaceConstructionAssignments_Impl.hpp"
#include "../ResourceObject/SurfaceConstructionAssignments.hpp"
#include "../ResourceObject/SurfaceConstructionAssignments_Impl.hpp"

#include <utilities/core/Filesystem.hpp>
#include <utilities/geometry/Point3d.hpp>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ConstructionAssignmentSet_GettersSetters) {
  Model m;
  ConstructionAssignmentSet constructionAssignmentSet(m);

  constructionAssignmentSet.setName("My ConstructionAssignmentSet");

  // Exterior Surface Construction Assignments Name: Optional Object
  EXPECT_FALSE(constructionAssignmentSet.exteriorSurfaceConstructionAssignments());
  SurfaceConstructionAssignments exteriorSurfaceConstructionAssignments(m);
  EXPECT_TRUE(constructionAssignmentSet.setExteriorSurfaceConstructionAssignments(exteriorSurfaceConstructionAssignments));
  ASSERT_TRUE(constructionAssignmentSet.exteriorSurfaceConstructionAssignments());
  EXPECT_EQ(exteriorSurfaceConstructionAssignments, constructionAssignmentSet.exteriorSurfaceConstructionAssignments().get());

  // Interior Surface Construction Assignments Name: Optional Object
  EXPECT_FALSE(constructionAssignmentSet.interiorSurfaceConstructionAssignments());
  SurfaceConstructionAssignments interiorSurfaceConstructionAssignments(m);
  EXPECT_TRUE(constructionAssignmentSet.setInteriorSurfaceConstructionAssignments(interiorSurfaceConstructionAssignments));
  ASSERT_TRUE(constructionAssignmentSet.interiorSurfaceConstructionAssignments());
  EXPECT_EQ(interiorSurfaceConstructionAssignments, constructionAssignmentSet.interiorSurfaceConstructionAssignments().get());

  // Ground Contact Surface Construction Assignments Name: Optional Object
  EXPECT_FALSE(constructionAssignmentSet.groundContactSurfaceConstructionAssignments());
  SurfaceConstructionAssignments groundContactSurfaceConstructionAssignments(m);
  EXPECT_TRUE(constructionAssignmentSet.setGroundContactSurfaceConstructionAssignments(groundContactSurfaceConstructionAssignments));
  ASSERT_TRUE(constructionAssignmentSet.groundContactSurfaceConstructionAssignments());
  EXPECT_EQ(groundContactSurfaceConstructionAssignments, constructionAssignmentSet.groundContactSurfaceConstructionAssignments().get());

  // Exterior SubSurface Construction Assignments Name: Optional Object
  EXPECT_FALSE(constructionAssignmentSet.exteriorSubSurfaceConstructionAssignments());
  SubSurfaceConstructionAssignments exteriorSubSurfaceConstructionAssignments(m);
  EXPECT_TRUE(constructionAssignmentSet.setExteriorSubSurfaceConstructionAssignments(exteriorSubSurfaceConstructionAssignments));
  ASSERT_TRUE(constructionAssignmentSet.exteriorSubSurfaceConstructionAssignments());
  EXPECT_EQ(exteriorSubSurfaceConstructionAssignments, constructionAssignmentSet.exteriorSubSurfaceConstructionAssignments().get());

  // Interior SubSurface Construction Assignments Name: Optional Object
  EXPECT_FALSE(constructionAssignmentSet.interiorSubSurfaceConstructionAssignments());
  SubSurfaceConstructionAssignments interiorSubSurfaceConstructionAssignments(m);
  EXPECT_TRUE(constructionAssignmentSet.setInteriorSubSurfaceConstructionAssignments(interiorSubSurfaceConstructionAssignments));
  ASSERT_TRUE(constructionAssignmentSet.interiorSubSurfaceConstructionAssignments());
  EXPECT_EQ(interiorSubSurfaceConstructionAssignments, constructionAssignmentSet.interiorSubSurfaceConstructionAssignments().get());

  // Interior Partition Construction Name: Optional Object
  EXPECT_FALSE(constructionAssignmentSet.interiorPartitionConstruction());
  Construction interiorPartitionConstruction(m);
  EXPECT_TRUE(constructionAssignmentSet.setInteriorPartitionConstruction(interiorPartitionConstruction));
  ASSERT_TRUE(constructionAssignmentSet.interiorPartitionConstruction());
  EXPECT_EQ(interiorPartitionConstruction, constructionAssignmentSet.interiorPartitionConstruction().get());

  // Adiabatic Surface Construction Name: Optional Object
  EXPECT_FALSE(constructionAssignmentSet.adiabaticSurfaceConstruction());
  Construction adiabaticSurfaceConstruction(m);
  EXPECT_TRUE(constructionAssignmentSet.setAdiabaticSurfaceConstruction(adiabaticSurfaceConstruction));
  ASSERT_TRUE(constructionAssignmentSet.adiabaticSurfaceConstruction());
  EXPECT_EQ(adiabaticSurfaceConstruction, constructionAssignmentSet.adiabaticSurfaceConstruction().get());

  // Reset
  constructionAssignmentSet.resetExteriorSurfaceConstructionAssignments();
  EXPECT_FALSE(constructionAssignmentSet.exteriorSurfaceConstructionAssignments());
  EXPECT_TRUE(constructionAssignmentSet.interiorSurfaceConstructionAssignments());
  EXPECT_TRUE(constructionAssignmentSet.groundContactSurfaceConstructionAssignments());
  EXPECT_TRUE(constructionAssignmentSet.exteriorSubSurfaceConstructionAssignments());
  EXPECT_TRUE(constructionAssignmentSet.interiorSubSurfaceConstructionAssignments());
  EXPECT_TRUE(constructionAssignmentSet.interiorPartitionConstruction());
  EXPECT_TRUE(constructionAssignmentSet.adiabaticSurfaceConstruction());

  constructionAssignmentSet.resetInteriorSurfaceConstructionAssignments();
  EXPECT_FALSE(constructionAssignmentSet.exteriorSurfaceConstructionAssignments());
  EXPECT_FALSE(constructionAssignmentSet.interiorSurfaceConstructionAssignments());
  EXPECT_TRUE(constructionAssignmentSet.groundContactSurfaceConstructionAssignments());
  EXPECT_TRUE(constructionAssignmentSet.exteriorSubSurfaceConstructionAssignments());
  EXPECT_TRUE(constructionAssignmentSet.interiorSubSurfaceConstructionAssignments());
  EXPECT_TRUE(constructionAssignmentSet.interiorPartitionConstruction());
  EXPECT_TRUE(constructionAssignmentSet.adiabaticSurfaceConstruction());

  constructionAssignmentSet.resetGroundContactSurfaceConstructionAssignments();
  EXPECT_FALSE(constructionAssignmentSet.exteriorSurfaceConstructionAssignments());
  EXPECT_FALSE(constructionAssignmentSet.interiorSurfaceConstructionAssignments());
  EXPECT_FALSE(constructionAssignmentSet.groundContactSurfaceConstructionAssignments());
  EXPECT_TRUE(constructionAssignmentSet.exteriorSubSurfaceConstructionAssignments());
  EXPECT_TRUE(constructionAssignmentSet.interiorSubSurfaceConstructionAssignments());
  EXPECT_TRUE(constructionAssignmentSet.interiorPartitionConstruction());
  EXPECT_TRUE(constructionAssignmentSet.adiabaticSurfaceConstruction());

  constructionAssignmentSet.resetExteriorSubSurfaceConstructionAssignments();
  EXPECT_FALSE(constructionAssignmentSet.exteriorSurfaceConstructionAssignments());
  EXPECT_FALSE(constructionAssignmentSet.interiorSurfaceConstructionAssignments());
  EXPECT_FALSE(constructionAssignmentSet.groundContactSurfaceConstructionAssignments());
  EXPECT_FALSE(constructionAssignmentSet.exteriorSubSurfaceConstructionAssignments());
  EXPECT_TRUE(constructionAssignmentSet.interiorSubSurfaceConstructionAssignments());
  EXPECT_TRUE(constructionAssignmentSet.interiorPartitionConstruction());
  EXPECT_TRUE(constructionAssignmentSet.adiabaticSurfaceConstruction());

  constructionAssignmentSet.resetInteriorSubSurfaceConstructionAssignments();
  EXPECT_FALSE(constructionAssignmentSet.exteriorSurfaceConstructionAssignments());
  EXPECT_FALSE(constructionAssignmentSet.interiorSurfaceConstructionAssignments());
  EXPECT_FALSE(constructionAssignmentSet.groundContactSurfaceConstructionAssignments());
  EXPECT_FALSE(constructionAssignmentSet.exteriorSubSurfaceConstructionAssignments());
  EXPECT_FALSE(constructionAssignmentSet.interiorSubSurfaceConstructionAssignments());
  EXPECT_TRUE(constructionAssignmentSet.interiorPartitionConstruction());
  EXPECT_TRUE(constructionAssignmentSet.adiabaticSurfaceConstruction());

  constructionAssignmentSet.resetInteriorPartitionConstruction();
  EXPECT_FALSE(constructionAssignmentSet.exteriorSurfaceConstructionAssignments());
  EXPECT_FALSE(constructionAssignmentSet.interiorSurfaceConstructionAssignments());
  EXPECT_FALSE(constructionAssignmentSet.groundContactSurfaceConstructionAssignments());
  EXPECT_FALSE(constructionAssignmentSet.exteriorSubSurfaceConstructionAssignments());
  EXPECT_FALSE(constructionAssignmentSet.interiorSubSurfaceConstructionAssignments());
  EXPECT_FALSE(constructionAssignmentSet.interiorPartitionConstruction());
  EXPECT_TRUE(constructionAssignmentSet.adiabaticSurfaceConstruction());

  constructionAssignmentSet.resetAdiabaticSurfaceConstruction();
  EXPECT_FALSE(constructionAssignmentSet.exteriorSurfaceConstructionAssignments());
  EXPECT_FALSE(constructionAssignmentSet.interiorSurfaceConstructionAssignments());
  EXPECT_FALSE(constructionAssignmentSet.groundContactSurfaceConstructionAssignments());
  EXPECT_FALSE(constructionAssignmentSet.exteriorSubSurfaceConstructionAssignments());
  EXPECT_FALSE(constructionAssignmentSet.interiorSubSurfaceConstructionAssignments());
  EXPECT_FALSE(constructionAssignmentSet.interiorPartitionConstruction());
  EXPECT_FALSE(constructionAssignmentSet.adiabaticSurfaceConstruction());
}

TEST_F(EPModelFixture, ConstructionAssignmentSet_RemovingAssignmentsClearsSlot) {
  Model model;
  ConstructionAssignmentSet set(model);
  SurfaceConstructionAssignments exteriorSurfaces(model);
  SubSurfaceConstructionAssignments exteriorSubSurfaces(model);
  ASSERT_TRUE(set.setExteriorSurfaceConstructionAssignments(exteriorSurfaces));
  ASSERT_TRUE(set.setExteriorSubSurfaceConstructionAssignments(exteriorSubSurfaces));

  EXPECT_FALSE(exteriorSurfaces.remove().empty());
  EXPECT_FALSE(set.exteriorSurfaceConstructionAssignments());
  EXPECT_FALSE(exteriorSubSurfaces.remove().empty());
  EXPECT_FALSE(set.exteriorSubSurfaceConstructionAssignments());
}

TEST_F(EPModelFixture, ConstructionAssignmentSet_Clone) {
  Model model;
  ConstructionAssignmentSet set(model);

  SurfaceConstructionAssignments exteriorSurfaceConstructionAssignments(model);
  SurfaceConstructionAssignments interiorSurfaceConstructionAssignments(model);
  SurfaceConstructionAssignments groundContactSurfaceConstructionAssignments(model);
  SubSurfaceConstructionAssignments exteriorSubSurfaceConstructionAssignments(model);
  SubSurfaceConstructionAssignments interiorSubSurfaceConstructionAssignments(model);
  Construction interiorPartitionConstruction(model);
  Construction adiabaticSurfaceConstruction(model);
  ASSERT_TRUE(set.setExteriorSurfaceConstructionAssignments(exteriorSurfaceConstructionAssignments));
  ASSERT_TRUE(set.setInteriorSurfaceConstructionAssignments(interiorSurfaceConstructionAssignments));
  ASSERT_TRUE(set.setGroundContactSurfaceConstructionAssignments(groundContactSurfaceConstructionAssignments));
  ASSERT_TRUE(set.setExteriorSubSurfaceConstructionAssignments(exteriorSubSurfaceConstructionAssignments));
  ASSERT_TRUE(set.setInteriorSubSurfaceConstructionAssignments(interiorSubSurfaceConstructionAssignments));
  ASSERT_TRUE(set.setInteriorPartitionConstruction(interiorPartitionConstruction));
  ASSERT_TRUE(set.setAdiabaticSurfaceConstruction(adiabaticSurfaceConstruction));

  EXPECT_EQ(1, model.getConcreteModelObjects<ConstructionAssignmentSet>().size());
  EXPECT_EQ(3, model.getConcreteModelObjects<SurfaceConstructionAssignments>().size());
  EXPECT_EQ(2, model.getConcreteModelObjects<SubSurfaceConstructionAssignments>().size());
  EXPECT_EQ(2, model.getConcreteModelObjects<Construction>().size());

  // TODO: Need to implement clone(Model&) and resources() for deep copy...
  // {
  //   // Clone in another model
  //   Model model2;
  //   auto clone = set.clone(model2).cast<ConstructionAssignmentSet>();
  //   EXPECT_EQ(1, model2.getConcreteModelObjects<ConstructionAssignmentSet>().size());
  //   EXPECT_EQ(3, model2.getConcreteModelObjects<SurfaceConstructionAssignments>().size());
  //   EXPECT_EQ(2, model2.getConcreteModelObjects<SubSurfaceConstructionAssignments>().size());
  //   EXPECT_EQ(2, model2.getConcreteModelObjects<Construction>().size());
  //   EXPECT_TRUE(clone.exteriorSurfaceConstructionAssignments());
  //   EXPECT_TRUE(clone.interiorSurfaceConstructionAssignments());
  //   EXPECT_TRUE(clone.groundContactSurfaceConstructionAssignments());
  //   EXPECT_TRUE(clone.exteriorSubSurfaceConstructionAssignments());
  //   EXPECT_TRUE(clone.interiorSubSurfaceConstructionAssignments());
  //   EXPECT_TRUE(clone.interiorPartitionConstruction());
  //   EXPECT_TRUE(clone.adiabaticSurfaceConstruction());
  // }

  // Same-model clone shares the assignments objects and constructions.
  auto clone_ = model.addObject(set.idfObject());
  ASSERT_TRUE(clone_);
  auto clone = clone_->cast<ConstructionAssignmentSet>();
  EXPECT_EQ(2, model.getConcreteModelObjects<ConstructionAssignmentSet>().size());
  EXPECT_EQ(3, model.getConcreteModelObjects<SurfaceConstructionAssignments>().size());
  EXPECT_EQ(2, model.getConcreteModelObjects<SubSurfaceConstructionAssignments>().size());
  EXPECT_EQ(2, model.getConcreteModelObjects<Construction>().size());
  ASSERT_TRUE(clone.exteriorSurfaceConstructionAssignments());
  EXPECT_EQ(exteriorSurfaceConstructionAssignments, *clone.exteriorSurfaceConstructionAssignments());
  ASSERT_TRUE(clone.interiorSurfaceConstructionAssignments());
  EXPECT_EQ(interiorSurfaceConstructionAssignments, *clone.interiorSurfaceConstructionAssignments());
  ASSERT_TRUE(clone.groundContactSurfaceConstructionAssignments());
  EXPECT_EQ(groundContactSurfaceConstructionAssignments, *clone.groundContactSurfaceConstructionAssignments());
  ASSERT_TRUE(clone.exteriorSubSurfaceConstructionAssignments());
  EXPECT_EQ(exteriorSubSurfaceConstructionAssignments, *clone.exteriorSubSurfaceConstructionAssignments());
  ASSERT_TRUE(clone.interiorSubSurfaceConstructionAssignments());
  EXPECT_EQ(interiorSubSurfaceConstructionAssignments, *clone.interiorSubSurfaceConstructionAssignments());
  ASSERT_TRUE(clone.interiorPartitionConstruction());
  EXPECT_EQ(interiorPartitionConstruction, *clone.interiorPartitionConstruction());
  ASSERT_TRUE(clone.adiabaticSurfaceConstruction());
  EXPECT_EQ(adiabaticSurfaceConstruction, *clone.adiabaticSurfaceConstruction());
}

TEST_F(EPModelFixture, ConstructionAssignmentSet_Merge_FillsEmptySlotsAndKeepsSetOnes) {
  Model model;
  ConstructionAssignmentSet set(model);
  ConstructionAssignmentSet other(model);
  Construction ownPartition(model);
  Construction otherPartition(model);
  Construction otherAdiabatic(model);
  SurfaceConstructionAssignments otherGroundSurfaces(model);
  SubSurfaceConstructionAssignments otherInteriorSubSurfaces(model);
  ASSERT_TRUE(set.setInteriorPartitionConstruction(ownPartition));
  ASSERT_TRUE(other.setInteriorPartitionConstruction(otherPartition));
  ASSERT_TRUE(other.setAdiabaticSurfaceConstruction(otherAdiabatic));
  ASSERT_TRUE(other.setGroundContactSurfaceConstructionAssignments(otherGroundSurfaces));
  ASSERT_TRUE(other.setInteriorSubSurfaceConstructionAssignments(otherInteriorSubSurfaces));

  set.merge(other);

  ASSERT_TRUE(set.interiorPartitionConstruction());
  ASSERT_TRUE(set.adiabaticSurfaceConstruction());
  ASSERT_TRUE(set.groundContactSurfaceConstructionAssignments());
  ASSERT_TRUE(set.interiorSubSurfaceConstructionAssignments());
  EXPECT_EQ(ownPartition, *set.interiorPartitionConstruction());
  EXPECT_EQ(otherAdiabatic, *set.adiabaticSurfaceConstruction());
  // Empty sub-object slots point at other's objects; no copy is made.
  EXPECT_EQ(otherGroundSurfaces, *set.groundContactSurfaceConstructionAssignments());
  EXPECT_EQ(otherInteriorSubSurfaces, *set.interiorSubSurfaceConstructionAssignments());
  EXPECT_FALSE(set.exteriorSurfaceConstructionAssignments());
  EXPECT_EQ(1, model.getConcreteModelObjects<SurfaceConstructionAssignments>().size());
  EXPECT_EQ(1, model.getConcreteModelObjects<SubSurfaceConstructionAssignments>().size());

  ASSERT_TRUE(other.interiorPartitionConstruction());
  EXPECT_EQ(otherPartition, *other.interiorPartitionConstruction());
}

TEST_F(EPModelFixture, ConstructionAssignmentSet_Merge_MergesUnsharedAssignmentsInPlace) {
  Model model;
  ConstructionAssignmentSet set(model);
  ConstructionAssignmentSet other(model);
  SurfaceConstructionAssignments ownExterior(model);
  SurfaceConstructionAssignments otherExterior(model);
  Construction ownWall(model);
  Construction otherWall(model);
  Construction otherRoof(model);
  ASSERT_TRUE(ownExterior.setWallConstruction(ownWall));
  ASSERT_TRUE(otherExterior.setWallConstruction(otherWall));
  ASSERT_TRUE(otherExterior.setRoofCeilingConstruction(otherRoof));
  ASSERT_TRUE(set.setExteriorSurfaceConstructionAssignments(ownExterior));
  ASSERT_TRUE(other.setExteriorSurfaceConstructionAssignments(otherExterior));

  set.merge(other);

  ASSERT_TRUE(set.exteriorSurfaceConstructionAssignments());
  EXPECT_EQ(ownExterior, *set.exteriorSurfaceConstructionAssignments());
  EXPECT_EQ(2, model.getConcreteModelObjects<SurfaceConstructionAssignments>().size());
  ASSERT_TRUE(ownExterior.wallConstruction());
  ASSERT_TRUE(ownExterior.roofCeilingConstruction());
  EXPECT_EQ(ownWall, *ownExterior.wallConstruction());
  EXPECT_EQ(otherRoof, *ownExterior.roofCeilingConstruction());
}

TEST_F(EPModelFixture, ConstructionAssignmentSet_Merge_ClonesSharedAssignmentsBeforeMerging) {
  Model model;
  ConstructionAssignmentSet set(model);
  ConstructionAssignmentSet bystander(model);
  ConstructionAssignmentSet other(model);
  SubSurfaceConstructionAssignments sharedExterior(model);
  SubSurfaceConstructionAssignments otherExterior(model);
  Construction sharedWindow(model);
  Construction otherDoor(model);
  ASSERT_TRUE(sharedExterior.setFixedWindowConstruction(sharedWindow));
  ASSERT_TRUE(otherExterior.setDoorConstruction(otherDoor));
  ASSERT_TRUE(set.setExteriorSubSurfaceConstructionAssignments(sharedExterior));
  ASSERT_TRUE(bystander.setExteriorSubSurfaceConstructionAssignments(sharedExterior));
  ASSERT_TRUE(other.setExteriorSubSurfaceConstructionAssignments(otherExterior));

  set.merge(other);

  // set now points at a merged clone; the bystander keeps the untouched original.
  auto merged = set.exteriorSubSurfaceConstructionAssignments();
  ASSERT_TRUE(merged);
  EXPECT_NE(sharedExterior, *merged);
  EXPECT_EQ(3, model.getConcreteModelObjects<SubSurfaceConstructionAssignments>().size());
  ASSERT_TRUE(merged->fixedWindowConstruction());
  ASSERT_TRUE(merged->doorConstruction());
  EXPECT_EQ(sharedWindow, *merged->fixedWindowConstruction());
  EXPECT_EQ(otherDoor, *merged->doorConstruction());

  ASSERT_TRUE(bystander.exteriorSubSurfaceConstructionAssignments());
  EXPECT_EQ(sharedExterior, *bystander.exteriorSubSurfaceConstructionAssignments());
  EXPECT_FALSE(sharedExterior.doorConstruction());
}

TEST_F(EPModelFixture, ConstructionAssignmentSet_BuildingSetReset) {
  Model model;
  auto building = model.getUniqueModelObject<Building>();
  ConstructionAssignmentSet set(model);
  EXPECT_FALSE(building.constructionAssignmentSet());

  EXPECT_TRUE(building.setConstructionAssignmentSet(set));
  ASSERT_TRUE(building.constructionAssignmentSet());
  EXPECT_EQ(set, *building.constructionAssignmentSet());

  building.resetConstructionAssignmentSet();
  EXPECT_FALSE(building.constructionAssignmentSet());

  ASSERT_TRUE(building.setConstructionAssignmentSet(set));
  EXPECT_FALSE(set.remove().empty());
  EXPECT_FALSE(building.constructionAssignmentSet());
}

TEST_F(EPModelFixture, ConstructionAssignmentSet_SpaceSetReset) {
  Model model;
  Space space(model);
  ConstructionAssignmentSet set(model);
  EXPECT_FALSE(space.constructionAssignmentSet());

  EXPECT_TRUE(space.setConstructionAssignmentSet(set));
  ASSERT_TRUE(space.constructionAssignmentSet());
  EXPECT_EQ(set, *space.constructionAssignmentSet());

  space.resetConstructionAssignmentSet();
  EXPECT_FALSE(space.constructionAssignmentSet());

  ASSERT_TRUE(space.setConstructionAssignmentSet(set));
  EXPECT_FALSE(set.remove().empty());
  EXPECT_FALSE(space.constructionAssignmentSet());
}

// Building and Space run canonicalizers on load: check that they still reference their ConstructionAssignmentSet afterwards.
TEST_F(EPModelFixture, ConstructionAssignmentSet_BuildingAndSpace_Reload) {
  Model model;
  const std::vector<openstudio::Point3d> floorPrint{{0.0, 0.0, 0.0}, {0.0, 10.0, 0.0}, {10.0, 10.0, 0.0}, {10.0, 0.0, 0.0}};
  auto space = Space::fromFloorPrint(floorPrint, 3.0, model, "My Space");
  ASSERT_TRUE(space);
  auto building = model.getUniqueModelObject<Building>();

  ConstructionAssignmentSet buildingSet(model);
  ASSERT_TRUE(buildingSet.setName("My Building ConstructionAssignmentSet"));
  ConstructionAssignmentSet spaceSet(model);
  ASSERT_TRUE(spaceSet.setName("My Space ConstructionAssignmentSet"));
  ASSERT_TRUE(building.setConstructionAssignmentSet(buildingSet));
  ASSERT_TRUE(space->setConstructionAssignmentSet(spaceSet));

  const auto idfPath =
    openstudio::tempDir() / openstudio::toPath("epmodel-construction-assignment-set-" + openstudio::removeBraces(openstudio::createUUID()) + ".idf");
  ASSERT_TRUE(model.save(idfPath, true));
  auto loadedModel = Model::load(idfPath);
  openstudio::filesystem::remove(idfPath);
  ASSERT_TRUE(loadedModel);

  auto loadedBuildingSet = loadedModel->getConcreteModelObjectByName<ConstructionAssignmentSet>("My Building ConstructionAssignmentSet");
  auto loadedSpaceSet = loadedModel->getConcreteModelObjectByName<ConstructionAssignmentSet>("My Space ConstructionAssignmentSet");
  auto loadedSpace = loadedModel->getConcreteModelObjectByName<Space>("My Space");
  ASSERT_TRUE(loadedBuildingSet);
  ASSERT_TRUE(loadedSpaceSet);
  ASSERT_TRUE(loadedSpace);

  auto loadedBuilding = loadedModel->getUniqueModelObject<Building>();
  ASSERT_TRUE(loadedBuilding.constructionAssignmentSet());
  EXPECT_EQ(*loadedBuildingSet, *loadedBuilding.constructionAssignmentSet());
  ASSERT_TRUE(loadedSpace->constructionAssignmentSet());
  EXPECT_EQ(*loadedSpaceSet, *loadedSpace->constructionAssignmentSet());
}
