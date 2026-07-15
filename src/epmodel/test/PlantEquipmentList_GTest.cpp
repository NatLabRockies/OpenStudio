/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/HVACComponent.hpp"
#include "../ModelObject/PlantEquipmentList.hpp"
#include "../StraightComponent/BoilerHotWater.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, PlantEquipmentList_AddReplaceRemoveEquipment) {
  Model model;
  PlantEquipmentList equipmentList(model);
  BoilerHotWater boiler(model);
  BoilerHotWater boiler2(model);

  EXPECT_EQ(PlantEquipmentList::iddObjectType(), equipmentList.iddObject().type());
  EXPECT_TRUE(equipmentList.equipment().empty());

  EXPECT_TRUE(equipmentList.addEquipment(boiler));
  EXPECT_FALSE(equipmentList.addEquipment(boiler));
  ASSERT_EQ(1u, equipmentList.equipment().size());
  EXPECT_EQ(boiler.cast<HVACComponent>(), equipmentList.equipment().front());

  EXPECT_TRUE(equipmentList.replaceEquipment({boiler2, boiler2, boiler}));
  const auto equipment = equipmentList.equipment();
  ASSERT_EQ(2u, equipment.size());
  EXPECT_EQ(boiler2.cast<HVACComponent>(), equipment[0]);
  EXPECT_EQ(boiler.cast<HVACComponent>(), equipment[1]);

  EXPECT_TRUE(equipmentList.removeEquipment(boiler2));
  ASSERT_EQ(1u, equipmentList.equipment().size());
  EXPECT_EQ(boiler.cast<HVACComponent>(), equipmentList.equipment().front());

  equipmentList.removeAllEquipment();
  EXPECT_TRUE(equipmentList.equipment().empty());
}
