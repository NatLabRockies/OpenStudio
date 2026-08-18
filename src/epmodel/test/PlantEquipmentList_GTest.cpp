/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/HVACComponent.hpp"
#include "../ModelObject/PlantEquipmentList.hpp"
#include "../ModelObject/PlantEquipmentList_Impl.hpp"
#include "../StraightComponent/BoilerHotWater.hpp"
#include "../StraightComponent/BoilerHotWater_Impl.hpp"

#include <utilities/idd/PlantEquipmentList_FieldEnums.hxx>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>

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

TEST_F(EPModelFixture, PlantEquipmentList_ComponentRemovalErasesTheCompleteEquipmentRow) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-plant-equipment-list-component-removal.idf");
  Model model;
  PlantEquipmentList equipmentList(model);
  PlantEquipmentList secondEquipmentList(model);
  BoilerHotWater boiler(model);

  ASSERT_TRUE(equipmentList.setName("Component Removal Equipment List"));
  ASSERT_TRUE(secondEquipmentList.setName("Second Component Removal Equipment List"));
  ASSERT_TRUE(boiler.setName("Removed Equipment List Boiler"));
  ASSERT_TRUE(equipmentList.addEquipment(boiler));
  ASSERT_TRUE(secondEquipmentList.addEquipment(boiler));
  ASSERT_EQ(1u, equipmentList.numExtensibleGroups());
  ASSERT_EQ(1u, secondEquipmentList.numExtensibleGroups());

  EXPECT_FALSE(boiler.remove().empty());
  EXPECT_TRUE(equipmentList.equipment().empty());
  EXPECT_EQ(0u, equipmentList.numExtensibleGroups());
  EXPECT_TRUE(secondEquipmentList.equipment().empty());
  EXPECT_EQ(0u, secondEquipmentList.numExtensibleGroups());
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedList = loadedModel->getConcreteModelObjectByName<PlantEquipmentList>("Component Removal Equipment List");
  ASSERT_TRUE(loadedList);
  EXPECT_TRUE(loadedList->equipment().empty());
  EXPECT_EQ(0u, loadedList->numExtensibleGroups());
  auto loadedSecondList = loadedModel->getConcreteModelObjectByName<PlantEquipmentList>("Second Component Removal Equipment List");
  ASSERT_TRUE(loadedSecondList);
  EXPECT_TRUE(loadedSecondList->equipment().empty());
  EXPECT_EQ(0u, loadedSecondList->numExtensibleGroups());
  EXPECT_FALSE(loadedModel->getConcreteModelObjectByName<BoilerHotWater>("Removed Equipment List Boiler"));

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, PlantEquipmentList_LoadCanonicalizationRemovesDuplicateEquipmentRows) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-plant-equipment-list-duplicate-load.idf");
  Model model;
  PlantEquipmentList equipmentList(model);
  BoilerHotWater boiler(model);

  ASSERT_TRUE(equipmentList.setName("Duplicate Equipment List"));
  ASSERT_TRUE(boiler.setName("Duplicate Equipment Boiler"));
  ASSERT_TRUE(equipmentList.addEquipment(boiler));
  auto firstGroup = equipmentList.extensibleGroups().front().optionalCast<openstudio::WorkspaceExtensibleGroup>();
  ASSERT_TRUE(firstGroup);
  ASSERT_TRUE(firstGroup->setString(openstudio::PlantEquipmentListExtensibleFields::EquipmentObjectType, "Chiller:Electric:EIR", false));
  auto duplicateGroup = equipmentList.pushExtensibleGroup().optionalCast<openstudio::WorkspaceExtensibleGroup>();
  ASSERT_TRUE(duplicateGroup);
  ASSERT_TRUE(duplicateGroup->setString(openstudio::PlantEquipmentListExtensibleFields::EquipmentObjectType,
                                        boiler.iddObject().name(), false));
  ASSERT_TRUE(duplicateGroup->setPointer(openstudio::PlantEquipmentListExtensibleFields::EquipmentName, boiler.handle(), false));
  ASSERT_EQ(2u, equipmentList.numExtensibleGroups());
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedList = loadedModel->getConcreteModelObjectByName<PlantEquipmentList>("Duplicate Equipment List");
  ASSERT_TRUE(loadedList);
  ASSERT_EQ(1u, loadedList->equipment().size());
  EXPECT_EQ("Duplicate Equipment Boiler", loadedList->equipment().front().nameString());
  EXPECT_EQ(1u, loadedList->numExtensibleGroups());
  auto loadedGroup = loadedList->extensibleGroups().front().optionalCast<openstudio::WorkspaceExtensibleGroup>();
  ASSERT_TRUE(loadedGroup);
  EXPECT_EQ("Boiler:HotWater",
            loadedGroup->getString(openstudio::PlantEquipmentListExtensibleFields::EquipmentObjectType, true).get());

  openstudio::filesystem::remove(idfPath);
}
