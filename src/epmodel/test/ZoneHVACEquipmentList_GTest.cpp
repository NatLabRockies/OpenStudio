/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <algorithm>
#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/ZoneHVACEquipmentList.hpp"
#include "../ModelObject/ZoneHVACEquipmentList_Impl.hpp"
#include "../StraightComponent/AirTerminalSingleDuctConstantVolumeReheat.hpp"

#include <utilities/idd/ZoneHVAC_EquipmentList_FieldEnums.hxx>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, API_ZoneHVACEquipmentList_DefaultConstructor) {
  Model model;
  ZoneHVACEquipmentList equipmentList(model);
  EXPECT_EQ(ZoneHVACEquipmentList::iddObjectType(), equipmentList.iddObject().type());
  EXPECT_FALSE(equipmentList.nameString().empty());
}

TEST_F(EPModelFixture, API_ZoneHVACEquipmentList_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneHVACEquipmentList equipmentList(model);

  const auto values = ZoneHVACEquipmentList::loadDistributionSchemeValues();
  EXPECT_FALSE(values.empty());
  EXPECT_EQ(values, ZoneHVACEquipmentList::validLoadDistributionSchemeValues());
  EXPECT_NE(values.cend(), std::find(values.cbegin(), values.cend(), equipmentList.loadDistributionScheme()));

  EXPECT_TRUE(equipmentList.setLoadDistributionScheme("Uniform"));
  EXPECT_EQ("UniformLoad", equipmentList.loadDistributionScheme());
  EXPECT_FALSE(equipmentList.isLoadDistributionSchemeDefaulted());

  equipmentList.resetLoadDistributionScheme();
  EXPECT_TRUE(equipmentList.isLoadDistributionSchemeDefaulted());
  EXPECT_EQ("SequentialLoad", equipmentList.loadDistributionScheme());
}

TEST_F(EPModelFixture, API_ZoneHVACEquipmentList_AddEquipment_RoundTripAndDedupe_ReheatTerminal) {
  Model model;
  ZoneHVACEquipmentList equipmentList(model);
  AirTerminalSingleDuctConstantVolumeReheat terminal(model);

  auto equipmentListImpl = equipmentList.getImpl<detail::ZoneHVACEquipmentList_Impl>();
  ASSERT_TRUE(equipmentListImpl);

  EXPECT_TRUE(equipmentListImpl->addEquipment(terminal.cast<ModelObject>()));
  EXPECT_TRUE(equipmentListImpl->addEquipment(terminal.cast<ModelObject>()));

  const auto equipment = equipmentList.equipment();
  ASSERT_EQ(1u, equipment.size());
  EXPECT_EQ(terminal.cast<ModelObject>(), equipment.front());

  EXPECT_TRUE(equipmentListImpl->removeEquipment(terminal.cast<ModelObject>()));
  EXPECT_TRUE(equipmentList.equipment().empty());
}

TEST_F(EPModelFixture, API_ZoneHVACEquipmentList_StringBackedEntry_ResolvesAndRemoves_ReheatTerminal) {
  Model model;
  ZoneHVACEquipmentList equipmentList(model);
  AirTerminalSingleDuctConstantVolumeReheat terminal(model);

  auto group = equipmentList.pushExtensibleGroup().optionalCast<openstudio::WorkspaceExtensibleGroup>();
  ASSERT_TRUE(group);
  ASSERT_TRUE(group->setString(openstudio::ZoneHVAC_EquipmentListExtensibleFields::ZoneEquipmentObjectType,
                               terminal.iddObject().name(), false));
  ASSERT_TRUE(group->setString(openstudio::ZoneHVAC_EquipmentListExtensibleFields::ZoneEquipmentName, terminal.nameString(), false));
  ASSERT_TRUE(group->setUnsigned(openstudio::ZoneHVAC_EquipmentListExtensibleFields::ZoneEquipmentCoolingSequence, 1u));
  ASSERT_TRUE(group->setUnsigned(openstudio::ZoneHVAC_EquipmentListExtensibleFields::ZoneEquipmentHeatingorNoLoadSequence, 1u));

  const auto equipment = equipmentList.equipment();
  ASSERT_EQ(1u, equipment.size());
  EXPECT_EQ(terminal.cast<ModelObject>(), equipment.front());

  auto equipmentListImpl = equipmentList.getImpl<detail::ZoneHVACEquipmentList_Impl>();
  ASSERT_TRUE(equipmentListImpl);
  EXPECT_TRUE(equipmentListImpl->removeEquipment(terminal.cast<ModelObject>()));
  EXPECT_TRUE(equipmentList.equipment().empty());
}

TEST_F(EPModelFixture, API_ZoneHVACEquipmentList_RemoveFirstEntry_ReindexesEntries) {
  Model model;
  ZoneHVACEquipmentList equipmentList(model);
  AirTerminalSingleDuctConstantVolumeReheat terminal1(model);
  AirTerminalSingleDuctConstantVolumeReheat terminal2(model);
  AirTerminalSingleDuctConstantVolumeReheat terminal3(model);

  auto equipmentListImpl = equipmentList.getImpl<detail::ZoneHVACEquipmentList_Impl>();
  ASSERT_TRUE(equipmentListImpl);

  EXPECT_TRUE(equipmentListImpl->addEquipment(terminal1.cast<ModelObject>()));

  EXPECT_TRUE(equipmentListImpl->addEquipment(terminal2.cast<ModelObject>()));

  EXPECT_TRUE(equipmentListImpl->addEquipment(terminal3.cast<ModelObject>()));

  const auto beforeRemoval = equipmentList.equipment();
  ASSERT_EQ(3u, beforeRemoval.size());
  EXPECT_EQ(terminal1.cast<ModelObject>(), beforeRemoval[0]);
  EXPECT_EQ(terminal2.cast<ModelObject>(), beforeRemoval[1]);
  EXPECT_EQ(terminal3.cast<ModelObject>(), beforeRemoval[2]);

  EXPECT_TRUE(equipmentListImpl->removeEquipment(terminal1.cast<ModelObject>()));

  const auto afterRemoval = equipmentList.equipment();
  ASSERT_EQ(2u, afterRemoval.size());
  EXPECT_EQ(terminal2.cast<ModelObject>(), afterRemoval[0]);
  EXPECT_EQ(terminal3.cast<ModelObject>(), afterRemoval[1]);

  const auto groups = equipmentList.extensibleGroups();
  ASSERT_EQ(2u, groups.size());
  auto firstGroup = groups[0].optionalCast<openstudio::WorkspaceExtensibleGroup>();
  auto secondGroup = groups[1].optionalCast<openstudio::WorkspaceExtensibleGroup>();
  ASSERT_TRUE(firstGroup);
  ASSERT_TRUE(secondGroup);
  EXPECT_EQ(1u, firstGroup->getUnsigned(openstudio::ZoneHVAC_EquipmentListExtensibleFields::ZoneEquipmentCoolingSequence).get());
  EXPECT_EQ(1u, firstGroup->getUnsigned(openstudio::ZoneHVAC_EquipmentListExtensibleFields::ZoneEquipmentHeatingorNoLoadSequence).get());
  EXPECT_EQ(2u, secondGroup->getUnsigned(openstudio::ZoneHVAC_EquipmentListExtensibleFields::ZoneEquipmentCoolingSequence).get());
  EXPECT_EQ(2u, secondGroup->getUnsigned(openstudio::ZoneHVAC_EquipmentListExtensibleFields::ZoneEquipmentHeatingorNoLoadSequence).get());
}
