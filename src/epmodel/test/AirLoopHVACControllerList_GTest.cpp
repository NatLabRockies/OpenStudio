/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"

#include "../AirLoopHVACControllerList.hpp"
#include "../AirLoopHVACControllerList_Impl.hpp"
#include "../ControllerOutdoorAir.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, API_AirLoopHVACControllerList_DefaultConstructor) {
  Model model;
  AirLoopHVACControllerList controllerList(model);
  EXPECT_EQ(AirLoopHVACControllerList::iddObjectType(), controllerList.iddObject().type());
  EXPECT_TRUE(controllerList.controllers().empty());
  EXPECT_FALSE(controllerList.optionalControllerOutdoorAir());
}

TEST_F(EPModelFixture, API_AirLoopHVACControllerList_SetControllerOutdoorAir) {
  Model model;
  AirLoopHVACControllerList controllerList(model);
  ControllerOutdoorAir controller1(model);
  ControllerOutdoorAir controller2(model);

  EXPECT_TRUE(controllerList.getImpl<detail::AirLoopHVACControllerList_Impl>()->setControllerOutdoorAir(controller1));
  auto optionalController = controllerList.optionalControllerOutdoorAir();
  ASSERT_TRUE(optionalController);
  EXPECT_EQ(controller1, *optionalController);

  EXPECT_TRUE(controllerList.getImpl<detail::AirLoopHVACControllerList_Impl>()->setControllerOutdoorAir(controller2));
  optionalController = controllerList.optionalControllerOutdoorAir();
  ASSERT_TRUE(optionalController);
  EXPECT_EQ(controller2, *optionalController);
}
