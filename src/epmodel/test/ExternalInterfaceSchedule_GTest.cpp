/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Schedule/ExternalInterfaceSchedule.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ExternalInterfaceSchedule_Constructor) {
  Model model;
  ExternalInterfaceSchedule object(model);
  EXPECT_EQ(ExternalInterfaceSchedule::iddObjectType(), object.iddObject().type());
  EXPECT_DOUBLE_EQ(0.0, object.initialValue());

  ExternalInterfaceSchedule withInitial(model, 10.0);
  EXPECT_EQ(ExternalInterfaceSchedule::iddObjectType(), withInitial.iddObject().type());
  EXPECT_DOUBLE_EQ(10.0, withInitial.initialValue());
}

TEST_F(EPModelFixture, ExternalInterfaceSchedule_ScalarAccessors_RoundTrip) {
  Model model;
  ExternalInterfaceSchedule object(model);

  EXPECT_TRUE(object.setInitialValue(11.25));
  EXPECT_DOUBLE_EQ(11.25, object.initialValue());

  EXPECT_TRUE(object.setInitialValue(-0.5));
  EXPECT_DOUBLE_EQ(-0.5, object.initialValue());
}
