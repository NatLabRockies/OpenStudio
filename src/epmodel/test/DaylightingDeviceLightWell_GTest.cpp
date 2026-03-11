/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/DaylightingDeviceLightWell.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, DaylightingDeviceLightWell_DefaultConstructor) {
  Model model;
  DaylightingDeviceLightWell lightWell(model);
  EXPECT_EQ(DaylightingDeviceLightWell::iddObjectType(), lightWell.iddObject().type());
}

TEST_F(EPModelFixture, DaylightingDeviceLightWell_ScalarAccessors_RoundTrip) {
  Model model;
  DaylightingDeviceLightWell lightWell(model);

  EXPECT_TRUE(lightWell.setHeightofWell(1.2));
  EXPECT_DOUBLE_EQ(1.2, lightWell.heightofWell());

  EXPECT_TRUE(lightWell.setPerimeterofBottomofWell(12.0));
  EXPECT_DOUBLE_EQ(12.0, lightWell.perimeterofBottomofWell());

  EXPECT_TRUE(lightWell.setAreaofBottomofWell(9.0));
  EXPECT_DOUBLE_EQ(9.0, lightWell.areaofBottomofWell());

  EXPECT_TRUE(lightWell.setVisibleReflectanceofWellWalls(0.7));
  EXPECT_DOUBLE_EQ(0.7, lightWell.visibleReflectanceofWellWalls());
}
