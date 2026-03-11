/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"

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
