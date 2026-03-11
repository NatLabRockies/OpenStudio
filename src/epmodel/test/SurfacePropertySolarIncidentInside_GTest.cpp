/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/SurfacePropertySolarIncidentInside.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SurfacePropertySolarIncidentInside_DefaultConstructor) {
  Model model;
  SurfacePropertySolarIncidentInside solarIncidentInside(model);
  EXPECT_EQ(SurfacePropertySolarIncidentInside::iddObjectType(), solarIncidentInside.iddObject().type());
}

TEST_F(EPModelFixture, SurfacePropertySolarIncidentInside_ScalarAccessors_RoundTrip) {
  Model model;
  SurfacePropertySolarIncidentInside solarIncidentInside(model);

  EXPECT_TRUE(solarIncidentInside.setName("Interior Solar Incident"));
  EXPECT_EQ("Interior Solar Incident", solarIncidentInside.nameString());
}
