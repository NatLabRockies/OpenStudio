/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/SurfaceContaminantSourceAndSinkGenericDepositionVelocitySink.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SurfaceContaminantSourceAndSinkGenericDepositionVelocitySink_DefaultConstructor) {
  Model model;
  SurfaceContaminantSourceAndSinkGenericDepositionVelocitySink obj(model);
  EXPECT_EQ(SurfaceContaminantSourceAndSinkGenericDepositionVelocitySink::iddObjectType(), obj.iddObject().type());
}

TEST_F(EPModelFixture, SurfaceContaminantSourceAndSinkGenericDepositionVelocitySink_ScalarAccessors_RoundTrip) {
  Model model;
  SurfaceContaminantSourceAndSinkGenericDepositionVelocitySink obj(model);

  // Deposition Velocity: optional, minimum 0.0, no default
  EXPECT_FALSE(obj.depositionVelocity());
  EXPECT_TRUE(obj.setDepositionVelocity(0.5));
  ASSERT_TRUE(obj.depositionVelocity());
  EXPECT_DOUBLE_EQ(0.5, obj.depositionVelocity().get());
  // boundary: 0.0 is valid (minimum 0.0 inclusive)
  EXPECT_TRUE(obj.setDepositionVelocity(0.0));
  ASSERT_TRUE(obj.depositionVelocity());
  EXPECT_DOUBLE_EQ(0.0, obj.depositionVelocity().get());
  // below minimum should fail
  EXPECT_FALSE(obj.setDepositionVelocity(-0.1));
  // reset
  obj.resetDepositionVelocity();
  EXPECT_FALSE(obj.depositionVelocity());
}
