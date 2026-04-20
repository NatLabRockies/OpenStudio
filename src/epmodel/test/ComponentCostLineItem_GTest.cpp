/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/ComponentCostLineItem.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ComponentCostLineItem_DefaultConstructor) {
  Model model;
  ComponentCostLineItem componentCostLineItem(model);
  EXPECT_EQ(ComponentCostLineItem::iddObjectType(), componentCostLineItem.iddObject().type());
}

TEST_F(EPModelFixture, ComponentCostLineItem_ScalarAccessors_RoundTrip) {
  Model model;
  ComponentCostLineItem componentCostLineItem(model);

  ASSERT_TRUE(componentCostLineItem.type());
  EXPECT_TRUE(componentCostLineItem.type()->empty());
  if (componentCostLineItem.objectEndUseKey()) {
    EXPECT_TRUE(componentCostLineItem.objectEndUseKey()->empty());
  }
  EXPECT_FALSE(componentCostLineItem.costperEach());
  EXPECT_FALSE(componentCostLineItem.costperArea());
  EXPECT_FALSE(componentCostLineItem.costperUnitofOutputCapacity());
  EXPECT_FALSE(componentCostLineItem.costperUnitofOutputCapacityperCOP());
  EXPECT_FALSE(componentCostLineItem.costperVolume());
  EXPECT_FALSE(componentCostLineItem.costperVolumeRate());
  EXPECT_FALSE(componentCostLineItem.costperEnergyperTemperatureDifference());
  EXPECT_FALSE(componentCostLineItem.quantity());

  EXPECT_TRUE(componentCostLineItem.setType("Construction"));
  ASSERT_TRUE(componentCostLineItem.type());
  EXPECT_EQ("Construction", componentCostLineItem.type().get());

  EXPECT_TRUE(componentCostLineItem.setLineItemType("General"));
  EXPECT_EQ("General", componentCostLineItem.lineItemType());

  EXPECT_TRUE(componentCostLineItem.setItemName("Test Item"));
  EXPECT_EQ("Test Item", componentCostLineItem.itemName());

  EXPECT_TRUE(componentCostLineItem.setObjectEndUseKey("InteriorLighting"));
  ASSERT_TRUE(componentCostLineItem.objectEndUseKey());
  EXPECT_EQ("InteriorLighting", componentCostLineItem.objectEndUseKey().get());

  EXPECT_TRUE(componentCostLineItem.setCostperEach(100.0));
  ASSERT_TRUE(componentCostLineItem.costperEach());
  EXPECT_DOUBLE_EQ(100.0, componentCostLineItem.costperEach().get());

  EXPECT_TRUE(componentCostLineItem.setCostperArea(5.25));
  ASSERT_TRUE(componentCostLineItem.costperArea());
  EXPECT_DOUBLE_EQ(5.25, componentCostLineItem.costperArea().get());

  EXPECT_TRUE(componentCostLineItem.setCostperUnitofOutputCapacity(10.0));
  ASSERT_TRUE(componentCostLineItem.costperUnitofOutputCapacity());
  EXPECT_DOUBLE_EQ(10.0, componentCostLineItem.costperUnitofOutputCapacity().get());

  EXPECT_TRUE(componentCostLineItem.setCostperUnitofOutputCapacityperCOP(3.0));
  ASSERT_TRUE(componentCostLineItem.costperUnitofOutputCapacityperCOP());
  EXPECT_DOUBLE_EQ(3.0, componentCostLineItem.costperUnitofOutputCapacityperCOP().get());

  EXPECT_TRUE(componentCostLineItem.setCostperVolume(1.5));
  ASSERT_TRUE(componentCostLineItem.costperVolume());
  EXPECT_DOUBLE_EQ(1.5, componentCostLineItem.costperVolume().get());

  EXPECT_TRUE(componentCostLineItem.setCostperVolumeRate(7.0));
  ASSERT_TRUE(componentCostLineItem.costperVolumeRate());
  EXPECT_DOUBLE_EQ(7.0, componentCostLineItem.costperVolumeRate().get());

  EXPECT_TRUE(componentCostLineItem.setCostperEnergyperTemperatureDifference(0.42));
  ASSERT_TRUE(componentCostLineItem.costperEnergyperTemperatureDifference());
  EXPECT_DOUBLE_EQ(0.42, componentCostLineItem.costperEnergyperTemperatureDifference().get());

  EXPECT_TRUE(componentCostLineItem.setQuantity(9.0));
  ASSERT_TRUE(componentCostLineItem.quantity());
  EXPECT_DOUBLE_EQ(9.0, componentCostLineItem.quantity().get());

  componentCostLineItem.resetType();
  componentCostLineItem.resetObjectEndUseKey();
  componentCostLineItem.resetCostperEach();
  componentCostLineItem.resetCostperArea();
  componentCostLineItem.resetCostperUnitofOutputCapacity();
  componentCostLineItem.resetCostperUnitofOutputCapacityperCOP();
  componentCostLineItem.resetCostperVolume();
  componentCostLineItem.resetCostperVolumeRate();
  componentCostLineItem.resetCostperEnergyperTemperatureDifference();
  componentCostLineItem.resetQuantity();

  ASSERT_TRUE(componentCostLineItem.type());
  EXPECT_TRUE(componentCostLineItem.type()->empty());
  if (componentCostLineItem.objectEndUseKey()) {
    EXPECT_TRUE(componentCostLineItem.objectEndUseKey()->empty());
  }
  EXPECT_FALSE(componentCostLineItem.costperEach());
  EXPECT_FALSE(componentCostLineItem.costperArea());
  EXPECT_FALSE(componentCostLineItem.costperUnitofOutputCapacity());
  EXPECT_FALSE(componentCostLineItem.costperUnitofOutputCapacityperCOP());
  EXPECT_FALSE(componentCostLineItem.costperVolume());
  EXPECT_FALSE(componentCostLineItem.costperVolumeRate());
  EXPECT_FALSE(componentCostLineItem.costperEnergyperTemperatureDifference());
  EXPECT_FALSE(componentCostLineItem.quantity());

  const auto values = ComponentCostLineItem::lineItemTypeValues();
  EXPECT_FALSE(values.empty());
}
