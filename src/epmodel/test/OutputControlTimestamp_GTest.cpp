/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"

#include "../ModelObject/OutputControlTimestamp.hpp"
#include "../ModelObject/OutputControlTimestamp_Impl.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, OutputControlTimestamp_DefaultConstructor) {
  Model model;
  auto object = model.getUniqueModelObject<OutputControlTimestamp>();

  EXPECT_EQ(OutputControlTimestamp::iddObjectType(), object.iddObject().type());
  EXPECT_FALSE(object.iso8601Format());
  EXPECT_FALSE(object.timestampAtBeginningOfInterval());
}

TEST_F(EPModelFixture, OutputControlTimestamp_ScalarAccessors_RoundTrip) {
  Model model;
  auto object = model.getUniqueModelObject<OutputControlTimestamp>();

  EXPECT_TRUE(object.setISO8601Format(true));
  EXPECT_TRUE(object.iso8601Format());
  EXPECT_TRUE(object.setISO8601Format(false));
  EXPECT_FALSE(object.iso8601Format());

  EXPECT_TRUE(object.setTimestampAtBeginningOfInterval(true));
  EXPECT_TRUE(object.timestampAtBeginningOfInterval());
  EXPECT_TRUE(object.setTimestampAtBeginningOfInterval(false));
  EXPECT_FALSE(object.timestampAtBeginningOfInterval());
}
