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
#include "../ResourceObject/SubSurfaceConstructionAssignments.hpp"
#include "../ResourceObject/SubSurfaceConstructionAssignments_Impl.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SubSurfaceConstructionAssignments_GettersSetters) {
  Model m;
  SubSurfaceConstructionAssignments subSurfaceConstructionAssignments(m);

  subSurfaceConstructionAssignments.setName("My SubSurfaceConstructionAssignments");

  // Fixed Window Construction Name: Optional Object
  EXPECT_FALSE(subSurfaceConstructionAssignments.fixedWindowConstruction());
  Construction fixedWindowConstruction(m);
  EXPECT_TRUE(subSurfaceConstructionAssignments.setFixedWindowConstruction(fixedWindowConstruction));
  ASSERT_TRUE(subSurfaceConstructionAssignments.fixedWindowConstruction());
  EXPECT_EQ(fixedWindowConstruction, subSurfaceConstructionAssignments.fixedWindowConstruction().get());

  // Operable Window Construction Name: Optional Object
  EXPECT_FALSE(subSurfaceConstructionAssignments.operableWindowConstruction());
  Construction operableWindowConstruction(m);
  EXPECT_TRUE(subSurfaceConstructionAssignments.setOperableWindowConstruction(operableWindowConstruction));
  ASSERT_TRUE(subSurfaceConstructionAssignments.operableWindowConstruction());
  EXPECT_EQ(operableWindowConstruction, subSurfaceConstructionAssignments.operableWindowConstruction().get());

  // Door Construction Name: Optional Object
  EXPECT_FALSE(subSurfaceConstructionAssignments.doorConstruction());
  Construction doorConstruction(m);
  EXPECT_TRUE(subSurfaceConstructionAssignments.setDoorConstruction(doorConstruction));
  ASSERT_TRUE(subSurfaceConstructionAssignments.doorConstruction());
  EXPECT_EQ(doorConstruction, subSurfaceConstructionAssignments.doorConstruction().get());

  // Glass Door Construction Name: Optional Object
  EXPECT_FALSE(subSurfaceConstructionAssignments.glassDoorConstruction());
  Construction glassDoorConstruction(m);
  EXPECT_TRUE(subSurfaceConstructionAssignments.setGlassDoorConstruction(glassDoorConstruction));
  ASSERT_TRUE(subSurfaceConstructionAssignments.glassDoorConstruction());
  EXPECT_EQ(glassDoorConstruction, subSurfaceConstructionAssignments.glassDoorConstruction().get());

  // Overhead Door Construction Name: Optional Object
  EXPECT_FALSE(subSurfaceConstructionAssignments.overheadDoorConstruction());
  Construction overheadDoorConstruction(m);
  EXPECT_TRUE(subSurfaceConstructionAssignments.setOverheadDoorConstruction(overheadDoorConstruction));
  ASSERT_TRUE(subSurfaceConstructionAssignments.overheadDoorConstruction());
  EXPECT_EQ(overheadDoorConstruction, subSurfaceConstructionAssignments.overheadDoorConstruction().get());

  // Skylight Construction Name: Optional Object
  EXPECT_FALSE(subSurfaceConstructionAssignments.skylightConstruction());
  Construction skylightConstruction(m);
  EXPECT_TRUE(subSurfaceConstructionAssignments.setSkylightConstruction(skylightConstruction));
  ASSERT_TRUE(subSurfaceConstructionAssignments.skylightConstruction());
  EXPECT_EQ(skylightConstruction, subSurfaceConstructionAssignments.skylightConstruction().get());

  // Tubular Daylight Dome Construction Name: Optional Object
  EXPECT_FALSE(subSurfaceConstructionAssignments.tubularDaylightDomeConstruction());
  Construction tubularDaylightDomeConstruction(m);
  EXPECT_TRUE(subSurfaceConstructionAssignments.setTubularDaylightDomeConstruction(tubularDaylightDomeConstruction));
  ASSERT_TRUE(subSurfaceConstructionAssignments.tubularDaylightDomeConstruction());
  EXPECT_EQ(tubularDaylightDomeConstruction, subSurfaceConstructionAssignments.tubularDaylightDomeConstruction().get());

  // Tubular Daylight Diffuser Construction Name: Optional Object
  EXPECT_FALSE(subSurfaceConstructionAssignments.tubularDaylightDiffuserConstruction());
  Construction tubularDaylightDiffuserConstruction(m);
  EXPECT_TRUE(subSurfaceConstructionAssignments.setTubularDaylightDiffuserConstruction(tubularDaylightDiffuserConstruction));
  ASSERT_TRUE(subSurfaceConstructionAssignments.tubularDaylightDiffuserConstruction());
  EXPECT_EQ(tubularDaylightDiffuserConstruction, subSurfaceConstructionAssignments.tubularDaylightDiffuserConstruction().get());

  // Reset
  subSurfaceConstructionAssignments.resetFixedWindowConstruction();
  EXPECT_FALSE(subSurfaceConstructionAssignments.fixedWindowConstruction());
  EXPECT_TRUE(subSurfaceConstructionAssignments.operableWindowConstruction());
  EXPECT_TRUE(subSurfaceConstructionAssignments.doorConstruction());
  EXPECT_TRUE(subSurfaceConstructionAssignments.glassDoorConstruction());
  EXPECT_TRUE(subSurfaceConstructionAssignments.overheadDoorConstruction());
  EXPECT_TRUE(subSurfaceConstructionAssignments.skylightConstruction());
  EXPECT_TRUE(subSurfaceConstructionAssignments.tubularDaylightDomeConstruction());
  EXPECT_TRUE(subSurfaceConstructionAssignments.tubularDaylightDiffuserConstruction());

  subSurfaceConstructionAssignments.resetOperableWindowConstruction();
  EXPECT_FALSE(subSurfaceConstructionAssignments.fixedWindowConstruction());
  EXPECT_FALSE(subSurfaceConstructionAssignments.operableWindowConstruction());
  EXPECT_TRUE(subSurfaceConstructionAssignments.doorConstruction());
  EXPECT_TRUE(subSurfaceConstructionAssignments.glassDoorConstruction());
  EXPECT_TRUE(subSurfaceConstructionAssignments.overheadDoorConstruction());
  EXPECT_TRUE(subSurfaceConstructionAssignments.skylightConstruction());
  EXPECT_TRUE(subSurfaceConstructionAssignments.tubularDaylightDomeConstruction());
  EXPECT_TRUE(subSurfaceConstructionAssignments.tubularDaylightDiffuserConstruction());

  subSurfaceConstructionAssignments.resetDoorConstruction();
  EXPECT_FALSE(subSurfaceConstructionAssignments.fixedWindowConstruction());
  EXPECT_FALSE(subSurfaceConstructionAssignments.operableWindowConstruction());
  EXPECT_FALSE(subSurfaceConstructionAssignments.doorConstruction());
  EXPECT_TRUE(subSurfaceConstructionAssignments.glassDoorConstruction());
  EXPECT_TRUE(subSurfaceConstructionAssignments.overheadDoorConstruction());
  EXPECT_TRUE(subSurfaceConstructionAssignments.skylightConstruction());
  EXPECT_TRUE(subSurfaceConstructionAssignments.tubularDaylightDomeConstruction());
  EXPECT_TRUE(subSurfaceConstructionAssignments.tubularDaylightDiffuserConstruction());

  subSurfaceConstructionAssignments.resetGlassDoorConstruction();
  EXPECT_FALSE(subSurfaceConstructionAssignments.fixedWindowConstruction());
  EXPECT_FALSE(subSurfaceConstructionAssignments.operableWindowConstruction());
  EXPECT_FALSE(subSurfaceConstructionAssignments.doorConstruction());
  EXPECT_FALSE(subSurfaceConstructionAssignments.glassDoorConstruction());
  EXPECT_TRUE(subSurfaceConstructionAssignments.overheadDoorConstruction());
  EXPECT_TRUE(subSurfaceConstructionAssignments.skylightConstruction());
  EXPECT_TRUE(subSurfaceConstructionAssignments.tubularDaylightDomeConstruction());
  EXPECT_TRUE(subSurfaceConstructionAssignments.tubularDaylightDiffuserConstruction());

  subSurfaceConstructionAssignments.resetOverheadDoorConstruction();
  EXPECT_FALSE(subSurfaceConstructionAssignments.fixedWindowConstruction());
  EXPECT_FALSE(subSurfaceConstructionAssignments.operableWindowConstruction());
  EXPECT_FALSE(subSurfaceConstructionAssignments.doorConstruction());
  EXPECT_FALSE(subSurfaceConstructionAssignments.glassDoorConstruction());
  EXPECT_FALSE(subSurfaceConstructionAssignments.overheadDoorConstruction());
  EXPECT_TRUE(subSurfaceConstructionAssignments.skylightConstruction());
  EXPECT_TRUE(subSurfaceConstructionAssignments.tubularDaylightDomeConstruction());
  EXPECT_TRUE(subSurfaceConstructionAssignments.tubularDaylightDiffuserConstruction());

  subSurfaceConstructionAssignments.resetSkylightConstruction();
  EXPECT_FALSE(subSurfaceConstructionAssignments.fixedWindowConstruction());
  EXPECT_FALSE(subSurfaceConstructionAssignments.operableWindowConstruction());
  EXPECT_FALSE(subSurfaceConstructionAssignments.doorConstruction());
  EXPECT_FALSE(subSurfaceConstructionAssignments.glassDoorConstruction());
  EXPECT_FALSE(subSurfaceConstructionAssignments.overheadDoorConstruction());
  EXPECT_FALSE(subSurfaceConstructionAssignments.skylightConstruction());
  EXPECT_TRUE(subSurfaceConstructionAssignments.tubularDaylightDomeConstruction());
  EXPECT_TRUE(subSurfaceConstructionAssignments.tubularDaylightDiffuserConstruction());

  subSurfaceConstructionAssignments.resetTubularDaylightDomeConstruction();
  EXPECT_FALSE(subSurfaceConstructionAssignments.fixedWindowConstruction());
  EXPECT_FALSE(subSurfaceConstructionAssignments.operableWindowConstruction());
  EXPECT_FALSE(subSurfaceConstructionAssignments.doorConstruction());
  EXPECT_FALSE(subSurfaceConstructionAssignments.glassDoorConstruction());
  EXPECT_FALSE(subSurfaceConstructionAssignments.overheadDoorConstruction());
  EXPECT_FALSE(subSurfaceConstructionAssignments.skylightConstruction());
  EXPECT_FALSE(subSurfaceConstructionAssignments.tubularDaylightDomeConstruction());
  EXPECT_TRUE(subSurfaceConstructionAssignments.tubularDaylightDiffuserConstruction());

  subSurfaceConstructionAssignments.resetTubularDaylightDiffuserConstruction();
  EXPECT_FALSE(subSurfaceConstructionAssignments.fixedWindowConstruction());
  EXPECT_FALSE(subSurfaceConstructionAssignments.operableWindowConstruction());
  EXPECT_FALSE(subSurfaceConstructionAssignments.doorConstruction());
  EXPECT_FALSE(subSurfaceConstructionAssignments.glassDoorConstruction());
  EXPECT_FALSE(subSurfaceConstructionAssignments.overheadDoorConstruction());
  EXPECT_FALSE(subSurfaceConstructionAssignments.skylightConstruction());
  EXPECT_FALSE(subSurfaceConstructionAssignments.tubularDaylightDomeConstruction());
  EXPECT_FALSE(subSurfaceConstructionAssignments.tubularDaylightDiffuserConstruction());
}

TEST_F(EPModelFixture, SubSurfaceConstructionAssignments_RemovingConstructionClearsSlot) {
  Model model;
  SubSurfaceConstructionAssignments assignments(model);
  Construction door(model);
  ASSERT_TRUE(assignments.setDoorConstruction(door));

  EXPECT_FALSE(door.remove().empty());
  EXPECT_FALSE(assignments.doorConstruction());
}

TEST_F(EPModelFixture, SubSurfaceConstructionAssignments_Merge) {
  Model model;
  SubSurfaceConstructionAssignments assignments(model);
  SubSurfaceConstructionAssignments other(model);
  Construction ownDoor(model);
  Construction otherDoor(model);
  Construction otherSkylight(model);
  ASSERT_TRUE(assignments.setDoorConstruction(ownDoor));
  ASSERT_TRUE(other.setDoorConstruction(otherDoor));
  ASSERT_TRUE(other.setSkylightConstruction(otherSkylight));

  assignments.merge(other);

  ASSERT_TRUE(assignments.doorConstruction());
  ASSERT_TRUE(assignments.skylightConstruction());
  EXPECT_EQ(ownDoor, *assignments.doorConstruction());
  EXPECT_EQ(otherSkylight, *assignments.skylightConstruction());
  EXPECT_FALSE(assignments.fixedWindowConstruction());

  ASSERT_TRUE(other.doorConstruction());
  EXPECT_EQ(otherDoor, *other.doorConstruction());
}

TEST_F(EPModelFixture, SubSurfaceConstructionAssignments_Clone) {

  Model model;
  SubSurfaceConstructionAssignments assignments(model);

  auto constructionWithMaterial = [&model](const std::string& name) -> Construction {
    Construction construction(model);
    construction.setName(name);
    StandardOpaqueMaterial material(model);
    material.setName("Material " + name);
    EXPECT_TRUE(construction.setLayers({material}));
    return construction;
  };

  auto fixedWindowConstruction = constructionWithMaterial("FixedWindow");
  auto operableWindowConstruction = constructionWithMaterial("OperableWindow");
  auto doorConstruction = constructionWithMaterial("Door");
  auto glassDoorConstruction = constructionWithMaterial("GlassDoor");
  auto overheadDoorConstruction = constructionWithMaterial("OverheadDoor");
  auto skylightConstruction = constructionWithMaterial("Skylight");
  auto tubularDaylightDomeConstruction = constructionWithMaterial("TubularDaylightDome");
  auto tubularDaylightDiffuserConstruction = constructionWithMaterial("TubularDaylightDiffuser");
  ASSERT_TRUE(assignments.setFixedWindowConstruction(fixedWindowConstruction));
  ASSERT_TRUE(assignments.setOperableWindowConstruction(operableWindowConstruction));
  ASSERT_TRUE(assignments.setDoorConstruction(doorConstruction));
  ASSERT_TRUE(assignments.setGlassDoorConstruction(glassDoorConstruction));
  ASSERT_TRUE(assignments.setOverheadDoorConstruction(overheadDoorConstruction));
  ASSERT_TRUE(assignments.setSkylightConstruction(skylightConstruction));
  ASSERT_TRUE(assignments.setTubularDaylightDomeConstruction(tubularDaylightDomeConstruction));
  ASSERT_TRUE(assignments.setTubularDaylightDiffuserConstruction(tubularDaylightDiffuserConstruction));

  EXPECT_EQ(1, model.getConcreteModelObjects<SubSurfaceConstructionAssignments>().size());
  EXPECT_EQ(8, model.getConcreteModelObjects<Construction>().size());
  EXPECT_EQ(8, model.getConcreteModelObjects<StandardOpaqueMaterial>().size());

  // TODO: Need to implement clone(Model&) and resources() for deep copy...
  // {
  //   // Clone in another model
  //   Model model2;
  //   auto clone = assignments.clone(model2).cast<SubSurfaceConstructionAssignments>();
  //   EXPECT_EQ(1, model2.getConcreteModelObjects<SubSurfaceConstructionAssignments>().size());
  //   EXPECT_EQ(8, model2.getConcreteModelObjects<Construction>().size());
  //   EXPECT_EQ(8, model2.getConcreteModelObjects<StandardOpaqueMaterial>().size());
  //   EXPECT_TRUE(clone.fixedWindowConstruction());
  //   EXPECT_TRUE(clone.operableWindowConstruction());
  //   EXPECT_TRUE(clone.doorConstruction());
  //   EXPECT_TRUE(clone.glassDoorConstruction());
  //   EXPECT_TRUE(clone.overheadDoorConstruction());
  //   EXPECT_TRUE(clone.skylightConstruction());
  //   EXPECT_TRUE(clone.tubularDaylightDomeConstruction());
  //   EXPECT_TRUE(clone.tubularDaylightDiffuserConstruction());
  // }

  auto clone_ = model.addObject(assignments.idfObject());
  ASSERT_TRUE(clone_);
  auto clone = clone_->cast<SubSurfaceConstructionAssignments>();
  EXPECT_EQ(2, model.getConcreteModelObjects<SubSurfaceConstructionAssignments>().size());
  EXPECT_EQ(8, model.getConcreteModelObjects<Construction>().size());
  EXPECT_EQ(8, model.getConcreteModelObjects<StandardOpaqueMaterial>().size());
  ASSERT_TRUE(clone.fixedWindowConstruction());
  EXPECT_EQ(fixedWindowConstruction, *clone.fixedWindowConstruction());
  ASSERT_TRUE(clone.operableWindowConstruction());
  EXPECT_EQ(operableWindowConstruction, *clone.operableWindowConstruction());
  ASSERT_TRUE(clone.doorConstruction());
  EXPECT_EQ(doorConstruction, *clone.doorConstruction());
  ASSERT_TRUE(clone.glassDoorConstruction());
  EXPECT_EQ(glassDoorConstruction, *clone.glassDoorConstruction());
  ASSERT_TRUE(clone.overheadDoorConstruction());
  EXPECT_EQ(overheadDoorConstruction, *clone.overheadDoorConstruction());
  ASSERT_TRUE(clone.skylightConstruction());
  EXPECT_EQ(skylightConstruction, *clone.skylightConstruction());
  ASSERT_TRUE(clone.tubularDaylightDomeConstruction());
  EXPECT_EQ(tubularDaylightDomeConstruction, *clone.tubularDaylightDomeConstruction());
  ASSERT_TRUE(clone.tubularDaylightDiffuserConstruction());
  EXPECT_EQ(tubularDaylightDiffuserConstruction, *clone.tubularDaylightDiffuserConstruction());
}
