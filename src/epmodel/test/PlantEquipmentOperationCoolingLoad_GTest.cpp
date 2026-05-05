/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/HVACComponent.hpp"
#include "../PlantEquipmentOperationScheme/PlantEquipmentOperationCoolingLoad.hpp"
#include "../StraightComponent/BoilerHotWater.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, PlantEquipmentOperationCoolingLoad_DefaultConstructor) {
  Model model;
  PlantEquipmentOperationCoolingLoad coolingLoad(model);
  EXPECT_EQ(PlantEquipmentOperationCoolingLoad::iddObjectType(), coolingLoad.iddObject().type());
  EXPECT_FALSE(coolingLoad.nameString().empty());
}

TEST_F(EPModelFixture, PlantEquipmentOperationCoolingLoad_RangeEquipmentApi) {
  Model model;
  PlantEquipmentOperationCoolingLoad coolingLoad(model);
  BoilerHotWater boiler(model);
  BoilerHotWater boiler2(model);
  BoilerHotWater boiler3(model);

  EXPECT_DOUBLE_EQ(1e9, coolingLoad.maximumUpperLimit());
  EXPECT_DOUBLE_EQ(0.0, coolingLoad.minimumLowerLimit());
  ASSERT_EQ(1u, coolingLoad.loadRangeUpperLimits().size());
  EXPECT_TRUE(coolingLoad.equipment(coolingLoad.maximumUpperLimit()).empty());

  EXPECT_TRUE(coolingLoad.addEquipment(boiler));
  EXPECT_FALSE(coolingLoad.addEquipment(boiler));
  ASSERT_EQ(1u, coolingLoad.equipment(coolingLoad.maximumUpperLimit()).size());
  EXPECT_EQ(boiler.cast<HVACComponent>(), coolingLoad.equipment(coolingLoad.maximumUpperLimit()).front());

  EXPECT_TRUE(coolingLoad.addLoadRange(1000.0, {boiler2}));
  auto upperLimits = coolingLoad.loadRangeUpperLimits();
  ASSERT_EQ(2u, upperLimits.size());
  EXPECT_DOUBLE_EQ(1000.0, upperLimits.front());
  ASSERT_EQ(1u, coolingLoad.equipment(1000.0).size());
  EXPECT_EQ(boiler2.cast<HVACComponent>(), coolingLoad.equipment(1000.0).front());

  EXPECT_TRUE(coolingLoad.replaceEquipment({boiler3}));
  ASSERT_EQ(1u, coolingLoad.equipment(1000.0).size());
  EXPECT_EQ(boiler2.cast<HVACComponent>(), coolingLoad.equipment(1000.0).front());
  ASSERT_EQ(1u, coolingLoad.equipment(coolingLoad.maximumUpperLimit()).size());
  EXPECT_EQ(boiler3.cast<HVACComponent>(), coolingLoad.equipment(coolingLoad.maximumUpperLimit()).front());

  auto removed = coolingLoad.removeLoadRange(1000.0);
  ASSERT_EQ(1u, removed.size());
  EXPECT_EQ(boiler2.cast<HVACComponent>(), removed.front());
  EXPECT_EQ(1u, coolingLoad.loadRangeUpperLimits().size());
}
