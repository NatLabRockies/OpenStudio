/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/HVACTemplatePlantTower.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, HVACTemplatePlantTower_DefaultConstructor) {
  Model model;
  HVACTemplatePlantTower object(model);
  EXPECT_EQ(HVACTemplatePlantTower::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, HVACTemplatePlantTower_ScalarAccessors_RoundTrip) {
  Model model;
  HVACTemplatePlantTower object(model);

  EXPECT_TRUE(object.setTowerType("SingleSpeed"));
  EXPECT_EQ("SingleSpeed", object.towerType());

  EXPECT_TRUE(object.setHighSpeedNominalCapacity(120000.0));
  ASSERT_TRUE(object.highSpeedNominalCapacity());
  EXPECT_DOUBLE_EQ(120000.0, object.highSpeedNominalCapacity().get());
  EXPECT_FALSE(object.isHighSpeedNominalCapacityAutosized());
  EXPECT_FALSE(object.isHighSpeedNominalCapacityDefaulted());
  object.autosizeHighSpeedNominalCapacity();
  EXPECT_TRUE(object.isHighSpeedNominalCapacityAutosized());
  object.resetHighSpeedNominalCapacity();
  EXPECT_TRUE(object.isHighSpeedNominalCapacityDefaulted());

  EXPECT_TRUE(object.setHighSpeedFanPower(4000.0));
  ASSERT_TRUE(object.highSpeedFanPower());
  EXPECT_DOUBLE_EQ(4000.0, object.highSpeedFanPower().get());
  object.autosizeHighSpeedFanPower();
  EXPECT_TRUE(object.isHighSpeedFanPowerAutosized());
  object.resetHighSpeedFanPower();
  EXPECT_TRUE(object.isHighSpeedFanPowerDefaulted());

  EXPECT_TRUE(object.setLowSpeedNominalCapacity(70000.0));
  ASSERT_TRUE(object.lowSpeedNominalCapacity());
  EXPECT_DOUBLE_EQ(70000.0, object.lowSpeedNominalCapacity().get());
  object.autosizeLowSpeedNominalCapacity();
  EXPECT_TRUE(object.isLowSpeedNominalCapacityAutosized());

  EXPECT_TRUE(object.setLowSpeedFanPower(1200.0));
  ASSERT_TRUE(object.lowSpeedFanPower());
  EXPECT_DOUBLE_EQ(1200.0, object.lowSpeedFanPower().get());
  object.autosizeLowSpeedFanPower();
  EXPECT_TRUE(object.isLowSpeedFanPowerAutosized());

  EXPECT_TRUE(object.setFreeConvectionCapacity(20000.0));
  ASSERT_TRUE(object.freeConvectionCapacity());
  EXPECT_DOUBLE_EQ(20000.0, object.freeConvectionCapacity().get());
  object.autosizeFreeConvectionCapacity();
  EXPECT_TRUE(object.isFreeConvectionCapacityAutosized());

  EXPECT_TRUE(object.setPriority("5"));
  ASSERT_TRUE(object.priority());
  EXPECT_EQ("5", object.priority().get());
  object.resetPriority();
  ASSERT_TRUE(object.priority());
  EXPECT_NE("5", object.priority().get());

  EXPECT_TRUE(object.setSizingFactor(1.15));
  EXPECT_DOUBLE_EQ(1.15, object.sizingFactor());
  EXPECT_FALSE(object.isSizingFactorDefaulted());
  object.resetSizingFactor();
  EXPECT_TRUE(object.isSizingFactorDefaulted());

  EXPECT_TRUE(object.setTemplatePlantLoopType("MixedWater"));
  ASSERT_TRUE(object.templatePlantLoopType());
  EXPECT_EQ("MixedWater", object.templatePlantLoopType().get());
  object.resetTemplatePlantLoopType();
  ASSERT_TRUE(object.templatePlantLoopType());
  EXPECT_NE("MixedWater", object.templatePlantLoopType().get());

  EXPECT_FALSE(object.setTowerType("InvalidTowerType"));
  EXPECT_FALSE(object.setHighSpeedNominalCapacity(0.0));
  EXPECT_FALSE(object.setHighSpeedFanPower(0.0));
  EXPECT_FALSE(object.setLowSpeedNominalCapacity(0.0));
  EXPECT_FALSE(object.setLowSpeedFanPower(0.0));
  EXPECT_FALSE(object.setFreeConvectionCapacity(-1.0));
  EXPECT_FALSE(object.setSizingFactor(0.0));
  EXPECT_FALSE(object.setTemplatePlantLoopType("InvalidTemplateLoopType"));

  EXPECT_GE(HVACTemplatePlantTower::towerTypeValues().size(), 1u);
  EXPECT_GE(HVACTemplatePlantTower::templatePlantLoopTypeValues().size(), 1u);
}
