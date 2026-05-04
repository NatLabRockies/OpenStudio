/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/Timestep.hpp"
#include "../ModelObject/Timestep_Impl.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, Timestep_DefaultConstructor) {
  Model model;
  auto object = model.getUniqueModelObject<Timestep>();

  EXPECT_EQ(Timestep::iddObjectType(), object.iddObject().type());
  EXPECT_FALSE(object.isNumberOfTimestepsPerHourDefaulted());
  EXPECT_EQ(6, object.numberOfTimestepsPerHour());
}

TEST_F(EPModelFixture, Timestep_ScalarAccessors_RoundTrip) {
  Model model;
  auto object = model.getUniqueModelObject<Timestep>();

  EXPECT_TRUE(object.setNumberOfTimestepsPerHour(10));
  EXPECT_EQ(10, object.numberOfTimestepsPerHour());

  object.resetNumberOfTimestepsPerHour();
  EXPECT_TRUE(object.isNumberOfTimestepsPerHourDefaulted());

  EXPECT_TRUE(object.setNumberOfTimestepsPerHour(8));
  EXPECT_EQ(8, object.numberOfTimestepsPerHour());
}
