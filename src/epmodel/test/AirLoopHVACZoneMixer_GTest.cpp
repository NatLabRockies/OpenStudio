/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Mixer/AirLoopHVACZoneMixer.hpp"
#include "../StraightComponent/Node.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, API_AirLoopHVACZoneMixer_DefaultConstructor) {
  Model model;
  AirLoopHVACZoneMixer mixer(model);
  EXPECT_EQ(AirLoopHVACZoneMixer::iddObjectType(), mixer.iddObject().type());
  EXPECT_FALSE(mixer.nameString().empty());
}

TEST_F(EPModelFixture, API_AirLoopHVACZoneMixer_DefaultPortsAndInlets) {
  Model model;
  AirLoopHVACZoneMixer mixer(model);

  EXPECT_EQ(0u, mixer.nextBranchIndex());
  EXPECT_FALSE(mixer.lastInletModelObject());
  EXPECT_TRUE(mixer.inletModelObjects().empty());
}

TEST_F(EPModelFixture, API_AirLoopHVACZoneMixer_ScalarAccessors_RoundTrip) {
  Model model;
  AirLoopHVACZoneMixer mixer(model);

  EXPECT_TRUE(mixer.setName("Zone Mixer Roundtrip"));
  ASSERT_TRUE(mixer.name());
  EXPECT_EQ("Zone Mixer Roundtrip", mixer.nameString());
}

TEST_F(EPModelFixture, API_AirLoopHVACZoneMixer_SetInletModelObjectCreatesMissingBranchRows) {
  Model model;
  AirLoopHVACZoneMixer mixer(model);
  Node branchNode0(model);
  Node branchNode1(model);

  ASSERT_TRUE(mixer.setInletModelObject(0u, branchNode0.cast<ModelObject>()));
  ASSERT_TRUE(mixer.setInletModelObject(1u, branchNode1.cast<ModelObject>()));

  ASSERT_EQ(2u, mixer.inletModelObjects().size());
  ASSERT_TRUE(mixer.inletModelObject(0u));
  ASSERT_TRUE(mixer.inletModelObject(1u));
  EXPECT_EQ(branchNode0.cast<ModelObject>(), *mixer.inletModelObject(0u));
  EXPECT_EQ(branchNode1.cast<ModelObject>(), *mixer.inletModelObject(1u));
  EXPECT_EQ(2u, mixer.nextBranchIndex());
}
