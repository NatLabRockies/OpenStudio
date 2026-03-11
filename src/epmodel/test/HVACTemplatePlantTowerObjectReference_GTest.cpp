/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/HVACTemplatePlantTowerObjectReference.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, HVACTemplatePlantTowerObjectReference_DefaultConstructor) {
  Model model;
  HVACTemplatePlantTowerObjectReference object(model);
  EXPECT_EQ(HVACTemplatePlantTowerObjectReference::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, HVACTemplatePlantTowerObjectReference_ScalarAccessors_RoundTrip) {
  Model model;
  HVACTemplatePlantTowerObjectReference object(model);

  EXPECT_TRUE(object.isCoolingTowerObjectTypeDefaulted());
  EXPECT_EQ("CoolingTower:SingleSpeed", object.coolingTowerObjectType());

  EXPECT_TRUE(object.setCoolingTowerObjectType("CoolingTower:VariableSpeed"));
  EXPECT_EQ("CoolingTower:VariableSpeed", object.coolingTowerObjectType());
  EXPECT_FALSE(object.isCoolingTowerObjectTypeDefaulted());
  object.resetCoolingTowerObjectType();
  EXPECT_TRUE(object.isCoolingTowerObjectTypeDefaulted());
  EXPECT_EQ("CoolingTower:SingleSpeed", object.coolingTowerObjectType());

  EXPECT_TRUE(object.setPriority(2.0));
  ASSERT_TRUE(object.priority());
  EXPECT_DOUBLE_EQ(2.0, object.priority().get());
  object.resetPriority();
  EXPECT_FALSE(object.priority());

  EXPECT_TRUE(object.setTemplatePlantLoopType("MixedWater"));
  ASSERT_TRUE(object.templatePlantLoopType());
  EXPECT_EQ("MixedWater", object.templatePlantLoopType().get());
  object.resetTemplatePlantLoopType();
  if (object.templatePlantLoopType()) {
    EXPECT_NE("MixedWater", object.templatePlantLoopType().get());
  }

  EXPECT_FALSE(object.setCoolingTowerObjectType("InvalidCoolingTowerObjectType"));

  EXPECT_GE(HVACTemplatePlantTowerObjectReference::coolingTowerObjectTypeValues().size(), 1u);
  EXPECT_GE(HVACTemplatePlantTowerObjectReference::templatePlantLoopTypeValues().size(), 1u);
}
