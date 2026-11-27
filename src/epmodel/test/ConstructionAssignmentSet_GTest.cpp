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
#include "../ParentObject/Building.hpp"
#include "../ParentObject/Building_Impl.hpp"
#include "../PlanarSurface/InteriorPartitionSurface.hpp"
#include "../PlanarSurface/InteriorPartitionSurface_Impl.hpp"
#include "../PlanarSurface/SubSurface.hpp"
#include "../PlanarSurface/SubSurface_Impl.hpp"
#include "../PlanarSurface/Surface.hpp"
#include "../PlanarSurface/Surface_Impl.hpp"
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
#include <utilities/idd/BuildingSurface_Detailed_FieldEnums.hxx>
#include <utilities/idd/InternalMass_FieldEnums.hxx>

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

namespace {

const std::vector<openstudio::Point3d> wallVertices{{0.0, 0.0, 3.0}, {0.0, 0.0, 0.0}, {10.0, 0.0, 0.0}, {10.0, 0.0, 3.0}};
const std::vector<openstudio::Point3d> windowVertices{{2.0, 0.0, 2.0}, {2.0, 0.0, 1.0}, {4.0, 0.0, 1.0}, {4.0, 0.0, 2.0}};

Construction namedConstruction(const Model& model, const std::string& name) {
  Construction construction(model);
  construction.setName(name);
  return construction;
}

SurfaceConstructionAssignments surfaceConstructionAssignments(const Model& model, const std::string& prefix) {
  SurfaceConstructionAssignments assignments(model);
  EXPECT_TRUE(assignments.setName(prefix + " Surface Construction Assignments"));
  EXPECT_TRUE(assignments.setFloorConstruction(namedConstruction(model, prefix + " Floor")));
  EXPECT_TRUE(assignments.setWallConstruction(namedConstruction(model, prefix + " Wall")));
  EXPECT_TRUE(assignments.setRoofCeilingConstruction(namedConstruction(model, prefix + " RoofCeiling")));
  return assignments;
}

SubSurfaceConstructionAssignments subSurfaceConstructionAssignments(const Model& model, const std::string& prefix) {
  SubSurfaceConstructionAssignments assignments(model);
  EXPECT_TRUE(assignments.setName(prefix + " SubSurface Construction Assignments"));
  EXPECT_TRUE(assignments.setFixedWindowConstruction(namedConstruction(model, prefix + " FixedWindow")));
  EXPECT_TRUE(assignments.setOperableWindowConstruction(namedConstruction(model, prefix + " OperableWindow")));
  EXPECT_TRUE(assignments.setDoorConstruction(namedConstruction(model, prefix + " Door")));
  EXPECT_TRUE(assignments.setGlassDoorConstruction(namedConstruction(model, prefix + " GlassDoor")));
  EXPECT_TRUE(assignments.setOverheadDoorConstruction(namedConstruction(model, prefix + " OverheadDoor")));
  EXPECT_TRUE(assignments.setSkylightConstruction(namedConstruction(model, prefix + " Skylight")));
  EXPECT_TRUE(assignments.setTubularDaylightDomeConstruction(namedConstruction(model, prefix + " TubularDaylightDome")));
  EXPECT_TRUE(assignments.setTubularDaylightDiffuserConstruction(namedConstruction(model, prefix + " TubularDaylightDiffuser")));
  return assignments;
}

// A single-layer construction: two zero-layer constructions count as reversed copies of each other, as in EnergyPlus
Construction layeredConstruction(const Model& model, const std::string& name) {
  auto construction = namedConstruction(model, name);
  StandardOpaqueMaterial material(model);
  EXPECT_TRUE(construction.setLayers({material}));
  return construction;
}

std::string defaultConstructionName(const ConstructionAssignmentSet& set, const PlanarSurface& planarSurface) {
  auto construction_ = set.getDefaultConstruction(planarSurface);
  return construction_ ? construction_->nameString() : "";
}

}  // namespace

TEST_F(EPModelFixture, ConstructionAssignmentSet_GetDefaultConstruction_Surface) {
  Model model;
  ConstructionAssignmentSet set(model);
  Surface surface(wallVertices, model);

  // Nothing assigned
  EXPECT_FALSE(set.getDefaultConstruction(surface));

  ASSERT_TRUE(set.setExteriorSurfaceConstructionAssignments(surfaceConstructionAssignments(model, "Exterior")));
  ASSERT_TRUE(set.setInteriorSurfaceConstructionAssignments(surfaceConstructionAssignments(model, "Interior")));
  ASSERT_TRUE(set.setGroundContactSurfaceConstructionAssignments(surfaceConstructionAssignments(model, "Ground")));
  ASSERT_TRUE(set.setAdiabaticSurfaceConstruction(namedConstruction(model, "Adiabatic")));

  // By Surface Type, Roof and Ceiling both use the roof ceiling slot
  ASSERT_TRUE(surface.setOutsideBoundaryCondition("Outdoors"));
  ASSERT_TRUE(surface.setSurfaceType("Wall"));
  EXPECT_EQ("Exterior Wall", defaultConstructionName(set, surface));
  ASSERT_TRUE(surface.setSurfaceType("Floor"));
  EXPECT_EQ("Exterior Floor", defaultConstructionName(set, surface));
  ASSERT_TRUE(surface.setSurfaceType("Roof"));
  EXPECT_EQ("Exterior RoofCeiling", defaultConstructionName(set, surface));
  ASSERT_TRUE(surface.setSurfaceType("Ceiling"));
  EXPECT_EQ("Exterior RoofCeiling", defaultConstructionName(set, surface));

  // By Outside Boundary Condition
  ASSERT_TRUE(surface.setSurfaceType("Wall"));
  ASSERT_TRUE(surface.setOutsideBoundaryCondition("Ground"));
  EXPECT_EQ("Ground Wall", defaultConstructionName(set, surface));
  ASSERT_TRUE(surface.setOutsideBoundaryCondition("GroundFCfactorMethod"));
  EXPECT_EQ("Ground Wall", defaultConstructionName(set, surface));
  ASSERT_TRUE(surface.setOutsideBoundaryCondition("Foundation"));
  EXPECT_EQ("Ground Wall", defaultConstructionName(set, surface));
  ASSERT_TRUE(surface.setOutsideBoundaryCondition("Zone"));
  EXPECT_EQ("Interior Wall", defaultConstructionName(set, surface));
  ASSERT_TRUE(surface.setOutsideBoundaryCondition("Adiabatic"));
  EXPECT_EQ("Adiabatic", defaultConstructionName(set, surface));

  // Model's DefaultConstructionSet assigns nothing to these, but EnergyPlus does
  ASSERT_TRUE(surface.setString(openstudio::BuildingSurface_DetailedFields::OutsideBoundaryCondition, "OtherSideCoefficients"));
  EXPECT_EQ("Exterior Wall", defaultConstructionName(set, surface));
  ASSERT_TRUE(surface.setString(openstudio::BuildingSurface_DetailedFields::OutsideBoundaryCondition, "OtherSideConditionsModel"));
  EXPECT_EQ("Interior Wall", defaultConstructionName(set, surface));

  // A Surface matched with another uses the interior assignments; one matched with itself is adiabatic
  Surface other(wallVertices, model);
  ASSERT_TRUE(surface.setAdjacentSurface(other));
  EXPECT_EQ("Surface", surface.outsideBoundaryCondition());
  EXPECT_EQ("Interior Wall", defaultConstructionName(set, surface));
  ASSERT_TRUE(surface.setAdjacentSurface(surface));
  EXPECT_EQ("Surface", surface.outsideBoundaryCondition());
  EXPECT_EQ("Adiabatic", defaultConstructionName(set, surface));

  // An empty slot assigns nothing
  set.resetInteriorSurfaceConstructionAssignments();
  ASSERT_TRUE(surface.setOutsideBoundaryCondition("Zone"));
  EXPECT_FALSE(set.getDefaultConstruction(surface));
}

TEST_F(EPModelFixture, ConstructionAssignmentSet_GetDefaultConstruction_SubSurface) {
  Model model;
  ConstructionAssignmentSet set(model);
  ASSERT_TRUE(set.setExteriorSubSurfaceConstructionAssignments(subSurfaceConstructionAssignments(model, "Exterior")));
  ASSERT_TRUE(set.setInteriorSubSurfaceConstructionAssignments(subSurfaceConstructionAssignments(model, "Interior")));
  ASSERT_TRUE(set.setAdiabaticSurfaceConstruction(namedConstruction(model, "Adiabatic")));

  // No base surface
  SubSurface subSurface(windowVertices, model);
  EXPECT_FALSE(set.getDefaultConstruction(subSurface));

  Surface surface(wallVertices, model);
  ASSERT_TRUE(surface.setSurfaceType("Wall"));
  ASSERT_TRUE(surface.setOutsideBoundaryCondition("Outdoors"));
  ASSERT_TRUE(subSurface.setSurface(surface));

  // Window is kept for backward compatibility and uses the fixed window slot
  for (const std::string type :
       {"Window", "FixedWindow", "OperableWindow", "Door", "GlassDoor", "Skylight", "TubularDaylightDome", "TubularDaylightDiffuser"}) {
    ASSERT_TRUE(subSurface.setSubSurfaceType(type)) << type;
    const std::string expectedSlot = (type == "Window") ? "FixedWindow" : type;
    EXPECT_EQ("Exterior " + expectedSlot, defaultConstructionName(set, subSurface)) << type;
  }

  // The base surface's Outside Boundary Condition picks exterior or interior, anything but Outdoors and OtherSideCoefficients is interior
  ASSERT_TRUE(subSurface.setSubSurfaceType("Door"));
  ASSERT_TRUE(surface.setString(openstudio::BuildingSurface_DetailedFields::OutsideBoundaryCondition, "OtherSideCoefficients"));
  EXPECT_EQ("Exterior Door", defaultConstructionName(set, subSurface));
  for (const std::string obc : {"Zone", "Ground", "Adiabatic"}) {
    ASSERT_TRUE(surface.setString(openstudio::BuildingSurface_DetailedFields::OutsideBoundaryCondition, obc)) << obc;
    ASSERT_TRUE(subSurface.surface()) << obc;
    EXPECT_EQ("Interior Door", defaultConstructionName(set, subSurface)) << obc;
  }

  // An empty slot assigns nothing
  set.resetInteriorSubSurfaceConstructionAssignments();
  EXPECT_FALSE(set.getDefaultConstruction(subSurface));

  // setOutsideBoundaryCondition("Adiabatic") removes the subsurfaces, the base surface then uses the adiabatic construction
  ASSERT_TRUE(surface.setOutsideBoundaryCondition("Adiabatic"));
  EXPECT_TRUE(subSurface.handle().isNull());
  EXPECT_TRUE(surface.subSurfaces().empty());
  EXPECT_EQ("Adiabatic", defaultConstructionName(set, surface));
}

TEST_F(EPModelFixture, ConstructionAssignmentSet_GetDefaultConstruction_InteriorPartitionSurface) {
  Model model;
  ConstructionAssignmentSet set(model);
  InteriorPartitionSurface interiorPartitionSurface(wallVertices, model);
  EXPECT_FALSE(set.getDefaultConstruction(interiorPartitionSurface));

  auto partition = namedConstruction(model, "Partition");
  ASSERT_TRUE(set.setInteriorPartitionConstruction(partition));
  ASSERT_TRUE(set.getDefaultConstruction(interiorPartitionSurface));
  EXPECT_EQ(partition, *set.getDefaultConstruction(interiorPartitionSurface));
}

TEST_F(EPModelFixture, ConstructionAssignmentSet_PlanarSurfaceConstruction_SearchDistance) {
  Model model;
  auto building = model.getUniqueModelObject<Building>();
  Space space(model);

  Surface surface(wallVertices, model);
  ASSERT_TRUE(surface.setSpace(space));
  ASSERT_TRUE(surface.setSurfaceType("Wall"));
  ASSERT_TRUE(surface.setOutsideBoundaryCondition("Outdoors"));
  SubSurface subSurface(windowVertices, model);
  ASSERT_TRUE(subSurface.setSurface(surface));
  ASSERT_TRUE(subSurface.setSubSurfaceType("FixedWindow"));
  InteriorPartitionSurface interiorPartitionSurface(wallVertices, model);
  ASSERT_TRUE(interiorPartitionSurface.setPointer(openstudio::InternalMassFields::SpaceorSpaceListName, space.handle()));

  const std::vector<PlanarSurface> planarSurfaces{surface, subSurface, interiorPartitionSurface};

  // No sets
  for (const auto& planarSurface : planarSurfaces) {
    EXPECT_TRUE(planarSurface.isConstructionDefaulted()) << planarSurface.briefDescription();
    EXPECT_FALSE(planarSurface.construction()) << planarSurface.briefDescription();
    EXPECT_FALSE(planarSurface.constructionWithSearchDistance()) << planarSurface.briefDescription();
  }

  // Building set: search distance 2
  ConstructionAssignmentSet buildingSet(model);
  SurfaceConstructionAssignments buildingSurfaceAssignments(model);
  SubSurfaceConstructionAssignments buildingSubSurfaceAssignments(model);
  auto buildingWall = namedConstruction(model, "Building Wall");
  auto buildingWindow = namedConstruction(model, "Building Window");
  auto buildingPartition = namedConstruction(model, "Building Partition");
  ASSERT_TRUE(buildingSurfaceAssignments.setWallConstruction(buildingWall));
  ASSERT_TRUE(buildingSubSurfaceAssignments.setFixedWindowConstruction(buildingWindow));
  ASSERT_TRUE(buildingSet.setExteriorSurfaceConstructionAssignments(buildingSurfaceAssignments));
  ASSERT_TRUE(buildingSet.setExteriorSubSurfaceConstructionAssignments(buildingSubSurfaceAssignments));
  ASSERT_TRUE(buildingSet.setInteriorPartitionConstruction(buildingPartition));
  ASSERT_TRUE(building.setConstructionAssignmentSet(buildingSet));

  const std::vector<Construction> buildingConstructions{buildingWall, buildingWindow, buildingPartition};
  for (size_t i = 0; i < planarSurfaces.size(); ++i) {
    const auto& planarSurface = planarSurfaces[i];
    EXPECT_TRUE(planarSurface.isConstructionDefaulted()) << planarSurface.briefDescription();
    ASSERT_TRUE(planarSurface.construction()) << planarSurface.briefDescription();
    EXPECT_EQ(buildingConstructions[i], *planarSurface.construction()) << planarSurface.briefDescription();
    auto cwsd_ = planarSurface.constructionWithSearchDistance();
    ASSERT_TRUE(cwsd_) << planarSurface.briefDescription();
    EXPECT_EQ(buildingConstructions[i], cwsd_->first) << planarSurface.briefDescription();
    EXPECT_EQ(2, cwsd_->second) << planarSurface.briefDescription();
  }

  // Space set with only the wall: search distance 1 for the wall, the others fall through to the Building's set
  ConstructionAssignmentSet spaceSet(model);
  SurfaceConstructionAssignments spaceSurfaceAssignments(model);
  auto spaceWall = namedConstruction(model, "Space Wall");
  ASSERT_TRUE(spaceSurfaceAssignments.setWallConstruction(spaceWall));
  ASSERT_TRUE(spaceSet.setExteriorSurfaceConstructionAssignments(spaceSurfaceAssignments));
  ASSERT_TRUE(space.setConstructionAssignmentSet(spaceSet));

  ASSERT_TRUE(surface.constructionWithSearchDistance());
  EXPECT_EQ(spaceWall, surface.constructionWithSearchDistance()->first);
  EXPECT_EQ(1, surface.constructionWithSearchDistance()->second);
  ASSERT_TRUE(space.getDefaultConstruction(surface));
  EXPECT_EQ(spaceWall, *space.getDefaultConstruction(surface));
  ASSERT_TRUE(subSurface.constructionWithSearchDistance());
  EXPECT_EQ(buildingWindow, subSurface.constructionWithSearchDistance()->first);
  EXPECT_EQ(2, subSurface.constructionWithSearchDistance()->second);

  // Explicit construction: search distance 0
  auto explicitWall = namedConstruction(model, "Explicit Wall");
  ASSERT_TRUE(surface.setConstruction(explicitWall));
  EXPECT_FALSE(surface.isConstructionDefaulted());
  ASSERT_TRUE(surface.constructionWithSearchDistance());
  EXPECT_EQ(explicitWall, surface.constructionWithSearchDistance()->first);
  EXPECT_EQ(0, surface.constructionWithSearchDistance()->second);
  ASSERT_TRUE(surface.construction());
  EXPECT_EQ(explicitWall, *surface.construction());

  surface.resetConstruction();
  EXPECT_TRUE(surface.isConstructionDefaulted());
  ASSERT_TRUE(surface.construction());
  EXPECT_EQ(spaceWall, *surface.construction());

  // A surface without a Space only uses the Building's set, as EnergyPlus puts it in its zone's default Space
  Surface spacelessSurface(wallVertices, model);
  ASSERT_TRUE(spacelessSurface.setSurfaceType("Wall"));
  ASSERT_TRUE(spacelessSurface.setOutsideBoundaryCondition("Outdoors"));
  EXPECT_FALSE(spacelessSurface.space());
  ASSERT_TRUE(spacelessSurface.constructionWithSearchDistance());
  EXPECT_EQ(buildingWall, spacelessSurface.constructionWithSearchDistance()->first);
  EXPECT_EQ(2, spacelessSurface.constructionWithSearchDistance()->second);
}

TEST_F(EPModelFixture, ConstructionAssignmentSet_PlanarSurfaceConstruction_AdjacentSurface) {
  Model model;
  auto building = model.getUniqueModelObject<Building>();
  Space space1(model);
  Space space2(model);

  Surface surface1(wallVertices, model);
  ASSERT_TRUE(surface1.setSpace(space1));
  ASSERT_TRUE(surface1.setSurfaceType("Wall"));
  Surface surface2(wallVertices, model);
  ASSERT_TRUE(surface2.setSpace(space2));
  ASSERT_TRUE(surface2.setSurfaceType("Wall"));
  ASSERT_TRUE(surface1.setAdjacentSurface(surface2));
  ASSERT_TRUE(surface2.adjacentSurface());

  // Neither side has a construction
  EXPECT_FALSE(surface1.construction());
  EXPECT_FALSE(surface2.construction());

  // Only one side has a construction: both use it
  ConstructionAssignmentSet buildingSet(model);
  SurfaceConstructionAssignments buildingInterior(model);
  auto buildingWall = layeredConstruction(model, "Building Wall");
  ASSERT_TRUE(buildingInterior.setWallConstruction(buildingWall));
  ASSERT_TRUE(buildingSet.setInteriorSurfaceConstructionAssignments(buildingInterior));

  auto explicitWall = layeredConstruction(model, "Explicit Wall");
  ASSERT_TRUE(surface1.setConstruction(explicitWall));
  ASSERT_TRUE(surface1.construction());
  EXPECT_EQ(explicitWall, *surface1.construction());
  ASSERT_TRUE(surface2.construction());
  EXPECT_EQ(explicitWall, *surface2.construction());
  EXPECT_FALSE(surface2.constructionWithSearchDistance());

  // Both have one: the lower search distance wins, here the explicit one (0) over the Building's (2)
  ASSERT_TRUE(building.setConstructionAssignmentSet(buildingSet));
  ASSERT_TRUE(surface2.constructionWithSearchDistance());
  EXPECT_EQ(buildingWall, surface2.constructionWithSearchDistance()->first);
  ASSERT_TRUE(surface2.construction());
  EXPECT_EQ(explicitWall, *surface2.construction());

  // Space's (1) over the Building's (2)
  surface1.resetConstruction();
  ConstructionAssignmentSet spaceSet(model);
  SurfaceConstructionAssignments spaceInterior(model);
  auto spaceWall = layeredConstruction(model, "Space Wall");
  ASSERT_TRUE(spaceInterior.setWallConstruction(spaceWall));
  ASSERT_TRUE(spaceSet.setInteriorSurfaceConstructionAssignments(spaceInterior));
  ASSERT_TRUE(space2.setConstructionAssignmentSet(spaceSet));
  ASSERT_TRUE(surface1.construction());
  EXPECT_EQ(spaceWall, *surface1.construction());
  ASSERT_TRUE(surface2.construction());
  EXPECT_EQ(spaceWall, *surface2.construction());

  // Same search distance and different constructions: each keeps its own
  ASSERT_TRUE(surface1.setConstruction(explicitWall));
  auto otherExplicitWall = layeredConstruction(model, "Other Explicit Wall");
  ASSERT_TRUE(surface2.setConstruction(otherExplicitWall));
  ASSERT_TRUE(surface1.construction());
  EXPECT_EQ(explicitWall, *surface1.construction());
  ASSERT_TRUE(surface2.construction());
  EXPECT_EQ(otherExplicitWall, *surface2.construction());

  // Constructions with reversed layers: each keeps its own regardless of search distance (EnergyPlus checks this first, Model last)
  StandardOpaqueMaterial outside(model);
  StandardOpaqueMaterial inside(model);
  ASSERT_TRUE(explicitWall.setLayers({outside, inside}));
  ASSERT_TRUE(spaceWall.setLayers({inside, outside}));
  surface2.resetConstruction();
  ASSERT_TRUE(surface2.constructionWithSearchDistance());
  EXPECT_EQ(spaceWall, surface2.constructionWithSearchDistance()->first);
  EXPECT_EQ(1, surface2.constructionWithSearchDistance()->second);
  ASSERT_TRUE(surface1.construction());
  EXPECT_EQ(explicitWall, *surface1.construction());
  ASSERT_TRUE(surface2.construction());
  EXPECT_EQ(spaceWall, *surface2.construction());
}
