/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../StraightComponent/Node.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, API_AirLoopHVACZoneSplitter_DefaultConstructor) {
  Model model;
  AirLoopHVACZoneSplitter splitter(model);
  EXPECT_EQ(AirLoopHVACZoneSplitter::iddObjectType(), splitter.iddObject().type());
  EXPECT_FALSE(splitter.nameString().empty());
}

TEST_F(EPModelFixture, API_AirLoopHVACZoneSplitter_DefaultPortsAndOutlets) {
  Model model;
  AirLoopHVACZoneSplitter splitter(model);

  EXPECT_EQ(0u, splitter.nextBranchIndex());
  EXPECT_FALSE(splitter.lastOutletModelObject());
  EXPECT_TRUE(splitter.outletModelObjects().empty());
}

TEST_F(EPModelFixture, API_AirLoopHVACZoneSplitter_ScalarAccessors_RoundTrip) {
  Model model;
  AirLoopHVACZoneSplitter splitter(model);

  EXPECT_TRUE(splitter.setName("Zone Splitter Roundtrip"));
  ASSERT_TRUE(splitter.name());
  EXPECT_EQ("Zone Splitter Roundtrip", splitter.nameString());
}

TEST_F(EPModelFixture, API_AirLoopHVACZoneSplitter_SetOutletModelObjectCreatesMissingBranchRows) {
  Model model;
  AirLoopHVACZoneSplitter splitter(model);
  Node branchNode0(model);
  Node branchNode1(model);

  ASSERT_TRUE(splitter.setOutletModelObject(0u, branchNode0.cast<ModelObject>()));
  ASSERT_TRUE(splitter.setOutletModelObject(1u, branchNode1.cast<ModelObject>()));

  ASSERT_EQ(2u, splitter.outletModelObjects().size());
  ASSERT_TRUE(splitter.outletModelObject(0u));
  ASSERT_TRUE(splitter.outletModelObject(1u));
  EXPECT_EQ(branchNode0.cast<ModelObject>(), *splitter.outletModelObject(0u));
  EXPECT_EQ(branchNode1.cast<ModelObject>(), *splitter.outletModelObject(1u));
  EXPECT_EQ(2u, splitter.nextBranchIndex());
}

TEST_F(EPModelFixture, API_AirLoopHVACZoneSplitter_RemovePortCompactsPointersAndReverseSources) {
  Model model;
  AirLoopHVACZoneSplitter splitter(model);
  Node branchNode0(model);
  Node branchNode1(model);

  ASSERT_TRUE(splitter.setOutletModelObject(0u, branchNode0.cast<ModelObject>()));
  ASSERT_TRUE(splitter.setOutletModelObject(1u, branchNode1.cast<ModelObject>()));
  ASSERT_EQ(1u, branchNode0.sources().size());
  ASSERT_EQ(1u, branchNode1.sources().size());

  splitter.removePortForBranch(0u);

  EXPECT_TRUE(branchNode0.sources().empty());
  ASSERT_EQ(1u, splitter.outletModelObjects().size());
  EXPECT_EQ(branchNode1.cast<ModelObject>(), *splitter.outletModelObject(0u));
  EXPECT_EQ(1u, branchNode1.sources().size());
}
