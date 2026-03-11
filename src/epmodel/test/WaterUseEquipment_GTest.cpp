/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../SpaceLoadInstance/WaterUseEquipment.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, WaterUseEquipment_DefaultConstructor) {
  Model model;
  WaterUseEquipment object(model);
  EXPECT_EQ(WaterUseEquipment::iddObjectType(), object.iddObject().type());
  EXPECT_FALSE(object.nameString().empty());
}

TEST_F(EPModelFixture, WaterUseEquipment_ScalarAccessors_RoundTrip) {
  Model model;
  WaterUseEquipment object(model);

  EXPECT_TRUE(object.setEndUseSubcategory("Process"));
  EXPECT_EQ("Process", object.endUseSubcategory());
  object.resetEndUseSubcategory();
  EXPECT_TRUE(object.isEndUseSubcategoryDefaulted());
  EXPECT_EQ("General", object.endUseSubcategory());

  EXPECT_TRUE(object.setPeakFlowRate(0.001));
  EXPECT_DOUBLE_EQ(0.001, object.peakFlowRate());
}
