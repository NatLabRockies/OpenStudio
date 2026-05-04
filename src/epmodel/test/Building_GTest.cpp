/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ParentObject/Building.hpp"
#include "../ParentObject/Building_Impl.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, Building_DefaultConstructor) {
  Model model;
  auto building = model.getUniqueModelObject<Building>();
  EXPECT_EQ(Building::iddObjectType(), building.iddObject().type());
}

TEST_F(EPModelFixture, Building_ScalarAccessors_RoundTrip) {
  Model model;
  auto building = model.getUniqueModelObject<Building>();

  EXPECT_TRUE(building.isNorthAxisDefaulted());
  EXPECT_DOUBLE_EQ(0.0, building.northAxis());

  EXPECT_TRUE(building.setNorthAxis(45.0));
  EXPECT_FALSE(building.isNorthAxisDefaulted());
  EXPECT_DOUBLE_EQ(45.0, building.northAxis());

  building.resetNorthAxis();
  EXPECT_TRUE(building.isNorthAxisDefaulted());
  EXPECT_DOUBLE_EQ(0.0, building.northAxis());
}
