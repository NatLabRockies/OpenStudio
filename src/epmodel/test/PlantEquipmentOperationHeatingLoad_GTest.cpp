/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/HVACComponent.hpp"
#include "../PlantEquipmentOperationScheme/PlantEquipmentOperationHeatingLoad.hpp"
#include "../StraightComponent/BoilerHotWater.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, PlantEquipmentOperationHeatingLoad_DefaultConstructor) {
  Model model;
  PlantEquipmentOperationHeatingLoad heatingLoad(model);
  EXPECT_EQ(PlantEquipmentOperationHeatingLoad::iddObjectType(), heatingLoad.iddObject().type());
  EXPECT_FALSE(heatingLoad.nameString().empty());
}

TEST_F(EPModelFixture, PlantEquipmentOperationHeatingLoad_RangeEquipmentApi) {
  Model model;
  PlantEquipmentOperationHeatingLoad heatingLoad(model);
  BoilerHotWater boiler(model);
  BoilerHotWater boiler2(model);

  EXPECT_DOUBLE_EQ(1e9, heatingLoad.maximumUpperLimit());
  EXPECT_DOUBLE_EQ(0.0, heatingLoad.minimumLowerLimit());
  ASSERT_EQ(1u, heatingLoad.loadRangeUpperLimits().size());
  EXPECT_TRUE(heatingLoad.equipment(heatingLoad.maximumUpperLimit()).empty());

  EXPECT_TRUE(heatingLoad.addEquipment(boiler));
  EXPECT_FALSE(heatingLoad.addEquipment(boiler));
  ASSERT_EQ(1u, heatingLoad.equipment(heatingLoad.maximumUpperLimit()).size());
  EXPECT_EQ(boiler.cast<HVACComponent>(), heatingLoad.equipment(heatingLoad.maximumUpperLimit()).front());

  EXPECT_TRUE(heatingLoad.addLoadRange(1000.0, {boiler2}));
  auto upperLimits = heatingLoad.loadRangeUpperLimits();
  ASSERT_EQ(2u, upperLimits.size());
  EXPECT_DOUBLE_EQ(1000.0, upperLimits.front());
  ASSERT_EQ(1u, heatingLoad.equipment(1000.0).size());
  EXPECT_EQ(boiler2.cast<HVACComponent>(), heatingLoad.equipment(1000.0).front());

  auto removed = heatingLoad.removeLoadRange(1000.0);
  ASSERT_EQ(1u, removed.size());
  EXPECT_EQ(boiler2.cast<HVACComponent>(), removed.front());
  EXPECT_EQ(1u, heatingLoad.loadRangeUpperLimits().size());
}
