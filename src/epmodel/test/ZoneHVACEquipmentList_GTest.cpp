/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <algorithm>
#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../HVACComponent/ThermalZone_Impl.hpp"
#include "../ModelObject/ZoneHVACEquipmentConnections.hpp"
#include "../ModelObject/ZoneHVACEquipmentList.hpp"
#include "../ModelObject/ZoneHVACEquipmentList_Impl.hpp"
#include "../Schedule/Schedule.hpp"
#include "../Schedule/Schedule_Impl.hpp"
#include "../Schedule/ScheduleConstant.hpp"
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

  EXPECT_TRUE(equipmentList.addEquipment(terminal.cast<ModelObject>()));
  EXPECT_TRUE(equipmentList.addEquipment(terminal.cast<ModelObject>()));

  const auto equipment = equipmentList.equipment();
  ASSERT_EQ(1u, equipment.size());
  EXPECT_EQ(terminal.cast<ModelObject>(), equipment.front());

  EXPECT_TRUE(equipmentList.removeEquipment(terminal.cast<ModelObject>()));
  EXPECT_TRUE(equipmentList.equipment().empty());
}

TEST_F(EPModelFixture, API_ZoneHVACEquipmentList_ThermalZoneConstructor_LinksConnections) {
  Model model;
  ThermalZone zone(model);

  ZoneHVACEquipmentList equipmentList(zone);

  EXPECT_EQ(zone, equipmentList.thermalZone());
  auto connections = zone.getImpl<detail::ThermalZone_Impl>()->zoneHVACEquipmentConnections();
  ASSERT_TRUE(connections);
  auto linkedEquipmentList = connections->zoneHVACEquipmentList();
  EXPECT_EQ(equipmentList, linkedEquipmentList);
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

  EXPECT_TRUE(equipmentList.removeEquipment(terminal.cast<ModelObject>()));
  EXPECT_TRUE(equipmentList.equipment().empty());
}

TEST_F(EPModelFixture, API_ZoneHVACEquipmentList_RemoveFirstEntry_ReindexesEntries) {
  Model model;
  ZoneHVACEquipmentList equipmentList(model);
  AirTerminalSingleDuctConstantVolumeReheat terminal1(model);
  AirTerminalSingleDuctConstantVolumeReheat terminal2(model);
  AirTerminalSingleDuctConstantVolumeReheat terminal3(model);

  EXPECT_TRUE(equipmentList.addEquipment(terminal1.cast<ModelObject>()));
  EXPECT_TRUE(equipmentList.addEquipment(terminal2.cast<ModelObject>()));
  EXPECT_TRUE(equipmentList.addEquipment(terminal3.cast<ModelObject>()));

  const auto beforeRemoval = equipmentList.equipment();
  ASSERT_EQ(3u, beforeRemoval.size());
  EXPECT_EQ(terminal1.cast<ModelObject>(), beforeRemoval[0]);
  EXPECT_EQ(terminal2.cast<ModelObject>(), beforeRemoval[1]);
  EXPECT_EQ(terminal3.cast<ModelObject>(), beforeRemoval[2]);

  EXPECT_TRUE(equipmentList.removeEquipment(terminal1.cast<ModelObject>()));

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

TEST_F(EPModelFixture, API_ZoneHVACEquipmentList_PrioritiesAndOrderedEquipment) {
  Model model;
  ZoneHVACEquipmentList equipmentList(model);
  AirTerminalSingleDuctConstantVolumeReheat terminal1(model);
  AirTerminalSingleDuctConstantVolumeReheat terminal2(model);
  AirTerminalSingleDuctConstantVolumeReheat terminal3(model);

  EXPECT_TRUE(equipmentList.addEquipment(terminal1.cast<ModelObject>()));
  EXPECT_TRUE(equipmentList.addEquipment(terminal2.cast<ModelObject>()));
  EXPECT_TRUE(equipmentList.addEquipment(terminal3.cast<ModelObject>()));

  EXPECT_TRUE(equipmentList.setCoolingPriority(terminal3.cast<ModelObject>(), 1u));
  EXPECT_TRUE(equipmentList.setHeatingPriority(terminal3.cast<ModelObject>(), 2u));

  const auto coolingOrder = equipmentList.equipmentInCoolingOrder();
  ASSERT_EQ(3u, coolingOrder.size());
  EXPECT_EQ(terminal3.cast<ModelObject>(), coolingOrder[0]);
  EXPECT_EQ(terminal1.cast<ModelObject>(), coolingOrder[1]);
  EXPECT_EQ(terminal2.cast<ModelObject>(), coolingOrder[2]);

  const auto heatingOrder = equipmentList.equipmentInHeatingOrder();
  ASSERT_EQ(3u, heatingOrder.size());
  EXPECT_EQ(terminal1.cast<ModelObject>(), heatingOrder[0]);
  EXPECT_EQ(terminal3.cast<ModelObject>(), heatingOrder[1]);
  EXPECT_EQ(terminal2.cast<ModelObject>(), heatingOrder[2]);

  EXPECT_EQ(1u, equipmentList.coolingPriority(terminal3.cast<ModelObject>()));
  EXPECT_EQ(2u, equipmentList.coolingPriority(terminal1.cast<ModelObject>()));
  EXPECT_EQ(3u, equipmentList.coolingPriority(terminal2.cast<ModelObject>()));

  EXPECT_EQ(1u, equipmentList.heatingPriority(terminal1.cast<ModelObject>()));
  EXPECT_EQ(2u, equipmentList.heatingPriority(terminal3.cast<ModelObject>()));
  EXPECT_EQ(3u, equipmentList.heatingPriority(terminal2.cast<ModelObject>()));
}

TEST_F(EPModelFixture, API_ZoneHVACEquipmentList_SequentialFractionSchedules) {
  Model model;
  ZoneHVACEquipmentList equipmentList(model);
  AirTerminalSingleDuctConstantVolumeReheat terminal(model);
  ScheduleConstant coolingFractionSchedule(model);
  ScheduleConstant heatingFractionSchedule(model);

  ASSERT_TRUE(coolingFractionSchedule.setValue(0.4));
  ASSERT_TRUE(heatingFractionSchedule.setValue(0.6));
  ASSERT_TRUE(equipmentList.addEquipment(terminal.cast<ModelObject>()));
  ASSERT_TRUE(equipmentList.setLoadDistributionScheme("SequentialLoad"));

  EXPECT_TRUE(equipmentList.setSequentialCoolingFractionSchedule(terminal.cast<ModelObject>(), coolingFractionSchedule));
  EXPECT_TRUE(equipmentList.setSequentialHeatingFractionSchedule(terminal.cast<ModelObject>(), heatingFractionSchedule));

  auto coolingSchedule = equipmentList.sequentialCoolingFractionSchedule(terminal.cast<ModelObject>());
  ASSERT_TRUE(coolingSchedule);
  EXPECT_EQ(coolingFractionSchedule.cast<Schedule>(), *coolingSchedule);
  ASSERT_TRUE(equipmentList.sequentialCoolingFraction(terminal.cast<ModelObject>()));
  EXPECT_DOUBLE_EQ(0.4, *equipmentList.sequentialCoolingFraction(terminal.cast<ModelObject>()));

  auto heatingSchedule = equipmentList.sequentialHeatingFractionSchedule(terminal.cast<ModelObject>());
  ASSERT_TRUE(heatingSchedule);
  EXPECT_EQ(heatingFractionSchedule.cast<Schedule>(), *heatingSchedule);
  ASSERT_TRUE(equipmentList.sequentialHeatingFraction(terminal.cast<ModelObject>()));
  EXPECT_DOUBLE_EQ(0.6, *equipmentList.sequentialHeatingFraction(terminal.cast<ModelObject>()));

  EXPECT_TRUE(equipmentList.setSequentialCoolingFraction(terminal.cast<ModelObject>(), 0.2));
  EXPECT_TRUE(equipmentList.sequentialCoolingFraction(terminal.cast<ModelObject>()));
  EXPECT_DOUBLE_EQ(0.2, *equipmentList.sequentialCoolingFraction(terminal.cast<ModelObject>()));

  EXPECT_TRUE(equipmentList.setLoadDistributionScheme("UniformLoad"));
  EXPECT_FALSE(equipmentList.sequentialCoolingFractionSchedule(terminal.cast<ModelObject>()));
  EXPECT_FALSE(equipmentList.sequentialHeatingFractionSchedule(terminal.cast<ModelObject>()));
}
