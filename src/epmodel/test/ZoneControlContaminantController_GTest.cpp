/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/ZoneControlContaminantController.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneControlContaminantController_DefaultConstructor) {
  Model model;
  ZoneControlContaminantController controller(model);
  EXPECT_EQ(ZoneControlContaminantController::iddObjectType(), controller.iddObject().type());
}

TEST_F(EPModelFixture, ZoneControlContaminantController_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneControlContaminantController controller(model);

  EXPECT_TRUE(controller.setName("Controller A"));
  EXPECT_EQ("Controller A", controller.nameString());
}
