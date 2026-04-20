/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/WindowPropertyStormWindow.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, WindowPropertyStormWindow_DefaultConstructor) {
  Model model;
  WindowPropertyStormWindow stormWindow(model);
  EXPECT_EQ(WindowPropertyStormWindow::iddObjectType(), stormWindow.iddObject().type());
}

TEST_F(EPModelFixture, WindowPropertyStormWindow_ScalarAccessors_RoundTrip) {
  Model model;
  WindowPropertyStormWindow stormWindow(model);

  EXPECT_TRUE(stormWindow.setDistanceBetweenStormGlassLayerandAdjacentGlass(0.11));
  EXPECT_DOUBLE_EQ(0.11, stormWindow.distanceBetweenStormGlassLayerandAdjacentGlass());
  stormWindow.resetDistanceBetweenStormGlassLayerandAdjacentGlass();
  EXPECT_TRUE(stormWindow.isDistanceBetweenStormGlassLayerandAdjacentGlassDefaulted());

  EXPECT_TRUE(stormWindow.setMonththatStormGlassLayerisPutOn(2));
  EXPECT_EQ(2, stormWindow.monththatStormGlassLayerisPutOn());

  EXPECT_TRUE(stormWindow.setDayofMonththatStormGlassLayerisPutOn(15));
  EXPECT_EQ(15, stormWindow.dayofMonththatStormGlassLayerisPutOn());

  EXPECT_TRUE(stormWindow.setMonththatStormGlassLayerisTakenOff(4));
  EXPECT_EQ(4, stormWindow.monththatStormGlassLayerisTakenOff());

  EXPECT_TRUE(stormWindow.setDayofMonththatStormGlassLayerisTakenOff(20));
  EXPECT_EQ(20, stormWindow.dayofMonththatStormGlassLayerisTakenOff());
}
