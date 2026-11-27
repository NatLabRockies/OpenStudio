/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include <cmath>

#include "EPModelFixture.hpp"

#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/AirLoopHVAC_Impl.hpp"
#include "../LayeredConstruction/Construction.hpp"
#include "../LayeredConstruction/Construction_Impl.hpp"
#include "../ModelObject/Branch.hpp"
#include "../ModelObject/BranchList.hpp"
#include "../ModelObject/BranchList_Impl.hpp"
#include "../ModelObject/Branch_Impl.hpp"
#include "../ModelObject/FluidPropertiesName.hpp"
#include "../Model.hpp"
#include "../ResourceObject/ScheduleTypeLimits.hpp"
#include "../ResourceObject/ScheduleTypeLimits_Impl.hpp"
#include "../StraightComponent/Node.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"

#include "../../utilities/idf/IdfFile.hpp"
#include "../../utilities/idf/IdfExtensibleGroup.hpp"
#include "../../utilities/idf/IdfObject.hpp"
#include "../../utilities/idf/Workspace.hpp"
#include "../../utilities/core/Filesystem.hpp"
#include "../../utilities/core/PathHelpers.hpp"
#include "../../utilities/filetypes/WorkflowJSON.hpp"
#include <utilities/idd/AirLoopHVAC_FieldEnums.hxx>
#include <utilities/idd/Branch_FieldEnums.hxx>
#include <utilities/idd/BranchList_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Schedule_Constant_FieldEnums.hxx>
#include <utilities/idd/ScheduleTypeLimits_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, Model_EnsuresSharedRefrigerantProperties) {
  Model model;

  EXPECT_FALSE(model.ensureRefrigerantProperties("NotARefrigerant"));
  EXPECT_TRUE(model.getObjectsByType(openstudio::IddObjectType::FluidProperties_Name).empty());

  EXPECT_TRUE(model.ensureRefrigerantProperties("r410A"));
  ASSERT_TRUE(model.getObjectByTypeAndName(openstudio::IddObjectType::FluidProperties_Name, "R410a"));
  EXPECT_EQ(2u, model.getObjectsByType(openstudio::IddObjectType::FluidProperties_Temperatures).size());
  EXPECT_EQ(7u, model.getObjectsByType(openstudio::IddObjectType::FluidProperties_Saturated).size());
  EXPECT_EQ(88u, model.getObjectsByType(openstudio::IddObjectType::FluidProperties_Superheated).size());

  const auto objectCount = model.numObjects();
  EXPECT_TRUE(model.ensureRefrigerantProperties("R410a"));
  EXPECT_EQ(objectCount, model.numObjects());

  EXPECT_TRUE(model.ensureRefrigerantProperties("R11"));
  EXPECT_EQ(2u, model.getObjectsByType(openstudio::IddObjectType::FluidProperties_Name).size());
  EXPECT_TRUE(model.getObjectByTypeAndName(openstudio::IddObjectType::FluidProperties_Name, "R11"));
}

TEST_F(EPModelFixture, Model_ProvidesEverySupportedRefrigerantDataset) {
  for (const char* refrigerant : {"R11", "R12", "R22", "R123", "R134a", "R404a", "R407a", "R410a", "NH3", "R507a", "R744"}) {
    Model model;
    EXPECT_TRUE(model.ensureRefrigerantProperties(refrigerant)) << refrigerant;
    EXPECT_TRUE(model.getObjectByTypeAndName(openstudio::IddObjectType::FluidProperties_Name, refrigerant)) << refrigerant;
    EXPECT_GT(model.getObjectsByType(openstudio::IddObjectType::FluidProperties_Temperatures).size(), 0u) << refrigerant;
    EXPECT_GT(model.getObjectsByType(openstudio::IddObjectType::FluidProperties_Saturated).size(), 0u) << refrigerant;
    EXPECT_GT(model.getObjectsByType(openstudio::IddObjectType::FluidProperties_Superheated).size(), 0u) << refrigerant;
  }
}

TEST_F(EPModelFixture, Model_TrustsCallerOwnedRefrigerantProperties) {
  Model model;
  FluidPropertiesName customProperties(model);
  ASSERT_TRUE(customProperties.setFluidName("R410a"));
  ASSERT_TRUE(customProperties.setFluidType("Refrigerant"));

  const auto objectCount = model.numObjects();
  EXPECT_TRUE(model.ensureRefrigerantProperties("R410a"));
  EXPECT_EQ(objectCount, model.numObjects());
  EXPECT_TRUE(model.getObjectsByType(openstudio::IddObjectType::FluidProperties_Saturated).empty());
  EXPECT_TRUE(model.getObjectsByType(openstudio::IddObjectType::FluidProperties_Superheated).empty());
}

TEST_F(EPModelFixture, Model_TransientNodeFactory) {
  Model model;

  Node nodeA = model.getOrCreateTransientByName<Node>("Node A");
  Node nodeA2 = model.getOrCreateTransientByName<Node>("node a");

  EXPECT_EQ(nodeA, nodeA2);
  EXPECT_EQ("Node A", nodeA.nameString());

  EXPECT_THROW(model.getOrCreateTransientByName<Node>(""), openstudio::Exception);
}

TEST_F(EPModelFixture, Model_FromGenericWorkspaceHydratesConcreteTypes) {
  openstudio::IdfFile idf(openstudio::IddFileType::EnergyPlus);
  openstudio::IdfObject constructionObject(openstudio::IddObjectType::Construction);
  ASSERT_TRUE(constructionObject.setName("Generic Workspace Construction"));
  idf.addObject(constructionObject);

  openstudio::IdfObject limitsObject(openstudio::IddObjectType::ScheduleTypeLimits);
  ASSERT_TRUE(limitsObject.setName("Generic Workspace Limits"));
  ASSERT_TRUE(limitsObject.setString(openstudio::ScheduleTypeLimitsFields::NumericType, "Continuous"));
  idf.addObject(limitsObject);

  openstudio::IdfObject scheduleObject(openstudio::IddObjectType::Schedule_Constant);
  ASSERT_TRUE(scheduleObject.setName("Generic Workspace Schedule"));
  ASSERT_TRUE(scheduleObject.setString(openstudio::Schedule_ConstantFields::ScheduleTypeLimitsName, "Generic Workspace Limits"));
  ASSERT_TRUE(scheduleObject.setDouble(openstudio::Schedule_ConstantFields::HourlyValue, 1.0));
  idf.addObject(scheduleObject);

  openstudio::Workspace workspace(idf, openstudio::StrictnessLevel::Draft);
  const auto workspaceConstruction = workspace.getObjectByTypeAndName(openstudio::IddObjectType::Construction, "Generic Workspace Construction");
  ASSERT_TRUE(workspaceConstruction);

  Model model(workspace);
  const auto construction = model.getConcreteModelObjectByName<Construction>("Generic Workspace Construction");
  ASSERT_TRUE(construction);
  EXPECT_EQ(workspaceConstruction->handle(), construction->handle());
  EXPECT_EQ(1u, model.getConcreteModelObjects<Construction>().size());

  const auto schedule = model.getConcreteModelObjectByName<ScheduleConstant>("Generic Workspace Schedule");
  ASSERT_TRUE(schedule);
  const auto limits = schedule->scheduleTypeLimits();
  ASSERT_TRUE(limits);
  EXPECT_EQ("Generic Workspace Limits", limits->nameString());
}

TEST_F(EPModelFixture, Model_FromEPModelWorkspacePreservesConcreteTransientObjects) {
  Model source;
  Construction sourceConstruction(source);
  ASSERT_TRUE(sourceConstruction.setName("EPModel Construction"));
  Node sourceNode = source.getOrCreateTransientByName<Node>("EPModel Transient Node");

  openstudio::Workspace workspace = source;
  Model copy(workspace);

  const auto construction = copy.getConcreteModelObjectByName<Construction>("EPModel Construction");
  ASSERT_TRUE(construction);
  EXPECT_EQ(sourceConstruction.handle(), construction->handle());

  const auto node = copy.getConcreteModelObjectByName<Node>("EPModel Transient Node");
  ASSERT_TRUE(node);
  EXPECT_EQ(sourceNode.handle(), node->handle());
  EXPECT_TRUE(node->getImpl<openstudio::detail::WorkspaceObject_Impl>()->isTransient());
}

TEST_F(EPModelFixture, Model_AlwaysOnContinuousSchedule) {
  Model model;

  auto schedule = model.alwaysOnContinuousSchedule();
  EXPECT_EQ(model.alwaysOnContinuousScheduleName(), schedule.nameString());
  EXPECT_DOUBLE_EQ(1.0, schedule.cast<ScheduleConstant>().value());

  auto limits = schedule.scheduleTypeLimits();
  ASSERT_TRUE(limits);
  ASSERT_TRUE(limits->numericType());
  EXPECT_EQ("Continuous", limits->numericType().get());
  ASSERT_TRUE(limits->lowerLimitValue());
  EXPECT_DOUBLE_EQ(0.0, limits->lowerLimitValue().get());
  ASSERT_TRUE(limits->upperLimitValue());
  EXPECT_DOUBLE_EQ(1.0, limits->upperLimitValue().get());
  EXPECT_TRUE(limits->isUnitTypeDefaulted());

  auto schedule2 = model.alwaysOnContinuousSchedule();
  EXPECT_EQ(schedule.handle(), schedule2.handle());
}

TEST_F(EPModelFixture, Model_AlwaysOnContinuousSchedule_ReusesNearlyUnitSchedule) {
  Model model;

  ScheduleConstant schedule(model);
  ASSERT_TRUE(schedule.setName(model.alwaysOnContinuousScheduleName()));
  ASSERT_TRUE(schedule.setValue(std::nextafter(1.0, 2.0)));

  ScheduleTypeLimits limits(model);
  ASSERT_TRUE(limits.setNumericType("Continuous"));
  limits.resetUnitType();
  ASSERT_TRUE(limits.setLowerLimitValue(0.0));
  ASSERT_TRUE(limits.setUpperLimitValue(1.0));
  ASSERT_TRUE(schedule.setScheduleTypeLimits(limits));

  auto reusedSchedule = model.alwaysOnContinuousSchedule();
  EXPECT_EQ(schedule.handle(), reusedSchedule.handle());
}

TEST_F(EPModelFixture, Model_Canonicalize_RepairsHierarchicalAirLoopBranchListBranch) {
  openstudio::IdfFile idf(openstudio::IddFileType::EnergyPlus);

  openstudio::IdfObject airLoopObject(openstudio::IddObjectType::AirLoopHVAC);
  ASSERT_TRUE(airLoopObject.setString(openstudio::AirLoopHVACFields::Name, "Loop A"));
  ASSERT_TRUE(airLoopObject.setString(openstudio::AirLoopHVACFields::BranchListName, "Loop A Branches"));
  idf.addObject(airLoopObject);

  openstudio::IdfObject branchListObject(openstudio::IddObjectType::BranchList);
  ASSERT_TRUE(branchListObject.setName("Loop A Branches"));
  auto branchListGroup = branchListObject.pushExtensibleGroup();
  ASSERT_TRUE(branchListGroup.setString(openstudio::BranchListExtensibleFields::BranchName, "Supply Branch A"));
  idf.addObject(branchListObject);

  openstudio::IdfObject branchObject(openstudio::IddObjectType::Branch);
  ASSERT_TRUE(branchObject.setName("Supply Branch A"));
  auto branchGroup = branchObject.pushExtensibleGroup();
  ASSERT_TRUE(branchGroup.setString(openstudio::BranchExtensibleFields::ComponentObjectType, "NotARealType"));
  ASSERT_TRUE(branchGroup.setString(openstudio::BranchExtensibleFields::ComponentName, "Broken Component"));
  idf.addObject(branchObject);

  Model model(idf);
  auto report = model.canonicalize(SanitizationPolicy::Repair);

  EXPECT_GT(report.infoCount, 0u);

  auto airLoops = model.getConcreteModelObjects<AirLoopHVAC>();
  ASSERT_EQ(1u, airLoops.size());

  auto branchListName = airLoops.front().getString(openstudio::AirLoopHVACFields::BranchListName);
  ASSERT_TRUE(branchListName);
  auto branchListObjectAfter = model.getObjectByTypeAndName(openstudio::IddObjectType::BranchList, *branchListName);
  ASSERT_TRUE(branchListObjectAfter);
  auto branchList = branchListObjectAfter->optionalCast<BranchList>();
  ASSERT_TRUE(branchList);
  EXPECT_FALSE(branchList->branches().empty());

  auto repairedBranchObject = model.getObjectByTypeAndName(openstudio::IddObjectType::Branch, "Supply Branch A");
  ASSERT_TRUE(repairedBranchObject);
  auto repairedBranch = repairedBranchObject->optionalCast<Branch>();
  ASSERT_TRUE(repairedBranch);
  EXPECT_EQ(0u, repairedBranch->numExtensibleGroups());
}

// Workspace::addObjects(std::vector<WorkspaceObject>) stages the objects in Model_Impl::cloneSubset before copying them in.
// The copies must keep their concrete epmodel types, and links between copied objects must point at the copies.
TEST_F(EPModelFixture, Model_AddWorkspaceObjects_KeepsConcreteTypes) {
  Model model;
  ScheduleTypeLimits limits(model);
  ScheduleConstant schedule(model);
  ASSERT_TRUE(schedule.setScheduleTypeLimits(limits));

  {
    // Same model
    const auto copies = model.addObjects(std::vector<openstudio::WorkspaceObject>{schedule});
    ASSERT_EQ(1, copies.size());
    auto copiedSchedule = copies.front().optionalCast<ScheduleConstant>();
    ASSERT_TRUE(copiedSchedule);
    EXPECT_NE(schedule, *copiedSchedule);
    ASSERT_TRUE(copiedSchedule->scheduleTypeLimits());
    EXPECT_EQ(limits, *copiedSchedule->scheduleTypeLimits());
    EXPECT_EQ(2, model.getConcreteModelObjects<ScheduleConstant>().size());
    EXPECT_EQ(1, model.getConcreteModelObjects<ScheduleTypeLimits>().size());
  }

  {
    // Other, non-empty model
    Model model2;
    ScheduleConstant existingSchedule(model2);
    const auto copies = model2.addObjects(std::vector<openstudio::WorkspaceObject>{schedule, limits});
    ASSERT_EQ(2, copies.size());
    auto copiedSchedule = copies[0].optionalCast<ScheduleConstant>();
    auto copiedLimits = copies[1].optionalCast<ScheduleTypeLimits>();
    ASSERT_TRUE(copiedSchedule);
    ASSERT_TRUE(copiedLimits);
    ASSERT_TRUE(copiedSchedule->scheduleTypeLimits());
    EXPECT_EQ(*copiedLimits, *copiedSchedule->scheduleTypeLimits());
    EXPECT_EQ(2, model2.getConcreteModelObjects<ScheduleConstant>().size());
    EXPECT_EQ(1, model2.getConcreteModelObjects<ScheduleTypeLimits>().size());
  }
}

TEST_F(EPModelFixture, Model_WorkflowJSON) {
  Model model;
  EXPECT_FALSE(model.workflowJSON().seedFile());

  openstudio::WorkflowJSON workflow;
  EXPECT_TRUE(workflow.setSeedFile(openstudio::toPath("seed.idf")));
  EXPECT_TRUE(model.setWorkflowJSON(workflow));
  ASSERT_TRUE(model.workflowJSON().seedFile());
  EXPECT_EQ(openstudio::toPath("seed.idf"), *model.workflowJSON().seedFile());

  // clone carries the workflow
  Model clone = model.clone();
  ASSERT_TRUE(clone.workflowJSON().seedFile());
  EXPECT_EQ(openstudio::toPath("seed.idf"), *clone.workflowJSON().seedFile());

  model.resetWorkflowJSON();
  EXPECT_FALSE(model.workflowJSON().seedFile());
}

TEST_F(EPModelFixture, Model_Load_WorkflowJSON) {
  const auto dir = openstudio::tempDir() / openstudio::toPath("epmodel-workflow-" + openstudio::removeBraces(openstudio::createUUID()));
  openstudio::filesystem::create_directories(dir);
  const auto idfPath = dir / openstudio::toPath("in.idf");
  const auto companionDir = openstudio::getCompanionFolder(idfPath);
  openstudio::filesystem::create_directories(companionDir);

  Model model;
  ASSERT_TRUE(model.save(idfPath, true));

  {
    // No workflow.osw in the companion folder
    auto loaded = Model::load(idfPath);
    ASSERT_TRUE(loaded);
    EXPECT_FALSE(loaded->workflowJSON().seedFile());

    // Explicit workflow path that does not exist: fails
    EXPECT_FALSE(Model::load(idfPath, dir / openstudio::toPath("missing.osw")));
  }

  openstudio::WorkflowJSON workflow;
  EXPECT_TRUE(workflow.setSeedFile(openstudio::toPath("in.idf")));
  ASSERT_TRUE(workflow.saveAs(companionDir / openstudio::toPath("workflow.osw")));
  ASSERT_TRUE(workflow.saveAs(dir / openstudio::toPath("other.osw")));

  {
    // workflow.osw in the companion folder is picked up
    auto loaded = Model::load(idfPath);
    ASSERT_TRUE(loaded);
    ASSERT_TRUE(loaded->workflowJSON().seedFile());
    EXPECT_EQ(openstudio::toPath("in.idf"), *loaded->workflowJSON().seedFile());
  }

  {
    // Explicit workflow path
    auto loaded = Model::load(idfPath, dir / openstudio::toPath("other.osw"));
    ASSERT_TRUE(loaded);
    ASSERT_TRUE(loaded->workflowJSON().oswPath());
    // WorkflowJSON stores the canonical path: on macOS the temp dir is under /var, a symlink to /private/var
    EXPECT_EQ(openstudio::filesystem::canonical(dir / openstudio::toPath("other.osw")), *loaded->workflowJSON().oswPath());
  }

  openstudio::filesystem::remove_all(dir);
}
