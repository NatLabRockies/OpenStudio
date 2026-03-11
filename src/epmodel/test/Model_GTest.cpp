/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"

#include "../AirLoopHVAC.hpp"
#include "../AirLoopHVAC_Impl.hpp"
#include "../Branch.hpp"
#include "../Branch_Impl.hpp"
#include "../BranchList.hpp"
#include "../BranchList_Impl.hpp"
#include "../Model.hpp"
#include "../Node.hpp"

#include "../../utilities/idf/IdfFile.hpp"
#include "../../utilities/idf/IdfExtensibleGroup.hpp"
#include "../../utilities/idf/IdfObject.hpp"
#include <utilities/idd/AirLoopHVAC_FieldEnums.hxx>
#include <utilities/idd/Branch_FieldEnums.hxx>
#include <utilities/idd/BranchList_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, Model_TransientNodeFactory) {
  Model model;

  Node nodeA = model.getOrCreateTransientByName<Node>("Node A");
  Node nodeA2 = model.getOrCreateTransientByName<Node>("node a");

  EXPECT_EQ(nodeA, nodeA2);
  EXPECT_EQ("Node A", nodeA.nameString());

  EXPECT_THROW(model.getOrCreateTransientByName<Node>(""), openstudio::Exception);
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
