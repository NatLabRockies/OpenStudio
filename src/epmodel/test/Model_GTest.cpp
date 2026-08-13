/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include <cmath>

#include "EPModelFixture.hpp"

#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/AirLoopHVAC_Impl.hpp"
#include "../ModelObject/Branch.hpp"
#include "../ModelObject/BranchList.hpp"
#include "../ModelObject/BranchList_Impl.hpp"
#include "../ModelObject/Branch_Impl.hpp"
#include "../ModelObject/FluidPropertiesName.hpp"
#include "../Model.hpp"
#include "../ResourceObject/ScheduleTypeLimits.hpp"
#include "../StraightComponent/Node.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"

#include "../../utilities/idf/IdfFile.hpp"
#include "../../utilities/idf/IdfExtensibleGroup.hpp"
#include "../../utilities/idf/IdfObject.hpp"
#include <utilities/idd/AirLoopHVAC_FieldEnums.hxx>
#include <utilities/idd/Branch_FieldEnums.hxx>
#include <utilities/idd/BranchList_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

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
