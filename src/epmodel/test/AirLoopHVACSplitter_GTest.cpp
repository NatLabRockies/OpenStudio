/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/AirLoopHVACSplitter.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirLoopHVACSplitter_DefaultConstructor) {
  Model model;
  AirLoopHVACSplitter splitter(model);
  EXPECT_EQ(AirLoopHVACSplitter::iddObjectType(), splitter.iddObject().type());
}

TEST_F(EPModelFixture, AirLoopHVACSplitter_ScalarAccessors_RoundTrip) {
  Model model;
  AirLoopHVACSplitter splitter(model);

  EXPECT_TRUE(splitter.setName("Main DOAS Splitter"));
  EXPECT_EQ("Main DOAS Splitter", splitter.nameString());
}
